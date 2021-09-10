/*
 * Colibri compiler helpers
 *
 * Copyright (c) 2011-2021 Alexei A. Smekalkine
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#ifndef COLIBRI_CONF_COMPILER_H
#define COLIBRI_CONF_COMPILER_H  1

#ifdef __GNUC__
#define sentinel  __attribute__ ((sentinel))
#else
#define sentinel
#endif

#endif  /* COLIBRI_CONF_COMPILER_H */
