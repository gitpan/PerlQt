/*
 * VQProgressDialog definitions.
 *
 * Copyright (C) 1997, Ashley Winters <jql@accessone.com>
 *
 * You may distribute under the terms of the LGPL as specified in the
 * README file
 */

#include <pqprogdlg.h>

const char *VQProgressDialog::className() const {
    return QObject_className();
}

void VQProgressDialog::connectNotify(const char *signal) {
    QObject_connectNotify(signal);
}

void VQProgressDialog::disconnectNotify(const char *signal) {
    QObject_disconnectNotify(signal);
}

bool VQProgressDialog::event(QEvent *event) {
    return QObject_event(event);
}

bool VQProgressDialog::eventFilter(QObject *obj, QEvent *event) {
    return QObject_eventFilter(obj, event);
}

void VQProgressDialog::initMetaObject() {
    if(!QProgressDialog::metaObject()) QProgressDialog::initMetaObject();
    QObject_initMetaObject();
}

QMetaObject *VQProgressDialog::metaObject() const {
    return QObject_metaObject();
}

void VQProgressDialog::timerEvent(QTimerEvent *event) {
    QObject_timerEvent(event);
}


void VQProgressDialog::adjustSize() {
    QWidget_adjustSize();
}

void VQProgressDialog::backgroundColorChange(const QColor &color) {
    QWidget_backgroundColorChange(color);
}

void VQProgressDialog::backgroundPixmapChange(const QPixmap &pixmap) {
    QWidget_backgroundPixmapChange(pixmap);
}

bool VQProgressDialog::close(bool forceKill) {
    return QWidget_close(forceKill);
}

void VQProgressDialog::closeEvent(QCloseEvent *event) {
    QWidget_closeEvent(event);
}

void VQProgressDialog::enabledChange(bool enable) {
    QWidget_enabledChange(enable);
}

void VQProgressDialog::enterEvent(QEvent *event) {
    QWidget_enterEvent(event);
}

void VQProgressDialog::focusInEvent(QFocusEvent *event) {
    QWidget_focusInEvent(event);
}

bool VQProgressDialog::focusNextPrevChild(bool next) {
    return QWidget_focusNextPrevChild(next);
}

void VQProgressDialog::focusOutEvent(QFocusEvent *event) {
    QWidget_focusOutEvent(event);
}

void VQProgressDialog::fontChange(const QFont &font) {
    QWidget_fontChange(font);
}

void VQProgressDialog::hide() {
    QWidget_hide();
}

void VQProgressDialog::keyPressEvent(QKeyEvent *event) {
    QWidget_keyPressEvent(event);
}

void VQProgressDialog::keyReleaseEvent(QKeyEvent *event) {
    QWidget_keyReleaseEvent(event);
}

void VQProgressDialog::leaveEvent(QEvent *event) {
    QWidget_leaveEvent(event);
}

void VQProgressDialog::mouseDoubleClickEvent(QMouseEvent *event) {
    QWidget_mouseDoubleClickEvent(event);
}

void VQProgressDialog::mouseMoveEvent(QMouseEvent *event) {
    QWidget_mouseMoveEvent(event);
}

void VQProgressDialog::mousePressEvent(QMouseEvent *event) {
    QWidget_mousePressEvent(event);
}

void VQProgressDialog::mouseReleaseEvent(QMouseEvent *event) {
    QWidget_mouseReleaseEvent(event);
}

void VQProgressDialog::move(int x, int y) {
    QWidget_move(x, y);
}

void VQProgressDialog::moveEvent(QMoveEvent *event) {
    QWidget_moveEvent(event);
}

void VQProgressDialog::paintEvent(QPaintEvent *event) {
    QWidget_paintEvent(event);
}

void VQProgressDialog::paletteChange(const QPalette &palette) {
    QWidget_paletteChange(palette);
}

void VQProgressDialog::resize(int w, int h) {
    QWidget_resize(w, h);
}

void VQProgressDialog::resizeEvent(QResizeEvent *event) {
    QWidget_resizeEvent(event);
}

void VQProgressDialog::setBackgroundColor(const QColor &color) {
    QWidget_setBackgroundColor(color);
}

void VQProgressDialog::setBackgroundPixmap(const QPixmap &pixmap) {
    QWidget_setBackgroundPixmap(pixmap);
}

void VQProgressDialog::setCursor(const QCursor &cursor) {
    QWidget_setCursor(cursor);
}

void VQProgressDialog::setEnabled(bool enable) {
    QWidget_setEnabled(enable);
}

void VQProgressDialog::setFont(const QFont &font) {
    QWidget_setFont(font);
}

void VQProgressDialog::setGeometry(int x, int y, int w, int h) {
    QWidget_setGeometry(x, y, w, h);
}

void VQProgressDialog::setPalette(const QPalette &palette) {
    QWidget_setPalette(palette);
}

void VQProgressDialog::setStyle(GUIStyle style) {
    QWidget_setStyle(style);
}

void VQProgressDialog::show() {
    QWidget_show();
}

QSize VQProgressDialog::sizeHint() const {
    return QWidget_sizeHint();
}

void VQProgressDialog::styleChange(GUIStyle style) {
    QWidget_styleChange(style);
}


