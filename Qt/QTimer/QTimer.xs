/*
 * PerlQt interface to QTimer (qtimer.h)
 *
 * Copyright (C) 1997, Ashley Winters <jql@accessone.com>
 *
 * You may distribute under the terms of the LGPL as specified in the
 * README file
 */

#include <pqtimer.h>

MODULE = Qt::QTimer		PACKAGE = QTimer
PROTOTYPES: DISABLE

BOOT:
    pqt_class_register(
	"QTimer",
	"QObject"
    );
