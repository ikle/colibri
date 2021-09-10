/*
 * Colibri RPC answer helpers
 *
 * Copyright (c) 2018-2021 Alexei A. Smekalkine <ikle@ikle.ru>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <errno.h>

#include <colibri/conf/rpc-ans.h>
#include <colibri/conf/rpc-data.h>
#include <colibri/conf/rpc-io.h>

json_object *conf_ans_read (struct json_tokener *o, FILE *from)
{
	return conf_rpc_read (o, from);
}

static json_object *json_fetch (json_object *root, const char *key, int i)
{
	json_object *o;

	if (!json_object_object_get_ex (root, key, &o))
		return NULL;

	if (!json_object_is_type (o, json_type_array))
		return NULL;

	return json_object_array_get_idx (o, i);
}

int conf_ans_code (json_object *o)
{
	json_object *p = json_fetch (o, "error", 0);

	return json_object_get_int (p);
}

const char *conf_ans_reason (json_object *o)
{
	json_object *p;

	if ((p = json_fetch (o, "error", 1)) == NULL)
		return NULL;

	return json_object_get_string (p);
}

json_object *conf_ans_data (json_object *o)
{
	json_object *p;

	if (!json_object_object_get_ex (o, "data", &p))
		return NULL;

	return p;
}

int conf_ans_last (json_object *o)
{
	json_object *p;

	if (!json_object_object_get_ex (o, "last", &p))
		return 1;

	return json_object_get_boolean (p);
}

json_object *conf_ans	(int code, const char *reason,
			 const char *data, int last);

static int
conf_ans_add (json_object *o, int type, const char *format, json_object *data)
{
	if (!json_object_is_type (data, type)) {
		errno = EINVAL;
		return 0;
	}

	if (!conf_dict_add (o, "format", format))
		return 0;

	return conf_dict_add_node (o, "data", data);
}

int conf_ans_add_text (json_object *o, json_object *data)
{
	return conf_ans_add (o, json_type_array, "text", data);
}

int conf_ans_add_dict (json_object *o, json_object *data)
{
	return conf_ans_add (o, json_type_object, "dict", data);
}

int conf_ans_add_tree (json_object *o, json_object *data)
{
	return conf_ans_add (o, json_type_object, "tree", data);
}

int conf_ans_add_table (json_object *o, json_object *data)
{
	return conf_ans_add (o, json_type_array, "table", data);
}

int conf_ans_write (json_object *o, FILE *to, int sync)
{
	return conf_rpc_write (o, to, sync);
}
