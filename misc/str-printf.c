/*
 * Colibri text string helpers
 *
 * Copyright (c) 2017-2021 Alexei A. Smekalkine <ikle@ikle.ru>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <stdio.h>
#include <stdlib.h>

#include <colibri/text/string.h>

char *str_printf_va (const char *fmt, va_list ap)
{
	va_list args;
	char *s;
	int len;

	va_copy (args, ap);
	len = vsnprintf (NULL, 0, fmt, args);
	va_end (args);

	if (len < 0)
		return NULL;

	if ((s = malloc (len + 1)) == NULL)
		return NULL;

	vsnprintf (s, len + 1, fmt, ap);
	return s;
}

char *str_printf (const char *fmt, ...)
{
	va_list ap;
	char *s;

	va_start (ap, fmt);
	s = str_printf_va (fmt, ap);
	va_end (ap);

	return s;
}
