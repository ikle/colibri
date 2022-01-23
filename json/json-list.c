/*
 * Colibri JSON list API
 *
 * Copyright (c) 2018-2021 Alexei A. Smekalkine <ikle@ikle.ru>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <colibri/data/json-list.h>

#define json_bool  json_bool_impl
#define json_type  json_type_impl

#include <json-c/json.h>

#undef json_bool
#undef json_type

int json_list_size (struct json *o)
{
	return json_object_array_length ((void *) o);
}

struct json *json_list_get (struct json *o, int i)
{
	return (void *) json_object_array_get_idx ((void *) o, i);
}

int json_list_set (struct json *o, int i, struct json *value)
{
	return json_object_array_put_idx ((void *) o, i, (void *) value) == 0;
}
