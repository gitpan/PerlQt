#!/usr/bin/perl -w

package EventWidget;

use QEvent;
#use QWidget;

#@ISA = qw(QWidget);

use QLabel;

@ISA = qw(QLabel);

sub new {
    my $self = shift->SUPER::new(@_);

    $self->resize(200, 200);
    $self->setAlignment($Align{Center});
    $self->setText("Hello World");

    return $self;
}

sub event {
#    print "event running\n";
    my $self = shift;
    my $event = shift;
#    print "calling type\n";
    my $type = $event->type;
    my($k, $v);
#    print "running foreach\n";

    while(($k, $v) = each %Event) {
#	print "key = $k\n";
	if($v == $type) { print "got a $k event\n"; last; }
    }
    $k = scalar keys %Event;

#    foreach(keys %Event) {
#	print "key = $_\n";
#	if($Event{$_} == $type) { print "got a $_ event\n"; last; }
#    }
#    print "returning\n";
    return 1;
}

package main;

use Qt;

$w = new EventWidget;
$qApp->setMainWidget($w);
$w->show;
$qApp->exec;
