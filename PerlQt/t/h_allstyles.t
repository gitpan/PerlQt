
BEGIN { print "1..2\n" }

# a segfault occuring during the second test most certainly indicates your KDE was
# compiled with --enable-malloc=full (which means KDE's custom malloc can't
# be turned off at runtime).
# There is a bug in KDE's malloc when used with the KThemeStyle engine.
# Either avoid kthemestyles (riscos, marble, system, systemalt)
# or use a KDE compiled with --enable-malloc (without =full)

package ButtonsGroups;
use strict;
use Qt;
use Qt::isa qw(Qt::Widget);
use Qt::slots
	slotChangeGrp3State => [];
use Qt::attributes qw(
	state
	rb21
	rb22
	rb23
);

#
# Constructor
#
# Creates all child widgets of the ButtonGroups window
#

sub NEW {
    shift->SUPER::NEW(@_);

    # Create Widgets which allow easy layouting
    my $vbox = Qt::VBoxLayout(this);
    my $box1 = Qt::HBoxLayout($vbox);
    my $box2 = Qt::HBoxLayout($vbox);

    # ------- first group

    # Create an exclusive button group
    my $bgrp1 = Qt::ButtonGroup(1, &Horizontal, "Button Group &1 (exclusive)", this);
    $box1->addWidget($bgrp1);
    $bgrp1->setExclusive(1);

    # insert 3 radiobuttons
    Qt::RadioButton("R&adiobutton 2", $bgrp1);
    Qt::RadioButton("Ra&diobutton 3", $bgrp1);

    # ------- second group

    # Create a non-exclusive buttongroup
    my $bgrp2 = Qt::ButtonGroup(1, &Horizontal, "Button Group &2 (non-exclusive)", this);
    $box1->addWidget($bgrp2);
    $bgrp2->setExclusive(0);

    # insert 3 checkboxes
    Qt::CheckBox("&Checkbox 1", $bgrp2);
    my $cb12 = Qt::CheckBox("C&heckbox 2", $bgrp2);
    $cb12->setChecked(1);
    my $cb13 = Qt::CheckBox("Triple &State Button", $bgrp2);
    $cb13->setTristate(1);
    $cb13->setChecked(1);

    # ----------- third group

    # create a buttongroup which is exclusive for radiobuttons and non-exclusive for all other buttons
    my $bgrp3 = Qt::ButtonGroup(1, &Horizontal, "Button Group &3 (Radiobutton-exclusive)", this);
    $box2->addWidget($bgrp3);
    $bgrp3->setRadioButtonExclusive(1);

    # insert three radiobuttons
    rb21 = Qt::RadioButton("Rad&iobutton 1", $bgrp3);
    rb22 = Qt::RadioButton("Radi&obutton 2", $bgrp3);
    rb23 = Qt::RadioButton("Radio&button 3", $bgrp3);
    rb23->setChecked(1);

    # insert a checkbox
    state = Qt::CheckBox("E&nable Radiobuttons", $bgrp3);
    state->setChecked(1);
    # ...and connect its SIGNAL clicked() with the SLOT slotChangeGrp3State()
    this->connect(state, SIGNAL('clicked()'), SLOT('slotChangeGrp3State()'));

    # ----------- fourth group

    # create a groupbox which layouts its childs in a columns
    my $bgrp4 = Qt::ButtonGroup(1, &Horizontal, "Groupbox with &normal buttons", this);
    $box2->addWidget($bgrp4);

    # insert three pushbuttons...
    Qt::PushButton("&Push Button", $bgrp4);
    my $tb2 = Qt::PushButton("&Toggle Button", $bgrp4);
    my $tb3 = Qt::PushButton("&Flat Button", $bgrp4);

    # ... and make the second one a toggle button
    $tb2->setToggleButton(1);
    $tb2->setOn(1);

    # ... and make the third one a flat button
    $tb3->setFlat(1);
}

#
# SLOT slotChangeGrp3State()
#
# enables/disables the radiobuttons of the third buttongroup
#

sub slotChangeGrp3State {
    rb21->setEnabled(state->isChecked);
    rb22->setEnabled(state->isChecked);
    rb23->setEnabled(state->isChecked);
}

1;

package MyApp;
use Qt;
use Qt::isa qw|Qt::Application|;
use Qt::attributes qw|styles kthemestyles tstno|;

sub NEW
{
    shift->SUPER::NEW(@_);
    styles = [ grep !/^(marble|riscos|system(alt)?)$/i, @{ Qt::StyleFactory::keys() } ];
    kthemestyles = [ grep /^(marble|riscos|system(alt)?)$/i, @{ Qt::StyleFactory::keys() } ];
    tstno = 0;
}

sub timerEvent
{
    my $style;
    $style = shift @{ &styles } or do 
    {
        # 1) testing all styles, excepted KThemeStyles 
        # 2) testing KThemeStyles
	print "ok ". ++tstno ."\n";
        styles = kthemestyles;
        $style = shift @{ &styles }
    } or emit quit();
    $style and do {
        mainWidget()->setCaption("PerlQt Test - Testing Style $style");
        this->setStyle($style)
    };
}   

1;

package main;

use Qt;
use ButtonsGroups;
use MyApp;

my $a = MyApp(\@ARGV);

my $buttonsgroups = ButtonsGroups;
$buttonsgroups->resize(500, 250);
$buttonsgroups->setCaption("PerlQt Test - Please wait");
$a->setMainWidget($buttonsgroups);
$buttonsgroups->show;

$a->startTimer(2000);
exit $a->exec;
