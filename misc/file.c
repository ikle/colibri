/*
 * file: generic helpers
 *
 * Copyright (c) 2006-2017 Alexei A. Smekalkine <ikle@ikle.ru>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "file.h"

int file_remove (const char *path)
{
	return remove (path) == 0;
}

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

	while (!feof (from)) {
		count = fread (buf, 1, sizeof (buf), from);

		if (fwrite (buf, count, 1, to) != 1)
			goto no_write;
	}

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

int file_move (const char *src, const char *dst)
{
	if (rename (src, dst) == 0)
		return 1;

#ifdef EXDEV
	if (errno != EXDEV || !file_copy (src, dst))
		return 0;

	if (file_remove (src))
		return 1;

	(void) file_remove (dst);
#endif
	return 0; 
}

/* returns newly allocated string */
char *file_basename (const char *path)
{
	const char *head, *tail = path + strlen (path);
	size_t len;
	char *name;

	/* omit trailing slashes */
	for (; tail > path && tail[-1] == '/'; --tail) {}

	/* find start of file name */
	for (head = tail; head > path && head[-1] != '/'; --head) {}

	len = tail - head;

	if (len == 0)
		return path[0] == '/' ? strdup ("/") : strdup (".");

	if ((name = malloc (len + 1)) == NULL)
		return NULL;

	memcpy (name, head, len);
	name[len] = '\0';
	return name;
}
