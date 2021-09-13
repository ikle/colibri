/*
 * Colibri text string helpers
 *
 * Copyright (c) 2017-2021 Alexei A. Smekalkine <ikle@ikle.ru>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#ifndef COLIBRI_TEXT_STRING_H
#define COLIBRI_TEXT_STRING_H  1

#include <stdarg.h>

char *str_printf_va (const char *fmt, va_list ap);
char *str_printf    (const char *fmt, ...);

#endif  /* COLIBRI_TEXT_STRING_H */
