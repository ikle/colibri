/*
 * Colibri callout monotonic clock test
 *
 * Copyright (c) 2015-2021 Alexei A. Smekalkine <ikle@ikle.ru>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <stdio.h>

#include <colibri/time/callout-clock.h>

int main (int argc, char *argv[])
{
	const struct timespec period = {0, 100000000L};  /* 100ms */
	struct co_clock *clock;
	size_t now;

	if ((clock = co_clock_alloc (&period)) == NULL) {
		perror ("E: cannot create clock");
		return 1;
	}

	while ((now = co_clock_get (clock, 1)) < 100)
		fprintf (stderr, "I: now = %zu\n", now);

	co_clock_free (clock);
	return 0;
}
