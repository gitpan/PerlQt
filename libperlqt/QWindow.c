/*
 * VQWindow definitions.
 *
 * Copyright (C) 1997, Ashley Winters <jql@accessone.com>
 *
 * You may distribute under the terms of the LGPL as specified in the
 * README file
 */

#include <pqwindow.h>

const char *VQWindow::className() const {
    return QObject_className();
}

void VQWindow::connectNotify(const char *signal) {
    QObject_connectNotify(signal);
}

void VQWindow::disconnectNotify(const char *signal) {
    QObject_disconnectNotify(signal);
}

bool VQWindow::event(QEvent *event) {
    return QObject_event(event);
}

bool VQWindow::eventFilter(QObject *obj, QEvent *event) {
    return QObject_eventFilter(obj, event);
}

void VQWindow::initMetaObject() {
    if(!QWindow::metaObject()) QWindow::initMetaObject();
    QObject_initMetaObject();
}

QMetaObject *VQWindow::metaObject() const {
    return QObject_metaObject();
}

void VQWindow::timerEvent(QTimerEvent *event) {
    QObject_timerEvent(event);
}


void VQWindow::adjustSize() {
    QWidget_adjustSize();
}

void VQWindow::backgroundColorChange(const QColor &color) {
    QWidget_backgroundColorChange(color);
}

void VQWindow::backgroundPixmapChange(const QPixmap &pixmap) {
    QWidget_backgroundPixmapChange(pixmap);
}

bool VQWindow::close(bool forceKill) {
    return QWidget_close(forceKill);
}

void VQWindow::closeEvent(QCloseEvent *event) {
    QWidget_closeEvent(event);
}

void VQWindow::enabledChange(bool enable) {
    QWidget_enabledChange(enable);
}

void VQWindow::enterEvent(QEvent *event) {
    QWidget_enterEvent(event);
}

void VQWindow::focusInEvent(QFocusEvent *event) {
    QWidget_focusInEvent(event);
}

bool VQWindow::focusNextPrevChild(bool next) {
    return QWidget_focusNextPrevChild(next);
}

void VQWindow::focusOutEvent(QFocusEvent *event) {
    QWidget_focusOutEvent(event);
}

void VQWindow::fontChange(const QFont &font) {
    QWidget_fontChange(font);
}

void VQWindow::hide() {
    QWidget_hide();
}

void VQWindow::keyPressEvent(QKeyEvent *event) {
    QWidget_keyPressEvent(event);
}

void VQWindow::keyReleaseEvent(QKeyEvent *event) {
    QWidget_keyReleaseEvent(event);
}

void VQWindow::leaveEvent(QEvent *event) {
    QWidget_leaveEvent(event);
}

void VQWindow::mouseDoubleClickEvent(QMouseEvent *event) {
    QWidget_mouseDoubleClickEvent(event);
}

void VQWindow::mouseMoveEvent(QMouseEvent *event) {
    QWidget_mouseMoveEvent(event);
}

void VQWindow::mousePressEvent(QMouseEvent *event) {
    QWidget_mousePressEvent(event);
}

void VQWindow::mouseReleaseEvent(QMouseEvent *event) {
    QWidget_mouseReleaseEvent(event);
}

void VQWindow::move(int x, int y) {
    QWidget_move(x, y);
}

void VQWindow::moveEvent(QMoveEvent *event) {
    QWidget_moveEvent(event);
}

void VQWindow::paintEvent(QPaintEvent *event) {
    QWidget_paintEvent(event);
}

void VQWindow::paletteChange(const QPalette &palette) {
    QWidget_paletteChange(palette);
}

void VQWindow::resize(int w, int h) {
    QWidget_resize(w, h);
}

void VQWindow::resizeEvent(QResizeEvent *event) {
    QWidget_resizeEvent(event);
}

void VQWindow::setBackgroundColor(const QColor &color) {
    QWidget_setBackgroundColor(color);
}

void VQWindow::setBackgroundPixmap(const QPixmap &pixmap) {
    QWidget_setBackgroundPixmap(pixmap);
}

void VQWindow::setCursor(const QCursor &cursor) {
    QWidget_setCursor(cursor);
}

void VQWindow::setEnabled(bool enable) {
    QWidget_setEnabled(enable);
}

void VQWindow::setFont(const QFont &font) {
    QWidget_setFont(font);
}

void VQWindow::setGeometry(int x, int y, int w, int h) {
    QWidget_setGeometry(x, y, w, h);
}

void VQWindow::setPalette(const QPalette &palette) {
    QWidget_setPalette(palette);
}

void VQWindow::setStyle(GUIStyle style) {
    QWidget_setStyle(style);
}

void VQWindow::show() {
    QWidget_show();
}

QSize VQWindow::sizeHint() const {
    return QWidget_sizeHint();
}

void VQWindow::styleChange(GUIStyle style) {
    QWidget_styleChange(style);
}


