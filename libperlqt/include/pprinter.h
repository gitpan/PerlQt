#ifndef PPRINTER_H
#define PPRINTER_H

/*
 * Declaration of the PPrinter class
 *
 * Copyright (C) 1997, Ashley Winters <jql@accessone.com>
 *
 * You may distribute under the terms of the LGPL as specified in the
 * README file
 */

#undef bool
#include "qprinter.h"
#include "pqt.h"

class PPrinter : public QPrinter {
public:
    PPrinter() {}
};

typedef QPrinter::Orientation QPrinter__Orientation;
typedef QPrinter::PageSize QPrinter__PageSize;

#endif  // PPRINTER_H
