/*
 * This file contains the pig_parse_proto function which parses
 * a Perl string into a Qt-compatible SIGNAL()/SLOT() prototype.
 *
 * Copyright (C) 1999, Ashley Winters <jql@accessone.com>
 *
 * You may distribute under the terms of the LGPL as specified in the
 * README.LICENSE file which should be included with this library.
 *
 */

#include "pigperl.h"

static bool pig_int_set(unsigned long &pigflags, unsigned long pigflag) {
    bool pigr = (pigflags != ~0UL);

    switch(pigflag) {
    case PIG_NUM_LONG:
    case PIG_NUM_SHORT:
	if(pigflags & 0x307) pigr = FALSE; break;
    case PIG_NUM_INT:
	if(pigflags & 0x302) pigr = FALSE; break;
    case PIG_NUM_SIGNED:
    case PIG_NUM_UNSIGNED:
	if(pigflags & 0x330) pigr = FALSE; break;
    case PIG_NUM_FLOAT:
	if(pigflags & 0x237) pigr = FALSE; break;
    case PIG_NUM_DOUBLE:
	if(pigflags & 0x133) pigr = FALSE; break;
    default:
	pigr = FALSE;
    }

    if(pigr) pigflags |= pigflag;
    else pigflags = ~0UL;
    
    return pigr;
}

static HV *pig_map_crypt = 0;

static SV *pig_hv_fetch(HV *pig_hv, const char *pig_key) {
    SV **pig_retsvp = hv_fetch(pig_hv, (char *)pig_key, strlen(pig_key), 0);

    return pig_retsvp ? *pig_retsvp : &PIGsv_undef;
}

static void pig_hv_store(HV *pig_hv, const char *pig_key, SV *pig_sv) {
    hv_store(pig_hv, (char *)pig_key, strlen(pig_key), pig_sv, 0);
}

static bool pig_hv_exists(HV *pig_hv, const char *pig_key) {
    return hv_exists(pig_hv, (char *)pig_key, strlen(pig_key));
}

PIG_DEFINE_FUNC_1(SV *, pig_map_proto, SV *) {
    STRLEN n_a;
    SV **pigsvp;
    char *pigp = SvPV(pig0, n_a);
    if(!hv_exists(pig_map_crypt, pigp, SvCUR(pig0)))
        return &PIGsv_undef;

    pigsvp = hv_fetch(pig_map_crypt, pigp, SvCUR(pig0), 0);
    if(pigsvp)
        return *pigsvp;

    return &PIGsv_undef;
}

PIG_DEFINE_FUNC_1(SV *, pig_parse_proto, SV *) {	// 75 lines of Perl, to 200+ lines of C
    STRLEN n_a;
    if(!pig_map_crypt)
	pig_map_crypt = newHV();
    else if(pig_hv_exists(pig_map_crypt, SvPV(pig0, n_a)))
	return newSVsv(pig0);	// Sane optimization

    SV *pig_protosv;
    SV *pig_fname, *pig_args;
    SV *pig_cryptproto = newSVpv((char *)"\0", 1);	// beyond this point, there be dragons
    SV *pig_saneproto = newSVpv((char *)"", 0);
    bool pig_constarg = FALSE;		// double-check ourselves

// A simple removal of whitespace and copy to pig_protosv of our favorite
// prototype bundle of joy

    {
        if(!SvLEN(pig0)) {
	    croak("You gotta at least put SOMETHING in the prototype! "
		  "Your code sucks");
	}
	char *pig_protostr = SvPV(pig0, n_a);
	char *pig_protoend = SvEND(pig0)-1;

	while(isSPACE(*pig_protostr)) pig_protostr++;
	while(isSPACE(*pig_protoend) && pig_protoend > pig_protostr) pig_protoend--;
	pig_protosv = newSVpv(pig_protostr, (pig_protoend + 1) - pig_protostr);
    }

// This is a nice place to extract pig_fname. Might as well do a few sanity
// checks while we're in the area

    {
	char *pig_protostr = SvPVX(pig_protosv);
	char *pig_fnamend = pig_protostr;
	char *pig_openparen;

	while(isALNUM(*pig_fnamend)) pig_fnamend++;		// pig_fname()
	pig_openparen = pig_fnamend;
	while(isSPACE(*pig_openparen)) pig_openparen++;		// pig_fname ()

	if(pig_fnamend == pig_protostr)
	    croak("Missing function-name in prototype '%s'", pig_protostr);
	if(!*pig_openparen)
	    croak("Missing argument prototype in '%s'", pig_protostr);

	pig_fname = newSVpv(pig_protostr, pig_fnamend - pig_protostr);

	char pig_len[1] = { SvCUR(pig_fname) + 1 };
	sv_catpvn(pig_cryptproto, pig_len, 1);
	sv_catpvn(pig_cryptproto, SvPVX(pig_fname), SvCUR(pig_fname));
	sv_catpvn(pig_cryptproto, (char *)"\0", 1);

	sv_catsv(pig_saneproto, pig_fname);
	sv_catpv(pig_saneproto, (char *)"(");

	if(*pig_openparen != '(')	// bad news
	    croak("The argument-list for '%s' must begin with "
		  "an opening parenthesis", SvPVX(pig_fname));
	if(*(SvEND(pig_protosv)-1) != ')')
	    croak("The argument-list for '%s' must end with "
		  "a closing parenthesis", SvPVX(pig_fname));

	pig_args = newSVpv(pig_openparen, SvEND(pig_protosv) - pig_openparen);
    }

// Here we get to play 'fun with pig_args'. A game which looks kinda
// like a tokenizer. Oh well.

    {
	char *pig_argstart = SvPVX(pig_args)+1;		// skip (
	char *pig_argsend  = SvEND(pig_args)-1;		// skip )
	while(isSPACE(*pig_argstart)) pig_argstart++;	// ditch whitespace
	while(isSPACE(*pig_argsend))  pig_argsend--;
	while(pig_argstart < pig_argsend) {
	    bool pig_reference = FALSE;

	    if(*pig_argstart == '\\') {			// catch argument-references
		pig_reference = TRUE;
		pig_argstart++;
	    }
	    if(!isALNUM(*pig_argstart)) {
		char pig_sanestr[] = "SV*";		// copy, not pointer (I hope)
		char pig_cryptstr[1] = { 0 };

		if(*pig_argstart == '.' && *++pig_argstart == '.' &&
		   *++pig_argstart == '.') {
		    *pig_sanestr = 'A';		// AV*
		    *pig_cryptstr = PIG_PROTO_LIST;		// ...
		}
		else if(*pig_argstart == '$')
		    *pig_cryptstr = (*++pig_argstart == '$') ? PIG_PROTO_SVSCALAR :
			(pig_reference ? PIG_PROTO_SCALARREF : PIG_PROTO_SCALAR);
		else if(*pig_argstart == '@' || *pig_argstart == '%') {
		    if(*(pig_argstart+1) != '$')
			croak("This version of PerlQt is not capable of "
			      "accepting non-scalars as prototype arguments");
		    *pig_cryptstr = (*pig_argstart == '@') ? PIG_PROTO_AVSCALAR : PIG_PROTO_HVSCALAR;
		}
		else croak("Fatal error while parsing '%s': "
			   "Invalid character near '%s'",
			   SvPVX(pig_protosv), pig_argstart);
		sv_catpv(pig_saneproto, pig_sanestr);
		sv_catpvn(pig_cryptproto, pig_cryptstr, 1);
	    }
	    else {
		SV *pig_tokensv = newSVpv((char *)"", 0);
		unsigned long pig_intstat = 0;
		while(isALNUM(*pig_argstart)) {
		    char *pig_token = NULL, *pig_tokend = pig_argstart;
		    char pig_cryptstr[] = { -1 }, *pig_sanestr;
		    int pig_cryptlen = 1;

		    while(isALNUM(*pig_tokend)) pig_tokend++;
		    sv_setpvn(pig_tokensv, pig_argstart, pig_tokend-pig_argstart);
		    while(isSPACE(*pig_tokend)) pig_tokend++;
		    pig_argstart = pig_tokend;

		    pig_token = SvPVX(pig_tokensv);
		    pig_sanestr = pig_token;		// default to the token

		    if(strEQ(pig_token, "const")) {	// const is a toughie
			if(pig_constarg == TRUE)
			    croak("Multiple const declarations for an "
				  "argument in '%s', try again",
				  SvPVX(pig_fname));
			if(pig_intstat)
			    croak("const is a reserved word and must be "
				  "the first in the type identification");
			pig_constarg = TRUE;
			pig_sanestr = (char *)"const ";
			*pig_cryptstr = PIG_PROTO_CONST;

			sv_catpv(pig_saneproto, pig_sanestr);
			sv_catpvn(pig_cryptproto, pig_cryptstr, pig_cryptlen);

			if(*pig_argstart == '\\') {			// catch argument-references
			    if(pig_reference)
				croak("Multiple \\reference declarations in '%s'", SvPVX(pig_fname));
			    pig_reference = TRUE;
			    pig_argstart++;
		    	}

			continue;
		    }

		    if(pig_intstat) sv_catpv(pig_saneproto, (char *)" ");

		    if(strEQ(pig_token, "int")) pig_int_set(pig_intstat, PIG_NUM_INT);
		    else if(strEQ(pig_token, "long")) pig_int_set(pig_intstat, PIG_NUM_LONG);
		    else if(strEQ(pig_token, "short")) pig_int_set(pig_intstat, PIG_NUM_SHORT);
		    else if(strEQ(pig_token, "signed"))
			pig_int_set(pig_intstat, PIG_NUM_SIGNED);
		    else if(strEQ(pig_token, "unsigned"))
			pig_int_set(pig_intstat, PIG_NUM_UNSIGNED);
		    else if(strEQ(pig_token, "float"))
			pig_int_set(pig_intstat, PIG_NUM_FLOAT);
		    else if(strEQ(pig_token, "double"))
			pig_int_set(pig_intstat, PIG_NUM_DOUBLE);
		    else if(pig_intstat) {
			SvCUR_set(pig_saneproto, SvCUR(pig_saneproto)-1);  // chop
			break;
		    }
		    else {
		        if(strEQ(pig_token, "bool")) *pig_cryptstr = PIG_PROTO_BOOL;
		        else if(strEQ(pig_token, "string")) {
			    *pig_cryptstr = PIG_PROTO_STRING;
			    pig_sanestr = (char *)"char*";
			}
			else if(strEQ(pig_token, "cstring")) {
			    *pig_cryptstr = PIG_PROTO_STRING;
			    pig_sanestr = (char *)"const char*";
			    if(pig_constarg)
				croak("const cstring is redundant in '%s'", SvPVX(pig_fname));
			}
			else {
			    sv_catpv(pig_saneproto, pig_token);	// object*
			    sv_catpv(pig_saneproto, pig_reference ? (char *)"&" : (char *)"*");

			    *pig_cryptstr = PIG_PROTO_OBJECT;		// \1\lenObject\0
			    sv_catpvn(pig_cryptproto, pig_cryptstr, pig_cryptlen);
			    *pig_cryptstr = SvCUR(pig_tokensv) + 1;
			    sv_catpvn(pig_cryptproto, pig_cryptstr, pig_cryptlen);
			    sv_catpv(pig_cryptproto, pig_token);
			    *pig_cryptstr = 0;
			    sv_catpvn(pig_cryptproto, pig_cryptstr, pig_cryptlen);
			    break;
			}
			sv_catpv(pig_saneproto, pig_sanestr);
			sv_catpvn(pig_cryptproto, pig_cryptstr, pig_cryptlen);
			break;
		    }
		    sv_catpv(pig_saneproto, pig_sanestr);
		}
		if(pig_intstat) {
		    if(pig_intstat == ~0UL) {
		        char *pig_start = SvEND(pig_saneproto)-1;
			while(isALNUM(*pig_start) || isSPACE(*pig_start)) pig_start--;
			croak("Invalid type '%s' in '%s' prototype, stopped",
			      ++pig_start, SvPVX(pig_fname));
		    }
		    char pig_cryptstr[1] = { 0 };
		    if(pig_intstat & PIG_NUM_DOUBLE)
			*pig_cryptstr = (pig_intstat & PIG_NUM_LONG) ? PIG_PROTO_LDOUBLE : PIG_PROTO_DOUBLE;
		    else if(pig_intstat & PIG_NUM_FLOAT) *pig_cryptstr = PIG_PROTO_FLOAT;
		    else if(pig_intstat & PIG_NUM_LONG)  *pig_cryptstr = PIG_PROTO_LONG;
		    else if(pig_intstat & PIG_NUM_SHORT) *pig_cryptstr = PIG_PROTO_SHORT;
		    else if(pig_intstat & PIG_NUM_INT)   *pig_cryptstr = PIG_PROTO_INT;
		    if(*pig_cryptstr) sv_catpvn(pig_cryptproto, pig_cryptstr, 1);
		}
		SvREFCNT_dec(pig_tokensv);
		pig_constarg = FALSE;
	    }
	    (*SvPVX(pig_cryptproto))++;
	    while(*pig_argstart != ',' && pig_argstart < pig_argsend) pig_argstart++;
	    if(*pig_argstart == ',') {
		pig_argstart++;
		while(isSPACE(*pig_argstart)) pig_argstart++;
		if(pig_argstart < pig_argsend) sv_catpv(pig_saneproto, (char *)",");
		else {
		    pig_argstart--;
		    while(isSPACE(*pig_argstart)) pig_argstart--;	// force error
		}
	    }
	}
	sv_catpv(pig_saneproto, (char *)")");
    }

#if PIGDEBUG & PIGDEBUG_SIGSLOT
    {
	SV *ch = newSVpv("", 0);
	SV *pig_cryptstr = newSVpv("", 0);
	char *crypt = SvPVX(pig_cryptproto);
	for(int i = 0; i < SvCUR(pig_cryptproto); i++) {
	    if(!isALNUM(crypt[i])) {
		sv_catpv(pig_cryptstr, "\\");
		sv_setiv(ch, (IV)crypt[i]);
		sv_catpv(pig_cryptstr, SvPV(ch, n_a));
	    }
	    else sv_catpvn(pig_cryptstr, crypt+i, 1);
	}
	printf("pig_cryptlen of '%s' is %d\n", SvPVX(pig_protosv), SvCUR(pig_cryptproto));
	printf("pig_cryptstr is '%s'\n", SvPVX(pig_cryptstr));

	SvREFCNT_dec(pig_cryptstr);
	SvREFCNT_dec(ch);
    }
#endif

// Don't allocate new memory for an existing prototype

    if(!pig_hv_exists(pig_map_crypt, SvPVX(pig_saneproto)))
	pig_hv_store(pig_map_crypt, SvPVX(pig_saneproto), pig_cryptproto);
    else
        SvREFCNT_dec(pig_cryptproto);

    SvREFCNT_dec(pig_protosv);
    SvREFCNT_dec(pig_fname);
    SvREFCNT_dec(pig_args);

    return pig_saneproto;
}

PIG_EXPORT_TABLE(pigproto)
    PIG_EXPORT_FUNC(pig_map_proto)
    PIG_EXPORT_FUNC(pig_parse_proto)
PIG_EXPORT_ENDTABLE
