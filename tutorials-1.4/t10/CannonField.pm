package CannonField;

use Qt 2.0;

use Qt::signals 'angleChanged(int)', 'forceChanged(int)';
use Qt::slots 'setAngle(int)', 'setForce(int)';

@ISA = qw(Qt::Widget);

sub new {
    my $self = shift->SUPER::new(@_);

    @$self{'ang', 'f'} = (45, 0);
    return $self;
}

sub angle { return shift->{'ang'} }
sub force { return shift->{'f'} }

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

sub paintEvent {
    my $self = shift;
    my $updateR = shift->rect();
    my $p = Qt::Painter->new;

    $p->begin($self);
    $self->paintCannon($p) if $updateR->intersects($self->cannonRect());
    $p->end();
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
