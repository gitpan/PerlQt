package Table;

use Qt 2.0;

@ISA = qw(Qt::TableView);

sub new ($$$;@) {
    my $class = shift;
    my $numRows = shift;
    my $numCols = shift;
    my $self = $class->SUPER::new(@_);

    @$self{'curRow', 'curCol'} = (0, 0);
    $self->setFocusPolicy(Qt::Widget::StrongFocus);
    $self->setBackgroundColor(Qt::white);
    $self->setNumCols($numCols);
    $self->setNumRows($numRows);
    $self->setCellWidth(100);
    $self->setCellHeight(30);
    $self->setTableFlags(Qt::Tbl_vScrollBar |
			 Qt::Tbl_hScrollBar |
			 Qt::Tbl_clipCellPainting |
			 Qt::Tbl_smoothScrolling);
    $self->resize(400, 200);

    $self->{'contents'} = [];

    return $self;
}

#
# Return content of cell
#

sub cellContent {
    my $self = shift;
    my $contents = $self->{'contents'};
    my $row = shift;
    my $col = shift;

    return $contents->[$self->indexOf($row, $col)];
}

#
# Set content of cell
#

sub setCellContent {
    my $self = shift;
    my($contents, $curRow, $curCol) = @$self{'contents', 'curRow', 'curCol'};
    my $row = shift;
    my $col = shift;
    my $c = shift;

    $contents->[$self->indexOf($row, $col)] = $c;
    $self->updateCell($row, $col);
}

#
# Handles cell painting for the Table widget.
#

sub paintCell {
    my $self = shift;
    my($contents, $curRow, $curCol) = @$self{'contents', 'curRow', 'curCol'};
    my $p = shift;
    my $row = shift;
    my $col = shift;
    my $w = $self->cellWidth($col);
    my $h = $self->cellHeight($row);
    my $x2 = $w - 1;
    my $y2 = $h - 1;

    #
    # Draw our part of cell frame.
    #

    $p->drawLine($x2, 0, $x2, $y2);
    $p->drawLine(0, $y2, $x2, $y2);

    #
    # Draw extra frame inside if this is the current cell.
    #

    if(($row == $curRow) && ($col == $curCol)) {
	if($self->hasFocus()) {
	    $p->drawRect(0, 0, $x2, $y2);
	} else {
	    $p->setPen(Qt::DotLine);
	    $p->drawRect(0, 0, $x2, $y2);
	    $p->setPen(Qt::SolidLine);
	}
    }
    
    #
    # Draw cell content (text)
    #

    $p->drawText(0, 0, $w, $h, Qt::AlignCenter,
		 $contents->[$self->indexOf($row, $col)]);
}

#
# Handles mouse press events for the Table widget.
# The current cell marker is set to the cell the mouse is clicked in.
#

sub mousePressEvent {
    my $self = shift;
    my $e = shift;
    my($oldRow, $oldCol) = @$self{'curRow', 'curCol'};
    my $clickedPos = $e->pos();
    my $curRow = $self->findRow($clickedPos->y());
    my $curCol = $self->findCol($clickedPos->x());
    if(($curRow != $oldRow) ||
       ($curCol != $oldCol)) {
	@$self{'curRow', 'curCol'} = ($curRow, $curCol);
	$self->updateCell($oldRow, $oldCol);
	$self->updateCell($curRow, $curCol);
    }
}

#
# Handles key press events for the Table widget.
# Allows moving the current cell marker around with the arrow keys
#

sub keyPressEvent {
    my $self = shift;
    my $e = shift;
    my($curRow, $curCol) = @$self{'curRow', 'curCol'};
    my($oldRow, $oldCol) = @$self{'curRow', 'curCol'};
    my $edge = 0;
    $_ = $e->key();

    if($_ == Qt::Key_Left) {
	if($curCol > 0) {
	    $curCol--;
	    $edge = $self->leftCell();
	    $self->setLeftCell($edge - 1)
		if($curCol < $edge);
	}
    } elsif($_ == Qt::Key_Right) {
	if($curCol < $self->numCols()-1) {
	    $curCol++;
	    $edge = $self->lastColVisible();
	    $self->setLeftCell($self->leftCell() + 1)
		if($curCol >= $edge);
	}
    } elsif($_ == Qt::Key_Up) {
	if($curRow > 0) {
	    $curRow--;
	    $edge = $self->topCell();
	    $self->setTopCell($edge - 1)
		if($curRow < $edge);
	}
    } elsif($_ == Qt::Key_Down) {
	if($curRow < $self->numRows()-1) {
	    $curRow++;
	    $edge = $self->lastRowVisible();
	    $self->setTopCell($self->topCell()+1)
		if($curRow >= $edge);
	}
    } else {
	$e->ignore();
	return;
    }

    if(($curRow != $oldRow) ||
       ($curCol != $oldCol)) {
	@$self{'curRow', 'curCol'} = ($curRow, $curCol);
	$self->updateCell($oldRow, $oldCol);
	$self->updateCell($curRow, $curCol);
    }
}

#
# Handles focus reception events for the Table widget.
# Repaint only the current cell; to avoid flickering
#

sub focusInEvent {
    my $self = shift;
    my($curRow, $curCol) = @$self{'curRow', 'curCol'};

    $self->updateCell($curRow, $curCol);
}

#
# Handles focus loss events for the Table widget.
# Repaint only the current cell; to avoid flickering
#

sub focusOutEvent {
    my $self = shift;
    my($curRow, $curCol) = @$self{'curRow', 'curCol'};

    $self->updateCell($curRow, $curCol);
}

#
# Utility function for mapping from 2D table to 1D array
#

sub indexOf {
    my $self = shift;
    my $row = shift;
    my $col = shift;

    return ($row * $self->numCols()) + $col;
}
