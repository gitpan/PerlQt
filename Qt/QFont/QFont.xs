/*
 * PerlQt interface to QFont (qfont.h)
 *
 * Copyright (C) 1997, Ashley Winters <jql@accessone.com>
 *
 * You may distribute under the terms of the LGPL as specified in the
 * README file
 */

#include <pqfont.h>

static struct pqt_const_hash pqt_const_hash_Style[] = {
    { "Any",	    QFont::AnyStyle	},
    { "Helvetica",  QFont::Helvetica	},
    { "Times",	    QFont::Times	},
    { "Courier",    QFont::Courier	},
    { "OldEnglish", QFont::OldEnglish	},
    { "System",     QFont::System	},
    { "SansSerif",  QFont::SansSerif	},
    { "Serif",	    QFont::Serif	},
    { "TypeWriter", QFont::TypeWriter	},
    { "Decorative", QFont::Decorative	},
    { 0,	    0			}
};

static struct pqt_const_hash pqt_const_hash_Weight[] = {
    { "Light",	  QFont::Light	  },
    { "Normal",   QFont::Normal   },
    { "DemiBold", QFont::DemiBold },
    { "Bold",	  QFont::Bold	  },
    { "Black",	  QFont::Black	  },
    { 0,	  0		  }
};

static struct pqt_const_hash pqt_const_hash_CharSet[] = {
    { "Any",	    QFont::AnyCharSet	},
    { "Latin1",     QFont::Latin1	},
    { "Latin2",     QFont::Latin2	},
    { "Latin3",     QFont::Latin3	},
    { "Latin4",     QFont::Latin4	},
    { "Latin5",     QFont::Latin5	},
    { "Latin6",     QFont::Latin6	},
    { "Latin7",     QFont::Latin7	},
    { "Latin8",     QFont::Latin8	},
    { "Latin9",     QFont::Latin9	},
    { "ISO_8859_1", QFont::ISO_8859_1	},
    { "ISO_8859_2", QFont::ISO_8859_2	},
    { "ISO_8859_3", QFont::ISO_8859_3	},
    { "ISO_8859_4", QFont::ISO_8859_4	},
    { "ISO_8859_5", QFont::ISO_8859_5	},
    { "ISO_8859_6", QFont::ISO_8859_6	},
    { "ISO_8859_7", QFont::ISO_8859_7	},
    { "ISO_8859_8", QFont::ISO_8859_8	},
    { "ISO_8859_9", QFont::ISO_8859_9	},
    { 0,	    0			}
};

static struct pqt_export QFont_export[] = {
    { "%Style",   pqt_const_hash_Style   },
    { "%Weight",  pqt_const_hash_Weight  },
    { "%CharSet", pqt_const_hash_CharSet },
    { 0, 0 }
};

static const char *QFont_overload[] = { "==", "!=", "<<", ">>", 0 };

MODULE = Qt::QFont	PACKAGE = QFont
PROTOTYPES: DISABLE

BOOT:
    pqt_class_register(
	"QFont",
	NULL,
	0,
	QFont_export,
	QFont_overload
    );
