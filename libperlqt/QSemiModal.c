/*
 * PSemiModal definitions.
 *
 * Copyright (C) 1997, Ashley Winters <jql@accessone.com>
 *
 * You may distribute under the terms of the LGPL as specified in the
 * README file
 */

#include "psemimodal.h"

const char *PSemiModal::className() const {
    return PObject_className();
}

bool PSemiModal::event(QEvent *event) {
    bool ret = PObject_event(event);
    if(pfailed) ret = QSemiModal::event(event);
    return ret;
}

bool PSemiModal::eventFilter(QObject *obj, QEvent *event) {
    bool ret = PObject_eventFilter(obj, event);
    if(pfailed) ret = QSemiModal::eventFilter(obj, event);
    return ret;
}

QMetaObject *PSemiModal::metaObject() const {
    QMetaObject *ret = PObject_metaObject();
    if(pfailed) ret = QSemiModal::metaObject();
    return ret;
}

void PSemiModal::initMetaObject() {
    if(!QSemiModal::metaObject()) QSemiModal::initMetaObject();
    PObject_initMetaObject();
}

void PSemiModal::timerEvent(QTimerEvent *event) {
    PObject_timerEvent(event);
    if(pfailed) QSemiModal::timerEvent(event);
}


void PSemiModal::adjustSize() {
    PWidget_adjustSize();
    if(pfailed) QSemiModal::adjustSize();
}

bool PSemiModal::close(bool b) {
    bool ret = PWidget_close(b);
    if(pfailed) ret = QSemiModal::close(b);
    return ret;
}

void PSemiModal::hide() {
    PWidget_hide();
    if(pfailed) QSemiModal::hide();
}

void PSemiModal::move(int x, int y) {
    PWidget_move(x, y);
    if(pfailed) QSemiModal::move(x, y);
}

void PSemiModal::resize(int w, int h) {
    PWidget_resize(w, h);
    if(pfailed) QSemiModal::resize(w, h);
}

void PSemiModal::setBackgroundColor(const QColor &c) {
    PWidget_setBackgroundColor(c);
    if(pfailed) QSemiModal::setBackgroundColor(c);
}

void PSemiModal::setBackgroundPixmap(const QPixmap &p) {
    PWidget_setBackgroundPixmap(p);
    if(pfailed) QSemiModal::setBackgroundPixmap(p);
}

void PSemiModal::setCursor(const QCursor &c) {
    PWidget_setCursor(c);
    if(pfailed) QSemiModal::setCursor(c);
}

void PSemiModal::setEnabled(bool b) {
    PWidget_setEnabled(b);
    if(pfailed) QSemiModal::setEnabled(b);
}

void PSemiModal::setFont(const QFont &f) {
    PWidget_setFont(f);
    if(pfailed) QSemiModal::setFont(f);
}

void PSemiModal::setGeometry(int x, int y, int w, int h) {
    PWidget_setGeometry(x, y, w, h);
    if(pfailed) QSemiModal::setGeometry(x, y, w, h);
}

void PSemiModal::setPalette(const QPalette &p) {
    PWidget_setPalette(p);
    if(pfailed) QSemiModal::setPalette(p);
}

void PSemiModal::setStyle(GUIStyle s) {
    PWidget_setStyle(s);
    if(pfailed) QSemiModal::setStyle(s);
}

void PSemiModal::show() {
    PWidget_show();
    if(pfailed) QSemiModal::show();
}

QSize PSemiModal::sizeHint() const {
    QSize ret = PWidget_sizeHint();
    if(pfailed) ret = QSemiModal::sizeHint();
    return ret;
}

void PSemiModal::closeEvent(QCloseEvent *event) {
    PWidget_closeEvent(event);
    if(pfailed) QSemiModal::closeEvent(event);
}

void PSemiModal::enterEvent(QEvent *event) {
    PWidget_enterEvent(event);
    if(pfailed) QSemiModal::enterEvent(event);
}

void PSemiModal::focusInEvent(QFocusEvent *event) {
    PWidget_focusInEvent(event);
    if(pfailed) QSemiModal::focusInEvent(event);
}

void PSemiModal::focusOutEvent(QFocusEvent *event) {
    PWidget_focusOutEvent(event);
    if(pfailed) QSemiModal::focusOutEvent(event);
}

void PSemiModal::keyPressEvent(QKeyEvent *event) {
    PWidget_keyPressEvent(event);
    if(pfailed) QSemiModal::keyPressEvent(event);
}

void PSemiModal::keyReleaseEvent(QKeyEvent *event) {
    PWidget_keyReleaseEvent(event);
    if(pfailed) QSemiModal::keyReleaseEvent(event);
}

void PSemiModal::leaveEvent(QEvent *event) {
    PWidget_leaveEvent(event);
    if(pfailed) QSemiModal::leaveEvent(event);
}

void PSemiModal::mouseDoubleClickEvent(QMouseEvent *event) {
    PWidget_mouseDoubleClickEvent(event);
    if(pfailed) QSemiModal::mouseDoubleClickEvent(event);
}

void PSemiModal::mouseMoveEvent(QMouseEvent *event) {
    PWidget_mouseMoveEvent(event);
    if(pfailed) QSemiModal::mouseMoveEvent(event);
}

void PSemiModal::mousePressEvent(QMouseEvent *event) {
    PWidget_mousePressEvent(event);
    if(pfailed) QSemiModal::mousePressEvent(event);
}

void PSemiModal::mouseReleaseEvent(QMouseEvent *event) {
    PWidget_mouseReleaseEvent(event);
    if(pfailed) QSemiModal::mouseReleaseEvent(event);
}

void PSemiModal::moveEvent(QMoveEvent *event) {
    PWidget_moveEvent(event);
    if(pfailed) QSemiModal::moveEvent(event);
}

void PSemiModal::paintEvent(QPaintEvent *event) {
    PWidget_paintEvent(event);
    if(pfailed) QSemiModal::paintEvent(event);
}

void PSemiModal::resizeEvent(QResizeEvent *event) {
    PWidget_resizeEvent(event);
    if(pfailed) QSemiModal::resizeEvent(event);
}


