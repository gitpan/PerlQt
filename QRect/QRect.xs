/*
 * PerlQt interface to qrect.h
 *
 * Copyright (C) 1997, Ashley Winters <jql@accessone.com>
 *
 * You may distribute under the terms of the LGPL as specified in the
 * README file
 */

#include "prect.h"
#include "ppoint.h"
#include "psize.h"

MODULE = QRect		PACKAGE = QRect

PROTOTYPES: DISABLE

PRect *
PRect::new(...)
    CASE: items == 1
	CODE:
	RETVAL = new PRect();
	OUTPUT:
	RETVAL
    CASE: items == 2
	PREINIT:
	QRect *rect = pextract(QRect, 1);
	CODE:
	RETVAL = new PRect(*rect);
	OUTPUT:
	RETVAL
    CASE: items == 3 && sv_isobject(ST(1)) && sv_derived_from(ST(2), "QPoint")
	PREINIT:
	QPoint *topleft     = pextract(QPoint, 1);
	QPoint *bottomright = pextract(QPoint, 2);
	CODE:
	RETVAL = new PRect(*topleft, *bottomright);
	OUTPUT:
	RETVAL
    CASE: items == 3 && sv_isobject(ST(1)) && sv_derived_from(ST(2), "QSize")
	PREINIT:
	QPoint *topleft = pextract(QPoint, 1);
	QSize  *size    = pextract(QSize, 2);
	CODE:
	RETVAL = new PRect(*topleft, *size);
	OUTPUT:
	RETVAL
    CASE: items > 4
	PREINIT:
	int left = SvIV(ST(1));
	int top = SvIV(ST(2));
	int width = SvIV(ST(3));
	int height = SvIV(ST(4));
	CODE:
	RETVAL = new PRect(left, top, width, height);
	OUTPUT:
	RETVAL

void
QRect::DESTROY()
    CODE:
    if(want_destroy(ST(0)))
	delete THIS;

int
QRect::bottom()

PPoint *
QRect::bottomLeft()
    CODE:
    RETVAL = new PPoint(THIS->bottomLeft());
    OUTPUT:
    RETVAL

PPoint *
QRect::bottomRight()
    CODE:
    RETVAL = new PPoint(THIS->bottomRight());
    OUTPUT:
    RETVAL

PPoint *
QRect::center()
    CODE:
    RETVAL = new PPoint(THIS->center());
    OUTPUT:
    RETVAL

bool
QRect::contains(thing, proper = FALSE)
    CASE: sv_derived_from(ST(1), "QRect")
	QRect *thing
	bool proper
	CODE:
	RETVAL = THIS->contains(*thing, proper);
	OUTPUT:
	RETVAL
    CASE:
	QPoint *thing
	bool proper
	CODE:
	RETVAL = THIS->contains(*thing, proper);
	OUTPUT:
	RETVAL

void
QRect::coords(x1, y1, x2, y2)
    PREINIT:
    int x1, y1, x2, y2;
    CODE:
    THIS->rect(&x1, &y1, &x2, &y2);
    sv_setiv(ST(1), x1);
    sv_setiv(ST(2), y1);
    sv_setiv(ST(3), x2);
    sv_setiv(ST(4), y2);

int
QRect::height()

PRect *
QRect::intersect(r)
    QRect *r
    CODE:
    RETVAL = new PRect(THIS->intersect(*r));
    OUTPUT:
    RETVAL

bool
QRect::intersects(r)
    QRect *r
    CODE:
    RETVAL = THIS->intersects(*r);
    OUTPUT:
    RETVAL

bool
QRect::isEmpty()

bool
QRect::isNull()

bool
QRect::isValid()

int
QRect::left()

void
QRect::moveBottomLeft(p)
    QPoint *p
    CODE:
    THIS->moveBottomLeft(*p);

void
QRect::moveBottomRight(p)
    QPoint *p
    CODE:
    THIS->moveBottomRight(*p);

void
QRect::moveBy(dx, dy)
    int dx
    int dy

void
QRect::moveCenter(p)
    QPoint *p
    CODE:
    THIS->moveCenter(*p);

void
QRect::moveTopLeft(p)
    QPoint *p
    CODE:
    THIS->moveTopLeft(*p);

void
QRect::moveTopRight(p)
    QPoint *p
    CODE:
    THIS->moveTopRight(*p);

PRect *
QRect::normalize()
    CODE:
    RETVAL = new PRect(THIS->normalize());
    OUTPUT:
    RETVAL

void
QRect::rect(x, y, w, h)
    PREINIT:
    int x, y, w, h;
    CODE:
    THIS->rect(&x, &y, &w, &h);
    sv_setiv(ST(1), x);
    sv_setiv(ST(2), y);
    sv_setiv(ST(3), w);
    sv_setiv(ST(4), h);

int
QRect::right()

void
QRect::setBottom(pos)
    int pos

void
QRect::setCoords(x1, y1, x2, y2)
    int x1
    int y1
    int x2
    int y2

void
QRect::setHeight(h)
    int h

void
QRect::setLeft(pos)
    int pos

void
QRect::setRect(x, y, w, h)
    int x
    int y
    int w
    int h

void
QRect::setRight(pos)
    int pos

void
QRect::setSize(s)
    QSize *s
    CODE:
    THIS->setSize(*s);

void
QRect::setTop(pos)
    int pos

void
QRect::setWidth(w)
    int w

void
QRect::setX(x)
    int x

void
QRect::setY(y)
    int y

PSize *
QRect::size()
    CODE:
    RETVAL = new PSize(THIS->size());
    OUTPUT:
    RETVAL

int
QRect::top()

PPoint *
QRect::topLeft()
    CODE:
    RETVAL = new PPoint(THIS->topLeft());
    OUTPUT:
    RETVAL

PPoint *
QRect::topRight()
    CODE:
    RETVAL = new PPoint(THIS->topRight());
    OUTPUT:
    RETVAL

PRect *
QRect::unite(r)
    QRect *r
    CODE:
    RETVAL = new PRect(THIS->unite(*r));
    OUTPUT:
    RETVAL

int
QRect::width()

int
QRect::x()

int
QRect::y()


bool
QRect::beq(rect, misc)
    QRect *rect
    CODE:
    RETVAL = (*THIS == *rect);
    OUTPUT:
    RETVAL

bool
QRect::bne(rect, misc)
    QRect *rect
    CODE:
    RETVAL = (*THIS != *rect);
    OUTPUT:
    RETVAL
