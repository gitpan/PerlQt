
BEGIN { print "1..2\n" }

use Qt;

eval {my $c = Qt::TextCodec::codecForLocale()};

print +$@ ? "not ok\n" : "ok 1\n";

eval {my $s = Qt::Variant( Qt::DateTime::currentDateTime() ) };

print +$@ ? "not ok\n" : "ok 2\n";

