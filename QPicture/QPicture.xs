/*
 * PerlQt interface to qpicture.h
 *
 * Copyright (C) 1997, Ashley Winters <jql@accessone.com>
 *
 * You may distribute under the terms of the LGPL as specified in the
 * README file
 */

#include "ppicture.h"

MODULE = QPicture		PACKAGE = QPicture

PROTOTYPES: DISABLE

PPicture *
PPicture::new()

void
QPicture::DESTROY()
    CODE:
    if(want_destroy(ST(0)))
	delete THIS;

bool
QPicture::load(fileName)
    char *fileName

bool
QPicture::play(painter)
    QPainter *painter

bool
QPicture::save(fileName)
    char *fileName