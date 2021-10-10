/*
 * file-tree: file tree helpers
 *
 * Copyright (c) 2006-2019 Alexei A. Smekalkine <ikle@ikle.ru>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/types.h>
#include <dirent.h>

#include "file-tree.h"

int file_tree_walk (const char *root, int flags,
		    file_tree_visitor_fn open, file_tree_visitor_fn close,
		    void *cookie)
{
	DIR *d;
	struct dirent *de;
	int len;
	char *path;

	if (!open (root, cookie))
		return 0;

	if ((d = opendir (root)) != NULL) {
		while ((de = readdir (d)) != NULL) {
			if ((flags & FILE_TREE_WALK_HIDDEN) == 0 &&
			    de->d_name[0] == '.')
				continue;

			if (strcmp (de->d_name, ".")  == 0 ||
			    strcmp (de->d_name, "..") == 0)
				continue;

			len = snprintf (NULL, 0, "%s/%s", root, de->d_name);

			if ((path = malloc (len + 1)) == NULL)
				continue;

			snprintf (path, len + 1, "%s/%s", root, de->d_name);

			if (!file_tree_walk (path, flags, open, close, cookie))
				goto stop;

			free (path);
		}

		closedir (d);
	}

	if (!close (root, cookie))
		return 0;

	return 1;
stop:
	free (path);
	closedir (d);
	return 0;
}
