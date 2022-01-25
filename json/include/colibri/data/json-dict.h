/*
 * Colibri JSON dictionary API
 *
 * Copyright (c) 2018-2022 Alexei A. Smekalkine <ikle@ikle.ru>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#ifndef COLIBRI_DATA_JSON_DICT_H
#define COLIBRI_DATA_JSON_DICT_H  1

#include <colibri/data/json-core.h>

int json_dict_exists (struct json *o, const char *key);

struct json *json_dict_get        (struct json *o, const char *key);
int          json_dict_get_bool   (struct json *o, const char *key);
int          json_dict_get_int    (struct json *o, const char *key);
double       json_dict_get_float  (struct json *o, const char *key);
const char  *json_dict_get_string (struct json *o, const char *key);

struct json *json_dict_get_list (struct json *o, const char *key);
struct json *json_dict_get_dict (struct json *o, const char *key);

int json_dict_set        (struct json *o, const char *key, struct json *value);
int json_dict_set_bool   (struct json *o, const char *key, int value);
int json_dict_set_int    (struct json *o, const char *key, int value);
int json_dict_set_float  (struct json *o, const char *key, double value);
int json_dict_set_string (struct json *o, const char *key, const char *value);

struct json *json_dict_set_list (struct json *o, const char *key, int size);
struct json *json_dict_set_dict (struct json *o, const char *key);

void json_dict_remove (struct json *o, const char *key);

struct json_entry *json_dict_list (struct json *o);
struct json_entry *json_entry_next (struct json_entry *o);

const char  *json_entry_key (struct json_entry *o);
struct json *json_entry_get (struct json_entry *o);

#endif  /* COLIBRI_DATA_JSON_DICT_H */
