#line 1 "C:\\source\\fossil_depot\\fossil\\Fossil\\src\\security_audit.c"
/*
** Copyright (c) 2017 D. Richard Hipp
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
** This file implements various web pages use for running a security audit
** of a Fossil configuration.
*/
#include "config.h"
#include <assert.h>
#include "security_audit.h"

/*
** Return TRUE if any of the capability letters in zTest are found
** in the capability string zCap.
*/
static int hasAnyCap(const char *zCap, const char *zTest){
  while( zTest[0] ){
    if( strchr(zCap, zTest[0]) ) return 1;
    zTest++;
  }
  return 0;
}

/*
** Parse the content-security-policy
** into separate fields, and return a pointer to a null-terminated
** array of pointers to strings, one entry for each field.  Or return
** a NULL pointer if no CSP could be located in the header.
**
** Memory to hold the returned array and of the strings is obtained from
** a single memory allocation, which the caller should free to avoid a
** memory leak.
*/
static char **parse_content_security_policy(void){
  char **azCSP = 0;
  int nCSP = 0;
  char *zAll;
  char *zCopy;
  int nAll = 0;
  int jj;
  int nSemi;

  zAll = style_csp(0);
  nAll = (int)strlen(zAll);
  for(jj=nSemi=0; jj<nAll; jj++){ if( zAll[jj]==';' ) nSemi++; }
  azCSP = fossil_malloc( nAll+1+(nSemi+2)*sizeof(char*) );
  zCopy = (char*)&azCSP[nSemi+2];
  memcpy(zCopy,zAll,nAll);
  zCopy[nAll] = 0;
  while( fossil_isspace(zCopy[0]) || zCopy[0]==';' ){ zCopy++; }
  azCSP[0] = zCopy;
  nCSP = 1;
  for(jj=0; zCopy[jj]; jj++){
    if( zCopy[jj]==';' ){
      int k;
      for(k=jj-1; k>0 && fossil_isspace(zCopy[k]); k--){ zCopy[k] = 0; }
      zCopy[jj] = 0;
      while( jj+1<nAll
         && (fossil_isspace(zCopy[jj+1]) || zCopy[jj+1]==';')
      ){
        jj++;
      }
      assert( nCSP<nSemi+1 );
      azCSP[nCSP++] = zCopy+jj;
    }
  }
  assert( nCSP<=nSemi+2 );
  azCSP[nCSP] = 0;
  fossil_free(zAll);
  return azCSP;
}

/*
** WEBPAGE: secaudit0
**
** Run a security audit of the current Fossil setup, looking
** for configuration problems that might allow unauthorized
** access to the repository.
**
** This page requires administrator access.  It is usually
** accessed using the Admin/Security-Audit menu option
** from any of the default skins.
*/
void secaudit0_page(void){
  const char *zAnonCap;      /* Capabilities of user "anonymous" and "nobody" */
  const char *zDevCap;       /* Capabilities of user group "developer" */
  const char *zReadCap;      /* Capabilities of user group "reader" */
  const char *zPubPages;     /* GLOB pattern for public pages */
  const char *zSelfCap;      /* Capabilities of self-registered users */
  int hasSelfReg = 0;        /* True if able to self-register */
  const char *zPublicUrl;    /* Canonical access URL */
  const char *zVulnReport;   /* The vuln-report setting */
  Blob cmd;
  char *z;
  int n, i;
  CapabilityString *pCap;
  char **azCSP;              /* Parsed content security policy */

  login_check_credentials();
  if( !g.perm.Admin ){
    login_needed(0);
    return;
  }
  style_header("Security Audit");
  cgi_printf("<ol>\n");

  /* Step 1:  Determine if the repository is public or private.  "Public"
  ** means that any anonymous user on the internet can access all content.
  ** "Private" repos require (non-anonymous) login to access all content,
  ** though some content may be accessible anonymously.
  */
  zAnonCap = db_text("", "SELECT fullcap(NULL)");
  zDevCap  = db_text("", "SELECT fullcap('v')");
  zReadCap = db_text("", "SELECT fullcap('u')");
  zPubPages = db_get("public-pages",0);
  hasSelfReg = db_get_boolean("self-register",0);
  pCap = capability_add(0, db_get("default-perms","u"));
  capability_expand(pCap);
  zSelfCap = capability_string(pCap);
  capability_free(pCap);
  if( hasAnyCap(zAnonCap,"as") ){
    cgi_printf("<li><p>This repository is <big><b>Wildly INSECURE</b></big> because\n"
           "it grants administrator privileges to anonymous users.  You\n"
           "should <a href=\"takeitprivate\">take this repository private</a>\n"
           "immediately!  Or, at least remove the Setup and Admin privileges\n"
           "for users \"anonymous\" and \"login\" on the\n"
           "<a href=\"setup_ulist\">User Configuration</a> page.\n");
  }else if( hasAnyCap(zSelfCap,"as") && hasSelfReg ){
    cgi_printf("<li><p>This repository is <big><b>Wildly INSECURE</b></big> because\n"
           "it grants administrator privileges to self-registered users.  You\n"
           "should <a href=\"takeitprivate\">take this repository private</a>\n"
           "and/or disable self-registration\n"
           "immediately!  Or, at least remove the Setup and Admin privileges\n"
           "from the default permissions for new users.\n");
  }else if( hasAnyCap(zAnonCap,"y") ){
    cgi_printf("<li><p>This repository is <big><b>INSECURE</b></big> because\n"
           "it allows anonymous users to push unversioned files.\n"
           "Fix this by <a href=\"takeitprivate\">taking the repository private</a>\n"
           "or by removing the \"y\" permission from users \"anonymous\" and\n"
           "\"nobody\" on the <a href=\"setup_ulist\">User Configuration</a> page.\n");
  }else if( hasAnyCap(zSelfCap,"y") ){
    cgi_printf("<li><p>This repository is <big><b>INSECURE</b></big> because\n"
           "it allows self-registered users to push unversioned files.\n"
           "Fix this by <a href=\"takeitprivate\">taking the repository private</a>\n"
           "or by removing the \"y\" permission from the default permissions or\n"
           "by disabling self-registration.\n");
  }else if( hasAnyCap(zAnonCap,"goz") ){
    cgi_printf("<li><p>This repository is <big><b>PUBLIC</b></big>. All\n"
           "checked-in content can be accessed by anonymous users.\n"
           "<a href=\"takeitprivate\">Take it private</a>.<p>\n");
  }else if( hasAnyCap(zSelfCap,"goz") && hasSelfReg ){
    cgi_printf("<li><p>This repository is <big><b>PUBLIC</b></big> because all\n"
           "checked-in content can be accessed by self-registered users.\n"
           "This repostory would be private if you disabled self-registration.</p>\n");
  }else if( !hasAnyCap(zAnonCap, "jrwy234567")
         && (!hasSelfReg || !hasAnyCap(zSelfCap, "jrwy234567"))
         && (zPubPages==0 || zPubPages[0]==0) ){
    cgi_printf("<li><p>This repository is <big><b>Completely PRIVATE</b></big>.\n"
           "A valid login and password is required to access any content.\n");
  }else{
    cgi_printf("<li><p>This repository is <big><b>Mostly PRIVATE</b></big>.\n"
           "A valid login and password is usually required, however some\n"
           "content can be accessed either anonymously or by self-registered\n"
           "users:\n"
           "<ul>\n");
    if( hasSelfReg ){
      if( hasAnyCap(zAnonCap,"j") || hasAnyCap(zSelfCap,"j") ){
        cgi_printf("<li> Wiki pages\n");
      }
      if( hasAnyCap(zAnonCap,"r") || hasAnyCap(zSelfCap,"r") ){
        cgi_printf("<li> Tickets\n");
      }
      if( hasAnyCap(zAnonCap,"234567") || hasAnyCap(zSelfCap,"234567") ){
        cgi_printf("<li> Forum posts\n");
      }
    }
    if( zPubPages && zPubPages[0] ){
      Glob *pGlob = glob_create(zPubPages);
      int i;
      cgi_printf("<li> \"Public Pages\" are URLs that match any of these GLOB patterns:\n"
             "<p><ul>\n");
      for(i=0; i<pGlob->nPattern; i++){
        cgi_printf("<li> %h\n",(pGlob->azPattern[i]));
      }
      cgi_printf("</ul>\n"
             "<p>Anoymous users are vested with capabilities \"%h\" on\n"
             "public pages. See the \"Public Pages\" entry in the\n"
             "\"User capability summary\" below.\n",(zSelfCap));
    }
    cgi_printf("</ul>\n");
    if( zPubPages && zPubPages[0] ){
      cgi_printf("<p>Change GLOB patterns exceptions using the \"Public pages\" setting\n"
             "on the <a href=\"setup_access\">Access Settings</a> page.</p>\n");
    }
  }

  zPublicUrl = public_url();
  if( zPublicUrl!=0 ){
    int nOther = db_int(0, "SELECT count(*) FROM config"
                           " WHERE name GLOB 'baseurl:*'"
                           " AND name<>'baseurl:%q'", zPublicUrl);
    cgi_printf("<li><p>The <a href=\"setup_config#eurl\">canonical URL</a> for this\n"
           "repository is <a href=\"%s\">%h</a>.\n",(zPublicUrl),(zPublicUrl));
    if( nOther==1 ){
      cgi_printf("This is also <a href=\"urllist?urlonly\">1 other URL</a> that has\n"
             "been used to access this repository.\n");
    }else if( nOther>=2 ){
      cgi_printf("There are also\n"
             "<a href=\"urllist?all&urlonly\">%d other URLs</a> that have\n"
             "been used to access this repository.\n",(nOther));
    }
  }else{
    int nUrl = db_int(0, "SELECT count(*) FROM config"
                         " WHERE name GLOB 'baseurl:*'");
    cgi_printf("<li><p>This repository does not have a\n"
           "<a href=\"setup_config#eurl\">canonical access URL</a>.\n");
    if( nUrl==1 ){
      cgi_printf("There is\n"
             "<a href=\"urllist?urlonly\">1 non-canonical URL</a>\n"
             "that has been used to access this repository.\n");
    }else if( nUrl>=2 ){
      cgi_printf("There are\n"
             "<a href=\"urllist?all&urlonly\">%d non-canonical URLs</a>\n"
             "that have been used to access this repository.\n",(nUrl));
    }
  }

  /* Make sure the HTTPS is required for login, at least, so that the
  ** password does not go across the Internet in the clear.
  */
  if( db_get_int("redirect-to-https",0)==0 ){
    cgi_printf("<li><p><b>WARNING:</b>\n"
           "Sensitive material such as login passwords can be sent over an\n"
           "unencrypted connection.\n"
           "Fix this by changing the \"Redirect to HTTPS\" setting on the\n"
           "<a href=\"setup_access\">Access Control</a> page. If you were using\n"
           "the old \"Redirect to HTTPS on Login Page\" setting, switch to the\n"
           "new setting: it has a more secure implementation.\n");
  }

#ifdef FOSSIL_ENABLE_TH1_DOCS
  /* The use of embedded TH1 is dangerous.  Warn if it is possible.
  */
  if( !Th_AreDocsEnabled() ){
    cgi_printf("<li><p>\n"
           "This server is compiled with -DFOSSIL_ENABLE_TH1_DOCS. TH1 docs\n"
           "are disabled for this particular repository, so you are safe for\n"
           "now.  However, to prevent future problems caused by accidentally\n"
           "enabling TH1 docs in the future, it is recommended that you\n"
           "recompile Fossil without the -DFOSSIL_ENABLE_TH1_DOCS flag.</p>\n");
  }else{
    cgi_printf("<li><p><b>DANGER:</b>\n"
           "This server is compiled with -DFOSSIL_ENABLE_TH1_DOCS and TH1 docs\n"
           "are enabled for this repository.  Anyone who can check-in or push\n"
           "to this repository can create a malicious TH1 script and then cause\n"
           "that script to be run on the server. This is a serious security concern.\n"
           "TH1 docs should only be enabled for repositories with a very limited\n"
           "number of trusted committers, and the repository should be monitored\n"
           "closely to ensure no hostile content sneaks in.  If a bad TH1 script\n"
           "does make it into the repository, the only want to prevent it from\n"
           "being run is to shun it.</p>\n"
           "\n"
           "<p>Disable TH1 docs by recompiling Fossil without the\n"
           "-DFOSSIL_ENABLE_TH1_DOCS flag, and/or clear the th1-docs setting\n"
           "and ensure that the TH1_ENABLE_DOCS environment variable does not\n"
           "exist in the environment.</p>\n");
  }
#endif

#if FOSSIL_ENABLE_TCL
  cgi_printf("<li><p>\n");
  if( db_get_boolean("tcl",0) ){
    #ifdef FOSSIL_ENABLE_TH1_DOCS
      if( Th_AreDocsEnabled() ){
        cgi_printf("<b>DANGER:</b>\n");
      }else{
        cgi_printf("<b>WARNING:</b>\n");
      }
    #else
      cgi_printf("<b>WARNING:</b>\n");
    #endif
    cgi_printf("This server is compiled with -DFOSSIL_ENABLE_TCL and Tcl integration\n"
           "is enabled for this repository.  Anyone who can execute malicious\n"
           "TH1 script on that server can also execute arbitrary Tcl script\n"
           "under the identity of the operating system process of that server.\n"
           "This is a serious security concern.</p>\n"
           "\n"
           "<p>Disable Tcl integration by recompiling Fossil without the\n"
           "-DFOSSIL_ENABLE_TCL flag, and/or clear the 'tcl' setting.</p>\n");
  }else{
    cgi_printf("This server is compiled with -DFOSSIL_ENABLE_TCL. Tcl integration\n"
           "is disabled for this particular repository, so you are safe for\n"
           "now.  However, to prevent potential problems caused by accidentally\n"
           "enabling Tcl integration in the future, it is recommended that you\n"
           "recompile Fossil without the -DFOSSIL_ENABLE_TCL flag.</p>\n");
  }
#endif

  /* Anonymous users should not be able to harvest email addresses
  ** from tickets.
  */
  if( hasAnyCap(zAnonCap, "e") ){
    cgi_printf("<li><p><b>WARNING:</b>\n"
           "Anonymous users can view email addresses and other personally\n"
           "identifiable information on tickets.\n"
           "Fix this by removing the \"Email\" privilege\n"
           "(<a href=\"setup_ucap_list\">capability \"e\"</a>) from users\n"
           "\"anonymous\" and \"nobody\" on the\n"
           "<a href=\"setup_ulist\">User Configuration</a> page.\n");
  }

  /* Anonymous users probably should not be allowed to push content
  ** to the repository.
  */
  if( hasAnyCap(zAnonCap, "i") ){
    cgi_printf("<li><p><b>WARNING:</b>\n"
           "Anonymous users can push new check-ins into the repository.\n"
           "Fix this by removing the \"Check-in\" privilege\n"
           "(<a href=\"setup_ucap_list\">capability</a> \"i\") from users\n"
           "\"anonymous\" and \"nobody\" on the\n"
           "<a href=\"setup_ulist\">User Configuration</a> page.\n");
  }

  /* Anonymous users probably should not be allowed act as moderators
  ** for wiki or tickets.
  */
  if( hasAnyCap(zAnonCap, "lq5") ){
    cgi_printf("<li><p><b>WARNING:</b>\n"
           "Anonymous users can act as moderators for wiki, tickets, or\n"
           "forum posts. This defeats the whole purpose of moderation.\n"
           "Fix this by removing the \"Mod-Wiki\", \"Mod-Tkt\", and \"Mod-Forum\"\n"
           "privileges (<a href=\"%R/setup_ucap_list\">capabilities</a> \"fq5\")\n"
           "from users \"anonymous\" and \"nobody\"\n"
           "on the <a href=\"setup_ulist\">User Configuration</a> page.\n");
  }

  /* Check to see if any TH1 scripts are configured to run on a sync
  */
  if( db_exists("SELECT 1 FROM config WHERE name GLOB 'xfer-*-script'"
                " AND length(value)>0") ){
    cgi_printf("<li><p><b>WARNING:</b>\n"
           "TH1 scripts might be configured to run on any sync, push, pull, or\n"
           "clone operation.  See the the <a href=\"%R/xfersetup\">/xfersetup</a>\n"
           "page for more information.  These TH1 scripts are a potential\n"
           "security concern and so should be carefully audited by a human.\n");
  }

  /* The strict-manifest-syntax setting should be on. */
  if( db_get_boolean("strict-manifest-syntax",1)==0 ){
    cgi_printf("<li><p><b>WARNING:</b>\n"
           "The \"strict-manifest-syntax\"  flag is off.  This is a security\n"
           "risk.  Turn this setting on (its default) to protect the users\n"
           "of this repository.\n");
  }

  zVulnReport = db_get("vuln-report","log");
  if( fossil_strcmp(zVulnReport,"block")!=0
   && fossil_strcmp(zVulnReport,"fatal")!=0
  ){
    cgi_printf("<li><p><b>WARNING:</b>\n"
           "The <a href=\"%R/help?cmd=vuln-report\">vuln-report setting</a>\n"
           "has a value of \"%h\". This disables defenses against\n"
           "XSS or SQL-injection vulnerabilities caused by coding errors in\n"
           "custom TH1 scripts.  For the best security, change\n"
           "the value of the vuln-report setting to \"block\" or \"fatal\".\n",(zVulnReport));
  }

  /* Obsolete:  */
  if( hasAnyCap(zAnonCap, "d") ||
      hasAnyCap(zDevCap,  "d") ||
      hasAnyCap(zReadCap, "d") ){
    cgi_printf("<li><p><b>WARNING:</b>\n"
           "One or more users has the <a\n"
           "href=\"https://fossil-scm.org/forum/forumpost/43c78f4bef\">obsolete</a>\n"
           "\"d\" capability. You should remove it using the\n"
           "<a href=\"setup_ulist\">User Configuration</a> page in case we\n"
           "ever reuse the letter for another purpose.\n");
  }

  /* If anonymous users are allowed to create new Wiki, then
  ** wiki moderation should be activated to pervent spam.
  */
  if( hasAnyCap(zAnonCap, "fk") ){
    if( db_get_boolean("modreq-wiki",0)==0 ){
      cgi_printf("<li><p><b>WARNING:</b>\n"
             "Anonymous users can create or edit wiki without moderation.\n"
             "This can result in robots inserting lots of wiki spam into\n"
             "repository.\n"
             "Fix this by removing the \"New-Wiki\" and \"Write-Wiki\"\n"
             "privileges from users \"anonymous\" and \"nobody\" on the\n"
             "<a href=\"setup_ulist\">User Configuration</a> page or\n"
             "by enabling wiki moderation on the\n"
             "<a href=\"setup_modreq\">Moderation Setup</a> page.\n");
    }else{
      cgi_printf("<li><p>\n"
             "Anonymous users can create or edit wiki, but moderator\n"
             "approval is required before the edits become permanent.\n");
    }
  }

  /* Anonymous users should not be able to create trusted forum
  ** posts.
  */
  if( hasAnyCap(zAnonCap, "456") ){
    cgi_printf("<li><p><b>WARNING:</b>\n"
           "Anonymous users can create forum posts that are\n"
           "accepted into the permanent record without moderation.\n"
           "This can result in robots generating spam on forum posts.\n"
           "Fix this by removing the \"WriteTrusted-Forum\" privilege\n"
           "(<a href=\"setup_ucap_list\">capabilities</a> \"456\") from\n"
           "users \"anonymous\" and \"nobody\" on the\n"
           "<a href=\"setup_ulist\">User Configuration</a> page or\n");
  }

  /* Anonymous users should not be able to send announcements.
  */
  if( hasAnyCap(zAnonCap, "A") ){
    cgi_printf("<li><p><b>WARNING:</b>\n"
           "Anonymous users can send announcements to anybody who is signed\n"
           "up to receive announcements.  This can result in spam.\n"
           "Fix this by removing the \"Announce\" privilege\n"
           "(<a href=\"setup_ucap_list\">capability</a> \"A\") from\n"
           "users \"anonymous\" and \"nobody\" on the\n"
           "<a href=\"setup_ulist\">User Configuration</a> page or\n");
  }

  /* Administrative privilege should only be provided to
  ** specific individuals, not to entire classes of people.
  ** And not too many people should have administrator privilege.
  */
  z = db_text(0,
    "SELECT group_concat("
                 "printf('<a href=''setup_uedit?id=%%d''>%%s</a>',uid,login),"
             "' and ')"
    " FROM user"
    " WHERE cap GLOB '*[as]*'"
    "   AND login in ('anonymous','nobody','reader','developer')"
  );
  if( z && z[0] ){
    cgi_printf("<li><p><b>WARNING:</b>\n"
           "Administrative privilege ('a' or 's')\n"
           "is granted to an entire class of users: %s.\n"
           "Administrative privilege should only be\n"
           "granted to specific individuals.\n",(z));
  }
  n = db_int(0,"SELECT count(*) FROM user WHERE fullcap(cap) GLOB '*[as]*'");
  if( n==0 ){
    cgi_printf("<li><p>\n"
           "No users have administrator privilege.\n");
  }else{
    z = db_text(0,
      "SELECT group_concat("
                 "printf('<a href=''setup_uedit?id=%%d''>%%s</a>',uid,login),"
             "', ')"
      " FROM user"
      " WHERE fullcap(cap) GLOB '*[as]*'"
    );
    cgi_printf("<li><p>\n"
           "Users with administrator privilege are: %s\n",(z));
    fossil_free(z);
    if( n>3 ){
      cgi_printf("<li><p><b>WARNING:</b>\n"
             "Administrator privilege is granted to\n"
             "<a href='setup_ulist?with=as'>%d users</a>.\n"
             "Ideally, administrator privilege ('s' or 'a') should only\n"
             "be granted to one or two users.\n",(n));
    }
  }

  /* The push-unversioned privilege should only be provided to
  ** specific individuals, not to entire classes of people.
  ** And no too many people should have this privilege.
  */
  z = db_text(0,
    "SELECT group_concat("
                 "printf('<a href=''setup_uedit?id=%%d''>%%s</a>',uid,login),"
             "' and ')"
    " FROM user"
    " WHERE cap GLOB '*y*'"
    "   AND login in ('anonymous','nobody','reader','developer')"
  );
  if( z && z[0] ){
    cgi_printf("<li><p><b>WARNING:</b>\n"
           "The \"Write-Unver\" privilege is granted to an entire class of users: %s.\n"
           "The Write-Unver privilege should only be granted to specific individuals.\n",(z));
    fossil_free(z);
  }
  n = db_int(0,"SELECT count(*) FROM user WHERE cap GLOB '*y*'");
  if( n>0 ){
    z = db_text(0,
       "SELECT group_concat("
          "printf('<a href=''setup_uedit?id=%%d''>%%s</a>',uid,login),', ')"
       " FROM user WHERE fullcap(cap) GLOB '*y*'"
    );
    cgi_printf("<li><p>\n"
           "Users with \"Write-Unver\" privilege: %s\n",(z));
    fossil_free(z);
    if( n>3 ){
      cgi_printf("<p><b>Caution:</b>\n"
             "The \"Write-Unver\" privilege ('y') is granted to an excessive\n"
             "number of users (%d).\n"
             "Ideally, the Write-Unver privilege should only\n"
             "be granted to one or two users.\n",(n));
    }
  }

  /* Providing hyperlink capability to user "nobody" can lead to robots
  ** making excessive requests resulting in DoS
  */
  if( db_exists("SELECT 1 FROM user WHERE login='nobody' AND cap GLOB '*h*'") ){
    int nobodyId = db_int(0,"SELECT uid FROM user WHERE login='nobody'");
    int anonId = db_int(0,
      "SELECT uid FROM user WHERE login='anonymous' AND cap NOT GLOB '*h*'");
    cgi_printf("<li><p>\n"
           "User \"nobody\" has \"Hyperlink\" privilege ('h') which can lead to\n"
           "robots walking a nearly endless progression of pages on public-facing\n"
           "repositories, causing excessive server load and possible DoS.\n"
           "Suggested remediation:\n"
           "<ol type=\"a\">\n"
           "<li>Remove the 'h' privilege from the\n"
           "    <a href=\"%R/setup_uedit?id=%d\">'nobody' user</a> so that\n"
           "    robots cannot see hyperlinks.\n"
           "<li>Activate <a href=\"%R/setup_robot\">autohyperlink</a> so that\n"
           "    human readers can still see hyperlinks even if they are not logged in.\n"
           "    Set the delay to at least 50 milliseconds and require a mouse\n"
           "    event for maximum robot defense.\n",(nobodyId));
    if( anonId>0 ){
      cgi_printf("<li>Perhaps set the 'h' privilege on the\n"
             "    <a href=\"%R/setup_uedit?id=%d\">'anonymous' user</a> so\n"
             "    that humans that have javascript disabled in their browsers can\n"
             "    still see hyperlinks if they will log in as \"anonymous\".\n",(anonId));
    }
    cgi_printf("</ol>\n");
  }

  /* Notify if REMOTE_USER or HTTP_AUTHENTICATION is used for login.
  */
  if( db_get_boolean("remote_user_ok", 0) ){
    cgi_printf("<li><p><b>Caution:</b>\n"
           "This repository trusts that the REMOTE_USER environment variable set\n"
           "up by the webserver contains the name of an authenticated user.\n"
           "Fossil's built-in authentication mechanism is bypassed.\n"
           "Fix this by deactivating the \"Allow REMOTE_USER authentication\"\n"
           "checkbox on the <a href=\"setup_access\">Access Control</a> page.\n");
  }
  if( db_get_boolean("http_authentication_ok", 0) ){
    cgi_printf("<li><p><b>Caution:</b>\n"
           "This repository trusts that the HTTP_AUTHENTICATION environment\n"
           "variable set up by the webserver contains the name of an\n"
           "authenticated user.\n"
           "Fossil's built-in authentication mechanism is bypassed.\n"
           "Fix this by deactivating the \"Allow HTTP_AUTHENTICATION authentication\"\n"
           "checkbox on the <a href=\"setup_access\">Access Control</a> page.\n");
  }

  /* Logging should be turned on
  */
  if( db_get_boolean("access-log",1)==0 ){
    cgi_printf("<li><p>\n"
           "The <a href=\"access_log\">User Log</a> is disabled.  The user log\n"
           "keeps a record of successful and unsuccessful login attempts and is\n"
           "useful for security monitoring.\n");
  }
  if( db_get_boolean("admin-log",1)==0 ){
    cgi_printf("<li><p>\n"
           "The <a href=\"admin_log\">Administrative Log</a> is disabled.\n"
           "The administrative log provides a record of configuration changes\n"
           "and is useful for security monitoring.\n");
  }

#if !defined(_WIN32) && !defined(FOSSIL_OMIT_LOAD_AVERAGE)
  /* Make sure that the load-average limiter is armed and working */
  if( load_average()==0.0 ){
    cgi_printf("<li><p>\n"
           "Unable to get the system load average.  This can prevent Fossil\n"
           "from throttling expensive operations during peak demand.\n"
           "If running in a chroot jail on Linux, verify that the /proc\n"
           "filesystem is mounted within the jail, so that the load average\n"
           "can be obtained from the /proc/loadavg file.\n");
  }else {
    double r = atof(db_get("max-loadavg", "0.0"));
    if( r<=0.0 ){
      cgi_printf("<li><p>\n"
             "Load average limiting is turned off.  This can cause the server\n"
             "to bog down if many requests for expensive services (such as\n"
             "large diffs or tarballs) arrive at about the same time.\n"
             "To fix this, set the\n"
             "<a href='%R/setup_access#slal'>\"Server Load Average Limit\"</a> on the\n"
             "<a href='%R/setup_access'>Access Control</a> page to the approximate\n"
             "the number of available cores on your server, or maybe just a little\n"
             "less.\n");
    }else if( r>=8.0 ){
      cgi_printf("<li><p>\n"
             "The <a href='%R/setup_access#slal'>\"Server Load Average Limit\"</a> on\n"
             "the <a href=\"setup_access\">Access Control</a> page is set to %g,\n"
             "which seems high.  Is this server really a %d-core machine?\n",(r),((int)r));
    }
  }
#endif

  if( g.zErrlog==0 || fossil_strcmp(g.zErrlog,"-")==0 ){
    cgi_printf("<li><p>\n"
           "The server error log is disabled.\n"
           "To set up an error log,\n");
    if( fossil_strcmp(g.zCmdName, "cgi")==0 ){
      cgi_printf("make an entry like \"errorlog: <i>FILENAME</i>\" in the\n"
             "CGI script at %h.\n",(P("SCRIPT_FILENAME")));
    }else{
      cgi_printf("add the \"--errorlog <i>FILENAME</i>\" option to the\n"
             "\"%h %h\" command that launched this server.\n",(g.argv[0]),(g.zCmdName));
    }
  }else{
    FILE *pTest = fossil_fopen(g.zErrlog,"a");
    if( pTest==0 ){
      cgi_printf("<li><p>\n"
             "<b>Error:</b>\n"
             "There is an error log at \"%h\" but that file is not\n"
             "writable and so no logging will occur.\n",(g.zErrlog));
    }else{
      fclose(pTest);
      cgi_printf("<li><p>\n"
             "The error log at \"<a href='%R/errorlog'>%h</a>\" is\n"
             "%,lld bytes in size.\n",(g.zErrlog),(file_size(g.zErrlog, ExtFILE)));
    }
  }

  if( g.zExtRoot ){
    int nFile;
    int nCgi;
    ext_files();
    nFile = db_int(0, "SELECT count(*) FROM sfile");
    nCgi = nFile==0 ? 0 : db_int(0,"SELECT count(*) FROM sfile WHERE isexe");
    cgi_printf("<li><p> CGI Extensions are enabled with a document root\n"
           "at <a href='%R/extfilelist'>%h</a> holding\n"
           "%d CGIs and %d static content and data files.\n",(g.zExtRoot),(nCgi),(nFile-nCgi));
  }

  if( fileedit_glob()!=0 ){
    cgi_printf("<li><p><a href='%R/fileedit'>Online File Editing</a> is enabled\n"
           "for this repository.  Clear the\n"
           "<a href='%R/setup_settings'>\"fileedit-glob\" setting</a> to\n"
           "disable online editing.</p>\n");
  }

  cgi_printf("<li><p> User capability summary:\n");
  capability_summary();


  azCSP = parse_content_security_policy();
  if( azCSP==0 ){
    cgi_printf("<li><p> WARNING: No Content Security Policy (CSP) is specified in the\n"
           "header. Though not required, a strong CSP is recommended. Fossil will\n"
           "automatically insert an appropriate CSP if you let it generate the\n"
           "HTML <tt>&lt;head&gt;</tt> element by omitting <tt>&lt;body&gt;</tt>\n"
           "from the header configuration in your customized skin.\n"
           "\n");
  }else{
    int ii;
    cgi_printf("<li><p> Content Security Policy:\n"
           "<ol type=\"a\">\n");
    for(ii=0; azCSP[ii]; ii++){
      cgi_printf("<li>%h\n",(azCSP[ii]));
    }
    cgi_printf("</ol>\n");
  }
  fossil_free(azCSP);

  if( alert_enabled() ){
    cgi_printf("<li><p> Email alert configuration summary:\n"
           "<table class=\"label-value\">\n");
    stats_for_email();
    cgi_printf("</table>\n");
  }else{
    cgi_printf("<li><p> Email alerts are disabled\n");
  }

  n = db_int(0,"SELECT count(*) FROM ("
               "SELECT rid FROM phantom EXCEPT SELECT rid FROM private)");
  if( n>0 ){
    cgi_printf("<li><p>"
           "There exists public phantom artifacts in this repository, shown below.\n"
           "Phantom artifacts are artifacts whose hash name is referenced by some\n"
           "other artifact but whose content is unknown.  Some phantoms are marked\n"
           "private and those are ignored.  But public phantoms cause unnecessary\n"
           "sync traffic and might represent malicious attempts to corrupt the\n"
           "repository structure.\n"
           "</p><p>\n"
           "To suppress unnecessary sync traffic caused by phantoms, add the RID\n"
           "of each phantom to the \"private\" table.  Example:\n"
           "<blockquote><pre>\n"
           "   INSERT INTO private SELECT rid FROM blob WHERE content IS NULL;\n"
           "</pre></blockquote>\n"
           "</p>\n");
    table_of_public_phantoms();
    cgi_printf("</li>\n");
  }

  cgi_printf("<li><p>Robot Defenses:\n"
         "<ol type=\"a\">\n");
  switch( db_get_int("auto-hyperlink",1) ){
    default:
       cgi_printf("<li> No auto-enable of hyperlinks.\n");
       break;
    case 1:
       cgi_printf("<li> Hyperlinks auto-enabled based on UserAgent and Javascript.\n");
       break;
    case 2:
       cgi_printf("<li> Hyperlinks auto-enabled based on UserAgent only.\n");
       break;
  }
  z = db_get("max-loadavg",0);
  if( z && atof(z)>0.0 ){
    cgi_printf("<li> Maximum load average for expensive requests: %h;\n",(z));
  }else{
    cgi_printf("<li> No limits on the load average\n");
  }
  z = db_get("robot-restrict",0);
  if( z==0 ){
    cgi_printf("<li> No complex-request constraints on robots\n");
  }else{
    cgi_printf("<li> Complex requests limited for pages matching: %h\n",(z));
  }
  cgi_printf("</ol>\n");

  blob_init(&cmd, 0, 0);
  for(i=0; g.argvOrig[i]!=0; i++){
    blob_append_escaped_arg(&cmd, g.argvOrig[i], 0);
  }
  cgi_printf("<li><p>\n");
  if( g.zCgiFile ){
    Blob fullname;
    blob_init(&fullname, 0, 0);
    file_canonical_name(g.zCgiFile, &fullname, 0);
    cgi_printf("The CGI control file for this page is \"%h\".\n",(blob_str(&fullname)));
  }
  cgi_printf("The command that generated this page:\n"
         "<blockquote>\n"
         "<tt>%h</tt>\n"
         "</blockquote></li>\n",(blob_str(&cmd)));
  blob_zero(&cmd);

  cgi_printf("</ol>\n");
  style_finish_page();
}

/*
** WEBPAGE: takeitprivate
**
** Disable anonymous access to this website
*/
void takeitprivate_page(void){
  login_check_credentials();
  if( !g.perm.Admin ){
    login_needed(0);
    return;
  }
  if( P("cancel") ){
    /* User pressed the cancel button.  Go back */
    cgi_redirect("secaudit0");
  }
  if( P("apply") ){
    db_unprotect(PROTECT_ALL);
    db_multi_exec(
      "UPDATE user SET cap=''"
      " WHERE login IN ('nobody','anonymous');"
      "DELETE FROM config WHERE name='public-pages';"
    );
    db_set("self-register","0",0);
    db_protect_pop();
    cgi_redirect("secaudit0");
  }
  style_header("Make This Website Private");
  cgi_printf("<p>Click the \"Make It Private\" button below to disable all\n"
         "anonymous access to this repository.  A valid login and password\n"
         "will be required to access this repository after clicking that\n"
         "button.</p>\n"
         "\n"
         "<p>Click the \"Cancel\" button to leave things as they are.</p>\n"
         "\n"
         "<form action=\"%s\" method=\"post\">\n"
         "<input type=\"submit\" name=\"apply\" value=\"Make It Private\">\n"
         "<input type=\"submit\" name=\"cancel\" value=\"Cancel\">\n"
         "</form>\n",(g.zPath));

  style_finish_page();
}

/*
** Output a message explaining that no error log is available.
*/
static void no_error_log_available(void){
  cgi_printf("<p>No error log is configured.\n");
  if( g.zCgiFile==0 ){
    cgi_printf("To create an error log, add the \"--errorlog FILENAME\"\n"
           "command-line option to the command that launches the Fossil server.\n");
  }else{
    Blob fullname;
    blob_init(&fullname, 0, 0);
    file_canonical_name(g.zCgiFile, &fullname, 0);
    cgi_printf("To create an error log, edit the CGI control file\n"
           "named \"%h\" to add a line like this:\n"
           "<blockquote><pre>\n"
           "errorlog: <i>FILENAME</i>\n"
           "</pre></blockquote>\n",(blob_str(&fullname)));
    blob_reset(&fullname);
  }
}

/*
** WEBPAGE: errorlog
**
** Show the content of the error log.  Only the administrator can view
** this page.
**
**    y=0x001          Show only hack attempts
**    y=0x002          Show only panics and assertion faults
**    y=0x004          Show hung backoffice processes
**    y=0x008          Show POST requests from a different origin
**    y=0x010          Show SQLITE_AUTH and similar
**    y=0x020          Show SMTP error reports
**    y=0x040          Show TH1 vulnerability reports
**    y=0x080          Show SQL errors
**    y=0x800          Show other uncategorized messages
**
** If y is omitted or is zero, a count of the various message types is
** shown.
*/
void errorlog_page(void){
  i64 szFile;
  FILE *in;
  char *zLog;
  const char *zType = P("y");
  static const int eAllTypes = 0x8ff;
  long eType = 0;
  int bOutput = 0;
  int prevWasTime = 0;
  int nHack = 0;
  int nPanic = 0;
  int nOther = 0;
  int nHang = 0;
  int nXPost = 0;
  int nAuth = 0;
  int nSmtp = 0;
  int nVuln = 0;
  int nSqlErr = 0;
  char z[10000];
  char zTime[10000];

  login_check_credentials();
  if( !g.perm.Admin ){
    login_needed(0);
    return;
  }
  if( zType ){
    eType = strtol(zType,0,0) & eAllTypes;
  }
  style_header("Server Error Log");
  style_submenu_element("Test", "%R/test-warning");
  style_submenu_element("Refresh", "%R/errorlog");
  style_submenu_element("Download", "%R/errorlog?download");
  style_submenu_element("Truncate", "%R/errorlog?truncate");
  style_submenu_element("Log-Menu", "%R/setup-logmenu");
  if( eType ){
    style_submenu_element("Summary", "%R/errorlog");
  }

  if( g.zErrlog==0 || fossil_strcmp(g.zErrlog,"-")==0 ){
    no_error_log_available();
    style_finish_page();
    return;
  }
  if( P("truncate1") && cgi_csrf_safe(2) ){
    fclose(fopen(g.zErrlog,"w"));
  }
  if( P("download") ){
    Blob log;
    blob_read_from_file(&log, g.zErrlog, ExtFILE);
    cgi_set_content_type("text/plain");
    cgi_set_content(&log);
    return;
  }
  szFile = file_size(g.zErrlog, ExtFILE);
  if( P("truncate") ){
    cgi_printf("<form action=\"%R/errorlog\" method=\"POST\">\n");
    login_insert_csrf_secret();
    cgi_printf("<p>Confirm that you want to truncate the %,lld-byte error log:\n"
           "<input type=\"submit\" name=\"truncate1\" value=\"Confirm\">\n"
           "<input type=\"submit\" name=\"cancel\" value=\"Cancel\">\n"
           "</form>\n",(szFile));
    style_finish_page();
    return;
  }
  zLog = file_canonical_name_dup(g.zErrlog);
  cgi_printf("<p>The server error log at \"%h\" is %,lld bytes in size.\n",(zLog),(szFile));
  fossil_free(zLog);
  in = fossil_fopen(g.zErrlog, "rb");
  if( in==0 ){
    cgi_printf("<p class='generalError'>Unable to open that file for reading!</p>\n");
    style_finish_page();
    return;
  }
  if( eType==0 ){
    /* will do a summary */
  }else if( (eType&eAllTypes)!=eAllTypes ){
    cgi_printf("Only the following types of messages displayed:\n"
           "<ul>\n");
    if( eType & 0x01 ){
      cgi_printf("<li>Hack attempts\n");
    }
    if( eType & 0x02 ){
      cgi_printf("<li>Panics and assertion faults\n");
    }
    if( eType & 0x04 ){
      cgi_printf("<li>Hung backoffice processes\n");
    }
    if( eType & 0x08 ){
      cgi_printf("<li>POST requests from different origin\n");
    }
    if( eType & 0x10 ){
      cgi_printf("<li>SQLITE_AUTH and similar errors\n");
    }
    if( eType & 0x20 ){
      cgi_printf("<li>SMTP malfunctions\n");
    }
    if( eType & 0x40 ){
      cgi_printf("<li>TH1 vulnerabilities\n");
    }
    if( eType & 0x80 ){
      cgi_printf("<li>SQL errors\n");
    }
    if( eType & 0x800 ){
      cgi_printf("<li>Other uncategorized messages\n");
    }
    cgi_printf("</ul>\n");
  }
  cgi_printf("<hr>\n");
  if( eType ){
    cgi_printf("<pre>\n");
  }
  while( fgets(z, sizeof(z), in) ){
    if( prevWasTime ){
      if( strncmp(z,"possible hack attempt - 418 ", 27)==0 ){
        bOutput = (eType & 0x01)!=0;
        nHack++;
      }else
      if( (strncmp(z,"panic: ", 7)==0 && strncmp(z+7,"Timeout",7)!=0)
       || strstr(z," assertion fault ")!=0
      ){
        bOutput = (eType & 0x02)!=0;
        nPanic++;
      }else
      if( strncmp(z,"SMTP:", 5)==0 ){
        bOutput = (eType & 0x20)!=0;
        nSmtp++;
      }else
      if( sqlite3_strglob("warning: backoffice process * still *",z)==0 ){
        bOutput = (eType & 0x04)!=0;
        nHang++;
      }else
      if( sqlite3_strglob("warning: POST from different origin*",z)==0 ){
        bOutput = (eType & 0x08)!=0;
        nXPost++;
      }else
      if( sqlite3_strglob("SECURITY: authorizer blocks*",z)==0
       || sqlite3_strglob("warning: SQLITE_AUTH*",z)==0
      ){
        bOutput = (eType & 0x10)!=0;
        nAuth++;
      }else
      if( strncmp(z,"possible", 8)==0 && strstr(z,"tainted")!=0 ){
        bOutput = (eType & 0x40)!=0;
        nVuln++;
      }else
      if( strstr(z,"statement aborts at ") ){
        bOutput = (eType & 0x80)!=0;
        nSqlErr++;
      }else
      {
        bOutput = (eType & 0x800)!=0;
        nOther++;
      }
      if( bOutput ){
        cgi_printf("%h",(zTime));
      }
    }
    if( strncmp(z, "--------", 8)==0 ){
      size_t n = strlen(z);
      memcpy(zTime, z, n+1);
      prevWasTime = 1;
      bOutput = 0;
    }else{
      prevWasTime = 0;
    }
    if( bOutput && eType ){
      cgi_printf("%h",(z));
    }
  }
  fclose(in);
  if( eType ){
    cgi_printf("</pre>\n");
  }
  if( eType==0 ){
    int nNonHack = nPanic + nHang + nAuth + nSmtp + nVuln + nOther + nSqlErr;
    int nTotal = nNonHack + nHack + nXPost;
    cgi_printf("<p><table border=\"a\" cellspacing=\"0\" cellpadding=\"5\">\n");
    if( nPanic>0 ){
      cgi_printf("<tr><td align=\"right\">%d</td>\n"
             "    <td><a href=\"./errorlog?y=2\">Panics</a></td>\n",(nPanic));
    }
    if( nVuln>0 ){
      cgi_printf("<tr><td align=\"right\">%d</td>\n"
             "    <td><a href=\"./errorlog?y=64\">TH1 Vulnerabilities</a></td>\n",(nVuln));
    }
    if( nHack>0 ){
      cgi_printf("<tr><td align=\"right\">%d</td>\n"
             "    <td><a href=\"./errorlog?y=1\">Hack Attempts</a></td>\n",(nHack));
    }
    if( nSqlErr>0 ){
      cgi_printf("<tr><td align=\"right\">%d</td>\n"
             "    <td><a href=\"./errorlog?y=128\">SQL Errors</a></td>\n",(nSqlErr));
    }
    if( nHang>0 ){
      cgi_printf("<tr><td align=\"right\">%d</td>\n"
             "    <td><a href=\"./errorlog?y=4\">Hung Backoffice</a></td>\n",(nHang));
    }
    if( nXPost>0 ){
      cgi_printf("<tr><td align=\"right\">%d</td>\n"
             "    <td><a href=\"./errorlog?y=8\">POSTs from different origin</a></td>\n",(nXPost));
    }
    if( nAuth>0 ){
      cgi_printf("<tr><td align=\"right\">%d</td>\n"
             "    <td><a href=\"./errorlog?y=16\">SQLITE_AUTH and similar</a></td>\n",(nAuth));
    }
    if( nSmtp>0 ){
      cgi_printf("<tr><td align=\"right\">%d</td>\n"
             "    <td><a href=\"./errorlog?y=32\">SMTP faults</a></td>\n",(nSmtp));
    }
    if( nOther>0 ){
      cgi_printf("<tr><td align=\"right\">%d</td>\n"
             "    <td><a href=\"./errorlog?y=2048\">Other</a></td>\n",(nOther));
    }
    cgi_printf("<tr><td align=\"right\">%d</td>\n",(nTotal));
    if( nTotal>0 ){
      cgi_printf("    <td><a href=\"./errorlog?y=4095\">All Messages</a></td>\n");
    }else{
      cgi_printf("    <td>All Messages</td>\n");
    }
    cgi_printf("</table>\n");
  }
  style_finish_page();
}
