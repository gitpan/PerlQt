package QSemiModal;

use strict;
use vars qw($VERSION @ISA);

require Exporter;
require DynaLoader;
require QGlobal;

require QWidget;

@ISA = qw(Exporter DynaLoader QWidget);

$VERSION = '1.00';
bootstrap QSemiModal $VERSION;

1;
__END__

=head1 NAME

QSemiModal - Interface to the Qt QSemiModal class

=head1 SYNOPSIS

C<use QSemiModal;>

Inherits QWidget.

=head2 Member functions

new

=head2 Overridden functions

move,
resize,
setGeometry,
show

=head1 DESCRIPTION

What you see is what you get.

=head1 AUTHOR

Ashley Winters <jql@accessone.com>
