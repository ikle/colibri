/*
 * Colibri CGI output helpers
 *
 * Copyright (c) 2016-2021 Alexei A. Smekalkine <ikle@ikle.ru>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#ifndef COLIBRI_NET_CGI_OUTPUT_H
#define COLIBRI_NET_CGI_OUTPUT_H  1

#include <stddef.h>

typedef int cgi_writer (const void *data, int len, void *cookie);

struct cgi_output *cgi_output_open (cgi_writer *write, void *cookie);
void cgi_output_close (struct cgi_output *o);

int cgi_output_write (const void *data, int len, void *cookie);

int cgi_output_type (struct cgi_output *o, const char *type);
int cgi_output_len  (struct cgi_output *o, size_t len);

int cgi_output_blob  (struct cgi_output *o, const void *data, size_t len);

#endif  /* COLIBRI_NET_CGI_OUTPUT_H */
