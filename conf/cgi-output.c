/*
 * Colibri CGI output helpers
 *
 * Copyright (c) 2016-2021 Alexei A. Smekalkine <ikle@ikle.ru>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

#include <colibri/net/cgi-output.h>

static int stdio_write (const void *data, int len, void *cookie)
{
	return fwrite (data, 1, len, cookie);
}

struct cgi_output {
	cgi_writer *write;
	void *cookie;
	int head;
};

struct cgi_output *cgi_output_open (cgi_writer *write, void *cookie)
{
	struct cgi_output *o;

	if ((o = malloc (sizeof (*o))) == NULL)
		return NULL;

	o->write  = write == NULL ? stdio_write : write;
	o->cookie = cookie;
	o->head   = 1;

	return o;
}

void cgi_output_close (struct cgi_output *o)
{
	if (o == NULL)
		return;

	free (o);
}

static int write_all (struct cgi_output *o, const void *data, size_t len)
{
	const char *p;
	int n;

	for (p = data; len > 0; p += n, len -= n)
		if ((n = o->write (p, len, o->cookie)) <= 0)
			return 0;

	return 1;
}

static int start_data (struct cgi_output *o)
{
	if (!o->head)
		return 1;

	if (!write_all (o, "\r\n", 2))
		return 0;

	o->head = 0;
	return 1;
}

int cgi_output_write (const void *data, int len, void *cookie)
{
	struct cgi_output *o = cookie;

	if (!start_data (o))
		return 0;

	return o->write (data, len, o->cookie);
}

int cgi_output_type (struct cgi_output *o, const char *type)
{
	char line[128];
	int n;

	o->head = 1;

	n = snprintf (line, sizeof (line), "Content-Type: %s\r\n", type);
	if (n >= sizeof (line)) {
		errno = EOVERFLOW;
		return 0;
	}

	return write_all (o, line, n);
}

int cgi_output_len (struct cgi_output *o, size_t len)
{
	char line[128];
	int n;

	o->head = 1;

	n = snprintf (line, sizeof (line), "Content-Length: %zu\r\n", len);
	if (n >= sizeof (line)) {
		errno = EOVERFLOW;
		return 0;
	}

	return write_all (o, line, n);
}

int cgi_output_blob (struct cgi_output *o, const void *data, size_t len)
{
	if (!start_data (o))
		return 0;

	return write_all (o, data, len);
}
