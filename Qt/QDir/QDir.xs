/*
 * PerlQt interface to QDir (qdir.h)
 *
 * Copyright (C) 1997, Ashley Winters <jql@accessone.com>
 *
 * You may distribute under the terms of the LGPL as specified in the
 * README file
 */

#include <pqdir.h>

MODULE = Qt::QDir	PACKAGE = QDir
PROTOTYPES: DISABLE

BOOT:
    pqt_class_register("QDir");
