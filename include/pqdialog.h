#ifndef PQDIALOG_H
#define PQDIALOG_H

/*
 * QDialog interface.
 *
 * Copyright (C) 1997, Ashley Winters <jql@accessone.com>
 *
 * You may distribute under the terms of the LGPL as specified in the
 * README file
 */

#include <pqwidget.h>
#include <qdialog.h>

#define QDialog_functions						\
    void done(int);

#define QDialog_inlines(class)						\
    void v_done(int a) { class::done(a); }

#define QDialog_virtual_functions					\
    QWidget_virtual_functions						\
    QDialog_functions
#define QDialog_virtual_inlines(class)					\
    QWidget_virtual_inlines(class)					\
    QDialog_inlines(class)

class QDialog_virtualize : public QWidget_virtualize {
public:
    void QDialog_done(int);
};

class VQDialog : public QDialog, public QDialog_virtualize {
    QDialog_virtual_functions
public:
    VQDialog(QWidget *parent = 0, const char *name = 0, bool modal = FALSE,
	     WFlags f = 0) : QDialog(parent, name, modal, f) {}
};

class PQDialog : public QDialog {
    QDialog_virtual_inlines(QDialog)
public:
    void accept() { QDialog::accept(); }
    void reject() { QDialog::reject(); }
    void setResult(int a) { QDialog::setResult(a); }
};

typedef const QDialog CQDialog;

#endif  // PQDIALOG_H
