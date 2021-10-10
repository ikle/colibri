/*
 * Colibri file basename helper
 *
 * Copyright (c) 2006-2021 Alexei A. Smekalkine <ikle@ikle.ru>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <stdlib.h>
#include <string.h>

#include <colibri/file/util.h>

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
