/* This file was automatically generated.  Do not edit! */
#undef INTERFACE
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
void usage(const char *zFormat);
#if defined(FOSSIL_ENABLE_JSON) && defined(FOSSIL_ENABLE_JSON)
void json_cmd_top(void);
void json_page_top(void);
#endif
#if defined(FOSSIL_ENABLE_JSON)
cson_value *json_page_wiki(void);
cson_value *json_page_whoami(void);
cson_value *json_page_timeline(void);
cson_value *json_page_settings(void);
cson_value *json_page_status(void);
cson_value *json_page_status();
cson_value *json_page_finfo(void);
cson_value *json_page_finfo(void);
cson_value *json_page_config(void);
cson_value *json_page_config(void);
cson_value *json_page_user(void);
cson_value *json_page_user(void);
cson_value *json_page_tag(void);
cson_value *json_page_tag(void);
cson_value *json_page_report(void);
cson_value *json_page_report(void);
cson_value *json_page_query(void);
cson_value *json_page_query(void);
cson_value *json_page_logout(void);
cson_value *json_page_logout(void);
cson_value *json_page_login(void);
cson_value *json_page_login(void);
cson_value *json_page_dir(void);
cson_value *json_page_dir(void);
cson_value *json_page_diff(void);
cson_value *json_page_diff(void);
cson_value *json_page_branch(void);
cson_value *json_page_branch(void);
cson_value *json_page_artifact(void);
cson_value *json_page_artifact(void);
cson_value *json_page_anon_password(void);
cson_value *json_page_anon_password(void);
#endif
void db_end_transaction(int rollbackFlag);
int rebuild_db(int doOut,int doClustering);
void db_begin_transaction_real(const char *zStartFile,int iStartLine);
#define db_begin_transaction()    db_begin_transaction_real(__FILE__,__LINE__)
void db_open_repository(const char *zDbName);
void db_close(int reportErrors);
#if defined(FOSSIL_ENABLE_JSON)
cson_value *json_page_dispatch_helper(JsonPageDef const *pages);
#endif
typedef struct Blob Blob;
void blob_init(Blob *pBlob,const char *zData,int size);
#if defined(FOSSIL_ENABLE_JSON)
void json_dispatch_missing_args_err(JsonPageDef const *pCommands,char const *zErrPrefix);
#endif
char *db_text(const char *zDefault,const char *zSql,...);
typedef struct Stmt Stmt;
int db_column_int(Stmt *pStmt,int N);
i64 db_column_int64(Stmt *pStmt,int N);
int db_int(int iDflt,const char *zSql,...);
#include <stdlib.h>
#define ExtFILE    0  /* Always follow symlinks */
#include <dirent.h>
i64 file_size(const char *zFilename,int eFType);
char *db_get(const char *zName,const char *zDefault);
#if defined(FOSSIL_ENABLE_JSON)
cson_value *json_page_stat(void);
cson_value *json_page_cap(void);
#endif
#define RELEASE_VERSION_NUMBER 22600
#define RELEASE_VERSION "2.26"
#define MANIFEST_YEAR "2025"
#define MANIFEST_DATE "2025-04-30 16:57:32"
#define MANIFEST_VERSION "[1205ec86cb]"
#if defined(FOSSIL_ENABLE_JSON)
cson_value *json_page_version(void);
cson_value *json_page_resultCodes(void);
cson_value *json_value_to_bool(cson_value const *zVal);
#endif
char *info_tags_of_checkin(int rid,int propagatingOnly);
#if defined(FOSSIL_ENABLE_JSON)
cson_value *json_tags_for_checkin_rid(int rid,int propagatingOnly);
#endif
int db_finalize(Stmt *pStmt);
int db_prepare(Stmt *pStmt,const char *zFormat,...);
struct Blob {
  unsigned int nUsed;            /* Number of bytes used in aData[] */
  unsigned int nAlloc;           /* Number of bytes allocated for aData[] */
  unsigned int iCursor;          /* Next character of input to parse */
  unsigned int blobFlags;        /* One or more BLOBFLAG_* bits */
  char *aData;                   /* Where the information is stored */
  void (*xRealloc)(Blob*, unsigned int); /* Function to reallocate the buffer */
};
struct Stmt {
  Blob sql;               /* The SQL for this statement */
  sqlite3_stmt *pStmt;    /* The results of sqlite3_prepare_v2() */
  Stmt *pNext, *pPrev;    /* List of all unfinalized statements */
  int nStep;              /* Number of sqlite3_step() calls */
  int rc;                 /* Error from db_vprepare() */
};
extern const struct Stmt empty_Stmt;
#if defined(FOSSIL_ENABLE_JSON)
cson_value *json_sql_to_array_of_obj(Blob *pSql,cson_array *pTgt,int resetBlob);
cson_value *json_stmt_to_array_of_values(Stmt *pStmt,int resultColumn,cson_array *pTgt);
cson_value *json_stmt_to_array_of_array(Stmt *pStmt,cson_array *pTgt);
#endif
int db_step(Stmt *pStmt);
#if defined(FOSSIL_ENABLE_JSON)
cson_value *json_stmt_to_array_of_obj(Stmt *pStmt,cson_array *pTgt);
#endif
char *mprintf(const char *zFormat,...);
#if defined(FOSSIL_ENABLE_JSON)
int json_set_err(int code,char const *fmt,...);
void json_err(int code,char const *msg,int alsoOutput);
#endif
sqlite3_uint64 fossil_timer_stop(int timerId);
int fossil_timer_is_active(int timerId);
#define MANIFEST_UUID "1205ec86cb5508e94b90698db2900997fe5c9db62429c67ac6fdc03d59aa2782"
#if defined(FOSSIL_ENABLE_JSON)
cson_value *json_cap_value();
cson_value *json_g_to_json();
#endif
#define blob_buffer(X)  ((X)->aData)
void blob_appendf(Blob *pBlob,const char *zFormat,...);
void fossil_warning(const char *zFormat,...);
extern const Blob empty_blob;
#if defined(FOSSIL_ENABLE_JSON)
cson_value *json_new_timestamp(cson_int_t timeVal);
cson_int_t json_timestamp();
#endif
i64 db_int64(i64 iDflt,const char *zSql,...);
#if defined(FOSSIL_ENABLE_JSON)
cson_value *json_julian_to_timestamp(double j);
JsonPageDef const *json_handler_for_name(char const *name,JsonPageDef const *head);
char const *json_auth_token_cstr();
#endif
#define OPEN_ANY_SCHEMA         0x002   /* Do not error if schema is wrong */
void db_find_and_open_repository(int bFlags,int nArgUsed);
void login_check_credentials(void);
void blob_reset(Blob *pBlob);
#if defined(FOSSIL_ENABLE_JSON)
void cgi_parse_POST_JSON(Blob *pIn);
#endif
void fossil_fclose(FILE *f);
int blob_read_from_channel(Blob *pBlob,FILE *in,int nToRead);
NORETURN void fossil_fatal(const char *zFormat,...);
FILE *fossil_fopen(const char *zName,const char *zMode);
void blobReallocMalloc(Blob *pBlob,unsigned int newSize);
#define BLOB_INITIALIZER  {0,0,0,0,0,blobReallocMalloc}
#if defined(FOSSIL_ENABLE_JSON)
void json_bootstrap_late();
cson_value *json_string_split2(char const *zStr,char separator,int doDeHttp);
#endif
int dehttpize(char *z);
void *fossil_malloc(size_t n);
int fossil_isspace(char c);
#if defined(FOSSIL_ENABLE_JSON)
int json_string_split(char const *zStr,char separator,int doDeHttp,cson_array *target);
void json_warn(int code,char const *fmt,...);
#endif
int fossil_timer_start();
#if defined(FOSSIL_ENABLE_JSON)
void json_bootstrap_early(void);
int json_is_bootstrapped_early(void);
cson_value *json_req_payload_get(char const *pKey);
#endif
const char *cgi_parameter(const char *zName,const char *zDefault);
#define P(x)          cgi_parameter((x),0)
void cgi_replace_parameter(const char *zName,const char *zValue);
char *login_cookie_name(void);
#if defined(FOSSIL_ENABLE_JSON)
cson_value *json_auth_token();
#endif
void cgi_printf(const char *zFormat,...);
void cgi_set_content_type(const char *zType);
void cgi_reset_content(void);
#if defined(FOSSIL_ENABLE_JSON)
void json_send_response(cson_value const *pResponse);
#endif
int fossil_strcmp(const char *zA,const char *zB);
#if defined(FOSSIL_ENABLE_JSON)
int json_can_consume_content_type(const char *zType);
char const *json_guess_content_type();
int json_find_option_int(char const *zKey,char const *zCLILong,char const *zCLIShort,int dflt);
int json_find_option_bool(char const *zKey,char const *zCLILong,char const *zCLIShort,int dflt);
char const *json_find_option_cstr(char const *zKey,char const *zCLILong,char const *zCLIShort);
char const *json_command_arg(unsigned short ndx);
#endif
const char *find_option(const char *zLong,const char *zShort,int hasArg);
#if defined(FOSSIL_ENABLE_JSON)
char const *json_find_option_cstr2(char const *zKey,char const *zCLILong,char const *zCLIShort,int argPos);
char const *json_getenv_cstr(char const *zKey);
int json_getenv_bool(char const *pKey,int dflt);
int json_getenv_int(char const *pKey,int dflt);
int json_setenv(char const *zKey,cson_value *v);
#endif
char *fossil_getenv(const char *zName);
#define PD(x,y)       cgi_parameter((x),(y))
#if defined(FOSSIL_ENABLE_JSON)
cson_value *json_getenv(char const *zKey);
cson_value *json_new_int(i64 v);
#endif
void fossil_free(void *p);
void fossil_free(void *);
char *vmprintf(const char *zFormat,va_list ap);
#if defined(FOSSIL_ENABLE_JSON)
cson_value *json_new_string_f(char const *fmt,...);
cson_value *json_new_string(char const *str);
cson_value *json_rc_string(int code);
#endif
NORETURN void fossil_exit(int rc);
#if defined(FOSSIL_ENABLE_JSON)
void json_gc_add(char const *key,cson_value *v);
char const *json_rc_cstr(int code);
#endif
void cgi_append_content(const char *zData,int nAmt);
#if defined(FOSSIL_ENABLE_JSON)
int cson_data_dest_cgi(void *pState,void const *src,unsigned int n);
#endif
#define blob_size(X)  ((X)->nUsed)
char *blob_str(Blob *p);
#if defined(FOSSIL_ENABLE_JSON)
cson_value *cson_parse_Blob(Blob *pSrc,cson_parse_info *pInfo);
int cson_output_Blob(cson_value const *pVal,Blob *pDest,cson_output_opt const *pOpt);
#endif
void blob_append(Blob *pBlob,const char *aData,int nData);
#if defined(FOSSIL_ENABLE_JSON)
int cson_data_dest_Blob(void *pState,void const *src,unsigned int n);
cson_value *json_page_nyi();
int fossil_has_json();
#endif
typedef struct ReCompiled ReCompiled;
void re_free(ReCompiled *pRe);
int re_match(ReCompiled *pRe,const unsigned char *zIn,int nIn);
const char *re_compile(ReCompiled **ppRe,const char *zIn,int noCase);
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
  int nInit;                  /* Number of characters in zInit */
  unsigned nState;            /* Number of entries in aOp[] and aArg[] */
  unsigned nAlloc;            /* Slots allocated for aOp[] and aArg[] */
};
typedef struct Global Global;
typedef struct Th_Interp Th_Interp;
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
  char Query;            /* q: create new reports */
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
  int isHuman;            /* True if access by a human, not a spider or bot */
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
#if defined(FOSSIL_ENABLE_JSON)
int json_request_is_json_api(const char *zPathInfo);
extern const FossilJsonKeys_ FossilJsonKeys;
#endif
#define INTERFACE 0
