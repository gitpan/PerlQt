////////////////////////////////////////////////////////////////////////////////
//
// Copyright (C) 1998, Ashley Winters <jql@accessone.com> - All rights reserved.
//
// Since you aren't supposed to have this code, I certainly cannot
// permit your to redistribute it.
//

#ifndef PQT_V_H
#define PQT_V_H

#undef bool

struct pqt_virtual {
    void *pqt_rv;
    void *pqt_this;

    pqt_virtual() {}
    pqt_virtual(void *);
    virtual ~pqt_virtual();
    void pqt_begin_virtual(const char *) const;
    void pqt_call_method(const char *) const;    // unenforced const
    void pqt_call_retmethod(const char *) const; // unenforced const
    void pqt_object(void *);
};

#endif  // PQT_V_H
