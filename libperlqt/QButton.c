/*
 * VQButton definitions.
 *
 * Copyright (C) 1997, Ashley Winters <jql@accessone.com>
 *
 * You may distribute under the terms of the LGPL as specified in the
 * README file
 */

#include <pqbutton.h>

const char *VQButton::className() const {
    return QObject_className();
}

void VQButton::connectNotify(const char *signal) {
    QObject_connectNotify(signal);
}

void VQButton::disconnectNotify(const char *signal) {
    QObject_disconnectNotify(signal);
}

bool VQButton::event(QEvent *event) {
    return QObject_event(event);
}

bool VQButton::eventFilter(QObject *obj, QEvent *event) {
    return QObject_eventFilter(obj, event);
}

void VQButton::initMetaObject() {
    if(!QButton::metaObject()) QButton::initMetaObject();
    QObject_initMetaObject();
}

QMetaObject *VQButton::metaObject() const {
    return QObject_metaObject();
}

void VQButton::timerEvent(QTimerEvent *event) {
    QObject_timerEvent(event);
}


void VQButton::adjustSize() {
    QWidget_adjustSize();
}

void VQButton::backgroundColorChange(const QColor &color) {
    QWidget_backgroundColorChange(color);
}

void VQButton::backgroundPixmapChange(const QPixmap &pixmap) {
    QWidget_backgroundPixmapChange(pixmap);
}

bool VQButton::close(bool forceKill) {
    return QWidget_close(forceKill);
}

void VQButton::closeEvent(QCloseEvent *event) {
    QWidget_closeEvent(event);
}

void VQButton::enabledChange(bool enable) {
    QWidget_enabledChange(enable);
}

void VQButton::enterEvent(QEvent *event) {
    QWidget_enterEvent(event);
}

void VQButton::focusInEvent(QFocusEvent *event) {
    QWidget_focusInEvent(event);
}

bool VQButton::focusNextPrevChild(bool next) {
    return QWidget_focusNextPrevChild(next);
}

void VQButton::focusOutEvent(QFocusEvent *event) {
    QWidget_focusOutEvent(event);
}

void VQButton::fontChange(const QFont &font) {
    QWidget_fontChange(font);
}

void VQButton::hide() {
    QWidget_hide();
}

void VQButton::keyPressEvent(QKeyEvent *event) {
    QWidget_keyPressEvent(event);
}

void VQButton::keyReleaseEvent(QKeyEvent *event) {
    QWidget_keyReleaseEvent(event);
}

void VQButton::leaveEvent(QEvent *event) {
    QWidget_leaveEvent(event);
}

void VQButton::mouseDoubleClickEvent(QMouseEvent *event) {
    QWidget_mouseDoubleClickEvent(event);
}

void VQButton::mouseMoveEvent(QMouseEvent *event) {
    QWidget_mouseMoveEvent(event);
}

void VQButton::mousePressEvent(QMouseEvent *event) {
    QWidget_mousePressEvent(event);
}

void VQButton::mouseReleaseEvent(QMouseEvent *event) {
    QWidget_mouseReleaseEvent(event);
}

void VQButton::move(int x, int y) {
    QWidget_move(x, y);
}

void VQButton::moveEvent(QMoveEvent *event) {
    QWidget_moveEvent(event);
}

void VQButton::paintEvent(QPaintEvent *event) {
    QWidget_paintEvent(event);
}

void VQButton::paletteChange(const QPalette &palette) {
    QWidget_paletteChange(palette);
}

void VQButton::resize(int w, int h) {
    QWidget_resize(w, h);
}

void VQButton::resizeEvent(QResizeEvent *event) {
    QWidget_resizeEvent(event);
}

void VQButton::setBackgroundColor(const QColor &color) {
    QWidget_setBackgroundColor(color);
}

void VQButton::setBackgroundPixmap(const QPixmap &pixmap) {
    QWidget_setBackgroundPixmap(pixmap);
}

void VQButton::setCursor(const QCursor &cursor) {
    QWidget_setCursor(cursor);
}

void VQButton::setEnabled(bool enable) {
    QWidget_setEnabled(enable);
}

void VQButton::setFont(const QFont &font) {
    QWidget_setFont(font);
}

void VQButton::setGeometry(int x, int y, int w, int h) {
    QWidget_setGeometry(x, y, w, h);
}

void VQButton::setPalette(const QPalette &palette) {
    QWidget_setPalette(palette);
}

void VQButton::setStyle(GUIStyle style) {
    QWidget_setStyle(style);
}

void VQButton::show() {
    QWidget_show();
}

QSize VQButton::sizeHint() const {
    return QWidget_sizeHint();
}

void VQButton::styleChange(GUIStyle style) {
    QWidget_styleChange(style);
}


void VQButton::drawButton(QPainter *p) {
    QButton_drawButton(p);
}

void VQButton::drawButtonLabel(QPainter *p) {
    QButton_drawButtonLabel(p);
}

bool VQButton::hitButton(const QPoint &pos) const {
    return QButton_hitButton(pos);
}


void QButton_virtualize::QButton_drawButton(QPainter *p) {
    voidCall("drawButton", pArgREF(p, QPainter));
}

void QButton_virtualize::QButton_drawButtonLabel(QPainter *p) {
    voidCall("drawButtonLabel", pArgREF(p, QPainter));
}

bool QButton_virtualize::QButton_hitButton(const QPoint &pos) const {
    return prBOOL(retCallConst("hitButton", pArgREF(&pos, const QPoint)));
}
