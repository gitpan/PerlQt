/*
 * PerlQt interface to QMessageBox (qmsgbox.h)
 *
 * Copyright (C) 1997, Ashley Winters <jql@accessone.com>
 *
 * You may distribute under the terms of the LGPL as specified in the
 * README file
 */

#include <pqmsgbox.h>

static struct pqt_const_hash pqt_const_hash_Icon[] = {
    { "None",	     QMessageBox::NoIcon      },
    { "Information", QMessageBox::Information },
    { "Warning",     QMessageBox::Warning     },
    { "Critical",    QMessageBox::Critical    },
    { 0,	     0			      }
};

static struct pqt_const_hash pqt_const_hash_Message[] = {
    { "Ok",	    QMessageBox::Ok	    },
    { "Cancel",     QMessageBox::Cancel     },
    { "Yes",	    QMessageBox::Yes	    },
    { "No",	    QMessageBox::No	    },
    { "Abort",      QMessageBox::Abort      },
    { "Retry",      QMessageBox::Retry      },
    { "Ignore",     QMessageBox::Ignore     },
    { "ButtonMask", QMessageBox::ButtonMask },
    { "Default",    QMessageBox::Default    },
    { "Escape",     QMessageBox::Escape     },
    { "FlagMask",   QMessageBox::FlagMask   },
    { 0,	    0			    }
};

static struct pqt_export QMessageBox_export[] = {
    { "%Icon",    pqt_const_hash_Icon	 },
    { "%Message", pqt_const_hash_Message },
    { 0, 0 }
};

static const char *QMessageBox_require[] = { "QPixmap", 0 };

MODULE = Qt::QMessageBox     PACKAGE = QMessageBox	PREFIX = v_
PROTOTYPES: DISABLE

BOOT:
    pqt_class_register(
	"QMessageBox",
	"QDialog",
	QMessageBox_require,
	QMessageBox_export
    );
