/*
 * Colibri JSON dictionary iteration API
 *
 * Copyright (c) 2018-2022 Alexei A. Smekalkine <ikle@ikle.ru>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <colibri/data/json-dict.h>

#define json_bool  json_bool_impl
#define json_type  json_type_impl

#include <json-c/json.h>

#undef json_bool
#undef json_type

struct json_entry *json_dict_list (struct json *o)
{
	struct lh_table *table = json_object_get_object ((void *) o);

	return table == NULL ? NULL : (void *) table->head;
}

struct json_entry *json_entry_next (struct json_entry *o)
{
	struct lh_entry *e = (void *) o;

	return e == NULL ? NULL : (void *) e->next;
}

const char *json_entry_key (struct json_entry *o)
{
	struct lh_entry *e = (void *) o;

	return e == NULL ? NULL : e->k;
}

struct json *json_entry_get (struct json_entry *o)
{
	struct lh_entry *e = (void *) o;

	return e == NULL ? NULL : (void *) e->v;
}
