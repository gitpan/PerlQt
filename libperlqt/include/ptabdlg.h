#ifndef PTABDLG_H
#define PTABDLG_H

/*
 * Declaration of the PTabDialog class
 *
 * Copyright (C) 1997, Ashley Winters <jql@accessone.com>
 *
 * You may distribute under the terms of the LGPL as specified in the
 * README file
 */

#undef bool
#include "qtabdlg.h"
#include "pdialog.h"

#define QTabDialog_virtual_functions QDialog_virtual_functions

class PTabDialog_virtualize : public PDialog_virtualize {};

class PTabDialog : public QTabDialog, public PTabDialog_virtualize {
    QTabDialog_virtual_functions
public:
    PTabDialog(QWidget *parent = 0, const char *name = 0, bool modal = FALSE,
	       WFlags f = 0) : QTabDialog(parent, name, modal, f) {}
};

class pTabDialog : public QTabDialog {
public:
    void virtual_paintEvent(QPaintEvent *e) { QTabDialog::paintEvent(e); }
    void virtual_resizeEvent(QResizeEvent *e) { QTabDialog::resizeEvent(e); }
    void virtual_setFont(const QFont &f) { QTabDialog::setFont(f); }
    void virtual_show() { QTabDialog::show(); }
};

#endif  // PTABDLG_H
