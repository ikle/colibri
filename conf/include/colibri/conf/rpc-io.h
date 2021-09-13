/*
 * Colibri RPC I/O helpers
 *
 * Copyright (c) 2018-2021 Alexei A. Smekalkine <ikle@ikle.ru>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#ifndef COLIBRI_CONF_RPC_IO_H
#define COLIBRI_CONF_RPC_IO_H  1

#include <stdio.h>

#include <json-c/json.h>

json_object *conf_rpc_read (struct json_tokener *o, FILE *from);
int conf_rpc_write (json_object *o, FILE *to, int sync);

#endif  /* COLIBRI_CONF_RPC_IO_H */
