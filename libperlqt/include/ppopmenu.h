#ifndef PPOPMENU_H
#define PPOPMENU_H

/*
 * Declaration of the PPopupMenu class
 *
 * Copyright (C) 1997, Ashley Winters <jql@accessone.com>
 *
 * You may distribute under the terms of the LGPL as specified in the
 * README file
 */

#undef bool
#include "qpopmenu.h"
#include "virtual.h"

class PPopupMenu : public QPopupMenu, public PPopupMenu_virtualize {
    QPopupMenu_virtual_functions
public:
    PPopupMenu(QWidget *parent = 0, const char *name = 0) :
	QPopupMenu(parent, name) {}
};

class pPopupMenu : public QPopupMenu {
public:
    void virtual_cellHeight(int row) { QPopupMenu::cellHeight(row); }
    void virtual_cellWidth(int col) { QPopupMenu::cellWidth(col); }
    void virtual_hide() { QPopupMenu::hide(); }
    void virtual_keyPressEvent(QKeyEvent *e) {
	QPopupMenu::keyPressEvent(e);
    }
    void virtual_mouseMoveEvent(QMouseEvent *e) {
	QPopupMenu::mouseMoveEvent(e);
    }
    void virtual_mousePressEvent(QMouseEvent *e) {
	QPopupMenu::mousePressEvent(e);
    }
    void virtual_mouseReleaseEvent(QMouseEvent *e) {
	QPopupMenu::mouseReleaseEvent(e);
    }
    void virtual_paintCell(QPainter *p, int row, int col) {
	QPopupMenu::paintCell(p, row, col);
    }
    void virtual_paintEvent(QPaintEvent *e) { QPopupMenu::paintEvent(e); }
    void virtual_setFont(const QFont &f) { QPopupMenu::setFont(f); }
    void virtual_show() { QPopupMenu::show(); }
    void virtual_timerEvent(QTimerEvent *e) { QPopupMenu::timerEvent(e); }
    void virtual_updateItem(int id) { QPopupMenu::updateItem(id); }
};

#endif  // PPOPMENU_H
