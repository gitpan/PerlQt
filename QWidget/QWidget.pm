package QWidget;

use strict;
use vars qw($VERSION @ISA @EXPORT);
use QGlobal qw(%GUI);

require Exporter;
require DynaLoader;
require QObject;
require QPaintDevice;

require QColor;
require QCursor;
require QEvent;
require QFont;
require QFontInfo;
require QFontMetrics;
require QPalette;
require QPixmap;
require QPoint;
require QRect;
require QSize;

@ISA = qw(Exporter DynaLoader QObject QPaintDevice);
@EXPORT = qw(%Focus %Flags %GUI);

$VERSION = '1.03';
bootstrap QWidget $VERSION;

1;
__END__

=head1 NAME

QWidget - Interface to the Qt QWidget class

=head1 SYNOPSIS

C<use QWidget;>

Inherits QObject and QPaintDevice.

Requires QColor, QCursor, QEvent, QFont, QFontInfo, QFontMetrics,
QPalette, QPixmap, QPoint, QRect, and QSize.

=head2 Member functions

new,
adjustSize,
backgroundColor,
backgroundPixmap,
caption,
childrenRect,
clearFocus,
close,
closeEvent,
colorGroup,
cursor,
drawText,
enterEvent,
erase,
focusInEvent,
focusOutEvent,
focusPolicy,
font,
fontInfo,
fontMetrics,
foregroundColor,
frameGeometry,
geometry,
grabKeyboard,
grabMouse,
hasFocus,
hasMouseTracking,
height,
hide,
icon,
iconText,
iconify,
isActiveWindow,
isDesktop,
isEnabled,
isFocusEnabled,
isModal,
isPopup,
isTopLevel,
isUpdatesEnabled,
isVisible,
keyboardGrabber,
keyPressEvent,
keyReleaseEvent,
leaveEvent,
lower,
mapFromGlobal,
mapFromParent,
mapToGlobal,
mapToParent,
maximumSize,
minimumSize,
mouseDoubleClickEvent,
mouseMoveEvent,
mousePressEvent,
mouseReleaseEvent,
mouseGrabber,
move,
moveEvent,
paintEvent,
palette,
parentWidget,
pos,
raise,
recreate,
rect,
releaseKeyboard,
releaseMouse,
repaint,
resize,
resizeEvent,
scroll,
setActiveWindow,
setBackgroundColor,
setBackgroundPixmap,
setCaption,
setCursor,
setEnabled,
setFixedSize,
setFocus,
setFocusPolicy,
setFont,
setGeometry,
setIcon,
setIconText,
setMaximumSize,
setMinimumSize,
setMouseTracking,
setPalette,
setSizeIncrement,
setStyle,
setUpdatesEnabled,
show,
size,
sizeHint,
sizeIncrement,
style,
topLevelWidget,
update,
width,
winId,
x,
y

=head2 Overridable functions

adjustSize,
close,
closeEvent,
enterEvent,
focusInEvent,
focusOutEvent,
hide,
keyPressEvent,
keyReleaseEvent,
leaveEvent,
mouseDoubleClickEvent,
mouseMoveEvent,
mousePressEvent,
mouseReleaseEvent,
move,
moveEvent,
paintEvent,
resize,
resizeEvent,
setBackgroundColor,
setBackgroundPixmap,
setCursor,
setEnabled,
setFont,
setGeometry,
setPalette,
setStyle,
show,
sizeHint

=head2 Overridden functions

event

=head1 DESCRIPTION

Every function made available to PerlQt is meant to be interfaced
identically to C++ Qt.

=head1 EXPORTED

The C<%Focus> and C<%Flags> hashes are exported into the user's
namespace, and C<%GUI> is exported from QGlobal.

C<%Focus> contains all of the constants in QWidget that end in Focus.
That trailing I<Focus> is removed from the end of the keys for brevity.

The C<%Flags> hash is much more involved. It contains all of the
C<WState_*>, C<WType_*>, and C<WStyle_*> flags, as well as quite a few
others that begin with W. You can get a full list of them from
F<qwindefs.h>.

But you won't find these constants exactly as they're spelled out in there.
I've stripped all the leading W's, for example. And all of the constants
which have an underscore in them have been split up into two components
based on the underscore. I think a few examples are in order.

    Was: WStyle_NormalBorder
    Now: $Flags{Style}{NormalBorder}
    Was: WState_TrackMouse
    Now: $Flags{State}{TrackMouse}
    Was: WPaintDesktop
    Now: $Flags{PaintDesktop}

You can hopefully figure out the rest yourself.

=head1 SEE ALSO

qwidget(3qt)

=head1 AUTHOR

Ashley Winters <jql@accessone.com>
