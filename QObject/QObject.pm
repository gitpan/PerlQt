package QObject;

use strict;
use vars qw($VERSION @ISA %Protos);
use Carp;

require DynaLoader;
require QGlobal;

@ISA = qw(DynaLoader Qt::Base);

$VERSION = '1.04';
bootstrap QObject $VERSION;

sub find_superclass {
    my $class = shift;
    no strict 'refs';
    foreach(@{"${class}::ISA"}) { return $_ if $_->isa('QObject') }
    return undef;
}

sub getMemberArgs {
    my $member = shift;

    return [] unless $member =~ /^\w+\((.*)\)$/;
    my $args = $1;
    my(@args) = split /\s*,\s*/, $args;

    return \@args;
}

sub parse_member {
    my $member = shift;

    $member =~ s/(\W)string(\W)/$1char*$2/g;
    return $member;
}

sub proto {
    my $orig = shift;
    my($fname, $proto) = $orig =~ /^(\w*)\s*(.*)\s*$/;

    croak "Missing function-name in prototype '$orig'" unless $fname;
    croak "Missing argument prototype in '$orig'" unless $proto;
    croak "The arguments to '$fname' must begin with an opening parenthesis"
	unless $proto =~ /^\(/;
    croak "The arguments to '$fname' must end with a closing parenthesis"
	unless $proto =~ /\)$/;

    $proto =~ /^\(\s*(.*)\s*\)$/;
    my $type = chr(length($fname)+1) . $fname . chr(0);
    my $args = $1;
    my $argcnt = 0;
    if($args) {
	my @args = split ',', $args;
	croak "Too many arguments (max 3) in $orig" if scalar(@args) > 3;
	while(@args) {
	    $_ = $args[0];
            s/^\s*(.*)\s*$/$1/;
	    my @arg = split;
	    if($arg[0] eq 'const') {
		$type .= chr(0);  # Perhaps in the future. But not today.
		shift @arg;
	    }
	    my $arg = shift @arg;
            if($arg eq 'int') {
                $type .= chr(2);
            } elsif($arg eq 'float') {
                $type .= chr(3);
            } elsif($arg eq 'double') {
                $type .= chr(4);
            } elsif($arg eq 'bool') {
                $type .= chr(5);
            } elsif($arg eq 'string') {
                $type .= chr(6);
	    } elsif($arg eq '...') {
		$type .= chr(12);

# this croak may be unnecessary in the future, because I could concievably
# create an argument to \12 which would tell how many arguments come after
# it on the stack. We'll see...

		croak "There's something after ... in '$orig'" if @args > 1;
	    } elsif($arg =~ /^\@\$/) {
                $type .= chr(10);
            } elsif($arg =~ /^\%\$/) {
                $type .= chr(11);
            } elsif($arg =~ /^\$\$/) {
                $type .= chr(9);
            } elsif($arg =~ /^\$/) {
                $type .= chr(8);
	    } elsif($arg =~ /\*$/) {
		croak "Explicit pointers in PerlQt signals/slots is illegal.";
	    } else {
		unless($arg =~ /^\w+$/) {
		    croak "Type '$arg' is not alphanumeric";
		} else {
		    $type .= chr(1) . chr(length($arg)+1) . $arg . chr(0);
		}
	    }
	} continue {
            shift @args;
            $argcnt++ unless $argcnt;
            if(scalar(@args)) {
                $argcnt++;
            }
        }
    }

    $type = chr($argcnt) . $type;
    $Protos{$type} = &unproto($type) unless exists $Protos{$type};
    return($type);
}

#sub unproto {
#    return $Protos{$_[0]};
#}

sub unproto {
    my $type = shift;
    my $proto;
    my $i = 0;
    my @type = split '', $type;

    my $argcnt = ord($type[$i++]);
    my $len = ord($type[$i++]);
    my $j = 1;
    while($j < $len) {
        $proto .= $type[$i++];
        $j++;
    }
    $i++;
    $proto .= '(';
    while($i < @type) {
        $_ = ord($type[$i]);
        if($_ == 0) {
            $proto .= 'const ';
            $i++;
            redo;
        } elsif($_ == 1) {
            $len = ord($type[++$i]);
            $j = 1;
            while($j < $len) {
                $proto .= $type[++$i];
                $j++;
            }
            $i++;  # strip off terminating \0
            $proto .= '*';
        } elsif($_ == 2) {
            $proto .= 'int';
        } elsif($_ == 3) {
            $proto .= 'float';
        } elsif($_ == 4) {
            $proto .= 'double';
        } elsif($_ == 5) {
            $proto .= 'bool';
        } elsif($_ == 6) {
            $proto .= 'char*';
        } elsif($_ == 8 || $_ == 9 || $_ == 10 || $_ == 11) {
            $proto .= 'SV*';
        } elsif($_ == 12) {
            $proto .= 'AV*';
        }
    } continue {
        $i++;
        if($i < @type) {
            $proto .= ',';
        }
    }
    $proto .= ')';
    return $proto;
}


package slots;

use strict;
use Carp;
use vars qw(%slots);

$INC{'slots.pm'} = $INC{'QObject.pm'};

sub find_slot {		# Perl has regexps, C++ has Perl regexps
    my $self = shift;
    my $class = ref $self || $self;
    my $slotname = shift;
    $slotname =~ /^(\w+)/;
    my $slot = $1;

    if(exists $slots{$class} and exists $slots{$class}{$slot}) {
	return $slot;
    }

    if($class ne 'QObject') {
	my $super = QObject::find_superclass($class);
	return find_slot($super, $slotname);
    }
    return undef;
}

sub import {
    shift;
    my $caller = (caller)[0];

    if($^W && !@_) { carp "'use slots' without arguments"; return }
    foreach my $m (@_) {
	my($type, $args) = QObject::proto($m);
	my($fname) = QObject::unproto($type) =~ /^(\w+)/;
	$slots{$caller}{$fname} = $type;
    }
}

#sub import {
#    shift;
#    my $caller = (caller)[0];

#    if(@_) {
#	foreach my $m (@_) {
#	    $_ = QObject::parse_member($m);
#	    /^([^\(]+)/;
#	    $slots{$caller}{$1} = $_;
#	}
#    }
#    elsif($^W) { carp "'use slots' without arguments" }
#}

package signals;

use strict;
use Carp;
use vars qw(@ISA @EXPORT %signals);

@ISA = qw(Exporter);
@EXPORT = qw(&emit);

$INC{'signals.pm'} = $INC{'QObject.pm'};

sub emit {}             # Just for the keyword

sub find_signal {	# Perl has regexps, C++ has Perl regexps
    my $self = shift;
    my $class = ref $self || $self;
    my $signame = shift;
    $signame =~ /^(\w+)/;
    my $sig = $1;

    if(exists $signals{$class} and exists $signals{$class}{$sig}) {
	return $sig;
    }

    if($class ne 'QObject') {
	my $super = QObject::find_superclass($class);
	return find_signal($super, $signame);
    }
    return undef;
}

sub import {
    my $class = shift;
    my $caller = (caller)[0];

    if($^W and !@_) { carp "'use signals' without arguments"; return }
    foreach my $m (@_) {
	my $proto = QObject::proto($m);
	$_ = QObject::unproto($proto);
	if(/^(\w+)/) {
	    addSignal("$caller"."::$1");
	    $signals{$caller}{$1} = $proto;
	}
    }

    @_ = ($class);
    goto &Exporter::import;    # Export &emit
}

#sub import {
#    my $class = shift;
#    my $caller = (caller)[0];
#
#    if($^W and !@_) { carp "'use signals' without arguments" }
#    foreach my $m (@_) {
#	$_ = QObject::parse_member($m);
#	if(/^(\w+)/) {
#	    addSignal("$caller"."::$1");
#	    $signals{$caller}{$1} = $_;
#	}
#    }
#
#    @_ = ($class);
#    goto &Exporter::import;    # Export &emit
#}

1;
__END__

=head1 NAME

QObject - Interface to the Qt QObject class

=head1 SYNOPSIS

C<use QObject;>

C<use signals 'sig1()', ..., 'sigx(int)';>

C<use slots 'slot1()', ..., 'sigx(int,int)';>

=head2 Member functions

new,
blockSignals,
className,
connect,
disconnect,
dumpObjectInfo,
dumpObjectTree,
event,
eventFilter,
highPriority,
inherits,
insertChild,
installEventFilter,
isA,
isWidgetType,
killTimer,
killTimers,
name,
parent,
removeChild,
removeEventFilter,
setName,
signalsBlocked,
startTimer,
timerEvent

=head2 Overridable functions

event,
eventFilter,
timerEvent

=head1 DESCRIPTION

Except for children() and queryList(), every public QObject member-function
is fully-implemented. Unless noted below, all of those functions are
completely direct interfaces.

=over 4

=item $connected = $reciever->connect(sender, signal, member)

Do I<NOT> attempt to use SIGNAL() or SLOT() on the signal and member
arguments. They are not needed by PerlQt, because the connect() function
can automatically determine whether the member argument is a signal or a
slot, and the signal will always be a signal. The signal and member
arguments must be strings. And at the moment, there isn't much room for
error.

=item $connected = QObject::connect(sender, signal, reciever, member)

Same as above listing, just as a normal function with a different
argument-list.

=item $disconnected = $sender->disconnect(signal = undef, reciever = undef, member = undef)

Remember I<NOT> to use SIGNAL() and SLOT() with disconnect(). This function
takes over for both the static disconnect() and the 3-arg member disconnect()
in Qt.

=item $disconnected = $sender->disconnect(reciever, member = undef)

Same warning about SIGNAL() and SLOT() as above.

=head2 Signals and slots

Signals and slots are implemented in a limited way at the moment. You may
use no-arg signals and slots freely, as well as 1 and 2 integer argument
signals and slots, and string signals.

The declaration of signals and slots is done through the usage
of 'use signals' and 'use slots'. Any classes which have QObject
in their inheritance tree are free to use signals/slots after their
superclass has been included via use.

=over 4

=item use signals 'sig1()', ..., 'sigx(int,string)'

The arguments to C<use signals> must be strings representing the signal
prototypes I<excluding> the object parameter. You may use C<qw()> to quote
the function prototypes, but it warns about commas when B<-w> is in use.

Add spaces at your own risk. Misspell at your own risk. PerlQt doesn't
do any error-checking yet. All error-checking that is done is done by
Qt. You may run C<use signals> as many times as you want. I'm pretty
sure that if you define the same signal-name twice, the latter prototype
is used. But you should get a redefined function warning. Also, the
argument-types are not checked yet.

Running C<use signals> exports a function named C<emit> into your namespace.
It does nothing, and is just there for clarity and consistency with Qt
where the emit keyword is just as void. When you emit a signal, you I<must>
call it as a method-call C<$self-E<gt>signal()>, and not as C<'signal()'>
or C<signal()> because it is not a string and it is not a normal function.

=item use slots 'slot1(int)', ..., 'slotx(const string, int)'

The arguments to C<use slots> must be strings representing the prototypes
of the slots you want to declare I<excluding> the object parameter. The slot
functions aren't cached by PerlQt, and are always called as full method-calls.

Once you declare a function as being a slot, you may use connect() to
connect any signal, Perl or C++, to it.

=back

=head1 BUGS

Signals and slots still have a way to go before achieving a state which can
be considered 'good'. What is available now is good enough for many uses,
but time and attention must be paid to signals and slots.

=head1 SEE ALSO

qobject(3qt), QGlobal(3)

=head1 AUTHOR

Ashley Winters <jql@accessone.com>
