/*
 * PerlQt interface to QMovie (qmovie.h)
 *
 * Copyright (C) 1997, Ashley Winters <jql@accessone.com>
 *
 * You may distribute under the terms of the LGPL as specified in the
 * README file
 */

#include <pqmovie.h>

static struct pqt_const_hash pqt_const_hash_Status[] = {
    { "SourceEmpty",	    QMovie::SourceEmpty		},
    { "UnrecognizedFormat", QMovie::UnrecognizedFormat	},
    { "Paused",		    QMovie::Paused		},
    { "EndOfFrame",	    QMovie::EndOfFrame		},
    { "EndOfLoop",	    QMovie::EndOfLoop		},
    { "EndOfMovie",	    QMovie::EndOfMovie		},
    { "SpeedChanged",	    QMovie::SpeedChanged	},
    { 0,	  	    0				}
};

static struct pqt_export QMovie_export[] = {
    { "%Status", pqt_const_hash_Status }, { 0, 0 }
};

static const char *QMovie_require[] = {
    "QColor",
    "QObject",
    "QPixmap",
    "QRect",
    0
};

MODULE = Qt::QMovie		PACKAGE = QMovie
PROTOTYPES: DISABLE

BOOT:
    pqt_class_register(
	"QMovie",
	NULL,
	QMovie_require,
	QMovie_export
    );
