#!/usr/bin/perl -w

package TestWidget;

use QEvent;
#use QWidget; @ISA = qw(QWidget);
#use QFrame; @ISA = qw(QFrame);
#use QLabel; @ISA = qw(QLabel);
#use QButton; @ISA = qw(QButton);
#use QCheckBox; @ISA = qw(QCheckBox);   # buggy
#use QPushButton; @ISA = qw(QPushButton);
#use QRadioButton; @ISA = qw(QRadioButton);
use QComboBox; @ISA = qw(QComboBox);
#use QTableView; @ISA = qw(QTableView);
#use QListBox; @ISA = qw(QListBox);
#use QDialog; @ISA = qw(QDialog);
#use QFileDialog; @ISA = qw(QFileDialog);
#use QMessageBox; @ISA = qw(QMessageBox);
#use QTabDialog; @ISA = qw(QTabDialog);

sub new {
    $self = shift->SUPER::new; #(undef, 0, $WFlags{Type}{Popup});
#("Hello World");

#    $self->setAlignment($Align{Center});
#    print "self = @{[$$self{'THIS'}]}\n";
    $self->resize(200, 200);
#    print "Umm\n";
#    $self->setBottomScrollBar(1);

    return $self;
}

sub mousePressEvent {
    my $self = shift;
    my $e = shift;
    my $b;

    foreach(keys %Button) { $b = $_ if $e->button == $Button{$_} }
    printf "%s mouse button clicked at %d, %d\n", $b, $e->x, $e->y;
    $self->SUPER::mousePressEvent($e);
}

sub mouseReleaseEvent {
    my $self = shift;
    my $e = shift;
    my $b;

    foreach(keys %Button) { $b = $_ if $e->button == $Button{$_} }
    printf "%s mouse button released at %d, %d\n", $b, $e->x, $e->y;
    $self->SUPER::mouseReleaseEvent($e);
}

sub mouseDoubleClickEvent {
    my $self = shift;
    my $e = shift;
    my $b;

    foreach(keys %Button) { $b = $_ if $e->button == $Button{$_} }
    printf "%s mouse button double-clicked at %d, %d\n",
        $b, $e->x, $e->y;
    $self->SUPER::mouseDoubleClickEvent($e);
}

sub mouseMoveEvent {
    my $self = shift;
    my $e = shift;

    printf "mouse moved to %d, %d\n", $e->x, $e->y;
    $self->SUPER::mouseMoveEvent($e);
}

sub keyPressEvent {
    my $self = shift;
    my $e = shift;
    my $key = $e->key();
#    my($k, $v);

#    while(($k, $v) = each %Key) {
    foreach(keys %Key) {
	if($Key{$_} == $key) { $key = $_; last; }
#	if($v == $key) { $key = $k; last; } 
    }
    if($e->ascii()) {
	my $ascii = chr($e->ascii());
	print "'$ascii' ($key) key pressed\n";
    } else {
	print "$key key pressed\n";
    }
    $self->SUPER::keyPressEvent($e);
}

sub keyReleaseEvent {
    my $self = shift;
    my $e = shift;
    my $key = $e->key();

    foreach(keys %Key) { if($Key{$_} == $key) { $key = $_; last; } }
    if($e->ascii()) {
        my $ascii = chr($e->ascii());
        print "'$ascii' ($key) key released\n";
    } else {
        print "$key key released\n";
    }
    $self->SUPER::keyReleaseEvent($e);
}

sub focusInEvent {
    my $self = shift;
    my $e = shift;

    print "got focus\n" if $e->gotFocus;
    print "lost focus\n" if $e->lostFocus;
    $self->SUPER::focusInEvent($e);
}

sub focusOutEvent {
    my $self = shift;
    my $e = shift;

    print "got focus\n" if $e->gotFocus;
    print "lost focus\n" if $e->lostFocus;
    $self->SUPER::focusOutEvent($e);
}

sub enterEvent {
    my $self = shift;
    my $e = shift;
    print "entered\n";
    $self->SUPER::enterEvent($e);
}

sub leaveEvent {
    my $self = shift;
    my $e = shift;
    print "left\n";
    $self->SUPER::leaveEvent($e);
}

sub paintEvent {
    my $self = shift;
    my $e = shift;
    my($x, $y, $w, $h);

    $e->rect->rect($x, $y, $w, $h);

    print "paint $x, $y, $w, $h\n";
    $self->SUPER::paintEvent($e);
}

sub moveEvent {
    my $self = shift;
    my $e = shift;
    my $old = $e->oldPos;
    my $new = $e->pos;

    printf "moved from %d, %d to %d, %d\n", $old->x, $old->y, $new->x, $new->y;
    $self->SUPER::moveEvent($e);
}

sub resizeEvent {
    my $self = shift;
    my $e = shift;
    my $old = $e->oldSize;
    my $new = $e->size;

    printf "resized from %d, %d to %d, %d\n", $old->width, $old->height,
        $new->width, $new->height;
    $self->SUPER::resizeEvent($e);
}

sub closeEvent {
    my $self = shift;
    my $e = shift;

    print "closing\n";
    $self->SUPER::closeEvent($e);
}

package main;

use Qt;
use QEvent;

$w = new TestWidget;
$qApp->setMainWidget($w);
$w->show();
exit $qApp->exec();
