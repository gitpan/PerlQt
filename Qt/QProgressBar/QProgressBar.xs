/*
 * PerlQt interface to QProgressBar (qprogbar.h)
 *
 * Copyright (C) 1997, Ashley Winters <jql@accessone.com>
 *
 * You may distribute under the terms of the LGPL as specified in the
 * README file
 */

#include <pqprogbar.h>

MODULE = Qt::QProgressBar    PACKAGE = QProgressBar	PREFIX = v_
PROTOTYPES: DISABLE

BOOT:
    pqt_class_register(
	"QProgressBar",
	"QFrame"
    );
