/*
 * PerlQt interface to QListBox (qlistbox.h)
 *
 * Copyright (C) 1997, Ashley Winters <jql@accessone.com>
 *
 * You may distribute under the terms of the LGPL as specified in the
 * README file
 */

#include <pqlistbox.h>

static const char *QListBox_require[] = {
    "QListBoxPixmap",
    "QListBoxText",
    "QPixmap",
    0
};

MODULE = Qt::QListBox	PACKAGE = QListBox	PREFIX = v_
PROTOTYPES: DISABLE

BOOT:
    pqt_class_register(
	"QListBox",
	"QTableView",
	QListBox_require
    );
