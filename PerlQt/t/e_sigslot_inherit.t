BEGIN { print "1..3\n" }

package MyApp;
use Qt;
use Qt::isa qw(Qt::Application);
use Qt::slots
        foo => ['int'],
        baz => [];
use Qt::signals
        bar => ['int'];

sub NEW
{
     shift->SUPER::NEW(@_);
     this->connect(this, SIGNAL 'bar(int)', SLOT 'foo(int)');
     this->connect(this, SIGNAL 'aboutToQuit()', SLOT 'baz()');
}

sub foo
{
    # 1) testing correct inheritance of sig/slots
    print +($_[0] == 3) ? "ok 1\n" : "not ok\n";
}

sub baz
{
    print "ok 3\n";
}     

1;

package MySubApp;
use Qt;
use MyApp;
use Qt::isa qw( MyApp );


sub NEW 
{
    shift->SUPER::NEW(@_);
    emit foo(3);
}

sub baz
{
   # 2) testing further inheritance of sig/slots
   print "ok 2\n";
   # 3) testing Perl to Perl SUPER
   SUPER->baz()
}

1;

package main;

use Qt;
use MySubApp;

$a = 0;
$a = MySubApp(\@ARGV);

Qt::Timer::singleShot( 300, Qt::app(), SLOT "quit()" );

exit Qt::app()->exec;
