/*
 * PerlQt interface to QTimerEvent (qevent.h)
 *
 * Copyright (C) 1997, Ashley Winters <jql@accessone.com>
 *
 * You may distribute under the terms of the LGPL as specified in the
 * README file
 */

#include <pqtimerev.h>

MODULE = Qt::QTimerEvent	PACKAGE = QTimerEvent
PROTOTYPES: DISABLE

BOOT:
    pqt_class_register(
	"QTimerEvent",
	"QEvent"
    );
