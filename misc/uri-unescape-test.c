/*
 * Colibri URI unescape helper test
 *
 * Copyright (c) 2011-2021 Alexei A. Smekalkine <ikle@ikle.ru>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <stdio.h>

#include <colibri/text/uri.h>

static const char *sample[] = {
	"test%20string",
	"with%20%22%20quote%20character%20and%20with%20%5C%20—%20backslash",
	"Се%20вѣтри%2C%20Стрибожи%20внуци%2C%20вѣютъ%20съ%20моря%20стрѣлами"
	"%20на%20храбрыя%20пълкы%20Игоревы.",
	"Не лѣпо ли ны бяшетъ, братіе, начяти старыми словесы трудныхъ "
	"повѣстій о пълку Игоревѣ, Игоря Святъславлича?",
	NULL
};

int main (int argc, char *argv[])
{
	char buf[180];
	size_t i, n;

	for (i = 0; sample[i] != NULL; ++i) {
		n = uri_unescape (buf, sizeof (buf), sample[i]);

		printf ("sample %zu, result length = %zu\n", i, n);

		if (n < sizeof (buf))
			printf ("sample %zu, result = %s\n", i, buf);
		else
			printf ("sample %zu, overflow\n", i);
	}

	return 0;
}
