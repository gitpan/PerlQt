/*
 * VQRadioButton definitions.
 *
 * Copyright (C) 1997, Ashley Winters <jql@accessone.com>
 *
 * You may distribute under the terms of the LGPL as specified in the
 * README file
 */

#include <pqradiobt.h>

const char *VQRadioButton::className() const {
    return QObject_className();
}

void VQRadioButton::connectNotify(const char *signal) {
    QObject_connectNotify(signal);
}

void VQRadioButton::disconnectNotify(const char *signal) {
    QObject_disconnectNotify(signal);
}

bool VQRadioButton::event(QEvent *event) {
    return QObject_event(event);
}

bool VQRadioButton::eventFilter(QObject *obj, QEvent *event) {
    return QObject_eventFilter(obj, event);
}

void VQRadioButton::initMetaObject() {
    if(!QRadioButton::metaObject()) QRadioButton::initMetaObject();
    QObject_initMetaObject();
}

QMetaObject *VQRadioButton::metaObject() const {
    return QObject_metaObject();
}

void VQRadioButton::timerEvent(QTimerEvent *event) {
    QObject_timerEvent(event);
}


void VQRadioButton::adjustSize() {
    QWidget_adjustSize();
}

void VQRadioButton::backgroundColorChange(const QColor &color) {
    QWidget_backgroundColorChange(color);
}

void VQRadioButton::backgroundPixmapChange(const QPixmap &pixmap) {
    QWidget_backgroundPixmapChange(pixmap);
}

bool VQRadioButton::close(bool forceKill) {
    return QWidget_close(forceKill);
}

void VQRadioButton::closeEvent(QCloseEvent *event) {
    QWidget_closeEvent(event);
}

void VQRadioButton::enabledChange(bool enable) {
    QWidget_enabledChange(enable);
}

void VQRadioButton::enterEvent(QEvent *event) {
    QWidget_enterEvent(event);
}

void VQRadioButton::focusInEvent(QFocusEvent *event) {
    QWidget_focusInEvent(event);
}

bool VQRadioButton::focusNextPrevChild(bool next) {
    return QWidget_focusNextPrevChild(next);
}

void VQRadioButton::focusOutEvent(QFocusEvent *event) {
    QWidget_focusOutEvent(event);
}

void VQRadioButton::fontChange(const QFont &font) {
    QWidget_fontChange(font);
}

void VQRadioButton::hide() {
    QWidget_hide();
}

void VQRadioButton::keyPressEvent(QKeyEvent *event) {
    QWidget_keyPressEvent(event);
}

void VQRadioButton::keyReleaseEvent(QKeyEvent *event) {
    QWidget_keyReleaseEvent(event);
}

void VQRadioButton::leaveEvent(QEvent *event) {
    QWidget_leaveEvent(event);
}

void VQRadioButton::mouseDoubleClickEvent(QMouseEvent *event) {
    QWidget_mouseDoubleClickEvent(event);
}

void VQRadioButton::mouseMoveEvent(QMouseEvent *event) {
    QWidget_mouseMoveEvent(event);
}

void VQRadioButton::mousePressEvent(QMouseEvent *event) {
    QWidget_mousePressEvent(event);
}

void VQRadioButton::mouseReleaseEvent(QMouseEvent *event) {
    QWidget_mouseReleaseEvent(event);
}

void VQRadioButton::move(int x, int y) {
    QWidget_move(x, y);
}

void VQRadioButton::moveEvent(QMoveEvent *event) {
    QWidget_moveEvent(event);
}

void VQRadioButton::paintEvent(QPaintEvent *event) {
    QWidget_paintEvent(event);
}

void VQRadioButton::paletteChange(const QPalette &palette) {
    QWidget_paletteChange(palette);
}

void VQRadioButton::resize(int w, int h) {
    QWidget_resize(w, h);
}

void VQRadioButton::resizeEvent(QResizeEvent *event) {
    QWidget_resizeEvent(event);
}

void VQRadioButton::setBackgroundColor(const QColor &color) {
    QWidget_setBackgroundColor(color);
}

void VQRadioButton::setBackgroundPixmap(const QPixmap &pixmap) {
    QWidget_setBackgroundPixmap(pixmap);
}

void VQRadioButton::setCursor(const QCursor &cursor) {
    QWidget_setCursor(cursor);
}

void VQRadioButton::setEnabled(bool enable) {
    QWidget_setEnabled(enable);
}

void VQRadioButton::setFont(const QFont &font) {
    QWidget_setFont(font);
}

void VQRadioButton::setGeometry(int x, int y, int w, int h) {
    QWidget_setGeometry(x, y, w, h);
}

void VQRadioButton::setPalette(const QPalette &palette) {
    QWidget_setPalette(palette);
}

void VQRadioButton::setStyle(GUIStyle style) {
    QWidget_setStyle(style);
}

void VQRadioButton::show() {
    QWidget_show();
}

QSize VQRadioButton::sizeHint() const {
    return QWidget_sizeHint();
}

void VQRadioButton::styleChange(GUIStyle style) {
    QWidget_styleChange(style);
}


void VQRadioButton::drawButton(QPainter *p) {
    QButton_drawButton(p);
}

void VQRadioButton::drawButtonLabel(QPainter *p) {
    QButton_drawButtonLabel(p);
}

bool VQRadioButton::hitButton(const QPoint &pos) const {
    return QButton_hitButton(pos);
}


