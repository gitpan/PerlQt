/*
 * PerlQt interface to QTabBar (qtabbar.h)
 *
 * Copyright (C) 1997, Ashley Winters <jql@accessone.com>
 *
 * You may distribute under the terms of the LGPL as specified in the
 * README file
 */

#include <pqtabbar.h>

static struct pqt_const_hash pqt_const_hash_TabShape[] = {
    { "RoundedAbove",	 QTabBar::RoundedAbove	  },
    { "RoundedBelow",	 QTabBar::RoundedBelow	  },
    { "TriangularAbove", QTabBar::TriangularAbove },
    { "TriangularBelow", QTabBar::TriangularBelow },
    { 0,		 0			  }
};

static struct pqt_export QTabBar_export[] = {
    { "%TabShape", pqt_const_hash_TabShape }, { 0, 0 }
};

static const char *QTabBar_require[] = { "QTab", 0 };

MODULE = Qt::QTabBar		PACKAGE = QTabBar	PREFIX = v_
PROTOTYPES: DISABLE

BOOT:
    pqt_class_register(
	"QTabBar",
	"QWidget",
	QTabBar_require,
	QTabBar_export
    );
