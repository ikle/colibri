/*
 * Colibri JSON output helpers
 *
 * Copyright (c) 2016-2021 Alexei A. Smekalkine <ikle@ikle.ru>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <colibri/data/json-output.h>

#define json_bool  json_bool_impl
#define json_type  json_type_impl

#include <json-c/json.h>

#undef json_bool
#undef json_type

static int stdio_write (const void *buffer, int size, void *cookie)
{
	return fwrite (buffer, 1, size, cookie);
}

struct json_output {
	json_writer *write;
	void *cookie;
};

struct json_output *json_output_open (json_writer *write, void *cookie)
{
	struct json_output *o;

	if ((o = malloc (sizeof (*o))) == NULL)
		return NULL;

	o->write  = write == NULL ? stdio_write : write;
	o->cookie = cookie;

	return o;
}

void json_output_close (struct json_output *o)
{
	if (o == NULL)
		return;

	free (o);
}

int json_write (struct json_output *o, const struct json *json)
{
	const char *s;
	long long len;
	int n;

	s = json_object_to_json_string_ext ((void *) json, 0);
	if (s == NULL)
		return 0;

	for (len = strlen (s); len > 0; s += n, len -= n)
		if ((n = o->write (s, len, o->cookie)) <= 0)
			return 0;

	return 1;
}
