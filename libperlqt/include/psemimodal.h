#ifndef PSEMIMODAL_H
#define PSEMIMODAL_H

/*
 * Declaration of the PSemiModal class
 *
 * Copyright (C) 1997, Ashley Winters <jql@accessone.com>
 *
 * You may distribute under the terms of the LGPL as specified in the
 * README file
 */

#undef bool
#include "qsemimodal.h"
#include "pwidget.h"

#define QSemiModal_virtual_functions QWidget_virtual_functions

class PSemiModal_virtualize : public PWidget_virtualize {};

class PSemiModal : public QSemiModal, public PSemiModal_virtualize {
    QSemiModal_virtual_functions
public:
    PSemiModal(QWidget *parent = 0, const char *name = 0, bool modal = FALSE,
	       WFlags f = 0) : QSemiModal(parent, name, modal, f) {}
};

class pSemiModal : public QSemiModal {
public:
    void virtual_move(int x, int y) { QSemiModal::move(x, y); }
    void virtual_resize(int w, int h) { QSemiModal::resize(w, h); }
    void virtual_setGeometry(int x, int y, int w, int h) {
        QSemiModal::setGeometry(x, y, w, h);
    }
    void virtual_show() { QSemiModal::show(); }
};

#endif  // PSEMIMODAL_H
