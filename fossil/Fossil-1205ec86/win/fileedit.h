/* This file was automatically generated.  Do not edit! */
#undef INTERFACE
typedef struct Glob Glob;
void glob_render_json_to_cgi(Glob *pGlob);
void builtin_fulfill_js_requests(void);
void builtin_request_js(const char *zFilename);
void ajax_emit_js_preview_modes(int addScriptTag);
NULL_SENTINEL void builtin_fossil_js_bundle_or(const char *zApi,...);
void style_select_list_str(const char *zWrapperId,const char *zFieldName,const char *zLabel,const char *zToolTip,char const *zSelectedVal,...);
void style_labeled_checkbox(const char *zWrapperId,const char *zFieldName,const char *zLabel,const char *zValue,int isChecked,const char *zTip);
#define AJAX_RENDER_PLAIN_TEXT 1  /* Render as plain text. */
#define AJAX_RENDER_HTML_INLINE 3 /* Render as HTML without an IFRAME. */
#define AJAX_RENDER_HTML_IFRAME 2 /* Render as HTML inside an IFRAME. */
#define AJAX_RENDER_WIKI 4        /* Render as wiki/markdown. */
int ajax_render_mode_for_mimetype(const char *zMimetype);
void wikiedit_emit_toggle_preview(void);
void style_select_list_int(const char *zWrapperId,const char *zFieldName,const char *zLabel,const char *zToolTip,int selectedVal,...);
void style_script_end(void);
void style_script_begin(const char *zOrigin,int iLine);
void style_emit_noscript_for_js_page(void);
void style_finish_page();
void style_header(const char *zTitleFormat,...);
void login_needed(int anonOk);
void login_check_credentials(void);
#define AJAX_RENDER_GUESS 0   /* Guess rendering mode based on mimetype. */
void fileedit_page(void);
char *fossil_strdup(const char *zOrig);
void cgi_printf(const char *zFormat,...);
#define CX cgi_printf
typedef struct Stmt Stmt;
typedef struct Blob Blob;
int db_prepare_blob(Stmt *pStmt,Blob *pSql);
# define TAG_CLOSED     9     /* Do not display this check-in as a leaf */
void blob_append_sql(Blob *pBlob,const char *zFormat,...);
const char *timeline_query_for_tty(void);
char *cgi_parameter_trimmed(const char *zName,const char *zDefault);
#define PT(x)         cgi_parameter_trimmed((x),0)
void ajax_render_diff(Blob *pOrig,const char *zOrigHash,Blob *pContent,u64 diffFlags);
void blob_init(Blob *pBlob,const char *zData,int size);
#define DIFF_STRIP_EOLCR       0x00001000 /* Strip trailing CR */
#define DIFF_IGNORE_EOLWS      0x00000001 /* Ignore end-of-line whitespace */
#define DIFF_IGNORE_ALLWS      0x00000003 /* Ignore all whitespace */
#define DIFF_SIDEBYSIDE        0x00000004 /* Generate a side-by-side diff */
#define DIFF_LINENO            0x00000040 /* Show line numbers */
const char *cgi_parameter(const char *zName,const char *zDefault);
#define PD(x,y)       cgi_parameter((x),(y))
#define DIFF_NOTTOOBIG         0x00000800 /* Only display if not too big */
#define DIFF_HTML              0x00000020 /* Render for HTML */
#define P(x)          cgi_parameter((x),0)
void cgi_set_content(Blob *pNewContent);
void cgi_set_content_type(const char *zType);
char *branch_of_rid(int rid);
void cgi_printf_header(const char *zLine,...);
int looks_like_utf8(const Blob *pContent,int stopFlags);
#define LOOK_NUL     ((int)0x00000001) /* One or more NUL chars were found. */
#define LOOK_LONG    ((int)0x00000040) /* An over length line was found. */
#define LOOK_SHORT   ((int)0x00000100) /* Unable to perform full check. */
#define LOOK_BINARY  (LOOK_NUL | LOOK_LONG | LOOK_SHORT) /* May be binary. */
#define LOOK_NONE    ((int)0x00000000) /* Nothing special was found. */
#define looks_like_binary(blob) \
    ((looks_like_utf8((blob), LOOK_BINARY) & LOOK_BINARY) != LOOK_NONE)
const char *mimetype_from_name(const char *zName);
int ajax_route_bootstrap(int requireWrite,int requirePost);
int ajax_get_fnci_args(const char **zFn,const char **zCi);
int symbolic_name_to_rid(const char *zTag,const char *zType);
void ajax_route_error(int httpCode,const char *zFmt,...);
int db_finalize(Stmt *pStmt);
const char *db_column_text(Stmt *pStmt,int N);
int db_step(Stmt *pStmt);
const char *filename_collation(void);
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
int glob_match(Glob *pGlob,const char *zString);
int fileedit_is_editable(const char *zFilename);
Glob *glob_create(const char *zPatternList);
char *db_get(const char *zName,const char *zDefault);
Glob *fileedit_glob(void);
struct Glob {
  int nPattern;        /* Number of patterns */
  char **azPattern;    /* Array of pointers to patterns */
};
void fossil_warning(const char *zFormat,...);
int blob_write_to_file(Blob *pBlob,const char *zFilename);
int name_to_uuid2(const char *zName,const char *zType,char **pUuid);
char *db_lget(const char *zName,const char *zDefault);
const char *login_name(void);
#include <stdlib.h>
#include <dirent.h>
int file_perm(const char *zFilename,int eFType);
char *mprintf(const char *zFormat,...);
#define ExtFILE    0  /* Always follow symlinks */
sqlite3_int64 blob_read_from_file(Blob *pBlob,const char *zFilename,int eFType);
NORETURN void fossil_fatal(const char *zFormat,...);
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
int user_select(void);
void verify_all_options(void);
void db_find_and_open_repository(int bFlags,int nArgUsed);
const char *find_option(const char *zLong,const char *zShort,int hasArg);
void test_ci_mini_cmd(void);
int db_transaction_nesting_depth(void);
void db_end_transaction(int rollbackFlag);
int manifest_crosslink(int rid,Blob *pContent,int flags);
int content_deltify(int rid,int *aSrc,int nSrc,int force);
#define blob_buffer(X)  ((X)->aData)
void fossil_print(const char *zFormat,...);
int content_put_ex(Blob *pBlob,const char *zUuid,int srcId,int nBlob,int isPrivate);
int content_is_private(int rid);
int hname_hash(const Blob *pContent,unsigned int iHType,Blob *pHashOut);
void blob_add_cr(Blob *p);
void blob_to_lf_only(Blob *p);
int content_get(int rid,Blob *pBlob);
#define LOOK_LONE_LF ((int)0x00000010) /* An unpaired LF char was found. */
#define LOOK_CRLF    ((int)0x00000020) /* One or more CR/LF pairs were found. */
int fast_uuid_to_rid(const char *zUuid);
char *db_text(const char *zDefault,const char *zSql,...);
int checkin_is_younger(int rid,const char *zDate);
int file_is_simple_pathname(const char *z,int bStrictUtf8);
int contains_merge_marker(Blob *p);
int is_a_leaf(int rid);
int db_exists(const char *zSql,...);
int leaf_is_closed(int vid);
char *rid_to_uuid(int rid);
typedef struct Manifest Manifest;
Manifest *manifest_get_by_name(const char *zName,int *pRid);
void db_begin_transaction_real(const char *zStartFile,int iStartLine);
#define db_begin_transaction()    db_begin_transaction_real(__FILE__,__LINE__)
int md5sum_blob(const Blob *pIn,Blob *pCksum);
#define blob_size(X)  ((X)->nUsed)
int db_get_boolean(const char *zName,int dflt);
void blob_zero(Blob *pBlob);
char *blob_str(Blob *p);
typedef struct ManifestFile ManifestFile;
ManifestFile *manifest_file_next(Manifest *p,int *pErr);
ManifestFile *manifest_file_find(Manifest *p,const char *zName);
void manifest_file_rewind(Manifest *p);
int fossil_stricmp(const char *zA,const char *zB);
int fossil_strcmp(const char *zA,const char *zB);
int filenames_are_case_sensitive(void);
void blob_append(Blob *pBlob,const char *aData,int nData);
int manifest_file_mperm(const ManifestFile *pFile);
void blob_appendf(Blob *pBlob,const char *zFormat,...);
struct ManifestFile {
  char *zName;           /* Name of a file */
  char *zUuid;           /* Artifact hash for the file */
  char *zPerm;           /* File permissions */
  char *zPrior;          /* Prior name if the name was changed */
};
#define PERM_REG          0     /*  regular file  */
#define PERM_LNK          2     /*  symlink       */
#define PERM_EXE          1     /*  executable    */
void fossil_free(void *p);
void fossil_free(void *);
void manifest_destroy(Manifest *p);
void blob_reset(Blob *pBlob);
extern const Blob empty_blob;
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
