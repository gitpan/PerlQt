package QTableView;

use strict;
use vars qw($VERSION @ISA @EXPORT);

require Exporter;
require DynaLoader;
require QGlobal;

require QFrame;

@ISA = qw(Exporter DynaLoader QFrame);
@EXPORT = qw(%Tbl);

$VERSION = '0.02';
bootstrap QTableView $VERSION;

1;
__END__

=head1 NAME

QTableView - Interface to the Qt QTableView class

=head1 SYNOPSIS

C<use QTableView;>

Inherits QFrame.

=head1 DESCRIPTION

Empty.

=head1 AUTHOR

Ashley Winters <jql@accessone.com>
