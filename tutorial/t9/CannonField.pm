package CannonField;

use Qt (%Pen %Color);

use signals 'angleChanged(int)';
use slots 'setAngle(int)';

@ISA = qw(QWidget);

sub new {
    my $self = shift->SUPER::new(@_);

    $self->{'ang'} = 45;
    return $self;
}

sub angle { return shift->{'ang'} }

sub setAngle {
    my $self = shift;
    my $degrees = shift;

    $degrees = 5 if $degrees < 5;
    $degrees = 70 if $degrees > 70;
    return if $self->{'ang'} == $degrees;
    $self->{'ang'} = $degrees;
    $self->repaint();
    emit $self->angleChanged($self->{'ang'});
}

sub paintEvent {
    my $self  = shift;
    my $p     = QPainter->new;
    my $brush = QBrush->new($Color{Blue});
    my $pen   = QPen->new($Pen{None});

    $p->begin($self);
    $p->setBrush($brush);
    $p->setPen($pen);

    $p->translate(0, $self->rect()->bottom());
    $p->drawPie(QRect->new(-35, -35, 70, 70), 0, 90*16);
    $p->rotate(-$self->{'ang'});
    $p->drawRect(QRect->new(33, -4, 15, 8));

    $p->end();
}
