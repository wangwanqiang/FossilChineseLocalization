/* This file was automatically generated.  Do not edit! */
#undef INTERFACE
int is_false(const char *zVal);
#include <stdlib.h>
#include <dirent.h>
char *fossil_getenv(const char *zName);
int fossil_isatty(int fd);
#if defined(_WIN32)
int win32_terminal_is_vt100(int fd);
#endif
int terminal_is_vt100(void);
void fossil_print(const char *zFormat,...);
void test_terminal_size_cmd(void);
unsigned int terminal_get_height(unsigned int nDefault);
unsigned int terminal_get_width(unsigned int nDefault);
typedef struct TerminalSize TerminalSize;
int terminal_get_size(TerminalSize *t);
struct TerminalSize {
  unsigned int nColumns;         /* Number of characters on a single line */
  unsigned int nLines;           /* Number of lines */
};
#define INTERFACE 0
