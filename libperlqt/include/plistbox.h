#ifndef PLISTBOX_H
#define PLISTBOX_H

/*
 * Declaration of the PListBox, PListBoxText and PListBoxPixmap classes
 *
 * Copyright (C) 1997, Ashley Winters <jql@accessone.com>
 *
 * You may distribute under the terms of the LGPL as specified in the
 * README file
 */

#undef bool
#include "qlistbox.h"
#include "ptablevw.h"

#define QListBox_virtual_functions QTableView_virtual_functions

class PListBox_virtualize : public PTableView_virtualize {};

class PListBox : public QListBox, public PListBox_virtualize {
    QListBox_virtual_functions
public:
    PListBox(QWidget *parent = 0, const char *name = 0, WFlags f = 0) :
	QListBox(parent, name, f) {}
};

class pListBox : public QListBox {
public:
    int virtual_cellHeight(int i = 0) { return QListBox::cellHeight(i); }
    void virtual_focusInEvent(QFocusEvent *e) { QListBox::focusInEvent(e); }
    void virtual_keyPressEvent(QKeyEvent *e) { QListBox::keyPressEvent(e); }
    void virtual_mouseDoubleClickEvent(QMouseEvent *e) {
	QListBox::mouseDoubleClickEvent(e);
    }
    void virtual_mouseMoveEvent(QMouseEvent *e) {
	QListBox::mouseMoveEvent(e);
    }
    void virtual_mousePressEvent(QMouseEvent *e) {
	QListBox::mousePressEvent(e);
    }
    void virtual_mouseReleaseEvent(QMouseEvent *e) {
	QListBox::mouseReleaseEvent(e);
    }
    void virtual_paintCell(QPainter *p, int row, int col) {
	QListBox::paintCell(p, row, col);
    }
    void virtual_resizeEvent(QResizeEvent *e) {
	QListBox::resizeEvent(e);
    }
    void virtual_setFont(const QFont &f) { QListBox::setFont(f); }
    void virtual_timerEvent(QTimerEvent *e) { QListBox::timerEvent(e); }

    void protected_clearList() { QListBox::clearList(); }
    int protected_findItem(int yPos) const { return QListBox::findItem(yPos); }
    QListBoxItem *protected_item(int i) const { return QListBox::item(i); }
    bool protected_itemVisible(int i) { return QListBox::itemVisible(i); }
    bool protected_itemYPos(int i, int *yPos) const {
	return QListBox::itemYPos(i, yPos);
    }
    void protected_updateCellWidth() { QListBox::updateCellWidth(); }
    void protected_updateItem(int i, bool clear = TRUE) {
	QListBox::updateItem(i, clear);
    }
};

class PListBoxPixmap : public QListBoxPixmap {
public:
    PListBoxPixmap(const QPixmap &pixmap) : QListBoxPixmap(pixmap) {}
};

class PListBoxText : public QListBoxText {
public:
    PListBoxText(const char *text) : QListBoxText(text) {}
};

#endif  // PLISTBOX_H
