#ifndef PQSEMIMODAL_H
#define PQSEMIMODAL_H

/*
 * QSemiModal interface.
 *
 * Copyright (C) 1997, Ashley Winters <jql@accessone.com>
 *
 * You may distribute under the terms of the LGPL as specified in the
 * README file
 */

#include <pqwidget.h>
#include <qsemimodal.h>

#define QSemiModal_functions
#define QSemiModal_inlines(class)
#define QSemiModal_virtual_functions					\
    QWidget_virtual_functions						\
    QSemiModal_functions
#define QSemiModal_virtual_inlines(class)				\
    QWidget_virtual_inlines(class)					\
    QSemiModal_inlines(class)

class QSemiModal_virtualize : public QWidget_virtualize {};

class VQSemiModal : public QSemiModal, public QSemiModal_virtualize {
    QSemiModal_virtual_functions
public:
    VQSemiModal(QWidget *parent = 0, const char *name = 0, bool modal = FALSE,
		WFlags f = 0) : QSemiModal(parent, name, modal, f) {}
};

class PQSemiModal : public QSemiModal {
    QSemiModal_virtual_inlines(QSemiModal)
};

typedef const QSemiModal CQSemiModal;

#endif  // PQSEMIMODAL_H
