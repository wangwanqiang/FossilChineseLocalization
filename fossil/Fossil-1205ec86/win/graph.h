/* This file was automatically generated.  Do not edit! */
#undef INTERFACE
void cgi_printf(const char *zFormat,...);
typedef struct Matcher Matcher;
int match_text(Matcher *p,const char *zText);
typedef unsigned short int u16;
int count_nonbranch_children(int pid);
#define TIMELINE_FILLGAPS 0x0800000 /* Dotted lines for missing nodes */
#define TIMELINE_XMERGE   0x1000000 /* Omit merges from off-graph nodes */
typedef enum {
  MS_EXACT=1,   /* Exact string comparison */
  MS_GLOB=2,    /* Matches against a list of GLOB patterns. */
  MS_LIKE=3,    /* Matches against a list of LIKE patterns. */
  MS_REGEXP=4,  /* Matches against a list of regular expressions. */
  MS_BRLIST=5,  /* Matches any element of a list */
}MatchStyle;
typedef struct ReCompiled ReCompiled;
struct Matcher {
  MatchStyle style;   /* Which algorithm to use */
  int nPattern;       /* How many patterns are their */
  char **azPattern;   /* List of patterns */
  ReCompiled **aRe;   /* List of compiled regular expressions */
};
typedef struct GraphContext GraphContext;
typedef unsigned int u32;
void graph_finish(GraphContext *p,Matcher *pLeftBranch,u32 tmFlags);
#define TIMELINE_DISJOINT 0x0000010 /* Elements are not contiguous */
typedef sqlite3_int64 GraphRowId;
int graph_add_row(GraphContext *p,GraphRowId rid,int nParent,int nCherrypick,GraphRowId *aParent,const char *zBranch,const char *zBgClr,const char *zUuid,int isLeaf);
char *mprintf(const char *zFormat,...);
void *fossil_realloc(void *p,size_t n);
void *fossil_realloc(void *,size_t);
int fossil_strcmp(const char *zA,const char *zB);
void graph_free(GraphContext *p);
GraphContext *graph_init(void);
void *fossil_malloc(size_t n);
void *safeMalloc(int nByte);
typedef struct GraphRow GraphRow;
#define GR_MAX_RAIL   64      /* Max number of "rails" to display */
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
#define HNAME_MAX  64     /* Length for SHA3-256 */
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
#define INTERFACE 0
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
