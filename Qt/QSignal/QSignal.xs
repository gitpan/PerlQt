/*
 * PerlQt interface to QSignal (qsignal.h)
 *
 * Copyright (C) 1997, Ashley Winters <jql@accessone.com>
 *
 * You may distribute under the terms of the LGPL as specified in the
 * README file
 */

#include <pqsignal.h>

MODULE = Qt::QSignal		PACKAGE = QSignal
PROTOTYPES: DISABLE

BOOT:
    pqt_class_register(
	"QSignal",
	"QObject"
    );
