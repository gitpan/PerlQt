#!/usr/bin/perl -w

#
# This Makefile.PL is an interface to ./configure intended to be used 
# by automatic CPAN builds. It just checks that some needed environment
# variables are set and eventually tries to guess their value... 
#
# You should use it instead of the ./configure program ;
# it accepts the same options.
#

use strict;

my $current_automake="1.5";
my @prefix = ('/usr', '/usr/local');

my $res="";
my %p;

exec "./configure --help" if grep /^-?-h(elp)?$/, @ARGV;

unless ($ENV{'QTDIR'} or grep /--with-qt-dir/, @ARGV)
{
  print "\n!!!!!!!!!!!! WARNING !!!!!!!!!!!!\n".
        " Your QTDIR environment variable is not set and you\n".
        "did not use the '--with-qt-dir=' commandline option.\n".
        "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n\n";
  print "Nevermind, I'll try to guess Qt's location.\n";
  sleep(6);
  
  my @alt=`locate libqt-mt.so 2>/dev/null`;

  if(!check_exit_status($?) || !@alt)
  {
    print "mmh... locate did not help. We'll try a find then.\n";
    sleep(2);
    
    print "Scanning local file system...\n";
    @alt=`find / -name "libqt-mt.so*" 2>/dev/null`;    
  }

  if(!check_exit_status($?) || !@alt)
  {
    print "Still no luck... I'll give up and let ./configure work it out\n";
  }
  elsif(@alt>1)
  {
    print "We have several answers. I'll try to discriminate a bit...\n";
    sleep(3);
    for(@alt) { /(.*)\/lib\// and $p{$1}++ }
    if(keys %p == 1)
    {
      $res = each %p;
    }
    else
    {
      my ($ver,$tmp)=(0,0);
      for(@alt)
      { 
        /libqt-mt\.so(?:\.(\d+))?(?:\.(\d+))?(?:\.(\d+))?$/;
        $tmp = (($1?$1:0)*100)+(($2?$2:0)*10)+($3?$3:0);
        if($tmp>=$ver)
        {
          $ver = $tmp;
          $res = (/(.*)\/lib\//)[0]
        }
      }
      $res = each %p if keys %p ==1;
    }
    print $res?"OK. We can try --with-qt-dir=$res.\n":"Nope, that's too fuzzy. I'll give up and let ./configure decide.\n";  
  }
  else
  {
    ($res=$alt[0])=~s|(.*)/lib/.*|$1|;
    print "Fine. We'll try with --with-qt-dir=$res.\n";
  }  
  sleep(3);
}

unshift(@ARGV, "--with-qt-dir=$res") if $res;

unless ($ENV{'KDEDIR'} or grep /--prefix/, @ARGV)
{
  print "\n!!!!!!!!!!!! WARNING !!!!!!!!!!!!\n".
        " Your KDEDIR environment variable is not set and you\n".
        "did not use the '--prefix=' commandline option.\n";
  print "KDE-3 isn't required at all. However, if it's installed on your system,\n".
        "it is much better to specify it's location since PerlQt uses (or build, if\n".
        "it can't find it) a KDE library named Smoke.\n";
  print "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n\n";
  sleep(5);
}

my @auto=`automake --version 2>/dev/null`;
if(!check_exit_status($?))
{
  for(@prefix)
  {
    my $path = $_."/bin/automake";
    if(-e $path and -x $path)
    {
      @auto=`$path --version`;
      last;
    }
  }
}
if(!check_exit_status($?))
{
  print "\n!!!!!!!!!! WARNING !!!!!!!!!!!\n".
        "I couldn't find *automake* anywhere in PATH or standard directories.\n".
        "Unless the Smoke library is already installed on your system,\n".
        "you won't be able to build PerlQt.\n".
        "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n\n";
  die if grep /--enable-smoke/, @ARGV;
  sleep(5);
}
else
{
  if($auto[0] =~/([\d.]+)/ and $& >= ($current_automake + 0.1))
  {
    print "Automake looks recent... we'd better try to rebuild the framework...\n";
    sleep(2);
    `make -f Makefile.cvs`;
    if(!check_exit_status($?))
    { 
      print "Ah, there was a problem...  better let configure sort it out then.\n";
      sleep(3);
    }
  }
}

print "\nNow starting ./configure ...\n\n";

exec join " ", "./configure", @ARGV;

#--------------------------------------------------------------#

sub check_exit_status
{
        my $a = 0xFFFF & shift;
        if( !$a )
        {
                return 1;
        }
        elsif( $a == 0xFF00 )
        {
                #die "\nSystem call failed: $!\n";
        }
        elsif( $a > 0x80 )
        {
                # non-zero status.
        }
        else
        {
                if( $a & 0x80 )
                {
                       #die "\nProgram coredumped with signal ". ($a & ~0x80);
                }
                die "\nProgram interrupted by signal $a\n";
        }
        return 0;
}

