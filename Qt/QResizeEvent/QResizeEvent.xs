/*
 * PerlQt interface to QResizeEvent (qevent.h)
 *
 * Copyright (C) 1997, Ashley Winters <jql@accessone.com>
 *
 * You may distribute under the terms of the LGPL as specified in the
 * README file
 */

#include <pqresizeev.h>

static const char *QResizeEvent_require[] = { "QSize", 0 };

MODULE = Qt::QResizeEvent	PACKAGE = QResizeEvent
PROTOTYPES: DISABLE

BOOT:
    pqt_class_register(
	"QResizeEvent",
	"QEvent",
	QResizeEvent_require
    );
