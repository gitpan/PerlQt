/*
 * PSlider definitions.
 *
 * Copyright (C) 1997, Ashley Winters <jql@accessone.com>
 *
 * You may distribute under the terms of the LGPL as specified in the
 * README file
 */

#include "pslider.h"

const char *PSlider::className() const {
    return PObject_className();
}

bool PSlider::event(QEvent *event) {
    bool ret = PObject_event(event);
    if(pfailed) ret = QSlider::event(event);
    return ret;
}

bool PSlider::eventFilter(QObject *obj, QEvent *event) {
    bool ret = PObject_eventFilter(obj, event);
    if(pfailed) ret = QSlider::eventFilter(obj, event);
    return ret;
}

QMetaObject *PSlider::metaObject() const {
    QMetaObject *ret = PObject_metaObject();
    if(pfailed) ret = QSlider::metaObject();
    return ret;
}

void PSlider::initMetaObject() {
    if(!QSlider::metaObject()) QSlider::initMetaObject();
    PObject_initMetaObject();
}

void PSlider::timerEvent(QTimerEvent *event) {
    PObject_timerEvent(event);
    if(pfailed) QSlider::timerEvent(event);
}


void PSlider::adjustSize() {
    PWidget_adjustSize();
    if(pfailed) QSlider::adjustSize();
}

bool PSlider::close(bool b) {
    bool ret = PWidget_close(b);
    if(pfailed) ret = QSlider::close(b);
    return ret;
}

void PSlider::hide() {
    PWidget_hide();
    if(pfailed) QSlider::hide();
}

void PSlider::move(int x, int y) {
    PWidget_move(x, y);
    if(pfailed) QSlider::move(x, y);
}

void PSlider::resize(int w, int h) {
    PWidget_resize(w, h);
    if(pfailed) QSlider::resize(w, h);
}

void PSlider::setBackgroundColor(const QColor &c) {
    PWidget_setBackgroundColor(c);
    if(pfailed) QSlider::setBackgroundColor(c);
}

void PSlider::setBackgroundPixmap(const QPixmap &p) {
    PWidget_setBackgroundPixmap(p);
    if(pfailed) QSlider::setBackgroundPixmap(p);
}

void PSlider::setCursor(const QCursor &c) {
    PWidget_setCursor(c);
    if(pfailed) QSlider::setCursor(c);
}

void PSlider::setEnabled(bool b) {
    PWidget_setEnabled(b);
    if(pfailed) QSlider::setEnabled(b);
}

void PSlider::setFont(const QFont &f) {
    PWidget_setFont(f);
    if(pfailed) QSlider::setFont(f);
}

void PSlider::setGeometry(int x, int y, int w, int h) {
    PWidget_setGeometry(x, y, w, h);
    if(pfailed) QSlider::setGeometry(x, y, w, h);
}

void PSlider::setPalette(const QPalette &p) {
    PWidget_setPalette(p);
    if(pfailed) QSlider::setPalette(p);
}

void PSlider::setStyle(GUIStyle s) {
    PWidget_setStyle(s);
    if(pfailed) QSlider::setStyle(s);
}

void PSlider::show() {
    PWidget_show();
    if(pfailed) QSlider::show();
}

QSize PSlider::sizeHint() const {
    QSize ret = PWidget_sizeHint();
    if(pfailed) ret = QSlider::sizeHint();
    return ret;
}

void PSlider::closeEvent(QCloseEvent *event) {
    PWidget_closeEvent(event);
    if(pfailed) QSlider::closeEvent(event);
}

void PSlider::enterEvent(QEvent *event) {
    PWidget_enterEvent(event);
    if(pfailed) QSlider::enterEvent(event);
}

void PSlider::focusInEvent(QFocusEvent *event) {
    PWidget_focusInEvent(event);
    if(pfailed) QSlider::focusInEvent(event);
}

void PSlider::focusOutEvent(QFocusEvent *event) {
    PWidget_focusOutEvent(event);
    if(pfailed) QSlider::focusOutEvent(event);
}

void PSlider::keyPressEvent(QKeyEvent *event) {
    PWidget_keyPressEvent(event);
    if(pfailed) QSlider::keyPressEvent(event);
}

void PSlider::keyReleaseEvent(QKeyEvent *event) {
    PWidget_keyReleaseEvent(event);
    if(pfailed) QSlider::keyReleaseEvent(event);
}

void PSlider::leaveEvent(QEvent *event) {
    PWidget_leaveEvent(event);
    if(pfailed) QSlider::leaveEvent(event);
}

void PSlider::mouseDoubleClickEvent(QMouseEvent *event) {
    PWidget_mouseDoubleClickEvent(event);
    if(pfailed) QSlider::mouseDoubleClickEvent(event);
}

void PSlider::mouseMoveEvent(QMouseEvent *event) {
    PWidget_mouseMoveEvent(event);
    if(pfailed) QSlider::mouseMoveEvent(event);
}

void PSlider::mousePressEvent(QMouseEvent *event) {
    PWidget_mousePressEvent(event);
    if(pfailed) QSlider::mousePressEvent(event);
}

void PSlider::mouseReleaseEvent(QMouseEvent *event) {
    PWidget_mouseReleaseEvent(event);
    if(pfailed) QSlider::mouseReleaseEvent(event);
}

void PSlider::moveEvent(QMoveEvent *event) {
    PWidget_moveEvent(event);
    if(pfailed) QSlider::moveEvent(event);
}

void PSlider::paintEvent(QPaintEvent *event) {
    PWidget_paintEvent(event);
    if(pfailed) QSlider::paintEvent(event);
}

void PSlider::resizeEvent(QResizeEvent *event) {
    PWidget_resizeEvent(event);
    if(pfailed) QSlider::resizeEvent(event);
}


void PSlider::rangeChange() {
    PRangeControl_rangeChange();
    if(pfailed) QSlider::rangeChange();
}

void PSlider::stepChange() {
    PRangeControl_stepChange();
    if(pfailed) QSlider::stepChange();
}

void PSlider::valueChange() {
    PRangeControl_valueChange();
    if(pfailed) QSlider::valueChange();
}


void PSlider::setTickInterval(int interval) {
    PSlider_setTickInterval(interval);
    if(pfailed) QSlider::setTickInterval(interval);
}

void PSlider::setTickmarks(QSlider::TickSetting setting) {
    PSlider_setTickmarks(setting);
    if(pfailed) QSlider::setTickmarks(setting);
}

void PSlider::paintSlider(QPainter *p, const QRect &rect) {
    PSlider_paintSlider(p, rect);
    if(pfailed) QSlider::paintSlider(p, rect);
}

int PSlider::thickness() const {
    int ret = PSlider_thickness();
    if(pfailed) ret = QSlider::thickness();
    return ret;
}


void PSlider_virtualize::PSlider_setTickInterval(int interval) {
    SV *arg1 = newSViv(interval);
    voidCall("setTickInterval", arg1);
    SvREFCNT_dec(arg1);
}

void PSlider_virtualize::PSlider_setTickmarks(QSlider::TickSetting setting) {
    SV *arg1 = newSViv((IV)setting);
    voidCall("setTickmarks", arg1);
    SvREFCNT_dec(arg1);
}

void PSlider_virtualize::PSlider_paintSlider(QPainter *p, const QRect &rect) {
    voidCallObj("paintSlider", p, "QPainter", &rect, "QRect");
}

int PSlider_virtualize::PSlider_thickness() const {
    SV *r = retCall("thickness");
    if(pfailed) return -1;
    int ret = SvIV(r);
    SvREFCNT_dec(r);
    return ret;
}
