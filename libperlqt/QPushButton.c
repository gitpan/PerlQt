/*
 * VQPushButton definitions.
 *
 * Copyright (C) 1997, Ashley Winters <jql@accessone.com>
 *
 * You may distribute under the terms of the LGPL as specified in the
 * README file
 */

#include <pqpushbt.h>

const char *VQPushButton::className() const {
    return QObject_className();
}

void VQPushButton::connectNotify(const char *signal) {
    QObject_connectNotify(signal);
}

void VQPushButton::disconnectNotify(const char *signal) {
    QObject_disconnectNotify(signal);
}

bool VQPushButton::event(QEvent *event) {
    return QObject_event(event);
}

bool VQPushButton::eventFilter(QObject *obj, QEvent *event) {
    return QObject_eventFilter(obj, event);
}

void VQPushButton::initMetaObject() {
    if(!QPushButton::metaObject()) QPushButton::initMetaObject();
    QObject_initMetaObject();
}

QMetaObject *VQPushButton::metaObject() const {
    return QObject_metaObject();
}

void VQPushButton::timerEvent(QTimerEvent *event) {
    QObject_timerEvent(event);
}


void VQPushButton::adjustSize() {
    QWidget_adjustSize();
}

void VQPushButton::backgroundColorChange(const QColor &color) {
    QWidget_backgroundColorChange(color);
}

void VQPushButton::backgroundPixmapChange(const QPixmap &pixmap) {
    QWidget_backgroundPixmapChange(pixmap);
}

bool VQPushButton::close(bool forceKill) {
    return QWidget_close(forceKill);
}

void VQPushButton::closeEvent(QCloseEvent *event) {
    QWidget_closeEvent(event);
}

void VQPushButton::enabledChange(bool enable) {
    QWidget_enabledChange(enable);
}

void VQPushButton::enterEvent(QEvent *event) {
    QWidget_enterEvent(event);
}

void VQPushButton::focusInEvent(QFocusEvent *event) {
    QWidget_focusInEvent(event);
}

bool VQPushButton::focusNextPrevChild(bool next) {
    return QWidget_focusNextPrevChild(next);
}

void VQPushButton::focusOutEvent(QFocusEvent *event) {
    QWidget_focusOutEvent(event);
}

void VQPushButton::fontChange(const QFont &font) {
    QWidget_fontChange(font);
}

void VQPushButton::hide() {
    QWidget_hide();
}

void VQPushButton::keyPressEvent(QKeyEvent *event) {
    QWidget_keyPressEvent(event);
}

void VQPushButton::keyReleaseEvent(QKeyEvent *event) {
    QWidget_keyReleaseEvent(event);
}

void VQPushButton::leaveEvent(QEvent *event) {
    QWidget_leaveEvent(event);
}

void VQPushButton::mouseDoubleClickEvent(QMouseEvent *event) {
    QWidget_mouseDoubleClickEvent(event);
}

void VQPushButton::mouseMoveEvent(QMouseEvent *event) {
    QWidget_mouseMoveEvent(event);
}

void VQPushButton::mousePressEvent(QMouseEvent *event) {
    QWidget_mousePressEvent(event);
}

void VQPushButton::mouseReleaseEvent(QMouseEvent *event) {
    QWidget_mouseReleaseEvent(event);
}

void VQPushButton::move(int x, int y) {
    QWidget_move(x, y);
}

void VQPushButton::moveEvent(QMoveEvent *event) {
    QWidget_moveEvent(event);
}

void VQPushButton::paintEvent(QPaintEvent *event) {
    QWidget_paintEvent(event);
}

void VQPushButton::paletteChange(const QPalette &palette) {
    QWidget_paletteChange(palette);
}

void VQPushButton::resize(int w, int h) {
    QWidget_resize(w, h);
}

void VQPushButton::resizeEvent(QResizeEvent *event) {
    QWidget_resizeEvent(event);
}

void VQPushButton::setBackgroundColor(const QColor &color) {
    QWidget_setBackgroundColor(color);
}

void VQPushButton::setBackgroundPixmap(const QPixmap &pixmap) {
    QWidget_setBackgroundPixmap(pixmap);
}

void VQPushButton::setCursor(const QCursor &cursor) {
    QWidget_setCursor(cursor);
}

void VQPushButton::setEnabled(bool enable) {
    QWidget_setEnabled(enable);
}

void VQPushButton::setFont(const QFont &font) {
    QWidget_setFont(font);
}

void VQPushButton::setGeometry(int x, int y, int w, int h) {
    QWidget_setGeometry(x, y, w, h);
}

void VQPushButton::setPalette(const QPalette &palette) {
    QWidget_setPalette(palette);
}

void VQPushButton::setStyle(GUIStyle style) {
    QWidget_setStyle(style);
}

void VQPushButton::show() {
    QWidget_show();
}

QSize VQPushButton::sizeHint() const {
    return QWidget_sizeHint();
}

void VQPushButton::styleChange(GUIStyle style) {
    QWidget_styleChange(style);
}


void VQPushButton::drawButton(QPainter *p) {
    QButton_drawButton(p);
}

void VQPushButton::drawButtonLabel(QPainter *p) {
    QButton_drawButtonLabel(p);
}

bool VQPushButton::hitButton(const QPoint &pos) const {
    return QButton_hitButton(pos);
}


