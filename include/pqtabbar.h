#ifndef PQTABBAR_H
#define PQTABBAR_H

/*
 * QTabBar interface.
 *
 * Copyright (C) 1997, Ashley Winters <jql@accessone.com>
 *
 * You may distribute under the terms of the LGPL as specified in the
 * README file
 */

#include <pqwidget.h>
#include <qtabbar.h>

#define QTabBar_functions
#define QTabBar_inlines(class)
#define QTabBar_virtual_functions					\
    QWidget_virtual_functions						\
    QTabBar_functions
#define QTabBar_virtual_inlines(class)					\
    QWidget_virtual_inlines(class)					\
    QTabBar_inlines(class)

class QTabBar_virtualize : public QWidget_virtualize {};

class VQTabBar : public QTabBar, public QTabBar_virtualize {
    QTabBar_virtual_functions
public:
    VQTabBar(QWidget *parent = 0, const char *name = 0) :
	QTabBar(parent, name) {}
};

class PQTabBar : public QTabBar { QTabBar_virtual_inlines(QTabBar) };

typedef const QTabBar CQTabBar;

#endif  // PQTABBAR_H
