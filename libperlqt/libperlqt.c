/*
 * Useful routines needed globally in PerlQt.
 *
 * Copyright (C) 1997, Ashley Winters <jql@accessone.com>
 *
 * You may distribute under the terms of the LGPL as specified in the
 * README file
 */

#include <pqt.h>

HV *obj_check(SV *sv, const char *message) {
    HV *rv = (HV *)rv_check(sv, message);
    if(!SvOBJECT(rv) || SvTYPE(rv) != SVt_PVHV)
        croak(message);
    return rv;
}

SV *rv_check(SV *sv, const char *message) {
    if(!sv || !SvROK(sv)) croak(message);
    return SvRV(sv);
}

bool safe_hv_exists(HV *hv, const char *key) {
    return hv_exists(hv, (char *)key, strlen(key));
}

SV *safe_av_fetch(AV *av, I32 key, const char *message) {
    register SV **svp = av_fetch(av, key, 0);
    if(!svp) {
	if(message) warn(message);
	else warn("Could not fetch array element %d", key);
	return &sv_undef;
    }
    return *svp;
}

SV *safe_av_store(AV *av, I32 key, SV *value, const char *message) {
    register SV **svp = av_store(av, key, value);
    if(!svp) {
	if(message) warn(message);
	else warn("Could not save array element %d", key);
	return &sv_undef;
    }
    SvREFCNT_inc(value);
    return *svp;
}

SV *safe_hv_fetch(HV *hv, const char *key, const char *message) {
    register SV **svp = hv_fetch(hv, (char *)key, strlen(key), 0);
    if(!svp) {
	if(message) warn(message);
	else warn("Could not fetch hash key \"%s\"", key);
	return &sv_undef;
    }
    return *svp;
}

SV *safe_hv_store(HV *hv, const char *key, SV *value, const char *message) {
    register SV **svp = hv_store(hv, (char *)key, strlen(key), value, 0);
    if(!svp) {
	if(message) warn(message);
	else warn("Could not save hash key \"%s\"", key);
	return &sv_undef;
    }
    SvREFCNT_inc(value);
    return *svp;
}

AV *safe_gv_store(const char *name, AV *value) {
    register GV *gv = gv_fetchpv((char *)name, TRUE | GV_ADDMULTI, SVt_PVGV);
    SvREFCNT_inc(value);
    if(GvAV(gv)) SvREFCNT_dec(GvAV(gv));
    GvAV(gv) = value;
    return value;
}

CV *safe_gv_store(const char *name, CV *value) {
    register GV *gv = gv_fetchpv((char *)name, TRUE | GV_ADDMULTI, SVt_PVGV);
    SvREFCNT_inc(value);
    if(GvCV(gv)) SvREFCNT_dec(GvCV(gv));
    GvCV(gv) = value;
    return value;
}

HV *safe_gv_store(const char *name, HV *value) {
    register GV *gv = gv_fetchpv((char *)name, TRUE | GV_ADDMULTI, SVt_PVGV);
    SvREFCNT_inc(value);
    if(GvHV(gv)) SvREFCNT_dec(GvHV(gv));
    GvHV(gv) = value;
    return value;
}

SV *safe_gv_store(const char *name, SV *value) {
    register GV *gv = gv_fetchpv((char *)name, TRUE | GV_ADDMULTI, SVt_PVGV);
    SvREFCNT_inc(value);
    if(GvSV(gv)) SvREFCNT_dec(GvSV(gv));
    GvSV(gv) = value;
    return value;
}

char *pchar_pv(SV *sv, bool def) {
    if(!sv) sv = &sv_undef;
    if(!def && !SvOK(sv)) return 0;
//  else give em an uninitialized value warning. :)
    return SvPV(sv, na);
}

const char *pcchar_pv(SV *sv, bool def) {
    return pchar_pv(sv, def);
}

SV *pcchar_sv(const char *str) {
    return str ? newSVpv((char *)str, 0) : newSVsv(&sv_undef);
}