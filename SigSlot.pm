################################################################################
#
# Copyright (C) 1998-2000, Ashley Winters <jql@accessone.com>
# All rights reserved.
#
# This program is free software; you can redistribute it and/or
# modify it under the same terms as Perl itself.
#

package SigSlot;
use Exporter;
use strict;
use vars qw(@ISA @EXPORT);

@ISA = qw(Exporter);
@EXPORT = qw(&GenerateSignalSlotTemplate);

my(%Typemap) = (
    'void*' => [
	qw(PIG_PROTO_OBJECT
	   PIG_PROTO_STRING
	   PIG_PROTO_SCALAR
	   PIG_PROTO_SCALARREF
	   PIG_PROTO_HVSCALAR
	   PIG_PROTO_AVSCALAR
	   PIG_PROTO_LIST)
    ],
    'long' => [ 'PIG_PROTO_LONG' ],
    'short' => [ 'PIG_PROTO_SHORT' ],
    'int' => [ 'PIG_PROTO_INT' ],
    'float' => [ 'PIG_PROTO_FLOAT' ],
    'double' => [ 'PIG_PROTO_DOUBLE' ],
    'long double' => [ 'PIG_PROTO_LDOUBLE' ],
    'bool' => [ 'PIG_PROTO_BOOL' ],
);

my(%From) = (
    'PIG_PROTO_BOOL' => 'pig_type_bool_push(*(bool*)&$var)',
    'PIG_PROTO_LONG' => 'pig_type_long_push(*(long*)&$var)',
    'PIG_PROTO_INT' => 'pig_type_int_push(*(int*)&$var)',
    'PIG_PROTO_SHORT' => 'pig_type_short_push(*(short*)&$var)',
    'PIG_PROTO_FLOAT' => 'pig_type_float_push(*(float*)&$var)',
    'PIG_PROTO_DOUBLE' => 'pig_type_double_push(*(double*)&$var)',
    'PIG_PROTO_LDOUBLE' => 'pig_type_long_double_push(*(long double*)&$var)',
    'PIG_PROTO_STRING' => 'pig_type_cstring_push(*(char**)&$var)',
    'PIG_PROTO_OBJECT' => 'pig_type_object_push(*(void**)&$var,$ptr+1)',
    'PIG_PROTO_AVSCALAR' => 'pig_type_ptr_push(*(void**)&$var)',
    'PIG_PROTO_HVSCALAR' => 'pig_type_ptr_push(*(void**)&$var)',
    'PIG_PROTO_SCALARREF' => 'pig_type_ptr_push(*(void**)&$var)',
    'PIG_PROTO_SCALAR' => 'pig_type_ptr_push(*(void**)&$var)',
    'PIG_PROTO_LIST' => 'pig_type_ptr_push(*(void**)&$var)',
);

my(%To) = (
    'PIG_PROTO_BOOL' => 'pig_type_bool_argument()',
    'PIG_PROTO_LONG' => 'pig_type_long_argument()',
    'PIG_PROTO_INT' => 'pig_type_int_argument()',
    'PIG_PROTO_SHORT' => 'pig_type_short_argument()',
    'PIG_PROTO_FLOAT' => 'pig_type_float_argument()',
    'PIG_PROTO_DOUBLE' => 'pig_type_double_argument()',
    'PIG_PROTO_LDOUBLE' => 'pig_type_long_double_argument()',
    'PIG_PROTO_SCALAR' => 'pig_type_ptr_argument()',
    'PIG_PROTO_SCALARREF' => 'pig_type_ptr_argument()',
    'PIG_PROTO_HVSCALAR' => 'pig_type_ptr_argument()',
    'PIG_PROTO_AVSCALAR' => 'pig_type_ptr_argument()',
    'PIG_PROTO_LIST' => 'pig_type_ptr_argument()',
    'PIG_PROTO_STRING' => 'pig_type_cstring_argument()',
    'PIG_PROTO_OBJECT' => 'pig_type_object_argument(0)'
);

my %sizeof;
my @size;
my @types;
my $header = "_pigsigslot.h";
my $source = "_pigsigslot.c";
my $typefile = "types";
my $count = 3;
my $shclass = "pig_S";
my $shmethod = "s";
my(@argv) = ('long', 'short', 'int', 'bool', 'void*', 'float', 'double');

sub output {
    print @_;
}

sub init_data_type_sizes {
    open SIZES, $typefile or die "piped open: $!";
    while(<SIZES>) {
	chomp;
	/^(.*)\s+\=\s+(.*)$/;
	$sizeof{$1} = $2;
    }
    close SIZES;
    for(keys %sizeof) { push @{$size[$sizeof{$_}]}, $_ }
}

sub make_data_type_list {
    for my $type (@argv) {
	die "Invalid type: $type" unless exists $sizeof{$type};
	push @types, $type
	    unless grep { $sizeof{$_} == $sizeof{$type} } @types;
    }
}


sub open_header_file {
    open STDOUT, ">$header" or die "open $header: $!";
}

sub close_header_file {
    close STDOUT;
}

sub output_headers {
    output <<HEADERS;
#include <qobject.h>
#include <qmetaobj.h>

HEADERS
}

sub output_defines {
    output <<DEFINES
#define PIG_SIGSLOT_MAX_ARGS $count
DEFINES
}

sub output_stolen_moc_header {
    output <<MOC_HEADER;
#if !defined(Q_MOC_CONNECTIONLIST_DECLARED)
#define Q_MOC_CONNECTIONLIST_DECLARED
#include <qlist.h>
#if defined(Q_DECLARE)
Q_DECLARE(QListM,QConnection);
Q_DECLARE(QListIteratorM,QConnection);
#else
declare(QListM,QConnection);
declare(QListIteratorM,QConnection);
#endif
#endif
MOC_HEADER
}

sub declare_slot_class {
    output <<SLOT_CLASS;
#undef $shclass
#undef $shmethod
class $shclass : public QObject {
public:
    class pig_slot_data *pigsd;

    $shclass();
    virtual ~$shclass();

    virtual const char *className() const;
    virtual QMetaObject *metaObject() const;

    void ${shclass}_destroyed();

SLOT_CLASS

    my @index;
    for(1..$count) { $index[$_ - 1] = -1 }
INF:
    while(1) {
	my @args;
	for(reverse @index) { push @args, $types[$_] if $_ >= 0 }

	output "    void $shmethod(@args);";

	for(my $i = 0; $i < @index; $i++) {
	    last if ++$index[$i] < @types;
	    last INF if $i == $#index;
	    $index[$i] = 0;
	}
    }

    output "";

    declare_signals();

    output "};";
}

sub open_source_file {
    open STDOUT, ">$source" or die "open $source: $!";
}

sub close_source_file {
    close STDOUT;
}

sub output_includes {
    output <<INCLUDES;
#include "$header"
INCLUDES
}

sub output_global_stacks {
    for(@types) {
	my $a = $_;
	$a =~ s/\W//g;
	output "static $_ pig_sigslot_stack_$a\[PIG_SIGSLOT_MAX_ARGS];";
    }
    output "";
}

sub output_global_variables {
    output <<VARIABLES;
typedef void (*pig_signal)();

QObject *pig_signal_object;
QMember *pig_signal_member;
VARIABLES
}

sub output_pig_hash {
    my(@table) = (1);
    for my $x (1..$count) { push @table, scalar(@types)**$x }
    output "int pig_sigslot_exp_table[] = { @table };\n";

    output "int pig_sigslot_typeidx(char pig1) {";
    output "    switch(pig1) {";
    for my $i (0..$#types) {
	for my $t (@{$size[$sizeof{$types[$i]}]}) {
	    for my $x (@{$Typemap{$t}}) { output "\tcase $x:" }
	}
	output "\t    return $i + 1;";
    }
    output "\tdefault:";
    output "\t    return 0;";
    output "    }";
    output "}\n";
}

sub output_slot_matrix {
    output "QMember pig_slot_matrix[] = {";

    my @index;
    for(1..$count) { $index[$_ - 1] = -1 }
INF:
    while(1) {
	my @args;
	for(reverse @index) { push @args, $types[$_] if $_ >= 0 }

	output "    (QMember)((void ($shclass\::*)(@args))&$shclass\::$shmethod),";

	for(my $i = 0; $i < @index; $i++) {
	    last if ++$index[$i] < @types;
	    last INF if $i == $#index;
	    $index[$i] = 0;
	}
    }

    output "};\n";
}

sub output_slot_helper {
    output "void pig_push_slot_arguments(const char *pigcrypt) {";

    my(@t) = map { my $a = $_; $a =~ s/\W//g; ($a) } @types;

    for my $i (0..$#types) {
        my $a = $t[$i];
        my $t = $types[$i];

	output "    int pig_sigslot_idx_$a = 0;";
    }

    output <<METHOD;
    pig_sigslot_argument_iterator pigiter(pigcrypt);
    int pigi;

    for(pigi = 0; pigi < *pigcrypt; pigi++) {
        const char *pigc = ++pigiter;
METHOD

    output "\tswitch(*pigc) {";

    for my $type (@types) {
	my $a = $type;
	$a =~ s/\W//g;
	for my $t (@{$size[$sizeof{$type}]}) {
            for(@{$Typemap{$t}}) {
		output "\t    case $_:";
		my $f = $From{$_};
		next unless $f;
		$f =~ s/\$var/pig_sigslot_stack_$a\[pig_sigslot_idx_$a++]/;
		$f =~ s/\$ptr/pigc/g;
	        output "\t\t$f;";
		output "\t\tbreak;";
	    }
	}
    }
    output "\t}";
    output "    }";
    output "}\n";
}

sub output_signal_helper {
    output "void pig_pop_signal_arguments(const char *pigcrypt) {";

    my(@t) = map { my $a = $_; $a =~ s/\W//g; ($a) } @types;

    for my $i (0..$#types) {
        my $a = $t[$i];
        my $t = $types[$i];

	output "    int pig_sigslot_idx_$a = 0;";
    }

    output <<METHOD;
    pig_sigslot_argument_iterator pigiter(pigcrypt);
    int pigi;

    for(pigi = 0; pigi < *pigcrypt; pigi++) {
        const char *pigc = ++pigiter;
METHOD

    output "\tswitch(*pigc) {";

    for my $type (@types) {
	my $a = $type;
	$a =~ s/\W//g;
	for my $t (@{$size[$sizeof{$type}]}) {
            for(@{$Typemap{$t}}) {
		output "\t    case $_:";
		output "\t\t{";
		my $f = $To{$_};
		my $var;
		next unless $f;
FINDTYPE:	for my $e (keys %Typemap) {
		    for my $f (@{$Typemap{$e}}) {
			if($f eq $_) { $var = $e; last FINDTYPE }
		    }
		}
		$f = "$var pigx = ($var)$f";
		$f =~ s/\$ptr/pigc/g;
	        output "\t\t    $f;";
		$f = "pig_sigslot_stack_$a\[pig_sigslot_idx_$a++] = *(($type *)&pigx)";
	        output "\t\t    $f;";
		output "\t\t}";
		output "\t\tbreak;";
	    }
	}
    }
    output "\t}";
    output "    }";
    output "}\n";
}

sub define_slots {
    my %indices;
    my @index;
    for(1..$count) { $index[$_ - 1] = -1 }
INF:
    while(1) {
	my(@arglist, @args);
	for(reverse @index) {
	    if($_ >= 0) {
		push @args, $types[$_];
		push @arglist, $types[$_];
		$arglist[$#arglist] .= " pig$#arglist";
	    }
	}
	output "void $shclass\::$shmethod(@arglist) {";

	%indices = map { $_ => 0 } @args;
	my $a = 0;
	for(@args) {
	    output "    pig_sigslot_stack_$_\[$indices{$_}] = pig$a;";
	    $a++;
	    $indices{$_}++;
	}
	output "    pigslot(this);";
	output "}\n";

	for(my $i = 0; $i < @index; $i++) {
	    last if ++$index[$i] < @types;
	    last INF if $i == $#index;
	    $index[$i] = 0;
	}
    }
}

sub declare_signals {
    my %indices;
    my @index;

    for(1..$count) { $index[$_ - 1] = -1 }
INF:
    while(1) {
	my(@arglist, @args, @stack);
	for(reverse @index) {
	    if($_ >= 0) {
		my $a = $types[$_];
		$a =~ s/\W//g;
		push @args, $a;
		push @arglist, $types[$_];
	    }
	}
	%indices = map { $_ => 0 } @args;
	for(@args) {
	    push @stack, "pig_sigslot_stack_$_\[$indices{$_}]";
	    $indices{$_}++;
	}

	my @sizes = map { $sizeof{$_} } @args;
	output "    static void " . join("_", "pig_call", @sizes) . "();";

	for(my $i = 0; $i < @index; $i++) {
	    last if ++$index[$i] < @types;
	    last INF if $i == $#index;
	    $index[$i] = 0;
	}
    }
}

sub define_signals {
    my %indices;
    my @index;

    for(1..$count) { $index[$_ - 1] = -1 }
INF:
    while(1) {
	my(@arglist, @args, @stack);
	for(reverse @index) {
	    if($_ >= 0) {
		my $a = $types[$_];
		$a =~ s/\W//g;
		push @args, $a;
		push @arglist, $types[$_];
	    }
	}
	%indices = map { $_ => 0 } @args;
	for(@args) {
	    push @stack, "pig_sigslot_stack_$_\[$indices{$_}]";
	    $indices{$_}++;
	}

	my @sizes = map { $sizeof{$_} } @args;
	output "void $shclass\::" . join("_", "pig_call", @sizes) . "() {";
	output "    typedef void (QObject::**PIG)(@arglist);";
	output "    (pig_signal_object->*pig_func)(@stack);";
	output "}\n";

	for(my $i = 0; $i < @index; $i++) {
	    last if ++$index[$i] < @types;
	    last INF if $i == $#index;
	    $index[$i] = 0;
	}
    }
}

sub output_signal_matrix {
    output "pig_signal pig_signal_matrix[] = {";

    my @index;
    for(1..$count) { $index[$_ - 1] = -1 }
INF:
    while(1) {
	my @args;
	for(reverse @index) { push @args, $types[$_] if $_ >= 0 }
        my @sizes = map { $sizeof{$_} } @args;
	output "    &$shclass\::" . join("_", "pig_call", @sizes) . ",";
	for(my $i = 0; $i < @index; $i++) {
	    last if ++$index[$i] < @types;
	    last INF if $i == $#index;
	    $index[$i] = 0;
	}
    }

    output "};\n";
}

sub myprint {
    local $\ = undef;
    select((select(STDSAVE),$|=1)[0]);
    print STDSAVE @_;
}

sub GenerateSignalSlotTemplate {
    my(%args) = @_;
    local $\ = "\n";
    local $" = ", ";
    local $| = 1;

    open(STDSAVE, ">&STDOUT");
    myprint "Generating Signal/Slot templates...";

    $source = $args{'SOURCE'} if exists $args{'SOURCE'};
    $header = $args{'HEADER'} if exists $args{'HEADER'};
    $count = $args{'ARGUMENTS'} if exists $args{'ARGUMENTS'};
    $typefile = $args{'TYPESIZELIST'} if exists $args{'TYPESIZELIST'};
    @argv = @{$args{'TYPES'}} if exists $args{'TYPES'};

    init_data_type_sizes();
    make_data_type_list();

    open_header_file();
#    output_headers();
    output_defines();
#    output_stolen_moc_header();
    declare_slot_class();
    close_header_file();

    myprint ".";

    open_source_file();
#    output_includes();
    output_global_stacks();
#    output_global_variables();
    output_signal_helper();
    output_slot_helper();
    output_pig_hash();
    define_slots();
    myprint ".";
    define_signals();
    myprint ".";
    output_slot_matrix();
    output_signal_matrix();
    close_source_file();

    myprint "\n";
    open(STDOUT, ">&STDSAVE");
}

1;
