/*
 * PButtonGroup definitions.
 *
 * Copyright (C) 1997, Ashley Winters <jql@accessone.com>
 *
 * You may distribute under the terms of the LGPL as specified in the
 * README file
 */

#include "pbttngrp.h"

const char *PButtonGroup::className() const {
    return PObject_className();
}

bool PButtonGroup::event(QEvent *event) {
    bool ret = PObject_event(event);
    if(pfailed) ret = QButtonGroup::event(event);
    return ret;
}

bool PButtonGroup::eventFilter(QObject *obj, QEvent *event) {
    bool ret = PObject_eventFilter(obj, event);
    if(pfailed) ret = QButtonGroup::eventFilter(obj, event);
    return ret;
}

QMetaObject *PButtonGroup::metaObject() const {
    QMetaObject *ret = PObject_metaObject();
    if(pfailed) ret = QButtonGroup::metaObject();
    return ret;
}

void PButtonGroup::initMetaObject() {
    if(!QButtonGroup::metaObject()) QButtonGroup::initMetaObject();
    PObject_initMetaObject();
}

void PButtonGroup::timerEvent(QTimerEvent *event) {
    PObject_timerEvent(event);
    if(pfailed) QButtonGroup::timerEvent(event);
}


void PButtonGroup::adjustSize() {
    PWidget_adjustSize();
    if(pfailed) QButtonGroup::adjustSize();
}

bool PButtonGroup::close(bool b) {
    bool ret = PWidget_close(b);
    if(pfailed) ret = QButtonGroup::close(b);
    return ret;
}

void PButtonGroup::hide() {
    PWidget_hide();
    if(pfailed) QButtonGroup::hide();
}

void PButtonGroup::move(int x, int y) {
    PWidget_move(x, y);
    if(pfailed) QButtonGroup::move(x, y);
}

void PButtonGroup::resize(int w, int h) {
    PWidget_resize(w, h);
    if(pfailed) QButtonGroup::resize(w, h);
}

void PButtonGroup::setBackgroundColor(const QColor &c) {
    PWidget_setBackgroundColor(c);
    if(pfailed) QButtonGroup::setBackgroundColor(c);
}

void PButtonGroup::setBackgroundPixmap(const QPixmap &p) {
    PWidget_setBackgroundPixmap(p);
    if(pfailed) QButtonGroup::setBackgroundPixmap(p);
}

void PButtonGroup::setCursor(const QCursor &c) {
    PWidget_setCursor(c);
    if(pfailed) QButtonGroup::setCursor(c);
}

void PButtonGroup::setEnabled(bool b) {
    PWidget_setEnabled(b);
    if(pfailed) QButtonGroup::setEnabled(b);
}

void PButtonGroup::setFont(const QFont &f) {
    PWidget_setFont(f);
    if(pfailed) QButtonGroup::setFont(f);
}

void PButtonGroup::setGeometry(int x, int y, int w, int h) {
    PWidget_setGeometry(x, y, w, h);
    if(pfailed) QButtonGroup::setGeometry(x, y, w, h);
}

void PButtonGroup::setPalette(const QPalette &p) {
    PWidget_setPalette(p);
    if(pfailed) QButtonGroup::setPalette(p);
}

void PButtonGroup::setStyle(GUIStyle s) {
    PWidget_setStyle(s);
    if(pfailed) QButtonGroup::setStyle(s);
}

void PButtonGroup::show() {
    PWidget_show();
    if(pfailed) QButtonGroup::show();
}

QSize PButtonGroup::sizeHint() const {
    QSize ret = PWidget_sizeHint();
    if(pfailed) ret = QButtonGroup::sizeHint();
    return ret;
}

void PButtonGroup::closeEvent(QCloseEvent *event) {
    PWidget_closeEvent(event);
    if(pfailed) QButtonGroup::closeEvent(event);
}

void PButtonGroup::enterEvent(QEvent *event) {
    PWidget_enterEvent(event);
    if(pfailed) QButtonGroup::enterEvent(event);
}

void PButtonGroup::focusInEvent(QFocusEvent *event) {
    PWidget_focusInEvent(event);
    if(pfailed) QButtonGroup::focusInEvent(event);
}

void PButtonGroup::focusOutEvent(QFocusEvent *event) {
    PWidget_focusOutEvent(event);
    if(pfailed) QButtonGroup::focusOutEvent(event);
}

void PButtonGroup::keyPressEvent(QKeyEvent *event) {
    PWidget_keyPressEvent(event);
    if(pfailed) QButtonGroup::keyPressEvent(event);
}

void PButtonGroup::keyReleaseEvent(QKeyEvent *event) {
    PWidget_keyReleaseEvent(event);
    if(pfailed) QButtonGroup::keyReleaseEvent(event);
}

void PButtonGroup::leaveEvent(QEvent *event) {
    PWidget_leaveEvent(event);
    if(pfailed) QButtonGroup::leaveEvent(event);
}

void PButtonGroup::mouseDoubleClickEvent(QMouseEvent *event) {
    PWidget_mouseDoubleClickEvent(event);
    if(pfailed) QButtonGroup::mouseDoubleClickEvent(event);
}

void PButtonGroup::mouseMoveEvent(QMouseEvent *event) {
    PWidget_mouseMoveEvent(event);
    if(pfailed) QButtonGroup::mouseMoveEvent(event);
}

void PButtonGroup::mousePressEvent(QMouseEvent *event) {
    PWidget_mousePressEvent(event);
    if(pfailed) QButtonGroup::mousePressEvent(event);
}

void PButtonGroup::mouseReleaseEvent(QMouseEvent *event) {
    PWidget_mouseReleaseEvent(event);
    if(pfailed) QButtonGroup::mouseReleaseEvent(event);
}

void PButtonGroup::moveEvent(QMoveEvent *event) {
    PWidget_moveEvent(event);
    if(pfailed) QButtonGroup::moveEvent(event);
}

void PButtonGroup::paintEvent(QPaintEvent *event) {
    PWidget_paintEvent(event);
    if(pfailed) QButtonGroup::paintEvent(event);
}

void PButtonGroup::resizeEvent(QResizeEvent *event) {
    PWidget_resizeEvent(event);
    if(pfailed) QButtonGroup::resizeEvent(event);
}


void PButtonGroup::drawContents(QPainter *p) {
    PFrame_drawContents(p);
    if(pfailed) QButtonGroup::drawContents(p);
}

void PButtonGroup::drawFrame(QPainter *p) {
    PFrame_drawFrame(p);
    if(pfailed) QButtonGroup::drawFrame(p);
}

void PButtonGroup::frameChanged() {
    PFrame_frameChanged();
    if(pfailed) QButtonGroup::frameChanged();
}


