#ifndef PSOCKNOT_H
#define PSOCKNOT_H

/*
 * Declaration of the PSocketNotifier class
 *
 * Copyright (C) 1997, Ashley Winters <jql@accessone.com>
 *
 * You may distribute under the terms of the LGPL as specified in the
 * README file
 */

#undef bool
#include "qsocknot.h"

class PSocketNotifier : public QSocketNotifier {
public:
    PSocketNotifier(int socket, Type type, QObject *parent = 0, const char
*name = 0) : QSocketNotifier(socket, type, parent, name) {}
};

typedef QSocketNotifier::Type QSocketNotifier__Type;

#endif  // PSOCKNOT_H
