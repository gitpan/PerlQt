#ifndef PMENUBAR_H
#define PMENUBAR_H

/*
 * Declaration of the PMenuBar class
 *
 * Copyright (C) 1997, Ashley Winters <jql@accessone.com>
 *
 * You may distribute under the terms of the LGPL as specified in the
 * README file
 */

#undef bool
#include "qmenubar.h"
#include "pframe.h"
#include "pmenudta.h"

// @!$! %&!@ &!#@ &!@&# troll tech @!%&@*! @(!@*#& $*&%!!!!!!!!!!!!!!!!! //

#define QMenuBar_virtual_functions					\
    QWidget_virtual_functions						\
protected:								\
    void drawFrame(QPainter *);						\
    void drawContents(QPainter *);					\
public:									\
    void updateItem(int);						\
protected:								\
    void menuContentsChanged();						\
    void menuStateChanged();

class PMenuBar_virtualize : public PFrame_virtualize,
			    public PMenuData_virtualize {};

class PMenuBar : public QMenuBar, public PMenuBar_virtualize {
    QMenuBar_virtual_functions
public:
    PMenuBar(QWidget *parent = 0, const char *name = 0) :
	QMenuBar(parent, name) {}
};

class pMenuBar : public QMenuBar {
public:
    void virtual_drawContents(QPainter *p) { QMenuBar::drawContents(p); }
    void virtual_hide() { QMenuBar::hide(); }
    bool virtual_eventFilter(QObject *o, QEvent *e) {
	return QMenuBar::eventFilter(o, e);
    }
    void virtual_keyPressEvent(QKeyEvent *e) {
	QMenuBar::keyPressEvent(e);
    }
    void virtual_menuContentsChanged() { QMenuBar::menuContentsChanged(); }
    void virtual_menuStateChanged() { QMenuBar::menuStateChanged(); }
    void virtual_mouseMoveEvent(QMouseEvent *e) {
	QMenuBar::mouseMoveEvent(e);
    }
    void virtual_mousePressEvent(QMouseEvent *e) {
	QMenuBar::mousePressEvent(e);
    }
    void virtual_mouseReleaseEvent(QMouseEvent *e) {
	QMenuBar::mouseReleaseEvent(e);
    }
    void virtual_resizeEvent(QResizeEvent *e) {
	QMenuBar::resizeEvent(e);
    }
    void virtual_show() { QMenuBar::show(); }
    void virtual_updateItem(int id) { QMenuBar::updateItem(id); }
};

#endif  // PMENUBAR_H
