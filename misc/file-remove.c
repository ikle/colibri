/*
 * Colibri file remove helper
 *
 * Copyright (c) 2006-2021 Alexei A. Smekalkine <ikle@ikle.ru>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <stdio.h>

#include <colibri/file/util.h>

int file_remove (const char *path)
{
	return remove (path) == 0;
}
