package QProgressDialog;

use strict;
use vars qw($VERSION @ISA);

require DynaLoader;
require QGlobal;

require QSemiModal;

@ISA = qw(DynaLoader QSemiModal);

$VERSION = '1.00';
bootstrap QProgressDialog $VERSION;

1;
__END__

=head1 NAME

QProgressDialog - Interface to the Qt QProgressDialog class

=head1 SYNOPSIS

C<use QProgressDialog;>

Inherits QSemiModal.

=head2 Member functions

new,
cancel,
progress,
reset,
setBar,
setCancelButton,
setCancelButtonText,
setLabel,
setLabelText,
setProgress,
setTotalSteps,
totalSteps,
wasCancelled

=head2 Overridden functions

resizeEvent,
sizeHint

=head1 DESCRIPTION

What you see is what you get.

=head1 AUTHOR

Ashley Winters <jql@accessone.com>
