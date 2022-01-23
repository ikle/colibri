/*
 * Colibri JSON dictionary set helpers
 *
 * Copyright (c) 2018-2021 Alexei A. Smekalkine <ikle@ikle.ru>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <colibri/data/json-dict.h>

struct json *json_dict_set_list (struct json *o, const char *key, int size)
{
	struct json *node;

	if ((node = json_list (size)) == NULL)
		return NULL;

	if (json_dict_set (o, key, node))
		return node;

	json_put (node);
	return NULL;
}

struct json *json_dict_set_dict (struct json *o, const char *key)
{
	struct json *node;

	if ((node = json_dict ()) == NULL)
		return NULL;

	if (json_dict_set (o, key, node))
		return node;

	json_put (node);
	return NULL;
}
