/*
 * PerlQt interface to QRangeControl (qrangect.h)
 *
 * Copyright (C) 1997, Ashley Winters <jql@accessone.com>
 *
 * You may distribute under the terms of the LGPL as specified in the
 * README file
 */

#include <pqrangect.h>

MODULE = Qt::QRangeControl   PACKAGE = QRangeControl	PREFIX = v_
PROTOTYPES: DISABLE

BOOT:
    pqt_class_register(
	"QRangeControl"
    );
