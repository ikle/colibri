/*
 * Colibri JSON output helpers
 *
 * Copyright (c) 2016-2021 Alexei A. Smekalkine <ikle@ikle.ru>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#ifndef COLIBRI_DATA_JSON_OUTPUT_H
#define COLIBRI_DATA_JSON_OUTPUT_H  1

#include <colibri/data/json-core.h>

typedef int json_writer (const void *buffer, int size, void *cookie);

struct json_output *json_output_open (json_writer *write, void *cookie);
void json_output_close (struct json_output *o);

int json_write (struct json_output *o, const struct json *json);

#endif  /* COLIBRI_DATA_JSON_OUTPUT_H */
