/*
 * Colibri time helpers
 *
 * Copyright (c) 2015-2021 Alexei A. Smekalkine <ikle@ikle.ru>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#ifndef COLIBRI_TIME_H
#define COLIBRI_TIME_H  1

#include <time.h>

#include <colibri/bits/c.h>

#ifndef TIME_UTC
#ifdef CLOCK_REALTIME
#define TIME_UTC  1

static inline int timespec_get (struct timespec *ts, int base)
{
	if (base != TIME_UTC)
		return 0;

	return clock_gettime (CLOCK_REALTIME, ts) == 0 ? base : 0;
}
#else
#error "C11 standard library or POSIX Timers required"
#endif  /* CLOCK_REALTIME */
#endif  /* !TIME_UTC */

#endif  /* COLIBRI_TIME_H */
