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
  @ <tr><td valign="top" align="right">
  if( zLink && zLink[0] ){
    @ <a href="%s(zLink)"><nobr>%h(zTitle)</nobr></a>
  }else{
    @ <nobr>%h(zTitle)</nobr>
  }
  @ </td><td width="5"></td><td valign="top">%s(zDesc)</td></tr>
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
  style_header("Server Administration");

  /* Make sure the header contains <base href="...">.   Issue a warning
  ** if it does not. */
  if( !cgi_header_contains("<base href=") ){
    @ <p class="generalError"><b>Configuration Error:</b> Please add
    @ <tt>&lt;base href="$secureurl/$current_page"&gt;</tt> after
    @ <tt>&lt;head&gt;</tt> in the
    @ <a href="setup_skinedit?w=2">HTML header</a>!</p>
  }

#if !defined(_WIN32)
  /* Check for /dev/null and /dev/urandom.  We want both devices to be present,
  ** but they are sometimes omitted (by mistake) from chroot jails. */
  if( access("/dev/null", R_OK|W_OK) ){
    @ <p class="generalError">WARNING: Device "/dev/null" is not available
    @ for reading and writing.</p>
  }
  if( access("/dev/urandom", R_OK) ){
    @ <p class="generalError">WARNING: Device "/dev/urandom" is not available
    @ for reading. This means that the pseudo-random number generator used
    @ by SQLite will be poorly seeded.</p>
  }
#endif

  @ <table border="0" cellspacing="3">
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
  @ </table>

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
  @ <table border="0" cellspacing="3">

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
    "A separate text file to which warning and error\n"
    "messages are appended.  A single error log can and often is shared\n"
    "across multiple repositories.\n"
  );
  if( g.zErrlog==0 || fossil_strcmp(g.zErrlog,"-")==0 ){
    blob_appendf(&desc,"<b>Disabled</b>: "
                       "To enable the error log ");
    if( fossil_strcmp(g.zCmdName, "cgi")==0 ){
      blob_appendf(&desc,
        "make an entry like \"errorlog: <i>FILENAME</i>\""
        " in the CGI script at %h",
        P("SCRIPT_FILENAME")
      );
    }else{
      blob_appendf(&desc,
        " add the \"--errorlog <i>FILENAME</i>\" option to the\n"
        "\"%h %h\" command that launched the server.",
        g.argv[0], g.zCmdName
      );
    }
    bErrLog = 0;
  }else{
    blob_appendf(&desc,"In this repository, the error log is the file "
       "named \"%s\".", g.zErrlog);
    bErrLog = 1;
  }
  setup_menu_entry("Error Log", bErrLog ? "errorlog" : 0, blob_str(&desc));
  blob_reset(&desc);

  @ </table>
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
  @ <label><input type="checkbox" name="%s(zQParm)" \
  @ aria-label="%h(zLabel[0]?zLabel:zQParm)" \
  if( iVal ){
    @ checked="checked" \
  }
  if( disabled ){
    @ disabled="disabled" \
  }
  @ > <b>%s(zLabel)</b></label>
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
  @ <input aria-label="%h(zLabel[0]?zLabel:zQParm)" type="text" \
  @ id="%s(zQParm)" name="%s(zQParm)" value="%h(zVal)" size="%d(width)" \
  if( disabled ){
    @ disabled="disabled" \
  }
  @ > <b>%s(zLabel)</b>
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
    @ <textarea id="id%s(zQP)" name="%s(zQP)" rows="%d(rows)" \
    @ aria-label="%h(zLabel[0]?zLabel:zQP)" \
    if( disabled ){
      @ disabled="disabled" \
    }
    @ cols="%d(cols)">%h(z)</textarea>
    if( *zLabel ){
      @ <span class="textareaLabel">%s(zLabel)</span>
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
  @ <select aria-label="%h(zLabel)" size="1" name="%s(zQP)" id="id%s(zQP)">
  for(i=0; i<nChoice*2; i+=2){
    const char *zSel = fossil_strcmp(azChoice[i],z)==0 ? " selected" : "";
    @ <option value="%h(azChoice[i])"%s(zSel)>%h(azChoice[i+1])</option>
  }
  @ </select> <b>%h(zLabel)</b>
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
  @ <br>
  entry_attribute("Delay in milliseconds before enabling hyperlinks", 5,
                  "auto-hyperlink-delay", "ah-delay", "50", 0);
  @ <br>
  onoff_attribute("Also require a mouse event before enabling hyperlinks",
                  "auto-hyperlink-mouseover", "ahmo", 0, 0);
  @ <p>Enable hyperlinks (the equivalent of the "h" permission) for all users,
  @ including user "nobody" if the request appears to be from a human.
  @ Disabling hyperlinks helps prevent robots from walking your site and
  @ soaking up all your CPU and bandwidth.
  @ If this setting is "UserAgent only" (2) then the
  @ UserAgent string is the only factor considered.  If the value of this
  @ setting is "UserAgent And Javascript" (1) then Javascript is added that
  @ runs after the page loads and fills in the href= values of &lt;a&gt;
  @ elements.  In either case, &lt;a&gt; tags are not generated if the
  @ UserAgent string indicates that the client is a robot.
  @ (Property: "auto-hyperlink")</p>
  @
  @ <p>For maximum robot defense, "Delay" should be at least 50 milliseconds
  @ and "require a mouse event" should be turned on.  These values only come
  @ into play when the main auto-hyperlink settings is 2 ("UserAgent and
  @ Javascript").
  @ (Properties: "auto-hyperlink-delay" and "auto-hyperlink-mouseover")</p>
  @
  @ <p>To see if Javascript-base hyperlink enabling mechanism is working,
  @ visit the <a href="%R/test-env">/test-env</a> page from a separate
  @ web browser that is not logged in, even as "anonymous" and verify
  @ that the "g.jsHref" value is "1".</p>
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
  @ <p>即使是一个适度的项目，Fossil网站的树结构中也可能有数以十亿计的页面。其中许多页面（例如：差异比较和压缩包）
  @ 可能需要大量计算资源。尝试遍历整个网站的机器人可能会造成严重的CPU和带宽负载。
  @
  @ <p>本页面的设置旨在帮助站点管理员保护站点免受机器人的影响。
  @
  @ <form action="%R/setup_robot" method="post"><div>
  login_insert_csrf_secret();
  @ <input type="submit"  name="submit" value="应用更改"></p>
  @ <hr>
  @ <p><b>不允许机器人访问这些页面。</b><br>
  @ 如果页面名称与此设置的GLOB模式匹配，且用户是"nobody"，且客户端之前未通过验证码
  @ 测试以证明它不是机器人，则不显示该页面。而是显示验证码测试。
  @ 此设置的推荐值为：
  @ <p>
  @ &emsp;&emsp;&emsp;<tt>%h(robot_restrict_default())</tt>
  @ <p>
  @ "diff"标签涵盖所有差异比较页面，如/vdiff、/fdiff和
  @ /vpatch。"annotate"标签涵盖/annotate以及/blame和
  @ /praise。"zip"涵盖自身以及/tarball和/sqlar。如果一个
  @ 标签后附加了"X"字符，则仅当查询参数使页面特别难以计算时才适用。
  @ 在所有其他情况下，标签应与页面名称完全匹配。
  @
  @ 要禁用机器人限制，请将此设置更改为"off"。
  @ (属性: robot-restrict)
  @ <br>
  textarea_attribute("", 2, 80,
      "robot-restrict", "rbrestrict", robot_restrict_default(), 0);

  @ <hr>
  @ <p><b>反机器人限制的例外情况</b><br>
  @ 下面的条目是一个正则表达式列表，每行一个。
  @ 如果这些正则表达式中的任何一个与输入URL匹配，则该
  @ 请求免受反机器人防御。例如，使用如下模式
  @ 允许脚本下载发布压缩包：</p>
  @ <p>
  @ &emsp;&emsp;<tt>^/tarball\b.*\b(version-|release)\b</tt>
  @ <p>该模式应匹配已删除SCRIPT_NAME前缀的REQUEST_URI，并在QUERY_STRING存在时
  @ 在其后附加"?"和QUERY_STRING。(属性: robot-exception)<br>
  textarea_attribute("", 3, 80,
      "robot-exception", "rbexcept", "", 0);

  @ <hr>
  addAutoHyperlinkSettings();

  @ <hr>
  entry_attribute("匿名登录有效期", 11, "anon-cookie-lifespan",
                  "anoncookls", "840", 0);
  @ <p>匿名登录Cookie的有效分钟数。
  @ 设置为零可禁用匿名登录。
  @ (属性: anon-cookie-lifespan)

  @ <hr>
  entry_attribute("服务器负载平均限制", 11, "max-loadavg", "mxldavg",
                  "0.0", 0);
  @ <p>如果主机计算机的负载平均值过大，则禁止某些昂贵的操作（如计算tarball、zip归档
  @ 或注释/归咎页面）。在此设置禁止昂贵计算的阈值。设置为0.0可禁用负载平均限制。
  @ 此限制仅在Unix服务器上强制执行。在Linux系统上，
  @ 需要访问/proc虚拟文件系统，这意味着此限制可能在chroot()监狱内不起作用。
  @ (属性: "max-loadavg")</p>
  @
  @ <hr>
  @ <p><input type="submit"  name="submit" value="应用更改"></p>
  @ </div></form>
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
  @ <form action="%R/setup_access" method="post"><div>
  login_insert_csrf_secret();
  @ <input type="submit"  name="submit" value="应用更改"></p>
  @ <hr>
  multiple_choice_attribute("重定向到HTTPS",
     "redirect-to-https", "redirhttps", "0",
     count(azRedirectOpts)/2, azRedirectOpts);
  @ <p>当接收到未加密请求时，通过重定向到HTTPS强制使用HTTPS。此功能可以仅对登录页面启用，或对所有页面启用。
  @ <p>进一步详情：启用此选项后，$secureurl TH1变量将被设置为$baseurl的"https:"变体。否则，
  @ $secureurl仅作为$baseurl的别名。
  @ (属性: "redirect-to-https"。"0"表示关闭，"1"表示仅登录页面，
  @ "2"表示所有页面。)
  @ <hr>
  onoff_attribute("本地访问需要密码",
     "localauth", "localauth", 0, 0);
  @ <p>启用后，Web访问始终需要密码登录。禁用时，当使用
  @ <a href="%R/help/ui">fossil ui</a>命令，或使用
  @ <a href="%R/help/server">fossil server</a>、
  @ <a href="%R/help/http">fossil http</a>命令并添加"--localauth"命令行选项时，
  @ 允许从127.0.0.1进行无限制的Web访问。如果CGI脚本中包含"localauth"关键字，
  @ 也允许从<a href="%R/help/cgi">fossil cgi</a>进行无限制访问。
  @ 
  @ <p>在以下任一情况下，始终需要密码：
  @ <ol>
  @ <li> 此按钮被勾选
  @ <li> 入站TCP/IP连接并非来自127.0.0.1
  @ <li> 服务器使用<a href="%R/help/server">fossil server</a>或
  @ <a href="%R/help/server">fossil http</a>命令启动，
  @ 但未使用"--localauth"选项。
  @ <li> 服务器从CGI启动，但CGI脚本中没有"localauth"关键字。
  @ </ol>
  @ (属性: "localauth")
  @
  @ <hr>
  onoff_attribute("启用 /test-env",
     "test_env_enable", "test_env_enable", 0, 0);
  @ <p>启用后，%h(g.zBaseURL)/test_env URL对所有用户可用。禁用时（默认），只有Admin和Setup用户可以访问
  @ /test_env页面。
  @ (属性: "test_env_enable")
  @ </p>
  @ 
  @ <hr>
  onoff_attribute("启用 /artifact_stats",
     "artifact_stats_enable", "artifact_stats_enable", 0, 0);
  @ <p>启用后，%h(g.zBaseURL)/artifact_stats URL对所有用户可用。禁用时（默认），只有具有签入权限的用户可以访问
  @ /artifact_stats页面。
  @ (属性: "artifact_stats_enable")
  @ </p>
  @
  @ <hr>
  onoff_attribute("允许REMOTE_USER认证",
     "remote_user_ok", "remote_user_ok", 0, 0);
  @ <p>启用后，如果REMOTE_USER环境变量设置为有效用户的登录名，且没有其他登录凭据可用，
  @ 则REMOTE_USER将被视为已认证用户。
  @ (属性: "remote_user_ok")
  @ </p>
  @ 
  @ <hr>
  onoff_attribute("允许HTTP_AUTHENTICATION认证",
     "http_authentication_ok", "http_authentication_ok", 0, 0);
  @ <p>启用后，允许使用HTTP_AUTHENTICATION环境变量或"Authentication:" HTTP头来查找用户名和
  @ 密码。这是支持Basic Authentication的另一种方式。
  @ (属性: "http_authentication_ok")
  @ </p>
  @
  @ <hr>
  entry_attribute("登录过期时间", 6, "cookie-expire", "cex",
                  "8766", 0);
  @ <p>登录有效的小时数。必须是正数。默认值为8766小时，约等于一年。
  @ (属性: "cookie-expire")</p>

  @ <hr>
  entry_attribute("下载数据包限制", 10, "max-download", "mxdwn",
                  "5000000", 0);
  @ <p>Fossil尝试将出站同步、克隆和拉取数据包限制为不压缩状态下的此字节数。如果客户端需要更多数据，
  @ 则客户端将发出多个HTTP请求。不建议将值设置为低于100万。500万是一个合理的数值。
  @ (属性: "max-download")</p>

  @ <hr>
  entry_attribute("下载时间限制", 11, "max-download-time", "mxdwnt",
                  "30", 0);

  @ <p>Fossil尝试在收集同步、克隆和拉取数据包的出站数据时花费少于此秒数。
  @ 如果客户端请求耗时更长，则会给出部分回复，类似于下载数据包限制。30秒是一个合理的默认值。
  @ (属性: "max-download-time")</p>

  @ <a id="slal"></a>
  @ <hr>
  entry_attribute("服务器负载平均限制", 11, "max-loadavg", "mxldavg",
                  "0.0", 0);
  @ <p>如果主机计算机的负载平均值过大，则禁止某些昂贵的操作（如计算tarball、zip归档
  @ 或注释/归咎页面）。在此设置禁止昂贵计算的阈值。设置为0.0可禁用负载平均限制。
  @ 此限制仅在Unix服务器上强制执行。在Linux系统上，
  @ 需要访问/proc虚拟文件系统，这意味着此限制可能在chroot()监狱内不起作用。
  @ (属性: "max-loadavg")</p>

  /* Add the auto-hyperlink settings controls.  These same controls
  ** are also accessible from the /setup_robot page.
  */
  @ <hr>
  addAutoHyperlinkSettings();

  @ <hr>
  onoff_attribute("未登录时需要验证码",
                  "require-captcha", "reqcapt", 1, 0);
  @ <p>对于未登录用户的编辑操作（追加、创建或编辑wiki或工单，或向wiki或工单添加附件）需要验证码。
  @ (属性: "require-captcha")</p>

  @ <hr>
  entry_attribute("公开页面", 30, "public-pages",
                  "pubpage", "", 0);
  @ <p>一组逗号分隔的glob模式，指定无需登录即可访问的页面，使用下方
  @ "默认权限"设置提供的权限。
  @
  @ <p>使用示例：将此字段设置为"/doc/trunk/www/*"，并将
  @ "默认权限"设置为包含"o"权限，
  @ 从而为匿名用户提供对www/文件夹中嵌入文档最新版本的只读权限，而不允许
  @ 他们查看源代码的其余部分。
  @ (属性: "public-pages")
  @ </p>

  @ <hr>
  onoff_attribute("允许用户自行注册",
                  "self-register", "selfreg", 0, 0);
  @ <p>允许用户在/register网页上自行注册。
  @ 自行注册会在USER表中创建一个新条目，
  @ 如果启用了电子邮件通知，可能还会在SUBSCRIBER表中创建一个条目。
  @ (属性: "self-register")</p>

  @ <hr>
  onoff_attribute("允许用户重置自己的密码",
                  "self-pw-reset", "selfpw", 0, 0);
  @ <p>允许用户请求发送包含指向密码重置页面的超链接的电子邮件到他们的记录邮箱地址。
  @ 这使健忘的用户能够在无需管理员干预的情况下恢复忘记的密码。
  @ (属性: "self-pw-reset")</p>

  @ <hr>
  onoff_attribute("自行注册需要电子邮件验证",
                  "selfreg-verify", "sfverify", 0, 0);
  @ <p>如果启用，自行注册会在USER表中创建一个新条目，
  @ 仅具有"7"权限。默认用户权限不会被添加，直到与自行注册相关联的
  @ 电子邮件地址已被验证。此设置仅在
  @ 启用电子邮件通知时才有意义。
  @ (属性: "selfreg-verify")</p>

  @ <hr>
  onoff_attribute("允许匿名订阅",
                  "anon-subscribe", "anonsub", 1, 0);
  @ <p>如果禁用，电子邮件通知订阅仅允许
  @ 具有登录账户的用户使用。如果匿名用户访问/subscribe
  @ 页面，他们将被重定向到/register或/login。
  @ (属性: "anon-subscribe")</p>

  @ <hr>
  entry_attribute("授权的订阅电子邮件地址", 35,
                  "auth-sub-email", "asemail", "", 0);
  @ <p>这是一个逗号分隔的GLOB模式列表，指定
  @ 有权订阅的电子邮件地址。如果为空
  @（通常情况），则任何电子邮件地址都可用于自行注册。
  @ 此设置用于基于电子邮件地址将订阅限制为特定
  @ 组织或团体的成员。
  @ (属性: "auth-sub-email")</p>

  @ <hr>
  entry_attribute("默认权限", 10, "default-perms",
                  "defaultperms", "u", 0);
  @ <p>授予以下用户的权限：<ul><li>使用自行注册程序注册的用户（如果启用），或<li>访问由上述public-pages glob模式标识的"公开"
  @ 页面的用户，或<li>
  @ 由管理员新创建的用户。</ul>
  @ <p>推荐值："u"表示只读权限。
  @ <a href="%R/setup_ucap_list">权限密钥</a>。
  @ (属性: "default-perms")
  @ </p>

  @ <hr>
  onoff_attribute("显示自动填写验证码的JavaScript按钮",
                  "auto-captcha", "autocaptcha", 0, 0);
  @ <p>启用后，匿名用户的登录屏幕上会出现一个按钮，可自动填写验证码密码。
  @ 这比强制用户手动填写安全性较低，但可能足够安全，并且对
  @ 匿名用户来说肯定更方便。
  @ (属性: "auto-captcha")</p>

  @ <hr>
  entry_attribute("匿名登录有效期", 11, "anon-cookie-lifespan",
                  "anoncookls", "840", 0);
  @ <p>匿名登录Cookie有效的分钟数。
  @ 设置为零可禁用匿名登录。
  @ (属性: anon-cookie-lifespan)

  @ <hr>
  @ <p><input type="submit"  name="submit" value="应用更改"></p>
  @ </div></form>
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
    @ <p class="generalError">%s(zErrMsg)</p>
  }
  zGroup = login_group_name();
  if( zGroup==0 ){
    @ <p>This repository (in the file named "%h(zSelfRepo)")
    @ is not currently part of any login-group.
    @ To join a login group, fill out the form below.</p>
    @
    @ <form action="%R/setup_login_group" method="post"><div>
    login_insert_csrf_secret();
    @ <blockquote><table border="0">
    @
    @ <tr><th align="right" id="rfigtj">Repository filename \
    @ in group to join:</th>
    @ <td width="5"></td><td>
    @ <input aria-labelledby="rfigtj" type="text" size="50" \
    @ value="%h(zRepo)" name="repo"></td></tr>
    @
    @ <tr><th align="right" id="lotar">Login on the above repo:</th>
    @ <td width="5"></td><td>
    @ <input aria-labelledby="lotar" type="text" size="20" \
    @ value="%h(zLogin)" name="login"></td></tr>
    @
    @ <tr><th align="right" id="lgpw">Password:</th>
    @ <td width="5"></td><td>
    @ <input aria-labelledby="lgpw" type="password" size="20" name="pw">\
    @ </td></tr>
    @
    @ <tr><th align="right" id="nolg">Name of login-group:</th>
    @ <td width="5"></td><td>
    @ <input aria-labelledby="nolg" type="text" size="30" \
    @ value="%h(zNewName)" name="newname">
    @ (only used if creating a new login-group).</td></tr>
    @
    @ <tr><td colspan="3" align="center">
    @ <input type="submit" value="Join" name="join"></td></tr>
    @ </table></blockquote></div></form>
  }else{
    int n = 0;
    @ <p>This repository (in the file "%h(zSelfRepo)")
    @ is currently part of the "<b>%h(zGroup)</b>" login group.
    @ Other repositories in that group are:</p>
    @ <table border="0" cellspacing="4">
    @ <tr><td colspan="2"><th align="left">Project Name<td>
    @ <th align="left">Repository File</tr>
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
      @ <tr><td align="right">%d(n).</td><td width="4">
      @ <td>%h(zTitle)<td width="10"><td>%h(zRepo)</tr>
    }
    db_finalize(&q);
    @ </table>
    @
    @ <p><form action="%R/setup_login_group" method="post"><div>
    login_insert_csrf_secret();
    @ <p>To leave this login group press:
    @ <input type="submit" value="Leave Login Group" name="leave">
    @ <p>Setting a common captcha-secret on all repositories in the login-group
    @ allows anonymous logins for one repository in the login group to be used
    @ by all other repositories of the group within the same domain.  Warning:
    @ If a captcha dialog was painted before setting the common captcha-secret
    @ and the "Speak password for 'anonymous'" button is pressed afterwards,
    @ the spoken text will be incorrect.
    @ <input type="submit" name="rotate" value="Set common captcha-secret">
    @ </form></p>
  }
  @ <hr><h2>Implementation Details</h2>
  @ <p>The following are fields from the CONFIG table related to login-groups.
  @ </p>
  @ <table border='1' cellspacing="0" cellpadding="4"\
  @ class='sortable' data-column-types='ttt' data-init-sort='1'>
  @ <thead><tr>
  @ <th>Config.Name<th>Config.Value<th>Config.mtime</tr>
  @ </thead><tbody>
  db_prepare(&q, "SELECT name, value, datetime(mtime,'unixepoch') FROM config"
                 " WHERE name GLOB 'peer-*'"
                 "    OR name GLOB 'project-*'"
                 "    OR name GLOB 'login-group-*'"
                 " ORDER BY name");
  while( db_step(&q)==SQLITE_ROW ){
    @ <tr><td>%h(db_column_text(&q,0))</td>
    @ <td>%h(db_column_text(&q,1))</td>
    @ <td>%h(db_column_text(&q,2))</td></tr>
  }
  db_finalize(&q);
  @ </tbody></table>
  @ <h2>Interpretation</h2>
  @ <ul>
  @ <li><p><b>login-group-code</b> &rarr;
  @ A random code assigned to each login-group.  The login-group-code is
  @ a unique identifier for the login-group.
  @
  @ <li><p><b>login-group-name</b> &rarr;
  @ The human-readable name of the login-group.
  @
  @ <li><p><b>project-code</b> &rarr;
  @ A random code assigned to each project.  The project-code is
  @ a unique identifier for the project.  Multiple repositories can share
  @ the same project-code.  When two or more repositories have the same
  @ project code, that mean those repositories are clones of each other.
  @ Repositories are only able to sync if they share the same project-code.
  @
  @ <li><p><b>project-description</b> &rarr;
  @ A description of project in this repository.  This is a verbose form
  @ of project-name.  This description can be edited in the second entry
  @ box on the <a href="./setup_config">Setup/Configuration page</a>.
  @
  @ <li><p><b>project-name</b> &rarr;
  @ The human-readable name for the project.  The project-name can be
  @ modified in the first entry on the
  @ <a href="./setup_config">Setup/Configuration page</a>.
  @
  @ <li><p><b>peer-repo-<i>CODE</i></b> &rarr;
  @ <i>CODE</i> is 16-character prefix of the project-code for another
  @ repository that is part of the same login-group.  The value is the
  @ filename for the peer repository.
  @
  @ <li><p><b>peer-name-<i>CODE</i></b> &rarr;
  @ <i>CODE</i> is 16-character prefix of the project-code for another
  @ repository that is part of the same login-group.  The value is
  @ project-name value for the other repository.
  @ </ul>
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
  @ <form action="%R/setup_timeline" method="post"><div>
  login_insert_csrf_secret();
  @ <p><input type="submit"  name="submit" value="应用更改"></p>

  @ <hr>
  onoff_attribute("时间线上的纯文本评论",
                  "timeline-plaintext", "tpt", 0, 0);
  @ <p>在时间线显示中，签入评论将按字面显示，
  @ 不进行任何 wiki 或 HTML 解释。使用 CSS 更改
  @ 显示格式特性，如字体和换行行为。
  @ (属性: "timeline-plaintext")</p>

  @ <hr>
  onoff_attribute("在第一个空行截断评论 (Git风格)",
                  "timeline-truncate-at-blank", "ttb", 0, 0);
  @ <p>在时间线显示中，签入评论仅显示到
  @ 第一个空行。这是在 Git 仓库中显示评论的传统方式
  @ (属性: "timeline-truncate-at-blank")</p>

  @ <hr>
  onoff_attribute("在换行符处断开评论",
                  "timeline-hard-newlines", "thnl", 0, 0);
  @ <p>在时间线显示中，签入评论中的换行符强制
  @ 显示时换行。
  @ (属性: "timeline-hard-newlines")</p>

  @ <hr>
  onoff_attribute("不调整用户选择的背景颜色",
                  "raw-bgcolor", "rbgc", 0, 0);
  @ <p>Fossil 通常会尝试调整签入和分支上用户指定的背景颜色的饱和度和强度，以便
  @ 前景文本在所有皮肤中都易于阅读。启用此设置
  @ 可省略该调整，并完全使用用户指定的背景颜色。
  @ (属性: "raw-bgcolor")</p>

  @ <hr>
  onoff_attribute("使用协调世界时 (UTC)",
                  "timeline-utc", "utc", 1, 0);
  @ <p>显示 UTC 时间（有时也称为格林威治标准时间 (GMT) 或
  @ 祖鲁时间）而不是本地时间。在此服务器上，本地时间当前
  tmDiff = db_double(0.0, "SELECT julianday('now')");
  tmDiff = db_double(0.0,
        "SELECT (julianday(%.17g,'localtime')-julianday(%.17g))*24.0",
        tmDiff, tmDiff);
  sqlite3_snprintf(sizeof(zTmDiff), zTmDiff, "%.1f", tmDiff);
  if( strcmp(zTmDiff, "0.0")==0 ){
    @ 与 UTC 相同，因此此设置在显示中不会有任何区别。</p>
  }else if( tmDiff<0.0 ){
    sqlite3_snprintf(sizeof(zTmDiff), zTmDiff, "%.1f", -tmDiff);
    @ 比 UTC 晚 %s(zTmDiff) 小时。</p>
  }else{
    @ 比 UTC 早 %s(zTmDiff) 小时。</p>
  }
  @ <p>(属性: "timeline-utc")

  @ <hr>
  multiple_choice_attribute("样式", "timeline-default-style",
            "tdss", "0", N_TIMELINE_VIEW_STYLE, timeline_view_styles);
  @ <p>默认时间线查看样式，适用于用户未指定替代样式的情况。
  @ (属性: "timeline-default-style")</p>

  @ <hr>
  entry_attribute("默认行数", 6, "timeline-default-length",
                  "tldl", "50", 0);
  @ <p>在没有用户显示偏好 cookie 设置或显式 n= 查询参数的情况下，时间线上显示的最大行数。
  @ (属性: "timeline-default-length")</p>

  @ <hr>
  multiple_choice_attribute("每项时间格式", "timeline-date-format",
            "tdf", "0", count(azTimeFormats)/2, azTimeFormats);
  @ <p>如果选择了 "HH:MM" 或 "HH:MM:SS" 格式，那么每当日期更改时，日期将显示在单独的框中
  @（使用 CSS 类 "timelineDate"）。使用 "YYYY-MM-DD&nbsp;HH:MM" 和 "YYMMDD ..." 格式时，
  @ 每个时间线条目都使用 CSS 类 "timelineTime" 显示完整的日期和时间。
  @ (属性: "timeline-date-format")</p>

  @ <hr>
  entry_attribute("最大时间线评论长度", 6,
                  "timeline-max-comment", "tmc", "0", 0);
  @ <p>在时间线中显示的评论的最大长度。
  @ "0" 表示没有长度限制。
  @ (属性: "timeline-max-comment")</p>

  @ <hr>
  entry_attribute("工具提示停留时间 (毫秒)", 6,
                  "timeline-dwelltime", "tdt", "100", 0);
  @ <br>
  entry_attribute("工具提示关闭时间 (毫秒)", 6,
                  "timeline-closetime", "tct", "250", 0);
  @ <p><strong>停留时间</strong> 定义了鼠标指针在图表对象上方静止多长时间后才会显示工具提示。<br>
  @ <strong>关闭时间</strong> 定义了鼠标指针离开对象多长时间后工具提示会关闭。</p>
  @ <p>将 <strong>停留时间</strong> 设置为 "0" 可禁用工具提示。<br>
  @ 将 <strong>关闭时间</strong> 设置为 "0" 可使工具提示保持可见，直到
  @ 鼠标在其他位置点击。<p>
  @ <p>(属性: "timeline-dwelltime", "timeline-closetime")</p>

  @ <hr>
  onoff_attribute("时间戳超链接到 /info",
                  "timeline-tslink-info", "ttlti", 0, 0);
  @ <p>屏幕最左侧与每个时间线条目关联的时间戳上的超链接，通常指向另一个
  @ /timeline 页面，该页面在上下文中显示该条目。但是，如果启用此选项，
  @ 该超链接将指向显示条目详细信息的 /info 页面。
  @ <p>/timeline 链接是默认值，因为在上下文中查看条目通常很有用，
  @ 并且该链接在时间线上无法通过其他方式访问。/info 链接也可以通过
  @ 双击时间线节点或点击右侧补充信息部分中 "check-in:" 后面的哈希值来访问。
  @ <p>(属性: "timeline-tslink-info")

  @ <hr>
  @ <p><input type="submit"  name="submit" value="应用更改"></p>
  @ </div></form>
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
    @ <p>仅显示值与默认值不同的设置。
    @ 点击上方的"全部"按钮可设置所有设置。
  }
  @ <p>标记为(v)的设置是"可版本化"的，会被命名为
  @ "<tt>.fossil-settings/</tt><i>SETTING-NAME</i>"的托管文件内容覆盖。
  @ 如果可版本化设置的文件存在，则无法在此屏幕上更改其值。</p><hr><p>
  @
  @ <form action="%R/setup_settings" method="post"><div>
  if( bIfChng ){
    style_submenu_element("全部", "%R/setup_settings?all");
  }else{
    @ <input type="hidden" name="all" value="1">
    style_submenu_element("仅显示变更", "%R/setup_settings");
  }
  @ <table border="0"><tr><td valign="top">
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
      @ <a href='%R/help?cmd=%s(pSet->name)'>%h(pSet->name)</a>
      if( pSet->versionable ){
        @  (v)<br>
      } else {
        @ <br>
      }
    }
  }
  @ <br><input type="submit"  name="submit" value="应用更改">
  @ </td><td style="width:50px;"></td><td valign="top">
  @ <table>
  for(i=0, pSet=aSetting; i<nSetting; i++, pSet++){
    if( pSet->width>0 && !pSet->forceTextArea ){
      int hasVersionableValue = pSet->versionable &&
          (db_get_versioned(pSet->name, NULL, NULL)!=0);
      if( bIfChng && setting_has_default_value(pSet, db_get(pSet->name,0)) ){
        continue;
      }
      @ <tr><td>
      @ <a href='%R/help?cmd=%s(pSet->name)'>%h(pSet->name)</a>
      if( pSet->versionable ){
        @  (v)
      } else {
        @
      }
      @</td><td>
      entry_attribute("", /*pSet->width*/ 25, pSet->name,
                      pSet->var!=0 ? pSet->var : pSet->name /*works-like:"x"*/,
                      (char*)pSet->def, hasVersionableValue);
      @</td></tr>
    }
  }
  @</table>
  @ </td><td style="width:50px;"></td><td valign="top">
  for(i=0, pSet=aSetting; i<nSetting; i++, pSet++){
    if( pSet->width>0 && pSet->forceTextArea ){
      int hasVersionableValue = db_get_versioned(pSet->name, NULL, NULL)!=0;
      if( bIfChng && setting_has_default_value(pSet, db_get(pSet->name,0)) ){
        continue;
      }
      @ <a href='%R/help?cmd=%s(pSet->name)'>%s(pSet->name)</a>
      if( pSet->versionable ){
        @  (v)<br>
      } else {
        @ <br>
      }
      textarea_attribute("", /*rows*/ 2, /*cols*/ 35, pSet->name,
                      pSet->var!=0 ? pSet->var : pSet->name /*works-like:"x"*/,
                      (char*)pSet->def, hasVersionableValue);
      @<br>
    }
  }
  @ </td></tr></table>
  @ </div></form>
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
  @ <form action="%R/setup_config" method="post"><div>
  login_insert_csrf_secret();
  @ <input type="submit"  name="submit" value="应用更改"></p>
  @ <hr>
  entry_attribute("项目名称", 60, "project-name", "pn", "", 0);
  @ <p>简短的项目名称，以便访问者了解本网站的内容。
  @ 项目名称也将用作RSS feed标题。
  @ (属性: "project-name")
  @ </p>
  @ <hr>
  textarea_attribute("项目描述", 3, 80,
                     "project-description", "pd", "", 0);
  @ <p>描述您的项目。这将用于搜索引擎的页面标题、
  @ 仓库列表和简短的RSS描述。
  @ (属性: "project-description")</p>
  @ <hr>
  entry_attribute("规范服务器URL", 40, "email-url",
                   "eurl", "", 0);
  @ <p>这是用于作为服务器访问此仓库的URL。
  @ 其他仓库使用此URL来克隆或与此仓库同步。
  @ 这也是电子邮件通知文本中包含的超链接的基础URL。
  @ 请省略尾部的"/"。
  @ 如果此仓库不会设置为持久服务器且不会发送电子邮件通知，
  @ 则将此条目留空。
  @ 建议值: "%h(g.zBaseURL)"
  @ (属性: "email-url")</p>
  @ <hr>
  entry_attribute("Tarball和ZIP归档前缀", 20, "short-project-name",
                  "spn", "", 0);
  @ <p>这用作生成的tarball和ZIP归档名称的前缀。为获得最佳效果，
  @ 请保持此前缀简短，并避免使用特殊字符如"/"和"\".
  @ 如果未指定tarball前缀，则使用上面的完整项目名称。
  @ (属性: "short-project-name")
  @ </p>
  @ <hr>
  entry_attribute("下载标签", 20, "download-tag", "dlt", "trunk", 0);
  @ <p><a href='%R/download'>/download</a>页面旨在为新手提供方便的位置，
  @ 以下载项目的ZIP归档或tarball。默认情况下，
  @ 下载最新的trunk签入。将此标签更改为其他内容（例如：release）
  @ 可以更改/download页面的行为。
  @ (属性: "download-tag")
  @ </p>
  @ <hr>
  entry_attribute("索引页", 60, "index-page", "idxpg", "/home", 0);
  @ <p>输入当选择"主页"菜单选项以及URL中未指定路径名时显示的页面路径名。
  @ 例如，如果您访问以下URL：</p>
  @
  @ <blockquote><p>%h(g.zBaseURL)</p></blockquote>
  @
  @ <p>并且您已指定索引页为"/home"，上述URL将自动重定向到：</p>
  @
  @ <blockquote><p>%h(g.zBaseURL)/home</p></blockquote>
  @
  @ <p>默认的"/home"页面显示与上面指定的项目名称同名的Wiki页面。
  @ 一些站点更喜欢重定向到文档页面（例如："/doc/trunk/index.wiki"）或"/timeline"。</p>
  @
  @ <p>注意：为避免重定向循环或其他问题，此条目必须以"/"开头，
  @ 并且必须指定有效的页面。例如，
  @ "<b>/home</b>"将起作用，但"<b>home</b>"不会，因为它省略了前导的"/"。</p>
  @ <p>(属性: "index-page")
  @ <hr>
  @ <p>Web界面的主菜单
  @ <p>
  @
  @ <p>此设置应为TCL列表。每组连续的四个值定义一个主菜单项：
  @ <ol>
  @ <li> 第一个项是显示在菜单上的文本。
  @ <li> 第二个项是当用户点击该条目时要跳转到的超链接。
  @      以"/"开头的超链接相对于仓库根目录。
  @ <li> 第三个项是TH1 "capexpr"命令的参数。
  @      如果capexpr求值为true，则显示该条目。否则，省略该条目。
  @      "*"始终为true。"{}"始终为false。
  @ <li> 第四个项是应用于新菜单项的额外类名列表。
  @      一些皮肤使用类"desktoponly"和"wideonly"分别仅在Web浏览器屏幕较宽或
  @      非常宽时显示条目。
  @ </ol>
  @
  @ <p>一些自定义皮肤可能不使用此属性。是否使用此属性是由皮肤设计师做出的选择。
  @ 一些皮肤可能会向菜单中添加额外的选项（例如汉堡按钮），这些选项在此列表中未显示。
  @ (属性: mainmenu)
  @ <p>
  if(P("resetMenu")!=0){
    db_unset("mainmenu", 0);
    cgi_delete_parameter("mmenu");
  }
  textarea_attribute("主菜单", 12, 80,
      "mainmenu", "mmenu", style_default_mainmenu(), 0);
  @ </p>
  @ <p><input type='checkbox' id='cbResetMenu' name='resetMenu' value='1'>
  @ <label for='cbResetMenu'>将菜单重置为默认值</label>
  @ </p>
  @ <hr>
  @ <p>出现在<a href="%R/sitemap">/sitemap</a>页面上的额外链接，
  @ 作为"主页"条目的子项，出现在"文档搜索"条目（如果有）之前。
  @ 在使用/sitemap页面构建汉堡菜单下拉菜单的皮肤中，
  @ 此处添加的新条目将出现在汉堡菜单上。
  @
  @ <p>此设置应为分为三元组的TCL列表。每个三元组定义一个新条目：
  @ <ol>
  @ <li> 第一个项是/sitemap条目的显示名称
  @ <li> 第二个项是当用户点击该条目时要跳转到的超链接。
  @      以"/"开头的超链接相对于仓库根目录。
  @ <li> 第三个项是TH1 "capexpr"命令的参数。
  @      如果capexpr求值为true，则显示该条目。否则，省略该条目。
  @      "*"始终为true。
  @ </ol>
  @
  @ <p>默认值为空，意味着没有添加的条目。
  @ (属性: sitemap-extra)
  @ <p>
  textarea_attribute("自定义站点地图条目", 8, 80,
      "sitemap-extra", "smextra", "", 0);
  @ <hr>
  @ <p><input type="submit"  name="submit" value="应用更改"></p>
  @ </div></form>
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
  @ <form action="%R/setup_wiki" method="post"><div>
  login_insert_csrf_secret();
  @ <input type="submit"  name="submit" value="应用更改"></p>
  @ <hr>
  onoff_attribute("将Wiki页面与分支、标签、工单或签入关联",
                  "wiki-about", "wiki-about", 1, 0);
  @ <p>
  @ 根据Wiki页面名称将Wiki页面与分支、标签、工单或签入关联。当此功能启用时，以"branch/"、"checkin/"、
  @ "tag/"或"ticket"开头并后跟现有分支、签入、标签或工单名称的Wiki页面将被特殊处理。
  @ <ul>
  @ <li> <b>branch/</b><i>分支名称</i>
  @ <li> <b>checkin/</b><i>完整签入哈希值</i>
  @ <li> <b>tag/</b><i>标签名称</i>
  @ <li> <b>ticket/</b><i>完整工单哈希值</i>
  @ </ul>
  @ (属性: "wiki-about")</p>
  @ <hr>
  entry_attribute("允许在Markdown中使用不安全HTML", 6,
                  "safe-html", "safe-html", "", 0);
  @ <p>允许在<a href="%R/md_rules">Markdown格式</a>文档中生成"不安全"HTML（例如：&lt;script&gt;、&lt;form&gt;等）。
  @ 此设置是一个字符串，其中每个字符表示允许使用不安全HTML的文档"类型"：
  @ <ul>
  @ <li> <b>b</b> &rarr; 签入文件、嵌入式文档
  @ <li> <b>f</b> &rarr; 论坛帖子
  @ <li> <b>t</b> &rarr; 工单
  @ <li> <b>w</b> &rarr; Wiki页面
  @ </ul>
  @ 为每种应允许不安全HTML的文档类型包含相应字母。例如，仅允许在签入文件中使用不安全HTML，
  @ 请将此设置设为仅"<b>b</b>"。要允许在除论坛帖子外的任何地方使用不安全HTML，请将此设置设为"<b>btw</b>"。
  @ 默认值为空字符串，表示Fossil从不允许Markdown文档生成不安全HTML。
  @ (属性: "safe-html")</p>
  @ <hr>
  @ 当前的跨Wiki标签映射如下：
  interwiki_append_map_table(cgi_output_blob());
  @ <p>访问 <a href="./intermap">%R/intermap</a> 了解详情或修改跨Wiki标签映射。
  @ <hr>
  onoff_attribute("使用HTML作为Wiki标记语言",
    "wiki-use-html", "wiki-use-html", 0, 0);
  @ <p>使用HTML作为Wiki标记语言。Wiki链接仍将被解析，
  @ 但所有其他Wiki格式将被忽略。</p>
  @ <p><strong>警告：</strong>启用时，Wiki中将接受<i>所有</i>HTML标签和属性。
  @ 不会进行任何清理。这意味着恶意用户很可能向您的Wiki注入危险的HTML、CSS和JavaScript代码。</p>
  @ <p>仅当Wiki编辑限于受信任用户时才应<strong>启用</strong>此功能。
  @ 不应在可公开编辑的Wiki上使用此功能。</p>
  @ (属性: "wiki-use-html")
  @ <hr>
  @ <p><input type="submit"  name="submit" value="应用更改"></p>
  @ </div></form>
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
  @ <form action="%R/setup_chat" method="post"><div>
  login_insert_csrf_secret();
  @ <input type="submit"  name="submit" value="应用更改"></p>
  @ <hr>
  entry_attribute("初始聊天历史记录大小", 10,
                  "chat-initial-history", "chatih", "50", 0);
  @ <p>当/chat首次启动时，它会预加载最多此数量的历史消息。
  @ (属性: "chat-initial-history")</p>
  @ <hr>
  entry_attribute("保留的历史消息最小数量", 10,
                  "chat-keep-count", "chatkc", "50", 0);
  @ <p>聊天子系统会清理较旧的消息，但它将始终保留最近的N条消息，其中N是此设置的值。
  @ (属性: "chat-keep-count")</p>
  @ <hr>
  entry_attribute("消息最大保留天数", 10,
                  "chat-keep-days", "chatkd", "7", 0);
  @ <p>聊天消息在N天后被移除，其中N是此设置的值。N可以是小数。例如，若只想保留12小时的聊天历史记录，
  @ 请将此值设置为0.5。
  @ (属性: "chat-keep-days")</p>
  @ <hr>
  entry_attribute("聊天轮询超时时间", 10,
                  "chat-poll-timeout", "chatpt", "420", 0);
  @ <p>新的聊天内容使用"长轮询"技术下载。系统向/chat-poll发送HTTP请求，该请求会阻塞等待新内容到达。
  @ 但/chat-poll不能永远阻塞，最终必须放弃并返回空消息集。此设置决定/chat-poll在放弃前等待的时间。
  @ 默认约7分钟的设置在许多系统上运行良好。使用代理或具有短超时的Web服务器的安装可能需要更短的延迟。
  @ 为获得最佳效率，此值应尽可能大。
  @ (属性: "chat-poll-timeout")</p>
  @ <hr>
  entry_attribute("聊天时间线机器人用户名", 15,
                  "chat-timeline-user", "chatrobot", "", 0);
  @ <p>如果此设置不为空字符串，则时间线上出现的任何更改都会在聊天室中以提供的用户名进行公告。
  @ 该用户名不需要实际存在于USER表中。
  @ 建议的用户名: "chat-robot"。
  @ (属性: "chat-timeline-user")</p>
  @ <hr>

  multiple_choice_attribute("提示音",
     "chat-alert-sound", "snd", azAlerts[0],
     count(azAlerts)/2, azAlerts);
  @ <p>客户端聊天中用于指示新聊天消息到达的声音。
  @ (属性: "chat-alert-sound")</p>
  @ <hr/>
  @ <p><input type="submit"  name="submit" value="应用更改"></p>
  @ </div></form>
  db_end_transaction(0);
  @ <script nonce="%h(style_nonce())">
  @ (function(){
  @   var w = document.getElementById('idsnd');
  @   w.onchange = function(){
  @     var audio = new Audio('%s(g.zBaseURL)/builtin/' + w.value);
  @     audio.currentTime = 0;
  @     audio.play();
  @   }
  @ })();
  @ </script>
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
  @ <form action="%R/setup_modreq" method="post"><div>
  login_insert_csrf_secret();
  @ <hr>
  onoff_attribute("审核工单变更",
     "modreq-tkt", "modreq-tkt", 0, 0);
  @ <p>启用后，任何工单变更都需要工单审核员的批准
  @ - 拥有"q"或Mod-Tkt权限的用户。
  @ 工单变更会进入系统并在本地显示，但在获得批准前不会同步。
  @ 审核员可以选择删除变更而不是批准它。
  @ 拥有Mod-Tkt权限的用户所做的工单变更永远不受审核限制。
  @ (属性: "modreq-tkt")
  @
  @ <hr>
  onoff_attribute("审核Wiki变更",
     "modreq-wiki", "modreq-wiki", 0, 0);
  @ <p>启用后，任何Wiki变更都需要Wiki审核员的批准
  @ - 拥有"l"或Mod-Wiki权限的用户。
  @ Wiki变更会进入系统并在本地显示，但在获得批准前不会同步。
  @ 审核员可以选择删除变更而不是批准它。
  @ 拥有Mod-Wiki权限的用户所做的Wiki变更永远不受审核限制。
  @ (属性: "modreq-wiki")
  @ </p>

  @ <hr>
  @ <p><input type="submit"  name="submit" value="应用更改"></p>
  @ </div></form>
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
  @ <form action="%R/setup_adunit" method="post"><div>
  login_insert_csrf_secret();
  @ <b>横幅广告单元：</b><br>
 textarea_attribute("", 6, 80, "adunit", "adunit", "", 0);
  @ <br>
  @ <b>右侧栏广告单元：</b><br>
  textarea_attribute("", 6, 80, "adunit-right", "adright", "", 0);
  @ <br>
  onoff_attribute("向管理员隐藏广告",
     "adunit-omit-if-admin", "oia", 0, 0);
  @ <br>
  onoff_attribute("向已登录用户隐藏广告",
     "adunit-omit-if-user", "oiu", 0, 0);
  @ <br>
  onoff_attribute("临时禁用所有广告",
     "adunit-disable", "oall", 0, 0);
  @ <br>
  @ <input type="submit" name="submit" value="应用更改">
  @ <input type="submit" name="clear" value="删除广告单元">
  @ </div></form>
  @ <hr>
  @ <b>广告单元说明：</b><ul>
  @ <li>将两个广告单元都留空可禁用所有广告。
  @ <li>"横幅广告单元"用于宽页面。
  @ <li>"右侧栏广告单元"用于内容高而窄的页面。
  @ <li>如果"右侧栏广告单元"为空，则所有页面都使用"横幅广告单元"。
  @ <li>属性："adunit"、"adunit-right"、"adunit-omit-if-admin"和
  @     "adunit-omit-if-user"。
  @ <li>建议的 <a href="setup_skinedit?w=0">CSS</a> 更改：
  @ <blockquote><pre>
  @ div.adunit_banner {
  @   margin: auto;
  @   width: 100%%;
  @ }
  @ div.adunit_right {
  @   float: right;
  @ }
  @ div.adunit_right_container {
  @   min-height: <i>右侧栏广告单元高度</i>;
  @ }
  @ </pre></blockquote>
  @ <li>如需测试用的占位广告单元，请复制粘贴以下内容，并适当调整"width:"和"height:"。
  @ <blockquote><pre>
  @ &lt;div style='
  @   margin: 0 auto;
  @   width: 600px;
  @   height: 90px;
  @   border: 1px solid #f11;
  @   background-color: #fcc;
  @ '&gt;演示广告&lt;/div&gt;
  @ </pre></blockquote>
  @ </li>
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
  style_header("Edit Project Logo And Background");
  @ <p>The current project logo has a MIME-Type of <b>%h(zLogoMime)</b>
  @ and looks like this:</p>
  @ <blockquote><p>
  @ <img src="%R/logo/%z(zLogoMtime)" alt="logo" border="1">
  @ </p></blockquote>
  @
  @ <form action="%R/setup_logo" method="post"
  @  enctype="multipart/form-data"><div>
  @ <p>The logo is accessible to all users at this URL:
  @ <a href="%s(g.zBaseURL)/logo">%s(g.zBaseURL)/logo</a>.
  @ The logo may or may not appear on each
  @ page depending on the <a href="setup_skinedit?w=0">CSS</a> and
  @ <a href="setup_skinedit?w=2">header setup</a>.
  @ To change the logo image, use the following form:</p>
  login_insert_csrf_secret();
  @ Logo Image file:
  @ <input type="file" name="logoim" size="60" accept="image/*">
  @ <p align="center">
  @ <input type="submit" name="setlogo" value="Change Logo">
  @ <input type="submit" name="clrlogo" value="Revert To Default"></p>
  @ <p>(Properties: "logo-image" and "logo-mimetype")
  @ </div></form>
  @ <hr>
  @
  @ <p>The current background image has a MIME-Type of <b>%h(zBgMime)</b>
  @ and looks like this:</p>
  @ <blockquote><p><img src="%R/background/%z(zBgMtime)" \
  @ alt="background" border=1>
  @ </p></blockquote>
  @
  @ <form action="%R/setup_logo" method="post"
  @  enctype="multipart/form-data"><div>
  @ <p>The background image is accessible to all users at this URL:
  @ <a href="%s(g.zBaseURL)/background">%s(g.zBaseURL)/background</a>.
  @ The background image may or may not appear on each
  @ page depending on the <a href="setup_skinedit?w=0">CSS</a> and
  @ <a href="setup_skinedit?w=2">header setup</a>.
  @ To change the background image, use the following form:</p>
  login_insert_csrf_secret();
  @ Background image file:
  @ <input type="file" name="bgim" size="60" accept="image/*">
  @ <p align="center">
  @ <input type="submit" name="setbg" value="Change Background">
  @ <input type="submit" name="clrbg" value="Revert To Default"></p>
  @ </div></form>
  @ <p>(Properties: "background-image" and "background-mimetype")
  @ <hr>
  @
  @ <p>The current icon image has a MIME-Type of <b>%h(zIconMime)</b>
  @ and looks like this:</p>
  @ <blockquote><p><img src="%R/favicon.ico/%z(zIconMtime)" \
  @ alt="icon" border=1>
  @ </p></blockquote>
  @
  @ <form action="%R/setup_logo" method="post"
  @  enctype="multipart/form-data"><div>
  @ <p>The icon image is accessible to all users at this URL:
  @ <a href="%s(g.zBaseURL)/favicon.ico">%s(g.zBaseURL)/favicon.ico</a>.
  @ The icon image may or may not appear on each
  @ page depending on the web browser in use and the MIME-Types that it
  @ supports for icon images.
  @ To change the icon image, use the following form:</p>
  login_insert_csrf_secret();
  @ Icon image file:
  @ <input type="file" name="iconim" size="60" accept="image/*">
  @ <p align="center">
  @ <input type="submit" name="seticon" value="Change Icon">
  @ <input type="submit" name="clricon" value="Revert To Default"></p>
  @ </div></form>
  @ <p>(Properties: "icon-image" and "icon-mimetype")
  @ <hr>
  @
  @ <p><span class="note">Note:</span>  Your browser has probably cached these
  @ images, so you may need to press the Reload button before changes will
  @ take effect. </p>
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
  @ <p><b>Caution:</b> There are no restrictions on the SQL that can be
  @ run by this page.  You can do serious and irrepairable damage to the
  @ repository.  Proceed with extreme caution.</p>
  @
#if 0
  @ <p>Only the first statement in the entry box will be run.
  @ Any subsequent statements will be silently ignored.</p>
  @
  @ <p>Database names:<ul><li>repository
  if( g.zConfigDbName ){
    @ <li>configdb
  }
  if( g.localOpen ){
    @ <li>localdb
  }
  @ </ul></p>
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
  @
  @ <form method="post" action="%R/admin_sql">
  login_insert_csrf_secret();
  @ SQL:<br>
  @ <textarea name="q" rows="8" cols="80">%h(zQ)</textarea><br>
  @ <input type="submit" name="go" value="Run SQL">
  @ <input type="submit" name="schema" value="Show Schema">
  @ <input type="submit" name="tablelist" value="List Tables">
  @ <input type="submit" name="configtab" value="CONFIG Table Query">
  @ </form>
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
    @ <hr>
    sqlite3_set_authorizer(g.db, raw_sql_query_authorizer, 0);
    search_sql_setup(g.db);
    rc = sqlite3_prepare_v2(g.db, zQ, -1, &pStmt, &zTail);
    if( rc!=SQLITE_OK ){
      @ <div class="generalError">%h(sqlite3_errmsg(g.db))</div>
      sqlite3_finalize(pStmt);
    }else if( pStmt==0 ){
      /* No-op */
    }else if( (nCol = sqlite3_column_count(pStmt))==0 ){
      sqlite3_step(pStmt);
      rc = sqlite3_finalize(pStmt);
      if( rc ){
        @ <div class="generalError">%h(sqlite3_errmsg(g.db))</div>
      }
    }else{
      @ <table border="1" cellpadding="4" cellspacing="0">
      while( sqlite3_step(pStmt)==SQLITE_ROW ){
        if( nRow==0 ){
          @ <tr>
          for(i=0; i<nCol; i++){
            @ <th>%h(sqlite3_column_name(pStmt, i))</th>
          }
          @ </tr>
        }
        nRow++;
        @ <tr>
        for(i=0; i<nCol; i++){
          switch( sqlite3_column_type(pStmt, i) ){
            case SQLITE_INTEGER:
            case SQLITE_FLOAT: {
               @ <td align="right" valign="top">
               @ %s(sqlite3_column_text(pStmt, i))</td>
               break;
            }
            case SQLITE_NULL: {
               @ <td valign="top" align="center"><i>NULL</i></td>
               break;
            }
            case SQLITE_TEXT: {
               const char *zText = (const char*)sqlite3_column_text(pStmt, i);
               @ <td align="left" valign="top"
               @ style="white-space:pre;">%h(zText)</td>
               break;
            }
            case SQLITE_BLOB: {
               @ <td valign="top" align="center">
               @ <i>%d(sqlite3_column_bytes(pStmt, i))-byte BLOB</i></td>
               break;
            }
          }
        }
        @ </tr>
      }
      sqlite3_finalize(pStmt);
      @ </table>
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
  style_header("Raw TH1 Commands");
  @ <p><b>Caution:</b> There are no restrictions on the TH1 that can be
  @ run by this page.  If Tcl integration was enabled at compile-time and
  @ the "tcl" setting is enabled, Tcl commands may be run as well.</p>
  @
  form_begin(0, "%R/admin_th1");
  @ TH1:<br>
  @ <textarea name="q" rows="5" cols="80">%h(zQ)</textarea><br>
  @ <input type="submit" name="go" value="Run TH1">
  @ </form>
  if( go && cgi_csrf_safe(2) ){
    const char *zR;
    int rc;
    int n;
    @ <hr>
    rc = Th_Eval(g.interp, 0, zQ, -1);
    zR = Th_GetResult(g.interp, &n);
    if( rc==TH_OK ){
      @ <pre class="th1result">%h(zR)</pre>
    }else{
      @ <pre class="th1error">%h(zR)</pre>
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
  @ <div>管理日志功能处于%s(fLogEnabled?"开启":"关闭")状态。
  @ 可在<a href="setup_settings">设置</a>页面更改此设置。</div>

  if( ofst>0 ){
    int prevx = ofst - limit;
    if( prevx<0 ) prevx = 0;
    @ <p><a href="admin_log?n=%d(limit)&x=%d(prevx)">[较新]</a></p>
  }
  db_prepare(&stLog,
    "SELECT datetime(time,'unixepoch'), who, page, what "
    "FROM admin_log "
    "ORDER BY time DESC, rowid DESC");
  style_table_sorter();
  @ <table class="sortable adminLogTable" width="100%%" \
  @  data-column-types='Tttx' data-init-sort='1'>
  @ <thead>
  @ <th>时间</th>
  @ <th>用户</th>
  @ <th>页面</th>
  @ <th width="60%%">消息</th>
  @ </thead><tbody>
  while( SQLITE_ROW == db_step(&stLog) ){
    const char *zTime = db_column_text(&stLog, 0);
    const char *zUser = db_column_text(&stLog, 1);
    const char *zPage = db_column_text(&stLog, 2);
    const char *zMessage = db_column_text(&stLog, 3);
    counter++;
    if( counter<ofst ) continue;
    if( counter>ofst+limit ) break;
    @ <tr class="row%d(counter%2)">
    @ <td class="adminTime">%s(zTime)</td>
    @ <td>%s(zUser)</td>
    @ <td>%s(zPage)</td>
    @ <td>%h(zMessage)</td>
    @ </tr>
  }
  db_finalize(&stLog);
  @ </tbody></table>
  if( counter>ofst+limit ){
    @ <p><a href="admin_log?n=%d(limit)&x=%d(limit+ofst)">[较旧]</a></p>
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
  @ <form action="%R/srchsetup" method="post"><div>
  login_insert_csrf_secret();
  @ <div style="text-align:center;font-weight:bold;">
  @ 影响<a href="%R/search">/search</a>网页的服务器特定设置。
  @ </div>
  @ <hr>
  textarea_attribute("文档全局列表", 3, 35, "doc-glob", "dg", "", 0);
  @ <p>"文档全局列表"是用逗号或换行符分隔的GLOB表达式列表，
  @ 用于标识当"文档搜索"启用时，源代码树中所有需要搜索的文档。
  @ 一些示例：
  @ <table border=0 cellpadding=2 align=center>
  @ <tr><td>*.wiki,*.html,*.md,*.txt<td style="width: 4x;">
  @ <td>搜索所有wiki、HTML、Markdown和文本文件</tr>
  @ <tr><td>doc/*.md,*/README.txt,README.txt<td>
  @ <td>搜索doc/子文件夹中的所有Markdown文件和所有README.txt
  @ 文件。</tr>
  @ <tr><td>*<td><td>搜索所有已签入文件</tr>
  @ <tr><td><i>(空白)</i><td>
  @ <td>不搜索任何内容。（禁用文档搜索）</tr>
  @ </table>
  @ <hr>
  entry_attribute("文档分支", 20, "doc-branch", "db", "trunk", 0);
  @ <p>搜索文档时，使用在"文档分支"分支类型中找到的文件版本。推荐值："trunk"。
  @ 如果为空则禁用文档搜索。可以是用空格和/或逗号分隔的分支名称列表。
  @ <hr>
  onoff_attribute("搜索签入注释", "search-ci", "sc", 0, 0);
  @ <br>
  onoff_attribute("搜索文档", "search-doc", "sd", 0, 0);
  @ <br>
  onoff_attribute("搜索工单", "search-tkt", "st", 0, 0);
  @ <br>
  onoff_attribute("搜索Wiki", "search-wiki", "sw", 0, 0);
  @ <br>
  onoff_attribute("搜索技术笔记", "search-technote", "se", 0, 0);
  @ <br>
  onoff_attribute("搜索论坛", "search-forum", "sf", 0, 0);
  @ <br>
  onoff_attribute("搜索内置帮助文本", "search-help", "sh", 0, 0);
  @ <hr>
  @ <p><input type="submit"  name="submit" value="应用更改"></p>
  @ <hr>
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
    @ <p>当前使用SQLite FTS%d(search_index_type(0))搜索索引。
    @ 该索引有助于加快搜索速度，特别是在大型代码仓库中，
    @ 但会占用空间。索引当前使用约%s(zSize)的空间，
    @ 占代码仓库的%.1f(100.0*(double)nFts/(double)nTotal)%%。</p>
    select_fts_tokenizer();
    @ <p><input type="submit" name="fts0" value="删除全文索引">
    @ <input type="submit" name="fts1" value="重建全文索引">
    style_submenu_element("FTS索引调试","%R/test-ftsdocs");
  }else{
    @ <p>SQLite搜索索引已禁用。所有搜索都将进行全文扫描。
    @ 这通常可以正常工作，但对于大型代码仓库可能会很慢。</p>
    select_fts_tokenizer();
    @ <p><input type="submit" name="fts1" value="创建全文索引">
  }
  @ </div></form>
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
  @ <form action="%R/waliassetup" method="post"><div>
  login_insert_csrf_secret();
  @ <table border=0 cellpadding=5>
  @ <tr><th>别名<th>别名映射到的URI
  blob_init(&namelist, 0, 0);
  while( db_step(&q)==SQLITE_ROW ){
    const char *zName = db_column_text(&q, 0);
    const char *zValue = db_column_text(&q, 1);
    @ <tr><td>
    @ <input type='text' size='20' value='%h(zName)' name='n%d(cnt)'>
    @ </td><td>
    @ <input type='text' size='80' value='%h(zValue)' name='v%d(cnt)'>
    @ </td></tr>
    cnt++;
    if( blob_size(&namelist)>0 ) blob_append(&namelist, " ", 1);
    blob_append(&namelist, zName, -1);
  }
  db_finalize(&q);
  @ <tr><td>
  @ <input type='hidden' name='namelist' value='%h(blob_str(&namelist))'>
  @ <input type='submit' name='submit' value="应用更改">
  @ </td><td></td></tr>
  @ </table></form>
  @ <hr>
  @ <p>当传入URL的第一个部分与上方左侧(LHS)的"别名"完全匹配时，URL将转换为右侧(RHS)的相应形式。
  @ <ul>
  @ <li><p>
  @ 左侧(LHS)仅与传入URL的第一个部分进行比较。因此，别名表中的所有左侧条目都应该以单个"/"开头，后跟单个路径元素。
  @ <li><p>
  @ 别名表中的右侧(RHS)条目应该以单个"/"开头，后跟路径元素，可选地后跟"?"和查询参数列表。
  @ <li><p>
  @ 右侧(RHS)的查询参数会添加到传入URL的查询参数集中。
  @ <li><p>
  @ 如果相同的查询参数同时出现在传入URL和别名的右侧(RHS)，则右侧(RHS)的查询参数值会覆盖传入URL上的值。
  @ <li><p>
  @ 如果别名右侧(RHS)的查询参数形式为"X!"（名称后跟"!"），则如果存在X查询参数，它将从传入URL中移除。
  @ <li><p>
  @ 只发生单个别名操作。不可能嵌套别名。右侧(RHS)条目必须是内置网页名称。
  @ <li><p>
  @ 只有当没有内置网页与传入URL匹配时，才会检查别名表。
  @ 因此，无法使用别名覆盖内置网页。这是设计使然。
  @ </ul>
  @
  @ <p>要从别名表中删除条目，请将其名称或值更改为空字符串，然后按"应用更改"。
  @
  @ <p>要添加新别名，请在上面表格的最后一行填写名称和值，然后按"应用更改"。
  style_finish_page();
}
