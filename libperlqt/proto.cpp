#define PQT_NUM_SHORT		0x0001
#define PQT_NUM_INT		0x0002
#define PQT_NUM_LONG		0x0004
#define PQT_NUM_LONG_LONG	0x0008
#define PQT_NUM_SIGNED		0x0010
#define PQT_NUM_UNSIGNED	0x0020
#define PQT_NUM_FLOAT		0x0100
#define PQT_NUM_DOUBLE		0x0200

bool int_set(unsigned long &flags, unsigned long flag) {
    bool ret = (flags != ~0UL);

    switch(flag) {
    case PQT_NUM_LONG:
    case PQT_NUM_SHORT:
	if(flags & 0x307) ret = FALSE; break;
    case PQT_NUM_INT:
	if(flags & 0x302) ret = FALSE; break;
    case PQT_NUM_SIGNED:
    case PQT_NUM_UNSIGNED:
	if(flags & 0x330) ret = FALSE; break;
    case PQT_NUM_FLOAT:
	if(flags & 0x237) ret = FALSE; break;
    case PQT_NUM_DOUBLE:
	if(flags & 0x133) ret = FALSE; break;
    default:
	ret = FALSE;
    }

    if(ret) flags |= flag;
    else flags = ~0UL;
    
    return ret;
}

HV *Crypt;

SV *parse_proto(SV *origproto) {	// 75 lines of Perl, to 200+ lines of C
    if(hv_exists(Crypt, SvPV(origproto, na), SvCUR(origproto)))
	return newSVsv(origproto);	// Sane optimization

    SV *protosv;
    SV *fname, *args;
    SV *cryptproto = newSVpv("\0", 1);	// beyond this point, there be dragons
    SV *saneproto = newSVpv("", 0);
    bool constarg = FALSE;		// double-check ourselves

// A simple removal of whitespace and copy to protosv of our favorite
// prototype bundle of joy

    {
	if(!SvLEN(origproto))
	    croak("You gotta at least put SOMETHING in the prototype! "
		  "Your code sucks");
	char *protostr = SvPV(origproto, na);
	char *protoend = SvEND(origproto)-1;

	while(isSPACE(*protostr)) protostr++;
	while(isSPACE(*protoend) && protoend > protostr) protoend--;
	protosv = newSVpv(protostr, (protoend + 1) - protostr);
    }

// This is a nice place to extract fname. Might as well do a few sanity
// checks while we're in the area

    {
	char *protostr = SvPVX(protosv);
	char *fnamend = protostr;
	char *openparen;

	while(isALNUM(*fnamend)) fnamend++;		// fname()
	openparen = fnamend;
	while(isSPACE(*openparen)) openparen++;		// fname ()

	if(fnamend == protostr)
	    croak("Missing function-name in prototype '%s'", protostr);
	if(!*openparen)
	    croak("Missing argument prototype in '%s'", protostr);

	fname = newSVpv(protostr, fnamend - protostr);

	char len[1] = { SvCUR(fname) + 1 };
	sv_catpvn(cryptproto, len, 1);
	sv_catpvn(cryptproto, SvPVX(fname), SvCUR(fname));
	sv_catpvn(cryptproto, "\0", 1);

	sv_catsv(saneproto, fname);
	sv_catpv(saneproto, "(");

	if(*openparen != '(')	// bad news
	    croak("The argument-list for '%s' must begin with "
		  "an opening parenthesis", SvPVX(fname));
	if(*(SvEND(protosv)-1) != ')')
	    croak("The argument-list for '%s' must end with "
		  "a closing parenthesis", SvPVX(fname));

	args = newSVpv(openparen, SvEND(protosv) - openparen);
    }

// Here we get to play 'fun with args'. A game which looks kinda
// like a tokenizer. Oh well.

    {
	char *argstart = SvPVX(args)+1;		// skip (
	char *argsend  = SvEND(args)-1;		// skip )
	while(isSPACE(*argstart)) argstart++;	// ditch whitespace
	while(isSPACE(*argsend))  argsend--;
	while(argstart < argsend) {
	    if(!isALNUM(*argstart)) {
		char sanestr[] = "SV*";		// copy, not pointer (I hope)
		char cryptstr[1] = { 0 };

		if(*argstart == '.' && *++argstart == '.' &&
		   *++argstart == '.') {
		    *sanestr = 'A';		// AV*
		    *cryptstr = 14;		// ...
		}
		else if(*argstart == '$')
		    *cryptstr = (*++argstart == '$') ? 11 : 10;
		else if(*argstart == '@' || *argstart == '%') {
		    if(*(argstart+1) != '$')
			croak("This version of PerlQt is not capable of "
			      "accepting non-scalars as prototype arguments");
		    *cryptstr = (*argstart == '@') ? 13 : 12;
		}
		else croak("Fatal error while parsing '%s': "
			   "Invalid character near '%s'",
			   SvPVX(protosv), argstart);
		sv_catpv(saneproto, sanestr);
		sv_catpvn(cryptproto, cryptstr, 1);
	    }
	    else {
		SV *tokensv = newSVpv("", 0);
		unsigned long intstat = 0;
		while(isALNUM(*argstart)) {
		    char *token = NULL, *tokend = argstart;
		    char cryptstr[] = { -1 }, *sanestr;
		    int cryptlen = 1;

		    while(isALNUM(*tokend)) tokend++;
		    sv_setpvn(tokensv, argstart, tokend-argstart);
		    while(isSPACE(*tokend)) tokend++;
		    argstart = tokend;

		    token = SvPVX(tokensv);
		    sanestr = token;		// default to the token

		    if(strEQ(token, "const")) {	// const is a toughie
			if(constarg == TRUE)
			    croak("Multiple const declarations for an "
				  "argument in '%s', try again",
				  SvPVX(fname));
			if(intstat)
			    croak("const is a reserved word and must be "
				  "the first in the type identification");
			constarg = TRUE;
			sanestr = "const ";
			*cryptstr = 0;

			sv_catpv(saneproto, sanestr);
			sv_catpvn(cryptproto, cryptstr, cryptlen);
			continue;
		    }

		    if(intstat) sv_catpv(saneproto, " ");

		    if(strEQ(token, "int")) int_set(intstat, PQT_NUM_INT);
		    else if(strEQ(token, "long")) int_set(intstat, PQT_NUM_LONG);
		    else if(strEQ(token, "short")) int_set(intstat, PQT_NUM_SHORT);
		    else if(strEQ(token, "signed"))
			int_set(intstat, PQT_NUM_SIGNED);
		    else if(strEQ(token, "unsigned"))
			int_set(intstat, PQT_NUM_UNSIGNED);
		    else if(strEQ(token, "float"))
			int_set(intstat, PQT_NUM_FLOAT);
		    else if(strEQ(token, "double"))
			int_set(intstat, PQT_NUM_DOUBLE);
		    else if(intstat) {
			SvCUR_set(saneproto, SvCUR(saneproto)-1);  // chop
			break;
		    }
		    else {
		        if(strEQ(token, "bool")) *cryptstr = 8;
		        else if(strEQ(token, "string")) {
			    *cryptstr = 9;
			    sanestr = "char*";
			}
			else {
			    sv_catpv(saneproto, token);	// object*
			    sv_catpv(saneproto, "*");

			    *cryptstr = 1;		// \1\lenObject\0
			    sv_catpvn(cryptproto, cryptstr, cryptlen);
			    *cryptstr = SvCUR(tokensv) + 1;
			    sv_catpvn(cryptproto, cryptstr, cryptlen);
			    sv_catpv(cryptproto, token);
			    *cryptstr = 0;
			    sv_catpvn(cryptproto, cryptstr, cryptlen);
			    break;
			}
			sv_catpv(saneproto, sanestr);
			sv_catpvn(cryptproto, cryptstr, cryptlen);
			break;
		    }
		    sv_catpv(saneproto, sanestr);
		}
		if(intstat) {
		    if(intstat == ~0UL) {
			char *start = SvEND(saneproto)-1;
			while(isALNUM(*start) || isSPACE(*start)) start--;
			croak("Invalid type '%s' in '%s' prototype, stopped",
			      ++start, SvPVX(fname));
		    }
		    char cryptstr[1] = { 0 };
		    if(intstat & PQT_NUM_DOUBLE)
			*cryptstr = (intstat & PQT_NUM_LONG) ? 7 : 6;
		    else if(intstat & PQT_NUM_FLOAT) *cryptstr = 5;
		    else if(intstat & PQT_NUM_LONG)  *cryptstr = 2;
		    else if(intstat & PQT_NUM_SHORT) *cryptstr = 3;
		    else if(intstat & PQT_NUM_INT)   *cryptstr = 4;
		    if(*cryptstr) sv_catpvn(cryptproto, cryptstr, 1);
		}
		SvREFCNT_dec(tokensv);
		constarg = FALSE;
	    }
	    (*SvPVX(cryptproto))++;
	    while(*argstart != ',' && argstart < argsend) argstart++;
	    if(*argstart == ',') {
		argstart++;
		while(isSPACE(*argstart)) argstart++;
		if(argstart < argsend) sv_catpv(saneproto, ",");
		else {
		    argstart--;
		    while(isSPACE(*argstart)) argstart--;	// force error
		}
	    }
	}
	sv_catpv(saneproto, ")");
    }
/*
    {
	SV *ch = newSVpv("", 0);
	SV *cryptstr = newSVpv("", 0);
	char *crypt = SvPVX(cryptproto);
	for(int i = 0; i < SvCUR(cryptproto); i++) {
	    if(!isALNUM(crypt[i])) {
		sv_catpv(cryptstr, "\\");
		sv_setiv(ch, (IV)crypt[i]);
		sv_catpv(cryptstr, SvPV(ch, na));
	    }
	    else sv_catpvn(cryptstr, crypt+i, 1);
	}
	printf("cryptlen of '%s' is %d\n", SvPVX(protosv), SvCUR(cryptproto));
	printf("cryptstr is '%s'\n", SvPVX(cryptstr));
    }
*/

// Don't allocate new memory for an existing prototype

    if(!hv_exists(Crypt, SvPVX(saneproto), SvCUR(saneproto)))
	safe_hv_store(Crypt, SvPVX(saneproto), cryptproto);

    SvREFCNT_dec(protosv);
    SvREFCNT_dec(fname);
    SvREFCNT_dec(args);

    return saneproto;
}

SV *reverse_proto(SV *p) {
    return safe_hv_fetch(Crypt, SvPV(p, na), "Invalid prototype");
}

