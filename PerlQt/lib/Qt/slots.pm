package Qt::slots;
#
# Proposed usage:
#
# use Qt::slots changeSomething => ['int'];
#
# use Qt::slots 'changeSomething(int)' => {
#     args => ['int'],
#     call => 'changeSomething'
# };
#

sub import {
    no strict 'refs';
    my $self = shift;
    my $caller = (caller)[0];
    my $parent = ${ $caller . '::ISA' }[0];
    my $parent_qt_invoke = $parent . '::qt_invoke';

    Qt::_internal::installqt_invoke($caller . '::qt_invoke');

#    *{ $caller . '::qt_invoke' } = sub {
#	my $meta = \%{ $caller . '::META' };
#	die unless $meta->{object};
#	my $offset = $_[0] - $meta->{object}->slotOffset;
#	if($offset >= 0) {
#	    Qt::_internal::invoke(Qt::this(), $meta->{slots}[$offset], $_[1]);
#	    return 1;
#	} else {
#	    Qt::this()->$parent_qt_invoke(@_);
#	}
#    } unless defined &{ $caller . '::qt_invoke' };

    my $meta = \%{ $caller . '::META' };
    my(%slots) = @_;
    for my $slotname (keys %slots) {
	my $slot = { name => $slotname };
	my $args = $slots{$slotname};
	$slot->{arguments} = [map { s/\s(?=[*&])//; { type => $_, name => "" } } @$args];
	my $arglist = join ',', @$args;
	$slot->{prototype} = $slotname . "($arglist)";
	$slot->{returns} = 'void';
	$slot->{method} = $slotname;
	push @{$meta->{slots}}, $slot;
	my $slot_index = $#{ $meta->{slots} };

	my $argcnt = scalar @$args;
	my $mocargs = Qt::_internal::allocateMocArguments($argcnt);
	my $i = 0;
	for my $arg (@$args) {
	    my $a = $arg;
	    $a =~ s/^const\s+//;
	    if($a =~ /^(bool|int|double|char\*|QString)&?$/) {
		$a = $1;
	    } else {
		$a = 'ptr';
	    }
	    my $valid = Qt::_internal::setMocType($mocargs, $i, $arg, $a);
	    die "Invalid type for slot argument ($arg)\n" unless $valid;
	    $i++;
	}

	$meta->{slot}{$slotname} = $slot;
	$slot->{index} = $slot_index;
	$slot->{mocargs} = $mocargs;
	$slot->{argcnt} = $argcnt;
    }
}

1;
