/* This file was automatically generated.  Do not edit! */
#undef INTERFACE
void rptview_page_content(const char *defaultTitleSearch,int pageWrap,int redirectMissing);
char *db_get(const char *zName,const char *zDefault);
int search_screen(unsigned srchAllowed,int mFlags);
void view_list(void);
void tkt_srchpage(void);
void tkt_home_page(void);
#define SRCH_TKT      0x0004    /* Search over tickets */
unsigned int search_restrict(unsigned int srchFlags);
#define T_ALL         0x00007
#define T_REPLIST     0x00002
#define T_SRCH        0x00001
#define INTERFACE 0
void defossilize(char *z);
int get_comment_format();
int comment_print(const char *zText,const char *zOrigText,int indent,int width,int flags);
typedef struct Blob Blob;
void blob_set(Blob *pBlob,const char *zStr);
void fossil_print(const char *zFormat,...);
enum eTktShowEnc { tktNoTab=0, tktFossilize=1 };
typedef enum eTktShowEnc eTktShowEnc;
typedef enum eTktShowEnc tTktShowEncoding;
void rptshow(const char *zRep,const char *zSepIn,const char *zFilter,tTktShowEncoding enc);
void rpt_list_reports(void);
#if defined(FOSSIL_ENABLE_TCL)
#include "tcl.h"
#endif
#if defined(FOSSIL_ENABLE_JSON)
#include "cson_amalgamation.h"
#include "json_detail.h"
#endif
#if defined(HAVE_BACKTRACE)
#include <execinfo.h>
#endif
const char *find_option(const char *zLong,const char *zShort,int hasArg);
int user_select(void);
void ticket_cmd(void);
void blob_append(Blob *pBlob,const char *aData,int nData);
#define blob_buffer(X)  ((X)->aData)
#define blob_size(X)  ((X)->nUsed)
#define blob_appendb(dest, src) \
  blob_append((dest), blob_buffer(src), blob_size(src))
typedef struct DiffConfig DiffConfig;
int *text_diff(Blob *pA_Blob,Blob *pB_Blob,Blob *pOut,DiffConfig *pCfg);
#define DIFF_LINENO            0x00000040 /* Show line numbers */
#define DIFF_HTML              0x00000020 /* Render for HTML */
DiffConfig *construct_diff_flags(int diffType,DiffConfig *pCfg);
typedef unsigned int u32;
typedef struct ReCompiled ReCompiled;
struct DiffConfig {
  u64 diffFlags;           /* Diff flags */
  int nContext;            /* Number of lines of context */
  int wColumn;             /* Column width in -y mode */
  u32 nFile;               /* Number of files diffed so far */
  const char *zDiffCmd;    /* External diff command to use instead of builtin */
  const char *zBinGlob;    /* GLOB pattern for binary files */
  ReCompiled *pRe;         /* Show only changes matching this pattern */
  const char *zLeftHash;   /* HASH-id of the left file */
  const char *azLabel[2];  /* Optional labels for left and right files */
};
void blob_init(Blob *pBlob,const char *zData,int size);
void blobReallocMalloc(Blob *pBlob,unsigned int newSize);
#define BLOB_INITIALIZER  {0,0,0,0,0,blobReallocMalloc}
typedef struct Manifest Manifest;
void ticket_output_change_artifact(Manifest *pTkt,const char *zListType,int n,Blob *aLastVal);
int content_get(int rid,Blob *pBlob);
void hyperlink_to_date(const char *zDate,const char *zSuffix);
void hyperlink_to_user(const char *zU,const char *zD,const char *zSuf);
char *href(const char *zFormat,...);
void tkthistory_page(void);
void canonical16(char *z,int n);
void tkttimeline_page(void);
#define TIMELINE_REFS     0x8000000 /* Output intended for References tab */
#define TIMELINE_NOTKT    0x2000000 /* Omit extra ticket classes */
#define TIMELINE_GRAPH    0x0000008 /* Compute a graph */
#define TIMELINE_DISJOINT 0x0000010 /* Elements are not contiguous */
#define TIMELINE_ARTID    0x0000001 /* Show artifact IDs on non-check-in lines*/
typedef struct Stmt Stmt;
typedef struct Matcher Matcher;
void www_print_timeline(Stmt *pQuery,int tmFlags,const char *zThisUser,const char *zThisTag,Matcher *pLeftBranch,int selectedRid,int secondRid,void(*xExtra)(int));
const char *timeline_query_for_www(void);
char *ticket_schema_check(const char *zSchema);
const char *ticket_editpage_code(void);
#define HNAME_LEN_SHA1   40
NORETURN void cgi_redirectf(const char *zFormat,...);
void tktedit_page(void);
void captcha_generate(int mFlags);
#define TH_RETURN   3
typedef struct Th_Interp Th_Interp;
typedef int(*Th_CommandProc)(Th_Interp *,void *,int,const char **,int *);
int Th_CreateCommand(Th_Interp *interp,const char *zName,Th_CommandProc xProc,void *pContext,void(*xDel)(Th_Interp *,void *));
const char *ticket_newpage_code(void);
void form_begin(const char *zOtherArgs,const char *zAction,...);
#define T_NEW         0x00004
#define T_ALL_BUT(x)  (T_ALL&~(x))
void ticket_standard_submenu(unsigned int ok);
NORETURN void cgi_redirect(const char *zURL);
void tktnew_page(void);
char *blob_str(Blob *p);
int md5sum_blob(const Blob *pIn,Blob *pCksum);
const char *login_name(void);
char *db_conceal(const char *zContent,int n);
int fossil_isspace(char c);
char *fossilize(const char *zIn,int nIn);
void blob_appendf(Blob *pBlob,const char *zFormat,...);
char *date_in_standard_format(const char *zInputDate);
int captcha_is_correct(int bAlwaysNeeded);
int cgi_csrf_safe(int securityLevel);
#define MC_PERMIT_HOOKS   1  /*  permit hooks to execute    */
int manifest_crosslink_end(int flags);
int blob_is_reset(Blob *pBlob);
#define MC_NONE           0  /*  default handling           */
int manifest_crosslink(int rid,Blob *pContent,int flags);
void db_add_unsent(int rid);
void moderation_table_create(void);
int content_deltify(int rid,int *aSrc,int nSrc,int force);
void *fossil_malloc(size_t n);
int content_put_ex(Blob *pBlob,const char *zUuid,int srcId,int nBlob,int isPrivate);
void manifest_crosslink_begin(void);
#define TH_OK       0
#define TH_ERROR    1
int Th_ErrorMessage(Th_Interp *,const char *,const char *,int);
#define TH1_SIGN          0x80000000
#define TH1_MX_STRLEN     0x0fffffff      /* Maximum length of a TH1-C string */
#define TH1_LEN(X)        ((TH1_SIGN|TH1_MX_STRLEN)&(X))
int Th_WrongNumArgs(Th_Interp *interp,const char *zMsg);
void style_finish_page();
void attachment_list(const char *zTarget,const char *zHeader,int fHorizontalRule);
int Th_Render(const char *z);
#define DOCSRC_TICKET     3     /* Document is a ticket comment */
void safe_html_context(int eTrust);
const char *ticket_viewpage_code(void);
void Th_Trace(const char *zFormat,...);
void tkt_draw_timeline(int tagid,const char *zType);
void style_header(const char *zTitleFormat,...);
void style_set_current_feature(const char *zFeature);
void style_submenu_element(const char *zLabel,const char *zLink,...);
void login_needed(int anonOk);
void login_check_credentials(void);
void tktview_page(void);
void cgi_printf(const char *zFormat,...);
NORETURN void fossil_fatal(const char *zFormat,...);
char *db_text(const char *zDefault,const char *zSql,...);
void usage(const char *zFormat);
void db_find_and_open_repository(int bFlags,int nArgUsed);
void test_ticket_rebuild(void);
int validate16(const char *zIn,int nIn);
void db_begin_transaction_real(const char *zStartFile,int iStartLine);
#define db_begin_transaction()    db_begin_transaction_real(__FILE__,__LINE__)
void ticket_rebuild(void);
void db_init_database(const char *zFileName,const char *zSchema,...);
void db_end_transaction(int rollbackFlag);
int db_transaction_nesting_depth(void);
char *ticket_table_schema(void);
void ticket_create_table(int separateConnection);
void db_clear_authorizer(void);
void ticket_unrestrict_sql(void);
void db_set_authorizer(int(*xAuth)(void *,int,const char *,const char *,const char *,const char *),void *pArg,const char *zName);
void ticket_restrict_sql(int *pNErr);
const char *ticket_change_code(void);
int ticket_change(const char *zUuid);
int Th_Eval(Th_Interp *interp,int iFrame,const char *zProg,int nProg);
const char *ticket_common_code(void);
#define TH_INIT_NONE        ((u32)0x00000000) /* No flags. */
#define TH_INIT_DEFAULT     (TH_INIT_NONE)      /* Default flags. */
void Th_FossilInit(u32 flags);
void ticket_init(void);
void blobarray_delete(Blob *aBlob,int n);
void manifest_destroy(Manifest *p);
void manifest_ticket_event(int rid,const Manifest *pManifest,int isNew,int tktTagId);
#define CFTYPE_TICKET     5
Manifest *manifest_get(int rid,int cfType,Blob *pErr);
int db_column_int(Stmt *pStmt,int N);
Blob *blobarray_new(int n);
void search_doc_touch(char cType,int rid,const char *zName);
int db_int(int iDflt,const char *zSql,...);
int tag_findid(const char *zTag,int createFlag);
void ticket_rebuild_entry(const char *zTktUuid);
int db_get_boolean(const char *zName,int dflt);
typedef struct Global Global;
struct Blob {
  unsigned int nUsed;            /* Number of bytes used in aData[] */
  unsigned int nAlloc;           /* Number of bytes allocated for aData[] */
  unsigned int iCursor;          /* Next character of input to parse */
  unsigned int blobFlags;        /* One or more BLOBFLAG_* bits */
  char *aData;                   /* Where the information is stored */
  void (*xRealloc)(Blob*, unsigned int); /* Function to reallocate the buffer */
};
typedef struct UrlData UrlData;
struct UrlData {
  int isFile;           /* True if a "file:" url */
  int isHttps;          /* True if a "https:" url */
  int isSsh;            /* True if an "ssh:" url */
  int isAlias;          /* Input URL was an alias */
  char *name;           /* Hostname for http: or filename for file: */
  char *hostname;       /* The HOST: parameter on http headers */
  const char *protocol; /* "http" or "https" or "ssh" or "file" */
  int port;             /* TCP port number for http: or https: */
  int dfltPort;         /* The default port for the given protocol */
  char *path;           /* Pathname for http: */
  char *user;           /* User id for http: */
  char *passwd;         /* Password for http: */
  char *canonical;      /* Canonical representation of the URL */
  char *proxyAuth;      /* Proxy-Authorizer: string */
  char *fossil;         /* The fossil query parameter on ssh: */
  char *pwConfig;       /* CONFIG table entry that gave us the password */
  unsigned flags;       /* Boolean flags controlling URL processing */
  int useProxy;         /* Used to remember that a proxy is in use */
  int proxyOrigPort;       /* Tunneled port number for https through proxy */
  char *proxyUrlPath;      /* Remember path when proxy is use */
  char *proxyUrlCanonical; /* Remember canonical path when proxy is use */
};
typedef struct FossilUserPerms FossilUserPerms;
struct FossilUserPerms {
  char Setup;            /* s: use Setup screens on web interface */
  char Admin;            /* a: administrative permission */
  char Password;         /* p: change password */
  char Write;            /* i: xfer inbound. check-in */
  char Read;             /* o: xfer outbound. check-out */
  char Hyperlink;        /* h: enable the display of hyperlinks */
  char Clone;            /* g: clone */
  char RdWiki;           /* j: view wiki via web */
  char NewWiki;          /* f: create new wiki via web */
  char ApndWiki;         /* m: append to wiki via web */
  char WrWiki;           /* k: edit wiki via web */
  char ModWiki;          /* l: approve and publish wiki content (Moderator) */
  char RdTkt;            /* r: view tickets via web */
  char NewTkt;           /* n: create new tickets */
  char ApndTkt;          /* c: append to tickets via the web */
  char WrTkt;            /* w: make changes to tickets via web */
  char ModTkt;           /* q: approve and publish ticket changes (Moderator) */
  char Attach;           /* b: add attachments */
  char TktFmt;           /* t: create new ticket report formats */
  char RdAddr;           /* e: read email addresses or other private data */
  char Zip;              /* z: download zipped artifact via /zip URL */
  char Private;          /* x: can send and receive private content */
  char WrUnver;          /* y: can push unversioned content */
  char RdForum;          /* 2: Read forum posts */
  char WrForum;          /* 3: Create new forum posts */
  char WrTForum;         /* 4: Post to forums not subject to moderation */
  char ModForum;         /* 5: Moderate (approve or reject) forum posts */
  char AdminForum;       /* 6: Grant capability 4 to other users */
  char EmailAlert;       /* 7: Sign up for email notifications */
  char Announce;         /* A: Send announcements */
  char Chat;             /* C: read or write the chatroom */
  char Debug;            /* D: show extra Fossil debugging features */
  /* These last two are included to block infinite recursion */
  char XReader;          /* u: Inherit all privileges of "reader" */
  char XDeveloper;       /* v: Inherit all privileges of "developer" */
};
#if defined(FOSSIL_ENABLE_TCL)
typedef struct TclContext TclContext;
struct TclContext {
  int argc;              /* Number of original (expanded) arguments. */
  char **argv;           /* Full copy of the original (expanded) arguments. */
  void *hLibrary;        /* The Tcl library module handle. */
  void *xFindExecutable; /* See tcl_FindExecutableProc in th_tcl.c. */
  void *xCreateInterp;   /* See tcl_CreateInterpProc in th_tcl.c. */
  void *xDeleteInterp;   /* See tcl_DeleteInterpProc in th_tcl.c. */
  void *xFinalize;       /* See tcl_FinalizeProc in th_tcl.c. */
  Tcl_Interp *interp;    /* The on-demand created Tcl interpreter. */
  int useObjProc;        /* Non-zero if an objProc can be called directly. */
  int useTip285;         /* Non-zero if TIP #285 is available. */
  char *setup;           /* The optional Tcl setup script. */
  void *xPreEval;        /* Optional, called before Tcl_Eval*(). */
  void *pPreContext;     /* Optional, provided to xPreEval(). */
  void *xPostEval;       /* Optional, called after Tcl_Eval*(). */
  void *pPostContext;    /* Optional, provided to xPostEval(). */
};
#endif
#define MX_AUX  5
struct Global {
  int argc; char **argv;  /* Command-line arguments to the program */
  char **argvOrig;        /* Original g.argv prior to removing options */
  char *nameOfExe;        /* Full path of executable. */
  const char *zErrlog;    /* Log errors to this file, if not NULL */
  const char *zPhase;     /* Phase of operation, for use by the error log
                          ** and for deriving $canonical_page TH1 variable */
  int isConst;            /* True if the output is unchanging & cacheable */
  const char *zVfsName;   /* The VFS to use for database connections */
  sqlite3 *db;            /* The connection to the databases */
  sqlite3 *dbConfig;      /* Separate connection for global_config table */
  char *zAuxSchema;       /* Main repository aux-schema */
  int dbIgnoreErrors;     /* Ignore database errors if true */
  char *zConfigDbName;    /* Path of the config database. NULL if not open */
  sqlite3_int64 now;      /* Seconds since 1970 */
  int repositoryOpen;     /* True if the main repository database is open */
  unsigned iRepoDataVers;  /* Initial data version for repository database */
  char *zRepositoryOption; /* Most recent cached repository option value */
  char *zRepositoryName;  /* Name of the repository database file */
  char *zLocalDbName;     /* Name of the local database file */
  char *zOpenRevision;    /* Check-in version to use during database open */
  const char *zCmdName;   /* Name of the Fossil command currently running */
  int localOpen;          /* True if the local database is open */
  char *zLocalRoot;       /* The directory holding the  local database */
  int minPrefix;          /* Number of digits needed for a distinct hash */
  int eHashPolicy;        /* Current hash policy.  One of HPOLICY_* */
  int fSqlTrace;          /* True if --sqltrace flag is present */
  int fSqlStats;          /* True if --sqltrace or --sqlstats are present */
  int fSqlPrint;          /* True if --sqlprint flag is present */
  int fCgiTrace;          /* True if --cgitrace is enabled */
  int fQuiet;             /* True if -quiet flag is present */
  int fJail;              /* True if running with a chroot jail */
  int fHttpTrace;         /* Trace outbound HTTP requests */
  int fAnyTrace;          /* Any kind of tracing */
  int fAllowACME;         /* Deliver files from .well-known */
  char *zHttpAuth;        /* HTTP Authorization user:pass information */
  int fSystemTrace;       /* Trace calls to fossil_system(), --systemtrace */
  int fSshTrace;          /* Trace the SSH setup traffic */
  int fSshClient;         /* HTTP client flags for SSH client */
  int fNoHttpCompress;    /* Do not compress HTTP traffic (for debugging) */
  char *zSshCmd;          /* SSH command string */
  const char *zHttpCmd;   /* External program to do HTTP requests */
  int fNoSync;            /* Do not do an autosync ever.  --nosync */
  int fIPv4;              /* Use only IPv4, not IPv6. --ipv4 */
  char *zPath;            /* Name of webpage being served (may be NULL) */
  char *zExtra;           /* Extra path information past the webpage name */
  char *zBaseURL;         /* Full text of the URL being served */
  char *zHttpsURL;        /* zBaseURL translated to https: */
  char *zTop;             /* Parent directory of zPath */
  int nExtraURL;          /* Extra bytes added to SCRIPT_NAME */
  const char *zExtRoot;   /* Document root for the /ext sub-website */
  const char *zContentType;  /* The content type of the input HTTP request */
  int iErrPriority;       /* Priority of current error message */
  char *zErrMsg;          /* Text of an error message */
  int sslNotAvailable;    /* SSL is not available.  Do not redirect to https: */
  Blob cgiIn;             /* Input to an xfer www method */
  int cgiOutput;          /* 0: command-line 1: CGI. 2: after CGI */
  int xferPanic;          /* Write error messages in XFER protocol */
  int fullHttpReply;      /* True for full HTTP reply.  False for CGI reply */
  Th_Interp *interp;      /* The TH1 interpreter */
  char *th1Setup;         /* The TH1 post-creation setup script, if any */
  int th1Flags;           /* The TH1 integration state flags */
  FILE *httpIn;           /* Accept HTTP input from here */
  FILE *httpOut;          /* Send HTTP output here */
  int httpUseSSL;         /* True to use an SSL codec for HTTP traffic */
  void *httpSSLConn;      /* The SSL connection */
  int xlinkClusterOnly;   /* Set when cloning.  Only process clusters */
  int fTimeFormat;        /* 1 for UTC.  2 for localtime.  0 not yet selected */
  int *aCommitFile;       /* Array of files to be committed */
  int markPrivate;        /* All new artifacts are private if true */
  char *ckinLockFail;     /* Check-in lock failure received from server */
  int clockSkewSeen;      /* True if clocks on client and server out of sync */
  int wikiFlags;          /* Wiki conversion flags applied to %W */
  char isHTTP;            /* True if server/CGI modes, else assume CLI. */
  char jsHref;            /* If true, set href= using javascript, not HTML */
  Blob httpHeader;        /* Complete text of the HTTP request header */
  UrlData url;            /* Information about current URL */
  const char *zLogin;     /* Login name.  NULL or "" if not logged in. */
  const char *zCkoutAlias;   /* doc/ uses this branch as an alias for "ckout" */
  const char *zMainMenuFile; /* --mainmenu FILE from server/ui/cgi */
  const char *zSSLIdentity;  /* Value of --ssl-identity option, filename of
                             ** SSL client identity */
  const char *zCgiFile;      /* Name of the CGI file */
  const char *zReqType;      /* Type of request: "HTTP", "CGI", "SCGI" */
#if USE_SEE
  const char *zPidKey;    /* Saved value of the --usepidkey option.  Only
                           * applicable when using SEE on Windows or Linux. */
#endif
  int useLocalauth;       /* No login required if from 127.0.0.1 */
  int noPswd;             /* Logged in without password (on 127.0.0.1) */
  int userUid;            /* Integer user id */
  int isRobot;            /* True if the client is definitely a robot.  False
                          ** negatives are common for this flag */
  int comFmtFlags;        /* Zero or more "COMMENT_PRINT_*" bit flags, should be
                          ** accessed through get_comment_format(). */
  const char *zSockName;  /* Name of the unix-domain socket file */
  const char *zSockMode;  /* File permissions for unix-domain socket */
  const char *zSockOwner; /* Owner, or owner:group for unix-domain socket */

  /* Information used to populate the RCVFROM table */
  int rcvid;              /* The rcvid.  0 if not yet defined. */
  char *zIpAddr;          /* The remote IP address */
  char *zNonce;           /* The nonce used for login */

  /* permissions available to current user */
  struct FossilUserPerms perm;

  /* permissions available to current user or to "anonymous".
  ** This is the logical union of perm permissions above with
  ** the value that perm would take if g.zLogin were "anonymous". */
  struct FossilUserPerms anon;

#ifdef FOSSIL_ENABLE_TCL
  /* all Tcl related context necessary for integration */
  struct TclContext tcl;
#endif

  /* For defense against Cross-site Request Forgery attacks */
  char zCsrfToken[16];    /* Value of the anti-CSRF token */
  int okCsrf;             /* -1:  unsafe
                          **  0:  unknown
                          **  1:  same origin
                          **  2:  same origin + is POST
                          **  3:  same origin, POST, valid csrf token */

  int parseCnt[10];       /* Counts of artifacts parsed */
  FILE *fDebug;           /* Write debug information here, if the file exists */
#ifdef FOSSIL_ENABLE_TH1_HOOKS
  int fNoThHook;          /* Disable all TH1 command/webpage hooks */
#endif
  int thTrace;            /* True to enable TH1 debugging output */
  Blob thLog;             /* Text of the TH1 debugging output */

  int isHome;             /* True if rendering the "home" page */

  /* Storage for the aux() and/or option() SQL function arguments */
  int nAux;                    /* Number of distinct aux() or option() values */
  const char *azAuxName[MX_AUX]; /* Name of each aux() or option() value */
  char *azAuxParam[MX_AUX];      /* Param of each aux() or option() value */
  const char *azAuxVal[MX_AUX];  /* Value of each aux() or option() value */
  const char **azAuxOpt[MX_AUX]; /* Options of each option() value */
  int anAuxCols[MX_AUX];         /* Number of columns for option() values */
  int allowSymlinks;             /* Cached "allow-symlinks" option */
  int mainTimerId;               /* Set to fossil_timer_start() */
  int nPendingRequest;           /* # of HTTP requests in "fossil server" */
  int nRequest;                  /* Total # of HTTP request */
  int bAvoidDeltaManifests;      /* Avoid using delta manifests if true */

  /* State for communicating specific details between the inbound HTTP
  ** header parser (cgi.c), xfer.c, and http.c. */
  struct {
    char *zLoginCard;       /* Inbound "x-f-l-c" Cookie header. */
    int fLoginCardMode;     /* If non-0, emit login cards in outbound
                            ** requests as a HTTP cookie instead of as
                            ** part of the payload. Gets activated
                            ** on-demand based on xfer traffic
                            ** contents. Values, for
                            ** diagnostic/debugging purposes: 0x01=CLI
                            ** --flag, 0x02=cgi_setup_query_string(),
                            ** 0x04=page_xfer(),
                            ** 0x08=client_sync(). */
    int remoteVersion;      /* Remote fossil version. Used for negotiating
                            ** how to handle the login card. */
  } syncInfo;
#ifdef FOSSIL_ENABLE_JSON
  struct FossilJsonBits {
    int isJsonMode;            /* True if running in JSON mode, else
                                  false. This changes how errors are
                                  reported. In JSON mode we try to
                                  always output JSON-form error
                                  responses and always (in CGI mode)
                                  exit() with code 0 to avoid an HTTP
                                  500 error.
                               */
    int preserveRc;            /* Do not convert error codes into 0.
                                * This is primarily intended for use
                                * by the test suite. */
    int resultCode;            /* used for passing back specific codes
                               ** from /json callbacks. */
    int errorDetailParanoia;   /* 0=full error codes, 1=%10, 2=%100, 3=%1000 */
    cson_output_opt outOpt;    /* formatting options for JSON mode. */
    cson_value *authToken;     /* authentication token */
    const char *jsonp;         /* Name of JSONP function wrapper. */
    unsigned char dispatchDepth /* Tells JSON command dispatching
                                   which argument we are currently
                                   working on. For this purpose, arg#0
                                   is the "json" path/CLI arg.
                                */;
    struct {                   /* "garbage collector" */
      cson_value *v;
      cson_array *a;
    } gc;
    struct {                   /* JSON POST data. */
      cson_value *v;
      cson_array *a;
      int offset;              /* Tells us which PATH_INFO/CLI args
                                  part holds the "json" command, so
                                  that we can account for sub-repos
                                  and path prefixes.  This is handled
                                  differently for CLI and CGI modes.
                               */
      const char *commandStr   /*"command" request param.*/;
    } cmd;
    struct {                   /* JSON POST data. */
      cson_value *v;
      cson_object *o;
    } post;
    struct {                   /* GET/COOKIE params in JSON mode. */
      cson_value *v;
      cson_object *o;
    } param;
    struct {
      cson_value *v;
      cson_object *o;
    } reqPayload;              /* request payload object (if any) */
    cson_array *warnings;      /* response warnings */
    int timerId;               /* fetched from fossil_timer_start() */
  } json;
#endif /* FOSSIL_ENABLE_JSON */
  int ftntsIssues[4];     /* Counts for misref, strayed, joined, overnested */
  int diffCnt[3];         /* Counts for DIFF_NUMSTAT: files, ins, del */
};
extern Global g;
#include <stdlib.h>
#include <dirent.h>
char *fossil_getenv(const char *zName);
int ticket_need_moderation(int localUser);
void blob_truncate(Blob *p,int sz);
#define blob_count(X,elType)  (blob_size(X)/sizeof(elType))
# define BKLNK_TICKET     1   /* Ticket body or title */
void backlink_extract(char *zSrc,int mimetype,int srcid,int srctype,double mtime,int replaceFlag);
void fossil_free(void *p);
void fossil_free(void *);
void blob_reset(Blob *pBlob);
int db_bind_double(Stmt *pStmt,const char *zParamName,double rValue);
char *blob_sql_text(Blob *p);
#define blob_append_literal(blob, literal) \
  blob_append((blob), "" literal, (sizeof literal)-1)
int parse_mimetype(const char *zMimetype);
void *fossil_malloc_zero(size_t n);
void *fossil_malloc_zero(size_t);
void blob_append_sql(Blob *pBlob,const char *zFormat,...);
void blob_zero(Blob *pBlob);
int db_last_insert_rowid(void);
int db_multi_exec(const char *zSql,...);
# define MT_NONE       0   /* unspecified */
typedef struct ManifestFile ManifestFile;
struct Manifest {
  Blob content;         /* The original content blob */
  int type;             /* Type of artifact.  One of CFTYPE_xxxxx */
  int rid;              /* The blob-id for this manifest */
  const char *zBaseline;/* Baseline manifest.  The B card. */
  Manifest *pBaseline;  /* The actual baseline manifest */
  char *zComment;       /* Decoded comment.  The C card. */
  double rDate;         /* Date and time from D card.  0.0 if no D card. */
  char *zUser;          /* Name of the user from the U card. */
  char *zRepoCksum;     /* MD5 checksum of the baseline content.  R card. */
  char *zWiki;          /* Text of the wiki page.  W card. */
  char *zWikiTitle;     /* Name of the wiki page. L card. */
  char *zMimetype;      /* Mime type of wiki or comment text.  N card.  */
  char *zThreadTitle;   /* The forum thread title. H card */
  double rEventDate;    /* Date of an event.  E card. */
  char *zEventId;       /* Artifact hash for an event.  E card. */
  char *zTicketUuid;    /* UUID for a ticket. K card. */
  char *zAttachName;    /* Filename of an attachment. A card. */
  char *zAttachSrc;     /* Artifact hash for document being attached. A card. */
  char *zAttachTarget;  /* Ticket or wiki that attachment applies to.  A card */
  char *zThreadRoot;    /* Thread root artifact.  G card */
  char *zInReplyTo;     /* Forum in-reply-to artifact.  I card */
  int nFile;            /* Number of F cards */
  int nFileAlloc;       /* Slots allocated in aFile[] */
  int iFile;            /* Index of current file in iterator */
  ManifestFile *aFile;  /* One entry for each F-card */
  int nParent;          /* Number of parents. */
  int nParentAlloc;     /* Slots allocated in azParent[] */
  char **azParent;      /* Hashes of parents.  One for each P card argument */
  int nCherrypick;      /* Number of entries in aCherrypick[] */
  struct {
    char *zCPTarget;    /* Hash for cherry-picked version w/ +|- prefix */
    char *zCPBase;      /* Hash for cherry-pick baseline. NULL for singletons */
  } *aCherrypick;
  int nCChild;          /* Number of cluster children */
  int nCChildAlloc;     /* Number of closts allocated in azCChild[] */
  char **azCChild;      /* Hashes of referenced objects in a cluster. M cards */
  int nTag;             /* Number of T Cards */
  int nTagAlloc;        /* Slots allocated in aTag[] */
  struct TagType {
    char *zName;           /* Name of the tag */
    char *zUuid;           /* Hash of artifact that the tag is applied to */
    char *zValue;          /* Value if the tag is really a property */
  } *aTag;              /* One for each T card */
  int nField;           /* Number of J cards */
  int nFieldAlloc;      /* Slots allocated in aField[] */
  struct {
    char *zName;           /* Key or field name */
    char *zValue;          /* Value of the field */
  } *aField;            /* One for each J card */
};
const char *cgi_parameter(const char *zName,const char *zDefault);
#define P(x)          cgi_parameter((x),0)
const char *cgi_parameter_name(int i);
void Th_StoreUnsafe(const char *zName,const char *zValue);
double db_column_double(Stmt *pStmt,int N);
char *human_readable_age(double rAge);
void Th_Store(const char *zName,const char *zValue);
char *Th_Fetch(const char *zName,int *pSize);
char *db_reveal(const char *zKey);
const char *db_column_name(Stmt *pStmt,int N);
int db_column_count(Stmt *pStmt);
#define PD(x,y)       cgi_parameter((x),(y))
int db_exists(const char *zSql,...);
int db_reset(Stmt *pStmt);
int db_bind_text(Stmt *pStmt,const char *zParamName,const char *zValue);
char *mprintf(const char *zFormat,...);
int db_finalize(Stmt *pStmt);
char *fossil_strdup(const char *zOrig);
void *fossil_realloc(void *p,size_t n);
void *fossil_realloc(void *,size_t);
const char *db_column_text(Stmt *pStmt,int N);
int db_step(Stmt *pStmt);
int db_prepare(Stmt *pStmt,const char *zFormat,...);
struct Stmt {
  Blob sql;               /* The SQL for this statement */
  sqlite3_stmt *pStmt;    /* The results of sqlite3_prepare_v2() */
  Stmt *pNext, *pPrev;    /* List of all unfinalized statements */
  int nStep;              /* Number of sqlite3_step() calls */
  int rc;                 /* Error from db_vprepare() */
};
int fossil_strcmp(const char *zA,const char *zB);
struct ManifestFile {
  char *zName;           /* Name of a file */
  char *zUuid;           /* Artifact hash for the file */
  char *zPerm;           /* File permissions */
  char *zPrior;          /* Prior name if the name was changed */
};
typedef enum {
  MS_EXACT=1,   /* Exact string comparison */
  MS_GLOB=2,    /* Matches against a list of GLOB patterns. */
  MS_LIKE=3,    /* Matches against a list of LIKE patterns. */
  MS_REGEXP=4,  /* Matches against a list of regular expressions. */
  MS_BRLIST=5,  /* Matches any element of a list */
}MatchStyle;
struct Matcher {
  MatchStyle style;   /* Which algorithm to use */
  int nPattern;       /* How many patterns are their */
  char **azPattern;   /* List of patterns */
  ReCompiled **aRe;   /* List of compiled regular expressions */
};
typedef struct ReInput ReInput;
struct ReInput {
  const unsigned char *z;  /* All text */
  int i;                   /* Next byte to read */
  int mx;                  /* EOF when i>=mx */
};
struct ReCompiled {
  ReInput sIn;                /* Regular expression text */
  const char *zErr;           /* Error message to return */
  char *aOp;                  /* Operators for the virtual machine */
  int *aArg;                  /* Arguments to each operator */
  unsigned (*xNextChar)(ReInput*);  /* Next character function */
  unsigned char zInit[12];    /* Initial text to match */
  int nInit;                  /* Number of bytes in zInit */
  unsigned nState;            /* Number of entries in aOp[] and aArg[] */
  unsigned nAlloc;            /* Slots allocated for aOp[] and aArg[] */
  unsigned mxAlloc;           /* Complexity limit */
};
