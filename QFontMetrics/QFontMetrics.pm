package QFontMetrics;

use strict;
use vars qw($VERSION @ISA);

require DynaLoader;
require QGlobal;

require QFont;
require QRect;

@ISA = qw(DynaLoader Qt::Base);

$VERSION = '1.00';
bootstrap QFontMetrics $VERSION;

1;
__END__

=head1 NAME

QFontMetrics - Interface to the Qt QFontMetrics class

=head1 SYNOPSIS

C<use QFontMetrics;>

Requires QFont and QRect.

=head2 Member functions

ascent,
boundingRect,
descent,
font,
height,
leading,
lineSpacing,
lineWidth,
maxWidth,
strikeOutPos,
underlinePos,
width

=head1 DESCRIPTION

Fully implemented. Very good.

=head1 SEE ALSO

qfontmetrics(3qt)

=head1 AUTHOR

Ashley Winters <jql@accessone.com>
