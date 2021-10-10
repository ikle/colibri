/*
 * Colibri file copy helper
 *
 * Copyright (c) 2006-2021 Alexei A. Smekalkine <ikle@ikle.ru>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <unistd.h>

#include <colibri/file/util.h>

int file_test (const char *path, const char *mode)
{
	int m;

	for (m = 0; *mode != '\0'; ++mode)
		switch (*mode) {
		case 'e': m |= F_OK; break;
		case 'r': m |= R_OK; break;
		case 'w': m |= W_OK; break;
		case 'x': m |= X_OK; break;
		}

	return access (path, m) == 0;
}
