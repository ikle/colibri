/*
 * file-tree: file tree helpers
 *
 * Copyright (c) 2006-2019 Alexei A. Smekalkine <ikle@ikle.ru>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#ifndef FILE_TREE_H
#define FILE_TREE_H  1

typedef int (*file_tree_visitor_fn) (const char *path, void *cookie);

int file_tree_walk (const char *root, int flags,
		    file_tree_visitor_fn open, file_tree_visitor_fn close,
		    void *cookie);

#define FILE_TREE_WALK_HIDDEN	1

#endif  /* FILE_TREE_H */
