/*
 * PGroupBox definitions.
 *
 * Copyright (C) 1997, Ashley Winters <jql@accessone.com>
 *
 * You may distribute under the terms of the LGPL as specified in the
 * README file
 */

#include "pgrpbox.h"

const char *PGroupBox::className() const {
    return PObject_className();
}

bool PGroupBox::event(QEvent *event) {
    bool ret = PObject_event(event);
    if(pfailed) ret = QGroupBox::event(event);
    return ret;
}

bool PGroupBox::eventFilter(QObject *obj, QEvent *event) {
    bool ret = PObject_eventFilter(obj, event);
    if(pfailed) ret = QGroupBox::eventFilter(obj, event);
    return ret;
}

QMetaObject *PGroupBox::metaObject() const {
    QMetaObject *ret = PObject_metaObject();
    if(pfailed) ret = QGroupBox::metaObject();
    return ret;
}

void PGroupBox::initMetaObject() {
    if(!QGroupBox::metaObject()) QGroupBox::initMetaObject();
    PObject_initMetaObject();
}

void PGroupBox::timerEvent(QTimerEvent *event) {
    PObject_timerEvent(event);
    if(pfailed) QGroupBox::timerEvent(event);
}


void PGroupBox::adjustSize() {
    PWidget_adjustSize();
    if(pfailed) QGroupBox::adjustSize();
}

bool PGroupBox::close(bool b) {
    bool ret = PWidget_close(b);
    if(pfailed) ret = QGroupBox::close(b);
    return ret;
}

void PGroupBox::hide() {
    PWidget_hide();
    if(pfailed) QGroupBox::hide();
}

void PGroupBox::move(int x, int y) {
    PWidget_move(x, y);
    if(pfailed) QGroupBox::move(x, y);
}

void PGroupBox::resize(int w, int h) {
    PWidget_resize(w, h);
    if(pfailed) QGroupBox::resize(w, h);
}

void PGroupBox::setBackgroundColor(const QColor &c) {
    PWidget_setBackgroundColor(c);
    if(pfailed) QGroupBox::setBackgroundColor(c);
}

void PGroupBox::setBackgroundPixmap(const QPixmap &p) {
    PWidget_setBackgroundPixmap(p);
    if(pfailed) QGroupBox::setBackgroundPixmap(p);
}

void PGroupBox::setCursor(const QCursor &c) {
    PWidget_setCursor(c);
    if(pfailed) QGroupBox::setCursor(c);
}

void PGroupBox::setEnabled(bool b) {
    PWidget_setEnabled(b);
    if(pfailed) QGroupBox::setEnabled(b);
}

void PGroupBox::setFont(const QFont &f) {
    PWidget_setFont(f);
    if(pfailed) QGroupBox::setFont(f);
}

void PGroupBox::setGeometry(int x, int y, int w, int h) {
    PWidget_setGeometry(x, y, w, h);
    if(pfailed) QGroupBox::setGeometry(x, y, w, h);
}

void PGroupBox::setPalette(const QPalette &p) {
    PWidget_setPalette(p);
    if(pfailed) QGroupBox::setPalette(p);
}

void PGroupBox::setStyle(GUIStyle s) {
    PWidget_setStyle(s);
    if(pfailed) QGroupBox::setStyle(s);
}

void PGroupBox::show() {
    PWidget_show();
    if(pfailed) QGroupBox::show();
}

QSize PGroupBox::sizeHint() const {
    QSize ret = PWidget_sizeHint();
    if(pfailed) ret = QGroupBox::sizeHint();
    return ret;
}

void PGroupBox::closeEvent(QCloseEvent *event) {
    PWidget_closeEvent(event);
    if(pfailed) QGroupBox::closeEvent(event);
}

void PGroupBox::enterEvent(QEvent *event) {
    PWidget_enterEvent(event);
    if(pfailed) QGroupBox::enterEvent(event);
}

void PGroupBox::focusInEvent(QFocusEvent *event) {
    PWidget_focusInEvent(event);
    if(pfailed) QGroupBox::focusInEvent(event);
}

void PGroupBox::focusOutEvent(QFocusEvent *event) {
    PWidget_focusOutEvent(event);
    if(pfailed) QGroupBox::focusOutEvent(event);
}

void PGroupBox::keyPressEvent(QKeyEvent *event) {
    PWidget_keyPressEvent(event);
    if(pfailed) QGroupBox::keyPressEvent(event);
}

void PGroupBox::keyReleaseEvent(QKeyEvent *event) {
    PWidget_keyReleaseEvent(event);
    if(pfailed) QGroupBox::keyReleaseEvent(event);
}

void PGroupBox::leaveEvent(QEvent *event) {
    PWidget_leaveEvent(event);
    if(pfailed) QGroupBox::leaveEvent(event);
}

void PGroupBox::mouseDoubleClickEvent(QMouseEvent *event) {
    PWidget_mouseDoubleClickEvent(event);
    if(pfailed) QGroupBox::mouseDoubleClickEvent(event);
}

void PGroupBox::mouseMoveEvent(QMouseEvent *event) {
    PWidget_mouseMoveEvent(event);
    if(pfailed) QGroupBox::mouseMoveEvent(event);
}

void PGroupBox::mousePressEvent(QMouseEvent *event) {
    PWidget_mousePressEvent(event);
    if(pfailed) QGroupBox::mousePressEvent(event);
}

void PGroupBox::mouseReleaseEvent(QMouseEvent *event) {
    PWidget_mouseReleaseEvent(event);
    if(pfailed) QGroupBox::mouseReleaseEvent(event);
}

void PGroupBox::moveEvent(QMoveEvent *event) {
    PWidget_moveEvent(event);
    if(pfailed) QGroupBox::moveEvent(event);
}

void PGroupBox::paintEvent(QPaintEvent *event) {
    PWidget_paintEvent(event);
    if(pfailed) QGroupBox::paintEvent(event);
}

void PGroupBox::resizeEvent(QResizeEvent *event) {
    PWidget_resizeEvent(event);
    if(pfailed) QGroupBox::resizeEvent(event);
}


void PGroupBox::drawContents(QPainter *p) {
    PFrame_drawContents(p);
    if(pfailed) QGroupBox::drawContents(p);
}

void PGroupBox::drawFrame(QPainter *p) {
    PFrame_drawFrame(p);
    if(pfailed) QGroupBox::drawFrame(p);
}

void PGroupBox::frameChanged() {
    PFrame_frameChanged();
    if(pfailed) QGroupBox::frameChanged();
}


