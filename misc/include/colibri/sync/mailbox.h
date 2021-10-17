/*
 * Colibri message mailbox
 *
 * Copyright (c) 2014-2021 Alexei A. Smekalkine <ikle@ikle.ru>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#ifndef COLIBRI_SYNC_MAILBOX_H
#define COLIBRI_SYNC_MAILBOX_H  1

#include <stddef.h>

struct message {
	struct message *next;
};

static inline void message_init (struct message *o)
{
	o->next = NULL;
}

typedef void message_free (struct message *m);

struct mailbox *mailbox_alloc (int limit, message_free *free);
void mailbox_free (struct mailbox *o);

int mailbox_write (struct mailbox *o, struct message *m, int wait);
struct message *mailbox_read (struct mailbox *o, int wait);

#endif  /* COLIBRI_SYNC_MAILBOX_H */
