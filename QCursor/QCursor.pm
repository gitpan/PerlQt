package QCursor;

use strict;
use vars qw($VERSION @ISA @EXPORT);

require Exporter;
require DynaLoader;
require QGlobal;

require QBitmap;
require QPoint;

@ISA = qw(Exporter DynaLoader Qt::Base);
@EXPORT = qw(%Cursor %Shape);

$VERSION = '1.00';
bootstrap QCursor $VERSION;

1;
__END__

=head1 NAME

QCursor - Interface to the Qt QCursor class

=head1 SYNOPSIS

C<use QCursor;>

Require QBitmap and QPoint.

=head2 Member functions

new,
bitmap,
hotSpot,
mask,
pos,
setPos,
setShape,
shape

=head1 DESCRIPTION

What you see is what you get

=head1 EXPORTED

The C<%Cursor> and C<%Shape> hashes are exported into the user's namespace.

C<%Cursor> contains all of the global cursors (C<arrowCursor>,
C<crossCursor>, etc..) without the Cursor suffix (C<$Cursor{arrow}>,
C<$Cursor{cross}>, etc...)

The C<%Shape> has contains all of the cursor shapes (C<ArrowCursor>, 
C<CrossCursor>, etc..) without the Cursor suffix (C<$Shape{Arrow}>,
C<$Shape{Cross}>, etc...)

=head1 SEE ALSO

qcursor(3qt)

=head1 AUTHOR

Ashley Winters <jql@accessone.com>
