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
require Config;

unless($OS) {
    unless($OS = $^O) {
	$OS = $Config::Config{'osname'};
    }
}

$win32 = 1 if $OS =~ /Win/;

$MAKE = 'Qt-1.4';

# If you want to compile using Qt-2.0, uncomment the next line
#$MAKE = 'Qt-2.0';

$ENV{QTDIR} = $win32 ? "C:\\Qt" : '/usr/lib/qt' unless $ENV{QTDIR};

##########
# Please modify these arguments as needed
if(!$win32) {
# This is for Unix-based systems
    %Args = (
	CC => 'g++',
	CCFLAGS => '',
	DEFINE => '',
	INC => '-I$(QTDIR)/include -I/usr/X11R6/include -I/usr/include/qt',
	LIBS => "-L$ENV{QTDIR}/lib -L/usr/X11R6/lib -lqt -lX11",
	OPTIMIZE => '-O'
    );
} else {
# This is for Win32 based systems with Visual C++
    %Args = (
        CC => 'cl.exe -nologo',
        CCFLAGS => "$Config::Config{ccflags} -TP",
	DEFINE => '-DQT_DLL -DNO_XSLOCKS',
        LIBS => "-L$ENV{QTDIR}\\lib -L$ENV{MSVCDIR}\\lib qt202.lib qtmain.lib",
	INC => '-I$(QTDIR)\include'
    );
}
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
	INCLUDE => [ "pigmodule_Qt.h" ],
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
    $pl = 0+$Config{PATCHLEVEL};
}

$sv = 0+$Config{SUBVERSION};

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

    if($win32) {
	eval {
	    open(SAVEERR, ">&STDERR") || die "Cannot redirect stderr";
#	    open(STDERR, ">&STDOUT") || die "Cannot >&";   # doesn't work
	    open(STDERR, ">/dev/null") || die "Cannot redirect stderr";
	    my $filename = `$Args{CC} -print-libgcc-file-name`;
	    $libs .= " -L$1 -lgcc" if $filename =~ /(.*)\/libgcc\.a/;
	    open(STDERR, ">&SAVEERR") || die "Cannot restore stderr";
	    close(SAVEERR);
	}
    }

    return { OBJECT => $object, DEFINE => $define, LIBS => $libs };
}

$Args{INC} .= ' -I. -I./include';

$bug = $win32 ? " &1 'Qt'," : '';
WriteMakefile(
# These arguments should remain unchanged.
    %Args,
    NAME => 'Qt',
    DISTNAME => 'PerlQt',
    VERSION_FROM => 'Qt.pm',
    PM => { 'Qt.pm', '$(INST_LIBDIR)/Qt.pm' },
    CONFIGURE => \&configurate,
    depend => { '$(C_FILES)' => '_pigsigslot.h' },
    realclean => { FILES => 'pig_* _pig* typesizes$(EXE_EXT) typesizes.c typelist' . $bug }
);

copy "typesizes_c", "typesizes.c";

sub MY::postamble {
    if(!$win32) {
    return '
typesizes$(EXE_EXT): typesizes$(OBJ_EXT)
	$(CC) $(LARGE) $(LDFLAGS) -o typesizes$(EXE_EXT) typesizes$(OBJ_EXT)

typelist: typesizes$(EXE_EXT)
	./typesizes$(EXE_EXT) > typelist

_pigsigslot.h: typelist
	$(PERL) gensigslot

';
    } else {
    return '
typesizes$(EXE_EXT): typesizes$(OBJ_EXT)
	$(CC) $(LARGE) -o typesizes$(EXE_EXT) typesizes$(OBJ_EXT)

typelist: typesizes$(EXE_EXT)
	.\typesizes$(EXE_EXT) > typelist

_pigsigslot.h: typelist
	$(PERL) gensigslot

';
    }
}
