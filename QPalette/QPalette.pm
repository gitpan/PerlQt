package QPalette;

use strict;
use vars qw($VERSION @ISA);
use overload
    '==' => \&beq,
    '!=' => \&bne,
    'fallback' => 1;

require DynaLoader;
require QGlobal;

@ISA = qw(DynaLoader Qt::Base);

$VERSION = '1.03';
bootstrap QPalette $VERSION;


package QColorGroup;

use strict;
use vars qw(@ISA);
use overload
    '==' => \&beq,
    '!=' => \&bne,
    'fallback' => 1;

require QGlobal;

require QColor;

@ISA = qw(Qt::Base);

1;
__END__

=head1 NAME

QPalette - Interface to the Qt QPalette and QColorGroup classes

=head1 SYNOPSIS

C<use QPalette;>

=head2 QColorGroup

Requires QColor.

=head2 Member functions

new,
background,
base,
dark,
foreground,
light,
mid,
text

=head2 QPalette

=head2 Member functions

new,
active,
copy,
disabled,
normal,
setActive,
setDisabled,
setNormal,
serialNumber

=head2 Overloaded operators

!= ==

=head1 DESCRIPTION

What you see is what you get.

=head1 SEE ALSO

qpalette(3qt)

=head1 AUTHOR

Ashley Winters <jql@accessone.com>
