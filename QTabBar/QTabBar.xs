/*
 * PerlQt interface to qtabbar.h
 *
 * Copyright (C) 1997, Ashley Winters <jql@accessone.com>
 *
 * You may distribute under the terms of the LGPL as specified in the
 * README file
 */

#include "ptabbar.h"

static const char *QTab_keys[] = {
    "label",
    "r",
    "enabled",
    "id",
    NULL
};

MODULE = QTabBar		PACKAGE = QTabBar

PROTOTYPES: DISABLE

PTabBar *
PTabBar::new(parent, name)
    QWidget *parent
    char *name

void
QTabBar::DESTROY()
    CODE:
    if(want_destroy(ST(0)))
	delete THIS;

int
QTabBar::currentTab()

bool
QTabBar::isTabEnabled(id)
    int id

int
QTabBar::keyboardFocusTab()

void
QTabBar::setTabEnabled(id, enable)
    int id
    bool enable


MODULE = QTabBar	PACKAGE = QTabBar	PREFIX = virtual_

int
pTabBar::virtual_addTab(tab)
    QTab *tab

void
pTabBar::virtual_keyPressEvent(event)
    QKeyEvent *event

void
pTabBar::virtual_mousePressEvent(event)
    QMouseEvent *event

void
pTabBar::virtual_mouseReleaseEvent(event)
    QMouseEvent *event

void
pTabBar::virtual_paint(p, tab, b)
    QPainter *p
    QTab *tab
    bool b

void
pTabBar::virtual_paintEvent(event)
    QPaintEvent *event

QTab *
pTabBar::virtual_selectTab(p)
    QPoint *p
    CODE:
    RETVAL = THIS->virtual_selectTab(*p);
    OUTPUT:
    RETVAL


MODULE = QTabBar		PACKAGE = QTab

void
setup(object)
    SV *object
    CODE:
    HV *hash = (HV *)rv_check(object);
    QTab *tab = new QTab;
    safe_hv_store(hash, "THIS", newSViv((IV)tab));

void
CLEAR(...)
    CODE:

void
DELETE(...)
    CODE:

bool
QTab::EXISTS(key)
    char *key
    CODE:
    RETVAL = FALSE;
    for(const char **ptr = QTab_keys; *ptr; ptr++)
	if(strEQ(key, *ptr)) { RETVAL = TRUE; break; }
    OUTPUT:
    RETVAL

SV *
QTab::FETCH(key)
    char *key
    CODE:
    if(strEQ(key, "label"))
	RETVAL = ((const char *)THIS->label) ?
	    newSVpv((char *)(const char *)THIS->label, 0) : &sv_undef;
    else if(strEQ(key, "r"))
	RETVAL = objectify_ptr(&(THIS->r), "QRect");
    else if(strEQ(key, "enabled"))
	RETVAL = (THIS->enabled) ? &sv_yes : &sv_no;
    else if(strEQ(key, "id"))
	RETVAL = newSViv(THIS->id);
    else RETVAL = &sv_undef;
    OUTPUT:
    RETVAL

void
QTab::FIRSTKEY(...)
    CODE:
    XSRETURN_UNDEF;

void
QTab::NEXTKEY(...)
    CODE:
    XSRETURN_UNDEF;

void
QTab::STORE(key, value)
    char *key
    SV *value
    CODE:
    if(strEQ(key, "label"))
	THIS->label = SvPV(value, na);
    else if(strEQ(key, "r"))
	THIS->r = *(QRect *)extract_ptr(value, "QRect");
    else if(strEQ(key, "enabled"))
	THIS->enabled = SvTRUE(value) ? TRUE : FALSE;
    else if(strEQ(key, "id"))
	THIS->id = SvIV(value);
