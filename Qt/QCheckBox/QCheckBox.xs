/*
 * PerlQt interface to QCheckBox (qchkbox.h)
 *
 * Copyright (C) 1997, Ashley Winters <jql@accessone.com>
 *
 * You may distribute under the terms of the LGPL as specified in the
 * README file
 */

#include <pqchkbox.h>

MODULE = Qt::QCheckBox	PACKAGE = QCheckBox	PREFIX = v_
PROTOTYPES: DISABLE

BOOT:
    pqt_class_register(
	"QCheckBox",
	"QButton"
    );
