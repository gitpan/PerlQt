/*
 * PerlQt interface to QBitmap (qbitmap.h)
 *
 * Copyright (C) 1997, Ashley Winters <jql@accessone.com>
 *
 * You may distribute under the terms of the LGPL as specified in the
 * README file
 */

#include <pqbitmap.h>

static const char *QBitmap_require[] = { "QImage", "QSize", "QWMatrix", 0 };

MODULE = Qt::QBitmap	PACKAGE = QBitmap
PROTOTYPES: DISABLE

BOOT:
    pqt_class_register(
	"QBitmap",
	"QPixmap",
	QBitmap_require
    );
