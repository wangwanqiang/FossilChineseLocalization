/* This file was automatically generated.  Do not edit! */
#undef INTERFACE
void webpage_error(const char *zFormat,...);
void cgi_reset_content(void);
void webpage_assert_page(const char *zFile,int iLine,const char *zExpr);
# define webpage_assert(T) if(!(T)){webpage_assert_page(__FILE__,__LINE__,#T);}
void style_set_current_feature(const char *zFeature);
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
void test_warning_page(void);
void test_echo_cmd(void);
#if defined(_WIN32)
void win32_http_server(int mnPort,int mxPort,const char *zBrowser,const char *zStopper,const char *zBaseUrl,const char *zNotFound,const char *zFileGlob,const char *zIpAddr,int flags);
int win32_http_service(int nPort,const char *zBaseUrl,const char *zNotFound,const char *zFileGlob,int flags);
#endif
int cgi_http_server(int mnPort,int mxPort,const char *zBrowser,const char *zIpAddr,int flags);
#define HTTP_SERVER_HAD_CHECKOUT   0x0008     /* Was a checkout open? */
#define HTTP_SERVER_HAD_REPOSITORY 0x0004     /* Was the repository open? */
int fossil_system(const char *zOrigCmd);
void db_close_config();
const char *skin_in_use(void);
#include <stdlib.h>
#include <dirent.h>
int file_is_absolute_path(const char *zPath);
typedef struct Blob Blob;
void blob_append_escaped_arg(Blob *pBlob,const char *zIn,int isFilename);
void ssh_add_path_argument(Blob *pCmd);
int ssh_needs_path_argument(const char *zHostname,int iTruth);
void transport_ssh_command(Blob *p);
const char *fossil_web_browser(void);
int db_open_config(int useAttach,int isOptional);
#define HTTP_SERVER_REPOLIST       0x0010     /* Allow repo listing */
const char *file_skip_userhost(const char *zIn);
int dir_has_ckout_db(const char *zDir);
#define HTTP_SERVER_NOFORK         0x0020     /* Do not call fork() */
#define HTTP_SERVER_UNIXSOCKET     0x0040     /* Use a unix-domain socket */
#define HTTP_SERVER_LOCALHOST      0x0001     /* Bind to 127.0.0.1 only */
#define HTTP_SERVER_SCGI           0x0002     /* SCGI instead of HTTP */
char *file_dirname(const char *z);
char *file_canonical_name_dup(const char *zOrigName);
const char *file_tail(const char *z);
#if USE_SEE
void db_setup_for_saved_encryption_key();
#endif
void cmd_webserver(void);
void fossil_cpu_times(sqlite3_uint64 *piUser,sqlite3_uint64 *piKernel);
void cgi_set_parameter(const char *zName,const char *zValue);
void login_set_capabilities(const char *zCap,unsigned flags);
void cmd_test_http(void);
#define CGI_SSH_COMPAT           0x0002     /* Compat for old SSH transport */
#define CGI_SSH_FOSSIL           0x0004     /* Use new Fossil SSH transport */
void cgi_handle_ssh_http_request(const char *zIpAddr);
#if defined(FOSSIL_ENABLE_SSL)
void ssl_close_server(void *pServerArg);
#endif
void cgi_handle_http_request(const char *zIpAddr);
#if defined(FOSSIL_ENABLE_SSL)
void *ssl_new_server(int iSocket);
#endif
typedef struct Glob Glob;
void ssh_request_loop(const char *zIpAddr,Glob *FileGlob);
void cgi_handle_scgi_request(void);
const char *cgi_ssh_remote_addr(const char *zDefault);
#define CGI_SSH_CLIENT           0x0001     /* Client is SSH */
void backoffice_no_delay(void);
void backoffice_disable(void);
void skin_override(void);
void Th_InitTraceLog();
void cmd_http(void);
#if defined(FOSSIL_ENABLE_SSL)
void ssl_init_server(const char *zCertFile,const char *zKeyFile);
#endif
#if USE_SEE
size_t db_get_saved_encryption_key_size();
char *db_get_saved_encryption_key();
#endif
void test_pid_page(void);
#if !defined(_WIN32)
typedef size_t SIZE_T;
typedef void *LPVOID;
#endif
#if USE_SEE
void parse_pid_key_value(const char *zPidKey,PID_T *pProcessId,LPVOID *ppAddress,SIZE_T *pnSize);
#endif
void cache_initialize(void);
void hash_user_password(const char *zUser);
char *db_text(const char *zDefault,const char *zSql,...);
void db_end_transaction(int rollbackFlag);
void db_initial_setup(const char *zTemplate,const char *zInitialDate,const char *zDefaultUser);
void db_set_int(const char *zName,int value,int globalFlag);
#define HPOLICY_SHA3           2      /* Use SHA3 hashes */
void db_begin_transaction_real(const char *zStartFile,int iStartLine);
#define db_begin_transaction()    db_begin_transaction_real(__FILE__,__LINE__)
void db_create_repository(const char *zFilename);
int file_simplify_name(char *z,int n,int slash);
void db_must_be_within_tree(void);
void cgi_init(void);
void cgi_load_environment(void);
char *cgi_iso8601_datestamp(void);
void builtin_set_js_delivery_mode(const char *zMode,int bSilent);
#define SKIN_FROM_CGI       2   /* skin: parameter in CGI script */
char *skin_use_alternative(const char *zName,int rank,int iSource);
void cgi_setenv(const char *zName,const char *zValue);
int fossil_setenv(const char *zName,const char *zValue);
Glob *glob_create(const char *zPatternList);
int blob_trim(Blob *p);
int blob_tail(Blob *pFrom,Blob *pTo);
# define blob_eq(B,S) \
     ((B)->nUsed==sizeof(S"")-1 && memcmp((B)->aData,S,sizeof(S)-1)==0)
int blob_token(Blob *pFrom,Blob *pTo);
NORETURN void cgi_panic(const char *zFormat,...);
void fossil_set_timeout(int N);
void fossil_binary_mode(FILE *p);
void cmd_cgi(void);
NORETURN void cgi_redirect_perm(const char *zURL);
int validate16(const char *zIn,int nIn);
void cgi_print_all(int showAll,unsigned int eDest,FILE *out);
void fossil_trace(const char *zFormat,...);
#define PROTECT_READONLY   0x08  /* everything except TEMP tables */
void db_protect(unsigned flags);
int cgi_same_origin(int bErrorLog);
void cgi_decode_post_parameters(void);
#define CMDFLAG_RAWCONTENT   0x0200     /* Do not interpret POST content */
#if defined(FOSSIL_ENABLE_JSON)
void json_bootstrap_late();
int json_is_bootstrapped_early(void);
#endif
void load_control(void);
#define CMDFLAG_LDAVG_EXEMPT 0x1000     /* Exempt from load_control() */
int db_schema_is_outofdate(void);
void page_xfer(void);
#if defined(FOSSIL_ENABLE_TH1_HOOKS)
int Th_WebpageNotify(const char *zName,unsigned int cmdFlags);
int Th_WebpageHook(const char *zName,unsigned int cmdFlags);
#endif
typedef struct CmdOrPage CmdOrPage;
int dispatch_alias(const char *zName,const CmdOrPage **ppCmd);
#define CMDFLAG_WEBPAGE      0x0008     /* Web pages */
void cgi_set_parameter_nocopy(const char *zName,const char *zValue,int isQP);
void etag_cancel(void);
void skin_use_draft(int i);
int db_int(int iDflt,const char *zSql,...);
#if USE_SEE
void db_set_see_key_page(void);
#endif
void cgi_replace_parameter(const char *zName,const char *zValue);
NORETURN void cgi_redirect(const char *zURL);
int repo_list_page(void);
void cgi_set_content(Blob *pNewContent);
void cgi_set_content_type(const char *zType);
sqlite3_int64 blob_read_from_file(Blob *pBlob,const char *zFilename,int eFType);
const char *mimetype_from_name(const char *zName);
int file_contains_repository_extension(const char *zPath);
int glob_match(Glob *pGlob,const char *zString);
int file_is_repository_extension(const char *zPath);
i64 file_size(const char *zFilename,int eFType);
const char *file_cleanup_fullpath(const char *z);
#if defined(FOSSIL_ENABLE_JSON)
void json_bootstrap_early(void);
int json_request_is_json_api(const char *zPathInfo);
#endif
int cgi_parameter_boolean(const char *zName);
#define PB(x)         cgi_parameter_boolean(x)
int dehttpize(char *z);
struct Glob {
  int nPattern;        /* Number of patterns */
  char **azPattern;    /* Array of pointers to patterns */
};
void cgi_reply(void);
void cgi_set_status(int iStat,const char *zStat);
#if defined(FOSSIL_ENABLE_JSON)
void json_err(int code,char const *msg,int alsoOutput);
#endif
void fossil_not_found_page(void);
NORETURN void cgi_redirect_with_status(const char *zURL,int iStat,const char *zStat);
int fossil_redirect_to_https_if_needed(int iLevel);
int db_get_int(const char *zName,int dflt);
int fossil_wants_https(int iLevel);
void db_panic_close(void);
void sigpipe_handler(int x);
void sigsegv_handler(int x);
void db_open_repository(const char *zDbName);
int file_isdir(const char *zFilename,int eFType);
#define blob_size(X)  ((X)->nUsed)
void file_canonical_name(const char *zOrigName,Blob *pOut,int slash);
char *db_get(const char *zName,const char *zDefault);
NORETURN void cgi_redirectf(const char *zFormat,...);
void cookie_render(void);
int cgi_setup_query_string(void);
NORETURN void fossil_redirect_home(void);
void db_protect_pop(void);
void db_optional_sql(const char *zDb,const char *zSql,...);
int db_multi_exec(const char *zSql,...);
int db_exists(const char *zSql,...);
#define PROTECT_CONFIG     0x02  /* CONFIG and GLOBAL_CONFIG tables */
void db_unprotect(unsigned flags);
char *fossil_strndup(const char *zOrig,ssize_t len);
int db_is_writeable(const char *zName);
int fossil_stricmp(const char *zA,const char *zB);
const char *cgi_parameter(const char *zName,const char *zDefault);
#define PD(x,y)       cgi_parameter((x),(y))
void set_base_url(const char *zAltBase);
void style_finish_page();
void cgi_printf(const char *zFormat,...);
void style_submenu_element(const char *zLabel,const char *zLink,...);
void style_header(const char *zTitleFormat,...);
#define P(x)          cgi_parameter((x),0)
void login_needed(int anonOk);
void login_check_credentials(void);
void test_version_page(void);
void version_cmd(void);
const char *get_user_agent();
typedef struct Stmt Stmt;
int db_finalize(Stmt *pStmt);
const char *db_column_text(Stmt *pStmt,int N);
int db_step(Stmt *pStmt);
int db_prepare(Stmt *pStmt,const char *zFormat,...);
#if USE_SEE
int db_have_saved_encryption_key();
#endif
void blob_append(Blob *pBlob,const char *aData,int nData);
void fossil_get_page_size(size_t *piPageSize);
#define AUX_SCHEMA_MAX  "2015-01-24"
typedef struct Th_Interp Th_Interp;
const char *Th_GetResult(Th_Interp *,int *);
const char *Th_ReturnCodeName(int rc,int nullIfOk);
int Th_Eval(Th_Interp *interp,int iFrame,const char *zProg,int nProg);
typedef unsigned int u32;
void Th_FossilInit(u32 flags);
const char *fusefs_lib_version(void);
const char *fusefs_inc_version(void);
void blob_zero(Blob *pBlob);
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
void fossil_version_blob(Blob *pOut,int eVerbose);
#define MANIFEST_DATE "2025-04-30 16:57:32"
#define MANIFEST_VERSION "[1205ec86cb]"
#define RELEASE_VERSION "2.26"
const char *get_version();
void verify_all_options(void);
char *mprintf(const char *zFormat,...);
void fossil_free(void *p);
void fossil_free(void *);
const char *find_repository_option();
void *fossil_realloc(void *p,size_t n);
void *fossil_realloc(void *,size_t);
const char **find_repeatable_option(const char *zLong,const char *zShort,int *pnUsedArgs);
int has_option(const char *zOption);
void restore_option(const char *zName,const char *zValue,int hasOpt);
void usage(const char *zFormat);
void dispatch_matching_names(const char *zPrefix,unsigned eType,Blob *pList);
#if defined(FOSSIL_ENABLE_TH1_HOOKS)
int Th_CommandNotify(const char *zName,unsigned int cmdFlags);
#endif
#define TH_CONTINUE 4
#define TH_RETURN   3
#define TH_OK       0
#if defined(FOSSIL_ENABLE_TH1_HOOKS)
int Th_CommandHook(const char *zName,unsigned int cmdFlags);
#endif
int file_is_repository(const char *zFilename);
#define CMDFLAG_PREFIX      0x0200      /* Prefix match is ok */
#define CMDFLAG_COMMAND      0x0010     /* A command */
int dispatch_name_search(const char *zName,unsigned eType,const CmdOrPage **ppCmd);
int is_valid_fd(int fd);
#define SEE_KEY_READ  ((int)0)
#if USE_SEE
PID_T db_maybe_handle_saved_encryption_key_for_process(int eType);
#endif
int file_chdir(const char *zChDir,int bChroot);
NORETURN void fossil_exit(int rc);
void capture_case_sensitive_option(void);
int fossil_timer_start();
NORETURN void fossil_panic(const char *zFormat,...);
void fossil_limit_memory(int onOff);
void fossil_printf_selfcheck(void);
int fossil_isatty(int fd);
struct CmdOrPage {
  const char *zName;       /* Name.  Webpages start with "/". Commands do not */
  void (*xFunc)(void);     /* Implementation function, or NULL for settings */
  const char *zHelp;       /* Raw help text */
  int iHelp;               /* Index of help variable */
  unsigned int eCmdFlags;  /* Flags */
};
#if defined(FOSSIL_FUZZ)
extern int _CRT_glob;
#endif
int fossil_main(int argc,char **argv);
#if defined(FOSSIL_FUZZ)
int wmain(int argc,wchar_t **argv);
extern int _dowildcard;
#endif
#define COMMENT_PRINT_UNSET      (-1)              /* Not initialized */
const char *find_option(const char *zLong,const char *zShort,int hasArg);
void blob_reset(Blob *pBlob);
void fossil_warning(const char *zFormat,...);
void blob_appendf(Blob *pBlob,const char *zFormat,...);
void blob_init(Blob *pBlob,const char *zData,int size);
char *fossil_strdup(const char *zOrig);
int fossil_isspace(char c);
#define blob_buffer(X)  ((X)->aData)
int blob_line(Blob *pFrom,Blob *pTo);
void blob_rewind(Blob *p);
char *blob_str(Blob *p);
void blob_to_utf8_no_bom(Blob *pBlob,int useMbcs);
int blob_read_from_channel(Blob *pBlob,FILE *in,int nToRead);
FILE *fossil_fopen(const char *zName,const char *zMode);
NORETURN void fossil_fatal(const char *zFormat,...);
#define ExtFILE    0  /* Always follow symlinks */
int file_isfile(const char *zFilename,int eFType);
void *fossil_malloc(size_t n);
int fossil_strcmp(const char *zA,const char *zB);
char *file_fullexename(const char *zCmd);
char *fossil_path_to_utf8(const void *zPath);
#if defined(_WIN32)
char *fossil_mbcs_to_utf8(const char *zMbcs);
#endif
extern const Blob empty_blob;
void expand_args_option(int argc,void *argv);
void fossil_print(const char *zFormat,...);
#if defined(TH_MEMDEBUG)
int Th_GetOutstandingMalloc();
#endif
void Th_DeleteInterp(Th_Interp *);
char *fossil_getenv(const char *zName);
void rebuild_clear_cache();
void content_clear_cache(int bFreeIt);
void manifest_clear_cache();
void db_close(int reportErrors);
int file_issocket(const char *zFilename);
#if defined(FOSSIL_ENABLE_TCL)
int unloadTcl(Th_Interp *,void *);
#endif
#if defined(_WIN32) || (defined(__BIONIC__) && !defined(FOSSIL_HAVE_GETPASS))
void freepass();
#endif
#if USE_SEE
void db_unsave_encryption_key();
#endif
void cgi_debug(const char *zFormat,...);
typedef struct Global Global;
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
#if !defined(FOSSIL_DEFAULT_TIMEOUT)
# define FOSSIL_DEFAULT_TIMEOUT 600  /* 10 minutes */
#endif
#define INTERFACE 0
