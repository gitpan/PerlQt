/*
 * PListBox definitions.
 *
 * Copyright (C) 1997, Ashley Winters <jql@accessone.com>
 *
 * You may distribute under the terms of the LGPL as specified in the
 * README file
 */

#include "plistbox.h"

const char *PListBox::className() const {
    return PObject_className();
}

bool PListBox::event(QEvent *event) {
    bool ret = PObject_event(event);
    if(pfailed) ret = QListBox::event(event);
    return ret;
}

bool PListBox::eventFilter(QObject *obj, QEvent *event) {
    bool ret = PObject_eventFilter(obj, event);
    if(pfailed) ret = QListBox::eventFilter(obj, event);
    return ret;
}

QMetaObject *PListBox::metaObject() const {
    QMetaObject *ret = PObject_metaObject();
    if(pfailed) ret = QListBox::metaObject();
    return ret;
}

void PListBox::initMetaObject() {
    if(!QListBox::metaObject()) QListBox::initMetaObject();
    PObject_initMetaObject();
}

void PListBox::timerEvent(QTimerEvent *event) {
    PObject_timerEvent(event);
    if(pfailed) QListBox::timerEvent(event);
}


void PListBox::adjustSize() {
    PWidget_adjustSize();
    if(pfailed) QListBox::adjustSize();
}

bool PListBox::close(bool b) {
    bool ret = PWidget_close(b);
    if(pfailed) ret = QListBox::close(b);
    return ret;
}

void PListBox::hide() {
    PWidget_hide();
    if(pfailed) QListBox::hide();
}

void PListBox::move(int x, int y) {
    PWidget_move(x, y);
    if(pfailed) QListBox::move(x, y);
}

void PListBox::resize(int w, int h) {
    PWidget_resize(w, h);
    if(pfailed) QListBox::resize(w, h);
}

void PListBox::setBackgroundColor(const QColor &c) {
    PWidget_setBackgroundColor(c);
    if(pfailed) QListBox::setBackgroundColor(c);
}

void PListBox::setBackgroundPixmap(const QPixmap &p) {
    PWidget_setBackgroundPixmap(p);
    if(pfailed) QListBox::setBackgroundPixmap(p);
}

void PListBox::setCursor(const QCursor &c) {
    PWidget_setCursor(c);
    if(pfailed) QListBox::setCursor(c);
}

void PListBox::setEnabled(bool b) {
    PWidget_setEnabled(b);
    if(pfailed) QListBox::setEnabled(b);
}

void PListBox::setFont(const QFont &f) {
    PWidget_setFont(f);
    if(pfailed) QListBox::setFont(f);
}

void PListBox::setGeometry(int x, int y, int w, int h) {
    PWidget_setGeometry(x, y, w, h);
    if(pfailed) QListBox::setGeometry(x, y, w, h);
}

void PListBox::setPalette(const QPalette &p) {
    PWidget_setPalette(p);
    if(pfailed) QListBox::setPalette(p);
}

void PListBox::setStyle(GUIStyle s) {
    PWidget_setStyle(s);
    if(pfailed) QListBox::setStyle(s);
}

void PListBox::show() {
    PWidget_show();
    if(pfailed) QListBox::show();
}

QSize PListBox::sizeHint() const {
    QSize ret = PWidget_sizeHint();
    if(pfailed) ret = QListBox::sizeHint();
    return ret;
}

void PListBox::closeEvent(QCloseEvent *event) {
    PWidget_closeEvent(event);
    if(pfailed) QListBox::closeEvent(event);
}

void PListBox::enterEvent(QEvent *event) {
    PWidget_enterEvent(event);
    if(pfailed) QListBox::enterEvent(event);
}

void PListBox::focusInEvent(QFocusEvent *event) {
    PWidget_focusInEvent(event);
    if(pfailed) QListBox::focusInEvent(event);
}

void PListBox::focusOutEvent(QFocusEvent *event) {
    PWidget_focusOutEvent(event);
    if(pfailed) QListBox::focusOutEvent(event);
}

void PListBox::keyPressEvent(QKeyEvent *event) {
    PWidget_keyPressEvent(event);
    if(pfailed) QListBox::keyPressEvent(event);
}

void PListBox::keyReleaseEvent(QKeyEvent *event) {
    PWidget_keyReleaseEvent(event);
    if(pfailed) QListBox::keyReleaseEvent(event);
}

void PListBox::leaveEvent(QEvent *event) {
    PWidget_leaveEvent(event);
    if(pfailed) QListBox::leaveEvent(event);
}

void PListBox::mouseDoubleClickEvent(QMouseEvent *event) {
    PWidget_mouseDoubleClickEvent(event);
    if(pfailed) QListBox::mouseDoubleClickEvent(event);
}

void PListBox::mouseMoveEvent(QMouseEvent *event) {
    PWidget_mouseMoveEvent(event);
    if(pfailed) QListBox::mouseMoveEvent(event);
}

void PListBox::mousePressEvent(QMouseEvent *event) {
    PWidget_mousePressEvent(event);
    if(pfailed) QListBox::mousePressEvent(event);
}

void PListBox::mouseReleaseEvent(QMouseEvent *event) {
    PWidget_mouseReleaseEvent(event);
    if(pfailed) QListBox::mouseReleaseEvent(event);
}

void PListBox::moveEvent(QMoveEvent *event) {
    PWidget_moveEvent(event);
    if(pfailed) QListBox::moveEvent(event);
}

void PListBox::paintEvent(QPaintEvent *event) {
    PWidget_paintEvent(event);
    if(pfailed) QListBox::paintEvent(event);
}

void PListBox::resizeEvent(QResizeEvent *event) {
    PWidget_resizeEvent(event);
    if(pfailed) QListBox::resizeEvent(event);
}


void PListBox::drawContents(QPainter *p) {
    PFrame_drawContents(p);
    if(pfailed) QListBox::drawContents(p);
}

void PListBox::drawFrame(QPainter *p) {
    PFrame_drawFrame(p);
    if(pfailed) QListBox::drawFrame(p);
}

void PListBox::frameChanged() {
    PFrame_frameChanged();
    if(pfailed) QListBox::frameChanged();
}


int PListBox::cellHeight(int row) {
    int ret = PTableView_cellHeight(row);
    if(pfailed) ret = QListBox::cellHeight(row);
    return ret;
}

int PListBox::cellWidth(int col) {
    int ret = PTableView_cellWidth(col);
    if(pfailed) ret = QListBox::cellWidth(col);
    return ret;
}

void PListBox::paintCell(QPainter *p, int row, int col) {
    PTableView_paintCell(p, row, col);
    if(pfailed) QListBox::paintCell(p, row, col);
}

void PListBox::setupPainter(QPainter *p) {
    PTableView_setupPainter(p);
    if(pfailed) QListBox::setupPainter(p);
}

int PListBox::totalHeight() {
    int ret = PTableView_totalHeight();
    if(pfailed) ret = QListBox::totalHeight();
    return ret;
}

int PListBox::totalWidth() {
    int ret = PTableView_totalWidth();
    if(pfailed) ret = QListBox::totalWidth();
    return ret;
}


