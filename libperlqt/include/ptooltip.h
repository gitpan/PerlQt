#ifndef PTOOLTIP_H
#define PTOOLTIP_H

/*
 * Declaration of the PToolTip and PToolTipGroup classes
 *
 * Copyright (C) 1997, Ashley Winters <jql@accessone.com>
 *
 * You may distribute under the terms of the LGPL as specified in the
 * README file
 */

#undef bool
#include "qtooltip.h"
//#include "pqt.h"
#include "pvirtual.h"

class PToolTipGroup : public QToolTipGroup, public virtualize {
public:
    PToolTipGroup(QObject *parent, const char *name = 0) :
	QToolTipGroup(parent, name) {}
};

class PToolTip : public QToolTip, public virtualize {
    PToolTip(QWidget *parent, QToolTipGroup *group = 0) :
	QToolTip(parent, group) {}
};

#endif  // PTOOLTIP_H
