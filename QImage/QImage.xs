/*
 * PerlQt interface to qimage.h
 *
 * Copyright (C) 1997, Ashley Winters <jql@accessone.com>
 *
 * You may distribute under the terms of the LGPL as specified in the
 * README file
 */

#include "pimage.h"
#include "prect.h"
#include "psize.h"
#include "penum.h"

#define STORE_key(key) enumIV(hv, MSTR(key), QImage::key ## Endian)

inline void init_enum() {
    HV *hv = perl_get_hv("QImage::Endian", TRUE | GV_ADDMULTI);

    STORE_key(Ignore);
    STORE_key(Big);
    STORE_key(Little);
}

MODULE = QImage		PACKAGE = QImage

PROTOTYPES: DISABLE

BOOT:
    init_enum();

PImage *
PImage::new(...)
    CASE: items == 1
	CODE:
	RETVAL = new PImage();
	OUTPUT:
	RETVAL
    CASE: items > 3
	PREINIT:
	int width = SvIV(ST(1));
	int height = SvIV(ST(2));
	int depth = SvIV(ST(3));
	int numColors = (items > 4) ? SvIV(ST(4)) : 0;
	QImage::Endian bitOrder = (items > 5) ?
	    (QImage::Endian)SvIV(ST(5)) : QImage::IgnoreEndian;
	CODE:
	RETVAL = new PImage(width, height, depth, numColors, bitOrder);
	OUTPUT:
	RETVAL
    CASE: items == 3 || (items == 2 && !sv_isobject(ST(1)))
	PREINIT:
	char *fileName = SvPV(ST(1), na);
	pChar *format = (items > 2 && SvOK(ST(2))) ? SvPV(ST(2), na) : 0;
	CODE:
	RETVAL = new PImage(fileName, format);
	OUTPUT:
	RETVAL
    CASE: items == 2 && sv_derived_from(ST(1), "QImage")
	PREINIT:
	QImage *image = pextract(QImage, 1);
	CODE:
	RETVAL = new PImage(*image);
	OUTPUT:
	RETVAL
    CASE: items == 2
	PREINIT:
	QPixmap *pixmap = pextract(QPixmap, 1);
	CODE:
	RETVAL = new PImage(*pixmap);
	OUTPUT:
	RETVAL

void
QImage::DESTROY()
    CODE:
    if(want_destroy(ST(0)))
	delete THIS;

QImage::Endian
QImage::bitOrder()

int
QImage::bytesPerLine()

QRgb
QImage::color(i)
    int i

PImage *
QImage::convertBitOrder(bitOrder)
    QImage::Endian bitOrder
    CODE:
    RETVAL = new PImage(THIS->convertBitOrder(bitOrder));
    OUTPUT:
    RETVAL

PImage *
QImage::convertDepth(depth)
    int depth
    CODE:
    RETVAL = new PImage(THIS->convertDepth(depth));
    OUTPUT:
    RETVAL

PImage *
QImage::copy()
    CODE:
    RETVAL = new PImage(THIS->copy());
    OUTPUT:
    RETVAL

bool
QImage::create(w, h, depth, numColors = 0, bitOrder = QImage::IgnoreEndian)
    int w
    int h
    int depth
    int numColors
    QImage::Endian bitOrder

PImage *
QImage::createAlphaMask(dither = FALSE)
    bool dither
    CODE:
    RETVAL = new PImage(THIS->createAlphaMask(dither));
    OUTPUT:
    RETVAL

PImage *
QImage::createHeuristicMask(clipTight = TRUE)
    bool clipTight
    CODE:
    RETVAL = new PImage(THIS->createHeuristicMask(clipTight));
    OUTPUT:
    RETVAL

int
QImage::depth()

void
QImage::detach()

void
QImage::fill(pixel)
    uint pixel

bool
QImage::hasAlphaBuffer()

int
QImage::height()

const char *
imageFormat(fileName)
    char *fileName
    CODE:
    RETVAL = QImage::imageFormat(fileName);
    OUTPUT:
    RETVAL

bool
QImage::isNull()

bool
QImage::load(fileName, format = 0)
    char *fileName
    pChar *format

bool
QImage::loadFromData(buf, format = 0)
    PREINIT:
    STRLEN len;
    uchar *buf = (uchar *)SvPV(ST(1), len);
    pChar *format = (items > 2) ? SvPV(ST(2), na) : 0;
    CODE:
    RETVAL = THIS->loadFromData(buf, len, format);
    OUTPUT:
    RETVAL

int
QImage::numBytes()

int
QImage::numColors()

PRect *
QImage::rect()
    CODE:
    RETVAL = new PRect(THIS->rect());
    OUTPUT:
    RETVAL

void
QImage::reset()

bool
QImage::save(fileName, format)
    char *fileName
    char *format

void
QImage::setAlphaBuffer(b)
    bool b

void
QImage::setColor(i, c)
    int i
    QRgb c

void
QImage::setNumColors(num)
    int num

PSize *
QImage::size()
    CODE:
    RETVAL = new PSize(THIS->size());
    OUTPUT:
    RETVAL

QImage::Endian
systemBitOrder()
    CODE:
    RETVAL = QImage::systemBitOrder();
    OUTPUT:
    RETVAL

QImage::Endian
systemByteOrder()
    CODE:
    RETVAL = QImage::systemByteOrder();
    OUTPUT:
    RETVAL

int
QImage::width()