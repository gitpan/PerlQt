package QEvent;

use strict;
use vars qw($VERSION @ISA @EXPORT);
use QGlobal qw(%Key);

require Exporter;
require DynaLoader;

@ISA = qw(Exporter DynaLoader Qt::Base);
@EXPORT = qw(%Button %Event %Key);

$VERSION = '0.03';
bootstrap QEvent $VERSION;


package QCloseEvent;

use strict;
use vars qw(@ISA);

@ISA = qw(QEvent);

*VERSION = \$QEvent::VERSION;


package QFocusEvent;

use strict;
use vars qw(@ISA);

@ISA = qw(QEvent);

*VERSION = \$QEvent::VERSION;


package QKeyEvent;

use strict;
use vars qw(@ISA);

@ISA = qw(QEvent);

*VERSION = \$QEvent::VERSION;


package QMouseEvent;

use strict;
use vars qw(@ISA);
require QPoint;

@ISA = qw(QEvent);

*VERSION = \$QEvent::VERSION;
*Button = \%QEvent::Button;


package QMoveEvent;

use strict;
use vars qw(@ISA);

@ISA = qw(QEvent);

*VERSION = \$QEvent::VERSION;


package QPaintEvent;

use strict;
use vars qw(@ISA);
require QRect;

@ISA = qw(QEvent);

*VERSION = \$QEvent::VERSION;


package QResizeEvent;

use strict;
use vars qw(@ISA);
require QSize;

@ISA = qw(QEvent);

*VERSION = \$QEvent::VERSION;

1;
__END__

=head1 NAME

QEvent - Interface to the Qt QEvent, QMouseEvent, QPaintEvent, QResizeEvent, and QTimerEvent classes

=head1 SYNOPSIS

C<use QEvent;>

=head2 QEvent

=head2 Member functions

new,
type

=head2 QCloseEvent

Inherits QEvent.

=head2 Member functions

new,
accept,
ignore,
isAccepted

=head2 QFocusEvent

Inherits QEvent.

=head2 Member functions

new,
gotFocus,
lostFocus

=head2 QKeyEvent

Inherits QEvent.

=head2 Member functions

new,
accept,
ascii,
ignore,
isAccepted,
key,
state

=head2 QMouseEvent

Inherits QEvent.

Requires QPoint.

=head2 Member functions

new,
button,
pos,
state,
x,
y

=head2 QMoveEvent

Inherits QEvent.

=head2 Member functions

new,
oldPos,
pos

=head2 QPaintEvent

Inherits QEvent.

Requires QRect.

=head2 Member functions

new, rect

=head2 QResizeEvent

Inherits QEvent.

Requires QSize.

=head2 Member functions

new,
oldSize,
size

=head2 QTimerEvent

Inherits QEvent

=head2 Member functions

new,
timerId

=head1 DESCRIPTION

All QEvent* classes have been completely interfaced except QCustomEvent.
It will take a bit of creativity to figure out how to make that work.

=head1 EXPORTED

The C<%Event>, C<%Button>, and C<%Key> hashes are exported into the user's
namespace. The C<%Event> hash contains the Qt C<Event_*> constants.
All C<%Event> elements have had their prepending C<Event_> removed for
brevity. The C<%Button> hash contains the ButtonState enum constants
with the Button removed. So C<LeftButton> becomes $Button{Left} and
C<KeyButtonMask> becomes $Button{KeyMask}, and so on. The C<%Key> hash
contains all the F<qkeycode.h> keys without the Key_.

=head1 SEE ALSO

QEvent(3qt)

=head1 AUTHOR

Ashley Winters <jql@accessone.com>