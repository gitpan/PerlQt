/*
 * PWindow definitions.
 *
 * Copyright (C) 1997, Ashley Winters <jql@accessone.com>
 *
 * You may distribute under the terms of the LGPL as specified in the
 * README file
 */

#include "pwindow.h"

const char *PWindow::className() const {
    return PObject_className();
}

bool PWindow::event(QEvent *event) {
    bool ret = PObject_event(event);
    if(pfailed) ret = QWindow::event(event);
    return ret;
}

bool PWindow::eventFilter(QObject *obj, QEvent *event) {
    bool ret = PObject_eventFilter(obj, event);
    if(pfailed) ret = QWindow::eventFilter(obj, event);
    return ret;
}

QMetaObject *PWindow::metaObject() const {
    QMetaObject *ret = PObject_metaObject();
    if(pfailed) ret = QWindow::metaObject();
    return ret;
}

void PWindow::initMetaObject() {
    if(!QWindow::metaObject()) QWindow::initMetaObject();
    PObject_initMetaObject();
}

void PWindow::timerEvent(QTimerEvent *event) {
    PObject_timerEvent(event);
    if(pfailed) QWindow::timerEvent(event);
}


void PWindow::adjustSize() {
    PWidget_adjustSize();
    if(pfailed) QWindow::adjustSize();
}

bool PWindow::close(bool b) {
    bool ret = PWidget_close(b);
    if(pfailed) ret = QWindow::close(b);
    return ret;
}

void PWindow::hide() {
    PWidget_hide();
    if(pfailed) QWindow::hide();
}

void PWindow::move(int x, int y) {
    PWidget_move(x, y);
    if(pfailed) QWindow::move(x, y);
}

void PWindow::resize(int w, int h) {
    PWidget_resize(w, h);
    if(pfailed) QWindow::resize(w, h);
}

void PWindow::setBackgroundColor(const QColor &c) {
    PWidget_setBackgroundColor(c);
    if(pfailed) QWindow::setBackgroundColor(c);
}

void PWindow::setBackgroundPixmap(const QPixmap &p) {
    PWidget_setBackgroundPixmap(p);
    if(pfailed) QWindow::setBackgroundPixmap(p);
}

void PWindow::setCursor(const QCursor &c) {
    PWidget_setCursor(c);
    if(pfailed) QWindow::setCursor(c);
}

void PWindow::setEnabled(bool b) {
    PWidget_setEnabled(b);
    if(pfailed) QWindow::setEnabled(b);
}

void PWindow::setFont(const QFont &f) {
    PWidget_setFont(f);
    if(pfailed) QWindow::setFont(f);
}

void PWindow::setGeometry(int x, int y, int w, int h) {
    PWidget_setGeometry(x, y, w, h);
    if(pfailed) QWindow::setGeometry(x, y, w, h);
}

void PWindow::setPalette(const QPalette &p) {
    PWidget_setPalette(p);
    if(pfailed) QWindow::setPalette(p);
}

void PWindow::setStyle(GUIStyle s) {
    PWidget_setStyle(s);
    if(pfailed) QWindow::setStyle(s);
}

void PWindow::show() {
    PWidget_show();
    if(pfailed) QWindow::show();
}

QSize PWindow::sizeHint() const {
    QSize ret = PWidget_sizeHint();
    if(pfailed) ret = QWindow::sizeHint();
    return ret;
}

void PWindow::closeEvent(QCloseEvent *event) {
    PWidget_closeEvent(event);
    if(pfailed) QWindow::closeEvent(event);
}

void PWindow::enterEvent(QEvent *event) {
    PWidget_enterEvent(event);
    if(pfailed) QWindow::enterEvent(event);
}

void PWindow::focusInEvent(QFocusEvent *event) {
    PWidget_focusInEvent(event);
    if(pfailed) QWindow::focusInEvent(event);
}

void PWindow::focusOutEvent(QFocusEvent *event) {
    PWidget_focusOutEvent(event);
    if(pfailed) QWindow::focusOutEvent(event);
}

void PWindow::keyPressEvent(QKeyEvent *event) {
    PWidget_keyPressEvent(event);
    if(pfailed) QWindow::keyPressEvent(event);
}

void PWindow::keyReleaseEvent(QKeyEvent *event) {
    PWidget_keyReleaseEvent(event);
    if(pfailed) QWindow::keyReleaseEvent(event);
}

void PWindow::leaveEvent(QEvent *event) {
    PWidget_leaveEvent(event);
    if(pfailed) QWindow::leaveEvent(event);
}

void PWindow::mouseDoubleClickEvent(QMouseEvent *event) {
    PWidget_mouseDoubleClickEvent(event);
    if(pfailed) QWindow::mouseDoubleClickEvent(event);
}

void PWindow::mouseMoveEvent(QMouseEvent *event) {
    PWidget_mouseMoveEvent(event);
    if(pfailed) QWindow::mouseMoveEvent(event);
}

void PWindow::mousePressEvent(QMouseEvent *event) {
    PWidget_mousePressEvent(event);
    if(pfailed) QWindow::mousePressEvent(event);
}

void PWindow::mouseReleaseEvent(QMouseEvent *event) {
    PWidget_mouseReleaseEvent(event);
    if(pfailed) QWindow::mouseReleaseEvent(event);
}

void PWindow::moveEvent(QMoveEvent *event) {
    PWidget_moveEvent(event);
    if(pfailed) QWindow::moveEvent(event);
}

void PWindow::paintEvent(QPaintEvent *event) {
    PWidget_paintEvent(event);
    if(pfailed) QWindow::paintEvent(event);
}

void PWindow::resizeEvent(QResizeEvent *event) {
    PWidget_resizeEvent(event);
    if(pfailed) QWindow::resizeEvent(event);
}


