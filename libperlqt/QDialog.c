/*
 * PDialog definitions.
 *
 * Copyright (C) 1997, Ashley Winters <jql@accessone.com>
 *
 * You may distribute under the terms of the LGPL as specified in the
 * README file
 */

#include "pdialog.h"

const char *PDialog::className() const {
    return PObject_className();
}

bool PDialog::event(QEvent *event) {
    bool ret = PObject_event(event);
    if(pfailed) ret = QDialog::event(event);
    return ret;
}

bool PDialog::eventFilter(QObject *obj, QEvent *event) {
    bool ret = PObject_eventFilter(obj, event);
    if(pfailed) ret = QDialog::eventFilter(obj, event);
    return ret;
}

QMetaObject *PDialog::metaObject() const {
    QMetaObject *ret = PObject_metaObject();
    if(pfailed) ret = QDialog::metaObject();
    return ret;
}

void PDialog::initMetaObject() {
    if(!QDialog::metaObject()) QDialog::initMetaObject();
    PObject_initMetaObject();
}

void PDialog::timerEvent(QTimerEvent *event) {
    PObject_timerEvent(event);
    if(pfailed) QDialog::timerEvent(event);
}


void PDialog::adjustSize() {
    PWidget_adjustSize();
    if(pfailed) QDialog::adjustSize();
}

bool PDialog::close(bool b) {
    bool ret = PWidget_close(b);
    if(pfailed) ret = QDialog::close(b);
    return ret;
}

void PDialog::hide() {
    PWidget_hide();
    if(pfailed) QDialog::hide();
}

void PDialog::move(int x, int y) {
    PWidget_move(x, y);
    if(pfailed) QDialog::move(x, y);
}

void PDialog::resize(int w, int h) {
    PWidget_resize(w, h);
    if(pfailed) QDialog::resize(w, h);
}

void PDialog::setBackgroundColor(const QColor &c) {
    PWidget_setBackgroundColor(c);
    if(pfailed) QDialog::setBackgroundColor(c);
}

void PDialog::setBackgroundPixmap(const QPixmap &p) {
    PWidget_setBackgroundPixmap(p);
    if(pfailed) QDialog::setBackgroundPixmap(p);
}

void PDialog::setCursor(const QCursor &c) {
    PWidget_setCursor(c);
    if(pfailed) QDialog::setCursor(c);
}

void PDialog::setEnabled(bool b) {
    PWidget_setEnabled(b);
    if(pfailed) QDialog::setEnabled(b);
}

void PDialog::setFont(const QFont &f) {
    PWidget_setFont(f);
    if(pfailed) QDialog::setFont(f);
}

void PDialog::setGeometry(int x, int y, int w, int h) {
    PWidget_setGeometry(x, y, w, h);
    if(pfailed) QDialog::setGeometry(x, y, w, h);
}

void PDialog::setPalette(const QPalette &p) {
    PWidget_setPalette(p);
    if(pfailed) QDialog::setPalette(p);
}

void PDialog::setStyle(GUIStyle s) {
    PWidget_setStyle(s);
    if(pfailed) QDialog::setStyle(s);
}

void PDialog::show() {
    PWidget_show();
    if(pfailed) QDialog::show();
}

QSize PDialog::sizeHint() const {
    QSize ret = PWidget_sizeHint();
    if(pfailed) ret = QDialog::sizeHint();
    return ret;
}

void PDialog::closeEvent(QCloseEvent *event) {
    PWidget_closeEvent(event);
    if(pfailed) QDialog::closeEvent(event);
}

void PDialog::enterEvent(QEvent *event) {
    PWidget_enterEvent(event);
    if(pfailed) QDialog::enterEvent(event);
}

void PDialog::focusInEvent(QFocusEvent *event) {
    PWidget_focusInEvent(event);
    if(pfailed) QDialog::focusInEvent(event);
}

void PDialog::focusOutEvent(QFocusEvent *event) {
    PWidget_focusOutEvent(event);
    if(pfailed) QDialog::focusOutEvent(event);
}

void PDialog::keyPressEvent(QKeyEvent *event) {
    PWidget_keyPressEvent(event);
    if(pfailed) QDialog::keyPressEvent(event);
}

void PDialog::keyReleaseEvent(QKeyEvent *event) {
    PWidget_keyReleaseEvent(event);
    if(pfailed) QDialog::keyReleaseEvent(event);
}

void PDialog::leaveEvent(QEvent *event) {
    PWidget_leaveEvent(event);
    if(pfailed) QDialog::leaveEvent(event);
}

void PDialog::mouseDoubleClickEvent(QMouseEvent *event) {
    PWidget_mouseDoubleClickEvent(event);
    if(pfailed) QDialog::mouseDoubleClickEvent(event);
}

void PDialog::mouseMoveEvent(QMouseEvent *event) {
    PWidget_mouseMoveEvent(event);
    if(pfailed) QDialog::mouseMoveEvent(event);
}

void PDialog::mousePressEvent(QMouseEvent *event) {
    PWidget_mousePressEvent(event);
    if(pfailed) QDialog::mousePressEvent(event);
}

void PDialog::mouseReleaseEvent(QMouseEvent *event) {
    PWidget_mouseReleaseEvent(event);
    if(pfailed) QDialog::mouseReleaseEvent(event);
}

void PDialog::moveEvent(QMoveEvent *event) {
    PWidget_moveEvent(event);
    if(pfailed) QDialog::moveEvent(event);
}

void PDialog::paintEvent(QPaintEvent *event) {
    PWidget_paintEvent(event);
    if(pfailed) QDialog::paintEvent(event);
}

void PDialog::resizeEvent(QResizeEvent *event) {
    PWidget_resizeEvent(event);
    if(pfailed) QDialog::resizeEvent(event);
}


void PDialog::done(int result) {
    PDialog_done(result);
    if(pfailed) QDialog::done(result);
}


void PDialog_virtualize::PDialog_done(int result) { 
    SV *arg1 = newSViv(result);
    voidCall("done", arg1);
    SvREFCNT_dec(arg1);
}
