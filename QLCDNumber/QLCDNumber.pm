package QLCDNumber;

use strict;
use vars qw($VERSION @ISA @EXPORT);

require Exporter;
require DynaLoader;
require QFrame;

@ISA = qw(Exporter DynaLoader QFrame);
@EXPORT = qw(%Mode %Segment);

$VERSION = '1.02';
bootstrap QLCDNumber $VERSION;

1;
__END__

=head1 NAME

QLCDNumber - Interface to the Qt QLCDNumber class

=head1 SYNOPSIS

C<use QLCDNumber;>

Inherits QFrame.

=head2 Member functions

new,
checkOverflow,
display,
intValue,
mode,
numDigits,
segmentStyle,
setBinMode,
setDecMode,
setHexMode,
setMode,
setNumDigits,
setOctMode,
setSegmentStyle,
setSmallDecimalPoint,
smallDecimalPoint,
value

=head2 Overridden functions

drawContents,
resizeEvent

=head1 DESCRIPTION

What you see is what you get.

=head1 EXPORTED

The C<%Mode> and C<%Segment> hashes are exported into the user's namespace.
C<%Mode> contains the various numeric modes, DEC, HEX, etc.. C<%Segment>
corresponds to the QLCDNumber::SegmentStyle enum.

=head1 SEE ALSO

qlcdnumber(3qt)

=head1 AUTHOR

Ashley Winters <jql@accessone.com>
