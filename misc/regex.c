/*
 * Colibri regular expression helpers
 *
 * Copyright (c) 2011-2021 Alexei A. Smekalkine <ikle@ikle.ru>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <stddef.h>

#include <regex.h>

#include <colibri/text/regex.h>

int regex_match (const char *re, const char *value)
{
	regex_t preg;
	int ret;

	if (regcomp (&preg, re, REG_EXTENDED | REG_NOSUB) != 0)
		return 0;

	ret = regexec (&preg, value, 0, NULL, 0) == 0;

	regfree (&preg);
	return ret;
}
