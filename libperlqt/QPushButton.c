/*
 * PPushButton definitions.
 *
 * Copyright (C) 1997, Ashley Winters <jql@accessone.com>
 *
 * You may distribute under the terms of the LGPL as specified in the
 * README file
 */

#include "ppushbt.h"

const char *PPushButton::className() const {
    return PObject_className();
}

bool PPushButton::event(QEvent *event) {
    bool ret = PObject_event(event);
    if(pfailed) ret = QPushButton::event(event);
    return ret;
}

bool PPushButton::eventFilter(QObject *obj, QEvent *event) {
    bool ret = PObject_eventFilter(obj, event);
    if(pfailed) ret = QPushButton::eventFilter(obj, event);
    return ret;
}

QMetaObject *PPushButton::metaObject() const {
    QMetaObject *ret = PObject_metaObject();
    if(pfailed) ret = QPushButton::metaObject();
    return ret;
}

void PPushButton::initMetaObject() {
    if(!QPushButton::metaObject()) QPushButton::initMetaObject();
    PObject_initMetaObject();
}

void PPushButton::timerEvent(QTimerEvent *event) {
    PObject_timerEvent(event);
    if(pfailed) QPushButton::timerEvent(event);
}


void PPushButton::adjustSize() {
    PWidget_adjustSize();
    if(pfailed) QPushButton::adjustSize();
}

bool PPushButton::close(bool b) {
    bool ret = PWidget_close(b);
    if(pfailed) ret = QPushButton::close(b);
    return ret;
}

void PPushButton::hide() {
    PWidget_hide();
    if(pfailed) QPushButton::hide();
}

void PPushButton::move(int x, int y) {
    PWidget_move(x, y);
    if(pfailed) QPushButton::move(x, y);
}

void PPushButton::resize(int w, int h) {
    PWidget_resize(w, h);
    if(pfailed) QPushButton::resize(w, h);
}

void PPushButton::setBackgroundColor(const QColor &c) {
    PWidget_setBackgroundColor(c);
    if(pfailed) QPushButton::setBackgroundColor(c);
}

void PPushButton::setBackgroundPixmap(const QPixmap &p) {
    PWidget_setBackgroundPixmap(p);
    if(pfailed) QPushButton::setBackgroundPixmap(p);
}

void PPushButton::setCursor(const QCursor &c) {
    PWidget_setCursor(c);
    if(pfailed) QPushButton::setCursor(c);
}

void PPushButton::setEnabled(bool b) {
    PWidget_setEnabled(b);
    if(pfailed) QPushButton::setEnabled(b);
}

void PPushButton::setFont(const QFont &f) {
    PWidget_setFont(f);
    if(pfailed) QPushButton::setFont(f);
}

void PPushButton::setGeometry(int x, int y, int w, int h) {
    PWidget_setGeometry(x, y, w, h);
    if(pfailed) QPushButton::setGeometry(x, y, w, h);
}

void PPushButton::setPalette(const QPalette &p) {
    PWidget_setPalette(p);
    if(pfailed) QPushButton::setPalette(p);
}

void PPushButton::setStyle(GUIStyle s) {
    PWidget_setStyle(s);
    if(pfailed) QPushButton::setStyle(s);
}

void PPushButton::show() {
    PWidget_show();
    if(pfailed) QPushButton::show();
}

QSize PPushButton::sizeHint() const {
    QSize ret = PWidget_sizeHint();
    if(pfailed) ret = QPushButton::sizeHint();
    return ret;
}

void PPushButton::closeEvent(QCloseEvent *event) {
    PWidget_closeEvent(event);
    if(pfailed) QPushButton::closeEvent(event);
}

void PPushButton::enterEvent(QEvent *event) {
    PWidget_enterEvent(event);
    if(pfailed) QPushButton::enterEvent(event);
}

void PPushButton::focusInEvent(QFocusEvent *event) {
    PWidget_focusInEvent(event);
    if(pfailed) QPushButton::focusInEvent(event);
}

void PPushButton::focusOutEvent(QFocusEvent *event) {
    PWidget_focusOutEvent(event);
    if(pfailed) QPushButton::focusOutEvent(event);
}

void PPushButton::keyPressEvent(QKeyEvent *event) {
    PWidget_keyPressEvent(event);
    if(pfailed) QPushButton::keyPressEvent(event);
}

void PPushButton::keyReleaseEvent(QKeyEvent *event) {
    PWidget_keyReleaseEvent(event);
    if(pfailed) QPushButton::keyReleaseEvent(event);
}

void PPushButton::leaveEvent(QEvent *event) {
    PWidget_leaveEvent(event);
    if(pfailed) QPushButton::leaveEvent(event);
}

void PPushButton::mouseDoubleClickEvent(QMouseEvent *event) {
    PWidget_mouseDoubleClickEvent(event);
    if(pfailed) QPushButton::mouseDoubleClickEvent(event);
}

void PPushButton::mouseMoveEvent(QMouseEvent *event) {
    PWidget_mouseMoveEvent(event);
    if(pfailed) QPushButton::mouseMoveEvent(event);
}

void PPushButton::mousePressEvent(QMouseEvent *event) {
    PWidget_mousePressEvent(event);
    if(pfailed) QPushButton::mousePressEvent(event);
}

void PPushButton::mouseReleaseEvent(QMouseEvent *event) {
    PWidget_mouseReleaseEvent(event);
    if(pfailed) QPushButton::mouseReleaseEvent(event);
}

void PPushButton::moveEvent(QMoveEvent *event) {
    PWidget_moveEvent(event);
    if(pfailed) QPushButton::moveEvent(event);
}

void PPushButton::paintEvent(QPaintEvent *event) {
    PWidget_paintEvent(event);
    if(pfailed) QPushButton::paintEvent(event);
}

void PPushButton::resizeEvent(QResizeEvent *event) {
    PWidget_resizeEvent(event);
    if(pfailed) QPushButton::resizeEvent(event);
}


void PPushButton::drawButton(QPainter *p) {
    PButton_drawButton(p);
    if(pfailed) QPushButton::drawButton(p);
}

void PPushButton::drawButtonLabel(QPainter *p) {
    PButton_drawButtonLabel(p);
    if(pfailed) QPushButton::drawButtonLabel(p);
}

bool PPushButton::hitButton(const QPoint &p) const {
    bool ret = PButton_hitButton(p);
    if(pfailed) ret = QPushButton::hitButton(p);
    return ret;
}


