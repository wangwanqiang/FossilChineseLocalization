/* This file was automatically generated.  Do not edit! */
#undef INTERFACE
void style_table_sorter(void);
void test_timewarp_page(void);
void test_timewarp_cmd(void);
int fossil_isdate(const char *z);
void style_set_current_feature(const char *zFeature);
void thisdayinhistory_page(void);
typedef struct Stmt Stmt;
typedef struct Blob Blob;
int db_prepare_blob(Stmt *pStmt,Blob *pSql);
int filenames_are_case_sensitive(void);
void compute_descendants(int rid,int N);
#include <stdlib.h>
#include <dirent.h>
int file_tree_name(const char *zOrigName,Blob *pOut,int absolute,int errFatal);
int name_to_uuid(Blob *pName,int iErrPriority,const char *zType);
NORETURN void fossil_fatal(const char *zFormat,...);
void timeline_cmd(void);
const char *timeline_query_for_tty(void);
void html_to_plaintext(const char *zIn,Blob *pOut,int mFlags);
int wiki_convert_flags(int altForm2);
int get_comment_format();
int comment_print(const char *zText,const char *zOrigText,int indent,int width,int flags);
int count_nonbranch_children(int pid);
void print_timeline(Stmt *q,int nLimit,int width,const char *zFormat,int verboseFlag);
void style_finish_page();
void document_emit_js(void);
typedef struct Matcher Matcher;
void match_free(Matcher *p);
typedef enum {
  MS_EXACT=1,   /* Exact string comparison */
  MS_GLOB=2,    /* Matches against a list of GLOB patterns. */
  MS_LIKE=3,    /* Matches against a list of LIKE patterns. */
  MS_REGEXP=4,  /* Matches against a list of regular expressions. */
  MS_BRLIST=5,  /* Matches any element of a list */
}MatchStyle;
Matcher *match_create(MatchStyle style,const char *zPat);
void cgi_check_for_malice(void);
#define WIKIASSOC_ALL         0x00007   /* All of the above */
int wiki_render_associated(const char *zPrefix,const char *zName,unsigned int mFlags);
int fossil_toupper(char c);
int fossil_islower(char c);
#define SRCH_CKIN     0x0001    /* Search over check-in comments */
unsigned int search_restrict(unsigned int srchFlags);
typedef struct HQuery HQuery;
void url_add_parameter(HQuery *p,const char *zName,const char *zValue);
double symbolic_name_to_mtime(const char *z,const char **pzDisplay,int bRoundUp);
char *url_render(HQuery *p,const char *zName1,const char *zValue1,const char *zName2,const char *zValue2);
int fossil_ui_localtime(void);
void style_submenu_entry(const char *zName,const char *zLabel,int iSize,int eVisible);
int last_checkin_with_tag_before_date(const char *zTag,double rLimit);
int db_exists(const char *zSql,...);
int first_checkin_with_tag_after_date(const char *zTag,double rStart);
double mtime_of_rid(int rid,double mtime);
void compute_ancestors(int rid,int N,int directOnly,int ridBackTo);
void path_reset(void);
typedef struct PathNode PathNode;
const char *path_branch(PathNode *p);
PathNode *path_first(void);
int path_common_ancestor(int iMe,int iYou);
typedef struct Bag Bag;
PathNode *path_shortest(int iFrom,int iTo,int directOnly,int oneWayOnly,Bag *pHidden,int branchCost);
struct PathNode {
  int rid;                 /* ID for this node */
  u8 fromIsParent;         /* True if pFrom is the parent of rid */
  u8 isPrim;               /* True if primary side of common ancestor */
  u8 isHidden;             /* Abbreviate output in "fossil bisect ls" */
  char *zBranch;           /* Branch name for this node.  Might be NULL */
  double mtime;            /* Date/time of this check-in */
  PathNode *pFrom;         /* Node we came from */
  union {
    double rCost;          /* Cost of getting to this node from pStart */
    PathNode *pTo;         /* Next on path from beginning to end */
  } u;
  PathNode *pAll;          /* List of all nodes */
};
void cgi_replace_parameter(const char *zName,const char *zValue);
# define TAG_HIDDEN     5     /* Do not display in timeline */
void login_anonymous_available(void);
void style_header(const char *zTitleFormat,...);
void style_submenu_element(const char *zLabel,const char *zLink,...);
int bisect_create_bilog_table(int iCurrent,const char *zDesc,int bDetail);
char *bisect_permalink(void);
# define TAG_BRANCH     8     /* Value is name of the current branch */
void compute_uses_file(const char *zTab,int fid,int usesFlags);
void db_append_dml_to_blob(Blob *pBlob);
void style_submenu_enable(int onOff);
const char *match_tag_sqlexpr(MatchStyle matchStyle,const char *zTag,const char **zDesc,const char **zError);
void style_submenu_checkbox(const char *zName,const char *zLabel,int eVisible,const char *zJS);
void Th_StoreUnsafe(const char *zName,const char *zValue);
MatchStyle match_style(const char *zStyle,MatchStyle eDflt);
void cgi_set_query_parameter(const char *zName,const char *zValue);
void cgi_delete_query_parameter(const char *zName);
void cgi_set_parameter(const char *zName,const char *zValue);
#define ETAG_CONFIG   0x01 /* Output depends on the CONFIG table */
#define ETAG_DATA     0x02 /* Output depends on the EVENT table */
#define ETAG_COOKIE   0x04 /* Output depends on a display cookie value */
#define ETAG_QUERY    0x10 /* Output depends on PATH_INFO and QUERY_STRING */
void etag_check(unsigned eFlags,const char *zHash);
void login_needed(int anonOk);
void builtin_set_js_delivery_mode(const char *zMode,int bSilent);
void cgi_replace_query_parameter(const char *zName,const char *zValue);
void cookie_read_parameter(const char *zQP,const char *zPName);
void cookie_write_parameter(const char *zQP,const char *zPName,const char *zDflt);
const char *cgi_parameter_no_attack(const char *zName,const char *zDefault);
#define P_NoBot(x)    cgi_parameter_no_attack((x),0)
void cgi_query_parameters_to_url(HQuery *p);
void url_initialize(HQuery *p,const char *zBase);
void login_check_credentials(void);
int name_choice(const char *zQP1,const char *zQP2,const char **pzPick);
int name_to_typed_rid(const char *zName,const char *zType);
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
void page_timeline(void);
char *rid_to_uuid(int rid);
void fossil_print(const char *zFormat,...);
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
void timeline_test_endpoint(void);
char *blob_sql_text(Blob *p);
int db_exec_sql(const char *z);
int name_to_rid(const char *zName);
void blob_init(Blob *pBlob,const char *zData,int size);
void db_unpause_dml_log(void);
void db_pause_dml_log(void);
int symbolic_name_to_rid(const char *zTag,const char *zType);
int fossil_isdigit(char c);
const char *timeline_expand_datetime(const char *zIn,int *pbZulu);
char *glob_expr(const char *zVal,const char *zGlobList);
void blob_append_sql(Blob *pBlob,const char *zFormat,...);
void cookie_link_parameter(const char *zQP,const char *zPName,const char *zDflt);
int timeline_ss_submenu(void);
# define N_TIMELINE_VIEW_STYLE 5
extern const char *const timeline_view_styles[];
const char *cookie_value(const char *zPName,const char *zDefault);
const char *timeline_default_ss(void);
void style_submenu_multichoice(const char *zName,int nChoice,const char *const *azChoice,int eVisible);
char *names_of_file(const char *zUuid);
int db_int(int iDflt,const char *zSql,...);
const char *timeline_query_for_www(void);
int db_multi_exec(const char *zSql,...);
void builtin_request_js(const char *zFilename);
int hash_digits(int bForUrl);
int cgi_parameter_boolean(const char *zName);
#define PB(x)         cgi_parameter_boolean(x)
char *db_get(const char *zName,const char *zDefault);
const char *cgi_parameter(const char *zName,const char *zDefault);
#define PD(x,y)       cgi_parameter((x),(y))
typedef struct GraphRow GraphRow;
typedef sqlite3_int64 GraphRowId;
#define HNAME_MAX  64     /* Length for SHA3-256 */
#define GR_MAX_RAIL   64      /* Max number of "rails" to display */
struct GraphRow {
  GraphRowId rid;             /* The rid for the check-in */
  i8 nParent;                 /* Number of parents. */
  i8 nCherrypick;             /* Subset of aParent that are cherrypicks */
  i8 nNonCherrypick;          /* Number of non-cherrypick parents */
  u8 nMergeChild;             /* Number of merge children */
  GraphRowId *aParent;        /* Array of parents.  0 element is primary .*/
  char *zBranch;              /* Branch name */
  char *zBgClr;               /* Background Color */
  char zUuid[HNAME_MAX+1];    /* Check-in for file ID */

  GraphRow *pNext;            /* Next row down in the list of all rows */
  GraphRow *pPrev;            /* Previous row */

  int idx;                    /* Row index.  Top row is smallest. */
  int idxTop;                 /* Direct descendant highest up on the graph */
  GraphRow *pChild;           /* Child immediately above this node */
  u8 isDup;                   /* True if this is duplicate of a prior entry */
  u8 isLeaf;                  /* True if this is a leaf node */
  u8 isStepParent;            /* pChild is actually a step-child. The thick
                              ** arrow up to the child is dashed, not solid */
  u8 hasNormalOutMerge;       /* Is parent of at laest 1 non-cherrypick merge */
  u8 timeWarp;                /* Child is earlier in time */
  u8 bDescender;              /* True if riser from bottom of graph to here. */
  u8 selfUp;                  /* Space above this node but belonging */
  i8 iRail;                   /* Which rail this check-in appears on. 0-based.*/
  i8 mergeOut;                /* Merge out to this rail.  -1 if no merge-out */
  u8 mergeIn[GR_MAX_RAIL];    /* Merge in from non-zero rails */
  int aiRiser[GR_MAX_RAIL];   /* Risers from this node to a higher row. */
  int mergeUpto;              /* Draw the mergeOut rail up to this level */
  int cherrypickUpto;         /* Continue the mergeOut rail up to here */
  u64 mergeDown;              /* Draw merge lines up from bottom of graph */
  u64 cherrypickDown;         /* Draw cherrypick lines up from bottom */
  u64 railInUse;              /* Mask of occupied rails at this row */
};
int skin_detail_boolean(const char *zName);
int hex_digit_value(char c);
typedef struct GraphContext GraphContext;
void timeline_output_graph_javascript(GraphContext *pGraph,int tmFlags,int iTableId);
int db_finalize(Stmt *pStmt);
void graph_free(GraphContext *p);
typedef unsigned int u32;
void graph_finish(GraphContext *p,Matcher *pLeftBranch,u32 tmFlags);
void forum_render(const char *zTitle,const char *zMimetype,const char *zContent,const char *zClass,int bScroll);
int forum_rid_has_been_edited(int rid);
char *fossil_strdup(const char *zOrig);
int db_prepare(Stmt *pStmt,const char *zFormat,...);
void blob_appendf(Blob *pBlob,const char *zFormat,...);
#define MANIFEST_UUID "1205ec86cb5508e94b90698db2900997fe5c9db62429c67ac6fdc03d59aa2782"
void blob_reset(Blob *pBlob);
#define blob_buffer(X)  ((X)->aData)
void blob_append(Blob *pBlob,const char *aData,int nData);
int fossil_isspace(char c);
#define blob_size(X)  ((X)->nUsed)
#define WIKI_INLINE        0x0002  /* Do not surround with <p>..</p> */
int wiki_convert(Blob *pIn,Blob *pOut,int flags);
void wiki_hyperlink_override(const char *zUuid);
char *blob_str(Blob *p);
int delta_source_rid(int rid);
void hyperlink_to_event_tagid(int tagid);
void db_column_blob(Stmt *pStmt,int N,Blob *pBlob);
int graph_add_row(GraphContext *p,GraphRowId rid,int nParent,int nCherrypick,GraphRowId *aParent,const char *zBranch,const char *zBgClr,const char *zUuid,int isLeaf);
char *branch_of_rid(int rid);
const char *reasonable_bg_color(const char *zRequested,int iFgClr);
char *hash_color(const char *z);
char *user_color(const char *zLogin);
char *mprintf(const char *zFormat,...);
void fossil_free(void *p);
void fossil_free(void *);
int is_ticket(const char *zTarget,int *pClosed);
char *db_text(const char *zDefault,const char *zSql,...);
int fossil_strnicmp(const char *zA,const char *zB,int nByte);
int fossil_strcmp(const char *zA,const char *zB);
int moderation_pending(int rid);
const char *db_column_text(Stmt *pStmt,int N);
int db_column_int(Stmt *pStmt,int N);
void blob_zero(Blob *pBlob);
int db_table_exists(const char *zDb,const char *zTable);
GraphContext *graph_init(void);
#define P(x)          cgi_parameter((x),0)
int timeline_ss_cookie(void);
int db_get_boolean(const char *zName,int dflt);
int db_get_int(const char *zName,int dflt);
int db_lget_int(const char *zName,int dflt);
int db_open_local(const char *zDbName);
int cgi_is_loopback(const char *zIpAddr);
struct GraphContext {
  int nErr;                  /* Number of errors encountered */
  int mxRail;                /* Number of rails required to render the graph */
  GraphRow *pFirst;          /* First row in the list.  Top row of graph. */
  GraphRow *pLast;           /* Last row in the list. Bottom row of graph. */
  int nBranch;               /* Number of distinct branches */
  char **azBranch;           /* Names of the branches */
  int nRow;                  /* Number of rows */
  int nHash;                 /* Number of slots in apHash[] */
  u8 hasOffsetMergeRiser;    /* Merge arrow from leaf goes up on a different
                             ** rail that the node */
  u8 bOverfull;              /* Unable to allocate sufficient rails */
  u64 mergeRail;             /* Rails used for merge lines */
  GraphRow **apHash;         /* Hash table of GraphRow objects.  Key: rid */
  u8 aiRailMap[GR_MAX_RAIL+1]; /* Mapping of rails to actually columns */
};
typedef struct ReCompiled ReCompiled;
struct Matcher {
  MatchStyle style;   /* Which algorithm to use */
  int nPattern;       /* How many patterns are their */
  char **azPattern;   /* List of patterns */
  ReCompiled **aRe;   /* List of compiled regular expressions */
};
void www_print_timeline(Stmt *pQuery,int tmFlags,const char *zThisUser,const char *zThisTag,Matcher *pLeftBranch,int selectedRid,int secondRid,void(*xExtra)(int));
typedef struct Manifest Manifest;
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
int db_reset(Stmt *pStmt);
int db_step(Stmt *pStmt);
int db_bind_int(Stmt *pStmt,const char *zParamName,int iValue);
# define TAG_CLOSED     9     /* Do not display this check-in as a leaf */
int db_static_prepare(Stmt *pStmt,const char *zFormat,...);
struct Stmt {
  Blob sql;               /* The SQL for this statement */
  sqlite3_stmt *pStmt;    /* The results of sqlite3_prepare_v2() */
  Stmt *pNext, *pPrev;    /* List of all unfinalized statements */
  int nStep;              /* Number of sqlite3_step() calls */
  int rc;                 /* Error from db_vprepare() */
};
int timeline_tableid(void);
#define TIMELINE_NOCOLOR 0x20000000 /* No colors except for highlights */
#define TIMELINE_DELTA   0x10000000 /* Background color shows delta manifests */
#define TIMELINE_REFS     0x8000000 /* Output intended for References tab */
#define TIMELINE_FORUMTXT 0x4000000 /* Render all forum messages */
#define TIMELINE_NOTKT    0x2000000 /* Omit extra ticket classes */
#define TIMELINE_XMERGE   0x1000000 /* Omit merges from off-graph nodes */
#define TIMELINE_FILLGAPS 0x0800000 /* Dotted lines for missing nodes */
#define TIMELINE_CHPICK   0x0400000 /* Show cherrypick merges */
#define TIMELINE_FILEDIFF 0x0200000 /* Show File differences, not ckin diffs */
#define TIMELINE_NOSCROLL 0x0100000 /* Don't scroll to the selection */
#define TIMELINE_VIEWS    0x001f000 /* Mask for all of the view styles */
#define TIMELINE_CLASSIC  0x0010000 /* Use the "classic" view style */
#define TIMELINE_COLUMNAR 0x0008000 /* Use the "columns" view style */
#define TIMELINE_MODERN   0x0004000 /* Use the "modern" view style */
#define TIMELINE_VERBOSE  0x0002000 /* Use the "detailed" view style */
#define TIMELINE_COMPACT  0x0001000 /* Use the "compact" view style */
#define TIMELINE_BISECT   0x0000800 /* Show supplemental bisect information */
#define TIMELINE_SHOWRID  0x0000400 /* Show RID values in addition to hashes */
#define TIMELINE_UNHIDE   0x0000200 /* Unhide check-ins with "hidden" tag */
#define TIMELINE_FRENAMES 0x0000100 /* Detail only file name changes */
#define TIMELINE_UCOLOR   0x0000080 /* Background color by user */
#define TIMELINE_BRCOLOR  0x0000040 /* Background color by branch name */
#define TIMELINE_FCHANGES 0x0000020 /* Detail file changes */
#define TIMELINE_DISJOINT 0x0000010 /* Elements are not contiguous */
#define TIMELINE_GRAPH    0x0000008 /* Compute a graph */
#define TIMELINE_BRIEF    0x0000004 /* Combine adjacent elements of same obj */
#define TIMELINE_LEAFONLY 0x0000002 /* Show "Leaf" but not "Merge", "Fork" etc*/
#define TIMELINE_ARTID    0x0000001 /* Show artifact IDs on non-check-in lines*/
#define INTERFACE 0
void hyperlink_to_user(const char *zU,const char *zD,const char *zSuf);
char *href(const char *zFormat,...);
void hyperlink_to_date(const char *zDate,const char *zSuffix);
char *chref(const char *zExtra,const char *zFormat,...);
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
void hyperlink_to_version(const char *zVerHash);
void cgi_printf(const char *zFormat,...);
int content_is_private(int rid);
void tag_private_status(int rid);
struct Bag {
  int cnt;   /* Number of integers in the bag */
  int sz;    /* Number of slots in a[] */
  int used;  /* Number of used slots in a[] */
  int *a;    /* Hash table of integers that are in the bag */
};
struct ManifestFile {
  char *zName;           /* Name of a file */
  char *zUuid;           /* Artifact hash for the file */
  char *zPerm;           /* File permissions */
  char *zPrior;          /* Prior name if the name was changed */
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
