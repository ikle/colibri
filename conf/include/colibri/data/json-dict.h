/*
 * Colibri JSON dictionary API
 *
 * Copyright (c) 2018-2021 Alexei A. Smekalkine <ikle@ikle.ru>
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
double       json_dict_get_number (struct json *o, const char *key);
const char  *json_dict_get_string (struct json *o, const char *key);

int json_dict_set        (struct json *o, const char *key, struct json *value);
int json_dict_set_bool   (struct json *o, const char *key, int value);
int json_dict_set_int    (struct json *o, const char *key, int value);
int json_dict_set_float  (struct json *o, const char *key, double value);
int json_dict_set_string (struct json *o, const char *key, const char *value);

void json_dict_remove (struct json *o, const char *key);

#endif  /* COLIBRI_DATA_JSON_DICT_H */
