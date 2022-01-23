/*
 * Colibri JSON merge helper
 *
 * Copyright (c) 2018-2022 Alexei A. Smekalkine <ikle@ikle.ru>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <colibri/data/json.h>

#define json_bool  json_bool_impl
#define json_type  json_type_impl

#include <json-c/json.h>

#undef json_bool
#undef json_type

static struct json *json_dict_merge (struct json *a, struct json *b)
{
	struct json *o, *e;
	struct json_object_iter it;

	if ((o = json_dict ()) == NULL)
		return NULL;

	json_object_object_foreachC ((void *) a, it) {
		if (json_dict_get (b, it.key) != NULL)
			continue;

		e = json_merge ((void *) it.val, NULL);

		if (!json_dict_set (o, it.key, e))
			goto error;
	}

	json_object_object_foreachC ((void *) b, it) {
		e = json_merge (json_dict_get (a, it.key), (void *) it.val);

		if (e == NULL && it.val != NULL)
			goto error;

		if (!json_dict_set (o, it.key, e))
			goto error;
	}

	return o;
error:
	json_put (e);
	json_put (o);
	return NULL;
}

struct json *json_merge (struct json *a, struct json *b)
{
	enum json_type type;

	if ((type = json_type (a)) == json_type (b) && type == JSON_DICT)
		return json_dict_merge (a, b);

	json_get (b);
	return b;
}
