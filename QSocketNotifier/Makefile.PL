use ExtUtils::MakeMaker;
require "../Qt.config";

WriteMakefile(
    'NAME'	=> 'QSocketNotifier',
    'VERSION_FROM' => 'QSocketNotifier.pm',
    'CONFIGURE' => sub { return \%QtConfig },
);
