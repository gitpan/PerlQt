package QPen;

use strict;
use vars qw($VERSION @ISA @EXPORT);
use overload
    '==' => \&beq,
    '!=' => \&bne,
    'fallback' => 1;

require Exporter;
require DynaLoader;
require QGlobal;

require QColor;

@ISA = qw(Exporter DynaLoader Qt::Base);
@EXPORT = qw(%Pen);

$VERSION = '1.02';
bootstrap QPen $VERSION;

1;
__END__

=head1 NAME

QPen - Interface to the Qt QPen class

=head1 SYNOPSIS

C<use QPen;>

Requires QColor.

=head2 Member functions

new,
color,
setColor,
setStyle,
setWidth,
style,
width

=head2 Overloaded operators

!= ==

=head1 DESCRIPTION

Except for the operators, this class is fully implemented.

=head1 EXPORTED

The C<%Pen> hash is exported into the user's namespace, and contains
all of the elements from the PenStyle enum defined in F<qpen.h>. The
C<NoPen> constant has been changed to C<$Pen{None}> and all the other
constants have had their appended Line's removed; thereby making 
C<SolidLine> become C<$Pen{Solid}>, and so on.

=head1 SEE ALSO

qpen(3qt)

=head1 AUTHOR

Ashley Winters <jql@accessone.com>
