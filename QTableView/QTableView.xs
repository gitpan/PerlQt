/*
 * PerlQt interface to qtablevw.h
 *
 * Copyright (C) 1997, Ashley Winters <jql@accessone.com>
 *
 * You may distribute under the terms of the LGPL as specified in the
 * README file
 */

#include "ptablevw.h"
#include "enum.h"

#define STORE_key(key) enumIV(hv, MSTR(key), Tbl_ ## key)

inline void init_enum() {
    HV *hv = perl_get_hv("QTableView::Tbl", TRUE | GV_ADDMULTI);

    STORE_key(vScrollBar);
    STORE_key(hScrollBar);
    STORE_key(autoVScrollBar);
    STORE_key(autoHScrollBar);
    STORE_key(autoScrollBars);
    STORE_key(clipCellPainting);
    STORE_key(cutCellsV);
    STORE_key(cutCellsH);
    STORE_key(cutCells);
    STORE_key(scrollLastHCell);
    STORE_key(scrollLastVCell);
    STORE_key(scrollLastCell);
    STORE_key(smoothHScrolling);
    STORE_key(smoothVScrolling);
    STORE_key(smoothScrolling);
    STORE_key(snapToHGrid);
    STORE_key(snapToVGrid);
    STORE_key(snapToGrid);
};

MODULE = QTableView		PACKAGE = QTableView

PROTOTYPES: ENABLE

BOOT:
    init_enum();

PTableView *
PTableView::new(parent = 0, name = 0, f = 0)
    QWidget *parent
    char *name
    WFlags f


MODULE = QTableView	PACKAGE = QTableView	PREFIX = virtual_

int
pTableView::virtual_cellHeight(row)
    int row

int
pTableView::virtual_cellWidth(col)
    int col

void
pTableView::virtual_paintEvent(event)
    QPaintEvent *event

void
pTableView::virtual_resizeEvent(event)
    QResizeEvent *event

void
pTableView::virtual_setBackgroundColor(color)
    QColor *color
    CODE:
    THIS->virtual_setBackgroundColor(*color);

void
pTableView::virtual_setPalette(palette)
    QPalette *palette
    CODE:
    THIS->virtual_setPalette(*palette);

void
pTableView::virtual_setupPainter(p)
    QPainter *p

void
pTableView::virtual_show()

int
pTableView::virtual_totalHeight()

int
pTableView::virtual_totalWidth()


MODULE = QTableView	PACKAGE = QTableView	PREFIX = protected_

bool
pTableView::protected_autoUpdate()

PRect *
pTableView::protected_cellUpdateRect()
    CODE:
    RETVAL = new PRect(THIS->protected_cellUpdateRect());
    OUTPUT:
    RETVAL

void
pTableView::protected_clearTableFlags(f = ~0)
    uint f

bool
pTableView::protected_colIsVisible(col)
    int col

bool
pTableView::protected_colXPos(col, yPos)
    int col
    int &yPos
    OUTPUT:
    yPos

int
pTableView::protected_findCol(xPos)
    int xPos

int
pTableView::protected_findRow(yPos)
    int yPos

const QScrollBar *
pTableView::protected_horizontalScrollBar()

int
pTableView::protected_lastColVisible()

int
pTableView::protected_lastRowVisible()

int
pTableView::protected_leftCell()

int
pTableView::protected_maxColOffset()

int
pTableView::protected_maxRowOffset()

int
pTableView::protected_maxViewX()

int
pTableView::protected_maxViewY()

int
pTableView::protected_maxXOffset()

int
pTableView::protected_maxYOffset()

int
pTableView::protected_numCols()

int
pTableView::protected_numRows()

bool
pTableView::protected_rowIsVisible(row)
    int row

bool
pTableView::protected_rowYPos(row, xPos)
    int row
    int &xPos
    OUTPUT:
    xPos

void
pTableView::protected_scroll(x, y)
    int x
    int y

void
pTableView::protected_setAutoUpdate(b)
    bool b

void
pTableView::protected_setCellHeight(h)
    int h

void
pTableView::protected_setCellWidth(w)
    int w

void
pTableView::protected_setLeftCell(col)
    int col

void
pTableView::protected_setNumCols(cols)
    int cols

void
pTableView::protected_setNumRows(rows)
    int rows

void
pTableView::protected_setOffset(x, y, updateScrBars = TRUE)
    int x
    int y
    bool updateScrBars

void
pTableView::protected_setTableFlags(f)
    uint f

void
pTableView::protected_setTopCell(row)
    int row

void
pTableView::protected_setTopLeftCell(row, col)
    int row
    int col

void
pTableView::protected_setXOffset(x)
    int x

void
pTableView::protected_setYOffset(y)
    int y

uint
pTableView::protected_tableFlags()

bool
pTableView::protected_testTableFlags(f)
    uint f

int
pTableView::protected_topCell()

void
pTableView::protected_updateCell(row, column, erase = TRUE)
    int row
    int column
    bool erase

void
pTableView::protected_updateScrollBars()

const QScrollBar *
pTableView::protected_verticalScrollBar()

int
pTableView::protected_viewHeight()

int
pTableView::protected_viewWidth()

PRect *
pTableView::protected_viewRect()
    CODE:
    RETVAL = new PRect(THIS->protected_viewRect());
    OUTPUT:
    RETVAL

int
pTableView::protected_xOffset()

int
pTableView::protected_yOffset()
