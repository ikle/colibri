/*
 * Colibri JSON list set helpers
 *
 * Copyright (c) 2018-2022 Alexei A. Smekalkine <ikle@ikle.ru>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <colibri/data/json-list.h>

struct json *json_list_set_list (struct json *o, int i, int size)
{
	struct json *node;

	if ((node = json_list (size)) == NULL)
		return NULL;

	if (json_list_set (o, i, node))
		return node;

	json_put (node);
	return NULL;
}

struct json *json_list_set_dict (struct json *o, int i)
{
	struct json *node;

	if ((node = json_dict ()) == NULL)
		return NULL;

	if (json_list_set (o, i, node))
		return node;

	json_put (node);
	return NULL;
}
