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
	message_free *free;
	struct message_seq queue;
	mtx_t lock;
	cnd_t signal;
};

struct mailbox *mailbox_alloc (message_free *free)
{
	struct mailbox *o;

	if ((o = malloc (sizeof (*o))) == NULL)
		return NULL;

	o->free = free;

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

void mailbox_send (struct mailbox *o, struct message *m)
{
	mtx_lock (&o->lock);

	message_seq_enqueue (&o->queue, m);

	mtx_unlock (&o->lock);
}

struct message *mailbox_recv (struct mailbox *o, int wait)
{
	struct message *m;

	mtx_lock (&o->lock);

	m = message_seq_dequeue (&o->queue);

	if (m == NULL && wait) {
		cnd_wait (&o->signal, &o->lock);
		m = message_seq_dequeue (&o->queue);
	}

	mtx_unlock (&o->lock);

	return m;
}
