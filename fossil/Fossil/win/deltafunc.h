/* This file was automatically generated.  Do not edit! */
#undef INTERFACE
int deltafunc_init(sqlite3 *db);
int delta_apply(const char *zSrc,int lenSrc,const char *zDelta,int lenDelta,char *zOut);
int delta_output_size(const char *zDelta,int lenDelta);
int delta_create(const char *zSrc,unsigned int lenSrc,const char *zOut,unsigned int lenOut,char *zDelta);
