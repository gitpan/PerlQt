/*
 * VQWidget definitions.
 *
 * Copyright (C) 1997, Ashley Winters <jql@accessone.com>
 *
 * You may distribute under the terms of the LGPL as specified in the
 * README file
 */

#include <pqwidget.h>

const char *VQWidget::className() const {
    return QObject_className();
}

void VQWidget::connectNotify(const char *signal) {
    QObject_connectNotify(signal);
}

void VQWidget::disconnectNotify(const char *signal) {
    QObject_disconnectNotify(signal);
}

bool VQWidget::event(QEvent *event) {
    return QObject_event(event);
}

bool VQWidget::eventFilter(QObject *obj, QEvent *event) {
    return QObject_eventFilter(obj, event);
}

void VQWidget::initMetaObject() {
    if(!QWidget::metaObject()) QWidget::initMetaObject();
    QObject_initMetaObject();
}

QMetaObject *VQWidget::metaObject() const {
    return QObject_metaObject();
}

void VQWidget::timerEvent(QTimerEvent *event) {
    QObject_timerEvent(event);
}


void VQWidget::adjustSize() {
    QWidget_adjustSize();
}

void VQWidget::backgroundColorChange(const QColor &color) {
    QWidget_backgroundColorChange(color);
}

void VQWidget::backgroundPixmapChange(const QPixmap &pixmap) {
    QWidget_backgroundPixmapChange(pixmap);
}

bool VQWidget::close(bool forceKill) {
    return QWidget_close(forceKill);
}

void VQWidget::closeEvent(QCloseEvent *event) {
    QWidget_closeEvent(event);
}

void VQWidget::enabledChange(bool enable) {
    QWidget_enabledChange(enable);
}

void VQWidget::enterEvent(QEvent *event) {
    QWidget_enterEvent(event);
}

void VQWidget::focusInEvent(QFocusEvent *event) {
    QWidget_focusInEvent(event);
}

bool VQWidget::focusNextPrevChild(bool next) {
    return QWidget_focusNextPrevChild(next);
}

void VQWidget::focusOutEvent(QFocusEvent *event) {
    QWidget_focusOutEvent(event);
}

void VQWidget::fontChange(const QFont &font) {
    QWidget_fontChange(font);
}

void VQWidget::hide() {
    QWidget_hide();
}

void VQWidget::keyPressEvent(QKeyEvent *event) {
    QWidget_keyPressEvent(event);
}

void VQWidget::keyReleaseEvent(QKeyEvent *event) {
    QWidget_keyReleaseEvent(event);
}

void VQWidget::leaveEvent(QEvent *event) {
    QWidget_leaveEvent(event);
}

void VQWidget::mouseDoubleClickEvent(QMouseEvent *event) {
    QWidget_mouseDoubleClickEvent(event);
}

void VQWidget::mouseMoveEvent(QMouseEvent *event) {
    QWidget_mouseMoveEvent(event);
}

void VQWidget::mousePressEvent(QMouseEvent *event) {
    QWidget_mousePressEvent(event);
}

void VQWidget::mouseReleaseEvent(QMouseEvent *event) {
    QWidget_mouseReleaseEvent(event);
}

void VQWidget::move(int x, int y) {
    QWidget_move(x, y);
}

void VQWidget::moveEvent(QMoveEvent *event) {
    QWidget_moveEvent(event);
}

void VQWidget::paintEvent(QPaintEvent *event) {
    QWidget_paintEvent(event);
}

void VQWidget::paletteChange(const QPalette &palette) {
    QWidget_paletteChange(palette);
}

void VQWidget::resize(int w, int h) {
    QWidget_resize(w, h);
}

void VQWidget::resizeEvent(QResizeEvent *event) {
    QWidget_resizeEvent(event);
}

void VQWidget::setBackgroundColor(const QColor &color) {
    QWidget_setBackgroundColor(color);
}

void VQWidget::setBackgroundPixmap(const QPixmap &pixmap) {
    QWidget_setBackgroundPixmap(pixmap);
}

void VQWidget::setCursor(const QCursor &cursor) {
    QWidget_setCursor(cursor);
}

void VQWidget::setEnabled(bool enable) {
    QWidget_setEnabled(enable);
}

void VQWidget::setFont(const QFont &font) {
    QWidget_setFont(font);
}

void VQWidget::setGeometry(int x, int y, int w, int h) {
    QWidget_setGeometry(x, y, w, h);
}

void VQWidget::setPalette(const QPalette &palette) {
    QWidget_setPalette(palette);
}

void VQWidget::setStyle(GUIStyle style) {
    QWidget_setStyle(style);
}

void VQWidget::show() {
    QWidget_show();
}

QSize VQWidget::sizeHint() const {
    return QWidget_sizeHint();
}

void VQWidget::styleChange(GUIStyle style) {
    QWidget_styleChange(style);
}


void QWidget_virtualize::QWidget_adjustSize() {
    voidCall("adjustSize");
}

void QWidget_virtualize::QWidget_backgroundColorChange(const QColor &color) {
    voidCall("backgroundColorChange", pArgREF(&color, const QColor));
}

void QWidget_virtualize::QWidget_backgroundPixmapChange(const QPixmap &pm) {
    voidCall("backgroundPixmapChange", pArgREF(&pm, const QPixmap));
}

bool QWidget_virtualize::QWidget_close(bool forceKill) {
    return prBOOL(retCall("close", pArgBOOL(forceKill)));
}

void QWidget_virtualize::QWidget_closeEvent(QCloseEvent *event) {
    voidCall("closeEvent", pArgREF(event, QCloseEvent));
}

void QWidget_virtualize::QWidget_enabledChange(bool enabled) {
    voidCall("enabledChange", pArgBOOL(enabled));
}

void QWidget_virtualize::QWidget_enterEvent(QEvent *event) {
    voidCall("enterEvent", pArgREF(event, QEvent));
}

void QWidget_virtualize::QWidget_focusInEvent(QFocusEvent *event) {
    voidCall("focusInEvent", pArgREF(event, QFocusEvent));
}

bool QWidget_virtualize::QWidget_focusNextPrevChild(bool next) {
    return prBOOL(retCall("focusNextPrevChild", pArgBOOL(next)));
}

void QWidget_virtualize::QWidget_focusOutEvent(QFocusEvent *event) {
    voidCall("focusOutEvent", pArgREF(event, QFocusEvent));
}

void QWidget_virtualize::QWidget_fontChange(const QFont &font) {
    voidCall("fontChange", pArgREF(&font, const QFont));
}

void QWidget_virtualize::QWidget_hide() {
    voidCall("hide");
}

void QWidget_virtualize::QWidget_keyPressEvent(QKeyEvent *event) {
    voidCall("keyPressEvent", pArgREF(event, QKeyEvent));
}

void QWidget_virtualize::QWidget_keyReleaseEvent(QKeyEvent *event) {
    voidCall("keyReleaseEvent", pArgREF(event, QKeyEvent));
}

void QWidget_virtualize::QWidget_leaveEvent(QEvent *event) {
    voidCall("leaveEvent", pArgREF(event, QEvent));
}

void QWidget_virtualize::QWidget_mouseDoubleClickEvent(QMouseEvent *event) {
    voidCall("mouseDoubleClickEvent", pArgREF(event, QMouseEvent));
}

void QWidget_virtualize::QWidget_mouseMoveEvent(QMouseEvent *event) {
    voidCall("mouseMoveEvent", pArgREF(event, QMouseEvent));
}

void QWidget_virtualize::QWidget_mousePressEvent(QMouseEvent *event) {
    voidCall("mousePressEvent", pArgREF(event, QMouseEvent));
}

void QWidget_virtualize::QWidget_mouseReleaseEvent(QMouseEvent *event) {
    voidCall("mouseReleaseEvent", pArgREF(event, QMouseEvent));
}

void QWidget_virtualize::QWidget_move(int x, int y) {
    voidCall("move", pArgIV(x), pArgIV(y));
}

void QWidget_virtualize::QWidget_moveEvent(QMoveEvent *event) {
    voidCall("moveEvent", pArgREF(event, QMoveEvent));
}

void QWidget_virtualize::QWidget_paintEvent(QPaintEvent *event) {
    voidCall("paintEvent", pArgREF(event, QPaintEvent));
}

void QWidget_virtualize::QWidget_paletteChange(const QPalette &palette) {
    voidCall("paletteChange", pArgREF(&palette, const QPalette));
}

void QWidget_virtualize::QWidget_resize(int w, int h) {
    voidCall("resize", pArgIV(w), pArgIV(h));
}

void QWidget_virtualize::QWidget_resizeEvent(QResizeEvent *event) {
    voidCall("resizeEvent", pArgREF(event, QResizeEvent));
}

void QWidget_virtualize::QWidget_setBackgroundColor(const QColor &color) {
    voidCall("setBackgroundColor", pArgREF(&color, const QColor));
}

void QWidget_virtualize::QWidget_setBackgroundPixmap(const QPixmap &pixmap) {
    voidCall("setBackgroundPixmap", pArgREF(&pixmap, const QPixmap));
}

void QWidget_virtualize::QWidget_setCursor(const QCursor &cursor) {
    voidCall("setCursor", pArgREF(&cursor, const QCursor));
}

void QWidget_virtualize::QWidget_setEnabled(bool enable) {
    voidCall("setEnabled", pArgBOOL(enable));
}

void QWidget_virtualize::QWidget_setFont(const QFont &font) {
    voidCall("setFont", pArgREF(&font, const QFont));
}

void QWidget_virtualize::QWidget_setGeometry(int x, int y, int w, int h) {
    voidCall("setGeometry", pArgIV(x), pArgIV(y), pArgIV(w), pArgIV(h));
}

void QWidget_virtualize::QWidget_setPalette(const QPalette &palette) {
    voidCall("setPalette", pArgREF(&palette, const QPalette));
}

void QWidget_virtualize::QWidget_setStyle(GUIStyle style) {
    voidCall("setStyle", pArgIV(style));
}

void QWidget_virtualize::QWidget_show() {
    voidCall("show");
}

QSize QWidget_virtualize::QWidget_sizeHint() const {
    return prDEREF(retCallConst("sizeHint"), QSize);
}

void QWidget_virtualize::QWidget_styleChange(GUIStyle style) {
    voidCall("styleChange", pArgIV(style));
}
