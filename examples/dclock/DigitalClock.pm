#
# PerlQt Example Widget: DigitalClock (DigitalClock.pm)
#
# Implementation of DigitalClock widget.
#
# The DigitalClock widget inherits QLCDNumber and adds timer and mouse
# press events to show the time and the date.
#

package DigitalClock;

use QEvent;
use QFrame;
use QLCDNumber;

use slots 'stopDate()', 'showTime()';

@ISA = qw(QLCDNumber);

#
# Constructs a DigitalClock widget.
#

sub new {
    my $self = shift->SUPER::new(@_);

    $self->setFrameStyle($Frame{Panel} | $Frame{Raised});
    $self->setLineWidth(2);
    $self->showTime();

    @$self{'showingColon', 'normalTimer', 'showDateTimer'} = (
	 0,
	 $self->startTimer(500),
	 -1
    );
    return $self;
}

#
# Handles timer events for the digital clock widget.
# There are two different timers; one timer for updating the clock
# and another one for switching back from date mode to time mode.
#

sub timerEvent {
    my $self = shift;
    my $e = shift;

    if($e->timerId() == $$self{'showDateTimer'}) {
	$self->stopDate();
    } elsif($$self{'showDateTimer'} == -1) {
	$self->showTime();
    }
}

#
# Enters date mode when the left mouse button is pressed.
#

sub mousePressEvent {
    my $self = shift;
    my $e = shift;

    $self->showDate() if $e->button() == $Button{Left};
}

#
# Shows the current date in the internal lcd widget.
# Fires a timer to stop showing the date.
#

sub showDate {
    my $self = shift;

    return unless $$self{'showDateTimer'} == -1;
    my($day, $mon) = (localtime)[3, 4];
    $self->display(sprintf('%2d %2d', $mon+1, $day));
    $$self{'showDateTimer'} = $self->startTimer(2000);
}

#
# Stops showing the date.
#

sub stopDate {
    my $self = shift;

    $self->killTimer($$self{'showDateTimer'});
    $$self{'showDateTimer'} = -1;
    $self->showTime();
}

#
# Shows the current time in the internal lcd widget.
#

sub showTime {
    my $self = shift;

    $$self{'showingColon'} = !$$self{'showingColon'};
    my($min, $hour) = (localtime)[1, 2];
    my $s = sprintf("%d %.2d", $hour, $min);
    $s =~ s/ /:/ if $$self{'showingColon'};
    $self->display($s);
}
