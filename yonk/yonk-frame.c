/*
 * Yonk Configuration Template Loader helpers
 *
 * Copyright (c) 2018-2022 Alexei A. Smekalkine <ikle@ikle.ru>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#include <stdio.h>
#include <stdlib.h>

#include <dirent.h>

#include <colibri/text/string.h>
#include <yonk/conf.h>

static int yonk_unroll_one (struct json *o, const char *root)
{
	struct json *list, *body, *dopant;
	const char *class;
	int i, size;
	char *path;

	/* unroll this node */

	if (json_type (o) != JSON_DICT ||
	    (list = json_dict_get_list (o, "class")) == NULL)
		return 1;

	size = json_list_size (list);
	body = json_dict_get (o, "body");

	for (i = 0; i < size; ++i) {
		if ((class = json_list_get_string (list, i)) == NULL)
			return 0;

		path = str_printf ("%s/class/%s.json", root, class);
		if (path == NULL)
			return 0;

		dopant = json_load (path);
		free (path);

		if (dopant == NULL ||
		    (body = json_merge (body, dopant)) == NULL)
			return 0;

		if (!json_dict_set (o, "body", body)) {
			json_put (body);
			return 0;
		}
	}

	json_dict_remove (o, "class");
	return 1;
}

static int yonk_unroll_node (struct json *o, const char *root)
{
	struct json *body;
	struct json_entry *e;

	/* unroll this node */

	if (!yonk_unroll_one (o, root))
		return 0;

	/* unroll childs: get body and for each key unroll value */

	body = json_dict_get (o, "body");

	for (e = json_dict_list (body); e != NULL; e = json_entry_next (e))
		if (!yonk_unroll_node (json_entry_get (e), root))
			return 0;

	json_dict_remove (o, "class");
	return 1;
}

static struct json *yonk_load_one (const char *root, const char *from)
{
	struct json *o;
	struct json_entry *e;

	if ((o = json_load (from)) == NULL)
		return NULL;

	for (e = json_dict_list (o); e != NULL; e = json_entry_next (e))
		if (!yonk_unroll_node (json_entry_get (e), root))
			goto error;

	return o;
error:
	json_put (o);
	return NULL;
}

struct json *yonk_load_frame (const char *root)
{
	DIR *dir;
	struct dirent *de;
	struct json *o, *one, *next;
	char *path;

	if ((path = str_printf ("%s/conf", root)) == NULL)
		return NULL;

	dir = opendir (path);
	free (path);

	if (dir == NULL)
		return NULL;

	for (o = NULL; (de = readdir (dir)) != NULL;) {
		if (de->d_name[0] == '.')
			continue;

		path = str_printf ("%s/conf/%s", root, de->d_name);
		if (path == NULL)
			goto no_path;

		one = yonk_load_one (root, path);
		free (path);

		if (one == NULL)
			goto no_load;

		if ((next = json_merge (o, one)) == NULL)
			goto no_merge;

		json_put (one);
		json_put (o);
		o = next;
	}

	closedir (dir);
	return o;
no_merge:
	json_put (one);
no_load:
no_path:
	json_put (o);
	closedir (dir);
	return NULL;
}
