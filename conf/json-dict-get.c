/*
 * Colibri JSON dictionary get helpers
 *
 * Copyright (c) 2018-2021 Alexei A. Smekalkine <ikle@ikle.ru>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <colibri/data/json-dict.h>

struct json *json_dict_get_list (struct json *o, const char *key)
{
	struct json *node;

	if ((node = json_dict_get (o, key)) == NULL)
		return NULL;

	return json_type (node) == JSON_LIST ? node : NULL;
}

struct json *json_dict_get_dict (struct json *o, const char *key)
{
	struct json *node;

	if ((node = json_dict_get (o, key)) == NULL)
		return NULL;

	return json_type (node) == JSON_DICT ? node : NULL;
}
