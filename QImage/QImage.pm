package QImage;

use strict;
use vars qw($VERSION @ISA @EXPORT);

require Exporter;
require DynaLoader;
require QGlobal;

@ISA = qw(Exporter DynaLoader Qt::Base);
@EXPORT = qw(%Endian);

$VERSION = '1.02';
bootstrap QImage $VERSION;

1;
__END__

=head1 NAME

QImage - Interface to the Qt QImage class

=head1 SYNOPSIS

C<use QImage;>

=head2 Member functions

new,
bitOrder,
bytesPerLine,
color,
convertBitOrder,
convertDepth,
copy,
create,
createAlphaMask,
createHeuristicMask,
depth,
detach,
fill,
hasAlphaBuffer,
height,
imageFormat,
isNull,
load,
loadFromData,
numBytes,
numColors,
rect,
reset,
save,
setAlphaBuffer,
setColor,
setNumColors,
systemBitOrder,
systemByteOrder,
size,
width

=head1 DESCRIPTION

Fully interfaced. The missing overloaded operator=() is made up for with
extra new() prototypes accepting QPixmap or QBitmap arguments to copy.
No xpm constructor.

=head1 EXPORTED

The C<%Endian> hash is exported into the user's namespace. It has the
QImage Endian constants with the traling Endian removed.

=head1 SEE ALSO

qimage(3qt)

=head1 AUTHOR

Ashley Winters <jql@accessone.com>
