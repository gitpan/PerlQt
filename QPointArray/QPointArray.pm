package QPointArray;

use strict;
use vars qw($VERSION @ISA);
use overload
    '==' => \&beq,
    '!=' => \&bne,
    'fallback' => 1;

require DynaLoader;
require QGlobal;

require QRect;
require QPoint;

@ISA = qw(DynaLoader Qt::Base);

$VERSION = '1.02';
bootstrap QPointArray $VERSION;

1;
__END__

=head1 NAME

QPointArray - Interface to the Qt QPointArray class

=head1 SYNOPSIS

C<use QPointArray;>

=head2 Member functions

new,
at,
boundingRect,
copy,
detach,
fill,
isEmpty,
isNull,
makeArc,
makeEllipse,
point,
putPoints,
quadBezier,
resize,
setPoint,
setPoints,
size,
translate,
truncate

=head2 Overloaded operators

!= ==

=head1 DESCRIPTION

Many of the functions in the original QPointArray used nPoints to specify
the number of arguments or elements in *points. Perl is fortunatly better
than that, so just ditch nPoints and arrays of QCOORD's. Just type the
arguments in a list starting from where the nPoints would be.

=head1 SEE ALSO

qpointarray(3qt)

=head1 AUTHOR

Ashley Winters <jql@accessone.com>
