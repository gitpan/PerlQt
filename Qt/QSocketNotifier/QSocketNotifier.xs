/*
 * PerlQt interface to QSocketNotifier (qsocknot.h)
 *
 * Copyright (C) 1997, Ashley Winters <jql@accessone.com>
 *
 * You may distribute under the terms of the LGPL as specified in the
 * README file
 */

#include <pqsocknot.h>

MODULE = Qt::QSocketNotifier	PACKAGE = QSocketNotifier	PREFIX = v_
PROTOTYPES: DISABLE

BOOT:
    pqt_class_register(
	"QSocketNotifier",
	"QObject"
    );
