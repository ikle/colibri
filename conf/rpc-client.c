/*
 * Colibri RPC client helpers
 *
 * Copyright (c) 2018-2021 Alexei A. Smekalkine <ikle@ikle.ru>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <colibri/rpc/client.h>

struct json *rpc_req (const char *key, const char *mode, const char *cmd,
		      int argc, char *argv[])
{
	struct json *o, *args;
	int i, ok = 1;

	if ((o = json_dict ()) == NULL)
		return NULL;

	if (key != NULL)
		ok &= json_dict_set_string (o, "key", key);

	ok &= json_dict_set_string (o, "mode", mode);
	ok &= json_dict_set_string (o, "cmd",  cmd);

	if (argc > 0) {
		if ((args = json_dict_set_list (o, "args", argc)) == NULL)
			goto error;

		for (i = 0; i < argc; ++i)
			ok &= json_list_set_string (args, i, argv[i]);
	}

	if (ok)
		return o;
error:
	json_put (o);
	return NULL;
}

struct json *rpc_auth (const char *key, const char *user, const char *pass)
{
	struct json *o, *auth;
	int ok = 1;

	if ((o = rpc_req (key, "auth", "ba", 0, NULL)) == NULL)
		return NULL;

	if ((auth = json_dict_set_dict (o, "args")) == NULL)
		goto error;

	ok &= json_dict_set_string (auth, "user",     user);
	ok &= json_dict_set_string (auth, "password", pass);

	if (ok)
		return o;
error:
	json_put (o);
	return NULL;
}

int rpc_ans_code (struct json *o)
{
	struct json *e;

	if (json_type (o) != JSON_DICT)
		return 0;

	if ((e = json_dict_get_list (o, "error")) == NULL)
		return 0;

	return json_list_get_int (e, 0);
}

const char *rpc_ans_reason (struct json *o)
{
	struct json *e;

	if (json_type (o) != JSON_DICT)
		return NULL;

	if ((e = json_dict_get_list (o, "error")) == NULL)
		return NULL;

	return json_list_get_string (e, 1);
}

struct json *rpc_ans_data (struct json *o)
{
	if (json_type (o) != JSON_DICT)
		return NULL;

	return json_dict_get (o, "data");
}

int rpc_ans_last (struct json *o)
{
	struct json *last;

	if (json_type (o) != JSON_DICT)
		return 1;

	if ((last = json_dict_get (o, "last")) == NULL)
		return 1;

	return json_get_bool (last);
}
