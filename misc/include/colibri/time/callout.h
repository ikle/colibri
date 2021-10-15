/*
 * Colibri callout task scheduler
 *
 * Copyright (c) 2015-2021 Alexei A. Smekalkine <ikle@ikle.ru>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#ifndef COLIBRI_TIME_CALLOUT_H
#define COLIBRI_TIME_CALLOUT_H  1

#include <colibri/time/callout-core.h>

struct co_state *co_state_alloc (unsigned order, int count);
void co_state_free (struct co_state *o);

void callout_schedule (struct co_state *o, struct callout *co, size_t timeout);

#endif  /* COLIBRI_TIME_CALLOUT_H */
