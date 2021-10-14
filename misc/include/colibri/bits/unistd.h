/*
 * Colibri UNIX standard helpers
 *
 * Copyright (c) 2019-2021 Alexei A. Smekalkine <ikle@ikle.ru>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#ifndef COLIBRI_BITS_UNISTD_H
#define COLIBRI_BITS_UNISTD_H  1

/*
 * Mac OS X and iOS are unixes really
 */
#if !defined (__unix__) && defined (__APPLE__) && defined (__MACH__)
#define __unix__
#endif

/*
 * Get POSIX macroses
 */
#if defined (unix) || defined (__unix__) || defined (__unix)
#include <unistd.h>
#endif

#endif  /* COLIBRI_BITS_UNISTD_H */
