/*
 * PerlQt interface to qlistbox.h
 *
 * Copyright (C) 1997, Ashley Winters <jql@accessone.com>
 *
 * You may distribute under the terms of the LGPL as specified in the
 * README file
 */

#include "plistbox.h"
#include "ppixmap.h"

MODULE = QListBox		PACKAGE = QListBoxItem

PROTOTYPES: DISABLE

int
QListBoxItem::height(listbox)
    QListBox *listbox

PPixmap *
QListBoxItem::pixmap()
    CODE:
    RETVAL = new PPixmap(*(THIS->pixmap()));
    OUTPUT:
    RETVAL

const char *
QListBoxItem::text()

int
QListBoxItem::width(listbox)
    QListBox *listbox


MODULE = QListBox		PACKAGE = QListBoxPixmap

PListBoxPixmap *
PListBoxPixmap::new(pixmap)
    QPixmap *pixmap
    CODE:
    RETVAL = new PListBoxPixmap(*pixmap);
    OUTPUT:
    RETVAL

void
QListBoxPixmap::DESTROY()
    CODE:
    if(want_destroy(ST(0)))
	delete THIS;


MODULE = QListBox		PACKAGE = QListBoxText

PListBoxText *
PListBoxText::new(text)
    char *text

void
QListBoxText::DESTROY()
    CODE:
    if(want_destroy(ST(0)))
	delete THIS;


MODULE = QListBox		PACKAGE = QListBox

PListBox *
PListBox::new(parent = 0, name = 0, f = 0)
    pWidget *parent
    pChar *name
    WFlags f

void
QListBox::DESTROY()
    CODE:
    if(want_destroy(ST(0)))
	delete THIS;

bool
QListBox::autoBottomScrollBar()

bool
QListBox::autoScroll()

bool
QListBox::autoScrollBar()

bool
QListBox::autoUpdate()

bool
QListBox::bottomScrollBar()

void
QListBox::centerCurrentItem()

void
QListBox::changeItem(thing, index)
    CASE: !sv_isobject(ST(1))
	char *thing
	int index
    CASE: sv_derived_from(ST(1), "QPixmap")
	QPixmap *thing
	int index
	CODE:
	THIS->changeItem(*thing, index);
    CASE:
	QListBoxItem *thing
	int index

void
QListBox::clear()

uint
QListBox::count()

int
QListBox::currentItem()

bool
QListBox::dragSelect()

void
QListBox::insertItem(thing, index = -1)
    CASE: !sv_isobject(ST(1))
	char *thing
	int index
    CASE: sv_derived_from(ST(1), "QPixmap")
        QPixmap *thing
        int index
        CODE:
        THIS->insertItem(*thing, index);
    CASE:
	QListBoxItem *thing
	int index

void
QListBox::insertStrList(index, str1, ...)
    int index
    PREINIT:
    char **strings;
    CODE:
    New(123, strings, items-2, char *);
    for(int i = 2; i < items; i++)
        strings[i-2] = SvPV(ST(i), na);
    THIS->insertStrList((const char **)strings, (int)items-2, (int)index);
    Safefree(strings);

void
QListBox::inSort(thing)
    CASE: sv_isobject(ST(1))
	QListBoxItem *thing
    CASE:
	char *thing

int
QListBox::itemHeight(...)
    CASE: items > 1
	PREINIT:
	int index = SvIV(ST(1));
	CODE:
	RETVAL = THIS->itemHeight(index);
	OUTPUT:
	RETVAL
    CASE:

long
QListBox::maxItemWidth()
	
int
QListBox::numItemsVisible()

PPixmap *
QListBox::pixmap(index)
    int index
    PREINIT:
    const QPixmap *pixmap;
    CODE:
    pixmap = THIS->pixmap(index);
    if(!pixmap) XSRETURN_UNDEF;		// Fix the others that don't do this
    RETVAL = new PPixmap(*pixmap);
    OUTPUT:
    RETVAL

void
QListBox::removeItem(index)
    int index

bool
QListBox::scrollBar()

void
QListBox::setAutoBottomScrollBar(b)
    bool b

void
QListBox::setAutoScroll(b)
    bool b

void
QListBox::setAutoScrollBar(b)
    bool b

void
QListBox::setAutoUpdate(b)
    bool b

void
QListBox::setBottomScrollBar(b)
    bool b

void
QListBox::setCurrentItem(index)
    int index

void
QListBox::setDragSelect(b)
    bool b

void
QListBox::setScrollBar(b)
    bool b

void
QListBox::setSmoothScrolling(b)
    bool b

void
QListBox::setTopItem(index)
    int index

bool
QListBox::smoothScrolling()

const char *
QListBox::text(index)
    int index

int
QListBox::topItem()


MODULE = QListBox	PACKAGE = QListBox	PREFIX = virtual_

int
pListBox::virtual_cellHeight(i = 0)
    int i

void
pListBox::virtual_focusInEvent(event)
    QFocusEvent *event

void
pListBox::virtual_keyPressEvent(event)
    QKeyEvent *event

void
pListBox::virtual_mouseDoubleClickEvent(event)
    QMouseEvent *event

void
pListBox::virtual_mouseMoveEvent(event)
    QMouseEvent *event

void
pListBox::virtual_mousePressEvent(event)
    QMouseEvent *event

void
pListBox::virtual_mouseReleaseEvent(event)
    QMouseEvent *event

void
pListBox::virtual_paintCell(p, row, col)
    QPainter *p
    int row
    int col

void
pListBox::virtual_resizeEvent(event)
    QResizeEvent *event

void
pListBox::virtual_setFont(font)
    QFont *font
    CODE:
    THIS->virtual_setFont(*font);

void
pListBox::virtual_timerEvent(event)
    QTimerEvent *event


MODULE = QListBox	PACKAGE = QListBox	PREFIX = protected_

void
pListBox::protected_clearList()

int
pListBox::protected_findItem(yPos)
    int yPos

QListBoxItem *
pListBox::protected_item(index)
    int index

bool
pListBox::protected_itemVisible(index)
    int index

bool
pListBox::protected_itemYPos(index, yPos)
    int index
    int &yPos
    OUTPUT:
    yPos

void
pListBox::protected_updateCellWidth()

void
pListBox::protected_updateItem(index, clear = TRUE)
    int index
    bool clear
