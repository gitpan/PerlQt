/*
 * VQDialog definitions.
 *
 * Copyright (C) 1997, Ashley Winters <jql@accessone.com>
 *
 * You may distribute under the terms of the LGPL as specified in the
 * README file
 */

#include <pqdialog.h>

const char *VQDialog::className() const {
    return QObject_className();
}

void VQDialog::connectNotify(const char *signal) {
    QObject_connectNotify(signal);
}

void VQDialog::disconnectNotify(const char *signal) {
    QObject_disconnectNotify(signal);
}

bool VQDialog::event(QEvent *event) {
    return QObject_event(event);
}

bool VQDialog::eventFilter(QObject *obj, QEvent *event) {
    return QObject_eventFilter(obj, event);
}

void VQDialog::initMetaObject() {
    if(!QDialog::metaObject()) QDialog::initMetaObject();
    QObject_initMetaObject();
}

QMetaObject *VQDialog::metaObject() const {
    return QObject_metaObject();
}

void VQDialog::timerEvent(QTimerEvent *event) {
    QObject_timerEvent(event);
}


void VQDialog::adjustSize() {
    QWidget_adjustSize();
}

void VQDialog::backgroundColorChange(const QColor &color) {
    QWidget_backgroundColorChange(color);
}

void VQDialog::backgroundPixmapChange(const QPixmap &pixmap) {
    QWidget_backgroundPixmapChange(pixmap);
}

bool VQDialog::close(bool forceKill) {
    return QWidget_close(forceKill);
}

void VQDialog::closeEvent(QCloseEvent *event) {
    QWidget_closeEvent(event);
}

void VQDialog::enabledChange(bool enable) {
    QWidget_enabledChange(enable);
}

void VQDialog::enterEvent(QEvent *event) {
    QWidget_enterEvent(event);
}

void VQDialog::focusInEvent(QFocusEvent *event) {
    QWidget_focusInEvent(event);
}

bool VQDialog::focusNextPrevChild(bool next) {
    return QWidget_focusNextPrevChild(next);
}

void VQDialog::focusOutEvent(QFocusEvent *event) {
    QWidget_focusOutEvent(event);
}

void VQDialog::fontChange(const QFont &font) {
    QWidget_fontChange(font);
}

void VQDialog::hide() {
    QWidget_hide();
}

void VQDialog::keyPressEvent(QKeyEvent *event) {
    QWidget_keyPressEvent(event);
}

void VQDialog::keyReleaseEvent(QKeyEvent *event) {
    QWidget_keyReleaseEvent(event);
}

void VQDialog::leaveEvent(QEvent *event) {
    QWidget_leaveEvent(event);
}

void VQDialog::mouseDoubleClickEvent(QMouseEvent *event) {
    QWidget_mouseDoubleClickEvent(event);
}

void VQDialog::mouseMoveEvent(QMouseEvent *event) {
    QWidget_mouseMoveEvent(event);
}

void VQDialog::mousePressEvent(QMouseEvent *event) {
    QWidget_mousePressEvent(event);
}

void VQDialog::mouseReleaseEvent(QMouseEvent *event) {
    QWidget_mouseReleaseEvent(event);
}

void VQDialog::move(int x, int y) {
    QWidget_move(x, y);
}

void VQDialog::moveEvent(QMoveEvent *event) {
    QWidget_moveEvent(event);
}

void VQDialog::paintEvent(QPaintEvent *event) {
    QWidget_paintEvent(event);
}

void VQDialog::paletteChange(const QPalette &palette) {
    QWidget_paletteChange(palette);
}

void VQDialog::resize(int w, int h) {
    QWidget_resize(w, h);
}

void VQDialog::resizeEvent(QResizeEvent *event) {
    QWidget_resizeEvent(event);
}

void VQDialog::setBackgroundColor(const QColor &color) {
    QWidget_setBackgroundColor(color);
}

void VQDialog::setBackgroundPixmap(const QPixmap &pixmap) {
    QWidget_setBackgroundPixmap(pixmap);
}

void VQDialog::setCursor(const QCursor &cursor) {
    QWidget_setCursor(cursor);
}

void VQDialog::setEnabled(bool enable) {
    QWidget_setEnabled(enable);
}

void VQDialog::setFont(const QFont &font) {
    QWidget_setFont(font);
}

void VQDialog::setGeometry(int x, int y, int w, int h) {
    QWidget_setGeometry(x, y, w, h);
}

void VQDialog::setPalette(const QPalette &palette) {
    QWidget_setPalette(palette);
}

void VQDialog::setStyle(GUIStyle style) {
    QWidget_setStyle(style);
}

void VQDialog::show() {
    QWidget_show();
}

QSize VQDialog::sizeHint() const {
    return QWidget_sizeHint();
}

void VQDialog::styleChange(GUIStyle style) {
    QWidget_styleChange(style);
}


void VQDialog::done(int r) {
    QDialog_done(r);
}


void QDialog_virtualize::QDialog_done(int r) {
    voidCall("done", pArgIV(r));
}
