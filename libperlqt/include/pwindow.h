#ifndef PWINDOW_H
#define PWINDOW_H

/*
 * Declaration of the PWindow class
 *
 * Copyright (C) 1997, Ashley Winters <jql@accessone.com>
 *
 * You may distribute under the terms of the LGPL as specified in the
 * README file
 */

#undef bool
#include "qwindow.h"
#include "virtual.h"

class PWindow : public QWindow, public PWindow_virtualize {
    QWindow_virtual_functions
public:
    PWindow(QWidget *parent = 0, const char *name = 0, WFlags f = 0) :
	QWindow(parent, name, f) {}
};

#endif  // PWINDOW_H
