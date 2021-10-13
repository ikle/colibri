/*
 * Colibri simple callout task scheduler
 *
 * Copyright (c) 2015-2021 Alexei A. Smekalkine <ikle@ikle.ru>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <errno.h>
#include <stdlib.h>

#include <colibri/data/seq.h>
#include <colibri/time/callout.h>

void callout_init (struct callout *o, callout_cb *cb, void *cookie)
{
	o->next   = NULL;
	o->time   = 0;
	o->cb     = cb;
	o->cookie = cookie;
}

SEQ_DECLARE (callout)

struct co_wheel {
	struct co_wheel *next;
	unsigned order;
	struct callout_seq *spoke;
};

static size_t co_wheel_count (struct co_wheel *o)
{
	return 1 << o->order;
}

static size_t co_wheel_index (struct co_wheel *o, size_t i)
{
	return i & (co_wheel_count (o) - 1);
}

static struct co_wheel *co_wheel_alloc (unsigned order)
{
	struct co_wheel *o;
	size_t i;

	if ((o = malloc (sizeof (*o))) == NULL)
		return NULL;

	o->next  = NULL;
	o->order = order;
	o->spoke = malloc (sizeof (o->spoke[0]) * co_wheel_count (o));

	if (o->spoke == NULL)
		goto no_spokes;

	for (i = 0; i < co_wheel_count (o); ++i)
		callout_seq_init (o->spoke + i);

	return o;
no_spokes:
	free (o);
	return NULL;
}

static void co_wheel_throw (struct co_wheel *o, size_t i, int reason)
{
	struct callout_seq *spoke = o->spoke + co_wheel_index (o, i);
	struct callout *co;

	while ((co = callout_seq_dequeue (spoke)) != NULL) {
		co->time = 0;
		co->cb (reason, co->cookie);
	}
}

static void co_wheel_free (struct co_wheel *o)
{
	size_t i;

	if (o == NULL)
		return;

	for (i = 0; i < co_wheel_count (o); ++i)
		co_wheel_throw (o, i, 0);  /* reason = drop */

	free (o->spoke);
	free (o);
}

static void co_wheel_push (struct co_wheel *o, size_t delay,
			   struct callout *co, size_t i)
{
	if (o->next == NULL || delay < co_wheel_count (o)) {
		callout_seq_enqueue (o->spoke + co_wheel_index (o, i), co);
		return;
	}

	co_wheel_push (o->next, delay >> o->order, co, i);
}

static void co_wheel_shake (struct co_wheel *o, struct co_counter *c, size_t i)
{
	struct callout_seq *spoke = o->spoke + co_wheel_index (o, i);
	struct callout *co;

	while ((co = callout_seq_dequeue (spoke)) != NULL)
		co_counter_add (c, co, co->time);
}

static void co_wheel_step (struct co_wheel *o, struct co_counter *c, size_t i)
{
	if (o->next == NULL || co_wheel_index (o, i) != 0)
		return;

	i >>= o->order;

	co_wheel_shake (o->next, c, i);
	co_wheel_step  (o->next, c, i);
}

SEQ_DECLARE (co_wheel)

struct co_counter {
	size_t now;
	struct co_wheel_seq seq;
};

struct co_counter *co_counter_alloc (size_t now, unsigned order, int count)
{
	struct co_counter *o;
	struct co_wheel *wheel;

	if (order < 4 || count < 2) {
		errno = EINVAL;
		return NULL;
	}

	if ((o = malloc (sizeof (*o))) == NULL)
		return NULL;

	o->now = now;

	co_wheel_seq_init (&o->seq);

	for (; count > 0; --count) {
		if ((wheel = co_wheel_alloc (order)) == NULL)
			goto no_wheels;

		co_wheel_seq_enqueue (&o->seq, wheel);
	}

	return o;
no_wheels:
	co_wheel_seq_fini (&o->seq, co_wheel_free);
	free (o);
	return NULL;
}

void co_counter_free (struct co_counter *o)
{
	if (o == NULL)
		return;

	co_wheel_seq_fini (&o->seq, co_wheel_free);
	free (o);
}

void co_counter_add (struct co_counter *o, struct callout *co, size_t at)
{
	if (at > o->now) {
		co->time = at;
		co_wheel_push (o->seq.head, at - o->now, co, at);
	}
	else
		co->cb (1, co->cookie);  /* reason = timeout */
}

static void co_counter_step (struct co_counter *o)
{
	co_wheel_throw (o->seq.head, o->now, 1);  /* reason = timeout */
	co_wheel_step  (o->seq.head, o, ++o->now);
}

void co_counter_run (struct co_counter *o, size_t now)
{
	while (o->now < now)
		co_counter_step (o);
}
