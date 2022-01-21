/*
 * Colibri JSON dictionary API helpers
 *
 * Copyright (c) 2018-2022 Alexei A. Smekalkine <ikle@ikle.ru>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <colibri/data/json-dict.h>

int json_dict_get_bool (struct json *o, const char *key)
{
	struct json *node;

	if ((node = json_dict_get (o, key)) == NULL)
		return 0;

	return json_get_bool (node);
}

int json_dict_get_int (struct json *o, const char *key)
{
	struct json *node;

	if ((node = json_dict_get (o, key)) == NULL)
		return 0;

	return json_get_int (node);
}

double json_dict_get_float (struct json *o, const char *key)
{
	struct json *node;

	if ((node = json_dict_get (o, key)) == NULL)
		return 0;

	return json_get_float (node);
}

const char *json_dict_get_string (struct json *o, const char *key)
{
	struct json *node;

	if ((node = json_dict_get (o, key)) == NULL)
		return 0;

	return json_get_string (node);
}

int json_dict_set_bool (struct json *o, const char *key, int value)
{
	struct json *node;

	if ((node = json_bool (value)) == NULL)
		return 0;

	if (json_dict_set (o, key, node))
		return 1;

	json_put (node);
	return 0;
}

int json_dict_set_int (struct json *o, const char *key, int value)
{
	struct json *node;

	if ((node = json_int (value)) == NULL)
		return 0;

	if (json_dict_set (o, key, node))
		return 1;

	json_put (node);
	return 0;
}

int json_dict_set_float (struct json *o, const char *key, double value)
{
	struct json *node;

	if ((node = json_float (value)) == NULL)
		return 0;

	if (json_dict_set (o, key, node))
		return 1;

	json_put (node);
	return 0;
}

int json_dict_set_string (struct json *o, const char *key, const char *value)
{
	struct json *node;

	if ((node = json_string (value)) == NULL)
		return 0;

	if (json_dict_set (o, key, node))
		return 1;

	json_put (node);
	return 0;
}
