/*
 * Colibri data dump helpers
 *
 * Copyright (c) 2017-2021 Alexei A. Smekalkine <ikle@ikle.ru>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <colibri/file/dump.h>

void capi_dump (FILE *to, const char *prefix, const void *data, size_t size)
{
	const unsigned char *p;
	size_t i;

	fputs (prefix, to);

	for (p = data, i = 0; i < size; ++i)
		printf ("%02x", p[i]);

	putc ('\n', to);
}
