#ifndef PQWIDGET_H
#define PQWIDGET_H

/*
 * Declaration of the VQWidget class
 *
 * Copyright (C) 1997, Ashley Winters <jql@accessone.com>
 *
 * You may distribute under the terms of the LGPL as specified in the
 * README file
 */

#include <pqobject.h>
#include <qwidget.h>

#define QWidget_functions						\
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
    void backgroundColorChange(const QColor &);				\
    void backgroundPixmapChange(const QPixmap &);			\
    void closeEvent(QCloseEvent *);					\
    void enabledChange(bool);						\
    void enterEvent(QEvent *);						\
    void focusInEvent(QFocusEvent *);					\
    bool focusNextPrevChild(bool);					\
    void focusOutEvent(QFocusEvent *);					\
    void fontChange(const QFont &);					\
    void keyPressEvent(QKeyEvent *);					\
    void keyReleaseEvent(QKeyEvent *);					\
    void leaveEvent(QEvent *);						\
    void mouseDoubleClickEvent(QMouseEvent *);				\
    void mouseMoveEvent(QMouseEvent *);					\
    void mousePressEvent(QMouseEvent *);				\
    void mouseReleaseEvent(QMouseEvent *);				\
    void moveEvent(QMoveEvent *);					\
    void paintEvent(QPaintEvent *);					\
    void paletteChange(const QPalette &);				\
    void resizeEvent(QResizeEvent *);					\
    void styleChange(GUIStyle);


#define QWidget_inlines(class)						\
public:									\
    void v_adjustSize() { class::adjustSize(); }			\
    void v_backgroundColorChange(const QColor &a) {			\
	class::backgroundColorChange(a);				\
    }									\
    void v_backgroundPixmapChange(const QPixmap &a) {			\
	class::backgroundPixmapChange(a);				\
    }									\
    bool v_close(bool a = FALSE) { return class::close(a); }		\
    void v_closeEvent(QCloseEvent *a) { class::closeEvent(a); }		\
    void v_enabledChange(bool a) { class::enabledChange(a); }		\
    void v_enterEvent(QEvent *a) { class::enterEvent(a); }		\
    void v_focusInEvent(QFocusEvent *a) { class::focusInEvent(a); }	\
    bool v_focusNextPrevChild(bool a) {					\
	return class::focusNextPrevChild(a);				\
    }									\
    void v_focusOutEvent(QFocusEvent *a) { class::focusOutEvent(a); }	\
    void v_fontChange(const QFont &a) { class::fontChange(a); }		\
    void v_hide() { class::hide(); }					\
    void v_keyPressEvent(QKeyEvent *a) { class::keyPressEvent(a); }	\
    void v_keyReleaseEvent(QKeyEvent *a) { class::keyReleaseEvent(a); }	\
    void v_leaveEvent(QEvent *a) { class::leaveEvent(a); }		\
    void v_mouseDoubleClickEvent(QMouseEvent *a) {			\
	class::mouseDoubleClickEvent(a);				\
    }									\
    void v_mouseMoveEvent(QMouseEvent *a) {				\
	class::mouseMoveEvent(a);					\
    }									\
    void v_mousePressEvent(QMouseEvent *a) {				\
	class::mousePressEvent(a);					\
    }									\
    void v_mouseReleaseEvent(QMouseEvent *a) {				\
	class::mouseReleaseEvent(a);					\
    }									\
    void v_move(int a1, int a2) { class::move(a1, a2); }		\
    void v_moveEvent(QMoveEvent *a) { class::moveEvent(a); }		\
    void v_paintEvent(QPaintEvent *a) { class::paintEvent(a); }		\
    void v_paletteChange(const QPalette &a) {				\
	class::paletteChange(a);					\
    }									\
    void v_resize(int a1, int a2) { class::resize(a1, a2); }		\
    void v_resizeEvent(QResizeEvent *a) { class::resizeEvent(a); }	\
    void v_setBackgroundColor(const QColor &a) {			\
	class::setBackgroundColor(a);					\
    }									\
    void v_setBackgroundPixmap(const QPixmap &a) {			\
	class::setBackgroundPixmap(a);					\
    }									\
    void v_setCursor(const QCursor &a) { class::setCursor(a); }		\
    void v_setEnabled(bool a) { class::setEnabled(a); }			\
    void v_setFont(const QFont &a) { class::setFont(a); }		\
    void v_setGeometry(int a1, int a2, int a3, int a4) {		\
	class::setGeometry(a1, a2, a3, a4);				\
    }									\
    void v_setPalette(const QPalette &a) { class::setPalette(a); }	\
    void v_setStyle(GUIStyle a) { class::setStyle(a); }			\
    void v_show() { class::show(); }					\
    QSize v_sizeHint() const { class::sizeHint(); }			\
    void v_styleChange(GUIStyle a) { class::styleChange(a); }

#define QWidget_virtual_functions QObject_virtual_functions QWidget_functions

#define QWidget_virtual_inlines(class)					\
    QObject_virtual_inlines(class)					\
    QWidget_inlines(class)


class QWidget_virtualize : public QObject_virtualize {
public:
    void QWidget_adjustSize();
    void QWidget_backgroundColorChange(const QColor &);
    void QWidget_backgroundPixmapChange(const QPixmap &);
    bool QWidget_close(bool = FALSE);
    void QWidget_closeEvent(QCloseEvent *);
    void QWidget_enabledChange(bool);
    void QWidget_enterEvent(QEvent *);
    void QWidget_focusInEvent(QFocusEvent *);
    bool QWidget_focusNextPrevChild(bool);
    void QWidget_focusOutEvent(QFocusEvent *);
    void QWidget_fontChange(const QFont &);
    void QWidget_hide();
    void QWidget_keyPressEvent(QKeyEvent *);
    void QWidget_keyReleaseEvent(QKeyEvent *);
    void QWidget_leaveEvent(QEvent *);
    void QWidget_mouseDoubleClickEvent(QMouseEvent *);
    void QWidget_mouseMoveEvent(QMouseEvent *);
    void QWidget_mousePressEvent(QMouseEvent *);
    void QWidget_mouseReleaseEvent(QMouseEvent *);
    void QWidget_move(int, int);
    void QWidget_moveEvent(QMoveEvent *);
    void QWidget_paintEvent(QPaintEvent *);
    void QWidget_paletteChange(const QPalette &);
    void QWidget_resize(int, int);
    void QWidget_resizeEvent(QResizeEvent *);
    void QWidget_setBackgroundColor(const QColor &);
    void QWidget_setBackgroundPixmap(const QPixmap &);
    void QWidget_setCursor(const QCursor &);
    void QWidget_setEnabled(bool);
    void QWidget_setFont(const QFont &);
    void QWidget_setGeometry(int, int, int, int);
    void QWidget_setPalette(const QPalette &);
    void QWidget_setStyle(GUIStyle);
    void QWidget_show();
    QSize QWidget_sizeHint() const;
    void QWidget_styleChange(GUIStyle);
};

class VQWidget : public QWidget, public QWidget_virtualize {
    QWidget_virtual_functions
public:
    VQWidget(QWidget *parent = 0, const char *name = 0, WFlags f = 0) :
	QWidget(parent, name, f) {}
};

class PQWidget : public QWidget {
    QWidget_virtual_inlines(QWidget)
public:
    void create(WId a1, bool a2, bool a3) { QWidget::create(a1, a2, a3); }
    void destroy(bool a1, bool a2) { QWidget::destroy(a1, a2); }
};

typedef const QWidget CQWidget;
typedef const PQWidget CPQWidget;

typedef QWidget::BackgroundMode QWidget__BackgroundMode;
typedef QWidget::FocusPolicy QWidget__FocusPolicy;

#endif  // PQWIDGET_H
