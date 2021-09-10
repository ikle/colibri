/*
 * Colibri RPC data helpers
 *
 * Copyright (c) 2018-2021 Alexei A. Smekalkine <ikle@ikle.ru>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <errno.h>
#include <stdarg.h>

#include <colibri/conf/rpc-data.h>

json_object *conf_text (void)
{
	return json_object_new_array ();
}

int conf_text_add (json_object *o, const char *line)
{
	json_object *p;

	if (!json_object_is_type (o, json_type_array)) {
		errno = EINVAL;
		return 0;
	}

	if ((p = json_object_new_string (line)) == NULL)
		return 0;

	if (json_object_array_add (o, p) == 0)
		return 1;

	json_object_put (p);
	return 0;
}

json_object *conf_dict (void)
{
	return json_object_new_object ();
}

int conf_dict_add_node (json_object *o, const char *name, json_object *value)
{
	if (!json_object_is_type (o, json_type_object)) {
		errno = EINVAL;
		return 0;
	}

	json_object_object_add (o, name, value);
	return 1;
}

int conf_dict_add (json_object *o, const char *key, const char *value)
{
	json_object *p;

	if ((p = json_object_new_string (value)) == NULL)
		return 0;

	if (conf_dict_add_node (o, key, p))
		return 1;

	json_object_put (p);
	return 0;
}

int conf_dict_add_int (json_object *o, const char *key, int value)
{
	json_object *p;

	if ((p = json_object_new_int (value)) == NULL)
		return 0;

	if (conf_dict_add_node (o, key, p))
		return 1;

	json_object_put (p);
	return 0;
}

int conf_dict_add_float (json_object *o, const char *key, double value)
{
	json_object *p;

	if ((p = json_object_new_double (value)) == NULL)
		return 0;

	if (conf_dict_add_node (o, key, p))
		return 1;

	json_object_put (p);
	return 0;
}

int conf_dict_add_attr (json_object *o, const char *name, const char *value)
{
	json_object *a = NULL, *p = NULL;

	if (!json_object_is_type (o, json_type_object)) {
		errno = EINVAL;
		return 0;
	}

	if (json_object_object_get_ex (o, name, &p)) {
		json_object_get (p);

		if (json_object_is_type (p, json_type_array)) {
			a = p;
			p = NULL;
		}
	}

	if (a == NULL && (a = conf_text ()) == NULL)
		goto no_array;

	if (!conf_dict_add_node (o, name, a))
		goto no_replace;

	if (p != NULL && json_object_array_add (a, p) < 0)
		goto no_revert;

	return conf_text_add (a, value);
no_replace:
	json_object_put (a);
no_array:
no_revert:
	json_object_put (p);
	return 0;
}

json_object *conf_table (const char *key, ...)
{
	json_object *o, *row;
	va_list ap;

	if ((o = json_object_new_array ()) == NULL)
		return NULL;

	if ((row = conf_text ()) == NULL)
		goto no_row;

	va_start (ap, key);

	do {
		if (!conf_text_add (row, key))
			goto no_add;
	}
	while ((key = va_arg (ap, const char *)) != NULL);

	va_end (ap);

	if (json_object_array_add (o, row) < 0)
		goto no_add;

	return o;
no_add:
	json_object_put (row);
no_row:
	json_object_put (o);
	return 0;
}

int conf_table_add (json_object *o, const char *cell, ...)
{
	json_object *row;
	va_list ap;

	if (!json_object_is_type (o, json_type_array)) {
		errno = EINVAL;
		return 0;
	}

	if ((row = conf_text ()) == NULL)
		return 0;

	va_start (ap, cell);

	do {
		if (!conf_text_add (row, cell))
			goto no_add;
	}
	while ((cell = va_arg (ap, const char *)) != NULL);

	va_end (ap);

	if (json_object_array_add (o, row) < 0)
		goto no_add;

	return 1;
no_add:
	json_object_put (row);
	return 0;
}
