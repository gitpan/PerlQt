/*
 * PerlQt interface to QMenuItem (qmenudta.h)
 *
 * Copyright (C) 1997, Ashley Winters <jql@accessone.com>
 *
 * You may distribute under the terms of the LGPL as specified in the
 * README file
 */

#include <pqmenuitem.h>

static const char *QMenuItem_require[] = {
    "QPixmap",
    "QPopupMenu",
    "QSignal",
    0
};

MODULE = Qt::QMenuItem	PACKAGE = QMenuItem
PROTOTYPES: DISABLE

BOOT:
    pqt_class_register(
	"QMenuItem",
	NULL,
	QMenuItem_require
    );
