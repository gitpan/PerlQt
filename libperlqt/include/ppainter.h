#ifndef PPAINTER_H
#define PPAINTER_H

/*
 * Declaration of the PPainter class
 *
 * Copyright (C) 1997, Ashley Winters <jql@accessone.com>
 *
 * You may distribute under the terms of the LGPL as specified in the
 * README file
 */

#undef bool
#include "qpainter.h"
#include "pqt.h"

class PPainter : public QPainter {
public:
    PPainter() {}
    PPainter(QPaintDevice *d) : QPainter(d) {}
};

#endif  // PPAINTER_H
