package QComboBox;

use strict;
use vars qw($VERSION @ISA @EXPORT);

require Exporter;
require DynaLoader;
require QGlobal;

require QPixmap;
require QWidget;

@ISA = qw(Exporter DynaLoader QWidget);
@EXPORT = qw(%Policy);

$VERSION = '1.03';
bootstrap QComboBox $VERSION;

1;
__END__

=head1 NAME

QComboBox - Interface to the Qt QComboBox class

=head1 SYNOPSIS

C<use QComboBox;>

Inherits QWidget.

Requires QPixmap.

=head2 Member functions

new,
autoResize,
changeItem,
clear,
count,
currentItem,
currentText,
insertionPolicy,
insertItem,
insertStrList,
maxCount,
pixmap,
popup,
removeItem,
setAutoResize,
setCurrentItem,
setInsertionPolicy,
setMaxCount,
setSizeLimit,
sizeLimit,
text

=head2 Overridden functions

keyPressEvent,
mouseDoubleClickEvent,
mouseMoveEvent,
mousePressEvent,
mouseReleaseEvent,
paintEvent,
resizeEvent,
setBackgroundColor,
setEnabled,
setFont,
setPalette,
sizeHint

=head1 DESCRIPTION

The only significant change is insertStrList(). For obvious reasons, this
function cannot be directly converted to Perl because of it's list argument.
Perl simplifies the matter greatly by allowing a simple argument-list
change to C<insertStrList(index, str1, ..., strN)>. Just set the C<index>
argument to -1 of you want it the items to be appended.

=head1 EXPORTED

The C<%Policy> hash is exported into the user's namespace. It contains
the insertion policy constants. I couldn't resist changing everything,
so here's some sample code...

    Was: QComboBox::NoInsertion
    Now: $Policy{None}
    Was: QComboBox::AtTop
    Now: $Policy{Top}
    Was: QComboBox::AfterCurrent
    Now: $Policy{After}

The other constants are consistent with these. And when all else fails,
there's always C<keys %Policy>.

=head1 CAVEATS

If there is sufficient demand, I'm more than willing to change the
insertStrList() arguments to make index the last argument and defaulted
to -1. This would break scripts, so be warned.

=head1 AUTHOR

Ashley Winters <jql@accessone.com>
