package QPoint;

use strict;
use vars qw($VERSION @ISA);
use overload
    'neg' => \&uneg,
    '*'   => \&bmul,
    '/'   => \&bdiv,
    '+'   => \&badd,
    '-'   => \&bsub,
    '=='  => \&beq,
    '!='  => \&bne,
    'fallback' => 1;

require DynaLoader;
require QGlobal;

@ISA = qw(DynaLoader Qt::Base);

$VERSION = '1.01';
bootstrap QPoint $VERSION;

1;
__END__

=head1 NAME

QPoint - Interface to the Qt QPoint class

=head1 SYNOPSIS

C<use QPoint;>

=head2 Member functions

new,
isNull,
setX,
setY,
x,
y

=head2 Overloaded operators

neg (unary minus) * / + - != ==

=head1 DESCRIPTION

What you see is what you get. That means operators.

=head1 RESTRICTIONS

The functions rx() and ry() will not be interfaced to PerlQt unless there
is sufficient demand for it, or lvalue Perl XSUBs become a reality.

=head1 SEE ALSO

qpoint(3qt)

=head1 AUTHOR

Ashley Winters <jql@accessone.com>
