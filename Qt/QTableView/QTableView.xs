/*
 * PerlQt interface to QTableView (qtablevw.h)
 *
 * Copyright (C) 1997, Ashley Winters <jql@accessone.com>
 *
 * You may distribute under the terms of the LGPL as specified in the
 * README file
 */

#include <pqtablevw.h>

MODULE = Qt::QTableView	     PACKAGE = QTableView	PREFIX = v_
PROTOTYPES: DISABLE

BOOT:
    pqt_class_register(
	"QTableView",
	"QFrame"
    );
