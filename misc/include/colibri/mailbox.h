/*
 * Colibri message mailbox
 *
 * Copyright (c) 2014-2021 Alexei A. Smekalkine <ikle@ikle.ru>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#ifndef COLIBRI_MAILBOX_H
#define COLIBRI_MAILBOX_H  1

#include <stddef.h>

struct message {
	struct message *next;
};

typedef void message_free (struct message *m);

struct mailbox *mailbox_alloc (message_free *free);
void mailbox_free (struct mailbox *o);

void mailbox_send (struct mailbox *o, struct message *m);
struct message *mailbox_recv (struct mailbox *o, int wait);

#endif  /* COLIBRI_MAILBOX_H */
