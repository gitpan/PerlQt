/*
 * Critical support file for Pig symbol import and export in Perl.
 * Authors of add-on modules will need to include this file in their
 * library.
 *
 * Copyright (C) 1999, Ashley Winters <jql@accessone.com>
 *
 * You may distribute under the terms of the LGPL as specified in the
 * README.LICENSE file which should be included with this library.
 *
 */

// Get definitions of SV* and qsort()
#include "pigperl.h"
#include <stdlib.h>

int pig_count_symbols(struct pig_symboltable *pig_symbols) {
    int pigcnt = 0;

    if(!pig_symbols) return 0;
    while(pig_symbols->pigname || pig_symbols->pigptr) {
	if(pig_symbols->pigname)
	    pigcnt++;
	else
	    pigcnt += pig_count_symbols((struct pig_symboltable *)pig_symbols->pigptr);
	pig_symbols++;
    }

    return pigcnt;
}

struct pig_symboltable **pig_get_symbols(struct pig_symboltable **pig_list, struct pig_symboltable *pig_symbols) {
    if(!pig_symbols) return pig_list;
    while(pig_symbols->pigname || pig_symbols->pigptr) {
	if(pig_symbols->pigname) {
	    *pig_list = pig_symbols;
	    pig_list++;
	}
	else
	    pig_list = pig_get_symbols(pig_list, (struct pig_symboltable *)pig_symbols->pigptr);

	pig_symbols++;
    }

    return pig_list;
}

static int pig_comparesymbol(const void *pig0, const void *pig1) {
    struct pig_symboltable **pigsym0, **pigsym1;
    pigsym0 = (struct pig_symboltable **)pig0;
    pigsym1 = (struct pig_symboltable **)pig1;
    return strcmp((*pigsym0)->pigname, (*pigsym1)->pigname);
}

struct pig_symboltable **pig_create_symbol_list(struct pig_symboltable *pig_symbols, SV *pig_sv) {
    int pigcnt;
    struct pig_symboltable **pig_list;
    pigcnt = pig_count_symbols(pig_symbols);

    sv_setpv(pig_sv, "");
    SvGROW(pig_sv, (pigcnt + 1) * sizeof(struct pig_symboltable *));
    pig_list = (struct pig_symboltable **)SvPVX(pig_sv);

    *(pig_get_symbols(pig_list, pig_symbols)) = 0;

    qsort(pig_list, pigcnt, sizeof(struct pig_symboltable *), pig_comparesymbol); 

    return pig_list;
}

void pig_symbol_import(struct pig_symboltable **pig_import, struct pig_symboltable **pig_export) {
    while(*pig_import) {
	while(*pig_export && strcmp((*pig_export)->pigname, (*pig_import)->pigname) < 0)
	    pig_export++;
	if(!*pig_export) break;

	if(!strcmp((*pig_export)->pigname, (*pig_import)->pigname)) {
	    PIG_DEBUG_SYMBOL(("import %s %p => %p\n", (*pig_export)->pigname,
			      (*pig_import)->pigptr,  (*pig_export)->pigptr));
	    *((void **)(*pig_import)->pigptr) = (*pig_export)->pigptr;
	}
	else {
	    PIG_DEBUG_SYMBOL(("import %s to nowhere\n", (*pig_import)->pigname));
	    *((void **)(*pig_import)->pigptr) = 0;
	}

	pig_import++;
    }
}

void pig_symbol_exchange(pig_symboltable *pig_export, pig_symboltable *pig_import,
			 const char *pig_class, const char *pig_super) {
    pig_symboltable **pig_export_vtbl, **pig_import_vtbl;  // **pig_super_vtbl
    char *pigsvname;

    if(!pig_class) return;

    pigsvname = new char [strlen(pig_class) + 7];
    strcpy(pigsvname, pig_class);
    strcpy(pigsvname, "::.pig");

    pig_export_vtbl = pig_create_symbol_list(pig_export, perl_get_sv(pigsvname, TRUE));
    pig_import_vtbl = pig_create_symbol_list(pig_import, sv_newmortal());
//  pig_super_vtbl = pig_extract_symbol_list(pig_super);
    pig_symbol_import(pig_import_vtbl, pig_export_vtbl);
//  pig_symbol_import(pig_import_vtbl, pig_super_vtbl);

    delete [] pigsvname;
}
