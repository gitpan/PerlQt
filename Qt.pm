use strict;

# These variables will be auto-created with absolute paths on installation
# For now, I give them decent default values.

my $file = 'src/Qt/blib/arch/auto/Qt/Qt.so';
my $symbolname = 'PQT_boot_Qt';

{
    package DynaLoader;
    my($handle, $symbol, $xs);

    $DynaLoader::dl_debug = $ENV{'PERL_DL_DEBUG'} || 0;
    boot_DynaLoader('DynaLoader') if defined &boot_DynaLoader;

    $handle = dl_load_file($file, 0) || die dl_error();
    $symbol = dl_find_symbol($handle, $symbolname) || die dl_error();
    $xs = dl_install_xsub('', $symbol) || die dl_error();

    eval { $xs->() }; die $@ if $@;
}

1;
