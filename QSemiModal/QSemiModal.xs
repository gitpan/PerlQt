/*
 * PerlQt interface to qsemimodal.h
 *
 * Copyright (C) 1997, Ashley Winters <jql@accessone.com>
 *
 * You may distribute under the terms of the LGPL as specified in the
 * README file
 */

#include "psemimodal.h"

MODULE = QSemiModal		PACKAGE = QSemiModal

PROTOTYPES: DISABLE

PSemiModal *
PSemiModal::new(parent = 0, name = 0, modal = FALSE, f = 0)
    QWidget *parent
    char *name
    bool modal
    WFlags f

void
QSemiModal::DESTROY()
    CODE:
    if(want_destroy(ST(0)))
        delete THIS;

MODULE = QSemiModal	PACKAGE = QSemiModal	PREFIX = virtual_

void
pSemiModal::virtual_move(...)
    CASE: items > 2
        PREINIT:
        int x = SvIV(ST(1));
        int y = SvIV(ST(2));
        CODE:
        THIS->virtual_move(x, y);
    CASE: items > 1
        PREINIT:
        QPoint *point = pextract(QPoint, 1);
        CODE:
        THIS->QSemiModal::move(*point);

void
pSemiModal::virtual_resize(...)
    CASE: items > 2
        PREINIT:
        int w = SvIV(ST(1));
        int h = SvIV(ST(2));
        CODE:
        THIS->virtual_resize(w, h);
    CASE: items > 1
        PREINIT:
        QSize *size = pextract(QSize, 1);
        CODE:
        THIS->QSemiModal::resize(*size);

void
pSemiModal::virtual_setGeometry(...)
    CASE: items > 4
        PREINIT:
        int x = SvIV(ST(1));
        int y = SvIV(ST(2));
        int w = SvIV(ST(3));
        int h = SvIV(ST(4));
        CODE:
        THIS->virtual_setGeometry(x, y, w, h);
    CASE: items > 1
        PREINIT:
        QRect *rect = pextract(QRect, 1);
        CODE:
        THIS->QSemiModal::setGeometry(*rect);

void
pSemiModal::virtual_show()
