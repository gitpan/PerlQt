use ExtUtils::MakeMaker;

for(<*.c>) { $files .= "$1\$(OBJ_EXT)\n" if /^(.*)\.c$/ }

WriteMakefile(
    'NAME'      => 'libperlqt',
    'VERSION'	=> '2.000',
    'OBJECT'	=> $files,
    'CC'	=> 'g++',
    'INC'	=> '-I$(QTDIR)/include -I../include',
);

sub MY::install {
    return <<INSTALL;
install: all
	cp \$(INST_DYNAMIC) /usr/local/lib
INSTALL
}
