/*
 * PerlQt interface to qwindow.h
 *
 * Copyright (C) 1997, Ashley Winters <jql@accessone.com>
 *
 * You may distribute under the terms of the LGPL as specified in the
 * README file
 */

#include "pwindow.h"

MODULE = QWindow		PACKAGE = QWindow

PROTOTYPES: DISABLE

PWindow *
PWindow::new(parent = 0, name = 0, f = 0)
    pWidget *parent
    char *name
    WFlags f

void
QWindow::DESTROY()
    CODE:
    if(want_destroy(ST(0)))
	delete THIS;
