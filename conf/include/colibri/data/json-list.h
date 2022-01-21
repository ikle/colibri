/*
 * Colibri JSON list API
 *
 * Copyright (c) 2018-2022 Alexei A. Smekalkine <ikle@ikle.ru>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#ifndef COLIBRI_DATA_JSON_LIST_H
#define COLIBRI_DATA_JSON_LIST_H  1

#include <colibri/data/json-core.h>

int  json_list_size (struct json *o);

struct json *json_list_get        (struct json *o, int i);
int          json_list_get_bool   (struct json *o, int i);
int          json_list_get_int    (struct json *o, int i);
double       json_list_get_float  (struct json *o, int i);
const char  *json_list_get_string (struct json *o, int i);

struct json *json_list_get_list (struct json *o, int i);
struct json *json_list_get_dict (struct json *o, int i);

int json_list_set        (struct json *o, int i, struct json *value);
int json_list_set_bool   (struct json *o, int i, int value);
int json_list_set_int    (struct json *o, int i, int value);
int json_list_set_float  (struct json *o, int i, double value);
int json_list_set_string (struct json *o, int i, const char *value);

struct json *json_list_set_list (struct json *o, int i, int size);
struct json *json_list_set_dict (struct json *o, int i);

#endif  /* COLIBRI_DATA_JSON_LIST_H */
