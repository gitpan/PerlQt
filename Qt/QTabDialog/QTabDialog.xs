/*
 * PerlQt interface to QTabDialog (qtabdlg.h)
 *
 * Copyright (C) 1997, Ashley Winters <jql@accessone.com>
 *
 * You may distribute under the terms of the LGPL as specified in the
 * README file
 */

#include <pqtabdlg.h>

static const char *QTabDialog_require[] = { "QTab", 0 };

MODULE = Qt::QTabDialog	     PACKAGE = QTabDialog	PREFIX = v_
PROTOTYPES: DISABLE

BOOT:
    pqt_class_register(
	"QTabDialog",
	"QDialog",
	QTabDialog_require
    );
