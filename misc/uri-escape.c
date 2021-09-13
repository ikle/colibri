/*
 * Colibri URI escape helper
 *
 * Copyright (c) 2006-2021 Alexei A. Smekalkine <ikle@ikle.ru>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <stdlib.h>
#include <string.h>
#include <wchar.h>

#include <colibri/text/uri.h>

static char allowed[128] = {
	0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,
	0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,
	0, 0, 0, 0,  0, 0, 0, 0,  0, 0, 0, 0,  0, 1, 1, 0,  /* [-.]   */
	1, 1, 1, 1,  1, 1, 1, 1,  1, 1, 0, 0,  0, 0, 0, 0,  /* [0-9]  */

	0, 1, 1, 1,  1, 1, 1, 1,  1, 1, 1, 1,  1, 1, 1, 1,  /* [A-O]  */
	1, 1, 1, 1,  1, 1, 1, 1,  1, 1, 1, 0,  0, 0, 0, 1,  /* [P-Z_] */
	0, 1, 1, 1,  1, 1, 1, 1,  1, 1, 1, 1,  1, 1, 1, 1,  /* [a-o]  */
	1, 1, 1, 1,  1, 1, 1, 1,  1, 1, 1, 0,  0, 0, 1, 0,  /* [p-z~] */
};

static char *hex = "0123456789ABCDEF";

#define put_char(a)  do {		\
	if (size > 1)			\
		*buf++ = (a), --size;	\
					\
	++total;			\
}					\
while (0)

size_t uri_escape (char *buf, size_t size, const char *p)
{
	mbstate_t mbs;
	size_t total = 0, n;

	memset (&mbs, 0, sizeof (mbs));

	while ((int) (n = mbrlen (p, MB_CUR_MAX, &mbs)) > 0) {
		if ((unsigned) *p >= sizeof (allowed)) {
			for (; n > 0; --n, ++p)
				put_char (*p);

			continue;
		}

		if (allowed[(unsigned) *p])
			put_char (*p);
		else {
			put_char ('%');
			put_char (hex[(*p >> 4) & 0xf]);
			put_char (hex[*p & 0xf]);
		}

		++p;
	}

	if (size > 0)
		*buf = '\0';

	return total;
}
