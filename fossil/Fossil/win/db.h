/* This file was automatically generated.  Do not edit! */
#undef INTERFACE
void db_add_unsent(int rid);
#define MANIFEST_UUID "99675884a93c09125dbfbef0ca47959626c81545c132e247e67a08bd12ac7256"
#define MANIFEST_DATE "2025-09-30 11:03:45"
#define RELEASE_VERSION "2.27"
void test_fingerprint(void);
void md5sum_step_text(const char *zText,int nBytes);
void test_database_name_cmd(void);
typedef struct Blob Blob;
struct Blob {
  unsigned int nUsed;            /* Number of bytes used in aData[] */
  unsigned int nAlloc;           /* Number of bytes allocated for aData[] */
  unsigned int iCursor;          /* Next character of input to parse */
  unsigned int blobFlags;        /* One or more BLOBFLAG_* bits */
  char *aData;                   /* Where the information is stored */
  void (*xRealloc)(Blob*, unsigned int); /* Function to reallocate the buffer */
};
extern const Blob empty_blob;
void admin_log(const char *zFormat,...);
void create_admin_log_table(void);
void test_without_rowid(void);
void test_timespan_cmd(void);
char *db_timespan_name(double rSpan);
void manifest_to_disk(int vid);
void setting_cmd(void);
int fossil_strncmp(const char *zA,const char *zB,int nByte);
typedef struct Setting Setting;
void print_setting(const Setting *pSetting,int valueOnly,int bIfChng);
int setting_has_default_value(const Setting *pSetting,const char *zVal);
void info_cmd(void);
#define CKSIG_SETMTIME  0x004   /* Set mtime to last check-out time */
void vfile_check_signature(int vid,unsigned int cksigFlags);
void checkout_cmd(void);
void db_set_checkout(int rid);
extern const char zLocalSchema[];
#define SYNC_PULL           0x00002    /* pull content server to client */
int autosync_loop(int flags,int doPrompt,const char *zSubsystem);
int fossil_system(const char *zOrigCmd);
void blob_append_escaped_arg(Blob *pBlob,const char *zIn,int isFilename);
char *url_to_repo_basename(const char *zUrl);
#include <stdlib.h>
#include <dirent.h>
int file_in_cwd(const char *zFile);
int file_directory_size(const char *zDir,const char *zGlob,int omitDotFiles);
int file_mkfolder(const char *zFilename,int eFType,int forceFlag,int errorReturn);
void url_proxy_options(void);
void cmd_open(void);
const char *filename_collation(void);
void test_manfest_setting_cmd(void);
int db_get_manifest_setting(const char *zCkin);
#define MFESTFLG_TAGS 0x04
#define MFESTFLG_UUID 0x02
#define MFESTFLG_RAW  0x01
char *db_get_for_subsystem(const char *zName,const char *zSubsys);
void db_unset_mprintf(int iGlobal,const char *zFormat,...);
void db_set_mprintf(const char *zNew,int iGlobal,const char *zFormat,...);
char *db_get_mprintf(const char *zDefault,const char *zFormat,...);
void db_lset_int(const char *zName,int value);
int db_lget_boolean(const char *zName,int dflt);
int db_lget_int(const char *zName,int dflt);
int db_get_versioned_boolean(const char *zName,int dflt);
i64 db_large_file_size(void);
int db_is_global(const char *zName);
void db_unset(const char *zName,int globalFlag);
#define CMDFLAG_KEEPEMPTY    0x4000     /* Do not unset empty settings */
#define CMDFLAG_SETTING      0x0020     /* A setting */
typedef struct CmdOrPage CmdOrPage;
int dispatch_name_search(const char *zName,unsigned eType,const CmdOrPage **ppCmd);
struct CmdOrPage {
  const char *zName;       /* Name.  Webpages start with "/". Commands do not */
  void (*xFunc)(void);     /* Implementation function, or NULL for settings */
  const char *zHelp;       /* Raw help text */
  int iHelp;               /* Index of help variable */
  unsigned int eCmdFlags;  /* Flags */
};
char *db_get_mtime(const char *zName,const char *zFormat,const char *zDefault);
void *fossil_malloc(size_t n);
int blob_trim(Blob *p);
void blob_strip_comment_lines(Blob *pIn,Blob *pOut);
sqlite3_int64 blob_read_from_file(Blob *pBlob,const char *zFilename,int eFType);
int historical_blob(const char *zRevision,const char *zFile,Blob *pBlob,int fatal);
char *db_get_versioned(const char *zName,char *zNonVersionedSetting,const char *zCkin);
void db_swap_connections(void);
int is_false(const char *zVal);
int fossil_stricmp(const char *zA,const char *zB);
int is_truth(const char *zVal);
char *db_reveal(const char *zKey);
char *sha1sum_finish(Blob *pOut);
void sha1sum_step_text(const char *zText,int nBytes);
int hname_validate(const char *zHash,int nHash);
#define HNAME_MAX  64     /* Length for SHA3-256 */
char *db_conceal(const char *zContent,int n);
const char *file_is_win_reserved(const char *zPath);
void hash_user_password(const char *zUser);
#define HPOLICY_SHA1           0      /* Use SHA1 hashes */
void create_repository_cmd(void);
#define MC_NONE           0  /*  default handling           */
int manifest_crosslink(int rid,Blob *pContent,int flags);
int content_put(Blob *pBlob);
int md5sum_blob(const Blob *pIn,Blob *pCksum);
char *md5sum_finish(Blob *pOut);
void md5sum_init(void);
char *date_in_standard_format(const char *zInputDate);
#define CONFIGSET_ALL       0x0007ff     /* Everything */
const char *configure_inop_rhs(int iMask);
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
const char *get_version();
#define CONTENT_SCHEMA  "2"
void db_set(const char *zName,const char *zValue,int globalFlag);
void db_initial_setup(const char *zTemplate,const char *zInitialDate,const char *zDefaultUser);
void blob_append_sql(Blob *pBlob,const char *zFormat,...);
const Setting *setting_info(int *pnCount);
const char *db_setting_inop_rhs();
char *fossil_random_password(int N);
void db_create_default_users(int setupUserOnly,const char *zDefaultUser);
extern const char zRepositorySchema2[];
extern const char zRepositorySchemaDefaultReports[];
extern const char zRepositorySchema1[];
void db_panic_close(void);
void backoffice_run_if_needed(void);
void db_must_be_within_tree(void);
void db_record_repository_filename(const char *zName);
void move_repo_cmd(void);
#define AUX_SCHEMA_MAX  "2015-01-24"
#define AUX_SCHEMA_MIN  "2011-04-25 19:50"
int db_schema_is_outofdate(void);
void db_create_repository(const char *zFilename);
void db_verify_schema(void);
const char *find_repository_option();
#define OPEN_SUBSTITUTE         0x004   /* Fake in-memory repo if not found */
#define OPEN_ANY_SCHEMA         0x002   /* Do not error if schema is wrong */
#define OPEN_OK_NOT_FOUND       0x001   /* Do not error out if not found */
int db_repository_has_changed(void);
extern const char zLocalSchemaVmerge[];
void db_lset(const char *zName,const char *zValue);
char *db_fingerprint(int rcvid,int iVersion);
void bisect_reset(void);
void undo_reset(void);
void stash_rid_renumbering_event(void);
void vfile_rid_renumbering_event(int dryRun);
int db_fingerprint_ok(void);
void db_set_int(const char *zName,int value,int globalFlag);
int hname_default_policy(void);
char *db_get(const char *zName,const char *zDefault);
int db_get_boolean(const char *zName,int dflt);
void test_is_repo(void);
int db_looks_like_a_repository(const char *zDbName);
int db_allow_symlinks(void);
char *file_canonical_name_dup(const char *zOrigName);
int file_is_absolute_path(const char *zPath);
char *db_lget(const char *zName,const char *zDefault);
const char *db_repository_filename(void);
int db_open_local(const char *zDbName);
void db_open_repository(const char *zDbName);
int db_open_local_v2(const char *zDbName,int bRootOnly);
int db_table_has_column(const char *zDb,const char *zTable,const char *zColumn);
extern const char zConfigSchema[];
int file_access(const char *zFilename,int flags);
int file_mkdir(const char *zName,int eFType,int forceFlag);
char *file_dirname(const char *z);
int db_open_config(int useAttach,int isOptional);
int file_isdir(const char *zFilename,int eFType);
#define ExtFILE    0  /* Always follow symlinks */
i64 file_size(const char *zFilename,int eFType);
void db_close_config();
void db_open_or_attach(const char *zDbName,const char *zLabel);
int fossil_strcmp(const char *zA,const char *zB);
int db_database_slot(const char *zLabel);
void db_set_main_schemaname(sqlite3 *db,const char *zLabel);
int db_table_exists(const char *zDb,const char *zTable);
void db_attach(const char *zDbName,const char *zLabel);
void db_detach(const char *zLabel);
int db_register_fts5(sqlite3 *db);
int foci_register(sqlite3 *db);
int re_add_sql_func(sqlite3 *db);
int db_sql_trace(unsigned m,void *notUsed,void *pP,void *pX);
#define LOCAL static
LOCAL void file_is_selected(sqlite3_context *context,int argc,sqlite3_value **argv);
void db_sql_print(sqlite3_context *context,int argc,sqlite3_value **argv);
LOCAL void db_sql_cgi(sqlite3_context *context,int argc,sqlite3_value **argv);
LOCAL void db_sql_user(sqlite3_context *context,int argc,sqlite3_value **argv);
void file_canonical_name(const char *zOrigName,Blob *pOut,int slash);
void db_maybe_set_encryption_key(sqlite3 *db,const char *zDbName);
void prompt_for_password(const char *zPrompt,Blob *pPassphrase,int verify);
char *fossil_getenv(const char *zName);
int file_chdir(const char *zChDir,int bChroot);
#if !defined(_WIN32)
typedef void *LPVOID;
typedef size_t SIZE_T;
#endif
#if USE_SEE
void parse_pid_key_value(const char *zPidKey,PID_T *pProcessId,LPVOID *ppAddress,SIZE_T *pnSize);
#endif
#define TH_OK       0
typedef struct Th_Interp Th_Interp;
const char *Th_GetResult(Th_Interp *,int *);
int Th_Eval(Th_Interp *interp,int iFrame,const char *zProg,int nProg);
typedef unsigned int u32;
#define TH_INIT_NO_REPO     ((u32)0x00000010) /* Skip opening repository. */
#define TH_INIT_NEED_CONFIG ((u32)0x00000001) /* Open configuration first? */
#define TH_INIT_NONE        ((u32)0x00000000) /* No flags. */
#define TH_INIT_DEFAULT     (TH_INIT_NONE)      /* Default flags. */
void Th_FossilInit(u32 flags);
char *file_getcwd(char *zBuf,int nBuf);
void login_needed(int anonOk);
void login_check_credentials(void);
#if USE_SEE
void db_unset_see_key_page(void);
PID_T db_maybe_handle_saved_encryption_key_for_process(int eType);
#endif
void blob_set(Blob *pBlob,const char *zStr);
const char *cgi_parameter(const char *zName,const char *zDefault);
#define P(x)          cgi_parameter((x),0)
#if USE_SEE
void db_set_see_key_page(void);
#endif
void fossil_secure_zero(void *p,size_t n);
void fossil_secure_free_page(void *p,size_t n);
int fossil_setenv(const char *zName,const char *zValue);
void blob_appendf(Blob *pBlob,const char *zFormat,...);
void *fossil_secure_alloc_page(size_t *pN);
void fossil_get_page_size(size_t *piPageSize);
#if USE_SEE
void db_unsave_encryption_key();
void db_setup_for_saved_encryption_key();
size_t db_get_saved_encryption_key_size();
char *db_get_saved_encryption_key();
int db_is_valid_saved_encryption_key(const char *p,size_t n);
int db_have_saved_encryption_key();
#endif
void artifact_to_json_sql_func(sqlite3_context *context,int argc,sqlite3_value **argv);
void file_inode_sql_func(sqlite3_context *context,int argc,sqlite3_value **argv);
void chat_msg_from_event(sqlite3_context *context,int argc,sqlite3_value **argv);
void url_nouser_func(sqlite3_context *context,int argc,sqlite3_value **argv);
LOCAL void db_win_reserved_func(sqlite3_context *context,int argc,sqlite3_value **argv);
void alert_display_name_func(sqlite3_context *context,int argc,sqlite3_value **argv);
void alert_find_emailaddr_func(sqlite3_context *context,int argc,sqlite3_value **argv);
void capability_fullcap(sqlite3_context *context,int argc,sqlite3_value **argv);
void capability_union_finalize(sqlite3_context *context);
void capability_union_step(sqlite3_context *context,int argc,sqlite3_value **argv);
void db_add_aux_functions(sqlite3 *db);
int fossil_tolower(char c);
int fossil_isdigit(char c);
LOCAL void db_protected_setting_func(sqlite3_context *context,int argc,sqlite3_value **argv);
Setting *db_find_setting(const char *zName,int allowPrefix);
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
void fossil_strcpy(char *dest,const char *src);
char *unobscure(const char *zIn);
char *obscure(const char *zIn);
void db_obscure(sqlite3_context *context,int argc,sqlite3_value **argv);
int decode16(const unsigned char *zIn,unsigned char *pOut,int N);
int validate16(const char *zIn,int nIn);
void db_hextoblob(sqlite3_context *context,int argc,sqlite3_value **argv);
void db_fromlocal_function(sqlite3_context *context,int argc,sqlite3_value **argv);
void db_tolocal_function(sqlite3_context *context,int argc,sqlite3_value **argv);
int fossil_ui_localtime(void);
int db_get_int(const char *zName,int dflt);
int fossil_ui_utctime(void);
int symbolic_name_to_rid(const char *zTag,const char *zType);
void db_sym2rid_function(sqlite3_context *context,int argc,sqlite3_value **argv);
int mtime_of_manifest_file(int vid,int fid,i64 *pMTime);
void db_checkin_mtime_function(sqlite3_context *context,int argc,sqlite3_value **argv);
void db_now_function(sqlite3_context *context,int argc,sqlite3_value **argv);
LOCAL sqlite3 *db_open(const char *zDbName);
void db_init_database(const char *zFileName,const char *zSchema,...);
char *db_text(const char *zDefault,const char *zSql,...);
void db_blob(Blob *pResult,const char *zSql,...);
double db_double(double rDflt,const char *zSql,...);
int db_exists(const char *zSql,...);
int db_int(int iDflt,const char *zSql,...);
i64 db_int64(i64 iDflt,const char *zSql,...);
void db_optional_sql(const char *zDb,const char *zSql,...);
int db_exec_sql(const char *z);
void fossil_print(const char *zFormat,...);
int db_debug(const char *zSql,...);
void ticket_unrestrict_sql(void);
void fossil_free(void *p);
void fossil_free(void *);
void report_unrestrict_sql(void);
void ticket_restrict_sql(int *pNErr);
void report_restrict_sql(char **pzErr);
void usage(const char *zFormat);
void verify_all_options(void);
const char *find_option(const char *zLong,const char *zShort,int hasArg);
void db_test_db_prepare(void);
void db_find_and_open_repository(int bFlags,int nArgUsed);
void db_test_db_exec_cmd(void);
typedef struct Stmt Stmt;
int db_exec(Stmt *pStmt);
void db_ephemeral_blob(Stmt *pStmt,int N,Blob *pBlob);
Blob db_column_text_as_blob(Stmt *pStmt,int N);
void db_column_blob(Stmt *pStmt,int N,Blob *pBlob);
char *fossil_strdup_nn(const char *zOrig);
char *db_column_malloc(Stmt *pStmt,int N);
int db_column_count(Stmt *pStmt);
const char *db_column_name(Stmt *pStmt,int N);
const char *db_column_raw(Stmt *pStmt,int N);
const char *db_column_text(Stmt *pStmt,int N);
double db_column_double(Stmt *pStmt,int N);
i64 db_column_int64(Stmt *pStmt,int N);
int db_column_int(Stmt *pStmt,int N);
int db_column_bytes(Stmt *pStmt,int N);
int db_column_type(Stmt *pStmt,int N);
int db_changes(void);
int db_last_insert_rowid(void);
void blob_reset(Blob *pBlob);
int db_reset(Stmt *pStmt);
int db_step(Stmt *pStmt);
int db_bind_str(Stmt *pStmt,const char *zParamName,Blob *pBlob);
#define blob_buffer(X)  ((X)->aData)
int db_bind_blob(Stmt *pStmt,const char *zParamName,Blob *pBlob);
int db_bind_null(Stmt *pStmt,const char *zParamName);
int db_bind_text16(Stmt *pStmt,const char *zParamName,const char *zValue);
int db_bind_text(Stmt *pStmt,const char *zParamName,const char *zValue);
int db_bind_double(Stmt *pStmt,const char *zParamName,double rValue);
int db_bind_int64(Stmt *pStmt,const char *zParamName,i64 iValue);
int db_bind_int(Stmt *pStmt,const char *zParamName,int iValue);
char *blob_sql_text(Blob *p);
void blob_init(Blob *pBlob,const char *zData,int size);
int db_prepare_blob(Stmt *pStmt,Blob *pSql);
int db_static_stmt_is_init(Stmt *pStmt);
#define blob_size(X)  ((X)->nUsed)
int db_static_prepare(Stmt *pStmt,const char *zFormat,...);
int db_prepare_ignore_error(Stmt *pStmt,const char *zFormat,...);
int db_prepare(Stmt *pStmt,const char *zFormat,...);
int fossil_all_whitespace(const char *z);
void blob_vappendf(Blob *pBlob,const char *zFormat,va_list ap);
void blob_zero(Blob *pBlob);
int db_vprepare(Stmt *pStmt,int flags,const char *zFormat,va_list ap);
void db_unpause_dml_log(void);
void db_pause_dml_log(void);
void db_append_dml_to_blob(Blob *pBlob);
void blob_append_char(Blob *pBlob,char c);
void blob_append(Blob *pBlob,const char *aData,int nData);
int fossil_strnicmp(const char *zA,const char *zB,int nByte);
int fossil_isspace(char c);
#define DB_PREPARE_PERSISTENT    0x002  /* Stmt will stick around for a while */
#define DB_PREPARE_IGNORE_ERROR  0x001  /* Suppress errors */
void db_clear_authorizer(void);
void db_set_authorizer(int(*xAuth)(void *,int,const char *,const char *,const char *,const char *),void *pArg,const char *zName);
void fossil_errorlog(const char *zFormat,...);
int db_top_authorizer(void *pNotUsed,int eCode,const char *z0,const char *z1,const char *z2,const char *z3);
int db_setting_is_protected(const char *zName);
void db_assert_protection_off_or_not_sensitive(const char *zName);
void db_assert_protected(unsigned flags);
int db_is_protected(unsigned flags);
void db_unprotect(unsigned flags);
void db_protect(unsigned flags);
#define PROTECT_NONE       0x00  /* Nothing.  Everything is open */
#define PROTECT_ALL        0x1f  /* All of the above */
#define PROTECT_READONLY   0x08  /* everything except TEMP tables */
void db_commit_hook(int(*x)(void),int sequence);
int file_delete(const char *zFilename);
void db_close(int reportErrors);
void undo_rollback(void);
void db_force_rollback(void);
int db_finalize(Stmt *pStmt);
void db_protect_pop(void);
void leaf_do_pending_checks(void);
#define PROTECT_SENSITIVE  0x04  /* Sensitive and/or global settings */
void db_protect_only(unsigned flags);
void fossil_trace(const char *zFormat,...);
void fossil_warning(const char *zFormat,...);
int db_is_writeable(const char *zName);
int db_multi_exec(const char *zSql,...);
void db_end_transaction(int rollbackFlag);
#define db_rollback_transaction() db_end_transaction(1)
#define db_commit_transaction()   db_end_transaction(0)
void db_begin_write_real(const char *zStartFile,int iStartLine);
#define db_begin_write()          db_begin_write_real(__FILE__,__LINE__)
void db_begin_transaction_real(const char *zStartFile,int iStartLine);
#define db_begin_transaction()    db_begin_transaction_real(__FILE__,__LINE__)
NORETURN void fossil_panic(const char *zFormat,...);
char *db_transaction_start_point(void);
int db_transaction_nesting_depth(void);
char *fossil_strdup(const char *zOrig);
void db_delete_on_failure(const char *zFilename);
#define PROTECT_BASELINE   0x10  /* protection system is working */
#define PROTECT_CONFIG     0x02  /* CONFIG and GLOBAL_CONFIG tables */
#define PROTECT_USER       0x01  /* USER table */
char *blob_str(Blob *p);
NORETURN void fossil_fatal(const char *zFormat,...);
char *mprintf(const char *zFormat,...);
void cgi_reply(void);
void cgi_printf(const char *zFormat,...);
void cgi_reset_content(void);
#if defined(FOSSIL_ENABLE_JSON)
void json_err(int code,char const *msg,int alsoOutput);
void json_bootstrap_early(void);
#endif
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
char *vmprintf(const char *zFormat,va_list ap);
struct Stmt {
  Blob sql;               /* The SQL for this statement */
  sqlite3_stmt *pStmt;    /* The results of sqlite3_prepare_v2() */
  Stmt *pNext, *pPrev;    /* List of all unfinalized statements */
  int nStep;              /* Number of sqlite3_step() calls */
  int rc;                 /* Error from db_vprepare() */
};
extern const struct Stmt empty_Stmt;
void blobReallocMalloc(Blob *pBlob,unsigned int newSize);
#define BLOB_INITIALIZER  {0,0,0,0,0,blobReallocMalloc}
#define empty_Stmt_m {BLOB_INITIALIZER,NULL, NULL, NULL, 0, 0}
#define SEE_KEY_ZERO  ((int)2)
#define SEE_KEY_WRITE ((int)1)
#define SEE_KEY_READ  ((int)0)
#define INTERFACE 0
