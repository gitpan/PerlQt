/*
 * PMenuBar definitions.
 *
 * Copyright (C) 1997, Ashley Winters <jql@accessone.com>
 *
 * You may distribute under the terms of the LGPL as specified in the
 * README file
 */

#include "pmenubar.h"

const char *PMenuBar::className() const {
    return PObject_className();
}

bool PMenuBar::event(QEvent *event) {
    bool ret = PObject_event(event);
    if(pfailed) ret = QMenuBar::event(event);
    return ret;
}

bool PMenuBar::eventFilter(QObject *obj, QEvent *event) {
    bool ret = PObject_eventFilter(obj, event);
    if(pfailed) ret = QMenuBar::eventFilter(obj, event);
    return ret;
}

QMetaObject *PMenuBar::metaObject() const {
    QMetaObject *ret = PObject_metaObject();
    if(pfailed) ret = QMenuBar::metaObject();
    return ret;
}

void PMenuBar::initMetaObject() {
    if(!QMenuBar::metaObject()) QMenuBar::initMetaObject();
    PObject_initMetaObject();
}

void PMenuBar::timerEvent(QTimerEvent *event) {
    PObject_timerEvent(event);
    if(pfailed) QMenuBar::timerEvent(event);
}


void PMenuBar::adjustSize() {
    PWidget_adjustSize();
    if(pfailed) QMenuBar::adjustSize();
}

bool PMenuBar::close(bool b) {
    bool ret = PWidget_close(b);
    if(pfailed) ret = QMenuBar::close(b);
    return ret;
}

void PMenuBar::hide() {
    PWidget_hide();
    if(pfailed) QMenuBar::hide();
}

void PMenuBar::move(int x, int y) {
    PWidget_move(x, y);
    if(pfailed) QMenuBar::move(x, y);
}

void PMenuBar::resize(int w, int h) {
    PWidget_resize(w, h);
    if(pfailed) QMenuBar::resize(w, h);
}

void PMenuBar::setBackgroundColor(const QColor &c) {
    PWidget_setBackgroundColor(c);
    if(pfailed) QMenuBar::setBackgroundColor(c);
}

void PMenuBar::setBackgroundPixmap(const QPixmap &p) {
    PWidget_setBackgroundPixmap(p);
    if(pfailed) QMenuBar::setBackgroundPixmap(p);
}

void PMenuBar::setCursor(const QCursor &c) {
    PWidget_setCursor(c);
    if(pfailed) QMenuBar::setCursor(c);
}

void PMenuBar::setEnabled(bool b) {
    PWidget_setEnabled(b);
    if(pfailed) QMenuBar::setEnabled(b);
}

void PMenuBar::setFont(const QFont &f) {
    PWidget_setFont(f);
    if(pfailed) QMenuBar::setFont(f);
}

void PMenuBar::setGeometry(int x, int y, int w, int h) {
    PWidget_setGeometry(x, y, w, h);
    if(pfailed) QMenuBar::setGeometry(x, y, w, h);
}

void PMenuBar::setPalette(const QPalette &p) {
    PWidget_setPalette(p);
    if(pfailed) QMenuBar::setPalette(p);
}

void PMenuBar::setStyle(GUIStyle s) {
    PWidget_setStyle(s);
    if(pfailed) QMenuBar::setStyle(s);
}

void PMenuBar::show() {
    PWidget_show();
    if(pfailed) QMenuBar::show();
}

QSize PMenuBar::sizeHint() const {
    QSize ret = PWidget_sizeHint();
    if(pfailed) ret = QMenuBar::sizeHint();
    return ret;
}

void PMenuBar::closeEvent(QCloseEvent *event) {
    PWidget_closeEvent(event);
    if(pfailed) QMenuBar::closeEvent(event);
}

void PMenuBar::enterEvent(QEvent *event) {
    PWidget_enterEvent(event);
    if(pfailed) QMenuBar::enterEvent(event);
}

void PMenuBar::focusInEvent(QFocusEvent *event) {
    PWidget_focusInEvent(event);
    if(pfailed) QMenuBar::focusInEvent(event);
}

void PMenuBar::focusOutEvent(QFocusEvent *event) {
    PWidget_focusOutEvent(event);
    if(pfailed) QMenuBar::focusOutEvent(event);
}

void PMenuBar::keyPressEvent(QKeyEvent *event) {
    PWidget_keyPressEvent(event);
    if(pfailed) QMenuBar::keyPressEvent(event);
}

void PMenuBar::keyReleaseEvent(QKeyEvent *event) {
    PWidget_keyReleaseEvent(event);
    if(pfailed) QMenuBar::keyReleaseEvent(event);
}

void PMenuBar::leaveEvent(QEvent *event) {
    PWidget_leaveEvent(event);
    if(pfailed) QMenuBar::leaveEvent(event);
}

void PMenuBar::mouseDoubleClickEvent(QMouseEvent *event) {
    PWidget_mouseDoubleClickEvent(event);
    if(pfailed) QMenuBar::mouseDoubleClickEvent(event);
}

void PMenuBar::mouseMoveEvent(QMouseEvent *event) {
    PWidget_mouseMoveEvent(event);
    if(pfailed) QMenuBar::mouseMoveEvent(event);
}

void PMenuBar::mousePressEvent(QMouseEvent *event) {
    PWidget_mousePressEvent(event);
    if(pfailed) QMenuBar::mousePressEvent(event);
}

void PMenuBar::mouseReleaseEvent(QMouseEvent *event) {
    PWidget_mouseReleaseEvent(event);
    if(pfailed) QMenuBar::mouseReleaseEvent(event);
}

void PMenuBar::moveEvent(QMoveEvent *event) {
    PWidget_moveEvent(event);
    if(pfailed) QMenuBar::moveEvent(event);
}

void PMenuBar::paintEvent(QPaintEvent *event) {
    PWidget_paintEvent(event);
    if(pfailed) QMenuBar::paintEvent(event);
}

void PMenuBar::resizeEvent(QResizeEvent *event) {
    PWidget_resizeEvent(event);
    if(pfailed) QMenuBar::resizeEvent(event);
}


void PMenuBar::drawContents(QPainter *p) {
    PFrame_drawContents(p);
    if(pfailed) QMenuBar::drawContents(p);
}

void PMenuBar::drawFrame(QPainter *p) {
    PFrame_drawFrame(p);
    if(pfailed) QMenuBar::drawFrame(p);
}
/*
void PMenuBar::frameChanged() {
    PFrame_frameChanged();
    if(pfailed) QMenuBar::frameChanged();
}
*/

void PMenuBar::updateItem(int id) {
    PMenuData_updateItem(id);
    if(pfailed) QMenuBar::updateItem(id);
}

void PMenuBar::menuContentsChanged() {
    PMenuData_menuContentsChanged();
    if(pfailed) QMenuBar::menuContentsChanged();
}
/*
void PMenuBar::menuDelPopup(QPopupMenu *popmenu) {
    PMenuData_menuDelPopup(popmenu);
    if(pfailed) QMenuBar::menuDelPopup(popmenu);
}

void PMenuBar::menuInsPopup(QPopupMenu *popmenu) {
    PMenuData_menuInsPopup(popmenu);
    if(pfailed) QMenuBar::menuInsPopup(popmenu);
}
*/
void PMenuBar::menuStateChanged() {
    PMenuData_menuStateChanged();
    if(pfailed) QMenuBar::menuStateChanged();
}
