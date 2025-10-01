#line 1 "C:\\source\\fossil_depot\\fossil\\Fossil\\src\\setup.c"
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
** Implementation of the Setup page
*/
#include "config.h"
#include <assert.h>
#include "setup.h"

/*
** Increment the "cfgcnt" variable, so that ETags will know that
** the configuration has changed.
*/
void setup_incr_cfgcnt(void){
  static int once = 1;
  if( once ){
    once = 0;
    db_unprotect(PROTECT_CONFIG);
    db_multi_exec("UPDATE config SET value=value+1 WHERE name='cfgcnt'");
    if( db_changes()==0 ){
      db_multi_exec("INSERT INTO config(name,value) VALUES('cfgcnt',1)");
    }
    db_protect_pop();
  }
}

/*
** Output a single entry for a menu generated using an HTML table.
** If zLink is neither NULL nor an empty string, then it is the page that
** the menu entry will hyperlink to.  If zLink is NULL or "", then
** the menu entry has no hyperlink - it is disabled.
*/
void setup_menu_entry(
  const char *zTitle,
  const char *zLink,
  const char *zDesc  /* Caution!  Rendered using %s.  May contain raw HTML. */
){
  cgi_printf("<tr><td valign=\"top\" align=\"right\">\n");
  if( zLink && zLink[0] ){
    cgi_printf("<a href=\"%s\"><nobr>%h</nobr></a>\n",(zLink),(zTitle));
  }else{
    cgi_printf("<nobr>%h</nobr>\n",(zTitle));
  }
  cgi_printf("</td><td width=\"5\"></td><td valign=\"top\">%s</td></tr>\n",(zDesc));
}



/*
** WEBPAGE: setup
**
** Main menu for the administrative pages.  Requires Admin or Setup
** privileges.  Links to sub-pages only usable by Setup users are
** shown only to Setup users.
*/
void setup_page(void){
  int setup_user = 0;
  login_check_credentials();
  if( !g.perm.Admin ){
    login_needed(0);
  }
  setup_user = g.perm.Setup;

  style_set_current_feature("setup");
  style_header("服务器管理");

  /* Make sure the header contains <base href="...">.   Issue a warning
  ** if it does not. */
  if( !cgi_header_contains("<base href=") ){
    cgi_printf("<p class=\"generalError\"><b>配置错误：</b>请在\n"
           "<a href=\"setup_skinedit?w=2\">HTML 头部</a>的\n"
           "<tt>&lt;head&gt;</tt>标签后添加\n"
           "<tt>&lt;base href=\"$secureurl/$current_page\"&gt;</tt>!</p>\n");
  }

#if !defined(_WIN32)
  /* Check for /dev/null and /dev/urandom.  We want both devices to be present,
  ** but they are sometimes omitted (by mistake) from chroot jails. */
  if( access("/dev/null", R_OK|W_OK) ){
    cgi_printf("<p class=\"generalError\">警告：设备\"/dev/null\"无法用于\n"
           "读取和写入。</p>\n");
  }
  if( access("/dev/urandom", R_OK) ){
    cgi_printf("<p class=\"generalError\">警告：设备\"/dev/urandom\"无法用于\n"
           "读取。这意味着SQLite使用的伪随机数生成器的种子质量会很差。</p>\n");
  }
#endif

  cgi_printf("<table border=\"0\" cellspacing=\"3\">\n");
  setup_menu_entry("用户", "setup_ulist",
    "为个人用户授予权限。");
  if( setup_user ){
    setup_menu_entry("访问控制", "setup_access",
      "控制访问设置。");
    setup_menu_entry("配置", "setup_config",
      "配置仓库的WWW组件");
  }
  setup_menu_entry("安全审计", "secaudit0",
    "分析当前配置的安全问题");
  if( setup_user ){
    setup_menu_entry("机器人防御", "setup_robot",
      "配置防御机器人的设置");
    setup_menu_entry("设置", "setup_settings",
      "\"fossil settings\"命令的Web界面");
  }
  setup_menu_entry("时间线", "setup_timeline",
    "时间线显示首选项");
  if( setup_user ){
    setup_menu_entry("登录组", "setup_login_group",
      "管理此仓库与同一服务器上其他仓库之间的单点登录"
      "");
    setup_menu_entry("工单", "tktsetup",
      "为此仓库配置问题工单系统");
    setup_menu_entry("Wiki", "setup_wiki",
      "为此仓库配置Wiki");
    setup_menu_entry("跨Wiki映射", "intermap",
      "跨Wiki链接的关键字映射");
    setup_menu_entry("聊天", "setup_chat",
      "配置聊天室");
    setup_menu_entry("论坛", "setup_forum",
      "论坛配置和统计");
  }
  setup_menu_entry("搜索","srchsetup",
    "配置内置搜索引擎");
  setup_menu_entry("URL别名", "waliassetup",
    "配置URL别名");
  if( setup_user ){
    setup_menu_entry("通知", "setup_notification",
      "通过出站电子邮件自动通知变更");
    setup_menu_entry("传输", "xfersetup",
      "为此仓库配置传输系统");
  }
  setup_menu_entry("皮肤", "setup_skin_admin",
    "选择和/或修改Web界面\"皮肤\"");
  setup_menu_entry("审核", "setup_modreq",
    "启用/禁用Wiki和/或工单变更和附件需要审核"
    "");
  setup_menu_entry("广告单元", "setup_adunit",
    "编辑插入在菜单栏后的广告单元HTML文本");
  setup_menu_entry("URL和检出", "urllist",
    "显示用于访问此仓库的URL和已知检出");
  if( setup_user ){
    setup_menu_entry("Web缓存", "cachestat",
      "查看昂贵页面缓存的状态");
  }
  setup_menu_entry("Logo", "setup_logo",
    "更改服务器的Logo和背景图像");
  setup_menu_entry("屏蔽", "shun",
    "显示此仓库屏蔽的工件");
  setup_menu_entry("日志文件", "setup-logmenu",
    "可用日志文件菜单");
  setup_menu_entry("未版本化文件", "uvlist?byage=1",
    "显示所有未版本化的文件");
  setup_menu_entry("统计", "stat",
    "显示仓库统计信息");
  setup_menu_entry("站点地图", "sitemap",
    "指向各种页面的链接");
  if( setup_user ){
    setup_menu_entry("SQL", "admin_sql",
      "输入原始SQL命令");
    setup_menu_entry("TH1", "admin_th1",
      "输入原始TH1命令");
  }
  cgi_printf("</table>\n");

  style_finish_page();
}


/*
** WEBPAGE: setup-logmenu
**
** Show a menu of available log renderings accessible to an administrator,
** together with a succinct explanation of each.
**
** This page is only accessible by administrators.
*/
void setup_logmenu_page(void){
  Blob desc;
  int bErrLog;                 /* True if Error Log enabled */
  blob_init(&desc, 0, 0);

  /* Administrator access only */
  login_check_credentials();
  if( !g.perm.Admin ){
    login_needed(0);
    return;
  }
  style_header("Log Menu");
  cgi_printf("<table border=\"0\" cellspacing=\"3\">\n");

  if( db_get_boolean("admin-log",1)==0 ){
    blob_appendf(&desc,
      "管理员日志记录对仓库的配置变更。\n"
      "<b>已禁用</b>:  开启 "
      " <a href='%R/setup_settings'>admin-log设置</a> 以启用。"
    );
    setup_menu_entry("管理员日志", 0, blob_str(&desc));
    blob_reset(&desc);
  }else{
    setup_menu_entry("管理员日志", "admin_log",
      "管理员日志记录对仓库的配置变更\n"
      "保存在\"admin_log\"表中。\n"
    );
  }
  setup_menu_entry("传输日志", "rcvfromlist",
    "工件日志记录何时在\n"
    "\"rcvfrom\"表中添加新内容。\n"
  );
  if( db_get_boolean("access-log",1) ){
    setup_menu_entry("用户日志", "user_log",
      "登录尝试记录在\"accesslog\"表中。"
    );
  }else{
    blob_appendf(&desc,
      "登录尝试记录在\"accesslog\"表中。\n"
      "<b>已禁用</b>:  开启 "
      "<a href='%R/setup_settings'>access-log设置</a> 以启用。"
    );
    setup_menu_entry("用户日志", 0, blob_str(&desc));
    blob_reset(&desc);
  }

  blob_appendf(&desc,
    "一个单独的文本文件，用于记录警告和错误消息。\n"
    "单个错误日志可以并且经常在多个仓库之间共享。\n"
  );
  if( g.zErrlog==0 || fossil_strcmp(g.zErrlog,"-")==0 ){
    blob_appendf(&desc,"<b>已禁用</b>: "
                       "要启用错误日志 ");
    if( fossil_strcmp(g.zCmdName, "cgi")==0 ){
      blob_appendf(&desc,
        "在位于 %h 的CGI脚本中添加像 \"errorlog: <i>文件名</i>\" 这样的条目",
        P("SCRIPT_FILENAME")
      );
    }else{
      blob_appendf(&desc,
        " 在启动服务器的命令 \"%h %h\" 中添加 \"--errorlog <i>文件名</i>\" 参数。",
        g.argv[0], g.zCmdName
      );
    }
    bErrLog = 0;
  }else{
    blob_appendf(&desc,"在本仓库中，错误日志是名为 \"%s\" 的文件。", g.zErrlog);
    bErrLog = 1;
  }
  setup_menu_entry("错误日志", bErrLog ? "errorlog" : 0, blob_str(&desc));
  blob_reset(&desc);

  cgi_printf("</table>\n");
  style_finish_page();
}

/*
** Generate a checkbox for an attribute.
*/
void onoff_attribute(
  const char *zLabel,   /* The text label on the checkbox */
  const char *zVar,     /* The corresponding row in the CONFIG table */
  const char *zQParm,   /* The query parameter */
  int dfltVal,          /* Default value if CONFIG table entry does not exist */
  int disabled          /* 1 if disabled */
){
  const char *zQ = P(zQParm);
  int iVal = db_get_boolean(zVar, dfltVal);
  if( zQ==0 && !disabled && P("submit") ){
    zQ = "off";
  }
  if( zQ ){
    int iQ = fossil_strcmp(zQ,"on")==0 || atoi(zQ);
    if( iQ!=iVal && cgi_csrf_safe(2) ){
      db_protect_only(PROTECT_NONE);
      db_set(zVar/*works-like:"x"*/, iQ ? "1" : "0", 0);
      db_protect_pop();
      setup_incr_cfgcnt();
      admin_log("Set option [%q] to [%q].",
                zVar, iQ ? "on" : "off");
      iVal = iQ;
    }
  }
  cgi_printf("<label><input type=\"checkbox\" name=\"%s\" "
         "aria-label=\"%h\" ",(zQParm),(zLabel[0]?zLabel:zQParm));
  if( iVal ){
    cgi_printf("checked=\"checked\" ");
  }
  if( disabled ){
    cgi_printf("disabled=\"disabled\" ");
  }
  cgi_printf("> <b>%s</b></label>\n",(zLabel));
}

/*
** Generate an entry box for an attribute.
*/
void entry_attribute(
  const char *zLabel,   /* The text label on the entry box */
  int width,            /* Width of the entry box */
  const char *zVar,     /* The corresponding row in the CONFIG table */
  const char *zQParm,   /* The query parameter */
  const char *zDflt,    /* Default value if CONFIG table entry does not exist */
  int disabled          /* 1 if disabled */
){
  const char *zVal = db_get(zVar, zDflt);
  const char *zQ = P(zQParm);
  if( zQ && fossil_strcmp(zQ,zVal)!=0 && cgi_csrf_safe(2) ){
    const int nZQ = (int)strlen(zQ);
    setup_incr_cfgcnt();
    db_protect_only(PROTECT_NONE);
    db_set(zVar/*works-like:"x"*/, zQ, 0);
    db_protect_pop();
    admin_log("Set entry_attribute %Q to: %.*s%s",
              zVar, 20, zQ, (nZQ>20 ? "..." : ""));
    zVal = zQ;
  }
  cgi_printf("<input aria-label=\"%h\" type=\"text\" "
         "id=\"%s\" name=\"%s\" value=\"%h\" size=\"%d\" ",(zLabel[0]?zLabel:zQParm),(zQParm),(zQParm),(zVal),(width));
  if( disabled ){
    cgi_printf("disabled=\"disabled\" ");
  }
  cgi_printf("> <b>%s</b>\n",(zLabel));
}

/*
** Generate a text box for an attribute.
*/
const char *textarea_attribute(
  const char *zLabel,   /* The text label on the textarea */
  int rows,             /* Rows in the textarea */
  int cols,             /* Columns in the textarea */
  const char *zVar,     /* The corresponding row in the CONFIG table */
  const char *zQP,      /* The query parameter */
  const char *zDflt,    /* Default value if CONFIG table entry does not exist */
  int disabled          /* 1 if the textarea should  not be editable */
){
  const char *z = db_get(zVar, zDflt);
  const char *zQ = P(zQP);
  if( zQ && !disabled && fossil_strcmp(zQ,z)!=0 && cgi_csrf_safe(2) ){
    const int nZQ = (int)strlen(zQ);
    db_protect_only(PROTECT_NONE);
    db_set(zVar/*works-like:"x"*/, zQ, 0);
    db_protect_pop();
    setup_incr_cfgcnt();
    admin_log("Set textarea_attribute %Q to: %.*s%s",
              zVar, 20, zQ, (nZQ>20 ? "..." : ""));
    z = zQ;
  }
  if( rows>0 && cols>0 ){
    cgi_printf("<textarea id=\"id%s\" name=\"%s\" rows=\"%d\" "
           "aria-label=\"%h\" ",(zQP),(zQP),(rows),(zLabel[0]?zLabel:zQP));
    if( disabled ){
      cgi_printf("disabled=\"disabled\" ");
    }
    cgi_printf("cols=\"%d\">%h</textarea>\n",(cols),(z));
    if( *zLabel ){
      cgi_printf("<span class=\"textareaLabel\">%s</span>\n",(zLabel));
    }
  }
  return z;
}

/*
** Generate a text box for an attribute.
*/
void multiple_choice_attribute(
  const char *zLabel,   /* The text label on the menu */
  const char *zVar,     /* The corresponding row in the CONFIG table */
  const char *zQP,      /* The query parameter */
  const char *zDflt,    /* Default value if CONFIG table entry does not exist */
  int nChoice,          /* Number of choices */
  const char *const *azChoice /* Choices in pairs (VAR value, Display) */
){
  const char *z = db_get(zVar, zDflt);
  const char *zQ = P(zQP);
  int i;
  if( zQ && fossil_strcmp(zQ,z)!=0 && cgi_csrf_safe(2) ){
    const int nZQ = (int)strlen(zQ);
    db_unprotect(PROTECT_ALL);
    db_set(zVar/*works-like:"x"*/, zQ, 0);
    setup_incr_cfgcnt();
    db_protect_pop();
    admin_log("Set multiple_choice_attribute %Q to: %.*s%s",
              zVar, 20, zQ, (nZQ>20 ? "..." : ""));
    z = zQ;
  }
  cgi_printf("<select aria-label=\"%h\" size=\"1\" name=\"%s\" id=\"id%s\">\n",(zLabel),(zQP),(zQP));
  for(i=0; i<nChoice*2; i+=2){
    const char *zSel = fossil_strcmp(azChoice[i],z)==0 ? " selected" : "";
    cgi_printf("<option value=\"%h\"%s>%h</option>\n",(azChoice[i]),(zSel),(azChoice[i+1]));
  }
  cgi_printf("</select> <b>%h</b>\n",(zLabel));
}

/*
** Insert code into the current page that allows the user to configure
** auto-hyperlink related robot defense settings.
*/
static void addAutoHyperlinkSettings(void){
  static const char *const azDefenseOpts[] = {
    "0", "Off",
    "2", "UserAgent only",
    "1", "UserAgent and Javascript",
  };
  multiple_choice_attribute(
     "Enable hyperlinks base on User-Agent and/or Javascript",
     "auto-hyperlink", "autohyperlink", "1",
     count(azDefenseOpts)/2, azDefenseOpts);
  cgi_printf("<br>\n");
  entry_attribute("Delay in milliseconds before enabling hyperlinks", 5,
                  "auto-hyperlink-delay", "ah-delay", "50", 0);
  cgi_printf("<br>\n");
  onoff_attribute("Also require a mouse event before enabling hyperlinks",
                  "auto-hyperlink-mouseover", "ahmo", 0, 0);
  cgi_printf("<p>Enable hyperlinks (the equivalent of the \"h\" permission) for all users,\n"
         "including user \"nobody\" if the request appears to be from a human.\n"
         "Disabling hyperlinks helps prevent robots from walking your site and\n"
         "soaking up all your CPU and bandwidth.\n"
         "If this setting is \"UserAgent only\" (2) then the\n"
         "UserAgent string is the only factor considered.  If the value of this\n"
         "setting is \"UserAgent And Javascript\" (1) then Javascript is added that\n"
         "runs after the page loads and fills in the href= values of &lt;a&gt;\n"
         "elements.  In either case, &lt;a&gt; tags are not generated if the\n"
         "UserAgent string indicates that the client is a robot.\n"
         "(Property: \"auto-hyperlink\")</p>\n"
         "\n"
         "<p>For maximum robot defense, \"Delay\" should be at least 50 milliseconds\n"
         "and \"require a mouse event\" should be turned on.  These values only come\n"
         "into play when the main auto-hyperlink settings is 2 (\"UserAgent and\n"
         "Javascript\").\n"
         "(Properties: \"auto-hyperlink-delay\" and \"auto-hyperlink-mouseover\")</p>\n"
         "\n"
         "<p>To see if Javascript-base hyperlink enabling mechanism is working,\n"
         "visit the <a href=\"%R/test-env\">/test-env</a> page from a separate\n"
         "web browser that is not logged in, even as \"anonymous\" and verify\n"
         "that the \"g.jsHref\" value is \"1\".</p>\n");
}

/*
** WEBPAGE: setup_robot
**
** Settings associated with defense against robots.  Requires setup privilege.
*/
void setup_robots(void){
  login_check_credentials();
  if( !g.perm.Setup ){
    login_needed(0);
    return;
  }
  style_set_current_feature("setup");
  style_header("机器人防御设置");
  db_begin_transaction();
  cgi_printf("<p>即使是一个适度的项目，Fossil网站的树结构中也可能有数以十亿计的页面。其中许多页面（例如：差异比较和压缩包）\n"
         "可能需要大量计算资源。尝试遍历整个网站的机器人可能会造成严重的CPU和带宽负载。\n"
         "\n"
         "<p>本页面的设置旨在帮助站点管理员保护站点免受机器人的影响。\n"
         "\n"
         "<form action=\"%R/setup_robot\" method=\"post\"><div>\n");
  login_insert_csrf_secret();
  cgi_printf("<input type=\"submit\"  name=\"submit\" value=\"应用更改\"></p>\n"
         "<hr>\n"
         "<p><b>不允许机器人访问这些页面。</b><br>\n"
         "如果页面名称与此设置的GLOB模式匹配，且用户是\"nobody\"，且客户端之前未通过验证码\n"
         "测试以证明它不是机器人，则不显示该页面。而是显示验证码测试。\n"
         "此设置的推荐值为：\n"
         "<p>\n"
         "&emsp;&emsp;&emsp;<tt>%h</tt>\n"
         "<p>\n"
         "\"diff\"标签涵盖所有差异比较页面，如/vdiff、/fdiff和\n"
         "/vpatch。\"annotate\"标签涵盖/annotate以及/blame和\n"
         "/praise。\"zip\"涵盖自身以及/tarball和/sqlar。如果一个\n"
         "标签后附加了\"X\"字符，则仅当查询参数使页面特别难以计算时才适用。\n"
         "在所有其他情况下，标签应与页面名称完全匹配。\n"
         "\n"
         "要禁用机器人限制，请将此设置更改为\"off\"。\n"
         "(属性: robot-restrict)\n"
         "<br>\n",(robot_restrict_default()));
  textarea_attribute("", 2, 80,
      "robot-restrict", "rbrestrict", robot_restrict_default(), 0);

  cgi_printf("<hr>\n"
         "<p><b>反机器人限制的例外情况</b><br>\n"
         "下面的条目是一个正则表达式列表，每行一个。\n"
         "如果这些正则表达式中的任何一个与输入URL匹配，则该\n"
         "请求免受反机器人防御。例如，使用如下模式\n"
         "允许脚本下载发布压缩包：</p>\n"
         "<p>\n"
         "&emsp;&emsp;<tt>^/tarball\\b.*\\b(version-|release)\\b</tt>\n"
         "<p>该模式应匹配已删除SCRIPT_NAME前缀的REQUEST_URI，并在QUERY_STRING存在时\n"
         "在其后附加\"?\"和QUERY_STRING。(属性: robot-exception)<br>\n");
  textarea_attribute("", 3, 80,
      "robot-exception", "rbexcept", "", 0);

  cgi_printf("<hr>\n");
  addAutoHyperlinkSettings();

  cgi_printf("<hr>\n");
  entry_attribute("匿名登录有效期", 11, "anon-cookie-lifespan",
                  "anoncookls", "840", 0);
  cgi_printf("<p>匿名登录Cookie的有效分钟数。\n"
         "设置为零可禁用匿名登录。\n"
         "(属性: anon-cookie-lifespan)\n");

  cgi_printf("<hr>\n");
  entry_attribute("服务器负载平均限制", 11, "max-loadavg", "mxldavg",
                  "0.0", 0);
  cgi_printf("<p>如果主机计算机的负载平均值过大，则禁止某些昂贵的操作（如计算tarball、zip归档\n"
         "或注释/归咎页面）。在此设置禁止昂贵计算的阈值。设置为0.0可禁用负载平均限制。\n"
         "此限制仅在Unix服务器上强制执行。在Linux系统上，\n"
         "需要访问/proc虚拟文件系统，这意味着此限制可能在chroot()监狱内不起作用。\n"
         "(属性: \"max-loadavg\")</p>\n"
         "\n"
         "<hr>\n"
         "<p><input type=\"submit\"  name=\"submit\" value=\"应用更改\"></p>\n"
         "</div></form>\n");
  db_end_transaction(0);
  style_finish_page();
}

/*
** WEBPAGE: setup_access
**
** The access-control settings page.  Requires Setup privileges.
*/
void setup_access(void){
  static const char *const azRedirectOpts[] = {
    "0", "关闭",
    "1", "仅登录页面",
    "2", "所有页面"
  };
  login_check_credentials();
  if( !g.perm.Setup ){
    login_needed(0);
    return;
  }

  style_set_current_feature("setup");
  style_header("访问控制设置");
  db_begin_transaction();
  cgi_printf("<form action=\"%R/setup_access\" method=\"post\"><div>\n");
  login_insert_csrf_secret();
  cgi_printf("<input type=\"submit\"  name=\"submit\" value=\"应用更改\"></p>\n"
         "<hr>\n");
  multiple_choice_attribute("重定向到HTTPS",
     "redirect-to-https", "redirhttps", "0",
     count(azRedirectOpts)/2, azRedirectOpts);
  cgi_printf("<p>当接收到未加密请求时，通过重定向到HTTPS强制使用HTTPS。此功能可以仅对登录页面启用，或对所有页面启用。\n"
         "<p>进一步详情：启用此选项后，$secureurl TH1变量将被设置为$baseurl的\"https:\"变体。否则，\n"
         "$secureurl仅作为$baseurl的别名。\n"
         "(属性: \"redirect-to-https\"。\"0\"表示关闭，\"1\"表示仅登录页面，\n"
         "\"2\"表示所有页面。)\n"
         "<hr>\n");
  onoff_attribute("本地访问需要密码",
     "localauth", "localauth", 0, 0);
  cgi_printf("<p>启用后，Web访问始终需要密码登录。禁用时，当使用\n"
         "<a href=\"%R/help/ui\">fossil ui</a>命令，或使用\n"
         "<a href=\"%R/help/server\">fossil server</a>、\n"
         "<a href=\"%R/help/http\">fossil http</a>命令并添加\"--localauth\"命令行选项时，\n"
         "允许从127.0.0.1进行无限制的Web访问。如果CGI脚本中包含\"localauth\"关键字，\n"
         "也允许从<a href=\"%R/help/cgi\">fossil cgi</a>进行无限制访问。\n"
         "\n"
         "<p>在以下任一情况下，始终需要密码：\n"
         "<ol>\n"
         "<li> 此按钮被勾选\n"
         "<li> 入站TCP/IP连接并非来自127.0.0.1\n"
         "<li> 服务器使用<a href=\"%R/help/server\">fossil server</a>或\n"
         "<a href=\"%R/help/server\">fossil http</a>命令启动，\n"
         "但未使用\"--localauth\"选项。\n"
         "<li> 服务器从CGI启动，但CGI脚本中没有\"localauth\"关键字。\n"
         "</ol>\n"
         "(属性: \"localauth\")\n"
         "\n"
         "<hr>\n");
  onoff_attribute("启用 /test-env",
     "test_env_enable", "test_env_enable", 0, 0);
  cgi_printf("<p>启用后，%h/test_env URL对所有用户可用。禁用时（默认），只有Admin和Setup用户可以访问\n"
         "/test_env页面。\n"
         "(属性: \"test_env_enable\")\n"
         "</p>\n"
         "\n"
         "<hr>\n",(g.zBaseURL));
  onoff_attribute("启用 /artifact_stats",
     "artifact_stats_enable", "artifact_stats_enable", 0, 0);
  cgi_printf("<p>启用后，%h/artifact_stats URL对所有用户可用。禁用时（默认），只有具有签入权限的用户可以访问\n"
         "/artifact_stats页面。\n"
         "(属性: \"artifact_stats_enable\")\n"
         "</p>\n"
         "\n"
         "<hr>\n",(g.zBaseURL));
  onoff_attribute("允许REMOTE_USER认证",
     "remote_user_ok", "remote_user_ok", 0, 0);
  cgi_printf("<p>启用后，如果REMOTE_USER环境变量设置为有效用户的登录名，且没有其他登录凭据可用，\n"
         "则REMOTE_USER将被视为已认证用户。\n"
         "(属性: \"remote_user_ok\")\n"
         "</p>\n"
         "\n"
         "<hr>\n");
  onoff_attribute("允许HTTP_AUTHENTICATION认证",
     "http_authentication_ok", "http_authentication_ok", 0, 0);
  cgi_printf("<p>启用后，允许使用HTTP_AUTHENTICATION环境变量或\"Authentication:\" HTTP头来查找用户名和\n"
         "密码。这是支持Basic Authentication的另一种方式。\n"
         "(属性: \"http_authentication_ok\")\n"
         "</p>\n"
         "\n"
         "<hr>\n");
  entry_attribute("登录过期时间", 6, "cookie-expire", "cex",
                  "8766", 0);
  cgi_printf("<p>登录有效的小时数。必须是正数。默认值为8766小时，约等于一年。\n"
         "(属性: \"cookie-expire\")</p>\n");

  cgi_printf("<hr>\n");
  entry_attribute("下载数据包限制", 10, "max-download", "mxdwn",
                  "5000000", 0);
  cgi_printf("<p>Fossil尝试将出站同步、克隆和拉取数据包限制为不压缩状态下的此字节数。如果客户端需要更多数据，\n"
         "则客户端将发出多个HTTP请求。不建议将值设置为低于100万。500万是一个合理的数值。\n"
         "(属性: \"max-download\")</p>\n");

  cgi_printf("<hr>\n");
  entry_attribute("下载时间限制", 11, "max-download-time", "mxdwnt",
                  "30", 0);

  cgi_printf("<p>Fossil尝试在收集同步、克隆和拉取数据包的出站数据时花费少于此秒数。\n"
         "如果客户端请求耗时更长，则会给出部分回复，类似于下载数据包限制。30秒是一个合理的默认值。\n"
         "(属性: \"max-download-time\")</p>\n");

  cgi_printf("<a id=\"slal\"></a>\n"
         "<hr>\n");
  entry_attribute("服务器负载平均限制", 11, "max-loadavg", "mxldavg",
                  "0.0", 0);
  cgi_printf("<p>如果主机计算机的负载平均值过大，则禁止某些昂贵的操作（如计算tarball、zip归档\n"
         "或注释/归咎页面）。在此设置禁止昂贵计算的阈值。设置为0.0可禁用负载平均限制。\n"
         "此限制仅在Unix服务器上强制执行。在Linux系统上，\n"
         "需要访问/proc虚拟文件系统，这意味着此限制可能在chroot()监狱内不起作用。\n"
         "(属性: \"max-loadavg\")</p>\n");

  /* Add the auto-hyperlink settings controls.  These same controls
  ** are also accessible from the /setup_robot page.
  */
  cgi_printf("<hr>\n");
  addAutoHyperlinkSettings();

  cgi_printf("<hr>\n");
  onoff_attribute("未登录时需要验证码",
                  "require-captcha", "reqcapt", 1, 0);
  cgi_printf("<p>对于未登录用户的编辑操作（追加、创建或编辑wiki或工单，或向wiki或工单添加附件）需要验证码。\n"
         "(属性: \"require-captcha\")</p>\n");

  cgi_printf("<hr>\n");
  entry_attribute("公开页面", 30, "public-pages",
                  "pubpage", "", 0);
  cgi_printf("<p>一组逗号分隔的glob模式，指定无需登录即可访问的页面，使用下方\n"
         "\"默认权限\"设置提供的权限。\n"
         "\n"
         "<p>使用示例：将此字段设置为\"/doc/trunk/www/*\"，并将\n"
         "\"默认权限\"设置为包含\"o\"权限，\n"
         "从而为匿名用户提供对www/文件夹中嵌入文档最新版本的只读权限，而不允许\n"
         "他们查看源代码的其余部分。\n"
         "(属性: \"public-pages\")\n"
         "</p>\n");

  cgi_printf("<hr>\n");
  onoff_attribute("允许用户自行注册",
                  "self-register", "selfreg", 0, 0);
  cgi_printf("<p>允许用户在/register网页上自行注册。\n"
         "自行注册会在USER表中创建一个新条目，\n"
         "如果启用了电子邮件通知，可能还会在SUBSCRIBER表中创建一个条目。\n"
         "(属性: \"self-register\")</p>\n");

  cgi_printf("<hr>\n");
  onoff_attribute("允许用户重置自己的密码",
                  "self-pw-reset", "selfpw", 0, 0);
  cgi_printf("<p>允许用户请求发送包含指向密码重置页面的超链接的电子邮件到他们的记录邮箱地址。\n"
         "这使健忘的用户能够在无需管理员干预的情况下恢复忘记的密码。\n"
         "(属性: \"self-pw-reset\")</p>\n");

  cgi_printf("<hr>\n");
  onoff_attribute("自行注册需要电子邮件验证",
                  "selfreg-verify", "sfverify", 0, 0);
  cgi_printf("<p>如果启用，自行注册会在USER表中创建一个新条目，\n"
         "仅具有\"7\"权限。默认用户权限不会被添加，直到与自行注册相关联的\n"
         "电子邮件地址已被验证。此设置仅在\n"
         "启用电子邮件通知时才有意义。\n"
         "(属性: \"selfreg-verify\")</p>\n");

  cgi_printf("<hr>\n");
  onoff_attribute("允许匿名订阅",
                  "anon-subscribe", "anonsub", 1, 0);
  cgi_printf("<p>如果禁用，电子邮件通知订阅仅允许\n"
         "具有登录账户的用户使用。如果匿名用户访问/subscribe\n"
         "页面，他们将被重定向到/register或/login。\n"
         "(属性: \"anon-subscribe\")</p>\n");

  cgi_printf("<hr>\n");
  entry_attribute("授权的订阅电子邮件地址", 35,
                  "auth-sub-email", "asemail", "", 0);
  cgi_printf("<p>这是一个逗号分隔的GLOB模式列表，指定\n"
         "有权订阅的电子邮件地址。如果为空\n"
        "（通常情况），则任何电子邮件地址都可用于自行注册。\n"
         "此设置用于基于电子邮件地址将订阅限制为特定\n"
         "组织或团体的成员。\n"
         "(属性: \"auth-sub-email\")</p>\n");

  cgi_printf("<hr>\n");
  entry_attribute("默认权限", 10, "default-perms",
                  "defaultperms", "u", 0);
  cgi_printf("<p>授予以下用户的权限：<ul><li>使用自行注册程序注册的用户（如果启用），或<li>访问由上述public-pages glob模式标识的\"公开\"\n"
         "页面的用户，或<li>\n"
         "由管理员新创建的用户。</ul>\n"
         "<p>推荐值：\"u\"表示只读权限。\n"
         "<a href=\"%R/setup_ucap_list\">权限密钥</a>。\n"
         "(属性: \"default-perms\")\n"
         "</p>\n");

  cgi_printf("<hr>\n");
  onoff_attribute("显示自动填写验证码的JavaScript按钮",
                  "auto-captcha", "autocaptcha", 0, 0);
  cgi_printf("<p>启用后，匿名用户的登录屏幕上会出现一个按钮，可自动填写验证码密码。\n"
         "这比强制用户手动填写安全性较低，但可能足够安全，并且对\n"
         "匿名用户来说肯定更方便。\n"
         "(属性: \"auto-captcha\")</p>\n");

  cgi_printf("<hr>\n");
  entry_attribute("匿名登录有效期", 11, "anon-cookie-lifespan",
                  "anoncookls", "840", 0);
  cgi_printf("<p>匿名登录Cookie有效的分钟数。\n"
         "设置为零可禁用匿名登录。\n"
         "(属性: anon-cookie-lifespan)\n");

  cgi_printf("<hr>\n"
         "<p><input type=\"submit\"  name=\"submit\" value=\"应用更改\"></p>\n"
         "</div></form>\n");
  db_end_transaction(0);
  style_finish_page();
}

/*
** WEBPAGE: setup_login_group
**
** Change how the current repository participates in a login
** group.
*/
void setup_login_group(void){
  const char *zGroup;
  char *zErrMsg = 0;
  Stmt q;
  Blob fullName;
  char *zSelfRepo;
  const char *zRepo = PD("repo", "");
  const char *zLogin = PD("login", "");
  const char *zPw = PD("pw", "");
  const char *zNewName = PD("newname", "New Login Group");

  login_check_credentials();
  if( !g.perm.Setup ){
    login_needed(0);
    return;
  }
  file_canonical_name(g.zRepositoryName, &fullName, 0);
  zSelfRepo = fossil_strdup(blob_str(&fullName));
  blob_reset(&fullName);
  if( P("join")!=0 ){
    login_group_join(zRepo, 1, zLogin, zPw, zNewName, &zErrMsg);
  }else if( P("leave") ){
    login_group_leave(&zErrMsg);
  }else if( P("rotate") ){
    captcha_secret_rotate();
  }
  style_set_current_feature("setup");
  style_header("Login Group Configuration");
  if( zErrMsg ){
    cgi_printf("<p class=\"generalError\">%s</p>\n",(zErrMsg));
  }
  zGroup = login_group_name();
  if( zGroup==0 ){
    cgi_printf("<p>This repository (in the file named \"%h\")\n"
           "is not currently part of any login-group.\n"
           "To join a login group, fill out the form below.</p>\n"
           "\n"
           "<form action=\"%R/setup_login_group\" method=\"post\"><div>\n",(zSelfRepo));
    login_insert_csrf_secret();
    cgi_printf("<blockquote><table border=\"0\">\n"
           "\n"
           "<tr><th align=\"right\" id=\"rfigtj\">Repository filename "
           "in group to join:</th>\n"
           "<td width=\"5\"></td><td>\n"
           "<input aria-labelledby=\"rfigtj\" type=\"text\" size=\"50\" "
           "value=\"%h\" name=\"repo\"></td></tr>\n"
           "\n"
           "<tr><th align=\"right\" id=\"lotar\">Login on the above repo:</th>\n"
           "<td width=\"5\"></td><td>\n"
           "<input aria-labelledby=\"lotar\" type=\"text\" size=\"20\" "
           "value=\"%h\" name=\"login\"></td></tr>\n"
           "\n"
           "<tr><th align=\"right\" id=\"lgpw\">Password:</th>\n"
           "<td width=\"5\"></td><td>\n"
           "<input aria-labelledby=\"lgpw\" type=\"password\" size=\"20\" name=\"pw\">"
           "</td></tr>\n"
           "\n"
           "<tr><th align=\"right\" id=\"nolg\">Name of login-group:</th>\n"
           "<td width=\"5\"></td><td>\n"
           "<input aria-labelledby=\"nolg\" type=\"text\" size=\"30\" "
           "value=\"%h\" name=\"newname\">\n"
           "(only used if creating a new login-group).</td></tr>\n"
           "\n"
           "<tr><td colspan=\"3\" align=\"center\">\n"
           "<input type=\"submit\" value=\"Join\" name=\"join\"></td></tr>\n"
           "</table></blockquote></div></form>\n",(zRepo),(zLogin),(zNewName));
  }else{
    int n = 0;
    cgi_printf("<p>This repository (in the file \"%h\")\n"
           "is currently part of the \"<b>%h</b>\" login group.\n"
           "Other repositories in that group are:</p>\n"
           "<table border=\"0\" cellspacing=\"4\">\n"
           "<tr><td colspan=\"2\"><th align=\"left\">Project Name<td>\n"
           "<th align=\"left\">Repository File</tr>\n",(zSelfRepo),(zGroup));
    db_prepare(&q,
       "SELECT value,"
       "       (SELECT value FROM config"
       "         WHERE name=('peer-name-' || substr(x.name,11)))"
       "  FROM config AS x"
       " WHERE name GLOB 'peer-repo-*'"
       " ORDER BY value"
    );
    while( db_step(&q)==SQLITE_ROW ){
      const char *zRepo = db_column_text(&q, 0);
      const char *zTitle = db_column_text(&q, 1);
      n++;
      cgi_printf("<tr><td align=\"right\">%d.</td><td width=\"4\">\n"
             "<td>%h<td width=\"10\"><td>%h</tr>\n",(n),(zTitle),(zRepo));
    }
    db_finalize(&q);
    cgi_printf("</table>\n"
           "\n"
           "<p><form action=\"%R/setup_login_group\" method=\"post\"><div>\n");
    login_insert_csrf_secret();
    cgi_printf("<p>To leave this login group press:\n"
           "<input type=\"submit\" value=\"Leave Login Group\" name=\"leave\">\n"
           "<p>Setting a common captcha-secret on all repositories in the login-group\n"
           "allows anonymous logins for one repository in the login group to be used\n"
           "by all other repositories of the group within the same domain.  Warning:\n"
           "If a captcha dialog was painted before setting the common captcha-secret\n"
           "and the \"Speak password for 'anonymous'\" button is pressed afterwards,\n"
           "the spoken text will be incorrect.\n"
           "<input type=\"submit\" name=\"rotate\" value=\"Set common captcha-secret\">\n"
           "</form></p>\n");
  }
  cgi_printf("<hr><h2>Implementation Details</h2>\n"
         "<p>The following are fields from the CONFIG table related to login-groups.\n"
         "</p>\n"
         "<table border='1' cellspacing=\"0\" cellpadding=\"4\""
         "class='sortable' data-column-types='ttt' data-init-sort='1'>\n"
         "<thead><tr>\n"
         "<th>Config.Name<th>Config.Value<th>Config.mtime</tr>\n"
         "</thead><tbody>\n");
  db_prepare(&q, "SELECT name, value, datetime(mtime,'unixepoch') FROM config"
                 " WHERE name GLOB 'peer-*'"
                 "    OR name GLOB 'project-*'"
                 "    OR name GLOB 'login-group-*'"
                 " ORDER BY name");
  while( db_step(&q)==SQLITE_ROW ){
    cgi_printf("<tr><td>%h</td>\n"
           "<td>%h</td>\n"
           "<td>%h</td></tr>\n",(db_column_text(&q,0)),(db_column_text(&q,1)),(db_column_text(&q,2)));
  }
  db_finalize(&q);
  cgi_printf("</tbody></table>\n"
         "<h2>Interpretation</h2>\n"
         "<ul>\n"
         "<li><p><b>login-group-code</b> &rarr;\n"
         "A random code assigned to each login-group.  The login-group-code is\n"
         "a unique identifier for the login-group.\n"
         "\n"
         "<li><p><b>login-group-name</b> &rarr;\n"
         "The human-readable name of the login-group.\n"
         "\n"
         "<li><p><b>project-code</b> &rarr;\n"
         "A random code assigned to each project.  The project-code is\n"
         "a unique identifier for the project.  Multiple repositories can share\n"
         "the same project-code.  When two or more repositories have the same\n"
         "project code, that mean those repositories are clones of each other.\n"
         "Repositories are only able to sync if they share the same project-code.\n"
         "\n"
         "<li><p><b>project-description</b> &rarr;\n"
         "A description of project in this repository.  This is a verbose form\n"
         "of project-name.  This description can be edited in the second entry\n"
         "box on the <a href=\"./setup_config\">Setup/Configuration page</a>.\n"
         "\n"
         "<li><p><b>project-name</b> &rarr;\n"
         "The human-readable name for the project.  The project-name can be\n"
         "modified in the first entry on the\n"
         "<a href=\"./setup_config\">Setup/Configuration page</a>.\n"
         "\n"
         "<li><p><b>peer-repo-<i>CODE</i></b> &rarr;\n"
         "<i>CODE</i> is 16-character prefix of the project-code for another\n"
         "repository that is part of the same login-group.  The value is the\n"
         "filename for the peer repository.\n"
         "\n"
         "<li><p><b>peer-name-<i>CODE</i></b> &rarr;\n"
         "<i>CODE</i> is 16-character prefix of the project-code for another\n"
         "repository that is part of the same login-group.  The value is\n"
         "project-name value for the other repository.\n"
         "</ul>\n");
  style_table_sorter();
  style_finish_page();
}

/*
** WEBPAGE: setup_timeline
**
** Edit administrative settings controlling the display of
** timelines.
*/
void setup_timeline(void){
  double tmDiff;
  char zTmDiff[20];
  static const char *const azTimeFormats[] = {
      "0", "时:分",
      "1", "时:分:秒",
      "2", "年-月-日 时:分",
      "3", "年月日 时:分",
      "4", "(关闭)"
  };
  login_check_credentials();
  if( !g.perm.Admin ){
    login_needed(0);
    return;
  }

  style_set_current_feature("setup");
  style_header("时间线显示偏好");
  db_begin_transaction();
  cgi_printf("<form action=\"%R/setup_timeline\" method=\"post\"><div>\n");
  login_insert_csrf_secret();
  cgi_printf("<p><input type=\"submit\"  name=\"submit\" value=\"应用更改\"></p>\n");

  cgi_printf("<hr>\n");
  onoff_attribute("时间线上的纯文本评论",
                  "timeline-plaintext", "tpt", 0, 0);
  cgi_printf("<p>在时间线显示中，签入评论将按字面显示，\n"
         "不进行任何 wiki 或 HTML 解释。使用 CSS 更改\n"
         "显示格式特性，如字体和换行行为。\n"
         "(属性: \"timeline-plaintext\")</p>\n");

  cgi_printf("<hr>\n");
  onoff_attribute("在第一个空行截断评论 (Git风格)",
                  "timeline-truncate-at-blank", "ttb", 0, 0);
  cgi_printf("<p>在时间线显示中，签入评论仅显示到\n"
         "第一个空行。这是在 Git 仓库中显示评论的传统方式\n"
         "(属性: \"timeline-truncate-at-blank\")</p>\n");

  cgi_printf("<hr>\n");
  onoff_attribute("在换行符处断开评论",
                  "timeline-hard-newlines", "thnl", 0, 0);
  cgi_printf("<p>在时间线显示中，签入评论中的换行符强制\n"
         "显示时换行。\n"
         "(属性: \"timeline-hard-newlines\")</p>\n");

  cgi_printf("<hr>\n");
  onoff_attribute("不调整用户选择的背景颜色",
                  "raw-bgcolor", "rbgc", 0, 0);
  cgi_printf("<p>Fossil 通常会尝试调整签入和分支上用户指定的背景颜色的饱和度和强度，以便\n"
         "前景文本在所有皮肤中都易于阅读。启用此设置\n"
         "可省略该调整，并完全使用用户指定的背景颜色。\n"
         "(属性: \"raw-bgcolor\")</p>\n");

  cgi_printf("<hr>\n");
  onoff_attribute("使用协调世界时 (UTC)",
                  "timeline-utc", "utc", 1, 0);
  cgi_printf("<p>显示 UTC 时间（有时也称为格林威治标准时间 (GMT) 或\n"
         "祖鲁时间）而不是本地时间。在此服务器上，本地时间当前\n");
  tmDiff = db_double(0.0, "SELECT julianday('now')");
  tmDiff = db_double(0.0,
        "SELECT (julianday(%.17g,'localtime')-julianday(%.17g))*24.0",
        tmDiff, tmDiff);
  sqlite3_snprintf(sizeof(zTmDiff), zTmDiff, "%.1f", tmDiff);
  if( strcmp(zTmDiff, "0.0")==0 ){
    cgi_printf("与 UTC 相同，因此此设置在显示中不会有任何区别。</p>\n");
  }else if( tmDiff<0.0 ){
    sqlite3_snprintf(sizeof(zTmDiff), zTmDiff, "%.1f", -tmDiff);
    cgi_printf("比 UTC 晚 %s 小时。</p>\n",(zTmDiff));
  }else{
    cgi_printf("比 UTC 早 %s 小时。</p>\n",(zTmDiff));
  }
  cgi_printf("<p>(属性: \"timeline-utc\")\n");

  cgi_printf("<hr>\n");
  multiple_choice_attribute("样式", "timeline-default-style",
            "tdss", "0", N_TIMELINE_VIEW_STYLE, timeline_view_styles);
  cgi_printf("<p>默认时间线查看样式，适用于用户未指定替代样式的情况。\n"
         "(属性: \"timeline-default-style\")</p>\n");

  cgi_printf("<hr>\n");
  entry_attribute("默认行数", 6, "timeline-default-length",
                  "tldl", "50", 0);
  cgi_printf("<p>在没有用户显示偏好 cookie 设置或显式 n= 查询参数的情况下，时间线上显示的最大行数。\n"
         "(属性: \"timeline-default-length\")</p>\n");

  cgi_printf("<hr>\n");
  multiple_choice_attribute("每项时间格式", "timeline-date-format",
            "tdf", "0", count(azTimeFormats)/2, azTimeFormats);
  cgi_printf("<p>如果选择了 \"HH:MM\" 或 \"HH:MM:SS\" 格式，那么每当日期更改时，日期将显示在单独的框中\n"
        "（使用 CSS 类 \"timelineDate\"）。使用 \"YYYY-MM-DD&nbsp;HH:MM\" 和 \"YYMMDD ...\" 格式时，\n"
         "每个时间线条目都使用 CSS 类 \"timelineTime\" 显示完整的日期和时间。\n"
         "(属性: \"timeline-date-format\")</p>\n");

  cgi_printf("<hr>\n");
  entry_attribute("最大时间线评论长度", 6,
                  "timeline-max-comment", "tmc", "0", 0);
  cgi_printf("<p>在时间线中显示的评论的最大长度。\n"
         "\"0\" 表示没有长度限制。\n"
         "(属性: \"timeline-max-comment\")</p>\n");

  cgi_printf("<hr>\n");
  entry_attribute("工具提示停留时间 (毫秒)", 6,
                  "timeline-dwelltime", "tdt", "100", 0);
  cgi_printf("<br>\n");
  entry_attribute("工具提示关闭时间 (毫秒)", 6,
                  "timeline-closetime", "tct", "250", 0);
  cgi_printf("<p><strong>停留时间</strong> 定义了鼠标指针在图表对象上方静止多长时间后才会显示工具提示。<br>\n"
         "<strong>关闭时间</strong> 定义了鼠标指针离开对象多长时间后工具提示会关闭。</p>\n"
         "<p>将 <strong>停留时间</strong> 设置为 \"0\" 可禁用工具提示。<br>\n"
         "将 <strong>关闭时间</strong> 设置为 \"0\" 可使工具提示保持可见，直到\n"
         "鼠标在其他位置点击。<p>\n"
         "<p>(属性: \"timeline-dwelltime\", \"timeline-closetime\")</p>\n");

  cgi_printf("<hr>\n");
  onoff_attribute("时间戳超链接到 /info",
                  "timeline-tslink-info", "ttlti", 0, 0);
  cgi_printf("<p>屏幕最左侧与每个时间线条目关联的时间戳上的超链接，通常指向另一个\n"
         "/timeline 页面，该页面在上下文中显示该条目。但是，如果启用此选项，\n"
         "该超链接将指向显示条目详细信息的 /info 页面。\n"
         "<p>/timeline 链接是默认值，因为在上下文中查看条目通常很有用，\n"
         "并且该链接在时间线上无法通过其他方式访问。/info 链接也可以通过\n"
         "双击时间线节点或点击右侧补充信息部分中 \"check-in:\" 后面的哈希值来访问。\n"
         "<p>(属性: \"timeline-tslink-info\")\n");

  cgi_printf("<hr>\n"
         "<p><input type=\"submit\"  name=\"submit\" value=\"应用更改\"></p>\n"
         "</div></form>\n");
  db_end_transaction(0);
  style_finish_page();
}

/*
** WEBPAGE: setup_settings
**
** Change or view miscellaneous settings.  Part of the
** /setup pages requiring Setup privileges.
*/
void setup_settings(void){
  int nSetting;
  int i;
  Setting const *pSet;
  int bIfChng = P("all")==0;
  const Setting *aSetting = setting_info(&nSetting);

  login_check_credentials();
  if( !g.perm.Setup ){
    login_needed(0);
    return;
  }

  style_set_current_feature("setup");
  style_header("设置");
  if(!g.repositoryOpen){
    /* Provide read-only access to versioned settings,
       but only if no repo file was explicitly provided. */
    db_open_local(0);
  }
  db_begin_transaction();
  if( bIfChng ){
    cgi_printf("<p>仅显示值与默认值不同的设置。\n"
           "点击上方的\"全部\"按钮可设置所有设置。\n");
  }
  cgi_printf("<p>标记为(v)的设置是\"可版本化\"的，会被命名为\n"
         "\"<tt>.fossil-settings/</tt><i>SETTING-NAME</i>\"的托管文件内容覆盖。\n"
         "如果可版本化设置的文件存在，则无法在此屏幕上更改其值。</p><hr><p>\n"
         "\n"
         "<form action=\"%R/setup_settings\" method=\"post\"><div>\n");
  if( bIfChng ){
    style_submenu_element("全部", "%R/setup_settings?all");
  }else{
    cgi_printf("<input type=\"hidden\" name=\"all\" value=\"1\">\n");
    style_submenu_element("仅显示变更", "%R/setup_settings");
  }
  cgi_printf("<table border=\"0\"><tr><td valign=\"top\">\n");
  login_insert_csrf_secret();
  for(i=0, pSet=aSetting; i<nSetting; i++, pSet++){
    if( pSet->width==0 ){
      int hasVersionableValue = pSet->versionable &&
          (db_get_versioned(pSet->name, NULL, NULL)!=0);
      if( bIfChng && setting_has_default_value(pSet, db_get(pSet->name,0)) ){
        continue;
      }
      onoff_attribute("", pSet->name,
                      pSet->var!=0 ? pSet->var : pSet->name /*works-like:"x"*/,
                      is_truth(pSet->def), hasVersionableValue);
      cgi_printf("<a href='%R/help?cmd=%s'>%h</a>\n",(pSet->name),(pSet->name));
      if( pSet->versionable ){
        cgi_printf(" (v)<br>\n");
      } else {
        cgi_printf("<br>\n");
      }
    }
  }
  cgi_printf("<br><input type=\"submit\"  name=\"submit\" value=\"应用更改\">\n"
         "</td><td style=\"width:50px;\"></td><td valign=\"top\">\n"
         "<table>\n");
  for(i=0, pSet=aSetting; i<nSetting; i++, pSet++){
    if( pSet->width>0 && !pSet->forceTextArea ){
      int hasVersionableValue = pSet->versionable &&
          (db_get_versioned(pSet->name, NULL, NULL)!=0);
      if( bIfChng && setting_has_default_value(pSet, db_get(pSet->name,0)) ){
        continue;
      }
      cgi_printf("<tr><td>\n"
             "<a href='%R/help?cmd=%s'>%h</a>\n",(pSet->name),(pSet->name));
      if( pSet->versionable ){
        cgi_printf(" (v)\n");
      } else {
        cgi_printf("\n");
      }
     cgi_printf("</td><td>\n");
      entry_attribute("", /*pSet->width*/ 25, pSet->name,
                      pSet->var!=0 ? pSet->var : pSet->name /*works-like:"x"*/,
                      (char*)pSet->def, hasVersionableValue);
     cgi_printf("</td></tr>\n");
    }
  }
 cgi_printf("</table>\n"
         "</td><td style=\"width:50px;\"></td><td valign=\"top\">\n");
  for(i=0, pSet=aSetting; i<nSetting; i++, pSet++){
    if( pSet->width>0 && pSet->forceTextArea ){
      int hasVersionableValue = db_get_versioned(pSet->name, NULL, NULL)!=0;
      if( bIfChng && setting_has_default_value(pSet, db_get(pSet->name,0)) ){
        continue;
      }
      cgi_printf("<a href='%R/help?cmd=%s'>%s</a>\n",(pSet->name),(pSet->name));
      if( pSet->versionable ){
        cgi_printf(" (v)<br>\n");
      } else {
        cgi_printf("<br>\n");
      }
      textarea_attribute("", /*rows*/ 2, /*cols*/ 35, pSet->name,
                      pSet->var!=0 ? pSet->var : pSet->name /*works-like:"x"*/,
                      (char*)pSet->def, hasVersionableValue);
     cgi_printf("<br>\n");
    }
  }
  cgi_printf("</td></tr></table>\n"
         "</div></form>\n");
  db_end_transaction(0);
  style_finish_page();
}

/*
** SETTING:  mainmenu          width=70 block-text keep-empty
**
** The mainmenu setting specifies the entries on the main menu
** for many skins.  The mainmenu should be a TCL list.  Each set
** of four consecutive values defines a single main menu item:
**
**   *   The first term is text that appears on the menu.
**
**   *   The second term is a hyperlink to take when a user clicks on the
**       entry.  Hyperlinks that start with "/" are relative to the
**       repository root.
**
**   *   The third term is an argument to the TH1 "capexpr" command.
**       If capexpr evaluates to true, then the entry is shown.  If not,
**       the entry is omitted.  "*" is always true.  "{}" is never true.
**
**   *   The fourth term is a list of extra class names to apply to the
**       new menu entry.  Some skins use classes "desktoponly" and
**       "wideonly" to only show the entries when the web browser
**       screen is wide or very wide, respectively.
**
** Some custom skins might not use this property.  Whether the property
** is used or not a choice made by the skin designer.  Some skins may add
** extra choices (such as the hamburger button) to the menu.
*/
/*
** SETTING: sitemap-extra      width=70 block-text
**
** The sitemap-extra setting defines extra links to appear on the
** /sitemap web page as sub-items of the "Home Page" entry before the
** "Documentation Search" entry (if any).  For skins that use the /sitemap
** page to construct a hamburger menu dropdown, new entries added here
** will appear on the hamburger menu.
**
** This setting should be a TCL list divided into triples.  Each
** triple defines a new entry:
**
**   *   The first term is the display name of the /sitemap entry
**
**   *   The second term is a hyperlink to take when a user clicks on the
**       entry.  Hyperlinks that start with "/" are relative to the
**       repository root.
**
**   *   The third term is an argument to the TH1 "capexpr" command.
**       If capexpr evaluates to true, then the entry is shown.  If not,
**       the entry is omitted.  "*" is always true.
**
** The default value is blank, meaning no added entries.
*/


/*
** WEBPAGE: setup_config
**
** The "Admin/Configuration" page.  Requires Setup privilege.
*/
void setup_config(void){
  login_check_credentials();
  if( !g.perm.Setup ){
    login_needed(0);
    return;
  }

  style_set_current_feature("setup");
  style_header("WWW 配置");
  db_begin_transaction();
  cgi_printf("<form action=\"%R/setup_config\" method=\"post\"><div>\n");
  login_insert_csrf_secret();
  cgi_printf("<input type=\"submit\"  name=\"submit\" value=\"应用更改\"></p>\n"
         "<hr>\n");
  entry_attribute("项目名称", 60, "project-name", "pn", "", 0);
  cgi_printf("<p>简短的项目名称，以便访问者了解本网站的内容。\n"
         "项目名称也将用作RSS feed标题。\n"
         "(属性: \"project-name\")\n"
         "</p>\n"
         "<hr>\n");
  textarea_attribute("项目描述", 3, 80,
                     "project-description", "pd", "", 0);
  cgi_printf("<p>描述您的项目。这将用于搜索引擎的页面标题、\n"
         "仓库列表和简短的RSS描述。\n"
         "(属性: \"project-description\")</p>\n"
         "<hr>\n");
  entry_attribute("规范服务器URL", 40, "email-url",
                   "eurl", "", 0);
  cgi_printf("<p>这是用于作为服务器访问此仓库的URL。\n"
         "其他仓库使用此URL来克隆或与此仓库同步。\n"
         "这也是电子邮件通知文本中包含的超链接的基础URL。\n"
         "请省略尾部的\"/\"。\n"
         "如果此仓库不会设置为持久服务器且不会发送电子邮件通知，\n"
         "则将此条目留空。\n"
         "建议值: \"%h\"\n"
         "(属性: \"email-url\")</p>\n"
         "<hr>\n",(g.zBaseURL));
  entry_attribute("Tarball和ZIP归档前缀", 20, "short-project-name",
                  "spn", "", 0);
  cgi_printf("<p>这用作生成的tarball和ZIP归档名称的前缀。为获得最佳效果，\n"
         "请保持此前缀简短，并避免使用特殊字符如\"/\"和\"\\\".\n"
         "如果未指定tarball前缀，则使用上面的完整项目名称。\n"
         "(属性: \"short-project-name\")\n"
         "</p>\n"
         "<hr>\n");
  entry_attribute("下载标签", 20, "download-tag", "dlt", "trunk", 0);
  cgi_printf("<p><a href='%R/download'>/download</a>页面旨在为新手提供方便的位置，\n"
         "以下载项目的ZIP归档或tarball。默认情况下，\n"
         "下载最新的trunk签入。将此标签更改为其他内容（例如：release）\n"
         "可以更改/download页面的行为。\n"
         "(属性: \"download-tag\")\n"
         "</p>\n"
         "<hr>\n");
  entry_attribute("索引页", 60, "index-page", "idxpg", "/home", 0);
  cgi_printf("<p>输入当选择\"主页\"菜单选项以及URL中未指定路径名时显示的页面路径名。\n"
         "例如，如果您访问以下URL：</p>\n"
         "\n"
         "<blockquote><p>%h</p></blockquote>\n"
         "\n"
         "<p>并且您已指定索引页为\"/home\"，上述URL将自动重定向到：</p>\n"
         "\n"
         "<blockquote><p>%h/home</p></blockquote>\n"
         "\n"
         "<p>默认的\"/home\"页面显示与上面指定的项目名称同名的Wiki页面。\n"
         "一些站点更喜欢重定向到文档页面（例如：\"/doc/trunk/index.wiki\"）或\"/timeline\"。</p>\n"
         "\n"
         "<p>注意：为避免重定向循环或其他问题，此条目必须以\"/\"开头，\n"
         "并且必须指定有效的页面。例如，\n"
         "\"<b>/home</b>\"将起作用，但\"<b>home</b>\"不会，因为它省略了前导的\"/\"。</p>\n"
         "<p>(属性: \"index-page\")\n"
         "<hr>\n"
         "<p>Web界面的主菜单\n"
         "<p>\n"
         "\n"
         "<p>此设置应为TCL列表。每组连续的四个值定义一个主菜单项：\n"
         "<ol>\n"
         "<li> 第一个项是显示在菜单上的文本。\n"
         "<li> 第二个项是当用户点击该条目时要跳转到的超链接。\n"
         "     以\"/\"开头的超链接相对于仓库根目录。\n"
         "<li> 第三个项是TH1 \"capexpr\"命令的参数。\n"
         "     如果capexpr求值为true，则显示该条目。否则，省略该条目。\n"
         "     \"*\"始终为true。\"{}\"始终为false。\n"
         "<li> 第四个项是应用于新菜单项的额外类名列表。\n"
         "     一些皮肤使用类\"desktoponly\"和\"wideonly\"分别仅在Web浏览器屏幕较宽或\n"
         "     非常宽时显示条目。\n"
         "</ol>\n"
         "\n"
         "<p>一些自定义皮肤可能不使用此属性。是否使用此属性是由皮肤设计师做出的选择。\n"
         "一些皮肤可能会向菜单中添加额外的选项（例如汉堡按钮），这些选项在此列表中未显示。\n"
         "(属性: mainmenu)\n"
         "<p>\n",(g.zBaseURL),(g.zBaseURL));
  if(P("resetMenu")!=0){
    db_unset("mainmenu", 0);
    cgi_delete_parameter("mmenu");
  }
  textarea_attribute("主菜单", 12, 80,
      "mainmenu", "mmenu", style_default_mainmenu(), 0);
  cgi_printf("</p>\n"
         "<p><input type='checkbox' id='cbResetMenu' name='resetMenu' value='1'>\n"
         "<label for='cbResetMenu'>将菜单重置为默认值</label>\n"
         "</p>\n"
         "<hr>\n"
         "<p>出现在<a href=\"%R/sitemap\">/sitemap</a>页面上的额外链接，\n"
         "作为\"主页\"条目的子项，出现在\"文档搜索\"条目（如果有）之前。\n"
         "在使用/sitemap页面构建汉堡菜单下拉菜单的皮肤中，\n"
         "此处添加的新条目将出现在汉堡菜单上。\n"
         "\n"
         "<p>此设置应为分为三元组的TCL列表。每个三元组定义一个新条目：\n"
         "<ol>\n"
         "<li> 第一个项是/sitemap条目的显示名称\n"
         "<li> 第二个项是当用户点击该条目时要跳转到的超链接。\n"
         "     以\"/\"开头的超链接相对于仓库根目录。\n"
         "<li> 第三个项是TH1 \"capexpr\"命令的参数。\n"
         "     如果capexpr求值为true，则显示该条目。否则，省略该条目。\n"
         "     \"*\"始终为true。\n"
         "</ol>\n"
         "\n"
         "<p>默认值为空，意味着没有添加的条目。\n"
         "(属性: sitemap-extra)\n"
         "<p>\n");
  textarea_attribute("自定义站点地图条目", 8, 80,
      "sitemap-extra", "smextra", "", 0);
  cgi_printf("<hr>\n"
         "<p><input type=\"submit\"  name=\"submit\" value=\"应用更改\"></p>\n"
         "</div></form>\n");
  db_end_transaction(0);
  style_finish_page();
}

/*
** WEBPAGE: setup_wiki
**
** The "Admin/Wiki" page.  Requires Setup privilege.
*/
void setup_wiki(void){
  login_check_credentials();
  if( !g.perm.Setup ){
    login_needed(0);
    return;
  }

  style_set_current_feature("setup");
  style_header("Wiki 配置");
  db_begin_transaction();
  cgi_printf("<form action=\"%R/setup_wiki\" method=\"post\"><div>\n");
  login_insert_csrf_secret();
  cgi_printf("<input type=\"submit\"  name=\"submit\" value=\"应用更改\"></p>\n"
         "<hr>\n");
  onoff_attribute("将Wiki页面与分支、标签、工单或签入关联",
                  "wiki-about", "wiki-about", 1, 0);
  cgi_printf("<p>\n"
         "根据Wiki页面名称将Wiki页面与分支、标签、工单或签入关联。当此功能启用时，以\"branch/\"、\"checkin/\"、\n"
         "\"tag/\"或\"ticket\"开头并后跟现有分支、签入、标签或工单名称的Wiki页面将被特殊处理。\n"
         "<ul>\n"
         "<li> <b>branch/</b><i>分支名称</i>\n"
         "<li> <b>checkin/</b><i>完整签入哈希值</i>\n"
         "<li> <b>tag/</b><i>标签名称</i>\n"
         "<li> <b>ticket/</b><i>完整工单哈希值</i>\n"
         "</ul>\n"
         "(属性: \"wiki-about\")</p>\n"
         "<hr>\n");
  entry_attribute("允许在Markdown中使用不安全HTML", 6,
                  "safe-html", "safe-html", "", 0);
  cgi_printf("<p>允许在<a href=\"%R/md_rules\">Markdown格式</a>文档中生成\"不安全\"HTML（例如：&lt;script&gt;、&lt;form&gt;等）。\n"
         "此设置是一个字符串，其中每个字符表示允许使用不安全HTML的文档\"类型\"：\n"
         "<ul>\n"
         "<li> <b>b</b> &rarr; 签入文件、嵌入式文档\n"
         "<li> <b>f</b> &rarr; 论坛帖子\n"
         "<li> <b>t</b> &rarr; 工单\n"
         "<li> <b>w</b> &rarr; Wiki页面\n"
         "</ul>\n"
         "为每种应允许不安全HTML的文档类型包含相应字母。例如，仅允许在签入文件中使用不安全HTML，\n"
         "请将此设置设为仅\"<b>b</b>\"。要允许在除论坛帖子外的任何地方使用不安全HTML，请将此设置设为\"<b>btw</b>\"。\n"
         "默认值为空字符串，表示Fossil从不允许Markdown文档生成不安全HTML。\n"
         "(属性: \"safe-html\")</p>\n"
         "<hr>\n"
         "当前的跨Wiki标签映射如下：\n");
  interwiki_append_map_table(cgi_output_blob());
  cgi_printf("<p>访问 <a href=\"./intermap\">%R/intermap</a> 了解详情或修改跨Wiki标签映射。\n"
         "<hr>\n");
  onoff_attribute("使用HTML作为Wiki标记语言",
    "wiki-use-html", "wiki-use-html", 0, 0);
  cgi_printf("<p>使用HTML作为Wiki标记语言。Wiki链接仍将被解析，\n"
         "但所有其他Wiki格式将被忽略。</p>\n"
         "<p><strong>警告：</strong>启用时，Wiki中将接受<i>所有</i>HTML标签和属性。\n"
         "不会进行任何清理。这意味着恶意用户很可能向您的Wiki注入危险的HTML、CSS和JavaScript代码。</p>\n"
         "<p>仅当Wiki编辑限于受信任用户时才应<strong>启用</strong>此功能。\n"
         "不应在可公开编辑的Wiki上使用此功能。</p>\n"
         "(属性: \"wiki-use-html\")\n"
         "<hr>\n"
         "<p><input type=\"submit\"  name=\"submit\" value=\"应用更改\"></p>\n"
         "</div></form>\n");
  db_end_transaction(0);
  style_finish_page();
}

/*
** WEBPAGE: setup_chat
**
** The "Admin/Chat" page.  Requires Setup privilege.
*/
void setup_chat(void){
  static const char *const azAlerts[] = {
    "alerts/plunk.wav",  "叮咚声",
    "alerts/bflat3.wav", "提示音1",
    "alerts/bflat2.wav", "提示音2",
    "alerts/bloop.wav",  "嘟嘟声",
  };

  login_check_credentials();
  if( !g.perm.Setup ){
    login_needed(0);
    return;
  }

  style_set_current_feature("setup");
  style_header("聊天配置");
  db_begin_transaction();
  cgi_printf("<form action=\"%R/setup_chat\" method=\"post\"><div>\n");
  login_insert_csrf_secret();
  cgi_printf("<input type=\"submit\"  name=\"submit\" value=\"应用更改\"></p>\n"
         "<hr>\n");
  entry_attribute("初始聊天历史记录大小", 10,
                  "chat-initial-history", "chatih", "50", 0);
  cgi_printf("<p>当/chat首次启动时，它会预加载最多此数量的历史消息。\n"
         "(属性: \"chat-initial-history\")</p>\n"
         "<hr>\n");
  entry_attribute("保留的历史消息最小数量", 10,
                  "chat-keep-count", "chatkc", "50", 0);
  cgi_printf("<p>聊天子系统会清理较旧的消息，但它将始终保留最近的N条消息，其中N是此设置的值。\n"
         "(属性: \"chat-keep-count\")</p>\n"
         "<hr>\n");
  entry_attribute("消息最大保留天数", 10,
                  "chat-keep-days", "chatkd", "7", 0);
  cgi_printf("<p>聊天消息在N天后被移除，其中N是此设置的值。N可以是小数。例如，若只想保留12小时的聊天历史记录，\n"
         "请将此值设置为0.5。\n"
         "(属性: \"chat-keep-days\")</p>\n"
         "<hr>\n");
  entry_attribute("聊天轮询超时时间", 10,
                  "chat-poll-timeout", "chatpt", "420", 0);
  cgi_printf("<p>新的聊天内容使用\"长轮询\"技术下载。系统向/chat-poll发送HTTP请求，该请求会阻塞等待新内容到达。\n"
         "但/chat-poll不能永远阻塞，最终必须放弃并返回空消息集。此设置决定/chat-poll在放弃前等待的时间。\n"
         "默认约7分钟的设置在许多系统上运行良好。使用代理或具有短超时的Web服务器的安装可能需要更短的延迟。\n"
         "为获得最佳效率，此值应尽可能大。\n"
         "(属性: \"chat-poll-timeout\")</p>\n"
         "<hr>\n");
  entry_attribute("聊天时间线机器人用户名", 15,
                  "chat-timeline-user", "chatrobot", "", 0);
  cgi_printf("<p>如果此设置不为空字符串，则时间线上出现的任何更改都会在聊天室中以提供的用户名进行公告。\n"
         "该用户名不需要实际存在于USER表中。\n"
         "建议的用户名: \"chat-robot\"。\n"
         "(属性: \"chat-timeline-user\")</p>\n"
         "<hr>\n");

  multiple_choice_attribute("提示音",
     "chat-alert-sound", "snd", azAlerts[0],
     count(azAlerts)/2, azAlerts);
  cgi_printf("<p>客户端聊天中用于指示新聊天消息到达的声音。\n"
         "(属性: \"chat-alert-sound\")</p>\n"
         "<hr/>\n"
         "<p><input type=\"submit\"  name=\"submit\" value=\"应用更改\"></p>\n"
         "</div></form>\n");
  db_end_transaction(0);
  cgi_printf("<script nonce=\"%h\">\n"
         "(function(){\n"
         "  var w = document.getElementById('idsnd');\n"
         "  w.onchange = function(){\n"
         "    var audio = new Audio('%s/builtin/' + w.value);\n"
         "    audio.currentTime = 0;\n"
         "    audio.play();\n"
         "  }\n"
         "})();\n"
         "</script>\n",(style_nonce()),(g.zBaseURL));
  style_finish_page();
}

/*
** WEBPAGE: setup_modreq
**
** Admin page for setting up moderation of tickets and wiki.
*/
void setup_modreq(void){
  login_check_credentials();
  if( !g.perm.Admin ){
    login_needed(0);
    return;
  }

  style_set_current_feature("setup");
  style_header("Wiki和工单审核设置");
  db_begin_transaction();
  cgi_printf("<form action=\"%R/setup_modreq\" method=\"post\"><div>\n");
  login_insert_csrf_secret();
  cgi_printf("<hr>\n");
  onoff_attribute("审核工单变更",
     "modreq-tkt", "modreq-tkt", 0, 0);
  cgi_printf("<p>启用后，任何工单变更都需要工单审核员的批准\n"
         "- 拥有\"q\"或Mod-Tkt权限的用户。\n"
         "工单变更会进入系统并在本地显示，但在获得批准前不会同步。\n"
         "审核员可以选择删除变更而不是批准它。\n"
         "拥有Mod-Tkt权限的用户所做的工单变更永远不受审核限制。\n"
         "(属性: \"modreq-tkt\")\n"
         "\n"
         "<hr>\n");
  onoff_attribute("审核Wiki变更",
     "modreq-wiki", "modreq-wiki", 0, 0);
  cgi_printf("<p>启用后，任何Wiki变更都需要Wiki审核员的批准\n"
         "- 拥有\"l\"或Mod-Wiki权限的用户。\n"
         "Wiki变更会进入系统并在本地显示，但在获得批准前不会同步。\n"
         "审核员可以选择删除变更而不是批准它。\n"
         "拥有Mod-Wiki权限的用户所做的Wiki变更永远不受审核限制。\n"
         "(属性: \"modreq-wiki\")\n"
         "</p>\n");

  cgi_printf("<hr>\n"
         "<p><input type=\"submit\"  name=\"submit\" value=\"应用更改\"></p>\n"
         "</div></form>\n");
  db_end_transaction(0);
  style_finish_page();

}

/*
** WEBPAGE: setup_adunit
**
** Administrative page for configuring and controlling ad units
** and how they are displayed.
*/
void setup_adunit(void){
  login_check_credentials();
  if( !g.perm.Admin ){
    login_needed(0);
    return;
  }
  db_begin_transaction();
  if( P("clear")!=0 && cgi_csrf_safe(2) ){
    db_unprotect(PROTECT_CONFIG);
    db_multi_exec("DELETE FROM config WHERE name GLOB 'adunit*'");
    db_protect_pop();
    cgi_replace_parameter("adunit","");
    cgi_replace_parameter("adright","");
    setup_incr_cfgcnt();
  }

  style_set_current_feature("setup");
  style_header("编辑广告单元");
  cgi_printf("<form action=\"%R/setup_adunit\" method=\"post\"><div>\n");
  login_insert_csrf_secret();
  cgi_printf("<b>横幅广告单元：</b><br>\n");
 textarea_attribute("", 6, 80, "adunit", "adunit", "", 0);
  cgi_printf("<br>\n"
         "<b>右侧栏广告单元：</b><br>\n");
  textarea_attribute("", 6, 80, "adunit-right", "adright", "", 0);
  cgi_printf("<br>\n");
  onoff_attribute("向管理员隐藏广告",
     "adunit-omit-if-admin", "oia", 0, 0);
  cgi_printf("<br>\n");
  onoff_attribute("向已登录用户隐藏广告",
     "adunit-omit-if-user", "oiu", 0, 0);
  cgi_printf("<br>\n");
  onoff_attribute("临时禁用所有广告",
     "adunit-disable", "oall", 0, 0);
  cgi_printf("<br>\n"
         "<input type=\"submit\" name=\"submit\" value=\"应用更改\">\n"
         "<input type=\"submit\" name=\"clear\" value=\"删除广告单元\">\n"
         "</div></form>\n"
         "<hr>\n"
         "<b>广告单元说明：</b><ul>\n"
         "<li>将两个广告单元都留空可禁用所有广告。\n"
         "<li>\"横幅广告单元\"用于宽页面。\n"
         "<li>\"右侧栏广告单元\"用于内容高而窄的页面。\n"
         "<li>如果\"右侧栏广告单元\"为空，则所有页面都使用\"横幅广告单元\"。\n"
         "<li>属性：\"adunit\"、\"adunit-right\"、\"adunit-omit-if-admin\"和\n"
         "    \"adunit-omit-if-user\"。\n"
         "<li>建议的 <a href=\"setup_skinedit?w=0\">CSS</a> 更改：\n"
         "<blockquote><pre>\n"
         "div.adunit_banner {\n"
         "  margin: auto;\n"
         "  width: 100%%;\n"
         "}\n"
         "div.adunit_right {\n"
         "  float: right;\n"
         "}\n"
         "div.adunit_right_container {\n"
         "  min-height: <i>右侧栏广告单元高度</i>;\n"
         "}\n"
         "</pre></blockquote>\n"
         "<li>如需测试用的占位广告单元，请复制粘贴以下内容，并适当调整\"width:\"和\"height:\"。\n"
         "<blockquote><pre>\n"
         "&lt;div style='\n"
         "  margin: 0 auto;\n"
         "  width: 600px;\n"
         "  height: 90px;\n"
         "  border: 1px solid #f11;\n"
         "  background-color: #fcc;\n"
         "'&gt;演示广告&lt;/div&gt;\n"
         "</pre></blockquote>\n"
         "</li>\n");
  style_finish_page();
  db_end_transaction(0);
}

/*
** WEBPAGE: setup_logo
**
** Administrative page for changing the logo, background, and icon images.
*/
void setup_logo(void){
  const char *zLogoMtime = db_get_mtime("logo-image", 0, 0);
  const char *zLogoMime = db_get("logo-mimetype","image/gif");
  const char *aLogoImg = P("logoim");
  int szLogoImg = atoi(PD("logoim:bytes","0"));
  const char *zBgMtime = db_get_mtime("background-image", 0, 0);
  const char *zBgMime = db_get("background-mimetype","image/gif");
  const char *aBgImg = P("bgim");
  int szBgImg = atoi(PD("bgim:bytes","0"));
  const char *zIconMtime = db_get_mtime("icon-image", 0, 0);
  const char *zIconMime = db_get("icon-mimetype","image/gif");
  const char *aIconImg = P("iconim");
  int szIconImg = atoi(PD("iconim:bytes","0"));
  if( szLogoImg>0 ){
    zLogoMime = PD("logoim:mimetype","image/gif");
  }
  if( szBgImg>0 ){
    zBgMime = PD("bgim:mimetype","image/gif");
  }
  if( szIconImg>0 ){
    zIconMime = PD("iconim:mimetype","image/gif");
  }
  login_check_credentials();
  if( !g.perm.Admin ){
    login_needed(0);
    return;
  }
  db_begin_transaction();
  if( !cgi_csrf_safe(2) ){
    /* Allow no state changes if not safe from CSRF */
  }else if( P("setlogo")!=0 && zLogoMime && zLogoMime[0] && szLogoImg>0 ){
    Blob img;
    Stmt ins;
    blob_init(&img, aLogoImg, szLogoImg);
    db_unprotect(PROTECT_CONFIG);
    db_prepare(&ins,
        "REPLACE INTO config(name,value,mtime)"
        " VALUES('logo-image',:bytes,now())"
    );
    db_bind_blob(&ins, ":bytes", &img);
    db_step(&ins);
    db_finalize(&ins);
    db_multi_exec(
       "REPLACE INTO config(name,value,mtime) VALUES('logo-mimetype',%Q,now())",
       zLogoMime
    );
    db_protect_pop();
    db_end_transaction(0);
    cgi_redirect("setup_logo");
  }else if( P("clrlogo")!=0 ){
    db_unprotect(PROTECT_CONFIG);
    db_multi_exec(
       "DELETE FROM config WHERE name IN "
           "('logo-image','logo-mimetype')"
    );
    db_protect_pop();
    db_end_transaction(0);
    cgi_redirect("setup_logo");
  }else if( P("setbg")!=0 && zBgMime && zBgMime[0] && szBgImg>0 ){
    Blob img;
    Stmt ins;
    blob_init(&img, aBgImg, szBgImg);
    db_unprotect(PROTECT_CONFIG);
    db_prepare(&ins,
        "REPLACE INTO config(name,value,mtime)"
        " VALUES('background-image',:bytes,now())"
    );
    db_bind_blob(&ins, ":bytes", &img);
    db_step(&ins);
    db_finalize(&ins);
    db_multi_exec(
       "REPLACE INTO config(name,value,mtime)"
       " VALUES('background-mimetype',%Q,now())",
       zBgMime
    );
    db_protect_pop();
    db_end_transaction(0);
    cgi_redirect("setup_logo");
  }else if( P("clrbg")!=0 ){
    db_unprotect(PROTECT_CONFIG);
    db_multi_exec(
       "DELETE FROM config WHERE name IN "
           "('background-image','background-mimetype')"
    );
    db_protect_pop();
    db_end_transaction(0);
    cgi_redirect("setup_logo");
  }else if( P("seticon")!=0 && zIconMime && zIconMime[0] && szIconImg>0 ){
    Blob img;
    Stmt ins;
    blob_init(&img, aIconImg, szIconImg);
    db_unprotect(PROTECT_CONFIG);
    db_prepare(&ins,
        "REPLACE INTO config(name,value,mtime)"
        " VALUES('icon-image',:bytes,now())"
    );
    db_bind_blob(&ins, ":bytes", &img);
    db_step(&ins);
    db_finalize(&ins);
    db_multi_exec(
       "REPLACE INTO config(name,value,mtime)"
       " VALUES('icon-mimetype',%Q,now())",
       zIconMime
    );
    db_protect_pop();
    db_end_transaction(0);
    cgi_redirect("setup_logo");
  }else if( P("clricon")!=0 ){
    db_unprotect(PROTECT_CONFIG);
    db_multi_exec(
       "DELETE FROM config WHERE name IN "
           "('icon-image','icon-mimetype')"
    );
    db_protect_pop();
    db_end_transaction(0);
    cgi_redirect("setup_logo");
  }
  style_set_current_feature("setup");
  style_header("编辑项目Logo和背景");
  cgi_printf("<p>当前项目Logo的MIME类型为 <b>%h</b>\n"
         "，显示如下：</p>\n"
         "<blockquote><p>\n"
         "<img src=\"%R/logo/%z\" alt=\"logo\" border=\"1\">\n"
         "</p></blockquote>\n"
         "\n"
         "<form action=\"%R/setup_logo\" method=\"post\"\n"
         " enctype=\"multipart/form-data\"><div>\n"
         "<p>所有用户都可以通过以下URL访问Logo：\n"
         "<a href=\"%s/logo\">%s/logo</a>。\n"
         "Logo是否在每个页面上显示，取决于\n"
         "<a href=\"setup_skinedit?w=0\">CSS</a>设置和\n"
         "<a href=\"setup_skinedit?w=2\">头部设置</a>。\n"
         "要更改Logo图像，请使用以下表单：</p>\n",(zLogoMime),(zLogoMtime),(g.zBaseURL),(g.zBaseURL));
  login_insert_csrf_secret();
  cgi_printf("Logo图像文件：\n"
         "<input type=\"file\" name=\"logoim\" size=\"60\" accept=\"image/*\">\n"
         "<p align=\"center\">\n"
         "<input type=\"submit\" name=\"setlogo\" value=\"更改Logo\">\n"
         "<input type=\"submit\" name=\"clrlogo\" value=\"恢复默认\"></p>\n"
         "<p>（属性：\"logo-image\" 和 \"logo-mimetype\"）\n"
         "</div></form>\n"
         "<hr>\n"
         "\n"
         "<p>当前背景图像的MIME类型为 <b>%h</b>\n"
         "，显示如下：</p>\n"
         "<blockquote><p><img src=\"%R/background/%z\" "
         "alt=\"background\" border=1>\n"
         "</p></blockquote>\n"
         "\n"
         "<form action=\"%R/setup_logo\" method=\"post\"\n"
         " enctype=\"multipart/form-data\"><div>\n"
         "<p>所有用户都可以通过以下URL访问背景图像：\n"
         "<a href=\"%s/background\">%s/background</a>。\n"
         "背景图像是否在每个页面上显示，取决于\n"
         "<a href=\"setup_skinedit?w=0\">CSS</a>设置和\n"
         "<a href=\"setup_skinedit?w=2\">头部设置</a>。\n"
         "要更改背景图像，请使用以下表单：</p>\n",(zBgMime),(zBgMtime),(g.zBaseURL),(g.zBaseURL));
  login_insert_csrf_secret();
  cgi_printf("背景图像文件：\n"
         "<input type=\"file\" name=\"bgim\" size=\"60\" accept=\"image/*\">\n"
         "<p align=\"center\">\n"
         "<input type=\"submit\" name=\"setbg\" value=\"更改背景\">\n"
         "<input type=\"submit\" name=\"clrbg\" value=\"恢复默认\"></p>\n"
         "</div></form>\n"
         "<p>（属性：\"background-image\" 和 \"background-mimetype\"）\n"
         "<hr>\n"
         "\n"
         "<p>当前图标图像的MIME类型为 <b>%h</b>\n"
         "，显示如下：</p>\n"
         "<blockquote><p><img src=\"%R/favicon.ico/%z\" "
         "alt=\"icon\" border=1>\n"
         "</p></blockquote>\n"
         "\n"
         "<form action=\"%R/setup_logo\" method=\"post\"\n"
         " enctype=\"multipart/form-data\"><div>\n"
         "<p>所有用户都可以通过以下URL访问图标图像：\n"
         "<a href=\"%s/favicon.ico\">%s/favicon.ico</a>。\n"
         "图标图像是否在每个页面上显示，取决于\n"
         "使用的Web浏览器以及它支持的图标图像MIME类型。\n"
         "要更改图标图像，请使用以下表单：</p>\n",(zIconMime),(zIconMtime),(g.zBaseURL),(g.zBaseURL));
  login_insert_csrf_secret();
  cgi_printf("图标图像文件：\n"
         "<input type=\"file\" name=\"iconim\" size=\"60\" accept=\"image/*\">\n"
         "<p align=\"center\">\n"
         "<input type=\"submit\" name=\"seticon\" value=\"更改图标\">\n"
         "<input type=\"submit\" name=\"clricon\" value=\"恢复默认\"></p>\n"
         "</div></form>\n"
         "<p>（属性：\"icon-image\" 和 \"icon-mimetype\"）\n"
         "<hr>\n"
         "\n"
         "<p><span class=\"note\">注意：</span> 您的浏览器可能已经缓存了这些\n"
         "图像，因此您可能需要按下重新加载按钮，才能使更改生效。</p>\n");
  style_finish_page();
  db_end_transaction(0);
}

/*
** Prevent the RAW SQL feature from being used to ATTACH a different
** database and query it.
**
** Actually, the RAW SQL feature only does a single statement per request.
** So it is not possible to ATTACH and then do a separate query.  This
** routine is not strictly necessary, therefore.  But it does not hurt
** to be paranoid.
*/
int raw_sql_query_authorizer(
  void *pError,
  int code,
  const char *zArg1,
  const char *zArg2,
  const char *zArg3,
  const char *zArg4
){
  if( code==SQLITE_ATTACH ){
    return SQLITE_DENY;
  }
  return SQLITE_OK;
}


/*
** WEBPAGE: admin_sql
**
** Run raw SQL commands against the database file using the web interface.
** Requires Setup privileges.
*/
void sql_page(void){
  const char *zQ;
  int go = P("go")!=0;
  login_check_credentials();
  if( !g.perm.Setup ){
    login_needed(0);
    return;
  }
  add_content_sql_commands(g.db);
  zQ = cgi_csrf_safe(2) ? P("q") : 0;
  style_set_current_feature("setup");
  style_header("Raw SQL Commands");
  cgi_printf("<p><b>Caution:</b> There are no restrictions on the SQL that can be\n"
         "run by this page.  You can do serious and irrepairable damage to the\n"
         "repository.  Proceed with extreme caution.</p>\n"
         "\n");
#if 0
  cgi_printf("<p>Only the first statement in the entry box will be run.\n"
         "Any subsequent statements will be silently ignored.</p>\n"
         "\n"
         "<p>Database names:<ul><li>repository\n");
  if( g.zConfigDbName ){
    cgi_printf("<li>configdb\n");
  }
  if( g.localOpen ){
    cgi_printf("<li>localdb\n");
  }
  cgi_printf("</ul></p>\n");
#endif

  if( P("configtab") ){
    /* If the user presses the "CONFIG Table Query" button, populate the
    ** query text with a pre-packaged query against the CONFIG table */
    zQ = "SELECT\n"
         " CASE WHEN length(name)<50 THEN name ELSE printf('%.50s...',name)"
         "  END AS name,\n"
         " CASE WHEN typeof(value)<>'blob' AND length(value)<80 THEN value\n"
         "           ELSE '...' END AS value,\n"
         " datetime(mtime, 'unixepoch') AS mtime\n"
         "FROM config\n"
         "-- ORDER BY mtime DESC; -- optional";
     go = 1;
  }
  cgi_printf("\n"
         "<form method=\"post\" action=\"%R/admin_sql\">\n");
  login_insert_csrf_secret();
  cgi_printf("SQL:<br>\n"
         "<textarea name=\"q\" rows=\"8\" cols=\"80\">%h</textarea><br>\n"
         "<input type=\"submit\" name=\"go\" value=\"Run SQL\">\n"
         "<input type=\"submit\" name=\"schema\" value=\"Show Schema\">\n"
         "<input type=\"submit\" name=\"tablelist\" value=\"List Tables\">\n"
         "<input type=\"submit\" name=\"configtab\" value=\"CONFIG Table Query\">\n"
         "</form>\n",(zQ));
  if( P("schema") ){
    zQ = sqlite3_mprintf(
            "SELECT sql FROM repository.sqlite_schema"
            " WHERE sql IS NOT NULL ORDER BY name");
    go = 1;
  }else if( P("tablelist") ){
    zQ = sqlite3_mprintf("SELECT*FROM pragma_table_list ORDER BY schema, name");
    go = 1;
  }
  if( go && cgi_csrf_safe(2) ){
    sqlite3_stmt *pStmt;
    int rc;
    const char *zTail;
    int nCol;
    int nRow = 0;
    int i;
    cgi_printf("<hr>\n");
    sqlite3_set_authorizer(g.db, raw_sql_query_authorizer, 0);
    search_sql_setup(g.db);
    rc = sqlite3_prepare_v2(g.db, zQ, -1, &pStmt, &zTail);
    if( rc!=SQLITE_OK ){
      cgi_printf("<div class=\"generalError\">%h</div>\n",(sqlite3_errmsg(g.db)));
      sqlite3_finalize(pStmt);
    }else if( pStmt==0 ){
      /* No-op */
    }else if( (nCol = sqlite3_column_count(pStmt))==0 ){
      sqlite3_step(pStmt);
      rc = sqlite3_finalize(pStmt);
      if( rc ){
        cgi_printf("<div class=\"generalError\">%h</div>\n",(sqlite3_errmsg(g.db)));
      }
    }else{
      cgi_printf("<table border=\"1\" cellpadding=\"4\" cellspacing=\"0\">\n");
      while( sqlite3_step(pStmt)==SQLITE_ROW ){
        if( nRow==0 ){
          cgi_printf("<tr>\n");
          for(i=0; i<nCol; i++){
            cgi_printf("<th>%h</th>\n",(sqlite3_column_name(pStmt, i)));
          }
          cgi_printf("</tr>\n");
        }
        nRow++;
        cgi_printf("<tr>\n");
        for(i=0; i<nCol; i++){
          switch( sqlite3_column_type(pStmt, i) ){
            case SQLITE_INTEGER:
            case SQLITE_FLOAT: {
               cgi_printf("<td align=\"right\" valign=\"top\">\n"
                      "%s</td>\n",(sqlite3_column_text(pStmt, i)));
               break;
            }
            case SQLITE_NULL: {
               cgi_printf("<td valign=\"top\" align=\"center\"><i>NULL</i></td>\n");
               break;
            }
            case SQLITE_TEXT: {
               const char *zText = (const char*)sqlite3_column_text(pStmt, i);
               cgi_printf("<td align=\"left\" valign=\"top\"\n"
                      "style=\"white-space:pre;\">%h</td>\n",(zText));
               break;
            }
            case SQLITE_BLOB: {
               cgi_printf("<td valign=\"top\" align=\"center\">\n"
                      "<i>%d-byte BLOB</i></td>\n",(sqlite3_column_bytes(pStmt, i)));
               break;
            }
          }
        }
        cgi_printf("</tr>\n");
      }
      sqlite3_finalize(pStmt);
      cgi_printf("</table>\n");
    }
  }
  style_finish_page();
}


/*
** WEBPAGE: admin_th1
**
** Run raw TH1 commands using the web interface.  If Tcl integration was
** enabled at compile-time and the "tcl" setting is enabled, Tcl commands
** may be run as well.  Requires Admin privilege.
*/
void th1_page(void){
  const char *zQ = P("q");
  int go = P("go")!=0;
  login_check_credentials();
  if( !g.perm.Setup ){
    login_needed(0);
    return;
  }
  style_set_current_feature("setup");
  style_header("原始TH1命令");
  cgi_printf("<p><b>警告：</b>本页面运行的TH1命令没有任何限制。如果编译时启用了Tcl集成，并且\"tcl\"设置已启用，还可以运行Tcl命令。</p>\n"
         "\n");
  form_begin(0, "%R/admin_th1");
  cgi_printf("TH1：<br>\n"
         "<textarea name=\"q\" rows=\"5\" cols=\"80\">%h</textarea><br>\n"
         "<input type=\"submit\" name=\"go\" value=\"运行TH1\">\n"
         "</form>\n",(zQ));
  if( go && cgi_csrf_safe(2) ){
    const char *zR;
    int rc;
    int n;
    cgi_printf("<hr>\n");
    rc = Th_Eval(g.interp, 0, zQ, -1);
    zR = Th_GetResult(g.interp, &n);
    if( rc==TH_OK ){
      cgi_printf("<pre class=\"th1result\">%h</pre>\n",(zR));
    }else{
      cgi_printf("<pre class=\"th1error\">%h</pre>\n",(zR));
    }
  }
  style_finish_page();
}

/*
** WEBPAGE: admin_log
**
** Shows the contents of the admin_log table, which is only created if
** the admin-log setting is enabled. Requires Admin or Setup ('a' or
** 's') permissions.
*/
void page_admin_log(){
  Stmt stLog;
  int limit;                 /* How many entries to show */
  int ofst;                  /* Offset to the first entry */
  int fLogEnabled;
  int counter = 0;
  login_check_credentials();
  if( !g.perm.Admin ){
    login_needed(0);
    return;
  }
  style_set_current_feature("setup");
  style_header("管理日志");
  style_submenu_element("日志菜单", "setup-logmenu");
  create_admin_log_table();
  limit = atoi(PD("n","200"));
  ofst = atoi(PD("x","0"));
  fLogEnabled = db_get_boolean("admin-log", 1);
  cgi_printf("<div>管理日志功能处于%s状态。\n"
         "可在<a href=\"setup_settings\">设置</a>页面更改此设置。</div>\n",(fLogEnabled?"开启":"关闭"));

  if( ofst>0 ){
    int prevx = ofst - limit;
    if( prevx<0 ) prevx = 0;
    cgi_printf("<p><a href=\"admin_log?n=%d&x=%d\">[较新]</a></p>\n",(limit),(prevx));
  }
  db_prepare(&stLog,
    "SELECT datetime(time,'unixepoch'), who, page, what "
    "FROM admin_log "
    "ORDER BY time DESC, rowid DESC");
  style_table_sorter();
  cgi_printf("<table class=\"sortable adminLogTable\" width=\"100%%\" "
         " data-column-types='Tttx' data-init-sort='1'>\n"
         "<thead>\n"
         "<th>时间</th>\n"
         "<th>用户</th>\n"
         "<th>页面</th>\n"
         "<th width=\"60%%\">消息</th>\n"
         "</thead><tbody>\n");
  while( SQLITE_ROW == db_step(&stLog) ){
    const char *zTime = db_column_text(&stLog, 0);
    const char *zUser = db_column_text(&stLog, 1);
    const char *zPage = db_column_text(&stLog, 2);
    const char *zMessage = db_column_text(&stLog, 3);
    counter++;
    if( counter<ofst ) continue;
    if( counter>ofst+limit ) break;
    cgi_printf("<tr class=\"row%d\">\n"
           "<td class=\"adminTime\">%s</td>\n"
           "<td>%s</td>\n"
           "<td>%s</td>\n"
           "<td>%h</td>\n"
           "</tr>\n",(counter%2),(zTime),(zUser),(zPage),(zMessage));
  }
  db_finalize(&stLog);
  cgi_printf("</tbody></table>\n");
  if( counter>ofst+limit ){
    cgi_printf("<p><a href=\"admin_log?n=%d&x=%d\">[较旧]</a></p>\n",(limit),(limit+ofst));
  }
  style_finish_page();
}


/*
** Renders a selection list of values for the search-tokenizer
** setting, using the form field name "ftstok".
*/
static void select_fts_tokenizer(void){
  const char *const aTokenizer[] = {
  "off",     "无",
  "porter",  "Porter词干提取器",
  "unicode61", "不使用词干提取的Unicode",
  "trigram", "三元组",
  };
  multiple_choice_attribute("FTS分词器", "search-tokenizer",
                            "ftstok", "off", 4, aTokenizer);
}

/*
** WEBPAGE: srchsetup
**
** Configure the search engine.  Requires Admin privilege.
*/
void page_srchsetup(){
  login_check_credentials();
  if( !g.perm.Admin ){
    login_needed(0);
    return;
  }
  style_set_current_feature("setup");
  style_header("搜索配置");
  cgi_printf("<form action=\"%R/srchsetup\" method=\"post\"><div>\n");
  login_insert_csrf_secret();
  cgi_printf("<div style=\"text-align:center;font-weight:bold;\">\n"
         "影响<a href=\"%R/search\">/search</a>网页的服务器特定设置。\n"
         "</div>\n"
         "<hr>\n");
  textarea_attribute("文档全局列表", 3, 35, "doc-glob", "dg", "", 0);
  cgi_printf("<p>\"文档全局列表\"是用逗号或换行符分隔的GLOB表达式列表，\n"
         "用于标识当\"文档搜索\"启用时，源代码树中所有需要搜索的文档。\n"
         "一些示例：\n"
         "<table border=0 cellpadding=2 align=center>\n"
         "<tr><td>*.wiki,*.html,*.md,*.txt<td style=\"width: 4x;\">\n"
         "<td>搜索所有wiki、HTML、Markdown和文本文件</tr>\n"
         "<tr><td>doc/*.md,*/README.txt,README.txt<td>\n"
         "<td>搜索doc/子文件夹中的所有Markdown文件和所有README.txt\n"
         "文件。</tr>\n"
         "<tr><td>*<td><td>搜索所有已签入文件</tr>\n"
         "<tr><td><i>(空白)</i><td>\n"
         "<td>不搜索任何内容。（禁用文档搜索）</tr>\n"
         "</table>\n"
         "<hr>\n");
  entry_attribute("文档分支", 20, "doc-branch", "db", "trunk", 0);
  cgi_printf("<p>搜索文档时，使用在\"文档分支\"分支类型中找到的文件版本。推荐值：\"trunk\"。\n"
         "如果为空则禁用文档搜索。可以是用空格和/或逗号分隔的分支名称列表。\n"
         "<hr>\n");
  onoff_attribute("搜索签入注释", "search-ci", "sc", 0, 0);
  cgi_printf("<br>\n");
  onoff_attribute("搜索文档", "search-doc", "sd", 0, 0);
  cgi_printf("<br>\n");
  onoff_attribute("搜索工单", "search-tkt", "st", 0, 0);
  cgi_printf("<br>\n");
  onoff_attribute("搜索Wiki", "search-wiki", "sw", 0, 0);
  cgi_printf("<br>\n");
  onoff_attribute("搜索技术笔记", "search-technote", "se", 0, 0);
  cgi_printf("<br>\n");
  onoff_attribute("搜索论坛", "search-forum", "sf", 0, 0);
  cgi_printf("<br>\n");
  onoff_attribute("搜索内置帮助文本", "search-help", "sh", 0, 0);
  cgi_printf("<hr>\n"
         "<p><input type=\"submit\"  name=\"submit\" value=\"应用更改\"></p>\n"
         "<hr>\n");
  if( P("fts0") ){
    search_drop_index();
  }else if( P("fts1") ){
    const char *zTokenizer = PD("ftstok","off");
    search_set_tokenizer(zTokenizer);
    search_drop_index();
    search_create_index();
    search_fill_index();
    search_update_index(search_restrict(SRCH_ALL));
  }
  if( search_index_exists() ){
    int pgsz = db_int64(0, "PRAGMA repository.page_size;");
    i64 nTotal = db_int64(0, "PRAGMA repository.page_count;")*pgsz;
    i64 nFts = db_int64(0, "SELECT count(*) FROM dbstat"
                               " WHERE schema='repository'"
                               " AND name LIKE 'fts%%'")*pgsz;
    char zSize[30];
    approxSizeName(sizeof(zSize),zSize,nFts);
    cgi_printf("<p>当前使用SQLite FTS%d搜索索引。\n"
           "该索引有助于加快搜索速度，特别是在大型代码仓库中，\n"
           "但会占用空间。索引当前使用约%s的空间，\n"
           "占代码仓库的%.1f%%。</p>\n",(search_index_type(0)),(zSize),(100.0*(double)nFts/(double)nTotal));
    select_fts_tokenizer();
    cgi_printf("<p><input type=\"submit\" name=\"fts0\" value=\"删除全文索引\">\n"
           "<input type=\"submit\" name=\"fts1\" value=\"重建全文索引\">\n");
    style_submenu_element("FTS索引调试","%R/test-ftsdocs");
  }else{
    cgi_printf("<p>SQLite搜索索引已禁用。所有搜索都将进行全文扫描。\n"
           "这通常可以正常工作，但对于大型代码仓库可能会很慢。</p>\n");
    select_fts_tokenizer();
    cgi_printf("<p><input type=\"submit\" name=\"fts1\" value=\"创建全文索引\">\n");
  }
  cgi_printf("</div></form>\n");
  style_finish_page();
}

/*
** A URL Alias originally called zOldName is now zNewName/zValue.
** Write SQL to make this change into pSql.
**
** If zNewName or zValue is an empty string, then delete the entry.
**
** If zOldName is an empty string, create a new entry.
*/
static void setup_update_url_alias(
  Blob *pSql,
  const char *zOldName,
  const char *zNewName,
  const char *zValue
){
  if( !cgi_csrf_safe(2) ) return;
  if( zNewName[0]==0 || zValue[0]==0 ){
    if( zOldName[0] ){
      blob_append_sql(pSql,
        "DELETE FROM config WHERE name='walias:%q';\n",
        zOldName);
    }
    return;
  }
  if( zOldName[0]==0 ){
    blob_append_sql(pSql,
      "INSERT INTO config(name,value,mtime) VALUES('walias:%q',%Q,now());\n",
      zNewName, zValue);
    return;
  }
  if( strcmp(zOldName, zNewName)!=0 ){
    blob_append_sql(pSql,
       "UPDATE config SET name='walias:%q', value=%Q, mtime=now()"
       " WHERE name='walias:%q';\n",
       zNewName, zValue, zOldName);
  }else{
    blob_append_sql(pSql,
       "UPDATE config SET value=%Q, mtime=now()"
       " WHERE name='walias:%q' AND value<>%Q;\n",
       zValue, zOldName, zValue);
  }
}

/*
** WEBPAGE: waliassetup
**
** Configure the URL aliases
*/
void page_waliassetup(){
  Stmt q;
  int cnt = 0;
  Blob namelist;
  login_check_credentials();
  if( !g.perm.Admin ){
    login_needed(0);
    return;
  }
  style_set_current_feature("setup");
  style_header("URL别名配置");

  if( P("submit")!=0 && cgi_csrf_safe(2) ){
    Blob token;
    Blob sql;
    const char *zNewName;
    const char *zValue;
    char zCnt[10];
    blob_init(&namelist, PD("namelist",""), -1);
    blob_init(&sql, 0, 0);
    while( blob_token(&namelist, &token) ){
      const char *zOldName = blob_str(&token);
      sqlite3_snprintf(sizeof(zCnt), zCnt, "n%d", cnt);
      zNewName = PD(zCnt, "");
      sqlite3_snprintf(sizeof(zCnt), zCnt, "v%d", cnt);
      zValue = PD(zCnt, "");
      setup_update_url_alias(&sql, zOldName, zNewName, zValue);
      cnt++;
      blob_reset(&token);
    }
    sqlite3_snprintf(sizeof(zCnt), zCnt, "n%d", cnt);
    zNewName = PD(zCnt,"");
    sqlite3_snprintf(sizeof(zCnt), zCnt, "v%d", cnt);
    zValue = PD(zCnt,"");
    setup_update_url_alias(&sql, "", zNewName, zValue);
    db_unprotect(PROTECT_CONFIG);
    db_multi_exec("%s", blob_sql_text(&sql));
    db_protect_pop();
    blob_reset(&sql);
    blob_reset(&namelist);
    cnt = 0;
  }
  db_prepare(&q,
      "SELECT substr(name,8), value FROM config WHERE name GLOB 'walias:/*'"
      " UNION ALL SELECT '', ''"
  );
  cgi_printf("<form action=\"%R/waliassetup\" method=\"post\"><div>\n");
  login_insert_csrf_secret();
  cgi_printf("<table border=0 cellpadding=5>\n"
         "<tr><th>别名<th>别名映射到的URI\n");
  blob_init(&namelist, 0, 0);
  while( db_step(&q)==SQLITE_ROW ){
    const char *zName = db_column_text(&q, 0);
    const char *zValue = db_column_text(&q, 1);
    cgi_printf("<tr><td>\n"
           "<input type='text' size='20' value='%h' name='n%d'>\n"
           "</td><td>\n"
           "<input type='text' size='80' value='%h' name='v%d'>\n"
           "</td></tr>\n",(zName),(cnt),(zValue),(cnt));
    cnt++;
    if( blob_size(&namelist)>0 ) blob_append(&namelist, " ", 1);
    blob_append(&namelist, zName, -1);
  }
  db_finalize(&q);
  cgi_printf("<tr><td>\n"
         "<input type='hidden' name='namelist' value='%h'>\n"
         "<input type='submit' name='submit' value=\"应用更改\">\n"
         "</td><td></td></tr>\n"
         "</table></form>\n"
         "<hr>\n"
         "<p>当传入URL的第一个部分与上方左侧(LHS)的\"别名\"完全匹配时，URL将转换为右侧(RHS)的相应形式。\n"
         "<ul>\n"
         "<li><p>\n"
         "左侧(LHS)仅与传入URL的第一个部分进行比较。因此，别名表中的所有左侧条目都应该以单个\"/\"开头，后跟单个路径元素。\n"
         "<li><p>\n"
         "别名表中的右侧(RHS)条目应该以单个\"/\"开头，后跟路径元素，可选地后跟\"?\"和查询参数列表。\n"
         "<li><p>\n"
         "右侧(RHS)的查询参数会添加到传入URL的查询参数集中。\n"
         "<li><p>\n"
         "如果相同的查询参数同时出现在传入URL和别名的右侧(RHS)，则右侧(RHS)的查询参数值会覆盖传入URL上的值。\n"
         "<li><p>\n"
         "如果别名右侧(RHS)的查询参数形式为\"X!\"（名称后跟\"!\"），则如果存在X查询参数，它将从传入URL中移除。\n"
         "<li><p>\n"
         "只发生单个别名操作。不可能嵌套别名。右侧(RHS)条目必须是内置网页名称。\n"
         "<li><p>\n"
         "只有当没有内置网页与传入URL匹配时，才会检查别名表。\n"
         "因此，无法使用别名覆盖内置网页。这是设计使然。\n"
         "</ul>\n"
         "\n"
         "<p>要从别名表中删除条目，请将其名称或值更改为空字符串，然后按\"应用更改\"。\n"
         "\n"
         "<p>要添加新别名，请在上面表格的最后一行填写名称和值，然后按\"应用更改\"。\n",(blob_str(&namelist)));
  style_finish_page();
}
