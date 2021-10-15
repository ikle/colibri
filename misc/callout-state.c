/*
 * Colibri callout task scheduler
 *
 * Copyright (c) 2015-2021 Alexei A. Smekalkine <ikle@ikle.ru>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <stdlib.h>

#include <colibri/data/seq.h>
#include <colibri/threads.h>
#include <colibri/time/callout-counter.h>
#include <colibri/time/callout.h>

SEQ_DECLARE (callout)

struct co_state {
	struct callout_seq queue;
	mtx_t              queue_lock;

	struct co_counter *counter;
	mtx_t              counter_lock;

	volatile int run;
	thrd_t worker;
};

static size_t get_ticks (void)
{
	struct timespec ts;

	timespec_get (&ts, TIME_UTC);

	return ts.tv_sec * 1000 + ts.tv_nsec / 1000000L;
}

static int co_worker (void *cookie)
{
	struct co_state *o = cookie;
	struct callout *co;
	struct timespec ts = {0, 500000L};  /* 2 * 1kHz */

	while (o->run) {
		mtx_lock (&o->counter_lock);
		mtx_lock (&o->queue_lock);

		while ((co = callout_seq_dequeue (&o->queue)) != NULL)
			co_counter_add (o->counter, co, co->time);

		mtx_unlock (&o->queue_lock);

		co_counter_run (o->counter, get_ticks ());

		mtx_unlock (&o->counter_lock);
		thrd_sleep (&ts, NULL);
	}

	return 0;
}

struct co_state *co_state_alloc (unsigned order, int count)
{
	struct co_state *o;
	size_t now = get_ticks ();

	if ((o = malloc (sizeof (*o))) == NULL)
		return NULL;

	callout_seq_init (&o->queue);
	mtx_init (&o->queue_lock, 0);

	if ((o->counter = co_counter_alloc (now, order, count)) == NULL)
		goto no_counter;

	mtx_init (&o->counter_lock, 0);

	o->run = 1;

	if (thrd_create (&o->worker, co_worker, o) != thrd_success)
		goto no_worker;

	return o;
no_worker:
	co_counter_free (o->counter);
no_counter:
	free (o);
	return NULL;
}

void co_state_free (struct co_state *o)
{
	struct callout *co;

	if (o == NULL)
		return;

	o->run = 0;
	thrd_join (o->worker, NULL);

	mtx_destroy (&o->counter_lock);
	co_counter_free (o->counter);

	mtx_destroy (&o->queue_lock);

	while ((co = callout_seq_dequeue (&o->queue)) != NULL) {
		co->time = 0;
		co->cb (0, co->cookie);  /* reason = drop */
	}

	free (o);
}

void callout_schedule (struct co_state *o, struct callout *co, size_t timeout)
{
	co->time = get_ticks () + timeout;

	mtx_lock (&o->queue_lock);

	callout_seq_enqueue (&o->queue, co);

	mtx_unlock (&o->queue_lock);
}
