#ifndef PMLINED_H
#define PMLINED_H

/*
 * Declaration of the PMultiLineEdit class
 *
 * Copyright (C) 1997, Ashley Winters <jql@accessone.com>
 *
 * You may distribute under the terms of the LGPL as specified in the
 * README file
 */

#undef bool
#include "qmlined.h"
#include "ptablevw.h"

#define QMultiLineEdit_virtual_functions				\
    QTableView_virtual_functions					\
public:									\
    void insertAt(const char *, int, int);				\
    void insertLine(const char *, int = -1);				\
    void removeLine(int);						\
protected:								\
    void backspace();							\
    void cursorDown(bool = FALSE);					\
    void cursorLeft(bool = FALSE, bool = TRUE);				\
    void cursorRight(bool = FALSE, bool = TRUE);			\
    void cursorUp(bool = FALSE);					\
    void del();								\
    void end(bool = FALSE);						\
    void home(bool = FALSE);						\
    void insertChar(char);						\
    void killLine();							\
    void newLine();							\
    void pageUp(bool = FALSE);						\
    void pageDown(bool = FALSE);

class PMultiLineEdit_virtualize : public PTableView_virtualize {
public:
    void PMultiLineEdit_insertAt(const char *, int, int);
    void PMultiLineEdit_insertLine(const char *, int = -1);
    void PMultiLineEdit_removeLine(int);
protected:
    void PMultiLineEdit_backspace();
    void PMultiLineEdit_cursorDown(bool = FALSE);
    void PMultiLineEdit_cursorLeft(bool = FALSE, bool = TRUE);
    void PMultiLineEdit_cursorRight(bool = FALSE, bool = TRUE);
    void PMultiLineEdit_cursorUp(bool = FALSE);
    void PMultiLineEdit_del();
    void PMultiLineEdit_end(bool = FALSE);
    void PMultiLineEdit_home(bool = FALSE);
    void PMultiLineEdit_insertChar(char);
    void PMultiLineEdit_killLine();
    void PMultiLineEdit_newLine();
    void PMultiLineEdit_pageUp(bool = FALSE);
    void PMultiLineEdit_pageDown(bool = FALSE);
};

class PMultiLineEdit : public QMultiLineEdit, public PMultiLineEdit_virtualize {
    QMultiLineEdit_virtual_functions
public:
    PMultiLineEdit(QWidget *parent = 0, const char *name = 0) :
	QMultiLineEdit(parent, name) {}
};

class pMultiLineEdit : public QMultiLineEdit {
public:
    void virtual_backspace() { QMultiLineEdit::backspace(); }
    void virtual_cursorDown(bool m = FALSE) { QMultiLineEdit::cursorDown(m); }
    void virtual_cursorLeft(bool m = FALSE, bool w = TRUE) {
	QMultiLineEdit::cursorLeft(m, w);
    }
    void virtual_cursorRight(bool m = FALSE, bool w = TRUE) {
	QMultiLineEdit::cursorRight(m, w);
    }
    void virtual_cursorUp(bool m = FALSE) { QMultiLineEdit::cursorUp(m); }
    void virtual_del() { QMultiLineEdit::del(); }
    void virtual_end(bool m = FALSE) { QMultiLineEdit::end(m); }
    void virtual_focusInEvent(QFocusEvent *e) {
	QMultiLineEdit::focusInEvent(e);
    }
    void virtual_focusOutEvent(QFocusEvent *e) {
	QMultiLineEdit::focusOutEvent(e);
    }
    void virtual_home(bool m = FALSE) { QMultiLineEdit::home(m); }
    void virtual_insertAt(const char *s, int l, int c) {
	QMultiLineEdit::insertAt(s, l, c);
    }
    void virtual_insertChar(char *c) { QMultiLineEdit::insertChar(*c); }
    void virtual_insertLine(const char *s, int l = -1) {
	QMultiLineEdit::insertLine(s, l);
    }
    void virtual_keyPressEvent(QKeyEvent *e) {
	QMultiLineEdit::keyPressEvent(e);
    }
    void virtual_killLine() { QMultiLineEdit::killLine(); }
    void virtual_mouseDoubleClickEvent(QMouseEvent *e) {
	QMultiLineEdit::mouseDoubleClickEvent(e);
    }
    void virtual_mouseMoveEvent(QMouseEvent *e) {
	QMultiLineEdit::mouseMoveEvent(e);
    }
    void virtual_mousePressEvent(QMouseEvent *e) {
	QMultiLineEdit::mousePressEvent(e);
    }
    void virtual_mouseReleaseEvent(QMouseEvent *e) {
	QMultiLineEdit::mouseReleaseEvent(e);
    }
    void virtual_newLine() { QMultiLineEdit::newLine(); }
    void virtual_pageUp(bool m = FALSE) { QMultiLineEdit::pageUp(m); }
    void virtual_pageDown(bool m = FALSE) { QMultiLineEdit::pageDown(m); }
    void virtual_paintCell(QPainter *p, int row, int col) {
	QMultiLineEdit::paintCell(p, row, col);
    }
    void virtual_removeLine(int line) { QMultiLineEdit::removeLine(line); }
    void virtual_timerEvent(QTimerEvent *e) { QMultiLineEdit::timerEvent(e); }

    const char *protected_getString(int row) {
	QString *s = QMultiLineEdit::getString(row);
	return *s;
    }
    bool protected_hasMarkedText() const {
	return QMultiLineEdit::hasMarkedText();
    }
    int protected_lineLength(int row) { QMultiLineEdit::lineLength(row); }
    const char *protected_markedText() const {
	return QMultiLineEdit::markedText();
    }
    int protected_textWidth(int line) {
	return QMultiLineEdit::textWidth(line);
    }
    int protected_textWidth(const char *s) {
	QString str(s);
	return QMultiLineEdit::textWidth(&str);
    }
};

#endif  // PMLINED_H
