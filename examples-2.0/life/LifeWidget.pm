package LifeWidget;

use Qt 2.0;
use Qt::slots ('nextGeneration()', 'clear()');

@ISA = qw(Qt::Frame);

$SCALE = 10;
$MAXSIZE = 50;
$MINSIZE = 10;
$BORDER = 5;

sub pos2index {
    my $x = shift;
    return int(($x - $BORDER) / $SCALE + 1);
}

sub index2pos {
    my $i = shift;
    return int(($i - 1) * $SCALE + $BORDER);
}

sub maxCol { shift->{'maxi'} }
sub maxRow { shift->{'maxj'} }

sub new {
    my $self = shift->SUPER::new(@_);

    $self->{'maxi'} = $self->{'maxj'} = 50;
    $self->setMinimumSize($MINSIZE * $SCALE + 2 * $BORDER,
			  $MINSIZE * $SCALE + 2 * $BORDER);
    $self->setMaximumSize($MAXSIZE * $SCALE + 2 * $BORDER,
			  $MAXSIZE * $SCALE + 2 * $BORDER );
    $self->setSizeIncrement($SCALE, $SCALE);

    $self->clear();
    $self->resize($self->{'maxi'} * $SCALE + 2 * $BORDER,
		  $self->{'maxj'} * $SCALE + 2 * $BORDER);

    return $self;
}


sub clear {
    my $self = shift;
    $self->{'current'} = 0;
    for(my $t = 0; $t < 2; $t++) {
	for(my $i = 0; $i < $MAXSIZE + 2; $i++) {
	    for (my $j = 0; $j < $MAXSIZE + 2; $j++) {
		$self->{'cells'}[$t][$i][$j] = 0;
	    }
	}
    }

    $self->repaint();
}


sub resizeEvent {
    my $self = shift;
    my $e = shift;
    $self->{'maxi'} = ($e->size()->width()  - 2 * $BORDER) / $SCALE;
    $self->{'maxj'} = ($e->size()->height() - 2 * $BORDER) / $SCALE;
}


sub setPoint {
    my $self = shift;
    my($i, $j) = @_;
    return if $i < 1 || $i > $self->{'maxi'} ||
	      $j < 1 || $j > $self->{'maxi'};
    $self->{'cells'}[$self->{'current'}][$i][$j] = 1;
    $self->repaint(index2pos($i), index2pos($j), $SCALE, $SCALE, 0);
}


sub mouseHandle {
    my $self = shift;
    my $pos = shift;
    my $i = pos2index($pos->x());
    my $j = pos2index($pos->y());
    $self->setPoint($i, $j);
}

sub mouseMoveEvent {
    my $self = shift;
    my $e = shift;
    $self->mouseHandle($e->pos());
}

sub mousePressEvent {
    my $self = shift;
    my $e = shift;
    $self->mouseHandle($e->pos()) if $e->button() == Qt::LeftButton;
}

sub nextGeneration() {
    my $self = shift;
    my(@cells) = @{$self->{'cells'}};
    my $current = $self->{'current'};

    for(my $i = 1; $i <= $MAXSIZE; $i++) {
	for (my $j = 1; $j <= $MAXSIZE; $j++ ) {
	    my $t = $cells[$current][$i - 1][$j - 1]
	    + $cells[$current][$i - 1][$j]
	    + $cells[$current][$i - 1][$j + 1]
	    + $cells[$current][$i][$j - 1]
	    + $cells[$current][$i][$j + 1]
	    + $cells[$current][$i + 1][$j - 1]
	    + $cells[$current][$i + 1][$j]
	    + $cells[$current][$i + 1][$j + 1];

	    $cells[!$current][$i][$j] = ( $t == 3 ||
				      $t == 2 && $cells[$current][$i][$j]);
	}
    }
    $self->{'current'} = !$current;
    $self->repaint(0);
}

sub paintEvent {
    my $self = shift;
    my $cells = $self->{'cells'};
    my $e = shift;
    my $starti = pos2index($e->rect()->left());
    my $stopi  = pos2index($e->rect()->right());
    my $startj = pos2index($e->rect()->top());
    my $stopj  = pos2index($e->rect()->bottom());

    $stopi = $self->{'maxi'} if $stopi > $self->{'maxi'};
    $stopj = $self->{'maxj'} if $stopj > $self->{'maxj'};

    my $paint = Qt::Painter->new($self);
    for(my $i = $starti; $i <= $stopi; $i++) {
	for(my $j = $startj; $j <= $stopj; $j++) {
#	    print "getting [$self->{'current'}][$i][$j]\n";
	    if($cells->[$self->{'current'}][$i][$j]) {
		my $ipos = index2pos($i);
		my $jpos = index2pos($j);
		$paint->drawShadePanel($ipos, $jpos,
				$SCALE - 1, $SCALE - 1,
$self->colorGroup());
#,0,1,undef);
	    } elsif($cells->[!$self->{'current'}][$i][$j]) {
		$paint->eraseRect(index2pos($i), index2pos($j),
				 $SCALE - 1, $SCALE - 1);
	    }
	}
    }
    $self->drawFrame($paint);
}
