/*
 * PTableView definitions.
 *
 * Copyright (C) 1997, Ashley Winters <jql@accessone.com>
 *
 * You may distribute under the terms of the LGPL as specified in the
 * README file
 */

#include "ptablevw.h"

const char *PTableView::className() const {
    return PObject_className();
}

bool PTableView::event(QEvent *event) {
    bool ret = PObject_event(event);
    if(pfailed) ret = QTableView::event(event);
    return ret;
}

bool PTableView::eventFilter(QObject *obj, QEvent *event) {
    bool ret = PObject_eventFilter(obj, event);
    if(pfailed) ret = QTableView::eventFilter(obj, event);
    return ret;
}

QMetaObject *PTableView::metaObject() const {
    QMetaObject *ret = PObject_metaObject();
    if(pfailed) ret = QTableView::metaObject();
    return ret;
}

void PTableView::initMetaObject() {
    if(!QTableView::metaObject()) QTableView::initMetaObject();
    PObject_initMetaObject();
}

void PTableView::timerEvent(QTimerEvent *event) {
    PObject_timerEvent(event);
    if(pfailed) QTableView::timerEvent(event);
}


void PTableView::adjustSize() {
    PWidget_adjustSize();
    if(pfailed) QTableView::adjustSize();
}

bool PTableView::close(bool b) {
    bool ret = PWidget_close(b);
    if(pfailed) ret = QTableView::close(b);
    return ret;
}

void PTableView::hide() {
    PWidget_hide();
    if(pfailed) QTableView::hide();
}

void PTableView::move(int x, int y) {
    PWidget_move(x, y);
    if(pfailed) QTableView::move(x, y);
}

void PTableView::resize(int w, int h) {
    PWidget_resize(w, h);
    if(pfailed) QTableView::resize(w, h);
}

void PTableView::setBackgroundColor(const QColor &c) {
    PWidget_setBackgroundColor(c);
    if(pfailed) QTableView::setBackgroundColor(c);
}

void PTableView::setBackgroundPixmap(const QPixmap &p) {
    PWidget_setBackgroundPixmap(p);
    if(pfailed) QTableView::setBackgroundPixmap(p);
}

void PTableView::setCursor(const QCursor &c) {
    PWidget_setCursor(c);
    if(pfailed) QTableView::setCursor(c);
}

void PTableView::setEnabled(bool b) {
    PWidget_setEnabled(b);
    if(pfailed) QTableView::setEnabled(b);
}

void PTableView::setFont(const QFont &f) {
    PWidget_setFont(f);
    if(pfailed) QTableView::setFont(f);
}

void PTableView::setGeometry(int x, int y, int w, int h) {
    PWidget_setGeometry(x, y, w, h);
    if(pfailed) QTableView::setGeometry(x, y, w, h);
}

void PTableView::setPalette(const QPalette &p) {
    PWidget_setPalette(p);
    if(pfailed) QTableView::setPalette(p);
}

void PTableView::setStyle(GUIStyle s) {
    PWidget_setStyle(s);
    if(pfailed) QTableView::setStyle(s);
}

void PTableView::show() {
    PWidget_show();
    if(pfailed) QTableView::show();
}

QSize PTableView::sizeHint() const {
    QSize ret = PWidget_sizeHint();
    if(pfailed) ret = QTableView::sizeHint();
    return ret;
}

void PTableView::closeEvent(QCloseEvent *event) {
    PWidget_closeEvent(event);
    if(pfailed) QTableView::closeEvent(event);
}

void PTableView::enterEvent(QEvent *event) {
    PWidget_enterEvent(event);
    if(pfailed) QTableView::enterEvent(event);
}

void PTableView::focusInEvent(QFocusEvent *event) {
    PWidget_focusInEvent(event);
    if(pfailed) QTableView::focusInEvent(event);
}

void PTableView::focusOutEvent(QFocusEvent *event) {
    PWidget_focusOutEvent(event);
    if(pfailed) QTableView::focusOutEvent(event);
}

void PTableView::keyPressEvent(QKeyEvent *event) {
    PWidget_keyPressEvent(event);
    if(pfailed) QTableView::keyPressEvent(event);
}

void PTableView::keyReleaseEvent(QKeyEvent *event) {
    PWidget_keyReleaseEvent(event);
    if(pfailed) QTableView::keyReleaseEvent(event);
}

void PTableView::leaveEvent(QEvent *event) {
    PWidget_leaveEvent(event);
    if(pfailed) QTableView::leaveEvent(event);
}

void PTableView::mouseDoubleClickEvent(QMouseEvent *event) {
    PWidget_mouseDoubleClickEvent(event);
    if(pfailed) QTableView::mouseDoubleClickEvent(event);
}

void PTableView::mouseMoveEvent(QMouseEvent *event) {
    PWidget_mouseMoveEvent(event);
    if(pfailed) QTableView::mouseMoveEvent(event);
}

void PTableView::mousePressEvent(QMouseEvent *event) {
    PWidget_mousePressEvent(event);
    if(pfailed) QTableView::mousePressEvent(event);
}

void PTableView::mouseReleaseEvent(QMouseEvent *event) {
    PWidget_mouseReleaseEvent(event);
    if(pfailed) QTableView::mouseReleaseEvent(event);
}

void PTableView::moveEvent(QMoveEvent *event) {
    PWidget_moveEvent(event);
    if(pfailed) QTableView::moveEvent(event);
}

void PTableView::paintEvent(QPaintEvent *event) {
    PWidget_paintEvent(event);
    if(pfailed) QTableView::paintEvent(event);
}

void PTableView::resizeEvent(QResizeEvent *event) {
    PWidget_resizeEvent(event);
    if(pfailed) QTableView::resizeEvent(event);
}


void PTableView::drawContents(QPainter *p) {
    PFrame_drawContents(p);
    if(pfailed) QTableView::drawContents(p);
}

void PTableView::drawFrame(QPainter *p) {
    PFrame_drawFrame(p);
    if(pfailed) QTableView::drawFrame(p);
}

void PTableView::frameChanged() {
    PFrame_frameChanged();
    if(pfailed) QTableView::frameChanged();
}


int PTableView::cellHeight(int row) {
    int ret = PTableView_cellHeight(row);
    if(pfailed) ret = QTableView::cellHeight(row);
    return ret;
}

int PTableView::cellWidth(int col) {
    int ret = PTableView_cellWidth(col);
    if(pfailed) ret = QTableView::cellWidth(col);
    return ret;
}

void PTableView::paintCell(QPainter *p, int row, int col) {
    PTableView_paintCell(p, row, col);  // croak() on failure
}

void PTableView::setupPainter(QPainter *p) {
    PTableView_setupPainter(p);
    if(pfailed) QTableView::setupPainter(p);
}

int PTableView::totalHeight() {
    int ret = PTableView_totalHeight();
    if(pfailed) ret = QTableView::totalHeight();
    return ret;
}

int PTableView::totalWidth() {
    int ret = PTableView_totalWidth();
    if(pfailed) ret = QTableView::totalWidth();
    return ret;
}


int PTableView_virtualize::PTableView_cellHeight(int row) {
    SV *arg1 = newSViv(row);
    SV *r = retCall("cellHeight", arg1);
    SvREFCNT_dec(arg1);
    if(pfailed) return -1;
    int ret = SvIV(r);
    SvREFCNT_dec(r);
    return ret;
}

int PTableView_virtualize::PTableView_cellWidth(int col) {
    SV *arg1 = newSViv(col);
    SV *r = retCall("cellWidth", arg1);
    SvREFCNT_dec(arg1);
    if(pfailed) return -1;
    int ret = SvIV(r);
    SvREFCNT_dec(r);
    return ret;
}

void PTableView_virtualize::PTableView_paintCell(QPainter *p, int row,
						 int col) {
    SV *arg1 = objectify_ptr(p, "QPainter");
    SV *arg2 = newSViv(row);
    SV *arg3 = newSViv(col);
    voidCall("paintCell", arg1, arg2, arg3);
    SvREFCNT_dec(arg3);
    SvREFCNT_dec(arg2);
    SvREFCNT_dec(arg1);
}

void PTableView_virtualize::PTableView_setupPainter(QPainter *p) {
    voidCallObj("setupPainter", p, "QPainter");
}

int PTableView_virtualize::PTableView_totalHeight() {
    SV *r = retCall("totalHeight");
    if(pfailed) return -1;
    int ret = SvIV(r);
    SvREFCNT_dec(r);
    return ret;
}

int PTableView_virtualize::PTableView_totalWidth() {
    SV *r = retCall("totalWidth");
    if(pfailed) return -1;
    int ret = SvIV(r);
    SvREFCNT_dec(r);
    return ret;
}
