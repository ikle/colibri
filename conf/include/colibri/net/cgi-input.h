/*
 * Colibri CGI input helpers
 *
 * Copyright (c) 2016-2021 Alexei A. Smekalkine <ikle@ikle.ru>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#ifndef COLIBRI_NET_CGI_INPUT_H
#define COLIBRI_NET_CGI_INPUT_H  1

#include <stddef.h>
#include <stdint.h>

typedef int cgi_reader (void *data, int len, void *cookie);

struct cgi_input *cgi_input_open (cgi_reader *read, void *cookie);
void cgi_input_close (struct cgi_input *o);

int cgi_input_read (void *data, int len, void *cookie);

const char *cgi_input_method (struct cgi_input *o);
const char *cgi_input_type   (struct cgi_input *o);
size_t      cgi_input_len    (struct cgi_input *o);

int cgi_input_blob (struct cgi_input *o, void *data, size_t len);

#endif  /* COLIBRI_NET_CGI_INPUT_H */
