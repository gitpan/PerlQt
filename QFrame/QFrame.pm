package QFrame;

use strict;
use vars qw($VERSION @ISA @ANCESTORS @EXPORT);

require Exporter;
require DynaLoader;
require QGlobal;

require QRect;
require QWidget;

@ISA = qw(Exporter DynaLoader QWidget);
@EXPORT = qw(%Frame);

$VERSION = '1.00';
bootstrap QFrame $VERSION;

1;
__END__

=head1 NAME

QFrame - Interface to the Qt QFrame class

=head1 SYNOPSIS

C<use QFrame;>

Inherits QWidget.

Requires QRect.

=head2 Member functions

new,
contentsRect,
drawContents,
drawFrame,
frameChanged,
frameRect,
frameShadow,
frameShape,
frameStyle,
frameWidth,
lineShapesOk,
lineWidth,
midLineWidth,
setFrameRect,
setFrameStyle,
setLineWidth,
setMidLineWidth

=head2 Overridable functions

drawContents,
drawFrame,
frameChanged

=head2 Overridden functions

paintEvent,
resizeEvent

=head1 DESCRIPTION

As direct an interface as humanly possible.

=head1 EXPORTED

Exports C<%Frame> into the user's namespace. It contains all the constants
accessed through QFrame:: in C++. QFrame::NoFrame has been changed to
$Frame{None}.

=head1 SEE ALSO

qframe(3qt)

=head1 AUTHOR

Ashley Winters <jql@accessone.com>
