/*
 * PerlQt interface to qmenubar.h
 *
 * Copyright (C) 1997, Ashley Winters <jql@accessone.com>
 *
 * You may distribute under the terms of the LGPL as specified in the
 * README file
 */

#include "pmenubar.h"
#include "pqt.h"

MODULE = QMenuBar		PACKAGE = QMenuBar

PROTOTYPES: ENABLE

PMenuBar *
PMenuBar::new(parent = 0, name = 0)
    QWidget *parent
    char *name


MODULE = QMenuBar	PACKAGE = QMenuBar	PREFIX = virtual_

void
pMenuBar::virtual_drawContents(p)
    QPainter *p

void
pMenuBar::virtual_hide()

bool
pMenuBar::virtual_eventFilter(obj, event)
    QObject *obj
    QEvent *event

void
pMenuBar::virtual_keyPressEvent(event)
    QKeyEvent *event

void
pMenuBar::virtual_menuContentsChanged()

void
pMenuBar::virtual_menuStateChanged()

void
pMenuBar::virtual_mouseMoveEvent(event)
    QMouseEvent *event

void
pMenuBar::virtual_mousePressEvent(event)
    QMouseEvent *event

void
pMenuBar::virtual_mouseReleaseEvent(event)
    QMouseEvent *event

void
pMenuBar::virtual_resizeEvent(event)
    QResizeEvent *event

void
pMenuBar::virtual_show()

void
pMenuBar::virtual_updateItem(id)
    int id