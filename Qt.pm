################################################################################
#
# Copyright (C) 1999-2000, Ashley Winters <jql@accessone.com>
# All rights reserved.
#
# This program is free software; you can redistribute it and/or
# modify it under the same terms as Perl itself.
#

package Qt;
require DynaLoader;

@ISA = qw(DynaLoader);
$VERSION = '2.105';

bootstrap Qt $VERSION;

1;
