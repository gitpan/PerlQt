/*
 * PerlQt interface to QColor (qcolor.h)
 *
 * Copyright (C) 1997, Ashley Winters <jql@accessone.com>
 *
 * You may distribute under the terms of the LGPL as specified in the
 * README file
 */

#include <pqcolor.h>

static const char *qcolor_str = "QColor";

static pqt_const_object pqt_const_QColor_objects[] = {
    { "color0",		&color0,	qcolor_str },
    { "color1",		&color1,	qcolor_str },
    { "black",		&black,		qcolor_str },
    { "white",		&white,		qcolor_str },
    { "darkGray",	&darkGray,	qcolor_str },
    { "gray",		&gray,		qcolor_str },
    { "lightGray",	&lightGray,	qcolor_str },
    { "red",		&red,		qcolor_str },
    { "green",		&green,		qcolor_str },
    { "blue",		&blue,		qcolor_str },
    { "cyan",		&cyan,		qcolor_str },
    { "magenta",	&magenta,	qcolor_str },
    { "yellow",		&yellow,	qcolor_str },
    { "darkRed",	&darkRed,	qcolor_str },
    { "darkGreen",	&darkGreen,	qcolor_str },
    { "darkBlue",	&darkBlue,	qcolor_str },
    { "darkCyan",	&darkCyan,	qcolor_str },
    { "darkMagenta",	&darkMagenta,	qcolor_str },
    { "darkYellow",	&darkYellow,	qcolor_str },
    { 0,		0,		0	   }
};
static struct pqt_export QColor_export[] = {
    { "%$Color", pqt_const_QColor_objects }, { 0, 0 }
};

MODULE = Qt::QColor	PACKAGE = QColor
PROTOTYPES: DISABLE

BOOT:
    pqt_class_register(
	"QColor",
	NULL,
	NULL,
	QColor_export
    );
