#line 1 "C:\\source\\fossil_depot\\fossil\\Fossil\\src\\finfo.c"
/*
** Copyright (c) 2009 D. Richard Hipp
**
** This program is free software; you can redistribute it and/or
** modify it under the terms of the Simplified BSD License (also
** known as the "2-Clause License" or "FreeBSD License".)

** This program is distributed in the hope that it will be useful,
** but without any warranty; without even the implied warranty of
** merchantability or fitness for a particular purpose.
**
** Author contact information:
**   drh@hwaci.com
**   http://www.hwaci.com/drh/
**
*******************************************************************************
**
** This file contains code to implement the "finfo" command.
*/
#include "config.h"
#include "finfo.h"

/*
** COMMAND: finfo
**
** Usage: %fossil finfo ?OPTIONS? FILENAME
**
** Print the complete change history for a single file going backwards
** in time.  The default mode is -l.
**
** For the -l|--log mode: If "-b|--brief" is specified one line per revision
** is printed, otherwise the full comment is printed.  The "-n|--limit N"
** and "--offset P" options limits the output to the first N changes
** after skipping P changes.
**
** The -i mode will print various facts about FILENAME, including its
** hash and the check-in and time when the current version of the file
** was created.  Use -v for additional information.  Add the -r VERSION
** option to see similar information about the same file for the check-in
** specified by VERSION.
**
** The -s mode prints the status as <status> <revision>.  This is
** a quick status and does not check for up-to-date-ness of the file.
**
** In the -p mode, there's an optional flag "-r|--revision REVISION".
** The specified version (or the latest checked-out version) is printed
** to stdout.  The -p mode is another form of the "cat" command.
**
** Options:
**   -b|--brief           Display a brief (one line / revision) summary
**   --case-sensitive B   Enable or disable case-sensitive filenames.  B is a
**                          boolean: "yes", "no", "true", "false", etc.
**   -i|--id              Print the artifact ID
**   -l|--log             Select log mode (the default)
**   -n|--limit N         Display the first N changes (default unlimited).
**                          N less than 0 means no limit.
**   --offset P           Skip P changes
**   -p|--print           Select print mode
**   -r|--revision R      Print the given revision (or ckout, if none is given)
**                          to stdout (only in print mode)
**   -s|--status          Select status mode (print a status indicator for FILE)
**   -v|--verbose         On the -i option, show all check-ins that use the
**                          file, not just the earliest check-in
**   -W|--width N         Width of lines (default is to auto-detect). Must be
**                          more than 22 or else 0 to indicate no limit.
**
** See also: [[artifact]], [[cat]], [[descendants]], [[info]], [[leaves]]
*/
void finfo_cmd(void){
  db_must_be_within_tree();
  if( find_option("status","s",0) ){
    Stmt q;
    Blob line;
    Blob fname;
    int vid;

    /* We should be done with options.. */
    verify_all_options();

    if( g.argc!=3 ) usage("-s|--status FILENAME");
    vid = db_lget_int("checkout", 0);
    if( vid==0 ){
      fossil_fatal("no check-out to finfo files in");
    }
    vfile_check_signature(vid, CKSIG_ENOTFILE);
    file_tree_name(g.argv[2], &fname, 0, 1);
    db_prepare(&q,
        "SELECT pathname, deleted, rid, chnged, coalesce(origname!=pathname,0)"
        "  FROM vfile WHERE vfile.pathname=%B %s",
        &fname, filename_collation());
    blob_zero(&line);
    if( db_step(&q)==SQLITE_ROW ) {
      Blob uuid;
      int isDeleted = db_column_int(&q, 1);
      int isNew = db_column_int(&q,2) == 0;
      int chnged = db_column_int(&q,3);
      int renamed = db_column_int(&q,4);

      blob_zero(&uuid);
      db_blob(&uuid,
           "SELECT uuid FROM blob, mlink, vfile WHERE "
           "blob.rid = mlink.mid AND mlink.fid = vfile.rid AND "
           "vfile.pathname=%B %s",
           &fname, filename_collation()
      );
      if( isNew ){
        blob_appendf(&line, "new");
      }else if( isDeleted ){
        blob_appendf(&line, "deleted");
      }else if( renamed ){
        blob_appendf(&line, "renamed");
      }else if( chnged ){
        blob_appendf(&line, "edited");
      }else{
        blob_appendf(&line, "unchanged");
      }
      blob_appendf(&line, " ");
      blob_appendf(&line, " %10.10s", blob_str(&uuid));
      blob_reset(&uuid);
    }else{
      blob_appendf(&line, "unknown 0000000000");
    }
    db_finalize(&q);
    fossil_print("%s\n", blob_str(&line));
    blob_reset(&fname);
    blob_reset(&line);
  }else if( find_option("print","p",0) ){
    Blob record;
    Blob fname;
    const char *zRevision = find_option("revision", "r", 1);

    /* We should be done with options.. */
    verify_all_options();

    file_tree_name(g.argv[2], &fname, 0, 1);
    if( zRevision ){
      historical_blob(zRevision, blob_str(&fname), &record, 1);
    }else{
      int rid = db_int(0, "SELECT rid FROM vfile WHERE pathname=%B %s",
                       &fname, filename_collation());
      if( rid==0 ){
        fossil_fatal("no history for file: %b", &fname);
      }
      content_get(rid, &record);
    }
    blob_write_to_file(&record, "-");
    blob_reset(&record);
    blob_reset(&fname);
  }else if( find_option("id","i",0) ){
    Blob fname;
    int rid;
    int whatisFlags = WHATIS_BRIEF;
    const char *zRevision = find_option("revision", "r", 1);
    if( find_option("verbose","v",0)!=0 ) whatisFlags = 0;

    verify_all_options();

    if( zRevision==0 ) zRevision = "current";
    if( g.argc!=3 ) usage("FILENAME");
    file_tree_name(g.argv[2], &fname, 0, 1);
    rid = db_int(0, "SELECT rid FROM blob WHERE uuid ="
                    "  (SELECT uuid FROM files_of_checkin(%Q)"
                    "   WHERE filename=%B %s)",
                 zRevision, &fname, filename_collation());
    if( rid==0 ) {
      fossil_fatal("file not found for revision %s: %s",
                   zRevision, blob_str(&fname));
    }
    whatis_rid(rid,whatisFlags);
    blob_reset(&fname);
  }else{
    Blob line;
    Stmt q;
    Blob fname;
    int rid;
    const char *zFilename;
    const char *zLimit;
    const char *zWidth;
    const char *zOffset;
    int iLimit, iOffset, iBrief, iWidth;

    if( find_option("log","l",0) ){
      /* this is the default, no-op */
    }
    zLimit = find_option("limit","n",1);
    zWidth = find_option("width","W",1);
    iLimit = zLimit ? atoi(zLimit) : -1;
    zOffset = find_option("offset",0,1);
    iOffset = zOffset ? atoi(zOffset) : 0;
    iBrief = find_option("brief","b",0) != 0;
    if( iLimit==0 ){
      iLimit = -1;
    }
    if( zWidth ){
      iWidth = atoi(zWidth);
      if( (iWidth!=0) && (iWidth<=22) ){
        fossil_fatal("-W|--width value must be >22 or 0");
      }
    }else{
      iWidth = -1;
    }

    /* We should be done with options.. */
    verify_all_options();

    if( g.argc!=3 ){
      usage("?-l|--log? ?-b|--brief? FILENAME");
    }
    file_tree_name(g.argv[2], &fname, 0, 1);
    rid = db_int(0, "SELECT rid FROM vfile WHERE pathname=%B %s",
                 &fname, filename_collation());
    if( rid==0 ){
      fossil_fatal("no history for file: %b", &fname);
    }
    zFilename = blob_str(&fname);
    db_prepare(&q,
        "SELECT DISTINCT b.uuid, ci.uuid, date(event.mtime,toLocal()),"
        "       coalesce(event.ecomment, event.comment),"
        "       coalesce(event.euser, event.user),"
        "       (SELECT value FROM tagxref WHERE tagid=%d AND tagtype>0"
                                " AND tagxref.rid=mlink.mid)" /* Tags */
        "  FROM mlink, blob b, event, blob ci, filename"
        " WHERE filename.name=%Q %s"
        "   AND mlink.fnid=filename.fnid"
        "   AND b.rid=mlink.fid"
        "   AND event.objid=mlink.mid"
        "   AND event.objid=ci.rid"
        " ORDER BY event.mtime DESC LIMIT %d OFFSET %d",
        TAG_BRANCH, zFilename, filename_collation(),
        iLimit, iOffset
    );
    blob_zero(&line);
    if( iBrief == 0 ){
      fossil_print("History for %s\n", blob_str(&fname));
    }
    while( db_step(&q)==SQLITE_ROW ){
      const char *zFileUuid = db_column_text(&q, 0);
      const char *zCiUuid = db_column_text(&q,1);
      const char *zDate = db_column_text(&q, 2);
      const char *zCom = db_column_text(&q, 3);
      const char *zUser = db_column_text(&q, 4);
      const char *zBr = db_column_text(&q, 5);
      char *zOut;
      if( zBr==0 ) zBr = "trunk";
      if( iBrief == 0 ){
        fossil_print("%s ", zDate);
        zOut = mprintf(
           "[%S] %s (user: %s, artifact: [%S], branch: %s)",
           zCiUuid, zCom, zUser, zFileUuid, zBr);
        comment_print(zOut, zCom, 11, iWidth, get_comment_format());
        fossil_free(zOut);
      }else{
        blob_reset(&line);
        blob_appendf(&line, "%S ", zCiUuid);
        blob_appendf(&line, "%.10s ", zDate);
        blob_appendf(&line, "%8.8s ", zUser);
        blob_appendf(&line, "%8.8s ", zBr);
        blob_appendf(&line,"%-39.39s", zCom );
        comment_print(blob_str(&line), zCom, 0, iWidth, get_comment_format());
      }
    }
    db_finalize(&q);
    blob_reset(&fname);
  }
}

/*
** COMMAND: cat
**
** Usage: %fossil cat FILENAME ... ?OPTIONS?
**
** Print on standard output the content of one or more files as they exist
** in the repository.  The version currently checked out is shown by default.
** Other versions may be specified using the -r option.
**
** Options:
**    -o|--out OUTFILE         For exactly one given FILENAME, write to OUTFILE
**    -R|--repository REPO     Extract artifacts from repository REPO
**    -r VERSION               The specific check-in containing the file
**
** See also: [[finfo]]
*/
void cat_cmd(void){
  int i;
  Blob content, fname;
  const char *zRev;
  const char *zFileName;
  db_find_and_open_repository(0, 0);
  zRev = find_option("r","r",1);
  zFileName = find_option("out","o",1);

  /* We should be done with options.. */
  verify_all_options();

  if ( zFileName && g.argc>3 ){
    fossil_fatal("output file can only be given when retrieving a single file");
  }

  for(i=2; i<g.argc; i++){
    file_tree_name(g.argv[i], &fname, 0, 1);
    blob_zero(&content);
    historical_blob(zRev, blob_str(&fname), &content, 1);
    if ( g.argc==3 && zFileName ){
      blob_write_to_file(&content, zFileName);
    }else{
      blob_write_to_file(&content, "-");
    }
    blob_reset(&fname);
    blob_reset(&content);
  }
}

/* Values for the debug= query parameter to finfo */
#define FINFO_DEBUG_MLINK  0x01

/*
** WEBPAGE: finfo
** Usage:
**   *  /finfo?name=FILENAME
**   *  /finfo?name=FILENAME&ci=HASH
**
** Show the change history for a single file.  The name=FILENAME query
** parameter gives the filename and is a required parameter.  If the
** ci=HASH parameter is also supplied, then the FILENAME,HASH combination
** identifies a particular version of a file, and in that case all changes
** to that one file version are tracked across both edits and renames.
** If only the name=FILENAME parameter is supplied (if ci=HASH is omitted)
** then the graph shows all changes to any file while it happened
** to be called FILENAME and changes are not tracked across renames.
**
** Additional query parameters:
**
**    a=DATETIME      Only show changes after DATETIME
**    b=DATETIME      Only show changes before DATETIME
**    ci=HASH         identify a particular version of a file and then
**                    track changes to that file across renames
**    m=HASH          Mark this particular file version.
**    n=NUM           Show the first NUM changes only
**    name=FILENAME   (Required) name of file whose history to show
**    brbg            Background color by branch name
**    ubg             Background color by user name
**    from=HASH       Ancestors only (not descendants) of the version of
**                    the file in this particular check-in.
**    to=HASH         If both from= and to= are supplied, only show those
**                    changes on the direct path between the two given
**                    checkins.
**    showid          Show RID values for debugging
**    showsql         Show the SQL query used to gather the data for
**                    the graph
**
** DATETIME may be in any of usual formats, including "now",
** "YYYY-MM-DDTHH:MM:SS.SSS", "YYYYMMDDHHMM", and others.
*/
void finfo_page(void){
  Stmt q;
  const char *zFilename = PD("name","");
  char zPrevDate[20];
  const char *zA;
  const char *zB;
  int n;
  int ridFrom;
  int ridTo = 0;
  int ridCi = 0;
  const char *zCI = P("ci");
  int fnid;
  Blob title;
  Blob sql;
  HQuery url;
  GraphContext *pGraph;
  int brBg = P("brbg")!=0;
  int uBg = P("ubg")!=0;
  int fDebug = atoi(PD("debug","0"));
  int fShowId = P("showid")!=0;
  Stmt qparent;
  int iTableId = timeline_tableid();
  int tmFlags = 0;            /* Viewing mode */
  const char *zStyle;         /* Viewing mode name */
  const char *zMark;          /* Mark this version of the file */
  int selRid = 0;             /* RID of the marked file version */
  int mxfnid;                 /* Maximum filename.fnid value */

  login_check_credentials();
  if( !g.perm.Read ){ login_needed(g.anon.Read); return; }
  fnid = db_int(0, "SELECT fnid FROM filename WHERE name=%Q", zFilename);
  ridCi = zCI ? name_to_rid_www("ci") : 0;
  if( fnid==0 ){
    style_header("No such file");
  }else if( ridCi==0 ){
    style_header("All files named \"%s\"", zFilename);
  }else{
    style_header("History of %s of %s",zFilename, zCI);
  }
  login_anonymous_available();
  tmFlags = timeline_ss_submenu();
  if( tmFlags & TIMELINE_COLUMNAR ){
    zStyle = "Columnar";
  }else if( tmFlags & TIMELINE_COMPACT ){
    zStyle = "Compact";
  }else if( tmFlags & TIMELINE_VERBOSE ){
    zStyle = "Verbose";
  }else if( tmFlags & TIMELINE_CLASSIC ){
    zStyle = "Classic";
  }else{
    zStyle = "Modern";
  }
  url_initialize(&url, "finfo");
  if( brBg ) url_add_parameter(&url, "brbg", 0);
  if( uBg ) url_add_parameter(&url, "ubg", 0);
  ridFrom = name_to_rid_www("from");
  zPrevDate[0] = 0;
  if( fnid==0 ){
    cgi_printf("No such file: %h\n",(zFilename));
    style_finish_page();
    return;
  }
  if( g.perm.Admin ){
    style_submenu_element("MLink Table", "%R/mlink?name=%t", zFilename);
  }
  if( ridFrom ){
    if( P("to")!=0 ){
      ridTo = name_to_typed_rid(P("to"),"ci");
      path_shortest_stored_in_ancestor_table(ridFrom,ridTo);
    }else{
      compute_direct_ancestors(ridFrom);
    }
  }
  url_add_parameter(&url, "name", zFilename);
  cgi_check_for_malice();
  blob_zero(&sql);
  if( ridCi ){
    /* If we will be tracking changes across renames, some extra temp
    ** tables (implemented as CTEs) are required */
    blob_append_sql(&sql,
      /* The clade(fid,fnid) table is the set of all (fid,fnid) pairs
      ** that should participate in the output.  Clade is computed by
      ** walking the graph of mlink edges.
      */
      "WITH RECURSIVE clade(fid,fnid) AS (\n"
      "  SELECT blob.rid, %d FROM blob\n"         /* %d is fnid */
      "   WHERE blob.uuid=(SELECT uuid FROM files_of_checkin(%Q)"
                         " WHERE filename=%Q)\n"  /* %Q is the filename */
      "   UNION\n"
      "  SELECT mlink.fid, mlink.fnid\n"
      "    FROM clade, mlink\n"
      "   WHERE clade.fid=mlink.pid\n"
      "     AND ((mlink.pfnid=0 AND mlink.fnid=clade.fnid)\n"
      "          OR mlink.pfnid=clade.fnid)\n"
      "     AND (mlink.fid>0 OR NOT EXISTS(SELECT 1 FROM mlink AS mx"
                 " WHERE mx.mid=mlink.mid AND mx.pid=mlink.pid"
                 "   AND mx.fid>0 AND mx.pfnid=mlink.fnid))\n"
      "   UNION\n"
      "  SELECT mlink.pid,"
              " CASE WHEN mlink.pfnid>0 THEN mlink.pfnid ELSE mlink.fnid END\n"
      "    FROM clade, mlink\n"
      "   WHERE mlink.pid>0\n"
      "     AND mlink.fid=clade.fid\n"
      "     AND mlink.fnid=clade.fnid\n"
      ")\n",
      fnid, zCI, zFilename
    );
  }else{
    /* This is the case for all files with a given name.  We will still
    ** create a "clade(fid,fnid)" table that identifies all participates
    ** in the output graph, so that subsequent queries can all be the same,
    ** but in the case the clade table is much simplier, being just a
    ** single direct query against the mlink table.
    */
    blob_append_sql(&sql,
      "WITH clade(fid,fnid) AS (\n"
      "  SELECT DISTINCT fid, %d\n"
      "    FROM mlink\n"
      "   WHERE fnid=%d)",
      fnid, fnid
    );
  }
  blob_append_sql(&sql,
    "SELECT\n"
    "  datetime(min(event.mtime),toLocal()),\n"         /* Date of change */
    "  coalesce(event.ecomment, event.comment),\n"      /* Check-in comment */
    "  coalesce(event.euser, event.user),\n"            /* User who made chng */
    "  mlink.pid,\n"                                    /* Parent file rid */
    "  mlink.fid,\n"                                    /* File rid */
    "  (SELECT uuid FROM blob WHERE rid=mlink.pid),\n"  /* Parent file hash */
    "  blob.uuid,\n"                                    /* Current file hash */
    "  (SELECT uuid FROM blob WHERE rid=mlink.mid),\n"  /* Check-in hash */
    "  event.bgcolor,\n"                                /* Background color */
    "  (SELECT value FROM tagxref WHERE tagid=%d AND tagtype>0"
                             " AND tagxref.rid=mlink.mid),\n" /* Branchname */
    "  mlink.mid,\n"                                    /* check-in ID */
    "  mlink.pfnid,\n"                                  /* Previous filename */
    "  blob.size,\n"                                    /* File size */
    "  mlink.fnid,\n"                                   /* Current filename */
    "  filename.name\n"                                 /* Current filename */
    "FROM clade CROSS JOIN mlink, event"
    " LEFT JOIN blob ON blob.rid=clade.fid"
    " LEFT JOIN filename ON filename.fnid=clade.fnid\n"
    "WHERE mlink.fnid=clade.fnid AND mlink.fid=clade.fid\n"
    "  AND event.objid=mlink.mid\n",
    TAG_BRANCH
  );
  if( (zA = P("a"))!=0 ){
    blob_append_sql(&sql, "  AND event.mtime>=%.16g\n",
         symbolic_name_to_mtime(zA,0,0));
    url_add_parameter(&url, "a", zA);
  }
  if( (zB = P("b"))!=0 ){
    blob_append_sql(&sql, "  AND event.mtime<=%.16g\n",
         symbolic_name_to_mtime(zB,0,1));
    url_add_parameter(&url, "b", zB);
  }
  if( ridFrom ){
    blob_append_sql(&sql,
      "  AND mlink.mid IN (SELECT rid FROM ancestor)\n"
      "GROUP BY mlink.fid\n"
    );
  }else{
    /* We only want each version of a file to appear on the graph once,
    ** at its earliest appearance.  All the other times that it gets merged
    ** into this or that branch can be ignored.  An exception is for when
    ** files are deleted (when they have mlink.fid==0).  If the same file
    ** is deleted in multiple places, we want to show each deletion, so
    ** use a "fake fid" which is derived from the parent-fid for grouping.
    ** The same fake-fid must be used on the graph.
    */
    blob_append_sql(&sql,
      "GROUP BY"
      " CASE WHEN mlink.fid>0 THEN mlink.fid ELSE mlink.pid+1000000000 END,"
      " mlink.fnid\n"
    );
  }
  blob_append_sql(&sql, "ORDER BY event.mtime DESC");
  if( (n = atoi(PD("n","0")))>0 ){
    blob_append_sql(&sql, " LIMIT %d", n);
    url_add_parameter(&url, "n", P("n"));
  }
  blob_append_sql(&sql, " /*sort*/\n");
  db_prepare(&q, "%s", blob_sql_text(&sql));
  if( P("showsql")!=0 ){
    cgi_printf("<p>SQL: <blockquote><pre>%h</blockquote></pre>\n",(blob_str(&sql)));
  }
  zMark = P("m");
  if( zMark ){
    selRid = symbolic_name_to_rid(zMark, "*");
  }
  blob_reset(&sql);
  blob_zero(&title);
  if( ridFrom ){
    char *zUuid = db_text(0, "SELECT uuid FROM blob WHERE rid=%d", ridFrom);
    char *zLink = href("%R/info/%!S", zUuid);
    if( ridTo ){
      blob_appendf(&title, "Changes to file ");
    }else if( n>0 ){
      blob_appendf(&title, "First %d ancestors of file ", n);
    }else{
      blob_appendf(&title, "Ancestors of file ");
    }
    blob_appendf(&title,"%z%h</a>",
                 href("%R/file?name=%T&ci=%!S", zFilename, zUuid),
                 zFilename);
    if( fShowId ) blob_appendf(&title, " (%d)", fnid);
    blob_append(&title, ridTo ? " between " : " from ", -1);
    blob_appendf(&title, "check-in %z%S</a>", zLink, zUuid);
    if( fShowId ) blob_appendf(&title, " (%d)", ridFrom);
    fossil_free(zUuid);
    if( ridTo ){
      zUuid = db_text(0, "SELECT uuid FROM blob WHERE rid=%d", ridTo);
      zLink = href("%R/info/%!S", zUuid);
      blob_appendf(&title, " and check-in %z%S</a>", zLink, zUuid);
      fossil_free(zUuid);
    }
  }else if( ridCi ){
    blob_appendf(&title, "History of file ");
    hyperlinked_path(zFilename, &title, 0, "tree", "", LINKPATH_FILE);
    if( fShowId ) blob_appendf(&title, " (%d)", fnid);
    blob_appendf(&title, " at check-in %z%h</a>",
        href("%R/info?name=%t",zCI), zCI);
  }else{
    blob_appendf(&title, "History for ");
    hyperlinked_path(zFilename, &title, 0, "tree", "", LINKPATH_FILE);
    if( fShowId ) blob_appendf(&title, " (%d)", fnid);
  }
  if( uBg ){
    blob_append(&title, " (color-coded by user)", -1);
  }
  cgi_printf("<h2>%b</h2>\n",(&title));
  blob_reset(&title);
  pGraph = graph_init();
  cgi_printf("<table id=\"timelineTable%d\" class=\"timelineTable\">\n",(iTableId));
  mxfnid = db_int(0, "SELECT max(fnid) FROM filename");
  if( ridFrom ){
    db_prepare(&qparent,
      "SELECT DISTINCT pid*%d+CASE WHEN pfnid>0 THEN pfnid ELSE fnid END"
      "  FROM mlink"
      " WHERE fid=:fid AND mid=:mid AND pid>0 AND fnid=:fnid"
      "   AND pmid IN (SELECT rid FROM ancestor)"
      " ORDER BY isaux /*sort*/", mxfnid+1
    );
  }else{
    db_prepare(&qparent,
      "SELECT DISTINCT pid*%d+CASE WHEN pfnid>0 THEN pfnid ELSE fnid END"
      "  FROM mlink"
      " WHERE fid=:fid AND mid=:mid AND pid>0 AND fnid=:fnid"
      " ORDER BY isaux /*sort*/", mxfnid+1
    );
  }
  while( db_step(&q)==SQLITE_ROW ){
    const char *zDate = db_column_text(&q, 0);
    const char *zCom = db_column_text(&q, 1);
    const char *zUser = db_column_text(&q, 2);
    int fpid = db_column_int(&q, 3);
    int frid = db_column_int(&q, 4);
    const char *zPUuid = db_column_text(&q, 5);
    const char *zUuid = db_column_text(&q, 6);
    const char *zCkin = db_column_text(&q,7);
    const char *zBgClr = db_column_text(&q, 8);
    const char *zBr = db_column_text(&q, 9);
    int fmid = db_column_int(&q, 10);
    int pfnid = db_column_int(&q, 11);
    int szFile = db_column_int(&q, 12);
    int fnid = db_column_int(&q, 13);
    const char *zFName = db_column_text(&q,14);
    int gidx;
    char zTime[10];
    int nParent = 0;
    int bIsModified = 0;
    GraphRowId aParent[GR_MAX_RAIL];

    db_bind_int(&qparent, ":fid", frid);
    db_bind_int(&qparent, ":mid", fmid);
    db_bind_int(&qparent, ":fnid", fnid);
    while( db_step(&qparent)==SQLITE_ROW && nParent<count(aParent) ){
      aParent[nParent] = db_column_int64(&qparent, 0);
      nParent++;
    }
    db_reset(&qparent);
    if( zBr==0 ) zBr = "trunk";
    if( uBg ){
      zBgClr = user_color(zUser);
    }else if( brBg || zBgClr==0 || zBgClr[0]==0 ){
      zBgClr = strcmp(zBr,"trunk")==0 ? "" : hash_color(zBr);
    }else if( zBgClr ){
      zBgClr = reasonable_bg_color(zBgClr,0);
    }
    gidx = graph_add_row(pGraph,
                   frid>0 ? (GraphRowId)frid*(mxfnid+1)+fnid : fpid+1000000000,
                   nParent, 0, aParent, zBr, zBgClr,
                   zUuid, 0);
    if( strncmp(zDate, zPrevDate, 10) ){
      sqlite3_snprintf(sizeof(zPrevDate), zPrevDate, "%.10s", zDate);
      cgi_printf("<tr><td>\n"
             "  <div class=\"divider timelineDate\">%s</div>\n"
             "</td><td></td><td></td></tr>\n",(zPrevDate));
    }
    memcpy(zTime, &zDate[11], 5);
    zTime[5] = 0;
    if( frid==selRid ){
      cgi_printf("<tr class='timelineSelected'>\n");
    }else{
      cgi_printf("<tr>\n");
    }
    cgi_printf("<td class=\"timelineTime\">"
           "%z%s</a></td>\n"
           "<td class=\"timelineGraph\"><div id=\"m%d\" class=\"tl-nodemark\"></div>\n"
           "</td>\n",(href("%R/file?name=%T&ci=%!S",zFName,zCkin)),(zTime),(gidx));
    if( zBgClr && zBgClr[0] ){
      cgi_printf("<td class=\"timeline%sCell\" id='mc%d'>\n",(zStyle),(gidx));
    }else{
      cgi_printf("<td class=\"timeline%sCell\">\n",(zStyle));
    }
    if( zPUuid && zUuid && fossil_strcmp(zPUuid, zUuid)!=0 ){
      bIsModified = 1;
    }
    if( tmFlags & TIMELINE_COMPACT ){
      cgi_printf("<span class='timelineCompactComment' data-id='%d'>\n",(frid));
    }else{
      cgi_printf("<span class='timeline%sComment'>\n",(zStyle));
      if( pfnid ){
        char *zPrevName = db_text(0,"SELECT name FROM filename WHERE fnid=%d",
                                   pfnid);
        if( bIsModified ){
          cgi_printf("<b>Renamed and modified</b> %h &rarr; %h.\n",(zPrevName),(zFName));
        }else{
          cgi_printf("<b>Renamed</b> %h &rarr; %h.\n",(zPrevName),(zFName));
        }
        fossil_free(zPrevName);
      }
      if( zUuid && ridTo==0 && nParent==0 ){
        cgi_printf("<b>Added:</b>\n");
      }
      if( zUuid==0 ){
        char *zNewName;
        zNewName = db_text(0,
          "SELECT name FROM filename WHERE fnid = "
          "   (SELECT fnid FROM mlink"
          "     WHERE mid=%d"
          "       AND pfnid IN (SELECT fnid FROM filename WHERE name=%Q))",
          fmid, zFName);
        if( zNewName ){
          cgi_printf("<b>Renamed</b> to\n"
                 "%z%h</a>.\n",(href("%R/finfo?name=%t",zNewName)),(zNewName));
          fossil_free(zNewName);
        }else{
          cgi_printf("<b>Deleted:</b>\n");
        }
      }
      if( (tmFlags & TIMELINE_VERBOSE)!=0 && zUuid ){
        hyperlink_to_version(zUuid);
        if( fShowId ){
          int srcId = delta_source_rid(frid);
          if( srcId ){
            cgi_printf("(%z%d&larr;%d</a>)\n",(href("%R/deltachain/%d",frid)),(frid),(srcId));
          }else{
            cgi_printf("(%z%d</a>)\n",(href("%R/deltachain/%d",frid)),(frid));
          }
        }
        cgi_printf("part of check-in ");
        hyperlink_to_version(zCkin);
      }
    }
    cgi_printf("%W</span>\n",(zCom));
    if( (tmFlags & TIMELINE_COMPACT)!=0 ){
      cgi_printf("<span class='timelineEllipsis' data-id='%d' "
             "id='ellipsis-%d'>...</span>\n",(frid),(frid));
    }
    if( tmFlags & TIMELINE_COLUMNAR ){
      if( zBgClr && zBgClr[0] ){
        cgi_printf("<td class=\"timelineDetailCell\" id='md%d'>\n",(gidx));
      }else{
        cgi_printf("<td class=\"timelineDetailCell\">\n");
      }
    }
    if( tmFlags & TIMELINE_COMPACT ){
      cgi_printf("<span class='clutter' id='detail-%d'>",frid);
    }
    cgi_printf("<span class='timeline%sDetail'>", zStyle);
    if( tmFlags & (TIMELINE_COMPACT|TIMELINE_VERBOSE) ) cgi_printf("(");
    if( zUuid && (tmFlags & TIMELINE_VERBOSE)==0 ){
      cgi_printf("file:&nbsp;%z"
             "[%S]</a>\n",(href("%R/file?name=%T&ci=%!S",zFName,zCkin)),(zUuid));
      if( fShowId ){
        int srcId = delta_source_rid(frid);
        if( srcId>0 ){
          cgi_printf("id:&nbsp;%z"
                 "%d&larr;%d</a>\n",(href("%R/deltachain/%d",frid)),(frid),(srcId));
        }else{
          cgi_printf("id:&nbsp;%z%d</a>\n",(href("%R/deltachain/%d",frid)),(frid));
        }
      }
    }
    cgi_printf("check-in:&nbsp;");
    hyperlink_to_version(zCkin);
    if( fShowId ){
      cgi_printf("(%d)\n",(fmid));
    }
    cgi_printf("user:&nbsp;");
    hyperlink_to_user(zUser, zDate, ",");
    cgi_printf("branch:&nbsp;%z%h</a>,\n",(href("%R/timeline?t=%T",zBr)),(zBr));
    if( tmFlags & (TIMELINE_COMPACT|TIMELINE_VERBOSE) ){
      cgi_printf("size:&nbsp;%d)\n",(szFile));
    }else{
      cgi_printf("size:&nbsp;%d\n",(szFile));
    }
    if( g.perm.Hyperlink && zUuid ){
      const char *z = zFName;
      cgi_printf("<span id='links-%d'><span class='timelineExtraLinks'>\n"
             "%z\n"
             "[annotate]</a>\n"
             "%z\n"
             "[blame]</a>\n"
             "%z[check-ins&nbsp;using]</a>\n",(frid),(href("%R/annotate?filename=%h&checkin=%s",z,zCkin)),(href("%R/blame?filename=%h&checkin=%s",z,zCkin)),(href("%R/timeline?uf=%!S",zUuid)));
      if( fpid>0 && bIsModified!=0 ){
        cgi_printf("%z[diff]</a>\n",(href("%R/fdiff?v1=%!S&v2=%!S",zPUuid,zUuid)));
      }
      if( fileedit_is_editable(zFName) ){
        cgi_printf("%z"
               "[edit]</a>\n",(href("%R/fileedit?filename=%T&checkin=%!S",zFName,zCkin)));
      }
      cgi_printf("</span></span>\n");
    }
    if( fDebug & FINFO_DEBUG_MLINK ){
      int ii;
      char *zAncLink;
      cgi_printf("<br>fid=%d "
             "graph-id=%lld "
             "pid=%d mid=%d fnid=%d "
             "pfnid=%d mxfnid=%d\n",(frid),(frid>0?(GraphRowId)frid*(mxfnid+1)+fnid:fpid+1000000000),(fpid),(fmid),(fnid),(pfnid),(mxfnid));
      if( nParent>0 ){
        cgi_printf("parents=%lld\n",(aParent[0]));
        for(ii=1; ii<nParent; ii++){
          cgi_printf("%lld\n",(aParent[ii]));
        }
      }
      zAncLink = href("%R/finfo?name=%T&from=%!S&debug=1",zFName,zCkin);
      cgi_printf("%z[ancestry]</a>\n",(zAncLink));
    }
    tag_private_status(frid);
    /* End timelineDetail */
    if( tmFlags & TIMELINE_COMPACT ){
      cgi_printf("</span></span>\n");
    }else{
      cgi_printf("</span>\n");
    }
    cgi_printf("</td></tr>\n");
  }
  db_finalize(&q);
  db_finalize(&qparent);
  if( pGraph ){
    graph_finish(pGraph, 0, TIMELINE_DISJOINT);
    if( pGraph->nErr ){
      graph_free(pGraph);
      pGraph = 0;
    }else{
      cgi_printf("<tr class=\"timelineBottom\" id=\"btm-%d\">"
             "<td></td><td></td><td></td></tr>\n",(iTableId));
    }
  }
  cgi_printf("</table>\n");
  timeline_output_graph_javascript(pGraph, TIMELINE_FILEDIFF, iTableId);
  style_finish_page();
}

/*
** WEBPAGE: mlink
** URL: /mlink?name=FILENAME
** URL: /mlink?ci=NAME
**
** Show all MLINK table entries for a particular file, or for
** a particular check-in.
**
** This screen is intended for use by Fossil developers to help
** in debugging Fossil itself.  Ordinary Fossil users are not
** expected to know what the MLINK table is or why it is important.
**
** To avoid confusing ordinary users, this page is only available
** to administrators.
*/
void mlink_page(void){
  const char *zFName = P("name");
  const char *zCI = P("ci");
  Stmt q;

  login_check_credentials();
  if( !g.perm.Admin ){ login_needed(g.anon.Admin); return; }
  style_set_current_feature("finfo");
  style_header("MLINK Table");
  if( zFName==0 && zCI==0 ){
    cgi_printf("<span class='generalError'>\n"
           "Requires either a name= or ci= query parameter\n"
           "</span>\n");
  }else if( zFName ){
    int fnid = db_int(0,"SELECT fnid FROM filename WHERE name=%Q",zFName);
    if( fnid<=0 ) fossil_fatal("no such file: \"%s\"", zFName);
    db_prepare(&q,
       "SELECT"
       /* 0 */ "  datetime(event.mtime,toLocal()),"
       /* 1 */ "  (SELECT uuid FROM blob WHERE rid=mlink.mid),"
       /* 2 */ "  (SELECT uuid FROM blob WHERE rid=mlink.pmid),"
       /* 3 */ "  isaux,"
       /* 4 */ "  (SELECT uuid FROM blob WHERE rid=mlink.fid),"
       /* 5 */ "  (SELECT uuid FROM blob WHERE rid=mlink.pid),"
       /* 6 */ "  mlink.pid,"
       /* 7 */ "  mperm,"
       /* 8 */ "  (SELECT name FROM filename WHERE fnid=mlink.pfnid)"
       "  FROM mlink, event"
       " WHERE mlink.fnid=%d"
       "   AND event.objid=mlink.mid"
       " ORDER BY 1 DESC",
       fnid
    );
    style_table_sorter();
    cgi_printf("<h1>MLINK table for file\n"
           "<a href='%R/finfo?name=%t'>%h</a></h1>\n"
           "<div class='brlist'>\n"
           "<table class='sortable' data-column-types='tttxtttt' data-init-sort='1'>\n"
           "<thead><tr>\n"
           "<th>Date</th>\n"
           "<th>Check-in</th>\n"
           "<th>Parent<br>Check-in</th>\n"
           "<th>Merge?</th>\n"
           "<th>New</th>\n"
           "<th>Old</th>\n"
           "<th>Exe<br>Bit?</th>\n"
           "<th>Prior<br>Name</th>\n"
           "</tr></thead>\n"
           "<tbody>\n",(zFName),(zFName));
    while( db_step(&q)==SQLITE_ROW ){
      const char *zDate = db_column_text(&q,0);
      const char *zCkin = db_column_text(&q,1);
      const char *zParent = db_column_text(&q,2);
      int isMerge = db_column_int(&q,3);
      const char *zFid = db_column_text(&q,4);
      const char *zPid = db_column_text(&q,5);
      int isExe = db_column_int(&q,7);
      const char *zPrior = db_column_text(&q,8);
      cgi_printf("<tr>\n"
             "<td><a href='%R/timeline?c=%!S'>%s</a></td>\n"
             "<td><a href='%R/info/%!S'>%S</a></td>\n",(zCkin),(zDate),(zCkin),(zCkin));
      if( zParent ){
        cgi_printf("<td><a href='%R/info/%!S'>%S</a></td>\n",(zParent),(zParent));
      }else{
        cgi_printf("<td><i>(New)</i></td>\n");
      }
      cgi_printf("<td align='center'>%s</td>\n",(isMerge?"&#x2713;":""));
      if( zFid ){
        cgi_printf("<td><a href='%R/info/%!S'>%S</a></td>\n",(zFid),(zFid));
      }else{
        cgi_printf("<td><i>(Deleted)</i></td>\n");
      }
      if( zPid ){
        cgi_printf("<td><a href='%R/info/%!S'>%S</a>\n",(zPid),(zPid));
      }else if( db_column_int(&q,6)<0 ){
        cgi_printf("<td><i>(Added by merge)</i></td>\n");
      }else{
        cgi_printf("<td><i>(New)</i></td>\n");
      }
      cgi_printf("<td align='center'>%s</td>\n",(isExe?"&#x2713;":""));
      if( zPrior ){
        cgi_printf("<td><a href='%R/finfo?name=%t'>%h</a></td>\n",(zPrior),(zPrior));
      }else{
        cgi_printf("<td></td>\n");
      }
      cgi_printf("</tr>\n");
    }
    db_finalize(&q);
    cgi_printf("</tbody>\n"
           "</table>\n"
           "</div>\n");
  }else{
    int mid = name_to_rid_www("ci");
    db_prepare(&q,
       "SELECT"
       /* 0 */ "  (SELECT name FROM filename WHERE fnid=mlink.fnid),"
       /* 1 */ "  (SELECT uuid FROM blob WHERE rid=mlink.fid),"
       /* 2 */ "  pid,"
       /* 3 */ "  (SELECT uuid FROM blob WHERE rid=mlink.pid),"
       /* 4 */ "  (SELECT name FROM filename WHERE fnid=mlink.pfnid),"
       /* 5 */ "  (SELECT uuid FROM blob WHERE rid=mlink.pmid),"
       /* 6 */ "  mperm,"
       /* 7 */ "  isaux"
       "  FROM mlink WHERE mid=%d ORDER BY 1",
       mid
    );
    cgi_printf("<h1>MLINK table for check-in %h</h1>\n",(zCI));
    render_checkin_context(mid, 0, 1, 0);
    style_table_sorter();
    cgi_printf("<hr>\n"
           "<div class='brlist'>\n"
           "<table class='sortable' data-column-types='ttxtttt' data-init-sort='1'>\n"
           "<thead><tr>\n"
           "<th>File</th>\n"
           "<th>Parent<br>Check-in</th>\n"
           "<th>Merge?</th>\n"
           "<th>New</th>\n"
           "<th>Old</th>\n"
           "<th>Exe<br>Bit?</th>\n"
           "<th>Prior<br>Name</th>\n"
           "</tr></thead>\n"
           "<tbody>\n");
    while( db_step(&q)==SQLITE_ROW ){
      const char *zName = db_column_text(&q,0);
      const char *zFid = db_column_text(&q,1);
      const char *zPid = db_column_text(&q,3);
      const char *zPrior = db_column_text(&q,4);
      const char *zParent = db_column_text(&q,5);
      int isExec = db_column_int(&q,6);
      int isAux = db_column_int(&q,7);
      cgi_printf("<tr>\n"
             "<td><a href='%R/finfo?name=%t'>%h</a></td>\n",(zName),(zName));
      if( zParent ){
        cgi_printf("<td><a href='%R/info/%!S'>%S</a></td>\n",(zParent),(zParent));
      }else{
        cgi_printf("<td><i>(New)</i></td>\n");
      }
      cgi_printf("<td align='center'>%s</td>\n",(isAux?"&#x2713;":""));
      if( zFid ){
        cgi_printf("<td><a href='%R/info/%!S'>%S</a></td>\n",(zFid),(zFid));
      }else{
        cgi_printf("<td><i>(Deleted)</i></td>\n");
      }
      if( zPid ){
        cgi_printf("<td><a href='%R/info/%!S'>%S</a>\n",(zPid),(zPid));
      }else if( db_column_int(&q,2)<0 ){
        cgi_printf("<td><i>(Added by merge)</i></td>\n");
      }else{
        cgi_printf("<td><i>(New)</i></td>\n");
      }
      cgi_printf("<td align='center'>%s</td>\n",(isExec?"&#x2713;":""));
      if( zPrior ){
        cgi_printf("<td><a href='%R/finfo?name=%t'>%h</a></td>\n",(zPrior),(zPrior));
      }else{
        cgi_printf("<td></td>\n");
      }
      cgi_printf("</tr>\n");
    }
    db_finalize(&q);
    cgi_printf("</tbody>\n"
           "</table>\n"
           "</div>\n");
  }
  style_finish_page();
}
