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
#include "pobject.h"

#define QWidget_virtual_functions					\
    QObject_virtual_functions						\
public:									\
    void adjustSize();							\
    bool close(bool = FALSE);						\
    void hide();							\
    void move(int, int);						\
    void resize(int, int);						\
    void setBackgroundColor(const QColor &);				\
    void setBackgroundPixmap(const QPixmap &);				\
    void setCursor(const QCursor &);					\
    void setEnabled(bool);						\
    void setFont(const QFont &);					\
    void setGeometry(int, int, int, int);				\
    void setPalette(const QPalette &);					\
    void setStyle(GUIStyle);						\
    void show();							\
    QSize sizeHint() const;						\
protected:								\
    void closeEvent(QCloseEvent *);					\
    void enterEvent(QEvent *);						\
    void focusInEvent(QFocusEvent *);					\
    void focusOutEvent(QFocusEvent *);					\
    void keyPressEvent(QKeyEvent *);					\
    void keyReleaseEvent(QKeyEvent *);					\
    void leaveEvent(QEvent *);						\
    void mouseDoubleClickEvent(QMouseEvent *);				\
    void mouseMoveEvent(QMouseEvent *);					\
    void mousePressEvent(QMouseEvent *);				\
    void mouseReleaseEvent(QMouseEvent *);				\
    void moveEvent(QMoveEvent *);					\
    void paintEvent(QPaintEvent *);					\
    void resizeEvent(QResizeEvent *);

class PWidget_virtualize : public PObject_virtualize {
public:
    void PWidget_adjustSize();
    bool PWidget_close(bool = FALSE);
    void PWidget_hide();
    void PWidget_move(int, int);
    void PWidget_resize(int, int);
    void PWidget_setBackgroundColor(const QColor &);
    void PWidget_setBackgroundPixmap(const QPixmap &);
    void PWidget_setCursor(const QCursor &);
    void PWidget_setEnabled(bool);
    void PWidget_setFont(const QFont &);
    void PWidget_setGeometry(int, int, int, int);
    void PWidget_setPalette(const QPalette &);
    void PWidget_setStyle(GUIStyle);
    void PWidget_show();
    QSize PWidget_sizeHint() const;
protected:
    void PWidget_closeEvent(QCloseEvent *);
    void PWidget_enterEvent(QEvent *);
    void PWidget_focusInEvent(QFocusEvent *);
    void PWidget_focusOutEvent(QFocusEvent *);
    void PWidget_keyPressEvent(QKeyEvent *);
    void PWidget_keyReleaseEvent(QKeyEvent *);
    void PWidget_leaveEvent(QEvent *);
    void PWidget_mouseDoubleClickEvent(QMouseEvent *);
    void PWidget_mouseMoveEvent(QMouseEvent *);
    void PWidget_mousePressEvent(QMouseEvent *);
    void PWidget_mouseReleaseEvent(QMouseEvent *);
    void PWidget_moveEvent(QMoveEvent *);
    void PWidget_paintEvent(QPaintEvent *);
    void PWidget_resizeEvent(QResizeEvent *);
};

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

typedef QWidget::FocusPolicy QWidget__FocusPolicy;

#endif  // PWIDGET_H
