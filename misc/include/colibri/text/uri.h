/*
 * Colibri URI helpers
 *
 * Copyright (c) 2006-2021 Alexei A. Smekalkine <ikle@ikle.ru>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#ifndef COLIBRI_TEXT_URI_H
#define COLIBRI_TEXT_URI_H  1

#include <stddef.h>

size_t uri_escape (char *buf, size_t size, const char *p);

#endif  /* COLIBRI_TEXT_URI_H */
