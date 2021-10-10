/*
 * Colibri file copy helper
 *
 * Copyright (c) 2006-2021 Alexei A. Smekalkine <ikle@ikle.ru>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <stdio.h>

#include "file.h"

int file_copy (const char *src, const char *dst)
{
	FILE *from, *to;
	size_t count;
	char buf[BUFSIZ];
	int status;

	if ((from = fopen (src, "rb")) == NULL)
		goto no_from;

	if ((to = fopen (dst, "wb")) == NULL)
		goto no_to;

	while ((count = fread (buf, 1, sizeof (buf), from)) > 0)
		if (fwrite (buf, count, 1, to) != 1)
			goto no_write;

	status = !ferror (from);

	fclose (to);
	fclose (from);

	return status;;
no_write:
	fclose (to);
no_to:
	fclose (from);
no_from:
	return 0;
}
