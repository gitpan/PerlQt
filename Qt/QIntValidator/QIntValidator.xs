/*
 * PerlQt interface to QIntValidator (qvalidator.h)
 *
 * Copyright (C) 1997, Ashley Winters <jql@accessone.com>
 *
 * You may distribute under the terms of the LGPL as specified in the
 * README file
 */

#include <pqivalidator.h>

MODULE = Qt::QIntValidator   PACKAGE = QIntValidator	PREFIX = v_
PROTOTYPES: DISABLE

BOOT:
    pqt_class_register(
	"QIntValidator",
	"QValidator"
    );
