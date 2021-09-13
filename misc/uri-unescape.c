/*
 * Colibri URI unescape helper
 *
 * Copyright (c) 2006-2021 Alexei A. Smekalkine <ikle@ikle.ru>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <colibri/text/uri.h>

static int get_xdigit (int c)
{
	if (c < '0')
		return -1;

	if (c <= '9')
		return c - '0';

	c |= 0x20;

	if (c < 'a')
		return -1;

	if (c <= 'f')
		return c - 'a' + 10;

	return -1;
}

#define put_char(a)  do {		\
	if (size > 1)			\
		*buf++ = (a), --size;	\
					\
	++total;			\
}					\
while (0)

size_t uri_unescape (char *buf, size_t size, const char *p)
{
	size_t total = 0;
	int h, l;

	while (*p != '\0')
		if (*p != '%') {
			put_char (*p);
			++p;
		}
		else {
			if ((h = get_xdigit (p[1])) < 0 ||
			    (l = get_xdigit (p[2])) < 0)
				break;

			put_char (h << 4 | l);
			p += 3;
		}

	if (size > 0)
		*buf = '\0';

	return total;
}
