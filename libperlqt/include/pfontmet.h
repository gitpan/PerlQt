#ifndef PFONTMET_H
#define PFONTMET_H

/*
 * Declaration of the PFontMetrics class
 *
 * Copyright (C) 1997, Ashley Winters <jql@accessone.com>
 *
 * You may distribute under the terms of the LGPL as specified in the
 * README file
 */

#undef bool
#include "qfontmet.h"
#include "pqt.h"

class PFontMetrics : public QFontMetrics {
public:
    PFontMetrics(const QFontMetrics &fontMet) : QFontMetrics(fontMet) {}
    PFontMetrics(const QFont &font) : QFontMetrics(font) {}
};

#endif  // PFONTMET_H
