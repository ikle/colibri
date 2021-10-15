/*
 * Colibri simple callout task scheduler
 *
 * Copyright (c) 2015-2021 Alexei A. Smekalkine <ikle@ikle.ru>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#ifndef COLIBRI_TIME_CALLOUT_H
#define COLIBRI_TIME_CALLOUT_H  1

#include <stddef.h>

#include <colibri/time/callout-core.h>

/*
 * Create callout counter with counter wheels with 2^order time slots
 *
 * NOTE: order ≥ 4, count ≥ 2
 */
struct co_counter *co_counter_alloc (size_t now, unsigned order, int count);
void co_counter_free (struct co_counter *o);

/*
 * Schedule this callout to run in the specified timeout
 */
void co_counter_add (struct co_counter *o, struct callout *co, size_t at);

/*
 * Process all scheduled callouts upto now
 */
void co_counter_run (struct co_counter *o, size_t now);

#endif  /* COLIBRI_TIME_CALLOUT_H */
