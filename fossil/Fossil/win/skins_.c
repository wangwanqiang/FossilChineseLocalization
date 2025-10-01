#line 1 "C:\\source\\fossil_depot\\fossil\\Fossil-1205ec86\\src\\skins.c"
/*
** Copyright (c) 2009 D. Richard Hipp
**
** This program is free software; you can redistribute it and/or
** modify it under the terms of the Simplified BSD License (also
** known as the "2-Clause License" or "FreeBSD License".)
**
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
** Implementation of the Setup page for "skins".
*/
#include "config.h"
#include <assert.h>
#include "skins.h"

/*
** SETTING: default-skin width=16
**
** If the text value if this setting is the name of a built-in skin
** then the named skin becomes the default skin for the repository.
*/

/*
** An array of available built-in skins.
**
** To add new built-in skins:
**
**    1.  Pick a name for the new skin.  (Here we use "xyzzy").
**
**    2.  Install files skins/xyzzy/css.txt, skins/xyzzy/header.txt,
**        and skins/xyzzy/footer.txt into the source tree.
**
**    3.  Rerun "tclsh makemake.tcl" in the src/ folder in order to
**        rebuild the makefiles to reference the new CSS, headers, and footers.
**
**    4.  Make an entry in the following array for the new skin.
*/
static struct BuiltinSkin {
  const char *zDesc;    /* Description of this skin */
  const char *zLabel;   /* The directory under skins/ holding this skin */
  char *zSQL;           /* Filled in at run-time with SQL to insert this skin */
} aBuiltinSkin[] = {
  { "Default",                           "default",           0 },
  { "Ardoise",                           "ardoise",           0 },
  { "Black & White",                     "black_and_white",   0 },
  { "Blitz",                             "blitz",             0 },
  { "Dark Mode",                         "darkmode",          0 },
  { "Eagle",                             "eagle",             0 },
  { "Étienne",                           "etienne",           0 },
  { "Khaki",                             "khaki",             0 },
  { "Original",                          "original",          0 },
  { "Plain Gray",                        "plain_gray",        0 },
  { "Xekri",                             "xekri",             0 },
};

/*
** A skin consists of five "files" named here:
*/
static const char *const azSkinFile[] = {
  "css", "header", "footer", "details", "js"
};

/*
** Alternative skins can be specified in the CGI script or by options
** on the "http", "ui", and "server" commands.  The alternative skin
** name must be one of the aBuiltinSkin[].zLabel names.  If there is
** a match, that alternative is used.
**
** The following static variable holds the name of the alternative skin,
** or NULL if the skin should be as configured.
*/
static struct BuiltinSkin *pAltSkin = 0;
static char *zAltSkinDir = 0;
static int iDraftSkin = 0;
/*
** Used by skin_use_alternative() to store the current skin rank skin
** so that the /skins page can, if warranted, warn the user that skin
** changes won't have any effect.
*/
static int nSkinRank = 6;

/*
** How the specific skin being used was chosen
*/
#if INTERFACE
#define SKIN_FROM_DRAFT     0   /* The "draftN" prefix on the PATH_INFO */
#define SKIN_FROM_CMDLINE   1   /* --skin option to server command-line */
#define SKIN_FROM_CGI       2   /* skin: parameter in CGI script */
#define SKIN_FROM_QPARAM    3   /* skin= query parameter */
#define SKIN_FROM_COOKIE    4   /* skin= from fossil_display_settings cookie*/
#define SKIN_FROM_SETTING   5   /* Built-in named by "default-skin" setting */
#define SKIN_FROM_CUSTOM    6   /* Skin values in CONFIG table */
#define SKIN_FROM_DEFAULT   7   /* The built-in named "default" */
#define SKIN_FROM_UNKNOWN   8   /* Do not yet know which skin to use */
#endif /* INTERFACE */
static int iSkinSource = SKIN_FROM_UNKNOWN;


/*
** Skin details are a set of key/value pairs that define display
** attributes of the skin that cannot be easily specified using CSS
** or that need to be known on the server-side.
**
** The following array holds the value for all known skin details.
*/
static struct SkinDetail {
  const char *zName;      /* Name of the detail */
  const char *zValue;     /* Value of the detail */
} aSkinDetail[] = {
  { "pikchr-background",          ""      },
  { "pikchr-fontscale",           ""      },
  { "pikchr-foreground",          ""      },
  { "pikchr-scale",               ""      },
  { "timeline-arrowheads",        "1"     },
  { "timeline-circle-nodes",      "0"     },
  { "timeline-color-graph-lines", "0"     },
  { "white-foreground",           "0"     },
};

/*
** Invoke this routine to set the alternative skin.  Return NULL if the
** alternative was successfully installed.  Return a string listing all
** available skins if zName does not match an available skin.  Memory
** for the returned string comes from fossil_malloc() and should be freed
** by the caller.
**
** If the alternative skin name contains one or more '/' characters, then
** it is assumed to be a directory on disk that holds override css.txt,
** footer.txt, and header.txt.  This mode can be used for interactive
** development of new skins.
**
** The 2nd parameter is a ranking of how important this alternative
** skin declaration is, and lower values trump higher ones. If a call
** to this function passes a higher-valued rank than a previous call,
** the subsequent call becomes a no-op. Only calls with the same or
** lower rank (i.e. higher priority) will overwrite a previous
** setting. This approach is used because the CGI/server-time
** initialization happens in an order which is incompatible with our
** preferred ranking, making it otherwise more invasive to tell the
** internals "the --skin flag ranks higher than a URL parameter" (the
** former gets initialized before both URL parameters and the /draft
** path determination).
**
** The rankings were initially defined in
** https://fossil-scm.org/forum/forumpost/caf8c9a8bb
** but where subsequently revised:
**
** 0) A skin name matching the glob pattern "draft[1-9]" at the start of
**    the PATH_INFO.
**
** 1) The --skin flag for commands like "fossil ui", "fossil server", or
**    "fossil http", or  the "skin:" CGI config setting.
**
** 2) The "skin" display setting cookie or URL argument, in that
**    order. If the "skin" URL argument is provided and refers to a legal
**    skin then that will update the display cookie. If the skin name is
**    illegal it is silently ignored.
**
** 3) The built-in skin identfied by the "default-skin" setting, if such
**    a setting exists and matches one of the built-in skin names.
**
** 4) Skin properties (settings "css", "details", "footer", "header",
**    and "js") from the CONFIG db table
**
** 5) The built-in skin named "default"
**
** The iSource integer privides additional detail about where the skin
**
** As a special case, a NULL or empty name resets zAltSkinDir and
** pAltSkin to 0 to indicate that the current config-side skin should
** be used (rank 3, above), then returns 0.
*/
char *skin_use_alternative(const char *zName, int rank, int iSource){
  int i;
  Blob err = BLOB_INITIALIZER;
  if(rank > nSkinRank) return 0;
  nSkinRank = rank;
  if( zName && 1==rank && strchr(zName, '/')!=0 ){
    zAltSkinDir = fossil_strdup(zName);
    iSkinSource = iSource;
    return 0;
  }
  if( zName && sqlite3_strglob("draft[1-9]", zName)==0 ){
    skin_use_draft(zName[5] - '0');
    iSkinSource = iSource;
    return 0;
  }
  if(!zName || !*zName){
    pAltSkin = 0;
    zAltSkinDir = 0;
    return 0;
  }
  if( fossil_strcmp(zName, "custom")==0 ){
    pAltSkin = 0;
    zAltSkinDir = 0;
    iSkinSource = iSource;
    return 0;
  }
  for(i=0; i<count(aBuiltinSkin); i++){
    if( fossil_strcmp(aBuiltinSkin[i].zLabel, zName)==0 ){
      pAltSkin = &aBuiltinSkin[i];
      iSkinSource = iSource;
      return 0;
    }
  }
  blob_appendf(&err, "available skins: %s", aBuiltinSkin[0].zLabel);
  for(i=1; i<count(aBuiltinSkin); i++){
    blob_append(&err, " ", 1);
    blob_append(&err, aBuiltinSkin[i].zLabel, -1);
  }
  return blob_str(&err);
}

/*
** Look for the --skin command-line option and process it.  Or
** call fossil_fatal() if an unknown skin is specified.
**
** This routine is called during command-line parsing for commands
** like "fossil ui" and "fossil http".
*/
void skin_override(void){
  const char *zSkin = find_option("skin",0,1);
  if( zSkin ){
    char *zErr = skin_use_alternative(zSkin, 1, SKIN_FROM_CMDLINE);
    if( zErr ) fossil_fatal("%s", zErr);
  }
}

/*
** Use one of the draft skins.
*/
void skin_use_draft(int i){
  iDraftSkin = i;
  iSkinSource = SKIN_FROM_DRAFT;
}

/*
** The following routines return the various components of the skin
** that should be used for the current run.
**
** zWhat is one of:  "css", "header", "footer", "details", "js"
*/
const char *skin_get(const char *zWhat){
  const char *zOut;
  char *z;
  if( iDraftSkin ){
    z = mprintf("draft%d-%s", iDraftSkin, zWhat);
    zOut = db_get(z, 0);
    fossil_free(z);
    if( zOut ) return zOut;
  }
  if( zAltSkinDir ){
    char *z = mprintf("%s/%s.txt", zAltSkinDir, zWhat);
    if( file_isfile(z, ExtFILE) ){
      Blob x;
      blob_read_from_file(&x, z, ExtFILE);
      fossil_free(z);
      return blob_str(&x);
    }
    fossil_free(z);
  }
  if( iSkinSource==SKIN_FROM_UNKNOWN ){
    const char *zDflt = db_get("default-skin", 0);
    iSkinSource = SKIN_FROM_DEFAULT;
    if( zDflt!=0 ){
      int i;
      for(i=0; i<count(aBuiltinSkin); i++){
        if( fossil_strcmp(aBuiltinSkin[i].zLabel, zDflt)==0 ){
          pAltSkin = &aBuiltinSkin[i];
          iSkinSource = SKIN_FROM_SETTING;
          break;
        }
      }
    }
  }
  if( pAltSkin ){
    z = mprintf("skins/%s/%s.txt", pAltSkin->zLabel, zWhat);
    zOut = builtin_text(z);
    fossil_free(z);
  }else{
    zOut = db_get(zWhat, 0);
    if( zOut==0 ){
      z = mprintf("skins/default/%s.txt", zWhat);
      zOut = builtin_text(z);
      fossil_free(z);
    }else if( iSkinSource==SKIN_FROM_DEFAULT ){
      iSkinSource = SKIN_FROM_CUSTOM;
    }
  }
  return zOut;
}

/*
** Return the command-line option used to set the skin, or return NULL
** if the default skin is being used.
*/
const char *skin_in_use(void){
  if( zAltSkinDir ) return zAltSkinDir;
  if( pAltSkin ) return pAltSkin->zLabel;
  return 0;
}

/*
** Return a pointer to a SkinDetail element.  Return 0 if not found.
*/
static struct SkinDetail *skin_detail_find(const char *zName){
  int lwr = 0;
  int upr = count(aSkinDetail);
  while( upr>=lwr ){
    int mid = (upr+lwr)/2;
    int c = fossil_strcmp(aSkinDetail[mid].zName, zName);
    if( c==0 ) return &aSkinDetail[mid];
    if( c<0 ){
      lwr = mid+1;
    }else{
      upr = mid-1;
    }
  }
  return 0;
}

/* Initialize the aSkinDetail array using the text in the details.txt
** file.
*/
static void skin_detail_initialize(void){
  static int isInit = 0;
  char *zDetail;
  Blob detail, line, key, value;
  if( isInit ) return;
  isInit = 1;
  zDetail = (char*)skin_get("details");
  if( zDetail==0 ) return;
  zDetail = fossil_strdup(zDetail);
  blob_init(&detail, zDetail, -1);
  while( blob_line(&detail, &line) ){
    char *zKey;
    int nKey;
    struct SkinDetail *pDetail;
    if( !blob_token(&line, &key) ) continue;
    zKey = blob_buffer(&key);
    if( zKey[0]=='#' ) continue;
    nKey = blob_size(&key);
    if( nKey<2 ) continue;
    if( zKey[nKey-1]!=':' ) continue;
    zKey[nKey-1] = 0;
    pDetail = skin_detail_find(zKey);
    if( pDetail==0 ) continue;
    if( !blob_token(&line, &value) ) continue;
    pDetail->zValue = fossil_strdup(blob_str(&value));
  }
  blob_reset(&detail);
  fossil_free(zDetail);
}

/*
** Return a skin detail setting
*/
const char *skin_detail(const char *zName){
  struct SkinDetail *pDetail;
  skin_detail_initialize();
  pDetail = skin_detail_find(zName);
  if( pDetail==0 ) fossil_fatal("no such skin detail: %s", zName);
  return pDetail->zValue;
}
int skin_detail_boolean(const char *zName){
  return !is_false(skin_detail(zName));
}

/*
** Hash function for computing a skin id.
*/
static unsigned int skin_hash(unsigned int h, const char *z){
  if( z==0 ) return h;
  while( z[0] ){
    h = (h<<11) ^ (h<<1) ^ (h>>3) ^ z[0];
    z++;
  }
  return h;
}

/*
** Return an identifier that is (probably) different for every skin
** but that is (probably) the same if the skin is unchanged.  This
** identifier can be attached to resource URLs to force reloading when
** the resources change but allow the resources to be read from cache
** as long as they are unchanged.
**
** The zResource argument is the name of a CONFIG setting that
** defines the resource.  Examples:  "css", "logo-image".
*/
unsigned int skin_id(const char *zResource){
  unsigned int h = 0;
  if( zAltSkinDir ){
    h = skin_hash(0, zAltSkinDir);
  }else if( pAltSkin ){
    h = skin_hash(0, pAltSkin->zLabel);
  }else{
    char *zMTime = db_get_mtime(zResource, 0, 0);
    h = skin_hash(0, zMTime);
    fossil_free(zMTime);
  }

  /* Change the ID every time Fossil is recompiled */
  h = skin_hash(h, fossil_exe_id());
  return h;
}

/*
** For a skin named zSkinName, compute the name of the CONFIG table
** entry where that skin is stored and return it.
**
** Return NULL if zSkinName is NULL or an empty string.
**
** If ifExists is true, and the named skin does not exist, return NULL.
*/
static char *skinVarName(const char *zSkinName, int ifExists){
  char *z;
  if( zSkinName==0 || zSkinName[0]==0 ) return 0;
  z = mprintf("skin:%s", zSkinName);
  if( ifExists && !db_exists("SELECT 1 FROM config WHERE name=%Q", z) ){
    free(z);
    z = 0;
  }
  return z;
}

/*
** Return true if there exists a skin name "zSkinName".
*/
static int skinExists(const char *zSkinName){
  int i;
  if( zSkinName==0 ) return 0;
  for(i=0; i<count(aBuiltinSkin); i++){
    if( fossil_strcmp(zSkinName, aBuiltinSkin[i].zDesc)==0 ) return 1;
  }
  return db_exists("SELECT 1 FROM config WHERE name='skin:%q'", zSkinName);
}

/*
** Construct and return an string of SQL statements that represents
** a "skin" setting.  If zName==0 then return the skin currently
** installed.  Otherwise, return one of the built-in skins designated
** by zName.
**
** Memory to hold the returned string is obtained from malloc.
*/
static char *getSkin(const char *zName){
  const char *z;
  char *zLabel;
  int i;
  Blob val;
  blob_zero(&val);
  for(i=0; i<count(azSkinFile); i++){
    if( zName ){
      zLabel = mprintf("skins/%s/%s.txt", zName, azSkinFile[i]);
      z = builtin_text(zLabel);
      fossil_free(zLabel);
    }else{
      z = db_get(azSkinFile[i], 0);
      if( z==0 ){
        zLabel = mprintf("skins/default/%s.txt", azSkinFile[i]);
        z = builtin_text(zLabel);
        fossil_free(zLabel);
      }
    }
    db_unprotect(PROTECT_CONFIG);
    blob_appendf(&val,
       "REPLACE INTO config(name,value,mtime) VALUES(%Q,%Q,now());\n",
       azSkinFile[i], z
    );
    db_protect_pop();
  }
  return blob_str(&val);
}

/*
** Respond to a Rename button press.  Return TRUE if a dialog was painted.
** Return FALSE to continue with the main Skins page.
*/
static int skinRename(void){
  const char *zOldName;
  const char *zNewName;
  int ex = 0;
  if( P("rename")==0 ) return 0;
  zOldName = P("sn");
  zNewName = P("newname");
  if( zOldName==0 ) return 0;
  if( zNewName==0 || zNewName[0]==0 || (ex = skinExists(zNewName))!=0 ){
    if( zNewName==0 ) zNewName = zOldName;
    style_set_current_feature("skins");
    style_header("Rename A Skin");
    if( ex ){
      cgi_printf("<p><span class=\"generalError\">There is already another skin\n"
             "named \"%h\".  Choose a different name.</span></p>\n",(zNewName));
    }
    cgi_printf("<form action=\"%R/setup_skin_admin\" method=\"post\"><div>\n"
           "<table border=\"0\"><tr>\n"
           "<tr><td align=\"right\">Current name:<td align=\"left\"><b>%h</b>\n"
           "<tr><td align=\"right\">New name:<td align=\"left\">\n"
           "<input type=\"text\" size=\"35\" name=\"newname\" value=\"%h\">\n"
           "<tr><td><td>\n"
           "<input type=\"hidden\" name=\"sn\" value=\"%h\">\n"
           "<input type=\"submit\" name=\"rename\" value=\"Rename\">\n"
           "<input type=\"submit\" name=\"canren\" value=\"Cancel\">\n"
           "</table>\n",(zOldName),(zNewName),(zOldName));
    login_insert_csrf_secret();
    cgi_printf("</div></form>\n");
    style_finish_page();
    return 1;
  }
  db_unprotect(PROTECT_CONFIG);
  db_multi_exec(
    "UPDATE config SET name='skin:%q' WHERE name='skin:%q';",
    zNewName, zOldName
  );
  db_protect_pop();
  return 0;
}

/*
** Respond to a Save button press.  Return TRUE if a dialog was painted.
** Return FALSE to continue with the main Skins page.
*/
static int skinSave(const char *zCurrent){
  const char *zNewName;
  int ex = 0;
  if( P("save")==0 ) return 0;
  zNewName = P("svname");
  if( zNewName && zNewName[0]!=0 ){
  }
  if( zNewName==0 || zNewName[0]==0 || (ex = skinExists(zNewName))!=0 ){
    if( zNewName==0 ) zNewName = "";
    style_set_current_feature("skins");
    style_header("Save Current Skin");
    if( ex ){
      cgi_printf("<p><span class=\"generalError\">There is already another skin\n"
             "named \"%h\".  Choose a different name.</span></p>\n",(zNewName));
    }
    cgi_printf("<form action=\"%R/setup_skin_admin\" method=\"post\"><div>\n"
           "<table border=\"0\"><tr>\n"
           "<tr><td align=\"right\">Name for this skin:<td align=\"left\">\n"
           "<input type=\"text\" size=\"35\" name=\"svname\" value=\"%h\">\n"
           "<tr><td><td>\n"
           "<input type=\"submit\" name=\"save\" value=\"Save\">\n"
           "<input type=\"submit\" name=\"cansave\" value=\"Cancel\">\n"
           "</table>\n",(zNewName));
    login_insert_csrf_secret();
    cgi_printf("</div></form>\n");
    style_finish_page();
    return 1;
  }
  db_unprotect(PROTECT_CONFIG);
  db_multi_exec(
    "INSERT OR IGNORE INTO config(name, value, mtime)"
    "VALUES('skin:%q',%Q,now())",
    zNewName, zCurrent
  );
  db_protect_pop();
  return 0;
}

/*
** Return true if a custom skin exists
*/
static int skin_exists_custom(void){
  return db_exists("SELECT 1 FROM config WHERE name IN"
                        " ('css','details','footer','header','js')");
}

static void skin_publish(int);  /* Forward reference */

/*
** WEBPAGE: setup_skin_admin
**
** Administrative actions on skins.  For administrators only.
*/
void setup_skin_admin(void){
  const char *z;
  char *zName;
  char *zErr = 0;
  const char *zCurrent = 0;  /* Current skin */
  int i;                     /* Loop counter */
  Stmt q;
  int once;
  const char *zOverride = 0;
  const char *zDfltSkin = 0;
  int seenDefault = 0;
  int hasCustom;

  login_check_credentials();
  if( !g.perm.Admin ){
    login_needed(0);
    return;
  }
  db_begin_transaction();
  zCurrent = getSkin(0);
  for(i=0; i<count(aBuiltinSkin); i++){
    aBuiltinSkin[i].zSQL = getSkin(aBuiltinSkin[i].zLabel);
  }

  style_set_current_feature("skins");

  if( cgi_csrf_safe(2) ){
    /* Process requests to delete a user-defined skin */
    if( P("del1") && P("sn")!=0 ){
      style_header("Confirm Custom Skin Delete");
      cgi_printf("<form action=\"%R/setup_skin_admin\" method=\"post\"><div>\n"
             "<p>Deletion of a custom skin is a permanent action that cannot\n"
             "be undone.  Please confirm that this is what you want to do:</p>\n"
             "<input type=\"hidden\" name=\"sn\" value=\"%h\">\n"
             "<input type=\"submit\" name=\"del2\" value=\"Confirm - Delete The Skin\">\n"
             "<input type=\"submit\" name=\"cancel\" value=\"Cancel - Do Not Delete\">\n",(P("sn")));
      login_insert_csrf_secret();
      cgi_printf("</div></form>\n");
      style_finish_page();
      db_end_transaction(1);
      return;
    }
    if( P("del2")!=0 ){
      db_unprotect(PROTECT_CONFIG);
      if( fossil_strcmp(P("sn"),"custom")==0 ){
        db_multi_exec("DELETE FROM config WHERE name IN" 
                      "('css','details','footer','header','js')");
      }else if( (zName = skinVarName(P("sn"), 1))!=0 ){
        db_multi_exec("DELETE FROM config WHERE name=%Q", zName);
      }
      db_protect_pop();
    }
    if( P("draftdel")!=0 ){
      const char *zDraft = P("name");
      if( sqlite3_strglob("draft[1-9]",zDraft)==0 ){
        db_unprotect(PROTECT_CONFIG);
        db_multi_exec("DELETE FROM config WHERE name GLOB '%q-*'", zDraft);
        db_protect_pop();
      }
    }
    if( P("editdraft")!=0 ){
      db_end_transaction(0);
      cgi_redirectf("%R/setup_skin");
      return;
    }
    if( skinRename() || skinSave(zCurrent) ){
      db_end_transaction(0);
      return;
    }

    if( P("setdflt") && (z = P("bisl"))!=0 ){
      if( z[0] ){
        db_set("default-skin", z, 0);
      }else{
        db_unset("default-skin", 0);
      }
      db_end_transaction(0);
      cgi_redirectf("%R/setup_skin_admin");
      return;
    }

    /* The user pressed one of the "Install" buttons. */
    if( P("load") && (z = P("sn"))!=0 && z[0] ){
      int seen = 0;

      /* Check to see if the current skin is already saved.  If it is, there
      ** is no need to create a backup */
      hasCustom = skin_exists_custom();
      if( hasCustom ){
        zCurrent = getSkin(0);
        for(i=0; i<count(aBuiltinSkin); i++){
          if( fossil_strcmp(aBuiltinSkin[i].zSQL, zCurrent)==0 ){
            seen = 1;
            break;
          }
        }
        if( !seen ){
          seen = db_exists("SELECT 1 FROM config WHERE name GLOB 'skin:*'"
                           " AND value=%Q", zCurrent);
          if( !seen ){
            db_unprotect(PROTECT_CONFIG);
            db_multi_exec(
              "INSERT INTO config(name,value,mtime) VALUES("
              "  strftime('skin:Backup On %%Y-%%m-%%d %%H:%%M:%%S'),"
              "  %Q,now())", zCurrent
            );
            db_protect_pop();
          }
        }
      }
      seen = 0;
      if( z[0]>='1' && z[0]<='9' && z[1]==0 ){
        skin_publish(z[0]-'0');
        seen = 1;
      }
      for(i=0; seen==0 && i<count(aBuiltinSkin); i++){
        if( fossil_strcmp(aBuiltinSkin[i].zDesc, z)==0 ){
          seen = 1;
          zCurrent = aBuiltinSkin[i].zSQL;
          db_unprotect(PROTECT_CONFIG);
          db_multi_exec("%s", zCurrent/*safe-for-%s*/);
          db_protect_pop();
          break;
        }
      }
      if( !seen ){
        zName = skinVarName(z,0);
        zCurrent = db_get(zName, 0);
        db_unprotect(PROTECT_CONFIG);
        db_multi_exec("%s", zCurrent/*safe-for-%s*/);
        db_protect_pop();
      }
    }
  }

  zDfltSkin = db_get("default-skin",0);
  hasCustom = skin_exists_custom();
  if( !hasCustom && zDfltSkin==0 ){
    zDfltSkin = "default";
  }

  style_header("Skins");
  if( zErr ){
    cgi_printf("<p style=\"color:red\">%h</p>\n",(zErr));
  }
  cgi_printf("<table border=\"0\">\n"
         "<tr><td colspan=4><h2>Built-in Skins:</h2></td></tr>\n");
  for(i=0; i<count(aBuiltinSkin); i++){
    z = aBuiltinSkin[i].zDesc;
    cgi_printf("<tr><td>%d.<td>%h<td>&nbsp;&nbsp;<td>\n"
           "<form action=\"%R/setup_skin_admin\" method=\"POST\">\n",(i+1),(z));
    login_insert_csrf_secret();
    if( zDfltSkin==0 || fossil_strcmp(aBuiltinSkin[i].zLabel, zDfltSkin)!=0 ){
                                /* vvvv--- mnemonic: Built-In Skin Label */
      cgi_printf("<input type=\"hidden\" name=\"bisl\" value=\"%h\">\n"
             "<input type=\"submit\" name=\"setdflt\" value=\"Set\">\n",(aBuiltinSkin[i].zLabel));
    }else{
      cgi_printf("(Selected)\n");
      seenDefault = 1;
    }
    if( pAltSkin==&aBuiltinSkin[i] && iSkinSource!=SKIN_FROM_SETTING ){
      cgi_printf("(Override)\n");
      zOverride = z;
    }
    cgi_printf("</form></td></tr>\n");
  }
  if( zOverride ){
    cgi_printf("<tr><td>&nbsp;<td colspan=\"3\">\n"
           "<p>Note: Built-in skin \"%h\" is currently being used because of\n",(zOverride));
    switch( iSkinSource ){
      case SKIN_FROM_CMDLINE:
        cgi_printf("the --skin command-line option.\n");
        break;
      case SKIN_FROM_CGI:
        cgi_printf("the \"skin:\" option on CGI script.\n");
        break;
      case SKIN_FROM_QPARAM:
        cgi_printf("the \"skin=NAME\" query parameter.\n");
        break;
      case SKIN_FROM_COOKIE:
        cgi_printf("the \"skin\" value of the \n"
               "<a href='./fdscookie'>fossil_display_setting</a> cookie.\n");
        break;
      case SKIN_FROM_SETTING:
        cgi_printf("the \"default-skin\" setting.\n");
        break;
      default:
        cgi_printf("reasons unknown.  (Fix me!)\n");
        break;
    }
    cgi_printf("</tr>\n");
  }
  i++;
  cgi_printf("<tr><td colspan=4><h2>Custom skin:</h2></td></tr>\n"
         "<tr><td>%d.\n",(i));
  if( hasCustom ){
    cgi_printf("<td>Custom<td>&nbsp;&nbsp;<td>\n");
  }else{
    cgi_printf("<td><i>(None)</i><td>&nbsp;&nbsp;<td>\n");
  }
  cgi_printf("<form method=\"post\">\n");
  login_insert_csrf_secret();
  if( hasCustom ){
    cgi_printf("<input type=\"submit\" name=\"save\" value=\"Backup\">\n"
           "<input type=\"submit\" name=\"editdraft\" value=\"Edit\">\n");
    if( !seenDefault ){
      cgi_printf("(Selected)\n");
    }else{
      cgi_printf("<input type=\"hidden\" name=\"bisl\" value=\"\">\n"
             "<input type=\"submit\" name=\"setdflt\" value=\"Set\">\n"
             "<input type=\"submit\" name=\"del1\" value=\"Delete\">\n"
             "<input type=\"hidden\" name=\"sn\" value=\"custom\">\n");
    }
  }else{
    cgi_printf("<input type=\"submit\" name=\"editdraft\" value=\"Create\">\n");
  }
  cgi_printf("</form>\n"
         "</td></tr>\n");
  db_prepare(&q,
     "SELECT substr(name, 6) FROM config"
     " WHERE name GLOB 'skin:*'"
     " ORDER BY name"
  );
  once = 1;
  while( db_step(&q)==SQLITE_ROW ){
    const char *zN = db_column_text(&q, 0);
    i++;
    if( once ){
      once = 0;
      cgi_printf("<tr><td colspan=4><h2>Backups of past custom skins:</h2></td></tr>\n");
    }
    cgi_printf("<tr><td>%d.<td>%h<td>&nbsp;&nbsp;<td>\n"
           "<form action=\"%R/setup_skin_admin\" method=\"post\">\n",(i),(zN));
    login_insert_csrf_secret();
    cgi_printf("<input type=\"submit\" name=\"load\" value=\"Install\">\n"
           "<input type=\"submit\" name=\"del1\" value=\"Delete\">\n"
           "<input type=\"submit\" name=\"rename\" value=\"Rename\">\n"
           "<input type=\"hidden\" name=\"sn\" value=\"%h\">\n"
           "</form></tr>\n",(zN));
  }
  db_finalize(&q);
  db_prepare(&q,
     "SELECT DISTINCT substr(name, 1, 6) FROM config"
     " WHERE name GLOB 'draft[1-9]-*'"
     " ORDER BY name"
  );
  once = 1;
  while( db_step(&q)==SQLITE_ROW ){
    const char *zN = db_column_text(&q, 0);
    i++;
    if( once ){
      once = 0;
      cgi_printf("<tr><td colspan=4><h2>Draft skins:</h2></td></tr>\n");
    }
    cgi_printf("<tr><td>%d.<td>%h<td>&nbsp;&nbsp;<td>\n"
           "<form action=\"%R/setup_skin_admin\" method=\"post\">\n",(i),(zN));
    login_insert_csrf_secret();
    cgi_printf("<input type=\"submit\" name=\"load\" value=\"Install\">\n"
           "<input type=\"submit\" name=\"draftdel\" value=\"Delete\">\n"
           "<input type=\"hidden\" name=\"name\" value=\"%h\">\n"
           "<input type=\"hidden\" name=\"sn\" value=\"%h\">\n"
           "</form></tr>\n",(zN),(zN+5));
  }
  db_finalize(&q);

  cgi_printf("</table>\n");
  style_finish_page();
  db_end_transaction(0);
}

/*
** Generate HTML for a <select> that lists all the available skin names,
** except for zExcept if zExcept!=NULL.
*/
static void skin_emit_skin_selector(
  const char *zVarName,      /* Variable name for the <select> */
  const char *zDefault,      /* The default value, if not NULL */
  const char *zExcept        /* Omit this skin if not NULL */
){
  int i;
  Stmt s;
  cgi_printf("<select size='1' name='%s'>\n",(zVarName));
  if( fossil_strcmp(zExcept, "current")!=0 && skin_exists_custom() ){
    cgi_printf("<option value='current'>Current Custom Skin</option>\n");
  }
  for(i=0; i<count(aBuiltinSkin); i++){
    const char *zName = aBuiltinSkin[i].zLabel;
    if( fossil_strcmp(zName, zExcept)==0 ) continue;
    if( fossil_strcmp(zDefault, zName)==0 ){
      cgi_printf("<option value='%s' selected>"
             "%h</option>\n",(zName),(aBuiltinSkin[i].zDesc));
    }else{
      cgi_printf("<option value='%s'>"
             "%h</option>\n",(zName),(aBuiltinSkin[i].zDesc));
    }
  }
  db_prepare(&s, "SELECT DISTINCT substr(name,1,6) FROM config"
                 " WHERE name GLOB 'draft[1-9]-*' ORDER BY 1");
  while( db_step(&s)==SQLITE_ROW ){
    const char *zName = db_column_text(&s, 0);
    if( fossil_strcmp(zName, zExcept)==0 ) continue;
    if( fossil_strcmp(zDefault, zName)==0 ){
      cgi_printf("<option value='%s' selected>%s</option>\n",(zName),(zName));
    }else{
      cgi_printf("<option value='%s'>%s</option>\n",(zName),(zName));
    }
  }
  db_finalize(&s);
  cgi_printf("</select>\n");
}

/*
** Return the text of one of the skin files.
*/
static const char *skin_file_content(const char *zLabel, const char *zFile){
  const char *zResult;
  if( fossil_strcmp(zLabel, "current")==0 ){
    zResult = skin_get(zFile);
  }else if( sqlite3_strglob("draft[1-9]", zLabel)==0 ){
    zResult = db_get_mprintf("", "%s-%s", zLabel, zFile);
  }else{
    int i;
    for(i=0; i<2; i++){
      char *zKey = mprintf("skins/%s/%s.txt", zLabel, zFile);
      zResult = builtin_text(zKey);
      fossil_free(zKey);
      if( zResult!=0 ) break;
      zLabel = "default";
    }
  }
  return zResult;
}

extern const struct strctCssDefaults {
/* From the generated default_css.h, which we cannot #include here
** without causing an ODR violation.
*/
  const char *elementClass;  /* Name of element needed */
  const char *value;         /* CSS text */
} cssDefaultList[];

/*
** WEBPAGE: setup_skinedit
**
** Edit aspects of a skin determined by the w= query parameter.
** Requires Admin or Setup privileges.
**
**    w=NUM     -- 0=CSS, 1=footer, 2=header, 3=details, 4=js
**    sk=NUM    -- the draft skin number
*/
void setup_skinedit(void){
  static const struct sSkinAddr {
    const char *zFile;
    const char *zTitle;
    const char *zSubmenu;
  } aSkinAttr[] = {
    /* 0 */ { "css",     "CSS",             "CSS",     },
    /* 1 */ { "footer",  "Page Footer",     "Footer",  },
    /* 2 */ { "header",  "Page Header",     "Header",  },
    /* 3 */ { "details", "Display Details", "Details", },
    /* 4 */ { "js",      "JavaScript",      "Script",  },
  };
  const char *zBasis;         /* The baseline file */
  const char *zOrig;          /* Original content prior to editing */
  const char *zContent;       /* Content after editing */
  const char *zDflt;          /* Default content */
  char *zDraft;               /* Which draft:  "draft%d" */
  char *zTitle;               /* Title of this page */
  const char *zFile;          /* One of "css", "footer", "header", "details" */
  int iSkin;                  /* draft number.  1..9 */
  int ii;                     /* Index in aSkinAttr[] of this file */
  int j;                      /* Loop counter */
  int isRevert = 0;           /* True if Revert-to-Baseline was pressed */

  login_check_credentials();

  /* Figure out which skin we are editing */
  iSkin = atoi(PD("sk","1"));
  if( iSkin<1 || iSkin>9 ) iSkin = 1;

  /* Check that the user is authorized to edit this skin. */
  if( !g.perm.Admin ){
    char *zAllowedEditors = "";
    Glob *pAllowedEditors;
    int isMatch = 0;
    if( login_is_individual() ){
      zAllowedEditors = db_get_mprintf("", "draft%d-users", iSkin);
    }
    if( zAllowedEditors[0] ){
      pAllowedEditors = glob_create(zAllowedEditors);
      isMatch = glob_match(pAllowedEditors, g.zLogin);
      glob_free(pAllowedEditors);
    }
    if( isMatch==0 ){
      login_needed(0);
      return;
    }
  }

  /* figure out which file is to be edited */
  ii = atoi(PD("w","0"));
  if( ii<0 || ii>count(aSkinAttr) ) ii = 0;
  zFile = aSkinAttr[ii].zFile;
  zDraft = mprintf("draft%d", iSkin);
  zTitle = mprintf("%s for Draft%d", aSkinAttr[ii].zTitle, iSkin);
  zBasis = PD("basis","current");
  zDflt = skin_file_content(zBasis, zFile);
  zOrig = db_get_mprintf(zDflt, "draft%d-%s",iSkin,zFile);
  zContent = PD(zFile,zOrig);
  if( P("revert")!=0 && cgi_csrf_safe(2) ){
    zContent = zDflt;
    isRevert = 1;
  }

  db_begin_transaction();
  style_set_current_feature("skins");
  style_header("%s", zTitle);
  for(j=0; j<count(aSkinAttr); j++){
    style_submenu_element(aSkinAttr[j].zSubmenu,
          "%R/setup_skinedit?w=%d&basis=%h&sk=%d",j,zBasis,iSkin);
  }
  cgi_printf("<form action=\"%R/setup_skinedit\" method=\"post\"><div>\n");
  login_insert_csrf_secret();
  cgi_printf("<input type='hidden' name='w' value='%d'>\n"
         "<input type='hidden' name='sk' value='%d'>\n"
         "<h2>Edit %s:</h2>\n",(ii),(iSkin),(zTitle));
  if( P("submit") && cgi_csrf_safe(2)
   && (zOrig==0 || strcmp(zOrig,zContent)!=0)
  ){
    db_set_mprintf(zContent, 0, "draft%d-%s",iSkin,zFile);
  }
  cgi_printf("<textarea name=\"%s\" rows=\"10\" cols=\"80\">"
         "%h</textarea>\n"
         "<br>\n"
         "<input type=\"submit\" name=\"submit\" value=\"Apply Changes\">\n",(zFile),(zContent));
  if( isRevert ){
    cgi_printf("&larr; Press to complete reversion to \"%s\"\n",(zBasis));
  }else if( fossil_strcmp(zContent,zDflt)!=0 ){
    cgi_printf("<input type=\"submit\" name=\"revert\" value='Revert To \"%s\"'>\n",(zBasis));
  }
  cgi_printf("<hr>\n"
         "Baseline: ");
  skin_emit_skin_selector("basis", zBasis, zDraft);
  cgi_printf("<input type=\"submit\" name=\"diff\" value=\"Unified Diff\">\n"
         "<input type=\"submit\" name=\"sbsdiff\" value=\"Side-by-Side Diff\">\n");
  if( P("diff")!=0 || P("sbsdiff")!=0 ){
    Blob from, to, out;
    DiffConfig DCfg;
    construct_diff_flags(1, &DCfg);
    DCfg.diffFlags |= DIFF_STRIP_EOLCR;
    if( P("sbsdiff")!=0 ) DCfg.diffFlags |= DIFF_SIDEBYSIDE;
    blob_init(&to, zContent, -1);
    blob_init(&from, skin_file_content(zBasis, zFile), -1);
    blob_zero(&out);
    DCfg.diffFlags |= DIFF_HTML | DIFF_NOTTOOBIG;
    if( DCfg.diffFlags & DIFF_SIDEBYSIDE ){
      text_diff(&from, &to, &out, &DCfg);
      cgi_printf("%s\n",(blob_str(&out)));
    }else{
      DCfg.diffFlags |= DIFF_LINENO;
      text_diff(&from, &to, &out, &DCfg);
      cgi_printf("<pre class=\"udiff\">\n"
             "%s\n"
             "</pre>\n",(blob_str(&out)));
    }
    blob_reset(&from);
    blob_reset(&to);
    blob_reset(&out);
  }
  cgi_printf("</div></form>\n");
  style_finish_page();
  db_end_transaction(0);
}

/*
** Try to initialize draft skin iSkin to the built-in or preexisting
** skin named by zTemplate.
*/
static void skin_initialize_draft(int iSkin, const char *zTemplate){
  int i;
  if( zTemplate==0 ) return;
  for(i=0; i<count(azSkinFile); i++){
    const char *z = skin_file_content(zTemplate, azSkinFile[i]);
    db_set_mprintf(z, 0, "draft%d-%s", iSkin, azSkinFile[i]);
  }
}

/*
** Publish the draft skin iSkin as the new default.
*/
static void skin_publish(int iSkin){
  char *zCurrent;    /* SQL description of the current skin */
  char *zBuiltin;    /* SQL description of a built-in skin */
  int i;
  int seen = 0;      /* True if no need to make a backup */

  /* Check to see if the current skin is already saved.  If it is, there
  ** is no need to create a backup */
  zCurrent = getSkin(0);
  for(i=0; i<count(aBuiltinSkin); i++){
    zBuiltin = getSkin(aBuiltinSkin[i].zLabel);
    if( fossil_strcmp(zBuiltin, zCurrent)==0 ){
      seen = 1;
      break;
    }
  }
  if( !seen ){
    seen = db_exists("SELECT 1 FROM config WHERE name GLOB 'skin:*'"
                       " AND value=%Q", zCurrent);
  }
  if( !seen ){
    db_unprotect(PROTECT_CONFIG);
    db_multi_exec(
      "INSERT INTO config(name,value,mtime) VALUES("
      "  strftime('skin:Backup On %%Y-%%m-%%d %%H:%%M:%%S'),"
      "  %Q,now())", zCurrent
    );
    db_protect_pop();
  }

  /* Publish draft iSkin */
  for(i=0; i<count(azSkinFile); i++){
    char *zNew = db_get_mprintf("", "draft%d-%s", iSkin, azSkinFile[i]);
    db_set(azSkinFile[i]/*works-like:"x"*/, zNew, 0);
  }
  db_unset("default-skin", 0);
}

/*
** WEBPAGE: setup_skin
**
** Generate a page showing the steps needed to create or edit
** a custom skin.
*/
void setup_skin(void){
  int i;          /* Loop counter */
  int iSkin;      /* Which draft skin is being edited */
  int isSetup;    /* True for an administrator */
  int isEditor;   /* Others authorized to make edits */
  char *zAllowedEditors;   /* Who may edit the draft skin */
  char *zBase;             /* Base URL for draft under test */
  static const char *const azTestPages[] = {
     "home",
     "timeline",
     "dir?ci=tip",
     "dir?ci=tip&type=tree",
     "brlist",
     "info/trunk",
  };

  /* Figure out which skin we are editing */
  iSkin = atoi(PD("sk","1"));
  if( iSkin<1 || iSkin>9 ) iSkin = 1;

  /* Figure out if the current user is allowed to make administrative
  ** changes and/or edits
  */
  login_check_credentials();
  if( !login_is_individual() ){
    login_needed(0);
    return;
  }
  zAllowedEditors = db_get_mprintf("", "draft%d-users", iSkin);
  if( g.perm.Admin ){
    isSetup = isEditor = 1;
  }else{
    Glob *pAllowedEditors;
    isSetup = isEditor = 0;
    if( zAllowedEditors[0] ){
      pAllowedEditors = glob_create(zAllowedEditors);
      isEditor = glob_match(pAllowedEditors, g.zLogin);
      glob_free(pAllowedEditors);
    }
  }

  /* Initialize the skin, if requested and authorized. */
  if( P("init3")!=0 && isEditor ){
    skin_initialize_draft(iSkin, P("initskin"));
  }
  if( P("submit2")!=0 && isSetup ){
    db_set_mprintf(PD("editors",""), 0, "draft%d-users", iSkin);
    zAllowedEditors = db_get_mprintf("", "draft%d-users", iSkin);
  }

  /* Publish the draft skin */
  if( P("pub7")!=0 && PB("pub7ck1") && PB("pub7ck2") ){
    skin_publish(iSkin);
  }

  style_set_current_feature("skins");
  style_header("Customize Skin");
  if( g.perm.Admin ){
    style_submenu_element("Skin-Admin", "%R/setup_skin_admin");
  }

  cgi_printf("<p>Customize the look of this Fossil repository by making changes\n"
         "to the CSS, Header, Footer, and Detail Settings in one of nine \"draft\"\n"
         "configurations.  Then, after verifying that all is working correctly,\n"
         "publish the draft to become the new main Skin. Users can select a skin\n"
         "of their choice from the built-in ones or the locally-edited one via\n"
         "<a href='%R/skins'>the /skins page</a>.</p>\n"
         "\n"
         "<a name='step1'></a>\n"
         "<h1>Step 1: Identify Which Draft To Use</h1>\n"
         "\n"
         "<p>The main skin of Fossil cannot be edited directly.  Instead,\n"
         "edits are made to one of nine draft skins.  A draft skin can then\n"
         "be published to become the default skin.\n"
         "Nine separate drafts are available to facilitate A/B testing.</p>\n"
         "\n"
         "<form method='POST' action='%R/setup_skin#step2' id='f01'>\n"
         "<p class='skinInput'>Draft skin to edit:\n"
         "<select size='1' name='sk' id='skStep1'>\n");
  for(i=1; i<=9; i++){
    if( i==iSkin ){
      cgi_printf("<option value='%d' selected>draft%d</option>\n",(i),(i));
    }else{
      cgi_printf("<option value='%d'>draft%d</option>\n",(i),(i));
    }
  }
  cgi_printf("</select>\n"
         "</p>\n"
         "</form>\n"
         "\n"
         "<a name='step2'></a>\n"
         "<h1>Step 2: Authenticate</h1>\n"
         "\n");
  if( isSetup ){
    cgi_printf("<p>As an administrator, you can make any edits you like to this or\n"
           "any other skin.  You can also authorize other users to edit this\n"
           "skin.  Any user whose login name matches the comma-separated list\n"
           "of GLOB expressions below is given special permission to edit\n"
           "the draft%d skin:\n"
           "\n"
           "<form method='POST' action='%R/setup_skin#step2' id='f02'>\n"
           "<p class='skinInput'>\n"
           "<input type='hidden' name='sk' value='%d'>\n"
           "Authorized editors for skin draft%d:\n"
           "<input type='text' name='editors' value='%h'"
           " width='40'>\n"
           "<input type='submit' name='submit2' value='Change'>\n"
           "</p>\n"
           "</form>\n",(iSkin),(iSkin),(iSkin),(zAllowedEditors));
  }else if( isEditor ){
    cgi_printf("<p>You are authorized to make changes to the draft%d skin.\n"
           "Continue to the <a href='#step3'>next step</a>.</p>\n",(iSkin));
  }else{
    cgi_printf("<p>You are not authorized to make changes to the draft%d\n"
           "skin.  Contact the administrator of this Fossil repository for\n"
           "further information.</p>\n",(iSkin));
  }
  cgi_printf("\n"
         "<a name='step3'></a>\n"
         "<h1>Step 3: Initialize The Draft</h1>\n"
         "\n");
  if( !isEditor ){
    cgi_printf("<p>You are not allowed to initialize draft%d.  Contact\n"
           "the administrator for this repository for more information.\n",(iSkin));
  }else{
    char *zDraft = mprintf("draft%d", iSkin);
    cgi_printf("<p>Initialize the draft%d skin to one of the built-in skins\n"
           "or a preexisting skin, to use as a baseline.</p>\n"
           "\n"
           "<form method='POST' action='%R/setup_skin#step4' id='f03'>\n"
           "<p class='skinInput'>\n"
           "<input type='hidden' name='sk' value='%d'>\n"
           "Initialize skin <b>draft%d</b> using\n",(iSkin),(iSkin),(iSkin));
    skin_emit_skin_selector("initskin", 0, zDraft);
    fossil_free(zDraft);
    cgi_printf("<input type='submit' name='init3' value='Go'>\n"
           "</p>\n"
           "</form>\n");
  }
  cgi_printf("\n"
         "<a name='step4'></a>\n"
         "<h1>Step 4: Make Edits</h1>\n"
         "\n");
  if( !isEditor ){
    cgi_printf("<p>You are not authorized to make edits to the draft%d skin.\n"
           "Contact the administrator of this Fossil repository for help.</p>\n",(iSkin));
  }else{
    cgi_printf("<p>Edit the components of the draft%d skin:\n"
           "<ul>\n"
           "<li><a href='%R/setup_skinedit?w=0&sk=%d' target='_blank'>CSS</a>\n"
           "<li><a href='%R/setup_skinedit?w=2&sk=%d' target='_blank'>"
           "Header</a>\n"
           "<li><a href='%R/setup_skinedit?w=1&sk=%d' target='_blank'>"
           "Footer</a>\n"
           "<li><a href='%R/setup_skinedit?w=3&sk=%d' target='_blank'>"
           "Details</a>\n"
           "<li><a href='%R/setup_skinedit?w=4&sk=%d' target='_blank'>"
           "Javascript</a> (optional)\n"
           "</ul>\n",(iSkin),(iSkin),(iSkin),(iSkin),(iSkin),(iSkin));
  }
  cgi_printf("\n"
         "<a name='step5'></a>\n"
         "<h1>Step 5: Verify The Draft Skin</h1>\n"
         "\n"
         "<p>To test this draft skin, insert text \"/draft%d/\" just before the\n"
         "operation name in the URL.  Here are a few links to try:\n"
         "<ul>\n",(iSkin));
  if( iDraftSkin && sqlite3_strglob("*/draft[1-9]", g.zBaseURL)==0 ){
    zBase = mprintf("%.*s/draft%d", (int)strlen(g.zBaseURL)-7,g.zBaseURL,iSkin);
  }else{
    zBase = mprintf("%s/draft%d", g.zBaseURL, iSkin);
  }
  for(i=0; i<count(azTestPages); i++){
    cgi_printf("<li><a href='%s/%s' target='_blank'>"
           "%s/%s</a>\n",(zBase),(azTestPages[i]),(zBase),(azTestPages[i]));
  }
  fossil_free(zBase);
  cgi_printf("</ul>\n"
         "\n"
         "<p>You will probably need to press Reload on your browser before any\n"
         "CSS changes will take effect.</p>\n"
         "\n"
         "<a hame='step6'></a>\n"
         "<h1>Step 6: Iterate</h1>\n"
         "\n"
         "<p>Repeat <a href='#step4'>step 4</a> and\n"
         "<a href='#step5'>step 5</a> as many times as necessary to create\n"
         "a production-ready skin.\n"
         "\n"
         "<a name='step7'></a>\n"
         "<h1>Step 7: Publish</h1>\n"
         "\n");
  if( !g.perm.Admin ){
    cgi_printf("<p>Only administrators are allowed to publish draft skins.  Contact\n"
           "an administrator to get this \"draft%d\" skin published.</p>\n",(iSkin));
  }else{
    cgi_printf("<p>When the draft%d skin is ready for production use,\n"
           "make it the default skin by clicking the acknowledgements and\n"
           "pressing the button below:</p>\n"
           "\n"
           "<form method='POST' action='%R/setup_skin#step7'>\n"
           "<p class='skinInput'>\n"
           "<input type='hidden' name='sk' value='%d'>\n"
           "<input type='checkbox' name='pub7ck1' value='yes'>"
           "Skin draft%d has been tested and found ready for production.<br>\n"
           "<input type='checkbox' name='pub7ck2' value='yes'>"
           "The current skin should be overwritten with draft%d.<br>\n"
           "<input type='submit' name='pub7' value='Publish Draft%d'>\n"
           "</p></form>\n"
           "\n"
           "<p>You will probably need to press Reload on your browser after\n"
           "publishing the new skin.</p>\n",(iSkin),(iSkin),(iSkin),(iSkin),(iSkin));
  }
  cgi_printf("\n"
         "<a name='step8'></a>\n"
         "<h1>Step 8: Cleanup and Undo Actions</h1>\n"
         "\n");
  if( !g.perm.Admin ){
    cgi_printf("<p>Administrators can optionally save or restore legacy skins, and/or\n"
           "undo a prior publish.\n");
  }else{
    cgi_printf("<p>Visit the <a href='%R/setup_skin_admin'>Skin Admin</a> page\n"
           "for cleanup and recovery actions.\n");
  }
  builtin_request_js("skin.js");
  style_finish_page();
}

/*
** WEBPAGE: skins
**
** Show a list of all of the built-in skins, plus the respository skin,
** and provide the user with an opportunity to change to any of them.
*/
void skins_page(void){
  int i;
  char *zBase = fossil_strdup(g.zTop);
  size_t nBase = strlen(zBase);
  login_check_credentials();
  if( iDraftSkin && sqlite3_strglob("*/draft?", zBase)==0 ){
    nBase -= 7;
    zBase[nBase] = 0;
  }else if( pAltSkin ){
    char *zPattern = mprintf("*/skn_%s", pAltSkin->zLabel);
    if( sqlite3_strglob(zPattern, zBase)==0 ){
      nBase -= strlen(zPattern)-1;
      zBase[nBase] = 0;
    }
    fossil_free(zPattern);
  }
  style_header("Skins");
  if( iDraftSkin || nSkinRank<=1 ){
    cgi_printf("<p class=\"warning\">Warning:\n");
    if( iDraftSkin>0 ){
      cgi_printf("you are using a draft skin,\n");
    }else{
      cgi_printf("this fossil instance was started with a hard-coded skin\n"
             "value\n");
    }
    cgi_printf("which supercedes any option selected below. A skin selected\n"
           "below will be recorded in your \n"
           "\"%zfossil_display_settings</a>\" cookie\n"
           "but will not be used so long as the site has a\n"
           "higher-priority skin in place.\n"
           "</p>\n",(href("%R/fdscookie")));
  }
  cgi_printf("<p>The following skins are available for this repository:</p>\n"
         "<ul>\n");
  for(i=0; i<count(aBuiltinSkin); i++){
    if( pAltSkin==&aBuiltinSkin[i] ){
      cgi_printf("<li> %h &larr; <i>Currently in use</i>\n",(aBuiltinSkin[i].zDesc));
    }else{
      char *zUrl = href("%R/skins?skin=%T", aBuiltinSkin[i].zLabel);
      cgi_printf("<li> %z%h</a>\n",(zUrl),(aBuiltinSkin[i].zDesc));
    }
  }
  if( skin_exists_custom() ){
    if( pAltSkin==0 && zAltSkinDir==0 && iDraftSkin==0 ){
      cgi_printf("<li> Custom skin for this repository &larr; <i>Currently in use</i>\n");
    }else{
      cgi_printf("<li> %z"
             "Custom skin for this repository</a>\n",(href("%R/skins?skin=custom")));
    }
  }
  cgi_printf("</ul>\n");
  if( iSkinSource<SKIN_FROM_CUSTOM ){
    cgi_printf("<p>The current skin is selected by\n");
    switch( iSkinSource ){
      case SKIN_FROM_DRAFT:
         cgi_printf("the \"debugN\" prefix on the PATH_INFO portion of the URL.\n");
         break;
      case SKIN_FROM_CMDLINE:
         cgi_printf("the \"--skin\" command-line option on the Fossil server.\n");
         break;
      case SKIN_FROM_CGI:
         cgi_printf("the \"skin:\" property in the CGI script that runs the Fossil server.\n");
         break;
      case SKIN_FROM_QPARAM:
         cgi_printf("the \"skin=NAME\" query parameter on the URL.\n");
         break;
      case SKIN_FROM_COOKIE:
         cgi_printf("the \"skin\" property in the\n"
                "\"%zfossil_display_settings</a>\" cookie.\n",(href("%R/fdscookie")));
         break;
      case SKIN_FROM_SETTING:
         cgi_printf("the \"default-skin\" setting on the repository.\n");
         break;
    }
  }
  if( iSkinSource==SKIN_FROM_COOKIE || iSkinSource==SKIN_FROM_QPARAM ){
    cgi_printf("<ul>\n"
           "<li> %z<i>Let Fossil choose "
           "which skin to use</i></a>\n"
           "</ul>\n",(href("%R/skins?skin=")));
  }
  style_finish_page();
  if( P("skin")!=0 ){
    sqlite3_uint64 x;
    sqlite3_randomness(sizeof(x), &x);
    cgi_redirectf("%R/skins/%llx", x);
  }
  fossil_free(zBase);
}
