use ExtUtils::MakeMaker;
require 'Qt.config';

WriteMakefile(
    'NAME'	=> 'libperlqt',
    'VERSION'	=> '1.05',
    'CONFIGURE' => sub { return \%QtConfig },
    'OBJECT'	=> q{
	libperlqt$(OBJ_EXT)
	pvirtual$(OBJ_EXT)
	psigslot$(OBJ_EXT)
	QAccel$(OBJ_EXT)
	QApplication$(OBJ_EXT)
	QButton$(OBJ_EXT)
	QButtonGroup$(OBJ_EXT)
	QCheckBox$(OBJ_EXT)
	QComboBox$(OBJ_EXT)
	QDialog$(OBJ_EXT)
	QFileDialog$(OBJ_EXT)
	QFrame$(OBJ_EXT)
	QGroupBox$(OBJ_EXT)
	QLCDNumber$(OBJ_EXT)
	QLabel$(OBJ_EXT)
	QLineEdit$(OBJ_EXT)
	QListBox$(OBJ_EXT)
	QMenuBar$(OBJ_EXT)
	QMenuData$(OBJ_EXT)
	QMessageBox$(OBJ_EXT)
	QMultiLineEdit$(OBJ_EXT)
	QObject$(OBJ_EXT)
	QPopupMenu$(OBJ_EXT)
	QProgressBar$(OBJ_EXT)
	QProgressDialog$(OBJ_EXT)
	QPushButton$(OBJ_EXT)
	QRadioButton$(OBJ_EXT)
	QRangeControl$(OBJ_EXT)
	QScrollBar$(OBJ_EXT)
	QSemiModal$(OBJ_EXT)
	QSlider$(OBJ_EXT)
	QTabBar$(OBJ_EXT)
	QTabDialog$(OBJ_EXT)
	QTableView$(OBJ_EXT)
	QTimer$(OBJ_EXT)
	QWidget$(OBJ_EXT)
	QWindow$(OBJ_EXT)},
    'realclean' => { 'FILES' => '*.config' },
);

sub MY::install {
    return <<INSTALL;
install: all
	cp \$(INST_DYNAMIC) $InstallDir
INSTALL
}
