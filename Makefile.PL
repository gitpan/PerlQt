use ExtUtils::MakeMaker;
require ExtUtils::Liblist;

sub find_libperlqt {
    open(QSAVEOUT, ">&STDOUT") || die "failed to save STDOUT: $!";
    open(STDOUT, ">qcheck") || die "could not redirect output to qcheck: $!";

    shift->ExtUtils::Liblist::ext('-lperlqt');

    open(STDOUT, ">&QSAVEOUT") || die "failed to restore STDOUT: $!";
    close QSAVEOUT;
    if(-s "qcheck") {
	open(QCHECK, "qcheck") || die "qcheck: $!\n";
	print(<QCHECK>);
	close QCHECK;
	unlink "qcheck";
	die "You must install libperlqt where Perl can find it " .
	    "before compiling PerlQt.\n";
    }
    unlink "qcheck";
}

WriteMakefile(
    'NAME'	=> 'Qt',
    'DISTNAME'	=> 'PerlQt',
    'VERSION_FROM' => 'Qt.pm',
    'CONFIGURE'	=> \&find_libperlqt,
    'DIR'	=> [ qw(QAccel
			QApplication
			QBitmap
			QBrush
			QButton
			QButtonGroup
			QCheckBox
			QClipboard
			QColor
			QComboBox
			QCursor
			QDialog
			QEvent
			QFileDialog
			QFont
			QFontInfo
			QFontMetrics
			QFrame
			QGlobal
			QGroupBox
			QImage
			QLCDNumber
			QLabel
			QLayout
			QLineEdit
			QListBox
			QMenuBar
			QMenuData
			QMessageBox
			QMultiLineEdit
			QObject
			QPaintDevice
			QPainter
			QPalette
			QPen
			QPicture
			QPixmap
			QPoint
			QPointArray
			QPopupMenu
			QPrinter
			QProgressBar
			QProgressDialog
			QPushButton
			QRadioButton
			QRangeControl
			QRect
			QRegion
			QScrollBar
			QSemiModal
			QSize
			QSlider
			QSocketNotifier
			QTabBar
			QTabDialog
			QTableView
			QTimer
			QToolTip
			QWMatrix
			QWidget
			QWindow) ],
    'realclean' => { 'FILES' => '*.config' },
    'dist'  => { 'COMPRESS' => 'gzip -9', 'SUFFIX' => 'gz' },
);
