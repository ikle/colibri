/*
 * Yonk Configuration Template Loader test
 *
 * Copyright (c) 2018-2022 Alexei A. Smekalkine <ikle@ikle.ru>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <stdio.h>

#include <yonk/conf.h>

int main (int argc, char *argv[])
{
	struct json *frame;

	if (argc != 2) {
		fprintf (stderr, "usage:\n\t"
				 "json-merge <conf-root>\n");
		return 1;
	}

	if ((frame = yonk_load_frame (argv[1])) == NULL) {
		fprintf (stderr, "E: cannot load configuration template\n");
		return 1;
	}

	if (!json_save (frame, NULL)) {
		perror ("E: cannot output JSON template");
		return 1;
	}

	printf ("\n");

	json_put (frame);
	return 0;
}
