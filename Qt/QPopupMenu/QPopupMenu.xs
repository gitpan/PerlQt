/*
 * PerlQt interface to QPopupMenu (qpopmenu.h)
 *
 * Copyright (C) 1997, Ashley Winters <jql@accessone.com>
 *
 * You may distribute under the terms of the LGPL as specified in the
 * README file
 */

#include <pqpopmenu.h>

static const char *QPopupMenu_isa[] = { "QTableView", "QMenuData", 0 };
static const char *QPopupMenu_require[] = { "QPoint", 0 };

MODULE = Qt::QPopupMenu	    PACKAGE = QPopupMenu	PREFIX = v_
PROTOTYPES: DISABLE

BOOT:
    pqt_class_register(
	"QPopupMenu",
	QPopupMenu_isa,
	QPopupMenu_require
    );
