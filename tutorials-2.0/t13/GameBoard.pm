package GameBoard;

use Qt 2.0;
import Qt::app;

use CannonField;
use LCDRange;

use Qt::slots 'fire()', 'hit()', 'missed()', 'newGame()';

@ISA = qw(Qt::Widget);

sub new {
    my $self = shift->SUPER::new(@_);

    $self->setMinimumSize(500, 355);

    my $quit = Qt::PushButton->new('Quit', $self, 'quit');
    $quit->setFont(Qt::Font->new('Times', 18, Qt::Font::Bold));

    $app->connect($quit, 'clicked()', 'quit()');

    my $angle = LCDRange->new('ANGLE', $self, 'angle');
    $angle->setRange(5, 70);

    my $force = LCDRange->new('FORCE', $self, 'force');
    $force->setRange(10, 50);

    my $cannonField = CannonField->new($self, 'cannonField');
    $cannonField->setBackgroundColor(Qt::Color->new(250, 250, 200));

    $cannonField->connect($angle, 'valueChanged(int)', 'setAngle(int)');
    $angle->connect($cannonField, 'angleChanged(int)', 'setValue(int)');

    $cannonField->connect($force, 'valueChanged(int)', 'setForce(int)');
    $force->connect($cannonField, 'forceChanged(int)', 'setValue(int)');

    $self->connect($cannonField, 'hit()', 'hit()');
    $self->connect($cannonField, 'missed()', 'missed()');

    $angle->setValue(60);
    $force->setValue(25);

    my $shoot = Qt::PushButton->new('Shoot', $self, 'shoot');
    $shoot->setFont(Qt::Font->new('Times', 18, Qt::Font::Bold));

    $self->connect($shoot, 'clicked()', 'fire()');

    my $restart = Qt::PushButton->new('New Game', $self, 'newgame');
    $restart->setFont(Qt::Font->new('Times', 18, Qt::Font::Bold));

    $self->connect($restart, 'clicked()', 'newGame()');

    my $hits = Qt::LCDNumber->new(2, $self, 'hits');
    my $shotsLeft = Qt::LCDNumber->new(2, $self, 'shotsleft');
    my $hitsL = Qt::Label->new('HITS', $self, 'hitsLabel');
    my $shotsLeftL = Qt::Label->new('SHOTS LEFT', $self, 'shotsleftLabel');



    my $grid = Qt::GridLayout->new($self, 2, 2, 10);
    $grid->addWidget($quit, 0, 0);
    $grid->addWidget($cannonField, 1, 1);
    $grid->setColStretch(1, 10);

    my $leftBox = Qt::VBoxLayout->new;
    $grid->addLayout($leftBox, 1, 0);
    $leftBox->addWidget($angle);
    $leftBox->addWidget($force);

    my $topBox = Qt::HBoxLayout->new;
    $grid->addLayout($topBox, 0, 1);
    $topBox->addWidget($shoot);
    $topBox->addWidget($hits);
    $topBox->addWidget($hitsL);
    $topBox->addWidget($shotsLeft);
    $topBox->addWidget($shotsLeftL);
    $topBox->addStretch(1);
    $topBox->addWidget($restart);

    @$self{'hits', 'shotsLeft', 'cannonField'} =
	($hits, $shotsLeft, $cannonField);
    $self->newGame();

    return $self;
}

sub fire {
    my $self = shift;
    my($cannonField, $shotsLeft) = @$self{'cannonField', 'shotsLeft'};

    return if $cannonField->gameOver() || $cannonField->isShooting();
    $shotsLeft->display($shotsLeft->intValue() - 1);
    $cannonField->shoot();
}

sub hit {
    my $self = shift;
    my($hits, $cannonField, $shotsLeft) =
	@$self{'hits', 'cannonField', 'shotsLeft'};

    $hits->display($hits->intValue() + 1);
    if($shotsLeft->intValue() == 0) { $cannonField->setGameOver() }
    else { $cannonField->newTarget() }
}

sub missed {
    my $self = shift;
    my($cannonField, $shotsLeft) = @$self{'cannonField', 'shotsLeft'};

    $cannonField->setGameOver() if $shotsLeft->intValue() == 0;
}

sub newGame {
    my $self = shift;
    my($hits, $cannonField, $shotsLeft) =
	@$self{'hits', 'cannonField', 'shotsLeft'};

    $shotsLeft->display(15);
    $hits->display(0);
    $cannonField->restartGame();
    $cannonField->newTarget();
}
