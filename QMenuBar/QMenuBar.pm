package QMenuBar;

use strict;
use vars qw($VERSION @ISA);

require DynaLoader;
require QGlobal;

require QFrame;
require QMenuData;

@ISA = qw(DynaLoader QFrame QMenuData);

$VERSION = '1.03';
bootstrap QMenuBar $VERSION;

1;
__END__

=head1 NAME

QMenuBar - Interface to the Qt QMenuBar class

=head1 SYNOPSIS

C<use QMenuBar;>

Inherits QFrame and QMenuData.

=head2 Member functions

new

=head2 Overridden functions

drawContents,
eventFilter,
hide,
keyPressEvent,
menuContentsChanged,
menuStateChanged,
mouseMoveEvent,
mousePressEvent,
mouseReleaseEvent,
resizeEvent,
show,
updateItem,

=head1 DESCRIPTION

What you see is what you get.

=head1 ANNOYING

menuInsPopup, menuDelPopup and frameChanged were overridden privately.
Which means that PerlQt can never call them. Sorry, blame Troll Tech.

=head1 AUTHOR

Ashley Winters <jql@accessone.com>
