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
#include <colibri/time/callout-clock.h>
#include <colibri/time/callout-counter.h>
#include <colibri/time/callout.h>

SEQ_DECLARE (callout)

struct co_state {
	struct callout_seq queue;
	mtx_t              queue_lock;

	struct co_counter *counter;
	struct co_clock   *clock;

	volatile int run;
	thrd_t worker;
};

static int co_state_worker (void *cookie)
{
	struct co_state *o = cookie;
	size_t now;
	struct callout *co;

	while (o->run) {
		now = co_clock_get (o->clock, 1);

		mtx_lock (&o->queue_lock);

		while ((co = callout_seq_dequeue (&o->queue)) != NULL)
			co_counter_add (o->counter, co, co->time);

		mtx_unlock (&o->queue_lock);

		co_counter_run (o->counter, now);
	}

	return 0;
}

struct co_state *co_state_alloc (unsigned order, int count)
{
	const struct timespec period = {0, 1000000L};  /* 1ms */
	struct co_state *o;

	if ((o = malloc (sizeof (*o))) == NULL)
		return NULL;

	callout_seq_init (&o->queue);
	mtx_init (&o->queue_lock, 0);

	if ((o->counter = co_counter_alloc (0, order, count)) == NULL)
		goto no_counter;

	if ((o->clock = co_clock_alloc (&period)) == NULL)
		goto no_clock;

	o->run = 1;

	if (thrd_create (&o->worker, co_state_worker, o) != thrd_success)
		goto no_worker;

	return o;
no_worker:
	co_clock_free (o->clock);
no_clock:
	co_counter_free (o->counter);
no_counter:
	mtx_destroy (&o->queue_lock);
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

	co_clock_free (o->clock);
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
	co->time = co_clock_get (o->clock, 0) + timeout;

	mtx_lock (&o->queue_lock);

	callout_seq_enqueue (&o->queue, co);

	mtx_unlock (&o->queue_lock);
}
