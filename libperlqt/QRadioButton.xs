/*
 * PRadioButton definitions.
 *
 * Copyright (C) 1997, Ashley Winters <jql@accessone.com>
 *
 * You may distribute under the terms of the LGPL as specified in the
 * README file
 */

#include "pradiobt.h"

const char *PRadioButton::className() const {
    return PObject_className();
}

bool PRadioButton::event(QEvent *event) {
    bool ret = PObject_event(event);
    if(pfailed) ret = QRadioButton::event(event);
    return ret;
}

bool PRadioButton::eventFilter(QObject *obj, QEvent *event) {
    bool ret = PObject_eventFilter(obj, event);
    if(pfailed) ret = QRadioButton::eventFilter(obj, event);
    return ret;
}

QMetaObject *PRadioButton::metaObject() const {
    QMetaObject *ret = PObject_metaObject();
    if(pfailed) ret = QRadioButton::metaObject();
    return ret;
}

void PRadioButton::initMetaObject() {
    if(!QRadioButton::metaObject()) QRadioButton::initMetaObject();
    PObject_initMetaObject();
}

void PRadioButton::timerEvent(QTimerEvent *event) {
    PObject_timerEvent(event);
    if(pfailed) QRadioButton::timerEvent(event);
}


void PRadioButton::adjustSize() {
    PWidget_adjustSize();
    if(pfailed) QRadioButton::adjustSize();
}

bool PRadioButton::close(bool b) {
    bool ret = PWidget_close(b);
    if(pfailed) ret = QRadioButton::close(b);
    return ret;
}

void PRadioButton::hide() {
    PWidget_hide();
    if(pfailed) QRadioButton::hide();
}

void PRadioButton::move(int x, int y) {
    PWidget_move(x, y);
    if(pfailed) QRadioButton::move(x, y);
}

void PRadioButton::resize(int w, int h) {
    PWidget_resize(w, h);
    if(pfailed) QRadioButton::resize(w, h);
}

void PRadioButton::setBackgroundColor(const QColor &c) {
    PWidget_setBackgroundColor(c);
    if(pfailed) QRadioButton::setBackgroundColor(c);
}

void PRadioButton::setBackgroundPixmap(const QPixmap &p) {
    PWidget_setBackgroundPixmap(p);
    if(pfailed) QRadioButton::setBackgroundPixmap(p);
}

void PRadioButton::setCursor(const QCursor &c) {
    PWidget_setCursor(c);
    if(pfailed) QRadioButton::setCursor(c);
}

void PRadioButton::setEnabled(bool b) {
    PWidget_setEnabled(b);
    if(pfailed) QRadioButton::setEnabled(b);
}

void PRadioButton::setFont(const QFont &f) {
    PWidget_setFont(f);
    if(pfailed) QRadioButton::setFont(f);
}

void PRadioButton::setGeometry(int x, int y, int w, int h) {
    PWidget_setGeometry(x, y, w, h);
    if(pfailed) QRadioButton::setGeometry(x, y, w, h);
}

void PRadioButton::setPalette(const QPalette &p) {
    PWidget_setPalette(p);
    if(pfailed) QRadioButton::setPalette(p);
}

void PRadioButton::setStyle(GUIStyle s) {
    PWidget_setStyle(s);
    if(pfailed) QRadioButton::setStyle(s);
}

void PRadioButton::show() {
    PWidget_show();
    if(pfailed) QRadioButton::show();
}

QSize PRadioButton::sizeHint() const {
    QSize ret = PWidget_sizeHint();
    if(pfailed) ret = QRadioButton::sizeHint();
    return ret;
}

void PRadioButton::closeEvent(QCloseEvent *event) {
    PWidget_closeEvent(event);
    if(pfailed) QRadioButton::closeEvent(event);
}

void PRadioButton::enterEvent(QEvent *event) {
    PWidget_enterEvent(event);
    if(pfailed) QRadioButton::enterEvent(event);
}

void PRadioButton::focusInEvent(QFocusEvent *event) {
    PWidget_focusInEvent(event);
    if(pfailed) QRadioButton::focusInEvent(event);
}

void PRadioButton::focusOutEvent(QFocusEvent *event) {
    PWidget_focusOutEvent(event);
    if(pfailed) QRadioButton::focusOutEvent(event);
}

void PRadioButton::keyPressEvent(QKeyEvent *event) {
    PWidget_keyPressEvent(event);
    if(pfailed) QRadioButton::keyPressEvent(event);
}

void PRadioButton::keyReleaseEvent(QKeyEvent *event) {
    PWidget_keyReleaseEvent(event);
    if(pfailed) QRadioButton::keyReleaseEvent(event);
}

void PRadioButton::leaveEvent(QEvent *event) {
    PWidget_leaveEvent(event);
    if(pfailed) QRadioButton::leaveEvent(event);
}

void PRadioButton::mouseDoubleClickEvent(QMouseEvent *event) {
    PWidget_mouseDoubleClickEvent(event);
    if(pfailed) QRadioButton::mouseDoubleClickEvent(event);
}

void PRadioButton::mouseMoveEvent(QMouseEvent *event) {
    PWidget_mouseMoveEvent(event);
    if(pfailed) QRadioButton::mouseMoveEvent(event);
}

void PRadioButton::mousePressEvent(QMouseEvent *event) {
    PWidget_mousePressEvent(event);
    if(pfailed) QRadioButton::mousePressEvent(event);
}

void PRadioButton::mouseReleaseEvent(QMouseEvent *event) {
    PWidget_mouseReleaseEvent(event);
    if(pfailed) QRadioButton::mouseReleaseEvent(event);
}

void PRadioButton::moveEvent(QMoveEvent *event) {
    PWidget_moveEvent(event);
    if(pfailed) QRadioButton::moveEvent(event);
}

void PRadioButton::paintEvent(QPaintEvent *event) {
    PWidget_paintEvent(event);
    if(pfailed) QRadioButton::paintEvent(event);
}

void PRadioButton::resizeEvent(QResizeEvent *event) {
    PWidget_resizeEvent(event);
    if(pfailed) QRadioButton::resizeEvent(event);
}


void PRadioButton::drawButton(QPainter *p) {
    PButton_drawButton(p);
    if(pfailed) QRadioButton::drawButton(p);
}

void PRadioButton::drawButtonLabel(QPainter *p) {
    PButton_drawButtonLabel(p);
    if(pfailed) QRadioButton::drawButtonLabel(p);
}

bool PRadioButton::hitButton(const QPoint &p) const {
    bool ret = PButton_hitButton(p);
    if(pfailed) ret = QRadioButton::hitButton(p);
    return ret;
}


