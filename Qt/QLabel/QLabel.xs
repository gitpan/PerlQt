/*
 * PerlQt interface to QLabel (qlabel.h)
 *
 * Copyright (C) 1997, Ashley Winters <jql@accessone.com>
 *
 * You may distribute under the terms of the LGPL as specified in the
 * README file
 */

#include <pqlabel.h>

static const char *QLabel_require[] = { "QMovie", "QPixmap", 0 };

MODULE = Qt::QLabel	PACKAGE = QLabel	PREFIX = v_
PROTOTYPES: DISABLE

BOOT:
    pqt_class_register(
	"QLabel",
	"QFrame",
	QLabel_require
    );
