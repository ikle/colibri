/*
 * Colibri URI escape helper test
 *
 * Copyright (c) 2011-2021 Alexei A. Smekalkine <ikle@ikle.ru>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <locale.h>
#include <stdio.h>

#include <colibri/text/uri.h>

static const char *sample[] = {
	"test string",
	"with \" quote character and with \\ — backslash",
	"Се вѣтри, Стрибожи внуци, вѣютъ съ моря стрѣлами на храбрыя пълкы "
	"Игоревы.",
	"Не лѣпо ли ны бяшетъ, братіе, начяти старыми словесы трудныхъ "
	"повѣстій о пълку Игоревѣ, Игоря Святъславлича?",
	NULL
};

int main (int argc, char *argv[])
{
	char buf[180];
	size_t i, n;

	setlocale (LC_ALL, "C.UTF-8");

	for (i = 0; sample[i] != NULL; ++i) {
		n = uri_escape (buf, sizeof (buf), sample[i]);

		printf ("sample %zu, result length = %zu\n", i, n);

		if (n < sizeof (buf))
			printf ("sample %zu, result = %s\n", i, buf);
		else
			printf ("sample %zu, overflow\n", i);
	}

	return 0;
}
