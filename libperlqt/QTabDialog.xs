/*
 * PTabDialog definitions.
 *
 * Copyright (C) 1997, Ashley Winters <jql@accessone.com>
 *
 * You may distribute under the terms of the LGPL as specified in the
 * README file
 */

#include "ptabdlg.h"

const char *PTabDialog::className() const {
    return PObject_className();
}

bool PTabDialog::event(QEvent *event) {
    bool ret = PObject_event(event);
    if(pfailed) ret = QTabDialog::event(event);
    return ret;
}

bool PTabDialog::eventFilter(QObject *obj, QEvent *event) {
    bool ret = PObject_eventFilter(obj, event);
    if(pfailed) ret = QTabDialog::eventFilter(obj, event);
    return ret;
}

QMetaObject *PTabDialog::metaObject() const {
    QMetaObject *ret = PObject_metaObject();
    if(pfailed) ret = QTabDialog::metaObject();
    return ret;
}

void PTabDialog::initMetaObject() {
    if(!QTabDialog::metaObject()) QTabDialog::initMetaObject();
    PObject_initMetaObject();
}

void PTabDialog::timerEvent(QTimerEvent *event) {
    PObject_timerEvent(event);
    if(pfailed) QTabDialog::timerEvent(event);
}


void PTabDialog::adjustSize() {
    PWidget_adjustSize();
    if(pfailed) QTabDialog::adjustSize();
}

bool PTabDialog::close(bool b) {
    bool ret = PWidget_close(b);
    if(pfailed) ret = QTabDialog::close(b);
    return ret;
}

void PTabDialog::hide() {
    PWidget_hide();
    if(pfailed) QTabDialog::hide();
}

void PTabDialog::move(int x, int y) {
    PWidget_move(x, y);
    if(pfailed) QTabDialog::move(x, y);
}

void PTabDialog::resize(int w, int h) {
    PWidget_resize(w, h);
    if(pfailed) QTabDialog::resize(w, h);
}

void PTabDialog::setBackgroundColor(const QColor &c) {
    PWidget_setBackgroundColor(c);
    if(pfailed) QTabDialog::setBackgroundColor(c);
}

void PTabDialog::setBackgroundPixmap(const QPixmap &p) {
    PWidget_setBackgroundPixmap(p);
    if(pfailed) QTabDialog::setBackgroundPixmap(p);
}

void PTabDialog::setCursor(const QCursor &c) {
    PWidget_setCursor(c);
    if(pfailed) QTabDialog::setCursor(c);
}

void PTabDialog::setEnabled(bool b) {
    PWidget_setEnabled(b);
    if(pfailed) QTabDialog::setEnabled(b);
}

void PTabDialog::setFont(const QFont &f) {
    PWidget_setFont(f);
    if(pfailed) QTabDialog::setFont(f);
}

void PTabDialog::setGeometry(int x, int y, int w, int h) {
    PWidget_setGeometry(x, y, w, h);
    if(pfailed) QTabDialog::setGeometry(x, y, w, h);
}

void PTabDialog::setPalette(const QPalette &p) {
    PWidget_setPalette(p);
    if(pfailed) QTabDialog::setPalette(p);
}

void PTabDialog::setStyle(GUIStyle s) {
    PWidget_setStyle(s);
    if(pfailed) QTabDialog::setStyle(s);
}

void PTabDialog::show() {
    PWidget_show();
    if(pfailed) QTabDialog::show();
}

QSize PTabDialog::sizeHint() const {
    QSize ret = PWidget_sizeHint();
    if(pfailed) ret = QTabDialog::sizeHint();
    return ret;
}

void PTabDialog::closeEvent(QCloseEvent *event) {
    PWidget_closeEvent(event);
    if(pfailed) QTabDialog::closeEvent(event);
}

void PTabDialog::enterEvent(QEvent *event) {
    PWidget_enterEvent(event);
    if(pfailed) QTabDialog::enterEvent(event);
}

void PTabDialog::focusInEvent(QFocusEvent *event) {
    PWidget_focusInEvent(event);
    if(pfailed) QTabDialog::focusInEvent(event);
}

void PTabDialog::focusOutEvent(QFocusEvent *event) {
    PWidget_focusOutEvent(event);
    if(pfailed) QTabDialog::focusOutEvent(event);
}

void PTabDialog::keyPressEvent(QKeyEvent *event) {
    PWidget_keyPressEvent(event);
    if(pfailed) QTabDialog::keyPressEvent(event);
}

void PTabDialog::keyReleaseEvent(QKeyEvent *event) {
    PWidget_keyReleaseEvent(event);
    if(pfailed) QTabDialog::keyReleaseEvent(event);
}

void PTabDialog::leaveEvent(QEvent *event) {
    PWidget_leaveEvent(event);
    if(pfailed) QTabDialog::leaveEvent(event);
}

void PTabDialog::mouseDoubleClickEvent(QMouseEvent *event) {
    PWidget_mouseDoubleClickEvent(event);
    if(pfailed) QTabDialog::mouseDoubleClickEvent(event);
}

void PTabDialog::mouseMoveEvent(QMouseEvent *event) {
    PWidget_mouseMoveEvent(event);
    if(pfailed) QTabDialog::mouseMoveEvent(event);
}

void PTabDialog::mousePressEvent(QMouseEvent *event) {
    PWidget_mousePressEvent(event);
    if(pfailed) QTabDialog::mousePressEvent(event);
}

void PTabDialog::mouseReleaseEvent(QMouseEvent *event) {
    PWidget_mouseReleaseEvent(event);
    if(pfailed) QTabDialog::mouseReleaseEvent(event);
}

void PTabDialog::moveEvent(QMoveEvent *event) {
    PWidget_moveEvent(event);
    if(pfailed) QTabDialog::moveEvent(event);
}

void PTabDialog::paintEvent(QPaintEvent *event) {
    PWidget_paintEvent(event);
    if(pfailed) QTabDialog::paintEvent(event);
}

void PTabDialog::resizeEvent(QResizeEvent *event) {
    PWidget_resizeEvent(event);
    if(pfailed) QTabDialog::resizeEvent(event);
}


void PTabDialog::done(int result) {
    PDialog_done(result);
    if(pfailed) QTabDialog::done(result);
}


