/*
 * Colibri RPC answer helpers
 *
 * Copyright (c) 2018-2021 Alexei A. Smekalkine <ikle@ikle.ru>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#ifndef COLIBRI_CONF_RPC_ANS_H
#define COLIBRI_CONF_RPC_ANS_H

#include <stdio.h>

#include <colibri/conf/error.h>
#include <colibri/conf/rpc-data.h>

#include <json-c/json.h>

json_object *conf_ans_read (struct json_tokener *o, FILE *from);

int          conf_ans_code	(json_object *o);
const char  *conf_ans_reason	(json_object *o);
json_object *conf_ans_data	(json_object *o);
int          conf_ans_last	(json_object *o);

json_object *conf_ans	(int code, const char *reason,
			 const char *data, int last);

int conf_ans_add_text	(json_object *o, json_object *data);
int conf_ans_add_dict	(json_object *o, json_object *data);
int conf_ans_add_tree	(json_object *o, json_object *data);
int conf_ans_add_table	(json_object *o, json_object *data);

int conf_ans_write (json_object *o, FILE *to, int sync);

#endif  /* COLIBRI_CONF_RPC_ANS_H */
