/*
 * PTabBar definitions.
 *
 * Copyright (C) 1997, Ashley Winters <jql@accessone.com>
 *
 * You may distribute under the terms of the LGPL as specified in the
 * README file
 */

#include "ptabbar.h"

const char *PTabBar::className() const {
    return PObject_className();
}

bool PTabBar::event(QEvent *event) {
    bool ret = PObject_event(event);
    if(pfailed) ret = QTabBar::event(event);
    return ret;
}

bool PTabBar::eventFilter(QObject *obj, QEvent *event) {
    bool ret = PObject_eventFilter(obj, event);
    if(pfailed) ret = QTabBar::eventFilter(obj, event);
    return ret;
}

QMetaObject *PTabBar::metaObject() const {
    QMetaObject *ret = PObject_metaObject();
    if(pfailed) ret = QTabBar::metaObject();
    return ret;
}

void PTabBar::initMetaObject() {
    if(!QTabBar::metaObject()) QTabBar::initMetaObject();
    PObject_initMetaObject();
}

void PTabBar::timerEvent(QTimerEvent *event) {
    PObject_timerEvent(event);
    if(pfailed) QTabBar::timerEvent(event);
}


void PTabBar::adjustSize() {
    PWidget_adjustSize();
    if(pfailed) QTabBar::adjustSize();
}

bool PTabBar::close(bool b) {
    bool ret = PWidget_close(b);
    if(pfailed) ret = QTabBar::close(b);
    return ret;
}

void PTabBar::hide() {
    PWidget_hide();
    if(pfailed) QTabBar::hide();
}

void PTabBar::move(int x, int y) {
    PWidget_move(x, y);
    if(pfailed) QTabBar::move(x, y);
}

void PTabBar::resize(int w, int h) {
    PWidget_resize(w, h);
    if(pfailed) QTabBar::resize(w, h);
}

void PTabBar::setBackgroundColor(const QColor &c) {
    PWidget_setBackgroundColor(c);
    if(pfailed) QTabBar::setBackgroundColor(c);
}

void PTabBar::setBackgroundPixmap(const QPixmap &p) {
    PWidget_setBackgroundPixmap(p);
    if(pfailed) QTabBar::setBackgroundPixmap(p);
}

void PTabBar::setCursor(const QCursor &c) {
    PWidget_setCursor(c);
    if(pfailed) QTabBar::setCursor(c);
}

void PTabBar::setEnabled(bool b) {
    PWidget_setEnabled(b);
    if(pfailed) QTabBar::setEnabled(b);
}

void PTabBar::setFont(const QFont &f) {
    PWidget_setFont(f);
    if(pfailed) QTabBar::setFont(f);
}

void PTabBar::setGeometry(int x, int y, int w, int h) {
    PWidget_setGeometry(x, y, w, h);
    if(pfailed) QTabBar::setGeometry(x, y, w, h);
}

void PTabBar::setPalette(const QPalette &p) {
    PWidget_setPalette(p);
    if(pfailed) QTabBar::setPalette(p);
}

void PTabBar::setStyle(GUIStyle s) {
    PWidget_setStyle(s);
    if(pfailed) QTabBar::setStyle(s);
}

void PTabBar::show() {
    PWidget_show();
    if(pfailed) QTabBar::show();
}

QSize PTabBar::sizeHint() const {
    QSize ret = PWidget_sizeHint();
    if(pfailed) ret = QTabBar::sizeHint();
    return ret;
}

void PTabBar::closeEvent(QCloseEvent *event) {
    PWidget_closeEvent(event);
    if(pfailed) QTabBar::closeEvent(event);
}

void PTabBar::enterEvent(QEvent *event) {
    PWidget_enterEvent(event);
    if(pfailed) QTabBar::enterEvent(event);
}

void PTabBar::focusInEvent(QFocusEvent *event) {
    PWidget_focusInEvent(event);
    if(pfailed) QTabBar::focusInEvent(event);
}

void PTabBar::focusOutEvent(QFocusEvent *event) {
    PWidget_focusOutEvent(event);
    if(pfailed) QTabBar::focusOutEvent(event);
}

void PTabBar::keyPressEvent(QKeyEvent *event) {
    PWidget_keyPressEvent(event);
    if(pfailed) QTabBar::keyPressEvent(event);
}

void PTabBar::keyReleaseEvent(QKeyEvent *event) {
    PWidget_keyReleaseEvent(event);
    if(pfailed) QTabBar::keyReleaseEvent(event);
}

void PTabBar::leaveEvent(QEvent *event) {
    PWidget_leaveEvent(event);
    if(pfailed) QTabBar::leaveEvent(event);
}

void PTabBar::mouseDoubleClickEvent(QMouseEvent *event) {
    PWidget_mouseDoubleClickEvent(event);
    if(pfailed) QTabBar::mouseDoubleClickEvent(event);
}

void PTabBar::mouseMoveEvent(QMouseEvent *event) {
    PWidget_mouseMoveEvent(event);
    if(pfailed) QTabBar::mouseMoveEvent(event);
}

void PTabBar::mousePressEvent(QMouseEvent *event) {
    PWidget_mousePressEvent(event);
    if(pfailed) QTabBar::mousePressEvent(event);
}

void PTabBar::mouseReleaseEvent(QMouseEvent *event) {
    PWidget_mouseReleaseEvent(event);
    if(pfailed) QTabBar::mouseReleaseEvent(event);
}

void PTabBar::moveEvent(QMoveEvent *event) {
    PWidget_moveEvent(event);
    if(pfailed) QTabBar::moveEvent(event);
}

void PTabBar::paintEvent(QPaintEvent *event) {
    PWidget_paintEvent(event);
    if(pfailed) QTabBar::paintEvent(event);
}

void PTabBar::resizeEvent(QResizeEvent *event) {
    PWidget_resizeEvent(event);
    if(pfailed) QTabBar::resizeEvent(event);
}


int PTabBar::addTab(QTab *tab) {
    int ret = PTabBar_addTab(tab);
    if(pfailed) ret = QTabBar::addTab(tab);
    return ret;
}

void PTabBar::paint(QPainter *p, QTab *tab, bool selected) const {
    PTabBar_paint(p, tab, selected);
    if(pfailed) QTabBar::paint(p, tab, selected);
}

QTab *PTabBar::selectTab(const QPoint &p) const {
    QTab *ret = PTabBar_selectTab(p);
    if(pfailed) ret = QTabBar::selectTab(p);
    return ret;
}


int PTabBar_virtualize::PTabBar_addTab(QTab *tab) {
    SV *r = retCallObj("addTab", tab, "QTab");
    if(pfailed) return -1;
    int ret = SvIV(r);
    SvREFCNT_dec(r);
    return ret;
}

void PTabBar_virtualize::PTabBar_paint(QPainter *p, QTab *tab, bool s) const {
    SV *arg1 = objectify_ptr(p, "QPainter");
    SV *arg2 = objectify_ptr(tab, "QTab");
    voidCall("paint", arg1, arg2, s ? &sv_yes : &sv_no);
    SvREFCNT_dec(arg2);
    SvREFCNT_dec(arg1);
}

QTab *PTabBar_virtualize::PTabBar_selectTab(const QPoint &p) const {
    SV *r = retCallObj("selectTab", &p, "QPoint");
    if(pfailed) return NULL;
    QTab *ret = (QTab *)extract_ptr(r, "QTab");
    SvREFCNT_dec(r);
    return ret;
}
