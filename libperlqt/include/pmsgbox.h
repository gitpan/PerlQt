#ifndef PMSGBOX_H
#define PMSGBOX_H

/*
 * Declaration of the PMessageBox class
 *
 * Copyright (C) 1997, Ashley Winters <jql@accessone.com>
 *
 * You may distribute under the terms of the LGPL as specified in the
 * README file
 */

#undef bool
#include "qmsgbox.h"
#include "virtual.h"

class PMessageBox : public QMessageBox, public PMessageBox_virtualize {
    QMessageBox_virtual_functions
public:
    PMessageBox(QWidget *parent = 0, const char *name = 0) :
	QMessageBox(parent, name) {}
};

class pMessageBox : public QMessageBox {
public:
    virtual_resizeEvent(QResizeEvent *e) { QMessageBox::resizeEvent(e); }
};

#endif  // PMSGBOX_H
