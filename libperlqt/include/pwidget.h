#ifndef PWIDGET_H
#define PWIDGET_H

/*
 * Declaration of the PWidget class
 *
 * Copyright (C) 1997, Ashley Winters <jql@accessone.com>
 *
 * You may distribute under the terms of the LGPL as specified in the
 * README file
 */

#undef bool
#include "qwidget.h"
#include "pcolor.h"
#include "pfont.h"
#include "pfontinf.h"
#include "ppalette.h"
#include "ppixmap.h"
#include "prect.h"
#include "virtual.h"

typedef QWidget::FocusPolicy QWidget__FocusPolicy;

class PWidget : public QWidget, public PWidget_virtualize {
    QWidget_virtual_functions
public:
    PWidget(QWidget *parent = 0, const char *name = 0, WFlags f = 0) :
	QWidget(parent, name, f) {}
};

#define pWidget_event(f, t) void virtual_ ## f(t *e) { QWidget::f(e); }

class pWidget : public QWidget {
public:
    pWidget_event(closeEvent, QCloseEvent);
    pWidget_event(enterEvent, QEvent);
    pWidget_event(focusInEvent, QFocusEvent);
    pWidget_event(focusOutEvent, QFocusEvent);
    pWidget_event(keyPressEvent, QKeyEvent);
    pWidget_event(keyReleaseEvent, QKeyEvent);
    pWidget_event(leaveEvent, QEvent);
    pWidget_event(mouseDoubleClickEvent, QMouseEvent);
    pWidget_event(mouseMoveEvent, QMouseEvent);
    pWidget_event(mousePressEvent, QMouseEvent);
    pWidget_event(mouseReleaseEvent, QMouseEvent);
    pWidget_event(moveEvent, QMoveEvent);
    pWidget_event(paintEvent, QPaintEvent);
    pWidget_event(resizeEvent, QResizeEvent);

    void virtual_adjustSize() { QWidget::adjustSize(); }
    bool virtual_close(bool f = FALSE) { return QWidget::close(f); }
    bool virtual_event(QEvent *e) { return QWidget::event(e); }
    void virtual_hide() { QWidget::hide(); }
    void virtual_move(int x, int y) { QWidget::move(x, y); }
    void virtual_resize(int w, int h) { QWidget::resize(w, h); }
    void virtual_setBackgroundColor(const QColor &c) {
	QWidget::setBackgroundColor(c);
    }
    void virtual_setBackgroundPixmap(const QPixmap &p) {
	QWidget::setBackgroundPixmap(p);
    }
    void virtual_setCursor(const QCursor &c) { QWidget::setCursor(c); }
    void virtual_setEnabled(bool b) { QWidget::setEnabled(b); }
    void virtual_setFont(const QFont &f) { QWidget::setFont(f); }
    void virtual_setGeometry(int x, int y, int w, int h) {
	QWidget::setGeometry(x, y, w, h);
    }
    void virtual_setPalette(const QPalette &p) { QWidget::setPalette(p); }
    void virtual_setStyle(GUIStyle s) { QWidget::setStyle(s); }
    void virtual_show() { QWidget::show(); }
    QSize virtual_sizeHint() const { return QWidget::sizeHint(); }
};

#endif  // PWIDGET_H
