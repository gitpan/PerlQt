/*
 * VQSlider definitions.
 *
 * Copyright (C) 1997, Ashley Winters <jql@accessone.com>
 *
 * You may distribute under the terms of the LGPL as specified in the
 * README file
 */

#include <pqslider.h>

const char *VQSlider::className() const {
    return QObject_className();
}

void VQSlider::connectNotify(const char *signal) {
    QObject_connectNotify(signal);
}

void VQSlider::disconnectNotify(const char *signal) {
    QObject_disconnectNotify(signal);
}

bool VQSlider::event(QEvent *event) {
    return QObject_event(event);
}

bool VQSlider::eventFilter(QObject *obj, QEvent *event) {
    return QObject_eventFilter(obj, event);
}

void VQSlider::initMetaObject() {
    if(!QSlider::metaObject()) QSlider::initMetaObject();
    QObject_initMetaObject();
}

QMetaObject *VQSlider::metaObject() const {
    return QObject_metaObject();
}

void VQSlider::timerEvent(QTimerEvent *event) {
    QObject_timerEvent(event);
}


void VQSlider::adjustSize() {
    QWidget_adjustSize();
}

void VQSlider::backgroundColorChange(const QColor &color) {
    QWidget_backgroundColorChange(color);
}

void VQSlider::backgroundPixmapChange(const QPixmap &pixmap) {
    QWidget_backgroundPixmapChange(pixmap);
}

bool VQSlider::close(bool forceKill) {
    return QWidget_close(forceKill);
}

void VQSlider::closeEvent(QCloseEvent *event) {
    QWidget_closeEvent(event);
}

void VQSlider::enabledChange(bool enable) {
    QWidget_enabledChange(enable);
}

void VQSlider::enterEvent(QEvent *event) {
    QWidget_enterEvent(event);
}

void VQSlider::focusInEvent(QFocusEvent *event) {
    QWidget_focusInEvent(event);
}

bool VQSlider::focusNextPrevChild(bool next) {
    return QWidget_focusNextPrevChild(next);
}

void VQSlider::focusOutEvent(QFocusEvent *event) {
    QWidget_focusOutEvent(event);
}

void VQSlider::fontChange(const QFont &font) {
    QWidget_fontChange(font);
}

void VQSlider::hide() {
    QWidget_hide();
}

void VQSlider::keyPressEvent(QKeyEvent *event) {
    QWidget_keyPressEvent(event);
}

void VQSlider::keyReleaseEvent(QKeyEvent *event) {
    QWidget_keyReleaseEvent(event);
}

void VQSlider::leaveEvent(QEvent *event) {
    QWidget_leaveEvent(event);
}

void VQSlider::mouseDoubleClickEvent(QMouseEvent *event) {
    QWidget_mouseDoubleClickEvent(event);
}

void VQSlider::mouseMoveEvent(QMouseEvent *event) {
    QWidget_mouseMoveEvent(event);
}

void VQSlider::mousePressEvent(QMouseEvent *event) {
    QWidget_mousePressEvent(event);
}

void VQSlider::mouseReleaseEvent(QMouseEvent *event) {
    QWidget_mouseReleaseEvent(event);
}

void VQSlider::move(int x, int y) {
    QWidget_move(x, y);
}

void VQSlider::moveEvent(QMoveEvent *event) {
    QWidget_moveEvent(event);
}

void VQSlider::paintEvent(QPaintEvent *event) {
    QWidget_paintEvent(event);
}

void VQSlider::paletteChange(const QPalette &palette) {
    QWidget_paletteChange(palette);
}

void VQSlider::resize(int w, int h) {
    QWidget_resize(w, h);
}

void VQSlider::resizeEvent(QResizeEvent *event) {
    QWidget_resizeEvent(event);
}

void VQSlider::setBackgroundColor(const QColor &color) {
    QWidget_setBackgroundColor(color);
}

void VQSlider::setBackgroundPixmap(const QPixmap &pixmap) {
    QWidget_setBackgroundPixmap(pixmap);
}

void VQSlider::setCursor(const QCursor &cursor) {
    QWidget_setCursor(cursor);
}

void VQSlider::setEnabled(bool enable) {
    QWidget_setEnabled(enable);
}

void VQSlider::setFont(const QFont &font) {
    QWidget_setFont(font);
}

void VQSlider::setGeometry(int x, int y, int w, int h) {
    QWidget_setGeometry(x, y, w, h);
}

void VQSlider::setPalette(const QPalette &palette) {
    QWidget_setPalette(palette);
}

void VQSlider::setStyle(GUIStyle style) {
    QWidget_setStyle(style);
}

void VQSlider::show() {
    QWidget_show();
}

QSize VQSlider::sizeHint() const {
    return QWidget_sizeHint();
}

void VQSlider::styleChange(GUIStyle style) {
    QWidget_styleChange(style);
}


void VQSlider::rangeChange() {
    QRangeControl_rangeChange();
}

void VQSlider::stepChange() {
    QRangeControl_stepChange();
}

void VQSlider::valueChange() {
    QRangeControl_valueChange();
}


