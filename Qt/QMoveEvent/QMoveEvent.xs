/*
 * PerlQt interface to QMoveEvent (qevent.h)
 *
 * Copyright (C) 1997, Ashley Winters <jql@accessone.com>
 *
 * You may distribute under the terms of the LGPL as specified in the
 * README file
 */

#include <pqmoveev.h>

static const char *QMoveEvent_require[] = { "QPoint", 0 };

MODULE = Qt::QMoveEvent	     PACKAGE = QMoveEvent
PROTOTYPES: DISABLE

BOOT:
    pqt_class_register(
	"QMoveEvent",
	"QEvent",
	QMoveEvent_require
    );
