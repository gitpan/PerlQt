/*
 * PScrollBar definitions.
 *
 * Copyright (C) 1997, Ashley Winters <jql@accessone.com>
 *
 * You may distribute under the terms of the LGPL as specified in the
 * README file
 */

#include "pscrbar.h"

const char *PScrollBar::className() const {
    return PObject_className();
}

bool PScrollBar::event(QEvent *event) {
    bool ret = PObject_event(event);
    if(pfailed) ret = QScrollBar::event(event);
    return ret;
}

bool PScrollBar::eventFilter(QObject *obj, QEvent *event) {
    bool ret = PObject_eventFilter(obj, event);
    if(pfailed) ret = QScrollBar::eventFilter(obj, event);
    return ret;
}

QMetaObject *PScrollBar::metaObject() const {
    QMetaObject *ret = PObject_metaObject();
    if(pfailed) ret = QScrollBar::metaObject();
    return ret;
}

void PScrollBar::initMetaObject() {
    if(!QScrollBar::metaObject()) QScrollBar::initMetaObject();
    PObject_initMetaObject();
}

void PScrollBar::timerEvent(QTimerEvent *event) {
    PObject_timerEvent(event);
    if(pfailed) QScrollBar::timerEvent(event);
}


void PScrollBar::adjustSize() {
    PWidget_adjustSize();
    if(pfailed) QScrollBar::adjustSize();
}

bool PScrollBar::close(bool b) {
    bool ret = PWidget_close(b);
    if(pfailed) ret = QScrollBar::close(b);
    return ret;
}

void PScrollBar::hide() {
    PWidget_hide();
    if(pfailed) QScrollBar::hide();
}

void PScrollBar::move(int x, int y) {
    PWidget_move(x, y);
    if(pfailed) QScrollBar::move(x, y);
}

void PScrollBar::resize(int w, int h) {
    PWidget_resize(w, h);
    if(pfailed) QScrollBar::resize(w, h);
}

void PScrollBar::setBackgroundColor(const QColor &c) {
    PWidget_setBackgroundColor(c);
    if(pfailed) QScrollBar::setBackgroundColor(c);
}

void PScrollBar::setBackgroundPixmap(const QPixmap &p) {
    PWidget_setBackgroundPixmap(p);
    if(pfailed) QScrollBar::setBackgroundPixmap(p);
}

void PScrollBar::setCursor(const QCursor &c) {
    PWidget_setCursor(c);
    if(pfailed) QScrollBar::setCursor(c);
}

void PScrollBar::setEnabled(bool b) {
    PWidget_setEnabled(b);
    if(pfailed) QScrollBar::setEnabled(b);
}

void PScrollBar::setFont(const QFont &f) {
    PWidget_setFont(f);
    if(pfailed) QScrollBar::setFont(f);
}

void PScrollBar::setGeometry(int x, int y, int w, int h) {
    PWidget_setGeometry(x, y, w, h);
    if(pfailed) QScrollBar::setGeometry(x, y, w, h);
}

void PScrollBar::setPalette(const QPalette &p) {
    PWidget_setPalette(p);
    if(pfailed) QScrollBar::setPalette(p);
}

void PScrollBar::setStyle(GUIStyle s) {
    PWidget_setStyle(s);
    if(pfailed) QScrollBar::setStyle(s);
}

void PScrollBar::show() {
    PWidget_show();
    if(pfailed) QScrollBar::show();
}

QSize PScrollBar::sizeHint() const {
    QSize ret = PWidget_sizeHint();
    if(pfailed) ret = QScrollBar::sizeHint();
    return ret;
}

void PScrollBar::closeEvent(QCloseEvent *event) {
    PWidget_closeEvent(event);
    if(pfailed) QScrollBar::closeEvent(event);
}

void PScrollBar::enterEvent(QEvent *event) {
    PWidget_enterEvent(event);
    if(pfailed) QScrollBar::enterEvent(event);
}

void PScrollBar::focusInEvent(QFocusEvent *event) {
    PWidget_focusInEvent(event);
    if(pfailed) QScrollBar::focusInEvent(event);
}

void PScrollBar::focusOutEvent(QFocusEvent *event) {
    PWidget_focusOutEvent(event);
    if(pfailed) QScrollBar::focusOutEvent(event);
}

void PScrollBar::keyPressEvent(QKeyEvent *event) {
    PWidget_keyPressEvent(event);
    if(pfailed) QScrollBar::keyPressEvent(event);
}

void PScrollBar::keyReleaseEvent(QKeyEvent *event) {
    PWidget_keyReleaseEvent(event);
    if(pfailed) QScrollBar::keyReleaseEvent(event);
}

void PScrollBar::leaveEvent(QEvent *event) {
    PWidget_leaveEvent(event);
    if(pfailed) QScrollBar::leaveEvent(event);
}

void PScrollBar::mouseDoubleClickEvent(QMouseEvent *event) {
    PWidget_mouseDoubleClickEvent(event);
    if(pfailed) QScrollBar::mouseDoubleClickEvent(event);
}

void PScrollBar::mouseMoveEvent(QMouseEvent *event) {
    PWidget_mouseMoveEvent(event);
    if(pfailed) QScrollBar::mouseMoveEvent(event);
}

void PScrollBar::mousePressEvent(QMouseEvent *event) {
    PWidget_mousePressEvent(event);
    if(pfailed) QScrollBar::mousePressEvent(event);
}

void PScrollBar::mouseReleaseEvent(QMouseEvent *event) {
    PWidget_mouseReleaseEvent(event);
    if(pfailed) QScrollBar::mouseReleaseEvent(event);
}

void PScrollBar::moveEvent(QMoveEvent *event) {
    PWidget_moveEvent(event);
    if(pfailed) QScrollBar::moveEvent(event);
}

void PScrollBar::paintEvent(QPaintEvent *event) {
    PWidget_paintEvent(event);
    if(pfailed) QScrollBar::paintEvent(event);
}

void PScrollBar::resizeEvent(QResizeEvent *event) {
    PWidget_resizeEvent(event);
    if(pfailed) QScrollBar::resizeEvent(event);
}


void PScrollBar::rangeChange() {
    PRangeControl_rangeChange();
    if(pfailed) QScrollBar::rangeChange();
}

void PScrollBar::stepChange() {
    PRangeControl_stepChange();
    if(pfailed) QScrollBar::stepChange();
}

void PScrollBar::valueChange() {
    PRangeControl_valueChange();
    if(pfailed) QScrollBar::valueChange();
}


