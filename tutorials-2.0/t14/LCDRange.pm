package LCDRange;

use Qt 2.0;

use Qt::signals 'valueChanged(int)';
use Qt::slots 'setValue(int)', 'setRange(int,int)', 'setText(cstring)';

@ISA = qw(Qt::VBox);

sub new {
    my $text = (ref $_[1]) ? undef : splice(@_, 1, 1);
    my $self = shift->SUPER::new(@_);

    $self->init();
    $self->setText($text) if $text;

    return $self;
}

sub init {
    my $self = shift;

    my $lcd = Qt::LCDNumber->new(2, $self, 'lcd');
    my $slider =
	Qt::Slider->new(0, 99,			# range
			10,			# page steps
			0,			# initial value
			Qt::Horizontal,		# orientation
			$self, 'slider');
    my $label = Qt::Label->new(" ", $self, 'label');
    $label->setAlignment(Qt::AlignHCenter);
    $label->setFixedHeight($label->sizeHint()->height());

    $lcd->connect($slider, 'valueChanged(int)', 'display(int)');
    $self->connect($slider, 'valueChanged(int)', 'valueChanged(int)');

    @$self{'slider', 'label'} = ($slider, $label);
}

sub value { return shift->{'slider'}->value() }
sub text { return shift->{'label'}->text() }

sub setValue {
    my $self = shift;
    my $value = shift;

    $self->{'slider'}->setValue($value);
}

sub setRange {
    my $self = shift;
    my $minVal = shift;
    my $maxVal = shift;

    if($minVal < 0 || $maxVal > 99 || $minVal > $maxVal) {
	warn "LCDRange::setRange($minVal, $maxVal)
	Range must be 0..99
	and minVal must not be greater than maxVal";
	return;
    }
    $self->{'slider'}->setRange($minVal, $maxVal);
}

sub setText {
    my $self = shift;
    my $text = shift;

    $self->{'label'}->setText($text);
}
