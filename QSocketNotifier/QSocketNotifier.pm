package QSocketNotifier;

use strict;
use vars qw($VERSION @ISA @EXPORT);

require Exporter;
require DynaLoader;
require QObject;

@ISA = qw(Exporter DynaLoader QObject);
@EXPORT = qw(%Type);

$VERSION = '1.00';
bootstrap QSocketNotifier $VERSION;

1;
__END__

=head1 NAME

QSocketNotifier - Interface to the Qt QSocketNotifier class

=head1 SYNOPSIS

C<use QSocketNotifier;>

Inherits QObject.

=head2 Member functions

new,
isEnabled,
setEnabled,
socket,
type

=head1 DESCRIPTION

Every function made available to PerlQt is meant to be interfaced
identically to C++ Qt.

=head1 EXPORTED

%Type

=head1 SEE ALSO

qsocketnotifier(3qt)

=head1 AUTHOR

Ashley Winters <jql@accessone.com>
