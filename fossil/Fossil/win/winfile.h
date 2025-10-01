/* This file was automatically generated.  Do not edit! */
#undef INTERFACE
char *mprintf(const char *zFormat,...);
#if defined(_WIN32)
char *win32_file_id(const char *zFileName);
#endif
void *fossil_utf8_to_path(const char *zUtf8,int isDir);
void *fossil_realloc(void *p,size_t n);
void *fossil_realloc(void *,size_t);
char *fossil_strdup(const char *zOrig);
int filenames_are_case_sensitive(void);
#if defined(_WIN32)
char *win32_file_case_preferred_name(const char *zBase,const char *zPath);
int win32_filenames_equal_nocase(const wchar_t *fn1,const wchar_t *fn2);
#endif
void fossil_path_free(void *pOld);
void fossil_free(void *p);
void fossil_free(void *);
char *fossil_path_to_utf8(const void *zPath);
NORETURN void fossil_fatal(const char *zFormat,...);
void *fossil_malloc(size_t n);
#if defined(_WIN32)
void win32_getcwd(char *zBuf,int nBuf);
int win32_chdir(const wchar_t *zChDir,int bChroot);
int win32_access(const wchar_t *zFilename,int flags);
#endif
#if defined(_WIN32) && (defined(__MSVCRT__) || defined(_MSC_VER))
typedef struct fossilStat fossilStat;
#endif
#include <stdlib.h>
#include <dirent.h>
#if defined(_WIN32) && (defined(__MSVCRT__) || defined(_MSC_VER))
struct fossilStat {
    i64 st_size;
    i64 st_mtime;
    int st_mode;
};
#endif
#if defined(_WIN32)
int win32_stat(const wchar_t *zFilename,struct fossilStat *buf,int eFType);
#endif
