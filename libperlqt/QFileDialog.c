/*
 * VQFileDialog definitions.
 *
 * Copyright (C) 1997, Ashley Winters <jql@accessone.com>
 *
 * You may distribute under the terms of the LGPL as specified in the
 * README file
 */

#include <pqfiledlg.h>

const char *VQFileDialog::className() const {
    return QObject_className();
}

void VQFileDialog::connectNotify(const char *signal) {
    QObject_connectNotify(signal);
}

void VQFileDialog::disconnectNotify(const char *signal) {
    QObject_disconnectNotify(signal);
}

bool VQFileDialog::event(QEvent *event) {
    return QObject_event(event);
}

bool VQFileDialog::eventFilter(QObject *obj, QEvent *event) {
    return QObject_eventFilter(obj, event);
}

void VQFileDialog::initMetaObject() {
    if(!QFileDialog::metaObject()) QFileDialog::initMetaObject();
    QObject_initMetaObject();
}

QMetaObject *VQFileDialog::metaObject() const {
    return QObject_metaObject();
}

void VQFileDialog::timerEvent(QTimerEvent *event) {
    QObject_timerEvent(event);
}


void VQFileDialog::adjustSize() {
    QWidget_adjustSize();
}

void VQFileDialog::backgroundColorChange(const QColor &color) {
    QWidget_backgroundColorChange(color);
}

void VQFileDialog::backgroundPixmapChange(const QPixmap &pixmap) {
    QWidget_backgroundPixmapChange(pixmap);
}

bool VQFileDialog::close(bool forceKill) {
    return QWidget_close(forceKill);
}

void VQFileDialog::closeEvent(QCloseEvent *event) {
    QWidget_closeEvent(event);
}

void VQFileDialog::enabledChange(bool enable) {
    QWidget_enabledChange(enable);
}

void VQFileDialog::enterEvent(QEvent *event) {
    QWidget_enterEvent(event);
}

void VQFileDialog::focusInEvent(QFocusEvent *event) {
    QWidget_focusInEvent(event);
}

bool VQFileDialog::focusNextPrevChild(bool next) {
    return QWidget_focusNextPrevChild(next);
}

void VQFileDialog::focusOutEvent(QFocusEvent *event) {
    QWidget_focusOutEvent(event);
}

void VQFileDialog::fontChange(const QFont &font) {
    QWidget_fontChange(font);
}

void VQFileDialog::hide() {
    QWidget_hide();
}

void VQFileDialog::keyPressEvent(QKeyEvent *event) {
    QWidget_keyPressEvent(event);
}

void VQFileDialog::keyReleaseEvent(QKeyEvent *event) {
    QWidget_keyReleaseEvent(event);
}

void VQFileDialog::leaveEvent(QEvent *event) {
    QWidget_leaveEvent(event);
}

void VQFileDialog::mouseDoubleClickEvent(QMouseEvent *event) {
    QWidget_mouseDoubleClickEvent(event);
}

void VQFileDialog::mouseMoveEvent(QMouseEvent *event) {
    QWidget_mouseMoveEvent(event);
}

void VQFileDialog::mousePressEvent(QMouseEvent *event) {
    QWidget_mousePressEvent(event);
}

void VQFileDialog::mouseReleaseEvent(QMouseEvent *event) {
    QWidget_mouseReleaseEvent(event);
}

void VQFileDialog::move(int x, int y) {
    QWidget_move(x, y);
}

void VQFileDialog::moveEvent(QMoveEvent *event) {
    QWidget_moveEvent(event);
}

void VQFileDialog::paintEvent(QPaintEvent *event) {
    QWidget_paintEvent(event);
}

void VQFileDialog::paletteChange(const QPalette &palette) {
    QWidget_paletteChange(palette);
}

void VQFileDialog::resize(int w, int h) {
    QWidget_resize(w, h);
}

void VQFileDialog::resizeEvent(QResizeEvent *event) {
    QWidget_resizeEvent(event);
}

void VQFileDialog::setBackgroundColor(const QColor &color) {
    QWidget_setBackgroundColor(color);
}

void VQFileDialog::setBackgroundPixmap(const QPixmap &pixmap) {
    QWidget_setBackgroundPixmap(pixmap);
}

void VQFileDialog::setCursor(const QCursor &cursor) {
    QWidget_setCursor(cursor);
}

void VQFileDialog::setEnabled(bool enable) {
    QWidget_setEnabled(enable);
}

void VQFileDialog::setFont(const QFont &font) {
    QWidget_setFont(font);
}

void VQFileDialog::setGeometry(int x, int y, int w, int h) {
    QWidget_setGeometry(x, y, w, h);
}

void VQFileDialog::setPalette(const QPalette &palette) {
    QWidget_setPalette(palette);
}

void VQFileDialog::setStyle(GUIStyle style) {
    QWidget_setStyle(style);
}

void VQFileDialog::show() {
    QWidget_show();
}

QSize VQFileDialog::sizeHint() const {
    return QWidget_sizeHint();
}

void VQFileDialog::styleChange(GUIStyle style) {
    QWidget_styleChange(style);
}


void VQFileDialog::done(int r) {
    QDialog_done(r);
}


