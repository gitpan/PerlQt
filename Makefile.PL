#!/usr/bin/perl -w
################################################################################
#
# Copyright (C) 1999-2000, Ashley Winters <jql@accessone.com>
#
# This program is free software; you can redistribute it and/or
# modify it under the same terms as Perl itself.
#
# This is the Makefile.PL for PerlQt
#
# Usage:
# perl Makefile.PL
# make
# make install
#
# This is a Unix-only Makefile.PL as far as I know...
#

$MAKE = 'Qt-1.4';

# If you want to compile using Qt-2.0, uncomment the next line
#$MAKE = 'Qt-2.0';

##########
# Please modify these arguments as needed
%Args = (
    CC => 'g++',
    CCFLAGS => '',
    DEFINE => '',
    INC => '-I$(QTDIR)/include -I/usr/X11R6/include -I/usr/include/qt -I.',
    LIBS => '-L$(QTDIR)/lib -L/usr/X11R6/lib -lqt -lX11',
    OPTIMIZE => '-O'
);
##########

use ExtUtils::MakeMaker;
use Config;
use File::Copy;
use Pig;

my $filelist;

unless(@ARGV && $ARGV[0] =~ /^-f/) {
    GenerateSource(
	DIR => [ $MAKE ],
	TYPEMAPS => [ "$MAKE/typemap" ],
	INCLUDE => [ "pigmodule_$MAKE.h" ],
	VIRTUALHEADER => 'pigvirtual.h',
	SOURCEDIR => '.',
	Source => \$filelist
    );
}

$debug = 0;

unlink "_pigsigslot.h";
unlink "_pigsigslot.c";
unlink "pigsigslot$Config{'obj_ext'}";
unlink "typesizes$Config{'exe_ext'}";
unlink "typesizes.c";
unlink "typelist";

if($Config{bincompat3} && $Config{bincompat3} =~ /y/) {
    $pl = 3;
} else {
    $pl = $Config{PATCHLEVEL};
}

$sv = $Config{SUBVERSION};

sub configurate {
    my $object = qq{
	pigboot\$(OBJ_EXT)
	pigclassinfo\$(OBJ_EXT)
	pigconstant\$(OBJ_EXT)
	pigemit\$(OBJ_EXT)
	pigobject\$(OBJ_EXT)
	pigperl\$(OBJ_EXT)
	pigproto\$(OBJ_EXT)
	pigsigslot\$(OBJ_EXT)
	pigsymbol\$(OBJ_EXT)
	pigsymbol_Qt\$(OBJ_EXT)
	pigvirtual\$(OBJ_EXT)
	pigtype_base\$(OBJ_EXT) 
	pigtype_object\$(OBJ_EXT)
	pigtype_qt\$(OBJ_EXT)
	pigtype_qt_qstring\$(OBJ_EXT)
	pigtype_qt_qstrlist\$(OBJ_EXT)
	pigfunc_base\$(OBJ_EXT)
	pigfunc_object\$(OBJ_EXT)
	pigfunc_qt\$(OBJ_EXT)
	@$filelist
    };

    my $define = "-DPIGDEBUG=$debug -DPIG_QT " .
	"-DPIGPERL_PL=$pl -DPIGPERL_SV=$sv $Args{DEFINE}";

    my $libs = $Args{LIBS};

    eval {
	open(SAVEERR, ">&STDERR") || die "Cannot redirect stderr";
#	open(STDERR, ">&STDOUT") || die "Cannot >&";   # doesn't work
	open(STDERR, ">/dev/null") || die "Cannot redirect stderr";
	my $filename = `$Args{CC} -print-libgcc-file-name`;
	$libs .= " -L$1 -lgcc" if $filename =~ /(.*)\/libgcc\.a/;
	open(STDERR, ">&SAVEERR") || die "Cannot restore stderr";
	close(SAVEERR);
    };

    return { OBJECT => $object, DEFINE => $define, LIBS => $libs };
}

WriteMakefile(
# These arguments should remain unchanged.
    %Args,
    NAME => 'Qt',
    DISTNAME => 'PerlQt',
    VERSION_FROM => 'Qt.pm',
    PM => { 'Qt.pm', '$(INST_LIBDIR)/Qt.pm' },
    CONFIGURE => \&configurate,
    depend => { '$(C_FILES)' => '_pigsigslot.h' },
    realclean => { FILES => 'pig_* _pig* typesizes$(EXE_EXT) typesizes.c typelist' }
);

copy "typesizes_c", "typesizes.c";

sub MY::postamble {
    '
typesizes$(EXE_EXT): typesizes$(OBJ_EXT)
	$(CC) $(LARGE) $(LDFLAGS) -o typesizes$(EXE_EXT) typesizes$(OBJ_EXT)

typelist: typesizes$(EXE_EXT)
	./typesizes$(EXE_EXT) > typelist

_pigsigslot.h: typelist
	$(PERL) gensigslot

';
}
