/*
 * PerlQt interface to QMultiLineEdit (qmlined.h)
 *
 * Copyright (C) 1997, Ashley Winters <jql@accessone.com>
 *
 * You may distribute under the terms of the LGPL as specified in the
 * README file
 */

#include <pqmlined.h>

MODULE = Qt::QMultiLineEdit	PACKAGE = QMultiLineEdit	PREFIX = v_
PROTOTYPES: DISABLE

BOOT:
    pqt_class_register(
	"QMultiLineEdit",
	"QTableView"
    );
