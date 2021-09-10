/*
 * Colibri configuration kind helpers
 *
 * Copyright (c) 2011-2021 Alexei A. Smekalkine
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#ifndef COLIBRI_CONF_KIND_H
#define COLIBRI_CONF_KIND_H  1

/*
 * The cm_kind_validate function validates value against specified kind.
 */
int cm_kind_validate (const char *kind, const char *value);

/*
 * The cm_kind_help function returns name and description of the subkind
 * specified by an index.
 *
 * If subkind with specified index exists and is known to system then
 * function returns non-zero, zero otherwise.
 */
int cm_kind_help (const char *kind, size_t index,
		  const char **name, const char **help);

#endif  /* COLIBRI_CONF_KIND_H */
