/*
 * PerlQt interface to QPalette (qpalette.h)
 *
 * Copyright (C) 1997, Ashley Winters <jql@accessone.com>
 *
 * You may distribute under the terms of the LGPL as specified in the
 * README file
 */

#include <pqpalette.h>

static const char *QPalette_require[] = { "QColor", "QColorGroup", 0 };
static const char *QPalette_overload[] = { "==", "!=", "<<", ">>", 0 };

MODULE = Qt::QPalette		PACKAGE = QPalette
PROTOTYPES: DISABLE

BOOT:
    pqt_class_register(
	"QPalette",
	NULL,
	QPalette_require,
	0,
	QPalette_overload
    );
