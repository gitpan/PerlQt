use ExtUtils::MakeMaker;
require "../Qt.config";

WriteMakefile(
    'NAME'	=> 'QProgressBar',
    'VERSION_FROM' => 'QProgressBar.pm',
    'CONFIGURE' => sub { return \%QtConfig },
);
