/*
 * PFileDialog definitions.
 *
 * Copyright (C) 1997, Ashley Winters <jql@accessone.com>
 *
 * You may distribute under the terms of the LGPL as specified in the
 * README file
 */

#include "pfiledlg.h"

const char *PFileDialog::className() const {
    return PObject_className();
}

bool PFileDialog::event(QEvent *event) {
    bool ret = PObject_event(event);
    if(pfailed) ret = QFileDialog::event(event);
    return ret;
}

bool PFileDialog::eventFilter(QObject *obj, QEvent *event) {
    bool ret = PObject_eventFilter(obj, event);
    if(pfailed) ret = QFileDialog::eventFilter(obj, event);
    return ret;
}

QMetaObject *PFileDialog::metaObject() const {
    QMetaObject *ret = PObject_metaObject();
    if(pfailed) ret = QFileDialog::metaObject();
    return ret;
}

void PFileDialog::initMetaObject() {
    if(!QFileDialog::metaObject()) QFileDialog::initMetaObject();
    PObject_initMetaObject();
}

void PFileDialog::timerEvent(QTimerEvent *event) {
    PObject_timerEvent(event);
    if(pfailed) QFileDialog::timerEvent(event);
}


void PFileDialog::adjustSize() {
    PWidget_adjustSize();
    if(pfailed) QFileDialog::adjustSize();
}

bool PFileDialog::close(bool b) {
    bool ret = PWidget_close(b);
    if(pfailed) ret = QFileDialog::close(b);
    return ret;
}

void PFileDialog::hide() {
    PWidget_hide();
    if(pfailed) QFileDialog::hide();
}

void PFileDialog::move(int x, int y) {
    PWidget_move(x, y);
    if(pfailed) QFileDialog::move(x, y);
}

void PFileDialog::resize(int w, int h) {
    PWidget_resize(w, h);
    if(pfailed) QFileDialog::resize(w, h);
}

void PFileDialog::setBackgroundColor(const QColor &c) {
    PWidget_setBackgroundColor(c);
    if(pfailed) QFileDialog::setBackgroundColor(c);
}

void PFileDialog::setBackgroundPixmap(const QPixmap &p) {
    PWidget_setBackgroundPixmap(p);
    if(pfailed) QFileDialog::setBackgroundPixmap(p);
}

void PFileDialog::setCursor(const QCursor &c) {
    PWidget_setCursor(c);
    if(pfailed) QFileDialog::setCursor(c);
}

void PFileDialog::setEnabled(bool b) {
    PWidget_setEnabled(b);
    if(pfailed) QFileDialog::setEnabled(b);
}

void PFileDialog::setFont(const QFont &f) {
    PWidget_setFont(f);
    if(pfailed) QFileDialog::setFont(f);
}

void PFileDialog::setGeometry(int x, int y, int w, int h) {
    PWidget_setGeometry(x, y, w, h);
    if(pfailed) QFileDialog::setGeometry(x, y, w, h);
}

void PFileDialog::setPalette(const QPalette &p) {
    PWidget_setPalette(p);
    if(pfailed) QFileDialog::setPalette(p);
}

void PFileDialog::setStyle(GUIStyle s) {
    PWidget_setStyle(s);
    if(pfailed) QFileDialog::setStyle(s);
}

void PFileDialog::show() {
    PWidget_show();
    if(pfailed) QFileDialog::show();
}

QSize PFileDialog::sizeHint() const {
    QSize ret = PWidget_sizeHint();
    if(pfailed) ret = QFileDialog::sizeHint();
    return ret;
}

void PFileDialog::closeEvent(QCloseEvent *event) {
    PWidget_closeEvent(event);
    if(pfailed) QFileDialog::closeEvent(event);
}

void PFileDialog::enterEvent(QEvent *event) {
    PWidget_enterEvent(event);
    if(pfailed) QFileDialog::enterEvent(event);
}

void PFileDialog::focusInEvent(QFocusEvent *event) {
    PWidget_focusInEvent(event);
    if(pfailed) QFileDialog::focusInEvent(event);
}

void PFileDialog::focusOutEvent(QFocusEvent *event) {
    PWidget_focusOutEvent(event);
    if(pfailed) QFileDialog::focusOutEvent(event);
}

void PFileDialog::keyPressEvent(QKeyEvent *event) {
    PWidget_keyPressEvent(event);
    if(pfailed) QFileDialog::keyPressEvent(event);
}

void PFileDialog::keyReleaseEvent(QKeyEvent *event) {
    PWidget_keyReleaseEvent(event);
    if(pfailed) QFileDialog::keyReleaseEvent(event);
}

void PFileDialog::leaveEvent(QEvent *event) {
    PWidget_leaveEvent(event);
    if(pfailed) QFileDialog::leaveEvent(event);
}

void PFileDialog::mouseDoubleClickEvent(QMouseEvent *event) {
    PWidget_mouseDoubleClickEvent(event);
    if(pfailed) QFileDialog::mouseDoubleClickEvent(event);
}

void PFileDialog::mouseMoveEvent(QMouseEvent *event) {
    PWidget_mouseMoveEvent(event);
    if(pfailed) QFileDialog::mouseMoveEvent(event);
}

void PFileDialog::mousePressEvent(QMouseEvent *event) {
    PWidget_mousePressEvent(event);
    if(pfailed) QFileDialog::mousePressEvent(event);
}

void PFileDialog::mouseReleaseEvent(QMouseEvent *event) {
    PWidget_mouseReleaseEvent(event);
    if(pfailed) QFileDialog::mouseReleaseEvent(event);
}

void PFileDialog::moveEvent(QMoveEvent *event) {
    PWidget_moveEvent(event);
    if(pfailed) QFileDialog::moveEvent(event);
}

void PFileDialog::paintEvent(QPaintEvent *event) {
    PWidget_paintEvent(event);
    if(pfailed) QFileDialog::paintEvent(event);
}

void PFileDialog::resizeEvent(QResizeEvent *event) {
    PWidget_resizeEvent(event);
    if(pfailed) QFileDialog::resizeEvent(event);
}


void PFileDialog::done(int result) {
    PDialog_done(result);
    if(pfailed) QFileDialog::done(result);
}


