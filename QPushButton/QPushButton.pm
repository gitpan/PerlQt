package QPushButton;

use strict;
use vars qw($VERSION @ISA);

require DynaLoader;
require QGlobal;

require QButton;

@ISA = qw(DynaLoader QButton);

$VERSION = '1.02';
bootstrap QPushButton $VERSION;

1;
__END__

=head1 NAME

QPushButton - Interface to the Qt QPushButton class

=head1 SYNOPSIS

C<use QPushButton;>

Inherits QButton.

=head2 Member functions

new,
autoDefault,
isDefault,
setAutoDefault,
setDefault,
setOn,
setToggleButton,
toggle,

=head2 Overridden functions

drawButton,
drawButtonLabel,
focusInEvent,
move,
resize,
setGeometry,
sizeHint

=head1 DESCRIPTION

Fully interfaced.

=head1 SEE ALSO

qpushbutton(3qt)

=head1 AUTHOR

Ashley Winters <jql@accessone.com>
