package QRegion;

use strict;
use vars qw($VERSION @ISA);

require DynaLoader;
require QGlobal;

require QPoint;
require QPointArray;
require QRect;

@ISA = qw(DynaLoader Qt::Base);

$VERSION = '1.00';
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

=head1 DESCRIPTION

Everything but the operators has been successfully interfaced.

=head1 SEE ALSO

qregion(3qt)

=head1 AUTHOR

Ashley Winters <jql@accessone.com>
