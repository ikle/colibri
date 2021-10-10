/*
 * Colibi file move helper
 *
 * Copyright (c) 2006-2021 Alexei A. Smekalkine <ikle@ikle.ru>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <errno.h>
#include <stdio.h>

#include "file.h"

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
