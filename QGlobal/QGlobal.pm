package QGlobal;

use strict;
use vars qw($VERSION @ISA @EXPORT @EXPORT_OK);

require Exporter;
require DynaLoader;

@ISA = qw(Exporter DynaLoader);
@EXPORT = qw(&qRound);
@EXPORT_OK = qw(%Align $SingleLine $DontClip $ExpandTabs $ShowPrefix $WordBreak
		$GrayText $DontPrint

		%Key $SHIFT $CTRL $ALT $ASCII_ACCEL

		%RasterOp

		%GUI);

$VERSION = '1.02';
bootstrap QGlobal $VERSION;

1;
__END__

=head1 NAME

QGlobal - Internal PerlQt class, required by all other classes

=head1 SYNOPSIS

C<require QGlobal;>

C<use QGlobal qw(...);>

$object = new QClass->immortal;
$object->mortal;

=head1 DESCRIPTION

QGlobal is an internal PerlQt class which holds all globally useful
data/classes. The main class it is host to is Qt::Base. As the name
implies, it is the base-class of all PerlQt objects.

=head2 Qt::Base member functions

=over 4

=item immortal

The C<immortal()> function is available through I<all> PerlQt objects.
Its purpose is to prevent the object from being destroyed by Perl when
it goes out of scope. This is relevant to object which have their
references stored in C<my()> lexical variables. If you allow an object to
go out of scope, it's memory will be freed and it's destructor run. A
destroyed object does not run, and destroyed widgets are not displayed.

When all immortal object references go out of scope, the immortal object
is not destroyed. It is kept around permanently for use in virtual
functions as well as signals/slots.

Be warned that parent objects kill their children on destruction. That
means your child object could be invalid while you I<still> have a Perl
reference to it. This I<is> detected by PerlQt, but it's fatal.

Running C<immortal()> on an object not allocated with new from PerlQt will
result in an unpleasant mandatory warning.

=item mortal

All C<new()> objects in PerlQt are by default mortal. The C<mortal()>
function is only available to reverse C<immortal()>.

If you run C<mortal()> from within a virtual function or slot of an
immortalized object which has gone out of scope, the object will be
destroyed when your self-referential object reference dies.

Running C<mortal()> on an object that did not have C<immortal()> executed
on it first will result in an unpleasant mandatory warning. Oh, and it
won't work either.

=back

=head2 PerlQt destructor internals

Important note: Overriding of DESTROY() for immortal objects may or may not
work. I don't know, and I don't care yet.

I spent alot of time getting destructors to work, and I thought I would
spend some time to document it.

It sounds easy to implement doesn't it? Just add a DESTROY() method which
deletes the object to every class, and you suddenly have object destruction.
It's not nearly that simple though. We have some major complications
to deal with before it works.

=over 4

=item Mortality

In C++ Qt, you can just allocate an object with new and it will last
forever. Even after it goes out of scope. It doesn't work that way in
Perl, so we need to find a way to emulate it. The obvious answer is
to just increase the reference-count of the object to make it immortal.
And, as it turns out, that is the right solution

=item Virtual functions

For virtual functions, we need a reference to the object to pass to
the virtual functions. So, we stash a reference to the object without
increasing the object's reference-count. How do we make sure that no
illegal accesses are made to the object? In C<virtualize::~virtualize()>,
we destroy the reference. In order to keep it from trying to reduce
the reference-count of the object (which may be dead, for all we know),
we convert it into an SVt_NULL and then destroy it.

=item Automatic child deletion

Qt has given us many chances for duplicate delete calls which will
crash PerlQt. To prevent that unpleasant occurance, we assign C<&sv_no>
to the C<DELETE> element of the PerlQt object in the C<virtualize>
destructor, and create a C<DELETED> element to make further accesses to
the C++ object pointer illegal. See the next item.

=item DELETE

The C<DELETE> element of PerlQt objects determines the ability to
destroy an object. The C<want_destroy()> function interprets C<DELETE>
into a simple boolean value to determine the ability to delete the object.

C<DELETE> has 3 possible values.

=over 4

=item &sv_no

This object can never be deleted, ever. This is used for the static
QColors (red, green, etc.) and for objects which have been deleted
without PerlQt's permission.

=item &sv_yes

This object is mortal and is scheduled for deletion when it goes out
of scope.

=item Non-existant

This object is currently immortal, but can be mortalized.

=back

=item Signals and slots

Signals and slots are currently leaked, and just contain a
non-refcount-increasing reference to the object for the slots. Since
signals and slots are globally disconnected on object destruction,
there is no chance of illegally using the slot. Perhaps I should
override disconnectNotify()...

=back

I'm sure there's more to it, but this will have to do for now.

=head2 PerlQt Object internals

QGlobal is a repository for constansts requires by more than one independant
class, and contains Qt::Base which is inherited by all Qt classes.
Every Qt object has two vital hash elements, C<THIS> and C<DESTROY>.
The C<THIS> element holds the actual pointer to the C++ object represented
in ram. PerlQt sub-classes all classes for convienience, access to protected
members, and garbage-collection.

Internally, there are two types of sub-class types, the PClass, and the
pClass. The pClass is availble only for classes which have protected or
virtual members which are accessible via Perl. The PClass is the main
sub-class type. Every class has a P version, and when a PClass is returned
from an XS function, the C<DESTROY> key is created and set to true. See
the Destruction section for info. PClass objects are returned from all
constructors, and from all classes returning S<QClass &> and S<QClass>.

=head2 Object access

There are three functions that are universally useful and likely to be
permanent. They are declared in F<pqt.h>, and every class requires that
header.

=over 4

=item SV *objectify_ptr(void *ptr, char *clname, int delete_on_destroy = 0)

This function is used when you want to convert a class pointer to an object.
I<NEVER, EVER, EVER> try to convert a pointer to an SV manually!!! The
internals are subject to change daily. And believe me, I've done it.
This function is automatically used in the typemap.

The ptr argument is the object to be accessable in Perl. The clname argument
is the name of the class. It is automatically modified so as to strip
off any trailing garbage like spaces or *'s. That means macro conversions
of pointer-types to strings are acceptable. In fact, that's how the typemap
does it. The delete_on_destroy argument is pretty obvious. Just set it to
a true value if you want the object to be deleted when it is destroyed.

=item void *extract_ptr(SV *obj, char *clname)

This does the opposite conversion from objectify_ptr. It I<will> cause
the program to croak if passed what it considers an invalid object.
In XS files, the macro C<pextract(QClass, stackElem)> is usually used
to convert stack elements to pointers. It does automatic typecasting
and ST() and clname.

=item bool want_delete(SV *obj)

This is used in destructors and some other places. It is used to
determine the mortality of the object. It interprets the C<DELETE>
key into a simple boolean value indicating whether the object will
be destroyed when it goes out of scope.

=back

=head2 Virtual functions

The way in which virtual function-calls from C++ to Perl are achieved
is pretty simple at the moment. For every virtual function to be
overridden, a function named QClass_virtualFunction is created in the
QClass_virtualize class. There is a virtualize heirarchy mirroring the
original QClass heirarchy, which passes virtual function guts along the
way.

Since the PClasses don't inherit each other, the same virtual function
must be overridden in all the sub-classes of the class with the virtual
function as well, if you want people to sub-class those classes. Since
every PClass which implements virtual classes inherits virtualize,
all that is needed in the virtual override function is a stub which calls
QClass_virtualFunction.

The QClass_virtualFunction itself just does a method-call to a perl object
which was automatically saved when the object was created.

Every class has a #define QClass_virtual_functions, which contains a list
of all virtual functions in that class. This, in turn, it placed in the
class definition of PClass, and that PClass also inherits PClass_virtualize,
thereby including everything necessary to successfully interface virtual
functions.

=head2 Signals and slots

This section is due for major revision, stay tuned.

=head1 EXPORTED

This list is outdated, stay tuned.

QGlobal is a repository of globally useful constants/enums and functions
for PerlQt.

Among these are C<%Align> and it's friends, C<%Key> and it's friends,
C<%RasterOp>, and C<%GUI>.

=head1 CAVEATS

Everything will change. Everything has changed. Life is not fair.

=head1 AUTHOR

Ashley Winters <jql@accessone.com>
