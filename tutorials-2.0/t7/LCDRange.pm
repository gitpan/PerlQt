package LCDRange;

use Qt 2.0;

use Qt::signals 'valueChanged(int)';
use Qt::slots 'setValue(int)';

@ISA = qw(Qt::VBox);

sub new {
    my $self = shift->SUPER::new(@_);

    my $lcd = Qt::LCDNumber->new(2, $self, 'lcd');
    my $slider = Qt::Slider->new(Qt::Horizontal, $self, 'slider');
    $slider->setRange(0, 99);
    $slider->setValue(0);
    $lcd->connect($slider, 'valueChanged(int)', 'display(int)');
    $self->connect($slider, 'valueChanged(int)', 'valueChanged(int)');

    $self->{'slider'} = $slider;
    return $self;
}

sub value { return shift->{'slider'}->value() }

sub setValue {
    my $self = shift;
    my $value = shift;

    $self->{'slider'}->setValue($value);
}
