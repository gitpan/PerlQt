/*
 * PerlQt interface to QTab (qtabbar.h)
 *
 * Copyright (C) 1997, Ashley Winters <jql@accessone.com>
 *
 * You may distribute under the terms of the LGPL as specified in the
 * README file
 */

#include <pqtab.h>

// label(), setLabel(), boundingRect(), setBoundingRect(),
// enabled(), setEnabled(), id(), setId()

static const char *QTab_require[] = { "QRect", 0 };

MODULE = Qt::QTab		PACKAGE = QTab
PROTOTYPES: DISABLE

BOOT:
    pqt_class_register(
	"QTab",
	NULL,
	QTab_require
    );
