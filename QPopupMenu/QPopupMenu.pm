package QPopupMenu;

use strict;
use vars qw($VERSION @ISA);

require DynaLoader;
require QGlobal;
require QTableView;
require QMenuData;

require QEvent;
require QPainter;
require QPoint;

@ISA = qw(DynaLoader QTableView QMenuData);

$VERSION = '1.02';
bootstrap QPopupMenu $VERSION;

1;
__END__

=head1 NAME

QPopupMenu - Interface to the Qt QPopupMenu class

=head1 SYNOPSIS

C<use QPopupMenu;>

Inherits QTableView and QMenuData.

Requires QPainter, QPoint and QEvent.

=head2 Member functions

new,
isCheckable,
popup,
setCheckable

=head2 Overridden functions

cellHeight,
cellWidth,
hide,
keyPressEvent,
mouseMoveEvent,
mousePressEvent,
mouseReleaseEvent,
paintCell,
paintEvent,
setFont,
show,
timerEvent,
updateItem,

=head1 DESCRIPTION

What you see is what you get.

=head1 AUTHOR

Ashley Winters <jql@accessone.com>
