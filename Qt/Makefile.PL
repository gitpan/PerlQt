use ExtUtils::MakeMaker;

for(<*>) { push @dirlist, $_ if -d && /^[A-Z]/ }
for(@dirlist) {
    open MAKEFILE, ">$_/Makefile.PL" or
	die "Could not write to $_/Makefile.PL";
    print MAKEFILE "\$::name = \"Qt::$_\";\n";
    print MAKEFILE "do '../Makefile.Qt';\n";
    close MAKEFILE;
}

WriteMakefile(
    NAME	=> 'Qt',
    DISTNAME	=> 'PerlQt',
    VERSION	=> '2.000',
    DIR		=> \@dirlist,
    CC		=> 'g++',
    CCFLAGS     => '-DHAS_BOOL',
    LIBS        => '-lperlqt -lqt',
    OPTIMIZE    => '-O2 -m486 -pipe',
    INC		=> '-I../include -I$(QTDIR)/include',
);
