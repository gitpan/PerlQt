/*
 * VQTabBar definitions.
 *
 * Copyright (C) 1997, Ashley Winters <jql@accessone.com>
 *
 * You may distribute under the terms of the LGPL as specified in the
 * README file
 */

#include <pqtabbar.h>

const char *VQTabBar::className() const {
    return QObject_className();
}

void VQTabBar::connectNotify(const char *signal) {
    QObject_connectNotify(signal);
}

void VQTabBar::disconnectNotify(const char *signal) {
    QObject_disconnectNotify(signal);
}

bool VQTabBar::event(QEvent *event) {
    return QObject_event(event);
}

bool VQTabBar::eventFilter(QObject *obj, QEvent *event) {
    return QObject_eventFilter(obj, event);
}

void VQTabBar::initMetaObject() {
    if(!QTabBar::metaObject()) QTabBar::initMetaObject();
    QObject_initMetaObject();
}

QMetaObject *VQTabBar::metaObject() const {
    return QObject_metaObject();
}

void VQTabBar::timerEvent(QTimerEvent *event) {
    QObject_timerEvent(event);
}


void VQTabBar::adjustSize() {
    QWidget_adjustSize();
}

void VQTabBar::backgroundColorChange(const QColor &color) {
    QWidget_backgroundColorChange(color);
}

void VQTabBar::backgroundPixmapChange(const QPixmap &pixmap) {
    QWidget_backgroundPixmapChange(pixmap);
}

bool VQTabBar::close(bool forceKill) {
    return QWidget_close(forceKill);
}

void VQTabBar::closeEvent(QCloseEvent *event) {
    QWidget_closeEvent(event);
}

void VQTabBar::enabledChange(bool enable) {
    QWidget_enabledChange(enable);
}

void VQTabBar::enterEvent(QEvent *event) {
    QWidget_enterEvent(event);
}

void VQTabBar::focusInEvent(QFocusEvent *event) {
    QWidget_focusInEvent(event);
}

bool VQTabBar::focusNextPrevChild(bool next) {
    return QWidget_focusNextPrevChild(next);
}

void VQTabBar::focusOutEvent(QFocusEvent *event) {
    QWidget_focusOutEvent(event);
}

void VQTabBar::fontChange(const QFont &font) {
    QWidget_fontChange(font);
}

void VQTabBar::hide() {
    QWidget_hide();
}

void VQTabBar::keyPressEvent(QKeyEvent *event) {
    QWidget_keyPressEvent(event);
}

void VQTabBar::keyReleaseEvent(QKeyEvent *event) {
    QWidget_keyReleaseEvent(event);
}

void VQTabBar::leaveEvent(QEvent *event) {
    QWidget_leaveEvent(event);
}

void VQTabBar::mouseDoubleClickEvent(QMouseEvent *event) {
    QWidget_mouseDoubleClickEvent(event);
}

void VQTabBar::mouseMoveEvent(QMouseEvent *event) {
    QWidget_mouseMoveEvent(event);
}

void VQTabBar::mousePressEvent(QMouseEvent *event) {
    QWidget_mousePressEvent(event);
}

void VQTabBar::mouseReleaseEvent(QMouseEvent *event) {
    QWidget_mouseReleaseEvent(event);
}

void VQTabBar::move(int x, int y) {
    QWidget_move(x, y);
}

void VQTabBar::moveEvent(QMoveEvent *event) {
    QWidget_moveEvent(event);
}

void VQTabBar::paintEvent(QPaintEvent *event) {
    QWidget_paintEvent(event);
}

void VQTabBar::paletteChange(const QPalette &palette) {
    QWidget_paletteChange(palette);
}

void VQTabBar::resize(int w, int h) {
    QWidget_resize(w, h);
}

void VQTabBar::resizeEvent(QResizeEvent *event) {
    QWidget_resizeEvent(event);
}

void VQTabBar::setBackgroundColor(const QColor &color) {
    QWidget_setBackgroundColor(color);
}

void VQTabBar::setBackgroundPixmap(const QPixmap &pixmap) {
    QWidget_setBackgroundPixmap(pixmap);
}

void VQTabBar::setCursor(const QCursor &cursor) {
    QWidget_setCursor(cursor);
}

void VQTabBar::setEnabled(bool enable) {
    QWidget_setEnabled(enable);
}

void VQTabBar::setFont(const QFont &font) {
    QWidget_setFont(font);
}

void VQTabBar::setGeometry(int x, int y, int w, int h) {
    QWidget_setGeometry(x, y, w, h);
}

void VQTabBar::setPalette(const QPalette &palette) {
    QWidget_setPalette(palette);
}

void VQTabBar::setStyle(GUIStyle style) {
    QWidget_setStyle(style);
}

void VQTabBar::show() {
    QWidget_show();
}

QSize VQTabBar::sizeHint() const {
    return QWidget_sizeHint();
}

void VQTabBar::styleChange(GUIStyle style) {
    QWidget_styleChange(style);
}


