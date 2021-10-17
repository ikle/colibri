/*
 * Colibri message mailbox test
 *
 * Copyright (c) 2014-2021 Alexei A. Smekalkine <ikle@ikle.ru>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <stdio.h>
#include <stdlib.h>

#include <colibri/sync/mailbox.h>
#include <colibri/threads.h>

struct test_message {
	struct message message;
	int id;
};

static struct test_message *test_message_alloc (int id)
{
	struct test_message *o;

	if ((o = malloc (sizeof (*o))) == NULL)
		return NULL;

	message_init (&o->message);
	o->id = id;
	return o;
}

static void test_message_free (struct test_message *o)
{
	if (o == NULL)
		return;

	free (o);
}

static int test_message_write (int id, struct mailbox *mb, int wait)
{
	struct test_message *o;

	if ((o = test_message_alloc (id)) == NULL)
		return 0;

	if (mailbox_write (mb, &o->message, wait))
		return 1;

	test_message_free (o);
	return 0;
}

static int test_message_read (struct mailbox *mb, int wait)
{
	struct test_message *o;
	int id;

	if ((o = (void *) mailbox_read (mb, wait)) == NULL)
		return 0;

	id = o->id;
	test_message_free (o);
	return id;
}

static void test_message_free_cb (struct message *o)
{
	test_message_free ((void *) o);
}

static struct mailbox *test_mailbox_alloc (int limit)
{
	return mailbox_alloc (limit, test_message_free_cb);
}

static int writer_worker (void *cookie)
{
	const struct timespec period = {0, 50000000L};  /* 50ms */
	struct mailbox *mb = cookie;
	size_t i;

	for (i = 1; i <= 10; ++i) {
		if (!test_message_write (i, mb, 1))
			fprintf (stderr, "W: cannot write %zu to mailbox\n", i);
		else
			fprintf (stderr, "D: send %zu\n", i);

		thrd_sleep (&period, NULL);
	}

	return 0;
}

static int reader_worker (void *cookie)
{
	const struct timespec period = {0, 70000000L};  /* 70ms */
	struct mailbox *mb = cookie;
	size_t i;
	int id;

	for (i = 0; i < 10; ++i) {
		if ((id = test_message_read (mb, 1)) == 0)
			fprintf (stderr, "W: cannot read from mailbox\n");
		else
			fprintf (stderr, "D: got %d\n", id);

		thrd_sleep (&period, NULL);
	}

	return 0;
}

int main (int argc, char *argv[])
{
	struct mailbox *mb;
	thrd_t writer, reader;

	if ((mb = test_mailbox_alloc (10)) == NULL) {
		perror ("E: cannot create mailbox");
		return 1;
	}

	if (thrd_create (&writer, writer_worker, mb) != thrd_success) {
		perror ("E: cannot create writer");
		return 1;
	}

	if (thrd_create (&reader, reader_worker, mb) != thrd_success) {
		perror ("E: cannot create reader");
		return 1;
	}

	thrd_join (reader, NULL);
	thrd_join (writer, NULL);
	mailbox_free (mb);
	return 0;
}
