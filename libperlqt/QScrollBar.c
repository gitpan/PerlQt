/*
 * VQScrollBar definitions.
 *
 * Copyright (C) 1997, Ashley Winters <jql@accessone.com>
 *
 * You may distribute under the terms of the LGPL as specified in the
 * README file
 */

#include <pqscrbar.h>

const char *VQScrollBar::className() const {
    return QObject_className();
}

void VQScrollBar::connectNotify(const char *signal) {
    QObject_connectNotify(signal);
}

void VQScrollBar::disconnectNotify(const char *signal) {
    QObject_disconnectNotify(signal);
}

bool VQScrollBar::event(QEvent *event) {
    return QObject_event(event);
}

bool VQScrollBar::eventFilter(QObject *obj, QEvent *event) {
    return QObject_eventFilter(obj, event);
}

void VQScrollBar::initMetaObject() {
    if(!QScrollBar::metaObject()) QScrollBar::initMetaObject();
    QObject_initMetaObject();
}

QMetaObject *VQScrollBar::metaObject() const {
    return QObject_metaObject();
}

void VQScrollBar::timerEvent(QTimerEvent *event) {
    QObject_timerEvent(event);
}


void VQScrollBar::adjustSize() {
    QWidget_adjustSize();
}

void VQScrollBar::backgroundColorChange(const QColor &color) {
    QWidget_backgroundColorChange(color);
}

void VQScrollBar::backgroundPixmapChange(const QPixmap &pixmap) {
    QWidget_backgroundPixmapChange(pixmap);
}

bool VQScrollBar::close(bool forceKill) {
    return QWidget_close(forceKill);
}

void VQScrollBar::closeEvent(QCloseEvent *event) {
    QWidget_closeEvent(event);
}

void VQScrollBar::enabledChange(bool enable) {
    QWidget_enabledChange(enable);
}

void VQScrollBar::enterEvent(QEvent *event) {
    QWidget_enterEvent(event);
}

void VQScrollBar::focusInEvent(QFocusEvent *event) {
    QWidget_focusInEvent(event);
}

bool VQScrollBar::focusNextPrevChild(bool next) {
    return QWidget_focusNextPrevChild(next);
}

void VQScrollBar::focusOutEvent(QFocusEvent *event) {
    QWidget_focusOutEvent(event);
}

void VQScrollBar::fontChange(const QFont &font) {
    QWidget_fontChange(font);
}

void VQScrollBar::hide() {
    QWidget_hide();
}

void VQScrollBar::keyPressEvent(QKeyEvent *event) {
    QWidget_keyPressEvent(event);
}

void VQScrollBar::keyReleaseEvent(QKeyEvent *event) {
    QWidget_keyReleaseEvent(event);
}

void VQScrollBar::leaveEvent(QEvent *event) {
    QWidget_leaveEvent(event);
}

void VQScrollBar::mouseDoubleClickEvent(QMouseEvent *event) {
    QWidget_mouseDoubleClickEvent(event);
}

void VQScrollBar::mouseMoveEvent(QMouseEvent *event) {
    QWidget_mouseMoveEvent(event);
}

void VQScrollBar::mousePressEvent(QMouseEvent *event) {
    QWidget_mousePressEvent(event);
}

void VQScrollBar::mouseReleaseEvent(QMouseEvent *event) {
    QWidget_mouseReleaseEvent(event);
}

void VQScrollBar::move(int x, int y) {
    QWidget_move(x, y);
}

void VQScrollBar::moveEvent(QMoveEvent *event) {
    QWidget_moveEvent(event);
}

void VQScrollBar::paintEvent(QPaintEvent *event) {
    QWidget_paintEvent(event);
}

void VQScrollBar::paletteChange(const QPalette &palette) {
    QWidget_paletteChange(palette);
}

void VQScrollBar::resize(int w, int h) {
    QWidget_resize(w, h);
}

void VQScrollBar::resizeEvent(QResizeEvent *event) {
    QWidget_resizeEvent(event);
}

void VQScrollBar::setBackgroundColor(const QColor &color) {
    QWidget_setBackgroundColor(color);
}

void VQScrollBar::setBackgroundPixmap(const QPixmap &pixmap) {
    QWidget_setBackgroundPixmap(pixmap);
}

void VQScrollBar::setCursor(const QCursor &cursor) {
    QWidget_setCursor(cursor);
}

void VQScrollBar::setEnabled(bool enable) {
    QWidget_setEnabled(enable);
}

void VQScrollBar::setFont(const QFont &font) {
    QWidget_setFont(font);
}

void VQScrollBar::setGeometry(int x, int y, int w, int h) {
    QWidget_setGeometry(x, y, w, h);
}

void VQScrollBar::setPalette(const QPalette &palette) {
    QWidget_setPalette(palette);
}

void VQScrollBar::setStyle(GUIStyle style) {
    QWidget_setStyle(style);
}

void VQScrollBar::show() {
    QWidget_show();
}

QSize VQScrollBar::sizeHint() const {
    return QWidget_sizeHint();
}

void VQScrollBar::styleChange(GUIStyle style) {
    QWidget_styleChange(style);
}


void VQScrollBar::rangeChange() {
    QRangeControl_rangeChange();
}

void VQScrollBar::stepChange() {
    QRangeControl_stepChange();
}

void VQScrollBar::valueChange() {
    QRangeControl_valueChange();
}


