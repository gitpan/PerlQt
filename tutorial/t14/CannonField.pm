package CannonField;

use Qt qw(%Align %Button %Color %Pen %Weight);

use POSIX 'math_h';  # No atan() in Perl.

use signals 'hit()', 'missed()', 'angleChanged(int)', 'forceChanged(int)';
use slots 'setAngle(int)', 'setForce(int)', 'shoot()', 'newTarget()';
use slots 'setGameOver()', 'restartGame()';

@ISA = qw(QWidget);

sub new {
    my $self = shift->SUPER::new(@_);

    @$self{'ang', 'f', 'shooting', 'timerCount', 'shoot_ang', 'shoot_f',
	   'gameEnded', 'barrelPressed', 'target'} =
	       (45, 0, 0, 0, 0, 0, 0, 0, QPoint->new);
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
	(0, $$self{'ang'}, $$self{'f'}, 1);
    $self->startTimer(50);
}

# You *ARE* using perl5.004 (or a beta-release), right?
# srand(time ^ $$);

sub newTarget {
    my $self = shift;

    $self->erase($self->targetRect());
    $self->{'target'} = QPoint->new(200 + rand(65536) % 190,
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
    if(($shotR->x() > $self->width() || $shotR->y() > $self->height()) ||
       $shotR->intersects($self->barrierRect())) {
	$self->stopShooting();
	emit $self->missed();
	return;
    }
    $self->repaint($shotR, 0);
}

sub paintEvent {
    my $self = shift;
    my $updateR = shift->rect();
    my $p = QPainter->new;
    $p->begin($self);

    $self->paintCannon($p) if $updateR->intersects($self->cannonRect());
    $self->paintBarrier($p) if $updateR->intersects($self->barrierRect());
    if($self->{'gameEnded'}) {
	$p->setPen($Color{Black});
	$p->setFont(QFont->new('Courier', 48, $Weight{Bold}));
	$p->drawText($self->rect(), $Align{Center}, 'Game Over');
    } else {
	$self->paintShot($p) if $self->isShooting() &&
	    $updateR->intersects($self->shotRect());
	$self->paintTarget($p) if $updateR->intersects($self->targetRect());
    }
    $p->end();
}

sub mousePressEvent {
    my $self = shift;
    my $e = shift;

    return if $e->button() != $Button{Left};
    $self->{'barrelPressed'} = 1 if $self->barrelHit($e->pos());
}

sub mouseMoveEvent {
    my $self = shift;
    my $e = shift;

    return unless $self->{'barrelPressed'};
    my $pnt = $e->pos();
    $pnt->setX(1) if $pnt->x() <= 0;
    $pnt->setY($self->height() - 1) if $pnt->y() >= $self->height();
    my $rad = atan(($self->rect()->bottom() - $pnt->y()) / $pnt->x());
    $self->setAngle($rad*180/3.14159265);
}

sub mouseReleaseEvent {
    my $self = shift;
    my $e = shift;

    $self->{'barrelPressed'} = 0 if $e->button() == $Button{Left};
}

sub stopShooting {
    my $self = shift;

    $self->{'shooting'} = 0;
    $self->killTimers();
}

sub paintShot {
    my $self = shift;
    my $p = shift;

    $p->setBrush($Color{Black});
    $p->setPen($Pen{None});
    $p->drawRect($self->shotRect());
}

sub paintTarget {
    my $self = shift;
    my $p = shift;

    $p->setBrush($Color{Red});
    $p->setPen($Color{Black});
    $p->drawRect($self->targetRect());
}

sub paintBarrier {
    my $self = shift;
    my $p = shift;

    $p->setBrush($Color{Yellow});
    $p->setPen($Color{Black});
    $p->drawRect($self->barrierRect());
}

$barrel_rect = QRect->new(33, -4, 15, 8);

sub paintCannon {
    my $self = shift;
    my $p = shift;
    my $cr = $self->cannonRect();
    my $pix = QPixmap->new($cr->size());
    my $tmp = QPainter->new;

    $pix->fill($self, $cr->topLeft());

    $tmp->begin($pix);
    $tmp->setBrush($Color{Blue});
    $tmp->setPen($Pen{None});

    $tmp->translate(0, $pix->height() - 1);
    $tmp->drawPie(QRect->new(-35, -35, 70, 70), 0, 90*16);
    $tmp->rotate(-$self->{'ang'});
    $tmp->drawRect($barrel_rect);
    $tmp->end();

    $p->drawPixmap($cr->topLeft(), $pix);
}

sub cannonRect {
    my $self = shift;
    my $r = QRect->new(0, 0, 50, 50);

    $r->moveBottomLeft($self->rect()->bottomLeft());
    return $r;
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

    my $r = QRect->new(0, 0, 6, 6);
    $r->moveCenter(QPoint->new($x, $self->height() - 1 - $y));
    return $r;
}

sub targetRect {
    my $self = shift;
    my $target = $self->{'target'};
    my $r = QRect->new(0, 0, 20, 10);

    $r->moveCenter(QPoint->new($target->x(), $self->height() - 1 -
			       $target->y()));
    return $r;
}

sub barrierRect {
    my $self = shift;

    return QRect->new(145, $self->height() - 100, 15, 100);
}

sub barrelHit {
    my $self = shift;
    my $p = shift;
    my $mtx = QWMatrix->new;

    $mtx->translate(0, $self->height() - 1);
    $mtx->rotate(-$self->{'ang'});
    $mtx = $mtx->invert();
    return $barrel_rect->contains($mtx->map($p));
}
