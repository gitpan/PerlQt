/*
 * PerlQt interface to QPixmapCache (qpmcache.h)
 *
 * Copyright (C) 1997, Ashley Winters <jql@accessone.com>
 *
 * You may distribute under the terms of the LGPL as specified in the
 * README file
 */

#include <pqpmcache.h>

static const char *QPixmapCache_require[] = { "QPixmap", 0 };

MODULE = Qt::QPixmapCache	PACKAGE = QPixmapCache
PROTOTYPES: DISABLE

BOOT:
    pqt_class_register(
	"QPixmapCache",
	NULL,
	QPixmapCache_require
    );
