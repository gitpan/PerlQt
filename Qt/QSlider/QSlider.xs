/*
 * PerlQt interface to QSlider (qslider.h)
 *
 * Copyright (C) 1997, Ashley Winters <jql@accessone.com>
 *
 * You may distribute under the terms of the LGPL as specified in the
 * README file
 */

#include <pqslider.h>

static struct pqt_const_hash pqt_const_hash_Tick[] = {
    { "None",  QSlider::NoMarks },
    { "Above", QSlider::Above	},
    { "Left",  QSlider::Left	},
    { "Below", QSlider::Below	},
    { "Right", QSlider::Right	},
    { "Both",  QSlider::Both	},
    { 0,       0		}
};

static struct pqt_export QSlider_export[] = {
    { "%Tick", pqt_const_hash_Tick },
    { "%Orientation", 0 },
    { 0, 0 }
};

static const char *QSlider_require[] = { "QRect", 0 };
static const char *QSlider_overload[] = { "QWidget", "QRangeControl", 0 };

MODULE = Qt::QSlider		PACKAGE = QSlider
PROTOTYPES: DISABLE

BOOT:
    pqt_class_register(
	"QSlider",
	"QWidget",
	QSlider_require,
	QSlider_export
    );
