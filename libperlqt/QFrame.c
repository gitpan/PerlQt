/*
 * VQFrame definitions.
 *
 * Copyright (C) 1997, Ashley Winters <jql@accessone.com>
 *
 * You may distribute under the terms of the LGPL as specified in the
 * README file
 */

#include <pqframe.h>

const char *VQFrame::className() const {
    return QObject_className();
}

void VQFrame::connectNotify(const char *signal) {
    QObject_connectNotify(signal);
}

void VQFrame::disconnectNotify(const char *signal) {
    QObject_disconnectNotify(signal);
}

bool VQFrame::event(QEvent *event) {
    return QObject_event(event);
}

bool VQFrame::eventFilter(QObject *obj, QEvent *event) {
    return QObject_eventFilter(obj, event);
}

void VQFrame::initMetaObject() {
    if(!QFrame::metaObject()) QFrame::initMetaObject();
    QObject_initMetaObject();
}

QMetaObject *VQFrame::metaObject() const {
    return QObject_metaObject();
}

void VQFrame::timerEvent(QTimerEvent *event) {
    QObject_timerEvent(event);
}


void VQFrame::adjustSize() {
    QWidget_adjustSize();
}

void VQFrame::backgroundColorChange(const QColor &color) {
    QWidget_backgroundColorChange(color);
}

void VQFrame::backgroundPixmapChange(const QPixmap &pixmap) {
    QWidget_backgroundPixmapChange(pixmap);
}

bool VQFrame::close(bool forceKill) {
    return QWidget_close(forceKill);
}

void VQFrame::closeEvent(QCloseEvent *event) {
    QWidget_closeEvent(event);
}

void VQFrame::enabledChange(bool enable) {
    QWidget_enabledChange(enable);
}

void VQFrame::enterEvent(QEvent *event) {
    QWidget_enterEvent(event);
}

void VQFrame::focusInEvent(QFocusEvent *event) {
    QWidget_focusInEvent(event);
}

bool VQFrame::focusNextPrevChild(bool next) {
    return QWidget_focusNextPrevChild(next);
}

void VQFrame::focusOutEvent(QFocusEvent *event) {
    QWidget_focusOutEvent(event);
}

void VQFrame::fontChange(const QFont &font) {
    QWidget_fontChange(font);
}

void VQFrame::hide() {
    QWidget_hide();
}

void VQFrame::keyPressEvent(QKeyEvent *event) {
    QWidget_keyPressEvent(event);
}

void VQFrame::keyReleaseEvent(QKeyEvent *event) {
    QWidget_keyReleaseEvent(event);
}

void VQFrame::leaveEvent(QEvent *event) {
    QWidget_leaveEvent(event);
}

void VQFrame::mouseDoubleClickEvent(QMouseEvent *event) {
    QWidget_mouseDoubleClickEvent(event);
}

void VQFrame::mouseMoveEvent(QMouseEvent *event) {
    QWidget_mouseMoveEvent(event);
}

void VQFrame::mousePressEvent(QMouseEvent *event) {
    QWidget_mousePressEvent(event);
}

void VQFrame::mouseReleaseEvent(QMouseEvent *event) {
    QWidget_mouseReleaseEvent(event);
}

void VQFrame::move(int x, int y) {
    QWidget_move(x, y);
}

void VQFrame::moveEvent(QMoveEvent *event) {
    QWidget_moveEvent(event);
}

void VQFrame::paintEvent(QPaintEvent *event) {
    QWidget_paintEvent(event);
}

void VQFrame::paletteChange(const QPalette &palette) {
    QWidget_paletteChange(palette);
}

void VQFrame::resize(int w, int h) {
    QWidget_resize(w, h);
}

void VQFrame::resizeEvent(QResizeEvent *event) {
    QWidget_resizeEvent(event);
}

void VQFrame::setBackgroundColor(const QColor &color) {
    QWidget_setBackgroundColor(color);
}

void VQFrame::setBackgroundPixmap(const QPixmap &pixmap) {
    QWidget_setBackgroundPixmap(pixmap);
}

void VQFrame::setCursor(const QCursor &cursor) {
    QWidget_setCursor(cursor);
}

void VQFrame::setEnabled(bool enable) {
    QWidget_setEnabled(enable);
}

void VQFrame::setFont(const QFont &font) {
    QWidget_setFont(font);
}

void VQFrame::setGeometry(int x, int y, int w, int h) {
    QWidget_setGeometry(x, y, w, h);
}

void VQFrame::setPalette(const QPalette &palette) {
    QWidget_setPalette(palette);
}

void VQFrame::setStyle(GUIStyle style) {
    QWidget_setStyle(style);
}

void VQFrame::show() {
    QWidget_show();
}

QSize VQFrame::sizeHint() const {
    return QWidget_sizeHint();
}

void VQFrame::styleChange(GUIStyle style) {
    QWidget_styleChange(style);
}


void VQFrame::drawContents(QPainter *p) {
    QFrame_drawContents(p);
}

void VQFrame::drawFrame(QPainter *p) {
    QFrame_drawFrame(p);
}

void VQFrame::frameChanged() {
    QFrame_frameChanged();
}


void QFrame_virtualize::QFrame_drawContents(QPainter *p) {
    voidCall("drawContents", pArgREF(p, QPainter));
}

void QFrame_virtualize::QFrame_drawFrame(QPainter *p) {
    voidCall("drawFrame", pArgREF(p, QPainter));
}

void QFrame_virtualize::QFrame_frameChanged() {
    voidCall("frameChanged");
}
