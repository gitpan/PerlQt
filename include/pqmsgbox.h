#ifndef PQMSGBOX_H
#define PQMSGBOX_H

/*
 * QMessageBox interface.
 *
 * Copyright (C) 1997, Ashley Winters <jql@accessone.com>
 *
 * You may distribute under the terms of the LGPL as specified in the
 * README file
 */

#include <pqdialog.h>
#include <qmsgbox.h>

#define QMessageBox_functions
#define QMessageBox_inlines(class)
#define QMessageBox_virtual_functions					\
    QDialog_virtual_functions						\
    QMessageBox_functions
#define QMessageBox_virtual_inlines(class)				\
    QDialog_virtual_inlines(class)					\
    QMessageBox_inlines(class)

class QMessageBox_virtualize : public QDialog_virtualize {};

class VQMessageBox : public QMessageBox, public QMessageBox_virtualize {
    QMessageBox_virtual_functions
public:
    VQMessageBox(QWidget *parent = 0, const char *name = 0) :
	QMessageBox(parent, name) {}
    VQMessageBox(const char *caption, const char *text, QMessageBox::Icon icon,
		 int button0, int button1, int button2, QWidget *parent = 0,
		 const char *name = 0, bool modal = TRUE, WFlags f = 0) :
	QMessageBox(caption, text, icon, button0, button1, button2, parent,
		    name, modal, f) {}
};

class PQMessageBox : public QMessageBox {
    QMessageBox_virtual_inlines(QMessageBox)
};

typedef const QMessageBox CQMessageBox;

#endif  // PQMSGBOX_H
