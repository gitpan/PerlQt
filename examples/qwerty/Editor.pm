package Editor;

use Qt;
use QMenuBar;
use QMultiLineEdit;
use QPopupMenu;
use QWidget;

use slots 'load()', 'loadFile(string)', 'save()', 'create()', 'print()';

@ISA = qw(QWidget);

sub new {
    my $self = shift->SUPER::new(@_);

    my $m = new QMenuBar($self, 'menu');
    my $file = new QPopupMenu->setImmortal;
    $m->insertItem('&File', $file);

    $file->insertItem('New', $self, 'create()', $ALT+$Key{N});
    $file->insertItem('Open', $self, 'load()', $ALT+$Key{O});
    $file->insertItem('Save', $self, 'save()', $ALT+$Key{S});
    $file->insertSeparator();
    $file->insertItem('Print', $self, 'print()', $ALT+$Key{P});
    $file->insertSeparator();
    $file->insertItem('Quit', $qApp, 'quit()', $ALT+$Key{Q});

    my $e = new QMultiLineEdit($self, 'editor');

    @$self{'m', 'e'} = ($m, $e);
    return $self;
}

sub resizeEvent {
    my $self = shift;
    my($m, $e) = @$self{'m', 'e'};

    if($m && $e) {
	$e->setGeometry(0, $m->height(), $self->width(),
			$self->height() - $m->height());
    }
}

sub load {
    my $self = shift;
    my $fn = QFileDialog::getOpenFileName();

    $self->loadFile($fn) if $fn;
}

sub loadFile {
    my $self = shift;
    my $e = $$self{'e'};
    my $fileName = shift;

    open(FILE, $fileName) || return;

    $e->setAutoUpdate(0);
    $e->clear();

    $e->append($_) while defined($_ = <FILE>);

    close(FILE);

    $e->setAutoUpdate(1);
    $e->repaint();
    $self->setCaption($fileName);
}

sub save {}

sub create {}

sub print {}
