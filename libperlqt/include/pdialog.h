#ifndef PDIALOG_H
#define PDIALOG_H

/*
 * Declaration of the PDialog class
 *
 * Copyright (C) 1997, Ashley Winters <jql@accessone.com>
 *
 * You may distribute under the terms of the LGPL as specified in the
 * README file
 */

#undef bool
#include "qdialog.h"
#include "virtual.h"

class PDialog : public QDialog, public PDialog_virtualize {
    QDialog_virtual_functions
public:
    PDialog(QWidget *parent = 0, const char *name = 0, bool modal = FALSE,
	    WFlags f=0) : QDialog(parent, name, modal, f) {}
};

class pDialog : public QDialog {
public:
    void virtual_closeEvent(QCloseEvent *e) { QDialog::closeEvent(e); }
    void virtual_done(int r) { QDialog::done(r); }
    void virtual_keyPressEvent(QKeyEvent *e) { QDialog::keyPressEvent(e); }
    void virtual_move(int x, int y) { QDialog::move(x, y); }
    void virtual_resize(int w, int h) { QDialog::resize(w, h); }
    void virtual_setGeometry(int x, int y, int w, int h) {
	QDialog::setGeometry(x, y, w, h);
    }
    void virtual_show() { QDialog::show(); }

    void protected_accept() { QDialog::accept(); }
    void protected_reject() { QDialog::reject(); }
    void protected_setResult(int r) { QDialog::setResult(r); }
};

#endif  // PDIALOG_H
