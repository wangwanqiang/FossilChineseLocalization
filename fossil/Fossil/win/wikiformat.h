/* This file was automatically generated.  Do not edit! */
#undef INTERFACE
typedef struct Blob Blob;
char *blob_terminate(Blob *p);
void test_safe_html_cmd(void);
#define DOCSRC_WIKI       4     /* Document is a wiki page */
#define DOCSRC_TICKET     3     /* Document is a ticket comment */
#define DOCSRC_FORUM      2     /* Document is a forum post */
#define DOCSRC_FILE       1     /* Document is a checked-in file */
char *db_text(const char *zDefault,const char *zSql,...);
const char *safe_html_nonce(int bGenerate);
void *fossil_malloc(size_t n);
void test_html_to_text(void);
typedef unsigned int u32;
#define blob_buffer(X)  ((X)->aData)
void fossil_puts(const char *z,int toStdErr,int n);
void test_html_tidy(void);
#define blob_size(X)  ((X)->nUsed)
void htmlTidy(const char *zIn,Blob *pOut);
void test_html_tokenize(void);
const char *html_attribute(const char *zMarkup,const char *zAttr,int *pLen);
int html_subtoken_length(const char *z);
int html_token_length(const char *z);
typedef struct Backlink Backlink;
void backlink_create(Backlink *p,const char *zTarget,int nTarget);
struct Backlink {
  int srcid;             /* srcid for the source document */
  int srctype;           /* One of BKLNK_*.  0=comment 1=ticket 2=wiki */
  double mtime;          /* mtime field for new BACKLINK table entries */
};
int wiki_extract_links(char *z,Backlink *pBklnk,int flags);
int wiki_find_title(Blob *pIn,Blob *pTitle,Blob *pTail);
NORETURN void fossil_fatal(const char *zFormat,...);
void safe_html(Blob *in);
#define DOCSRC_TRUSTED    5     /* safe_html() is always a no-op */
#define DOCSRC_UNTRUSTED  6     /* safe_html() is always enabled */
void safe_html_context(int eTrust);
void markdown_to_html(struct Blob *input_markdown,struct Blob *output_title,struct Blob *output_body);
void markdown_to_html(struct Blob *input_markdown,struct Blob *output_title,struct Blob *output_body);
void test_markdown_render(void);
int blob_write_to_file(Blob *pBlob,const char *zFilename);
int get_comment_format();
unsigned int terminal_get_width(unsigned int nDefault);
int comment_print(const char *zText,const char *zOrigText,int indent,int width,int flags);
void fossil_print(const char *zFormat,...);
void html_to_plaintext(const char *zIn,Blob *pOut,int mFlags);
#define HTOT_FLOW    0x02 /* Collapse internal whitespace to a single space */
#define HTOT_VT100   0x01 /* <mark> becomes ^[[91m */
int terminal_is_vt100(void);
#define HTOT_TRIM    0x04 /* Trim off leading and trailing whitespace */
#include <stdlib.h>
#define ExtFILE    0  /* Always follow symlinks */
sqlite3_int64 blob_read_from_file(Blob *pBlob,const char *zFilename,int eFType);
void blob_zero(Blob *pBlob);
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
void verify_all_options(void);
#define OPEN_SUBSTITUTE         0x004   /* Fake in-memory repo if not found */
#define OPEN_OK_NOT_FOUND       0x001   /* Do not error out if not found */
void db_find_and_open_repository(int bFlags,int nArgUsed);
#define PIKCHR_PROCESS_DARK_MODE         0x0002
void pikchr_to_html_add_flags(int f);
const char *find_option(const char *zLong,const char *zShort,int hasArg);
void test_wiki_render(void);
char *blob_str(Blob *p);
void blob_to_utf8_no_bom(Blob *pBlob,int useMbcs);
Blob *cgi_output_blob(void);
int wiki_convert(Blob *pIn,Blob *pOut,int flags);
int is_false(const char *zVal);
void htmlize_to_blob(Blob *p,const char *zIn,int n);
int interwiki_removable_prefix(const char *zTarget);
void pikchr_to_html(Blob *ob,const char *zSrc,int nSrc,const char *zArg,int nArg);
void blob_append(Blob *pBlob,const char *aData,int nData);
void blob_reset(Blob *pBlob);
void blob_init(Blob *pBlob,const char *zData,int size);
int wiki_valid_link_target(char *zTarget);
void fossil_free(void *p);
void fossil_free(void *);
int db_int(int iDflt,const char *zSql,...);
char *interwiki_url(const char *zTarget);
char *xhref(const char *zExtra,const char *zFormat,...);
typedef struct Global Global;
struct Blob {
  unsigned int nUsed;            /* Number of bytes used in aData[] */
  unsigned int nAlloc;           /* Number of bytes allocated for aData[] */
  unsigned int iCursor;          /* Next character of input to parse */
  unsigned int blobFlags;        /* One or more BLOBFLAG_* bits */
  char *aData;                   /* Where the information is stored */
  void (*xRealloc)(Blob*, unsigned int); /* Function to reallocate the buffer */
};
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
int wiki_resolve_hyperlink(Blob *pOut,int mFlags,const char *zTarget,char *zClose,int nClose,const char *zOrig,const char *zTitle);
void wiki_hyperlink_override(const char *zUuid);
int db_exists(const char *zSql,...);
int wiki_name_is_wellformed(const unsigned char *z);
typedef struct Stmt Stmt;
int db_column_int(Stmt *pStmt,int N);
char *db_get(const char *zName,const char *zDefault);
int db_static_stmt_is_init(Stmt *pStmt);
void canonical16(char *z,int n);
int is_ticket(const char *zTarget,int *pClosed);
int db_reset(Stmt *pStmt);
int db_step(Stmt *pStmt);
int db_bind_text(Stmt *pStmt,const char *zParamName,const char *zValue);
int db_static_prepare(Stmt *pStmt,const char *zFormat,...);
struct Stmt {
  Blob sql;               /* The SQL for this statement */
  sqlite3_stmt *pStmt;    /* The results of sqlite3_prepare_v2() */
  Stmt *pNext, *pPrev;    /* List of all unfinalized statements */
  int nStep;              /* Number of sqlite3_step() calls */
  int rc;                 /* Error from db_vprepare() */
};
int validate16(const char *zIn,int nIn);
#define HNAME_MAX  64     /* Length for SHA3-256 */
void *fossil_realloc(void *p,size_t n);
void *fossil_realloc(void *,size_t);
void style_submenu_element(const char *zLabel,const char *zLink,...);
char *mprintf(const char *zFormat,...);
int fossil_strnicmp(const char *zA,const char *zB,int nByte);
void blob_append_char(Blob *pBlob,char c);
void blob_appendf(Blob *pBlob,const char *zFormat,...);
int fossil_tolower(char c);
#define blob_append_literal(blob, literal) \
  blob_append((blob), "" literal, (sizeof literal)-1)
#define blob_append_string blob_append_literal
int fossil_isdigit(char c);
int fossil_isspace(char c);
int fossil_isalnum(char c);
int fossil_isalpha(char c);
int html_tag_length(const char *z);
int db_get_boolean(const char *zName,int dflt);
void cgi_printf(const char *zFormat,...);
void show_allowed_wiki_markup(void);
int fossil_strcmp(const char *zA,const char *zB);
#define RENDER_ANYERROR   0x9f00  /* Mask for any kind of error */
#define RENDER_ERROR      0x8000  /* Some other kind of error */
#define RENDER_BADHTML    0x1000  /* Bad HTML seen */
#define RENDER_BADENTITY  0x0800  /* Bad HTML entity syntax */
#define RENDER_BADTAG     0x0400  /* Bad HTML tag or tag syntax */
#define RENDER_BADTARGET  0x0200  /* Bad hyperlink target */
#define RENDER_BADLINK    0x0100  /* Bad hyperlink syntax seen */
#define RENDER_MARK       0x0020  /* Output contains <mark>..</mark> */
#define RENDER_BLOCK      0x0010  /* Block wiki (paragraphs, etc.) */
#define RENDER_BLOCKTAG   0x0008  /* One or more HTML block tags (ex: <p>) */
#define RENDER_TAG        0x0004  /* One or more HTML tags */
#define RENDER_ENTITY     0x0002  /* One or more HTML entities (ex: &lt;) */
#define RENDER_LINK       0x0001  /* One or more hyperlinks rendered */
#define WIKI_MARK          0x1000  /* Add <mark>..</mark> around problems */
#define WIKI_ADMIN         0x0800  /* Ignore g.perm.Hyperlink */
#define WIKI_NOBRACKET     0x0400  /* Omit extra [..] around hyperlinks */
#define WIKI_TARGET_BLANK  0x0200  /* Hyperlinks go to a new window */
#define WIKI_SAFE          0x0100  /* Make the result safe for embedding */
#define WIKI_MARKDOWNLINKS 0x0080  /* Resolve hyperlinks as in markdown */
#define WIKI_NEWLINE       0x0040  /* Honor \n - break lines at each \n */
#define WIKI_LINKSONLY     0x0020  /* No markup.  Only decorate links */
#define WIKI_NOBADLINKS    0x0010  /* Ignore broken hyperlinks */
#define WIKI_BUTTONS       0x0008  /* Allow sub-menu buttons */
#define WIKI_INLINE        0x0002  /* Do not surround with <p>..</p> */
#define WIKI_HTMLONLY      0x0001  /* HTML markup only.  No wiki */
#define INTERFACE 0
