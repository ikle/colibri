/*
 * Colibri file open helpers
 *
 * Copyright (c) 2017-2021 Alexei A. Smekalkine <ikle@ikle.ru>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <colibri/file.h>
#include <colibri/text/string.h>

FILE *file_open_va (const char *mode, const char *fmt, va_list ap)
{
	const char *home;
	char *path, *p;
	FILE *f;

	if ((path = str_printf_va (fmt, ap)) == NULL)
		return NULL;

	if (strncmp (path, "~/", 2) == 0) {
		if ((home = getenv ("HOME")) == NULL ||
		    (p = str_printf ("%s/%s", home, path + 2)) == NULL)
			goto no_home;

		free (path);
		path = p;
	}

	f = fopen (path, mode);
	free (path);
	return f;
no_home:
	free (path);
	return NULL;
}

FILE *file_open (const char *mode, const char *fmt, ...)
{
	va_list ap;
	FILE *f;

	va_start (ap, fmt);
	f = file_open_va (mode, fmt, ap);
	va_end (ap);

	return f;
}
