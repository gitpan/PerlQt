package QTableView;

use strict;
use vars qw($VERSION @ISA @EXPORT);

require Exporter;
require DynaLoader;
require QGlobal;

require QFrame;
require QPainter;
require QRect;
require QScrollBar;

@ISA = qw(Exporter DynaLoader QFrame);
@EXPORT = qw(%Tbl);

$VERSION = '1.03';
bootstrap QTableView $VERSION;

1;
__END__

=head1 NAME

QTableView - Interface to the Qt QTableView class

=head1 SYNOPSIS

C<use QTableView;>

Inherits QFrame.

Requires QPainter, QRect and QScrollBar

=head2 Member functions

new,
autoUpdate,
cellHeight,
cellUpdateRect,
cellWidth,
clearTableFlags,
colIsVisible,
colXPos,
findCol,
findRow,
horizontalScrollBar,
lastColVisible,
lastRowVisible,
leftCell,
maxColOffset,
maxRowOffset,
maxViewX,
maxViewY,
maxXOffset,
maxYOffset,
numCols,
numRows,
rowIsVisible,
rowYPos,
scroll,
setAutoUpdate,
setCellHeight,
setCellWidth,
setLeftCell,
setNumCols,
setNumRows,
setOffset,
setTableFlags,
setTopCell,
setTopLeftCell,
setXOffset,
setYOffset,
setupPainter,
tableFlags,
testTableFlags,
topCell,
totalHeight,
totalWidth,
updateCell,
updateScrollBars,
verticalScrollBar,
viewHeight,
viewWidth,
viewRect,
xOffset,
yOffset

=head2 Overridable functions

cellHeight,
cellWidth,
totalHeight,
totalWidth,
paintCell,
setupPainter

=head2 Overridden functions

paintEvent,
resizeEvent,
setBackgroundColor,
setPalette,
show

=head1 DESCRIPTION

What you see is what you get. One of the more notable things to see is that
paintCell is overridable, but is not listed as a member function. That
means if it's called and hasn't been overridden, you can consider your
program dead.

=head1 AUTHOR

Ashley Winters <jql@accessone.com>
