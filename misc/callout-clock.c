/*
 * Colibri callout monotonic clock
 *
 * Copyright (c) 2015-2021 Alexei A. Smekalkine <ikle@ikle.ru>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <stdlib.h>

#include <colibri/threads.h>
#include <colibri/time/callout-clock.h>

struct co_clock {
	struct timespec period;

	size_t now;
	mtx_t  lock;
	cnd_t  signal;

	volatile int run;
	thrd_t worker;
};

static int co_clock_worker (void *cookie)
{
	struct co_clock *o = cookie;

	while (o->run) {
		thrd_sleep (&o->period, NULL);

		mtx_lock (&o->lock);
		++o->now;
		mtx_unlock (&o->lock);

		cnd_broadcast (&o->signal);
	}

	return 0;
}

struct co_clock *co_clock_alloc (const struct timespec *period)
{
	struct co_clock *o;

	if ((o = malloc (sizeof (*o))) == NULL)
		return NULL;

	o->period = *period;
	o->now    = 0;
	o->run    = 1;

	mtx_init (&o->lock, 0);
	cnd_init (&o->signal);

	if (thrd_create (&o->worker, co_clock_worker, o) != thrd_success)
		goto no_worker;

	return o;
no_worker:
	cnd_destroy (&o->signal);
	mtx_destroy (&o->lock);
	free (o);
	return NULL;
}

void co_clock_free (struct co_clock *o)
{
	if (o == NULL)
		return;

	o->run = 0;
	thrd_join (o->worker, NULL);

	cnd_destroy (&o->signal);
	mtx_destroy (&o->lock);
	free (o);
}

size_t co_clock_get (struct co_clock *o, int wait)
{
	size_t now;

	mtx_lock (&o->lock);

	if (wait)
		cnd_wait (&o->signal, &o->lock);

	now = o->now;

	mtx_unlock (&o->lock);

	return now;
}
