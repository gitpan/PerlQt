/*
 * PerlQt interface to QListBoxItem (qlistbox.h)
 *
 * Copyright (C) 1997, Ashley Winters <jql@accessone.com>
 *
 * You may distribute under the terms of the LGPL as specified in the
 * README file
 */

#include <pqlbitem.h>

static const char *QListBoxItem_require[] = { "QListBox", "QPixmap", 0 };

MODULE = Qt::QListBoxItem	PACKAGE = QListBoxItem
PROTOTYPES: DISABLE

BOOT:
    pqt_class_register(
	"QListBoxItem",
	NULL,
	QListBoxItem_require
    );
