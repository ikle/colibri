/*
 * Colibri JSON save helper
 *
 * Copyright (c) 2016-2022 Alexei A. Smekalkine <ikle@ikle.ru>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <stdio.h>

#include <colibri/data/json-output.h>

int json_save (const struct json *o, const char *to)
{
	FILE *f;
	struct json_output *out;
	int ok;

	if (to == NULL)
		f = stdout;
	else
	if ((f = fopen (to, "w")) == NULL)
		return 0;

	if ((out = json_output_open (NULL, f)) == NULL)
		goto no_out;

	ok = json_write (out, o);
	json_output_close (out);

	if (to != NULL)
		fclose (f);

	return ok;
no_out:
	if (to != NULL)
		fclose (f);

	return 0;
}
