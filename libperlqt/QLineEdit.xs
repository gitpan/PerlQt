/*
 * PLineEdit definitions.
 *
 * Copyright (C) 1997, Ashley Winters <jql@accessone.com>
 *
 * You may distribute under the terms of the LGPL as specified in the
 * README file
 */

#include "plined.h"

const char *PLineEdit::className() const {
    return PObject_className();
}

bool PLineEdit::event(QEvent *event) {
    bool ret = PObject_event(event);
    if(pfailed) ret = QLineEdit::event(event);
    return ret;
}

bool PLineEdit::eventFilter(QObject *obj, QEvent *event) {
    bool ret = PObject_eventFilter(obj, event);
    if(pfailed) ret = QLineEdit::eventFilter(obj, event);
    return ret;
}

QMetaObject *PLineEdit::metaObject() const {
    QMetaObject *ret = PObject_metaObject();
    if(pfailed) ret = QLineEdit::metaObject();
    return ret;
}

void PLineEdit::initMetaObject() {
    if(!QLineEdit::metaObject()) QLineEdit::initMetaObject();
    PObject_initMetaObject();
}

void PLineEdit::timerEvent(QTimerEvent *event) {
    PObject_timerEvent(event);
    if(pfailed) QLineEdit::timerEvent(event);
}


void PLineEdit::adjustSize() {
    PWidget_adjustSize();
    if(pfailed) QLineEdit::adjustSize();
}

bool PLineEdit::close(bool b) {
    bool ret = PWidget_close(b);
    if(pfailed) ret = QLineEdit::close(b);
    return ret;
}

void PLineEdit::hide() {
    PWidget_hide();
    if(pfailed) QLineEdit::hide();
}

void PLineEdit::move(int x, int y) {
    PWidget_move(x, y);
    if(pfailed) QLineEdit::move(x, y);
}

void PLineEdit::resize(int w, int h) {
    PWidget_resize(w, h);
    if(pfailed) QLineEdit::resize(w, h);
}

void PLineEdit::setBackgroundColor(const QColor &c) {
    PWidget_setBackgroundColor(c);
    if(pfailed) QLineEdit::setBackgroundColor(c);
}

void PLineEdit::setBackgroundPixmap(const QPixmap &p) {
    PWidget_setBackgroundPixmap(p);
    if(pfailed) QLineEdit::setBackgroundPixmap(p);
}

void PLineEdit::setCursor(const QCursor &c) {
    PWidget_setCursor(c);
    if(pfailed) QLineEdit::setCursor(c);
}

void PLineEdit::setEnabled(bool b) {
    PWidget_setEnabled(b);
    if(pfailed) QLineEdit::setEnabled(b);
}

void PLineEdit::setFont(const QFont &f) {
    PWidget_setFont(f);
    if(pfailed) QLineEdit::setFont(f);
}

void PLineEdit::setGeometry(int x, int y, int w, int h) {
    PWidget_setGeometry(x, y, w, h);
    if(pfailed) QLineEdit::setGeometry(x, y, w, h);
}

void PLineEdit::setPalette(const QPalette &p) {
    PWidget_setPalette(p);
    if(pfailed) QLineEdit::setPalette(p);
}

void PLineEdit::setStyle(GUIStyle s) {
    PWidget_setStyle(s);
    if(pfailed) QLineEdit::setStyle(s);
}

void PLineEdit::show() {
    PWidget_show();
    if(pfailed) QLineEdit::show();
}

QSize PLineEdit::sizeHint() const {
    QSize ret = PWidget_sizeHint();
    if(pfailed) ret = QLineEdit::sizeHint();
    return ret;
}

void PLineEdit::closeEvent(QCloseEvent *event) {
    PWidget_closeEvent(event);
    if(pfailed) QLineEdit::closeEvent(event);
}

void PLineEdit::enterEvent(QEvent *event) {
    PWidget_enterEvent(event);
    if(pfailed) QLineEdit::enterEvent(event);
}

void PLineEdit::focusInEvent(QFocusEvent *event) {
    PWidget_focusInEvent(event);
    if(pfailed) QLineEdit::focusInEvent(event);
}

void PLineEdit::focusOutEvent(QFocusEvent *event) {
    PWidget_focusOutEvent(event);
    if(pfailed) QLineEdit::focusOutEvent(event);
}

void PLineEdit::keyPressEvent(QKeyEvent *event) {
    PWidget_keyPressEvent(event);
    if(pfailed) QLineEdit::keyPressEvent(event);
}

void PLineEdit::keyReleaseEvent(QKeyEvent *event) {
    PWidget_keyReleaseEvent(event);
    if(pfailed) QLineEdit::keyReleaseEvent(event);
}

void PLineEdit::leaveEvent(QEvent *event) {
    PWidget_leaveEvent(event);
    if(pfailed) QLineEdit::leaveEvent(event);
}

void PLineEdit::mouseDoubleClickEvent(QMouseEvent *event) {
    PWidget_mouseDoubleClickEvent(event);
    if(pfailed) QLineEdit::mouseDoubleClickEvent(event);
}

void PLineEdit::mouseMoveEvent(QMouseEvent *event) {
    PWidget_mouseMoveEvent(event);
    if(pfailed) QLineEdit::mouseMoveEvent(event);
}

void PLineEdit::mousePressEvent(QMouseEvent *event) {
    PWidget_mousePressEvent(event);
    if(pfailed) QLineEdit::mousePressEvent(event);
}

void PLineEdit::mouseReleaseEvent(QMouseEvent *event) {
    PWidget_mouseReleaseEvent(event);
    if(pfailed) QLineEdit::mouseReleaseEvent(event);
}

void PLineEdit::moveEvent(QMoveEvent *event) {
    PWidget_moveEvent(event);
    if(pfailed) QLineEdit::moveEvent(event);
}

void PLineEdit::paintEvent(QPaintEvent *event) {
    PWidget_paintEvent(event);
    if(pfailed) QLineEdit::paintEvent(event);
}

void PLineEdit::resizeEvent(QResizeEvent *event) {
    PWidget_resizeEvent(event);
    if(pfailed) QLineEdit::resizeEvent(event);
}


