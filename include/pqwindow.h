#ifndef PQWINDOW_H
#define PQWINDOW_H

/*
 * QWindow interface.
 *
 * Copyright (C) 1997, Ashley Winters <jql@accessone.com>
 *
 * You may distribute under the terms of the LGPL as specified in the
 * README file
 */

#include <pqwidget.h>
#include <qwindow.h>

#define QWindow_functions
#define QWindow_inlines(class)
#define QWindow_virtual_functions					\
    QWidget_virtual_functions						\
    QWindow_functions
#define QWindow_virtual_inlines(class)					\
    QWidget_virtual_inlines(class)					\
    QWindow_inlines(class)

class QWindow_virtualize : public QWidget_virtualize {};

class VQWindow : public QWindow, public QWindow_virtualize {
    QWindow_virtual_functions
public:
    VQWindow(QWidget *parent = 0, const char *name = 0, WFlags f = 0) :
	QWindow(parent, name, f) {}
};

class PQWindow : public QWindow { QWindow_virtual_inlines(QWindow) };

typedef const QWindow CQWindow;

#endif  // PQWINDOW_H
