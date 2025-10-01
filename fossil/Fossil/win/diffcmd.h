/* This file was automatically generated.  Do not edit! */
#undef INTERFACE
typedef struct DiffConfig DiffConfig;
DiffConfig *diff_config_init(DiffConfig *pCfg,u64 diffFlags);
void cgi_set_content_type(const char *zType);
void fossil_nice_default(void);
int robot_restrict(const char *zTag);
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
NORETURN void fossil_redirect_home(void);
void login_needed(int anonOk);
void login_check_credentials(void);
void cgi_check_for_malice(void);
const char *cgi_parameter(const char *zName,const char *zDefault);
#define P(x)          cgi_parameter((x),0)
void vpatch_page(void);
char *fossil_strdup(const char *zOrig);
#include <stdlib.h>
#include <dirent.h>
typedef struct Blob Blob;
int file_tree_name(const char *zOrigName,Blob *pOut,int absolute,int errFatal);
void *fossil_malloc(size_t n);
void verify_all_options(void);
void diff_options(DiffConfig *pCfg,int isGDiff,int bUnifiedTextOnly);
int db_exists(const char *zSql,...);
const char *file_tail(const char *z);
void restore_option(const char *zName,const char *zValue,int hasOpt);
void db_find_and_open_repository(int bFlags,int nArgUsed);
void db_must_be_within_tree(void);
int has_option(const char *zOption);
void diff_cmd(void);
const char *diff_get_binary_glob(void);
char *write_blob_to_temp_file(Blob *pBlob);
typedef struct Th_Interp Th_Interp;
#if defined(FOSSIL_ENABLE_TCL)
int evaluateTclWithEvents(Th_Interp *,void *,const char *,int,int,int,int);
#endif
typedef unsigned int u32;
#define TH_INIT_NONE        ((u32)0x00000000) /* No flags. */
#define TH_INIT_DEFAULT     (TH_INIT_NONE)      /* Default flags. */
void Th_FossilInit(u32 flags);
void diff_tk(const char *zSubCmd,int firstArg);
int fossil_app_on_path(const char *zBinary,int ePrint);
int gdiff_using_tk(int isGdiff);
char *db_get(const char *zName,const char *zDefault);
const char *diff_command_external(int guiDiff);
int file_isdir(const char *zFilename,int eFType);
typedef struct FileDirList FileDirList;
void diff_externbase_to_checkout(const char *zExternBase,DiffConfig *pCfg,FileDirList *pFileDir);
typedef struct Manifest Manifest;
void manifest_destroy(Manifest *p);
typedef struct ManifestFile ManifestFile;
ManifestFile *manifest_file_next(Manifest *p,int *pErr);
void manifest_file_rewind(Manifest *p);
Manifest *manifest_get_by_name(const char *zName,int *pRid);
struct Blob {
  unsigned int nUsed;            /* Number of bytes used in aData[] */
  unsigned int nAlloc;           /* Number of bytes allocated for aData[] */
  unsigned int iCursor;          /* Next character of input to parse */
  unsigned int blobFlags;        /* One or more BLOBFLAG_* bits */
  char *aData;                   /* Where the information is stored */
  void (*xRealloc)(Blob*, unsigned int); /* Function to reallocate the buffer */
};
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
int uuid_to_rid(const char *zUuid,int phantomize);
struct ManifestFile {
  char *zName;           /* Name of a file */
  char *zUuid;           /* Artifact hash for the file */
  char *zPerm;           /* File permissions */
  char *zPrior;          /* Prior name if the name was changed */
};
typedef struct Stmt Stmt;
void db_column_blob(Stmt *pStmt,int N,Blob *pBlob);
void db_end_transaction(int rollbackFlag);
int db_finalize(Stmt *pStmt);
int content_get(int rid,Blob *pBlob);
#define DIFF_CANNOT_COMPUTE_SYMLINK \
    "cannot compute difference between symlink and regular file\n"
int file_islink(const char *zFilename);
int file_access(const char *zFilename,int flags);
#define DIFF_FILE_MASK         0xc0000000 /* Used for clearing file flags */
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
void blob_set(Blob *pBlob,const char *zStr);
void file_relative_name(const char *zOrigName,Blob *pOut,int slash);
int db_column_int(Stmt *pStmt,int N);
const char *db_column_text(Stmt *pStmt,int N);
int db_step(Stmt *pStmt);
char *blob_sql_text(Blob *p);
int db_prepare(Stmt *pStmt,const char *zFormat,...);
char *db_lget(const char *zName,const char *zDefault);
#define DIFF_SHOW_VERS         0x00200000 /* Show compared versions */
void blob_append_sql(Blob *pBlob,const char *zFormat,...);
int load_vfile_from_rid(int vid);
int is_a_version(int rid);
int name_to_typed_rid(const char *zName,const char *zType);
void db_begin_transaction_real(const char *zStartFile,int iStartLine);
#define db_begin_transaction()    db_begin_transaction_real(__FILE__,__LINE__)
#define CKSIG_ENOTFILE  0x001   /* non-file FS objects throw an error */
void vfile_check_signature(int vid,unsigned int cksigFlags);
int db_lget_int(const char *zName,int dflt);
#define DIFF_VERBOSE           0x00000008 /* Missing shown as empty files */
struct Stmt {
  Blob sql;               /* The SQL for this statement */
  sqlite3_stmt *pStmt;    /* The results of sqlite3_prepare_v2() */
  Stmt *pNext, *pPrev;    /* List of all unfinalized statements */
  int nStep;              /* Number of sqlite3_step() calls */
  int rc;                 /* Error from db_vprepare() */
};
void diff_version_to_checkout(const char *zFrom,DiffConfig *pCfg,FileDirList *pFileDir,Blob *pOut);
#define blob_buffer(X)  ((X)->aData)
void diff_file_mem(Blob *pFile1,Blob *pFile2,const char *zName,DiffConfig *pCfg);
void blob_append_escaped_arg(Blob *pBlob,const char *zIn,int isFilename);
#define DIFF_INVERT            0x00000200 /* Invert the diff (debug) */
int blob_write_to_file(Blob *pBlob,const char *zFilename);
void blob_init(Blob *pBlob,const char *zData,int size);
void file_tempname(Blob *pBuf,const char *zBasis,const char *zTag);
typedef struct Glob Glob;
void glob_free(Glob *pGlob);
int glob_match(Glob *pGlob,const char *zString);
Glob *glob_create(const char *zPatternList);
struct Glob {
  int nPattern;        /* Number of patterns */
  char **azPattern;    /* Array of pointers to patterns */
};
#define DIFF_CANNOT_COMPUTE_BINARY \
    "cannot compute difference between binary files\n"
int looks_like_utf8(const Blob *pContent,int stopFlags);
#define LOOK_NUL     ((int)0x00000001) /* One or more NUL chars were found. */
#define LOOK_LONG    ((int)0x00000040) /* An over length line was found. */
#define LOOK_SHORT   ((int)0x00000100) /* Unable to perform full check. */
#define LOOK_BINARY  (LOOK_NUL | LOOK_LONG | LOOK_SHORT) /* May be binary. */
#define LOOK_NONE    ((int)0x00000000) /* Nothing special was found. */
#define looks_like_binary(blob) \
    ((looks_like_utf8((blob), LOOK_BINARY) & LOOK_BINARY) != LOOK_NONE)
#define DIFF_INCBINARY         0x00100000 /* The --diff-binary option */
void blob_reset(Blob *pBlob);
char *blob_str(Blob *p);
#define blob_size(X)  ((X)->nUsed)
int *text_diff(Blob *pA_Blob,Blob *pB_Blob,Blob *pOut,DiffConfig *pCfg);
int blob_compare(const Blob *pA,const Blob *pB);
sqlite3_int64 blob_read_from_file(Blob *pBlob,const char *zFilename,int eFType);
#define ExtFILE    0  /* Always follow symlinks */
i64 file_size(const char *zFilename,int eFType);
void blob_zero(Blob *pBlob);
void diff_file(Blob *pFile1,const char *zFile2,const char *zName,DiffConfig *pCfg,Blob *pOut);
void fossil_free(void *p);
void fossil_free(void *);
int fossil_system(const char *zOrigCmd);
const char *fossil_web_browser(void);
const unsigned char *builtin_file(const char *zFilename,int *piSize);
void diff_end(DiffConfig *pCfg,int nErr);
#define DIFF_DARKMODE          0x00400000 /* Use dark mode for HTML */
NORETURN void fossil_fatal(const char *zFormat,...);
FILE *fossil_freopen(const char *zName,const char *zMode,FILE *stream);
char *fossil_temp_filename(void);
void diff_begin(DiffConfig *pCfg);
int file_delete(const char *zFilename);
extern const char zWebpageEnd[];
int diff_width(DiffConfig *pCfg);
void blob_append_json_literal(Blob *pOut,const char *z,int n);
int blob_trim(Blob *p);
void blob_append_char(Blob *pBlob,char c);
void blob_append_tcl_literal(Blob *pOut,const char *z,int n);
void blob_append(Blob *pBlob,const char *aData,int nData);
int fossil_strcmp(const char *zA,const char *zB);
#define DIFF_DEBUG             0x00020000 /* Debugging diff output */
#define DIFF_RAW               0x00040000 /* Raw triples - for debugging */
#define DIFF_FILE_DELETED      0x80000000 /* Deleted or rename source */
#define DIFF_FILE_ADDED        0x40000000 /* Added or rename destination */
void diff_print_filenames(const char *zLeft,const char *zRight,DiffConfig *pCfg,Blob *pOut);
void blob_appendf(Blob *pBlob,const char *zFormat,...);
void diff_print_index(const char *zFile,DiffConfig *pCfg,Blob *pOut);
double symbolic_name_to_mtime(const char *z,const char **pzDisplay,int bRoundUp);
char *db_text(const char *zDefault,const char *zSql,...);
int symbolic_name_to_rid(const char *zTag,const char *zType);
char *rid_to_uuid(int rid);
char *mprintf(const char *zFormat,...);
void fossil_print(const char *zFormat,...);
#define DIFF_TCL               0x00080000 /* For the --tk option */
#define DIFF_JSON              0x00010000 /* JSON output */
#define DIFF_BROWSER           0x00008000 /* The --browser option */
#define DIFF_WEBPAGE           0x00004000 /* Complete webpage */
#define DIFF_HTML              0x00000020 /* Render for HTML */
#define DIFF_NUMSTAT           0x00000080 /* Show line count of changes */
#define DIFF_BRIEF             0x00000010 /* Show filenames only */
#define DIFF_SIDEBYSIDE        0x00000004 /* Generate a side-by-side diff */
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
void diff_print_versions(const char *zFrom,const char *zTo,DiffConfig *pCfg);
int fossil_strnicmp(const char *zA,const char *zB,int nByte);
int fossil_stricmp(const char *zA,const char *zB);
int filenames_are_case_sensitive(void);
struct FileDirList {
  int nUsed;       /* Number of times each entry is used */
  int nName;       /* Length of the entry */
  char *zName;     /* Text of the entry */
};
#define INTERFACE 0
int db_get_boolean(const char *zName,int dflt);
const char *find_option(const char *zLong,const char *zShort,int hasArg);
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
