package ApplicationWindow;

use Qt 2.0;
use Qt::app;
use Qt::slots (
    'newDoc()',
    'load()',
    'loadFile(cstring)',
    'save()',
    'print()',
    'closeDoc()',
    'toggleMenuBar()',
    'toggleStatusBar()',
    'toggleToolBar()'
);

@ISA = qw(Qt::MainWindow);

sub readxpm {
    my $xpm = shift;
    open(XPM, $xpm) || return [];
    $str = join('', <XPM>);
    close(XPM);
    $str =~ s/^.*\{(.*)\}.*/\@xpm = ($1)/s;
    my @xpm;
    eval "$str";
    return \@xpm;
}

$fileopen = readxpm("fileopen.xpm");
$filesave = readxpm("filesave.xpm");
$fileprint = readxpm("fileprint.xpm");

my $fileOpenText = "Click this button to open a new file.\n\n" .
"You can also select the Open command from the File menu.";
my $fileSaveText = "Click this button to save the file you are " .
"editing.  You will be prompted for a file name.\n\n" .
"You can also select the Save command from the File menu.\n\n" .
"Note that implementing this function is left as an exercise for the reader.";
my $filePrintText = "Click this button to print the file you " .
"are editing.\n\n" .
"You can also select the Print command from the File menu.";

sub new {
    my $self = shift->SUPER::new(undef, "example application main window");
    my $printer = $self->{'printer'} = Qt::Printer->new;
    $printer->setMinMax(1, 10);

    my $fileTools = $self->{'fileTools'} =
	Qt::ToolBar->new($self, 'file operations');

    my $openIcon = $self->{'openIcon'} = Qt::Pixmap->new($fileopen);
    my $fileOpen = Qt::ToolButton->new($openIcon, "Open File", undef,
				       $self, 'load()',
				       $fileTools, "open file");

    my $saveIcon = $self->{'saveIcon'} = Qt::Pixmap->new($filesave);
    my $fileSave = Qt::ToolButton->new($saveIcon, "Save File", undef,
				       $self, 'save()',
				       $fileTools, "save file");

    my $printIcon = $self->{'printIcon'} = Qt::Pixmap->new($fileprint);
    my $filePrint = Qt::ToolButton->new($printIcon, "Print File", undef,
					$self, 'print()',
					$fileTools, "print file");

    Qt::WhatsThis::whatsThisButton($fileTools);
    Qt::WhatsThis::add($fileOpen, $fileOpenText, 0);
    Qt::WhatsThis::add($fileSave, $fileSaveText, 0);
    Qt::WhatsThis::add($filePrint, $filePrintText, 0);

    my $file = Qt::PopupMenu->new;
    $self->menuBar()->insertItem('&File', $file);

    $file->insertItem("New", $self, 'newDoc()', Qt::CTRL+Qt::Key_N);
    $file->insertItem($openIcon, "Open", $self, 'load()', Qt::CTRL+Qt::Key_O);
    $file->insertItem($saveIcon, "Save", $self, 'save()', Qt::CTRL+Qt::Key_S);
    $file->insertSeparator();
    $file->insertItem($printIcon, "Print", $self, 'print()', Qt::CTRL+Qt::Key_P);
    $file->insertSeparator();
    $file->insertItem("Close", $self, 'closeDoc()', Qt::CTRL+Qt::Key_W);
    $file->insertItem("Quit", $app, 'quit()', Qt::CTRL+Qt::Key_Q);

    my $controls = $self->{'controls'} = Qt::PopupMenu->new;
    $self->menuBar()->insertItem("&Controls", $controls);

    my $mb = $self->{'mb'} = 
	$controls->insertItem("Menu bar", $self, 'toggleMenuBar()', Qt::CTRL+Qt::Key_M);
    # Now an accelerator for when the menubar is invisible!
    my $a = Qt::Accel->new($self);
    $a->connectItem($a->insertItem(Qt::CTRL+Qt::Key_M), $self, 'toggleMenuBar()');

    my $tb = $self->{'tb'} =
	$controls->insertItem("Tool bar", $self, 'toggleToolBar()', Qt::CTRL+Qt::Key_T);
    my $sb = $self->{'sb'} =
	$controls->insertItem("Status bar", $self, 'toggleStatusBar()', Qt::CTRL+Qt::Key_B);
    $controls->setCheckable(1);
    $controls->setItemChecked($mb, 1);
    $controls->setItemChecked($tb, 1);
    $controls->setItemChecked($sb, 1);

    my $e = $self->{'e'} = Qt::MultiLineEdit->new($self, "editor");
    $e->setFocus();
    $self->setCentralWidget($e);
    $self->statusBar()->message("Ready", 2000);

    return $self;
}

# No destructor needed, $self->{'printer'} deleted on destruction

sub newDoc {
    my $self = shift;
    my $ed = ApplicationWindow->new;
    $ed->resize(400, 400);
    $ed->show();
}

sub loadFile { shift->load(@_) }

sub load {
    my $self = shift;
    my $e = $self->{'e'};
    my $fileName = shift;
    unless($fileName) {
	my $fn = Qt::FileDialog::getOpenFileName(undef, undef, $self);
	if(defined $fn) {
	    $self->load($fn);
	} else {
	    $self->statusBar()->message("Loading aborted", 2000);
	}
	return;
    }

    return unless open(F, $fileName);

    $e->setAutoUpdate(0);
    $e->clear();

    while(defined($s = <F>)) {
	chomp($s);
	$e->append($s);
    }
    close(F);

    $e->setAutoUpdate(1);
    $e->repaint();
    $self->setCaption($fileName);
    $self->statusBar()->message("Loaded document $fileName", 2000);
}

sub save {
    my $self = shift;
    $self->statusBar()->message("File->Save is not implemented");
    Qt::MessageBox::information(undef, "Note", "Left as an exercise for the user.");
}

sub print {
    my $self = shift;
    my $e = $self->{'e'};
    my $printer = $self->{'printer'};
    my $MARGIN = 10;
    my $pageNo = 1;

    if($printer->setup($self)) {
	$self->statusBar()->message("Printing...");
	my $p = Qt::Painter->new;
	$p->begin($printer);
	$p->setFont($e->font());
	my $yPos = 0;
	my $fm = $p->fontMetrics();
	my $metrics = Qt::PaintDeviceMetrics->new($printer);
	for(my $i = 0; $i < $e->numLines(); $i++) {
	    if($MARGIN + $yPos > $metrics->height() - $MARGIN) {
		$self->statusBar()->message("Printing (page $pageNo)...");
		$pageNo++;
		$printer->newPage();
		$yPos = 0;
	    }
	    $p->drawText($MARGIN, $MARGIN + $yPos,
			 $metrics->width(), $fm->lineSpacing(),
			 Qt::ExpandTabs | Qt::DontClip,
			 $e->textLine($i));
	    $yPos += $fm->lineSpacing();
	}
	$p->end();
	$self->statusBar()->message("Printing completed", 2000);
    } else {
	$self->statusBar()->message("Printing aborted", 2000);
    }
}

sub closeDoc {
    my $self = shift;
    $self->close(1);
}

sub toggleMenuBar {
    my $self = shift;
    my $controls = $self->{'controls'};
    if($self->menuBar()->isVisible()) {
	$self->menuBar()->hide();
	$controls->setItemChecked($self->{'mb'}, 0);
    } else {
	$self->menuBar()->show();
	$controls->setItemChecked($self->{'mb'}, 1);
    }
}

sub toggleToolBar {
    my $self = shift;
    my $controls = $self->{'controls'};
    my $fileTools = $self->{'fileTools'};
    if($fileTools->isVisible()) {
	$fileTools->hide();
	$controls->setItemChecked($self->{'tb'}, 0);
    } else {
	$fileTools->show();
	$controls->setItemChecked($self->{'tb'}, 1);
    }
}

sub toggleStatusBar {
    my $self = shift;
    my $controls = $self->{'controls'};
    if($self->statusBar()->isVisible()) {
	$self->statusBar()->hide();
	$controls->setItemChecked($self->{'sb'}, 0);
    } else {
	$self->statusBar()->show();
	$controls->setItemChecked($self->{'sb'}, 1);
    }
}


