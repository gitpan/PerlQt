/*
 * PerlQt interface to QAccel (qaccel.h)
 *
 * Copyright (C) 1997, Ashley Winters <jql@accessone.com>
 *
 * You may distribute under the terms of the LGPL as specified in the
 * README file
 */

#include <pqaccel.h>

static const char *QAccel_require[] = { "QWidget", 0 };
static struct pqt_export QAccel_export[] = { { "%Key", 0 }, { 0, 0 } };

MODULE = Qt::QAccel	PACKAGE = QAccel	PREFIX = v_
PROTOTYPES: DISABLE

BOOT:
    pqt_class_register(
	"QAccel",
	"QObject",
	QAccel_require,
	QAccel_export
    );
