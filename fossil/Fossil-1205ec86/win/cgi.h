/* This file was automatically generated.  Do not edit! */
#undef INTERFACE
void cgi_check_for_malice(void);
int cgi_from_mobile(void);
const char *cgi_ssh_remote_addr(const char *zDefault);
void cgi_modified_since(time_t objectTime);
time_t cgi_rfc822_parsedate(const char *zDate);
void test_date(void);
char *cgi_iso8601_datestamp(void);
int fossil_system(const char *zOrigCmd);
void fossil_warning(const char *zFormat,...);
void *fossil_utf8_to_unicode(const char *zUtf8);
void fossil_print(const char *zFormat,...);
#include <stdlib.h>
#include <dirent.h>
void file_set_owner(const char *zFN,int fd,const char *zOwner);
void file_set_mode(const char *zFN,int fd,const char *zMode,int bNoErr);
int file_issocket(const char *zFilename);
#define ExtFILE    0  /* Always follow symlinks */
int file_isdir(const char *zFilename,int eFType);
int cgi_http_server(int mnPort,int mxPort,const char *zBrowser,const char *zIpAddr,int flags);
#define HTTP_SERVER_UNIXSOCKET     0x0040     /* Use a unix-domain socket */
#define HTTP_SERVER_NOFORK         0x0020     /* Do not call fork() */
#define HTTP_SERVER_REPOLIST       0x0010     /* Allow repo listing */
#define HTTP_SERVER_HAD_CHECKOUT   0x0008     /* Was a checkout open? */
#define HTTP_SERVER_HAD_REPOSITORY 0x0004     /* Was the repository open? */
#define HTTP_SERVER_SCGI           0x0002     /* SCGI instead of HTTP */
#define HTTP_SERVER_LOCALHOST      0x0001     /* Bind to 127.0.0.1 only */
void *fossil_malloc(size_t n);
void cgi_handle_scgi_request(void);
typedef struct Blob Blob;
int blob_read_from_channel(Blob *pBlob,FILE *in,int nToRead);
void cgi_handle_ssh_transport(const char *zCmd);
char *cgi_handle_ssh_probes(char *zLine,int zSize,char *z,char *zToken);
void cgi_handle_ssh_http_request(const char *zIpAddr);
int fossil_fileno(FILE *p);
void cgi_handle_http_request(const char *zIpAddr);
char *cgi_remote_ip(int fd);
int cgi_is_loopback(const char *zIpAddr);
void cgi_vprintf(const char *zFormat,va_list ap);
int vxprintf(Blob *pBlob,const char *fmt,va_list ap);
void cgi_tag_query_parameter(const char *zName);
char *cgi_reconstruct_original_url(void);
typedef struct HQuery HQuery;
void url_add_parameter(HQuery *p,const char *zName,const char *zValue);
struct Blob {
  unsigned int nUsed;            /* Number of bytes used in aData[] */
  unsigned int nAlloc;           /* Number of bytes allocated for aData[] */
  unsigned int iCursor;          /* Next character of input to parse */
  unsigned int blobFlags;        /* One or more BLOBFLAG_* bits */
  char *aData;                   /* Where the information is stored */
  void (*xRealloc)(Blob*, unsigned int); /* Function to reallocate the buffer */
};
struct HQuery {
  Blob url;                  /* The URL */
  const char *zBase;         /* The base URL */
  int nParam;                /* Number of parameters. */
  int nAlloc;                /* Number of allocated slots */
  const char **azName;       /* Parameter names */
  const char **azValue;      /* Parameter values */
};
void cgi_query_parameters_to_url(HQuery *p);
void cgi_query_parameters_to_hidden(void);
int cgi_param_info(int N,const char **pzName,const char **pzValue,int *pbIsQP);
void fossil_trace(const char *zFormat,...);
int fossil_strnicmp(const char *zA,const char *zB,int nByte);
int fossil_stricmp(const char *zA,const char *zB);
void cgi_print_all(int showAll,unsigned int eDest,FILE *out);
void cgi_load_environment(void);
int cgi_all(const char *z,...);
int cgi_any(const char *z,...);
void cgi_debug(const char *zFormat,...);
const char *cgi_parameter_name(int i);
int fossil_isdigit(char c);
int is_truth(const char *zVal);
const char *cgi_coalesce(const char *zName,...);
int looks_like_attack(const char *zTxt);
void cgi_value_spider_check(const char *zTxt,const char *zName);
void style_finish_page();
void style_header(const char *zTitleFormat,...);
void style_submenu_enable(int onOff);
void style_set_current_feature(const char *zFeature);
extern const Blob empty_blob;
char *fossil_getenv(const char *zName);
void blob_init(Blob *pBlob,const char *zData,int size);
void cgi_decode_post_parameters(void);
#if defined(FOSSIL_ENABLE_JSON)
#include "json_detail.h"
int json_can_consume_content_type(const char *zType);
#endif
int blob_uncompress(Blob *pIn,Blob *pOut);
int blob_read_from_cgi(Blob *pBlob,int nToRead);
#define SKIN_FROM_COOKIE    4   /* skin= from fossil_display_settings cookie*/
const char *cookie_value(const char *zPName,const char *zDefault);
#if defined(FOSSIL_ENABLE_JSON)
void json_bootstrap_early(void);
int json_request_is_json_api(const char *zPathInfo);
#endif
char *fossil_strndup(const char *zOrig,ssize_t len);
void cgi_init(void);
void cookie_write_parameter(const char *zQP,const char *zPName,const char *zDflt);
#define SKIN_FROM_QPARAM    3   /* skin= query parameter */
char *skin_use_alternative(const char *zName,int rank,int iSource);
int cgi_setup_query_string(void);
FILE *fossil_fopen(const char *zName,const char *zMode);
void cgi_trace(const char *z);
#if defined(FOSSIL_ENABLE_JSON)
void json_err(int code,char const *msg,int alsoOutput);
char const *json_guess_content_type();
void json_gc_add(char const *key,cson_value *v);
cson_value *cson_parse_Blob(Blob *pSrc,cson_parse_info *pInfo);
void cgi_parse_POST_JSON(Blob *pIn);
int json_setenv(char const *zKey,cson_value *v);
#endif
int fossil_isupper(char c);
int fossil_islower(char c);
int fossil_no_strange_characters(const char *z);
int fossil_isspace(char c);
void cgi_setenv(const char *zName,const char *zValue);
int cgi_qp_count(void);
void cgi_delete_query_parameter(const char *zName);
void cgi_delete_parameter(const char *zName);
void cgi_replace_query_parameter_tolower(char *zName,const char *zValue);
void cgi_replace_query_parameter(const char *zName,const char *zValue);
void cgi_replace_parameter(const char *zName,const char *zValue);
void cgi_set_query_parameter(const char *zName,const char *zValue);
void cgi_set_parameter(const char *zName,const char *zValue);
int fossil_tolower(char c);
void cgi_set_parameter_nocopy_tolower(char *zName,const char *zValue,int isQP);
void *fossil_realloc(void *p,size_t n);
void *fossil_realloc(void *,size_t);
void cgi_set_parameter_nocopy(const char *zName,const char *zValue,int isQP);
void cgi_csrf_verify(void);
int cgi_csrf_safe(int securityLevel);
void fossil_errorlog(const char *zFormat,...);
int dehttpize(char *z);
int cgi_same_origin(int bErrorLog);
const char *cgi_referer(const char *zDefault);
void fossil_free(void *p);
void fossil_free(void *);
int fossil_isalnum(char c);
const char *file_tail(const char *z);
void cgi_content_disposition_filename(const char *zFilename);
char *vmprintf(const char *zFormat,va_list ap);
NORETURN void cgi_redirectf(const char *zFormat,...);
NORETURN void cgi_redirect_with_method(const char *zURL);
NORETURN void cgi_redirect(const char *zURL);
NORETURN void cgi_redirect_perm(const char *zURL);
NORETURN void fossil_exit(int rc);
char *mprintf(const char *zFormat,...);
NORETURN void cgi_redirect_with_status(const char *zURL,int iStat,const char *zStat);
void backoffice_check_if_needed(void);
#if defined(FOSSIL_ENABLE_TCL)
#include "tcl.h"
#endif
#if defined(FOSSIL_ENABLE_JSON)
#include "cson_amalgamation.h"
#endif
#if defined(HAVE_BACKTRACE)
#include <execinfo.h>
#endif
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
#define CGIDEBUG(X)  if( g.fDebug ) cgi_debug X
void gzip_finish(Blob *pOut);
void gzip_step(const char *pIn,int nIn);
void gzip_begin(sqlite3_int64 now);
void blob_compress(Blob *pIn,Blob *pOut);
sqlite3_int64 etag_mtime(void);
int etag_maxage(void);
const char *etag_tag(void);
char *cgi_rfc822_datestamp(time_t now);
void cgi_reply(void);
#if defined(FOSSIL_ENABLE_SSL)
size_t ssl_write_server(void *pServerArg,char *zBuf,size_t nBuf);
int ssl_eof(void *pServerArg);
#endif
int cgi_feof(void);
#if defined(FOSSIL_ENABLE_SSL)
size_t ssl_read_server(void *pServerArg,char *zBuf,size_t nBuf,int doLoop);
#endif
size_t cgi_fread(void *ptr,size_t nmemb);
NORETURN void fossil_fatal(const char *zFormat,...);
#if defined(FOSSIL_ENABLE_SSL)
char *ssl_gets(void *pServerArg,char *zBuf,int nBuf);
#endif
int fossil_strcmp(const char *zA,const char *zB);
void blob_appendf(Blob *pBlob,const char *zFormat,...);
int fossil_strncmp(const char *zA,const char *zB,int nByte);
void cgi_set_cookie(const char *zName,const char *zValue,const char *zPath,int lifetime);
void blob_vappendf(Blob *pBlob,const char *zFormat,va_list ap);
void cgi_printf_header(const char *zLine,...);
void cgi_append_header(const char *zLine);
void cgi_set_status(int iStat,const char *zStat);
void blob_zero(Blob *pBlob);
void cgi_set_content(Blob *pNewContent);
char *fossil_strdup(const char *zOrig);
void cgi_set_content_type(const char *zType);
char *cgi_extract_content(void);
#define blob_buffer(X)  ((X)->aData)
#define blob_size(X)  ((X)->nUsed)
const char *cgi_header(void);
Blob *cgi_output_blob(void);
void blob_reset(Blob *pBlob);
void cgi_reset_content(void);
void blob_append(Blob *pBlob,const char *aData,int nData);
void cgi_append_content(const char *zData,int nAmt);
int cgi_body_contains(const char *zNeedle);
char *blob_str(Blob *p);
int cgi_header_contains(const char *zNeedle);
NORETURN void cgi_panic(const char *zFormat,...);
void cgi_destination(int dest);
void blobReallocMalloc(Blob *pBlob,unsigned int newSize);
#define BLOB_INITIALIZER  {0,0,0,0,0,blobReallocMalloc}
#define CGI_SSH_FOSSIL           0x0004     /* Use new Fossil SSH transport */
#define CGI_SSH_COMPAT           0x0002     /* Compat for old SSH transport */
#define CGI_SSH_CLIENT           0x0001     /* Client is SSH */
#define CGI_BODY     1
#define CGI_HEADER   0
void cgi_printf(const char *zFormat,...);
#define CX cgi_printf
const char *cgi_parameter_no_attack(const char *zName,const char *zDefault);
#define PD_NoBot(x,y) cgi_parameter_no_attack((x),(y))
#define P_NoBot(x)    cgi_parameter_no_attack((x),0)
const char *cgi_parameter_checked(const char *zName,int iValue);
#define PIF(x,y)      cgi_parameter_checked(x,y)
#define PCK(x)        cgi_parameter_checked(x,1)
int cgi_parameter_boolean(const char *zName);
#define PB(x)         cgi_parameter_boolean(x)
char *cgi_parameter_trimmed(const char *zName,const char *zDefault);
#define PDT(x,y)      cgi_parameter_trimmed((x),(y))
#define PT(x)         cgi_parameter_trimmed((x),0)
const char *cgi_parameter(const char *zName,const char *zDefault);
#define PD(x,y)       cgi_parameter((x),(y))
#define P(x)          cgi_parameter((x),0)
#define INTERFACE 0
