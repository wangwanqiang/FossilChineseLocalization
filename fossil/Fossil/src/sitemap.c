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
    style_header("站点地图");
    style_adunit_config(ADUNIT_RIGHT_OK);
  }

  @ <ul id="sitemap" class="columns" style="column-width:20em">
  if( (e&1)==0 ){
    @ <li>%z(href("%R/home"))首页</a>
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
          @ <ul>
          inSublist = 1;
        }
        if( azExtra[i+1][0]=='/' ){
          @ <li>%z(href("%R%s",azExtra[i+1]))%h(azExtra[i])</a></li>
        }else{
          @ <li>%z(href("%s",azExtra[i+1]))%s(azExtra[i])</a></li>
        }
      }
    }
    Th_Free(g.interp, azExtra);
  }
  if( (e&1)!=0 ) goto end_of_sitemap;

  if( inSublist ){
    @ </ul>
    inSublist = 0;
  }
  @ </li>
  if( cgi_is_loopback(g.zIpAddr) && db_open_local(0) ){
    @ <li>%z(href("%R/ckout"))检出状态</a></li>
  }
  if( g.perm.Read ){
    const char *zEditGlob = db_get("fileedit-glob","");
    @ <li>%z(href("%R/tree"))文件浏览器</a>
    @   <ul>
    @   <li>%z(href("%R/tree?type=tree&ci=trunk"))树状视图,
    @        主干检出</a></li>
    @   <li>%z(href("%R/tree?type=flat"))平面视图</a></li>
    @   <li>%z(href("%R/fileage?name=trunk"))主干文件年代</a></li>
    @   <li>%z(href("%R/uvlist"))未版本化文件</a>
    if( g.perm.Write && zEditGlob[0]!=0 ){
      @   <li>%z(href("%R/fileedit"))在线文件编辑器</li>
    }
    @ </ul>
  }
  if( g.perm.Read ){
    @ <li>%z(href("%R/timeline"))项目时间线</a>
    @ <ul>
    @   <li>%z(href("%R/reports"))活动报告</a></li>
    @   <li>%z(href("%R/sitemap-timeline"))其他时间线</a></li>
    @ </ul>
    @ </li>
  }
  if( g.perm.Read ){
    @ <li>%z(href("%R/brlist"))分支</a>
    @ <ul>
    @   <li>%z(href("%R/taglist"))标签</a></li>
    @   <li>%z(href("%R/leaves"))叶节点检出</a></li>
    @ </ul>
    @ </li>
  }
  if( srchFlags ){
    @ <li>%z(href("%R/search"))搜索</a></li>
  }
  if( g.perm.Chat ){
    @ <li>%z(href("%R/chat"))聊天</a></li>
  }
  if( g.perm.RdForum ){
    const char *zTitle = db_get("forum-title","Forum");
    @ <li>%z(href("%R/forum"))%h(zTitle)</a>
    @ <ul>
    @   <li>%z(href("%R/timeline?y=f"))近期活动</a></li>
    @ </ul>
    @ </li>
  }
  if( g.perm.RdTkt ){
    @ <li>%z(href("%R/reportlist"))工单/缺陷报告</a>
    @   <ul>
    if( srchFlags & SRCH_TKT ){
      @   <li>%z(href("%R/tktsrch"))工单搜索</a></li>
    }
    @   <li>%z(href("%R/timeline?y=t"))近期活动</a></li>
    @   <li>%z(href("%R/attachlist"))附件列表</a></li>
    @   </ul>
    @ </li>
  }
  if( g.perm.RdWiki ){
    @ <li>%z(href("%R/wikihelp"))维基</a>
    @   <ul>
    if( srchFlags & SRCH_WIKI ){
      @     <li>%z(href("%R/wikisrch"))维基搜索</a></li>
    }
    @     <li>%z(href("%R/wcontent"))维基页面列表</a></li>
    @     <li>%z(href("%R/timeline?y=w"))近期活动</a></li>
    @     <li>%z(href("%R/wikiedit?name=Sandbox"))维基沙盒</a></li>
    @     <li>%z(href("%R/attachlist"))附件列表</a></li>
    @     <li>%z(href("%R/pikchrshow"))Pikchr沙盒</a></li>
    @   </ul>
    @ </li>
  }

  if( !g.zLogin ){
    @ <li>%z(href("%R/login"))登录</a>
    @ <ul>
    if( login_self_register_available(0) ){
       @ <li>%z(href("%R/register"))创建新账户</a></li>
    }
  }else {
    @ <li>%z(href("%R/logout"))退出登录 %h(g.zLogin)</a>
    @ <ul>
    if( g.perm.Password ){
      @ <li>%z(href("%R/logout"))修改密码 %h(g.zLogin)</a></li>
    }
  }
  if( alert_enabled() && g.perm.EmailAlert ){
    if( login_is_individual() ){
      @ <li>%z(href("%R/alerts"))邮件提醒 %h(g.zLogin)</a></li>
    }else{
      @ <li>%z(href("%R/subscribe"))订阅邮件提醒</a></li>
    }
  }
  @ <li>%z(href("%R/cookies"))Cookie设置</a></li>
  @ </ul>
  @ </li>

  if( g.perm.Read ){
    @ <li>%z(href("%R/stat"))仓库状态</a>
    @   <ul>
    @   <li>%z(href("%R/hash-collisions"))哈希前缀冲突</a></li>
    if( g.perm.Admin ){
      @   <li>%z(href("%R/urllist"))访问此仓库的URL列表</a></li>
    }
    @   <li>%z(href("%R/bloblist"))制品列表</a></li>
    @   </ul>
    @ </li>
  }
  @ <li>%z(href("%R/help"))帮助</a>
  @   <ul>
  if( g.perm.Admin || g.perm.Write ||
      g.perm.WrForum || g.perm.WrTForum ||
      g.perm.NewWiki || g.perm.ApndWiki || g.perm.WrWiki || g.perm.ModWiki ||
      g.perm.NewTkt  || g.perm.ApndTkt  || g.perm.WrTkt  || g.perm.ModTkt ){
    @   <li>%z(href("%R/wiki_rules"))维基格式规则</a></li>
    @   <li>%z(href("%R/md_rules"))Markdown格式规则</a></li>
  }
  @   <li>%z(href("%R/test-all-help"))所有帮助文本（单页显示）</a></li>
  if( g.perm.Admin || g.perm.Write || g.perm.WrUnver ){
    @   <li>%z(href("%R/mimetype_list"))\
    @ 文件名后缀到MIME类型映射</a></li>
  }
  @   </ul></li>
  if( g.perm.Admin ){
    @ <li><a href="%R/setup">管理页面</a>
    @   <ul>
    @   <li><a href="%R/secaudit0">安全审计</a></li>
    @   <li><a href="%R/modreq">待审核请求</a></li>
    @   </ul></li>
  }
  @ <li>%z(href("%R/skins"))皮肤</a></li>
  @ <li>%z(href("%R/sitemap-test"))测试页面</a></li>
  if( isPopup ){
    @ <li>%z(href("%R/sitemap"))站点地图</a></li>
  }

end_of_sitemap:
  @ </ul>
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
    style_header("测试页面地图");
    style_adunit_config(ADUNIT_RIGHT_OK);
  }
  @ <ul id="sitemap" class="columns" style="column-width:20em">
  if( g.perm.Admin || db_get_boolean("test_env_enable",0) ){
    @ <li>%z(href("%R/test-env"))CGI环境测试</a></li>
  }
  if( g.perm.Read ){
    @ <li>%z(href("%R/test-rename-list"))文件重命名列表</a></li>
  }
  @ <li>%z(href("%R/test-builtin-files"))内置文件列表</a></li>
  @ <li>%z(href("%R/mimetype_list"))MIME类型列表</a></li>
  @ <li>%z(href("%R/hash-color-test"))哈希颜色测试</a>
  @ <li>%z(href("%R/test-bgcolor"))背景颜色测试</a>
  if( g.perm.Admin ){
    @ <li>%z(href("%R/test-backlinks"))反向链接列表</a></li>
    @ <li>%z(href("%R/test-backlink-timeline"))反向链接时间线</a></li>
    @ <li>%z(href("%R/phantoms"))幻影制品列表</a></li>
    @ <li>%z(href("%R/test-warning"))错误日志测试页面</a></li>
    @ <li>%z(href("%R/repo_stat1"))仓库 <tt>sqlite_stat1</tt> 表</a>
    @ <li>%z(href("%R/repo_schema"))仓库架构</a></li>
  }
  if( g.perm.Read && g.perm.Hyperlink ){
    @ <li>%z(href("%R/timewarps"))时间扭曲时间线</a></li>
  }
  @ <li>%z(href("%R/cookies"))显示首选项Cookie内容</a></li>
  @ <li>%z(href("%R/test-captcha"))随机ASCII艺术验证码图片</a></li>
  @ <li>%z(href("%R/test-piechart"))饼图生成器测试</a></li>
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
    style_header("时间线示例");
    style_adunit_config(ADUNIT_RIGHT_OK);
  }
  @ <ul id="sitemap" class="columns" style="column-width:20em">
  @ <li>%z(href("%R/timeline?ymd"))当天</a></li>
  @ <li>%z(href("%R/timeline?yw"))当周</a></li>
  @ <li>%z(href("%R/timeline?ym"))当月</a></li>
  @ <li>%z(href("%R/thisdayinhistory"))历史上的今天</a></li>
  @ <li>%z(href("%R/timeline?a=1970-01-01&y=ci&n=10"))前10个
  @     检出</a></li>
  @ <li>%z(href("%R/timeline?namechng"))文件名变更</a></li>
  @ <li>%z(href("%R/timeline?forks"))分支</a></li>
  @ <li>%z(href("%R/timeline?cherrypicks"))摘樱桃合并</a></li>
  @ <li>%z(href("%R/timewarps"))时间扭曲</a></li>
  @ <li>%z(href("%R/timeline?ubg"))按用户彩色编码</a></li>
  @ <li>%z(href("%R/timeline?deltabg"))与基准清单的差异</a></li>
  @ </ul>
  if( !isPopup ){
    style_finish_page();
  }
}
