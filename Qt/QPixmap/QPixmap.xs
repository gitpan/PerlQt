/*
 * PerlQt interface to QPixmap (qpixmap.h)
 *
 * Copyright (C) 1997, Ashley Winters <jql@accessone.com>
 *
 * You may distribute under the terms of the LGPL as specified in the
 * README file
 */

#include <pqpixmap.h>

static const char *QPixmap_require[] = {
    "QColor",
    "QBitmap",
    "QImage",
    "QPoint",
    "QRect",
    "QSize",
    "QWidget",
    "QWMatrix",
    0
};

static const char *QPixmap_overload[] = { "<<", ">>", 0 };

MODULE = Qt::QPixmap		PACKAGE = QPixmap
PROTOTYPES: DISABLE

BOOT:
    pqt_class_register(
	"QPixmap",
	"QWidget",
	QPixmap_require,
	0,
	QPixmap_overload
    );
