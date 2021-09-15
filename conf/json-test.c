/*
 * Colibri JSON API test
 *
 * Copyright (c) 2018-2021 Alexei A. Smekalkine <ikle@ikle.ru>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <stdio.h>

#include <colibri/data/json.h>

int main (int argc, char *argv[])
{
	struct json *req, *args, *opts;
	int ok = 1;
	struct json_output *out;

	if ((req = json_dict ()) == NULL) {
		perror ("cannot create request dict");
		return 1;
	}

	if ((args = json_dict ()) == NULL) {
		perror ("cannot create arguments dict");
		return 1;
	}

	if ((opts = json_list (7)) == NULL) {
		perror ("cannot create opts list");
		return 1;
	}

	ok &= json_dict_set_int    (req, "id",    13);
	ok &= json_dict_set        (req, "error", NULL);
	ok &= json_dict_set_string (req, "mode",  "auth");
	ok &= json_dict_set_string (req, "cmd",   "ba");
	ok &= json_dict_set        (req, "args",  args);

	ok &= json_dict_set_string (args, "user",     "admin");
	ok &= json_dict_set_string (args, "password", "top-secret");
	ok &= json_dict_set        (args, "opts",     opts);

	ok &= json_list_set_bool   (opts, 0, 1);
	ok &= json_list_set_int    (opts, 1, 100500);
	ok &= json_list_set_float  (opts, 3, 3.1415926);
	ok &= json_list_set_string (opts, 4, "test string");

	if (!ok) {
		perror ("cannot build request message");
		return 1;
	}

	if ((out = json_output_open (NULL, stdout)) == NULL) {
		perror ("cannot output JSON stream");
		return 1;
	}

	json_write (out, req);
	printf ("\n");
	return 0;
}
