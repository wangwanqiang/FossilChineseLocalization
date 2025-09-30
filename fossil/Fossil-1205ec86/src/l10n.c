/*
** Implementation of the localization (l10n) module for Fossil.
** This module provides functions for translating UI text strings.
*/

#include "config.h"
#include "l10n.h"
#include "th.h"
#include "hash.h"
#include <string.h>

/* Default language */
#define DEFAULT_LANGUAGE "en"

/* Current language */
static const char *current_language = DEFAULT_LANGUAGE;

/* Translation dictionary type */
typedef struct {
    Hash *domains;  /* Hash of domain names to their translation dictionaries */
} TranslationDict;

/* Global translation dictionary */
static TranslationDict *trans_dict = NULL;

/* Initialize a new translation dictionary */
static TranslationDict *dict_new(void) {
    TranslationDict *dict = fossil_malloc(sizeof(TranslationDict));
    dict->domains = hash_new(0, 0);
    return dict;
}

/* Free a translation dictionary */
static void dict_free(TranslationDict *dict) {
    if (dict) {
        if (dict->domains) {
            /* Free each domain's dictionary */
            HashElem *he;
            for (he = hash_first(dict->domains); he; he = hash_next(he)) {
                Hash *domain_dict = (Hash *)he->data;
                if (domain_dict) {
                    hash_clear(domain_dict, fossil_free);
                    fossil_free(domain_dict);
                }
            }
            hash_clear(dict->domains, NULL);
            fossil_free(dict->domains);
        }
        fossil_free(dict);
    }
}

/* Get or create a domain dictionary */
static Hash *dict_get_domain(TranslationDict *dict, const char *domain) {
    HashElem *he = hash_find(dict->domains, domain);
    if (he) {
        return (Hash *)he->data;
    }
    Hash *domain_dict = hash_new(0, 0);
    hash_insert(dict->domains, domain, domain_dict);
    return domain_dict;
}

/* Add a translation to the dictionary */
static void dict_add_translation(
    TranslationDict *dict, 
    const char *domain, 
    const char *msgid, 
    const char *msgstr
) {
    if (!dict || !domain || !msgid || !msgstr) return;
    
    Hash *domain_dict = dict_get_domain(dict, domain);
    char *trans = fossil_malloc(strlen(msgstr) + 1);
    strcpy(trans, msgstr);
    hash_insert(domain_dict, msgid, trans);
}

/* Look up a translation in the dictionary */
static const char *dict_lookup_translation(
    TranslationDict *dict, 
    const char *domain, 
    const char *msgid
) {
    if (!dict || !domain || !msgid) return NULL;
    
    HashElem *he = hash_find(dict->domains, domain);
    if (!he) return NULL;
    
    Hash *domain_dict = (Hash *)he->data;
    he = hash_find(domain_dict, msgid);
    if (!he) return NULL;
    
    return (const char *)he->data;
}

/* Initialize the localization system */
void l10n_init(void) {
    if (trans_dict) {
        dict_free(trans_dict);
    }
    trans_dict = dict_new();
    
    /* Add default English translations as fallbacks */
    dict_add_translation(trans_dict, "ui", "This is me!", "This is me!");
    dict_add_translation(trans_dict, "ui", "check-in:", "check-in:");
    dict_add_translation(trans_dict, "ui", "user:", "user:");
    dict_add_translation(trans_dict, "ui", "tags:", "tags:");
    dict_add_translation(trans_dict, "ui", "Branch", "Branch");
    dict_add_translation(trans_dict, "ui", "Leaf", "Leaf");
    dict_add_translation(trans_dict, "ui", "Login", "Login");
    dict_add_translation(trans_dict, "ui", "Home", "Home");
    dict_add_translation(trans_dict, "ui", "Timeline", "Timeline");
    dict_add_translation(trans_dict, "ui", "Files", "Files");
    dict_add_translation(trans_dict, "ui", "Wiki", "Wiki");
    dict_add_translation(trans_dict, "ui", "Tickets", "Tickets");
    dict_add_translation(trans_dict, "ui", "Admin", "Admin");
    
    /* Add language name translations */
    dict_add_translation(trans_dict, "ui", "en", "English");
    dict_add_translation(trans_dict, "ui", "zh", "中文");
    dict_add_translation(trans_dict, "ui", "Language", "Language");

    /* Add common UI translations */
    dict_add_translation(trans_dict, "ui", "This page was generated in about", "This page was generated in about");
    dict_add_translation(trans_dict, "ui", "s by", "s by");
    
    /* Chinese translations */
    if (strcmp(current_language, "zh") == 0) {
        dict_add_translation(trans_dict, "ui", "Language", "语言");
        dict_add_translation(trans_dict, "ui", "This is me!", "这是我！");
        dict_add_translation(trans_dict, "ui", "check-in:", "签入：");
        dict_add_translation(trans_dict, "ui", "user:", "用户：");
        dict_add_translation(trans_dict, "ui", "tags:", "标签：");
        dict_add_translation(trans_dict, "ui", "Branch", "分支");
        dict_add_translation(trans_dict, "ui", "Leaf", "叶节点");
        dict_add_translation(trans_dict, "ui", "Login", "登录");
        dict_add_translation(trans_dict, "ui", "Home", "首页");
        dict_add_translation(trans_dict, "ui", "Timeline", "时间线");
        dict_add_translation(trans_dict, "ui", "Files", "文件");
        dict_add_translation(trans_dict, "ui", "Wiki", "维基");
        dict_add_translation(trans_dict, "ui", "Tickets", "工单");
        dict_add_translation(trans_dict, "ui", "Admin", "管理");
        dict_add_translation(trans_dict, "ui", "This page was generated in about", "本页面生成耗时约");
        dict_add_translation(trans_dict, "ui", "s by", "秒，由");
    }
}

/* Set the current language */
void l10n_set_language(const char *lang) {
    if (lang) {
        current_language = lang;
        /* Reinitialize to load translations for the new language */
        l10n_init();
    }
}

/* Get the current language */
const char *l10n_get_language(void) {
    return current_language;
}

/* Translate a string to the current language */
const char *l10n_translate(const char *msgid, const char *domain) {
    if (!msgid) return NULL;
    
    if (!domain) {
        domain = "ui";  /* Default domain is "ui" */
    }
    
    /* If no translations are loaded, return the original string */
    if (!trans_dict) {
        return msgid;
    }
    
    /* Look up the translation */
    const char *msgstr = dict_lookup_translation(trans_dict, domain, msgid);
    
    /* If no translation found, return the original string */
    return (msgstr) ? msgstr : msgid;
}

/* TH1 command: translate <msgid> ?<domain>? */
static int translate_command(
    Th_Interp *interp,
    void *pContext,
    int argc,
    const char **argv,
    int *argl
) {
    const char *msgid, *domain = "ui";
    
    /* Check arguments */
    if (argc < 2 || argc > 3) {
        return Th_WrongNumArgs(interp, "translate msgid ?domain?");
    }
    
    msgid = argv[1];
    if (argc == 3) {
        domain = argv[2];
    }
    
    /* Translate the string */
    const char *msgstr = l10n_translate(msgid, domain);
    
    /* Set the result */
    if (msgstr) {
        return Th_SetResult(interp, msgstr, TH1_LEN(strlen(msgstr)));
    }
    
    return TH_OK;
}

/* TH1 command: lang ?<language>? */
static int lang_command(
    Th_Interp *interp,
    void *pContext,
    int argc,
    const char **argv,
    int *argl
) {
    /* Check arguments */
    if (argc > 2) {
        return Th_WrongNumArgs(interp, "lang ?language?");
    }
    
    /* If called without arguments, return current language */
    if (argc == 1) {
        const char *lang = l10n_get_language();
        return Th_SetResult(interp, lang, TH1_LEN(strlen(lang)));
    }
    
    /* If called with one argument, set current language */
    l10n_set_language(argv[1]);
    return TH_OK;
}

/* Register l10n commands with the TH1 interpreter */
int l10n_register_commands(Th_Interp *interp) {
    if (!interp) return TH_ERROR;
    
    /* Register the "translate" command */
    if (Th_CreateCommand(
            interp, 
            "translate", 
            translate_command, 
            NULL, 
            NULL
        ) != TH_OK) {
        return TH_ERROR;
    }
    
    /* Register the "lang" command */
    if (Th_CreateCommand(
            interp, 
            "lang", 
            lang_command, 
            NULL, 
            NULL
        ) != TH_OK) {
        return TH_ERROR;
    }
    
    return TH_OK;
}