/*
 * PerlQt interface to QPicture (qpicture.h)
 *
 * Copyright (C) 1997, Ashley Winters <jql@accessone.com>
 *
 * You may distribute under the terms of the LGPL as specified in the
 * README file
 */

#include <pqpicture.h>

static const char *QPicture_require[] = { "QPainter", 0 };

MODULE = Qt::QPicture		PACKAGE = QPicture
PROTOTYPES: DISABLE

BOOT:
    pqt_class_register(
	"QPicture",
	"QPaintDevice",
	QPicture_require
    );
