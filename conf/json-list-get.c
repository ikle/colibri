/*
 * Colibri JSON list get helpers
 *
 * Copyright (c) 2018-2022 Alexei A. Smekalkine <ikle@ikle.ru>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <colibri/data/json-list.h>

struct json *json_list_get_list (struct json *o, int i)
{
	struct json *node;

	if ((node = json_list_get (o, i)) == NULL)
		return NULL;

	return json_type (node) == JSON_LIST ? node : NULL;
}

struct json *json_list_get_dict (struct json *o, int i)
{
	struct json *node;

	if ((node = json_list_get (o, i)) == NULL)
		return NULL;

	return json_type (node) == JSON_DICT ? node : NULL;
}
