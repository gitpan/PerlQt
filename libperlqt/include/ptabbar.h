#ifndef PTABBAR_H
#define PTABBAR_H

/*
 * Declaration of the PTabBar class
 *
 * Copyright (C) 1997, Ashley Winters <jql@accessone.com>
 *
 * You may distribute under the terms of the LGPL as specified in the
 * README file
 */

#undef bool
#include "qtabbar.h"
#include "pwidget.h"

#define QTabBar_virtual_functions					\
    QWidget_virtual_functions						\
public:									\
    int addTab(QTab *);							\
protected:								\
    void paint(QPainter *, QTab *, bool) const;				\
    QTab *selectTab(const QPoint &) const;

class PTabBar_virtualize : public PWidget_virtualize {
public:
    int PTabBar_addTab(QTab *);
protected:
    void PTabBar_paint(QPainter *, QTab *, bool) const;
    QTab *PTabBar_selectTab(const QPoint &) const;
};

class PTabBar : public QTabBar, public PTabBar_virtualize {
    QTabBar_virtual_functions
public:
    PTabBar(QWidget *parent = 0, const char *name = 0) :
	QTabBar(parent, name) {}
};

class pTabBar : public QTabBar {
public:
    int virtual_addTab(QTab *t) { return QTabBar::addTab(t); }
    void virtual_keyPressEvent(QKeyEvent *e) { QTabBar::keyPressEvent(e); }
    void virtual_mousePressEvent(QMouseEvent *e) {
	QTabBar::mousePressEvent(e);
    }
    void virtual_mouseReleaseEvent(QMouseEvent *e) {
	QTabBar::mouseReleaseEvent(e);
    }
    void virtual_paint(QPainter *p, QTab *t, bool b) {
	QTabBar::paint(p, t, b);
    }
    void virtual_paintEvent(QPaintEvent *e) { QTabBar::paintEvent(e); }
    QTab *virtual_selectTab(const QPoint &p) { return QTabBar::selectTab(p); }
};

#endif  // PTABBAR_H
