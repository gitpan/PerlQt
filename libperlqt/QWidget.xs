/*
 * PWidget definitions.
 *
 * Copyright (C) 1997, Ashley Winters <jql@accessone.com>
 *
 * You may distribute under the terms of the LGPL as specified in the
 * README file
 */

#include "pwidget.h"

const char *PWidget::className() const {
    return PObject_className();
}

bool PWidget::event(QEvent *event) {
    bool ret = PObject_event(event);
    if(pfailed) ret = QWidget::event(event);
    return ret;
}

bool PWidget::eventFilter(QObject *obj, QEvent *event) {
    bool ret = PObject_eventFilter(obj, event);
    if(pfailed) ret = QWidget::eventFilter(obj, event);
    return ret;
}

QMetaObject *PWidget::metaObject() const {
    QMetaObject *ret = PObject_metaObject();
    if(pfailed) ret = QWidget::metaObject();
    return ret;
}

void PWidget::initMetaObject() {
    if(!QWidget::metaObject()) QWidget::initMetaObject();
    PObject_initMetaObject();
}

void PWidget::timerEvent(QTimerEvent *event) {
    PObject_timerEvent(event);
    if(pfailed) QWidget::timerEvent(event);
}


void PWidget::adjustSize() {
    PWidget_adjustSize();
    if(pfailed) QWidget::adjustSize();
}

bool PWidget::close(bool b) {
    bool ret = PWidget_close(b);
    if(pfailed) ret = QWidget::close(b);
    return ret;
}

void PWidget::hide() {
    PWidget_hide();
    if(pfailed) QWidget::hide();
}

void PWidget::move(int x, int y) {
    PWidget_move(x, y);
    if(pfailed) QWidget::move(x, y);
}

void PWidget::resize(int w, int h) {
    PWidget_resize(w, h);
    if(pfailed) QWidget::resize(w, h);
}

void PWidget::setBackgroundColor(const QColor &c) {
    PWidget_setBackgroundColor(c);
    if(pfailed) QWidget::setBackgroundColor(c);
}

void PWidget::setBackgroundPixmap(const QPixmap &p) {
    PWidget_setBackgroundPixmap(p);
    if(pfailed) QWidget::setBackgroundPixmap(p);
}

void PWidget::setCursor(const QCursor &c) {
    PWidget_setCursor(c);
    if(pfailed) QWidget::setCursor(c);
}

void PWidget::setEnabled(bool b) {
    PWidget_setEnabled(b);
    if(pfailed) QWidget::setEnabled(b);
}

void PWidget::setFont(const QFont &f) {
    PWidget_setFont(f);
    if(pfailed) QWidget::setFont(f);
}

void PWidget::setGeometry(int x, int y, int w, int h) {
    PWidget_setGeometry(x, y, w, h);
    if(pfailed) QWidget::setGeometry(x, y, w, h);
}

void PWidget::setPalette(const QPalette &p) {
    PWidget_setPalette(p);
    if(pfailed) QWidget::setPalette(p);
}

void PWidget::setStyle(GUIStyle s) {
    PWidget_setStyle(s);
    if(pfailed) QWidget::setStyle(s);
}

void PWidget::show() {
    PWidget_show();
    if(pfailed) QWidget::show();
}

QSize PWidget::sizeHint() const {
    QSize ret = PWidget_sizeHint();
    if(pfailed) ret = QWidget::sizeHint();
    return ret;
}

void PWidget::closeEvent(QCloseEvent *event) {
    PWidget_closeEvent(event);
    if(pfailed) QWidget::closeEvent(event);
}

void PWidget::enterEvent(QEvent *event) {
    PWidget_enterEvent(event);
    if(pfailed) QWidget::enterEvent(event);
}

void PWidget::focusInEvent(QFocusEvent *event) {
    PWidget_focusInEvent(event);
    if(pfailed) QWidget::focusInEvent(event);
}

void PWidget::focusOutEvent(QFocusEvent *event) {
    PWidget_focusOutEvent(event);
    if(pfailed) QWidget::focusOutEvent(event);
}

void PWidget::keyPressEvent(QKeyEvent *event) {
    PWidget_keyPressEvent(event);
    if(pfailed) QWidget::keyPressEvent(event);
}

void PWidget::keyReleaseEvent(QKeyEvent *event) {
    PWidget_keyReleaseEvent(event);
    if(pfailed) QWidget::keyReleaseEvent(event);
}

void PWidget::leaveEvent(QEvent *event) {
    PWidget_leaveEvent(event);
    if(pfailed) QWidget::leaveEvent(event);
}

void PWidget::mouseDoubleClickEvent(QMouseEvent *event) {
    PWidget_mouseDoubleClickEvent(event);
    if(pfailed) QWidget::mouseDoubleClickEvent(event);
}

void PWidget::mouseMoveEvent(QMouseEvent *event) {
    PWidget_mouseMoveEvent(event);
    if(pfailed) QWidget::mouseMoveEvent(event);
}

void PWidget::mousePressEvent(QMouseEvent *event) {
    PWidget_mousePressEvent(event);
    if(pfailed) QWidget::mousePressEvent(event);
}

void PWidget::mouseReleaseEvent(QMouseEvent *event) {
    PWidget_mouseReleaseEvent(event);
    if(pfailed) QWidget::mouseReleaseEvent(event);
}

void PWidget::moveEvent(QMoveEvent *event) {
    PWidget_moveEvent(event);
    if(pfailed) QWidget::moveEvent(event);
}

void PWidget::paintEvent(QPaintEvent *event) {
    PWidget_paintEvent(event);
    if(pfailed) QWidget::paintEvent(event);
}

void PWidget::resizeEvent(QResizeEvent *event) {
    PWidget_resizeEvent(event);
    if(pfailed) QWidget::resizeEvent(event);
}


void PWidget_virtualize::PWidget_adjustSize() {
    voidCall("adjustSize");
}

bool PWidget_virtualize::PWidget_close(bool b) {
    SV *r = retCall("close", b ? &sv_yes : &sv_no);
    if(pfailed) return FALSE;
    bool ret = SvTRUE(r) ? TRUE : FALSE;
    SvREFCNT_dec(r);
    return ret;
}

void PWidget_virtualize::PWidget_hide() {
    voidCall("hide");
}

void PWidget_virtualize::PWidget_move(int x, int y) {
    SV *arg1 = newSViv(x);
    SV *arg2 = newSViv(y);
    voidCall("move", arg1, arg2);
    SvREFCNT_dec(arg1);
    SvREFCNT_dec(arg2);
}

void PWidget_virtualize::PWidget_resize(int w, int h) {
    SV *arg1 = newSViv(w);
    SV *arg2 = newSViv(h);
    voidCall("resize", arg1, arg2);
    SvREFCNT_dec(arg1);
    SvREFCNT_dec(arg2);
}

void PWidget_virtualize::PWidget_setBackgroundColor(const QColor &color) {
    voidCallObj("setBackgroundColor", &color, "QColor");
}

void PWidget_virtualize::PWidget_setBackgroundPixmap(const QPixmap &pixmap) {
    voidCallObj("setBackgroundColor", &pixmap, "QPixmap");
}

void PWidget_virtualize::PWidget_setCursor(const QCursor &cursor) {
    voidCallObj("setBackgroundColor", &cursor, "QCursor");
}

void PWidget_virtualize::PWidget_setEnabled(bool enable) {
    voidCall("setEnabled", enable ? &sv_yes : &sv_no);
}

void PWidget_virtualize::PWidget_setFont(const QFont &font) {
    voidCallObj("setFont", &font, "QFont");
}

void PWidget_virtualize::PWidget_setGeometry(int x, int y, int w, int h) {
    SV *arg1 = newSViv(x);
    SV *arg2 = newSViv(y);
    SV *arg3 = newSViv(w);
    SV *arg4 = newSViv(h);
    voidCall("setGeometry", arg1, arg2, arg3, arg4);
    SvREFCNT_dec(arg4);
    SvREFCNT_dec(arg3);
    SvREFCNT_dec(arg2);
    SvREFCNT_dec(arg1);
}

void PWidget_virtualize::PWidget_setPalette(const QPalette &palette) {
    voidCallObj("setPalette", &palette, "QPalette");
}

void PWidget_virtualize::PWidget_setStyle(GUIStyle style) {
    SV *arg1 = newSViv(style);
    voidCall("setStyle", arg1);
    SvREFCNT_dec(arg1);
}

void PWidget_virtualize::PWidget_show() {
    voidCall("show");
}

QSize PWidget_virtualize::PWidget_sizeHint() const {
    SV *r = retCall("sizeHint");
    if(pfailed) return QSize();
    QSize *ret = (QSize *)extract_ptr(r, "QSize");
    SvREFCNT_dec(r);
    return *ret;
}

void PWidget_virtualize::PWidget_closeEvent(QCloseEvent *event) {
    voidCallObj("closeEvent", event, "QCloseEvent");
}

void PWidget_virtualize::PWidget_enterEvent(QEvent *event) {
    voidCallObj("enterEvent", event, "QEvent");
}

void PWidget_virtualize::PWidget_focusInEvent(QFocusEvent *event) {
    voidCallObj("focusInEvent", event, "QFocusEvent");
}

void PWidget_virtualize::PWidget_focusOutEvent(QFocusEvent *event) {
    voidCallObj("focusOutEvent", event, "QFocusEvent");
}

void PWidget_virtualize::PWidget_keyPressEvent(QKeyEvent *event) {
    voidCallObj("keyPressEvent", event, "QKeyEvent");
}

void PWidget_virtualize::PWidget_keyReleaseEvent(QKeyEvent *event) {
    voidCallObj("keyReleaseEvent", event, "QKeyEvent");
}

void PWidget_virtualize::PWidget_leaveEvent(QEvent *event) {
    voidCallObj("leaveEvent", event, "QEvent");
}

void PWidget_virtualize::PWidget_mouseDoubleClickEvent(QMouseEvent *event) {
    voidCallObj("mouseDoubleClickEvent", event, "QMouseEvent");
}

void PWidget_virtualize::PWidget_mouseMoveEvent(QMouseEvent *event) {
    voidCallObj("mouseMoveEvent", event, "QMouseEvent");
}

void PWidget_virtualize::PWidget_mousePressEvent(QMouseEvent *event) {
    voidCallObj("mousePressEvent", event, "QMouseEvent");
}

void PWidget_virtualize::PWidget_mouseReleaseEvent(QMouseEvent *event) {
    voidCallObj("mouseReleaseEvent", event, "QMouseEvent");
}

void PWidget_virtualize::PWidget_moveEvent(QMoveEvent *event) {
    voidCallObj("moveEvent", event, "QMoveEvent");
}

void PWidget_virtualize::PWidget_paintEvent(QPaintEvent *event) {
    voidCallObj("paintEvent", event, "QPaintEvent");
}

void PWidget_virtualize::PWidget_resizeEvent(QResizeEvent *event) {
    voidCallObj("resizeEvent", event, "QResizeEvent");
}

