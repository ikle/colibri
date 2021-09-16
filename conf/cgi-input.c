/*
 * Colibri CGI input helpers
 *
 * Copyright (c) 2016-2021 Alexei A. Smekalkine <ikle@ikle.ru>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <stdio.h>
#include <stdlib.h>

#include <colibri/net/cgi-input.h>

static int stdio_read (void *data, int len, void *cookie)
{
	return fread (data, 1, len, cookie);
}

struct cgi_input {
	cgi_reader *read;
	void *cookie;
	const char *type;
	size_t len;
};

struct cgi_input *cgi_input_open (cgi_reader *read, void *cookie)
{
	struct cgi_input *o;
	const char *type = getenv ("CONTENT_TYPE");
	const char *len  = getenv ("CONTENT_LENGTH");

	if ((o = malloc (sizeof (*o))) == NULL)
		return NULL;

	o->read   = read == NULL ? stdio_read : read;
	o->cookie = cookie;
	o->type   = type;
	o->len    = len != NULL ? atoll (len) : SIZE_MAX;

	return o;
}

void cgi_input_close (struct cgi_input *o)
{
	if (o == NULL)
		return;

	free (o);
}

int cgi_input_read (void *data, int len, void *cookie)
{
	struct cgi_input *o = cookie;
	int n;

	if (len > o->len)
		return 0;

	if ((n = o->read (data, len, o->cookie)) <= 0)
		return n;

	if (o->len != SIZE_MAX)
		o->len -= n;

	return n;
}

const char *cgi_input_type (struct cgi_input *o)
{
	return o->type;
}

size_t cgi_input_len (struct cgi_input *o)
{
	return o->len;
}

int cgi_input_blob (struct cgi_input *o, void *data, size_t len)
{
	char *p;
	int n;

	for (p = data; len > 0; p += n, len -=n)
		if ((n = cgi_input_read (p, len, o)) <= 0)
			return 0;

	return 1;
}
