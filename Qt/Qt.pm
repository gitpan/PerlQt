package Qt;
use 5.004;
use strict;

require DynaLoader;

@Qt::ISA = ('DynaLoader');
$Qt::VERSION = '2.000';

bootstrap Qt $Qt::VERSION;

1;
