/* TH1兼容性头文件 - 解决Windows上的TH1 API兼容性问题 */
#ifndef TH_COMPAT_H
#define TH_COMPAT_H

/* 定义一个特殊的宏，用于在构建时关闭特定的警告 */
#ifdef _MSC_VER
#pragma warning(disable: 4047) /* 间接级别不同 */
#pragma warning(disable: 4024) /* 形参和实参类型不同 */
#pragma warning(disable: 4312) /* 类型强制转换 */
#pragma warning(disable: 4100) /* 未引用的形参 */
#endif

/* 定义TH1类型转换宏 - 这些宏将用于处理类型转换问题 */
#define TH_CONST_CHAR_PTR_CAST(X) ((const char*)(X))
#define TH_CHAR_PTR_CAST(X)       ((char*)(X))

/* 定义字符串比较函数的包装宏，确保参数数量正确 */
#ifndef fossil_strcmp
#define fossil_strcmp(A,B) strcmp(TH_CONST_CHAR_PTR_CAST(A), TH_CONST_CHAR_PTR_CAST(B))
#endif

/* 定义TH1函数的包装宏，直接应用类型转换 */
#define TH_COMPAT_TH_LIST_APPEND(interp, pzList, pnList, zArg, nArg) \
    Th_ListAppend(interp, pzList, pnList, TH_CONST_CHAR_PTR_CAST(zArg), nArg)

#define TH_COMPAT_TH_FETCH(zName, pSize) \
    Th_Fetch(TH_CONST_CHAR_PTR_CAST(zName), pSize)

#define TH_COMPAT_TH_GET_VAR(interp, zName, nName) \
    Th_GetVar(interp, TH_CONST_CHAR_PTR_CAST(zName), nName)

#define TH_COMPAT_TH_SET_VAR(interp, zName, nName, zValue, nValue) \
    Th_SetVar(interp, TH_CONST_CHAR_PTR_CAST(zName), nName, TH_CONST_CHAR_PTR_CAST(zValue), nValue)

#define TH_COMPAT_TH_SET_RESULT(interp, zStr, nStr) \
    Th_SetResult(interp, TH_CONST_CHAR_PTR_CAST(zStr), nStr)

#define TH_COMPAT_TH_ERROR_MESSAGE(interp, zMsg, zArg, nArg) \
    Th_ErrorMessage(interp, TH_CONST_CHAR_PTR_CAST(zMsg), TH_CONST_CHAR_PTR_CAST(zArg), nArg)

#define TH_COMPAT_TH_WRONG_NUM_ARGS(interp, zMsg) \
    Th_WrongNumArgs(interp, TH_CONST_CHAR_PTR_CAST(zMsg))

#define TH_COMPAT_TH_GET_RESULT(interp) \
    TH_CHAR_PTR_CAST(Th_GetResult(interp))

/* 注意：我们不再重定义原始函数名，以避免与函数声明和定义冲突 */
/* 请在需要类型转换的地方显式使用TH_COMPAT_TH_*宏 */

/* 补充th_main.c中使用的常量定义 */
#ifndef TH_INIT_NONE
#define TH_INIT_NONE        0x00000000  /* No flags. */
#endif
#ifndef TH_INIT_NEED_CONFIG
#define TH_INIT_NEED_CONFIG 0x00000001  /* Open configuration first? */
#endif
#ifndef TH_INIT_FORCE_TCL
#define TH_INIT_FORCE_TCL   0x00000002  /* Force Tcl to be enabled? */
#endif
#ifndef TH_INIT_FORCE_RESET
#define TH_INIT_FORCE_RESET 0x00000004  /* Force TH1 commands re-added? */
#endif
#ifndef TH_INIT_FORCE_SETUP
#define TH_INIT_FORCE_SETUP 0x00000008  /* Force eval of setup script? */
#endif
#ifndef TH_INIT_NO_REPO
#define TH_INIT_NO_REPO     0x00000010  /* Skip opening repository. */
#endif
#ifndef TH_INIT_MASK
#define TH_INIT_MASK        0x0000001F  /* All possible init flags. */
#endif
#ifndef TH_INIT_DEFAULT
#define TH_INIT_DEFAULT     (TH_INIT_NONE)  /* Default flags. */
#endif
#ifndef TH_INIT_HOOK
#define TH_INIT_HOOK        (TH_INIT_NEED_CONFIG | TH_INIT_FORCE_SETUP)
#endif
#ifndef TH_INIT_FORBID_MASK
#define TH_INIT_FORBID_MASK (TH_INIT_FORCE_TCL) /* Illegal from a script. */
#endif
#ifndef TH_R2B_NO_VARS
#define TH_R2B_NO_VARS      0x01000  /* Disables eval of $vars and $<vars> */
#endif
#ifndef TH_R2B_MASK
#define TH_R2B_MASK         0x0f000  /* Mask for the above */
#endif
#ifndef TH_STATE_CONFIG
#define TH_STATE_CONFIG     0x00000200 /* We opened the config. */
#endif
#ifndef TH_STATE_REPOSITORY
#define TH_STATE_REPOSITORY 0x00000400 /* We opened the repository. */
#endif
#ifndef TH_STATE_MASK
#define TH_STATE_MASK       0x00000600 /* All possible state flags. */
#endif
#ifndef OPEN_OK_NOT_FOUND
#define OPEN_OK_NOT_FOUND   0x001  /* Do not error out if not found */
#endif
#ifndef OPEN_ANY_SCHEMA
#define OPEN_ANY_SCHEMA     0x002  /* Do not error if schema is wrong */
#endif
#ifndef OPEN_SUBSTITUTE
#define OPEN_SUBSTITUTE     0x004  /* Fake in-memory repo if not found */
#endif
#ifndef LOGIN_ANON
#define LOGIN_ANON          0x02   /* Use g.anon instead of g.perm */
#endif
#ifndef SRCH_WIKI
#define SRCH_WIKI           0x0008 /* Search over wiki */
#endif
#ifndef SRCH_TKT
#define SRCH_TKT            0x0004 /* Search over tickets */
#endif
#ifndef SRCH_DOC
#define SRCH_DOC            0x0002 /* Search over embedded documents */
#endif
#ifndef SRCH_CKIN
#define SRCH_CKIN           0x0001 /* Search over check-in comments */
#endif
#ifndef SRCH_ALL
#define SRCH_ALL            0x007f /* Search over everything */
#endif
#ifndef WIKI_LINKSONLY
#define WIKI_LINKSONLY      0x0020 /* No markup. Only decorate links */
#endif
#ifndef WIKI_NOBADLINKS
#define WIKI_NOBADLINKS     0x0010 /* Ignore broken hyperlinks */
#endif
#ifndef WIKI_INLINE
#define WIKI_INLINE         0x0002 /* Do not surround with <p>..</p> */
#endif
#ifndef CFTYPE_MANIFEST
#define CFTYPE_MANIFEST     1
#endif
#ifndef WIKIASSOC_FULL_TITLE
#define WIKIASSOC_FULL_TITLE 1
#endif
#ifndef MANIFESTFILE
#define MANIFESTFILE        1
#endif

#ifdef FOSSIL_ENABLE_TH1_HOOKS
#ifndef NO_COMMAND_HOOK_ERROR
#define NO_COMMAND_HOOK_ERROR "no such command:  command_hook"
#endif
#ifndef NO_WEBPAGE_HOOK_ERROR
#define NO_WEBPAGE_HOOK_ERROR "no such command:  webpage_hook"
#endif
#endif

#endif /* TH_COMPAT_H */