/*
 * Colibri error helpers
 *
 * Copyright (c) 2018-2021 Alexei A. Smekalkine <ikle@ikle.ru>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#ifndef COLIBRI_CONF_ERROR_H
#define COLIBRI_CONF_ERROR_H  1

enum conf_error {
	CONF_SUCCESS		= 0,
	CONF_ERROR_GENERIC	= 1,
	CONF_ERROR_ACCESS	= 2,
	CONF_ERROR_BUSY		= 3,
	CONF_ERROR_TIMEOUT	= 4,
	CONF_ERROR_SYNTAX	= 10,
	CONF_ERROR_SEMANTIC	= 11,
};

#endif  /* COLIBRI_CONF_ERROR_H */
