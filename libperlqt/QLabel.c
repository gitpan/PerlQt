/*
 * VQLabel definitions.
 *
 * Copyright (C) 1997, Ashley Winters <jql@accessone.com>
 *
 * You may distribute under the terms of the LGPL as specified in the
 * README file
 */

#include <pqlabel.h>

const char *VQLabel::className() const {
    return QObject_className();
}

void VQLabel::connectNotify(const char *signal) {
    QObject_connectNotify(signal);
}

void VQLabel::disconnectNotify(const char *signal) {
    QObject_disconnectNotify(signal);
}

bool VQLabel::event(QEvent *event) {
    return QObject_event(event);
}

bool VQLabel::eventFilter(QObject *obj, QEvent *event) {
    return QObject_eventFilter(obj, event);
}

void VQLabel::initMetaObject() {
    if(!QLabel::metaObject()) QLabel::initMetaObject();
    QObject_initMetaObject();
}

QMetaObject *VQLabel::metaObject() const {
    return QObject_metaObject();
}

void VQLabel::timerEvent(QTimerEvent *event) {
    QObject_timerEvent(event);
}


void VQLabel::adjustSize() {
    QWidget_adjustSize();
}

void VQLabel::backgroundColorChange(const QColor &color) {
    QWidget_backgroundColorChange(color);
}

void VQLabel::backgroundPixmapChange(const QPixmap &pixmap) {
    QWidget_backgroundPixmapChange(pixmap);
}

bool VQLabel::close(bool forceKill) {
    return QWidget_close(forceKill);
}

void VQLabel::closeEvent(QCloseEvent *event) {
    QWidget_closeEvent(event);
}

void VQLabel::enabledChange(bool enable) {
    QWidget_enabledChange(enable);
}

void VQLabel::enterEvent(QEvent *event) {
    QWidget_enterEvent(event);
}

void VQLabel::focusInEvent(QFocusEvent *event) {
    QWidget_focusInEvent(event);
}

bool VQLabel::focusNextPrevChild(bool next) {
    return QWidget_focusNextPrevChild(next);
}

void VQLabel::focusOutEvent(QFocusEvent *event) {
    QWidget_focusOutEvent(event);
}

void VQLabel::fontChange(const QFont &font) {
    QWidget_fontChange(font);
}

void VQLabel::hide() {
    QWidget_hide();
}

void VQLabel::keyPressEvent(QKeyEvent *event) {
    QWidget_keyPressEvent(event);
}

void VQLabel::keyReleaseEvent(QKeyEvent *event) {
    QWidget_keyReleaseEvent(event);
}

void VQLabel::leaveEvent(QEvent *event) {
    QWidget_leaveEvent(event);
}

void VQLabel::mouseDoubleClickEvent(QMouseEvent *event) {
    QWidget_mouseDoubleClickEvent(event);
}

void VQLabel::mouseMoveEvent(QMouseEvent *event) {
    QWidget_mouseMoveEvent(event);
}

void VQLabel::mousePressEvent(QMouseEvent *event) {
    QWidget_mousePressEvent(event);
}

void VQLabel::mouseReleaseEvent(QMouseEvent *event) {
    QWidget_mouseReleaseEvent(event);
}

void VQLabel::move(int x, int y) {
    QWidget_move(x, y);
}

void VQLabel::moveEvent(QMoveEvent *event) {
    QWidget_moveEvent(event);
}

void VQLabel::paintEvent(QPaintEvent *event) {
    QWidget_paintEvent(event);
}

void VQLabel::paletteChange(const QPalette &palette) {
    QWidget_paletteChange(palette);
}

void VQLabel::resize(int w, int h) {
    QWidget_resize(w, h);
}

void VQLabel::resizeEvent(QResizeEvent *event) {
    QWidget_resizeEvent(event);
}

void VQLabel::setBackgroundColor(const QColor &color) {
    QWidget_setBackgroundColor(color);
}

void VQLabel::setBackgroundPixmap(const QPixmap &pixmap) {
    QWidget_setBackgroundPixmap(pixmap);
}

void VQLabel::setCursor(const QCursor &cursor) {
    QWidget_setCursor(cursor);
}

void VQLabel::setEnabled(bool enable) {
    QWidget_setEnabled(enable);
}

void VQLabel::setFont(const QFont &font) {
    QWidget_setFont(font);
}

void VQLabel::setGeometry(int x, int y, int w, int h) {
    QWidget_setGeometry(x, y, w, h);
}

void VQLabel::setPalette(const QPalette &palette) {
    QWidget_setPalette(palette);
}

void VQLabel::setStyle(GUIStyle style) {
    QWidget_setStyle(style);
}

void VQLabel::show() {
    QWidget_show();
}

QSize VQLabel::sizeHint() const {
    return QWidget_sizeHint();
}

void VQLabel::styleChange(GUIStyle style) {
    QWidget_styleChange(style);
}


void VQLabel::drawContents(QPainter *p) {
    QFrame_drawContents(p);
}

void VQLabel::drawFrame(QPainter *p) {
    QFrame_drawFrame(p);
}

void VQLabel::frameChanged() {
    QFrame_frameChanged();
}


