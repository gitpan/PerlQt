/*
 * VQLineEdit definitions.
 *
 * Copyright (C) 1997, Ashley Winters <jql@accessone.com>
 *
 * You may distribute under the terms of the LGPL as specified in the
 * README file
 */

#include <pqlined.h>

const char *VQLineEdit::className() const {
    return QObject_className();
}

void VQLineEdit::connectNotify(const char *signal) {
    QObject_connectNotify(signal);
}

void VQLineEdit::disconnectNotify(const char *signal) {
    QObject_disconnectNotify(signal);
}

bool VQLineEdit::event(QEvent *event) {
    return QObject_event(event);
}

bool VQLineEdit::eventFilter(QObject *obj, QEvent *event) {
    return QObject_eventFilter(obj, event);
}

void VQLineEdit::initMetaObject() {
    if(!QLineEdit::metaObject()) QLineEdit::initMetaObject();
    QObject_initMetaObject();
}

QMetaObject *VQLineEdit::metaObject() const {
    return QObject_metaObject();
}

void VQLineEdit::timerEvent(QTimerEvent *event) {
    QObject_timerEvent(event);
}


void VQLineEdit::adjustSize() {
    QWidget_adjustSize();
}

void VQLineEdit::backgroundColorChange(const QColor &color) {
    QWidget_backgroundColorChange(color);
}

void VQLineEdit::backgroundPixmapChange(const QPixmap &pixmap) {
    QWidget_backgroundPixmapChange(pixmap);
}

bool VQLineEdit::close(bool forceKill) {
    return QWidget_close(forceKill);
}

void VQLineEdit::closeEvent(QCloseEvent *event) {
    QWidget_closeEvent(event);
}

void VQLineEdit::enabledChange(bool enable) {
    QWidget_enabledChange(enable);
}

void VQLineEdit::enterEvent(QEvent *event) {
    QWidget_enterEvent(event);
}

void VQLineEdit::focusInEvent(QFocusEvent *event) {
    QWidget_focusInEvent(event);
}

bool VQLineEdit::focusNextPrevChild(bool next) {
    return QWidget_focusNextPrevChild(next);
}

void VQLineEdit::focusOutEvent(QFocusEvent *event) {
    QWidget_focusOutEvent(event);
}

void VQLineEdit::fontChange(const QFont &font) {
    QWidget_fontChange(font);
}

void VQLineEdit::hide() {
    QWidget_hide();
}

void VQLineEdit::keyPressEvent(QKeyEvent *event) {
    QWidget_keyPressEvent(event);
}

void VQLineEdit::keyReleaseEvent(QKeyEvent *event) {
    QWidget_keyReleaseEvent(event);
}

void VQLineEdit::leaveEvent(QEvent *event) {
    QWidget_leaveEvent(event);
}

void VQLineEdit::mouseDoubleClickEvent(QMouseEvent *event) {
    QWidget_mouseDoubleClickEvent(event);
}

void VQLineEdit::mouseMoveEvent(QMouseEvent *event) {
    QWidget_mouseMoveEvent(event);
}

void VQLineEdit::mousePressEvent(QMouseEvent *event) {
    QWidget_mousePressEvent(event);
}

void VQLineEdit::mouseReleaseEvent(QMouseEvent *event) {
    QWidget_mouseReleaseEvent(event);
}

void VQLineEdit::move(int x, int y) {
    QWidget_move(x, y);
}

void VQLineEdit::moveEvent(QMoveEvent *event) {
    QWidget_moveEvent(event);
}

void VQLineEdit::paintEvent(QPaintEvent *event) {
    QWidget_paintEvent(event);
}

void VQLineEdit::paletteChange(const QPalette &palette) {
    QWidget_paletteChange(palette);
}

void VQLineEdit::resize(int w, int h) {
    QWidget_resize(w, h);
}

void VQLineEdit::resizeEvent(QResizeEvent *event) {
    QWidget_resizeEvent(event);
}

void VQLineEdit::setBackgroundColor(const QColor &color) {
    QWidget_setBackgroundColor(color);
}

void VQLineEdit::setBackgroundPixmap(const QPixmap &pixmap) {
    QWidget_setBackgroundPixmap(pixmap);
}

void VQLineEdit::setCursor(const QCursor &cursor) {
    QWidget_setCursor(cursor);
}

void VQLineEdit::setEnabled(bool enable) {
    QWidget_setEnabled(enable);
}

void VQLineEdit::setFont(const QFont &font) {
    QWidget_setFont(font);
}

void VQLineEdit::setGeometry(int x, int y, int w, int h) {
    QWidget_setGeometry(x, y, w, h);
}

void VQLineEdit::setPalette(const QPalette &palette) {
    QWidget_setPalette(palette);
}

void VQLineEdit::setStyle(GUIStyle style) {
    QWidget_setStyle(style);
}

void VQLineEdit::show() {
    QWidget_show();
}

QSize VQLineEdit::sizeHint() const {
    return QWidget_sizeHint();
}

void VQLineEdit::styleChange(GUIStyle style) {
    QWidget_styleChange(style);
}


