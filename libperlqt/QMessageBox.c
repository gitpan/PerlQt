/*
 * PMessageBox definitions.
 *
 * Copyright (C) 1997, Ashley Winters <jql@accessone.com>
 *
 * You may distribute under the terms of the LGPL as specified in the
 * README file
 */

#include "pmsgbox.h"

const char *PMessageBox::className() const {
    return PObject_className();
}

bool PMessageBox::event(QEvent *event) {
    bool ret = PObject_event(event);
    if(pfailed) ret = QMessageBox::event(event);
    return ret;
}

bool PMessageBox::eventFilter(QObject *obj, QEvent *event) {
    bool ret = PObject_eventFilter(obj, event);
    if(pfailed) ret = QMessageBox::eventFilter(obj, event);
    return ret;
}

QMetaObject *PMessageBox::metaObject() const {
    QMetaObject *ret = PObject_metaObject();
    if(pfailed) ret = QMessageBox::metaObject();
    return ret;
}

void PMessageBox::initMetaObject() {
    if(!QMessageBox::metaObject()) QMessageBox::initMetaObject();
    PObject_initMetaObject();
}

void PMessageBox::timerEvent(QTimerEvent *event) {
    PObject_timerEvent(event);
    if(pfailed) QMessageBox::timerEvent(event);
}


void PMessageBox::adjustSize() {
    PWidget_adjustSize();
    if(pfailed) QMessageBox::adjustSize();
}

bool PMessageBox::close(bool b) {
    bool ret = PWidget_close(b);
    if(pfailed) ret = QMessageBox::close(b);
    return ret;
}

void PMessageBox::hide() {
    PWidget_hide();
    if(pfailed) QMessageBox::hide();
}

void PMessageBox::move(int x, int y) {
    PWidget_move(x, y);
    if(pfailed) QMessageBox::move(x, y);
}

void PMessageBox::resize(int w, int h) {
    PWidget_resize(w, h);
    if(pfailed) QMessageBox::resize(w, h);
}

void PMessageBox::setBackgroundColor(const QColor &c) {
    PWidget_setBackgroundColor(c);
    if(pfailed) QMessageBox::setBackgroundColor(c);
}

void PMessageBox::setBackgroundPixmap(const QPixmap &p) {
    PWidget_setBackgroundPixmap(p);
    if(pfailed) QMessageBox::setBackgroundPixmap(p);
}

void PMessageBox::setCursor(const QCursor &c) {
    PWidget_setCursor(c);
    if(pfailed) QMessageBox::setCursor(c);
}

void PMessageBox::setEnabled(bool b) {
    PWidget_setEnabled(b);
    if(pfailed) QMessageBox::setEnabled(b);
}

void PMessageBox::setFont(const QFont &f) {
    PWidget_setFont(f);
    if(pfailed) QMessageBox::setFont(f);
}

void PMessageBox::setGeometry(int x, int y, int w, int h) {
    PWidget_setGeometry(x, y, w, h);
    if(pfailed) QMessageBox::setGeometry(x, y, w, h);
}

void PMessageBox::setPalette(const QPalette &p) {
    PWidget_setPalette(p);
    if(pfailed) QMessageBox::setPalette(p);
}

void PMessageBox::setStyle(GUIStyle s) {
    PWidget_setStyle(s);
    if(pfailed) QMessageBox::setStyle(s);
}

void PMessageBox::show() {
    PWidget_show();
    if(pfailed) QMessageBox::show();
}

QSize PMessageBox::sizeHint() const {
    QSize ret = PWidget_sizeHint();
    if(pfailed) ret = QMessageBox::sizeHint();
    return ret;
}

void PMessageBox::closeEvent(QCloseEvent *event) {
    PWidget_closeEvent(event);
    if(pfailed) QMessageBox::closeEvent(event);
}

void PMessageBox::enterEvent(QEvent *event) {
    PWidget_enterEvent(event);
    if(pfailed) QMessageBox::enterEvent(event);
}

void PMessageBox::focusInEvent(QFocusEvent *event) {
    PWidget_focusInEvent(event);
    if(pfailed) QMessageBox::focusInEvent(event);
}

void PMessageBox::focusOutEvent(QFocusEvent *event) {
    PWidget_focusOutEvent(event);
    if(pfailed) QMessageBox::focusOutEvent(event);
}

void PMessageBox::keyPressEvent(QKeyEvent *event) {
    PWidget_keyPressEvent(event);
    if(pfailed) QMessageBox::keyPressEvent(event);
}

void PMessageBox::keyReleaseEvent(QKeyEvent *event) {
    PWidget_keyReleaseEvent(event);
    if(pfailed) QMessageBox::keyReleaseEvent(event);
}

void PMessageBox::leaveEvent(QEvent *event) {
    PWidget_leaveEvent(event);
    if(pfailed) QMessageBox::leaveEvent(event);
}

void PMessageBox::mouseDoubleClickEvent(QMouseEvent *event) {
    PWidget_mouseDoubleClickEvent(event);
    if(pfailed) QMessageBox::mouseDoubleClickEvent(event);
}

void PMessageBox::mouseMoveEvent(QMouseEvent *event) {
    PWidget_mouseMoveEvent(event);
    if(pfailed) QMessageBox::mouseMoveEvent(event);
}

void PMessageBox::mousePressEvent(QMouseEvent *event) {
    PWidget_mousePressEvent(event);
    if(pfailed) QMessageBox::mousePressEvent(event);
}

void PMessageBox::mouseReleaseEvent(QMouseEvent *event) {
    PWidget_mouseReleaseEvent(event);
    if(pfailed) QMessageBox::mouseReleaseEvent(event);
}

void PMessageBox::moveEvent(QMoveEvent *event) {
    PWidget_moveEvent(event);
    if(pfailed) QMessageBox::moveEvent(event);
}

void PMessageBox::paintEvent(QPaintEvent *event) {
    PWidget_paintEvent(event);
    if(pfailed) QMessageBox::paintEvent(event);
}

void PMessageBox::resizeEvent(QResizeEvent *event) {
    PWidget_resizeEvent(event);
    if(pfailed) QMessageBox::resizeEvent(event);
}


void PMessageBox::done(int result) {
    PDialog_done(result);
    if(pfailed) QMessageBox::done(result);
}


