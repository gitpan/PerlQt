/*
 * PerlQt interface to QWidget (qwidget.h)
 *
 * Copyright (C) 1997, Ashley Winters <jql@accessone.com>
 *
 * You may distribute under the terms of the LGPL as specified in the
 * README file
 */

#include <pqwidget.h>
#include <pqcolgrp.h>
#include <pqcolor.h>
#include <pqcursor.h>
#include <pqfont.h>
#include <pqfontinf.h>
#include <pqfontmet.h>
#include <pqpalette.h>
#include <pqpixmap.h>
#include <pqpoint.h>
#include <pqrect.h>
#include <pqsize.h>

static struct pqt_const_hash pqt_const_hash_Focus[] = {
    { "None",	QWidget::NoFocus     },
    { "Tab",	QWidget::TabFocus    },
    { "Click",	QWidget::ClickFocus  },
    { "Strong",	QWidget::StrongFocus },
    { 0,	0		     }
};

static struct pqt_const_hash pqt_const_hash_BackgroundMode[] = {
    { "None",	    QWidget::NoBackground	},
    { "Color",	    QWidget::FixedColor		},
    { "Pixmap",	    QWidget::FixedPixmap	},
    { "Foreground", QWidget::PaletteForeground	},
    { "Background", QWidget::PaletteBackground	},
    { "Light",	    QWidget::PaletteLight	},
    { "Midlight",   QWidget::PaletteMidlight	},
    { "Dark",	    QWidget::PaletteDark	},
    { "Mid",	    QWidget::PaletteMid		},
    { "Text",	    QWidget::PaletteText	},
    { "Base",	    QWidget::PaletteBase	},
    { 0,	    0				}
};

static struct pqt_export QWidget_export[] = {
    { "%Focus",		 pqt_const_hash_Focus		},
    { "%BackgroundMode", pqt_const_hash_BackgroundMode	},
    { 0,		 0				}
};

static const char *QWidget_isa[] = { "QObject", "QPaintDevice", 0 };

static const char *QWidget_require[] = {
    "QColor",
    "QColorGroup",
    "QCursor",
    "QFont",
    "QFontInfo",
    "QFontMetrics",
    "QPalette",
    "QPixmap",
    "QPoint",
    "QRect",
    "QSize",
    0
};

MODULE = Qt::QWidget	PACKAGE = QWidget	PREFIX = v_
PROTOTYPES: DISABLE

BOOT:
    pqt_class_register(
	"QWidget",
	QWidget_isa,
	QWidget_require,
	QWidget_export
    );

VQWidget *
VQWidget::new(parent = 0, name = 0, f = 0)
    QWidget *parent
    pcchar name
    WFlags f

void
QWidget::DESTROY()
    CODE:
    if(want_destroy(ST(0)))
	delete THIS;

void
PQWidget::v_adjustSize()

CQColor
CQWidget::backgroundColor()

void
PQWidget::v_backgroundColorChange(oldBackgroundColor)
    CQColor oldBackgroundColor

QWidget::BackgroundMode
CQWidget::backgroundMode()

const QPixmap *
CQWidget::backgroundPixmap()

void
PQWidget::v_backgroundPixmapChange(oldBackgroundPixmap)
    CQPixmap oldBackgroundPixmap

pcchar
CQWidget::caption()

MQRect
CQWidget::childrenRect()

void
QWidget::clearFocus()

bool
PQWidget::v_close(forceKill = FALSE)
    bool forceKill

void
PQWidget::v_closeEvent(event)
    QCloseEvent *event

CQColorGroup
CQWidget::colorGroup()

void
PQWidget::create(id, initializeWindow, destroyOldWindow)
    WId id
    bool initializeWindow
    bool destroyOldWindow

CQCursor
CQWidget::cursor()

void
PQWidget::destroy(destroyWindow, destroySubWindows)
    bool destroyWindow
    bool destroySubWindows

void
QWidget::drawText(...)
    CASE: items == 4
	PREINIT:
	int x = pIV(1);
	int y = pIV(2);
	pcchar text = pcPV(3);
	CODE:
	THIS->drawText(x, y, text);
    CASE: items == 3
	PREINIT:
	CQPoint point = pQ(1, const QPoint);
	pcchar text = pcPV(2);
	CODE:
	THIS->drawText(point, text);

void
PQWidget::v_enabledChange(oldEnabled)
    bool oldEnabled

void
PQWidget::v_enterEvent(event)
    QEvent *event

void
QWidget::erase(...)
    CASE: items == 1
    CASE: items == 4
	PREINIT:
	int x = pIV(1);
	int y = pIV(2);
	int w = pIV(3);
	int h = pIV(4);
	CODE:
	THIS->erase(x, y, w, h);
    CASE: items == 2
	PREINIT:
	CQRect rect = pQ(1, const QRect);
	CODE:
	THIS->erase(rect);
    CASE:
	CODE:
	croak("Usage: $widget->erase(x, y, w, h);\nUsage: $widget->erase(rect);\nUsage: $widget->erase();");

bool
PQWidget::v_event(event)
    QEvent *event

bool
PQWidget::v_focusNextPrevChild(next)
    bool next

QWidget::FocusPolicy
CQWidget::focusPolicy()

QWidget *
CQWidget::focusProxy()

QWidget *
CQWidget::focusWidget()

CQFont
CQWidget::font()

void
PQWidget::v_fontChange(oldFont)
    CQFont oldFont

CQFontInfo
CQWidget::fontInfo()

CQFontMetrics
CQWidget::fontMetrics()

CQColor
CQWidget::foregroundColor()

CQRect
CQWidget::frameGeometry()

CQRect
CQWidget::geometry()

void
QWidget::grabKeyboard()

void
QWidget::grabMouse(...)
    CASE: items == 1
    CASE:
	PREINIT:
	CQCursor cursor = pQ(1, const QCursor);
	CODE:
	THIS->grabMouse(cursor);

bool
CQWidget::hasFocus()

bool
CQWidget::hasMouseTracking()

int
CQWidget::height()

void
PQWidget::v_hide()

const QPixmap *
CQWidget::icon()

void
QWidget::iconify()

pcchar
CQWidget::iconText()

bool
CQWidget::isActiveWindow()

bool
CQWidget::isDesktop()

bool
CQWidget::isEnabled()

bool
CQWidget::isFocusEnabled()

bool
CQWidget::isModal()

bool
CQWidget::isPopup()

bool
CQWidget::isTopLevel()

bool
CQWidget::isUpdatesEnabled()

bool
CQWidget::isVisible()

bool
CQWidget::isVisibleToTLW()

void
PQWidget::v_keyPressEvent(event)
    QKeyEvent *event

void
PQWidget::v_keyReleaseEvent(event)
    QKeyEvent *event

void
PQWidget::v_leaveEvent(event)
    QEvent *event

void
QWidget::lower()

MQPoint
CQWidget::mapFromGlobal(point)
    CQPoint point

MQPoint
CQWidget::mapFromParent(point)
    CQPoint point

MQPoint
CQWidget::mapToGlobal(point)
    CQPoint point

MQPoint
CQWidget::mapToParent(point)
    CQPoint point

MQSize
CQWidget::maximumSize()

MQSize
CQWidget::minimumSize()

void
PQWidget::v_mouseDoubleClickEvent(event)
    QMouseEvent *event

void
PQWidget::v_mouseMoveEvent(event)
    QMouseEvent *event

void
PQWidget::v_mousePressEvent(event)
    QMouseEvent *event

void
PQWidget::v_mouseReleaseEvent(event)
    QMouseEvent *event

void
PQWidget::v_move(...)
    CASE: items == 3
	PREINIT:
	int x = pIV(1);
	int y = pIV(2);
	CODE:
	THIS->v_move(x, y);
    CASE: items == 2
	PREINIT:
	CQPoint point = pQ(1, const QPoint);
	CODE:
	THIS->move(point);
    CASE:
	CODE:
	croak("Usage: $widget->move(x, y);\nUsage: $widget->move(point);");

void
PQWidget::v_paintEvent(event)
    QPaintEvent *event

CQPalette
CQWidget::palette()

void
PQWidget::v_paletteChange(oldPalette)
    CQPalette oldPalette

QWidget *
CQWidget::parentWidget()

MQPoint
CQWidget::pos()

void
QWidget::raise()

void
QWidget::recreate(parent, f, point, showIt = FALSE)
    QWidget *parent
    WFlags f
    CQPoint point
    bool showIt

MQRect
CQWidget::rect()

void
QWidget::releaseKeyboard()

void
QWidget::releaseMouse()

void
QWidget::repaint(...)
    CASE: items == 5 || items == 6
	PREINIT:
	int x = pIV(1);
	int y = pIV(2);
	int w = pIV(3);
	int h = pIV(4);
	bool erase = ptBOOL(5);
	CODE:
	THIS->repaint(x, y, w, h, erase);
    CASE: items == 3 || items == 2 && pqt_object(ST(1))
	PREINIT:
	CQRect rect = pQ(1, const QRect);
	bool erase = ptBOOL(2);
	CODE:
	THIS->repaint(rect, erase);
    CASE: items == 1 || items == 2
	PREINIT:
	bool erase = ptBOOL(1);
	CODE:
	THIS->repaint(erase);
    CASE:
	CODE:
	croak("Usage: $widget->repaint(x, y, w, h, erase = 1);\nUsage: $widget->repaint(rect, erase = 1);\nUsage: $widget->repaint(erase = 1);");

void
PQWidget::v_resize(...)
    CASE: items == 3
	PREINIT:
	int w = pIV(1);
	int h = pIV(2);
	CODE:
	THIS->v_resize(w, h);
    CASE: items == 2
	PREINIT:
	CQSize size = pQ(1, const QSize);
	CODE:
	THIS->resize(size);
    CASE:
	CODE:
	croak("Usage: $widget->resize(w, h);\nUsage: $widget->resize(size);");

void
PQWidget::v_resizeEvent(event)
    QResizeEvent *event

void
QWidget::scroll(dx, dy)
    int dx
    int dy

void
QWidget::setActiveWindow()

void
PQWidget::v_setBackgroundColor(color)
    CQColor color

void
QWidget::setBackgroundMode(mode)
    QWidget::BackgroundMode mode

void
QWidget::setBackgroundPixmap(pixmap)
    CQPixmap pixmap

void
QWidget::setCaption(caption)
    pcchar caption

void
PQWidget::v_setCursor(cursor)
    CQCursor cursor

void
PQWidget::v_setEnabled(enable)
    bool enable

void
QWidget::setFixedHeight(h)
    int h

void
QWidget::setFixedSize(...)
    CASE: items == 3
	PREINIT:
	int w = pIV(1);
	int h = pIV(2);
	CODE:
	THIS->setFixedSize(w, h);
    CASE: items == 2
	PREINIT:
	CQSize size = pQ(1, const QSize);
	CODE:
	THIS->setFixedSize(size);
    CASE:
	CODE:
	croak("Usage: $widget->setFixedSize(w, h);\nUsage: $widget->setFixedSize(size);");

void
QWidget::setFixedWidth(w)
    int w

void
QWidget::setFocus()

void
QWidget::setFocusPolicy(policy)
    QWidget::FocusPolicy policy

void
QWidget::setFocusProxy(proxy)
    QWidget *proxy

void
QWidget::setFont(font)
    CQFont font

void
PQWidget::v_setGeometry(...)
    CASE: items == 5
	PREINIT:
	int x = pIV(1);
	int y = pIV(2);
	int w = pIV(3);
	int h = pIV(4);
	CODE:
	THIS->v_setGeometry(x, y, w, h);
    CASE: items == 2
	PREINIT:
	CQRect rect = pQ(1, const QRect);
	CODE:
	THIS->setGeometry(rect);
    CASE:
	CODE:
	croak("Usage: $widget->setGeometry(x, y, w, h);\nUsage: $widget->setGeometry(rect);");

void
QWidget::setIcon(pixmap)
    CQPixmap pixmap

void
QWidget::setIconText(text)
    pcchar text

void
QWidget::setMaximumHeight(h)
    int h

void
QWidget::setMaximumSize(...)
    CASE: items == 3
	PREINIT:
	int w = pIV(1);
	int h = pIV(2);
	CODE:
	THIS->setMaximumSize(w, h);
    CASE: items == 2
	PREINIT:
	CQSize size = pQ(1, const QSize);
	CODE:
	THIS->setMaximumSize(size);
    CASE:
	CODE:
	croak("Usage: $widget->setMaximumSize(w, h);\nUsage: $widget->setMaximumSize(size);");

void
QWidget::setMaximumWidth(w)
    int w

void
QWidget::setMinimumHeight(h)
    int h

void
QWidget::setMinimumSize(...)
    CASE: items == 3
	PREINIT:
	int w = pIV(1);
	int h = pIV(2);
	CODE:
	THIS->setMinimumSize(w, h);
    CASE: items == 2
	PREINIT:
	CQSize size = pQ(1, const QSize);
	CODE:
	THIS->setMinimumSize(size);
    CASE:
	CODE:
	croak("Usage: $widget->setMinimumSize(w, h);\nUsage: $widget->setMinimumSize(size);");

void
QWidget::setMinimumWidth(w)
    int w

void
QWidget::setMouseTracking(enable)
    bool enable

void
PQWidget::v_setPalette(palette)
    CQPalette palette

void
QWidget::setSizeIncrement(...)
    CASE: items == 3
	PREINIT:
	int w = pIV(1);
	int h = pIV(2);
	CODE:
	THIS->setSizeIncrement(w, h);
    CASE: items == 2
	PREINIT:
	CQSize size = pQ(1, const QSize);
	CODE:
	THIS->setSizeIncrement(size);
    CASE:
	CODE:
	croak("Usage: $widget->setSizeIncrement(w, h);\nUsage: $widget->setSizeIncrement(size);");

void
PQWidget::v_setStyle(style)
    GUIStyle style

void
QWidget::setUpdatesEnabled(enable)
    bool enable

void
PQWidget::v_show()

MQSize
CQWidget::size()

MQSize
CPQWidget::v_sizeHint()

MQSize
CQWidget::sizeIncrement()

GUIStyle
CQWidget::style()

void
PQWidget::v_styleChange(oldStyle)
    GUIStyle oldStyle

QWidget *
CQWidget::topLevelWidget()

void
QWidget::update(...)
    CASE: items == 1
    CASE: items == 4
	PREINIT:
	int x = pIV(1);
	int y = pIV(2);
	int w = pIV(3);
	int h = pIV(4);
	CODE:
	THIS->update(x, y, w, h);
    CASE: items == 2
	PREINIT:
	CQRect rect = pQ(1, const QRect);
	CODE:
	THIS->update(rect);
    CASE:
	CODE:
	croak("Usage: $widget->update(x, y, w, h);\nUsage: $widget->update(rect);\nUsage: $widget->update();");

int
CQWidget::width()

WId
CQWidget::winId()

int
CQWidget::x()

int
CQWidget::y()


QWidget *
find(id)
    WId id
    CODE:
    RETVAL = QWidget::find(id);
    OUTPUT:
    RETVAL

QWidget *
keyboardGrabber()
    CODE:
    RETVAL = QWidget::keyboardGrabber();
    OUTPUT:
    RETVAL

QWidget *
mouseGrabber()
    CODE:
    RETVAL = QWidget::mouseGrabber();
    OUTPUT:
    RETVAL

void
setTabOrder(first, second)
    QWidget *first
    QWidget *second
    CODE:
    QWidget::setTabOrder(first, second);
