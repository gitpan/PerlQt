/*
 * PerlQt interface to QApplication (qapp.h)
 *
 * Copyright (C) 1997, Ashley Winters <jql@accessone.com>
 *
 * You may distribute under the terms of the LGPL as specified in the
 * README file
 */

#include <pqapp.h>
#include <pqcolor.h>
#include <pqcursor.h>
#include <pqfont.h>
#include <pqfontmet.h>
#include <pqpalette.h>
#include <pqpoint.h>

static struct pqt_const_hash pqt_const_hash_ColorSpec[] = {
    { "Normal",	 QApplication::NormalColor  },
    { "Custom",	 QApplication::CustomColor  },
    { "Private", QApplication::PrivateColor },
    { "Many",	 QApplication::ManyColor    },
    { "True",	 QApplication::TrueColor    },
    { 0,	 0			    }
};

static struct pqt_export QApplication_export[] = {
    { "%ColorSpec", pqt_const_hash_ColorSpec }, { 0, 0 }
};

static const char *QApplication_require[] = {
    "QClipBoard",
    "QColor",
    "QCursor",
    "QEvent",
    "QFont",
    "QFontMetrics",
    "QPalette",
    "QPoint",
    "QWidget",
    0
};

MODULE = Qt::QApplication     PACKAGE = QApplication	 PREFIX = v_
PROTOTYPES: DISABLE

BOOT:
    pqt_class_register(
	"QApplication",			// QApplication::
	"QObject",			// @ISA = ('QObject');
	QApplication_require,		// require Q*;
	QApplication_export		// @EXPORT = qw(%ColorSpec);
    );

VQApplication *
VQApplication::new()
    PREINIT:
    int argc = 0;
    char **argv = NULL;
    CODE:
    AV *ARGV = perl_get_av("ARGV", FALSE);
    SV *ARGV0 = perl_get_sv("0", FALSE);

    New(123, argv, argc+1, char *);	// allocate sizeof(char *) for argv
    argc = 0;
    argv[0] = NULL;			// initialization is good
    if(ARGV0) {
	STRLEN ARGV0_len;
	char *ARGV0_str = SvPV(ARGV0, ARGV0_len);  // Gimmie the script name
	Renew(argv, ++argc+1, char *);		   // Extend argv
	if(ARGV0_str) {				   // paranoia is good
	    New(123, argv[argc-1], ARGV0_len+1, char);
	    Copy(ARGV0_str, argv[argc-1], ARGV0_len+1, char);
	    argv[argc] = NULL;
	} else {				   // Extreme paranoia
	    warn("Unable to retrieve $0, that's impossible");
	    New(123, argv[argc-1], 1, char);
	    *argv[argc-1] = '\0';
	}
	if(ARGV)
	    for(I32 elem = 0; elem <= av_len(ARGV); elem++) {
		SV **ARGV_sv = av_fetch(ARGV, elem, 0);
		STRLEN ARGV_elem_len;
		char *ARGV_elem;

		if(!ARGV_sv) continue;
		ARGV_elem = SvPV(*ARGV_sv, ARGV_elem_len);
		Renew(argv, ++argc+1, char *);
		New(123, argv[argc-1], ARGV_elem_len+1, char);
		Copy(ARGV_elem, argv[argc-1], ARGV_elem_len+1, char);
		argv[argc-1][ARGV_elem_len] = '\0';	// paranoia is good
	    }
    }

    RETVAL = new VQApplication(argc, argv);  // The memory in argv is leaked :(
    argc = RETVAL->argc();
    argv = RETVAL->argv();
    av_clear(ARGV);			     // Free the command-line args...
    if(argc) { sv_setpv(ARGV0, argv[0]); argc--; argv++; }
    for(int i = 0; i < argc; i++)
	av_push(ARGV, newSVpv(argv[i], 0));  // rebuild @ARGV
    OUTPUT:
    RETVAL

void
QApplication::DESTROY()
    CODE:
    if(want_destroy(ST(0)))
	delete THIS;

int
QApplication::enter_loop()

int
QApplication::exec()

void
QApplication::exit_loop()

QWidget *
CQApplication::focusWidget()

QWidget *
CQApplication::mainWidget()

bool
PQApplication::v_notify(receiver, event)
    QObject DEF *receiver
    QEvent DEF *event

void
QApplication::processEvents(...)
    CASE: items == 1
    CASE:
	CODE:
	THIS->processEvents(pIV(1));

void
QApplication::processOneEvent()

void
QApplication::quit()

void
QApplication::setMainWidget(widget)
    QWidget *widget


QWidget *
activeModalWidget()
    CODE:
    RETVAL = QApplication::activeModalWidget();
    OUTPUT:
    RETVAL

QWidget *
activePopupWidget()
    CODE:
    RETVAL = QApplication::activePopupWidget();
    OUTPUT:
    RETVAL

QWidgetList *
allWidgets()
    CODE:
    RETVAL = QApplication::allWidgets();
    OUTPUT:
    RETVAL

void
beep()
    CODE:
    QApplication::beep();

QClipboard *
clipboard()
    CODE:
    RETVAL = QApplication::clipboard();
    OUTPUT:
    RETVAL

bool
closingDown()
    CODE:
    RETVAL = QApplication::closingDown();
    OUTPUT:
    RETVAL

int
colorSpec()
    CODE:
    RETVAL = QApplication::colorSpec();
    OUTPUT:
    RETVAL

QWidget *
desktop()
    CODE:
    RETVAL = QApplication::desktop();
    OUTPUT:
    RETVAL

int
doubleClickInterval()
    CODE:
    RETVAL = QApplication::doubleClickInterval();
    OUTPUT:
    RETVAL

void
exit(retcode = 0)
    int retcode
    CODE:
    QApplication::exit(retcode);

void
flushX()
    CODE:
    QApplication::flushX();

QFont *
font()
    CODE:
    RETVAL = QApplication::font();
    OUTPUT:
    RETVAL

MQFontMetrics
fontMetrics()
    CODE:
    RETVAL = QApplication::fontMetrics();
    OUTPUT:
    RETVAL

bool
hasGlobalMouseTracking()
    CODE:
    RETVAL = QApplication::hasGlobalMouseTracking();
    OUTPUT:
    RETVAL

QCursor *
overrideCursor()
    CODE:
    RETVAL = QApplication::overrideCursor();
    OUTPUT:
    RETVAL

QPalette *
palette()
    CODE:
    RETVAL = QApplication::palette();
    OUTPUT:
    RETVAL

void
postEvent(receiver, event)
    QObject DEF *receiver
    QEvent DEF *event
    CODE:
    QApplication::postEvent(receiver, event);

void
restoreOverrideCursor()
    CODE:
    QApplication::restoreOverrideCursor();

bool
sendEvent(receiver, event)
    QObject DEF *receiver
    QEvent DEF *event
    CODE:
    QApplication::sendEvent(receiver, event);

void
setColorSpec(spec)
    int spec
    CODE:
    QApplication::setColorSpec(spec);

void
setDoubleClickInterval(interval)
    int interval
    CODE:
    QApplication::setDoubleClickInterval(interval);

void
setFont(font, updateAllWidgets = FALSE)
    CQFont font
    bool updateAllWidgets
    CODE:
    QApplication::setFont(font, updateAllWidgets);

void
setGlobalMouseTracking(enable)
    bool enable
    CODE:
    QApplication::setGlobalMouseTracking(enable);

void
setOverrideCursor(cursor, replace = FALSE)
    CQCursor cursor
    bool replace
    CODE:
    QApplication::setOverrideCursor(cursor, replace);

void
setPalette(palette, updateAllWidgets = FALSE)
    CQPalette palette
    bool updateAllWidgets
    CODE:
    QApplication::setPalette(palette, updateAllWidgets);

void
setStyle(style)
    GUIStyle style
    CODE:
    QApplication::setStyle(style);

void
setWinStyleHighlightColor(color)
    CQColor color
    CODE:
    QApplication::setWinStyleHighlightColor(color);

bool
startingUp()
    CODE:
    RETVAL = QApplication::startingUp();
    OUTPUT:
    RETVAL

GUIStyle
style()
    CODE:
    RETVAL = QApplication::style();
    OUTPUT:
    RETVAL

void
syncX()
    CODE:
    QApplication::syncX();

QWidgetList *
topLevelWidgets()
    CODE:
    RETVAL = QApplication::topLevelWidgets();
    OUTPUT:
    RETVAL

QWidget *
widgetAt(...)
    CASE: items && pqt_object(ST(0))
	CODE:
	QApplication::widgetAt(CQPoint(pQ(0, const QPoint)), pfBOOL(1));
    CASE: items > 1
	CODE:
	QApplication::widgetAt(pIV(0), pIV(1), pfBOOL(2));
    CASE:
	CODE:
	croak("Usage: QApplication::widgetAt(x, y, child);\nUsage: QApplication::widgetAt(point, child);");

CQColor
winStyleHighlightColor()
    CODE:
    RETVAL = QApplication::winStyleHighlightColor();
    OUTPUT:
    RETVAL
