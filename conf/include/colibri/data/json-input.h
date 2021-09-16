/*
 * Colibri JSON input helpers
 *
 * Copyright (c) 2016-2021 Alexei A. Smekalkine <ikle@ikle.ru>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#ifndef COLIBRI_DATA_JSON_INPUT_H
#define COLIBRI_DATA_JSON_INPUT_H  1

#include <colibri/data/json-core.h>

typedef int json_reader (void *buffer, int size, void *cookie);

struct json_input *json_input_open (json_reader *read, void *cookie);
void json_input_close (struct json_input *o);

struct json *json_read (struct json_input *o);

#endif  /* COLIBRI_DATA_JSON_INPUT_H */
