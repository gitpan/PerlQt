/*
 * PerlQt interface to QImage (qimage.h)
 *
 * Copyright (C) 1997, Ashley Winters <jql@accessone.com>
 *
 * You may distribute under the terms of the LGPL as specified in the
 * README file
 */

#include <pqimage.h>

static struct pqt_const_hash pqt_const_hash_Endian[] = {
    { "Ignore", QImage::IgnoreEndian },
    { "Big",	QImage::BigEndian    },
    { "Little", QImage::LittleEndian },
    { 0,	0		     }
};

static const char *QImage_require[] = { "QPixmap", "QRect", "QSize", 0 };

static struct pqt_export QImage_export[] = {
    { "%Endian", pqt_const_hash_Endian },
    { 0, 0 }
};

MODULE = Qt::QImage	     PACKAGE = QImage
PROTOTYPES: DISABLE

BOOT:
    pqt_class_register(
	"QImage",
	NULL,
	QImage_require,
	QImage_export
    );
