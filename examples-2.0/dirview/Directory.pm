package Directory;

use Qt 2.0;

@ISA = qw(Qt::ListViewItem);

sub new {
    my($class, $parent, $filename) = @_;
    my $self = $class->SUPER::new($parent);

    $self->{'readable'} = 1;
    if($filename) {
	$self->{'p'} = $parent;
	$self->{'f'} = $filename;
    } else {
	$self->{'p'} = undef;
	$self->{'f'} = "/";
    }

    return $self;
}

sub setOpen {
    my $self = shift;
    my $o = shift;

    if($o && !$self->childCount()) {
	my $s = $self->fullName();
	unless(-r $s) {
	    $self->{'readable'} = 0;
	    return;
	}

	if(opendir(FILES, $s)) {
	    my $f;
	    while(defined($f = readdir(FILES))) {
		my $name = "$s/$f";
		if($f eq '.' || $f eq '..') {}
		elsif(-l $name) {
		    Qt::ListViewItem->new($self, $f, "Symbolic Link");
		} elsif(-d $name) {
		    Directory->new($self, $f);
		} else {
		    Qt::ListViewItem->new($self, $f, (-f $name) ? "File" : "Special");
		}
	    }
	    closedir(FILES);
	}
    }

    $self->SUPER::setOpen($o);
}

sub setup {
    my $self = shift;
    $self->setExpandable(1);
    $self->SUPER::setup();
}

sub fullName {
    my $self = shift;
    my $s;
    if($self->{'p'}) {
	$s = $self->{'p'}->fullName() . $self->{'f'} . "/";
    } else {
	$s = "/";
    }
    return $s;
}

sub text {
    my $self = shift;
    my $column = shift;

    if($column == 0) {
	return $self->{'f'};
    } elsif($self->{'readable'}) {
	return "Directory";
    } else {
	return "Unreadable Directory";
    }
}
