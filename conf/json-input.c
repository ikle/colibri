/*
 * Colibri JSON input helpers
 *
 * Copyright (c) 2016-2021 Alexei A. Smekalkine <ikle@ikle.ru>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

#include <colibri/data/json-input.h>

#define json_bool  json_bool_impl
#define json_type  json_type_impl

#include <json-c/json.h>

#undef json_bool
#undef json_type

static int stdio_read (void *buffer, int size, void *cookie)
{
	return fread (buffer, 1, size, cookie);
}

struct json_input {
	struct json_tokener *state;
	json_reader *read;
	void *cookie;
};

struct json_input *json_input_open (json_reader *read, void *cookie)
{
	struct json_input *o;

	if ((o = malloc (sizeof (*o))) == NULL)
		return NULL;

	if ((o->state = json_tokener_new ()) == NULL)
		goto no_state;

	o->read   = read == NULL ? stdio_read : read;
	o->cookie = cookie;

	return o;
no_state:
	free (o);
	return NULL;
}

void json_input_close (struct json_input *o)
{
	if (o == NULL)
		return;

	json_tokener_free (o->state);
	free (o);
}

struct json *json_read (struct json_input *o)
{
	char buf[256];
	int n;
	enum json_tokener_error e;
	json_object *node;

	do {
		if ((n = o->read (buf, sizeof (buf), o->cookie)) <= 0)
			return NULL;

		node = json_tokener_parse_ex (o->state, buf, n);
	}
	while ((e = json_tokener_get_error (o->state)) == json_tokener_continue);

	if (e != json_tokener_success) {
		errno = EILSEQ;
		return NULL;
	}

	return (void *) node;
}
