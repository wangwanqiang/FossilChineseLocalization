/* This file was automatically generated.  Do not edit! */
#undef INTERFACE
int fossil_isdigit(char c);
typedef struct Blob Blob;
void markdown_dehtmlize_blob(Blob *p);
typedef struct mkd_renderer mkd_renderer;
void markdown(struct Blob *ob,const struct Blob *ib,const struct mkd_renderer *rndrer);
void blob_set(Blob *pBlob,const char *zStr);
const char *cgi_parameter(const char *zName,const char *zDefault);
#define PD(x,y)       cgi_parameter((x),(y))
const char *escape_quotes(const char *zIn);
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
int wiki_resolve_hyperlink(Blob *pOut,int mFlags,const char *zTarget,char *zClose,int nClose,const char *zOrig,const char *zTitle);
#define WIKI_MARKDOWNLINKS 0x0080  /* Resolve hyperlinks as in markdown */
#define WIKI_NOBADLINKS    0x0010  /* Ignore broken hyperlinks */
void blob_reset(Blob *pBlob);
char *blob_str(Blob *p);
int pikchr_process(const char *zIn,int pikFlags,Blob *pOut);
const char *skin_detail(const char *zName);
int skin_detail_boolean(const char *zName);
#define PIKCHR_PROCESS_DIV_SOURCE_INLINE 0x4000
#define PIKCHR_PROCESS_DIV_SOURCE        0x2000
#define PIKCHR_PROCESS_DIV_TOGGLE        0x1000
#define PIKCHR_PROCESS_DIV_FLOAT_RIGHT   0x0800
#define PIKCHR_PROCESS_DIV_FLOAT_LEFT    0x0400
#define PIKCHR_PROCESS_DIV_INDENT        0x0100
#define PIKCHR_PROCESS_DIV_CENTER        0x0200
struct Blob {
  unsigned int nUsed;            /* Number of bytes used in aData[] */
  unsigned int nAlloc;           /* Number of bytes allocated for aData[] */
  unsigned int iCursor;          /* Next character of input to parse */
  unsigned int blobFlags;        /* One or more BLOBFLAG_* bits */
  char *aData;                   /* Where the information is stored */
  void (*xRealloc)(Blob*, unsigned int); /* Function to reallocate the buffer */
};
extern const Blob empty_blob;
#define PIKCHR_PROCESS_ERR_PRE           0x0020
#define PIKCHR_PROCESS_SRC               0x0040
#define PIKCHR_PROCESS_DIV               0x0080
#define PIKCHR_PROCESS_NONCE             0x0010
void pikchr_to_html(Blob *ob,const char *zSrc,int nSrc,const char *zArg,int nArg);
void pikchr_to_html_add_flags(int f);
int blob_trim(Blob *p);
int fossil_tolower(char c);
int fossil_isalnum(char c);
#define MKD_CELL_ALIGN_CENTER   3  /* LEFT | RIGHT */
#define MKD_CELL_ALIGN_RIGHT    2
#define MKD_CELL_ALIGN_LEFT     1
#define MKD_CELL_ALIGN_MASK     3
#define MKD_CELL_HEAD           4
#define MKD_LIST_ORDERED  1
void blob_appendf(Blob *pBlob,const char *zFormat,...);
int html_tag_length(const char *z);
int fossil_isspace(char c);
#define blob_buffer(X)  ((X)->aData)
void blob_append(Blob *pBlob,const char *aData,int nData);
#define blob_append_literal(blob, literal) \
  blob_append((blob), "" literal, (sizeof literal)-1)
#define blob_size(X)  ((X)->nUsed)
#define blob_appendb(dest, src) \
  blob_append((dest), blob_buffer(src), blob_size(src))
void blob_append_char(Blob *pBlob,char c);
void markdown_to_html(struct Blob *input_markdown,struct Blob *output_title,struct Blob *output_body);
void markdown_to_html(struct Blob *input_markdown,struct Blob *output_title,struct Blob *output_body);
#define INTERFACE 0
