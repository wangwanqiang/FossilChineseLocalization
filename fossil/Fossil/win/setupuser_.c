#line 1 "C:\\source\\fossil_depot\\fossil\\Fossil\\src\\setupuser.c"
/*
** Copyright (c) 2007 D. Richard Hipp
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
** Setup pages associated with user management.  The code in this
** file was formerly part of the "setup.c" module, but has been broken
** out into its own module to improve maintainability.
**
** Note:  Do not confuse "Users" with "Subscribers".  Code to deal with
** subscribers is over in the "alerts.c" source file.
*/
#include "config.h"
#include <assert.h>
#include "setupuser.h"

/*
** WEBPAGE: setup_ulist
**
** Show a list of users.  Clicking on any user jumps to the edit
** screen for that user.  Requires Admin privileges.
**
** Query parameters:
**
**   with=CAP         Only show users that have one or more capabilities in CAP.
**   ubg              Color backgrounds by username hash
*/
void setup_ulist(void){
  Stmt s;
  double rNow;
  const char *zWith = P("with");
  int bUnusedOnly = P("unused")!=0;
  int bUbg = P("ubg")!=0;
  int bHaveAlerts;

  login_check_credentials();
  if( !g.perm.Admin ){
    login_needed(0);
    return;
  }
  bHaveAlerts = alert_tables_exist();
  style_submenu_element("Add", "setup_uedit");
  style_submenu_element("Log", "access_log");
  style_submenu_element("Help", "setup_ulist_notes");
  if( bHaveAlerts ){
    style_submenu_element("Subscribers", "subscribers");
  }
  style_set_current_feature("setup");
  style_header("User List");
  if( (zWith==0 || zWith[0]==0) && !bUnusedOnly ){
    cgi_printf("<table border=1 cellpadding=2 cellspacing=0 class='userTable'>\n"
           "<thead><tr>\n"
           "  <th>Category\n"
           "  <th>Capabilities (<a href='%R/setup_ucap_list'>key</a>)\n"
           "  <th>Info <th>Last Change</tr></thead>\n"
           "<tbody>\n");
    db_prepare(&s,
       "SELECT uid, login, cap, date(mtime,'unixepoch')"
       "  FROM user"
       " WHERE login IN ('anonymous','nobody','developer','reader')"
       " ORDER BY login"
    );
    while( db_step(&s)==SQLITE_ROW ){
      int uid = db_column_int(&s, 0);
      const char *zLogin = db_column_text(&s, 1);
      const char *zCap = db_column_text(&s, 2);
      const char *zDate = db_column_text(&s, 4);
      cgi_printf("<tr>\n"
             "<td><a href='setup_uedit?id=%d'>%h</a>\n"
             "<td>%h\n",(uid),(zLogin),(zCap));

      if( fossil_strcmp(zLogin,"anonymous")==0 ){
        cgi_printf("<td>All logged-in users\n");
      }else if( fossil_strcmp(zLogin,"developer")==0 ){
        cgi_printf("<td>Users with '<b>v</b>' capability\n");
      }else if( fossil_strcmp(zLogin,"nobody")==0 ){
        cgi_printf("<td>All users without login\n");
      }else if( fossil_strcmp(zLogin,"reader")==0 ){
        cgi_printf("<td>Users with '<b>u</b>' capability\n");
      }else{
        cgi_printf("<td>\n");
      }
      if( zDate && zDate[0] ){
        cgi_printf("<td>%h\n",(zDate));
      }else{
        cgi_printf("<td>\n");
      }
      cgi_printf("</tr>\n");
    }
    db_finalize(&s);
    cgi_printf("</tbody></table>\n"
           "<div class='section'>Users</div>\n");
  }else{
    style_submenu_element("All Users", "setup_ulist");
    if( bUnusedOnly ){
      cgi_printf("<div class='section'>Unused logins</div>\n");
    }else if( zWith ){
      if( zWith[1]==0 ){
        cgi_printf("<div class='section'>Users with capability \"%h\"</div>\n",(zWith));
      }else{
        cgi_printf("<div class='section'>Users with any capability in \"%h\"</div>\n",(zWith));
      }
    }
  }
  if( !bUnusedOnly ){
    style_submenu_element("Unused", "setup_ulist?unused");
  }
  cgi_printf("<table border=1 cellpadding=2 cellspacing=0 class='userTable sortable' "
         " data-column-types='ktxKTKt' data-init-sort='4'>\n"
         "<thead><tr>\n"
         "<th>Login Name<th>Caps<th>Info<th>Date<th>Expire<th>Last Login"
         "<th>Alerts</tr></thead>\n"
         "<tbody>\n");
  db_multi_exec(
    "CREATE TEMP TABLE lastAccess(uname TEXT PRIMARY KEY, atime REAL)"
    "WITHOUT ROWID;"
  );
  if( db_table_exists("repository","accesslog") ){
    db_multi_exec(
      "INSERT INTO lastAccess(uname, atime)"
      " SELECT uname, max(mtime) FROM ("
      "    SELECT uname, mtime FROM accesslog WHERE success"
      "    UNION ALL"
      "    SELECT login AS uname, rcvfrom.mtime AS mtime"
      "      FROM rcvfrom JOIN user USING(uid))"
      " GROUP BY 1;"
    );
  }
  if( !db_table_exists("repository","subscriber") ){
    db_multi_exec(
      "CREATE TEMP TABLE subscriber(suname PRIMARY KEY, ssub, subscriberId)"
      "WITHOUT ROWID;"
    );
  }
  if( bUnusedOnly ){
    zWith = mprintf(
        " AND login NOT IN ("
        "SELECT user FROM event WHERE user NOT NULL "
        "UNION ALL SELECT euser FROM event WHERE euser NOT NULL%s)"
        " AND uid NOT IN (SELECT uid FROM rcvfrom)",
        bHaveAlerts ?
          " UNION ALL SELECT suname FROM subscriber WHERE suname NOT NULL":"");
  }else if( zWith && zWith[0] ){
    zWith = mprintf(" AND fullcap(cap) GLOB '*[%q]*'", zWith);
  }else{
    zWith = "";
  }
  db_prepare(&s,
      /*0-4*/"SELECT uid, login, cap, info, date(user.mtime,'unixepoch'),"
      /* 5 */"lower(login) AS sortkey, "
      /* 6 */"CASE WHEN info LIKE '%%expires 20%%'"
             "    THEN substr(info,instr(lower(info),'expires')+8,10)"
             "    END AS exp,"
      /* 7 */"atime,"
      /* 8 */"user.mtime AS sorttime,"
      /*9-11*/"%s"
             " FROM user LEFT JOIN lastAccess ON login=uname"
             "            LEFT JOIN subscriber ON login=suname"
             " WHERE login NOT IN ('anonymous','nobody','developer','reader') %s"
             " ORDER BY sorttime DESC",
             bHaveAlerts
             ? "subscriber.ssub, subscriber.subscriberId, subscriber.semail"
             : "null, null, null",
             zWith/*safe-for-%s*/
  );
  rNow = db_double(0.0, "SELECT julianday('now');");
  while( db_step(&s)==SQLITE_ROW ){
    int uid = db_column_int(&s, 0);
    const char *zLogin = db_column_text(&s, 1);
    const char *zCap = db_column_text(&s, 2);
    const char *zInfo = db_column_text(&s, 3);
    const char *zDate = db_column_text(&s, 4);
    const char *zSortKey = db_column_text(&s,5);
    const char *zExp = db_column_text(&s,6);
    double rATime = db_column_double(&s,7);
    char *zAge = 0;
    const char *zSub;
    int sid = db_column_int(&s,10);
    sqlite3_int64 sorttime = db_column_int64(&s, 8);
    if( rATime>0.0 ){
      zAge = human_readable_age(rNow - rATime);
    }
    if( bUbg ){
      cgi_printf("<tr style='background-color: %h;'>\n",(user_color(zLogin)));
    }else{
      cgi_printf("<tr>\n");
    }
    cgi_printf("<td data-sortkey='%h'>"
           "<a href='setup_uedit?id=%d'>%h</a>\n"
           "<td>%h\n"
           "<td>%h\n"
           "<td data-sortkey='%09llx'>%h\n"
           "<td>%h\n"
           "<td data-sortkey='%f' style='white-space:nowrap'>%s\n",(zSortKey),(uid),(zLogin),(zCap),(zInfo),(sorttime),(zDate?zDate:""),(zExp?zExp:""),(rATime),(zAge?zAge:""));
    if( db_column_type(&s,9)==SQLITE_NULL ){
      cgi_printf("<td>\n");
    }else if( (zSub = db_column_text(&s,9))==0 || zSub[0]==0 ){
      cgi_printf("<td><a href=\"%R/alerts?sid=%d\"><i>off</i></a>\n",(sid));
    }else{
      const char *zEmail = db_column_text(&s, 11);
      char * zAt = zEmail ? mprintf(" &rarr; %h", zEmail) : mprintf("");
      cgi_printf("<td><a href=\"%R/alerts?sid=%d\">%h</a>  %z\n",(sid),(zSub),(zAt));
    }

    cgi_printf("</tr>\n");
    fossil_free(zAge);
  }
  cgi_printf("</tbody></table>\n");
  db_finalize(&s);
  style_table_sorter();
  style_finish_page();
}

/*
** WEBPAGE: setup_ulist_notes
**
** A documentation page showing notes about user configuration.  This
** information used to be a side-bar on the user list page, but has been
** factored out for improved presentation.
*/
void setup_ulist_notes(void){
  style_set_current_feature("setup");
  style_header("User Configuration Notes");
  cgi_printf("<h1>User Configuration Notes:</h1>\n"
         "<ol>\n"
         "<li><p>\n"
         "Every user, logged in or not, inherits the privileges of\n"
         "<span class=\"usertype\">nobody</span>.\n"
         "</p></li>\n"
         "\n"
         "<li><p>\n"
         "Any human can login as <span class=\"usertype\">anonymous</span> since the\n"
         "password is clearly displayed on the login page for them to type. The\n"
         "purpose of requiring anonymous to log in is to prevent access by spiders.\n"
         "Every logged-in user inherits the combined privileges of\n"
         "<span class=\"usertype\">anonymous</span> and\n"
         "<span class=\"usertype\">nobody</span>.\n"
         "</p></li>\n"
         "\n"
         "<li><p>\n"
         "Users with privilege <span class=\"capability\">u</span> inherit the combined\n"
         "privileges of <span class=\"usertype\">reader</span>,\n"
         "<span class=\"usertype\">anonymous</span>, and\n"
         "<span class=\"usertype\">nobody</span>.\n"
         "</p></li>\n"
         "\n"
         "<li><p>\n"
         "Users with privilege <span class=\"capability\">v</span> inherit the combined\n"
         "privileges of <span class=\"usertype\">developer</span>,\n"
         "<span class=\"usertype\">anonymous</span>, and\n"
         "<span class=\"usertype\">nobody</span>.\n"
         "</p></li>\n"
         "\n"
         "<li><p>The permission flags are as follows:</p>\n");
  capabilities_table(CAPCLASS_ALL);
  cgi_printf("</li>\n"
         "</ol>\n");
  style_finish_page();
}

/*
** WEBPAGE: setup_ucap_list
**
** A documentation page showing the meaning of the various user capabilities
** code letters.
*/
void setup_ucap_list(void){
  style_set_current_feature("setup");
  style_header("User Capability Codes");
  cgi_printf("<h1>All capabilities</h1>\n");
  capabilities_table(CAPCLASS_ALL);
  cgi_printf("<h1>Capabilities associated with checked-in content</h1>\n");
  capabilities_table(CAPCLASS_CODE);
  cgi_printf("<h1>Capabilities associated with data transfer and sync</h1>\n");
  capabilities_table(CAPCLASS_DATA);
  cgi_printf("<h1>Capabilities associated with the forum</h1>\n");
  capabilities_table(CAPCLASS_FORUM);
  cgi_printf("<h1>Capabilities associated with tickets</h1>\n");
  capabilities_table(CAPCLASS_TKT);
  cgi_printf("<h1>Capabilities associated with wiki</h1>\n");
  capabilities_table(CAPCLASS_WIKI);
  cgi_printf("<h1>Administrative capabilities</h1>\n");
  capabilities_table(CAPCLASS_SUPER);
  cgi_printf("<h1>Miscellaneous capabilities</h1>\n");
  capabilities_table(CAPCLASS_OTHER);
  style_finish_page();
}

/*
** Return true if zPw is a valid password string.  A valid
** password string is:
**
**  (1)  A zero-length string, or
**  (2)  a string that contains a character other than '*'.
*/
static int isValidPwString(const char *zPw){
  if( zPw==0 ) return 0;
  if( zPw[0]==0 ) return 1;
  while( zPw[0]=='*' ){ zPw++; }
  return zPw[0]!=0;
}

/*
** Return true if user capability strings zOrig and zNew materially
** differ, taking into account that they may be sorted in an arbitary
** order. This does not take inherited permissions into
** account. Either argument may be NULL. A NULL and an empty string
** are considered equivalent here. e.g. "abc" and "cab" are equivalent
** for this purpose, but "aCb" and "acb" are not.
*/
static int userCapsChanged(const char *zOrig, const char *zNew){
  if( !zOrig ){
    return zNew ? (0!=*zNew) : 0;
  }else if( !zNew ){
    return 0!=*zOrig;
  }else if( 0==fossil_strcmp(zOrig, zNew) ){
    return 0;
  }else{
    /* We don't know that zOrig and zNew are sorted equivalently.  The
    ** following steps will compare strings which contain all the same
    ** capabilities letters as equivalent, regardless of the letters'
    ** order in their strings. */
    char aOrig[128]; /* table of zOrig bytes */
    int nOrig = 0, nNew = 0;

    memset( &aOrig[0], 0, sizeof(aOrig) );
    for( ; *zOrig; ++zOrig, ++nOrig ){
      if( 0==(*zOrig & 0x80) ){
        aOrig[(int)*zOrig] = 1;
      }
    }
    for( ; *zNew; ++zNew, ++nNew ){
      if( 0==(*zNew & 0x80) && !aOrig[(int)*zNew] ){
        return 1;
      }
    }
    return nOrig!=nNew;
  }
}

/*
** COMMAND: test-user-caps-changed
**
** Usage: %fossil test-user-caps-changed caps1 caps2
**
*/
void test_user_caps_changed(void){

  char const * zOld = g.argc>2 ? g.argv[2] : NULL;
  char const * zNew = g.argc>3 ? g.argv[3] : NULL;
  fossil_print("Has changes? = %d\n",
               userCapsChanged( zOld, zNew ));
}

/*
** Sends notification of user permission elevation changes to all
** subscribers with a "u" subscription. This is a no-op if alerts are
** not enabled.
**
** These subscriptions differ from most, in that:
**
** - They currently lack an "unsubscribe" link.
**
** - Only an admin can assign this subscription, but if a non-admin
**   edits their subscriptions after an admin assigns them this one,
**   this particular one will be lost.  "Feature or bug?" is unclear,
**   but it would be odd for a non-admin to be assigned this
**   capability.
*/
static void alert_user_cap_change(const char *zLogin,   /*Affected user*/
                                 int uid,              /*[user].uid*/
                                 int bIsNew,           /*true if new user*/
                                 const char *zOrigCaps,/*Old caps*/
                                 const char *zNewCaps  /*New caps*/){
  Blob hdr, body;
  Stmt q;
  int nBody;
  AlertSender *pSender;
  char *zSubname;
  char *zURL;
  char * zSubject;

  if( !alert_enabled() ) return;
  zSubject = bIsNew
    ? mprintf("New user created: [%q]", zLogin)
    : mprintf("User [%q] capabilities changed", zLogin);
  zURL = db_get("email-url",0);
  zSubname = db_get("email-subname", "[Fossil Repo]");
  blob_init(&body, 0, 0);
  blob_init(&hdr, 0, 0);
  if( bIsNew ){
    blob_appendf(&body, "User [%q] was created with "
                 "permissions [%q] by user [%q].\n",
                 zLogin, zNewCaps, g.zLogin);
  } else {
    blob_appendf(&body, "Permissions for user [%q] where changed "
                 "from [%q] to [%q] by user [%q].\n",
                 zLogin, zOrigCaps, zNewCaps, g.zLogin);
  }
  if( zURL ){
    blob_appendf(&body, "\nUser editor: %s/setup_uedit?id=%d\n", zURL, uid);
  }
  nBody = blob_size(&body);
  pSender = alert_sender_new(0, 0);
  db_prepare(&q,
        "SELECT semail, hex(subscriberCode)"
        "  FROM subscriber, user "
        " WHERE sverified AND NOT sdonotcall"
        "   AND suname=login"
        "   AND ssub GLOB '*u*'");
  while( !pSender->zErr && db_step(&q)==SQLITE_ROW ){
    const char *zTo = db_column_text(&q, 0);
    blob_truncate(&hdr, 0);
    blob_appendf(&hdr, "To: <%s>\r\nSubject: %s %s\r\n",
                 zTo, zSubname, zSubject);
    if( zURL ){
      const char *zCode = db_column_text(&q, 1);
      blob_truncate(&body, nBody);
      blob_appendf(&body,"\n-- \nSubscription info: %s/alerts/%s\n",
                   zURL, zCode);
    }
    alert_send(pSender, &hdr, &body, 0);
  }
  db_finalize(&q);
  alert_sender_free(pSender);
  fossil_free(zURL);
  fossil_free(zSubname);
  fossil_free(zSubject);
}

/*
** WEBPAGE: setup_uedit
**
** Edit information about a user or create a new user.
** Requires Admin privileges.
*/
void user_edit(void){
  const char *zId, *zLogin, *zInfo, *zCap, *zPw;
  const char *zGroup;
  const char *zOldLogin;
  int uid, i;
  char *zOldCaps = 0;        /* Capabilities before edit */
  char *zDeleteVerify = 0;   /* Delete user verification text */
  int higherUser = 0;  /* True if user being edited is SETUP and the */
                       /* user doing the editing is ADMIN.  Disallow editing */
  const char *inherit[128];
  int a[128];
  const char *oa[128];

  /* Must have ADMIN privileges to access this page
  */
  login_check_credentials();
  if( !g.perm.Admin ){ login_needed(0); return; }

  /* Check to see if an ADMIN user is trying to edit a SETUP account.
  ** Don't allow that.
  */
  zId = PD("id", "0");
  uid = atoi(zId);
  if( uid>0 ){
    zOldCaps = db_text("", "SELECT cap FROM user WHERE uid=%d",uid);
    if( zId && !g.perm.Setup ){
      higherUser = zOldCaps && strchr(zOldCaps,'s');
    }
  }

  if( P("can") ){
    /* User pressed the cancel button */
    cgi_redirect(cgi_referer("setup_ulist"));
    return;
  }

  /* Check for requests to delete the user */
  if( P("delete") && cgi_csrf_safe(2) ){
    int n;
    if( P("verifydelete") ){
      /* Verified delete user request */
      db_unprotect(PROTECT_USER);
      if( alert_tables_exist() ){
        /* Also delete any subscriptions associated with this user */
        db_multi_exec("DELETE FROM subscriber WHERE suname="
                      "(SELECT login FROM user WHERE uid=%d)", uid);
      }
      db_multi_exec("DELETE FROM user WHERE uid=%d", uid);
      db_protect_pop();
      moderation_disapprove_for_missing_users();
      admin_log("Deleted user [%s] (uid %d).",
                PD("login","???")/*safe-for-%s*/, uid);
      cgi_redirect(cgi_referer("setup_ulist"));
      return;
    }
    n = db_int(0, "SELECT count(*) FROM event"
                  " WHERE user=%Q AND objid NOT IN private",
                  P("login"));
    if( n==0 ){
      zDeleteVerify = mprintf("Check this box and press \"Delete User\" again");
    }else{
      zDeleteVerify = mprintf(
        "User \"%s\" has %d or more artifacts in the block-chain. "
        "Delete anyhow?",
        P("login")/*safe-for-%s*/, n);
    }
  }

  style_set_current_feature("setup");

  /* If we have all the necessary information, write the new or
  ** modified user record.  After writing the user record, redirect
  ** to the page that displays a list of users.
  */
  if( !cgi_all("login","info","pw","apply") ){
    /* need all of the above properties to make a change.  Since one or
    ** more are missing, no-op */
  }else if( higherUser ){
    /* An Admin (a) user cannot edit a Superuser (s) */
  }else if( zDeleteVerify!=0 ){
    /* Need to verify a delete request */
  }else if( !cgi_csrf_safe(2) ){
    /* This might be a cross-site request forgery, so ignore it */
  }else{
    /* We have all the information we need to make the change to the user */
    char c;
    int bCapsChanged = 0 /* 1 if user's permissions changed */;
    const int bIsNew = uid<=0;
    char aCap[70], zNm[4];
    zNm[0] = 'a';
    zNm[2] = 0;
    for(i=0, c='a'; c<='z'; c++){
      zNm[1] = c;
      a[c&0x7f] = ((c!='s' && c!='y') || g.perm.Setup) && P(zNm)!=0;
      if( a[c&0x7f] ) aCap[i++] = c;
    }
    for(c='0'; c<='9'; c++){
      zNm[1] = c;
      a[c&0x7f] = P(zNm)!=0;
      if( a[c&0x7f] ) aCap[i++] = c;
    }
    for(c='A'; c<='Z'; c++){
      zNm[1] = c;
      a[c&0x7f] = P(zNm)!=0;
      if( a[c&0x7f] ) aCap[i++] = c;
    }

    aCap[i] = 0;
    bCapsChanged = bIsNew || userCapsChanged(zOldCaps, &aCap[0]);
    zPw = P("pw");
    zLogin = P("login");
    if( strlen(zLogin)==0 ){
      const char *zRef = cgi_referer("setup_ulist");
      style_header("User Creation Error");
      cgi_printf("<span class=\"loginError\">Empty login not allowed.</span>\n"
             "\n"
             "<p><a href=\"setup_uedit?id=%d&referer=%T\">\n"
             "[Bummer]</a></p>\n",(uid),(zRef));
      style_finish_page();
      return;
    }
    if( isValidPwString(zPw) ){
      zPw = sha1_shared_secret(zPw, zLogin, 0);
    }else{
      zPw = db_text(0, "SELECT pw FROM user WHERE uid=%d", uid);
    }
    zOldLogin = db_text(0, "SELECT login FROM user WHERE uid=%d", uid);
    if( db_exists("SELECT 1 FROM user WHERE login=%Q AND uid!=%d",zLogin,uid) ){
      const char *zRef = cgi_referer("setup_ulist");
      style_header("User Creation Error");
      cgi_printf("<span class=\"loginError\">Login \"%h\" is already used by\n"
             "a different user.</span>\n"
             "\n"
             "<p><a href=\"setup_uedit?id=%d&referer=%T\">\n"
             "[Bummer]</a></p>\n",(zLogin),(uid),(zRef));
      style_finish_page();
      return;
    }
    cgi_csrf_verify();
    db_unprotect(PROTECT_USER);
    uid = db_int(0,
                 "REPLACE INTO user(uid,login,info,pw,cap,mtime) "
                 "VALUES(nullif(%d,0),%Q,%Q,%Q,%Q,now()) "
                 "RETURNING uid",
                 uid, zLogin, P("info"), zPw, &aCap[0]);
    assert( uid>0 );
    if( zOldLogin && fossil_strcmp(zLogin, zOldLogin)!=0 ){
      if( alert_tables_exist() ){
        /* Rename matching subscriber entry, else the user cannot
           re-subscribe with their same email address. */
        db_multi_exec("UPDATE subscriber SET suname=%Q WHERE suname=%Q",
                      zLogin, zOldLogin);
      }
      admin_log( "Renamed user [%q] to [%q].", zOldLogin, zLogin );
    }
    db_protect_pop();
    setup_incr_cfgcnt();
    admin_log( "%s user [%q] with capabilities [%q].",
               bIsNew ? "Added" : "Updated",
               zLogin, &aCap[0] );
    if( atoi(PD("all","0"))>0 ){
      Blob sql;
      char *zErr = 0;
      blob_zero(&sql);
      if( zOldLogin==0 ){
        blob_appendf(&sql,
          "INSERT INTO user(login)"
          "  SELECT %Q WHERE NOT EXISTS(SELECT 1 FROM user WHERE login=%Q);",
          zLogin, zLogin
        );
        zOldLogin = zLogin;
      }
#if 0
      /* Problem: when renaming a user we need to update the subcriber
      ** names to match but we cannot know from here if each member of
      ** the login group has the subscriber tables, so we cannot blindly
      ** include this SQL. */
      else if( fossil_strcmp(zLogin, zOldLogin)!=0
               && alert_tables_exist() ){
        /* Rename matching subscriber entry, else the user cannot
           re-subscribe with their same email address. */
        blob_appendf(&sql,
                     "UPDATE subscriber SET suname=%Q WHERE suname=%Q;",
                     zLogin, zOldLogin);
      }
#endif
      blob_appendf(&sql,
        "UPDATE user SET login=%Q,"
        "  pw=coalesce(shared_secret(%Q,%Q,"
                "(SELECT value FROM config WHERE name='project-code')),pw),"
        "  info=%Q,"
        "  cap=%Q,"
        "  mtime=now()"
        " WHERE login=%Q;",
        zLogin, P("pw"), zLogin, P("info"), &aCap[0],
        zOldLogin
      );
      db_unprotect(PROTECT_USER);
      login_group_sql(blob_str(&sql), "<li> ", " </li>\n", &zErr);
      db_protect_pop();
      blob_reset(&sql);
      admin_log( "Updated user [%q] in all login groups "
                 "with capabilities [%q].",
                 zLogin, &aCap[0] );
      if( zErr ){
        const char *zRef = cgi_referer("setup_ulist");
        style_header("User Change Error");
        admin_log( "Error updating user '%q': %s'.", zLogin, zErr );
        cgi_printf("<span class=\"loginError\">%h</span>\n"
               "\n"
               "<p><a href=\"setup_uedit?id=%d&referer=%T\">\n"
               "[Bummer]</a></p>\n",(zErr),(uid),(zRef));
        style_finish_page();
        if( bCapsChanged ){
          /* It's possible that caps were updated locally even if
          ** login group updates failed. */
          alert_user_cap_change(zLogin, uid, bIsNew, zOldCaps, &aCap[0]);
        }
        return;
      }
    }
    if( bCapsChanged ){
      alert_user_cap_change(zLogin, uid, bIsNew, zOldCaps, &aCap[0]);
    }
    cgi_redirect(cgi_referer("setup_ulist"));
    return;
  }

  /* Load the existing information about the user, if any
  */
  zLogin = "";
  zInfo = "";
  zCap = zOldCaps;
  zPw = "";
  for(i='a'; i<='z'; i++) oa[i] = "";
  for(i='0'; i<='9'; i++) oa[i] = "";
  for(i='A'; i<='Z'; i++) oa[i] = "";
  if( uid ){
    assert( zCap );
    zLogin = db_text("", "SELECT login FROM user WHERE uid=%d", uid);
    zInfo = db_text("", "SELECT info FROM user WHERE uid=%d", uid);
    zPw = db_text("", "SELECT pw FROM user WHERE uid=%d", uid);
    for(i=0; zCap[i]; i++){
      char c = zCap[i];
      if( (c>='a' && c<='z') || (c>='0' && c<='9') || (c>='A' && c<='Z') ){
        oa[c&0x7f] = " checked=\"checked\"";
      }
    }
  }

  /* figure out inherited permissions */
  memset((char *)inherit, 0, sizeof(inherit));
  if( fossil_strcmp(zLogin, "developer") ){
    char *z1, *z2;
    z1 = z2 = db_text(0,"SELECT cap FROM user WHERE login='developer'");
    while( z1 && *z1 ){
      inherit[0x7f & *(z1++)] =
         "<span class=\"ueditInheritDeveloper\"><sub>[D]</sub></span>";
    }
    free(z2);
  }
  if( fossil_strcmp(zLogin, "reader") ){
    char *z1, *z2;
    z1 = z2 = db_text(0,"SELECT cap FROM user WHERE login='reader'");
    while( z1 && *z1 ){
      inherit[0x7f & *(z1++)] =
          "<span class=\"ueditInheritReader\"><sub>[R]</sub></span>";
    }
    free(z2);
  }
  if( fossil_strcmp(zLogin, "anonymous") ){
    char *z1, *z2;
    z1 = z2 = db_text(0,"SELECT cap FROM user WHERE login='anonymous'");
    while( z1 && *z1 ){
      inherit[0x7f & *(z1++)] =
           "<span class=\"ueditInheritAnonymous\"><sub>[A]</sub></span>";
    }
    free(z2);
  }
  if( fossil_strcmp(zLogin, "nobody") ){
    char *z1, *z2;
    z1 = z2 = db_text(0,"SELECT cap FROM user WHERE login='nobody'");
    while( z1 && *z1 ){
      inherit[0x7f & *(z1++)] =
           "<span class=\"ueditInheritNobody\"><sub>[N]</sub></span>";
    }
    free(z2);
  }

  /* Begin generating the page
  */
  style_submenu_element("Cancel", "%s", cgi_referer("setup_ulist"));
  if( uid ){
    style_header("Edit User %h", zLogin);
    if( !login_is_special(zLogin) ){
      style_submenu_element("Access Log", "%R/access_log?u=%t", zLogin);
      style_submenu_element("Timeline","%R/timeline?u=%t", zLogin);
    }
  }else{
    style_header("Add A New User");
  }
  cgi_printf("<div class=\"ueditCapBox\">\n"
         "<form action=\"%s\" method=\"post\"><div>\n",(g.zPath));
  login_insert_csrf_secret();
  if( login_is_special(zLogin) ){
    cgi_printf("<input type=\"hidden\" name=\"login\" value=\"%s\">\n"
           "<input type=\"hidden\" name=\"info\" value=\"\">\n"
           "<input type=\"hidden\" name=\"pw\" value=\"*\">\n",(zLogin));
  }
  cgi_printf("<input type=\"hidden\" name=\"referer\" value=\"%h\">\n"
         "<table width=\"100%%\">\n"
         "<tr>\n"
         "  <td class=\"usetupEditLabel\" id=\"suuid\">User ID:</td>\n",(cgi_referer("setup_ulist")));
  if( uid ){
    cgi_printf("  <td>%d <input aria-labelledby=\"suuid\" type=\"hidden\" "
           "  name=\"id\" value=\"%d\"/>"
           "</td>\n",(uid),(uid));
  }else{
    cgi_printf("  <td>(new user)<input aria-labelledby=\"suuid\" type=\"hidden\" name=\"id\" "
           "value=\"0\"></td>\n");
  }
  cgi_printf("</tr>\n"
         "<tr>\n"
         "  <td class=\"usetupEditLabel\" id=\"sulgn\">Login:</td>\n");
  if( login_is_special(zLogin) ){
    cgi_printf("   <td><b>%h</b></td>\n",(zLogin));
  }else{
    cgi_printf("  <td><input aria-labelledby=\"sulgn\" type=\"text\" name=\"login\" "
           "value=\"%h\">\n",(zLogin));
    if( alert_tables_exist() ){
      int sid;
      sid = db_int(0, "SELECT subscriberId FROM subscriber"
                      " WHERE suname=%Q", zLogin);
      if( sid>0 ){
        cgi_printf("&nbsp;&nbsp;<a href=\"%R/alerts?sid=%d\">"
               "(subscription info for %h)</a>",(sid),(zLogin));
      }
    }
    cgi_printf("</td></tr>\n"
           "<tr>\n"
           "  <td class=\"usetupEditLabel\" id=\"sucnfo\">Contact&nbsp;Info:</td>\n"
           "  <td><textarea aria-labelledby=\"sucnfo\" name=\"info\" cols=\"40\" "
           "rows=\"2\">%h</textarea></td>\n",(zInfo));
  }
  cgi_printf("</tr>\n"
         "<tr>\n"
         "  <td class=\"usetupEditLabel\">Capabilities:</td>\n"
         "  <td width=\"100%%\">\n");
#define B(x) inherit[x]
  cgi_printf("<div class=\"columns\" style=\"column-width:13em;\">\n"
         "<ul style=\"list-style-type: none;\">\n");
  if( g.perm.Setup ){
    cgi_printf(" <li><label><input type=\"checkbox\" name=\"as\"%s>\n"
           " Setup%s</label>\n",(oa['s']),(B('s')));
  }
  cgi_printf(" <li><label><input type=\"checkbox\" name=\"aa\"%s>\n"
         " Admin%s</label>\n"
         " <li><label><input type=\"checkbox\" name=\"au\"%s>\n"
         " Reader%s</label>\n"
         " <li><label><input type=\"checkbox\" name=\"av\"%s>\n"
         " Developer%s</label>\n",(oa['a']),(B('a')),(oa['u']),(B('u')),(oa['v']),(B('v')));
#if 0  /* Not Used */
  cgi_printf(" <li><label><input type=\"checkbox\" name=\"ad\"%s>\n"
         " Delete%s</label>\n",(oa['d']),(B('d')));
#endif
  cgi_printf(" <li><label><input type=\"checkbox\" name=\"ae\"%s>\n"
         " View-PII%s</label>\n"
         " <li><label><input type=\"checkbox\" name=\"ap\"%s>\n"
         " Password%s</label>\n"
         " <li><label><input type=\"checkbox\" name=\"ai\"%s>\n"
         " Check-In%s</label>\n"
         " <li><label><input type=\"checkbox\" name=\"ao\"%s>\n"
         " Check-Out%s</label>\n"
         " <li><label><input type=\"checkbox\" name=\"ah\"%s>\n"
         " Hyperlinks%s</label>\n"
         " <li><label><input type=\"checkbox\" name=\"ab\"%s>\n"
         " Attachments%s</label>\n"
         " <li><label><input type=\"checkbox\" name=\"ag\"%s>\n"
         " Clone%s</label>\n"
         " <li><label><input type=\"checkbox\" name=\"aj\"%s>\n"
         " Read Wiki%s</label>\n"
         " <li><label><input type=\"checkbox\" name=\"af\"%s>\n"
         " New Wiki%s</label>\n"
         " <li><label><input type=\"checkbox\" name=\"am\"%s>\n"
         " Append Wiki%s</label>\n"
         " <li><label><input type=\"checkbox\" name=\"ak\"%s>\n"
         " Write Wiki%s</label>\n"
         " <li><label><input type=\"checkbox\" name=\"al\"%s>\n"
         " Moderate Wiki%s</label>\n"
         " <li><label><input type=\"checkbox\" name=\"ar\"%s>\n"
         " Read Ticket%s</label>\n"
         " <li><label><input type=\"checkbox\" name=\"an\"%s>\n"
         " New Tickets%s</label>\n"
         " <li><label><input type=\"checkbox\" name=\"ac\"%s>\n"
         " Append To Ticket%s</label>\n"
         " <li><label><input type=\"checkbox\" name=\"aw\"%s>\n"
         " Write Tickets%s</label>\n"
         " <li><label><input type=\"checkbox\" name=\"aq\"%s>\n"
         " Moderate Tickets%s</label>\n"
         " <li><label><input type=\"checkbox\" name=\"at\"%s>\n"
         " Ticket Report%s</label>\n"
         " <li><label><input type=\"checkbox\" name=\"ax\"%s>\n"
         " Private%s</label>\n"
         " <li><label><input type=\"checkbox\" name=\"ay\"%s>\n"
         " Write Unversioned%s</label>\n"
         " <li><label><input type=\"checkbox\" name=\"az\"%s>\n"
         " Download Zip%s</label>\n"
         " <li><label><input type=\"checkbox\" name=\"a2\"%s>\n"
         " Read Forum%s</label>\n"
         " <li><label><input type=\"checkbox\" name=\"a3\"%s>\n"
         " Write Forum%s</label>\n"
         " <li><label><input type=\"checkbox\" name=\"a4\"%s>\n"
         " WriteTrusted Forum%s</label>\n"
         " <li><label><input type=\"checkbox\" name=\"a5\"%s>\n"
         " Moderate Forum%s</label>\n"
         " <li><label><input type=\"checkbox\" name=\"a6\"%s>\n"
         " Supervise Forum%s</label>\n"
         " <li><label><input type=\"checkbox\" name=\"a7\"%s>\n"
         " Email Alerts%s</label>\n"
         " <li><label><input type=\"checkbox\" name=\"aA\"%s>\n"
         " Send Announcements%s</label>\n"
         " <li><label><input type=\"checkbox\" name=\"aC\"%s>\n"
         " Chatroom%s</label>\n"
         " <li><label><input type=\"checkbox\" name=\"aD\"%s>\n"
         " Enable Debug%s</label>\n"
         "</ul></div>\n"
         "  </td>\n"
         "</tr>\n"
         "<tr>\n"
         "  <td class=\"usetupEditLabel\">Selected Cap:</td>\n"
         "  <td>\n"
         "    <span id=\"usetupEditCapability\">(missing JS?)</span>\n"
         "    <a href=\"%R/setup_ucap_list\">(key)</a>\n"
         "  </td>\n"
         "</tr>\n",(oa['e']),(B('e')),(oa['p']),(B('p')),(oa['i']),(B('i')),(oa['o']),(B('o')),(oa['h']),(B('h')),(oa['b']),(B('b')),(oa['g']),(B('g')),(oa['j']),(B('j')),(oa['f']),(B('f')),(oa['m']),(B('m')),(oa['k']),(B('k')),(oa['l']),(B('l')),(oa['r']),(B('r')),(oa['n']),(B('n')),(oa['c']),(B('c')),(oa['w']),(B('w')),(oa['q']),(B('q')),(oa['t']),(B('t')),(oa['x']),(B('x')),(oa['y']),(B('y')),(oa['z']),(B('z')),(oa['2']),(B('2')),(oa['3']),(B('3')),(oa['4']),(B('4')),(oa['5']),(B('5')),(oa['6']),(B('6')),(oa['7']),(B('7')),(oa['A']),(B('A')),(oa['C']),(B('C')),(oa['D']),(B('D')));
  if( !login_is_special(zLogin) ){
    cgi_printf("<tr>\n"
           "  <td align=\"right\" id=\"supw\">Password:</td>\n");
    if( zPw[0] ){
      /* Obscure the password for all users */
      cgi_printf("  <td><input aria-labelledby=\"supw\" type=\"password\" autocomplete=\"off\" "
             "  name=\"pw\" value=\"**********\">\n"
             "  (Leave unchanged to retain password)</td>\n");
    }else{
      /* Show an empty password as an empty input field */
      char *zRPW = fossil_random_password(12);
      cgi_printf("  <td><input aria-labelledby=\"supw\" type=\"password\" name=\"pw\" "
             "  autocomplete=\"off\" value=\"\"> Password suggestion: %z</td>\n",(zRPW));
    }
    cgi_printf("</tr>\n");
  }
  zGroup = login_group_name();
  if( zGroup ){
    cgi_printf("<tr>\n"
           "<td valign=\"top\" align=\"right\">Scope:</td>\n"
           "<td valign=\"top\">\n"
           "<input type=\"radio\" name=\"all\" checked value=\"0\">\n"
           "Apply changes to this repository only.<br>\n"
           "<input type=\"radio\" name=\"all\" value=\"1\">\n"
           "Apply changes to all repositories in the \"<b>%h</b>\"\n"
           "login group.</td></tr>\n",(zGroup));
  }
  if( !higherUser ){
    if( zDeleteVerify ){
      cgi_printf("<tr>\n"
             "  <td valign=\"top\" align=\"right\">Verify:</td>\n"
             "  <td><label><input type=\"checkbox\" name=\"verifydelete\">"
             "  Confirm Delete "
             "  <span class=\"loginError\">&larr; %h</span>\n"
             "  </label></td>\n"
             "<tr>\n",(zDeleteVerify));
    }
    cgi_printf("<tr>\n"
           "  <td>&nbsp;</td>\n"
           "  <td><input type=\"submit\" name=\"apply\" value=\"Apply Changes\">\n");
    if( !login_is_special(zLogin) ){
      cgi_printf("  <input type=\"submit\" name=\"delete\" value=\"Delete User\">\n");
    }
    cgi_printf("  <input type=\"submit\" name=\"can\" value=\"Cancel\"></td>\n"
           "</tr>\n");
  }
  cgi_printf("</table>\n"
         "</div></form>\n"
         "</div>\n");
  builtin_request_js("useredit.js");
  cgi_printf("<hr>\n"
         "<h1>Notes On Privileges And Capabilities:</h1>\n"
         "<ul>\n");
  if( higherUser ){
    cgi_printf("<li><p class=\"missingPriv\">\n"
           "User %h has Setup privileges and you only have Admin privileges\n"
           "so you are not permitted to make changes to %h.\n"
           "</p></li>\n"
           "\n",(zLogin),(zLogin));
  }
  cgi_printf("<li><p>\n"
         "The <span class=\"capability\">Setup</span> user can make arbitrary\n"
         "configuration changes. An <span class=\"usertype\">Admin</span> user\n"
         "can add other users and change user privileges\n"
         "and reset user passwords.  Both automatically get all other privileges\n"
         "listed below.  Use these two settings with discretion.\n"
         "</p></li>\n"
         "\n"
         "<li><p>\n"
         "The \"<span class=\"ueditInheritNobody\"><sub>N</sub></span>\" subscript suffix\n"
         "indicates the privileges of <span class=\"usertype\">nobody</span> that\n"
         "are available to all users regardless of whether or not they are logged in.\n"
         "</p></li>\n"
         "\n"
         "<li><p>\n"
         "The \"<span class=\"ueditInheritAnonymous\"><sub>A</sub></span>\"\n"
         "subscript suffix\n"
         "indicates the privileges of <span class=\"usertype\">anonymous</span> that\n"
         "are inherited by all logged-in users.\n"
         "</p></li>\n"
         "\n"
         "<li><p>\n"
         "The \"<span class=\"ueditInheritDeveloper\"><sub>D</sub></span>\"\n"
         "subscript suffix indicates the privileges of\n"
         "<span class=\"usertype\">developer</span> that\n"
         "are inherited by all users with the\n"
         "<span class=\"capability\">Developer</span> privilege.\n"
         "</p></li>\n"
         "\n"
         "<li><p>\n"
         "The \"<span class=\"ueditInheritReader\"><sub>R</sub></span>\" subscript suffix\n"
         "indicates the privileges of <span class=\"usertype\">reader</span> that\n"
         "are inherited by all users with the <span class=\"capability\">Reader</span>\n"
         "privilege.\n"
         "</p></li>\n"
         "\n"
         "<li><p>\n"
         "The <span class=\"capability\">Delete</span> privilege give the user the\n"
         "ability to erase wiki, tickets, and attachments that have been added\n"
         "by anonymous users.  This capability is intended for deletion of spam.\n"
         "The delete capability is only in effect for 24 hours after the item\n"
         "is first posted.  The <span class=\"usertype\">Setup</span> user can\n"
         "delete anything at any time.\n"
         "</p></li>\n"
         "\n"
         "<li><p>\n"
         "The <span class=\"capability\">Hyperlinks</span> privilege allows a user\n"
         "to see most hyperlinks. This is recommended ON for most logged-in users\n"
         "but OFF for user \"nobody\" to avoid problems with spiders trying to walk\n"
         "every diff and annotation of every historical check-in and file.\n"
         "</p></li>\n"
         "\n"
         "<li><p>\n"
         "The <span class=\"capability\">Zip</span> privilege allows a user to\n"
         "see the \"download as ZIP\"\n"
         "hyperlink and permits access to the <tt>/zip</tt> page.  This allows\n"
         "users to download ZIP archives without granting other rights like\n"
         "<span class=\"capability\">Read</span> or\n"
         "<span class=\"capability\">Hyperlink</span>.  The \"z\" privilege is recommended\n"
         "for user <span class=\"usertype\">nobody</span> so that automatic package\n"
         "downloaders can obtain the sources without going through the login\n"
         "procedure.\n"
         "</p></li>\n"
         "\n"
         "<li><p>\n"
         "The <span class=\"capability\">Check-in</span> privilege allows remote\n"
         "users to \"push\". The <span class=\"capability\">Check-out</span> privilege\n"
         "allows remote users to \"pull\". The <span class=\"capability\">Clone</span>\n"
         "privilege allows remote users to \"clone\".\n"
         "</p></li>\n"
         "\n"
         "<li><p>\n"
         "The <span class=\"capability\">Read Wiki</span>,\n"
         "<span class=\"capability\">New Wiki</span>,\n"
         "<span class=\"capability\">Append Wiki</span>, and\n"
         "<b>Write Wiki</b> privileges control access to wiki pages.  The\n"
         "<span class=\"capability\">Read Ticket</span>,\n"
         "<span class=\"capability\">New Ticket</span>,\n"
         "<span class=\"capability\">Append Ticket</span>, and\n"
         "<span class=\"capability\">Write Ticket</span> privileges control access\n"
         "to trouble tickets.\n"
         "The <span class=\"capability\">Ticket Report</span> privilege allows\n"
         "the user to create or edit ticket report formats.\n"
         "</p></li>\n"
         "\n"
         "<li><p>\n"
         "Users with the <span class=\"capability\">Password</span> privilege\n"
         "are allowed to change their own password.  Recommended ON for most\n"
         "users but OFF for special users <span class=\"usertype\">developer</span>,\n"
         "<span class=\"usertype\">anonymous</span>,\n"
         "and <span class=\"usertype\">nobody</span>.\n"
         "</p></li>\n"
         "\n"
         "<li><p>\n"
         "The <span class=\"capability\">View-PII</span> privilege allows the display\n"
         "of personally-identifiable information information such as the\n"
         "email address of users and contact\n"
         "information on tickets. Recommended OFF for\n"
         "<span class=\"usertype\">anonymous</span> and for\n"
         "<span class=\"usertype\">nobody</span> but ON for\n"
         "<span class=\"usertype\">developer</span>.\n"
         "</p></li>\n"
         "\n"
         "<li><p>\n"
         "The <span class=\"capability\">Attachment</span> privilege is needed in\n"
         "order to add attachments to tickets or wiki.  Write privilege on the\n"
         "ticket or wiki is also required.\n"
         "</p></li>\n"
         "\n"
         "<li><p>\n"
         "Login is prohibited if the password is an empty string.\n"
         "</p></li>\n"
         "</ul>\n"
         "\n"
         "<h2>Special Logins</h2>\n"
         "\n"
         "<ul>\n"
         "<li><p>\n"
         "No login is required for user <span class=\"usertype\">nobody</span>. The\n"
         "capabilities of the <span class=\"usertype\">nobody</span> user are\n"
         "inherited by all users, regardless of whether or not they are logged in.\n"
         "To disable universal access to the repository, make sure that the\n"
         "<span class=\"usertype\">nobody</span> user has no capabilities\n"
         "enabled. The password for <span class=\"usertype\">nobody</span> is ignored.\n"
         "</p></li>\n"
         "\n"
         "<li><p>\n"
         "Login is required for user <span class=\"usertype\">anonymous</span> but the\n"
         "password is displayed on the login screen beside the password entry box\n"
         "so anybody who can read should be able to login as anonymous.\n"
         "On the other hand, spiders and web-crawlers will typically not\n"
         "be able to login.  Set the capabilities of the\n"
         "<span class=\"usertype\">anonymous</span>\n"
         "user to things that you want any human to be able to do, but not any\n"
         "spider.  Every other logged-in user inherits the privileges of\n"
         "<span class=\"usertype\">anonymous</span>.\n"
         "</p></li>\n"
         "\n"
         "<li><p>\n"
         "The <span class=\"usertype\">developer</span> user is intended as a template\n"
         "for trusted users with check-in privileges. When adding new trusted users,\n"
         "simply select the <span class=\"capability\">developer</span> privilege to\n"
         "cause the new user to inherit all privileges of the\n"
         "<span class=\"usertype\">developer</span>\n"
         "user.  Similarly, the <span class=\"usertype\">reader</span> user is a\n"
         "template for users who are allowed more access than\n"
         "<span class=\"usertype\">anonymous</span>,\n"
         "but less than a <span class=\"usertype\">developer</span>.\n"
         "</p></li>\n"
         "</ul>\n");
  style_finish_page();
}

/*
** WEBPAGE: setup_uinfo
**
** Detailed information about a user account, available to administrators
** only.
**
**    u=UID
**    l=LOGIN
*/
void setup_uinfo_page(void){
  Stmt q;
  Blob sql;
  const char *zLogin;
  int uid;

  /* Must have ADMIN privileges to access this page
  */
  login_check_credentials();
  if( !g.perm.Admin ){ login_needed(0); return; }
  style_set_current_feature("setup");
  zLogin = P("l");
  uid = atoi(PD("u","0"));
  if( zLogin==0 && uid==0 ){
    uid = db_int(1,"SELECT uid FROM user");
  }
  blob_init(&sql, 0, 0);
  blob_append_sql(&sql,
    "SELECT "
       /*  0 */ "uid,"
       /*  1 */ "login,"
       /*  2 */ "cap,"
       /*  3 */ "cookie,"
       /*  4 */ "datetime(cexpire),"
       /*  5 */ "info,"
       /*  6 */ "datetime(user.mtime,'unixepoch'),"
  );
  if( db_table_exists("repository","subscriber") ){
    blob_append_sql(&sql,
      /*  7 */ "subscriberId,"
      /*  8 */ "semail,"
      /*  9 */ "sverified,"
      /* 10 */ "date(lastContact+2440587.5)"
      " FROM user LEFT JOIN subscriber ON suname=login"
    );
  }else{
    blob_append_sql(&sql,
      /*  7 */ "NULL,"
      /*  8 */ "NULL,"
      /*  9 */ "NULL,"
      /* 10 */ "NULL"
      " FROM user"
    );
  }
  if( zLogin!=0 ){
    blob_append_sql(&sql, " WHERE login=%Q", zLogin);
  }else{
    blob_append_sql(&sql, " WHERE uid=%d", uid);
  }
  db_prepare(&q, "%s", blob_sql_text(&sql));
  blob_zero(&sql);
  if( db_step(&q)!=SQLITE_ROW ){
    style_header("No Such User");
    if( zLogin ){
      cgi_printf("<p>Cannot find any information on user %h.\n",(zLogin));
    }else{
      cgi_printf("<p>Cannot find any information on userid %d.\n",(uid));
    }
    style_finish_page();
    db_finalize(&q);
    return;
  }
  style_header("User %h", db_column_text(&q,1));
  cgi_printf("<table class=\"label-value\">\n"
         "<tr><th>uid:</th><td>%d\n"
         " (<a href=\"%R/setup_uedit?id=%d\">edit</a>)</td></tr>\n"
         "<tr><th>login:</th><td>%h</td></tr>\n"
         "<tr><th>capabilities:</th><td>%h</td></tr>\n"
         "<tr><th valign=\"top\">info:</th>\n"
         "<td valign=\"top\"><span style='white-space:pre-line;'>"
         "%h</span></td></tr>\n"
         "<tr><th>user.mtime:</th><td>%h</td></tr>\n",(db_column_int(&q,0)),(db_column_int(&q,0)),(db_column_text(&q,1)),(db_column_text(&q,2)),(db_column_text(&q,5)),(db_column_text(&q,6)));
  if( db_column_type(&q,7)!=SQLITE_NULL ){
    cgi_printf("<tr><th>subscriberId:</th><td>%d\n"
           " (<a href=\"%R/alerts?sid=%d\">edit</a>)</td></tr>\n"
           "<tr><th>semail:</th><td>%h</td></tr>\n"
           "<tr><th>verified:</th><td>%s</td></th>\n"
           "<tr><th>lastContact:</th><td>%h</td></tr>\n",(db_column_int(&q,7)),(db_column_int(&q,7)),(db_column_text(&q,8)),(db_column_int(&q,9)?"yes":"no"),(db_column_text(&q,10)));
  }
  cgi_printf("</table>\n");
  db_finalize(&q);
  style_finish_page();
}
