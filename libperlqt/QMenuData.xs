/*
 * PMenuData definitions.
 *
 * Copyright (C) 1997, Ashley Winters <jql@accessone.com>
 *
 * You may distribute under the terms of the LGPL as specified in the
 * README file
 */

#include "pmenudta.h"

void PMenuData::updateItem(int id) {
    PMenuData_updateItem(id);
    if(pfailed) QMenuData::updateItem(id);
}

void PMenuData::menuContentsChanged() {
    PMenuData_menuContentsChanged();
    if(pfailed) QMenuData::menuContentsChanged();
}

void PMenuData::menuDelPopup(QPopupMenu *popmenu) {
    PMenuData_menuDelPopup(popmenu);
    if(pfailed) QMenuData::menuDelPopup(popmenu);
}

void PMenuData::menuInsPopup(QPopupMenu *popmenu) {
    PMenuData_menuInsPopup(popmenu);
    if(pfailed) QMenuData::menuInsPopup(popmenu);
}

void PMenuData::menuStateChanged() {
    PMenuData_menuStateChanged();
    if(pfailed) QMenuData::menuStateChanged();
}


void PMenuData_virtualize::PMenuData_updateItem(int id) {
    SV *arg1 = newSViv(id);
    voidCall("updateItem", arg1);
    SvREFCNT_dec(arg1);
}

void PMenuData_virtualize::PMenuData_menuContentsChanged() {
    voidCall("menuContentsChanged");
}

void PMenuData_virtualize::PMenuData_menuDelPopup(QPopupMenu *popmenu) {
    voidCallObj("menuDelPopup", popmenu, "QPopupMenu");
}

void PMenuData_virtualize::PMenuData_menuInsPopup(QPopupMenu *popmenu) {
    voidCallObj("menuInsPopup", popmenu, "QPopupMenu");
}

void PMenuData_virtualize::PMenuData_menuStateChanged() {
    voidCall("menuStateChanged");
}
