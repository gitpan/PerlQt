package QRect;

use strict;
use vars qw($VERSION @ISA);
use overload
    '==' => \&beq,
    '!=' => \&bne,
    'fallback' => 1;

require DynaLoader;
require QGlobal;

require QPoint;
require QSize;

@ISA = qw(DynaLoader Qt::Base);

$VERSION = '1.03';
bootstrap QRect $VERSION;

1;
__END__

=head1 NAME

QRect - Interface to the Qt QRect class

=head1 SYNOPSIS

C<use QRect;>

Requires QPoint and QSize.

=head2 Member functions

new,
bottom,
bottomLeft,
bottomRight,
center,
contains,
coords,
height,
intersect,
intersects,
isEmpty,
isNull,
isValid,
left,
moveBottomLeft,
moveBottomRight,
moveBy,
moveCenter,
moveTopLeft,
moveTopRight,
normalize,
rect,
right,
setBottom,
setCoords,
setHeight,
setLeft,
setRect,
setRight,
setSize,
setTop,
setWidth,
setX,
setY,
size,
top,
topLeft,
topRight,
unite,
width,
x,
y

=head2 Overloaded operators

!= ==

=head1 DESCRIPTION

Everything is fully interfaced, including the operators.

=head1 SEE ALSO

qrect(3qt)

=head1 AUTHOR

Ashley Winters <jql@accessone.com>
