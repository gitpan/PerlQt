/*
 * PFrame definitions.
 *
 * Copyright (C) 1997, Ashley Winters <jql@accessone.com>
 *
 * You may distribute under the terms of the LGPL as specified in the
 * README file
 */

#include "pframe.h"

const char *PFrame::className() const {
    return PObject_className();
}

bool PFrame::event(QEvent *event) {
    bool ret = PObject_event(event);
    if(pfailed) ret = QFrame::event(event);
    return ret;
}

bool PFrame::eventFilter(QObject *obj, QEvent *event) {
    bool ret = PObject_eventFilter(obj, event);
    if(pfailed) ret = QFrame::eventFilter(obj, event);
    return ret;
}

QMetaObject *PFrame::metaObject() const {
    QMetaObject *ret = PObject_metaObject();
    if(pfailed) ret = QFrame::metaObject();
    return ret;
}

void PFrame::initMetaObject() {
    if(!QFrame::metaObject()) QFrame::initMetaObject();
    PObject_initMetaObject();
}

void PFrame::timerEvent(QTimerEvent *event) {
    PObject_timerEvent(event);
    if(pfailed) QFrame::timerEvent(event);
}


void PFrame::adjustSize() {
    PWidget_adjustSize();
    if(pfailed) QFrame::adjustSize();
}

bool PFrame::close(bool b) {
    bool ret = PWidget_close(b);
    if(pfailed) ret = QFrame::close(b);
    return ret;
}

void PFrame::hide() {
    PWidget_hide();
    if(pfailed) QFrame::hide();
}

void PFrame::move(int x, int y) {
    PWidget_move(x, y);
    if(pfailed) QFrame::move(x, y);
}

void PFrame::resize(int w, int h) {
    PWidget_resize(w, h);
    if(pfailed) QFrame::resize(w, h);
}

void PFrame::setBackgroundColor(const QColor &c) {
    PWidget_setBackgroundColor(c);
    if(pfailed) QFrame::setBackgroundColor(c);
}

void PFrame::setBackgroundPixmap(const QPixmap &p) {
    PWidget_setBackgroundPixmap(p);
    if(pfailed) QFrame::setBackgroundPixmap(p);
}

void PFrame::setCursor(const QCursor &c) {
    PWidget_setCursor(c);
    if(pfailed) QFrame::setCursor(c);
}

void PFrame::setEnabled(bool b) {
    PWidget_setEnabled(b);
    if(pfailed) QFrame::setEnabled(b);
}

void PFrame::setFont(const QFont &f) {
    PWidget_setFont(f);
    if(pfailed) QFrame::setFont(f);
}

void PFrame::setGeometry(int x, int y, int w, int h) {
    PWidget_setGeometry(x, y, w, h);
    if(pfailed) QFrame::setGeometry(x, y, w, h);
}

void PFrame::setPalette(const QPalette &p) {
    PWidget_setPalette(p);
    if(pfailed) QFrame::setPalette(p);
}

void PFrame::setStyle(GUIStyle s) {
    PWidget_setStyle(s);
    if(pfailed) QFrame::setStyle(s);
}

void PFrame::show() {
    PWidget_show();
    if(pfailed) QFrame::show();
}

QSize PFrame::sizeHint() const {
    QSize ret = PWidget_sizeHint();
    if(pfailed) ret = QFrame::sizeHint();
    return ret;
}

void PFrame::closeEvent(QCloseEvent *event) {
    PWidget_closeEvent(event);
    if(pfailed) QFrame::closeEvent(event);
}

void PFrame::enterEvent(QEvent *event) {
    PWidget_enterEvent(event);
    if(pfailed) QFrame::enterEvent(event);
}

void PFrame::focusInEvent(QFocusEvent *event) {
    PWidget_focusInEvent(event);
    if(pfailed) QFrame::focusInEvent(event);
}

void PFrame::focusOutEvent(QFocusEvent *event) {
    PWidget_focusOutEvent(event);
    if(pfailed) QFrame::focusOutEvent(event);
}

void PFrame::keyPressEvent(QKeyEvent *event) {
    PWidget_keyPressEvent(event);
    if(pfailed) QFrame::keyPressEvent(event);
}

void PFrame::keyReleaseEvent(QKeyEvent *event) {
    PWidget_keyReleaseEvent(event);
    if(pfailed) QFrame::keyReleaseEvent(event);
}

void PFrame::leaveEvent(QEvent *event) {
    PWidget_leaveEvent(event);
    if(pfailed) QFrame::leaveEvent(event);
}

void PFrame::mouseDoubleClickEvent(QMouseEvent *event) {
    PWidget_mouseDoubleClickEvent(event);
    if(pfailed) QFrame::mouseDoubleClickEvent(event);
}

void PFrame::mouseMoveEvent(QMouseEvent *event) {
    PWidget_mouseMoveEvent(event);
    if(pfailed) QFrame::mouseMoveEvent(event);
}

void PFrame::mousePressEvent(QMouseEvent *event) {
    PWidget_mousePressEvent(event);
    if(pfailed) QFrame::mousePressEvent(event);
}

void PFrame::mouseReleaseEvent(QMouseEvent *event) {
    PWidget_mouseReleaseEvent(event);
    if(pfailed) QFrame::mouseReleaseEvent(event);
}

void PFrame::moveEvent(QMoveEvent *event) {
    PWidget_moveEvent(event);
    if(pfailed) QFrame::moveEvent(event);
}

void PFrame::paintEvent(QPaintEvent *event) {
    PWidget_paintEvent(event);
    if(pfailed) QFrame::paintEvent(event);
}

void PFrame::resizeEvent(QResizeEvent *event) {
    PWidget_resizeEvent(event);
    if(pfailed) QFrame::resizeEvent(event);
}


void PFrame::drawContents(QPainter *p) {
    PFrame_drawContents(p);
    if(pfailed) QFrame::drawContents(p);
}

void PFrame::drawFrame(QPainter *p) {
    PFrame_drawFrame(p);
    if(pfailed) QFrame::drawFrame(p);
}

void PFrame::frameChanged() {
    PFrame_frameChanged();
    if(pfailed) QFrame::frameChanged();
}


void PFrame_virtualize::PFrame_drawContents(QPainter *p) {
    voidCallObj("drawContents", p, "QPainter");
}

void PFrame_virtualize::PFrame_drawFrame(QPainter *p) {
    voidCallObj("drawFrame", p, "QPainter");
}

void PFrame_virtualize::PFrame_frameChanged() {
    voidCall("frameChanged");
}
