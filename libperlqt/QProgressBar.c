/*
 * PProgressBar definitions.
 *
 * Copyright (C) 1997, Ashley Winters <jql@accessone.com>
 *
 * You may distribute under the terms of the LGPL as specified in the
 * README file
 */

#include "pprogbar.h"

const char *PProgressBar::className() const {
    return PObject_className();
}

bool PProgressBar::event(QEvent *event) {
    bool ret = PObject_event(event);
    if(pfailed) ret = QProgressBar::event(event);
    return ret;
}

bool PProgressBar::eventFilter(QObject *obj, QEvent *event) {
    bool ret = PObject_eventFilter(obj, event);
    if(pfailed) ret = QProgressBar::eventFilter(obj, event);
    return ret;
}

QMetaObject *PProgressBar::metaObject() const {
    QMetaObject *ret = PObject_metaObject();
    if(pfailed) ret = QProgressBar::metaObject();
    return ret;
}

void PProgressBar::initMetaObject() {
    if(!QProgressBar::metaObject()) QProgressBar::initMetaObject();
    PObject_initMetaObject();
}

void PProgressBar::timerEvent(QTimerEvent *event) {
    PObject_timerEvent(event);
    if(pfailed) QProgressBar::timerEvent(event);
}


void PProgressBar::adjustSize() {
    PWidget_adjustSize();
    if(pfailed) QProgressBar::adjustSize();
}

bool PProgressBar::close(bool b) {
    bool ret = PWidget_close(b);
    if(pfailed) ret = QProgressBar::close(b);
    return ret;
}

void PProgressBar::hide() {
    PWidget_hide();
    if(pfailed) QProgressBar::hide();
}

void PProgressBar::move(int x, int y) {
    PWidget_move(x, y);
    if(pfailed) QProgressBar::move(x, y);
}

void PProgressBar::resize(int w, int h) {
    PWidget_resize(w, h);
    if(pfailed) QProgressBar::resize(w, h);
}

void PProgressBar::setBackgroundColor(const QColor &c) {
    PWidget_setBackgroundColor(c);
    if(pfailed) QProgressBar::setBackgroundColor(c);
}

void PProgressBar::setBackgroundPixmap(const QPixmap &p) {
    PWidget_setBackgroundPixmap(p);
    if(pfailed) QProgressBar::setBackgroundPixmap(p);
}

void PProgressBar::setCursor(const QCursor &c) {
    PWidget_setCursor(c);
    if(pfailed) QProgressBar::setCursor(c);
}

void PProgressBar::setEnabled(bool b) {
    PWidget_setEnabled(b);
    if(pfailed) QProgressBar::setEnabled(b);
}

void PProgressBar::setFont(const QFont &f) {
    PWidget_setFont(f);
    if(pfailed) QProgressBar::setFont(f);
}

void PProgressBar::setGeometry(int x, int y, int w, int h) {
    PWidget_setGeometry(x, y, w, h);
    if(pfailed) QProgressBar::setGeometry(x, y, w, h);
}

void PProgressBar::setPalette(const QPalette &p) {
    PWidget_setPalette(p);
    if(pfailed) QProgressBar::setPalette(p);
}

void PProgressBar::setStyle(GUIStyle s) {
    PWidget_setStyle(s);
    if(pfailed) QProgressBar::setStyle(s);
}

void PProgressBar::show() {
    PWidget_show();
    if(pfailed) QProgressBar::show();
}

QSize PProgressBar::sizeHint() const {
    QSize ret = PWidget_sizeHint();
    if(pfailed) ret = QProgressBar::sizeHint();
    return ret;
}

void PProgressBar::closeEvent(QCloseEvent *event) {
    PWidget_closeEvent(event);
    if(pfailed) QProgressBar::closeEvent(event);
}

void PProgressBar::enterEvent(QEvent *event) {
    PWidget_enterEvent(event);
    if(pfailed) QProgressBar::enterEvent(event);
}

void PProgressBar::focusInEvent(QFocusEvent *event) {
    PWidget_focusInEvent(event);
    if(pfailed) QProgressBar::focusInEvent(event);
}

void PProgressBar::focusOutEvent(QFocusEvent *event) {
    PWidget_focusOutEvent(event);
    if(pfailed) QProgressBar::focusOutEvent(event);
}

void PProgressBar::keyPressEvent(QKeyEvent *event) {
    PWidget_keyPressEvent(event);
    if(pfailed) QProgressBar::keyPressEvent(event);
}

void PProgressBar::keyReleaseEvent(QKeyEvent *event) {
    PWidget_keyReleaseEvent(event);
    if(pfailed) QProgressBar::keyReleaseEvent(event);
}

void PProgressBar::leaveEvent(QEvent *event) {
    PWidget_leaveEvent(event);
    if(pfailed) QProgressBar::leaveEvent(event);
}

void PProgressBar::mouseDoubleClickEvent(QMouseEvent *event) {
    PWidget_mouseDoubleClickEvent(event);
    if(pfailed) QProgressBar::mouseDoubleClickEvent(event);
}

void PProgressBar::mouseMoveEvent(QMouseEvent *event) {
    PWidget_mouseMoveEvent(event);
    if(pfailed) QProgressBar::mouseMoveEvent(event);
}

void PProgressBar::mousePressEvent(QMouseEvent *event) {
    PWidget_mousePressEvent(event);
    if(pfailed) QProgressBar::mousePressEvent(event);
}

void PProgressBar::mouseReleaseEvent(QMouseEvent *event) {
    PWidget_mouseReleaseEvent(event);
    if(pfailed) QProgressBar::mouseReleaseEvent(event);
}

void PProgressBar::moveEvent(QMoveEvent *event) {
    PWidget_moveEvent(event);
    if(pfailed) QProgressBar::moveEvent(event);
}

void PProgressBar::paintEvent(QPaintEvent *event) {
    PWidget_paintEvent(event);
    if(pfailed) QProgressBar::paintEvent(event);
}

void PProgressBar::resizeEvent(QResizeEvent *event) {
    PWidget_resizeEvent(event);
    if(pfailed) QProgressBar::resizeEvent(event);
}


void PProgressBar::drawContents(QPainter *p) {
    PFrame_drawContents(p);
    if(pfailed) QProgressBar::drawContents(p);
}

void PProgressBar::drawFrame(QPainter *p) {
    PFrame_drawFrame(p);
    if(pfailed) QProgressBar::drawFrame(p);
}

void PProgressBar::frameChanged() {
    PFrame_frameChanged();
    if(pfailed) QProgressBar::frameChanged();
}


bool PProgressBar::setIndicator(QString &ps, int progress, int totalSteps) {
    PProgressBar_setIndicator(ps, progress, totalSteps);
    if(pfailed) QProgressBar::setIndicator(ps, progress, totalSteps);
}


bool PProgressBar_virtualize::PProgressBar_setIndicator(QString &ps,
							int progress,
							int totalSteps) {
    SV *arg1 = ps.isNull() ? &sv_undef : newSVpv(ps.data(), 0);
    SV *arg2 = newSViv(progress);
    SV *arg3 = newSViv(totalSteps);
    SV *r = retCall("setIndicator", arg1, arg2, arg3);
    SvREFCNT_dec(arg3);
    SvREFCNT_dec(arg2);
    SvREFCNT_dec(arg1);
    if(pfailed) return FALSE;
    bool ret = SvTRUE(r) ? TRUE : FALSE;
    SvREFCNT_dec(r);
    return ret;
}
