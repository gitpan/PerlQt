package GameBoard;

use Qt 2.0;
use Qt::app;

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

    my $frame = Qt::Frame->new($self, 'cannonFrame');
    $frame->setFrameStyle(Qt::Frame::WinPanel | Qt::Frame::Sunken);

    my $cannonField = new CannonField($self, 'cannonField');
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

    my $accel = Qt::Accel->new($self);
    $accel->connectItem($accel->insertItem(Qt::Key_Space), $self, 'fire()');
    $accel->connectItem($accel->insertItem(Qt::Key_Q), $app, 'quit()');

    $quit->setGeometry(10, 10, 75, 30);
    $angle->setGeometry(10, $quit->y() + $quit->height() + 10, 75, 130);
    $force->setGeometry(10, $angle->y() + $angle->height() + 10, 75, 130);
    $frame->move($angle->x() + $angle->width() + 10, $angle->y());
    $cannonField->move($frame->x() + 2, $frame->y() + 2);
    $shoot->setGeometry(10, 315, 75, 30);
    $restart->setGeometry(380, 10, 110, 30);
    $hits->setGeometry(130, 10, 40, 30);
    $hitsL->setGeometry($hits->x() + $hits->width() + 5, 10, 60, 30);
    $shotsLeft->setGeometry(240, 10, 40, 30 );
    $shotsLeftL->setGeometry($shotsLeft->x() + $shotsLeft->width() + 5, 10,
			     60, 30);

    @$self{'quit', 'angle', 'force', 'frame', 'cannonField', 'shoot',
	   'restart', 'hits', 'hitsL', 'shotsLeft', 'shotsleftL' , 'accel'} =
	($quit, $angle, $force, $frame, $cannonField, $shoot, $restart, $hits,
	 $hitsL, $shotsLeft, $shotsLeftL, $accel);
    $self->newGame();

    return $self;
}

sub resizeEvent {
    my $self = shift;
    my($frame, $cannonField) = @$self{'frame', 'cannonField'};

    $frame->resize($self->width()  - $frame->x() - 10,
		   $self->height() - $frame->y() - 10);
    $cannonField->resize($frame->width() - 4, $frame->height() - 4);
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
