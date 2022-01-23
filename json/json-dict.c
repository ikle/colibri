/*
 * Colibri JSON dictionary API
 *
 * Copyright (c) 2018-2021 Alexei A. Smekalkine <ikle@ikle.ru>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <colibri/data/json-dict.h>

#define json_bool  json_bool_impl
#define json_type  json_type_impl

#include <json-c/json.h>

#undef json_bool
#undef json_type

int json_dict_exists (struct json *o, const char *key)
{
	return json_object_object_get_ex ((void *) o, key, NULL);
}

struct json *json_dict_get (struct json *o, const char *key)
{
	struct json_object *node = NULL;

	json_object_object_get_ex ((void *) o, key, &node);

	return (void *) node;
}

int json_dict_set (struct json *o, const char *key, struct json *value)
{
	json_object_object_add ((void *) o, key, (void *) value);
	return 1;
}

void json_dict_remove (struct json *o, const char *key)
{
	json_object_object_del ((void *) o, key);
}
