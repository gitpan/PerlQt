package LifeTimer;

use Qt 2.0;
use Qt::slots ('setSpeed(int)', 'pause(bool)');

@ISA = qw(Qt::Timer);
$MAXSPEED = 1000;

sub new {
    my $self = shift->SUPER::new(@_);
    $self->{'interval'} = 500;
    $self->start($self->{'interval'});
    return $self;
}

sub pause {
    my $self = shift;
    my $stopIt = shift;
    if($stopIt) {
	$self->stop();
    } else {
	$self->start($self->{'interval'});
    }
}

sub setSpeed {
    my $self = shift;
    my $speed = shift;
    $self->{'interval'} = $MAXSPEED - $speed; 
    $self->changeInterval($self->{'interval'}) if $self->isActive();
}


package LifeDialog;

use Qt 2.0;
use Qt::app;
use Qt::slots ('getPattern(int)');
require 'patterns.pl';

use LifeWidget;

@ISA = qw(Qt::Widget);
$TOPBORDER = 70;
$SIDEBORDER = 10;

sub new {
    my $self = shift->SUPER::new(@_);
    my $qb = $self->{'qb'} = Qt::PushButton->new("Quit!", $self);
    my $cb = $self->{'cb'} = Qt::ComboBox->new($self, "comboBox");
    my $life = $self->{'life'} = LifeWidget->new($self);
    $life->move($SIDEBORDER, $TOPBORDER);

    $app->connect($qb, 'clicked()', 'quit()');
    $qb->setGeometry($SIDEBORDER, $SIDEBORDER, 75, 25);
    my $timer = $self->{'timer'} = LifeTimer->new($self);

    $life->connect($timer, 'timeout()', 'nextGeneration()');
    my $pb = $self->{'pb'} = Qt::PushButton->new("Pause", $self);
    $pb->setToggleButton(1);
    $timer->connect($pb, 'toggled(bool)', 'pause(bool)');
    $pb->resize(75, 25);
    $pb->move($self->width() - $SIDEBORDER - $pb->width(), $SIDEBORDER);

    my $sp = $self->{'sp'} = Qt::Label->new("Speed:", $self);
    $sp->adjustSize();
    $sp->move($SIDEBORDER, 45);
    my $scroll = $self->{'scroll'} =
	Qt::Slider->new(0, $LifeTimer::MAXSPEED, 50,
			   $LifeTimer::MAXSPEED / 2,
			   Qt::Slider::Horizontal, $self);
    $timer->connect($scroll, 'valueChanged(int)', 'setSpeed(int)');

    $scroll->move($sp->width() + 2 * $SIDEBORDER, 45);
    $scroll->resize(200, 15);

    $life->setFrameStyle(Qt::Frame::Panel | Qt::Frame::Sunken );
    $life->show();

    my $sel = int rand($NPATS);
    $self->getPattern($sel);

    $cb->move(2*$SIDEBORDER + $qb->width(), $SIDEBORDER);
    $cb->insertItem("Glider Gun ");
    $cb->insertItem("Figure Eight ");
    $cb->insertItem("Pulsar ");
    $cb->insertItem("Barber Pole P2 ");
    $cb->insertItem("Achim P5 ");
    $cb->insertItem("Hertz P4 ");
    $cb->insertItem("Tumbler ");
    $cb->insertItem("Pulse1 P4 ");
    $cb->insertItem("Shining Flower P5 ");
    $cb->insertItem("Pulse2 P6 ");
    $cb->insertItem("Pinwheel, Clock P4 ");
    $cb->insertItem("Pentadecatholon " );
    $cb->insertItem("Piston ");
    $cb->insertItem("Piston2 ");
    $cb->insertItem("Switch Engine ");
    $cb->insertItem("Gears (Gear, Flywheel, Blinker) " );
    $cb->insertItem("Turbine8 ");
    $cb->insertItem("P16 ");
    $cb->insertItem("Puffer ");
    $cb->insertItem("Escort ");
    $cb->insertItem("Dart Speed 1/3 ");
    $cb->insertItem("Period 4 Speed 1/2 ");
    $cb->insertItem("Another Period 4 Speed 1/2 ");
    $cb->insertItem("Smallest Known Period 3 Spaceship Speed 1/3 ");
    $cb->insertItem("Turtle Speed 1/3 ");
    $cb->insertItem("Smallest Known Period 5 Speed 2/5 ");
    $cb->insertItem("Sym Puffer ");
    $cb->insertItem("], Near Ship, Pi Heptomino ");
    $cb->insertItem("R Pentomino ");
    $cb->setAutoResize(0);
    $cb->setCurrentItem($sel);
    $cb->show();
    $self->connect($cb, 'activated(int)', 'getPattern(int)');

    my $s;
    $s = $life->minimumSize();
    $self->setMinimumSize($s->width() + 2 * $SIDEBORDER, 
			  $s->height() + $TOPBORDER + $SIDEBORDER);
    $s = $life->maximumSize();
    $self->setMaximumSize($s->width() + 2 * $SIDEBORDER, 
			  $s->height() + $TOPBORDER + $SIDEBORDER);
    $s = $life->sizeIncrement();
    $self->setSizeIncrement($s->width(), $s->height());

    $self->resize(512, 480);

    return $self;
}

sub resizeEvent {
    my $self = shift;
    my $sp = $self->{'sp'};
    my $e = shift;
    my $newsize = Qt::Size->new($e->size->width -  (2 * $SIDEBORDER),
				$e->size->height - ($TOPBORDER + $SIDEBORDER));

    $self->{'life'}->resize($newsize);

#    $self->{'life'}->resize($e->size() -
#	Qt::Size->new(2 * $SIDEBORDER, $TOPBORDER + $SIDEBORDER));
    $self->{'pb'}->move($e->size()->width() - $SIDEBORDER -
			$self->{'pb'}->width(), $SIDEBORDER);
    $self->{'scroll'}->resize($e->size()->width() - $sp->width() - 3 *
			      $SIDEBORDER, $self->{'scroll'}->height());
    $self->{'cb'}->resize($self->width() - 4*$SIDEBORDER - 
			$self->{'qb'}->width() - $self->{'pb'}->width(), 25);
}


sub getPattern {
    my $self = shift;
    my $life = $self->{'life'};
    my $pat = shift;
    $life->clear();
    my $i = $pat % $NPATS;

    my(@patt) = @{$patterns[$i]};
    while(@patt) {
	last if $patt[0] == 127;
	my $col = shift @patt;
	my $row = shift @patt;
	$col += $life->maxCol() / 2;
	$row += $life->maxRow() / 2;
	$life->setPoint($col, $row);
    }
}
