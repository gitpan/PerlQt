/*
 * PerlQt interface to QPaintDeviceMetrics (qpdevmet.h)
 *
 * Copyright (C) 1997, Ashley Winters <jql@accessone.com>
 *
 * You may distribute under the terms of the LGPL as specified in the
 * README file
 */

#include <pqpdevmet.h>

static const char *QPaintDeviceMetrics_require[] = { "QPaintDevice", 0 };

MODULE = Qt::QPaintDeviceMetrics PACKAGE = QPaintDeviceMetrics
PROTOTYPES: DISABLE

BOOT:
    pqt_class_register(
	"QPaintDeviceMetrics",
	NULL,
	QPaintDeviceMetrics_require
    );
