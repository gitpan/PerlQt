package Label;

use QLabel;

use signals 'foo(int)';

@ISA = qw(QLabel);

sub new {
    my $self = shift->SUPER::new(@_);

    $self->connect($self, 'foo(int)', 'setNum(int)');
    emit $self->foo(10);

    return $self;
}

package main;

use Qt;

$label = new Label;
$qApp->setMainWidget($label);
$label->show();
$qApp->exec();
