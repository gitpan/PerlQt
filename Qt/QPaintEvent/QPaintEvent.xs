/*
 * PerlQt interface to QPaintEvent (qevent.h)
 *
 * Copyright (C) 1997, Ashley Winters <jql@accessone.com>
 *
 * You may distribute under the terms of the LGPL as specified in the
 * README file
 */

#include <pqpaintev.h>

static const char *QPaintEvent_require[] = { "QRect", 0 };

MODULE = Qt::QPaintEvent	PACKAGE = QPaintEvent
PROTOTYPES: DISABLE

BOOT:
    pqt_class_register(
	"QPaintEvent",
	"QEvent",
	QPaintEvent_require
    );
