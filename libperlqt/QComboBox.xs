/*
 * PComboBox definitions.
 *
 * Copyright (C) 1997, Ashley Winters <jql@accessone.com>
 *
 * You may distribute under the terms of the LGPL as specified in the
 * README file
 */

#include "pcombo.h"

const char *PComboBox::className() const {
    return PObject_className();
}

bool PComboBox::event(QEvent *event) {
    bool ret = PObject_event(event);
    if(pfailed) ret = QComboBox::event(event);
    return ret;
}

bool PComboBox::eventFilter(QObject *obj, QEvent *event) {
    bool ret = PObject_eventFilter(obj, event);
//  if(pfailed) ret = QComboBox::eventFilter(obj, event);	// AHHH!!!!!
    if(pfailed) ret = QObject::eventFilter(obj, event);		// FIX ME!
    return ret;
}

QMetaObject *PComboBox::metaObject() const {
    QMetaObject *ret = PObject_metaObject();
    if(pfailed) ret = QComboBox::metaObject();
    return ret;
}

void PComboBox::initMetaObject() {
    if(!QComboBox::metaObject()) QComboBox::initMetaObject();
    PObject_initMetaObject();
}

void PComboBox::timerEvent(QTimerEvent *event) {
    PObject_timerEvent(event);
    if(pfailed) QComboBox::timerEvent(event);
}


void PComboBox::adjustSize() {
    PWidget_adjustSize();
    if(pfailed) QComboBox::adjustSize();
}

bool PComboBox::close(bool b) {
    bool ret = PWidget_close(b);
    if(pfailed) ret = QComboBox::close(b);
    return ret;
}

void PComboBox::hide() {
    PWidget_hide();
    if(pfailed) QComboBox::hide();
}

void PComboBox::move(int x, int y) {
    PWidget_move(x, y);
    if(pfailed) QComboBox::move(x, y);
}

void PComboBox::resize(int w, int h) {
    PWidget_resize(w, h);
    if(pfailed) QComboBox::resize(w, h);
}

void PComboBox::setBackgroundColor(const QColor &c) {
    PWidget_setBackgroundColor(c);
    if(pfailed) QComboBox::setBackgroundColor(c);
}

void PComboBox::setBackgroundPixmap(const QPixmap &p) {
    PWidget_setBackgroundPixmap(p);
    if(pfailed) QComboBox::setBackgroundPixmap(p);
}

void PComboBox::setCursor(const QCursor &c) {
    PWidget_setCursor(c);
    if(pfailed) QComboBox::setCursor(c);
}

void PComboBox::setEnabled(bool b) {
    PWidget_setEnabled(b);
    if(pfailed) QComboBox::setEnabled(b);
}

void PComboBox::setFont(const QFont &f) {
    PWidget_setFont(f);
    if(pfailed) QComboBox::setFont(f);
}

void PComboBox::setGeometry(int x, int y, int w, int h) {
    PWidget_setGeometry(x, y, w, h);
    if(pfailed) QComboBox::setGeometry(x, y, w, h);
}

void PComboBox::setPalette(const QPalette &p) {
    PWidget_setPalette(p);
    if(pfailed) QComboBox::setPalette(p);
}

void PComboBox::setStyle(GUIStyle s) {
    PWidget_setStyle(s);
    if(pfailed) QComboBox::setStyle(s);
}

void PComboBox::show() {
    PWidget_show();
    if(pfailed) QComboBox::show();
}

QSize PComboBox::sizeHint() const {
    QSize ret = PWidget_sizeHint();
    if(pfailed) ret = QComboBox::sizeHint();
    return ret;
}

void PComboBox::closeEvent(QCloseEvent *event) {
    PWidget_closeEvent(event);
    if(pfailed) QComboBox::closeEvent(event);
}

void PComboBox::enterEvent(QEvent *event) {
    PWidget_enterEvent(event);
    if(pfailed) QComboBox::enterEvent(event);
}

void PComboBox::focusInEvent(QFocusEvent *event) {
    PWidget_focusInEvent(event);
    if(pfailed) QComboBox::focusInEvent(event);
}

void PComboBox::focusOutEvent(QFocusEvent *event) {
    PWidget_focusOutEvent(event);
    if(pfailed) QComboBox::focusOutEvent(event);
}

void PComboBox::keyPressEvent(QKeyEvent *event) {
    PWidget_keyPressEvent(event);
    if(pfailed) QComboBox::keyPressEvent(event);
}

void PComboBox::keyReleaseEvent(QKeyEvent *event) {
    PWidget_keyReleaseEvent(event);
    if(pfailed) QComboBox::keyReleaseEvent(event);
}

void PComboBox::leaveEvent(QEvent *event) {
    PWidget_leaveEvent(event);
    if(pfailed) QComboBox::leaveEvent(event);
}

void PComboBox::mouseDoubleClickEvent(QMouseEvent *event) {
    PWidget_mouseDoubleClickEvent(event);
    if(pfailed) QComboBox::mouseDoubleClickEvent(event);
}

void PComboBox::mouseMoveEvent(QMouseEvent *event) {
    PWidget_mouseMoveEvent(event);
    if(pfailed) QComboBox::mouseMoveEvent(event);
}

void PComboBox::mousePressEvent(QMouseEvent *event) {
    PWidget_mousePressEvent(event);
    if(pfailed) QComboBox::mousePressEvent(event);
}

void PComboBox::mouseReleaseEvent(QMouseEvent *event) {
    PWidget_mouseReleaseEvent(event);
    if(pfailed) QComboBox::mouseReleaseEvent(event);
}

void PComboBox::moveEvent(QMoveEvent *event) {
    PWidget_moveEvent(event);
    if(pfailed) QComboBox::moveEvent(event);
}

void PComboBox::paintEvent(QPaintEvent *event) {
    PWidget_paintEvent(event);
    if(pfailed) QComboBox::paintEvent(event);
}

void PComboBox::resizeEvent(QResizeEvent *event) {
    PWidget_resizeEvent(event);
    if(pfailed) QComboBox::resizeEvent(event);
}


