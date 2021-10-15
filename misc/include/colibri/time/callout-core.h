/*
 * Colibri callout core helpers
 *
 * Copyright (c) 2015-2021 Alexei A. Smekalkine <ikle@ikle.ru>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#ifndef COLIBRI_TIME_CALLOUT_CORE_H
#define COLIBRI_TIME_CALLOUT_CORE_H  1

#include <stddef.h>

#include <colibri/bits/c.h>

typedef void callout_cb (int reason, void *cookie);

struct callout {
	struct callout *next;  /* for internal use, do not touch it */
	size_t time;
	callout_cb *cb;
	void *cookie;
};

/*
 * Initialize callout object
 */
static inline
void callout_init (struct callout *o, callout_cb *cb, void *cookie)
{
	o->next   = NULL;
	o->time   = 0;
	o->cb     = cb;
	o->cookie = cookie;
}

#endif  /* COLIBRI_TIME_CALLOUT_CORE_H */
