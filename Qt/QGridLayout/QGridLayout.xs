/*
 * PerlQt interface to QGridLayout (qlayout.h)
 *
 * Copyright (C) 1997, Ashley Winters <jql@accessone.com>
 *
 * You may distribute under the terms of the LGPL as specified in the
 * README file
 */

#include <pqglayout.h>

static const char *QGridLayout_require[] = { "QWidget", 0 };

MODULE = Qt::QGridLayout     PACKAGE = QGridLayout
PROTOTYPES: DISABLE

BOOT:
    pqt_class_register(
	"QGridLayout",
	"QLayout",
	QGridLayout_require
    );
