package Qt::base;

sub this () : lvalue {}

sub new {
    no strict 'refs';
    my $t = this;
    shift->NEW(@_);
    my $ret = this;
    this = $t;
    return $ret;
}

package Qt::_internal;
use strict;

our $Classes;
our %CppName;
our @IdClass;

our @PersistentObjects;   # objects which need a "permanent" reference in Perl

sub this () : lvalue {}


sub init_class {
    no strict 'refs';
    my $c = shift;
    my $class = $c;
    $class =~ s/^Q(?=[A-Z])/Qt::/;
    my $classId = Qt::_internal::idClass($c);
    insert_pclassid($class, $classId);

    $IdClass[$classId] = $class;
    $CppName{$class} = $c;
    {
	package Qt::_internal::autoload;   # this package holds $AUTOLOAD
	my $closure = sub {	# closure on $classId
	    our $AUTOLOAD;
	#    warn "Legacy AUTOLOAD for $AUTOLOAD\n";
	    Qt::_internal::autoloaded($AUTOLOAD, $classId, \@_) ||
		goto &Qt::_internal::methodcall;
	};
	*{ $class . "::AUTOLOAD" } = $closure;
    }

    my @isa = Qt::_internal::getIsa($classId);
    for my $super (@isa) {
	$super =~ s/^Q(?=[A-Z])/Qt::/;
    }
    # the general base class is Qt::base.
    # implicit new(@_) calls are forwarded there.
    @isa = ("Qt::base") unless @isa;
    *{ "$class\::ISA" } = \@isa;

    Qt::_internal::installautoload(" $class");
    {
	package Qt::AutoLoad;
	# do lookup at compile-time
	my $autosub = \&{ " $class\::_UTOLOAD" };
	*{ " $class\::AUTOLOAD" } = sub { &$autosub };
    }

    *{ "$class\::NEW" } = sub {
	my $class = shift;
	$Qt::AutoLoad::AUTOLOAD = "$class\::$c";
	my $autoload = " $class\::_UTOLOAD";
        {
            no warnings;
            # the next line triggers a warning on SuSE's Perl 5.6.1 (?)
	    this = bless &$autoload, " $class";
        }

	if(!$class->isa("Qt::Object") and
	    $class->isa("Qt::LayoutItem") ||
	    $class->isa("Qt::ListViewItem") ||
	    $class->isa("Qt::IconViewItem") ||
	    $class->isa("Qt::ListBoxItem") ||
	    $class->isa("Qt::StyleSheetItem") ||
	    $class->isa("Qt::TableItem") ||
            $class->isa("Qt::SqlCursor") ) {
	    push @PersistentObjects, this;
	} else {
	    setAllocated(this, 1);
	}
	mapObject(this);
    } unless defined &{"$class\::NEW"};

    *{ $class } = sub {
	$class->new(@_);
    } unless defined &{ $class };
}

sub argmatch {
    my $methods = shift;
    my $args = shift;
    my $i = shift;
    my @match;
    for my $method (@$methods) {
	my $typename = getTypeNameOfArg($method, $i);
	my $argtype = getSVt($args->[$i]);
	if($argtype eq 'i') {
	    if($typename =~ /^(short|ushort|int|uint|long|ulong|signed|unsigned)$/) {
		push @match, $method;
	    }
	} elsif($argtype eq 'n') {
	    if($typename =~ /^(float|double)$/) {
		push @match, $method;
	    }
	} elsif($argtype eq 's') {
	    if($typename =~ /^(char\*|const char\*|(?:const )?QC?String[*&]?)$/) {
		push @match, $method;
	    }
	} elsif($argtype eq 'a') {
            # FIXME: shouldn't be hardcoded. Installed handlers should tell what perl type they expect.
            if($typename =~ /^(?:
                                const\ QCOORD\*|
                                (?:const\ )?
                                (?:
                                  QStringList[\*&]?|
                                  QValueList<int>[\*&]?|
                                  QRgb\*|
                                  char\*\*
                                )
                              )$/x) {
                push @match, $method;
            }
	} elsif($argtype eq 'r' or $argtype eq 'U') {
	    push @match, $method;
	} else {
	    my $t = $typename;
	    $t =~ s/^const\s+//;
	    $t =~ s/(?<=\w)[&*]$//;
	    my $isa = classIsa($argtype, $t);
	    if($isa) {
		push @match, $method;
	    }
	}
    }

    return @match;
}

sub destroy {
    my $self = shift;
    return 1 if $self->{"has been hidden"};
    return 1 unless isValidAllocatedPointer($self) and isQObject($self);

    my $parent;
    eval { $parent = $self->parent() };
    return 1 if $@ || !$parent;
    warn "Increasing refcount in DESTROY for $self (still has a parent)"
        if debug() && (debug() & $Qt::debug::channel{'gc'});
    if(!isValidAllocatedPointer($parent))
    {
       my $a = findAllocatedObjectFor($parent);
       if($a) {
           push @{ $a->{"hidden children"} }, $self
       } else {
           push @PersistentObjects, $self
       }
       $self->{"has been hidden"} = 1;
       return 1;
    }
    push @{ $parent->{"hidden children"} }, $self;
    $self->{"has been hidden"} = 1;
    return 1;
}

sub do_autoload {
    my $package = pop;
    my $method = pop;
    my $classId = pop;

    my $class = $CppName{$IdClass[$classId]};
    my @methods = ($method);
    for my $arg (@_) {
	unless(defined $arg) {
	    @methods = map { $_ . '?', $_ . '#', $_ . '$' } @methods;
	} elsif(isObject($arg)) {
	    @methods = map { $_ . '#' } @methods;
	} elsif(ref $arg) {
	    @methods = map { $_ . '?' } @methods;
	} else {
	    @methods = map { $_ . '$' } @methods;
	}
    }
    my @methodids = map { findMethod($class, $_) } @methods;

    if(@methodids > 1) {
	# ghetto method resolution
	my $count = scalar @_;
	for my $i (0..$count-1) {
	    my @matching = argmatch(\@methodids, \@_, $i);
	    @methodids = @matching if @matching;
	}
        do {
            my $c = caller(3)?3:1;
            warn "Ambiguous method call for :\n".
                "\t${class}::${method}(".catArguments(\@_).")".
             ((debug() && (debug() & $Qt::debug::channel{'verbose'})) ?
             "\nCandidates are:\n".dumpCandidates(\@methodids).
             "\nTaking first one...\nat " : "").
             (caller($c))[1]." line ".(caller($c))[2].".\n"
        } if debug() && @methodids > 1 && (debug() & $Qt::debug::channel{'ambiguous'});

    }
    unless(@methodids) {
	if(@_) {
	    @methodids = findMethod($class, $method);
	    do {
                do {
                    my $c = caller(3)?3:1;
                    warn "Lookup for ${class}::${method}(".catArguments(\@_).
                         ")\ndid not yeld any result.\n".
                         ((debug() && (debug() & $Qt::debug::channel{'verbose'})) ?
                         "Might be a call for an enumerated value (enum).\n":"").
                         "Trying ${class}::${method}() with no arguments\nat ".
                         (caller($c))[1]." line ".(caller($c))[2].".\n"
                } if debug() && @_ > 1 && (debug() & $Qt::debug::channel{'ambiguous'});
                @_ = ()
            } if @methodids;
	}
	do{
            my $verbose = "";
            if(debug() && (debug() & $Qt::debug::channel{'verbose'})) {
                my $alt = findAllMethods( $classId );
                my $pat1 = my $pat2 = $method;
                my @near = ();
                while(!@near && length($pat1)>2) {
                    @near = map { /$pat1|$pat2/i ? @{ $$alt{$_} }:() } sort keys %$alt;
                    chop $pat1;
                    substr($pat2,-1,1)= "";
                }
                $verbose = @near ? ("\nCloser candidates are :\n".dumpCandidates(\@near)) :
                                    "\nNo close candidate found.\n";
            }
            my $c = caller(3)?3:1;
            die "--- No method to call for :\n\t${class}::${method}(".
            catArguments(\@_).")".$verbose."\nat ".(caller($c))[1].
            " line ".(caller($c))[2].".\n";
          } unless @methodids;
    }
    setCurrentMethod($methodids[0]);
    return 1;
}

sub autoloaded {
    my($method, $classId, $args) = @_;

    $method =~ s/.*:://;

    my $class = $CppName{$IdClass[$classId]};
    my $db = debug();

    warn "In Autoload for $class\::$method()"
      if $db && ($db & $Qt::debug::channel{'autoload'});

    my $id = join(";",$class,$method,map{ getSVt($_) } @$args);
    if( my $meth = find_mcid($id)) {
        setCurrentMethod($meth);
        warn "Calling method ".dumpCandidates([$meth]).
            (($db && ($db & $Qt::debug::channel{'verbose'})) ?
            "with arguments (".catArguments($args).")\n":"")
          if $db && ($db & $Qt::debug::channel{'calls'});
        return 0;
    }
    my $c = caller(3)?3:1;

    my @methods = ($method);
    for my $arg (@$args) {
	unless(defined $arg) {
	    @methods = map { $_ . '?', $_ . '#', $_ . '$' } @methods;
	} elsif(isObject($arg)) {
	    @methods = map { $_ . '#' } @methods;
	} elsif(ref $arg) {
	    @methods = map { $_ . '?' } @methods;
	} else {
	    @methods = map { $_ . '$' } @methods;
	}
    }
    my @methodids = map { findMethod($class, $_) } @methods;

    if(@methodids > 1) {
	# ghetto method resolution
	my $count = scalar @$args;
	for my $i (0..$count-1) {
	    my @matching = argmatch(\@methodids, $args, $i);
	    @methodids = @matching if @matching;
	}
        warn "Ambiguous method call for :\n".
             "\t${class}::${method}(".catArguments($args).")".
             (($db && ($db & $Qt::debug::channel{'verbose'})) ?
             "\nCandidates are:\n".dumpCandidates(\@methodids).
             "\nTaking first one...\nat " : "").
             (caller($c))[1]." line ".(caller($c))[2].".\n"
             if $db && @methodids > 1 && ($db & $Qt::debug::channel{'ambiguous'});
    }
    unless(@methodids) {
	if(@$args) {
	    @methodids = findMethod($class, $method);
	    do {
                warn "Lookup for ${class}::${method}(".catArguments($args).
                     ")\ndid not yeld any result.\n".
                     (($db && ($db & $Qt::debug::channel{'verbose'})) ?
                     "Might be a call for an enumerated value (enum).\n":"").
                     "Trying ${class}::${method}() with no arguments\nat ".
                     (caller($c))[1]." line ".(caller($c))[2].".\n"
                     if $db && @$args > 1 && (debug() & $Qt::debug::channel{'ambiguous'});
                @$args = ()
            } if @methodids;
	}
	do{
            my $verbose = "";
            if(debug() && (debug() & $Qt::debug::channel{'verbose'})) {
                my $alt = findAllMethods( $classId );
                my $pat1 = my $pat2 = $method;
                my @near = ();
                while(!@near && length($pat1)>2) {
                    @near = map { /$pat1|$pat2/i ? @{ $$alt{$_} }:() } sort keys %$alt;
                    chop $pat1;
                    substr($pat2,-1,1)= "";
                }
                $verbose = @near ? ("\nCloser candidates are :\n".dumpCandidates(\@near)) :
                                    "\nNo close candidate found.\n";
            }
            die "--- No method to call for :\n\t${class}::${method}(".
            catArguments($args).")".$verbose."\nat ".(caller($c))[1].
            " line ".(caller($c))[2].".\n";
        } unless @methodids;
    }

    insert_mcid($id, $methodids[0]);
    setCurrentMethod($methodids[0]);

    warn "Calling method ".dumpCandidates([$methodids[0]]).
         ((debug() && (debug() & $Qt::debug::channel{'verbose'})) ?
         "with arguments (".catArguments($args).")\n":"")
         if $db && ($db & $Qt::debug::channel{'calls'});

    return 0;
}

sub methodcall {
    goto &callMethod;
}

sub init {
    no warnings;
    installthis(__PACKAGE__);
    installthis("Qt::base");
    $Classes = getClassList();
    for my $c (@$Classes) {
	init_class($c);
    }
}

sub Qt::Application::NEW {
    my $class = shift;
    my $argv = shift;
    unshift @$argv, $0;
    my $count = scalar @$argv;
    this = bless Qt::Application::QApplication($count, $argv, @_), " $class";
    mapObject(this);
    setAllocated(this, 1);
    setqapp(this);
    shift @$argv;
}

sub Qt::Image::NEW {
    no strict 'refs';
    # another ugly hack, whee
    my $class = shift;
    if(@_ == 6) {
	my $colortable = $_[5];
	my $numColors = (ref $colortable eq 'ARRAY') ? @$colortable : 0;
	splice(@_, 5, 0, $numColors);
    }

    # FIXME: this is evil
    $Qt::AutoLoad::AUTOLOAD = 'Qt::Image::QImage';
    my $autoload = " Qt::Image::_UTOLOAD";
    dontRecurse();
    this = $autoload->(@_);
    setAllocated(this, 1);
}

sub makeMetaData {
    my $data = shift;
    my @tbl;
    for my $entry (@$data) {
	my @params;
	my $argcnt = scalar @{ $entry->{arguments} };
	for my $arg (@{ $entry->{arguments} }) {
	    push @params, make_QUParameter($arg->{name}, $arg->{type}, 0, 1);
	}
	my $method = make_QUMethod($entry->{name}, \@params);
	push @tbl, make_QMetaData($entry->{prototype}, $method);
    }
    my $count = scalar @tbl;
    my $metadata = make_QMetaData_tbl(\@tbl);
    return ($metadata, $count);
}

# This is the key function for signal/slots...
# All META hash entries have been defined by Qt::slots.pm &&|| Qt::signals.pm
# Thereafter, Qt::isa.pm build the MetaObject by calling this function
# Here is the structure of the META hash:
# META { 'slot' => { $slotname-1 => { name      =>  $slotname-1,
#                                     arguments => xxx,
#                                     prototype => xxx,
#                                     returns   => xxx,
#                                     method    => xxx,
#                                     index     => <index in 'slots' array>,
#                                     mocargs   => xxx,
#                                     argcnt    => xxx },
#                     ... ,
#                    $slotname-n => ...
#                  },
#       'slots' => [ slot1-hash, slot2-hash...slot-n-hash ],
#       'signal' => ibidem,
#       'signals' => ibidem,
#       'superClass' => ["classname1", .."classname-n"] # inherited
#     }

sub getMetaObject {
    no strict 'refs';
    my $class = shift;
    my $meta = \%{ $class . '::META' };
    return $meta->{object} if $meta->{object};
    inheritSuperSigSlots($class);
    my($slot_tbl, $slot_tbl_count) = makeMetaData($meta->{slots});
    my($signal_tbl, $signal_tbl_count) = makeMetaData($meta->{signals});
    $meta->{object} = make_metaObject($class, Qt::this()->staticMetaObject,
		$slot_tbl, $slot_tbl_count,
		$signal_tbl, $signal_tbl_count);
    return $meta->{object};
}

sub inheritSuperSigSlots {
    no strict 'refs';
    my $class = shift;
    my $meta = \%{ $class . '::META' };
    if(defined $meta->{'superClass'} && @{ $meta->{'superClass'} }) {
        for my $super(@{$meta->{'superClass'}}) {
            inheritSuperSigSlots($super);
            for my $ssn(keys %{${$super.'::META'}{slot}}) {
               if(!exists $meta->{slot}->{"$ssn"}) {
                   my %ss = %{${$super.'::META'}{slot}{$ssn}};
                   push @{$meta->{slots}}, \%ss;
                   $meta->{slot}->{$ssn} = \%ss;
                   $ss{index} = $#{ $meta->{slots} };
               }
            }
            for my $ssn(keys %{${$super.'::META'}{signal}}) {
               if(!exists $meta->{signal}->{"$ssn"}) {
                   my %ss = %{${$super.'::META'}{signal}{$ssn}};
                   push @{$meta->{signals}}, \%ss;
                   $meta->{signal}->{$ssn} = \%ss;
                   $ss{index} = $#{ $meta->{signals} };
                   Qt::_internal::installsignal("$class\::$ssn");
               }
            }
            Qt::_internal::installqt_invoke($class . '::qt_invoke')
                if( !defined &{ $class. '::qt_invoke' } && exists $meta->{slots} && @{ $meta->{slots} });
        }
    }
}


sub Qt::PointArray::setPoints {
    my $points = $_[0];
    no strict 'refs';
    # what a horrible, horrible way to do this
    $Qt::AutoLoad::AUTOLOAD = 'Qt::PointArray::setPoints';
    my $autoload = " Qt::PointArray::_UTOLOAD";
    dontRecurse();
    $autoload->(scalar(@$points)/2, $points);
}

sub Qt::GridLayout::addMultiCellLayout {
    # yet another hack. Turnaround for a bug in Qt < 3.1
    # (addMultiCellLayout doesn't reparent its QLayout argument)
    no strict 'refs';
    if(!defined $_[0]->{'has been hidden'})
    {
        push @{ this()->{'hidden children'} }, $_[0];
        $_[0]->{'has been hidden'} = 1;
    }
    $Qt::AutoLoad::AUTOLOAD = 'Qt::GridLayout::addMultiCellLayout';
    my $autoload = " Qt::GridLayout::_UTOLOAD";
    dontRecurse();
    $autoload->(@_);
}

package Qt;

use 5.006;
use strict;
use warnings;
use XSLoader;

require Exporter;

our $VERSION = '3.004';

our @EXPORT = qw(&SIGNAL &SLOT &CAST &emit &min &max);

XSLoader::load 'Qt', $VERSION;

# try to avoid KDE's buggy malloc
# only works for --enable-fast-malloc,
# not when --enable-fast-malloc=full
$ENV{'KDE_MALLOC'} = 0;

Qt::_internal::init();

# In general, I'm not a fan of prototypes.
# However, I'm also not a fan of parentheses

sub SIGNAL ($) { '2' . $_[0] }
sub SLOT ($) { '1' . $_[0] }
sub CAST ($$) { bless $_[0], " $_[1]" }
sub emit (@) { pop @_ }
sub min ($$) { $_[0] < $_[1] ? $_[0] : $_[1] }
sub max ($$) { $_[0] > $_[1] ? $_[0] : $_[1] }

sub import { goto &Exporter::import }
1;
