#ifndef VIRTUAL_H
#define VIRTUAL_H

/*
 * Declaration of the virtualize class
 *
 * Copyright (C) 1997, Ashley Winters <jql@accessone.com>
 *
 * You may distribute under the terms of the LGPL as specified in the
 * README file
 */

#undef bool
#include "qevent.h"
#include "pqt.h"

class QPopupMenu;
struct QTab;

#define QMenuData_virtual_functions					\
public:									\
    void updateItem(int);						\
protected:								\
    void menuContentsChanged();						\
    void menuDelPopup(QPopupMenu *);					\
    void menuInsPopup(QPopupMenu *);					\
    void menuStateChanged();

#define QRangeControl_virtual_functions					\
protected:								\
    void rangeChange();							\
    void stepChange();							\
    void valueChange();

#define QObject_virtual_functions					\
public:									\
    const char *className() const;					\
    bool event(QEvent *);						\
    bool eventFilter(QObject *, QEvent *);				\
    QMetaObject *metaObject() const;					\
protected:								\
    void initMetaObject();						\
    void timerEvent(QTimerEvent *);

#define QWidget_virtual_functions					\
    QObject_virtual_functions						\
public:									\
    void adjustSize();							\
    bool close(bool = FALSE);						\
    void hide();							\
    void move(int, int);						\
    void resize(int, int);						\
    void setBackgroundColor(const QColor &);				\
    void setBackgroundPixmap(const QPixmap &);				\
    void setCursor(const QCursor &);					\
    void setEnabled(bool);						\
    void setFont(const QFont &);					\
    void setGeometry(int, int, int, int);				\
    void setPalette(const QPalette &);					\
    void setStyle(GUIStyle);						\
    void show();							\
    QSize sizeHint() const;						\
protected:								\
    void closeEvent(QCloseEvent *);					\
    void enterEvent(QEvent *);						\
    void focusInEvent(QFocusEvent *);					\
    void focusOutEvent(QFocusEvent *);					\
    void keyPressEvent(QKeyEvent *);					\
    void keyReleaseEvent(QKeyEvent *);					\
    void leaveEvent(QEvent *);						\
    void mouseDoubleClickEvent(QMouseEvent *);				\
    void mouseMoveEvent(QMouseEvent *);					\
    void mousePressEvent(QMouseEvent *);				\
    void mouseReleaseEvent(QMouseEvent *);				\
    void moveEvent(QMoveEvent *);					\
    void paintEvent(QPaintEvent *);					\
    void resizeEvent(QResizeEvent *);

#define QButton_virtual_functions					\
    QWidget_virtual_functions						\
protected:								\
    void drawButton(QPainter *);					\
    void drawButtonLabel(QPainter *);					\
    bool hitButton(const QPoint &) const;

#define QCheckBox_virtual_functions QButton_virtual_functions

#define QPushButton_virtual_functions QButton_virtual_functions

#define QRadioButton_virtual_functions QButton_virtual_functions

#define QComboBox_virtual_functions QWidget_virtual_functions

#define QDialog_virtual_functions					\
    QWidget_virtual_functions						\
protected:								\
    void done(int);

#define QFileDialog_virtual_functions QDialog_virtual_functions

#define QMessageBox_virtual_functions QDialog_virtual_functions

#define QTabDialog_virtual_functions QDialog_virtual_functions

#define QFrame_virtual_functions					\
    QWidget_virtual_functions						\
protected:								\
    void drawFrame(QPainter *);						\
    void drawContents(QPainter *);					\
    void frameChanged();

#define QGroupBox_virtual_functions QFrame_virtual_functions

#define QButtonGroup_virtual_functions QGroupBox_virtual_functions

#define QLCDNumber_virtual_functions QFrame_virtual_functions

#define QLabel_virtual_functions QFrame_virtual_functions

#define QMenuBar_virtual_functions					\
    QWidget_virtual_functions						\
protected:								\
    void drawFrame(QPainter *);						\
    void drawContents(QPainter *);					\
public:									\
    void updateItem(int);						\
protected:								\
    void menuContentsChanged();						\
    void menuStateChanged();


#define QTableView_virtual_functions					\
    QFrame_virtual_functions						\
protected:								\
    int cellHeight(int);						\
    int cellWidth(int);							\
    void paintCell(QPainter *, int, int);				\
    void setupPainter(QPainter *);					\
    int totalHeight();							\
    int totalWidth();

#define QListBox_virtual_functions QTableView_virtual_functions

#define QMultiLineEdit_virtual_functions				\
    QTableView_virtual_functions					\
public:									\
    void insertAt(const char *, int, int);				\
    void insertLine(const char *, int = -1);				\
    void removeLine(int);						\
protected:								\
    void backspace();							\
    void cursorDown(bool = FALSE);					\
    void cursorLeft(bool = FALSE, bool = TRUE);				\
    void cursorRight(bool = FALSE, bool = TRUE);			\
    void cursorUp(bool = FALSE);					\
    void del();								\
    void end(bool = FALSE);						\
    void home(bool = FALSE);						\
    void insertChar(char);						\
    void killLine();							\
    void newLine();							\
    void pageUp(bool = FALSE);						\
    void pageDown(bool = FALSE);

#define QPopupMenu_virtual_functions					\
    QWidget_virtual_functions						\
public:									\
    void updateItem(int);						\
protected:								\
    void drawFrame(QPainter *);						\
    void drawContents(QPainter *);					\
									\
    int cellHeight(int);						\
    int cellWidth(int);							\
    void paintCell(QPainter *, int, int);				\
    void setupPainter(QPainter *);					\
    int totalHeight();							\
    int totalWidth();							\

#define QLineEdit_virtual_functions QWidget_virtual_functions

#define QScrollBar_virtual_functions					\
    QWidget_virtual_functions						\
    QRangeControl_virtual_functions

#define QSlider_virtual_functions					\
    QWidget_virtual_functions						\
    QRangeControl_virtual_functions					\
public:									\
    void setTickInterval(int);						\
    void setTickmarks(QSlider::TickSetting);				\
protected:								\
    void paintSlider(QPainter *, const QRect &);			\
    int thickness() const;

#define QTabBar_virtual_functions					\
    QWidget_virtual_functions						\
public:									\
    int addTab(QTab *);							\
protected:								\
    void paint(QPainter *, QTab *, bool) const;				\
    QTab *selectTab(const QPoint &) const;

#define QWindow_virtual_functions QWidget_virtual_functions

class virtualize {
    SV *qtObject;
    char *qtClassName;
public:
    virtualize() { qtObject = NULL; }
    virtual ~virtualize();
    void setQtObject(SV *obj) { qtObject = obj; SvREFCNT_inc(obj); }
    SV *getQtObject() const { return qtObject; }
    char *setQtClassName(char *cname);
    char *getQtClassName() const { return qtClassName; }
    void callQtMethod(CV *method, SV *arg1 = Nullsv, SV *arg2 = Nullsv,
		      SV *arg3 = Nullsv, SV *arg4 = Nullsv) const;
    void voidCall(char *methodName, SV *arg1 = Nullsv, SV *arg2 = Nullsv,
		  SV *arg3 = Nullsv, SV *arg4 = Nullsv) const;
    SV *retCall(char *methodName, SV *arg1 = Nullsv, SV *arg2 = Nullsv,
		SV *arg3 = Nullsv, SV *arg4 = Nullsv) const;
    void voidCallObj(char *methodName, const void *arg, char *type) const;
    void voidCallObj(char *methodName, const void *arg1, char *type1,
		     const void *arg2, char *type2) const;
    SV *retCallObj(char *methodName, const void *arg, char *type) const;
    SV *retCallObj(char *methodName, const void *arg1, char *type1,
		   const void *arg2, char *type2) const;
};

class PMenuData_virtualize : virtual public virtualize {
public:
    void PMenuData_updateItem(int);
protected:
    void PMenuData_menuContentsChanged();
    void PMenuData_menuDelPopup(QPopupMenu *);
    void PMenuData_menuInsPopup(QPopupMenu *);
    void PMenuData_menuStateChanged();
};

class PRangeControl_virtualize : virtual public virtualize {
protected:
    void PRangeControl_rangeChange();
    void PRangeControl_stepChange();
    void PRangeControl_valueChange();
};

class PObject_virtualize : virtual public virtualize {
public:
    const char *PObject_className() const;
    bool PObject_event(QEvent *);
    bool PObject_eventFilter(QObject *, QEvent *);
    QMetaObject *PObject_metaObject() const;
protected:
    void PObject_initMetaObject();
    void PObject_timerEvent(QTimerEvent *);
};

class PWidget_virtualize : public PObject_virtualize {
public:
    void PWidget_adjustSize();
    bool PWidget_close(bool = FALSE);
    void PWidget_hide();
    void PWidget_move(int, int);
    void PWidget_resize(int, int);
    void PWidget_setBackgroundColor(const QColor &);
    void PWidget_setBackgroundPixmap(const QPixmap &);
    void PWidget_setCursor(const QCursor &);
    void PWidget_setEnabled(bool);
    void PWidget_setFont(const QFont &);
    void PWidget_setGeometry(int, int, int, int);
    void PWidget_setPalette(const QPalette &);
    void PWidget_setStyle(GUIStyle);
    void PWidget_show();
    QSize PWidget_sizeHint() const;
protected:
    void PWidget_closeEvent(QCloseEvent *);
    void PWidget_enterEvent(QEvent *);
    void PWidget_focusInEvent(QFocusEvent *);
    void PWidget_focusOutEvent(QFocusEvent *);
    void PWidget_keyPressEvent(QKeyEvent *);
    void PWidget_keyReleaseEvent(QKeyEvent *);
    void PWidget_leaveEvent(QEvent *);
    void PWidget_mouseDoubleClickEvent(QMouseEvent *);
    void PWidget_mouseMoveEvent(QMouseEvent *);
    void PWidget_mousePressEvent(QMouseEvent *);
    void PWidget_mouseReleaseEvent(QMouseEvent *);
    void PWidget_moveEvent(QMoveEvent *);
    void PWidget_paintEvent(QPaintEvent *);
    void PWidget_resizeEvent(QResizeEvent *);
};

class PButton_virtualize : public PWidget_virtualize {
protected:
    void PButton_drawButton(QPainter *);
    void PButton_drawButtonLabel(QPainter *);
    bool PButton_hitButton(const QPoint &) const;
};

class PCheckBox_virtualize : public PButton_virtualize {};

class PPushButton_virtualize : public PButton_virtualize {};

class PRadioButton_virtualize : public PButton_virtualize {};

class PComboBox_virtualize : public PWidget_virtualize {};

class PDialog_virtualize : public PWidget_virtualize {
protected:
    void PDialog_done(int);
};

class PFileDialog_virtualize : public PDialog_virtualize {};

class PMessageBox_virtualize : public PDialog_virtualize {};

class PTabDialog_virtualize : public PDialog_virtualize {};

class PFrame_virtualize : public PWidget_virtualize {
protected:
    void PFrame_drawContents(QPainter *);
    void PFrame_drawFrame(QPainter *);
    void PFrame_frameChanged();
};

class PGroupBox_virtualize : public PFrame_virtualize {};

class PButtonGroup_virtualize : public PGroupBox_virtualize {};

class PLCDNumber_virtualize : public PFrame_virtualize {};

class PLabel_virtualize : public PFrame_virtualize {};

class PMenuBar_virtualize : public PFrame_virtualize,
			    public PMenuData_virtualize {};

class PTableView_virtualize : public PFrame_virtualize {
protected:
    int PTableView_cellHeight(int);
    int PTableView_cellWidth(int);
    void PTableView_paintCell(QPainter *, int, int);
    void PTableView_setupPainter(QPainter *);
    int PTableView_totalHeight();
    int PTableView_totalWidth();
};

class PListBox_virtualize : public PTableView_virtualize {};

class PMultiLineEdit_virtualize : public PTableView_virtualize {
public:
    void PMultiLineEdit_insertAt(const char *, int, int);
    void PMultiLineEdit_insertLine(const char *, int = -1);
    void PMultiLineEdit_removeLine(int);
protected:
    void PMultiLineEdit_backspace();
    void PMultiLineEdit_cursorDown(bool = FALSE);
    void PMultiLineEdit_cursorLeft(bool = FALSE, bool = TRUE);
    void PMultiLineEdit_cursorRight(bool = FALSE, bool = TRUE);
    void PMultiLineEdit_cursorUp(bool = FALSE);
    void PMultiLineEdit_del();
    void PMultiLineEdit_end(bool = FALSE);
    void PMultiLineEdit_home(bool = FALSE);
    void PMultiLineEdit_insertChar(char);
    void PMultiLineEdit_killLine();
    void PMultiLineEdit_newLine();
    void PMultiLineEdit_pageUp(bool = FALSE);
    void PMultiLineEdit_pageDown(bool = FALSE);
};

class PPopupMenu_virtualize : public PTableView_virtualize,
			      public PMenuData_virtualize {};

class PLineEdit_virtualize : public PWidget_virtualize {};

class PScrollBar_virtualize : public PWidget_virtualize,
			      public PRangeControl_virtualize {};

#include "qslider.h"

class PSlider_virtualize : public PWidget_virtualize,
			   public PRangeControl_virtualize {
public:
    void PSlider_setTickInterval(int);
    void PSlider_setTickmarks(QSlider::TickSetting);
protected:
    void PSlider_paintSlider(QPainter *, const QRect &);
    int PSlider_thickness() const;
};

class PTabBar_virtualize : public PWidget_virtualize {
public:
    int PTabBar_addTab(QTab *);
protected:
    void PTabBar_paint(QPainter *, QTab *, bool) const;
    QTab *PTabBar_selectTab(const QPoint &) const;
};

class PWindow_virtualize : public PWidget_virtualize {};

extern int pfailed;

#define pQtTHIS(type) ((p ## type *)(Q ## type *)(P ## type *)this)

#endif  // VIRTUAL_H
