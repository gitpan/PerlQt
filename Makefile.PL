#!/usr/bin/perl -w
################################################################################
#
# Copyright (C) 1999, Ashley Winters <jql@accessone.com>
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

use ExtUtils::MakeMaker;
use Config;
use File::Copy;
use Pig;

my $filelist;

GenerateSource(
    DIR => [ 'Qt' ],
    TYPEMAPS => [ 'Qt.typemap' ],
    INCLUDE => [ 'pigmodule_Qt.h' ],
    VIRTUALHEADER => 'pigvirtual.h',
    SOURCEDIR => '.',
    Source => \$filelist
);

$debug = 0;

unlink "_pigsigslot.h";
unlink "_pigsigslot.c";
unlink "pigsigslot$Config{'obj_ext'}";
unlink "typesizes$Config{'exe_ext'}";
unlink "typesizes.c";
unlink "typelist";

WriteMakefile(
# Add or modify these arguments as required.
    CC => 'g++',
    CCFLAGS => '',
    DEFINE => "-DPIGDEBUG=$debug -DPIG_QT -DPIGPERL_PATCHLEVEL=$Config{PATCHLEVEL} -DPIGPERL_SUBVERSION=$Config{SUBVERSION}",
    INC => '-I$(QTDIR)/include -I.',
    LIBS => '-lqt',
    OPTIMIZE => '-g',

# These arguments should remain unchanged.

    NAME => 'Qt',
    DISTNAME => 'PerlQt',
    VERSION_FROM => 'Qt.pm',
    PM => { 'Qt.pm', '$(INST_LIBDIR)/Qt.pm' },
    OBJECT => qq{
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
	pigfunc_base\$(OBJ_EXT)
	pigfunc_object\$(OBJ_EXT)
	pigfunc_qt\$(OBJ_EXT)
	@$filelist
    },
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
