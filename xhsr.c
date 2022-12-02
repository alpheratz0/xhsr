/*
	Copyright (C) 2022 <alpheratz99@protonmail.com>

	This program is free software; you can redistribute it and/or modify it under
	the terms of the GNU General Public License version 2 as published by the
	Free Software Foundation.

	This program is distributed in the hope that it will be useful, but WITHOUT ANY
	WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
	FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.

	You should have received a copy of the GNU General Public License along with
	this program; if not, write to the Free Software Foundation, Inc., 59 Temple
	Place, Suite 330, Boston, MA 02111-1307 USA

*/

#include <stdio.h>
#include <stdlib.h>
#include <xcb/xcb.h>
#include <xcb/xproto.h>
#include <stdarg.h>

static void
die(const char *fmt, ...)
{
	va_list args;

	fputs("xhsr: ", stderr);
	va_start(args, fmt);
	vfprintf(stderr, fmt, args);
	va_end(args);
	fputc('\n', stderr);
	exit(1);
}

static void
version(void)
{
	puts("xhsr version "VERSION);
	exit(0);
}

static void
xhsr(void)
{
	xcb_connection_t *conn;
	xcb_screen_iterator_t iter;
	xcb_screen_t *screen;
	xcb_query_pointer_cookie_t qpc;
	xcb_query_pointer_reply_t *qpr;
	xcb_generic_error_t *error;

	if (xcb_connection_has_error(conn = xcb_connect(NULL, NULL)))
		die("can't open display");

	iter = xcb_setup_roots_iterator(xcb_get_setup(conn));

	if (iter.rem == 0)
		die("no screen found");

	screen = iter.data;
	qpc = xcb_query_pointer(conn, screen->root);
	qpr = xcb_query_pointer_reply(conn, qpc, &error);

	if (NULL != error)
		die("xcb_query_pointer failed with error code: %hhu",
			error->error_code);

	printf("0x%x\n", qpr->root);

	free(qpr);
	xcb_disconnect(conn);
}

int
main(int argc, char **argv)
{
	while (++argv, --argc > 0) {
		if ((*argv)[0] == '-' && (*argv)[1] != '\0' && (*argv)[2] == '\0') {
			switch ((*argv)[1]) {
				case 'v': version(); break;
				default: die("invalid option %s", *argv); break;
			}
		} else {
			die("unexpected argument: %s", *argv);
		}
	}

	xhsr();

	return 0;
}
