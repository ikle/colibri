/*
 * Colibri RPC data helpers
 *
 * Copyright (c) 2018-2021 Alexei A. Smekalkine <ikle@ikle.ru>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#ifndef COLIBRI_CONF_RPC_DATA_H
#define COLIBRI_CONF_RPC_DATA_H

#include <colibri/conf/compiler.h>

#include <json-c/json.h>

json_object *conf_text (void);

int conf_text_add	(json_object *o, const char *line);

json_object *conf_dict (void);

int conf_dict_add	(json_object *o, const char *key, const char *value);
int conf_dict_add_int	(json_object *o, const char *key, int value);
int conf_dict_add_float	(json_object *o, const char *key, double value);

int conf_dict_add_attr	(json_object *o, const char *name, const char *value);
int conf_dict_add_node	(json_object *o, const char *name, json_object *value);

json_object *conf_table (const char *key, ...) sentinel;

int conf_table_add	(json_object *o, const char *cell, ...) sentinel;

#endif  /* COLIBRI_CONF_RPC_DATA_H */
