/* rscale.f -- translated by f2c (version 20100827).
   You must link the resulting object file with libf2c:
	on Microsoft Windows system, link with libf2c.lib;
	on Linux or Unix systems, link with .../path/to/libf2c.a -lm
	or, if you install libf2c.a in a standard place, with -lf2c -lm
	-- in that order, at the end of the command line, as in
		cc *.o -lf2c -lm
	Source for libf2c is in /netlib/f2c/libf2c.zip, e.g.,

		http://www.netlib.org/f2c/libf2c.zip
*/

#include "f2c.h"

/* Common Block Declarations */

struct {
    integer ilast, idebug, itrack, ishort, imilne, imodpt, istor, iowr;
} luout_;

#define luout_1 luout_

struct {
    doublereal rescal[200]	/* was [4][50] */;
    integer nmodls[50], iresca[50];
    logical lfirst[50];
    integer numrun;
} ckind_;

#define ckind_1 ckind_

struct {
    doublereal xenv, zenv, zenvm, amuenv, fxenv[12], xnew, znew, stotal, senv;
} comp_;

#define comp_1 comp_

struct {
    doublereal clsun, clsunl, clnsun, cmsun, cmsunl, crsun, crsunl, cmbol;
} const_;

#define const_1 const_

struct {
    doublereal cln, clni, c4pi, c4pil, c4pi3l, cc13, cc23, cpi;
} const1_;

#define const1_1 const1_

struct {
    doublereal xenv0, zenv0;
} label_;

#define label_1 label_

struct {
    doublereal xnewcp;
    integer inewcp;
    logical lnewcp, lrel;
    char anewcp[3];
} newcmp_;

#define newcmp_1 newcmp_

struct {
    doublereal rsclzc[50], rsclzm1[50], rsclzm2[50];
    integer iolaol2, ioopal2, nk2;
    logical lzramp;
    char flaol2[256], fopal2[256];
} zramp_;

#define zramp_1 zramp_

/* Table of constant values */

static integer c__1 = 1;
static doublereal c_b26 = 10.;
static integer c__9 = 9;
static integer c__5 = 5;

/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */
/* RSCALE */
/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */
/* Subroutine */ int rscale_(doublereal *hl, doublereal *hcomp, doublereal *
	hs, doublereal *hstot, integer *m, integer *nk, doublereal *smass, 
	logical *lc)
{
    /* Format strings */
    static char fmt_1000[] = "(1x,\002ERROR IN SUBROUTINE RSCALE\002/1x,\002"
	    "RESCALING OF\002,a4,1x,\002IN KIND CARD #\002,i3,1x,\002FAILED -"
	    " DESIRED COMP\002,f9.6/1x,\002GREATER THAN UNITY.  X NOT RESCALED"
	    "\002)";
    static char fmt_63[] = "(1x,\002HB-OLD MASSES: CORE \002,f9.6,\002 SHE"
	    "LL \002,f9.6,\002 ENV \002,f9.6,\002 TOTAL\002,f9.6)";
    static char fmt_69[] = "(1x,\002ERROR IN SUBROUTINE RSCALE\002/1x,\002DE"
	    "SIRED NEW ENVELOPE MASS LESS THAN ZERO\002/1x,\002OLD ENVELOPE M"
	    "ASS \002,1pe9.2,\002 NEW ENVELOPE \002,e9.2,\002 NEW AND OLD TOT"
	    "AL MASS \002,2e10.2)";
    static char fmt_71[] = "(1x,\002ERROR IN SUBROUTINE RSCALE\002/1x,\002NE"
	    "W ENVELOPE MASS LESS THAN ZERO BECAUSE OF CORE\002,\002 RESCALING"
	    "\002/1x,\002OLD ENVELOPE MASS \002,1pe10.2,\002 NEW ENVELOPE "
	    "\002,e10.2,\002 NEW AND OLD CORE MASS \002,2e10.2)";
    static char fmt_101[] = "(1x,\002HB-RESCALED MASSES: CORE \002,f9.6,\002"
	    " SHELL \002,f9.6,\002 ENV \002,f9.6,\002 TOTAL \002,f9.6)";

    /* System generated locals */
    integer i__1;
    doublereal d__1, d__2;

    /* Builtin functions */
    /* Subroutine */ int s_copy(char *, char *, ftnlen, ftnlen);
    integer s_wsfe(cilist *), do_fio(integer *, char *, ftnlen), e_wsfe(void);
    double exp(doublereal), d_lg10(doublereal *), pow_dd(doublereal *, 
	    doublereal *);
    integer s_wsle(cilist *), do_lio(integer *, integer *, char *, ftnlen), 
	    e_wsle(void);
    /* Subroutine */ int s_stop(char *, ftnlen);

    /* Local variables */
    static doublereal envtotal;
    static integer i__, j, i1;
    static doublereal fs, zp, dcor, denv, delz;
    static integer jenv;
    static doublereal temp, shlp;
    static char acomp[3];
    static integer jxbeg, jcore;
    static doublereal xfact, zfact;
    static integer jxend, jxmid;
    static doublereal shift, slope, hstot1;
    extern /* Subroutine */ int findsh_(doublereal *, doublereal *, logical *,
	     integer *, integer *, integer *, integer *, integer *, integer *,
	     logical *);
    static doublereal chkenv, corold;
    static logical lshell;
    static doublereal shlold, envold, cornew, envnew, shlnew, envold2, 
	    sfactor;

    /* Fortran I/O blocks */
    static cilist io___5 = { 0, 0, 0, fmt_1000, 0 };
    static cilist io___9 = { 0, 0, 0, fmt_1000, 0 };
    static cilist io___10 = { 0, 0, 0, fmt_1000, 0 };
    static cilist io___24 = { 0, 0, 0, fmt_63, 0 };
    static cilist io___26 = { 0, 6, 0, 0, 0 };
    static cilist io___27 = { 0, 6, 0, 0, 0 };
    static cilist io___28 = { 0, 6, 0, 0, 0 };
    static cilist io___29 = { 0, 0, 0, fmt_69, 0 };
    static cilist io___31 = { 0, 6, 0, 0, 0 };
    static cilist io___32 = { 0, 6, 0, 0, 0 };
    static cilist io___33 = { 0, 6, 0, 0, 0 };
    static cilist io___35 = { 0, 0, 0, fmt_69, 0 };
    static cilist io___38 = { 0, 0, 0, fmt_71, 0 };
    static cilist io___43 = { 0, 0, 0, fmt_101, 0 };


/* DBG 5/94 Added rescaling of Z in core ZRAMP stuff. */
/* MHP 5/91 COMMON BLOCK ADDED TO FIX CORE RESCALING. */
/* DBG 5/94 ZRAMP stuff. */
/* ************ */
/*      write(*,*) */
/*      write(*,*)'Entering rscale ',HSTOT-HS(M) */
/* ************ */
    /* Parameter adjustments */
    --lc;
    --hs;
    hcomp -= 16;
    --hl;

    /* Function Body */
    if (ckind_1.rescal[(*nk << 2) - 3] > 0.) {
/*  RESCALE X BY MULTIPLYING ALL SHELL X VALUES BY THE RATIO (XNEW/XOLD) */
/*  WHERE XOLD = OLD SURFACE X VALUE */
/*  THIS METHOD OK FOR BOTH HORIZONTAL BRANCH AND MAIN SEQUENCE STARS */
	if (ckind_1.rescal[(*nk << 2) - 3] <= 1.) {
	    xfact = ckind_1.rescal[(*nk << 2) - 3] / max(comp_1.xnew,1e-20);
	    i__1 = *m;
	    for (i__ = 1; i__ <= i__1; ++i__) {
/* Computing MIN */
		d__1 = ckind_1.rescal[(*nk << 2) - 3], d__2 = hcomp[i__ * 15 
			+ 1] * xfact;
		hcomp[i__ * 15 + 1] = min(d__1,d__2);
/* L10: */
	    }
	    comp_1.xnew = ckind_1.rescal[(*nk << 2) - 3];
	    label_1.xenv0 = ckind_1.rescal[(*nk << 2) - 3];
/* DBG 4/95 BUG FIX XENV IS USED IN SOME ROUTINES AND NOT XENV0 SO CHANGE */
/*     XENV WHENEVER X IS CHANGED. */
/* MHP 7/99 THIS IS NOT A BUG, IT IS NECESSARY. */
/* XENV IS USED TO SET THE INITIAL MU FOR THE YALE EQUATION OF STATE, */
/* AND IT SHOULD NOT BE CHANGED AFTER THE FIRST RUN. */
/*            XENV = XENV0 */
	} else {
/*  DESIRED X >100%; X NOT CHANGED */
	    s_copy(acomp, " X ", (ftnlen)3, (ftnlen)3);
	    i1 = 2;
	    io___5.ciunit = luout_1.ishort;
	    s_wsfe(&io___5);
	    do_fio(&c__1, acomp, (ftnlen)3);
	    do_fio(&c__1, (char *)&(*nk), (ftnlen)sizeof(integer));
	    do_fio(&c__1, (char *)&ckind_1.rescal[i1 + (*nk << 2) - 5], (
		    ftnlen)sizeof(doublereal));
	    e_wsfe();
	}
    }
    if (ckind_1.rescal[(*nk << 2) - 2] >= 0.) {
/*  RESCALE Z BY ADDING (RESCAL(3,NK)-OLD Z) TO EACH Z VALUE IN THE STAR */
/*  THE CNO CYCLE ELEMENTS AND HE3 ARE MULTIPLIED BY THE RATIO OF THE */
/*  DESIRED NEW Z TO THE OLD Z - LIGHT ELEMENT ABUNDANCES ARE LEFT ALONE */
	if (ckind_1.rescal[(*nk << 2) - 2] <= 1.) {
	    delz = ckind_1.rescal[(*nk << 2) - 2] - comp_1.znew;
	    i__1 = *m;
	    for (j = 1; j <= i__1; ++j) {
/* Computing MAX */
		d__1 = 0., d__2 = hcomp[j * 15 + 3] + delz;
		zfact = max(d__1,d__2) / (hcomp[j * 15 + 3] + 1e-30);
/* Computing MAX */
		d__1 = 0., d__2 = hcomp[j * 15 + 3] + delz;
		hcomp[j * 15 + 3] = max(d__1,d__2);
		for (i__ = 5; i__ <= 11; ++i__) {
		    hcomp[i__ + j * 15] *= zfact;
/* L20: */
		}
/* L30: */
	    }
	    comp_1.znew = ckind_1.rescal[(*nk << 2) - 2];
	    label_1.zenv0 = ckind_1.rescal[(*nk << 2) - 2];
/* DBG 4/95 BUG FIX ZENV IS USED IN MANY ROUTINES AND NOT ZENV0 SO CHANGE */
/*     ZENV WHENEVER Z IS CHANGED. */
	    comp_1.zenv = label_1.zenv0;
	} else {
/*  DESIRED Z >100%; Z NOT CHANGED */
	    s_copy(acomp, " Z ", (ftnlen)3, (ftnlen)3);
	    i1 = 3;
	    io___9.ciunit = luout_1.ishort;
	    s_wsfe(&io___9);
	    do_fio(&c__1, (char *)&(*nk), (ftnlen)sizeof(integer));
	    do_fio(&c__1, acomp, (ftnlen)3);
	    do_fio(&c__1, (char *)&ckind_1.rescal[i1 + (*nk << 2) - 5], (
		    ftnlen)sizeof(doublereal));
	    e_wsfe();
	}
    }
    if (hcomp[16] > 1e-10) {
/* ************ */
/*      write(*,*)'Entering MS change ',HSTOT-HS(M) */
/* ************ */
/*  MAIN SEQUENCE RESCALING - MASS AND SINGLE ELEMENT. */
	if (newcmp_1.lnewcp && newcmp_1.xnewcp >= 0.) {
/*  RESCALE THE ABUNDANCE OF ONE ELEMENT OTHER THAN X,Y,Z */
/*  JNEWCP = INDEX OF ELEMENT TO BE CHANGED IN MATRIX HCOMP */
/*  IF LREL = T, ABUNDANCE IS RELATIVE TO SURFACE HYDROGEN ABUNDANCE */
/*  ON A LOGARITHMIC SCALE WHERE X ABUNDANCE = 12.0 */
/*  E.G. AN ABUNDANCE OF 3.0 MEANS 1.0D-9* SURFACE H ABUNDANCE */
	    if (newcmp_1.lrel) {
		newcmp_1.xnewcp = exp(const1_1.cln * (newcmp_1.xnewcp - 12.)) 
			* hcomp[*m * 15 + 1];
	    }
	    if (newcmp_1.xnewcp < 1.) {
		i__1 = *m;
		for (i__ = 1; i__ <= i__1; ++i__) {
		    hcomp[newcmp_1.inewcp + i__ * 15] = newcmp_1.xnewcp;
/* L35: */
		}
	    } else {
/*  ERROR - RESCALED ABUNDANCE >100% - ABUNDANCE NOT CHANGED */
		s_copy(acomp, newcmp_1.anewcp, (ftnlen)3, (ftnlen)3);
		io___10.ciunit = luout_1.ishort;
		s_wsfe(&io___10);
		do_fio(&c__1, (char *)&(*nk), (ftnlen)sizeof(integer));
		do_fio(&c__1, acomp, (ftnlen)3);
		do_fio(&c__1, (char *)&newcmp_1.xnewcp, (ftnlen)sizeof(
			doublereal));
		e_wsfe();
	    }
	}
/*  RESCALE STAR MASS BY MULTIPLYING ALL MASS POINTS IN THE STAR BY */
/*  A SCALE FACTOR(MNEW/MOLD) WHILE LEAVING ALL OTHER LOCAL VARIABLES */
/*  UNCHANGED. */
	if (ckind_1.rescal[(*nk << 2) - 4] > 0.) {
	    d__1 = ckind_1.rescal[(*nk << 2) - 4] / *smass;
	    hstot1 = d_lg10(&d__1);
	    *hstot += hstot1;
	    *smass = ckind_1.rescal[(*nk << 2) - 4];
	    comp_1.stotal = *hstot;
	    i__1 = *m;
	    for (i__ = 1; i__ <= i__1; ++i__) {
		hs[i__] += hstot1;
/* L40: */
	    }
	}
    } else {
/*  HORIZONTAL BRANCH RESCALING;CORE MASS AND TOTAL MASS. */
/*  FOR TOTAL MASS,TREAT AS MAIN SEQUENCE BUT ONLY CHANGE */
/*  THE MASS POINTS OUTSIDE THE H-BURNING SHELL; */
/*  FOR CORE MASS CHANGE THE POINTS INSIDE THE H-BURNING */
/*  SHELL AND CORRESPONDINGLY REDUCE/INCREASE THE MASS OUTSIDE */
/*  THE SHELL. */
/* ************ */
/*      write(*,*)'Entering HB scale ',HSTOT-HS(M) */
/* ************ */
	if (ckind_1.rescal[(*nk << 2) - 4] > 0. || ckind_1.rescal[(*nk << 2) 
		- 1] > 0.) {
/*  RESCALE MASS AND/OR CORE MASS */
/*  FIND H-BURNING SHELL. */

/* ************* Added call to FINDSHELL (gn - 10/05)************** */
	    findsh_(&hcomp[16], &hl[1], &lc[1], m, &jcore, &jenv, &jxbeg, &
		    jxend, &jxmid, &lshell);
/* **************************************************************** */
/* FIND CORE, ENVELOPE, AND H-BURNING SHELL MASSES. */
	    corold = exp(const1_1.cln * hs[jxbeg - 1]) / const_1.cmsun;
	    envold = (exp(const1_1.cln * *hstot) - exp(const1_1.cln * hs[
		    jxend])) / const_1.cmsun;
	    envold2 = (exp(const1_1.cln * hs[*m]) - exp(const1_1.cln * hs[
		    jxend])) / const_1.cmsun;
	    shlold = (exp(const1_1.cln * hs[jxend]) - exp(const1_1.cln * hs[
		    jxbeg - 1])) / const_1.cmsun;
	    denv = 0.;
	    dcor = 0.;
	    io___24.ciunit = luout_1.ishort;
	    s_wsfe(&io___24);
	    do_fio(&c__1, (char *)&corold, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&shlold, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&envold, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&(*smass), (ftnlen)sizeof(doublereal));
	    e_wsfe();
	}
	if (ckind_1.rescal[(*nk << 2) - 4] > 0.) {
/* MASS RESCALING : ADD OR SUBTRACT MASS FROM THE ENVELOPE OUTSIDE */
/* THE H-BURNING SHELL (ONLY). */

/* ENSURE THAT THE NEW ENVELOPE MASS IS POSITIVE. */
	    denv = ckind_1.rescal[(*nk << 2) - 4] - *smass;
	    envnew = envold + denv;
/* ** Reduce either total mass outside core OR the standard envelope only *** */
	    if (pow_dd(&c_b26, hstot) / const_1.cmsun - corold >= .01) {
/* ************ */
		s_wsle(&io___26);
		do_lio(&c__9, &c__1, "Entering old method ", (ftnlen)20);
		d__1 = (pow_dd(&c_b26, hstot) - pow_dd(&c_b26, &hs[*m])) / (
			pow_dd(&c_b26, &hs[*m]) - pow_dd(&c_b26, &hs[jxbeg - 
			1]));
		do_lio(&c__5, &c__1, (char *)&d__1, (ftnlen)sizeof(doublereal)
			);
		e_wsle();
		s_wsle(&io___27);
		do_lio(&c__9, &c__1, "SENV ", (ftnlen)5);
		d__1 = pow_dd(&c_b26, hstot) - pow_dd(&c_b26, &hs[*m]);
		do_lio(&c__5, &c__1, (char *)&d__1, (ftnlen)sizeof(doublereal)
			);
		e_wsle();
		s_wsle(&io___28);
		do_lio(&c__9, &c__1, "Envelope ", (ftnlen)9);
		d__1 = pow_dd(&c_b26, &hs[*m]) - pow_dd(&c_b26, &hs[jxbeg - 1]
			);
		do_lio(&c__5, &c__1, (char *)&d__1, (ftnlen)sizeof(doublereal)
			);
		e_wsle();
/* ************ */
/* ************************************************************************** */
/*               write(*,*)JXBEG-1,JXMID,JXEND,M */
		if (envnew <= 0.) {
		    io___29.ciunit = luout_1.ishort;
		    s_wsfe(&io___29);
		    do_fio(&c__1, (char *)&envold, (ftnlen)sizeof(doublereal))
			    ;
		    d__1 = envold + denv;
		    do_fio(&c__1, (char *)&d__1, (ftnlen)sizeof(doublereal));
		    do_fio(&c__1, (char *)&ckind_1.rescal[(*nk << 2) - 4], (
			    ftnlen)sizeof(doublereal));
		    do_fio(&c__1, (char *)&(*smass), (ftnlen)sizeof(
			    doublereal));
		    e_wsfe();
		    s_stop("", (ftnlen)0);
		}
/* ***** Calculate scale factor for mass rescaling ***** */
/*            HSTOT1 = DLOG10(RESCAL(1,NK)/SMASS) */
		sfactor = (ckind_1.rescal[(*nk << 2) - 4] - exp(const1_1.cln *
			 hs[jxend]) / const_1.cmsun) / (*smass - exp(
			const1_1.cln * hs[jxend]) / const_1.cmsun);
/* ***************************************************** */
/*            HSTOT = HSTOT + HSTOT1 */
		d__1 = pow_dd(&c_b26, &hs[jxend]) + sfactor * (pow_dd(&c_b26, 
			hstot) - pow_dd(&c_b26, &hs[jxend]));
		*hstot = d_lg10(&d__1);
		*smass = ckind_1.rescal[(*nk << 2) - 4];
		comp_1.stotal = *hstot;
		i__1 = *m;
		for (i__ = jxend + 1; i__ <= i__1; ++i__) {
		    d__1 = pow_dd(&c_b26, &hs[jxend]) + sfactor * (pow_dd(&
			    c_b26, &hs[i__]) - pow_dd(&c_b26, &hs[jxend]));
		    hs[i__] = d_lg10(&d__1);
/* L70: */
		}
		envold = envnew;
/* ***** */
/*            write(*,*)'Mass difference ',DENV */
/*            write(*,*)'HSTOT1 ',HSTOT1 */
/*            write(*,*)'SFACTOR ',DLOG10(SFACTOR) */
/* ************ */
/*      write(*,*)'leaving old method ',HSTOT-HS(M) */
/* ************ */
	    } else {
/* ************ */
		s_wsle(&io___31);
		do_lio(&c__9, &c__1, "Entering new method ", (ftnlen)20);
		d__1 = (pow_dd(&c_b26, hstot) - pow_dd(&c_b26, &hs[*m])) / (
			pow_dd(&c_b26, &hs[*m]) - pow_dd(&c_b26, &hs[jxbeg - 
			1]));
		do_lio(&c__5, &c__1, (char *)&d__1, (ftnlen)sizeof(doublereal)
			);
		e_wsle();
		s_wsle(&io___32);
		do_lio(&c__9, &c__1, "SENV ", (ftnlen)5);
		d__1 = pow_dd(&c_b26, hstot) - pow_dd(&c_b26, &hs[*m]);
		do_lio(&c__5, &c__1, (char *)&d__1, (ftnlen)sizeof(doublereal)
			);
		e_wsle();
		s_wsle(&io___33);
		do_lio(&c__9, &c__1, "Envelope ", (ftnlen)9);
		d__1 = pow_dd(&c_b26, &hs[*m]) - pow_dd(&c_b26, &hs[jxbeg - 1]
			);
		do_lio(&c__5, &c__1, (char *)&d__1, (ftnlen)sizeof(doublereal)
			);
		e_wsle();
/* ************ */
/*           *** print debug info *** */
/*            write(*,*)JXBEG-1,JXMID,JXEND,M */
/*            write(*,*)(10**HS(JXBEG-1))/CMSUN,' core' */
/*            write(*,*)(10**HS(JXMID))/CMSUN,' mid' */
/*            write(*,*)(10**HS(JXEND))/CMSUN,' end' */
/*            write(*,*)(10**HS(M))/CMSUN,' M' */
/*            write(*,*)(10**HSTOT)/CMSUN,' total' */
		chkenv = pow_dd(&c_b26, hstot) / const_1.cmsun - corold;
		if (chkenv <= 0.) {
		    io___35.ciunit = luout_1.ishort;
		    s_wsfe(&io___35);
		    do_fio(&c__1, (char *)&envold, (ftnlen)sizeof(doublereal))
			    ;
		    d__1 = envold + denv;
		    do_fio(&c__1, (char *)&d__1, (ftnlen)sizeof(doublereal));
		    do_fio(&c__1, (char *)&ckind_1.rescal[(*nk << 2) - 4], (
			    ftnlen)sizeof(doublereal));
		    do_fio(&c__1, (char *)&(*smass), (ftnlen)sizeof(
			    doublereal));
		    e_wsfe();
		    s_stop("", (ftnlen)0);
		}
/* **** Calculate scale factor ***** */
/*           HSTOT1 = DLOG10(RESCAL(1,NK)/SMASS) */
		sfactor = (ckind_1.rescal[(*nk << 2) - 4] - exp(const1_1.cln *
			 hs[jxbeg - 1]) / const_1.cmsun) / (*smass - exp(
			const1_1.cln * hs[jxbeg - 1]) / const_1.cmsun);
/*        write(*,*)'hstot1',(10**HSTOT1) */
/*        write(*,*)'smass',SMASS */
/*            HSTOT = HSTOT + HSTOT1 */
		d__1 = pow_dd(&c_b26, &hs[jxbeg - 1]) + sfactor * (pow_dd(&
			c_b26, hstot) - pow_dd(&c_b26, &hs[jxbeg - 1]));
		*hstot = d_lg10(&d__1);
		*smass = ckind_1.rescal[(*nk << 2) - 4];
		comp_1.stotal = *hstot;
		i__1 = *m;
		for (i__ = jxbeg; i__ <= i__1; ++i__) {
		    d__1 = pow_dd(&c_b26, &hs[jxbeg - 1]) + sfactor * (pow_dd(
			    &c_b26, &hs[i__]) - pow_dd(&c_b26, &hs[jxbeg - 1])
			    );
		    hs[i__] = d_lg10(&d__1);
/* L78: */
		}
		envold = (exp(const1_1.cln * *hstot) - exp(const1_1.cln * hs[
			jxend])) / const_1.cmsun;
		envtotal = (exp(const1_1.cln * hs[*m]) - exp(const1_1.cln * 
			hs[jxbeg - 1])) / const_1.cmsun;
/*            write(*,*)'total envelope ',ENVTOTAL */
/*            write(*,*)'HSTOT1 ',HSTOT1 */
/*            write(*,*)'SFACTOR ',DLOG10(SFACTOR) */
/* ************ */
/*      write(*,*)'leaving new method ',HSTOT-HS(M) */
/* ************ */
	    }
	}
/* ****************************************************************** */
	if (ckind_1.rescal[(*nk << 2) - 1] > 0.) {
/* RESCALE CORE MASS. */
/* THE MASS OF THE H-BURNING SHELL IS HELD FIXED, AND MASS IS TRANSFERRED */
/* FROM THE CORE TO THE ENVELOPE (OR VICE VERSA). */

	    shlp = exp(const1_1.cln * hs[jxend]);
	    dcor = ckind_1.rescal[(*nk << 2) - 1] - corold;
	    denv = -dcor;
	    envnew = envold2 + denv;
	    if (envnew <= 0.) {
		io___38.ciunit = luout_1.ishort;
		s_wsfe(&io___38);
		do_fio(&c__1, (char *)&envold, (ftnlen)sizeof(doublereal));
		do_fio(&c__1, (char *)&envnew, (ftnlen)sizeof(doublereal));
		do_fio(&c__1, (char *)&ckind_1.rescal[(*nk << 2) - 1], (
			ftnlen)sizeof(doublereal));
		do_fio(&c__1, (char *)&corold, (ftnlen)sizeof(doublereal));
		e_wsfe();
		s_stop("", (ftnlen)0);
	    }
	    d__1 = ckind_1.rescal[(*nk << 2) - 1] / corold;
	    hstot1 = d_lg10(&d__1);
	    i__1 = jxbeg - 1;
	    for (i__ = 1; i__ <= i__1; ++i__) {
		hs[i__] += hstot1;
/* L80: */
	    }
/*  HOLD H-SHELL MASS CONSTANT;SHIFT IS THE CHANGE IN THE */
/*  UNLOGGED MASS OF EACH POINT IN THE H SHELL. */
	    shift = dcor * const_1.cmsun;
	    i__1 = jxend;
	    for (i__ = jxbeg; i__ <= i__1; ++i__) {
		temp = exp(const1_1.cln * hs[i__]);
		d__1 = temp + shift;
		hs[i__] = d_lg10(&d__1);
/* L90: */
	    }
/*  NOW SHRINK OR EXPAND THE ENVELOPE MASS TO RETAIN TOTAL CONSTANT MASS. */

	    sfactor = (exp(const1_1.cln * hs[*m]) - exp(const1_1.cln * hs[
		    jxend])) / (exp(const1_1.cln * hs[*m]) - shlp);
	    i__1 = *m;
	    for (i__ = jxend + 1; i__ <= i__1; ++i__) {
		d__1 = pow_dd(&c_b26, &hs[*m]) - sfactor * (pow_dd(&c_b26, &
			hs[*m]) - pow_dd(&c_b26, &hs[i__]));
		hs[i__] = d_lg10(&d__1);
/* L100: */
	    }
	}
	if (ckind_1.rescal[(*nk << 2) - 4] > 0. || ckind_1.rescal[(*nk << 2) 
		- 1] > 0.) {
	    cornew = exp(const1_1.cln * hs[jxbeg - 1]) / const_1.cmsun;
	    envnew = (exp(const1_1.cln * *hstot) - exp(const1_1.cln * hs[
		    jxend])) / const_1.cmsun;
	    shlnew = (exp(const1_1.cln * hs[jxend]) - exp(const1_1.cln * hs[
		    jxbeg - 1])) / const_1.cmsun;
	    io___43.ciunit = luout_1.ishort;
	    s_wsfe(&io___43);
	    do_fio(&c__1, (char *)&cornew, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&shlnew, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&envnew, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&(*smass), (ftnlen)sizeof(doublereal));
	    e_wsfe();
	}
    }
/*  CHANGE Y TO REFLECT NEW X,Z, AND HE3 VALUES. */
    i__1 = *m;
    for (i__ = 1; i__ <= i__1; ++i__) {
	hcomp[i__ * 15 + 2] = 1. - hcomp[i__ * 15 + 1] - hcomp[i__ * 15 + 3] 
		- hcomp[i__ * 15 + 4];
/* L110: */
    }

/* DBG 5/94 rescale interior Z if LZRAMP flag is T. */
/* Z is linearly adjusted from RSCLZC at the center to surface Z at */
/* mass fraction RSCLZM.  Compensate changing Z with X. */
    if (zramp_1.lzramp && zramp_1.rsclzc[*nk - 1] > 0. && zramp_1.rsclzm1[*nk 
	    - 1] > 0. && zramp_1.rsclzm2[*nk - 1] > 0.) {
	slope = (comp_1.znew - zramp_1.rsclzc[*nk - 1]) / (zramp_1.rsclzm2[*
		nk - 1] - zramp_1.rsclzm1[*nk - 1]);
	i__1 = *m;
	for (i__ = 1; i__ <= i__1; ++i__) {
	    fs = pow_dd(&c_b26, &hs[i__]) / (*smass * const_1.cmsun);
	    if (fs < zramp_1.rsclzm1[*nk - 1]) {
		zfact = (hcomp[i__ * 15 + 3] - zramp_1.rsclzc[*nk - 1]) / 
			hcomp[i__ * 15 + 3];
		hcomp[i__ * 15 + 3] = zramp_1.rsclzc[*nk - 1];
		hcomp[i__ * 15 + 1] = 1. - hcomp[i__ * 15 + 3] - hcomp[i__ * 
			15 + 4] - hcomp[i__ * 15 + 2];
		for (j = 5; j <= 11; ++j) {
		    hcomp[j + i__ * 15] *= zfact;
		}
	    } else if (fs < zramp_1.rsclzm2[*nk - 1]) {
		zp = (fs - zramp_1.rsclzm1[*nk - 1]) * slope + zramp_1.rsclzc[
			*nk - 1];
		zfact = (hcomp[i__ * 15 + 3] - zp) / hcomp[i__ * 15 + 3];
		hcomp[i__ * 15 + 3] = zp;
		hcomp[i__ * 15 + 1] = 1. - hcomp[i__ * 15 + 3] - hcomp[i__ * 
			15 + 4] - hcomp[i__ * 15 + 2];
		for (j = 5; j <= 11; ++j) {
		    hcomp[j + i__ * 15] *= zfact;
		}
	    }
	}
    }
/* ************ */
/*      write(*,*)'Leaving rscale ',HSTOT-HS(M) */
/* ************ */
/*      IF(HSTOT.LT.HS(M)) STOP */
    return 0;
} /* rscale_ */

