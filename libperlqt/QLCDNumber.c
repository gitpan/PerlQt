/*
 * VQLCDNumber definitions.
 *
 * Copyright (C) 1997, Ashley Winters <jql@accessone.com>
 *
 * You may distribute under the terms of the LGPL as specified in the
 * README file
 */

#include <pqlcdnum.h>

const char *VQLCDNumber::className() const {
    return QObject_className();
}

void VQLCDNumber::connectNotify(const char *signal) {
    QObject_connectNotify(signal);
}

void VQLCDNumber::disconnectNotify(const char *signal) {
    QObject_disconnectNotify(signal);
}

bool VQLCDNumber::event(QEvent *event) {
    return QObject_event(event);
}

bool VQLCDNumber::eventFilter(QObject *obj, QEvent *event) {
    return QObject_eventFilter(obj, event);
}

void VQLCDNumber::initMetaObject() {
    if(!QLCDNumber::metaObject()) QLCDNumber::initMetaObject();
    QObject_initMetaObject();
}

QMetaObject *VQLCDNumber::metaObject() const {
    return QObject_metaObject();
}

void VQLCDNumber::timerEvent(QTimerEvent *event) {
    QObject_timerEvent(event);
}


void VQLCDNumber::adjustSize() {
    QWidget_adjustSize();
}

void VQLCDNumber::backgroundColorChange(const QColor &color) {
    QWidget_backgroundColorChange(color);
}

void VQLCDNumber::backgroundPixmapChange(const QPixmap &pixmap) {
    QWidget_backgroundPixmapChange(pixmap);
}

bool VQLCDNumber::close(bool forceKill) {
    return QWidget_close(forceKill);
}

void VQLCDNumber::closeEvent(QCloseEvent *event) {
    QWidget_closeEvent(event);
}

void VQLCDNumber::enabledChange(bool enable) {
    QWidget_enabledChange(enable);
}

void VQLCDNumber::enterEvent(QEvent *event) {
    QWidget_enterEvent(event);
}

void VQLCDNumber::focusInEvent(QFocusEvent *event) {
    QWidget_focusInEvent(event);
}

bool VQLCDNumber::focusNextPrevChild(bool next) {
    return QWidget_focusNextPrevChild(next);
}

void VQLCDNumber::focusOutEvent(QFocusEvent *event) {
    QWidget_focusOutEvent(event);
}

void VQLCDNumber::fontChange(const QFont &font) {
    QWidget_fontChange(font);
}

void VQLCDNumber::hide() {
    QWidget_hide();
}

void VQLCDNumber::keyPressEvent(QKeyEvent *event) {
    QWidget_keyPressEvent(event);
}

void VQLCDNumber::keyReleaseEvent(QKeyEvent *event) {
    QWidget_keyReleaseEvent(event);
}

void VQLCDNumber::leaveEvent(QEvent *event) {
    QWidget_leaveEvent(event);
}

void VQLCDNumber::mouseDoubleClickEvent(QMouseEvent *event) {
    QWidget_mouseDoubleClickEvent(event);
}

void VQLCDNumber::mouseMoveEvent(QMouseEvent *event) {
    QWidget_mouseMoveEvent(event);
}

void VQLCDNumber::mousePressEvent(QMouseEvent *event) {
    QWidget_mousePressEvent(event);
}

void VQLCDNumber::mouseReleaseEvent(QMouseEvent *event) {
    QWidget_mouseReleaseEvent(event);
}

void VQLCDNumber::move(int x, int y) {
    QWidget_move(x, y);
}

void VQLCDNumber::moveEvent(QMoveEvent *event) {
    QWidget_moveEvent(event);
}

void VQLCDNumber::paintEvent(QPaintEvent *event) {
    QWidget_paintEvent(event);
}

void VQLCDNumber::paletteChange(const QPalette &palette) {
    QWidget_paletteChange(palette);
}

void VQLCDNumber::resize(int w, int h) {
    QWidget_resize(w, h);
}

void VQLCDNumber::resizeEvent(QResizeEvent *event) {
    QWidget_resizeEvent(event);
}

void VQLCDNumber::setBackgroundColor(const QColor &color) {
    QWidget_setBackgroundColor(color);
}

void VQLCDNumber::setBackgroundPixmap(const QPixmap &pixmap) {
    QWidget_setBackgroundPixmap(pixmap);
}

void VQLCDNumber::setCursor(const QCursor &cursor) {
    QWidget_setCursor(cursor);
}

void VQLCDNumber::setEnabled(bool enable) {
    QWidget_setEnabled(enable);
}

void VQLCDNumber::setFont(const QFont &font) {
    QWidget_setFont(font);
}

void VQLCDNumber::setGeometry(int x, int y, int w, int h) {
    QWidget_setGeometry(x, y, w, h);
}

void VQLCDNumber::setPalette(const QPalette &palette) {
    QWidget_setPalette(palette);
}

void VQLCDNumber::setStyle(GUIStyle style) {
    QWidget_setStyle(style);
}

void VQLCDNumber::show() {
    QWidget_show();
}

QSize VQLCDNumber::sizeHint() const {
    return QWidget_sizeHint();
}

void VQLCDNumber::styleChange(GUIStyle style) {
    QWidget_styleChange(style);
}


void VQLCDNumber::drawContents(QPainter *p) {
    QFrame_drawContents(p);
}

void VQLCDNumber::drawFrame(QPainter *p) {
    QFrame_drawFrame(p);
}

void VQLCDNumber::frameChanged() {
    QFrame_frameChanged();
}


