package Editor;

use Qt 2.0;
import Qt::app;

use Qt::slots 'load()', 'loadFile(string)', 'save()', 'create()', 'print()';

@ISA = qw(Qt::Widget);

sub new {
    my $self = shift->SUPER::new(@_);

    my $m = Qt::MenuBar->new($self, 'menu');
    my $file = Qt::PopupMenu->new;
    $m->insertItem('&File', $file);

    $file->insertItem('New', $self, 'create()', Qt::ALT+Qt::Key_N);
    $file->insertItem('Open', $self, 'load()', Qt::ALT+Qt::Key_O);
    $file->insertItem('Save', $self, 'save()', Qt::ALT+Qt::Key_S);
    $file->insertSeparator();
    $file->insertItem('Print', $self, 'print()', Qt::ALT+Qt::Key_P);
    $file->insertSeparator();
    $file->insertItem('Quit', $app, 'quit()', Qt::ALT+Qt::Key_Q);

    my $e = Qt::MultiLineEdit->new($self, 'editor');

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
    my $fn = Qt::FileDialog::getOpenFileName();

    $self->loadFile($fn) if $fn;
}

sub loadFile {
    my $self = shift;
    my $e = $self->{'e'};
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
