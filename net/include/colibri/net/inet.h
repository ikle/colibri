/*
 * Colibri Internet address helpers
 *
 * Copyright (c) 2017-2021 Alexei A. Smekalkine <ikle@ikle.ru>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#ifndef COLIBRI_NET_INET_H
#define COLIBRI_NET_INET_H  1

#include <colibri/net/ipv4.h>
#include <colibri/net/ipv6.h>

struct ip_port_range {
	unsigned short start, stop;
};

int inet_get_proto   (const char *from, unsigned *to);
int inet_get_service (const char *from, unsigned *to);
int inet_get_port_range (const char *from, struct ip_port_range *to);

#endif  /* COLIBRI_NET_INET_H */
