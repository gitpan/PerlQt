package QProgressBar;

use strict;
use vars qw($VERSION @ISA @EXPORT);

require Exporter;
require DynaLoader;

require QFrame;

@ISA = qw(Exporter DynaLoader QFrame);

$VERSION = '1.00';
bootstrap QProgressBar $VERSION;

1;
__END__

=head1 NAME

QProgressBar - Interface to the Qt QProgressBar class

=head1 SYNOPSIS

C<use QProgressBar;>

Inherits QFrame.

=head2 Member functions

new,
progress,
reset,
setProgress,
setTotalSteps,
totalSteps,

=head2 Overridden functions

drawContents,
show,
sizeHint

=head2 Overridable functions

setIndicator

=head1 DESCRIPTION

QProgressBar has been completely interfaced. Isn't that nice?

=head1 AUTHOR

Ashley Winters <jql@accessone.com>
