/**********************************************************************
** Copyright (C) 2000 Trolltech AS.  All rights reserved.
** Copyright (c) 2002 Germain Garand <germain@ebooksfrance.com>
**
** This file is part of Qt Designer.
**
** This file may be distributed and/or modified under the terms of the
** GNU General Public License version 2 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
**
** See http://www.trolltech.com/gpl/ for GPL licensing information.
**
** Contact info@trolltech.com if any conditions of this licensing are
** not clear to you.
**
**********************************************************************/
/*
** 06/2002 : Initial release of puic, the PerlQt User Interface Compiler,
**           a work derivated from uic (the Qt User Interface Compiler)
**           and pyuic (the PyQt User Interface Compiler).
**
**           G.Garand
**
**********************************************************************/

#include <iostream.h>
#include "uic.h"
#include "parser.h"
#include "widgetdatabase.h"
#include "domtool.h"
#include <qstringlist.h>
#include <qregexp.h>
#include <qfile.h>
#include <qfileinfo.h>
#define NO_STATIC_COLORS
#include <globaldefs.h>
#include <zlib.h>

static QByteArray unzipXPM( QString data, ulong& length )
{
    uchar *ba = new uchar[ data.length() / 2 ];
    for ( int i = 0; i < (int)data.length() / 2; ++i ) {
	char h = data[ 2 * i ].latin1();
	char l = data[ 2 * i  + 1 ].latin1();
	uchar r = 0;
	if ( h <= '9' )
	    r += h - '0';
	else
	    r += h - 'a' + 10;
	r = r << 4;
	if ( l <= '9' )
	    r += l - '0';
	else
	    r += l - 'a' + 10;
	ba[ i ] = r;
    }
    // I'm not sure this makes sense. Why couldn't the compressed data be
    // less than 20% of the original data? Maybe it's enough to trust the
    // `length' passed as an argument. Quoting the zlib header:
    // 		Upon entry, destLen is the total size of the destination
    // 		buffer, which must be large enough to hold the entire
    // 		uncompressed data. (The size of the uncompressed data must
    // 		have been saved previously by the compressor and transmitted
    // 		to the decompressor by some mechanism outside the scope of
    // 		this compression library.)
    // Which is the role of `length'. On the other hand this could prevent
    // crashes in some cases of slightly corrupt UIC files.
    if ( length <  data.length() * 5 )
	length = data.length() * 5;
    QByteArray baunzip( length );
    ::uncompress( (uchar*) baunzip.data(), &length, ba, data.length()/2 );
    delete[] ba;
    return baunzip;
}



/*!
  Creates an implementation ( cpp-file ) for the form given in \a e

  \sa createFormDecl(), createObjectImpl()
 */
void Uic::createFormImpl( const QDomElement &e )
{
    QDomElement n;
    QDomNodeList nl;
    int i;
    QString objClass = getClassName( e );
    if ( objClass.isEmpty() )
	return;
    QString objName = getObjectName( e );
    out << indent << "package " << nameOfClass << ";" << endl;
    out << indent << "use Qt;" << endl;

    // generate local and local includes required
    QStringList globalIncludes, localIncludes;
    QStringList::Iterator it;
    QStringList sqlClasses;

    QMap<QString, CustomInclude> customWidgetIncludes;
    QMap<QString, QString> functionImpls;

    // find additional slots
    QStringList extraSlots;
    QStringList extraSlotTypes;
    nl = e.parentNode().toElement().elementsByTagName( "slot" );
    for ( i = 0; i < (int) nl.length(); i++ ) {
	n = nl.item(i).toElement();
	if ( n.parentNode().toElement().tagName() != "slots"
	     && n.parentNode().toElement().tagName() != "connections" )
	    continue;
	if ( n.attribute( "language", "C++" ) != "C++" )
	    continue;
	QString slotName = n.firstChild().toText().data().stripWhiteSpace();
	if ( slotName.endsWith( ";" ) )
	    slotName = slotName.left( slotName.length() - 1 );

	extraSlots += Parser::cleanArgs(slotName);
	extraSlotTypes += n.attribute( "returnType", "void" );
    }

    // find signals
    QStringList extraSignals;
    nl = e.parentNode().toElement().elementsByTagName( "signal" );
    for ( i = 0; i < (int) nl.length(); i++ ) {
	n = nl.item(i).toElement();
	if ( n.parentNode().toElement().tagName() != "signals"
	     && n.parentNode().toElement().tagName() != "connections" )
	    continue;
	if ( n.attribute( "language", "C++" ) != "C++" )
	    continue;
	QString sigName = n.firstChild().toText().data().stripWhiteSpace();
	if ( sigName.endsWith( ";" ) )
	    sigName = sigName.left( sigName.length() - 1 );
	extraSignals += sigName;
    }

    //find additional functions
    QStringList extraFunctions;
    for ( n = e; !n.isNull(); n = n.nextSibling().toElement() ) {
        if ( n.tagName() == "functions" ) { // compatibility
            for ( QDomElement n2 = n.firstChild().toElement(); !n2.isNull(); n2 = n2.nextSibling().toElement() ) {
                if ( n2.tagName() == "function" ) {
                    QString fname;
                    if(n2.attribute("name") != QString::null )
                    {
                        fname = n2.attribute( "name" );
                        fname = Parser::cleanArgs( fname );
                        functionImpls.insert( fname, n2.firstChild().toText().data() );
                    }
                    else
                    {
                        fname = n2.text();
                        fname = Parser::cleanArgs( fname );
                    }
                    extraFunctions += fname;
                }
            }
        } else if ( n.tagName() == "customwidgets" ) {
	    QDomElement n2 = n.firstChild().toElement();
	    while ( !n2.isNull() ) {
		if ( n2.tagName() == "customwidget" ) {
		    QDomElement n3 = n2.firstChild().toElement();
		    QString cl, header;
		    WidgetDatabaseRecord *r = new WidgetDatabaseRecord;
		    while ( !n3.isNull() ) {
			if ( n3.tagName() == "class" ) {
			    cl = n3.firstChild().toText().data();
			    r->name = cl;
			} else if ( n3.tagName() == "header" ) {
			    CustomInclude ci;
			    ci.header = n3.firstChild().toText().data();
			    ci.location = n3.attribute( "location", "global" );
			    r->includeFile = ci.header;
			    header = ci.header;
			    customWidgetIncludes.insert( cl, ci );
			}
			WidgetDatabase::append( r );
			n3 = n3.nextSibling().toElement();
		    }

		    if (cl.isEmpty())
			cl = "UnnamedCustomClass";

		    int ext = header.findRev('.');

		    if (ext >= 0)
			header.truncate(ext);

		    if (header.isEmpty())
			header = cl.lower();

		    if (!nofwd)
		    	out << "use " << cl << ";" << endl; // FIXME: what about header ?
		}
		n2 = n2.nextSibling().toElement();
	    }
	}
    }

    out << indent << "use Qt::isa qw(" << objClass << ");" << endl;

    // PerlQt sig/slot declaration
    if ( !extraSlots.isEmpty() ) {
	out << indent << "use Qt::slots" << endl;
        ++indent;
        for ( it = extraSlots.begin(); it != extraSlots.end(); ++it )
        {
	    perlSlot( it );
	    out << ( ((*it) == extraSlots.last()) ? ";":",") << endl;
	}
        --indent;
    }

    // create signals
    if ( !extraSignals.isEmpty() ) {
	out << indent << "use Qt::signals" << endl;
        ++indent;
	for ( it = extraSignals.begin(); it != extraSignals.end(); ++it )
        {
	    perlSlot( it );
	    out << ( ((*it) == extraSignals.last()) ? ";":",") << endl;
	}
        --indent;
    }

    // PerlQt attributes
    out << indent << "use Qt::attributes qw("<< endl;
    ++indent;

    // children
    if( !objectNames.isEmpty() )
    	cerr << "WARNING : objectNames should be empty at form.cpp line" << __LINE__ << endl;
    nl = e.parentNode().toElement().elementsByTagName( "widget" );
    for ( i = 1; i < (int) nl.length(); i++ )
    { // start at 1, 0 is the toplevel widget
	n = nl.item(i).toElement();
	createAttrDecl( n );
    }
    objectNames.clear();

    // additional attributes (from Designer)
    QStringList publicVars, protectedVars, privateVars;
    nl = e.parentNode().toElement().elementsByTagName( "variable" );
    for ( i = 0; i < (int)nl.length(); i++ ) {
        n = nl.item( i ).toElement();
        // Because of compatibility the next lines have to be commented out.
        // Someday it should be uncommented.
        //if ( n.parentNode().toElement().tagName() != "variables" )
        //    continue;
        QString access = n.attribute( "access", "protected" );
        QString var = n.firstChild().toText().data().stripWhiteSpace();
        if ( var.endsWith( ";" ) )
            var.truncate(var.length() - 1);
        if ( access == "public" )
            publicVars += var;
        else if ( access == "private" )
            privateVars += var;
        else
            protectedVars += var;
    }

    // for now, all member variables are public.

    if ( !publicVars.isEmpty() ) {
        for ( it = publicVars.begin(); it != publicVars.end(); ++it )
            out << indent << *it << endl;
    }
    if ( !protectedVars.isEmpty() ) {
        for ( it = protectedVars.begin(); it != protectedVars.end(); ++it )
            out << indent << *it << endl;
    }
    if ( !privateVars.isEmpty() ) {
        for ( it = privateVars.begin(); it != privateVars.end(); ++it )
            out << indent << *it << endl;
    }


    // actions, toolbars, menus
    for ( n = e; !n.isNull(); n = n.nextSibling().toElement() )
    {
	if ( n.tagName()  == "actions" )
        {
	    for ( QDomElement a = n.firstChild().toElement(); !a.isNull(); a = a.nextSibling().toElement() )
		createActionDecl( a );
	}
        else if ( n.tagName() == "toolbars" )
        {
	    for ( QDomElement a = n.firstChild().toElement(); !a.isNull(); a = a.nextSibling().toElement() )
            {
                if ( a.tagName() == "toolbar" )
	        out << indent << getObjectName( a ) << endl;
            }

	}
        else if ( n.tagName() == "menubar" )
        {
	    out << indent << getObjectName( n ) << endl;
	    for ( QDomElement a = n.firstChild().toElement(); !a.isNull(); a = a.nextSibling().toElement() )
	    {
		if ( a.tagName() == "item" )
		out << indent << a.attribute( "name" ) << endl;
	    }
	}
    }

    // Databases Connection holders

    registerDatabases( e );
    dbConnections = unique( dbConnections );
    for ( it = dbConnections.begin(); it != dbConnections.end(); ++it ) {
	if ( !(*it).isEmpty() && (*it) != "(default)") {
	    out << indent << (*it) << "Connection" << endl;
	}
    }

    --indent;
    out << indent << ");" << endl;
    out << endl;


    // additional includes (local or global ) and forward declaractions
    nl = e.parentNode().toElement().elementsByTagName( "include" );
    for ( i = 0; i < (int) nl.length(); i++ ) {
	QDomElement n2 = nl.item(i).toElement();
	QString s = n2.firstChild().toText().data();
	if ( n2.attribute( "location" ) != "local" ) {
	    if ( s.right( 5 ) == ".ui.h" && !QFile::exists( s ) )
		continue;
	    if ( n2.attribute( "impldecl", "in implementation" ) != "in implementation" )
		continue;
	    globalIncludes += s;
	}
    }

    // do the local includes afterwards, since global includes have priority on clashes
    for ( i = 0; i < (int) nl.length(); i++ ) {
	QDomElement n2 = nl.item(i).toElement();
	QString s = n2.firstChild().toText().data();
	if ( n2.attribute( "location" ) == "local" &&!globalIncludes.contains( s ) ) {
	    if ( s.right( 5 ) == ".ui.h" && !QFile::exists( s ) )
		continue;
	    if ( n2.attribute( "impldecl", "in implementation" ) != "in implementation" )
		continue;
	    localIncludes += s;
	}
    }

    // additional custom widget headers
    nl = e.parentNode().toElement().elementsByTagName( "header" );
    for ( i = 0; i < (int) nl.length(); i++ ) {
	QDomElement n2 = nl.item(i).toElement();
	QString s = n2.firstChild().toText().data();
	if ( n2.attribute( "location" ) != "local" )
	    globalIncludes += s;
	else
	    localIncludes += s;
    }


    // grab slots/funcs defined in ui.h files
    for(QStringList::Iterator it = localIncludes.begin(); it != localIncludes.end(); ++it)
    {
        if((*it).right( 5 ) == ".ui.h")
        {
            QFile f((*it));
            if( f.open( IO_ReadOnly ) )
            {
                QRegExp re("^.*([a-zA-Z0-9_]+\\s*\\(.*\\))\\s*$");
                QRegExp re2("^\\}.*");
                QTextStream t( &f );
                QString s, s2, s3;
                while ( !t.eof() )
                {
                    s = t.readLine();
                    int pos = re.search(s);
                    if(pos == -1)
                        continue;
                    s2 = re.cap(1);
                    s2 = Parser::cleanArgs(s2);
                    s3 = QString::null;
                    while( !t.eof() )
                    {
                        s = t.readLine();
                        s3 += s + "\n";
                        if(re2.search(s) != -1)
                            break;
                    }
                    functionImpls.insert( s2, s3 );
                    if( t.eof() ) break;
                }
                f.close();
             }
        }
    }

    // includes for child widgets
    for ( it = tags.begin(); it != tags.end(); ++it ) {
	nl = e.parentNode().toElement().elementsByTagName( *it );
	for ( i = 1; i < (int) nl.length(); i++ ) { // start at 1, 0 is the toplevel widget
	    QString name = getClassName( nl.item(i).toElement() );
	    if ( name == "Spacer" ) {
		globalIncludes += "qlayout.h";
		globalIncludes += "qapplication.h";
		continue;
	    }
	    if ( name.mid( 4 ) == "ListView" )
		globalIncludes += "qheader.h";
	    if ( name != objClass ) {
		int wid = WidgetDatabase::idFromClassName( name.replace( QRegExp("^Qt::"), "Q" ) );
		QMap<QString, CustomInclude>::Iterator it = customWidgetIncludes.find( name );
		if ( it == customWidgetIncludes.end() )
		    globalIncludes += WidgetDatabase::includeFile( wid );
	    }
	}
    }

    dbConnections = unique( dbConnections );
    if ( dbConnections.count() )
	sqlClasses += "Qt::SqlDatabase";
    if ( dbCursors.count() )
	sqlClasses += "Qt::SqlCursor";
    bool dbForm = FALSE;
    if ( dbForms[ "(default)" ].count() )
	dbForm = TRUE;
    bool subDbForms = FALSE;
    for ( it = dbConnections.begin(); it != dbConnections.end(); ++it ) {
	if ( !(*it).isEmpty()  && (*it) != "(default)" ) {
	    if ( dbForms[ (*it) ].count() ) {
		subDbForms = TRUE;
		break;
	    }
	}
    }
    if ( dbForm || subDbForms ) {
	sqlClasses += "Qt::SqlForm";
	sqlClasses += "Qt::SqlRecord";
    }

    if (globalIncludes.findIndex("qdatatable.h") >= 0)
        sqlClasses += "Qt::DataTable";

    if (globalIncludes.findIndex("qtableview.h") >= 0)
        sqlClasses += "Qt::TableView";

    if (globalIncludes.findIndex("qdatabrowser.h") >= 0)
        sqlClasses += "Qt::DataBrowser";

    out << endl;

    // find out what images are required
    QStringList requiredImages;
    static const char *imgTags[] = { "pixmap", "iconset", 0 };
    for ( i = 0; imgTags[i] != 0; i++ ) {
       nl = e.parentNode().toElement().elementsByTagName( imgTags[i] );
       for ( int j = 0; j < (int) nl.length(); j++ )
           requiredImages += nl.item(j).firstChild().toText().data();
    }

    // register the object and unify its name
    objName = registerObject( objName );

    QStringList images;
    QStringList xpmImages;
    if ( pixmapLoaderFunction.isEmpty() && !externPixmaps )
    {
	// create images
	for ( n = e; !n.isNull(); n = n.nextSibling().toElement() )
        {
	    if ( n.tagName()  == "images" )
            {
		nl = n.elementsByTagName( "image" );
		for ( i = 0; i < (int) nl.length(); i++ )
                {
		    QString img = registerObject(  nl.item(i).toElement().attribute( "name" ) );
		    if ( !requiredImages.contains( img ) )
			continue;
		    QDomElement tmp = nl.item(i).firstChild().toElement();
		    if ( tmp.tagName() != "data" )
			continue;
		    QString format = tmp.attribute("format", "PNG" );
		    QString data = tmp.firstChild().toText().data();
		    if ( format == "XPM.GZ" )
                    {
			xpmImages += img;
			ulong length = tmp.attribute("length").toULong();
			QByteArray baunzip = unzipXPM( data, length );
			// shouldn't we test the initial `length' against the
			// resulting `length' to catch corrupt UIC files?
			int a = 0;
                        out << indent << "our $" << img << "_data =\n[";

			while ( baunzip[a] != '\"' )
			    a++;
			for ( ; a < (int) length; a++ )
			{
			    char ch;

			    if ((ch = baunzip[a]) == '}')
			    {
				out << "];\n" << endl;

				break;
			    }

			    out << ch;
			}
		    }
                    else
                    {
			images += img;
                        out << indent << "our $" << img << "_data = pack 'C*'," << endl;
			++indent;
 			int a ;
			for ( a = 0; a < (int) (data.length()/2)-1; a++ ) {
			    out << "0x" << QString(data[2*a]) << QString(data[2*a+1]) << ",";
			    if ( a % 12 == 11 )
				out << endl << "    ";
			    else
				out << " ";
			}
			out << "0x" << QString(data[2*a]) << QString(data[2*a+1]) << ";" << endl;
			--indent;
                        out << endl;
		    }
		}
	    }
	}
	out << endl;
    }
    else if ( externPixmaps )
    {
	out << indent << "sub uic_load_pixmap_" << objName<< endl;
	out << indent << "{" << endl;
	++indent;
	out << indent << "my $pix = Qt::Pixmap();" << endl;
	out << indent << "my $m = Qt::MimeSourceFactory::defaultFactory()->data(shift);" << endl;
	out << endl;
	out << indent << "if($m)" << endl;
	out << indent << "{" << endl;
	++indent;
	out << indent << "Qt::ImageDrag::decode($m, $pix);" << endl;
	--indent;
	out << indent << "}" << endl;
	out << endl;
	out << indent << "return $pix;" << endl;
	--indent;
	out << indent << "}" << endl;
	out << endl;
	out << endl;
	pixmapLoaderFunction = "uic_load_pixmap_" + objName;
    }


    // constructor(s)
    out << indent << "sub NEW" << endl;
    out << indent << "{" << endl;
    ++indent;
    if ( objClass == "Qt::Dialog" || objClass == "Qt::Wizard" ) {
	out << indent << "shift->SUPER::NEW(@_[0..3]);" << endl;
    } else if ( objClass == "Qt::Widget")  {
	out << indent << "shift->SUPER::NEW(@_[0..2]);" << endl;
    } else if ( objClass == "Qt::MainWindow" ) {
	out << indent << "shift->SUPER::NEW(@_[0..2]);" << endl;
	out << indent << "statusBar();" << endl;
	isMainWindow = TRUE;
    } else {
	out << indent << "shift->SUPER::NEW(@_[0,1]);" << endl;
    }

    out << endl;

    // create pixmaps for all images
    if ( !images.isEmpty() ) {
	QStringList::Iterator it;
	for ( it = images.begin(); it != images.end(); ++it ) {
	    out << indent << "my $" << (*it) << " = Qt::Pixmap();" << endl;
	    out << indent << "$" << (*it) << "->loadFromData($" << (*it) << "_data, length ($" << (*it) << "_data), \"PNG\");" << endl;
	}
        out << endl;
    }
    // create pixmaps for all images
    if ( !xpmImages.isEmpty() ) {
	for ( it = xpmImages.begin(); it != xpmImages.end(); ++it ) {
	    out << indent << "my $" << (*it) << " = Qt::Pixmap($" << (*it) << "_data);" << endl;
	}
	out << endl;
    }


    // set the properties
    for ( n = e.firstChild().toElement(); !n.isNull(); n = n.nextSibling().toElement() ) {
	if ( n.tagName() == "property" ) {
	    bool stdset = stdsetdef;
	    if ( n.hasAttribute( "stdset" ) )
		stdset = toBool( n.attribute( "stdset" ) );
	    QString prop = n.attribute("name");
	    QDomElement n2 = n.firstChild().toElement();
	    QString value = setObjectProperty( objClass, QString::null, prop, n2, stdset );
	    if ( value.isEmpty() )
		continue;
	    if ( prop == "name" ) {
		out << indent << "if( name() eq \"unnamed\" )" << endl;
                out << indent << "{" << endl;
		++indent;
	    }

	    out << indent;

	    if ( prop == "geometry" && n2.tagName() == "rect") {
		QDomElement n3 = n2.firstChild().toElement();
		int w = 0, h = 0;
		while ( !n3.isNull() ) {
		    if ( n3.tagName() == "width" )
			w = n3.firstChild().toText().data().toInt();
		    else if ( n3.tagName() == "height" )
			h = n3.firstChild().toText().data().toInt();
		    n3 = n3.nextSibling().toElement();
		}
		out << "resize(" << w << "," << h << ");" << endl;
	    } else {
		if ( stdset )
		    out << mkStdSet( prop ) << "(" << value << ");" << endl;
		else
		    out << "setProperty(\"" << prop << "\", Qt::Variant(" << value << "));" << endl;
	    }

	    if ( prop == "name" )
	    {
		--indent;
		out << indent << "}" << endl;
	    }
	}
    }

    out << endl;

    // create all children, some forms have special requirements

    if ( objClass == "Qt::Wizard" )
    {
	for ( n = e.firstChild().toElement(); !n.isNull(); n = n.nextSibling().toElement() )
        {
	    if ( tags.contains( n.tagName()  ) )
            {
		QString page = createObjectImpl( n, objClass, "this" );
		QString label = DomTool::readAttribute( n, "title", "" ).toString();
		out << indent << "addPage(" << page << ", "<< trcall( label ) << ");" << endl;
		QVariant def( FALSE, 0 );
		if ( DomTool::hasAttribute( n, "backEnabled" ) )
		    out << indent << "setBackEnabled(" << page << "," << mkBool( DomTool::readAttribute( n, "backEnabled", def).toBool() ) << ");" << endl;
		if ( DomTool::hasAttribute( n, "nextEnabled" ) )
		    out << indent << "setNextEnabled(" << page << "," << mkBool( DomTool::readAttribute( n, "nextEnabled", def).toBool() ) << ");" << endl;
		if ( DomTool::hasAttribute( n, "finishEnabled" ) )
		    out << indent << "setFinishEnabled(" << page << "," << mkBool( DomTool::readAttribute( n, "finishEnabled", def).toBool() ) << ");" << endl;
		if ( DomTool::hasAttribute( n, "helpEnabled" ) )
		    out << indent << "setHelpEnabled(" << page << "," << mkBool( DomTool::readAttribute( n, "helpEnabled", def).toBool() ) << ");" << endl;
		if ( DomTool::hasAttribute( n, "finish" ) )
		    out << indent << "setFinish( " << page << "," << mkBool( DomTool::readAttribute( n, "finish", def).toBool() ) << ");" << endl;
	    }
	}
    }
    else
    { // standard widgets
	for ( n = e.firstChild().toElement(); !n.isNull(); n = n.nextSibling().toElement() )
        {
	    if ( tags.contains( n.tagName()  ) )
		createObjectImpl( n, objName, "this" );
	}
    }

    // database support
    dbConnections = unique( dbConnections );
    if ( dbConnections.count() )
	out << endl;
    for ( it = dbConnections.begin(); it != dbConnections.end(); ++it ) {
	if ( !(*it).isEmpty() && (*it) != "(default)") {
	    out << indent << (*it) << "Connection = Qt::SqlDatabase::database(\"" <<(*it) << "\");" << endl;
	}
    }

    nl = e.parentNode().toElement().elementsByTagName( "widget" );
    for ( i = 1; i < (int) nl.length(); i++ ) { // start at 1, 0 is the toplevel widget
	n = nl.item(i).toElement();
	QString s = getClassName( n );
	if ( s == "Qt::DataBrowser" || s == "Qt::DataView" ) {
	    QString objName = getObjectName( n );
	    QString tab = getDatabaseInfo( n, "table" );
	    QString con = getDatabaseInfo( n, "connection" );
	    out << indent << "my $" << objName << "Form = Qt::SqlForm(this, \"" << objName << "Form\");" << endl;
	    QDomElement n2;
	    for ( n2 = n.firstChild().toElement(); !n2.isNull(); n2 = n2.nextSibling().toElement() )
		createFormImpl( n2, objName, con, tab );
	    out << indent << objName << "->setForm($" << objName << "Form);" << endl;
	}
    }

    // actions, toolbars, menubar
    bool needEndl = FALSE;
    for ( n = e; !n.isNull(); n = n.nextSibling().toElement() ) {
	if ( n.tagName()  == "actions" ) {
	    if ( !needEndl )
		out << endl;
	    createActionImpl( n.firstChild().toElement(), "this" );
	    needEndl = TRUE;
	}
    }
    if ( needEndl )
	out << endl;
    needEndl = FALSE;
    for ( n = e; !n.isNull(); n = n.nextSibling().toElement() ) {
	if ( n.tagName() == "toolbars" ) {
	    if ( !needEndl )
		out << endl;
	    createToolbarImpl( n, objClass, objName );
	    needEndl = TRUE;
	}
    }
    if ( needEndl )
	out << endl;
    needEndl = FALSE;
    for ( n = e; !n.isNull(); n = n.nextSibling().toElement() ) {
	if ( n.tagName() == "menubar" ) {
	    if ( !needEndl )
		out << endl;
	    createMenuBarImpl( n, objClass, objName );
	    needEndl = TRUE;
	}
    }
    if ( needEndl )
	out << endl;

    for ( n = e; !n.isNull(); n = n.nextSibling().toElement() ) {
	if ( n.tagName()  == "connections" ) {
	    // setup signals and slots connections
	    out << endl;
	    nl = n.elementsByTagName( "connection" );
	    for ( i = 0; i < (int) nl.length(); i++ ) {
		QString sender, receiver, signal, slot;
		for ( QDomElement n2 = nl.item(i).firstChild().toElement(); !n2.isNull(); n2 = n2.nextSibling().toElement() ) {
		    if ( n2.tagName() == "sender" )
			sender = n2.firstChild().toText().data();
		    else if ( n2.tagName() == "receiver" )
			receiver = n2.firstChild().toText().data();
		    else if ( n2.tagName() == "signal" )
			signal = n2.firstChild().toText().data();
		    else if ( n2.tagName() == "slot" )
			slot = n2.firstChild().toText().data();
		}
		if ( sender.isEmpty() || receiver.isEmpty() || signal.isEmpty() || slot.isEmpty() )
		    continue;
                else if ( sender[0] == '<' ||
                    receiver[0] == '<' ||
                    signal[0] == '<' ||
                    slot[0] == '<' )
                    continue;
		sender = registeredName( sender );
		receiver = registeredName( receiver );

		if ( sender == objName )
		    sender = "this";
		if ( receiver == objName )
		    receiver = "this";

		out << indent << "Qt::Object::connect(" << sender
		    << ", SIGNAL \"" << signal << "\", "<< receiver << ", SLOT \"" << slot << "\");" << endl;
	    }
	} else if ( n.tagName()  == "tabstops" ) {
	    // setup tab order
	    out << endl;
	    QString lastName;
	    QDomElement n2 = n.firstChild().toElement();
	    while ( !n2.isNull() ) {
		if ( n2.tagName() == "tabstop" ) {
		    QString name = n2.firstChild().toText().data();
		    name = registeredName( name );
		    if ( !lastName.isEmpty() )
			out << indent << "setTabOrder(" << lastName << ", " << name << ");" << endl;
		    lastName = name;
		}
		n2 = n2.nextSibling().toElement();
	    }
	}
    }

// PerlQt - FIXME: what the heck is this ?
    // buddies
    bool firstBuddy = TRUE;
    for ( QValueList<Buddy>::Iterator buddy = buddies.begin(); buddy != buddies.end(); ++buddy ) {
	if ( isObjectRegistered( (*buddy).buddy ) ) {
	    if ( firstBuddy ) {
		out << endl;
	    }
	    out << indent << (*buddy).key << "->setBuddy(this->" << registeredName( (*buddy).buddy ) << ");" << endl;
	    firstBuddy = FALSE;
	}

    }
    if ( extraSlots.find( "init()" ) != extraSlots.end() ||
         extraFunctions.find( "init()" ) != extraFunctions.end())
        out << endl << indent << "init();" << endl;

    // end of constructor
    --indent;
    out << indent << "}" << endl;
    out << endl;


    // FIXME PerlQt: is it safe to implement a destructor ?
    if ( extraSlots.find( "destroy()" ) != extraSlots.end() ||
         extraFunctions.find( "destroy()" ) != extraFunctions.end()) {
        out << endl;
        out << indent << "sub DESTROY" << endl;
        out << indent << "{" << endl;
        ++indent;
        out << indent << "destroy();" << endl;
        --indent;
        out << indent << "}" << endl;
    }


    // handle application events if required
    bool needFontEventHandler = FALSE;
    bool needSqlTableEventHandler = FALSE;
    bool needSqlDataBrowserEventHandler = FALSE;
    nl = e.elementsByTagName( "widget" );
    for ( i = 0; i < (int) nl.length(); i++ ) {
	if ( !DomTool::propertiesOfType( nl.item(i).toElement() , "font" ).isEmpty() )
	    needFontEventHandler = TRUE;
	QString s = getClassName( nl.item(i).toElement() );
	if ( s == "Qt::DataTable" || s == "Qt::DataBrowser" ) {
	    if ( !isFrameworkCodeGenerated( nl.item(i).toElement() ) )
		 continue;
	    if ( s == "Qt::DataTable" )
		needSqlTableEventHandler = TRUE;
	    if ( s == "Qt::DataBrowser" )
		needSqlDataBrowserEventHandler = TRUE;
	}
	if ( needFontEventHandler && needSqlTableEventHandler && needSqlDataBrowserEventHandler )
	    break;
    }

// PerlQt - TODO: is this needed ?
// Seems not.. let's ifzero for now...

    if ( 0 && needFontEventHandler) {
	//	indent = "\t"; // increase indentation for if-clause below
	out << endl;
	out << "#  Main event handler. Reimplemented to handle" << endl;
	out << "#  application font changes" << endl;
	out << endl;
	out << "sub event" << endl;
	out << "{" << endl;
        out << "    my $ev = shift;" << endl;
	out << "    my $ret = this->SUPER::event( $ev ); " << endl;
	if ( needFontEventHandler ) {
	    ++indent;
	    out << "    if ( $ev->type() == &Qt::Event::ApplicationFontChange ) {" << endl;
	    for ( i = 0; i < (int) nl.length(); i++ ) {
		n = nl.item(i).toElement();
		QStringList list = DomTool::propertiesOfType( n, "font" );
		for ( it = list.begin(); it != list.end(); ++it )
		    createExclusiveProperty( n, *it );
	    }
	    out << "    }" << endl;
	    --indent;
	}
	out << "}" << endl;
	out << endl;
    }

    if ( needSqlTableEventHandler || needSqlDataBrowserEventHandler ) {
	out << endl;
	out << indent << "# Widget polish.  Reimplemented to handle default data" << endl;
	if ( needSqlTableEventHandler )
	    out << indent << "# table initialization." << endl;
	if ( needSqlDataBrowserEventHandler )
	    out << indent << "# browser initialization." << endl;
	out << indent << "sub polish" << endl;
	out << indent << "{" << endl;
	++indent;
	if ( needSqlTableEventHandler ) {
	    for ( i = 0; i < (int) nl.length(); i++ ) {
		QString s = getClassName( nl.item(i).toElement() );
		if ( s == "Qt::DataTable" ) {
		    n = nl.item(i).toElement();
		    QString c = getObjectName( n );
		    QString conn = getDatabaseInfo( n, "connection" );
		    QString tab = getDatabaseInfo( n, "table" );
		    if ( !( conn.isEmpty() || tab.isEmpty() ) ) {
			out << indent << "if(" << c << ")" << endl;
			out << indent << "{" << endl;
			++indent;
			out << indent << "my $cursor = " << c << "->sqlCursor();" << endl;
			out << endl;
			out << indent << "if(!$cursor)" << endl;
			out << indent << "{" << endl;
			++indent;
			if ( conn == "(default)" )
			    out << indent << "$cursor = Qt::SqlCursor(\"" << tab << "\");" << endl;
			else
			    out << indent << "$cursor = Qt::SqlCursor(\"" << tab << "\", 1, " << conn << "Connection);" << endl;
			out << indent << c << "->setSqlCursor($cursor, 0, 1);" << endl;
			--indent;
			out << endl;
			out << indent << "}" << endl;
			out << indent << "if(!$cursor->isActive())" << endl;
			out << indent << "{" << endl;
			++indent;
			out << indent << c << "->refresh(&Qt::DataTable::RefreshAll);" << endl;
			--indent;
			out << indent << "}" << endl;
			--indent;
			out << indent << "}" << endl;
		    }
		}
	    }
	}
	if ( needSqlDataBrowserEventHandler ) {
	    nl = e.elementsByTagName( "widget" );
	    for ( i = 0; i < (int) nl.length(); i++ ) {
		QString s = getClassName( nl.item(i).toElement() );
		if ( s == "Qt::DataBrowser" ) {
		    QString obj = getObjectName( nl.item(i).toElement() );
		    QString tab = getDatabaseInfo( nl.item(i).toElement(),
						   "table" );
		    QString conn = getDatabaseInfo( nl.item(i).toElement(),
						    "connection" );
		    if ( !(tab).isEmpty() ) {
			out << indent << "if(" << obj << ")" << endl;
			out << indent << "{" << endl;
			++indent;
			out << indent << "if(!" << obj << "->sqlCursor())" << endl;
			out << indent << "{" << endl;
			++indent;
			if ( conn == "(default)" )
			    out << indent << "my $cursor = Qt::SqlCursor(\"" << tab << "\");" << endl;
			else
			    out << indent << "my $cursor = Qt::SqlCursor(\"" << tab << "\", 1, " << conn << "Connection);" << endl;
			out << indent << obj << "->setSqlCursor($cursor, 1);" << endl;
			out << indent << obj << "->refresh();" << endl;
			out << indent << obj << "->first();" << endl;
			--indent;
			out << indent << "}" << endl;
			--indent;
			out << indent << "}" << endl;
		    }
		}
	    }
	}
	out << indent << "SUPER->polish();" << endl;
	--indent;
	out << indent << "}" << endl;
    }
    if ( !extraSlots.isEmpty() && writeSlotImpl ) {
	for ( it = extraSlots.begin(); it != extraSlots.end(); ++it ) {
	    out << endl;
	    int astart = (*it).find('(');
	    out << indent << "sub " << (*it).left(astart)<< endl;
	    out << indent << "{" << endl;
	    bool createWarning = TRUE;
	    QString fname = Parser::cleanArgs( *it );
	    QMap<QString, QString>::Iterator fit = functionImpls.find( fname );
	    if ( fit != functionImpls.end() ) {
		int begin = (*fit).find( "{" );
		QString body = (*fit).mid( begin + 1, (*fit).findRev( "}" ) - begin - 1 );
		createWarning = body.simplifyWhiteSpace().isEmpty();
		if ( !createWarning )
		    out << body << endl;
	    }
	    if ( createWarning ) {
		++indent;
		if ( *it != "init()" && *it != "destroy()" )
		    out << indent << "print \"" << nameOfClass << "->" << (*it) << ": Not implemented yet.\\n\";" << endl;
		--indent;
	    }
	    out << indent << "}" << endl;

	}
    }

    if ( !extraFunctions.isEmpty() ) {
	for ( it = extraFunctions.begin(); it != extraFunctions.end(); ++it ) {
	    out << endl;
	    int astart = (*it).find('(');
	    out << indent << "sub " << (*it).left(astart)<< endl;
	    out << indent << "{" << endl;
	    QString fname = Parser::cleanArgs( *it );
	    QMap<QString, QString>::Iterator fit = functionImpls.find( fname );
	    if ( fit != functionImpls.end() ) {
		int begin = (*fit).find( "{" );
		QString body = (*fit).mid( begin + 1, (*fit).findRev( "}" ) - begin - 1 );
		body.simplifyWhiteSpace().isEmpty();
		out << body << endl;
	    }
	    out << indent << "}" << endl;

	}
    }


    out << endl;
    out << "1;" << endl; // Perl modules must return true
}


/*! Creates form support implementation code for the widgets given
  in \a e.

  Traverses recursively over all children.
 */

void Uic::createFormImpl( const QDomElement& e, const QString& form, const QString& connection, const QString& table )
{
    if ( e.tagName() == "widget" &&
	 e.attribute( "class" ) != "Qt::DataTable" ) {
	QString field = getDatabaseInfo( e, "field" );
	if ( !field.isEmpty() ) {
	    if ( isWidgetInTable( e, connection, table ) )
		out << indent << "$" << form << "Form->insert(" << getObjectName( e ) << ", " << fixString( field ) << ");" << endl;
	}
    }
    QDomElement n;
    for ( n = e.firstChild().toElement(); !n.isNull(); n = n.nextSibling().toElement() ) {
	createFormImpl( n, form, connection, table );
    }
}


// Generate a PerlQt signal/slot definition.

void Uic::perlSlot(QStringList::Iterator &it)
{
    int astart = (*it).find('(');
    out << indent << (*it).left(astart) << " => ";
    QString args = (*it).mid(astart + 1,(*it).find(')') - astart - 1).stripWhiteSpace();
    out << "[";
    if (!args.isEmpty())
    {
	QStringList arglist = QStringList::split( QRegExp(","), args );
	out << "'" << arglist.join( "', '") << "'";
    }
    out << "]";
}
