#include "perlqt.h"

void pqt_increment_argument_index();
extern const char *pqt_current_method;

int pqt_argumentcount() {
    PQT_dXSARGS;
    if(!strcmp(pqt_current_method, "new")) {
//        pqt_increment_argument_index();
	return items - 1;
    }
    return items;
}

unsigned int pqt_argument_info(int pqtidx) {
    PQT_dXSARGS;
    unsigned int pqtr;
    SV *pqtsv = ST(pqtidx);      // We ass_u_me ST(pqtidx) exists
    if(!SvOK(pqtsv)) pqtr = PQTTYPE_UNDEF;
    else if(SvIOK(pqtsv)) {
	IV pqti = SvIV(pqtsv);
	pqtr = PQTTYPE_INT;
	if(pqti == 0 || pqti == 1) pqtr |= PQTTYPE_BOOL;
    }
    else if(SvNOK(pqtsv)) pqtr = PQTTYPE_FLOAT;
    else if(SvPOK(pqtsv)) pqtr = PQTTYPE_STRING;
    else if(SvROK(pqtsv)) pqtr = PQTTYPE_OBJECT;		// BUG!
    else pqtr = 0;

    return pqtr;
}

bool pqt_object_isa(int, const char *) {			// BUG!
    return TRUE;
}
