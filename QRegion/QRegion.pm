package QRegion;

use strict;
use vars qw($VERSION @ISA @EXPORT);
use overload
    '==' => \&beq,
    '!=' => \&bne,
    'fallback' => 1;

require Exporter;
require DynaLoader;
require QGlobal;

require QPoint;
require QPointArray;
require QRect;

@ISA = qw(Exporter DynaLoader Qt::Base);
@EXPORT = qw(%Region);

$VERSION = '1.02';
bootstrap QRegion $VERSION;

1;
__END__

=head1 NAME

QRegion - Interface to the Qt QRegion class

=head1 SYNOPSIS

C<use QRegion;>

Requires QPoint, QPointArray, and QRect.

=head2 Member functions

new,
contains,
intersect,
isEmpty,
isNull,
subtract,
translate,
unite,
xor

=head2 Overloaded operators

!= ==

=head1 DESCRIPTION

Everything has been successfully interfaced.

=head2 EXPORTED

The C<%Region> hash is exported into the user's namespace. It contains
the RegionShape constants (Rectangle and Ellipse).

=head1 SEE ALSO

qregion(3qt)

=head1 AUTHOR

Ashley Winters <jql@accessone.com>
