/*
 * PerlQt interface to QRadioButton (qradiobt.h)
 *
 * Copyright (C) 1997, Ashley Winters <jql@accessone.com>
 *
 * You may distribute under the terms of the LGPL as specified in the
 * README file
 */

#include <pqradiobt.h>

MODULE = Qt::QRadioButton    PACKAGE = QRadioButton	PREFIX = v_
PROTOTYPES: DISABLE

BOOT:
    pqt_class_register(
	"QRadioButton",
	"QButton"
    );
