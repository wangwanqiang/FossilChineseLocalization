/*
** Header file for the localization (l10n) module of Fossil.
** This module provides functions for translating UI text strings.
*/

#ifndef FOSSIL_L10N_H
#define FOSSIL_L10N_H

#include "th.h"

/* Initialize the localization system */
void l10n_init(void);

/* Register l10n commands with the TH1 interpreter */
int l10n_register_commands(Th_Interp *interp);

/* Set the current language */
void l10n_set_language(const char *lang);

/* Get the current language */
const char *l10n_get_language(void);

/* Translate a string to the current language */
const char *l10n_translate(const char *msgid, const char *domain);

#endif /* FOSSIL_L10N_H */