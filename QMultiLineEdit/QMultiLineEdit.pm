package QMultiLineEdit;

use strict;
use vars qw($VERSION @ISA);

require DynaLoader;
require QGlobal;

require QFont;
require QTableView;

@ISA = qw(DynaLoader QTableView);

$VERSION = '1.02';
bootstrap QMultiLineEdit $VERSION;

1;
__END__

=head1 NAME

QMultiLineEdit - Interface to the Qt QMultiLineEdit class

=head1 SYNOPSIS

C<use QMultiLineEdit;>

Inherits QTableView.

Requires QFont.

=head2 Member functions

new,
append,
atBeginning,
atEnd,
autoUpdate,
backspace,
clear,
copyText,
cursorDown,
cursorLeft,
cursorRight,
cursorUp,
cut,
del,
deselect,
end,
getCursorPosition,
getString,
hasMarkedText,
home,
insertAt,
insertChar,
insertLine,
isOverwriteMode,
isReadOnly,
killLine,
lineLength,
markedText,
newLine,
numLines,
pageDown,
pageUp,
paste,
removeLine,
selectAll,
setAutoUpdate,
setCursorPosition,
setOverwriteMode,
setReadOnly,
setText,
text,
textLine,
textWidth

=head2 Overridable functions

backspace,
cursorDown,
cursorLeft,
cursorRight,
cursorUp,
del,
end,
home,
insertAt,
insertChar,
insertLine,
killLine,
newLine,
pageDown,
pageUp,
removeLine

=head1 DESCRIPTION

What you see is what you get.

=head1 AUTHOR

Ashley Winters <jql@accessone.com>
