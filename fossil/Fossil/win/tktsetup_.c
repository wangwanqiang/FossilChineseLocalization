#line 1 "C:\\source\\fossil_depot\\fossil\\Fossil\\src\\tktsetup.c"
/*
** Copyright (c) 2007 D. Richard Hipp
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
** This file contains code to implement the ticket configuration
** setup screens.
*/
#include "config.h"
#include "tktsetup.h"
#include <assert.h>

/*
** WEBPAGE: tktsetup
** Main sub-menu for configuring the ticketing system.
*/
void tktsetup_page(void){
  login_check_credentials();
  if( !g.perm.Setup ){
    login_needed(0);
    return;
  }

  style_header("Ticket Setup");
  cgi_printf("<table border=\"0\" cellspacing=\"20\">\n");
  setup_menu_entry("表结构", "tktsetup_tab",
    "指定数据库中\"ticket\"表的结构。");
  setup_menu_entry("时间线", "tktsetup_timeline",
    "如何在时间线中显示工单状态");
  setup_menu_entry("通用代码", "tktsetup_com",
    "所有工单处理前运行的通用TH1代码。");
  setup_menu_entry("变更后代码", "tktsetup_change",
    "工单编辑或创建后运行的TH1代码。");
  setup_menu_entry("新建工单页面", "tktsetup_newpage",
    "用于\"新建工单\"网页的内嵌TH1代码的HTML。");
  setup_menu_entry("查看工单页面", "tktsetup_viewpage",
    "用于\"查看工单\"网页的内嵌TH1代码的HTML。");
  setup_menu_entry("编辑工单页面", "tktsetup_editpage",
    "用于\"编辑工单\"网页的内嵌TH1代码的HTML。");
  setup_menu_entry("报告列表页面", "tktsetup_reportlist",
    "用于\"报告列表\"网页的内嵌TH1代码的HTML。");
  setup_menu_entry("报告模板", "tktsetup_rpttplt",
    "默认工单报告格式。");
  setup_menu_entry("颜色键模板", "tktsetup_keytplt",
    "报告的默认颜色键。");
  cgi_printf("</table>\n");
  style_finish_page();
}

/*
** NOTE:  When changing the table definition below, also change the
** equivalent definition found in schema.c.
*/
/* @-comment: ** */
static const char zDefaultTicketTable[] =
"CREATE TABLE ticket(\n"
"  -- Do not change any column that begins with tkt_\n"
"  tkt_id INTEGER PRIMARY KEY,\n"
"  tkt_uuid TEXT UNIQUE,\n"
"  tkt_mtime DATE,\n"
"  tkt_ctime DATE,\n"
"  -- Add as many fields as required below this line\n"
"  type TEXT,\n"
"  status TEXT,\n"
"  subsystem TEXT,\n"
"  priority TEXT,\n"
"  severity TEXT,\n"
"  foundin TEXT,\n"
"  private_contact TEXT,\n"
"  resolution TEXT,\n"
"  title TEXT,\n"
"  comment TEXT\n"
");\n"
"CREATE TABLE ticketchng(\n"
"  -- Do not change any column that begins with tkt_\n"
"  tkt_id INTEGER REFERENCES ticket,\n"
"  tkt_rid INTEGER REFERENCES blob,\n"
"  tkt_mtime DATE,\n"
"  tkt_user TEXT,\n"
"  -- Add as many fields as required below this line\n"
"  login TEXT,\n"
"  username TEXT,\n"
"  mimetype TEXT,\n"
"  icomment TEXT\n"
");\n"
"CREATE INDEX ticketchng_idx1 ON ticketchng(tkt_id, tkt_mtime);\n"
;

/*
** Return the ticket table definition in heap-allocated
** memory owned by the caller.
*/
char *ticket_table_schema(void){
  return db_get("ticket-table", zDefaultTicketTable);
}

/*
** Common implementation for the ticket setup editor pages.
*/
static void tktsetup_generic(
  const char *zTitle,           /* Page title */
  const char *zDbField,         /* Configuration field being edited */
  const char *zDfltValue,       /* Default text value */
  const char *zDesc,            /* Description of this field */
  char *(*xText)(const char*),  /* Validity test or NULL */
  void (*xRebuild)(void),       /* Run after successful update */
  int height                    /* Height of the edit box */
){
  const char *z;
  int isSubmit;

  login_check_credentials();
  if( !g.perm.Setup ){
    login_needed(0);
    return;
  }
  style_set_current_feature("tktsetup");
  if( P("setup") ){
    cgi_redirect("tktsetup");
  }
  isSubmit = P("submit")!=0;
  z = P("x");
  if( z==0 ){
    z = db_get(zDbField, zDfltValue);
  }
  style_set_current_feature("tktsetup");
  style_header("Edit %s", zTitle);
  if( P("clear")!=0 && cgi_csrf_safe(2) ){
    db_unset(zDbField/*works-like:"x"*/, 0);
    if( xRebuild ) xRebuild();
    cgi_redirect("tktsetup");
  }else if( isSubmit && cgi_csrf_safe(2) ){
    char *zErr = 0;
    if( xText && (zErr = xText(z))!=0 ){
      cgi_printf("<p class=\"tktsetupError\">ERROR: %h</p>\n",(zErr));
    }else{
      db_set(zDbField/*works-like:"x"*/, z, 0);
      if( xRebuild ) xRebuild();
      cgi_redirect("tktsetup");
    }
  }
  cgi_printf("<form action=\"%R/%s\" method=\"post\"><div>\n",(g.zPath));
  login_insert_csrf_secret();
  cgi_printf("<p>%s</p>\n"
         "<textarea name=\"x\" rows=\"%d\" cols=\"80\">%h</textarea>\n"
         "<blockquote><p>\n"
         "<input type=\"submit\" name=\"submit\" value=\"Apply Changes\">\n"
         "<input type=\"submit\" name=\"clear\" value=\"Revert To Default\">\n"
         "<input type=\"submit\" name=\"setup\" value=\"Cancel\">\n"
         "</p></blockquote>\n"
         "</div></form>\n"
         "<hr>\n"
         "<h2>Default %s</h2>\n"
         "<blockquote><pre>\n"
         "%h\n"
         "</pre></blockquote>\n",(zDesc),(height),(z),(zTitle),(zDfltValue));
  style_submenu_element("Back", "%R/tktsetup");
  style_finish_page();
}

/*
** WEBPAGE: tktsetup_tab
** Administrative page for defining the "ticket" table used
** to hold ticket information.
*/
void tktsetup_tab_page(void){
  static const char zDesc[] =
  "Enter a valid CREATE TABLE statement for the \"ticket\" table.  The\n"
  "table must contain columns named \"tkt_id\", \"tkt_uuid\", and \"tkt_mtime\"\n"
  "with an unique index on \"tkt_uuid\" and \"tkt_mtime\".\n"
  ;
  tktsetup_generic(
    "Ticket Table Schema",
    "ticket-table",
    zDefaultTicketTable,
    zDesc,
    ticket_schema_check,
    ticket_rebuild,
    20
  );
}

static const char zDefaultTicketCommon[] =
"set type_choices {\n"
"   Code_Defect\n"
"   Build_Problem\n"
"   Documentation\n"
"   Feature_Request\n"
"   Incident\n"
"}\n"
"set priority_choices {\n"
"  Immediate\n"
"  High\n"
"  Medium\n"
"  Low\n"
"  Zero\n"
"}\n"
"set severity_choices {\n"
"  Critical\n"
"  Severe\n"
"  Important\n"
"  Minor\n"
"  Cosmetic\n"
"}\n"
"set resolution_choices {\n"
"  Open\n"
"  Fixed\n"
"  Rejected\n"
"  Workaround\n"
"  Unable_To_Reproduce\n"
"  Works_As_Designed\n"
"  External_Bug\n"
"  Not_A_Bug\n"
"  Duplicate\n"
"  Overcome_By_Events\n"
"  Drive_By_Patch\n"
"  Misconfiguration\n"
"}\n"
"set status_choices {\n"
"  Open\n"
"  Verified\n"
"  Review\n"
"  Deferred\n"
"  Fixed\n"
"  Tested\n"
"  Closed\n"
"}\n"
"set subsystem_choices {\n"
"}\n"
;

/*
** Return the ticket common code.
*/
const char *ticket_common_code(void){
  return db_get("ticket-common", zDefaultTicketCommon);
}

/*
** WEBPAGE: tktsetup_com
** Administrative page used to define TH1 script that is
** common to all ticket screens.
*/
void tktsetup_com_page(void){
  static const char zDesc[] =
  "Enter TH1 script that initializes variables prior to generating\n"
  "any of the ticket view, edit, or creation pages.\n"
  ;
  tktsetup_generic(
    "Ticket Common Script",
    "ticket-common",
    zDefaultTicketCommon,
    zDesc,
    0,
    0,
    30
  );
}

static const char zDefaultTicketChange[] =
"return\n"
;

/*
** Return the ticket change code.
*/
const char *ticket_change_code(void){
  return db_get("ticket-change", zDefaultTicketChange);
}

/*
** WEBPAGE: tktsetup_change
** Administrative screen used to view or edit the TH1 script
** that shows ticket changes.
*/
void tktsetup_change_page(void){
  static const char zDesc[] =
  "Enter TH1 script that runs after processing the ticket editing\n"
  "and creation pages.\n"
  ;
  tktsetup_generic(
    "Ticket Change Script",
    "ticket-change",
    zDefaultTicketChange,
    zDesc,
    0,
    0,
    30
  );
}

static const char zDefaultNew[] =
"<th1>\n"
"  if {![info exists mutype]} {set mutype Markdown}\n"
"  if {[info exists submit] || [info exists submitandnew]} {\n"
"     set status Open\n"
"     if {$mutype eq \"HTML\"} {\n"
"       set mimetype \"text/html\"\n"
"     } elseif {$mutype eq \"Wiki\"} {\n"
"       set mimetype \"text/x-fossil-wiki\"\n"
"     } elseif {$mutype eq \"Markdown\"} {\n"
"       set mimetype text/x-markdown\n"
"     } elseif {$mutype eq {[links only]}} {\n"
"       set mimetype \"text/x-fossil-plain\"\n"
"     } else {\n"
"       set mimetype \"text/plain\"\n"
"     }\n"
"     submit_ticket\n"
"     set preview 1\n"
"  }\n"
"</th1>\n"
"<h1 style=\"text-align: center;\">Enter A New Ticket</h1>\n"
"<table cellpadding=\"5\">\n"
"<tr>\n"
"<td colspan=\"3\">\n"
"Enter a one-line summary of the ticket:<br>\n"
"<input type=\"text\" name=\"title\" size=\"60\" value=\"$<title>\">\n"
"</td>\n"
"</tr>\n"
"\n"
"<tr>\n"
"<td align=\"right\">Type:</td>\n"
"<td align=\"left\"><th1>combobox type $type_choices 1</th1></td>\n"
"<td align=\"left\">What type of ticket is this?</td>\n"
"</tr>\n"
"\n"
"<tr>\n"
"<td align=\"right\">Version:</td>\n"
"<td align=\"left\">\n"
"<input type=\"text\" name=\"foundin\" size=\"20\" value=\"$<foundin>\">\n"
"</td>\n"
"<td align=\"left\">In what version or build number do you observe\n"
"the problem?</td>\n"
"</tr>\n"
"\n"
"<tr>\n"
"<td align=\"right\">Severity:</td>\n"
"<td align=\"left\"><th1>combobox severity $severity_choices 1</th1></td>\n"
"<td align=\"left\">How debilitating is the problem?  How badly does the problem\n"
"affect the operation of the product?</td>\n"
"</tr>\n"
"\n"
"<th1>\n"
"  if {[capexpr {w}]} {\n"
"     html {<tr><td class=\"tktDspLabel\">Priority:</td><td>}\n"
"     combobox priority $priority_choices 1\n"
"     html {\n"
"       <td align=\"left\">How important is the affected functionality?</td>\n"
"       </td></tr>\n"
"     }\n"
"\n"
"     html {<tr><td class=\"tktDspLabel\">Subsystem:</td><td>}\n"
"     combobox subsystem $subsystem_choices 1\n"
"     html {\n"
"       <td align=\"left\">Which subsystem is affected?</td>\n"
"       </td></tr>\n"
"     }\n"
"  }\n"
"</th1>\n"
"\n"
"<tr>\n"
"<td align=\"right\">EMail:</td>\n"
"<td align=\"left\">\n"
"<input name=\"private_contact\" value=\"$<private_contact>\" size=\"30\">\n"
"</td>\n"
"<td align=\"left\"><u>Not publicly visible</u>\n"
"Used by developers to contact you with questions.</td>\n"
"</tr>\n"
"\n"
"<tr>\n"
"<td colspan=\"3\">\n"
"Enter a detailed description of the problem.\n"
"For code defects, be sure to provide details on exactly how\n"
"the problem can be reproduced.  Provide as much detail as\n"
"possible.  Format:\n"
"<th1>combobox mutype {HTML {[links only]} Markdown {Plain Text} Wiki} 1</th1>\n"
"<br>\n"
"<th1>set nline [linecount $comment 50 10]</th1>\n"
"<textarea name=\"icomment\" cols=\"80\" rows=\"$nline\"\n"
" wrap=\"virtual\" class=\"wikiedit\">$<icomment></textarea><br>\n"
"</tr>\n"
"\n"
"<th1>enable_output [info exists preview]</th1>\n"
"<tr><td colspan=\"3\">\n"
"Description Preview:<br><hr>\n"
"<th1>\n"
"if {$mutype eq \"Wiki\"} {\n"
"  wiki $icomment\n"
"} elseif {$mutype eq \"Plain Text\"} {\n"
"  set r [randhex]\n"
"  wiki \"<verbatim-$r>[string trimright $icomment]\\n</verbatim-$r>\"\n"
"} elseif {$mutype eq \"Markdown\"} {\n"
"  html [lindex [markdown \"$icomment\\n\"] 1]\n"
"} elseif {$mutype eq {[links only]}} {\n"
"  set r [randhex]\n"
"  wiki \"<verbatim-$r links>[string trimright $icomment]\\n</verbatim-$r>\"\n"
"} else {\n"
"  wiki \"<nowiki>$icomment\\n</nowiki>\"\n"
"}\n"
"</th1>\n"
"<hr></td></tr>\n"
"<th1>enable_output 1</th1>\n"
"\n"
"<tr>\n"
"<td><td align=\"left\">\n"
"<input type=\"submit\" name=\"preview\" value=\"Preview\">\n"
"</td>\n"
"<td align=\"left\">See how the description will appear after formatting.</td>\n"
"</tr>\n"
"\n"
"<th1>enable_output [info exists preview]</th1>\n"
"<tr>\n"
"<td><td align=\"left\">\n"
"<input type=\"submit\" name=\"submit\" value=\"Submit\">\n"
"</td>\n"
"<td align=\"left\">After filling in the information above, press this\n"
"button to create the new ticket.</td>\n"
"</tr>\n"
"\n"
"<tr>\n"
"<td><td align=\"left\">\n"
"<input type=\"submit\" name=\"submitandnew\" value=\"Submit and New\">\n"
"</td>\n"
"<td align=\"left\">Create the new ticket and start another\n"
"ticket form with the inputs.</td>\n"
"</tr>\n"
"<th1>enable_output 1</th1>\n"
"\n"
"<tr>\n"
"<td><td align=\"left\">\n"
"<input type=\"submit\" name=\"cancel\" value=\"Cancel\">\n"
"</td>\n"
"<td>Abandon and forget this ticket.</td>\n"
"</tr>\n"
"</table>\n"
;

/*
** Return the code used to generate the new ticket page
*/
const char *ticket_newpage_code(void){
  return db_get("ticket-newpage", zDefaultNew);
}

/*
** WEBPAGE: tktsetup_newpage
** Administrative page used to view or edit the TH1 script used
** to enter new tickets.
*/
void tktsetup_newpage_page(void){
  static const char zDesc[] =
  "Enter HTML with embedded TH1 script that will render the \"new ticket\"\n"
  "page\n"
  ;
  tktsetup_generic(
    "HTML For New Tickets",
    "ticket-newpage",
    zDefaultNew,
    zDesc,
    0,
    0,
    40
  );
}

static const char zDefaultView[] =
"<table cellpadding=\"5\">\n"
"<tr><td class=\"tktDspLabel\">Ticket&nbsp;Hash:</td>\n"
"<th1>\n"
"if {[info exists tkt_uuid]} {\n"
"  html \"<td class='tktDspValue' colspan='3'>\"\n"
"  copybtn hash-tk 0 $tkt_uuid 2\n"
"  if {[hascap s]} {\n"
"    puts \" ($tkt_id)\"\n"
"  }\n"
"  html \"</td></tr>\\n\"\n"
"} else {\n"
"  if {[hascap s]} {\n"
"    html \"<td class='tktDspValue' colspan='3'>Deleted \"\n"
"    html \"(0)</td></tr>\\n\"\n"
"  } else {\n"
"    html \"<td class='tktDspValue' colspan='3'>Deleted</td></tr>\\n\"\n"
"  }\n"
"}\n"
"\n"
"if {[capexpr {n}]} {\n"
"  submenu link \"Copy Ticket\" /tktnew/$tkt_uuid\n"
"}\n"
"if {[capexpr {nk}]} {\n"
"  submenu link \"Edit Wiki\" /wikiedit?name=ticket/$tkt_uuid\n"
"}\n"
"</th1>\n"
"<tr><td class=\"tktDspLabel\">Title:</td>\n"
"<td class=\"tktDspValue\" colspan=\"3\">\n"
"$<title>\n"
"</td></tr>\n"
"<tr><td class=\"tktDspLabel\">Status:</td><td class=\"tktDspValue\">\n"
"$<status>\n"
"</td>\n"
"<td class=\"tktDspLabel\">Type:</td><td class=\"tktDspValue\">\n"
"$<type>\n"
"</td></tr>\n"
"<tr><td class=\"tktDspLabel\">Severity:</td><td class=\"tktDspValue\">\n"
"$<severity>\n"
"</td>\n"
"<td class=\"tktDspLabel\">Priority:</td><td class=\"tktDspValue\">\n"
"$<priority>\n"
"</td></tr>\n"
"<tr><td class=\"tktDspLabel\">Subsystem:</td><td class=\"tktDspValue\">\n"
"$<subsystem>\n"
"</td>\n"
"<td class=\"tktDspLabel\">Resolution:</td><td class=\"tktDspValue\">\n"
"$<resolution>\n"
"</td></tr>\n"
"<tr><td class=\"tktDspLabel\">Last&nbsp;Modified:</td><td class=\"tktDspValue\">\n"
"<th1>\n"
"if {[info exists tkt_datetime]} {\n"
"  puts $tkt_datetime\n"
"}\n"
"if {[info exists tkt_mage]} {\n"
"  html \"<br>[htmlize $tkt_mage] ago\"\n"
"}\n"
"</th1>\n"
"</td>\n"
"<td class=\"tktDspLabel\">Created:</td><td class=\"tktDspValue\">\n"
"<th1>\n"
"if {[info exists tkt_datetime_creation]} {\n"
"  puts $tkt_datetime_creation\n"
"}\n"
"if {[info exists tkt_cage]} {\n"
"  html \"<br>[htmlize $tkt_cage] ago\"\n"
"}\n"
"</th1>\n"
"</td></tr>\n"
"<th1>enable_output [hascap e]</th1>\n"
"  <tr>\n"
"  <td class=\"tktDspLabel\">Contact:</td><td class=\"tktDspValue\" colspan=\"3\">\n"
"  $<private_contact>\n"
"  </td>\n"
"  </tr>\n"
"<th1>enable_output 1</th1>\n"
"<tr><td class=\"tktDspLabel\">Version&nbsp;Found&nbsp;In:</td>\n"
"<td colspan=\"3\" valign=\"top\" class=\"tktDspValue\">\n"
"<th1>\n"
"set versionlink \"\"\n"
"set urlfoundin [httpize $foundin]\n"
"set tagpattern {^[-0-9A-Za-z_\\\\.]+$}\n"
"if [regexp $tagpattern $foundin] {\n"
"  query {SELECT count(*) AS match FROM tag\n"
"         WHERE tagname=concat('sym-',$foundin)} {\n"
"    if {$match} {set versionlink \"timeline?t=$urlfoundin\"}\n"
"  }\n"
"}\n"
"set hashpattern {^[0-9a-f]+$}\n"
"if [regexp $hashpattern $foundin] {\n"
"  set pattern $foundin*\n"
"  query {SELECT count(*) AS match FROM blob WHERE uuid GLOB $pattern} {\n"
"    if {$match} {set versionlink \"info/$urlfoundin\"}\n"
"  }\n"
"}\n"
"if {$versionlink eq \"\"} {\n"
"  puts $foundin\n"
"} else {\n"
"  html \"<a href=\\\"\"\n"
"  puts $versionlink\n"
"  html \"\\\">\"\n"
"  puts $foundin\n"
"  html \"</a>\"\n"
"}\n"
"</th1>\n"
"</td></tr>\n"
"</table>\n"
"\n"
"<th1>\n"
"wiki_assoc \"ticket\" $tkt_uuid\n"
"</th1>\n"
"\n"
"<table cellpadding=\"5\" style=\"min-width:100%\">\n"
"<th1>\n"
"if {[info exists comment]} {\n"
"  if {[string length $comment]>10} {\n"
"    html {\n"
"      <tr><td class=\"tktDspLabel\">Description:</td></tr>\n"
"      <tr><td colspan=\"5\" class=\"tktDspValue\">\n"
"    }\n"
"    if {[info exists plaintext]} {\n"
"      set r [randhex]\n"
"      wiki \"<verbatim-$r links>\\n$comment\\n</verbatim-$r>\"\n"
"    } else {\n"
"      wiki $comment\n"
"    }\n"
"  }\n"
"}\n"
"set seenRow 0\n"
"set alwaysPlaintext [info exists plaintext]\n"
"query {SELECT datetime(tkt_mtime,toLocal()) AS xdate, login AS xlogin,\n"
"              mimetype as xmimetype, icomment AS xcomment,\n"
"              username AS xusername\n"
"         FROM ticketchng\n"
"        WHERE tkt_id=$tkt_id AND length(icomment)>0} {\n"
"  if {$seenRow} {\n"
"    html \"<hr>\\n\"\n"
"  } else {\n"
"    html \"<tr><td class='tktDspLabel' style='text-align:left'>\\n\"\n"
"    html \"User Comments:</td></tr>\\n\"\n"
"    html \"<tr><td colspan='5' class='tktDspValue'>\\n\"\n"
"    set seenRow 1\n"
"  }\n"
"  html \"<span class='tktDspCommenter'>\"\n"
"  puts $xlogin\n"
"  if {$xlogin ne $xusername && [string length $xusername]>0} {\n"
"    puts \" (claiming to be $xusername)\"\n"
"  }\n"
"  puts \" added on $xdate:\"\n"
"  html \"</span>\\n\"\n"
"  if {$alwaysPlaintext || $xmimetype eq \"text/plain\"} {\n"
"    set r [randhex]\n"
"    if {$xmimetype ne \"text/plain\"} {puts \"($xmimetype)\\n\"}\n"
"    wiki \"<verbatim-$r>[string trimright $xcomment]</verbatim-$r>\\n\"\n"
"  } elseif {$xmimetype eq \"text/x-fossil-wiki\"} {\n"
"    wiki \"<p>\\n[string trimright $xcomment]\\n</p>\\n\"\n"
"  } elseif {$xmimetype eq \"text/x-markdown\"} {\n"
"    html [lindex [markdown $xcomment] 1]\n"
"  } elseif {$xmimetype eq \"text/html\"} {\n"
"    wiki \"<p><nowiki>\\n[string trimright $xcomment]\\n</nowiki>\\n\"\n"
"  } else {\n"
"    set r [randhex]\n"
"    wiki \"<verbatim-$r links>[string trimright $xcomment]</verbatim-$r>\\n\"\n"
"  }\n"
"}\n"
"if {$seenRow} {html \"</td></tr>\\n\"}\n"
"</th1>\n"
"</table>\n"
;


/*
** Return the code used to generate the view ticket page
*/
const char *ticket_viewpage_code(void){
  return db_get("ticket-viewpage", zDefaultView);
}

/*
** WEBPAGE: tktsetup_viewpage
** Administrative page used to view or edit the TH1 script that
** displays individual tickets.
*/
void tktsetup_viewpage_page(void){
  static const char zDesc[] =
  "Enter HTML with embedded TH1 script that will render the \"view ticket\" page\n"
  ;
  tktsetup_generic(
    "HTML For Viewing Tickets",
    "ticket-viewpage",
    zDefaultView,
    zDesc,
    0,
    0,
    40
  );
}

static const char zDefaultEdit[] =
"<th1>\n"
"  if {![info exists mutype]} {set mutype Markdown}\n"
"  if {![info exists icomment]} {set icomment {}}\n"
"  if {![info exists username]} {set username $login}\n"
"  if {[info exists submit]} {\n"
"    if {$mutype eq \"Wiki\"} {\n"
"      set mimetype text/x-fossil-wiki\n"
"    } elseif {$mutype eq \"Markdown\"} {\n"
"      set mimetype text/x-markdown\n"
"    } elseif {$mutype eq \"HTML\"} {\n"
"      set mimetype text/html\n"
"    } elseif {$mutype eq {[links only]}} {\n"
"      set mimetype text/x-fossil-plain\n"
"    } else {\n"
"      set mimetype text/plain\n"
"    }\n"
"    submit_ticket\n"
"    set preview 1\n"
"  }\n"
"</th1>\n"
"<table cellpadding=\"5\">\n"
"<tr><td class=\"tktDspLabel\">Title:</td><td>\n"
"<input type=\"text\" name=\"title\" value=\"$<title>\" size=\"60\">\n"
"</td></tr>\n"
"\n"
"<tr><td class=\"tktDspLabel\">Status:</td><td>\n"
"<th1>combobox status $status_choices 1</th1>\n"
"</td></tr>\n"
"\n"
"<tr><td class=\"tktDspLabel\">Type:</td><td>\n"
"<th1>combobox type $type_choices 1</th1>\n"
"</td></tr>\n"
"\n"
"<tr><td class=\"tktDspLabel\">Severity:</td><td>\n"
"<th1>combobox severity $severity_choices 1</th1>\n"
"</td></tr>\n"
"\n"
"<tr><td class=\"tktDspLabel\">Priority:</td><td>\n"
"<th1>combobox priority $priority_choices 1</th1>\n"
"</td></tr>\n"
"\n"
"<tr><td class=\"tktDspLabel\">Resolution:</td><td>\n"
"<th1>combobox resolution $resolution_choices 1</th1>\n"
"</td></tr>\n"
"\n"
"<tr><td class=\"tktDspLabel\">Subsystem:</td><td>\n"
"<th1>combobox subsystem $subsystem_choices 1</th1>\n"
"</td></tr>\n"
"\n"
"<th1>enable_output [hascap e]</th1>\n"
"  <tr><td class=\"tktDspLabel\">Contact:</td><td>\n"
"  <input type=\"text\" name=\"private_contact\" size=\"40\"\n"
"   value=\"$<private_contact>\">\n"
"  </td></tr>\n"
"<th1>enable_output 1</th1>\n"
"\n"
"<tr><td class=\"tktDspLabel\">Version&nbsp;Found&nbsp;In:</td><td>\n"
"<input type=\"text\" name=\"foundin\" size=\"50\" value=\"$<foundin>\">\n"
"</td></tr>\n"
"\n"
"<tr><td colspan=\"2\">\n"
"  Append Remark with format\n"
" <th1>combobox mutype {HTML {[links only]} Markdown {Plain Text} Wiki} 1</th1>\n"
"  from\n"
"  <input type=\"text\" name=\"username\" value=\"$<username>\" size=\"30\">:<br>\n"
"  <textarea name=\"icomment\" cols=\"80\" rows=\"15\"\n"
"   wrap=\"virtual\" class=\"wikiedit\">$<icomment></textarea>\n"
"</td></tr>\n"
"\n"
"<th1>enable_output [info exists preview]</th1>\n"
"<tr><td colspan=\"2\">\n"
"Description Preview:<br><hr>\n"
"<th1>\n"
"if {$mutype eq \"Wiki\"} {\n"
"  wiki $icomment\n"
"} elseif {$mutype eq \"Plain Text\"} {\n"
"  set r [randhex]\n"
"  wiki \"<verbatim-$r>\\n[string trimright $icomment]\\n</verbatim-$r>\"\n"
"} elseif {$mutype eq \"Markdown\"} {\n"
"  html [lindex [markdown \"$icomment\\n\"] 1]\n"
"} elseif {$mutype eq {[links only]}} {\n"
"  set r [randhex]\n"
"  wiki \"<verbatim-$r links>\\n[string trimright $icomment]</verbatim-$r>\"\n"
"} else {\n"
"  wiki \"<nowiki>\\n[string trimright $icomment]\\n</nowiki>\"\n"
"}\n"
"</th1>\n"
"<hr>\n"
"</td></tr>\n"
"<th1>enable_output 1</th1>\n"
"\n"
"<tr>\n"
"<td align=\"right\">\n"
"<input type=\"submit\" name=\"preview\" value=\"Preview\">\n"
"</td>\n"
"<td align=\"left\">See how the description will appear after formatting.</td>\n"
"</tr>\n"
"\n"
"<th1>enable_output [info exists preview]</th1>\n"
"<tr>\n"
"<td align=\"right\">\n"
"<input type=\"submit\" name=\"submit\" value=\"Submit\">\n"
"</td>\n"
"<td align=\"left\">Apply the changes shown above</td>\n"
"</tr>\n"
"<th1>enable_output 1</th1>\n"
"\n"
"<tr>\n"
"<td align=\"right\">\n"
"<input type=\"submit\" name=\"cancel\" value=\"Cancel\">\n"
"</td>\n"
"<td>Abandon this edit</td>\n"
"</tr>\n"
"\n"
"<th1>\n"
"set seenRow 0\n"
"set alwaysPlaintext [info exists plaintext]\n"
"query {SELECT datetime(tkt_mtime,toLocal()) AS xdate, login AS xlogin,\n"
"              mimetype as xmimetype, icomment AS xcomment,\n"
"              username AS xusername\n"
"         FROM ticketchng\n"
"        WHERE tkt_id=$tkt_id AND length(icomment)>0} {\n"
"  if {$seenRow} {\n"
"    html \"<hr>\\n\"\n"
"  } else {\n"
"    html \"<tr><td colspan='2'><hr></td></tr>\\n\"\n"
"    html \"<tr><td colspan='2' class='tktDspLabel' style='text-align:left'>\\n\"\n"
"    html \"Previous User Comments:</td></tr>\\n\"\n"
"    html \"<tr><td colspan='2' class='tktDspValue'>\\n\"\n"
"    set seenRow 1\n"
"  }\n"
"  html \"<span class='tktDspCommenter'>\"\n"
"  puts $xlogin\n"
"  if {$xlogin ne $xusername && [string length $xusername]>0} {\n"
"    puts \" (claiming to be $xusername)\"\n"
"  }\n"
"  puts \" added on $xdate:\"\n"
"  html \"</span>\\n\"\n"
"  if {$alwaysPlaintext || $xmimetype eq \"text/plain\"} {\n"
"    set r [randhex]\n"
"    if {$xmimetype ne \"text/plain\"} {puts \"($xmimetype)\\n\"}\n"
"    wiki \"<verbatim-$r>[string trimright $xcomment]</verbatim-$r>\\n\"\n"
"  } elseif {$xmimetype eq \"text/x-fossil-wiki\"} {\n"
"    wiki \"<p>\\n[string trimright $xcomment]\\n</p>\\n\"\n"
"  } elseif {$xmimetype eq \"text/x-markdown\"} {\n"
"    html [lindex [markdown $xcomment] 1]\n"
"  } elseif {$xmimetype eq \"text/html\"} {\n"
"    wiki \"<p><nowiki>\\n[string trimright $xcomment]\\n</nowiki>\\n\"\n"
"  } else {\n"
"    set r [randhex]\n"
"    wiki \"<verbatim-$r links>[string trimright $xcomment]</verbatim-$r>\\n\"\n"
"  }\n"
"}\n"
"if {$seenRow} {html \"</td></tr>\\n\"}\n"
"</th1>\n"
"\n"
"</table>\n"
;

/*
** Return the code used to generate the edit ticket page
*/
const char *ticket_editpage_code(void){
  return db_get("ticket-editpage", zDefaultEdit);
}

/*
** WEBPAGE: tktsetup_editpage
** Administrative page for viewing or editing the TH1 script that
** drives the ticket editing page.
*/
void tktsetup_editpage_page(void){
  static const char zDesc[] =
  "Enter HTML with embedded TH1 script that will render the \"edit ticket\" page\n"
  ;
  tktsetup_generic(
    "HTML For Editing Tickets",
    "ticket-editpage",
    zDefaultEdit,
    zDesc,
    0,
    0,
    40
  );
}

/*
** The default report list page
*/
static const char zDefaultReportList[] =
"<th1>\n"
"if {[anoncap n]} {\n"
"  html \"<p>Enter a new ticket:</p>\"\n"
"  html \"<ul><li><a href='tktnew'>New ticket</a></li></ul>\"\n"
"}\n"
"</th1>\n"
"\n"
"<p>Choose a report format from the following list:</p>\n"
"<ol>\n"
"<th1>html $report_items</th1>\n"
"</ol>\n"
"\n"
"<th1>\n"
"if {[anoncap t q]} {\n"
"  html \"<p>Other options:</p>\\n<ul>\\n\"\n"
"  if {[anoncap t]} {\n"
"    html \"<li><a href='rptnew'>New report format</a></li>\\n\"\n"
"  }\n"
"  if {[anoncap q]} {\n"
"    html \"<li><a href='modreq'>Tend to pending moderation requests</a></li>\\n\"\n"
"  }\n"
"}\n"
"</th1>\n"
;

/*
** Return the code used to generate the report list
*/
const char *ticket_reportlist_code(void){
  return db_get("ticket-reportlist", zDefaultReportList);
}

/*
** WEBPAGE: tktsetup_reportlist
** Administrative page used to view or edit the TH1 script that
** defines the "report list" page.
*/
void tktsetup_reportlist(void){
  static const char zDesc[] =
  "Enter HTML with embedded TH1 script that will render the \"report list\" page\n"
  ;
  tktsetup_generic(
    "HTML For Report List",
    "ticket-reportlist",
    zDefaultReportList,
    zDesc,
    0,
    0,
    40
  );
}

/*
** The default template ticket report format:
*/
static char zDefaultReport[] =
"SELECT\n"
"  CASE WHEN status IN ('Open','Verified') THEN '#f2dcdc'\n"
"       WHEN status='Review' THEN '#e8e8e8'\n"
"       WHEN status='Fixed' THEN '#cfe8bd'\n"
"       WHEN status='Tested' THEN '#bde5d6'\n"
"       WHEN status='Deferred' THEN '#cacae5'\n"
"       ELSE '#c8c8c8' END AS 'bgcolor',\n"
"  substr(tkt_uuid,1,10) AS '#',\n"
"  datetime(tkt_ctime,toLocal()) AS 'created',\n"
"  datetime(tkt_mtime,toLocal()) AS 'modified',\n"
"  type,\n"
"  status,\n"
"  subsystem,\n"
"  title,\n"
"  comment AS '_comments'\n"
"FROM ticket\n"
;


/*
** Return the template ticket report format:
*/
char *ticket_report_template(void){
  return db_get("ticket-report-template", zDefaultReport);
}

/*
** WEBPAGE: tktsetup_rpttplt
**
** Administrative page used to view or edit the ticket report
** template.
*/
void tktsetup_rpttplt_page(void){
  static const char zDesc[] =
  "Enter the default ticket report format template.  This is the\n"
  "template report format that initially appears when creating a\n"
  "new ticket summary report.\n"
  ;
  tktsetup_generic(
    "Default Report Template",
    "ticket-report-template",
    zDefaultReport,
    zDesc,
    0,
    0,
    20
  );
}

/*
** The default template ticket key:
*/
static const char zDefaultKey[] =
"#ffffff Key:\n"
"#f2dcdc Active\n"
"#e8e8e8 Review\n"
"#cfe8bd Fixed\n"
"#bde5d6 Tested\n"
"#cacae5 Deferred\n"
"#c8c8c8 Closed\n"
;


/*
** Return the template ticket report format:
*/
const char *ticket_key_template(void){
  return db_get("ticket-key-template", zDefaultKey);
}

/*
** WEBPAGE: tktsetup_keytplt
**
** Administrative page used to view or edit the Key template
** for tickets.
*/
void tktsetup_keytplt_page(void){
  static const char zDesc[] =
  "Enter the default ticket report color-key template.  This is the\n"
  "the color-key that initially appears when creating a\n"
  "new ticket summary report.\n"
  ;
  tktsetup_generic(
    "Default Report Color-Key Template",
    "ticket-key-template",
    zDefaultKey,
    zDesc,
    0,
    0,
    10
  );
}

/*
** WEBPAGE: tktsetup_timeline
**
** Administrative page used ot configure how tickets are
** rendered on timeline views.
*/
void tktsetup_timeline_page(void){
  login_check_credentials();
  if( !g.perm.Setup ){
    login_needed(0);
    return;
  }

  if( P("setup") ){
    cgi_redirect("tktsetup");
  }
  style_set_current_feature("tktsetup");
  style_header("Ticket Display On Timelines");
  db_begin_transaction();
  cgi_printf("<form action=\"%R/tktsetup_timeline\" method=\"post\"><div>\n");
  login_insert_csrf_secret();

  cgi_printf("<hr>\n");
  entry_attribute("Ticket Title", 40, "ticket-title-expr", "t",
                  "title", 0);
  cgi_printf("<p>An SQL expression in a query against the TICKET table that will\n"
         "return the title of the ticket for display purposes.\n"
         "(Property: ticket-title-expr)</p>\n");

  cgi_printf("<hr>\n");
  entry_attribute("Ticket Status", 40, "ticket-status-column", "s",
                  "status", 0);
  cgi_printf("<p>The name of the column in the TICKET table that contains the ticket\n"
         "status in human-readable form.  Case sensitive.\n"
         "(Property: ticket-status-column)</p>\n");

  cgi_printf("<hr>\n");
  entry_attribute("Ticket Closed", 40, "ticket-closed-expr", "c",
                  "status='Closed'", 0);
  cgi_printf("<p>An SQL expression that evaluates to true in a TICKET table query if\n"
         "the ticket is closed.\n"
         "(Property: ticket-closed-expr)</p>\n");

  cgi_printf("<hr>\n"
         "<p>\n"
         "<input type=\"submit\"  name=\"submit\" value=\"Apply Changes\">\n"
         "<input type=\"submit\" name=\"setup\" value=\"Cancel\">\n"
         "</p>\n"
         "</div></form>\n");
  db_end_transaction(0);
  style_submenu_element("Back", "%R/tktsetup");
  style_finish_page();

}
