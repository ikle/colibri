/*
 * Colibri message mailbox
 *
 * Copyright (c) 2014-2021 Alexei A. Smekalkine <ikle@ikle.ru>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <stdlib.h>

#include <colibri/data/seq.h>
#include <colibri/sync/mailbox.h>
#include <colibri/threads.h>

SEQ_DECLARE (message)

struct mailbox {
	int avail;
	message_free *free;
	struct message_seq queue;
	mtx_t lock;
	cnd_t signal;
};

struct mailbox *mailbox_alloc (int limit, message_free *free)
{
	struct mailbox *o;

	if ((o = malloc (sizeof (*o))) == NULL)
		return NULL;

	o->avail = limit;
	o->free  = free;

	message_seq_init (&o->queue);
	mtx_init (&o->lock, 0);
	cnd_init (&o->signal);

	return o;
}

void mailbox_free (struct mailbox *o)
{
	if (o == NULL)
		return;

	cnd_destroy (&o->signal);
	mtx_destroy (&o->lock);
	message_seq_fini (&o->queue, o->free);
	free (o);
}

static int mailbox_write_locked (struct mailbox *o, struct message *m)
{
	if (o->avail <= 0)
		return 0;

	--o->avail;
	message_seq_enqueue (&o->queue, m);
	return 1;
}

int mailbox_write (struct mailbox *o, struct message *m, int wait)
{
	int ok;

	mtx_lock (&o->lock);

	ok = mailbox_write_locked (o, m);

	while (!ok && wait) {
		cnd_wait (&o->signal, &o->lock);
		ok = mailbox_write_locked (o, m);
	}

	mtx_unlock (&o->lock);

	if (ok)
		cnd_signal (&o->signal);

	return ok;
}

static struct message *mailbox_read_locked (struct mailbox *o)
{
	struct message *m = message_seq_dequeue (&o->queue);

	if (m != NULL)
		++o->avail;

	return m;
}

struct message *mailbox_read (struct mailbox *o, int wait)
{
	struct message *m;

	mtx_lock (&o->lock);

	m = mailbox_read_locked (o);

	while (m == NULL && wait) {
		cnd_wait (&o->signal, &o->lock);
		m = mailbox_read_locked (o);
	}

	mtx_unlock (&o->lock);

	if (m != NULL)
		cnd_signal (&o->signal);

	return m;
}
