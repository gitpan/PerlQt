/*
 * PProgressDialog definitions.
 *
 * Copyright (C) 1997, Ashley Winters <jql@accessone.com>
 *
 * You may distribute under the terms of the LGPL as specified in the
 * README file
 */

#include "pprogdlg.h"

const char *PProgressDialog::className() const {
    return PObject_className();
}

bool PProgressDialog::event(QEvent *event) {
    bool ret = PObject_event(event);
    if(pfailed) ret = QProgressDialog::event(event);
    return ret;
}

bool PProgressDialog::eventFilter(QObject *obj, QEvent *event) {
    bool ret = PObject_eventFilter(obj, event);
    if(pfailed) ret = QProgressDialog::eventFilter(obj, event);
    return ret;
}

QMetaObject *PProgressDialog::metaObject() const {
    QMetaObject *ret = PObject_metaObject();
    if(pfailed) ret = QProgressDialog::metaObject();
    return ret;
}

void PProgressDialog::initMetaObject() {
    if(!QProgressDialog::metaObject()) QProgressDialog::initMetaObject();
    PObject_initMetaObject();
}

void PProgressDialog::timerEvent(QTimerEvent *event) {
    PObject_timerEvent(event);
    if(pfailed) QProgressDialog::timerEvent(event);
}


void PProgressDialog::adjustSize() {
    PWidget_adjustSize();
    if(pfailed) QProgressDialog::adjustSize();
}

bool PProgressDialog::close(bool b) {
    bool ret = PWidget_close(b);
    if(pfailed) ret = QProgressDialog::close(b);
    return ret;
}

void PProgressDialog::hide() {
    PWidget_hide();
    if(pfailed) QProgressDialog::hide();
}

void PProgressDialog::move(int x, int y) {
    PWidget_move(x, y);
    if(pfailed) QProgressDialog::move(x, y);
}

void PProgressDialog::resize(int w, int h) {
    PWidget_resize(w, h);
    if(pfailed) QProgressDialog::resize(w, h);
}

void PProgressDialog::setBackgroundColor(const QColor &c) {
    PWidget_setBackgroundColor(c);
    if(pfailed) QProgressDialog::setBackgroundColor(c);
}

void PProgressDialog::setBackgroundPixmap(const QPixmap &p) {
    PWidget_setBackgroundPixmap(p);
    if(pfailed) QProgressDialog::setBackgroundPixmap(p);
}

void PProgressDialog::setCursor(const QCursor &c) {
    PWidget_setCursor(c);
    if(pfailed) QProgressDialog::setCursor(c);
}

void PProgressDialog::setEnabled(bool b) {
    PWidget_setEnabled(b);
    if(pfailed) QProgressDialog::setEnabled(b);
}

void PProgressDialog::setFont(const QFont &f) {
    PWidget_setFont(f);
    if(pfailed) QProgressDialog::setFont(f);
}

void PProgressDialog::setGeometry(int x, int y, int w, int h) {
    PWidget_setGeometry(x, y, w, h);
    if(pfailed) QProgressDialog::setGeometry(x, y, w, h);
}

void PProgressDialog::setPalette(const QPalette &p) {
    PWidget_setPalette(p);
    if(pfailed) QProgressDialog::setPalette(p);
}

void PProgressDialog::setStyle(GUIStyle s) {
    PWidget_setStyle(s);
    if(pfailed) QProgressDialog::setStyle(s);
}

void PProgressDialog::show() {
    PWidget_show();
    if(pfailed) QProgressDialog::show();
}

QSize PProgressDialog::sizeHint() const {
    QSize ret = PWidget_sizeHint();
    if(pfailed) ret = QProgressDialog::sizeHint();
    return ret;
}

void PProgressDialog::closeEvent(QCloseEvent *event) {
    PWidget_closeEvent(event);
    if(pfailed) QProgressDialog::closeEvent(event);
}

void PProgressDialog::enterEvent(QEvent *event) {
    PWidget_enterEvent(event);
    if(pfailed) QProgressDialog::enterEvent(event);
}

void PProgressDialog::focusInEvent(QFocusEvent *event) {
    PWidget_focusInEvent(event);
    if(pfailed) QProgressDialog::focusInEvent(event);
}

void PProgressDialog::focusOutEvent(QFocusEvent *event) {
    PWidget_focusOutEvent(event);
    if(pfailed) QProgressDialog::focusOutEvent(event);
}

void PProgressDialog::keyPressEvent(QKeyEvent *event) {
    PWidget_keyPressEvent(event);
    if(pfailed) QProgressDialog::keyPressEvent(event);
}

void PProgressDialog::keyReleaseEvent(QKeyEvent *event) {
    PWidget_keyReleaseEvent(event);
    if(pfailed) QProgressDialog::keyReleaseEvent(event);
}

void PProgressDialog::leaveEvent(QEvent *event) {
    PWidget_leaveEvent(event);
    if(pfailed) QProgressDialog::leaveEvent(event);
}

void PProgressDialog::mouseDoubleClickEvent(QMouseEvent *event) {
    PWidget_mouseDoubleClickEvent(event);
    if(pfailed) QProgressDialog::mouseDoubleClickEvent(event);
}

void PProgressDialog::mouseMoveEvent(QMouseEvent *event) {
    PWidget_mouseMoveEvent(event);
    if(pfailed) QProgressDialog::mouseMoveEvent(event);
}

void PProgressDialog::mousePressEvent(QMouseEvent *event) {
    PWidget_mousePressEvent(event);
    if(pfailed) QProgressDialog::mousePressEvent(event);
}

void PProgressDialog::mouseReleaseEvent(QMouseEvent *event) {
    PWidget_mouseReleaseEvent(event);
    if(pfailed) QProgressDialog::mouseReleaseEvent(event);
}

void PProgressDialog::moveEvent(QMoveEvent *event) {
    PWidget_moveEvent(event);
    if(pfailed) QProgressDialog::moveEvent(event);
}

void PProgressDialog::paintEvent(QPaintEvent *event) {
    PWidget_paintEvent(event);
    if(pfailed) QProgressDialog::paintEvent(event);
}

void PProgressDialog::resizeEvent(QResizeEvent *event) {
    PWidget_resizeEvent(event);
    if(pfailed) QProgressDialog::resizeEvent(event);
}


