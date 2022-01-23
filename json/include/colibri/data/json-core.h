/*
 * Colibri JSON core API
 *
 * Copyright (c) 2018-2021 Alexei A. Smekalkine <ikle@ikle.ru>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#ifndef COLIBRI_DATA_JSON_CORE_H
#define COLIBRI_DATA_JSON_CORE_H  1

#include <stddef.h>

enum json_type {
	JSON_NULL	= 0,
	JSON_BOOL	= 1,
	JSON_INT	= 2,
	JSON_FLOAT	= 3,
	JSON_STRING	= 4,
	JSON_LIST	= 5,
	JSON_DICT	= 6,
};

struct json *json_bool   (int value);
struct json *json_int    (int value);
struct json *json_float  (double value);
struct json *json_string (const char *value);
struct json *json_list   (int size);
struct json *json_dict   (void);

void json_get (struct json *o);
void json_put (struct json *o);

enum json_type json_type (struct json *o);

int          json_get_bool   (struct json *o);
int          json_get_int    (struct json *o);
double       json_get_float  (struct json *o);
const char  *json_get_string (struct json *o);

#endif  /* COLIBRI_DATA_JSON_CORE_H */
