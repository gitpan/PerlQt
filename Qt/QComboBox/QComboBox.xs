/*
 * PerlQt interface to QComboBox (qcombo.h)
 *
 * Copyright (C) 1997, Ashley Winters <jql@accessone.com>
 *
 * You may distribute under the terms of the LGPL as specified in the
 * README file
 */

#include <pqcombo.h>

static const char *QComboBox_require[] = { "QPixmap", 0 };
static struct pqt_const_hash pqt_const_hash_InsertionPolicy[] = {
    { "None",	 QComboBox::NoInsertion	  },
    { "Top",	 QComboBox::AtTop	  },
    { "Current", QComboBox::AtCurrent	  },
    { "Bottom",  QComboBox::AtBottom	  },
    { "After",	 QComboBox::AfterCurrent  },
    { "Before",	 QComboBox::BeforeCurrent },
    { 0,	 0			  }
};
static struct pqt_export QComboBox_export[] = {
    { "%InsertionPolicy", pqt_const_hash_InsertionPolicy }, { 0, 0 }
};

MODULE = Qt::QComboBox	PACKAGE = QComboBox	PREFIX = v_
PROTOTYPES: DISABLE

BOOT:
    pqt_class_register(
	"QComboBox",
	"QWidget",
	QComboBox_require,
	QComboBox_export
    );
