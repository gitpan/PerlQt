use ExtUtils::MakeMaker;
require "../Qt.config";

WriteMakefile(
    'NAME'	=> 'QProgressDialog',
    'VERSION_FROM' => 'QProgressDialog.pm',
    'CONFIGURE' => sub { return \%QtConfig },
);
