/*
 * Colibri callout counter test
 *
 * Copyright (c) 2015-2021 Alexei A. Smekalkine <ikle@ikle.ru>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <stdio.h>
#include <stdlib.h>

#include <colibri/threads.h>
#include <colibri/time/callout-counter.h>

#define COUNT	110
#define PERIOD	100

struct object {
	struct callout co;
	size_t id;
};

static void worker (int reason, void *cookie)
{
	struct object *o = cookie;

	fprintf (stderr, "I: %zu, reason = %d\n", o->id, reason);

	free (o);
}

int main (int argc, char *argv[])
{
	struct co_counter *c;
	struct object *o;
	size_t now = 1, i;
	struct timespec ts = {0, 100000000L};

	if ((c = co_counter_alloc (now, 4, 2)) == NULL) {
		perror ("E: cannot create callout counter");
		return 1;
	}

	for (i = 1; i <= COUNT; ++i) {
		if ((o = malloc (sizeof (*o))) == NULL) {
			perror ("E: cannot create callout");
			return 1;
		}

		callout_init (&o->co, worker, o);
		co_counter_add (c, &o->co, o->id = i);
	}

	for (; now <= PERIOD; ++now) {
		co_counter_run (c, now);
		thrd_sleep (&ts, NULL);
	}

	co_counter_free (c);
	return 0;
}
