/*
 * PLabel definitions.
 *
 * Copyright (C) 1997, Ashley Winters <jql@accessone.com>
 *
 * You may distribute under the terms of the LGPL as specified in the
 * README file
 */

#include "plabel.h"

const char *PLabel::className() const {
    return PObject_className();
}

bool PLabel::event(QEvent *event) {
    bool ret = PObject_event(event);
    if(pfailed) ret = QLabel::event(event);
    return ret;
}

bool PLabel::eventFilter(QObject *obj, QEvent *event) {
    bool ret = PObject_eventFilter(obj, event);
    if(pfailed) ret = QLabel::eventFilter(obj, event);
    return ret;
}

QMetaObject *PLabel::metaObject() const {
    QMetaObject *ret = PObject_metaObject();
    if(pfailed) ret = QLabel::metaObject();
    return ret;
}

void PLabel::initMetaObject() {
    if(!QLabel::metaObject()) QLabel::initMetaObject();
    PObject_initMetaObject();
}

void PLabel::timerEvent(QTimerEvent *event) {
    PObject_timerEvent(event);
    if(pfailed) QLabel::timerEvent(event);
}


void PLabel::adjustSize() {
    PWidget_adjustSize();
    if(pfailed) QLabel::adjustSize();
}

bool PLabel::close(bool b) {
    bool ret = PWidget_close(b);
    if(pfailed) ret = QLabel::close(b);
    return ret;
}

void PLabel::hide() {
    PWidget_hide();
    if(pfailed) QLabel::hide();
}

void PLabel::move(int x, int y) {
    PWidget_move(x, y);
    if(pfailed) QLabel::move(x, y);
}

void PLabel::resize(int w, int h) {
    PWidget_resize(w, h);
    if(pfailed) QLabel::resize(w, h);
}

void PLabel::setBackgroundColor(const QColor &c) {
    PWidget_setBackgroundColor(c);
    if(pfailed) QLabel::setBackgroundColor(c);
}

void PLabel::setBackgroundPixmap(const QPixmap &p) {
    PWidget_setBackgroundPixmap(p);
    if(pfailed) QLabel::setBackgroundPixmap(p);
}

void PLabel::setCursor(const QCursor &c) {
    PWidget_setCursor(c);
    if(pfailed) QLabel::setCursor(c);
}

void PLabel::setEnabled(bool b) {
    PWidget_setEnabled(b);
    if(pfailed) QLabel::setEnabled(b);
}

void PLabel::setFont(const QFont &f) {
    PWidget_setFont(f);
    if(pfailed) QLabel::setFont(f);
}

void PLabel::setGeometry(int x, int y, int w, int h) {
    PWidget_setGeometry(x, y, w, h);
    if(pfailed) QLabel::setGeometry(x, y, w, h);
}

void PLabel::setPalette(const QPalette &p) {
    PWidget_setPalette(p);
    if(pfailed) QLabel::setPalette(p);
}

void PLabel::setStyle(GUIStyle s) {
    PWidget_setStyle(s);
    if(pfailed) QLabel::setStyle(s);
}

void PLabel::show() {
    PWidget_show();
    if(pfailed) QLabel::show();
}

QSize PLabel::sizeHint() const {
    QSize ret = PWidget_sizeHint();
    if(pfailed) ret = QLabel::sizeHint();
    return ret;
}

void PLabel::closeEvent(QCloseEvent *event) {
    PWidget_closeEvent(event);
    if(pfailed) QLabel::closeEvent(event);
}

void PLabel::enterEvent(QEvent *event) {
    PWidget_enterEvent(event);
    if(pfailed) QLabel::enterEvent(event);
}

void PLabel::focusInEvent(QFocusEvent *event) {
    PWidget_focusInEvent(event);
    if(pfailed) QLabel::focusInEvent(event);
}

void PLabel::focusOutEvent(QFocusEvent *event) {
    PWidget_focusOutEvent(event);
    if(pfailed) QLabel::focusOutEvent(event);
}

void PLabel::keyPressEvent(QKeyEvent *event) {
    PWidget_keyPressEvent(event);
    if(pfailed) QLabel::keyPressEvent(event);
}

void PLabel::keyReleaseEvent(QKeyEvent *event) {
    PWidget_keyReleaseEvent(event);
    if(pfailed) QLabel::keyReleaseEvent(event);
}

void PLabel::leaveEvent(QEvent *event) {
    PWidget_leaveEvent(event);
    if(pfailed) QLabel::leaveEvent(event);
}

void PLabel::mouseDoubleClickEvent(QMouseEvent *event) {
    PWidget_mouseDoubleClickEvent(event);
    if(pfailed) QLabel::mouseDoubleClickEvent(event);
}

void PLabel::mouseMoveEvent(QMouseEvent *event) {
    PWidget_mouseMoveEvent(event);
    if(pfailed) QLabel::mouseMoveEvent(event);
}

void PLabel::mousePressEvent(QMouseEvent *event) {
    PWidget_mousePressEvent(event);
    if(pfailed) QLabel::mousePressEvent(event);
}

void PLabel::mouseReleaseEvent(QMouseEvent *event) {
    PWidget_mouseReleaseEvent(event);
    if(pfailed) QLabel::mouseReleaseEvent(event);
}

void PLabel::moveEvent(QMoveEvent *event) {
    PWidget_moveEvent(event);
    if(pfailed) QLabel::moveEvent(event);
}

void PLabel::paintEvent(QPaintEvent *event) {
    PWidget_paintEvent(event);
    if(pfailed) QLabel::paintEvent(event);
}

void PLabel::resizeEvent(QResizeEvent *event) {
    PWidget_resizeEvent(event);
    if(pfailed) QLabel::resizeEvent(event);
}


void PLabel::drawContents(QPainter *p) {
    PFrame_drawContents(p);
    if(pfailed) QLabel::drawContents(p);
}

void PLabel::drawFrame(QPainter *p) {
    PFrame_drawFrame(p);
    if(pfailed) QLabel::drawFrame(p);
}

void PLabel::frameChanged() {
    PFrame_frameChanged();
    if(pfailed) QLabel::frameChanged();
}


