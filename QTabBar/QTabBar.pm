package QTabBar;

use strict;
use vars qw($VERSION @ISA);

require DynaLoader;
require QGlobal;

require QWidget;

@ISA = qw(DynaLoader QWidget);

$VERSION = '1.00';
bootstrap QTabBar $VERSION;

package QTab;

use strict;
use vars qw(@ISA);

@ISA = qw(Qt::Base);

sub new {
    my $self = {};
    my $class = shift;
    tie %$self, $class;

    return bless $self, $class;
}

sub TIEHASH {
    my $self = bless {}, shift;

    $self->setup();
    return $self;
}

1;
__END__

=head1 NAME

QTabBar - Interface to the Qt QTabBar class

=head1 SYNOPSIS

C<use QTabBar;>

Inherits QWidget.

=head2 Member functions

new,
addTab,
currentTab,
isTabEnabled,
keyboardFocusTab,
paint,
selectTab,
setTabEnabled

=head2 Overridable functions

addTab,
paint,
selectTab

=head2 Overridden functions

keyPressEvent,
mousePressEvent,
mouseReleaseEvent,
paintEvent,
show,
sizeHint


=head2 QTab

    $tab = new QTab;
    $$tab{label} = "Hello World";
    $$tab{r} = new QRect(1, 2, 3, 4);
    $$tab{enabled} = 1;
    $$tab{id} = 10;

=head1 DESCRIPTION

What you see is what you get.

=head1 NOTES

QTab is a tied hash reference which accesses a real QTab.
keys() does not work on a QTab.

=head1 AUTHOR

Ashley Winters <jql@accessone.com>
