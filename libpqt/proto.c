#include "perlqt.h"

bool pqt_int_set(unsigned long &pqtflags, unsigned long pqtflag) {
    bool pqtr = (pqtflags != ~0UL);

    switch(pqtflag) {
    case PQT_NUM_LONG:
    case PQT_NUM_SHORT:
	if(pqtflags & 0x307) pqtr = FALSE; break;
    case PQT_NUM_INT:
	if(pqtflags & 0x302) pqtr = FALSE; break;
    case PQT_NUM_SIGNED:
    case PQT_NUM_UNSIGNED:
	if(pqtflags & 0x330) pqtr = FALSE; break;
    case PQT_NUM_FLOAT:
	if(pqtflags & 0x237) pqtr = FALSE; break;
    case PQT_NUM_DOUBLE:
	if(pqtflags & 0x133) pqtr = FALSE; break;
    default:
	pqtr = FALSE;
    }

    if(pqtr) pqtflags |= pqtflag;
    else pqtflags = ~0UL;
    
    return pqtr;
}

HV *pqt_map_crypt = 0;

SV *pqt_parse_proto(SV *pqtorigproto) {	// 75 lines of Perl, to 200+ lines of C
    if(!pqt_map_crypt)
	pqt_map_crypt = newHV();
    else if(pqt_hv_exists(pqt_map_crypt, SvPV(pqtorigproto, na)))
	return newSVsv(pqtorigproto);	// Sane optimization

    SV *pqt_protosv;
    SV *pqt_fname, *pqt_args;
    SV *pqt_cryptproto = newSVpv("\0", 1);	// beyond this point, there be dragons
    SV *pqt_saneproto = newSVpv("", 0);
    bool pqt_constarg = FALSE;		// double-check ourselves

// A simple removal of whitespace and copy to pqt_protosv of our favorite
// prototype bundle of joy

    {
	if(!SvLEN(pqtorigproto))
	    croak("You gotta at least put SOMETHING in the prototype! "
		  "Your code sucks");
	char *pqt_protostr = SvPV(pqtorigproto, na);
	char *pqt_protoend = SvEND(pqtorigproto)-1;

	while(isSPACE(*pqt_protostr)) pqt_protostr++;
	while(isSPACE(*pqt_protoend) && pqt_protoend > pqt_protostr) pqt_protoend--;
	pqt_protosv = newSVpv(pqt_protostr, (pqt_protoend + 1) - pqt_protostr);
    }

// This is a nice place to extract pqt_fname. Might as well do a few sanity
// checks while we're in the area

    {
	char *pqt_protostr = SvPVX(pqt_protosv);
	char *pqt_fnamend = pqt_protostr;
	char *pqt_openparen;

	while(isALNUM(*pqt_fnamend)) pqt_fnamend++;		// pqt_fname()
	pqt_openparen = pqt_fnamend;
	while(isSPACE(*pqt_openparen)) pqt_openparen++;		// pqt_fname ()

	if(pqt_fnamend == pqt_protostr)
	    croak("Missing function-name in prototype '%s'", pqt_protostr);
	if(!*pqt_openparen)
	    croak("Missing argument prototype in '%s'", pqt_protostr);

	pqt_fname = newSVpv(pqt_protostr, pqt_fnamend - pqt_protostr);

	char pqt_len[1] = { SvCUR(pqt_fname) + 1 };
	sv_catpvn(pqt_cryptproto, pqt_len, 1);
	sv_catpvn(pqt_cryptproto, SvPVX(pqt_fname), SvCUR(pqt_fname));
	sv_catpvn(pqt_cryptproto, "\0", 1);

	sv_catsv(pqt_saneproto, pqt_fname);
	sv_catpv(pqt_saneproto, "(");

	if(*pqt_openparen != '(')	// bad news
	    croak("The argument-list for '%s' must begin with "
		  "an opening parenthesis", SvPVX(pqt_fname));
	if(*(SvEND(pqt_protosv)-1) != ')')
	    croak("The argument-list for '%s' must end with "
		  "a closing parenthesis", SvPVX(pqt_fname));

	pqt_args = newSVpv(pqt_openparen, SvEND(pqt_protosv) - pqt_openparen);
    }

// Here we get to play 'fun with pqt_args'. A game which looks kinda
// like a tokenizer. Oh well.

    {
	char *pqt_argstart = SvPVX(pqt_args)+1;		// skip (
	char *pqt_argsend  = SvEND(pqt_args)-1;		// skip )
	while(isSPACE(*pqt_argstart)) pqt_argstart++;	// ditch whitespace
	while(isSPACE(*pqt_argsend))  pqt_argsend--;
	while(pqt_argstart < pqt_argsend) {
	    bool pqt_reference = FALSE;

	    if(*pqt_argstart == '\\') {			// catch argument-references
		pqt_reference = TRUE;
		pqt_argstart++;
	    }
	    if(!isALNUM(*pqt_argstart)) {
		char pqt_sanestr[] = "SV*";		// copy, not pointer (I hope)
		char pqt_cryptstr[1] = { 0 };

		if(*pqt_argstart == '.' && *++pqt_argstart == '.' &&
		   *++pqt_argstart == '.') {
		    *pqt_sanestr = 'A';		// AV*
		    *pqt_cryptstr = PQT_PROTO_LIST;		// ...
		}
		else if(*pqt_argstart == '$')
		    *pqt_cryptstr = (*++pqt_argstart == '$') ? PQT_PROTO_SVSCALAR :
			(pqt_reference ? PQT_PROTO_SCALARREF : PQT_PROTO_SCALAR);
		else if(*pqt_argstart == '@' || *pqt_argstart == '%') {
		    if(*(pqt_argstart+1) != '$')
			croak("This version of PerlQt is not capable of "
			      "accepting non-scalars as prototype arguments");
		    *pqt_cryptstr = (*pqt_argstart == '@') ? PQT_PROTO_AVSCALAR : PQT_PROTO_HVSCALAR;
		}
		else croak("Fatal error while parsing '%s': "
			   "Invalid character near '%s'",
			   SvPVX(pqt_protosv), pqt_argstart);
		sv_catpv(pqt_saneproto, pqt_sanestr);
		sv_catpvn(pqt_cryptproto, pqt_cryptstr, 1);
	    }
	    else {
		SV *pqt_tokensv = newSVpv("", 0);
		unsigned long pqt_intstat = 0;
		while(isALNUM(*pqt_argstart)) {
		    char *pqt_token = NULL, *pqt_tokend = pqt_argstart;
		    char pqt_cryptstr[] = { -1 }, *pqt_sanestr;
		    int pqt_cryptlen = 1;

		    while(isALNUM(*pqt_tokend)) pqt_tokend++;
		    sv_setpvn(pqt_tokensv, pqt_argstart, pqt_tokend-pqt_argstart);
		    while(isSPACE(*pqt_tokend)) pqt_tokend++;
		    pqt_argstart = pqt_tokend;

		    pqt_token = SvPVX(pqt_tokensv);
		    pqt_sanestr = pqt_token;		// default to the token

		    if(strEQ(pqt_token, "const")) {	// const is a toughie
			if(pqt_constarg == TRUE)
			    croak("Multiple const declarations for an "
				  "argument in '%s', try again",
				  SvPVX(pqt_fname));
			if(pqt_intstat)
			    croak("const is a reserved word and must be "
				  "the first in the type identification");
			pqt_constarg = TRUE;
			pqt_sanestr = "const ";
			*pqt_cryptstr = PQT_PROTO_CONST;

			sv_catpv(pqt_saneproto, pqt_sanestr);
			sv_catpvn(pqt_cryptproto, pqt_cryptstr, pqt_cryptlen);
			continue;
		    }

		    if(pqt_intstat) sv_catpv(pqt_saneproto, " ");

		    if(strEQ(pqt_token, "int")) pqt_int_set(pqt_intstat, PQT_NUM_INT);
		    else if(strEQ(pqt_token, "long")) pqt_int_set(pqt_intstat, PQT_NUM_LONG);
		    else if(strEQ(pqt_token, "short")) pqt_int_set(pqt_intstat, PQT_NUM_SHORT);
		    else if(strEQ(pqt_token, "signed"))
			pqt_int_set(pqt_intstat, PQT_NUM_SIGNED);
		    else if(strEQ(pqt_token, "unsigned"))
			pqt_int_set(pqt_intstat, PQT_NUM_UNSIGNED);
		    else if(strEQ(pqt_token, "float"))
			pqt_int_set(pqt_intstat, PQT_NUM_FLOAT);
		    else if(strEQ(pqt_token, "double"))
			pqt_int_set(pqt_intstat, PQT_NUM_DOUBLE);
		    else if(pqt_intstat) {
			SvCUR_set(pqt_saneproto, SvCUR(pqt_saneproto)-1);  // chop
			break;
		    }
		    else {
		        if(strEQ(pqt_token, "bool")) *pqt_cryptstr = PQT_PROTO_BOOL;
		        else if(strEQ(pqt_token, "string")) {
			    *pqt_cryptstr = PQT_PROTO_STRING;
			    pqt_sanestr = "char*";
			}
			else if(strEQ(pqt_token, "cstring")) {
			    *pqt_cryptstr = PQT_PROTO_STRING;
			    pqt_sanestr = "const char*";
			    if(pqt_constarg)
				croak("const cstring is redundant in '%s'", SvPVX(pqt_fname));
			}
			else {
			    sv_catpv(pqt_saneproto, pqt_token);	// object*
			    sv_catpv(pqt_saneproto, pqt_reference ? "&" : "*");

			    *pqt_cryptstr = PQT_PROTO_OBJECT;		// \1\lenObject\0
			    sv_catpvn(pqt_cryptproto, pqt_cryptstr, pqt_cryptlen);
			    *pqt_cryptstr = SvCUR(pqt_tokensv) + 1;
			    sv_catpvn(pqt_cryptproto, pqt_cryptstr, pqt_cryptlen);
			    sv_catpv(pqt_cryptproto, pqt_token);
			    *pqt_cryptstr = 0;
			    sv_catpvn(pqt_cryptproto, pqt_cryptstr, pqt_cryptlen);
			    break;
			}
			sv_catpv(pqt_saneproto, pqt_sanestr);
			sv_catpvn(pqt_cryptproto, pqt_cryptstr, pqt_cryptlen);
			break;
		    }
		    sv_catpv(pqt_saneproto, pqt_sanestr);
		}
		if(pqt_intstat) {
		    if(pqt_intstat == ~0UL) {
		        char *pqt_start = SvEND(pqt_saneproto)-1;
			while(isALNUM(*pqt_start) || isSPACE(*pqt_start)) pqt_start--;
			croak("Invalid type '%s' in '%s' prototype, stopped",
			      ++pqt_start, SvPVX(pqt_fname));
		    }
		    char pqt_cryptstr[1] = { 0 };
		    if(pqt_intstat & PQT_NUM_DOUBLE)
			*pqt_cryptstr = (pqt_intstat & PQT_NUM_LONG) ? PQT_PROTO_LDOUBLE : PQT_PROTO_DOUBLE;
		    else if(pqt_intstat & PQT_NUM_FLOAT) *pqt_cryptstr = PQT_PROTO_FLOAT;
		    else if(pqt_intstat & PQT_NUM_LONG)  *pqt_cryptstr = PQT_PROTO_LONG;
		    else if(pqt_intstat & PQT_NUM_SHORT) *pqt_cryptstr = PQT_PROTO_SHORT;
		    else if(pqt_intstat & PQT_NUM_INT)   *pqt_cryptstr = PQT_PROTO_INT;
		    if(*pqt_cryptstr) sv_catpvn(pqt_cryptproto, pqt_cryptstr, 1);
		}
		SvREFCNT_dec(pqt_tokensv);
		pqt_constarg = FALSE;
	    }
	    (*SvPVX(pqt_cryptproto))++;
	    while(*pqt_argstart != ',' && pqt_argstart < pqt_argsend) pqt_argstart++;
	    if(*pqt_argstart == ',') {
		pqt_argstart++;
		while(isSPACE(*pqt_argstart)) pqt_argstart++;
		if(pqt_argstart < pqt_argsend) sv_catpv(pqt_saneproto, ",");
		else {
		    pqt_argstart--;
		    while(isSPACE(*pqt_argstart)) pqt_argstart--;	// force error
		}
	    }
	}
	sv_catpv(pqt_saneproto, ")");
    }
/*
    {
	SV *ch = newSVpv("", 0);
	SV *pqt_cryptstr = newSVpv("", 0);
	char *crypt = SvPVX(pqt_cryptproto);
	for(int i = 0; i < SvCUR(pqt_cryptproto); i++) {
	    if(!isALNUM(crypt[i])) {
		sv_catpv(pqt_cryptstr, "\\");
		sv_setiv(ch, (IV)crypt[i]);
		sv_catpv(pqt_cryptstr, SvPV(ch, na));
	    }
	    else sv_catpvn(pqt_cryptstr, crypt+i, 1);
	}
	printf("pqt_cryptlen of '%s' is %d\n", SvPVX(pqt_protosv), SvCUR(pqt_cryptproto));
	printf("pqt_cryptstr is '%s'\n", SvPVX(pqt_cryptstr));

	SvREFCNT_dec(pqt_cryptstr);
	SvREFCNT_dec(ch);
    }
*/

// Don't allocate new memory for an existing prototype

    if(!pqt_hv_exists(pqt_map_crypt, SvPVX(pqt_saneproto)))
	pqt_hv_store(pqt_map_crypt, SvPVX(pqt_saneproto), pqt_cryptproto);
    else
        SvREFCNT_dec(pqt_cryptproto);

    SvREFCNT_dec(pqt_protosv);
    SvREFCNT_dec(pqt_fname);
    SvREFCNT_dec(pqt_args);

    return pqt_saneproto;
}
