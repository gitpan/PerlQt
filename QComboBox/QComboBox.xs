/*
 * PerlQt interface to qcombo.h
 *
 * Copyright (C) 1997, Ashley Winters <jql@accessone.com>
 *
 * You may distribute under the terms of the LGPL as specified in the
 * README file
 */

#include "pcombo.h"
#include "ppixmap.h"
#include "psize.h"
#include "penum.h"

#define STORE_key(key) enumIV(hv, MSTR(key), QComboBox::key)

inline void init_enum() {
    HV *hv = perl_get_hv("QComboBox::Policy", TRUE | GV_ADDMULTI);

    enumIV(hv, "None",    QComboBox::NoInsertion  );
    enumIV(hv, "Top",     QComboBox::AtTop	  );
    enumIV(hv, "Bottom",  QComboBox::AtBottom	  );
    enumIV(hv, "Current", QComboBox::AtCurrent	  );
    enumIV(hv, "Before",  QComboBox::BeforeCurrent);
    enumIV(hv, "After",   QComboBox::AfterCurrent );
}

MODULE = QComboBox		PACKAGE = QComboBox

PROTOTYPES: DISABLE

BOOT:
    init_enum();

PComboBox *
PComboBox::new(...)
    CASE: items == 1
	CODE:
	RETVAL = new PComboBox();
	OUTPUT:
	RETVAL
    CASE: sv_isobject(ST(1))
	PREINIT:
	QWidget *parent = pextract(QWidget, 1);
	pChar *name = (items > 2 && SvOK(ST(2))) ? SvPV(ST(2), na) : 0;
	CODE:
	RETVAL = new PComboBox(parent, name);
	OUTPUT:
	RETVAL
    CASE:
	PREINIT:
	bool rw = SvTRUE(ST(1)) ? TRUE : FALSE;
	pWidget *parent = (items > 2) ? pextract(pWidget, 2) : 0;
	pChar *name = (items > 3 && SvOK(ST(3))) ? SvPV(ST(3), na) : 0;
	CODE:
	RETVAL = new PComboBox(rw, parent, name);
	OUTPUT:
	RETVAL

void
QComboBox::DESTROY()
    CODE:
    if(want_destroy(ST(0)))
	delete THIS;

bool
QComboBox::autoResize()

void
QComboBox::changeItem(thing, index)
    CASE: sv_isobject(ST(1))
	QPixmap *thing
	int index
	CODE:
	THIS->changeItem(*thing, index);
    CASE:
	char *thing
	int index

void
QComboBox::clear()

int
QComboBox::count()

int
QComboBox::currentItem()

const char *
QComboBox::currentText()

QComboBox::Policy
QComboBox::insertionPolicy()

void
QComboBox::insertItem(thing, index = -1)
    CASE: sv_isobject(ST(1))
	QPixmap *thing
	int index
	CODE:
	THIS->insertItem(*thing, index);
    CASE:
	char *thing
	int index

void
QComboBox::insertStrList(index, str1, ...)
    int index
    PREINIT:
    char **strings;
    CODE:
    New(123, strings, items-2, char *);
    for(int i = 2; i < items; i++)
	strings[i-2] = SvPV(ST(i), na);
    THIS->insertStrList((const char **)strings, (int)items-2, (int)index);
    Safefree(strings);

int
QComboBox::maxCount()

PPixmap *
QComboBox::pixmap(index)
    int index
    CODE:
    RETVAL = new PPixmap(*(THIS->pixmap(index)));
    OUTPUT:
    RETVAL

void
QComboBox::removeItem(index)
    int index

void
QComboBox::setAutoResize(b)
    bool b

void
QComboBox::setCurrentItem(index)
    int index

void
QComboBox::setInsertionPolicy(policy)
    QComboBox::Policy policy

void
QComboBox::setMaxCount(count)
    int count

void
QComboBox::setSizeLimit(limit)
    int limit

int
QComboBox::sizeLimit()

const char *
QComboBox::text(index)
    int index


MODULE = QComboBox	PACKAGE = QComboBox	PREFIX = virtual_

void
pComboBox::virtual_keyPressEvent(event)
    QKeyEvent *event

void
pComboBox::virtual_mouseDoubleClickEvent(event)
    QMouseEvent *event

void
pComboBox::virtual_mouseMoveEvent(event)
    QMouseEvent *event

void
pComboBox::virtual_mousePressEvent(event)
    QMouseEvent *event

void
pComboBox::virtual_mouseReleaseEvent(event)
    QMouseEvent *event

void
pComboBox::virtual_paintEvent(event)
    QPaintEvent *event

void
pComboBox::virtual_resizeEvent(event)
    QResizeEvent *event

void
pComboBox::virtual_setBackgroundColor(color)
    QColor *color
    CODE:
    THIS->virtual_setBackgroundColor(*color);

void
pComboBox::virtual_setEnabled(b)
    bool b

void
pComboBox::virtual_setFont(font)
    QFont *font
    CODE:
    THIS->virtual_setFont(*font);

void
pComboBox::virtual_setPalette(palette)
    QPalette *palette
    CODE:
    THIS->virtual_setPalette(*palette);

QSize *
pComboBox::virtual_sizeHint()
    CODE:
    RETVAL = new PSize(THIS->virtual_sizeHint());
    OUTPUT:
    RETVAL


MODULE = QComboBox	PACKAGE = QComboBox	PREFIX = protected_

void
pComboBox::protected_popup()
