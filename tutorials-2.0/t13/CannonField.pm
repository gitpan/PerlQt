package CannonField;

use Qt 2.0;

use Qt::signals 'hit()', 'missed()', 'angleChanged(int)', 'forceChanged(int)';
use Qt::slots 'setAngle(int)', 'setForce(int)', 'shoot()', 'newTarget()';
use Qt::slots 'setGameOver()', 'restartGame()';

@ISA = qw(Qt::Widget);

sub new {
    my $self = shift->SUPER::new(@_);

    @$self{'ang', 'f', 'shooting', 'timerCount', 'shoot_ang', 'shoot_f',
	   'gameEnded', 'target'} = (45, 0, 0, 0, 0, 0, 0, Qt::Point->new);
    $self->newTarget();

    return $self;
}

sub angle { return shift->{'ang'} }
sub force { return shift->{'f'} }
sub gameOver { return shift->{'gameEnded'} }
sub isShooting { return shift->{'shooting'} }

sub setAngle {
    my $self = shift;
    my $degrees = shift;

    $degrees = 5 if $degrees < 5;
    $degrees = 70 if $degrees > 70;
    return if $self->{'ang'} == $degrees;
    $self->{'ang'} = $degrees;
    $self->repaint($self->cannonRect(), 0);
    emit $self->angleChanged($self->{'ang'});
}

sub setForce {
    my $self = shift;
    my $newton = shift;

    $newton = 0 if $newton < 0;
    return if $self->{'f'} == $newton;
    $self->{'f'} = $newton;
    emit $self->forceChanged($self->{'f'});
}

sub shoot {
    my $self = shift;

    return if $self->{'shooting'};
    @$self{'timerCount', 'shoot_ang', 'shoot_f', 'shooting'} =
	(0, $self->{'ang'}, $self->{'f'}, 1);
    $self->startTimer(50);
}

# You *ARE* using perl5.004 or above, right?
# srand(time ^ $$);

sub newTarget {
    my $self = shift;
    $self->erase($self->targetRect());
    $self->{'target'} = Qt::Point->new(200 + rand(65536) % 190,
				       10  + rand(65536) % 255);
    $self->repaint($self->targetRect());
}

sub setGameOver {
    my $self = shift;

    return if $self->{'gameEnded'};
    $self->stopShooting() if $self->{'shooting'};
    $self->{'gameEnded'} = 1;
    $self->repaint();
}

sub restartGame {
    my $self = shift;

    $self->stopShooting() if $self->{'shooting'};
    $self->{'gameEnded'} = 0;
    $self->repaint();
}

sub timerEvent {
    my $self = shift;

    $self->erase($self->shotRect());
    $self->{'timerCount'}++;

    my $shotR = $self->shotRect();

    if($shotR->intersects($self->targetRect())) {
	$self->stopShooting();
	emit $self->hit();
	return;
    }
    if($shotR->x() > $self->width() || $shotR->y() > $self->height()) {
	$self->stopShooting();
	emit $self->missed();
	return;
    }
    $self->repaint($shotR, 0);
}

sub paintEvent {
    my $self = shift;
    my $updateR = shift->rect();
    my $p = Qt::Painter->new;
    $p->begin($self);

    $self->paintCannon($p) if $updateR->intersects($self->cannonRect());
    if($self->{'gameEnded'}) {
	$p->setPen(Qt::black);
	$p->setFont(Qt::Font->new('Courier', 48, Qt::Font::Bold));
	$p->drawText($self->rect(), Qt::AlignCenter, 'Game Over');
    } else {
	$self->paintShot($p) if $self->isShooting() &&
	    $updateR->intersects($self->shotRect());
	$self->paintTarget($p) if $updateR->intersects($self->targetRect());
    }
    $p->end();
}

sub stopShooting {
    my $self = shift;

    $self->{'shooting'} = 0;
    $self->killTimers();
}

sub paintShot {
    my $self = shift;
    my $p = shift;

    $p->setBrush(Qt::black);
    $p->setPen(Qt::NoPen);
    $p->drawRect($self->shotRect());
}

sub paintTarget {
    my $self = shift;
    my $p = shift;

    $p->setBrush(Qt::red);
    $p->setPen(Qt::black);
    $p->drawRect($self->targetRect());
}

$barrel_rect = Qt::Rect->new(33, -4, 15, 8);

sub paintCannon {
    my $self = shift;
    my $p = shift;
    my $cr = $self->cannonRect();
    my $pix = Qt::Pixmap->new($cr->size());
    my $tmp = Qt::Painter->new;

    $pix->fill($self, $cr->topLeft());

    $tmp->begin($pix);
    $tmp->setBrush(Qt::blue);
    $tmp->setPen(Qt::NoPen);

    $tmp->translate(0, $pix->height() - 1);
    $tmp->drawPie(Qt::Rect->new(-35, -35, 70, 70), 0, 90*16);
    $tmp->rotate(-$self->{'ang'});
    $tmp->drawRect($barrel_rect);
    $tmp->end();

    $p->drawPixmap($cr->topLeft(), $pix);
}

sub cannonRect {
    my $self = shift;
    my $r = Qt::Rect->new(0, 0, 50, 50);

    $r->moveBottomLeft($self->rect()->bottomLeft());
    return $r;
}

sub qRound {
    my $d = shift;
    return $d > 0.0 ? int($d+0.5) : int($d-0.5);
}

sub shotRect {
    my $self = shift;

    my $gravity  = 4;

    my $time     = $self->{'timerCount'}/4.0;
    my $velocity = $self->{'shoot_f'}/0.7;
    my $radians  = $self->{'shoot_ang'}*3.14159265/180;

    my $velx = $velocity*cos($radians);
    my $vely = $velocity*sin($radians);
    my $x0   = ($barrel_rect->right() + 5)*cos($radians);
    my $y0   = ($barrel_rect->right() + 5)*sin($radians);
    my $x    = $x0 + $velx*$time;
    my $y    = $y0 + $vely*$time - $gravity*$time*$time;

    my $r = Qt::Rect->new(0, 0, 6, 6);
    $r->moveCenter(Qt::Point->new(qRound($x), $self->height() - 1 - qRound($y)));
    return $r;
}

sub targetRect {
    my $self = shift;
    my $target = $self->{'target'};
    my $r = Qt::Rect->new(0, 0, 20, 10);

    $r->moveCenter(Qt::Point->new($target->x(), $self->height() - 1 -
			          $target->y()));
    return $r;
}
