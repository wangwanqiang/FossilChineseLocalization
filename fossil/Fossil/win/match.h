/* This file was automatically generated.  Do not edit! */
#undef INTERFACE
#define blob_size(X)  ((X)->nUsed)
typedef struct Blob Blob;
void blob_appendf(Blob *pBlob,const char *zFormat,...);
int db_int(int iDflt,const char *zSql,...);
char *mprintf(const char *zFormat,...);
typedef enum {
  MS_EXACT=1,   /* Exact string comparison */
  MS_GLOB=2,    /* Matches against a list of GLOB patterns. */
  MS_LIKE=3,    /* Matches against a list of LIKE patterns. */
  MS_REGEXP=4,  /* Matches against a list of regular expressions. */
  MS_BRLIST=5,  /* Matches any element of a list */
}MatchStyle;
const char *match_tag_sqlexpr(MatchStyle matchStyle,const char *zTag,const char **zDesc,const char **zError);
char *blob_str(Blob *p);
void blob_append(Blob *pBlob,const char *aData,int nData);
void blob_zero(Blob *pBlob);
void blobReallocMalloc(Blob *pBlob,unsigned int newSize);
#define BLOB_INITIALIZER  {0,0,0,0,0,blobReallocMalloc}
struct Blob {
  unsigned int nUsed;            /* Number of bytes used in aData[] */
  unsigned int nAlloc;           /* Number of bytes allocated for aData[] */
  unsigned int iCursor;          /* Next character of input to parse */
  unsigned int blobFlags;        /* One or more BLOBFLAG_* bits */
  char *aData;                   /* Where the information is stored */
  void (*xRealloc)(Blob*, unsigned int); /* Function to reallocate the buffer */
};
typedef struct Matcher Matcher;
void match_free(Matcher *p);
typedef struct ReCompiled ReCompiled;
int re_match(ReCompiled *pRe,const unsigned char *zIn,int nIn);
int match_text(Matcher *p,const char *zText);
void fossil_free(void *p);
void fossil_free(void *);
void *fossil_realloc(void *p,size_t n);
void *fossil_realloc(void *,size_t);
void re_free(ReCompiled *pRe);
const char *fossil_re_compile(ReCompiled **ppRe,const char *zIn,int noCase);
char *fossil_strndup(const char *zOrig,ssize_t len);
int fossil_isspace(char c);
char *fossil_strdup(const char *zOrig);
void *fossil_malloc(size_t n);
Matcher *match_create(MatchStyle style,const char *zPat);
int fossil_stricmp(const char *zA,const char *zB);
MatchStyle match_style(const char *zStyle,MatchStyle eDflt);
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
struct Matcher {
  MatchStyle style;   /* Which algorithm to use */
  int nPattern;       /* How many patterns are their */
  char **azPattern;   /* List of patterns */
  ReCompiled **aRe;   /* List of compiled regular expressions */
};
#define INTERFACE 0
