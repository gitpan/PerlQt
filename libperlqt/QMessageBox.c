/*
 * VQMessageBox definitions.
 *
 * Copyright (C) 1997, Ashley Winters <jql@accessone.com>
 *
 * You may distribute under the terms of the LGPL as specified in the
 * README file
 */

#include <pqmsgbox.h>

const char *VQMessageBox::className() const {
    return QObject_className();
}

void VQMessageBox::connectNotify(const char *signal) {
    QObject_connectNotify(signal);
}

void VQMessageBox::disconnectNotify(const char *signal) {
    QObject_disconnectNotify(signal);
}

bool VQMessageBox::event(QEvent *event) {
    return QObject_event(event);
}

bool VQMessageBox::eventFilter(QObject *obj, QEvent *event) {
    return QObject_eventFilter(obj, event);
}

void VQMessageBox::initMetaObject() {
    if(!QMessageBox::metaObject()) QMessageBox::initMetaObject();
    QObject_initMetaObject();
}

QMetaObject *VQMessageBox::metaObject() const {
    return QObject_metaObject();
}

void VQMessageBox::timerEvent(QTimerEvent *event) {
    QObject_timerEvent(event);
}


void VQMessageBox::adjustSize() {
    QWidget_adjustSize();
}

void VQMessageBox::backgroundColorChange(const QColor &color) {
    QWidget_backgroundColorChange(color);
}

void VQMessageBox::backgroundPixmapChange(const QPixmap &pixmap) {
    QWidget_backgroundPixmapChange(pixmap);
}

bool VQMessageBox::close(bool forceKill) {
    return QWidget_close(forceKill);
}

void VQMessageBox::closeEvent(QCloseEvent *event) {
    QWidget_closeEvent(event);
}

void VQMessageBox::enabledChange(bool enable) {
    QWidget_enabledChange(enable);
}

void VQMessageBox::enterEvent(QEvent *event) {
    QWidget_enterEvent(event);
}

void VQMessageBox::focusInEvent(QFocusEvent *event) {
    QWidget_focusInEvent(event);
}

bool VQMessageBox::focusNextPrevChild(bool next) {
    return QWidget_focusNextPrevChild(next);
}

void VQMessageBox::focusOutEvent(QFocusEvent *event) {
    QWidget_focusOutEvent(event);
}

void VQMessageBox::fontChange(const QFont &font) {
    QWidget_fontChange(font);
}

void VQMessageBox::hide() {
    QWidget_hide();
}

void VQMessageBox::keyPressEvent(QKeyEvent *event) {
    QWidget_keyPressEvent(event);
}

void VQMessageBox::keyReleaseEvent(QKeyEvent *event) {
    QWidget_keyReleaseEvent(event);
}

void VQMessageBox::leaveEvent(QEvent *event) {
    QWidget_leaveEvent(event);
}

void VQMessageBox::mouseDoubleClickEvent(QMouseEvent *event) {
    QWidget_mouseDoubleClickEvent(event);
}

void VQMessageBox::mouseMoveEvent(QMouseEvent *event) {
    QWidget_mouseMoveEvent(event);
}

void VQMessageBox::mousePressEvent(QMouseEvent *event) {
    QWidget_mousePressEvent(event);
}

void VQMessageBox::mouseReleaseEvent(QMouseEvent *event) {
    QWidget_mouseReleaseEvent(event);
}

void VQMessageBox::move(int x, int y) {
    QWidget_move(x, y);
}

void VQMessageBox::moveEvent(QMoveEvent *event) {
    QWidget_moveEvent(event);
}

void VQMessageBox::paintEvent(QPaintEvent *event) {
    QWidget_paintEvent(event);
}

void VQMessageBox::paletteChange(const QPalette &palette) {
    QWidget_paletteChange(palette);
}

void VQMessageBox::resize(int w, int h) {
    QWidget_resize(w, h);
}

void VQMessageBox::resizeEvent(QResizeEvent *event) {
    QWidget_resizeEvent(event);
}

void VQMessageBox::setBackgroundColor(const QColor &color) {
    QWidget_setBackgroundColor(color);
}

void VQMessageBox::setBackgroundPixmap(const QPixmap &pixmap) {
    QWidget_setBackgroundPixmap(pixmap);
}

void VQMessageBox::setCursor(const QCursor &cursor) {
    QWidget_setCursor(cursor);
}

void VQMessageBox::setEnabled(bool enable) {
    QWidget_setEnabled(enable);
}

void VQMessageBox::setFont(const QFont &font) {
    QWidget_setFont(font);
}

void VQMessageBox::setGeometry(int x, int y, int w, int h) {
    QWidget_setGeometry(x, y, w, h);
}

void VQMessageBox::setPalette(const QPalette &palette) {
    QWidget_setPalette(palette);
}

void VQMessageBox::setStyle(GUIStyle style) {
    QWidget_setStyle(style);
}

void VQMessageBox::show() {
    QWidget_show();
}

QSize VQMessageBox::sizeHint() const {
    return QWidget_sizeHint();
}

void VQMessageBox::styleChange(GUIStyle style) {
    QWidget_styleChange(style);
}


void VQMessageBox::done(int r) {
    QDialog_done(r);
}


