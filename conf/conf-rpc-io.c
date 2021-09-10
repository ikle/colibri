/*
 * Colibri RPC I/O helpers
 *
 * Copyright (c) 2018-2021 Alexei A. Smekalkine <ikle@ikle.ru>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <errno.h>

#include <colibri/conf/rpc-io.h>

json_object *conf_rpc_read (struct json_tokener *o, FILE *from)
{
	char buf[BUFSIZ];
	size_t n;
	enum json_tokener_error je;
	json_object *obj;

	do {
		if ((n = fread (buf, 1, sizeof (buf), from)) == 0) {
			errno = ENODATA;
			return NULL;
		}

		obj = json_tokener_parse_ex (o, buf, n);
	}
	while ((je = json_tokener_get_error (o)) == json_tokener_continue);

	if (je != json_tokener_success) {
		errno = EILSEQ;
		return NULL;
	}

	return obj;
}

int conf_rpc_write (json_object *o, FILE *to, int sync)
{
	const char *s;

	s = json_object_to_json_string_ext (o, JSON_C_TO_STRING_PLAIN);
	if (s == NULL)
		return 0;

	if (fprintf (to, "%s", s) < 0)
		return 0;

	if (sync && fflush (to) != 0)
		return 0;

	return 1;
}
