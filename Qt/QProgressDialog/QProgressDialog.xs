/*
 * PerlQt interface to QProgressDialog (qprogdlg.h)
 *
 * Copyright (C) 1997, Ashley Winters <jql@accessone.com>
 *
 * You may distribute under the terms of the LGPL as specified in the
 * README file
 */

#include <pqprogdlg.h>

static const char *QProgressDialog_require[] = {
    "QLabel",
    "QProgressBar",
    "QPushButton",
    0
};

MODULE = Qt::QProgressDialog	 PACKAGE = QProgressDialog	PREFIX = v_
PROTOTYPES: DISABLE

BOOT:
    pqt_class_register(
	"QProgressDialog",
	"QSemiModal",
	QProgressDialog_require
    );
