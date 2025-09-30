/* This file was automatically generated.  Do not edit! */
#undef INTERFACE
int hash_digits(int bForUrl);
void describe_cmd(void);
int unsaved_changes(unsigned int cksigFlags);
typedef struct CommitDescr CommitDescr;
struct CommitDescr {
  char *zRelTagname;        /* Tag name on the relative check-in */
  int nCommitsSince;        /* Number of commits since then */
  char *zCommitHash;        /* Hash of the described check-in */
  int isDirty;              /* Working directory has uncommitted changes */
};
int describe_commit(const char *zName,const char *matchGlob,CommitDescr *descr);
int add_content_sql_commands(sqlite3 *db);
void test_symlink_list_cmd(void);
void manifest_to_disk(int vid);
typedef struct Blob Blob;
char *blob_materialize(Blob *pBlob);
int fossil_tolower(char c);
void prompt_user(const char *zPrompt,Blob *pIn);
int verify_comment(Blob *pComment,int mFlags);
#define COMCK_MARKUP    0x01  /* Check for mistakes */
#define COMCK_PREVIEW   0x02  /* Always preview, even if no issues found */
int is_false(const char *zVal);
int user_select(void);
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
const char **find_repeatable_option(const char *zLong,const char *zShort,int *pnUsedArgs);
void ci_amend_cmd(void);
void prompt_for_user_comment(Blob *pComment,Blob *pPrompt);
const unsigned char *get_utf8_bom(int *pnByte);
# define TAG_HIDDEN     5     /* Do not display in timeline */
# define TAG_CLOSED     9     /* Do not display this check-in as a leaf */
int fossil_strncmp(const char *zA,const char *zB,int nByte);
void form_begin(const char *zOtherArgs,const char *zAction,...);
char *hash_color(const char *z);
const char *reasonable_bg_color(const char *zRequested,int iFgClr);
char *date_in_standard_format(const char *zInputDate);
int cgi_csrf_safe(int securityLevel);
# define TAG_BGCOLOR    1     /* Set the background color for display */
char *cgi_parameter_trimmed(const char *zName,const char *zDefault);
#define PDT(x,y)      cgi_parameter_trimmed((x),(y))
void ci_edit_page(void);
int is_datetime(const char *zDate);
int blob_is_reset(Blob *pBlob);
void db_end_transaction(int rollbackFlag);
#define MC_PERMIT_HOOKS   1  /*  permit hooks to execute    */
int manifest_crosslink(int rid,Blob *pContent,int flags);
int content_put(Blob *pBlob);
int content_is_private(int rid);
void db_begin_transaction_real(const char *zStartFile,int iStartLine);
#define db_begin_transaction()    db_begin_transaction_real(__FILE__,__LINE__)
int md5sum_blob(const Blob *pIn,Blob *pCksum);
const char *login_name(void);
int is_a_leaf(int rid);
int fossil_isspace(char c);
void ainfo_page(void);
void forumthread_page(void);
void event_page(void);
void tktview_page(void);
void cgi_set_parameter_nocopy(const char *zName,const char *zValue,int isQP);
int name_to_uuid(Blob *pName,int iErrPriority,const char *zType);
void ambiguous_page(void);
void cgi_set_parameter(const char *zName,const char *zValue);
int name_collisions(const char *zName);
void info_page(void);
int skin_detail_boolean(const char *zName);
void describe_artifacts(const char *zWhere);
void blob_append_char(Blob *pBlob,char c);
int fast_uuid_to_rid(const char *zUuid);
#define CFTYPE_CLUSTER    2
typedef struct Manifest Manifest;
void ticket_output_change_artifact(Manifest *pTkt,const char *zListType,int n,Blob *aLastVal);
int db_table_has_column(const char *zDb,const char *zTable,const char *zColumn);
#define CFTYPE_TICKET     5
#define HNAME_MAX  64     /* Length for SHA3-256 */
void tinfo_page(void);
const char *mimetype_from_content(Blob *pBlob);
void blob_to_utf8_no_bom(Blob *pBlob,int useMbcs);
char *style_nonce(void);
#define DOCSRC_FILE       1     /* Document is a checked-in file */
typedef struct HQuery HQuery;
char *url_render(HQuery *p,const char *zName1,const char *zValue1,const char *zName2,const char *zValue2);
# define LINKPATH_FINFO  0x0001       /* Link final term to /finfo */
void hyperlinked_path(const char *zPath,Blob *pOut,const char *zCI,const char *zURI,const char *zREx,unsigned int mFlags);
void blob_set(Blob *pBlob,const char *zStr);
void url_add_parameter(HQuery *p,const char *zName,const char *zValue);
void url_initialize(HQuery *p,const char *zBase);
void page_tree(void);
void cgi_set_query_parameter(const char *zName,const char *zValue);
int branch_includes_uuid(const char *zBr,const char *zUuid);
int name_to_uuid2(const char *zName,const char *zType,char **pUuid);
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
void artifact_page(void);
void usage(const char *zFormat);
extern const Blob empty_blob;
void cmd_test_line_numbers(void);
void cgi_printf(const char *zFormat,...);
#define CX cgi_printf
char *htmlize(const char *z,int n);
int count_lines(const char *z,int n,int *pnLine);
int fossil_isdigit(char c);
#include <stdlib.h>
#include <dirent.h>
const char *file_extension(const char *zFileName);
void output_text_with_line_numbers(const char *z,int nZ,const char *zName,const char *zLn,int includeJS);
int name_to_typed_rid(const char *zName,const char *zType);
const char *file_tail(const char *z);
void hexdump_page(void);
void cgi_append_content(const char *zData,int nAmt);
void cgi_set_content(Blob *pNewContent);
void cgi_content_disposition_filename(const char *zFilename);
char *style_csp(int toHeader);
const char *mimetype_from_name(const char *zName);
void blob_append_json_literal(Blob *pOut,const char *z,int n);
int blob_line(Blob *pFrom,Blob *pTo);
int decode16(const unsigned char *zIn,unsigned char *pOut,int N);
void *fossil_malloc(size_t n);
int validate16(const char *zIn,int nIn);
void ajax_route_error(int httpCode,const char *zFmt,...);
void jchunk_page(void);
void cgi_set_status(int iStat,const char *zStat);
void secure_rawartifact_page(void);
void deliver_artifact(int rid,const char *zMime);
int login_is_nobody(void);
#define ETAG_HASH     0x08 /* Output depends on a hash */
void etag_check(unsigned eFlags,const char *zHash);
void rawartifact_page(void);
#define DIFF_VERBOSE           0x00000008 /* Missing shown as empty files */
void cgi_set_content_type(const char *zType);
NORETURN void fossil_redirect_home(void);
int artifact_from_ci_and_filename(const char *zNameParam);
void diff_page(void);
void cookie_link_parameter(const char *zQP,const char *zPName,const char *zDflt);
int user_agent_is_likely_mobile(void);
int db_get_int(const char *zName,int dflt);
# define TAG_CLUSTER    7     /* A cluster */
int fossil_is_artifact_hash(const char *zSym);
void hyperlink_to_event_tagid(int tagid);
int fileedit_is_editable(const char *zFilename);
char *fossil_strdup(const char *zOrig);
void tag_private_status(int rid);
void style_set_current_page(const char *zFormat,...);
# define TAG_BRANCH     8     /* Value is name of the current branch */
typedef unsigned int u32;
int object_description(int rid,u32 objdescFlags,const char *zFileName,Blob *pDownloadName);
#define OBJDESC_BASE        0x0002   /* Set <base> using this object */
#define OBJDESC_DETAIL      0x0001   /* Show more detail */
#define OBJTYPE_FORUM      0x0200
#define OBJTYPE_EXE        0x0100
#define OBJTYPE_SYMLINK    0x0080
#define OBJTYPE_TAG        0x0040
#define OBJTYPE_EVENT      0x0020
#define OBJTYPE_ATTACHMENT 0x0010
#define OBJTYPE_TICKET     0x0008
#define OBJTYPE_WIKI       0x0004
#define OBJTYPE_CONTENT    0x0002
#define OBJTYPE_CHECKIN    0x0001
#define INTERFACE 0
typedef struct Glob Glob;
void glob_free(Glob *pGlob);
typedef struct ManifestFile ManifestFile;
int manifest_file_mperm(const ManifestFile *pFile);
int glob_match(Glob *pGlob,const char *zString);
ManifestFile *manifest_file_next(Manifest *p,int *pErr);
void manifest_file_rewind(Manifest *p);
int symbolic_name_to_rid(const char *zTag,const char *zType);
char *rid_to_uuid(int rid);
void style_submenu_checkbox(const char *zName,const char *zLabel,int eVisible,const char *zJS);
#define TIMELINE_NOCOLOR 0x20000000 /* No colors except for highlights */
Glob *glob_create(const char *zPatternList);
void cgi_replace_parameter(const char *zName,const char *zValue);
void fossil_nice_default(void);
struct Glob {
  int nPattern;        /* Number of patterns */
  char **azPattern;    /* Array of pointers to patterns */
};
struct ManifestFile {
  char *zName;           /* Name of a file */
  char *zUuid;           /* Artifact hash for the file */
  char *zPerm;           /* File permissions */
  char *zPrior;          /* Prior name if the name was changed */
};
void vdiff_page(void);
#define CFTYPE_MANIFEST   1
int is_a_version(int rid);
void webpage_error(const char *zFormat,...);
void document_emit_js(void);
void manifest_destroy(Manifest *p);
void wiki_render_by_mimetype(Blob *pWiki,const char *zMimetype);
#define DOCSRC_WIKI       4     /* Document is a wiki page */
void safe_html_context(int eTrust);
void blob_init(Blob *pBlob,const char *zData,int size);
int wiki_next(int tagid,double mtime);
int wiki_tagid(const char *zPageName);
int moderation_pending_www(int rid);
void style_submenu_element(const char *zLabel,const char *zLink,...);
void moderation_approve(char class,int rid);
void moderation_disapprove(int objid);
#define CFTYPE_WIKI       4
Manifest *manifest_get(int rid,int cfType,Blob *pErr);
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
void winfo_page(void);
void render_backlink_graph(const char *zUuid,const char *zLabel);
int wiki_render_associated(const char *zPrefix,const char *zName,unsigned int mFlags);
int cgi_parameter_boolean(const char *zName);
#define PB(x)         cgi_parameter_boolean(x)
void builtin_request_js(const char *zFilename);
int db_get_boolean(const char *zName,int dflt);
void hyperlink_to_user(const char *zU,const char *zD,const char *zSuf);
const char *hname_alg(int nHash);
void blob_appendf(Blob *pBlob,const char *zFormat,...);
int wiki_tagid2(const char *zPrefix,const char *zPageName);
char *style_copy_button(int bOutputCGI,const char *zTargetId,int bFlipped,int cchLength,const char *zTextFmt,...);
int blob_trim(Blob *p);
# define TAG_COMMENT    2     /* The check-in comment */
# define TAG_USER       3     /* User who made a check-in */
void login_anonymous_available(void);
void Th_StoreUnsafe(const char *zName,const char *zValue);
void blobReallocMalloc(Blob *pBlob,unsigned int newSize);
#define BLOB_INITIALIZER  {0,0,0,0,0,blobReallocMalloc}
typedef struct Stmt Stmt;
int db_column_bytes(Stmt *pStmt,int N);
char *branch_of_rid(int rid);
int db_exists(const char *zSql,...);
typedef struct ReCompiled ReCompiled;
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
void ci_page(void);
char *decode16_dup(const char *zIn);
const char *cgi_parameter(const char *zName,const char *zDefault);
#define P(x)          cgi_parameter((x),0)
char *fossil_getenv(const char *zName);
char *file_getcwd(char *zBuf,int nBuf);
char *fossil_hostname(void);
void style_set_current_feature(const char *zFeature);
void db_protect_pop(void);
#define CKSIG_ENOTFILE  0x001   /* non-file FS objects throw an error */
void vfile_check_signature(int vid,unsigned int cksigFlags);
#define PROTECT_ALL        0x1f  /* All of the above */
void db_unprotect(unsigned flags);
int file_chdir(const char *zChDir,int bChroot);
NORETURN void cgi_redirectf(const char *zFormat,...);
int db_open_local(const char *zDbName);
int cgi_is_loopback(const char *zIpAddr);
void ckout_page(void);
void fossil_free(void *p);
void fossil_free(void *);
char *file_canonical_name_dup(const char *zOrigName);
#define blob_buffer(X)  ((X)->aData)
#define blob_size(X)  ((X)->nUsed)
char *mprintf(const char *zFormat,...);
sqlite3_int64 blob_read_from_file(Blob *pBlob,const char *zFilename,int eFType);
#define DIFF_CANNOT_COMPUTE_SYMLINK \
    "cannot compute difference between symlink and regular file\n"
int file_islink(const char *zFilename);
#define DIFF_FILE_ADDED        0x40000000 /* Added or rename destination */
int file_access(const char *zFilename,int flags);
#define DIFF_FILE_DELETED      0x80000000 /* Deleted or rename source */
#define DIFF_FILE_MASK         0xc0000000 /* Used for clearing file flags */
char *chref(const char *zExtra,const char *zFormat,...);
int preferred_diff_type(void);
#define TIMELINE_DISJOINT 0x0000010 /* Elements are not contiguous */
void hyperlink_to_date(const char *zDate,const char *zSuffix);
void hyperlink_to_version(const char *zVerHash);
char const *whatis_rid_type_label(int rid);
void cgi_check_for_malice(void);
void style_finish_page();
void style_header(const char *zTitleFormat,...);
int name_to_rid_www(const char *zParamName);
void login_needed(int anonOk);
void login_check_credentials(void);
void ci_tags_page(void);
#define PD(x,y)       cgi_parameter((x),(y))
typedef struct DiffConfig DiffConfig;
DiffConfig *diff_config_init(DiffConfig *pCfg,u64 diffFlags);
#define DIFF_STRIP_EOLCR       0x00001000 /* Strip trailing CR */
#define DIFF_NOOPT             0x00000100 /* Suppress optimizations (debug) */
const char *cgi_parameter_no_attack(const char *zName,const char *zDefault);
#define PD_NoBot(x,y) cgi_parameter_no_attack((x),(y))
#define DIFF_IGNORE_ALLWS      0x00000003 /* Ignore all whitespace */
#define P_NoBot(x)    cgi_parameter_no_attack((x),0)
DiffConfig *construct_diff_flags(int diffType,DiffConfig *pCfg);
NULL_SENTINEL void builtin_fossil_js_bundle_or(const char *zApi,...);
void append_diff_javascript(int diffType);
char *href(const char *zFormat,...);
#define PERM_LNK          2     /*  symlink       */
#define PERM_EXE          1     /*  executable    */
Blob *cgi_output_blob(void);
int *text_diff(Blob *pA_Blob,Blob *pB_Blob,Blob *pOut,DiffConfig *pCfg);
#define DIFF_LINENO            0x00000040 /* Show line numbers */
#define DIFF_NOTTOOBIG         0x00000800 /* Only display if not too big */
#define DIFF_HTML              0x00000020 /* Render for HTML */
#define DIFF_SIDEBYSIDE        0x00000004 /* Generate a side-by-side diff */
int content_get(int rid,Blob *pBlob);
int uuid_to_rid(const char *zUuid,int phantomize);
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
#define TIMELINE_CHPICK   0x0400000 /* Show cherrypick merges */
#define TIMELINE_XMERGE   0x1000000 /* Omit merges from off-graph nodes */
#define TIMELINE_NOSCROLL 0x0100000 /* Don't scroll to the selection */
#define TIMELINE_FILLGAPS 0x0800000 /* Dotted lines for missing nodes */
#define TIMELINE_GRAPH    0x0000008 /* Compute a graph */
typedef struct Matcher Matcher;
void www_print_timeline(Stmt *pQuery,int tmFlags,const char *zThisUser,const char *zThisTag,Matcher *pLeftBranch,int selectedRid,int secondRid,void(*xExtra)(int));
char *blob_sql_text(Blob *p);
void blob_append_sql(Blob *pBlob,const char *zFormat,...);
int db_table_exists(const char *zDb,const char *zTable);
int db_multi_exec(const char *zSql,...);
const char *timeline_query_for_www(void);
void blob_append(Blob *pBlob,const char *aData,int nData);
void blob_zero(Blob *pBlob);
void render_checkin_context(int rid,int rid2,int parentsOnly,int mFlags);
NORETURN void fossil_fatal(const char *zFormat,...);
int name_to_rid(const char *zName);
void blob_reset(Blob *pBlob);
char *file_fullexename(const char *zCmd);
char *blob_str(Blob *p);
void fossil_version_blob(Blob *pOut,int eVerbose);
int db_int(int iDflt,const char *zSql,...);
int db_lget_int(const char *zName,int dflt);
const char *db_repository_filename(void);
void verify_all_options(void);
#define OPEN_OK_NOT_FOUND       0x001   /* Do not error out if not found */
void db_find_and_open_repository(int bFlags,int nArgUsed);
void db_record_repository_filename(const char *zName);
void db_open_repository(const char *zDbName);
int db_open_config(int useAttach,int isOptional);
i64 file_size(const char *zFilename,int eFType);
#define ExtFILE    0  /* Always follow symlinks */
int file_isfile(const char *zFilename,int eFType);
const char *find_option(const char *zLong,const char *zShort,int hasArg);
void info_cmd(void);
char *db_get(const char *zName,const char *zDefault);
int fossil_strcmp(const char *zA,const char *zB);
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
int vfile_top_of_checkout(const char *zPath);
int get_comment_format();
int comment_print(const char *zText,const char *zOrigText,int indent,int width,int flags);
int db_finalize(Stmt *pStmt);
int db_column_int(Stmt *pStmt,int N);
const char *db_column_text(Stmt *pStmt,int N);
int db_step(Stmt *pStmt);
int db_prepare(Stmt *pStmt,const char *zFormat,...);
void fossil_print(const char *zFormat,...);
struct Stmt {
  Blob sql;               /* The SQL for this statement */
  sqlite3_stmt *pStmt;    /* The results of sqlite3_prepare_v2() */
  Stmt *pNext, *pPrev;    /* List of all unfinalized statements */
  int nStep;              /* Number of sqlite3_step() calls */
  int rc;                 /* Error from db_vprepare() */
};
void show_common_info(int rid,const char *zRecDesc,int showComment,int showFamily);
char *db_text(const char *zDefault,const char *zSql,...);
char *info_tags_of_checkin(int rid,int propagatingOnly);
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
