/*
 * PerlQt interface to QMenuData (qmenudta.h)
 *
 * Copyright (C) 1997, Ashley Winters <jql@accessone.com>
 *
 * You may distribute under the terms of the LGPL as specified in the
 * README file
 */

#include <pqmenudta.h>

static const char *QMenuData_require[] = {
    "QMenuItem",
    "QObject",
    "QPixmap",
    "QPopupMenu",
    0
};

MODULE = Qt::QMenuData	PACKAGE = QMenuData	PREFIX = v_
PROTOTYPES: DISABLE

BOOT:
    pqt_class_register(
	"QMenuData",
	NULL,
	QMenuData_require
    );
