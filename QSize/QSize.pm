package QSize;

use strict;
use vars qw($VERSION @ISA);
use overload
    '*'  => \&bmul,
    '/'  => \&bdiv,
    '+'  => \&badd,
    '-'  => \&bsub,
    '==' => \&beq,
    '!=' => \&bne,
    'fallback' => 1;

require DynaLoader;
require QGlobal;

require QPoint;

@ISA = qw(DynaLoader Qt::Base);

$VERSION = '1.03';
bootstrap QSize $VERSION;

1;
__END__

=head1 NAME

QSize - Interface to the Qt QSize class

=head1 SYNOPSIS

Requires QPoint.

=head2 Member functions

new,
height,
isEmpty,
isNull,
isValid,
setHeight,
setWidth,
width

=head2 Overloaded operators

* / + - != ==

=head1 DESCRIPTION

Fully implemented, including operators.

=head1 SEE ALSO

qsize(3qt)

=head1 AUTHOR

Ashley Winters <jql@accessone.com>
