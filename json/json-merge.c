/*
 * Colibri JSON merge helper
 *
 * Copyright (c) 2018-2022 Alexei A. Smekalkine <ikle@ikle.ru>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <colibri/data/json.h>

static struct json *json_dict_merge (struct json *a, struct json *b)
{
	struct json *o, *v, *val;
	struct json_entry *e;
	const char *key;

	if ((o = json_dict ()) == NULL)
		return NULL;

	for (e = json_dict_list (a); e != NULL; e = json_entry_next (e)) {
		key = json_entry_key (e);

		if (json_dict_get (b, key) != NULL)
			continue;

		v = json_merge (NULL, json_entry_get (e));

		if (!json_dict_set (o, key, v))
			goto error;
	}

	for (e = json_dict_list (b); e != NULL; e = json_entry_next (e)) {
		key = json_entry_key (e);
		val = json_entry_get (e);

		v = json_merge (json_dict_get (a, key), val);

		if (v == NULL && val != NULL)
			goto error;

		if (!json_dict_set (o, key, v))
			goto error;
	}

	return o;
error:
	json_put (v);
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
