/*
 * PCheckBox definitions.
 *
 * Copyright (C) 1997, Ashley Winters <jql@accessone.com>
 *
 * You may distribute under the terms of the LGPL as specified in the
 * README file
 */

#include "pchkbox.h"

const char *PCheckBox::className() const {
    return PObject_className();
}

bool PCheckBox::event(QEvent *event) {
    bool ret = PObject_event(event);
    if(pfailed) ret = QCheckBox::event(event);
    return ret;
}

bool PCheckBox::eventFilter(QObject *obj, QEvent *event) {
    bool ret = PObject_eventFilter(obj, event);
    if(pfailed) ret = QCheckBox::eventFilter(obj, event);
    return ret;
}

QMetaObject *PCheckBox::metaObject() const {
    QMetaObject *ret = PObject_metaObject();
    if(pfailed) ret = QCheckBox::metaObject();
    return ret;
}

void PCheckBox::initMetaObject() {
    if(!QCheckBox::metaObject()) QCheckBox::initMetaObject();
    PObject_initMetaObject();
}

void PCheckBox::timerEvent(QTimerEvent *event) {
    PObject_timerEvent(event);
    if(pfailed) QCheckBox::timerEvent(event);
}


void PCheckBox::adjustSize() {
    PWidget_adjustSize();
    if(pfailed) QCheckBox::adjustSize();
}

bool PCheckBox::close(bool b) {
    bool ret = PWidget_close(b);
    if(pfailed) ret = QCheckBox::close(b);
    return ret;
}

void PCheckBox::hide() {
    PWidget_hide();
    if(pfailed) QCheckBox::hide();
}

void PCheckBox::move(int x, int y) {
    PWidget_move(x, y);
    if(pfailed) QCheckBox::move(x, y);
}

void PCheckBox::resize(int w, int h) {
    PWidget_resize(w, h);
    if(pfailed) QCheckBox::resize(w, h);
}

void PCheckBox::setBackgroundColor(const QColor &c) {
    PWidget_setBackgroundColor(c);
    if(pfailed) QCheckBox::setBackgroundColor(c);
}

void PCheckBox::setBackgroundPixmap(const QPixmap &p) {
    PWidget_setBackgroundPixmap(p);
    if(pfailed) QCheckBox::setBackgroundPixmap(p);
}

void PCheckBox::setCursor(const QCursor &c) {
    PWidget_setCursor(c);
    if(pfailed) QCheckBox::setCursor(c);
}

void PCheckBox::setEnabled(bool b) {
    PWidget_setEnabled(b);
    if(pfailed) QCheckBox::setEnabled(b);
}

void PCheckBox::setFont(const QFont &f) {
    PWidget_setFont(f);
    if(pfailed) QCheckBox::setFont(f);
}

void PCheckBox::setGeometry(int x, int y, int w, int h) {
    PWidget_setGeometry(x, y, w, h);
    if(pfailed) QCheckBox::setGeometry(x, y, w, h);
}

void PCheckBox::setPalette(const QPalette &p) {
    PWidget_setPalette(p);
    if(pfailed) QCheckBox::setPalette(p);
}

void PCheckBox::setStyle(GUIStyle s) {
    PWidget_setStyle(s);
    if(pfailed) QCheckBox::setStyle(s);
}

void PCheckBox::show() {
    PWidget_show();
    if(pfailed) QCheckBox::show();
}

QSize PCheckBox::sizeHint() const {
    QSize ret = PWidget_sizeHint();
    if(pfailed) ret = QCheckBox::sizeHint();
    return ret;
}

void PCheckBox::closeEvent(QCloseEvent *event) {
    PWidget_closeEvent(event);
    if(pfailed) QCheckBox::closeEvent(event);
}

void PCheckBox::enterEvent(QEvent *event) {
    PWidget_enterEvent(event);
    if(pfailed) QCheckBox::enterEvent(event);
}

void PCheckBox::focusInEvent(QFocusEvent *event) {
    PWidget_focusInEvent(event);
    if(pfailed) QCheckBox::focusInEvent(event);
}

void PCheckBox::focusOutEvent(QFocusEvent *event) {
    PWidget_focusOutEvent(event);
    if(pfailed) QCheckBox::focusOutEvent(event);
}

void PCheckBox::keyPressEvent(QKeyEvent *event) {
    PWidget_keyPressEvent(event);
    if(pfailed) QCheckBox::keyPressEvent(event);
}

void PCheckBox::keyReleaseEvent(QKeyEvent *event) {
    PWidget_keyReleaseEvent(event);
    if(pfailed) QCheckBox::keyReleaseEvent(event);
}

void PCheckBox::leaveEvent(QEvent *event) {
    PWidget_leaveEvent(event);
    if(pfailed) QCheckBox::leaveEvent(event);
}

void PCheckBox::mouseDoubleClickEvent(QMouseEvent *event) {
    PWidget_mouseDoubleClickEvent(event);
    if(pfailed) QCheckBox::mouseDoubleClickEvent(event);
}

void PCheckBox::mouseMoveEvent(QMouseEvent *event) {
    PWidget_mouseMoveEvent(event);
    if(pfailed) QCheckBox::mouseMoveEvent(event);
}

void PCheckBox::mousePressEvent(QMouseEvent *event) {
    PWidget_mousePressEvent(event);
    if(pfailed) QCheckBox::mousePressEvent(event);
}

void PCheckBox::mouseReleaseEvent(QMouseEvent *event) {
    PWidget_mouseReleaseEvent(event);
    if(pfailed) QCheckBox::mouseReleaseEvent(event);
}

void PCheckBox::moveEvent(QMoveEvent *event) {
    PWidget_moveEvent(event);
    if(pfailed) QCheckBox::moveEvent(event);
}

void PCheckBox::paintEvent(QPaintEvent *event) {
    PWidget_paintEvent(event);
    if(pfailed) QCheckBox::paintEvent(event);
}

void PCheckBox::resizeEvent(QResizeEvent *event) {
    PWidget_resizeEvent(event);
    if(pfailed) QCheckBox::resizeEvent(event);
}


void PCheckBox::drawButton(QPainter *p) {
    PButton_drawButton(p);
    if(pfailed) QCheckBox::drawButton(p);
}

void PCheckBox::drawButtonLabel(QPainter *p) {
    PButton_drawButtonLabel(p);
    if(pfailed) QCheckBox::drawButtonLabel(p);
}

bool PCheckBox::hitButton(const QPoint &p) const {
    bool ret = PButton_hitButton(p);
    if(pfailed) ret = QCheckBox::hitButton(p);
    return ret;
}


