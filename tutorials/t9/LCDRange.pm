package LCDRange;

use Qt 2.0;

use Qt::signals 'valueChanged(int)';
use Qt::slots 'setValue(int)', 'setRange(int,int)';

@ISA = qw(Qt::Widget);

sub new {
    my $self = shift->SUPER::new(@_);

    my $lcd = Qt::LCDNumber->new(2, $self, 'lcd');
    $lcd->move(0, 0);
    my $sBar =
	Qt::ScrollBar->new(0, 99,			# range
			1, 10,				# line/page steps
			0,				# initial value
			Qt::Horizontal,			# orientation
			$self, 'scrollbar');
    $lcd->connect($sBar, 'valueChanged(int)', 'display(int)');
    $self->connect($sBar, 'valueChanged(int)', 'valueChanged(int)');

    @$self{'sBar', 'lcd'} = ($sBar, $lcd);
    return $self;
}

sub value { return shift->{'sBar'}->value() }

sub setValue {
    my $self = shift;
    my $value = shift;

    $self->{'sBar'}->setValue($value);
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
    $self->{'sBar'}->setRange($minVal, $maxVal);
}

sub resizeEvent {
    my $self = shift;
    my($sBar, $lcd) = @$self{'sBar', 'lcd'};

    $lcd->resize($self->width(), $self->height() - 16 - 5);
    $sBar->setGeometry(0, $lcd->height() + 5, $self->width(), 16);
}
