/*
 * PerlQt interface to qpopmenu.h
 *
 * Copyright (C) 1997, Ashley Winters <jql@accessone.com>
 *
 * You may distribute under the terms of the LGPL as specified in the
 * README file
 */

#include "ppopmenu.h"
#include "pwidget.h"
#include "pqt.h"

MODULE = QPopupMenu		PACKAGE = QPopupMenu

PROTOTYPES: ENABLE

PPopupMenu *
PPopupMenu::new(parent = 0, name = 0)
    pWidget *parent
    pChar *name

bool
QPopupMenu::isCheckable()

void
QPopupMenu::popup(pos, indexAtPoint = 0)
    QPoint *pos
    int indexAtPoint
    CODE:
    THIS->popup(*pos, indexAtPoint);

void
QPopupMenu::setCheckable(checkable)
    bool checkable


MODULE = QPopupMenu	PACKAGE = QPopupMenu	PREFIX = virtual_

void
pPopupMenu::virtual_cellHeight(row)
    int row

void
pPopupMenu::virtual_cellWidth(col)
    int col

void
pPopupMenu::virtual_hide()

void
pPopupMenu::virtual_keyPressEvent(event)
    QKeyEvent *event

void
pPopupMenu::virtual_mouseMoveEvent(event)
    QMouseEvent *event

void
pPopupMenu::virtual_mousePressEvent(event)
    QMouseEvent *event

void
pPopupMenu::virtual_mouseReleaseEvent(event)
    QMouseEvent *event

void
pPopupMenu::virtual_paintCell(p, row, col)
    QPainter *p
    int row
    int col

void
pPopupMenu::virtual_paintEvent(event)
    QPaintEvent *event

void
pPopupMenu::virtual_setFont(font)
    QFont *font
    CODE:
    THIS->virtual_setFont(*font);

void
pPopupMenu::virtual_show()

void
pPopupMenu::virtual_timerEvent(event)
    QTimerEvent *event

void
pPopupMenu::virtual_updateItem(id)
    int id
