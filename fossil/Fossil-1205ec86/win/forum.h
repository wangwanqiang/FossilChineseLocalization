/* This file was automatically generated.  Do not edit! */
#undef INTERFACE
char *human_readable_age(double rAge);
int db_table_exists(const char *zDb,const char *zTable);
void style_submenu_entry(const char *zName,const char *zLabel,int iSize,int eVisible);
void cookie_write_parameter(const char *zQP,const char *zPName,const char *zDflt);
void cookie_read_parameter(const char *zQP,const char *zPName);
int search_screen(unsigned srchAllowed,int mFlags);
int moderation_needed(void);
char *db_get(const char *zName,const char *zDefault);
#define SRCH_FORUM    0x0020    /* Search over forum messages */
unsigned int search_restrict(unsigned int srchFlags);
void forum_main_page(void);
void entry_attribute(const char *zLabel,int width,const char *zVar,const char *zQParm,const char *zDflt,int disabled);
void onoff_attribute(const char *zLabel,const char *zVar,const char *zQParm,int dfltVal,int disabled);
void db_set(const char *zName,const char *zValue,int globalFlag);
typedef struct Setting Setting;
const Setting *setting_find(const char *zName);
struct Setting {
  const char *name;     /* Name of the setting */
  const char *var;      /* Internal variable name used by db_set() */
  int width;            /* Width of display.  0 for boolean values and
                        ** negative for values which should not appear
                        ** on the /setup_settings page. */
  char versionable;     /* Is this setting versionable? */
  char forceTextArea;   /* Force using a text area for display? */
  char sensitive;       /* True if this a security-sensitive setting */
  const char *def;      /* Default value */
};
typedef struct Stmt Stmt;
typedef struct Blob Blob;
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
void forum_setup(void);
char *cgi_parameter_trimmed(const char *zName,const char *zDefault);
#define PT(x)         cgi_parameter_trimmed((x),0)
void moderation_disapprove(int objid);
void db_protect_pop(void);
int db_multi_exec(const char *zSql,...);
#define PROTECT_USER       0x01  /* USER table */
void db_unprotect(unsigned flags);
void moderation_approve(char class,int rid);
int cgi_csrf_safe(int securityLevel);
#define PDT(x,y)      cgi_parameter_trimmed((x),(y))
const char *cgi_parameter_checked(const char *zName,int iValue);
#define PCK(x)        cgi_parameter_checked(x,1)
int login_self_register_available(const char *zNeeded);
void forumnew_page(void);
void forumedit_page(void);
void forum_page_init(void);
void cgi_csrf_verify(void);
void forum_page_close(void);
void mimetype_option_menu(const char *zMimetype,const char *zParam);
NORETURN void cgi_redirectf(const char *zFormat,...);
void db_end_transaction(int rollbackFlag);
#define db_commit_transaction()   db_end_transaction(0)
void alert_unqueue(char eventType,int rid);
int wiki_put(Blob *pWiki,int parent,int needMod);
char *blob_str(Blob *p);
typedef struct Manifest Manifest;
Manifest *manifest_parse(Blob *pContent,int rid,Blob *pErr);
void blob_copy(Blob *pTo,Blob *pFrom);
int login_is_nobody(void);
void webpage_assert_page(const char *zFile,int iLine,const char *zExpr);
# define webpage_assert(T) if(!(T)){webpage_assert_page(__FILE__,__LINE__,#T);}
void schema_forum(void);
int fossil_isspace(char c);
void style_submenu_checkbox(const char *zName,const char *zLabel,int eVisible,const char *zJS);
void style_submenu_element(const char *zLabel,const char *zLink,...);
int cgi_from_mobile(void);
void cgi_delete_query_parameter(const char *zName);
void cgi_replace_query_parameter(const char *zName,const char *zValue);
void cgi_check_for_malice(void);
void login_needed(int anonOk);
const char *cgi_parameter(const char *zName,const char *zDefault);
#define PD(x,y)       cgi_parameter((x),(y))
void forumthread_page(void);
void forumpost_page(void);
void builtin_request_js(const char *zFilename);
NULL_SENTINEL void builtin_fossil_js_bundle_or(const char *zApi,...);
int cgi_parameter_boolean(const char *zName);
#define PB(x)         cgi_parameter_boolean(x)
int moderation_pending(int rid);
void login_insert_csrf_secret(void);
int login_is_special(const char *zLogin);
int login_is_individual(void);
int content_is_private(int rid);
int fossil_num_digits(int n);
void manifest_destroy(Manifest *p);
#define CFTYPE_FORUM      8
Manifest *manifest_get(int rid,int cfType,Blob *pErr);
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
char *href(const char *zFormat,...);
char *mprintf(const char *zFormat,...);
int db_column_type(Stmt *pStmt,int N);
int db_bind_text(Stmt *pStmt,const char *zParamName,const char *zValue);
void wiki_render_by_mimetype(Blob *pWiki,const char *zMimetype);
#define DOCSRC_FORUM      2     /* Document is a forum post */
void safe_html_context(int eTrust);
void blob_append(Blob *pBlob,const char *aData,int nData);
void blob_init(Blob *pBlob,const char *zData,int size);
int fossil_strcmp(const char *zA,const char *zB);
void forum_render(const char *zTitle,const char *zMimetype,const char *zContent,const char *zClass,int bScroll);
void style_finish_page();
void style_header(const char *zTitleFormat,...);
void style_set_current_feature(const char *zFeature);
char *db_text(const char *zDefault,const char *zSql,...);
void ambiguous_page(void);
void webpage_notfound_error(const char *zFormat,...);
void webpage_error(const char *zFormat,...);
void login_check_credentials(void);
#define P(x)          cgi_parameter((x),0)
void forumthreadhashlist(void);
int db_int(int iDflt,const char *zSql,...);
int symbolic_name_to_rid(const char *zTag,const char *zType);
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
void db_find_and_open_repository(int bFlags,int nArgUsed);
void forumthread_cmd(void);
void fossil_print(const char *zFormat,...);
double db_column_double(Stmt *pStmt,int N);
const char *db_column_text(Stmt *pStmt,int N);
char *fossil_strdup(const char *zOrig);
void *fossil_malloc(size_t n);
void cgi_printf(const char *zFormat,...);
int db_get_boolean(const char *zName,int dflt);
void fossil_free(void *p);
void fossil_free(void *);
void admin_log(const char *zFormat,...);
void db_add_unsent(int rid);
int blob_is_reset(Blob *pBlob);
#define MC_NONE           0  /*  default handling           */
int manifest_crosslink(int rid,Blob *pContent,int flags);
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
NORETURN void fossil_fatal(const char *zFormat,...);
int content_put_ex(Blob *pBlob,const char *zUuid,int srcId,int nBlob,int isPrivate);
void blob_reset(Blob *pBlob);
int md5sum_blob(const Blob *pIn,Blob *pCksum);
const char *login_name(void);
char *date_in_standard_format(const char *zInputDate);
void blob_appendf(Blob *pBlob,const char *zFormat,...);
char *rid_to_uuid(int rid);
void db_begin_transaction_real(const char *zStartFile,int iStartLine);
#define db_begin_transaction()    db_begin_transaction_real(__FILE__,__LINE__)
void blobReallocMalloc(Blob *pBlob,unsigned int newSize);
#define BLOB_INITIALIZER  {0,0,0,0,0,blobReallocMalloc}
int rid_has_active_tag_name(int rid,const char *zTagName);
#define empty_Stmt_m {BLOB_INITIALIZER,NULL, NULL, NULL, 0, 0}
int db_finalize(Stmt *pStmt);
int db_column_int(Stmt *pStmt,int N);
int db_prepare(Stmt *pStmt,const char *zFormat,...);
int db_reset(Stmt *pStmt);
int db_step(Stmt *pStmt);
int db_bind_int(Stmt *pStmt,const char *zParamName,int iValue);
int db_static_prepare(Stmt *pStmt,const char *zFormat,...);
int forum_rid_has_been_edited(int rid);
typedef struct ForumThread ForumThread;
typedef struct ForumPost ForumPost;
struct ForumThread {
  ForumPost *pFirst;     /* First post in chronological order */
  ForumPost *pLast;      /* Last post in chronological order */
  ForumPost *pDisplay;   /* Entries in display order */
  ForumPost *pTail;      /* Last on the display list */
  int mxIndent;          /* Maximum indentation level */
  int nArtifact;         /* Number of forum artifacts in this thread */
};
struct ForumPost {
  int fpid;              /* rid for this post */
  int sid;               /* Serial ID number */
  int rev;               /* Revision number */
  char *zUuid;           /* Artifact hash */
  char *zDisplayName;    /* Name of user who wrote this post */
  double rDate;          /* Date for this post */
  ForumPost *pIrt;       /* This post replies to pIrt */
  ForumPost *pEditHead;  /* Original, unedited post */
  ForumPost *pEditTail;  /* Most recent edit for this post */
  ForumPost *pEditNext;  /* This post is edited by pEditNext */
  ForumPost *pEditPrev;  /* This post is an edit of pEditPrev */
  ForumPost *pNext;      /* Next in chronological order */
  ForumPost *pPrev;      /* Previous in chronological order */
  ForumPost *pDisplay;   /* Next in display order */
  int nEdit;             /* Number of edits to this post */
  int nIndent;           /* Number of levels of indentation for this post */
  int iClosed;           /* See forum_rid_is_closed() */
};
#define INTERFACE 0
struct ManifestFile {
  char *zName;           /* Name of a file */
  char *zUuid;           /* Artifact hash for the file */
  char *zPerm;           /* File permissions */
  char *zPrior;          /* Prior name if the name was changed */
};
