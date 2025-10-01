#line 1 "C:\\source\\fossil_depot\\fossil\\Fossil\\src\\sitemap.c"
/*
** Copyright (c) 2014 D. Richard Hipp
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
** This file contains code to implement the sitemap webpage.
*/
#include "config.h"
#include "sitemap.h"
#include <assert.h>

/*
** WEBPAGE: sitemap
**
** List some of the web pages offered by the Fossil web engine.  This
** page is intended as a supplement to the menu bar on the main screen.
** That is, this page is designed to hold links that are omitted from
** the main menu due to lack of space.
**
** Additional entries defined by the "sitemap-extra" setting are included
** in the sitemap.  "sitemap-extra" should be a TCL script with three
** values per entry:
**
**    *    The displayed text
**
**    *    The URL
**
**    *    A "capexpr" expression that determines whether or not to include
**         the entry based on user capabilities.  "*" means always include
**         the entry and "{}" means never.
**
** If the "e=1" query parameter is present, then the standard content
** is omitted and only the sitemap-extra content is shown.  If "e=2" is
** present, then only the standard content is shown and sitemap-extra
** content is omitted.
**
** If the "popup" query parameter is present and this is a POST request
** from the same origin, then the normal HTML header and footer information
** is omitted and the HTML text returned is just a raw "<ul>...</ul>".
*/
void sitemap_page(void){
  int srchFlags;
  int inSublist = 0;
  int i;
  int isPopup = 0;         /* This is an XMLHttpRequest() for /sitemap */
  int e = atoi(PD("e","0"));
  const char *zExtra;

  login_check_credentials();
  if( P("popup")!=0 ){
    /* The "popup" query parameter
    ** then disable anti-robot defenses */
    isPopup = 1;
    g.perm.Hyperlink = 1;
    g.jsHref = 0;
  }
  srchFlags = search_restrict(SRCH_ALL);
  if( !isPopup ){
    style_header("Site Map");
    style_adunit_config(ADUNIT_RIGHT_OK);
  }

  cgi_printf("<ul id=\"sitemap\" class=\"columns\" style=\"column-width:20em\">\n");
  if( (e&1)==0 ){
    cgi_printf("<li>%zHome Page</a>\n",(href("%R/home")));
  }

  zExtra = db_get("sitemap-extra",0);
  if( zExtra && (e&2)==0 ){
    int rc;
    char **azExtra = 0;
    int *anExtra;
    int nExtra = 0;
    if( isPopup ) Th_FossilInit(0);
    if( (e&1)!=0 ) inSublist = 1;
    rc = Th_SplitList(g.interp, zExtra, (int)strlen(zExtra),
                      &azExtra, &anExtra, &nExtra);
    if( rc==TH_OK && nExtra ){
      for(i=0; i+2<nExtra; i+=3){
        int nResult = 0;
        const char *zResult;
        int iCond = 0;
        rc = capexprCmd(g.interp, 0, 2,
                (const char**)&azExtra[i+1], (int*)&anExtra[i+1]);
        if( rc!=TH_OK ) continue;
        zResult = Th_GetResult(g.interp, &nResult);
        Th_ToInt(g.interp, zResult, nResult, &iCond);
        if( iCond==0 ) continue;
        if( !inSublist ){
          cgi_printf("<ul>\n");
          inSublist = 1;
        }
        if( azExtra[i+1][0]=='/' ){
          cgi_printf("<li>%z%h</a></li>\n",(href("%R%s",azExtra[i+1])),(azExtra[i]));
        }else{
          cgi_printf("<li>%z%s</a></li>\n",(href("%s",azExtra[i+1])),(azExtra[i]));
        }
      }
    }
    Th_Free(g.interp, azExtra);
  }
  if( (e&1)!=0 ) goto end_of_sitemap;

  if( inSublist ){
    cgi_printf("</ul>\n");
    inSublist = 0;
  }
  cgi_printf("</li>\n");
  if( cgi_is_loopback(g.zIpAddr) && db_open_local(0) ){
    cgi_printf("<li>%zCheckout Status</a></li>\n",(href("%R/ckout")));
  }
  if( g.perm.Read ){
    const char *zEditGlob = db_get("fileedit-glob","");
    cgi_printf("<li>%zFile Browser</a>\n"
           "  <ul>\n"
           "  <li>%zTree-view,\n"
           "       Trunk Check-in</a></li>\n"
           "  <li>%zFlat-view</a></li>\n"
           "  <li>%zFile ages for Trunk</a></li>\n"
           "  <li>%zUnversioned Files</a>\n",(href("%R/tree")),(href("%R/tree?type=tree&ci=trunk")),(href("%R/tree?type=flat")),(href("%R/fileage?name=trunk")),(href("%R/uvlist")));
    if( g.perm.Write && zEditGlob[0]!=0 ){
      cgi_printf("  <li>%zOn-line File Editor</li>\n",(href("%R/fileedit")));
    }
    cgi_printf("</ul>\n");
  }
  if( g.perm.Read ){
    cgi_printf("<li>%zProject Timeline</a>\n"
           "<ul>\n"
           "  <li>%zActivity Reports</a></li>\n"
           "  <li>%zOther timelines</a></li>\n"
           "</ul>\n"
           "</li>\n",(href("%R/timeline")),(href("%R/reports")),(href("%R/sitemap-timeline")));
  }
  if( g.perm.Read ){
    cgi_printf("<li>%zBranches</a>\n"
           "<ul>\n"
           "  <li>%zTags</a></li>\n"
           "  <li>%zLeaf Check-ins</a></li>\n"
           "</ul>\n"
           "</li>\n",(href("%R/brlist")),(href("%R/taglist")),(href("%R/leaves")));
  }
  if( srchFlags ){
    cgi_printf("<li>%zSearch</a></li>\n",(href("%R/search")));
  }
  if( g.perm.Chat ){
    cgi_printf("<li>%zChat</a></li>\n",(href("%R/chat")));
  }
  if( g.perm.RdForum ){
    const char *zTitle = db_get("forum-title","Forum");
    cgi_printf("<li>%z%h</a>\n"
           "<ul>\n"
           "  <li>%zRecent activity</a></li>\n"
           "</ul>\n"
           "</li>\n",(href("%R/forum")),(zTitle),(href("%R/timeline?y=f")));
  }
  if( g.perm.RdTkt ){
    cgi_printf("<li>%zTickets/Bug Reports</a>\n"
           "  <ul>\n",(href("%R/reportlist")));
    if( srchFlags & SRCH_TKT ){
      cgi_printf("  <li>%zTicket Search</a></li>\n",(href("%R/tktsrch")));
    }
    cgi_printf("  <li>%zRecent activity</a></li>\n"
           "  <li>%zList of Attachments</a></li>\n"
           "  </ul>\n"
           "</li>\n",(href("%R/timeline?y=t")),(href("%R/attachlist")));
  }
  if( g.perm.RdWiki ){
    cgi_printf("<li>%zWiki</a>\n"
           "  <ul>\n",(href("%R/wikihelp")));
    if( srchFlags & SRCH_WIKI ){
      cgi_printf("    <li>%zWiki Search</a></li>\n",(href("%R/wikisrch")));
    }
    cgi_printf("    <li>%zList of Wiki Pages</a></li>\n"
           "    <li>%zRecent activity</a></li>\n"
           "    <li>%zWiki Sandbox</a></li>\n"
           "    <li>%zList of Attachments</a></li>\n"
           "    <li>%zPikchr Sandbox</a></li>\n"
           "  </ul>\n"
           "</li>\n",(href("%R/wcontent")),(href("%R/timeline?y=w")),(href("%R/wikiedit?name=Sandbox")),(href("%R/attachlist")),(href("%R/pikchrshow")));
  }

  if( !g.zLogin ){
    cgi_printf("<li>%zLogin</a>\n"
           "<ul>\n",(href("%R/login")));
    if( login_self_register_available(0) ){
       cgi_printf("<li>%zCreate a new account</a></li>\n",(href("%R/register")));
    }
  }else {
    cgi_printf("<li>%zLogout from %h</a>\n"
           "<ul>\n",(href("%R/logout")),(g.zLogin));
    if( g.perm.Password ){
      cgi_printf("<li>%zChange Password for %h</a></li>\n",(href("%R/logout")),(g.zLogin));
    }
  }
  if( alert_enabled() && g.perm.EmailAlert ){
    if( login_is_individual() ){
      cgi_printf("<li>%zEmail Alerts for %h</a></li>\n",(href("%R/alerts")),(g.zLogin));
    }else{
      cgi_printf("<li>%zSubscribe to Email Alerts</a></li>\n",(href("%R/subscribe")));
    }
  }
  cgi_printf("<li>%zCookies</a></li>\n"
         "</ul>\n"
         "</li>\n",(href("%R/cookies")));

  if( g.perm.Read ){
    cgi_printf("<li>%zRepository Status</a>\n"
           "  <ul>\n"
           "  <li>%zCollisions on hash prefixes</a></li>\n",(href("%R/stat")),(href("%R/hash-collisions")));
    if( g.perm.Admin ){
      cgi_printf("  <li>%zList of URLs used to access\n"
             "      this repository</a></li>\n",(href("%R/urllist")));
    }
    cgi_printf("  <li>%zList of Artifacts</a></li>\n"
           "  </ul>\n"
           "</li>\n",(href("%R/bloblist")));
  }
  cgi_printf("<li>%zHelp</a>\n"
         "  <ul>\n",(href("%R/help")));
  if( g.perm.Admin || g.perm.Write ||
      g.perm.WrForum || g.perm.WrTForum ||
      g.perm.NewWiki || g.perm.ApndWiki || g.perm.WrWiki || g.perm.ModWiki ||
      g.perm.NewTkt  || g.perm.ApndTkt  || g.perm.WrTkt  || g.perm.ModTkt ){
    cgi_printf("  <li>%zWiki Formatting Rules</a></li>\n"
           "  <li>%zMarkdown Formatting Rules</a></li>\n",(href("%R/wiki_rules")),(href("%R/md_rules")));
  }
  cgi_printf("  <li>%zAll \"help\" text on a single page</a></li>\n",(href("%R/test-all-help")));
  if( g.perm.Admin || g.perm.Write || g.perm.WrUnver ){
    cgi_printf("  <li>%z"
           "Filename suffix to MIME type map</a></li>\n",(href("%R/mimetype_list")));
  }
  cgi_printf("  </ul></li>\n");
  if( g.perm.Admin ){
    cgi_printf("<li><a href=\"%R/setup\">Administration Pages</a>\n"
           "  <ul>\n"
           "  <li><a href=\"%R/secaudit0\">Security Audit</a></li>\n"
           "  <li><a href=\"%R/modreq\">Pending Moderation Requests</a></li>\n"
           "  </ul></li>\n");
  }
  cgi_printf("<li>%zSkins</a></li>\n"
         "<li>%zTest Pages</a></li>\n",(href("%R/skins")),(href("%R/sitemap-test")));
  if( isPopup ){
    cgi_printf("<li>%zSite Map</a></li>\n",(href("%R/sitemap")));
  }

end_of_sitemap:
  cgi_printf("</ul>\n");
  if( !isPopup ){
    style_finish_page();
  }
}

/*
** WEBPAGE: sitemap-test
**
** List some of the web pages offered by the Fossil web engine for testing
** purposes.  This is similar to /sitemap, but is focused only on showing
** pages associated with testing.
*/
void sitemap_test_page(void){
  int isPopup = 0;         /* This is an XMLHttpRequest() for /sitemap */

  login_check_credentials();
  style_set_current_feature("sitemap");
  if( P("popup")!=0 && cgi_csrf_safe(0) ){
    /* If this is a POST from the same origin with the popup=1 parameter,
    ** then disable anti-robot defenses */
    isPopup = 1;
    g.perm.Hyperlink = 1;
    g.jsHref = 0;
  }
  if( !isPopup ){
    style_header("Test Page Map");
    style_adunit_config(ADUNIT_RIGHT_OK);
  }
  cgi_printf("<ul id=\"sitemap\" class=\"columns\" style=\"column-width:20em\">\n");
  if( g.perm.Admin || db_get_boolean("test_env_enable",0) ){
    cgi_printf("<li>%zCGI Environment Test</a></li>\n",(href("%R/test-env")));
  }
  if( g.perm.Read ){
    cgi_printf("<li>%zList of file renames</a></li>\n",(href("%R/test-rename-list")));
  }
  cgi_printf("<li>%zList of built-in files</a></li>\n"
         "<li>%zList of MIME types</a></li>\n"
         "<li>%zHash color test</a>\n"
         "<li>%zBackground color test</a>\n",(href("%R/test-builtin-files")),(href("%R/mimetype_list")),(href("%R/hash-color-test")),(href("%R/test-bgcolor")));
  if( g.perm.Admin ){
    cgi_printf("<li>%zList of backlinks</a></li>\n"
           "<li>%zBacklink timeline</a></li>\n"
           "<li>%zList of phantom artifacts</a></li>\n"
           "<li>%zError Log test page</a></li>\n"
           "<li>%zRepository <tt>sqlite_stat1</tt> table</a>\n"
           "<li>%zRepository schema</a></li>\n",(href("%R/test-backlinks")),(href("%R/test-backlink-timeline")),(href("%R/phantoms")),(href("%R/test-warning")),(href("%R/repo_stat1")),(href("%R/repo_schema")));
  }
  if( g.perm.Read && g.perm.Hyperlink ){
    cgi_printf("<li>%zTimeline of timewarps</a></li>\n",(href("%R/timewarps")));
  }
  cgi_printf("<li>%zContent of display preference cookie</a></li>\n"
         "<li>%zRandom ASCII-art Captcha image</a></li>\n"
         "<li>%zPie-Chart generator test</a></li>\n",(href("%R/cookies")),(href("%R/test-captcha")),(href("%R/test-piechart")));
  if( !isPopup ){
    style_finish_page();
  }
}

/*
** WEBPAGE: sitemap-timeline
**
** Generate a list of hyperlinks to various (obscure) variations on
** the /timeline page.
*/
void sitemap_timeline_page(void){
  int isPopup = 0;         /* This is an XMLHttpRequest() for /sitemap */

  login_check_credentials();
  style_set_current_feature("sitemap");
  if( P("popup")!=0 && cgi_csrf_safe(0) ){
    /* If this is a POST from the same origin with the popup=1 parameter,
    ** then disable anti-robot defenses */
    isPopup = 1;
    g.perm.Hyperlink = 1;
    g.jsHref = 0;
  }
  if( !isPopup ){
    style_header("Timeline Examples");
    style_adunit_config(ADUNIT_RIGHT_OK);
  }
  cgi_printf("<ul id=\"sitemap\" class=\"columns\" style=\"column-width:20em\">\n"
         "<li>%zCurrent day</a></li>\n"
         "<li>%zCurrent week</a></li>\n"
         "<li>%zCurrent month</a></li>\n"
         "<li>%zToday in history</a></li>\n"
         "<li>%zFirst 10\n"
         "    check-ins</a></li>\n"
         "<li>%zFile name changes</a></li>\n"
         "<li>%zForks</a></li>\n"
         "<li>%zCherrypick merges</a></li>\n"
         "<li>%zTimewarps</a></li>\n"
         "<li>%zColor-coded by user</a></li>\n"
         "<li>%zDelta vs. baseline manifests</a></li>\n"
         "</ul>\n",(href("%R/timeline?ymd")),(href("%R/timeline?yw")),(href("%R/timeline?ym")),(href("%R/thisdayinhistory")),(href("%R/timeline?a=1970-01-01&y=ci&n=10")),(href("%R/timeline?namechng")),(href("%R/timeline?forks")),(href("%R/timeline?cherrypicks")),(href("%R/timewarps")),(href("%R/timeline?ubg")),(href("%R/timeline?deltabg")));
  if( !isPopup ){
    style_finish_page();
  }
}
