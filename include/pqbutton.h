#ifndef PQBUTTON_H
#define PQBUTTON_H

/*
 * Declaration of the VQButton class
 *
 * Copyright (C) 1997, Ashley Winters <jql@accessone.com>
 *
 * You may distribute under the terms of the LGPL as specified in the
 * README file
 */

#include <pqwidget.h>
#include <qbutton.h>

#define QButton_functions						\
protected:								\
    void drawButton(QPainter *);					\
    void drawButtonLabel(QPainter *);					\
    bool hitButton(const QPoint &) const;

#define QButton_inlines(class)						\
public:									\
    void v_drawButton(QPainter *a) { class::drawButton(a); }		\
    void v_drawButtonLabel(QPainter *a) { class::drawButtonLabel(a); }	\
    bool v_hitButton(const QPoint &a) const { return class::hitButton(a); }

#define QButton_virtual_functions QWidget_virtual_functions QButton_functions

#define QButton_virtual_inlines(class)					\
    QWidget_virtual_inlines(class)					\
    QButton_inlines(class)

class QButton_virtualize : public QWidget_virtualize {
public:
    void QButton_drawButton(QPainter *);
    void QButton_drawButtonLabel(QPainter *);
    bool QButton_hitButton(const QPoint &) const;
};

class VQButton : public QButton, public QButton_virtualize {
    QButton_virtual_functions
public:
    VQButton(QWidget *parent = 0, const char *name = 0) :
	QButton(parent, name) {}
};

class PQButton : public QButton {
    QButton_virtual_inlines(QButton)
public:
    void setDown(bool a) { QButton::setDown(a); }
    void setOn(bool a) { QButton::setOn(a); }
    void setToggleButton(bool a) { QButton::setToggleButton(a); }
};

typedef const QButton CQButton;
typedef const PQButton CPQButton;

#endif  // PQBUTTON_H
