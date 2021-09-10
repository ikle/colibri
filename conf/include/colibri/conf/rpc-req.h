/*
 * Colibri RPC request helpers
 *
 * Copyright (c) 2018-2021 Alexei A. Smekalkine <ikle@ikle.ru>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#ifndef COLIBRI_CONF_RPC_REQ_H
#define COLIBRI_CONF_RPC_REQ_H

#include <stdio.h>

#include <colibri/conf/compiler.h>

#include <json-c/json.h>

json_object *conf_req_read (struct json_tokener *o, FILE *from);

const char  *conf_req_key	(json_object *o);
const char  *conf_req_mode	(json_object *o);
const char  *conf_req_cmd	(json_object *o);
json_object *conf_req_args	(json_object *o);

json_object *conf_auth	(const char *key, const char *user, const char *pass);
json_object *conf_req	(const char *key, const char *mode,
			 const char *cmd, const char *arg, ...) sentinel;

int conf_req_write (json_object *o, FILE *to, int sync);

#endif  /* COLIBRI_CONF_RPC_REQ_H */
