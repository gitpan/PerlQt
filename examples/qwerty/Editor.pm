package Editor;

use Qt qw($app %Key);

use slots 'load()', 'loadFile(cstring)', 'save()', 'create()', 'print()';

@ISA = qw(QWidget);

sub new {
    my $self = shift->SUPER::new(@_);

    my $m = QMenuBar->new($self, 'menu');
    my $file = QPopupMenu->new;
    $m->insertItem('&File', $file);

    $file->insertItem('New', $self, 'create()', $Key{Alt}+$Key{N});
    $file->insertItem('Open', $self, 'load()', $Key{Alt}+$Key{O});
    $file->insertItem('Save', $self, 'save()', $Key{Alt}+$Key{S});
    $file->insertSeparator();
    $file->insertItem('Print', $self, 'print()', $Key{Alt}+$Key{P});
    $file->insertSeparator();
    $file->insertItem('Quit', $app, 'quit()', $Key{Alt}+$Key{Q});

    my $e = QMultiLineEdit->new($self, 'editor');

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

    while(<FILE>) {
	chomp;
	$e->append($_);
    }
    close(FILE);

    $e->setAutoUpdate(1);
    $e->repaint();
    $self->setCaption($fileName);
}

sub save {}

sub create {}

sub print {}
