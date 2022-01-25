/*
 * Yonk Configuration API
 *
 * Copyright (c) 2018-2022 Alexei A. Smekalkine <ikle@ikle.ru>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#ifndef YONK_CONF_H
#define YONK_CONF_H  1

#include <colibri/data/json.h>

struct json *yonk_load_frame (const char *root);

#endif  /* YONK_CONF_H */
