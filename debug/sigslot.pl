#!/usr/bin/perl -w

package SigSlot;

use QObject;
#use QFrame;
#use QLabel;

use signals 'foo()';
use slots 'bar()';

@ISA = qw(QObject);
#@ISA = qw(QFrame);
#@ISA = qw(QLabel);

sub new {
    my $self = shift->SUPER::new(@_);

    $self->connect($self, 'foo()', 'bar()');
    emit $self->foo();

    return $self;
}

sub bar {
    print "bar called, it worked\n";
}

package main;

use Qt;

$x = new SigSlot;
print "$x\n";
