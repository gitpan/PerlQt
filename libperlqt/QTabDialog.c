/*
 * VQTabDialog definitions.
 *
 * Copyright (C) 1997, Ashley Winters <jql@accessone.com>
 *
 * You may distribute under the terms of the LGPL as specified in the
 * README file
 */

#include <pqtabdlg.h>

const char *VQTabDialog::className() const {
    return QObject_className();
}

void VQTabDialog::connectNotify(const char *signal) {
    QObject_connectNotify(signal);
}

void VQTabDialog::disconnectNotify(const char *signal) {
    QObject_disconnectNotify(signal);
}

bool VQTabDialog::event(QEvent *event) {
    return QObject_event(event);
}

bool VQTabDialog::eventFilter(QObject *obj, QEvent *event) {
    return QObject_eventFilter(obj, event);
}

void VQTabDialog::initMetaObject() {
    if(!QTabDialog::metaObject()) QTabDialog::initMetaObject();
    QObject_initMetaObject();
}

QMetaObject *VQTabDialog::metaObject() const {
    return QObject_metaObject();
}

void VQTabDialog::timerEvent(QTimerEvent *event) {
    QObject_timerEvent(event);
}


void VQTabDialog::adjustSize() {
    QWidget_adjustSize();
}

void VQTabDialog::backgroundColorChange(const QColor &color) {
    QWidget_backgroundColorChange(color);
}

void VQTabDialog::backgroundPixmapChange(const QPixmap &pixmap) {
    QWidget_backgroundPixmapChange(pixmap);
}

bool VQTabDialog::close(bool forceKill) {
    return QWidget_close(forceKill);
}

void VQTabDialog::closeEvent(QCloseEvent *event) {
    QWidget_closeEvent(event);
}

void VQTabDialog::enabledChange(bool enable) {
    QWidget_enabledChange(enable);
}

void VQTabDialog::enterEvent(QEvent *event) {
    QWidget_enterEvent(event);
}

void VQTabDialog::focusInEvent(QFocusEvent *event) {
    QWidget_focusInEvent(event);
}

bool VQTabDialog::focusNextPrevChild(bool next) {
    return QWidget_focusNextPrevChild(next);
}

void VQTabDialog::focusOutEvent(QFocusEvent *event) {
    QWidget_focusOutEvent(event);
}

void VQTabDialog::fontChange(const QFont &font) {
    QWidget_fontChange(font);
}

void VQTabDialog::hide() {
    QWidget_hide();
}

void VQTabDialog::keyPressEvent(QKeyEvent *event) {
    QWidget_keyPressEvent(event);
}

void VQTabDialog::keyReleaseEvent(QKeyEvent *event) {
    QWidget_keyReleaseEvent(event);
}

void VQTabDialog::leaveEvent(QEvent *event) {
    QWidget_leaveEvent(event);
}

void VQTabDialog::mouseDoubleClickEvent(QMouseEvent *event) {
    QWidget_mouseDoubleClickEvent(event);
}

void VQTabDialog::mouseMoveEvent(QMouseEvent *event) {
    QWidget_mouseMoveEvent(event);
}

void VQTabDialog::mousePressEvent(QMouseEvent *event) {
    QWidget_mousePressEvent(event);
}

void VQTabDialog::mouseReleaseEvent(QMouseEvent *event) {
    QWidget_mouseReleaseEvent(event);
}

void VQTabDialog::move(int x, int y) {
    QWidget_move(x, y);
}

void VQTabDialog::moveEvent(QMoveEvent *event) {
    QWidget_moveEvent(event);
}

void VQTabDialog::paintEvent(QPaintEvent *event) {
    QWidget_paintEvent(event);
}

void VQTabDialog::paletteChange(const QPalette &palette) {
    QWidget_paletteChange(palette);
}

void VQTabDialog::resize(int w, int h) {
    QWidget_resize(w, h);
}

void VQTabDialog::resizeEvent(QResizeEvent *event) {
    QWidget_resizeEvent(event);
}

void VQTabDialog::setBackgroundColor(const QColor &color) {
    QWidget_setBackgroundColor(color);
}

void VQTabDialog::setBackgroundPixmap(const QPixmap &pixmap) {
    QWidget_setBackgroundPixmap(pixmap);
}

void VQTabDialog::setCursor(const QCursor &cursor) {
    QWidget_setCursor(cursor);
}

void VQTabDialog::setEnabled(bool enable) {
    QWidget_setEnabled(enable);
}

void VQTabDialog::setFont(const QFont &font) {
    QWidget_setFont(font);
}

void VQTabDialog::setGeometry(int x, int y, int w, int h) {
    QWidget_setGeometry(x, y, w, h);
}

void VQTabDialog::setPalette(const QPalette &palette) {
    QWidget_setPalette(palette);
}

void VQTabDialog::setStyle(GUIStyle style) {
    QWidget_setStyle(style);
}

void VQTabDialog::show() {
    QWidget_show();
}

QSize VQTabDialog::sizeHint() const {
    return QWidget_sizeHint();
}

void VQTabDialog::styleChange(GUIStyle style) {
    QWidget_styleChange(style);
}


void VQTabDialog::done(int r) {
    QDialog_done(r);
}


