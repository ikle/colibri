/*
 * Colibri JSON core API
 *
 * Copyright (c) 2018-2021 Alexei A. Smekalkine <ikle@ikle.ru>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <colibri/data/json-core.h>

#define json_bool  json_bool_impl
#define json_type  json_type_impl

#include <json-c/json.h>

#undef json_bool
#undef json_type

struct json *json_bool (int value)
{
	return (void *) json_object_new_boolean (value);
}

struct json *json_int (int value)
{
	return (void *) json_object_new_int (value);
}

struct json *json_float (double value)
{
	return (void *) json_object_new_double (value);
}

struct json *json_string (const char *value)
{
	return (void *) json_object_new_string (value);
}

struct json *json_list (int size)
{
	json_object *o;

	if ((o = json_object_new_array ()) == NULL)
		return NULL;

	if (size > 0 && json_object_array_put_idx (o, size - 1, NULL) < 0)
		goto no_resize;

	return (void *) o;
no_resize:
	json_object_put (o);
	return NULL;
}

struct json *json_dict (void)
{
	return (void *) json_object_new_object ();
}

void json_get (struct json *o)
{
	json_object_get ((void *) o);
}

void json_put (struct json *o)
{
	json_object_put ((void *) o);
}

enum json_type json_type (struct json *o)
{
	switch (json_object_get_type ((void *) o)) {
	case json_type_boolean:	return JSON_BOOL;
	case json_type_double:	return JSON_FLOAT;
	case json_type_int:	return JSON_INT;
	case json_type_object:	return JSON_DICT;
	case json_type_array:	return JSON_LIST;
	case json_type_string:	return JSON_STRING;
	default:
		break;
	}

	return JSON_NULL;
}

int json_get_bool (struct json *o)
{
	return json_object_get_boolean ((void *) o);
}

int json_get_int (struct json *o)
{
	return json_object_get_int ((void *) o);
}

double json_get_float (struct json *o)
{
	return json_object_get_double ((void *) o);
}

const char *json_get_string (struct json *o)
{
	return json_object_get_string ((void *) o);
}
