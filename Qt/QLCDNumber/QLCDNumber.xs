/*
 * PerlQt interface to QLCDNumber (qlcdnum.h)
 *
 * Copyright (C) 1997, Ashley Winters <jql@accessone.com>
 *
 * You may distribute under the terms of the LGPL as specified in the
 * README file
 */

#include <pqlcdnum.h>

static struct pqt_const_hash pqt_const_hash_Base[] = {
    { "Hexadecimal", QLCDNumber::HEX },
    { "Decimal",     QLCDNumber::DEC },
    { "Octal",       QLCDNumber::OCT },
    { "Binary",      QLCDNumber::BIN },
    { "2",	     QLCDNumber::BIN },
    { "8",	     QLCDNumber::OCT },
    { "10",	     QLCDNumber::DEC },
    { "16",	     QLCDNumber::HEX },
    { 0,	     0		     }
};

static struct pqt_const_hash pqt_const_hash_Segment[] = {
    { "Outline", QLCDNumber::Outline },
    { "Filled",  QLCDNumber::Filled  },
    { "Flat",    QLCDNumber::Flat    },
    { 0,	 0		     }
};

static struct pqt_export QLCDNumber_export[] = {
    { "%Base",    pqt_const_hash_Base    },
    { "%Segment", pqt_const_hash_Segment },
    { 0, 0 }
};

MODULE = Qt::QLCDNumber	     PACKAGE = QLCDNumber	PREFIX = v_
PROTOTYPES: DISABLE

BOOT:
    pqt_class_register(
	"QLCDNumber",
	"QFrame",
	0,
	QLCDNumber_export
    );
