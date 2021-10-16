/*
 * Colibri callout monotonic clock
 *
 * Copyright (c) 2015-2021 Alexei A. Smekalkine <ikle@ikle.ru>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#ifndef COLIBRI_TIME_CALLOUT_CLOCK_H
#define COLIBRI_TIME_CALLOUT_CLOCK_H  1

#include <stddef.h>
#include <time.h>

struct co_clock *co_clock_alloc (struct timespec *period);
void co_clock_free (struct co_clock *o);

size_t co_clock_get (struct co_clock *o, int wait);

#endif  /* COLIBRI_TIME_CALLOUT_CLOCK_H */
