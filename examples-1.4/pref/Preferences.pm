package Preferences;

use Qt 2.0;

use Qt::slots 'setup()', 'apply()';

@ISA = qw(Qt::Label);

sub new {
    my $self = shift->SUPER::new(@_);
    my $tab = Qt::TabDialog->new(undef, 'top-level dialog');
    $tab->setCaption('Ugly Tab Dialog');

    # set up page one of the tab dialog
    my $w = Qt::Widget->new($tab, 'page one');

    # stuff the labels and lineedits into a grid layout
    my $g = Qt::GridLayout->new($w, 2, 2, 5);

    # two multilineedits in column 1
    my $ed1 = Qt::MultiLineEdit->new($w);
    $g->addWidget($ed1, 0, 1);
    $ed1->setText('');
    $ed1->setMinimumSize(Qt::Size->new(100, 10));
    my $ed2 = Qt::MultiLineEdit->new($w);
    $g->addWidget($ed2, 1, 1);
    $ed2->setText('');
    $ed2->setMinimumSize(Qt::Size->new(100, 10));

    # let the lineedits stretch
    $g->setColStretch(1, 1);

    # two labels in column 0
    my $l = Qt::Label->new($w);
    $g->addWidget($l, 0, 0);
    $l->setText('&Name');
    $l->setBuddy($ed1);
    $l->setMinimumSize($l->sizeHint());
    $l = Qt::Label->new($w);
    $g->addWidget($l, 1, 0);
    $l->setText('&Email');
    $l->setBuddy($ed2);
    $l->setMinimumSize($l->sizeHint());

    # no stretch on the labels unless they have to
    $g->setColStretch(0, 0);

    # finally insert page one into the tab dialog and start GM
    $tab->addTab($w, 'Who');
    $g->activate();

    # that was page one, now for page two, where we use a box layout
    $w = Qt::Widget->new($tab, 'page two');
    my $b = Qt::BoxLayout->new($w, Qt::BoxLayout::LeftToRight, 5);

    # two vertical boxes in the horizontal one
    my $radioBoxes = Qt::BoxLayout->new(Qt::BoxLayout::Down);
    $b->addLayout($radioBoxes);

    # fill the leftmost vertical box
    my $b1 = Qt::RadioButton->new($w, 'radio button 1');
    $b1->setText('Male');
    $b1->setMinimumSize($b1->sizeHint());
    $b1->setMaximumSize(500, $b1->minimumSize()->height());
    $radioBoxes->addWidget($b1, Qt::AlignLeft|Qt::AlignTop);
    my $b2 = Qt::RadioButton->new($w, 'radio button 2');
    $b2->setText('Female');
    $b2->setMinimumSize($b2->sizeHint());
    $b2->setMaximumSize(500, $b2->minimumSize()->height());
    $radioBoxes->addWidget($b2, Qt::AlignLeft|Qt::AlignTop);
    my $b3 = Qt::RadioButton->new($w, 'radio button 3');
    $b3->setText('Duo Pack');
    $b3->setMinimumSize($b3->sizeHint());
    $b3->setMaximumSize(500, $b3->minimumSize()->height());
    $radioBoxes->addWidget($b3, Qt::AlignLeft|Qt::AlignTop);

    # since none of those will stretch, add some stretch at the bottom
    $radioBoxes->addStretch(1);

    # insert all of the radio boxes into the button group, so they'll
    # switch each other off
    my $bg = Qt::ButtonGroup->new;
    $bg->insert($b1);
    $bg->insert($b2);
    $bg->insert($b3);

    # add some optional spacing between the radio buttons and the slider
    $b->addStretch(1);

    # make the central slider
    my $mood = Qt::Slider->new(Qt::Slider::Vertical, $w, 'mood slider');
    $mood->setRange(0, 127);
    $mood->setMinimumSize($mood->sizeHint());
    $mood->setMaximumSize($mood->minimumSize->width(), 500);
    $b->addWidget($mood, Qt::AlignLeft|Qt::AlignTop|Qt::AlignBottom);

    # make the top and bottom labels for the slider
    my $labels = Qt::BoxLayout->new(Qt::BoxLayout::Down);
    $b->addLayout($labels);
    $b->addLayout($labels);
    $l = Qt::Label->new('Optimistic', $w, 'optimistic');
    $l->setFixedSize($l->sizeHint());
    $labels->addWidget($l, Qt::AlignTop|Qt::AlignLeft);

    # spacing in the middle, so the labels are located right
    $labels->addStretch(1);

    $l = Qt::Label->new('Pessimistic', $w, 'pessimistic');
    $l->setFixedSize($l->sizeHint());
    $labels->addWidget($l, Qt::AlignBottom|Qt::AlignLeft);

    $b->activate();
    $tab->addTab($w, 'How');

    # we want both Apply and Cancel
    $tab->setApplyButton();
    $tab->setCancelButton();

    $self->connect($tab, 'applyButtonPressed()', 'apply()');
    $self->connect($tab, 'cancelButtonPressed()', 'setup()');
    $self->connect($tab, 'aboutToShow()', 'setup()');

    $tab->resize(200, 135);

    $self->setText("This tab dialog is rather ugly:  " .
		   "The code is clear, though:\n" .
		   "There are no hard-to-understand aesthetic tradeoffs\n");

    @$self{'ed1', 'ed2', 'bg', 'b1', 'b2', 'b3', 'mood'} =
	($ed1, $ed2, $bg, $b1, $b2, $b3, $mood);

    $self->show();
    $tab->show();
    return $self;
}

sub setup {
    my $self = shift;
    my($ed1, $ed2, $b1, $mood) = @$self{'ed1', 'ed2', 'b1', 'mood'};

    $ed1->setText('Perl Qt');
    $ed2->setText('perlqt@pig.org');

    $b1->setChecked(1);

    $mood->setValue(42);
}

sub apply {
    my $self = shift;
    my($ed1, $ed2, $b1, $b2, $b3, $mood) =
	@$self{'ed1', 'ed2', 'b1', 'b2', 'b3', 'mood'};
    my $s = sprintf("What the dialog decided:\n" .
		    "\tLine Edit 1: %s\n\tLineEdit 2: %s\n" .
		    "\tMood: %d (0 == down, 127 == up)\n" .
		    "\tButtons: %s %s %s\n",
		    $ed1->text(), $ed2->text(),
		    $mood->value(),
		    $b1->isChecked() ? 'X' : '-',
		    $b2->isChecked() ? 'X' : '-',
		    $b3->isChecked() ? 'X' : '-');
    $self->setText($s);
    my $sh = $self->sizeHint();
    my $b = 0;

    if($sh->width() > $self->width()) {
	$sh->setWidth($self->width());
	$b = 1;
    }
    if($sh->height() > $self->height()) {
	$sh->setHeight($self->height());
	$b = 1;
    }

    $self->resize($sh) if $b;

    $self->repaint();
}
