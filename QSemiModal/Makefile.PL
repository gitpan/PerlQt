use ExtUtils::MakeMaker;
require "../Qt.config";

WriteMakefile(
    'NAME'	=> 'QSemiModal',
    'VERSION_FROM' => 'QSemiModal.pm',
    'CONFIGURE' => sub { return \%QtConfig },
);
