#ifndef PTABLEVW_H
#define PTABLEVW_H

/*
 * Declaration of the PTableView class
 *
 * Copyright (C) 1997, Ashley Winters <jql@accessone.com>
 *
 * You may distribute under the terms of the LGPL as specified in the
 * README file
 */

#undef bool
#include "qtablevw.h"
#include "prect.h"
#include "virtual.h"

class PTableView : public QTableView, public PTableView_virtualize {
    QTableView_virtual_functions
public:
    PTableView(QWidget *parent = 0, const char *name = 0, WFlags f = 0) :
	QTableView(parent, name, f) {}
};

class pTableView : public QTableView {
public:
    int virtual_cellHeight(int row) { return QTableView::cellHeight(row); }
    int virtual_cellWidth(int col) { return QTableView::cellWidth(col); }
    void virtual_paintEvent(QPaintEvent *e) { QTableView::paintEvent(e); }
    void virtual_resizeEvent(QResizeEvent *e) { QTableView::resizeEvent(e); }
    void virtual_setBackgroundColor(const QColor &c) {
	QTableView::setBackgroundColor(c);
    }
    void virtual_setPalette(const QPalette &p) { QTableView::setPalette(p); }
    void virtual_setupPainter(QPainter *p) { QTableView::setupPainter(p); }
    void virtual_show() { QTableView::show(); }
    int virtual_totalHeight() { return QTableView::totalHeight(); }
    int virtual_totalWidth() { return QTableView::totalWidth(); }

    bool protected_autoUpdate() const { return QTableView::autoUpdate(); }
    QRect protected_cellUpdateRect() const {
	return QTableView::cellUpdateRect();
    }
    void protected_clearTableFlags(uint f = ~0) {
	QTableView::clearTableFlags(f);
    }
    bool protected_colIsVisible(int col) {
	return QTableView::colIsVisible(col);
    }
    bool protected_colXPos(int col, int *yPos) const {
	return QTableView::colXPos(col, yPos);
    }
    int protected_findCol(int xPos) const {
	return QTableView::findCol(xPos);
    }
    int protected_findRow(int yPos) const {
	return QTableView::findRow(yPos);
    }
    const QScrollBar *protected_horizontalScrollBar() const {
	return QTableView::horizontalScrollBar();
    }
    int protected_lastColVisible() const {
	return QTableView::lastColVisible();
    }
    int protected_lastRowVisible() const {
	return QTableView::lastRowVisible();
    }
    int protected_leftCell() const { return QTableView::leftCell(); }
    int protected_maxColOffset() { return QTableView::maxColOffset(); }
    int protected_maxRowOffset() { return QTableView::maxRowOffset(); }
    int protected_maxViewX() const { return QTableView::maxViewX(); }
    int protected_maxViewY() const { return QTableView::maxViewY(); }
    int protected_maxXOffset() { return QTableView::maxXOffset(); }
    int protected_maxYOffset() { return QTableView::maxYOffset(); }
    int protected_numCols() const { return QTableView::numCols(); }
    int protected_numRows() const { return QTableView::numRows(); }
    bool protected_rowIsVisible(int row) {
	return QTableView::rowIsVisible(row);
    }
    bool protected_rowYPos(int row, int *xPos) const {
	return QTableView::rowYPos(row, xPos);
    }
    void protected_scroll(int x, int y) { QTableView::scroll(x, y); }
    void protected_setAutoUpdate(bool b) { QTableView::setAutoUpdate(b); }
    void protected_setCellHeight(int h) { QTableView::setCellHeight(h); }
    void protected_setCellWidth(int w) { QTableView::setCellWidth(w); }
    void protected_setLeftCell(int col) { QTableView::setLeftCell(col); }
    void protected_setNumCols(int cols) { QTableView::setNumCols(cols); }
    void protected_setNumRows(int rows) { QTableView::setNumRows(rows); }
    void protected_setOffset(int x, int y, bool updateScrBars = TRUE) {
	QTableView::setOffset(x, y, updateScrBars);
    }
    void protected_setTableFlags(uint f) { QTableView::setTableFlags(f); }
    void protected_setTopCell(int row) { QTableView::setTopCell(row); }
    void protected_setTopLeftCell(int row, int col) {
	QTableView::setTopLeftCell(row, col);
    }
    void protected_setXOffset(int x) { QTableView::setXOffset(x); }
    void protected_setYOffset(int y) { QTableView::setYOffset(y); }
    uint protected_tableFlags() const { return QTableView::tableFlags(); }
    bool protected_testTableFlags(uint f) const {
	return QTableView::testTableFlags(f);
    }
    int protected_topCell() const { return QTableView::topCell(); }
    void protected_updateCell(int row, int column, bool erase = TRUE) {
	QTableView::updateCell(row, column, erase);
    }
    void protected_updateScrollBars() { QTableView::updateScrollBars(); }
    const QScrollBar *protected_verticalScrollBar() const {
	return QTableView::verticalScrollBar();
    }
    int protected_viewHeight() const { return QTableView::viewHeight(); }
    int protected_viewWidth() const { return QTableView::viewWidth(); }
    QRect protected_viewRect() const { return QTableView::viewRect(); }
    int protected_xOffset() const { return QTableView::xOffset(); }
    int protected_yOffset() const { return QTableView::yOffset(); }
};

#endif  // PTABLEVW_H
