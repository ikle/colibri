/*
 * Colibri file API
 *
 * Copyright (c) 2017-2021 Alexei A. Smekalkine <ikle@ikle.ru>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#ifndef COLIBRI_FILE_H
#define COLIBRI_FILE_H  1

#include <stdio.h>

FILE *file_open_va (const char *mode, const char *fmt, va_list ap);
FILE *file_open    (const char *mode, const char *fmt, ...);

#endif  /* COLIBRI_FILE_H */
