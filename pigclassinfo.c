#include "pig.h"
#include "pigperl.h"
#include "pigconstant.h"
#include "pigclassinfo.h"

PIG_DEFINE_VOID_FUNC_1(pig_load_classinfo, pig_classinfo *) {
    pig_classinfo *piginfo = pig0;
    while(piginfo->pigclassname) {
	const char *pigmap;

	pig_classinfo_store(piginfo->pigclassname, piginfo);
	pigmap = pig_map_class(piginfo->pigclassname);

	pig_load_constants(pigmap, piginfo->pigconstant);
	pig_load_methods(pigmap, piginfo->pigmethodlist);

	piginfo++;
    }

    piginfo = pig0;
    while(piginfo->pigclassname) {
	pig_load_isa(pig_map_class(piginfo->pigclassname), piginfo->pigisa);
	piginfo++;
    }
}

PIG_DEFINE_VOID_FUNC_2(pig_load_isa, const char *, const char **) {
    const char *pigISA = "::ISA";
    char *pigavname;
    AV *pigISAav;

    if(!pig0 || !pig1) return;

    pigavname = new char [strlen(pig0) + strlen(pigISA) + 1];
    strcpy(pigavname, pig0);
    strcat(pigavname, pigISA);
    pigISAav = perl_get_av(pigavname, TRUE);
//    delete [] pigavname;

    while(*pig1) {
        const char *pigmap = pig_map_class(*pig1);
        av_push(pigISAav, newSVpv((char *)pigmap, 0));
	PIG_DEBUG_INIT(("push @%s::ISA, \"%s\";\n", pig0, pigmap));
	pig1++;
    }

    delete [] pigavname;
}

PIG_DEFINE_VOID_FUNC_2(pig_load_methods, const char *, pig_method *) {
    size_t pigclasslen = 0;
    size_t pigmethodlen = 0;
    char *pigmethod = 0;
    char *pigm = 0;

    if(!pig0 || !pig1) return;

    pigclasslen = strlen(pig0) + 3;

    while(pig1->pigmethodname) {
        if(pigmethodlen < (pigclasslen + strlen(pig1->pigmethodname))) {
	    pigmethodlen = pigclasslen + strlen(pig1->pigmethodname) + 64;
	    if(pigmethod) delete [] pigmethod;
	    pigmethod = new char [pigmethodlen];
	    strcpy(pigmethod, pig0);
	    strcat(pigmethod, "::");
	    pigm = pigmethod + strlen(pigmethod);
	}

	strcpy(pigm, pig1->pigmethodname);
	PIG_DEBUG_INIT(("method &%s::%s = %p\n", pig0, pig1->pigmethodname, pig1->pigmethodfptr));
	newXS(pigmethod, (XS((*)))pig1->pigmethodfptr, __FILE__);
        pig1++;
    }

    if(pigmethod) delete [] pigmethod;
}


PIG_DEFINE_VOID_FUNC_2(pig_classinfo_store, const char *, struct pig_classinfo *) {
    char *pigclass = (char *)pig1->pigclassname;
    char *pigalias = (char *)pig1->pigalias;
    PIG_DEBUG_INIT(("map $class{\"%s\"} = \"%s\"\n", pigclass, pigalias));
    pig0 = pig0;    // What is this for?
    if(!pig_classinfo_hv) pig_classinfo_hv = newHV();
    if(!pig_classmap_hv) pig_classmap_hv = newHV();
    if(!pig_classunmap_hv) pig_classunmap_hv = newHV();
    hv_store(pig_classinfo_hv, pigclass, strlen(pigclass), newSViv((IV)pig1), 0);
    hv_store(pig_classmap_hv, pigclass, strlen(pigclass), newSVpv(pigalias, 0), 0);
    hv_store(pig_classunmap_hv, pigalias, strlen(pigalias), newSVpv(pigclass, 0), 0);
}

PIG_DEFINE_FUNC_1(struct pig_classinfo *, pig_classinfo_fetch, const char *) {
    if(!pig_classinfo_hv) return 0;
    SV **pigsvp = hv_fetch(pig_classinfo_hv, (char *)pig0, strlen(pig0), FALSE);
    if(!pigsvp || !SvOK(*pigsvp)) return 0;
    return (pig_classinfo *)SvIV(*pigsvp);
}

PIG_DEFINE_FUNC_1(const char *, pig_map_class, const char *) {
    STRLEN n_a;
    if(!pig_classmap_hv) return pig0;
    SV **pigsvp = hv_fetch(pig_classmap_hv, (char *)pig0, strlen(pig0), FALSE);
    if(!pigsvp || !SvOK(*pigsvp)) return pig0;
    return SvPV(*pigsvp, n_a);
}

PIG_DEFINE_FUNC_1(HV *, pig_map_class_stash, const char *) {
    return gv_stashpv((char *)pig_map_class(pig0), TRUE);
}

PIG_DEFINE_FUNC_1(const char *, pig_unmap_class, const char *) {
    STRLEN n_a;
    if(!pig_classunmap_hv) return pig0;
    SV **pigsvp = hv_fetch(pig_classunmap_hv, (char *)pig0, strlen(pig0), FALSE);
    if(!pigsvp || !SvOK(*pigsvp)) return pig0;
    return SvPV(*pigsvp, n_a);
}

#undef pig_classinfo_hv
#undef pig_classmap_hv
#undef pig_classunmap_hv

PIG_DEFINE_VARIABLE(HV *, pig_classinfo_hv) = 0;
PIG_DEFINE_VARIABLE(HV *, pig_classmap_hv) = 0;
PIG_DEFINE_VARIABLE(HV *, pig_classunmap_hv) = 0;

PIG_EXPORT_TABLE(pigclassinfo)
    PIG_EXPORT_FUNC(pig_load_classinfo)
    PIG_EXPORT_FUNC(pig_load_isa)
    PIG_EXPORT_FUNC(pig_load_methods)
    PIG_EXPORT_FUNC(pig_classinfo_store)
    PIG_EXPORT_FUNC(pig_classinfo_fetch)
    PIG_EXPORT_FUNC(pig_map_class)
    PIG_EXPORT_FUNC(pig_map_class_stash)
    PIG_EXPORT_FUNC(pig_unmap_class)
    PIG_EXPORT_VARIABLE(pig_classinfo_hv)
    PIG_EXPORT_VARIABLE(pig_classmap_hv)
    PIG_EXPORT_VARIABLE(pig_classunmap_hv)
PIG_EXPORT_ENDTABLE
