package QButton;

use strict;
use vars qw($VERSION @ISA);

require DynaLoader;
require QGlobal;

require QPixmap;
require QWidget;

@ISA = qw(DynaLoader QWidget);

$VERSION = '1.01';
bootstrap QButton $VERSION;

1;
__END__

=head1 NAME

QButton - Interface to the Qt QButton class

=head1 SYNOPSIS

C<use QButton;>

Inherits QWidget.

Requires QPixmap.

=head2 Member functions

new,
autoRepeat,
autoResize,
drawButton,
drawButtonLabel,
hitButton,
isDown,
isOn,
isToggleButton,
pixmap,
setAutoRepeat,
setAutoResize,
setDown,
setOn,
setPixmap,
setText,
setToggleButton,
text

=head2 Overridable functions

drawButton,
drawButtonLabel,
hitButton

=head2 Overridden functions

focusInEvent,
focusOutEvent,
keyPressEvent,
mouseMoveEvent,
mousePressEvent,
mouseReleaseEvent

=head1 DESCRIPTION

What you see is what you get.

=head1 SEE ALSO

qbutton(3qt)

=head1 AUTHOR

Ashley Winters <jql@accessone.com>
