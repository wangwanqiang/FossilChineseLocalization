/* This file was automatically generated.  Do not edit! */
#undef INTERFACE
#define WIKI_BUTTONS       0x0008  /* Allow sub-menu buttons */
typedef struct Blob Blob;
int wiki_find_title(Blob *pIn,Blob *pTitle,Blob *pTail);
void convert_href_and_output(Blob *pIn);
typedef struct mkd_renderer mkd_renderer;
void markdown(struct Blob *ob,const struct Blob *ib,const struct mkd_renderer *rndrer);
int wiki_render_associated(const char *zPrefix,const char *zName,unsigned int mFlags);
#define WIKIASSOC_ALL         0x00007   /* All of the above */
#define WIKIASSOC_MENU_WRITE  0x00004   /* Add submenu link to add wiki */
#define WIKIASSOC_MENU_READ   0x00002   /* Add submenu link to read wiki */
#define WIKIASSOC_FULL_TITLE  0x00001   /* Full title */
void event_cmd_commit(char *zETime,int rid,Blob *pContent,const char *zMimeType,const char *zComment,const char *zTags,const char *zClr);
void fossil_print(const char *zFormat,...);
void db_set(const char *zName,const char *zValue,int globalFlag);
#include <stdlib.h>
#define ExtFILE    0  /* Always follow symlinks */
sqlite3_int64 blob_read_from_file(Blob *pBlob,const char *zFilename,int eFType);
int blob_read_from_channel(Blob *pBlob,FILE *in,int nToRead);
#include <dirent.h>
void fossil_fclose(FILE *f);
#define blob_buffer(X)  ((X)->aData)
FILE *fossil_fopen_for_output(const char *zFilename);
void htmlize_to_blob(Blob *p,const char *zIn,int n);
int fossil_isspace(char c);
#define CFTYPE_EVENT      7
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
void verify_all_options(void);
void db_find_and_open_repository(int bFlags,int nArgUsed);
const char *find_option(const char *zLong,const char *zShort,int hasArg);
void wiki_cmd(void);
void canonical16(char *z,int n);
int validate16(const char *zIn,int nIn);
#define HNAME_MAX  64     /* Length for SHA3-256 */
int wiki_technote_to_rid(const char *zETime);
int user_select(void);
void wfind_page(void);
void style_table_sorter(void);
char *fossil_strdup(const char *zOrig);
void style_submenu_checkbox(const char *zName,const char *zLabel,int eVisible,const char *zJS);
void wcontent_page(void);
typedef struct DiffConfig DiffConfig;
int *text_diff(Blob *pA_Blob,Blob *pB_Blob,Blob *pOut,DiffConfig *pCfg);
DiffConfig *construct_diff_flags(int diffType,DiffConfig *pCfg);
void webpage_notfound_error(const char *zFormat,...);
int name_to_typed_rid(const char *zName,const char *zType);
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
void wdiff_page(void);
char *chref(const char *zExtra,const char *zFormat,...);
char *human_readable_age(double rAge);
typedef struct Stmt Stmt;
double db_column_double(Stmt *pStmt,int N);
double db_double(double rDflt,const char *zSql,...);
void whistory_page(void);
void captcha_generate(int mFlags);
int md5sum_blob(const Blob *pIn,Blob *pCksum);
#define blob_size(X)  ((X)->nUsed)
int login_is_nobody(void);
char *date_in_standard_format(const char *zInputDate);
void blob_append(Blob *pBlob,const char *aData,int nData);
void blob_zero(Blob *pBlob);
int captcha_is_correct(int bAlwaysNeeded);
NORETURN void fossil_redirect_home(void);
void wikiappend_page(void);
void blob_appendf(Blob *pBlob,const char *zFormat,...);
char *db_text(const char *zDefault,const char *zSql,...);
void form_begin(const char *zOtherArgs,const char *zAction,...);
void wikinew_page(void);
void style_script_end(void);
void style_script_begin(const char *zOrigin,int iLine);
void builtin_fulfill_js_requests(void);
void builtin_request_js(const char *zFilename);
NULL_SENTINEL void builtin_fossil_js_bundle_or(const char *zApi,...);
void style_select_list_int(const char *zWrapperId,const char *zFieldName,const char *zLabel,const char *zToolTip,int selectedVal,...);
void style_emit_noscript_for_js_page(void);
void wikiedit_page(void);
void wikiedit_emit_toggle_preview(void);
int cgi_csrf_safe(int securityLevel);
int cmp_ajax_route_name(const void *a,const void *b);
typedef struct AjaxRoute AjaxRoute;
struct AjaxRoute {
  const char *zName;   /* Name part of the route after "ajax/" */
  void (*xCallback)(); /* Impl function for the route. */
  int bWriteMode;      /* True if requires write mode */
  int bPost;           /* True if requires POST (i.e. CSRF
                       ** verification) */
};
void wiki_ajax_page(void);
void ajax_render_diff(Blob *pOrig,const char *zOrigHash,Blob *pContent,u64 diffFlags);
#define DIFF_IGNORE_ALLWS      0x00000003 /* Ignore all whitespace */
#define DIFF_IGNORE_EOLWS      0x00000001 /* Ignore end-of-line whitespace */
#define DIFF_SIDEBYSIDE        0x00000004 /* Generate a side-by-side diff */
#define DIFF_LINENO            0x00000040 /* Show line numbers */
const char *cgi_parameter(const char *zName,const char *zDefault);
#define PD(x,y)       cgi_parameter((x),(y))
#define DIFF_STRIP_EOLCR       0x00001000 /* Strip trailing CR */
#define DIFF_NOTTOOBIG         0x00000800 /* Only display if not too big */
#define DIFF_HTML              0x00000020 /* Render for HTML */
void db_end_transaction(int rollbackFlag);
int wiki_cmd_commit(const char *zPageName,int rid,Blob *pContent,const char *zMimeType,int localUser);
void db_begin_transaction_real(const char *zStartFile,int iStartLine);
#define db_begin_transaction()    db_begin_transaction_real(__FILE__,__LINE__)
struct Blob {
  unsigned int nUsed;            /* Number of bytes used in aData[] */
  unsigned int nAlloc;           /* Number of bytes allocated for aData[] */
  unsigned int iCursor;          /* Next character of input to parse */
  unsigned int blobFlags;        /* One or more BLOBFLAG_* bits */
  char *aData;                   /* Where the information is stored */
  void (*xRealloc)(Blob*, unsigned int); /* Function to reallocate the buffer */
};
extern const Blob empty_blob;
int ajax_p_bool(char const *zKey);
char *rid_to_uuid(int rid);
void cgi_printf(const char *zFormat,...);
#define CX cgi_printf
const char *db_column_text(Stmt *pStmt,int N);
void ajax_route_error(int httpCode,const char *zFmt,...);
int db_finalize(Stmt *pStmt);
int db_column_int(Stmt *pStmt,int N);
int db_step(Stmt *pStmt);
int db_prepare(Stmt *pStmt,const char *zFormat,...);
struct Stmt {
  Blob sql;               /* The SQL for this statement */
  sqlite3_stmt *pStmt;    /* The results of sqlite3_prepare_v2() */
  Stmt *pNext, *pPrev;    /* List of all unfinalized statements */
  int nStep;              /* Number of sqlite3_step() calls */
  int rc;                 /* Error from db_vprepare() */
};
extern const struct Stmt empty_Stmt;
void mimetype_option_menu(const char *zMimetype,const char *zParam);
const char *login_name(void);
void alert_user_contact(const char *zUser);
int login_is_individual(void);
#define MC_NONE           0  /*  default handling           */
int manifest_crosslink(int rid,Blob *pContent,int flags);
void db_add_unsent(int rid);
int db_multi_exec(const char *zSql,...);
void moderation_table_create(void);
int content_deltify(int rid,int *aSrc,int nSrc,int force);
int content_put_ex(Blob *pBlob,const char *zUuid,int srcId,int nBlob,int isPrivate);
int wiki_put(Blob *pWiki,int parent,int needMod);
void document_emit_js(void);
void fossil_free(void *p);
void fossil_free(void *);
void attachment_list(const char *zTarget,const char *zHeader,int fHorizontalRule);
typedef struct Manifest Manifest;
void manifest_destroy(Manifest *p);
#define DOCSRC_WIKI       4     /* Document is a wiki page */
void style_set_current_page(const char *zFormat,...);
#define CFTYPE_WIKI       4
Manifest *manifest_get(int rid,int cfType,Blob *pErr);
int symbolic_name_to_rid(const char *zTag,const char *zType);
char *mprintf(const char *zFormat,...);
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
const char *wiki_page_type_name(const char *zPageName);
int db_exists(const char *zSql,...);
int wiki_page_type(const char *zPageName);
# define WIKITYPE_TICKET     4
# define WIKITYPE_TAG        3
# define WIKITYPE_CHECKIN    2
# define WIKITYPE_BRANCH     1
# define WIKITYPE_NORMAL     0
# define WIKITYPE_UNKNOWN    (-1)
#define INTERFACE 0
int search_screen(unsigned srchAllowed,int mFlags);
void wiki_srchpage(void);
void login_needed(int anonOk);
void wiki_helppage(void);
#define SRCH_WIKI     0x0008    /* Search over wiki */
unsigned int search_restrict(unsigned int srchFlags);
int db_get_boolean(const char *zName,int dflt);
char *fossil_getenv(const char *zName);
int wiki_need_moderation(int localUser);
void markup_help_page(void);
void wiki_rules_page(void);
#define DOCSRC_TRUSTED    5     /* safe_html() is always a no-op */
void safe_html_context(int eTrust);
void interwiki_append_map_table(Blob *out);
char *blob_materialize(Blob *pBlob);
const char *builtin_text(const char *zFilename);
void blob_init(Blob *pBlob,const char *zData,int size);
void style_submenu_element(const char *zLabel,const char *zLink,...);
void markdown_rules_page(void);
void cgi_set_content_type(const char *zType);
char *pikchr(const char *zText,const char *zClass,unsigned int mFlags,int *pnWidth,int *pnHeight);
void blob_reset(Blob *pBlob);
char *blob_str(Blob *p);
void safe_html(Blob *in);
void markdown_to_html(struct Blob *input_markdown,struct Blob *output_title,struct Blob *output_body);
void markdown_to_html(struct Blob *input_markdown,struct Blob *output_title,struct Blob *output_body);
void blobReallocMalloc(Blob *pBlob,unsigned int newSize);
#define BLOB_INITIALIZER  {0,0,0,0,0,blobReallocMalloc}
int wiki_convert(Blob *pIn,Blob *pOut,int flags);
void wiki_render_by_mimetype(Blob *pWiki,const char *zMimetype);
const char *wiki_filter_mimetypes(const char *zMimetype);
int fossil_stricmp(const char *zA,const char *zB);
char *href(const char *zFormat,...);
void wiki_page(void);
void cgi_set_parameter_nocopy(const char *zName,const char *zValue,int isQP);
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
NORETURN void cgi_redirectf(const char *zFormat,...);
int fossil_strcmp(const char *zA,const char *zB);
#define P(x)          cgi_parameter((x),0)
void cgi_check_for_malice(void);
void login_check_credentials(void);
char *db_get(const char *zName,const char *zDefault);
void home_page(void);
int wiki_prev(int tagid,double mtime);
int wiki_next(int tagid,double mtime);
int wiki_tagid2(const char *zPrefix,const char *zPageName);
int db_int(int iDflt,const char *zSql,...);
int wiki_tagid(const char *zPageName);
void style_finish_page();
void style_header(const char *zTitleFormat,...);
void style_set_current_feature(const char *zFeature);
int wiki_name_is_wellformed(const unsigned char *z);
int fossil_strncmp(const char *zA,const char *zB,int nByte);
struct ManifestFile {
  char *zName;           /* Name of a file */
  char *zUuid;           /* Artifact hash for the file */
  char *zPerm;           /* File permissions */
  char *zPrior;          /* Prior name if the name was changed */
};
enum mkd_autolink {
  MKDA_NOT_AUTOLINK,    /* used internally when it is not an autolink*/
  MKDA_NORMAL,          /* normal http/http/ftp link */
  MKDA_EXPLICIT_EMAIL,  /* e-mail link with explicit mailto: */
  MKDA_IMPLICIT_EMAIL   /* e-mail link without mailto: */
};
typedef enum mkd_autolink mkd_autolink;
struct mkd_renderer {
  /* document level callbacks */
  void (*prolog)(struct Blob *ob, void *opaque);
  void (*epilog)(struct Blob *ob, void *opaque);
  void (*footnotes)(struct Blob *ob, const struct Blob *items, void *opaque);

  /* block level callbacks - NULL skips the block */
  void (*blockcode)(struct Blob *ob, struct Blob *text, void *opaque);
  void (*blockquote)(struct Blob *ob, struct Blob *text, void *opaque);
  void (*blockhtml)(struct Blob *ob, struct Blob *text, void *opaque);
  void (*header)(struct Blob *ob, struct Blob *text,
            int level, void *opaque);
  void (*hrule)(struct Blob *ob, void *opaque);
  void (*list)(struct Blob *ob, struct Blob *text, int flags, void *opaque);
  void (*listitem)(struct Blob *ob, struct Blob *text,
            int flags, void *opaque);
  void (*paragraph)(struct Blob *ob, struct Blob *text, void *opaque);
  void (*table)(struct Blob *ob, struct Blob *head_row, struct Blob *rows,
              void *opaque);
  void (*table_cell)(struct Blob *ob, struct Blob *text, int flags,
              void *opaque);
  void (*table_row)(struct Blob *ob, struct Blob *cells, int flags,
              void *opaque);
  void (*footnote_item)(struct Blob *ob, const struct Blob *text,
              int index, int nUsed, void *opaque);

  /* span level callbacks - NULL or return 0 prints the span verbatim */
  int (*autolink)(struct Blob *ob, struct Blob *link,
          enum mkd_autolink type, void *opaque);
  int (*codespan)(struct Blob *ob, struct Blob *text, int nSep, void *opaque);
  int (*double_emphasis)(struct Blob *ob, struct Blob *text,
            char c, void *opaque);
  int (*emphasis)(struct Blob *ob, struct Blob *text, char c,void*opaque);
  int (*image)(struct Blob *ob, struct Blob *link, struct Blob *title,
            struct Blob *alt, void *opaque);
  int (*linebreak)(struct Blob *ob, void *opaque);
  int (*link)(struct Blob *ob, struct Blob *link, struct Blob *title,
          struct Blob *content, void *opaque);
  int (*raw_html_tag)(struct Blob *ob, struct Blob *tag, void *opaque);
  int (*triple_emphasis)(struct Blob *ob, struct Blob *text,
            char c, void *opaque);
  int (*footnote_ref)(struct Blob *ob, const struct Blob *span,
              const struct Blob *upc, int index, int locus, void *opaque);

  /* low level callbacks - NULL copies input directly into the output */
  void (*entity)(struct Blob *ob, struct Blob *entity, void *opaque);
  void (*normal_text)(struct Blob *ob, struct Blob *text, void *opaque);

  /* renderer data */
  const char *emph_chars; /* chars that trigger emphasis rendering */
  void *opaque; /* opaque data send to every rendering callback */
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
  int nInit;                  /* Number of characters in zInit */
  unsigned nState;            /* Number of entries in aOp[] and aArg[] */
  unsigned nAlloc;            /* Slots allocated for aOp[] and aArg[] */
};
