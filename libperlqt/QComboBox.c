/*
 * VQComboBox definitions.
 *
 * Copyright (C) 1997, Ashley Winters <jql@accessone.com>
 *
 * You may distribute under the terms of the LGPL as specified in the
 * README file
 */

#include <pqcombo.h>

const char *VQComboBox::className() const {
    return QObject_className();
}

void VQComboBox::connectNotify(const char *signal) {
    QObject_connectNotify(signal);
}

void VQComboBox::disconnectNotify(const char *signal) {
    QObject_disconnectNotify(signal);
}

bool VQComboBox::event(QEvent *event) {
    return QObject_event(event);
}

void VQComboBox::initMetaObject() {
    if(!QComboBox::metaObject()) QComboBox::initMetaObject();
    QObject_initMetaObject();
}

QMetaObject *VQComboBox::metaObject() const {
    return QObject_metaObject();
}

void VQComboBox::timerEvent(QTimerEvent *event) {
    QObject_timerEvent(event);
}


void VQComboBox::adjustSize() {
    QWidget_adjustSize();
}

void VQComboBox::backgroundColorChange(const QColor &color) {
    QWidget_backgroundColorChange(color);
}

void VQComboBox::backgroundPixmapChange(const QPixmap &pixmap) {
    QWidget_backgroundPixmapChange(pixmap);
}

bool VQComboBox::close(bool forceKill) {
    return QWidget_close(forceKill);
}

void VQComboBox::closeEvent(QCloseEvent *event) {
    QWidget_closeEvent(event);
}

void VQComboBox::enabledChange(bool enable) {
    QWidget_enabledChange(enable);
}

void VQComboBox::enterEvent(QEvent *event) {
    QWidget_enterEvent(event);
}

void VQComboBox::focusInEvent(QFocusEvent *event) {
    QWidget_focusInEvent(event);
}

bool VQComboBox::focusNextPrevChild(bool next) {
    return QWidget_focusNextPrevChild(next);
}

void VQComboBox::focusOutEvent(QFocusEvent *event) {
    QWidget_focusOutEvent(event);
}

void VQComboBox::fontChange(const QFont &font) {
    QWidget_fontChange(font);
}

void VQComboBox::hide() {
    QWidget_hide();
}

void VQComboBox::keyPressEvent(QKeyEvent *event) {
    QWidget_keyPressEvent(event);
}

void VQComboBox::keyReleaseEvent(QKeyEvent *event) {
    QWidget_keyReleaseEvent(event);
}

void VQComboBox::leaveEvent(QEvent *event) {
    QWidget_leaveEvent(event);
}

void VQComboBox::mouseDoubleClickEvent(QMouseEvent *event) {
    QWidget_mouseDoubleClickEvent(event);
}

void VQComboBox::mouseMoveEvent(QMouseEvent *event) {
    QWidget_mouseMoveEvent(event);
}

void VQComboBox::mousePressEvent(QMouseEvent *event) {
    QWidget_mousePressEvent(event);
}

void VQComboBox::mouseReleaseEvent(QMouseEvent *event) {
    QWidget_mouseReleaseEvent(event);
}

void VQComboBox::move(int x, int y) {
    QWidget_move(x, y);
}

void VQComboBox::moveEvent(QMoveEvent *event) {
    QWidget_moveEvent(event);
}

void VQComboBox::paintEvent(QPaintEvent *event) {
    QWidget_paintEvent(event);
}

void VQComboBox::paletteChange(const QPalette &palette) {
    QWidget_paletteChange(palette);
}

void VQComboBox::resize(int w, int h) {
    QWidget_resize(w, h);
}

void VQComboBox::resizeEvent(QResizeEvent *event) {
    QWidget_resizeEvent(event);
}

void VQComboBox::setBackgroundColor(const QColor &color) {
    QWidget_setBackgroundColor(color);
}

void VQComboBox::setBackgroundPixmap(const QPixmap &pixmap) {
    QWidget_setBackgroundPixmap(pixmap);
}

void VQComboBox::setCursor(const QCursor &cursor) {
    QWidget_setCursor(cursor);
}

void VQComboBox::setEnabled(bool enable) {
    QWidget_setEnabled(enable);
}

void VQComboBox::setFont(const QFont &font) {
    QWidget_setFont(font);
}

void VQComboBox::setGeometry(int x, int y, int w, int h) {
    QWidget_setGeometry(x, y, w, h);
}

void VQComboBox::setPalette(const QPalette &palette) {
    QWidget_setPalette(palette);
}

void VQComboBox::setStyle(GUIStyle style) {
    QWidget_setStyle(style);
}

void VQComboBox::show() {
    QWidget_show();
}

QSize VQComboBox::sizeHint() const {
    return QWidget_sizeHint();
}

void VQComboBox::styleChange(GUIStyle style) {
    QWidget_styleChange(style);
}


