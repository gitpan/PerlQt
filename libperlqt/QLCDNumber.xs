/*
 * PLCDNumber definitions.
 *
 * Copyright (C) 1997, Ashley Winters <jql@accessone.com>
 *
 * You may distribute under the terms of the LGPL as specified in the
 * README file
 */

#include "plcdnum.h"

const char *PLCDNumber::className() const {
    return PObject_className();
}

bool PLCDNumber::event(QEvent *event) {
    bool ret = PObject_event(event);
    if(pfailed) ret = QLCDNumber::event(event);
    return ret;
}

bool PLCDNumber::eventFilter(QObject *obj, QEvent *event) {
    bool ret = PObject_eventFilter(obj, event);
    if(pfailed) ret = QLCDNumber::eventFilter(obj, event);
    return ret;
}

QMetaObject *PLCDNumber::metaObject() const {
    QMetaObject *ret = PObject_metaObject();
    if(pfailed) ret = QLCDNumber::metaObject();
    return ret;
}

void PLCDNumber::initMetaObject() {
    if(!QLCDNumber::metaObject()) QLCDNumber::initMetaObject();
    PObject_initMetaObject();
}

void PLCDNumber::timerEvent(QTimerEvent *event) {
    PObject_timerEvent(event);
    if(pfailed) QLCDNumber::timerEvent(event);
}


void PLCDNumber::adjustSize() {
    PWidget_adjustSize();
    if(pfailed) QLCDNumber::adjustSize();
}

bool PLCDNumber::close(bool b) {
    bool ret = PWidget_close(b);
    if(pfailed) ret = QLCDNumber::close(b);
    return ret;
}

void PLCDNumber::hide() {
    PWidget_hide();
    if(pfailed) QLCDNumber::hide();
}

void PLCDNumber::move(int x, int y) {
    PWidget_move(x, y);
    if(pfailed) QLCDNumber::move(x, y);
}

void PLCDNumber::resize(int w, int h) {
    PWidget_resize(w, h);
    if(pfailed) QLCDNumber::resize(w, h);
}

void PLCDNumber::setBackgroundColor(const QColor &c) {
    PWidget_setBackgroundColor(c);
    if(pfailed) QLCDNumber::setBackgroundColor(c);
}

void PLCDNumber::setBackgroundPixmap(const QPixmap &p) {
    PWidget_setBackgroundPixmap(p);
    if(pfailed) QLCDNumber::setBackgroundPixmap(p);
}

void PLCDNumber::setCursor(const QCursor &c) {
    PWidget_setCursor(c);
    if(pfailed) QLCDNumber::setCursor(c);
}

void PLCDNumber::setEnabled(bool b) {
    PWidget_setEnabled(b);
    if(pfailed) QLCDNumber::setEnabled(b);
}

void PLCDNumber::setFont(const QFont &f) {
    PWidget_setFont(f);
    if(pfailed) QLCDNumber::setFont(f);
}

void PLCDNumber::setGeometry(int x, int y, int w, int h) {
    PWidget_setGeometry(x, y, w, h);
    if(pfailed) QLCDNumber::setGeometry(x, y, w, h);
}

void PLCDNumber::setPalette(const QPalette &p) {
    PWidget_setPalette(p);
    if(pfailed) QLCDNumber::setPalette(p);
}

void PLCDNumber::setStyle(GUIStyle s) {
    PWidget_setStyle(s);
    if(pfailed) QLCDNumber::setStyle(s);
}

void PLCDNumber::show() {
    PWidget_show();
    if(pfailed) QLCDNumber::show();
}

QSize PLCDNumber::sizeHint() const {
    QSize ret = PWidget_sizeHint();
    if(pfailed) ret = QLCDNumber::sizeHint();
    return ret;
}

void PLCDNumber::closeEvent(QCloseEvent *event) {
    PWidget_closeEvent(event);
    if(pfailed) QLCDNumber::closeEvent(event);
}

void PLCDNumber::enterEvent(QEvent *event) {
    PWidget_enterEvent(event);
    if(pfailed) QLCDNumber::enterEvent(event);
}

void PLCDNumber::focusInEvent(QFocusEvent *event) {
    PWidget_focusInEvent(event);
    if(pfailed) QLCDNumber::focusInEvent(event);
}

void PLCDNumber::focusOutEvent(QFocusEvent *event) {
    PWidget_focusOutEvent(event);
    if(pfailed) QLCDNumber::focusOutEvent(event);
}

void PLCDNumber::keyPressEvent(QKeyEvent *event) {
    PWidget_keyPressEvent(event);
    if(pfailed) QLCDNumber::keyPressEvent(event);
}

void PLCDNumber::keyReleaseEvent(QKeyEvent *event) {
    PWidget_keyReleaseEvent(event);
    if(pfailed) QLCDNumber::keyReleaseEvent(event);
}

void PLCDNumber::leaveEvent(QEvent *event) {
    PWidget_leaveEvent(event);
    if(pfailed) QLCDNumber::leaveEvent(event);
}

void PLCDNumber::mouseDoubleClickEvent(QMouseEvent *event) {
    PWidget_mouseDoubleClickEvent(event);
    if(pfailed) QLCDNumber::mouseDoubleClickEvent(event);
}

void PLCDNumber::mouseMoveEvent(QMouseEvent *event) {
    PWidget_mouseMoveEvent(event);
    if(pfailed) QLCDNumber::mouseMoveEvent(event);
}

void PLCDNumber::mousePressEvent(QMouseEvent *event) {
    PWidget_mousePressEvent(event);
    if(pfailed) QLCDNumber::mousePressEvent(event);
}

void PLCDNumber::mouseReleaseEvent(QMouseEvent *event) {
    PWidget_mouseReleaseEvent(event);
    if(pfailed) QLCDNumber::mouseReleaseEvent(event);
}

void PLCDNumber::moveEvent(QMoveEvent *event) {
    PWidget_moveEvent(event);
    if(pfailed) QLCDNumber::moveEvent(event);
}

void PLCDNumber::paintEvent(QPaintEvent *event) {
    PWidget_paintEvent(event);
    if(pfailed) QLCDNumber::paintEvent(event);
}

void PLCDNumber::resizeEvent(QResizeEvent *event) {
    PWidget_resizeEvent(event);
    if(pfailed) QLCDNumber::resizeEvent(event);
}


void PLCDNumber::drawContents(QPainter *p) {
    PFrame_drawContents(p);
    if(pfailed) QLCDNumber::drawContents(p);
}

void PLCDNumber::drawFrame(QPainter *p) {
    PFrame_drawFrame(p);
    if(pfailed) QLCDNumber::drawFrame(p);
}

void PLCDNumber::frameChanged() {
    PFrame_frameChanged();
    if(pfailed) QLCDNumber::frameChanged();
}


