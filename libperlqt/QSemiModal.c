/*
 * VQSemiModal definitions.
 *
 * Copyright (C) 1997, Ashley Winters <jql@accessone.com>
 *
 * You may distribute under the terms of the LGPL as specified in the
 * README file
 */

#include <pqsemimodal.h>

const char *VQSemiModal::className() const {
    return QObject_className();
}

void VQSemiModal::connectNotify(const char *signal) {
    QObject_connectNotify(signal);
}

void VQSemiModal::disconnectNotify(const char *signal) {
    QObject_disconnectNotify(signal);
}

bool VQSemiModal::event(QEvent *event) {
    return QObject_event(event);
}

bool VQSemiModal::eventFilter(QObject *obj, QEvent *event) {
    return QObject_eventFilter(obj, event);
}

void VQSemiModal::initMetaObject() {
    if(!QSemiModal::metaObject()) QSemiModal::initMetaObject();
    QObject_initMetaObject();
}

QMetaObject *VQSemiModal::metaObject() const {
    return QObject_metaObject();
}

void VQSemiModal::timerEvent(QTimerEvent *event) {
    QObject_timerEvent(event);
}


void VQSemiModal::adjustSize() {
    QWidget_adjustSize();
}

void VQSemiModal::backgroundColorChange(const QColor &color) {
    QWidget_backgroundColorChange(color);
}

void VQSemiModal::backgroundPixmapChange(const QPixmap &pixmap) {
    QWidget_backgroundPixmapChange(pixmap);
}

bool VQSemiModal::close(bool forceKill) {
    return QWidget_close(forceKill);
}

void VQSemiModal::closeEvent(QCloseEvent *event) {
    QWidget_closeEvent(event);
}

void VQSemiModal::enabledChange(bool enable) {
    QWidget_enabledChange(enable);
}

void VQSemiModal::enterEvent(QEvent *event) {
    QWidget_enterEvent(event);
}

void VQSemiModal::focusInEvent(QFocusEvent *event) {
    QWidget_focusInEvent(event);
}

bool VQSemiModal::focusNextPrevChild(bool next) {
    return QWidget_focusNextPrevChild(next);
}

void VQSemiModal::focusOutEvent(QFocusEvent *event) {
    QWidget_focusOutEvent(event);
}

void VQSemiModal::fontChange(const QFont &font) {
    QWidget_fontChange(font);
}

void VQSemiModal::hide() {
    QWidget_hide();
}

void VQSemiModal::keyPressEvent(QKeyEvent *event) {
    QWidget_keyPressEvent(event);
}

void VQSemiModal::keyReleaseEvent(QKeyEvent *event) {
    QWidget_keyReleaseEvent(event);
}

void VQSemiModal::leaveEvent(QEvent *event) {
    QWidget_leaveEvent(event);
}

void VQSemiModal::mouseDoubleClickEvent(QMouseEvent *event) {
    QWidget_mouseDoubleClickEvent(event);
}

void VQSemiModal::mouseMoveEvent(QMouseEvent *event) {
    QWidget_mouseMoveEvent(event);
}

void VQSemiModal::mousePressEvent(QMouseEvent *event) {
    QWidget_mousePressEvent(event);
}

void VQSemiModal::mouseReleaseEvent(QMouseEvent *event) {
    QWidget_mouseReleaseEvent(event);
}

void VQSemiModal::move(int x, int y) {
    QWidget_move(x, y);
}

void VQSemiModal::moveEvent(QMoveEvent *event) {
    QWidget_moveEvent(event);
}

void VQSemiModal::paintEvent(QPaintEvent *event) {
    QWidget_paintEvent(event);
}

void VQSemiModal::paletteChange(const QPalette &palette) {
    QWidget_paletteChange(palette);
}

void VQSemiModal::resize(int w, int h) {
    QWidget_resize(w, h);
}

void VQSemiModal::resizeEvent(QResizeEvent *event) {
    QWidget_resizeEvent(event);
}

void VQSemiModal::setBackgroundColor(const QColor &color) {
    QWidget_setBackgroundColor(color);
}

void VQSemiModal::setBackgroundPixmap(const QPixmap &pixmap) {
    QWidget_setBackgroundPixmap(pixmap);
}

void VQSemiModal::setCursor(const QCursor &cursor) {
    QWidget_setCursor(cursor);
}

void VQSemiModal::setEnabled(bool enable) {
    QWidget_setEnabled(enable);
}

void VQSemiModal::setFont(const QFont &font) {
    QWidget_setFont(font);
}

void VQSemiModal::setGeometry(int x, int y, int w, int h) {
    QWidget_setGeometry(x, y, w, h);
}

void VQSemiModal::setPalette(const QPalette &palette) {
    QWidget_setPalette(palette);
}

void VQSemiModal::setStyle(GUIStyle style) {
    QWidget_setStyle(style);
}

void VQSemiModal::show() {
    QWidget_show();
}

QSize VQSemiModal::sizeHint() const {
    return QWidget_sizeHint();
}

void VQSemiModal::styleChange(GUIStyle style) {
    QWidget_styleChange(style);
}


