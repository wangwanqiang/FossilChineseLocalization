/*
** Copyright (c) 2008 D. Richard Hipp
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
** This file contains code used to manage SHUN table of the repository
*/
#include "config.h"
#include "shun.h"
#include <assert.h>

/*
** Return true if the given artifact ID should be shunned.
*/
int uuid_is_shunned(const char *zUuid){
  static Stmt q;
  int rc;
  if( zUuid==0 || zUuid[0]==0 ) return 0;
  if( g.eHashPolicy==HPOLICY_SHUN_SHA1 && zUuid[HNAME_LEN_SHA1]==0 ) return 1;
  db_static_prepare(&q, "SELECT 1 FROM shun WHERE uuid=:uuid");
  db_bind_text(&q, ":uuid", zUuid);
  rc = db_step(&q);
  db_reset(&q);
  return rc==SQLITE_ROW;
}

/*
** WEBPAGE: shun
**
** View the hashes of all shunned artifacts.  Add new hashes
** to the shun set.  Requires Admin privilege.
*/
void shun_page(void){
  Stmt q;
  int cnt = 0;
  const char *zUuid = P("uuid");
  const char *zShun = P("shun");
  const char *zAccept = P("accept");
  const char *zRcvid = P("rcvid");
  int reviewList = P("review")!=0;
  int nRcvid = 0;
  int numRows = 3;
  char *zCanonical = 0;

  login_check_credentials();
  if( !g.perm.Admin ){
    login_needed(0);
    return;
  }
  if( P("rebuild") ){
    db_close(1);
    db_open_repository(g.zRepositoryName);
    db_begin_transaction();
    rebuild_db(0, 0);
    admin_log("Rebuilt database.");
    db_end_transaction(0);
  }
  if( zUuid ){
    char *p;
    int i = 0;
    int j = 0;
    zCanonical = fossil_malloc(strlen(zUuid)+2);
    while( zUuid[i] ){
      if( fossil_isspace(zUuid[i]) ){
        if( j && zCanonical[j-1] ){
          zCanonical[j] = 0;
          j++;
        }
      }else{
        zCanonical[j] = zUuid[i];
        j++;
      }
      i++;
    }
    zCanonical[j+1] = zCanonical[j] = 0;
    p = zCanonical;
    while( *p ){
      int nUuid = strlen(p);
      if( !(reviewList || hname_validate(p, nUuid)) ){
        @ <p class="generalError">Error: Bad artifact IDs.</p>
        fossil_free(zCanonical);
        zCanonical = 0;
        break;
      }else{
        canonical16(p, nUuid);
        p += nUuid+1;
      }
    }
    zUuid = zCanonical;
  }
  style_header("被回避的制品");
  if( zUuid && P("sub") && cgi_csrf_safe(2) ){
    const char *p = zUuid;
    int allExist = 1;
    while( *p ){
      db_multi_exec("DELETE FROM shun WHERE uuid=%Q", p);
      if( !db_exists("SELECT 1 FROM blob WHERE uuid=%Q", p) ){
        allExist = 0;
      }
      admin_log("Unshunned %Q", p);
      p += strlen(p)+1;
    }
    if( allExist ){
      @ <p class="noMoreShun">制品<br>
      for( p = zUuid ; *p ; p += strlen(p)+1 ){
        @ <a href="%R/artifact/%s(p)">%s(p)</a><br>
      }
      @ 已不再被回避。</p>
    }else{
      @ <p class="noMoreShun">制品<br>
      for( p = zUuid ; *p ; p += strlen(p)+1 ){
        @ %s(p)<br>
      }
      @ 将不再被回避，但它们可能在仓库中不存在。
      @ 可能需要先重建仓库，
      @ 然后才能从其他仓库拉取制品内容。</p>
    }
  }
  if( zUuid && P("add") && cgi_csrf_safe(2) ){
    const char *p = zUuid;
    int rid, tagid;
    while( *p ){
      db_multi_exec(
        "INSERT OR IGNORE INTO shun(uuid,mtime)"
        " VALUES(%Q, now())", p);
      db_multi_exec("DELETE FROM attachment WHERE src=%Q", p);
      rid = db_int(0, "SELECT rid FROM blob WHERE uuid=%Q", p);
      if( rid ){
        db_multi_exec("DELETE FROM event WHERE objid=%d", rid);
      }
      tagid = db_int(0, "SELECT tagid FROM tag WHERE tagname='tkt-%q'", p);
      if( tagid ){
        db_multi_exec("DELETE FROM ticket WHERE tkt_uuid=%Q", p);
        db_multi_exec("DELETE FROM tag WHERE tagid=%d", tagid);
        db_multi_exec("DELETE FROM tagxref WHERE tagid=%d", tagid);
      }
      admin_log("Shunned %Q", p);
      p += strlen(p)+1;
    }
    @ <p class="shunned">制品<br>
    for( p = zUuid ; *p ; p += strlen(p)+1 ){
      @ <a href="%R/artifact/%s(p)">%s(p)</a><br>
    }
    @ 已被回避。它们将不再被推送。
    @ 它们将在下次使用 <b>fossil rebuild</b> 命令行重建
    @ 仓库时从仓库中移除。</p>
  }
  if( zUuid && reviewList ){
    const char *p;
    int nTotal = 0;
    int nOk = 0;
    @ <table class="shun-review"><tbody><tr><td>
    for( p = zUuid ; *p ; p += strlen(p)+1 ){
      int rid = symbolic_name_to_rid(p, 0);
      nTotal++;
      if( rid < 0 ){
        @ Ambiguous<br>
      }else if( rid == 0 ){
        if( !hname_validate(p, strlen(p)) ){
          @ 无效制品<br>
        }else if(db_int(0, "SELECT 1 FROM shun WHERE uuid=%Q", p)){
          @ 已被回避<br>
        }else{
          @ 未知<br>
        }
      }else{
        char *zCmpUuid = db_text(0,
            "SELECT uuid"
            "  FROM blob, rcvfrom"
            " WHERE rid=%d"
            "   AND rcvfrom.rcvid=blob.rcvid",
            rid);
        if( fossil_strcmp(p, zCmpUuid)==0 ){
          nOk++;
          @ 有效</br>
        }else{
          @ 缩写形式<br>
        }
      }
    }
    @ </td><td>
    for( p = zUuid ; *p ; p += strlen(p)+1 ){
      int rid = symbolic_name_to_rid(p, 0);
      if( rid > 0 ){
        @ <a href="%R/artifact/%s(p)">%s(p)</a><br>
      }else{
        @ %s(p)<br>
      }
    }
    @ </td></tr></tbody></table>
    @ <p class="shunned">
    if( nOk < nTotal){
      @ <b>警告：</b> 并非所有制品
    }else if( nTotal==1 ){
      @ 该制品存在且
    }else{
      @ 所有 %i(nOk) 个制品存在且
    }
    @ 可以通过上方的哈希值被回避。</p>
  }
  if( zRcvid ){
    nRcvid = atoi(zRcvid);
    numRows = db_int(0, "SELECT min(count(), 10) FROM blob WHERE rcvid=%d",
                     nRcvid);
  }
  @ <p>被回避的制品不会被推送，也不会在拉取时被接受，并且该制品
  @ 内容将在下次重建仓库时从仓库中清除。本页面底部可以查看
  @ 已被回避的制品列表。</p>
  @
  @ <a name="addshun"></a>
  @ <p>要回避制品，请在下方输入框中输入制品哈希值（制品内容的
  @ 40或64字符小写十六进制哈希值），然后点击"回避"按钮。
  @ 这将导致制品从仓库中移除，并防止后续同步操作将其重新添加
  @ 到仓库中。</p>
  @
  @ <p>请注意，您必须输入完整的制品哈希值，而不是缩写
  @ 或符号标签。</p>
  @
  @ <p>警告：回避功能仅应用于从仓库中移除不适当的内容。
  @ 不适当的内容包括添加到Wiki的垃圾内容、违反版权或专利协议的文件，
  @ 或因设计或意外干扰仓库处理的制品。不要仅仅为了将制品
  @ 从视野中移除而回避它们——对这些制品设置"hidden"标签即可。</p>
  @
  @ <blockquote>
  @ <form method="post" action="%R/%s(g.zPath)"><div>
  login_insert_csrf_secret();
  @ <textarea class="fullsize-text" cols="70" rows="%d(numRows)" name="uuid">
  if( zShun ){
    if( strlen(zShun) ){
      @ %h(zShun)
    }else if( nRcvid ){
      db_prepare(&q, "SELECT uuid FROM blob WHERE rcvid=%d", nRcvid);
      while( db_step(&q)==SQLITE_ROW ){
        @ %s(db_column_text(&q, 0))
      }
      db_finalize(&q);
    }
  }else if( zUuid && reviewList ){
    const char *p;
    for( p = zUuid ; *p ; p += strlen(p)+1 ){
      @ %s(p)
    }
  }
  @ </textarea>
  @ <input type="submit" name="add" value="回避">
  @ <input type="submit" name="review" value="查看">
  @ </div></form>
  @ </blockquote>
  @
  @ <a name="delshun"></a>
  @ <p>输入先前被回避的制品的UUID，使其重新被仓库接受。
  @ 制品内容不会被恢复，因为内容未知。唯一的变化是，
  @ 先前被回避的制品将在后续同步操作中被接受。</p>
  @
  @ <blockquote>
  @ <form method="post" action="%R/%s(g.zPath)"><div>
  login_insert_csrf_secret();
  @ <textarea class="fullsize-text" cols="70" rows="%d(numRows)" name="uuid">
  if( zAccept ){
    if( strlen(zAccept) ){
      @ %h(zAccept)
    }else if( nRcvid ){
      db_prepare(&q, "SELECT uuid FROM blob WHERE rcvid=%d", nRcvid);
      while( db_step(&q)==SQLITE_ROW ){
        @ %s(db_column_text(&q, 0))
      }
      db_finalize(&q);
    }
  }
  @ </textarea>
  @ <input type="submit" name="sub" value="接受">
  @ </div></form>
  @ </blockquote>
  @
  @ <p>点击下方的重建按钮来重建仓库。新被回避的制品
  @ 内容不会被清除，直到仓库被重建。在较大的仓库中，重建可能需要几分钟或
  @ 更长时间，因此点击按钮后请耐心等待。</p>
  @
  @ <blockquote>
  @ <form method="post" action="%R/%s(g.zPath)"><div>
  login_insert_csrf_secret();
  @ <input type="submit" name="rebuild" value="重建">
  @ </div></form>
  @ </blockquote>
  @
  @ <hr><p>已被回避的制品：</p>
  @ <blockquote><p>
  db_prepare(&q,
     "SELECT uuid, EXISTS(SELECT 1 FROM blob WHERE blob.uuid=shun.uuid)"
     "  FROM shun ORDER BY uuid");
  while( db_step(&q)==SQLITE_ROW ){
    const char *zUuid = db_column_text(&q, 0);
    int stillExists = db_column_int(&q, 1);
    cnt++;
    if( stillExists ){
      @ <b><a href="%R/artifact/%s(zUuid)">%s(zUuid)</a></b><br>
    }else{
      @ <b>%s(zUuid)</b><br>
    }
  }
  if( cnt==0 ){
    @ <i>此服务器上没有被回避的制品</i>
  }
  db_finalize(&q);
  @ </p></blockquote>
  style_finish_page();
  fossil_free(zCanonical);
}

/*
** Remove from the BLOB table all artifacts that are in the SHUN table.
*/
void shun_artifacts(void){
  Stmt q;
  db_multi_exec(
     "CREATE TEMP TABLE toshun(rid INTEGER PRIMARY KEY);"
     "INSERT INTO toshun SELECT rid FROM blob, shun WHERE blob.uuid=shun.uuid;"
  );
  db_prepare(&q,
     "SELECT rid FROM delta WHERE srcid IN toshun"
  );
  while( db_step(&q)==SQLITE_ROW ){
    int srcid = db_column_int(&q, 0);
    content_undelta(srcid);
  }
  db_finalize(&q);
  db_multi_exec(
     "DELETE FROM delta WHERE rid IN toshun;"
     "DELETE FROM blob WHERE rid IN toshun;"
     "DROP TABLE toshun;"
     "DELETE FROM private "
     " WHERE NOT EXISTS (SELECT 1 FROM blob WHERE rid=private.rid);"
  );
}

/*
** WEBPAGE: rcvfromlist
**
** Show a listing of RCVFROM table entries.
**
** The RCVFROM table records where this repository received each
** artifact, including the time of receipt, user, and IP address.
**
** Access requires Admin privilege.
*/
void rcvfromlist_page(void){
  int ofst = atoi(PD("ofst","0"));
  int showAll = P("all")!=0;
  int cnt;
  Stmt q;
  const int perScreen = 500;   /* RCVIDs per page */

  login_check_credentials();
  if( !g.perm.Admin ){
    login_needed(0);
    return;
  }
  style_header("Xfer Log");
  style_submenu_element("Log-Menu", "setup-logmenu");
  if( showAll ){
    ofst = 0;
  }else{
    style_submenu_element("All", "rcvfromlist?all=1");
  }
  if( ofst>0 ){
    style_submenu_element("Newer", "rcvfromlist?ofst=%d",
                           ofst>perScreen ? ofst-perScreen : 0);
  }
  style_submenu_element("Artifacts", "bloblist");
  style_submenu_element("Top-250", "bigbloblist");
  db_multi_exec(
    "CREATE TEMP TABLE rcvidUsed(x INTEGER PRIMARY KEY);"
    "CREATE TEMP TABLE rcvidSha1(x INTEGER PRIMARY KEY);"
    "CREATE TEMP TABLE rcvidSha3(x INTEGER PRIMARY KEY);"
    "INSERT OR IGNORE INTO rcvidUsed(x) SELECT rcvid FROM blob;"
    "INSERT OR IGNORE INTO rcvidSha1(x)"
    "   SELECT rcvid FROM blob WHERE length(uuid)==40;"
    "INSERT OR IGNORE INTO rcvidSha3(x)"
    "   SELECT rcvid FROM blob WHERE length(uuid)==64;"
  );
  if( db_table_exists("repository","unversioned") ){
    db_multi_exec(
      "INSERT OR IGNORE INTO rcvidUsed(x) SELECT rcvid FROM unversioned;"
      "INSERT OR IGNORE INTO rcvidSha1(x)"
      "   SELECT rcvid FROM unversioned WHERE length(hash)==40;"
      "INSERT OR IGNORE INTO rcvidSha3(x)"
      "   SELECT rcvid FROM unversioned WHERE length(hash)==64;"
    );
  }
  db_prepare(&q,
    "SELECT rcvid, login, datetime(rcvfrom.mtime), rcvfrom.ipaddr,"
    "       EXISTS(SELECT 1 FROM rcvidUsed WHERE x=rcvfrom.rcvid),"
    "       EXISTS(SELECT 1 FROM rcvidSha1 WHERE x=rcvfrom.rcvid),"
    "       EXISTS(SELECT 1 FROM rcvidSha3 WHERE x=rcvfrom.rcvid)"
    "  FROM rcvfrom LEFT JOIN user USING(uid)"
    " ORDER BY rcvid DESC LIMIT %d OFFSET %d",
    showAll ? -1 : perScreen+1, ofst
  );
  @ <p>Whenever new artifacts are added to the repository, either by
  @ push or using the web interface or by "fossil commit" or similar,
  @ an entry is made in the RCVFROM table
  @ to record the source of those artifacts.  This log facilitates
  @ finding and fixing attempts to inject illicit content into the
  @ repository.</p>
  @
  @ <p>Click on the "rcvid" to show a list of specific artifacts received
  @ by a transaction.  After identifying illicit artifacts, remove them
  @ using the "Shun" button.  If an "rcvid" is not hyperlinked, that means
  @ all artifacts associated with that rcvid have already been shunned
  @ or purged.</p>
  @
  @ <table cellpadding="0" cellspacing="0" border="0">
  @ <tr><th style="padding-right: 15px;text-align: right;">rcvid</th>
  @     <th style="padding-right: 15px;text-align: left;">Date</th>
  @     <th style="padding-right: 15px;text-align: left;">User</th>
  @     <th style="padding-right: 15px;text-align: left;">Hash</th>
  @     <th style="text-align: left;">IP&nbsp;Address</th></tr>
  cnt = 0;
  while( db_step(&q)==SQLITE_ROW ){
    int rcvid = db_column_int(&q, 0);
    const char *zUser = db_column_text(&q, 1);
    const char *zDate = db_column_text(&q, 2);
    const char *zIpAddr = db_column_text(&q, 3);
    int usesSha1 = db_column_int(&q, 5)!=0;
    int usesSha3 = db_column_int(&q, 6)!=0;
    static const char *const zHashType[] = { "", "sha1", "sha3", "both" };
    const char *zHash = zHashType[usesSha1+usesSha3*2];
    if( cnt==perScreen && !showAll ){
      style_submenu_element("Older", "rcvfromlist?ofst=%d", ofst+perScreen);
    }else{
      cnt++;
      @ <tr>
      if( db_column_int(&q,4) ){
        @ <td style="padding-right: 15px;text-align: right;">
        @ <a href="rcvfrom?rcvid=%d(rcvid)">%d(rcvid)</a></td>
      }else{
        @ <td style="padding-right: 15px;text-align: right;">%d(rcvid)</td>
      }
      @ <td style="padding-right: 15px;text-align: left;">%s(zDate)</td>
      @ <td style="padding-right: 15px;text-align: left;">%h(zUser)</td>
      @ <td style="padding-right: 15px;text-align: left;">%s(zHash)</td>
      @ <td style="text-align: left;">%s(zIpAddr)</td>
      @ </tr>
    }
  }
  db_finalize(&q);
  @ </table>
  style_finish_page();
}

/*
** WEBPAGE: rcvfrom
**
** Show a single RCVFROM table entry identified by the rcvid= query
** parameters.  Requires Admin privilege.
*/
void rcvfrom_page(void){
  int rcvid = atoi(PD("rcvid","0"));
  Stmt q;
  int cnt;

  login_check_credentials();
  if( !g.perm.Admin ){
    login_needed(0);
    return;
  }
  style_header("Artifact Receipt %d", rcvid);
  if( db_exists(
    "SELECT 1 FROM blob WHERE rcvid=%d AND"
    " NOT EXISTS (SELECT 1 FROM shun WHERE shun.uuid=blob.uuid)", rcvid)
  ){
    style_submenu_element("Shun All", "shun?shun&rcvid=%d#addshun", rcvid);
  }
  if( db_exists(
    "SELECT 1 FROM blob WHERE rcvid=%d AND"
    " EXISTS (SELECT 1 FROM shun WHERE shun.uuid=blob.uuid)", rcvid)
  ){
    style_submenu_element("Unshun All", "shun?accept&rcvid=%d#delshun", rcvid);
  }
  db_prepare(&q,
    "SELECT login, datetime(rcvfrom.mtime), rcvfrom.ipaddr"
    "  FROM rcvfrom LEFT JOIN user USING(uid)"
    " WHERE rcvid=%d",
    rcvid
  );
  @ <table cellspacing="15" cellpadding="0" border="0">
  @ <tr><th valign="top" align="right">rcvid:</th>
  @ <td valign="top">%d(rcvid)</td></tr>
  if( db_step(&q)==SQLITE_ROW ){
    const char *zUser = db_column_text(&q, 0);
    const char *zDate = db_column_text(&q, 1);
    const char *zIpAddr = db_column_text(&q, 2);
    @ <tr><th valign="top" align="right">User:</th>
    @ <td valign="top">%s(zUser)</td></tr>
    @ <tr><th valign="top" align="right">Date:</th>
    @ <td valign="top">%s(zDate)</td></tr>
    @ <tr><th valign="top" align="right">IP&nbsp;Address:</th>
    @ <td valign="top">%s(zIpAddr)</td></tr>
  }
  db_finalize(&q);
  db_multi_exec(
    "CREATE TEMP TABLE toshow(rid INTEGER PRIMARY KEY);"
    "INSERT INTO toshow SELECT rid FROM blob WHERE rcvid=%d", rcvid
  );
  describe_artifacts("IN toshow");
  db_prepare(&q,
    "SELECT blob.rid, blob.uuid, blob.size, description.summary\n"
    "  FROM blob LEFT JOIN description ON (blob.rid=description.rid)"
    " WHERE blob.rcvid=%d", rcvid
  );
  cnt = 0;
  while( db_step(&q)==SQLITE_ROW ){
    const char *zUuid = db_column_text(&q, 1);
    int size = db_column_int(&q, 2);
    const char *zDesc = db_column_text(&q, 3);
    if( zDesc==0 ) zDesc = "";
    if( cnt==0 ){
      @ <tr><th valign="top" align="right">Artifacts:</th>
      @ <td valign="top">
    }
    cnt++;
    @ <a href="%R/info/%s(zUuid)">%s(zUuid)</a>
    @ %h(zDesc) (size: %d(size))<br>
  }
  if( cnt>0 ){
    @ <p>
    if( db_exists(
      "SELECT 1 FROM blob WHERE rcvid=%d AND"
      " NOT EXISTS (SELECT 1 FROM shun WHERE shun.uuid=blob.uuid)", rcvid)
    ){
      @ <form action='%R/shun'>
      @ <input type="hidden" name="shun">
      @ <input type="hidden" name="rcvid" value='%d(rcvid)'>
      @ <input type="submit" value="Shun All These Artifacts">
      @ </form>
    }
    if( db_exists(
      "SELECT 1 FROM blob WHERE rcvid=%d AND"
      " EXISTS (SELECT 1 FROM shun WHERE shun.uuid=blob.uuid)", rcvid)
    ){
      @ <form action='%R/shun'>
      @ <input type="hidden" name="unshun">
      @ <input type="hidden" name="rcvid" value='%d(rcvid)'>
      @ <input type="submit" value="Unshun All These Artifacts">
      @ </form>
    }
    @ </td></tr>
  }
  if( db_table_exists("repository","unversioned") ){
    cnt = 0;
    if( PB("uvdelete") && PB("confirmdelete") ){
      db_multi_exec(
        "DELETE FROM unversioned WHERE rcvid=%d", rcvid
      );
    }
    db_finalize(&q);
    db_prepare(&q,
      "SELECT name, hash, sz\n"
      "  FROM unversioned "
      " WHERE rcvid=%d", rcvid
    );
    while( db_step(&q)==SQLITE_ROW ){
      const char *zName = db_column_text(&q,0);
      const char *zHash = db_column_text(&q,1);
      int size = db_column_int(&q,2);
      int isDeleted = zHash==0;
      if( cnt==0 ){
        @ <tr><th valign="top" align="right">Unversioned&nbsp;Files:</th>
        @ <td valign="top">
      }
      cnt++;
      if( isDeleted ){
        @ %h(zName) (deleted)<br>
      }else{
        @ <a href="%R/uv/%h(zName)">%h(zName)</a> (size: %d(size))<br>
      }
    }
    if( cnt>0 ){
      @ <p><form action='%R/rcvfrom'>
      @ <input type="hidden" name="rcvid" value='%d(rcvid)'>
      @ <input type="hidden" name="uvdelete" value="1">
      if( PB("uvdelete") ){
        @ <input type="hidden" name="confirmdelete" value="1">
        @ <input type="submit" value="Confirm Deletion of These Files">
      }else{
        @ <input type="submit" value="Delete These Unversioned Files">
      }
      @ </form>
      @ </td></tr>
    }
  }
  @ </table>
  db_finalize(&q);
  style_finish_page();
}
