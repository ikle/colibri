/*
 * Colibri data dump helpers
 *
 * Copyright (c) 2017-2021 Alexei A. Smekalkine <ikle@ikle.ru>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#ifndef COLIBRI_FILE_DUMP_H
#define COLIBRI_FILE_DUMP_H  1

#include <stdio.h>

void file_dump (FILE *to, const char *prefix, const void *data, size_t size);

#endif  /* COLIBRI_FILE_DUMP_H */
