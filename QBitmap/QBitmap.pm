package QBitmap;

use strict;
use vars qw($VERSION @ISA);

require DynaLoader;
require QGlobal;

require QPixmap;
require QSize;
require QWMatrix;

@ISA = qw(DynaLoader QPixmap);

$VERSION = '1.01';
bootstrap QBitmap $VERSION;

1;
__END__

=head1 NAME

QBitmap - Interface to the Qt QBitmap class

=head1 SYNOPSIS

C<use QBitmap;>

Inherits QPixmap.

Requires QSize and QWMatrix.

=head2 Member functions

new, xForm

=head1 DESCRIPTION

What you see is what you get. Because the = operator can't be properly
overloaded in Perl, new constructor prototypes were added to replicate
the effect. QBitmap::new({QBitmap|QPixmap|QImage}) is legal as a
replacement for an overloaded = operator.

=head1 SEE ALSO

qbitmap(3qt)

=head1 AUTHOR

Ashley Winters <jql@accessone.com>
