use ExtUtils::MakeMaker;
require 'perlqt.conf';

WriteMakefile(
    'NAME' => 'libpqt',
    'VERSION_FROM' => 'perlqt.conf',
    'CONFIGURE' => sub { return \%PigConfig },
    'OBJECT' => q{
	pqtmeta$(OBJ_EXT)
	proto$(OBJ_EXT)
	pqtbase$(OBJ_EXT)
	pqt$(OBJ_EXT)
	pqt_v$(OBJ_EXT)
	pqtis$(OBJ_EXT)
	pqtsigslot$(OBJ_EXT)
	sigslot$(OBJ_EXT)
    },
    'realclean' => { 'FILES' => '*.conf ../*.conf ../*/sigslot.* ../core ../types' },
    'depend' => { Makefile => 'perlqt.conf' }
);

sub MY::install {
    return <<INSTALL;
install: all
	cp \$(INST_DYNAMIC) $LibDest
INSTALL
}

