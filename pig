#!/usr/bin/perl -w
################################################################################
#
# Copyright (C) 1998, Ashley Winters <jql@accessone.com> - All rights reserved.
#
# This program is free software; you can redistribute it and/or
# modify it under the same terms as Perl itself.
#

$| = 1;
umask 0;

use strict;


my %Info;
my %Input;
my %Methods;
my %Prototypes;

my %IncCache;

my %Inclusive;    # All virtual methods in class and superclasses
my %Exclusive;    # Virtual methods first defined in this class

my $Ext = '.pqt';
my $Module = '';
my $Class = '';
my $Path = '';
my $File = '';
my $Line = 0;
my(%Operator) = (
    "=" => "newcopy",
    "()" => "run",
    "==" => "beq",
    "!=" => "bne",
    "*" => "bmul",
    "/" => "bdiv",
    "+" => "badd",
    "-" => "bsub",
    "neg" => "uneg",
    "*=" => "amul",
    "/=" => "adiv",
    "+=" => "aadd",
    "-=" => "asub",
    "<<" => "serialize",
    ">>" => "deserialize"
);

my(%Types) = (
    'int' => 'int($default)',
    'int*' => 'intptr($default)',
    'int&' => 'intref($default)',
    'long' => 'long($default)',
    'uint' => 'uint($default)',
    'short' => 'short($default)',
    'double' => 'double($default)',
    'float' => 'float($default)',
    'float*' => 'floatptr($default)',
    'bool' => 'bool($default)',
    'bool*' => 'boolptr($default)',
    'enum' => 'enum($default)',
    'char' => 'char($default)',
    'const char*' => 'cstring($default)',
    'QString' => 'cstring($default)',
    'QString&' => 'qstringref($default)',
    'QString*' => 'qstringptr($default)',
);

my(%Cast) = (
    'enum' => 'int',
    'uint' => 'uint'
);

my $Source = 'src';
my $Sourcedir;
my $Libdir = 'lib';

my($Sourcefile, $Headerfile);

my(@ClassList, %ConstantList);

my(@Modules, @I, @Include, @l, @L, @S, @r, @c);
my($verbose, $silent, $pedantic);
my $Indent;

my $Method;

&main();    # Start of the program, bottom of the application

sub whisper { print @_ unless $silent }
sub say { whisper @_ unless $verbose }
sub verbose { whisper $_[0] if $verbose }
sub veryverbose { whisper $_[0] if $verbose && $verbose > 1 }

sub source { print SOURCE @_ }
sub header { print HEADER @_ }
sub vheader { print VHEADER @_ }

package PerlQt::Method;

sub constructor {
    my $self = shift;
    return ($self->{'Name'} eq 'new');
}

sub destructor {
    my $self = shift;
    return ($self->{'Name'} eq 'DESTROY');
}

sub virtual {
    my $self = shift;
    return (defined($self->{'Virtual'}) &&
	    $self->{'Virtual'} ne 'static' &&
	    $self->{'Virtual'} ne 'variable');
}

sub variable {
    my $self = shift;
    return (defined($self->{'Virtual'}) && $self->{'Virtual'} eq 'variable');
}

sub abstract {
    my $self = shift;
    return (defined($self->{'Virtual'}) && $self->{'Virtual'} eq 'abstract');
}

sub static {
    my $self = shift;
    return ($self->constructor || defined $self->{'Virtual'} && $self->{'Virtual'} eq 'static');
}

sub private {
    my $self = shift;
    return ($self->{'Protection'} eq 'private');
}

sub protected {
    my $self = shift;
    return ($self->{'Protection'} eq 'protected');
}

sub public {
    my $self = shift;
    return ($self->{'Protection'} eq 'public');
}

sub const {
    my $self = shift;
    return $self->{'Const'} || "";
}

sub purpose {
    my $self = shift;
    return $self->{'Purpose'};
}

sub perlonly {
    my $self = shift;
    return ($self->purpose eq '&');
}

sub cpponly {
    my $self = shift;
    return ($self->purpose eq '^');
}

sub everylang {
    my $self = shift;
    return ($self->purpose eq '*');
}

package PerlQt::ClassInfo;

sub alias {
    my $self = shift;
    return @{$self->{'Alias'}} if exists $self->{'Alias'};
    return ();
}

sub define {
    my $self = shift;
    return @{$self->{'Define'}} if exists $self->{'Define'};
    return ();
}

sub undefine {
    my $self = shift;
    return @{$self->{'Undef'}} if exists $self->{'Undef'};
    return ();
}

sub include {
    my $self = shift;
    return @{$self->{'Include'}} if exists $self->{'Include'};
    return ();
}

sub inherit {
    my $self = shift;
    return @{$self->{'Inherit'}} if exists $self->{'Inherit'};
    return ();
}

sub virtual {
    my $self = shift;
    return @{$self->{'Virtual'}} if exists $self->{'Virtual'};
    return ();
}

sub export {
    my $self = shift;

    return @{$self->{'Export'}} if exists $self->{'Export'};
    return ();
}

sub class {
    my $self = shift;

    return (!exists $self->{'Class'} || $self->{'Class'});
}

sub copy {
    my $self = shift;

    return (exists $self->{'Copy'} && $self->{'Copy'});
}

package main;

################################################################################
#
# &cpp_type($psuedotype)
#
# Takes a &slurped psuedo-type and converts it into its C++-equivalent
# value.
#
# Returns a string which indicates the type of C++ argument $psuedotype
# represents.
#
sub cpp_type {
    my $arg = shift;

    $arg =~ s/\{.*\}//;
    $arg =~ s/=.*//;
    $arg =~ s/^\s*//;
    $arg =~ s/\s*$//;
    return $arg;
}

################################################################################
#
# &polyname($proto)
#
# Enhance the method-name of a prototype to indicate argument number and
# types.
#
# Returns a string which can be used to compare two prototypes and check for
# an exact C++ inheritance-override match.
#
sub polyname {
    my $proto = shift;
    my $name;
#    cpp_type($proto->{'Returns'});
    $name = $proto->{'Method'};
    $name .= "(";
    my $x = 0;
    for my $argname (@{$proto->{'Arguments'}}) {
        next unless $x++ || $proto->static;
        my $arg = cpp_type($argname);
        $name .= "," if ($x - (1 - $proto->static)) > 1;
        $name .= $arg;
    }
    $name .= ")";
    $name =~ s/\bconst\b//g;
    $name =~ s/\s+//g;
    $name .= 'static' if $proto->static;
    return $name;
}

################################################################################
#
# &getline(\*fileglob)
#
# Read a single prototype from $fileglobref for &slurp. The new prototype is
# saved in $_. Erroneous prototypes are passed through without warning.
#
# The line is saved in $_. The line-number (for debugging) is saved in $line.
# Returns true while not EOF.
#
# This is where any C++ => pqt translation would need to take place.
# &slurp is a sacred function, and should not be touched by mere mortals.
# &getline is far more useful to the huddled masses yearning to add features.
#
sub getline {
    my $handle = shift;

    $Line = 0 if $Line eq "EOF";
    $_ = readline(*$handle);
    $Line++;

    s~//.*~~ if $_;    # remove comments

    unless(defined $_ && !eof(*$handle)) {
	$Line = "EOF";
	return 0 unless defined $_;
    }

    return 1;
}

################################################################################
#
# &slurp(\*fileglob)
#
# Read from $fileglobref, parse it, save it in usable data-structures.
#
#
sub slurp {
    my $source = shift;

    my(@include, @define, @undef, @alias);
    my($class, $protection);
    my $info;

PARSE:
    while(getline($source)) {
	warn "Missing newline in $File ($Line): $_\n" unless chomp || !$pedantic;


########################### This section needs some cleanup
	if(/^\#(include|define|undef)\s*(.*)$/) {
	    my $type = $1;
	    my $arg = $2;
	    if($type eq 'include') {          #include <file.h>
		if($arg =~ /^\<(.*)\>$/) {
		    push @include, $1;
		} else {
		    warn "Bad \#include directive [$_] in $File ($Line)\n";
		}
	    } elsif($type eq 'define') {      #define THIS or #define THIS that
		if($arg =~ /^(\w+)(\s+.+|)$/) {
		    push @define, ($2 ? "$1=$2" : $1);
		} else {
		    warn "Bad \#define directive [$_] in $File ($Line)\n";
		}
	    } elsif($type eq 'undef') {       #undef THIS
		if($arg =~ /^(\w+)\s*$/) {
		    push @undef, $arg;
		} else {
		    warn "Bad \#undef directive [$_] in $File ($Line)\n";
		}
	    }
	}

	s/\#.*//;

	if(/^
	     (suicidal\s+|)        # don't delete on destroy?
	     (virtual\s+|)         # virtual class
	     (class|struct|namespace)\s+ # must have the word 'class' or 'struct'
	     (\w+)\s*              # (virtual)? class QClass
	     (:.*|)                # (virtual)? class QClass : QSuper
	     \{\s*                 # (virtual)? class QClass : QSuper {
	    $/x) {
	    my($suicidal, $v, $t, $c, $s) = ($1, $2, $3, $4, $5);
	    $class = $c;

	    $Info{$class} = $Input{$class}{"\$"}{$class} = {};
	    $info = bless $Info{$class}, 'PerlQt::ClassInfo';

	    push @{$info->{'Virtual'}}, $class if $v;
	    $info->{'Copy'} = 1 if $t eq 'struct';
	    $info->{'Class'} = 0 if $t eq 'namespace';
	    $info->{'Suicidal'} = 1 if $suicidal;

	    $protection = 'public';

	    if($s) {
		my(@list) = split(',', $s);
		for my $super (@list) {
		    if($super =~ /^:?\s*(virtual\s+|)(\w+)\s*$/) {
			push @{$info->{'Inherit'}}, $2;
			push @{$info->{'Virtual'}}, $2 if $1;
		    }
		}
	    }
	    next;
	}
	if(/^\}(.*);\s*$/) {
	    for my $alias (split(',', $1)) {
		$alias =~ s/^\s*(.*?)\s*$/$1/;
		push @alias, $alias;
	    }
	    # Since this is the end of the class, we populate $Info{$class}
	    $Info{$class}{'Alias'} = \@alias if @alias;
	    $Info{$class}{'Include'} = \@include if @include;
	    $Info{$class}{'Define'} = \@define if @define;
	    $Info{$class}{'Undef'} = \@undef if @undef;
	    $class = undef;
	    next;
	}
	if($class) {
	    if(/^\s*(public|protected|private):\s*$/) {
		$protection = $1;
		next;
	    }
	    s/^(\*|\&|\^|)\s*
	       ((?:(?:virtual|abstract|static|variable)\s+)?)
	       (const\s+|)
	       ((?:\w+\s*[\*\&]+\s*|[\w:\<\>\*]+\s*\*?[^\w\(\:\{]|[\w:]+\s+)?)
	       (\{.*?\}\s*|)
	       (~?\w+\s*\(.*|operator.*)
	     /$1$protection $2$3$4$5$class\::$6/x;
#	    print "$_\n";
	}
########################### End of nasty section
	if(/^		  # Method parsing regex
	     (\+|-|)	  # $1 => method-diffs. Defaults to "+" if unspecified
	     (\*|\^|\&|)  # $2 => purpose. Defaults to "*"
	     (.*?)	  # $3 => protection? attribute? return-type?
	     \s*	  # C++ type voodoo =~ m!type\s*(\**\s*)*&?\s*!
	     (\w+)::	  # $4 => class-name
	     (operator\s*\S+  # allow "operator ()" without choking the regex
	      |~?\w+)	  # $5 => method-name, allow "~destructor"
	     \s*	  # allow "type class::method ()"
	     \((.*?)\)	  # $6 => end this argument-list with a space or a ;
	     (?:\s+([:\w].*))? # $7 => post-arg modifiers and colon-substitutes
	     ;		  # EVERY method must be terminated with a semi-colon!
	     (?:\s*\#.*)? # toss any comments at the end of the line
	    $/x) {
	    my($sign, $purpose, $ret, $class, $method, $args, $mod) =
	      ($1,    $2,       $3,   $4,     $5,      $6,    $7);
	    my($perlname, $prot, $virt, $const, $sigslot, $code);
	    my @args;

	    # unified diff format, + means add, - means remove
	    $sign = "+" unless $sign;		# default to + (add)

	    # "*" means visible in Perl and C++
	    # "&" means visible in Perl
	    # "^" means visible in C++
	    $purpose = "*" unless $purpose;

	    # Class::~Class()	    => Class::DESTROY
	    # Class::Class()	    => Class::new
	    # Class::operator ?? () => Class::$operator{??}
	    # Class::method(...)    => Class::method

	    $perlname = ($method =~ /^~/) 		? "DESTROY"	:
			($method eq $class) 		? "new"		:
			($method =~ /operator\s*(.*)$/) ? $Operator{$1} :
			$method;

	    # ^public|protected|private virtual|abstract|static|variable ...+

	    if($ret =~ s/^(public|protected|private)\s*//) { $prot = $1 }
	    if($ret =~ s/^(virtual|abstract|static|variable|)\s*//) {
		$virt = $1 if $1;
	    }
	    if($ret =~ s/^\.{3,}$//) { $ret = length($ret) - 3 }
	    $prot = "public" unless defined $prot;    # default to public

	    # Class::Class() => Class *Class::Class()
	    # Class::~Class() => void Class::~Class()

	    unless($ret) {
		if($perlname eq "new") { $ret = "$class *" }
		elsif($perlname eq "DESTROY") { $ret = "void" }
		else { warn "No return-type [$_] in $File ($Line)\n" }
	    }

	    # Class::method() : $this->method();
	    # Class::method() signal;
	    # Class::method() const;

	    if($mod) {
		my $origmod = $mod;
		if($mod =~ s/\s*:\s*(.*)//) { $code = $1 }
		if($mod =~ s/\s*\b(slot|signal)\b\s*//) { $sigslot = $1 }
		if($mod =~ s/\s*\bconst\b\s*//) { $const = 1 }
		if($mod) {
		    warn "Invalid method-modifier [$origmod] ($mod) " .
			 "in $File ($Line)\n";
		}
	    }

	    # Class::method(...) => Class::method(AV *);
	    # Class::method(.....) => Class::method(SV *, SV *);
	    # Class::method(type1 = Thing(6,7,8,9), that2 = this);

	    for my $arg (split(/,\s+/, $args)) {
		push @args, $arg;
#		if($arg eq "...") {
#		    push @args, "...";
#"AV *";
#		} elsif($arg =~ /^\.{4,}$/) {
#		    push @args, ("SV *") x (length($arg) - 3);
#		} else {
#		}
	    }

	    # Class::method(int) => Class::method(Class *, int)
	    # Class::method() const => Class::method(const Class *)

	    if($perlname ne "new" && (!defined $virt || $virt ne "static")) {
		my $arg;
		$arg .= "const " if defined $const;
		$arg .= "$class *";
		unshift @args, $arg;
	    }

	    my $info = bless {
		Name => $perlname,      # Perl method-name
		File => \$File,		# Filename (for warnings)
		Line => $Line,		# Line-number (for warnings)
		Prototype => $_,	# Actual prototype (for warnings)

		Diff => $sign,          # Add or remove?
		Purpose => $purpose,    # C++ or Perl or Both?
		Protection => $prot,	# private/protected/public
		Virtual => $virt,	# abstract/virtual/static
		Returns => $ret,	# Return-type
		Class => $class,	# Classname for *this and inheritance
		Method => $method,	# Method-name for this->Method()
		Arguments => \@args,	# Argument-list ref
		SigSlot => $sigslot,	# signal/slot
		Const => $const,	# const?
		Code => $code		# Everything between the : and the ;
	    }, 'PerlQt::Method';

	    push @{$Input{$Class}{'Proto'}}, $info;
	    push @{$Methods{$Class}{$perlname}}, $info;
	    $Prototypes{$Class}{&polyname($info)} = $info;
	}   # end if(proto)
################################################################################
# Data parsing code
#
# The first and last line is strictly limited to the data name and style.
#
#%PerlConstantHashName = (
#);
#
#$ClassInfo = {
#};
#
################################################################################
# Data is specified with key/value pairs. The style is modeled after the
# standard perl hash initialization format. However, the comma and digraph =>
# operators are NOT interchangeable in my format. The => is the primary
# key/value delimiter. Without it, the comma has no effect.
#
#%Example = (
#    key => value,
#    this => value, with, a, bunch, of, commas,
#    \#nocomment => \#value,    # You may describe your data in a comment
#    whitespace => is truncated,
#    whitespace
#		=>   is     
#	truncated,
#    I can't have a normal comma => and*(I)-can$have @ny character I want,
#    back-slashing\, while discouraged\, might be permissible => not,
#    fooling with the \=> digraph is not recommended, though
#);
#
	elsif(/^(\%|\$)([:\w]+)(\{.*?\}|)\s*=\s*(\(|\{)\s*$/) {
	    my($id, $name, $type, $open) = ($1, $2, $3, $4);
	    my(%close) = ("(" => ")", "{" => "}");
	    my(%id) = ("(" => "\%", "{" => "\$");
	    my $hash = "";
	    my %hash;

	    push @{$info->{'Export'}}, "$id$name$type" if $id eq '%';

	    while(getline($source)) {
		warn "Missing newline in $File ($Line)\n" unless chomp;
		if(/^(\)|\})(;?)$/) {
		    warn "Missing semicolon in $File ($Line)\n" unless $2;
		    warn "Ambiguous assignment $id$name = $open$1 " .
			 "in $File ($Line)\n" if $id ne $id{$open};
		    warn "Mismatched grouping for $id$name = $open$1 " .
			 "in $File ($Line)\n" if $1 ne $close{$open};
		    last;
		} elsif(/^\#/) {       # Comment removal
		    next;
		} elsif(/^\S/) {
		    warn "Runaway $id$name marked by [$_] in $File ($Line)\n";
		    $_ .= $/;        # de-chompify for redo
		    redo PARSE;
		}
		s/([^\\])\#.*/$1/;
		s/\s+/ /g;

		$hash .= $_;
	    }

	    my(@splice) = split /=>/, $hash;

	    while(@splice) {
		my($key, $value);
		
		$key = shift @splice;
		if(@splice > 1) {
		    $splice[0] =~ s/^\s*(.*[^\s\\]),//;
		    $value = $1;
		} else {
		    $value = shift @splice;
		}
		$key   =~ s/^\s*(.*?)\s*$/$1/;
		$value =~ s/^\s*(.*?)\s*$/$1/;
		
		$hash{$key} = $value;
		$Input{$Class}{$id}{$name} = \%hash;
	    }
	    if($id eq "\$" && $name eq $Class) {
	        $Info{$Class} = $Input{$Class}{$id}{$name};
		bless $Info{$Class}, 'PerlQt::ClassInfo';
#		print "blassed $Class\n";
	    }
	} elsif(/\S/) {
	    warn "Invalid line $Line in $File: $_\n";
	}
    }
}

use Cwd;

sub arguments {
    my(@args) = @_;

    push @I, cwd . "/include";
    push @L, cwd . "/lib";

    for(my $i = 0; $i < @args; $i++) {
        if($args[$i] =~ /^-(.)(.*)/) {
            my($opt, $arg) = ($1, $2);
            if($opt eq 'v') {
                $verbose = 1;
		$verbose += length($arg) if $arg =~ /^v+$/;
            } elsif($opt eq 's') {
                $silent = 1;
           } elsif($opt eq 'p') {
                $pedantic = 1;
	    } elsif($opt eq 'o') {
		$Source = $arg ? $arg : $args[++$i];
	    } elsif($opt eq 'I') {
		push @I, $arg ? $arg : $args[++$i];
	    } elsif($opt eq 'L') {
		push @L, $arg ? $arg : $args[++$i];
	    } elsif($opt eq 'S') {
		push @S, $arg ? $arg : $args[++$i];
	    } elsif($opt eq 'i' && $arg eq 'nclude') {
		push @Include, $args[++$i];
	    } elsif($opt eq 'l') {
		push @l, $arg ? $arg : $args[++$i];
	    } elsif($opt eq 'r') {
		my $a = $arg ? $arg : $args[++$i];
		$a = "pqt_$a";
		push @l, $a;
	    } elsif($opt eq 'c') {
		push @c, $arg ? $arg : $args[++$i];
            } else {
                push @Modules, $args[$i];
            }
        } else {
            push @Modules, $args[$i];
        }
    }
}

sub find ($) {
    my $module = shift;
    my(@path) = ('.', @S);

    for my $path (@path) {
	return "$path/$module" if -d "$path/$module";
    }

    local($") = "', '";
    warn "Cannot find $module in ('@path') for $Class\n";
    return undef;
}

sub ismod ($) {
    my $module = shift;
    my(@path) = ('.', @S);
    for my $path (@path) {
        return 1 if -e "$path/$module$Ext";
        return 1 if -e "$path/$Module/$module$Ext";
    }
    return 0;
}

sub findmod ($) {
    my $module = shift;
    my(@path) = ('.', @S);
#    print "$Module => $Class\n";
    for my $path (@path) {
#	print "$path/$Module/$module\n";
	return "$path/$module" if -e "$path/$module";
	return "$path/$Module/$module" if -e "$path/$Module/$module";
    }

    local($") = "', '";
    warn "Cannot find $module in ('@path') for $Class\n";
    return undef;
}

sub mklibdir {
    mkdir $Libdir, 0755 unless -d $Libdir;
}

sub mksrcdir ($) {
    my $module = shift;
    my $srcdir = "$Source/$module";
    mkdir $Source, 0755 unless -d $Source;
    mkdir $srcdir, 0755 unless -d $srcdir;
    return $srcdir;
}

sub manifest ($) { print MANIFEST $_[0] . "\n" }
sub makefile ($) { print MAKEFILE "\t$_[0]\$(OBJ_EXT)\n" }
sub export ($) { print MODULEEXPORT $_[0] }

sub startmanifest {
    unless(open MANIFEST, ">$Sourcedir/MANIFEST") {
	warn "Cannot open $Sourcedir/MANIFEST for writing: $!";
	return;
    }
    
    manifest "MANIFEST";
}

sub endmanifest {
    close MANIFEST;
}

sub startmakefile {
    unless(open MAKEFILE, ">$Sourcedir/Makefile.PL") {
	warn "Cannot open $Sourcedir/Makefile.PL for writing: $!";
	return;
    }

    manifest "Makefile.PL";

    print MAKEFILE "use ExtUtils::MakeMaker;\n";
    print MAKEFILE "require 'perlqt.conf';\n\n";

    print MAKEFILE "WriteMakefile(\n";
    print MAKEFILE "    'NAME' => '$Module',\n";
    print MAKEFILE "    'VERSION_FROM' => 'perlqt.conf',\n";
    print MAKEFILE "    'CONFIGURE' => sub { return \\%PigConfig },\n";
    print MAKEFILE "    'OBJECT' => q{\n";


    for my $dir (@c) {
	my $path = ($dir =~ m!^/!) ? $dir : "../../$dir";
	next unless opendir(PQTDIR, $dir);
	my $file;
	while(defined($file = readdir(PQTDIR))) {
	    if($file =~ /^(.*)\.c$/) {
		symlink("$path/$file", "$Sourcedir/$file");
		manifest $file;
		makefile $1;
	    }
	}
	closedir(PQTDIR);
    }

    return 1;
}

sub endmakefile {
    print MAKEFILE "    }\n);\n";
    close MAKEFILE;
}

sub startmodulecode {
    unless(open MODULEEXPORT, ">$Sourcedir/$Module.entry.c") {
	warn "Cannot open $Sourcedir/$Module.entry.c for writing: $!";
	return;
    }

    manifest "$Module.entry.c";
    makefile "$Module.entry";

    export qq'#include "pqt.h"\n\n';
}

sub endmodulecode {
    export "\n";
    export "static pqt_classinfolist PQT_module\[] = {\n";
    for my $class (@ClassList) {
	my $suicidenote = $Info{$class}{'Suicidal'} ? "TRUE" : "FALSE";
	if($Info{$class}->class) {
	    export qq'    {\t"$class",\n\tPQT_${class}_methods,\n\tPQT_${class}_isa,\n\t';
	    export qq'PQT_${class}_alias,\n\tPQT_${class}_tocast,\n\tPQT_${class}_fromcast,\n\t$suicidenote\n    },\n';
	} else {
	    export qq'    {\t"$class",\n\tPQT_${class}_methods,\n\t0,\n';
	    export qq'\tPQT_${class}_alias,\n\t0,\n\t0,\n\tFALSE\n    },\n';
	}
    }
    export "    { 0, 0, 0, 0, 0, 0 }\n";
    export "};\n\n";

    export "static pqt_exportinfolist PQT_export\[] = {\n";
    for my $extern (sort { $ConstantList{$a}{'Name'} cmp $ConstantList{$b}{'Name'} } keys %ConstantList) {
	my $cast = $ConstantList{$extern}{'Cast'};
	export qq'    { "%$ConstantList{$extern}{"Name"}", $extern, ';
	if($cast) {
	    $cast =~ s/^\s*const\s+//;
	    if($cast =~ /^\s*(\w+)/) {
		export qq'"$1"';
	    } else {
		warn "$ConstantList{$extern}{'Cast'} is an unacceptable type";
	    }
	} else {
	    export "0";
	}
	export " },\n";
    }
    export "    { 0, 0 }\n";
    export "};\n\n";

    export qq'extern "C" PQT_PROTO(boot_${Module}) {\n';
    export qq'    pqt_load_module("$Module", PQT_module, PQT_export);\n';
    export qq'}\n';
    close MODULEEXPORT;
}

sub info () { return $Info{$Class} }

sub list ($) {
    my $path = shift;

    unless(opendir MODULEDIR, $path) {
	warn "Could not open $path for $Module: $!\n";
	return ();
    }

    my(@c, @h, @pqt);
    for my $file (sort readdir MODULEDIR) {
	push @c, $1 if $file =~ /(.+)\.c$/;
	push @h, $1 if $file =~ /(.+)\.h$/;
	push @pqt, $1 if $file =~ /(.+)$Ext$/;
    }

    closedir MODULEDIR;

    for my $c (@c) { manifest $c . '.c'; } # makefile $c }
    for my $h (@h) { manifest $h . '.h' }

    return @pqt;
}

sub loadmodule {
    my $class = shift;
    return if exists $Info{$class};
    $File = findmod("$class$Ext");
    unless(open PQT, $File) {
	warn "Cannot open $File for $class for reading: $!";
	return;
    }

    my $ssalc = $Class;
    $Class = $class;

    slurp(\*PQT);

    if(!exists($Methods{$class}{'DESTROY'}) && $Info{$class}->class) {
	my $destroy = bless {
	    Name => "DESTROY",
	    File => \$File,
	    Line => 0,
	    Prototype => "$class\::~$class();",
	    Diff => '+',
	    Purpose => '*',
	    Protection => 'public',
	    Virtual => undef,
	    Returns => 'void',
	    Class => $class,
	    Method => "~$class()",
	    Arguments => [ "$class *" ],
	    SigSlot => undef,
	    Const => undef,
	    Code => undef
	}, 'PerlQt::Method';

	push @{$Input{$class}{'Proto'}}, $destroy;
	push @{$Methods{$class}{'DESTROY'}}, $destroy;
	$Prototypes{$class}{&polyname($destroy)} = $destroy;
    }

    $Class = $ssalc;

    close PQT;
}

sub readmodule {
    my $class = shift;
    veryverbose "Reading $class...";
#    $Module = $class;

    loadmodule($class);

    if($Info{$class}{'Inherit'}) {
	for my $super ($Info{$class}->inherit) {
	    next if $Info{$super};
	    veryverbose "\n";
	    readmodule($super, $class);
	}
    }

    veryverbose "\n" unless shift;
}

sub startsource ($) {
    my $class = shift;
    my $info = $Info{$class};

    open SOURCE, ">$Sourcedir/$class.c";
    manifest $class . ".c";
    makefile $class;

    open HEADER, ">$Sourcedir/$class.h";
    manifest $class . ".h";

    my $ifndef = uc("pqt_${class}_h");
    header "#ifndef $ifndef\n";
    header "#define $ifndef\n\n";

    for my $include (@Include, $info->include) {
	for my $undef ($Info{$class}->undefine) {
	    header "#ifdef $undef\n";
	    header "#undef $undef\n";
	    header "#endif\n";
	} 
	for my $define ($Info{$class}->define) {
	    if($define =~ /^(\w+)=(.*)$/) {
		header "#ifdef $1\n#undef $1\n#endif\n";
		header "#define $1 $2\n";
	    } else {
		header "#ifdef $define\n#undef $define\n#endif\n";
		header "#define $define\n";
	    }
	}
	header qq'#include "$include"\n';
    }

    if($info->virtual) {
	open VHEADER, ">$Sourcedir/${class}_v.h";
	manifest $class . "_v.h";
	header qq'#include "${class}_v.h"\n';

	$ifndef = uc("pqt_${class}_v_h");
	vheader "#ifndef $ifndef\n";
	vheader "#define $ifndef\n\n";

	if($info->virtual > 1) {
	    for my $super ($info->virtual) {
		vheader qq'#include "${super}_v.h"\n' if $super ne $class;
	    }
	    vheader "\n";
	} else {
	    vheader qq'#include "pqt_v.h"\n\n' if $info->virtual == 1;
	}
    }

    header "\n";
    source qq'#include "$class.h"\n';

    my %inclist;
    for my $proto (@{$Input{$class}{'Proto'}}) {
	my $ret = $proto->{'Returns'};
	next if $ret eq 'void';
	unless(exists $IncCache{$ret}) {
	    my $type = fetch_ret($ret, 1);
	    if($type =~ /^new (\w+)$/) {
		$IncCache{$ret} = $1;
	    } else {
		$IncCache{$ret} = 0;
	    }
	}
	if($IncCache{$ret} && $IncCache{$ret} ne $class) {
	    for my $header ($Info{$IncCache{$ret}}->include) {
		$inclist{$header}++;
	    }
	}
    }

    for my $include (sort keys %inclist) {
	source qq'#include "$include"\n';
    }
    source "\n";
}

sub endsource ($) {
    my $class = shift;
    my $info = $Info{$class};
    my $ifndef = uc("pqt_${class}_h");
    header "#endif  // $ifndef\n";
    if($info->virtual) {
	$ifndef = uc("pqt_${class}_v_h");
	vheader "#endif  // $ifndef\n";
	close VHEADER;
    }
    close HEADER;
    close SOURCE;
}

sub writeheader {
    return if exists $Info{$Class}{'Class'};
    header "struct pqt_alias_$Class : $Class {\n";
    for my $proto (@{$Methods{$Class}{'new'}}) {
	next if $proto->perlonly;
	my $decl = cpp_constructor_decl($proto);
	next unless $decl;    # BUG
	header "    pqt_alias_$decl {}\n";
    }
    for my $proto (sort { $a->{'Method'} cmp $b->{'Method'} }
		   values %{$Prototypes{$Class}}) {
	next unless $proto->virtual || $proto->protected;
	next if $proto->constructor || $proto->destructor ||
	        $proto->private || $proto->variable || $proto->{'Code'};

	my $decl = cpp_decl_proto($proto, 'pqt');
        $decl =~ s/(\w+\()/pqt_alias_$1/;
	header "    ";
	header "static " if $proto->static;
	header "$decl { ";
	header "return " if $proto->{'Returns'} ne 'void';
	header "$Class\::$proto->{'Method'}\(" .
	    cpp_argname_list($proto, 'pqt') . "\);";
	header " }\n";
    }
    header "};\n\n";
}

sub by_protection {         # SLOW!!!
    my $x = '';
    $x = "A" if $a->public;
    $x = "B" if $a->protected;
    $x = "C" if $a->private;
    $x .= $a->{'Method'};

    my $y = '';
    $y = "A" if $b->public;
    $y = "B" if $b->protected;
    $y = "C" if $b->private;
    $y .= $b->{'Method'};

    $x cmp $y;
}

sub write_virtual_methods_def {
    vheader "#define pqt_virtual_${Class}_methods";
    for my $super (info->virtual) {
	vheader " \\\n    pqt_virtual_${super}_methods" if $super ne $Class;
    }
    my $prot = '';
    for my $proto (sort by_protection values %Exclusive) {
	next unless $proto->virtual;
	next if $proto->destructor;
	if($prot ne $proto->{'Protection'}) {
	    $prot = $proto->{'Protection'};
	    vheader " \\\n";
	    vheader "$prot:";
	}
	my $decl = cpp_decl_proto($proto);        # BUG: Can be removed
	vheader " \\\n    $decl;" if $decl;
    }
    vheader "\n\n";
}

sub write_virtual_class {
    vheader "struct pqt_virtual_$Class : ";
    if(info->virtual > 1) {
	my $i = 0;
	for my $super (info->virtual) {
	    next if $super eq $Class;
	    vheader ", " if $i++;
	    vheader "pqt_virtual_$super";
	}
    } else {
	vheader "virtual pqt_virtual";
    }
    vheader " {\n";

    for my $poly (sort keys %Exclusive) {
	my $proto = $Exclusive{$poly};
        next unless $proto->virtual;
        next if $proto->destructor;
	my $decl = cpp_decl_proto($proto);
	$decl =~ s/(\w+\()/pqt_virtual_$1/;
	vheader "    $decl;\n";
    }

    vheader "};\n\n";
}

sub cpp_deftype {
    my $arg = shift;

    return ($arg =~ /^.*=\s*(.*)/) ? $1 : undef;
}

sub cpp_defaultarg {
    my $arg = shift;
    my $def = cpp_deftype($arg);
#    print "$def\n";
    return defined($def) ? " = $def" : "";
}

sub cpp_decl_proto {
    my $proto = shift;
    my $pre = shift;
    my $nodefault = shift;
    my $decl;
    unless($proto->constructor || $proto->destructor) {
	$decl .= cpp_type($proto->{'Returns'}) . " ";
    }
    $decl .= "$proto->{'Method'}(";

    my $x = 0;
    for my $arg (@{$proto->{'Arguments'}}) {
	next unless $x++ || $proto->static;
	$decl .= ", " if ($x - (1 - $proto->static)) > 1;
	if($arg eq '...') {
	    $decl .= $arg;
	    next;
	}
	my $type = cpp_type($arg);
	return '' unless $type;    # BUG!

	$decl .= $type;
	$decl .= " $pre" . ($x-1) if $pre;
#	print "$arg\n";
	$decl .= cpp_defaultarg($arg) unless $nodefault;
    }

    $decl .= ")";

    if($proto->const) {
	$decl .= " const";
    }

    return $decl;
}

sub cpp_argname_list {
    my $proto = shift;
    my $pre = shift;
    my $arglist = '';
    my $x = 0;
    for my $arg (@{$proto->{'Arguments'}}) {
	next unless $x++ || $proto->static;
	next if $arg eq '...';
	$arglist .= ", " if ($x - (1 - $proto->static)) > 1;
	$arglist .= $pre . ($x-1);
    }
    return $arglist
}

sub cpp_constructor_decl {
    my $proto = shift;
    my @ret;
    my $s = '';

    $s .= cpp_decl_proto($proto, 'pqt');
    return $s unless $s;       # BUG!
    $s .= " : $Class(";
    $s .= cpp_argname_list($proto, 'pqt');
    $s .= ")";

    return $s;
}

sub write_enhanced_class {
    vheader "class pqt_enhanced_$Class : public $Class, private pqt_virtual_$Class {\n";
    vheader "    pqt_virtual_${Class}_methods\n";
    vheader "public:\n";
    for my $proto (@{$Methods{$Class}{'new'}}) {
	next if $proto->perlonly;
	vheader "    pqt_enhanced_" . cpp_constructor_decl($proto) .
	    ", pqt_virtual((void *)this) {}\n";
    }
    vheader "    virtual ~pqt_enhanced_$Class();\n";
    vheader "};\n\n";
}

sub writevheader {
    write_virtual_methods_def;
    write_virtual_class;
    write_enhanced_class;
}

sub fetch_varg {
    my $argument = shift;
    my $argname = shift;
    my $arg = cpp_type($argument);
    my $def = cpp_deftype($argument);
    my $cast = cpp_cast($argument);

    my $type = pqt_type($argument);
    $type =~ s/^\s*//;
    $type =~ s/\s*$//;
    $type =~ s/\s*([\*\&])/$1/g;

    my $s = '';

    my $cmp = $arg;
    $cmp =~ s/\s*([\*\&])/$1/g;

    if(exists $Types{$type}) {
	$s .= "pqt_push_$Types{$type}";
	$argname = "($Cast{$type})$argname" if $Cast{$type};
	$s =~ s/\$default/$argname/g;
    } elsif($cmp ne $type) {
	if($type =~ /^(\w+)\s*\*$/) {
	    $s = "pqt_push_$1($argname)";
	} else {
	    $type =~ s/\W.*//;
	    $s = "pqt_push_$type($argname)";
	}
    } elsif($cast =~ /^(?:const\s+)?(\w+)/) {
	my $class = $1;
	loadmodule($class);

	if($cast =~ /^const\s+(\w+)\s*\*$/) {
	    $s = qq'pqt_push_const_class($argname, "$1")';
	} elsif($cast =~ /^const\s+(\w+)\s*\&$/) {
	    $s = qq'pqt_push_const_classref(&$argname, "$1")';
	} elsif($cast =~ /^(\w+)\s*\*$/) {
	    $s = qq'pqt_push_class($argname, "$1")';
	} elsif($cast =~ /^(\w+)\s*\&$/) {
	    $s = qq'pqt_push_classref($argname, "$1")';
	} else {
	    print "NO $argument\n";
	}
    } else {
	print "--$argument\n";
	
	$s = "($arg)pqt_argument_skip()";
    }
    return $s;
}

sub fetch_vret {
    my $argument = shift;
    my $arg = cpp_type($argument);
    my $cast = cpp_cast($argument);
    my $type = pqt_type($argument);
    $type =~ s/^\s*//;
    $type =~ s/\s*$//;
    $type =~ s/\s*([\*\&])/$1/g;

    my $s = '';

    my $cmp = $arg;
    $cmp =~ s/\s*([\*\&])/$1/g;

    if(exists $Types{$type}) {
	$s = "pqt_pop_$Types{$type}";
	$s =~ s/\$default//g;
	$s = "($arg)$s" if exists $Cast{$type};
    } elsif($cmp ne $type) {
	$s = "pqt_return_$type()";
    } else {
        if($argument =~ /^(?:const\s+)?(\w+)/) {
	    my $class = $1;
	    loadmodule($class);

	    if($argument =~ /^const\s+(\w+)\s*\*$/) {
		$s = qq'(const $1 *)pqt_pop_const_class("$1")';
	    } elsif($argument =~ /^const\s+(\w+)\s*\&?$/) {
		$s = qq'*(const $1 *)pqt_pop_const_class("$1")';
	    } elsif($argument =~ /^(\w+)\s*\*$/) {
		$s = qq'($1 *)pqt_pop_class("$1")';
	    } elsif($argument =~ /^(\w+)\s*\&?$/) {
		$s = qq'*($1 *)pqt_pop_class("$1")';
	    } else {
		print "NO $argument\n";
	    }
	} else {
	    die "We must all die from $argument\n";
	}
#	print "%$argument\n";
    }

    return $s;
}


sub write_virtual_methods {
    for my $poly (sort keys %Exclusive) {
        my $proto = $Exclusive{$poly};
        next unless $proto->virtual;
        next if $proto->destructor;
	next if $proto->cpponly;
        my $decl = cpp_decl_proto($proto, 'pqt', 1);
        $decl =~ s/(\w+\()/pqt_virtual_$Class\::pqt_virtual_$1/;
        source "$decl {\n";
	source "    PQT_VIRTUAL($proto->{'Name'});\n";
	my $x = 0;
	for my $arg (@{$proto->{'Arguments'}}) {
	    next unless $x++;
	    source "    " . fetch_varg($arg, "pqt" . ($x-1)) . ";\n";
#	    source "    pqt_push(&pqt" . ($x-1) . ");\n";
	}
	if($proto->{'Returns'} ne 'void') {
	    source "    pqt_call_retmethod(\"$proto->{'Name'}\");\n";
	    source "    return(" . fetch_vret($proto->{'Returns'}) . ");\n";
	} else {
	    source "    pqt_call_method(\"$proto->{'Name'}\");\n";
	}
	source "}\n\n";
    }
    for my $poly (sort keys %Inclusive) {
	my $proto = $Inclusive{$poly};
	next unless $proto->virtual;
        next if $proto->destructor;
        my $decl = cpp_decl_proto($proto, 'pqt', 1);
	$decl =~ s/(\w+\()/pqt_enhanced_$Class\::$1/;
	source "$decl {\n";
	source "    ";
	source "return " if $proto->{'Returns'} ne 'void';
	source "pqt_virtual_$proto->{'Method'}(" .
	    cpp_argname_list($proto, 'pqt') . ");\n";
	source "}\n\n";
    }
}

sub newfirst {
    my($x, $y) = ($a, $b);
    for my $z ($x, $y) {
        $z = "A" if $z eq "new";         # highest alpha string
        $z = "AA" if $z eq "DESTROY";    # next highest alpha string
    }

    return $x cmp $y;
}

sub i {
    my $in = '';
    $in .= ("\t" x ($Indent/2));
    $in .= "    " if $Indent % 2;
    return $in;
}

sub pqt_type {
    my $argument = shift;

    if($argument =~ /\{(.*?)\}/) {
	return $1;
    } else {
	return cpp_type($argument);
    }
}

sub cpp_cast {
    my $arg = pqt_type(@_);
    $arg =~ s/^\s*//;
    $arg =~ s/\s*$//;
    $arg =~ s/\s*([\*\&])/$1/g;
    return (exists $Cast{$arg}) ? $Cast{$arg} : $arg;
}

sub fetch_ret {
    my $argument = shift;
    my $arg = cpp_type($argument);
    my $cast = cpp_cast($argument);
    my $type = pqt_type($argument);
    $type =~ s/^\s*//;
    $type =~ s/\s*$//;
    $type =~ s/\s*([\*\&])/$1/g;

    my $s = '';

    my $cmp = $arg;
    $cmp =~ s/\s*([\*\&])/$1/g;

    if(exists $Types{$type}) {
	$s = 'pqt_return_' . $Types{$type};
	if(exists $Cast{$type}) {
	    $s =~ s/\$default/($cast)pqtr/g;
	} else {
	    $s =~ s/\$default/pqtr/g;
	}
	$s =~ s/\$type/$arg/g;
    } elsif($cmp ne $type) {
#	print "?$type\n";
	my $pre = "";
	if($type =~ s/(\W).*//) {
	    $pre = '&' if $1 eq '&';
	}
	$s = "pqt_return_$type(${pre}pqtr)";
    } else {
        if($argument =~ /^(?:const\s+)?(\w+)/) {
	    my $class = $1;
#	    print "Loading $class\n";
	    loadmodule($class);
	    if($Info{$class}->copy) {
		return "new $class" if shift; # include headers for new $class()

		if($argument =~ /^(?:const\s+)?(\w+)\s*\*$/) {
		    $s = qq{pqt_return_new_class(pqtr ? new $1(*pqtr) : (void *)pqtr, "$1")};
		} elsif($argument =~ /^(?:const\s+)?(\w+)\s*\&?$/) {
		    $s = qq{pqt_return_new_class(new $1(pqtr), "$1")};
		} else {
		    print "NO $argument\n";
		}
	    } else {
		if($argument =~ /^const\s+(\w+)\s*\*$/) {
		    $s = qq{pqt_return_const_class(pqtr, "$1")};
		} elsif($argument =~ /^const\s+(\w+)\s*\&$/) {
		    $s = qq{pqt_return_const_class(&pqtr, "$1")};
		} elsif($argument =~ /^(\w+)\s*\*$/) {
		    $s = qq{pqt_return_class(pqtr, "$1")};
		} elsif($argument =~ /^(\w+)\s*\&$/) {
		    $s = qq{pqt_return_class(&pqtr, "$1")};
		} else {
		    print "NO $argument\n";
		}
	    }
	} else {
	    die "We must all die from $argument\n";
	}
#	print "%$argument\n";
    }

    return $s;
}

sub fetch_arg {
    my $argument = shift;
    my $arg = cpp_type($argument);
    my $def = cpp_deftype($argument);
    my $cast = cpp_cast($argument);
    my $defarg = defined($def) ? "($cast)($def)" : "";


    my $type = pqt_type($argument);
    $type =~ s/^\s*//;
    $type =~ s/\s*$//;
    $type =~ s/\s*([\*\&])/$1/g;

    my $s = '';

    my $cmp = $arg;
    $cmp =~ s/\s*([\*\&])/$1/g;

    if(exists $Types{$type}) {
	$s .= "($arg)" if exists $Cast{$type};
	$s .= 'pqt_argument_' . $Types{$type};
	$s =~ s/\$default/$defarg/g;
	$s =~ s/\$type/$arg/g;
    } elsif($cmp ne $type) {
	if($type =~ /^(\w+)\s*\*$/) {
	    $s = "*($arg *)pqt_argument_$1()";
	} else {
	    $type =~ s/\W.*//;
	    if($arg =~ /\&\s*$/) {
		$s = "pqt_argument_$type()";
	    } else {
		$s = "($arg)pqt_argument_$type()";
	    }
	}
    } elsif($cast =~ /^(?:const\s+)?(\w+)/) {
	my $class = $1;
	loadmodule($class);
	
	if($cast =~ /^const\s+(\w+)\s*\*$/) {
	    $s = qq'(const $1 *)pqt_argument_const_class';
	    $s .= defined($def) ? qq'("$1", $def)' : qq'("$1")';
	} elsif($cast =~ /^const\s+(\w+)\s*\&$/) {
	    $s = qq'*((const $1 *)pqt_argument_const_classref';
	    $s .= defined($def) ? qq'("$1", &$def))' : qq'("$1"))';
	} elsif($cast =~ /^(\w+)\s*\*$/) {
	    $s = qq'($1 *)pqt_argument_class';
	    $s .= defined($def) ? qq'("$1", $def)' : qq'("$1")';
	} elsif($cast =~ /^(\w+)\s*\&$/) {
	    $s = qq'*(($1 *)pqt_argument_classref';
	    $s .= defined($def) ? qq'("$1", &$def))' : qq'("$1"))';
	} else {
	    print "NO $argument\n";
	}
    } else {
	print "-$argument\n";
	
	$s = "($arg)pqt_argument_skip()";
    }
    return $s;
}

sub write_proto_method {
    my $proto = shift;

    my $x = 0;
    return if $proto->{'Name'} eq 'newcopy';         # broken for now

    if($proto->destructor) {
	source i."$Class * pqt0 = ($Class *)pqt_argument_class_destructor(\"$Class\");\n";
    } else {
	for my $argument (@{$proto->{'Arguments'}}) {
	    my $arg = cpp_type($argument);
	    source i.$arg;
	    source " pqt$x";
	    source " = ";
	    source fetch_arg($argument);
	    source ";\n";
	    $x++;
	}
    }
    source i."PQT_END_ARGUMENTS;\n\n";
#    source "\n" if @{$proto->{'Arguments'}};
    source i;
    if($proto->{'Returns'} ne 'void') {
	my $arg = cpp_type($proto->{'Returns'});
	source $arg;
	source " pqtr = ";
    }
    if($proto->{'Code'}) {
	my $code = $proto->{'Code'};
	$code =~ s/^\s*//;
	$code =~ s/\s*//;
	$code =~ s/\$class/pqtclass/;
	$code =~ s/\$this/pqt0/;
	$code =~ s/\$(\d+)/pqt$1/g;
	source "$code;\n\n";
    } elsif($proto->variable) {
	my $code = $proto->{'Name'};
	my $set = 0;
	if($code =~ /^set/) {
	    $set = 1;
	    $code =~ s/^set([A-Z])/\l$1/;
	    $code =~ s/^set([a-z])/\u$1/;
	}
	if($set) {
	    source "pqt0->$code = pqt1;\n\n";
	} else {
	    source "pqt0->$code;\n\n";
	}
    } elsif($proto->destructor) {
	if(info->virtual) {
	    source "if(pqt_can_delete()) delete ((pqt_enhanced_$Class *)pqt0);\n\n";
	} else {
	    source "if(pqt_can_delete()) delete pqt0;\n\n";
	}
	source i."pqt_return_nothing();\n";
	return;
    } elsif($proto->constructor) {
	if(info->virtual) {
	    source "new pqt_enhanced_";
	} else {
	    source "new ";
	}
    } elsif($proto->static) {
	if($proto->protected) {
	    source "pqt_alias_$Class\::pqt_alias_";
	} else {
	    source "$Class\::";
	}
    } else {
	if($proto->protected || $proto->virtual) {
	    source "((pqt_alias_$Class *)pqt0)->pqt_alias_";
	} else {
	    source "pqt0->";
	}
    }

    unless($proto->{'Code'} || $proto->variable) {
	source "$proto->{'Method'}(";
	source cpp_argname_list($proto, 'pqt');
	source ");\n\n";
    }

    if($proto->{'Name'} eq 'new') {
	source i.qq'pqt_return_new_class(pqtr, "$Class", pqtclass);\n';
    } elsif($proto->{'Returns'} ne 'void') {
	source i.fetch_ret($proto->{'Returns'}).";\n";
    } else {
	source i."pqt_return_nothing();\n";
    }
}

sub group_of_type {
    my $item = shift;
    my $arg = cpp_type($item);
    my $type = pqt_type($item);
    my $cmp = $arg;
    $cmp =~ s/\s*([\*\&])/$1/g;
    $cmp =~ s/\s*\*.*//;
    $type =~ s/^\s*//;
    $type =~ s/\s*$//;
    $type =~ s/\s*([\*\&])/$1/g;
    $type =~ s/\s*\*.*//;
    if($type =~ /^(?:int|long|uint|short|enum)$/) {
	return 'int';
    } elsif($type =~ /^bool$/) {
	return 'bool';
    } elsif($type =~ /^(?:float|double)$/) {
	return 'float';
    } elsif($arg =~ /^(?:const\s+)?char\s*\*\s*$/) {
	return 'string';
    } elsif($cmp ne $type) {
        return group_of_type($arg);
    } elsif($arg =~ /^(?:const\s+)?(\w+)/ and ismod $1) {
	return 'class';
    } else {
#	print "UNKNOWN $arg\n";
	return 'unknown';
    }
}

sub branched_filter {
    my $info = shift;
    my $list = shift;
    my $ninfo = {};

    $ninfo->{'undef'} = [ map { $$list{$_} ? ($_) : () } @{$info->{'undef'}} ];
    $ninfo->{'string'} = [ map { $$list{$_} ? ($_) : () } @{$info->{'string'}} ];

    for my $key (keys %{$info->{'number'}}) {
	$ninfo->{'number'}{$key} = [ map { $$list{$_} ? ($_) : () }
				     @{$info->{'number'}{$key}} ];
    }

    for my $key (keys %{$info->{'class'}}) {
	$ninfo->{'class'}{$key} = [ map { $$list{$_} ? ($_) : () }
				    @{$info->{'class'}{$key}} ];
    }

    return $ninfo;
}

sub branch_condition {
    my $pm = shift;
    my $idx = shift;
    my $list = shift;
    my %list;

    if($Method eq 'new') {
	return 0 unless $idx < @$pm;
    } else {
	return 0 unless $idx < $#$pm;
    }

    for my $item (@$list) { $list{$item}++ }
    source "{\n";
    $Indent++;
    branching_conditional($pm, $idx + 1, \%list);   # mutual recursion
    $Indent--;
    source i."}\n";

    return 1;
}

sub branching_conditional {
    my $pm = shift;
    my $idx = shift;
    my $list = shift;
    my $info = branched_filter(($Method eq 'new') ? $pm->[$idx-1] : $pm->[$idx], $list);
    my $else = 0;

    source i."unsigned int pqti$idx = pqt_argument_info($idx);\n";
    if(scalar @{$info->{'string'}} &&
       scalar @{$info->{'string'}} != scalar @{$info->{'undef'}}) {
	source i;
	source "else " if $else++;
	source "if(pqt_is_string($idx)) ";
	if(scalar @{$info->{'string'}} == 1) {
	    source "pqts = $info->{'string'}[0];\n";
	} elsif(!branch_condition($pm, $idx, $info->{'string'})) {
	    source "pqts = 0;    // AMBIGUOUS\n";
	}
    }
    if(scalar keys %{$info->{'number'}}) {
	my $c = scalar keys %{$info->{'number'}};
	if($c == 1) {
	    my($key) = keys(%{$info->{'number'}});
	    source i;
	    source "else " if $else++;
	    source "if(pqt_is_number($idx)) ";
	    if(scalar @{$info->{'number'}{$key}} == 1) {
		source "pqts = $info->{'number'}{$key}[0];\n";
	    } elsif(!branch_condition($pm, $idx, $info->{'number'}{$key})) {
		source "pqts = 0;      // AMBIGUOUS\n";
	    }
	} elsif($c == 2) {
	    my($k1, $k2) = keys(%{$info->{'number'}});
	    if($k1 eq 'int') {
		source i;
		source "else " if $else++;
                source "if(pqt_is_int($idx)) ";
                if(scalar @{$info->{'number'}{'int'}} == 1) {
                    source "pqts = $info->{'number'}{'int'}[0];\n";
                } elsif(!branch_condition($pm, $idx, $info->{'number'}{'int'})) {
                    source "pqts = 0;      // AMBIGUOUS\n";
                }
	    }
	    if($k2 eq 'int') {
		source i;
		source "else " if $else++;
                source "if(pqt_is_int($idx)) ";
                if(scalar @{$info->{'number'}{'int'}} == 1) {
                    source "pqts = $info->{'number'}{'int'}[0];\n";
                } elsif(!branch_condition($pm, $idx, $info->{'number'}{'int'})) {
                    source "pqts = 0;      // AMBIGUOUS\n";
                }
	    }

	    if($k1 eq 'float') {
		source i;
		source "else " if $else++;
                source "if(pqt_is_float($idx)) ";
                if(scalar @{$info->{'number'}{'float'}} == 1) {
                    source "pqts = $info->{'number'}{'float'}[0];\n";
                } elsif(!branch_condition($pm, $idx, $info->{'number'}{'float'})) {
                    source "pqts = 0;      // AMBIGUOUS\n";
                }
	    }
	    if($k2 eq 'float') {
		source i;
		source "else " if $else++;
                source "if(pqt_is_float($idx)) ";
                if(scalar @{$info->{'number'}{'float'}} == 1) {
                    source "pqts = $info->{'number'}{'float'}[0];\n";
                } elsif(!branch_condition($pm, $idx, $info->{'number'}{'float'})) {
                    source "pqts = 0;      // AMBIGUOUS\n";
                }
	    }

	    if($k1 eq 'bool') {
		source i;
		source "else " if $else++;
                source "if(pqt_is_bool($idx)) ";
		if(scalar @{$info->{'number'}{'bool'}} == 1) {
		    source "pqts = $info->{'number'}{'bool'}[0];\n";
		} elsif(!branch_condition($pm, $idx, $info->{'number'}{'bool'})) {
		    source "pqts = 0;      // AMBIGUOUS\n";
		}
	    }
	    if($k2 eq 'bool') {
		source i;
		source "else " if $else++;
                source "if(pqt_is_bool($idx)) ";
		if(scalar @{$info->{'number'}{'bool'}} == 1) {
		    source "pqts = $info->{'number'}{'bool'}[0];\n";
		} elsif(!branch_condition($pm, $idx, $info->{'number'}{'bool'})) {
		    source "pqts = 0;      // AMBIGUOUS\n";
		}
	    }
	}
    }
    if(scalar @{$info->{'undef'}}) {
	if(scalar @{$info->{'string'}} == scalar @{$info->{'undef'}}) {
	    source i;
	    source "else " if $else++;
	    source "if(pqt_is_string($idx) || pqt_is_undef($idx)) ";
	    if(scalar @{$info->{'string'}} == 1) {
		source "pqts = $info->{'string'}[0];\n";
	    } elsif(!branch_condition($pm, $idx, $info->{'string'})) {
		source "pqts = 0;      // AMBIGUOUS\n";
	    }
	} elsif(scalar(keys %{$info->{'class'}}) == 1 &&
		scalar(@{$info->{'class'}{(keys %{$info->{'class'}})[0]}}) ==
		(scalar(@{$info->{'undef'}}) - scalar(@{$info->{'string'}}))) {
	    my $key = (keys %{$info->{'class'}})[0];
	    source i;
	    source "else " if $else++;
	    source "if(pqt_is_object($idx) || pqt_is_undef($idx)) ";
	    if(scalar @{$info->{'class'}{$key}} == 1) {
		source "pqts = $info->{'class'}{$key}[0];\n";
	    } elsif(!branch_condition($pm, $idx, $info->{'class'}{$key})) {
		source "pqts = 0;    // AMBIGUOUS\n";
	    }
	} else {
	    source i;
	    source "else " if $else++;
	    source "if(pqt_is_undef($idx)) ";
	    if(scalar @{$info->{'undef'}} == 1) {
		source "pqts = $info->{'undef'}[0];\n";
	    } elsif(!branch_condition($pm, $idx, $info->{'undef'})) {
		source "pqts = 0;    // AMBIGUOUS\n";
	    }
	}
    }
    if(scalar keys %{$info->{'class'}}) {
	if(scalar keys %{$info->{'class'}} == 1 &&
#	  (scalar(@{$info->{'string'}}) != scalar(@{$info->{'undef'}})) &&
	   scalar(@{$info->{'class'}{(keys %{$info->{'class'}})[0]}}) !=
	  (scalar(@{$info->{'undef'}}) - scalar(@{$info->{'string'}}))) {
	    my($key) = keys(%{$info->{'class'}});
	    source i;
	    source "else " if $else++;
	    source "if(pqt_is_object($idx)) ";
	    if(scalar @{$info->{'class'}{$key}} == 1) {
		source "pqts = $info->{'class'}{$key}[0];\n";
	    } elsif(!branch_condition($pm, $idx, $info->{'class'}{$key})) {
		source "pqts = 0;     // AMBIGUOUS\n";
	    }
	} elsif(scalar(keys %{$info->{'class'}}) > 1) {

# BUG!!! The classes need to be sorted by sub-class inheritance order
# QWidget before QObject, QFrame before QWidget, QTableView before QFrame

	    for my $key (keys %{$info->{'class'}}) {
		source i;
		source "else " if $else++;
		source "if(pqt_is_class($idx, \"$key\")) ";
		if(scalar @{$info->{'class'}{$key}} == 1) {
		    source "pqts = $info->{'class'}{$key}[0];\n";
		} elsif(!branch_condition($pm, $idx, $info->{'class'}{$key})) {
		    source "pqts = 0;     // AMBIGUOUS\n";
		}
	    }
	}
    }
    if(!$else && $idx < $#$pm) {
#	branching_conditional($pm, $idx + 1, $list);
    }
}

sub write_whichproto {
    my $protos = shift;
    my $method = $protos->[0]{'Name'};
    my @argcnt;

    for(my $item = 0; $item < @$protos; $item++) {
	my $proto = $protos->[$item];
	my $x = 0;
	for my $arg (@{$proto->{'Arguments'}}) {
	    last if defined cpp_deftype($arg);
	    $x++;
	}
	for my $i ($x .. scalar(@{$proto->{'Arguments'}})) {
	    push @{$argcnt[$i]}, $item;
	}
    }

    source i."if(";

    my($i, $bottom);
    for($i = 0; $i < @argcnt; $i++) {
	if(!defined($bottom) && $argcnt[$i]) {
	    if($i == 0) {
		$bottom = 0;
		next;
	    }
	    $bottom = $i;
	    source "pqtc <= ".($i-1);
	}
	elsif(defined($bottom) && !$argcnt[$i]) {
	    source " || " if $bottom++;
	    source "pqtc == $i";
	}
    }

    source " || " if $bottom++;
    source "pqtc >= $i";

    source ") pqts = 0;\n";

    for($i = 0; $i < @argcnt; $i++) {
	next unless ref $argcnt[$i];
	if(scalar @{$argcnt[$i]} == 1) {
	    my $case = $argcnt[$i][0] + 1;
	    source i."else if(pqtc == $i) pqts = $case;\n";
	} else {
	    my @protomatrix;

	    source i."else if(pqtc == $i) {\n";
	    $Indent++;
	    source i."// ".scalar(@{$argcnt[$i]})." possibilities\n";

	    for my $idx (0..($i-1)) {
		$protomatrix[$idx] = {
		    'undef' => [],
		    'string' => [],
		    'number' => {},
		    'class' => {}
		};
	    }

	    my %x;

	    for my $idx (@{$argcnt[$i]}) {
		source "\n";
		source i."// idx: ".($idx+1)."\n";
		my $x = 0;
		for my $arg (@{$protos->[$idx]{'Arguments'}}[0..($i-1)]) {
		    my $info = $protomatrix[$x++];

		    my $type = group_of_type($arg);
		    source i."// $type\n";

		    $x{$idx+1}++;

		    if($type eq 'int') {
			push @{$info->{'number'}{'int'}}, $idx+1;
		    } elsif($type eq 'float') {
			push @{$info->{'number'}{'float'}}, $idx+1;
		    } elsif($type eq 'bool') {
			push @{$info->{'number'}{'bool'}}, $idx+1;
		    } elsif($type eq 'string') {
			push @{$info->{'undef'}}, $idx+1;
			push @{$info->{'string'}}, $idx+1;
		    } elsif($type eq 'class') {
			push @{$info->{'undef'}}, $idx+1 unless $arg =~ /\&\s*$/;
			my $class = $arg;
			$class =~ s/^\s*(?:const\s+)?(\w+).*$/$1/;
			push @{$info->{'class'}{$class}}, $idx+1;
		    } else {
			$x{$idx+1}--;
		    }
		}
	    }

	    for my $idx (0..$#protomatrix) {
		local($") = ', ';
		my $pm = $protomatrix[$idx];

		source i."// \$info[$idx] = {\n";
		source i."//     'undef' => [@{$pm->{'undef'}}],\n";
		source i."//     'string' => [@{$pm->{'string'}}],\n";
		my $x = 0;
		source i."//     'number' => {";
		for my $number (sort keys %{$pm->{'number'}}) {
		    source ", " if $x++ > 0;
		    source "'$number' => [@{$pm->{'number'}{$number}}]";
		}
		source "},\n";

		$x = 0;
		source i."//     'class' => {";
		for my $class (sort keys %{$pm->{'class'}}) {
		    source ", " if $x++ > 0;
		    source "'$class' => [@{$pm->{'class'}{$class}}]";
		}
		source "}\n";
		source i."// };\n";

	    }

	    $Method = $protos->[0]{'Name'};
	    branching_conditional(\@protomatrix, ($Method eq 'new') ? 1 : 0, \%x);

	    $Indent--;
	    source i."}\n";
	}
    }
}

sub write_perl_methods {
    my @methods;

    for my $meth (sort newfirst keys %{$Methods{$Class}}) {
	my @protos;
	for my $proto (@{$Methods{$Class}{$meth}}) {
	    push @protos, $proto
		unless #$proto->variable ||
		       $proto->private  ||
#		       $proto->{'Code'} || 
#		       !$proto->everylang;
		       $proto->cpponly;
	}
	my $protocnt = scalar(@protos);
	next if $protocnt == 0;
	push @methods, $meth;

	my $polymorph = ($protocnt > 1);
	my $poly = 1;

	source "static PQT_PROTO($meth) {\n";
	source "    PQT_BEGIN($meth);\n";
	if($meth eq 'new') {
	    source "    const char *pqtclass = pqt_argument_cstring();\n";
	}

	if($polymorph) {
	    source "\n";
	    source "    int pqts = 0;\n";
	    source "    int pqtc = pqt_argumentcount();\n\n";
	    $Indent = 1;
	    write_whichproto(\@protos);
	    source "    switch(pqts) {\n";
	}
	$Indent = $polymorph ? 3 : 1;
	for my $proto (@protos) {
	    if($polymorph) {
		source "    case $poly:\n\t{\n";
		$poly++;
	    }
	    write_proto_method($proto);
	    if($polymorph) {
		source "\t}\n";
		source "\tbreak;\n";
	    }
	}
	if($polymorph) {
	    source "    default:\n";
	    source qq{\tpqt_ambiguous("$Class", "$protos[0]{'Name'}");\n\tbreak;\n};
	    source "    }\n";
	}
	source "    PQT_END;\n";
	source "}\n\n";
    }
    export "extern pqt_struct_methodlist PQT_${Class}_methods[];\n";
    source "pqt_struct_methodlist PQT_${Class}_methods[] = {\n";
    for my $meth (sort newfirst @methods) {
	source "    { \"$meth\", PQT_PROTONAME($meth) },\n";
    }
    source "    { 0, 0 }\n";
    source "};\n\n";
}

sub write_alias {
    export "extern const char *PQT_${Class}_alias[];\n";
    source "const char *PQT_${Class}_alias[] = { ";
    for my $alias (info->alias) { source qq{"$alias", } }
    source "0 };\n\n";
}

sub write_isa {
    export "extern const char *PQT_${Class}_isa[];\n";
    source "const char *PQT_${Class}_isa[] = { ";
    for my $super (info->inherit) { source qq{"$super", } if $Info{$super}->class }
    source "0 };\n\n";
}

sub supernames {
    my $class = shift;
    my $array = shift;
    return if exists $Info{$class}{'Class'} && !$Info{$class}{'Class'};
    push @$array, $class;
    return unless exists $Info{$class}{'Inherit'};
    for my $super ($Info{$class}->inherit) {
        supernames($super, $array);
    }
}

sub write_typecast {
    my $direction = shift;
    export "extern void *PQT_${Class}_${direction}cast(const char *, void *);\n";
    source "void *PQT_${Class}_${direction}cast(const char *pqt0, void *pqt1) {\n";
    my @super;
    supernames($Class, \@super);
    push @super, "virtual" if info->virtual;
    source "    const char *pqt_super[] = { ";
    for my $super (@super) {
	source qq{"$super", };
    }
    source "0 };\n\n";

    source "    if(!pqt0) return pqt1;\n";
    source "    switch(pqt_find_in_array(pqt0, pqt_super)) {\n";
    my $x = 0;
    for my $super (@super) {
	source "\tcase $x: return (void *)";
	if($direction eq 'from') {
	    if($super eq 'virtual') {
		source "($Class *)(pqt_enhanced_$Class *)(((pqt_virtual *)pqt1)->pqt_this);\n";
	    } else {
		source "($Class *)($super *)pqt1;\n";
	    }
	} else {
	    if($super eq 'virtual') {
		source "(pqt_virtual *)(pqt_virtual_$Class *)(pqt_enhanced_$Class *)($Class *)";
	    } else {
		source "($super *)($Class *)";
	    }
	    source "pqt1;\n";
	}
	$x++;
    }
    source "\tdefault: return 0;\n";
    source "    }\n";

    source "}\n\n";
}

sub write_constants {
    for my $constant ($Info{$Class}->export) {
	if($constant =~ /(\%|\@|\$|\&)(\w+)(.*)/) {
	    my($type, $name, $rest) = ($1, $2, $3);
	    my $cast = 'ulong';
	    if($type eq '%') {
		$cast = $1 if $rest =~ s/^{(.*?)}//;
		export "extern pqt_struct_constantdata PQT_${Class}_constant_$name\[];\n";
		source "pqt_struct_constantdata PQT_${Class}_constant_$name\[] = {\n";

		$ConstantList{"PQT_${Class}_constant_$name"} = {
		    Name => $name,
		    Type => 'HASH',
		    Cast => ($cast eq 'ulong') ? undef : $cast
		};

		for my $key (sort keys %{$Input{$Class}{$type}{$name}}) {
		    source "    { \"$key\", (long)($cast)$Input{$Class}{$type}{$name}{$key} },\n";
		}
		source "    { 0, 0 }\n";
		source "};\n\n";
	    }
	}
    }
}

sub write_virtual_destructor {
    source "pqt_enhanced_$Class\::~pqt_enhanced_$Class() {\n";
    source "    pqt_destroy_object(this, (pqt_virtual *)this);\n";
    source "}\n\n";
}

sub writesource {
    write_alias;
    if(info->class) {
	write_isa;
	write_typecast('to');
	write_typecast('from');
    }
    write_constants;
    write_perl_methods;
    write_virtual_destructor if info->virtual;
    write_virtual_methods if info->virtual;
}

sub findvirtual {
    my $class = shift;
    for my $poly (keys %{$Prototypes{$class}}) {
	$Inclusive{$poly} = $Prototypes{$class}{$poly}
	    unless exists $Inclusive{$poly};
    }

    for my $super ($Info{$class}->virtual) {
	next if $super eq $class;
        findvirtual($super);
    }
}

sub getvirtual {
    %Inclusive = ();
    %Exclusive = ();
    for my $super (info->virtual) {
	next if $super eq $Class;
	findvirtual($super);
    }
    %Exclusive = %{$Prototypes{$Class}};
    for my $poly (keys %Exclusive) {
	if(exists $Inclusive{$poly}) {
	    delete $Exclusive{$poly};
	} else {
	    $Inclusive{$poly} = $Exclusive{$poly};
	}
    }
}

sub writemodule {
    my $class = shift;
    verbose "Writing $class...";

    getvirtual if info->virtual;

    startsource $class;
    writesource;
    writeheader;
    writevheader if info->virtual;
    endsource $class;

    push @ClassList, $class;

    say ".";
    verbose "\n";
}

sub main {
    arguments(@ARGV);

MODULE:
    for my $module (@Modules) {
	my $path = find $module;
	next MODULE unless $path;
	$Module = $module;
	$Path = $path;

	say "Loading $module...";
	verbose "Loading $module...";

#	mklibdir;

	my $srcdir = mksrcdir $module;
	next MODULE unless $srcdir;
	$Sourcedir = $srcdir;

	next MODULE unless startmanifest;
	next MODULE unless startmakefile;
	next MODULE unless startmodulecode;

	my(@classes) = list $path;

	verbose "\n";

	for my $class (@classes) {
	    $Class = $class;
	    readmodule $class;
	    writemodule $class;
	}
	say "\n";
	endmodulecode; endmanifest; endmakefile;
    }
}
