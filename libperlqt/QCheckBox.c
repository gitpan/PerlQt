/*
 * VQCheckBox definitions.
 *
 * Copyright (C) 1997, Ashley Winters <jql@accessone.com>
 *
 * You may distribute under the terms of the LGPL as specified in the
 * README file
 */

#include <pqchkbox.h>

const char *VQCheckBox::className() const {
    return QObject_className();
}

void VQCheckBox::connectNotify(const char *signal) {
    QObject_connectNotify(signal);
}

void VQCheckBox::disconnectNotify(const char *signal) {
    QObject_disconnectNotify(signal);
}

bool VQCheckBox::event(QEvent *event) {
    return QObject_event(event);
}

bool VQCheckBox::eventFilter(QObject *obj, QEvent *event) {
    return QObject_eventFilter(obj, event);
}

void VQCheckBox::initMetaObject() {
    if(!QCheckBox::metaObject()) QCheckBox::initMetaObject();
    QObject_initMetaObject();
}

QMetaObject *VQCheckBox::metaObject() const {
    return QObject_metaObject();
}

void VQCheckBox::timerEvent(QTimerEvent *event) {
    QObject_timerEvent(event);
}


void VQCheckBox::adjustSize() {
    QWidget_adjustSize();
}

void VQCheckBox::backgroundColorChange(const QColor &color) {
    QWidget_backgroundColorChange(color);
}

void VQCheckBox::backgroundPixmapChange(const QPixmap &pixmap) {
    QWidget_backgroundPixmapChange(pixmap);
}

bool VQCheckBox::close(bool forceKill) {
    return QWidget_close(forceKill);
}

void VQCheckBox::closeEvent(QCloseEvent *event) {
    QWidget_closeEvent(event);
}

void VQCheckBox::enabledChange(bool enable) {
    QWidget_enabledChange(enable);
}

void VQCheckBox::enterEvent(QEvent *event) {
    QWidget_enterEvent(event);
}

void VQCheckBox::focusInEvent(QFocusEvent *event) {
    QWidget_focusInEvent(event);
}

bool VQCheckBox::focusNextPrevChild(bool next) {
    return QWidget_focusNextPrevChild(next);
}

void VQCheckBox::focusOutEvent(QFocusEvent *event) {
    QWidget_focusOutEvent(event);
}

void VQCheckBox::fontChange(const QFont &font) {
    QWidget_fontChange(font);
}

void VQCheckBox::hide() {
    QWidget_hide();
}

void VQCheckBox::keyPressEvent(QKeyEvent *event) {
    QWidget_keyPressEvent(event);
}

void VQCheckBox::keyReleaseEvent(QKeyEvent *event) {
    QWidget_keyReleaseEvent(event);
}

void VQCheckBox::leaveEvent(QEvent *event) {
    QWidget_leaveEvent(event);
}

void VQCheckBox::mouseDoubleClickEvent(QMouseEvent *event) {
    QWidget_mouseDoubleClickEvent(event);
}

void VQCheckBox::mouseMoveEvent(QMouseEvent *event) {
    QWidget_mouseMoveEvent(event);
}

void VQCheckBox::mousePressEvent(QMouseEvent *event) {
    QWidget_mousePressEvent(event);
}

void VQCheckBox::mouseReleaseEvent(QMouseEvent *event) {
    QWidget_mouseReleaseEvent(event);
}

void VQCheckBox::move(int x, int y) {
    QWidget_move(x, y);
}

void VQCheckBox::moveEvent(QMoveEvent *event) {
    QWidget_moveEvent(event);
}

void VQCheckBox::paintEvent(QPaintEvent *event) {
    QWidget_paintEvent(event);
}

void VQCheckBox::paletteChange(const QPalette &palette) {
    QWidget_paletteChange(palette);
}

void VQCheckBox::resize(int w, int h) {
    QWidget_resize(w, h);
}

void VQCheckBox::resizeEvent(QResizeEvent *event) {
    QWidget_resizeEvent(event);
}

void VQCheckBox::setBackgroundColor(const QColor &color) {
    QWidget_setBackgroundColor(color);
}

void VQCheckBox::setBackgroundPixmap(const QPixmap &pixmap) {
    QWidget_setBackgroundPixmap(pixmap);
}

void VQCheckBox::setCursor(const QCursor &cursor) {
    QWidget_setCursor(cursor);
}

void VQCheckBox::setEnabled(bool enable) {
    QWidget_setEnabled(enable);
}

void VQCheckBox::setFont(const QFont &font) {
    QWidget_setFont(font);
}

void VQCheckBox::setGeometry(int x, int y, int w, int h) {
    QWidget_setGeometry(x, y, w, h);
}

void VQCheckBox::setPalette(const QPalette &palette) {
    QWidget_setPalette(palette);
}

void VQCheckBox::setStyle(GUIStyle style) {
    QWidget_setStyle(style);
}

void VQCheckBox::show() {
    QWidget_show();
}

QSize VQCheckBox::sizeHint() const {
    return QWidget_sizeHint();
}

void VQCheckBox::styleChange(GUIStyle style) {
    QWidget_styleChange(style);
}


void VQCheckBox::drawButton(QPainter *p) {
    QButton_drawButton(p);
}

void VQCheckBox::drawButtonLabel(QPainter *p) {
    QButton_drawButtonLabel(p);
}

bool VQCheckBox::hitButton(const QPoint &pos) const {
    return QButton_hitButton(pos);
}


