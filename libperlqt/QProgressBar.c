/*
 * VQProgressBar definitions.
 *
 * Copyright (C) 1997, Ashley Winters <jql@accessone.com>
 *
 * You may distribute under the terms of the LGPL as specified in the
 * README file
 */

#include <pqprogbar.h>

const char *VQProgressBar::className() const {
    return QObject_className();
}

void VQProgressBar::connectNotify(const char *signal) {
    QObject_connectNotify(signal);
}

void VQProgressBar::disconnectNotify(const char *signal) {
    QObject_disconnectNotify(signal);
}

bool VQProgressBar::event(QEvent *event) {
    return QObject_event(event);
}

bool VQProgressBar::eventFilter(QObject *obj, QEvent *event) {
    return QObject_eventFilter(obj, event);
}

void VQProgressBar::initMetaObject() {
    if(!QProgressBar::metaObject()) QProgressBar::initMetaObject();
    QObject_initMetaObject();
}

QMetaObject *VQProgressBar::metaObject() const {
    return QObject_metaObject();
}

void VQProgressBar::timerEvent(QTimerEvent *event) {
    QObject_timerEvent(event);
}


void VQProgressBar::adjustSize() {
    QWidget_adjustSize();
}

void VQProgressBar::backgroundColorChange(const QColor &color) {
    QWidget_backgroundColorChange(color);
}

void VQProgressBar::backgroundPixmapChange(const QPixmap &pixmap) {
    QWidget_backgroundPixmapChange(pixmap);
}

bool VQProgressBar::close(bool forceKill) {
    return QWidget_close(forceKill);
}

void VQProgressBar::closeEvent(QCloseEvent *event) {
    QWidget_closeEvent(event);
}

void VQProgressBar::enabledChange(bool enable) {
    QWidget_enabledChange(enable);
}

void VQProgressBar::enterEvent(QEvent *event) {
    QWidget_enterEvent(event);
}

void VQProgressBar::focusInEvent(QFocusEvent *event) {
    QWidget_focusInEvent(event);
}

bool VQProgressBar::focusNextPrevChild(bool next) {
    return QWidget_focusNextPrevChild(next);
}

void VQProgressBar::focusOutEvent(QFocusEvent *event) {
    QWidget_focusOutEvent(event);
}

void VQProgressBar::fontChange(const QFont &font) {
    QWidget_fontChange(font);
}

void VQProgressBar::hide() {
    QWidget_hide();
}

void VQProgressBar::keyPressEvent(QKeyEvent *event) {
    QWidget_keyPressEvent(event);
}

void VQProgressBar::keyReleaseEvent(QKeyEvent *event) {
    QWidget_keyReleaseEvent(event);
}

void VQProgressBar::leaveEvent(QEvent *event) {
    QWidget_leaveEvent(event);
}

void VQProgressBar::mouseDoubleClickEvent(QMouseEvent *event) {
    QWidget_mouseDoubleClickEvent(event);
}

void VQProgressBar::mouseMoveEvent(QMouseEvent *event) {
    QWidget_mouseMoveEvent(event);
}

void VQProgressBar::mousePressEvent(QMouseEvent *event) {
    QWidget_mousePressEvent(event);
}

void VQProgressBar::mouseReleaseEvent(QMouseEvent *event) {
    QWidget_mouseReleaseEvent(event);
}

void VQProgressBar::move(int x, int y) {
    QWidget_move(x, y);
}

void VQProgressBar::moveEvent(QMoveEvent *event) {
    QWidget_moveEvent(event);
}

void VQProgressBar::paintEvent(QPaintEvent *event) {
    QWidget_paintEvent(event);
}

void VQProgressBar::paletteChange(const QPalette &palette) {
    QWidget_paletteChange(palette);
}

void VQProgressBar::resize(int w, int h) {
    QWidget_resize(w, h);
}

void VQProgressBar::resizeEvent(QResizeEvent *event) {
    QWidget_resizeEvent(event);
}

void VQProgressBar::setBackgroundColor(const QColor &color) {
    QWidget_setBackgroundColor(color);
}

void VQProgressBar::setBackgroundPixmap(const QPixmap &pixmap) {
    QWidget_setBackgroundPixmap(pixmap);
}

void VQProgressBar::setCursor(const QCursor &cursor) {
    QWidget_setCursor(cursor);
}

void VQProgressBar::setEnabled(bool enable) {
    QWidget_setEnabled(enable);
}

void VQProgressBar::setFont(const QFont &font) {
    QWidget_setFont(font);
}

void VQProgressBar::setGeometry(int x, int y, int w, int h) {
    QWidget_setGeometry(x, y, w, h);
}

void VQProgressBar::setPalette(const QPalette &palette) {
    QWidget_setPalette(palette);
}

void VQProgressBar::setStyle(GUIStyle style) {
    QWidget_setStyle(style);
}

void VQProgressBar::show() {
    QWidget_show();
}

QSize VQProgressBar::sizeHint() const {
    return QWidget_sizeHint();
}

void VQProgressBar::styleChange(GUIStyle style) {
    QWidget_styleChange(style);
}


void VQProgressBar::drawContents(QPainter *p) {
    QFrame_drawContents(p);
}

void VQProgressBar::drawFrame(QPainter *p) {
    QFrame_drawFrame(p);
}

void VQProgressBar::frameChanged() {
    QFrame_frameChanged();
}


