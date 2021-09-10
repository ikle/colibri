/*
 * Colibri RPC request helpers
 *
 * Copyright (c) 2018-2021 Alexei A. Smekalkine <ikle@ikle.ru>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <errno.h>
#include <stdarg.h>

#include <colibri/conf/rpc-data.h>
#include <colibri/conf/rpc-io.h>
#include <colibri/conf/rpc-req.h>

json_object *conf_req_read (struct json_tokener *o, FILE *from)
{
	return conf_rpc_read (o, from);
}

static const char *json_fetch (json_object *root, const char *key)
{
	json_object *o;

	if (!json_object_object_get_ex (root, key, &o))
		return NULL;

	return json_object_get_string (o);
}

const char *conf_req_key (json_object *o)
{
	return json_fetch (o, "key");
}

const char *conf_req_mode (json_object *o)
{
	return json_fetch (o, "mode");
}

const char *conf_req_cmd (json_object *o)
{
	return json_fetch (o, "cmd");
}

json_object *conf_req_args (json_object *o)
{
	json_object *args;

	if (!json_object_object_get_ex (o, "args", &args))
		return NULL;

	if (!json_object_is_type (args, json_type_array)) {
		errno = EILSEQ;
		return NULL;
	}

	return args;
}

json_object *conf_req (const char *key, const char *mode,
		       const char *cmd, const char *arg, ...)
{
	json_object *o, *args;
	va_list ap;

	if ((o = conf_dict ()) == NULL)
		return NULL;

	if (key  != NULL && !conf_dict_add (o, "key",  key))
		goto no_init;

	if (mode != NULL && !conf_dict_add (o, "mode", mode))
		goto no_init;

	if (cmd  != NULL && !conf_dict_add (o, "cmd",  cmd))
		goto no_init;

	if (arg != NULL) {
		if ((args = conf_text ()) == NULL)
			goto no_args;

		va_start (ap, arg);

		do {
			if (!conf_text_add (args, arg))
				goto no_add;
		}
		while ((arg = va_arg (ap, const char *)) != NULL);

		va_end (ap);

		if (!conf_dict_add_node (o, "args", args))
			goto no_add;
	}

	return o;
no_add:
	json_object_put (args);
no_args:
no_init:
	json_object_put (o);
	return NULL;
}

json_object *conf_auth (const char *key, const char *user, const char *pass)
{
	return conf_req (key, "auth", "ba", "user", user, "pass", pass, NULL);
}

int conf_req_write (json_object *o, FILE *to, int sync)
{
	return conf_rpc_write (o, to, sync);
}
