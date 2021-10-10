/*
 * Colibri file helpers
 *
 * Copyright (c) 2006-2021 Alexei A. Smekalkine <ikle@ikle.ru>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#ifndef COLIBRI_FILE_UTILS_H
#define COLIBRI_FILE_UTILS_H  1

int file_remove (const char *path);
int file_copy (const char *src, const char *dst);
int file_move (const char *src, const char *dst);

/* returns newly allocated string */
char *file_basename (const char *path);

#endif  /* COLIBRI_FILE_UTILS_H */
