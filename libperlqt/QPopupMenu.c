/*
 * PPopupMenu definitions.
 *
 * Copyright (C) 1997, Ashley Winters <jql@accessone.com>
 *
 * You may distribute under the terms of the LGPL as specified in the
 * README file
 */

#include "ppopmenu.h"

const char *PPopupMenu::className() const {
    return PObject_className();
}

bool PPopupMenu::event(QEvent *event) {
    bool ret = PObject_event(event);
    if(pfailed) ret = QPopupMenu::event(event);
    return ret;
}

bool PPopupMenu::eventFilter(QObject *obj, QEvent *event) {
    bool ret = PObject_eventFilter(obj, event);
    if(pfailed) ret = QPopupMenu::eventFilter(obj, event);
    return ret;
}

QMetaObject *PPopupMenu::metaObject() const {
    QMetaObject *ret = PObject_metaObject();
    if(pfailed) ret = QPopupMenu::metaObject();
    return ret;
}

void PPopupMenu::initMetaObject() {
    if(!QPopupMenu::metaObject()) QPopupMenu::initMetaObject();
    PObject_initMetaObject();
}

void PPopupMenu::timerEvent(QTimerEvent *event) {
    PObject_timerEvent(event);
    if(pfailed) QPopupMenu::timerEvent(event);
}


void PPopupMenu::adjustSize() {
    PWidget_adjustSize();
    if(pfailed) QPopupMenu::adjustSize();
}

bool PPopupMenu::close(bool b) {
    bool ret = PWidget_close(b);
    if(pfailed) ret = QPopupMenu::close(b);
    return ret;
}

void PPopupMenu::hide() {
    PWidget_hide();
    if(pfailed) QPopupMenu::hide();
}

void PPopupMenu::move(int x, int y) {
    PWidget_move(x, y);
    if(pfailed) QPopupMenu::move(x, y);
}

void PPopupMenu::resize(int w, int h) {
    PWidget_resize(w, h);
    if(pfailed) QPopupMenu::resize(w, h);
}

void PPopupMenu::setBackgroundColor(const QColor &c) {
    PWidget_setBackgroundColor(c);
    if(pfailed) QPopupMenu::setBackgroundColor(c);
}

void PPopupMenu::setBackgroundPixmap(const QPixmap &p) {
    PWidget_setBackgroundPixmap(p);
    if(pfailed) QPopupMenu::setBackgroundPixmap(p);
}

void PPopupMenu::setCursor(const QCursor &c) {
    PWidget_setCursor(c);
    if(pfailed) QPopupMenu::setCursor(c);
}

void PPopupMenu::setEnabled(bool b) {
    PWidget_setEnabled(b);
    if(pfailed) QPopupMenu::setEnabled(b);
}

void PPopupMenu::setFont(const QFont &f) {
    PWidget_setFont(f);
    if(pfailed) QPopupMenu::setFont(f);
}

void PPopupMenu::setGeometry(int x, int y, int w, int h) {
    PWidget_setGeometry(x, y, w, h);
    if(pfailed) QPopupMenu::setGeometry(x, y, w, h);
}

void PPopupMenu::setPalette(const QPalette &p) {
    PWidget_setPalette(p);
    if(pfailed) QPopupMenu::setPalette(p);
}

void PPopupMenu::setStyle(GUIStyle s) {
    PWidget_setStyle(s);
    if(pfailed) QPopupMenu::setStyle(s);
}

void PPopupMenu::show() {
    PWidget_show();
    if(pfailed) QPopupMenu::show();
}

QSize PPopupMenu::sizeHint() const {
    QSize ret = PWidget_sizeHint();
    if(pfailed) ret = QPopupMenu::sizeHint();
    return ret;
}

void PPopupMenu::closeEvent(QCloseEvent *event) {
    PWidget_closeEvent(event);
    if(pfailed) QPopupMenu::closeEvent(event);
}

void PPopupMenu::enterEvent(QEvent *event) {
    PWidget_enterEvent(event);
    if(pfailed) QPopupMenu::enterEvent(event);
}

void PPopupMenu::focusInEvent(QFocusEvent *event) {
    PWidget_focusInEvent(event);
    if(pfailed) QPopupMenu::focusInEvent(event);
}

void PPopupMenu::focusOutEvent(QFocusEvent *event) {
    PWidget_focusOutEvent(event);
    if(pfailed) QPopupMenu::focusOutEvent(event);
}

void PPopupMenu::keyPressEvent(QKeyEvent *event) {
    PWidget_keyPressEvent(event);
    if(pfailed) QPopupMenu::keyPressEvent(event);
}

void PPopupMenu::keyReleaseEvent(QKeyEvent *event) {
    PWidget_keyReleaseEvent(event);
    if(pfailed) QPopupMenu::keyReleaseEvent(event);
}

void PPopupMenu::leaveEvent(QEvent *event) {
    PWidget_leaveEvent(event);
    if(pfailed) QPopupMenu::leaveEvent(event);
}

void PPopupMenu::mouseDoubleClickEvent(QMouseEvent *event) {
    PWidget_mouseDoubleClickEvent(event);
    if(pfailed) QPopupMenu::mouseDoubleClickEvent(event);
}

void PPopupMenu::mouseMoveEvent(QMouseEvent *event) {
    PWidget_mouseMoveEvent(event);
    if(pfailed) QPopupMenu::mouseMoveEvent(event);
}

void PPopupMenu::mousePressEvent(QMouseEvent *event) {
    PWidget_mousePressEvent(event);
    if(pfailed) QPopupMenu::mousePressEvent(event);
}

void PPopupMenu::mouseReleaseEvent(QMouseEvent *event) {
    PWidget_mouseReleaseEvent(event);
    if(pfailed) QPopupMenu::mouseReleaseEvent(event);
}

void PPopupMenu::moveEvent(QMoveEvent *event) {
    PWidget_moveEvent(event);
    if(pfailed) QPopupMenu::moveEvent(event);
}

void PPopupMenu::paintEvent(QPaintEvent *event) {
    PWidget_paintEvent(event);
    if(pfailed) QPopupMenu::paintEvent(event);
}

void PPopupMenu::resizeEvent(QResizeEvent *event) {
    PWidget_resizeEvent(event);
    if(pfailed) QPopupMenu::resizeEvent(event);
}


void PPopupMenu::drawContents(QPainter *p) {
    PFrame_drawContents(p);
    if(pfailed) QPopupMenu::drawContents(p);
}

void PPopupMenu::drawFrame(QPainter *p) {
    PFrame_drawFrame(p);
    if(pfailed) QPopupMenu::drawFrame(p);
}
/*
void PPopupMenu::frameChanged() {
    PFrame_frameChanged();
    if(pfailed) QPopupMenu::frameChanged();
}
*/

int PPopupMenu::cellHeight(int row) {
    int ret = PTableView_cellHeight(row);
    if(pfailed) ret = QPopupMenu::cellHeight(row);
    return ret;
}

int PPopupMenu::cellWidth(int col) {
    int ret = PTableView_cellWidth(col);
    if(pfailed) ret = QPopupMenu::cellWidth(col);
    return ret;
}

void PPopupMenu::paintCell(QPainter *p, int row, int col) {
    PTableView_paintCell(p, row, col);
    if(pfailed) QPopupMenu::paintCell(p, row, col);
}

void PPopupMenu::setupPainter(QPainter *p) {
    PTableView_setupPainter(p);
    if(pfailed) QPopupMenu::setupPainter(p);
}

int PPopupMenu::totalHeight() {
    int ret = PTableView_totalHeight();
    if(pfailed) ret = QPopupMenu::totalHeight();
    return ret;
}

int PPopupMenu::totalWidth() {
    int ret = PTableView_totalWidth();
    if(pfailed) ret = QPopupMenu::totalWidth();
    return ret;
}


void PPopupMenu::updateItem(int id) {
    PMenuData_updateItem(id);
    if(pfailed) QPopupMenu::updateItem(id);
}
/*
void PPopupMenu::menuContentsChanged() {
    PMenuData_menuContentsChanged();
    if(pfailed) QPopupMenu::menuContentsChanged();
}

void PPopupMenu::menuDelPopup(QPopupMenu *popmenu) {
    PMenuData_menuDelPopup(popmenu);
    if(pfailed) QPopupMenu::menuDelPopup(popmenu);
}

void PPopupMenu::menuInsPopup(QPopupMenu *popmenu) {
    PMenuData_menuInsPopup(popmenu);
    if(pfailed) QPopupMenu::menuInsPopup(popmenu);
}

void PPopupMenu::menuStateChanged() {
    PMenuData_menuStateChanged();
    if(pfailed) QPopupMenu::menuStateChanged();
}
*/

