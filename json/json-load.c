/*
 * Colibri JSON loader helper
 *
 * Copyright (c) 2016-2022 Alexei A. Smekalkine <ikle@ikle.ru>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <stdio.h>

#include <colibri/data/json-input.h>

struct json *json_load (const char *from)
{
	FILE *f;
	struct json_input *in;
	struct json *o;

	if (from == NULL)
		f = stdin;
	else
	if ((f = fopen (from, "r")) == NULL)
		return NULL;

	if ((in = json_input_open (NULL, f)) == NULL)
		goto no_in;

	o = json_read (in);
	json_input_close (in);

	if (from != NULL)
		fclose (f);

	return o;
no_in:
	if (from != NULL)
		fclose (f);

	return NULL;
}
