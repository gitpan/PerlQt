package Qt::debug;
use Qt;

our %channel = (
    'ambiguous' => 0x01,
    'autoload' => 0x02,
    'calls' => 0x04,
    'gc' => 0x08,
    'virtual' => 0x10,
    'verbose' => 0x20,
    'all' => 0xffff
);

sub import {
    shift;
    my $db = (@_)? 0x0000 : (0x01|0x20);
    map { $db |= $channel{$_} } @_;
    Qt::_internal::setDebug($db);    
}

sub unimport {
    Qt::_internal::setDebug(0);    
}

1;