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
	struct json_output *out;

	if (argc != 2) {
		fprintf (stderr, "usage:\n\t"
				 "json-merge <conf-root>\n");
		return 1;
	}

	if ((frame = yonk_load_frame (argv[1])) == NULL) {
		fprintf (stderr, "E: cannot load configuration template\n");
		return 1;
	}

	if ((out = json_output_open (NULL, stdout)) == NULL) {
		perror ("E: cannot output JSON template");
		return 1;
	}

	json_write (out, frame);
	printf ("\n");

	json_output_close (out);
	json_put (frame);
	return 0;
}
