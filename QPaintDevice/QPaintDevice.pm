package QPaintDevice;

use strict;
use vars qw($VERSION @ISA @EXPORT);

require Exporter;
require DynaLoader;
require QGlobal;

@ISA = qw(Exporter DynaLoader Qt::Base);
@EXPORT = qw(%PDT %PDF &bitBlt);

$VERSION = '1.00';
bootstrap QPaintDevice $VERSION;

1;
__END__

=head1 NAME

QPaintDevice - Interface to the Qt QPaintDevice class

=head1 SYNOPSIS

C<use QPaintDevice;>

=head2 Member functions

devType,
isExtDev,
paintingActive

=head1 DESCRIPTION

A very strange class.

=head1 EXPORTED

The C<%PDT> and C<%PDF> hashes are exported into the user's namespace.
They contain the values of the PD[FT]_* constants.

bitBlt() is also exported, but in a strange twist of Perlian fate,
it can be called as a member-function.

    $widget->bitBlt(dx, dy, pixmap, sx, sy, sw, sh);

=head2 NOTES

There are virtual functions in QPaintDevice in the C++ version of Qt,
but none in PerlQt. I see no reason why anyone would want to override a
QPaintDevice method in PerlQt, and it's a bit too much effort to add it
without cause. It's certainly not impossible though, and if you would
like them added, just tell me.

=head1 AUTHOR

Ashley Winters <jql@accessone.com>
