/*
 * PerlQt interface to QFileDialog (qfiledlg.h)
 *
 * Copyright (C) 1997, Ashley Winters <jql@accessone.com>
 *
 * You may distribute under the terms of the LGPL as specified in the
 * README file
 */

#include <pqfiledlg.h>

static const char *QFileDialog_require[] = { "QDir", 0 };

MODULE = Qt::QFileDialog	PACKAGE = QFileDialog	PREFIX = v_
PROTOTYPES: DISABLE

BOOT:
    pqt_class_register(
	"QFileDialog",
	"QDialog",
	QFileDialog_require
    );
