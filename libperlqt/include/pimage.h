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

typedef QImage::Endian QImage__Endian;

class PImage : public QImage {
public:
    PImage() {}
    PImage(int width, int height, int depth, int numColors = 0,
	   QImage::Endian bitOrder = QImage::IgnoreEndian) :
	QImage(width, height, depth, numColors, bitOrder) {}
    PImage(const char *fileName, const char *format = 0) :
	QImage(fileName, format) {}
    PImage(const char *xpm[]) : QImage(xpm) {}

    PImage(const QImage &image) : QImage(image) {}
    PImage(const QPixmap &pixmap) { *(QImage *)this = pixmap; }
};

#endif  // PIMAGE_H
