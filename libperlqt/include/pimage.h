#ifndef PIMAGE_H
#define PIMAGE_H

/*
 * Declaration of the PObject class
 *
 * Copyright (C) 1997, Ashley Winters <jql@accessone.com>
 *
 * You may distribute under the terms of the LGPL as specified in the
 * README file
 */

#undef bool
#include "qimage.h"
#include "prect.h"
#include "psize.h"
#include "pqt.h"

class PImage : public QImage {
public:
    PImage(const QImage &image) { *(QImage *)this = image; }
};

#endif  // PIMAGE_H
