#ifndef PQTABDLG_H
#define PQTABDLG_H

/*
 * QTabDialog interface.
 *
 * Copyright (C) 1997, Ashley Winters <jql@accessone.com>
 *
 * You may distribute under the terms of the LGPL as specified in the
 * README file
 */

#include <pqdialog.h>
#include <qtabdlg.h>

#define QTabDialog_functions
#define QTabDialog_inlines(class)
#define QTabDialog_virtual_functions					\
    QDialog_virtual_functions						\
    QTabDialog_functions
#define QTabDialog_virtual_inlines(class)				\
    QDialog_virtual_inlines(class)					\
    QTabDialog_inlines(class)

class QTabDialog_virtualize : public QDialog_virtualize {};

class VQTabDialog : public QTabDialog, public QTabDialog_virtualize {
    QTabDialog_virtual_functions
public:
    VQTabDialog(QWidget *parent = 0, const char *name = 0,
		 bool modal = FALSE, WFlags f = 0) :
	QTabDialog(parent, name, modal, f) {}
};

class PQTabDialog : public QTabDialog {
    QTabDialog_virtual_inlines(QTabDialog)
};

typedef const QTabDialog CQTabDialog;

#endif  // PQTABDLG_H
