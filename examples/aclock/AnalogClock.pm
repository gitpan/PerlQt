#
# PerlQt Example Widget: AnalogClock (AnalogClock.pm)
#
# Implementation of AnalogClock widget.
#
# The AnalogClock widget uses a QTimer object to redraw the clock
# every 5 seconds.  The advantage of QTimers over standard timer
# events is that QTimer emits a signal when the timer is activated.
# The DigitalClock (dclock) example uses standard timer events.
#

package AnalogClock;

use Qt ();

use slots 'timeout()';

@ISA = qw(QWidget);

#
# Constructs an analog clock widget that uses an internal QTimer.
#

sub new {
    my $self = shift->SUPER::new(@_);

    $self->{'time'} = [ localtime ];			# get current time
    my $internalTimer = QTimer->new($self);		# create internal timer
    $self->connect($internalTimer, 'timeout()', 'timeout()');
    $internalTimer->start(5000);		# emit signal every 5 seconds

    return $self;
}


#
# The QTimer::timeout() signal is received by this slot.
#

sub timeout {
    my $self = shift;

    $self->update() if (localtime)[1] != $self->{'time'}[1];
}


#
# The clock is painted using a 1000x1000 square coordinate system.
#

sub paintEvent {
    my $self = shift;

    return unless $self->isVisible();		# it is invisible
    my $time = $self->{'time'} = [ localtime ];	# save current time

    my $pts = QPointArray->new;
    my $paint = QPainter->new;
    $paint->begin($self);
    $paint->setBrush($self->foregroundColor());	# fill with foreground color

    my $cp = $self->rect()->center();		# widget center point
    my $d = ($self->width() < $self->height()) ?
	$self->width() : $self->height();	# we want a circular clock

    my $matrix = QWMatrix->new;			# setup transformation matrix
    $matrix->translate($cp->x(), $cp->y());	# origin at widget center
    $matrix->scale($d/1000.0, $d/1000.0);	# scale coordinate system

    my $h_angle = 30*($time->[2]%12-3) + $time->[1]/2;
    $matrix->rotate($h_angle);			# rotate to draw hour hand
    $paint->setWorldMatrix($matrix);
    $pts->setPoints(-20,0, 0,-20, 300,0, 0,20);
    $paint->drawPolygon($pts);			# draw hour hand
    $matrix->rotate(-$h_angle);			# rotate back to zero

    my $m_angle = ($time->[1]-15)*6;
    $matrix->rotate($m_angle);			# rotate to draw minute hand
    $paint->setWorldMatrix($matrix);
    $pts->setPoints(-10,0, 0,-10, 400,0, 0,10);
    $paint->drawPolygon($pts);			# draw minute hand
    $matrix->rotate(-$m_angle);			# rotate back to zero

    for(my $i = 0; $i < 12; $i++) {		# draw hour lines
	$paint->setWorldMatrix($matrix);
	$paint->drawLine(450,0, 500,0);
	$matrix->rotate(30);
    }
    $paint->end();
}
