/*
 * PMultiLineEdit definitions.
 *
 * Copyright (C) 1997, Ashley Winters <jql@accessone.com>
 *
 * You may distribute under the terms of the LGPL as specified in the
 * README file
 */

#include "pmlined.h"

const char *PMultiLineEdit::className() const {
    return PObject_className();
}

bool PMultiLineEdit::event(QEvent *event) {
    bool ret = PObject_event(event);
    if(pfailed) ret = QMultiLineEdit::event(event);
    return ret;
}

bool PMultiLineEdit::eventFilter(QObject *obj, QEvent *event) {
    bool ret = PObject_eventFilter(obj, event);
    if(pfailed) ret = QMultiLineEdit::eventFilter(obj, event);
    return ret;
}

QMetaObject *PMultiLineEdit::metaObject() const {
    QMetaObject *ret = PObject_metaObject();
    if(pfailed) ret = QMultiLineEdit::metaObject();
    return ret;
}

void PMultiLineEdit::initMetaObject() {
    if(!QMultiLineEdit::metaObject()) QMultiLineEdit::initMetaObject();
    PObject_initMetaObject();
}

void PMultiLineEdit::timerEvent(QTimerEvent *event) {
    PObject_timerEvent(event);
    if(pfailed) QMultiLineEdit::timerEvent(event);
}


void PMultiLineEdit::adjustSize() {
    PWidget_adjustSize();
    if(pfailed) QMultiLineEdit::adjustSize();
}

bool PMultiLineEdit::close(bool b) {
    bool ret = PWidget_close(b);
    if(pfailed) ret = QMultiLineEdit::close(b);
    return ret;
}

void PMultiLineEdit::hide() {
    PWidget_hide();
    if(pfailed) QMultiLineEdit::hide();
}

void PMultiLineEdit::move(int x, int y) {
    PWidget_move(x, y);
    if(pfailed) QMultiLineEdit::move(x, y);
}

void PMultiLineEdit::resize(int w, int h) {
    PWidget_resize(w, h);
    if(pfailed) QMultiLineEdit::resize(w, h);
}

void PMultiLineEdit::setBackgroundColor(const QColor &c) {
    PWidget_setBackgroundColor(c);
    if(pfailed) QMultiLineEdit::setBackgroundColor(c);
}

void PMultiLineEdit::setBackgroundPixmap(const QPixmap &p) {
    PWidget_setBackgroundPixmap(p);
    if(pfailed) QMultiLineEdit::setBackgroundPixmap(p);
}

void PMultiLineEdit::setCursor(const QCursor &c) {
    PWidget_setCursor(c);
    if(pfailed) QMultiLineEdit::setCursor(c);
}

void PMultiLineEdit::setEnabled(bool b) {
    PWidget_setEnabled(b);
    if(pfailed) QMultiLineEdit::setEnabled(b);
}

void PMultiLineEdit::setFont(const QFont &f) {
    PWidget_setFont(f);
    if(pfailed) QMultiLineEdit::setFont(f);
}

void PMultiLineEdit::setGeometry(int x, int y, int w, int h) {
    PWidget_setGeometry(x, y, w, h);
    if(pfailed) QMultiLineEdit::setGeometry(x, y, w, h);
}

void PMultiLineEdit::setPalette(const QPalette &p) {
    PWidget_setPalette(p);
    if(pfailed) QMultiLineEdit::setPalette(p);
}

void PMultiLineEdit::setStyle(GUIStyle s) {
    PWidget_setStyle(s);
    if(pfailed) QMultiLineEdit::setStyle(s);
}

void PMultiLineEdit::show() {
    PWidget_show();
    if(pfailed) QMultiLineEdit::show();
}

QSize PMultiLineEdit::sizeHint() const {
    QSize ret = PWidget_sizeHint();
    if(pfailed) ret = QMultiLineEdit::sizeHint();
    return ret;
}

void PMultiLineEdit::closeEvent(QCloseEvent *event) {
    PWidget_closeEvent(event);
    if(pfailed) QMultiLineEdit::closeEvent(event);
}

void PMultiLineEdit::enterEvent(QEvent *event) {
    PWidget_enterEvent(event);
    if(pfailed) QMultiLineEdit::enterEvent(event);
}

void PMultiLineEdit::focusInEvent(QFocusEvent *event) {
    PWidget_focusInEvent(event);
    if(pfailed) QMultiLineEdit::focusInEvent(event);
}

void PMultiLineEdit::focusOutEvent(QFocusEvent *event) {
    PWidget_focusOutEvent(event);
    if(pfailed) QMultiLineEdit::focusOutEvent(event);
}

void PMultiLineEdit::keyPressEvent(QKeyEvent *event) {
    PWidget_keyPressEvent(event);
    if(pfailed) QMultiLineEdit::keyPressEvent(event);
}

void PMultiLineEdit::keyReleaseEvent(QKeyEvent *event) {
    PWidget_keyReleaseEvent(event);
    if(pfailed) QMultiLineEdit::keyReleaseEvent(event);
}

void PMultiLineEdit::leaveEvent(QEvent *event) {
    PWidget_leaveEvent(event);
    if(pfailed) QMultiLineEdit::leaveEvent(event);
}

void PMultiLineEdit::mouseDoubleClickEvent(QMouseEvent *event) {
    PWidget_mouseDoubleClickEvent(event);
    if(pfailed) QMultiLineEdit::mouseDoubleClickEvent(event);
}

void PMultiLineEdit::mouseMoveEvent(QMouseEvent *event) {
    PWidget_mouseMoveEvent(event);
    if(pfailed) QMultiLineEdit::mouseMoveEvent(event);
}

void PMultiLineEdit::mousePressEvent(QMouseEvent *event) {
    PWidget_mousePressEvent(event);
    if(pfailed) QMultiLineEdit::mousePressEvent(event);
}

void PMultiLineEdit::mouseReleaseEvent(QMouseEvent *event) {
    PWidget_mouseReleaseEvent(event);
    if(pfailed) QMultiLineEdit::mouseReleaseEvent(event);
}

void PMultiLineEdit::moveEvent(QMoveEvent *event) {
    PWidget_moveEvent(event);
    if(pfailed) QMultiLineEdit::moveEvent(event);
}

void PMultiLineEdit::paintEvent(QPaintEvent *event) {
    PWidget_paintEvent(event);
    if(pfailed) QMultiLineEdit::paintEvent(event);
}

void PMultiLineEdit::resizeEvent(QResizeEvent *event) {
    PWidget_resizeEvent(event);
    if(pfailed) QMultiLineEdit::resizeEvent(event);
}


void PMultiLineEdit::drawContents(QPainter *p) {
    PFrame_drawContents(p);
    if(pfailed) QMultiLineEdit::drawContents(p);
}

void PMultiLineEdit::drawFrame(QPainter *p) {
    PFrame_drawFrame(p);
    if(pfailed) QMultiLineEdit::drawFrame(p);
}

void PMultiLineEdit::frameChanged() {
    PFrame_frameChanged();
    if(pfailed) QMultiLineEdit::frameChanged();
}


int PMultiLineEdit::cellHeight(int row) {
    int ret = PTableView_cellHeight(row);
    if(pfailed) ret = QMultiLineEdit::cellHeight(row);
    return ret;
}

int PMultiLineEdit::cellWidth(int col) {
    int ret = PTableView_cellWidth(col);
    if(pfailed) ret = QMultiLineEdit::cellWidth(col);
    return ret;
}

void PMultiLineEdit::paintCell(QPainter *p, int row, int col) {
    PTableView_paintCell(p, row, col);
    if(pfailed) QMultiLineEdit::paintCell(p, row, col);
}

void PMultiLineEdit::setupPainter(QPainter *p) {
    PTableView_setupPainter(p);
    if(pfailed) QMultiLineEdit::setupPainter(p);
}

int PMultiLineEdit::totalHeight() {
    int ret = PTableView_totalHeight();
    if(pfailed) ret = QMultiLineEdit::totalHeight();
    return ret;
}

int PMultiLineEdit::totalWidth() {
    int ret = PTableView_totalWidth();
    if(pfailed) ret = QMultiLineEdit::totalWidth();
    return ret;
}


void PMultiLineEdit::insertAt(const char *s, int line, int col) {
    PMultiLineEdit_insertAt(s, line, col);
    if(pfailed) QMultiLineEdit::insertAt(s, line, col);
}

void PMultiLineEdit::insertLine(const char *s, int line) {
    PMultiLineEdit_insertLine(s, line);
    if(pfailed) QMultiLineEdit::insertLine(s, line);
}

void PMultiLineEdit::removeLine(int line) {
    PMultiLineEdit_removeLine(line);
    if(pfailed) QMultiLineEdit::removeLine(line);
}

void PMultiLineEdit::backspace() {
    PMultiLineEdit_backspace();
    if(pfailed) QMultiLineEdit::backspace();
}

void PMultiLineEdit::cursorDown(bool mark) {
    PMultiLineEdit_cursorDown(mark);
    if(pfailed) QMultiLineEdit::cursorDown(mark);
}

void PMultiLineEdit::cursorLeft(bool mark, bool wrap) {
    PMultiLineEdit_cursorLeft(mark, wrap);
    if(pfailed) QMultiLineEdit::cursorLeft(mark, wrap);
}

void PMultiLineEdit::cursorRight(bool mark, bool wrap) {
    PMultiLineEdit_cursorRight(mark, wrap);
    if(pfailed) QMultiLineEdit::cursorRight(mark, wrap);
}

void PMultiLineEdit::cursorUp(bool mark) {
    PMultiLineEdit_cursorUp(mark);
    if(pfailed) QMultiLineEdit::cursorUp(mark);
}

void PMultiLineEdit::del() {
    PMultiLineEdit_del();
    if(pfailed) QMultiLineEdit::del();
}

void PMultiLineEdit::end(bool mark) {
    PMultiLineEdit_end(mark);
    if(pfailed) QMultiLineEdit::end(mark);
}

void PMultiLineEdit::home(bool mark) {
    PMultiLineEdit_home(mark);
    if(pfailed) QMultiLineEdit::home(mark);
}

void PMultiLineEdit::insertChar(char c) {
    PMultiLineEdit_insertChar(c);
    if(pfailed) QMultiLineEdit::insertChar(c);
}

void PMultiLineEdit::killLine() {
    PMultiLineEdit_killLine();
    if(pfailed) QMultiLineEdit::killLine();
}

void PMultiLineEdit::newLine() {
    PMultiLineEdit_newLine();
    if(pfailed) QMultiLineEdit::newLine();
}

void PMultiLineEdit::pageUp(bool mark) {
    PMultiLineEdit_pageUp(mark);
    if(pfailed) QMultiLineEdit::pageUp(mark);
}

void PMultiLineEdit::pageDown(bool mark) {
    PMultiLineEdit_pageDown(mark);
    if(pfailed) QMultiLineEdit::pageDown(mark);
}


void PMultiLineEdit_virtualize::PMultiLineEdit_insertAt(const char *s,
							int line, int col) {
    SV *arg1 = s ? newSVpv((char *)s, 0) : &sv_undef;
    SV *arg2 = newSViv(line);
    SV *arg3 = newSViv(col);
    voidCall("insertAt", arg1, arg2, arg3);
    SvREFCNT_dec(arg3);
    SvREFCNT_dec(arg2);
    if(s) SvREFCNT_dec(arg1);
}

void PMultiLineEdit_virtualize::PMultiLineEdit_insertLine(const char *s,
							  int line) {
    SV *arg1 = s ? newSVpv((char *)s, 0) : &sv_undef;
    SV *arg2 = newSViv(line);
    voidCall("insertLine", arg1, arg2);
    SvREFCNT_dec(arg2);
    if(s) SvREFCNT_dec(arg1);
}

void PMultiLineEdit_virtualize::PMultiLineEdit_removeLine(int line) {
    SV *arg1 = newSViv(line);
    voidCall("removeLine", arg1);
    SvREFCNT_dec(arg1);
}

void PMultiLineEdit_virtualize::PMultiLineEdit_backspace() {
    voidCall("backspace");
}

void PMultiLineEdit_virtualize::PMultiLineEdit_cursorDown(bool mark) {
    voidCall("cursorDown", mark ? &sv_yes : &sv_no);
}

void PMultiLineEdit_virtualize::PMultiLineEdit_cursorLeft(bool mark,
							  bool wrap) {
    voidCall("cursorLeft", mark ? &sv_yes : &sv_no, wrap ? &sv_yes : &sv_no);
}

void PMultiLineEdit_virtualize::PMultiLineEdit_cursorRight(bool mark,
							   bool wrap) {
    voidCall("cursorRight", mark ? &sv_yes : &sv_no, wrap ? &sv_yes : &sv_no);
}

void PMultiLineEdit_virtualize::PMultiLineEdit_cursorUp(bool mark) {
    voidCall("cursorUp", mark ? &sv_yes : &sv_no);
}

void PMultiLineEdit_virtualize::PMultiLineEdit_del() {
    voidCall("del");
}

void PMultiLineEdit_virtualize::PMultiLineEdit_end(bool mark) {
    voidCall("end", mark ? &sv_yes : &sv_no);
}

void PMultiLineEdit_virtualize::PMultiLineEdit_home(bool mark) {
    voidCall("home", mark ? &sv_yes : &sv_no);
}

void PMultiLineEdit_virtualize::PMultiLineEdit_insertChar(char c) {
    char str[2];
    sprintf(str, "%c", c);
    SV *arg1 = newSVpv(str, 0);
    voidCall("insertChar", arg1);
    SvREFCNT_dec(arg1);
}

void PMultiLineEdit_virtualize::PMultiLineEdit_killLine() {
    voidCall("killLine");
}

void PMultiLineEdit_virtualize::PMultiLineEdit_newLine() {
    voidCall("newLine");
}

void PMultiLineEdit_virtualize::PMultiLineEdit_pageUp(bool mark) {
    voidCall("pageUp", mark ? &sv_yes : &sv_no);
}

void PMultiLineEdit_virtualize::PMultiLineEdit_pageDown(bool mark) {
    voidCall("pageDown", mark ? &sv_yes : &sv_no);
}
