/*
 * PButton definitions.
 *
 * Copyright (C) 1997, Ashley Winters <jql@accessone.com>
 *
 * You may distribute under the terms of the LGPL as specified in the
 * README file
 */

#include "pbutton.h"

const char *PButton::className() const {
    return PObject_className();
}

bool PButton::event(QEvent *event) {
    bool ret = PObject_event(event);
    if(pfailed) ret = QButton::event(event);
    return ret;
}

bool PButton::eventFilter(QObject *obj, QEvent *event) {
    bool ret = PObject_eventFilter(obj, event);
    if(pfailed) ret = QButton::eventFilter(obj, event);
    return ret;
}

QMetaObject *PButton::metaObject() const {
    QMetaObject *ret = PObject_metaObject();
    if(pfailed) ret = QButton::metaObject();
    return ret;
}

void PButton::initMetaObject() {
    if(!QButton::metaObject()) QButton::initMetaObject();
    PObject_initMetaObject();
}

void PButton::timerEvent(QTimerEvent *event) {
    PObject_timerEvent(event);
    if(pfailed) QButton::timerEvent(event);
}


void PButton::adjustSize() {
    PWidget_adjustSize();
    if(pfailed) QButton::adjustSize();
}

bool PButton::close(bool b) {
    bool ret = PWidget_close(b);
    if(pfailed) ret = QButton::close(b);
    return ret;
}

void PButton::hide() {
    PWidget_hide();
    if(pfailed) QButton::hide();
}

void PButton::move(int x, int y) {
    PWidget_move(x, y);
    if(pfailed) QButton::move(x, y);
}

void PButton::resize(int w, int h) {
    PWidget_resize(w, h);
    if(pfailed) QButton::resize(w, h);
}

void PButton::setBackgroundColor(const QColor &c) {
    PWidget_setBackgroundColor(c);
    if(pfailed) QButton::setBackgroundColor(c);
}

void PButton::setBackgroundPixmap(const QPixmap &p) {
    PWidget_setBackgroundPixmap(p);
    if(pfailed) QButton::setBackgroundPixmap(p);
}

void PButton::setCursor(const QCursor &c) {
    PWidget_setCursor(c);
    if(pfailed) QButton::setCursor(c);
}

void PButton::setEnabled(bool b) {
    PWidget_setEnabled(b);
    if(pfailed) QButton::setEnabled(b);
}

void PButton::setFont(const QFont &f) {
    PWidget_setFont(f);
    if(pfailed) QButton::setFont(f);
}

void PButton::setGeometry(int x, int y, int w, int h) {
    PWidget_setGeometry(x, y, w, h);
    if(pfailed) QButton::setGeometry(x, y, w, h);
}

void PButton::setPalette(const QPalette &p) {
    PWidget_setPalette(p);
    if(pfailed) QButton::setPalette(p);
}

void PButton::setStyle(GUIStyle s) {
    PWidget_setStyle(s);
    if(pfailed) QButton::setStyle(s);
}

void PButton::show() {
    PWidget_show();
    if(pfailed) QButton::show();
}

QSize PButton::sizeHint() const {
    QSize ret = PWidget_sizeHint();
    if(pfailed) ret = QButton::sizeHint();
    return ret;
}

void PButton::closeEvent(QCloseEvent *event) {
    PWidget_closeEvent(event);
    if(pfailed) QButton::closeEvent(event);
}

void PButton::enterEvent(QEvent *event) {
    PWidget_enterEvent(event);
    if(pfailed) QButton::enterEvent(event);
}

void PButton::focusInEvent(QFocusEvent *event) {
    PWidget_focusInEvent(event);
    if(pfailed) QButton::focusInEvent(event);
}

void PButton::focusOutEvent(QFocusEvent *event) {
    PWidget_focusOutEvent(event);
    if(pfailed) QButton::focusOutEvent(event);
}

void PButton::keyPressEvent(QKeyEvent *event) {
    PWidget_keyPressEvent(event);
    if(pfailed) QButton::keyPressEvent(event);
}

void PButton::keyReleaseEvent(QKeyEvent *event) {
    PWidget_keyReleaseEvent(event);
    if(pfailed) QButton::keyReleaseEvent(event);
}

void PButton::leaveEvent(QEvent *event) {
    PWidget_leaveEvent(event);
    if(pfailed) QButton::leaveEvent(event);
}

void PButton::mouseDoubleClickEvent(QMouseEvent *event) {
    PWidget_mouseDoubleClickEvent(event);
    if(pfailed) QButton::mouseDoubleClickEvent(event);
}

void PButton::mouseMoveEvent(QMouseEvent *event) {
    PWidget_mouseMoveEvent(event);
    if(pfailed) QButton::mouseMoveEvent(event);
}

void PButton::mousePressEvent(QMouseEvent *event) {
    PWidget_mousePressEvent(event);
    if(pfailed) QButton::mousePressEvent(event);
}

void PButton::mouseReleaseEvent(QMouseEvent *event) {
    PWidget_mouseReleaseEvent(event);
    if(pfailed) QButton::mouseReleaseEvent(event);
}

void PButton::moveEvent(QMoveEvent *event) {
    PWidget_moveEvent(event);
    if(pfailed) QButton::moveEvent(event);
}

void PButton::paintEvent(QPaintEvent *event) {
    PWidget_paintEvent(event);
    if(pfailed) QButton::paintEvent(event);
}

void PButton::resizeEvent(QResizeEvent *event) {
    PWidget_resizeEvent(event);
    if(pfailed) QButton::resizeEvent(event);
}


void PButton::drawButton(QPainter *p) {
    PButton_drawButton(p);
    if(pfailed) QButton::drawButton(p);
}

void PButton::drawButtonLabel(QPainter *p) {
    PButton_drawButtonLabel(p);
    if(pfailed) QButton::drawButtonLabel(p);
}

bool PButton::hitButton(const QPoint &p) const {
    bool ret = PButton_hitButton(p);
    if(pfailed) ret = QButton::hitButton(p);
    return ret;
}


void PButton_virtualize::PButton_drawButton(QPainter *p) {
    voidCallObj("drawButton", p, "QPainter");
}

void PButton_virtualize::PButton_drawButtonLabel(QPainter *p) {
    voidCallObj("drawButtonLabel", p, "QPainter");
}

bool PButton_virtualize::PButton_hitButton(const QPoint &p) const {
    SV *r = retCallObj("hitButton", &p, "QPoint");
    if(pfailed) return FALSE;
    bool ret = SvTRUE(r) ? TRUE : FALSE;
    SvREFCNT_dec(r);
    return ret;
}
