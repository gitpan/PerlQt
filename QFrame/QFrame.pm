package QFrame;

use strict;
use vars qw($VERSION @ISA @ANCESTORS @EXPORT);

require Exporter;
require DynaLoader;
require QGlobal;

require QRect;
require QWidget;

@ISA = qw(Exporter DynaLoader QWidget);
@EXPORT = qw(%Frame);

$VERSION = '0.03';
bootstrap QFrame $VERSION;

1;
__END__

=head1 NAME

QFrame - Interface to the Qt QFrame class

=head1 SYNOPSIS

C<use QFrame;>

Inherits QWidget.

Requires QRect.

=head2 Member functions

new,
contentsRect,
frameRect,
frameShadow,
frameShape,
frameStyle,
frameWidth,
lineShapesOk,
lineWidth,
midLineWidth,
setFrameStyle,
setLineWidth,
setMidLineWidth

=head1 DESCRIPTION

As direct an interface as humanly possible.

=head1 EXPORTED

Exports C<%Frame> into the user's namespace. It contains all the constants
accessed through QFrame:: in C++

=head1 SEE ALSO

qframe(3qt)

=head1 AUTHOR

Ashley Winters <jql@accessone.com>
