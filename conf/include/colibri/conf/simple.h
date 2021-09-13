/*
 * Colibri simple configuration access helpers
 *
 * Copyright (c) 2018-2021 Alexei A. Smekalkine <ikle@ikle.ru>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#ifndef COLIBRI_CONF_SIMPLE_H
#define COLIBRI_CONF_SIMPLE_H  1

#include <stddef.h>

struct conf *conf_alloc (const char *root);
void conf_free (struct conf *o);

struct conf *conf_clone (struct conf *o, ...);
int conf_exists (struct conf *o, ...);

int conf_get (struct conf *o, char *buf, size_t size);
int conf_rewind (struct conf *o);

enum {
	CONF_TYPE_NODE	= 0,
	CONF_TYPE_TAG	= 1,	/* not supported yet */
	CONF_TYPE_ATTR	= 2,
	CONF_TYPE_VALUE	= 3,
};

typedef int (conf_cb) (struct conf *o, int type, char *entry, void *cookie);

int conf_iterate (struct conf *o, conf_cb *cb, void *cookie, ...);
int conf_fetch (struct conf *o, char *buf, size_t size, ...);

#endif  /* COLIBRI_CONF_SIMPLE_H */
