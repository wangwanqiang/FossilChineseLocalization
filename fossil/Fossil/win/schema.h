/* This file was automatically generated.  Do not edit! */
#undef INTERFACE
int db_multi_exec(const char *zSql,...);
int db_table_exists(const char *zDb,const char *zTable);
void schema_forum(void);
extern const char zLocalSchemaVmerge[];
extern const char zLocalSchema[];
# define TAG_NOTE       11    /* Extra text appended to a check-in comment */
# define TAG_PARENT     10    /* Change to parentage on a check-in */
# define TAG_CLOSED     9     /* Do not display this check-in as a leaf */
# define TAG_BRANCH     8     /* Value is name of the current branch */
# define TAG_CLUSTER    7     /* A cluster */
# define TAG_PRIVATE    6     /* Do not sync */
# define TAG_HIDDEN     5     /* Do not display in timeline */
# define TAG_DATE       4     /* The date of a check-in */
# define TAG_USER       3     /* User who made a check-in */
# define TAG_COMMENT    2     /* The check-in comment */
# define TAG_BGCOLOR    1     /* Set the background color for display */
# define ValidMTC(X)  ((X)>=0 && (X)<=3)  /* True if MIMEtype code is valid */
# define MT_UNKNOWN    3   /* unknown  */
# define MT_MARKDOWN   2   /* Markdonw */
# define MT_WIKI       1   /* Wiki */
# define MT_NONE       0   /* unspecified */
# define ValidBklnk(X)   (X>=0 && X<=4)  /* True if backlink.srctype is valid */
# define BKLNK_FORUM      4   /* Forum post */
# define BKLNK_EVENT      3   /* Technote */
# define BKLNK_WIKI       2   /* Wiki */
# define BKLNK_TICKET     1   /* Ticket body or title */
# define BKLNK_COMMENT    0   /* Check-in comment */
extern const char zRepositorySchema2[];
extern const char zRepositorySchemaDefaultReports[];
extern const char zRepositorySchema1[];
#define AUX_SCHEMA_MAX  "2015-01-24"
#define AUX_SCHEMA_MIN  "2011-04-25 19:50"
#define CONTENT_SCHEMA  "2"
#define INTERFACE 0
extern const char zConfigSchema[];
