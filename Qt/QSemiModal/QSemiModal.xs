/*
 * PerlQt interface to QSemiModal (qsemimodal.h)
 *
 * Copyright (C) 1997, Ashley Winters <jql@accessone.com>
 *
 * You may distribute under the terms of the LGPL as specified in the
 * README file
 */

#include <pqsemimodal.h>

MODULE = Qt::QSemiModal	     PACKAGE = QSemiModal	PREFIX = v_
PROTOTYPES: DISABLE

BOOT:
    pqt_class_register(
	"QSemiModal",
	"QWidget"
    );
