/*
 * PerlQt interface to QListBoxText (qlistbox.h)
 *
 * Copyright (C) 1997, Ashley Winters <jql@accessone.com>
 *
 * You may distribute under the terms of the LGPL as specified in the
 * README file
 */

#include <pqlbtext.h>

MODULE = Qt::QListBoxText	PACKAGE = QListBoxText
PROTOTYPES: DISABLE

BOOT:
    pqt_class_register(
	"QListBoxText",
	"QListBoxItem"
    );
