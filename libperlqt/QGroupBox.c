/*
 * VQGroupBox definitions.
 *
 * Copyright (C) 1997, Ashley Winters <jql@accessone.com>
 *
 * You may distribute under the terms of the LGPL as specified in the
 * README file
 */

#include <pqgrpbox.h>

const char *VQGroupBox::className() const {
    return QObject_className();
}

void VQGroupBox::connectNotify(const char *signal) {
    QObject_connectNotify(signal);
}

void VQGroupBox::disconnectNotify(const char *signal) {
    QObject_disconnectNotify(signal);
}

bool VQGroupBox::event(QEvent *event) {
    return QObject_event(event);
}

bool VQGroupBox::eventFilter(QObject *obj, QEvent *event) {
    return QObject_eventFilter(obj, event);
}

void VQGroupBox::initMetaObject() {
    if(!QGroupBox::metaObject()) QGroupBox::initMetaObject();
    QObject_initMetaObject();
}

QMetaObject *VQGroupBox::metaObject() const {
    return QObject_metaObject();
}

void VQGroupBox::timerEvent(QTimerEvent *event) {
    QObject_timerEvent(event);
}


void VQGroupBox::adjustSize() {
    QWidget_adjustSize();
}

void VQGroupBox::backgroundColorChange(const QColor &color) {
    QWidget_backgroundColorChange(color);
}

void VQGroupBox::backgroundPixmapChange(const QPixmap &pixmap) {
    QWidget_backgroundPixmapChange(pixmap);
}

bool VQGroupBox::close(bool forceKill) {
    return QWidget_close(forceKill);
}

void VQGroupBox::closeEvent(QCloseEvent *event) {
    QWidget_closeEvent(event);
}

void VQGroupBox::enabledChange(bool enable) {
    QWidget_enabledChange(enable);
}

void VQGroupBox::enterEvent(QEvent *event) {
    QWidget_enterEvent(event);
}

void VQGroupBox::focusInEvent(QFocusEvent *event) {
    QWidget_focusInEvent(event);
}

bool VQGroupBox::focusNextPrevChild(bool next) {
    return QWidget_focusNextPrevChild(next);
}

void VQGroupBox::focusOutEvent(QFocusEvent *event) {
    QWidget_focusOutEvent(event);
}

void VQGroupBox::fontChange(const QFont &font) {
    QWidget_fontChange(font);
}

void VQGroupBox::hide() {
    QWidget_hide();
}

void VQGroupBox::keyPressEvent(QKeyEvent *event) {
    QWidget_keyPressEvent(event);
}

void VQGroupBox::keyReleaseEvent(QKeyEvent *event) {
    QWidget_keyReleaseEvent(event);
}

void VQGroupBox::leaveEvent(QEvent *event) {
    QWidget_leaveEvent(event);
}

void VQGroupBox::mouseDoubleClickEvent(QMouseEvent *event) {
    QWidget_mouseDoubleClickEvent(event);
}

void VQGroupBox::mouseMoveEvent(QMouseEvent *event) {
    QWidget_mouseMoveEvent(event);
}

void VQGroupBox::mousePressEvent(QMouseEvent *event) {
    QWidget_mousePressEvent(event);
}

void VQGroupBox::mouseReleaseEvent(QMouseEvent *event) {
    QWidget_mouseReleaseEvent(event);
}

void VQGroupBox::move(int x, int y) {
    QWidget_move(x, y);
}

void VQGroupBox::moveEvent(QMoveEvent *event) {
    QWidget_moveEvent(event);
}

void VQGroupBox::paintEvent(QPaintEvent *event) {
    QWidget_paintEvent(event);
}

void VQGroupBox::paletteChange(const QPalette &palette) {
    QWidget_paletteChange(palette);
}

void VQGroupBox::resize(int w, int h) {
    QWidget_resize(w, h);
}

void VQGroupBox::resizeEvent(QResizeEvent *event) {
    QWidget_resizeEvent(event);
}

void VQGroupBox::setBackgroundColor(const QColor &color) {
    QWidget_setBackgroundColor(color);
}

void VQGroupBox::setBackgroundPixmap(const QPixmap &pixmap) {
    QWidget_setBackgroundPixmap(pixmap);
}

void VQGroupBox::setCursor(const QCursor &cursor) {
    QWidget_setCursor(cursor);
}

void VQGroupBox::setEnabled(bool enable) {
    QWidget_setEnabled(enable);
}

void VQGroupBox::setFont(const QFont &font) {
    QWidget_setFont(font);
}

void VQGroupBox::setGeometry(int x, int y, int w, int h) {
    QWidget_setGeometry(x, y, w, h);
}

void VQGroupBox::setPalette(const QPalette &palette) {
    QWidget_setPalette(palette);
}

void VQGroupBox::setStyle(GUIStyle style) {
    QWidget_setStyle(style);
}

void VQGroupBox::show() {
    QWidget_show();
}

QSize VQGroupBox::sizeHint() const {
    return QWidget_sizeHint();
}

void VQGroupBox::styleChange(GUIStyle style) {
    QWidget_styleChange(style);
}


void VQGroupBox::drawContents(QPainter *p) {
    QFrame_drawContents(p);
}

void VQGroupBox::drawFrame(QPainter *p) {
    QFrame_drawFrame(p);
}

void VQGroupBox::frameChanged() {
    QFrame_frameChanged();
}


