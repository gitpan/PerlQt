/*
 * PerlQt interface to QListBoxPixmap (qlistbox.h)
 *
 * Copyright (C) 1997, Ashley Winters <jql@accessone.com>
 *
 * You may distribute under the terms of the LGPL as specified in the
 * README file
 */

#include <pqlbpixmap.h>

static const char *QListBoxPixmap_require[] = { "QPixmap", 0 };

MODULE = Qt::QListBoxPixmap	PACKAGE = QListBoxPixmap
PROTOTYPES: DISABLE

BOOT:
    pqt_class_register(
	"QListBoxPixmap",
	"QListBoxItem",
	QListBoxPixmap_require
    );
