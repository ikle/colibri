/*
 * Colibri JSON API
 *
 * Copyright (c) 2018-2022 Alexei A. Smekalkine <ikle@ikle.ru>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#ifndef COLIBRI_DATA_JSON_H
#define COLIBRI_DATA_JSON_H  1

#include <colibri/data/json-list.h>
#include <colibri/data/json-dict.h>

#include <colibri/data/json-input.h>
#include <colibri/data/json-output.h>

struct json *json_merge (struct json *a, struct json *b);

#endif  /* COLIBRI_DATA_JSON_H */
