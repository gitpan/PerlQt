#ifndef PMENUDTA_H
#define PMENUDTA_H

/*
 * Declaration of the PMenuData class
 *
 * Copyright (C) 1997, Ashley Winters <jql@accessone.com>
 *
 * You may distribute under the terms of the LGPL as specified in the
 * README file
 */

#undef bool
#include "qobject.h"		// Work-around for buglet
#include "qmenudta.h"
#include "qpopmenu.h"
#include "qmenubar.h"
#include "pvirtual.h"

#define QMenuData_virtual_functions					\
public:									\
    void updateItem(int);						\
protected:								\
    void menuContentsChanged();						\
    void menuDelPopup(QPopupMenu *);					\
    void menuInsPopup(QPopupMenu *);					\
    void menuStateChanged();

class PMenuData_virtualize : virtual public virtualize {
public:
    void PMenuData_updateItem(int);
protected:
    void PMenuData_menuContentsChanged();
    void PMenuData_menuDelPopup(QPopupMenu *);
    void PMenuData_menuInsPopup(QPopupMenu *);
    void PMenuData_menuStateChanged();
};

class PMenuData : public QMenuData, public PMenuData_virtualize {
    QMenuData_virtual_functions
public:
    PMenuData() {}
};

class pMenuData : public QMenuData {
public:
    void virtual_menuContentsChanged() { QMenuData::menuContentsChanged(); }
    void virtual_menuDelPopup(QPopupMenu *p) { QMenuData::menuDelPopup(p); }
    void virtual_menuInsPopup(QPopupMenu *p) { QMenuData::menuInsPopup(p); }
    void virtual_menuStateChanged() { QMenuData::menuStateChanged(); }
    void virtual_updateItem(int id) { QMenuData::updateItem(id); }
};

#endif  // PMENUDTA_H
