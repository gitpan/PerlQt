package QLineEdit;

use strict;
use vars qw($VERSION @ISA @EXPORT);

require Exporter;
require DynaLoader;
require QGlobal;

require QWidget;

@ISA = qw(Exporter DynaLoader QWidget);
@EXPORT = qw(%Echo);

$VERSION = '1.00';
bootstrap QLineEdit $VERSION;

1;
__END__

=head1 NAME

QLineEdit - Interface to the Qt QLineEdit class

=head1 SYNOPSIS

C<use QLineEdit;>

Inherits QWidget.

=head2 Member functions

new,
deselect,
echoMode,
frame,
hasMarkedText,
markedText,
maxLength,
selectAll,
setEchoMode,
setFrame,
setMaxLength,
setText,
text

=head2 Overridden functions

focusInEvent,
focusOutEvent,
keyPressEvent,
mouseDoubleClickEvent,
mouseMoveEvent,
mousePressEvent,
mouseReleaseEvent,
paintEvent,
resizeEvent,
timerEvent

=head1 DESCRIPTION

What you see is what you get.

=head1 AUTHOR

Ashley Winters <jql@accessone.com>
