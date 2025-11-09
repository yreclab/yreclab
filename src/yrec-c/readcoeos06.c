/* readcoeos06.f -- translated by f2c (version 20061008).
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
    doublereal q[4], h__[4], xxh;
} aaeos06_;

#define aaeos06_1 aaeos06_

struct {
    doublereal xz[1664650]	/* was [5][10][197][169] */, t6list[33293]	
	    /* was [169][197] */, rho[169], t6a[197], esk[33293]	/* 
	    was [197][169] */, esk2[33293]	/* was [197][169] */, dfsx[5],
	     dfs[197], dfsr[169];
    integer m, mf;
    doublereal xa[5];
} aeos06_;

#define aeos06_1 aeos06_

struct {
    doublereal zz[5];
    integer iri[10], index[10], nta[169], nra[197];
} beos06_;

#define beos06_1 beos06_

struct {
    doublereal esact, eos[10];
} eeos06_;

#define eeos06_1 eeos06_

struct {
    doublereal epl[166465]	/* was [5][197][169] */, xx[5];
} eeeos06_;

#define eeeos06_1 eeeos06_

struct {
    doublereal moles[5], xin[5], tmass[5], amu_m__[33293]	/* was [169][
	    197] */, alogne[33293]	/* was [169][197] */, rhogr[845]	
	    /* was [5][169] */, frac[30]	/* was [5][6] */, alogr[33293]
	    	/* was [169][197] */;
    integer icycuse[845]	/* was [5][169] */;
} eeeeos06_;

#define eeeeos06_1 eeeeos06_

struct {
    integer ilast, idebug, itrack, ishort, imilne, imodpt, istor, iowr;
} luout_;

#define luout_1 luout_

struct {
    logical lopale;
    integer iopale;
    logical lopale01, lopale06, lnumderiv;
} opaleos_;

#define opaleos_1 opaleos_

/* Table of constant values */

static integer c__1 = 1;

/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */

/*     READCOEOS06 */

/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */
/* Subroutine */ int readcoeos06_(void)
{
    /* System generated locals */
    integer i__1;
    cllist cl__1;

    /* Builtin functions */
    integer f_clos(cllist *), s_rsfe(cilist *), do_fio(integer *, char *, 
	    ftnlen), e_rsfe(void), s_wsfe(cilist *), e_wsfe(void);
    /* Subroutine */ void s_stop(char *, ftnlen);

    /* Local variables */
    static integer i__, j, k, l, iv, jcs;
    static doublereal dum;
    static char blank[1];
    static integer numtot, itimeco;

    /* Fortran I/O blocks */
    static cilist io___7 = { 0, 0, 0, "(3x,f6.4,3x,f12.9,11x,f10.7,17x,f10.7)"
	    , 0 };
    static cilist io___8 = { 0, 0, 0, "(21x,e14.7,4x,e14.7,3x,e11.4,3x,e11.4"
	    ",3x,e11.4, 4x,e11.4)", 0 };
    static cilist io___9 = { 0, 0, 0, "(a)", 0 };
    static cilist io___11 = { 0, 0, 0, "(2i5,2f12.7,17x,e15.7)", 0 };
    static cilist io___14 = { 0, 0, 0, "(\" OEOS06 Data file incorrect: numt"
	    "ot,jcs= \"   ,  2i5)", 0 };
    static cilist io___15 = { 0, 0, 0, "(a)", 0 };
    static cilist io___16 = { 0, 0, 0, "(a)", 0 };
    static cilist io___17 = { 0, 0, 0, "(\"Problem with OEOS96 data files:"
	    " X=\",f6.4,         \" density=\",e14.4)", 0 };
    static cilist io___18 = { 0, 0, 0, "(a)", 0 };
    static cilist io___19 = { 0, 0, 0, "(f11.6,1x,f6.4,e11.4,2e13.6,2e11.3,5"
	    "f10.6)", 0 };
    static cilist io___21 = { 0, 0, 0, "(a)", 0 };
    static cilist io___22 = { 0, 0, 0, "(a)", 0 };
    static cilist io___23 = { 0, 0, 0, "(a)", 0 };
    static cilist io___24 = { 0, 0, 0, "(a)", 0 };
    static cilist io___25 = { 0, 0, 0, "(\"READCOEOS06: Error:\",i4,        "
	    "   \"-th T6 value is zero\")", 0 };


/* ..... The purpose of this subroutine is to read the OPAL 2006 EOS data tables */
/* MHP 8/25 Remove unused variables */
/*      CHARACTER*256 FOPALE,fopale01,fopale06 */
/* KC 2025-05-30 reordered common block elements */
/*       common/beos06/ iri(10),index(10),nta(nr),zz(mx),nra(nt) */
/* Amu_M and alogNe were incorrectly dimensoned Amu_M(mx,nr) and alogNe(mx,nr). */
/* the required dimensions are Amu_M(nr,nt) alogNe(nr,nt), which is much larger. */
/* Something was being overwritten.         llp 8/19/08 */
/*     x    amu_M(mx,nr),alogNe(mx,nr),rhogr(mx,nr),frac(mx,6), */
/* KC 2025-05-30 reordered common block elements */
/*       common/eeeeos06/moles(mx),xin(mx),tmass(mx),icycuse(mx,nr), */
/*      x    alogr(nr,nt) */
/* KC 2025-05-30 reordered common block elements */
/*       COMMON/OPALEOS/FOPALE,LOPALE,IOPALE,fopale01,lopale01,fopale06, */
/*      x     lopale06,LNumDeriv */
/* MHP 8/25 Remove file names from common blocks */
    *(unsigned char *)blank = ' ';
    if (itimeco != 12345678) {
	for (i__ = 1; i__ <= 5; ++i__) {
	    for (j = 1; j <= 10; ++j) {
		for (k = 1; k <= 197; ++k) {
		    for (l = 1; l <= 169; ++l) {
			aeos06_1.xz[i__ + (j + (k + l * 197) * 10) * 5 - 9906]
				 = 1e35;
		    }
		}
	    }
	}
	for (j = 1; j <= 10; ++j) {
	    eeos06_1.eos[j - 1] = 1.;
	}
	itimeco = 12345678;
    }
    cl__1.cerr = 0;
    cl__1.cunit = 2;
    cl__1.csta = 0;
    f_clos(&cl__1);
/* .....read  tables */
/* MHP 8/25 Moved opening of file to parmin */
    for (aeos06_1.m = 1; aeos06_1.m <= 5; ++aeos06_1.m) {
	io___7.ciunit = opaleos_1.iopale;
	s_rsfe(&io___7);
	do_fio(&c__1, (char *)&eeeeos06_1.xin[aeos06_1.m - 1], (ftnlen)sizeof(
		doublereal));
	do_fio(&c__1, (char *)&beos06_1.zz[aeos06_1.m - 1], (ftnlen)sizeof(
		doublereal));
	do_fio(&c__1, (char *)&eeeeos06_1.moles[aeos06_1.m - 1], (ftnlen)
		sizeof(doublereal));
	do_fio(&c__1, (char *)&eeeeos06_1.tmass[aeos06_1.m - 1], (ftnlen)
		sizeof(doublereal));
	e_rsfe();
	io___8.ciunit = opaleos_1.iopale;
	s_rsfe(&io___8);
	for (i__ = 1; i__ <= 6; ++i__) {
	    do_fio(&c__1, (char *)&eeeeos06_1.frac[aeos06_1.m + i__ * 5 - 6], 
		    (ftnlen)sizeof(doublereal));
	}
	e_rsfe();
	io___9.ciunit = opaleos_1.iopale;
	s_rsfe(&io___9);
	do_fio(&c__1, blank, (ftnlen)1);
	e_rsfe();
	for (jcs = 1; jcs <= 169; ++jcs) {
	    io___11.ciunit = opaleos_1.iopale;
	    s_rsfe(&io___11);
	    do_fio(&c__1, (char *)&numtot, (ftnlen)sizeof(integer));
	    do_fio(&c__1, (char *)&eeeeos06_1.icycuse[aeos06_1.m + jcs * 5 - 
		    6], (ftnlen)sizeof(integer));
	    do_fio(&c__1, (char *)&dum, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&dum, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&eeeeos06_1.rhogr[aeos06_1.m + jcs * 5 - 6],
		     (ftnlen)sizeof(doublereal));
	    e_rsfe();
	    if (numtot != jcs) {
		io___14.ciunit = luout_1.ishort;
		s_wsfe(&io___14);
		do_fio(&c__1, (char *)&numtot, (ftnlen)sizeof(integer));
		do_fio(&c__1, (char *)&jcs, (ftnlen)sizeof(integer));
		e_wsfe();
		s_stop("", (ftnlen)0);
	    }
	    io___15.ciunit = opaleos_1.iopale;
	    s_rsfe(&io___15);
	    do_fio(&c__1, blank, (ftnlen)1);
	    e_rsfe();
	    io___16.ciunit = opaleos_1.iopale;
	    s_rsfe(&io___16);
	    do_fio(&c__1, blank, (ftnlen)1);
	    e_rsfe();
	    if (eeeeos06_1.icycuse[aeos06_1.m + jcs * 5 - 6] < beos06_1.nta[
		    jcs - 1]) {
		io___17.ciunit = luout_1.ishort;
		s_wsfe(&io___17);
		do_fio(&c__1, (char *)&eeeeos06_1.xin[aeos06_1.m - 1], (
			ftnlen)sizeof(doublereal));
		do_fio(&c__1, (char *)&eeeeos06_1.rhogr[aeos06_1.m + jcs * 5 
			- 6], (ftnlen)sizeof(doublereal));
		e_wsfe();
		s_stop("", (ftnlen)0);
	    }
	    i__1 = eeeeos06_1.icycuse[aeos06_1.m + jcs * 5 - 6];
	    for (i__ = 1; i__ <= i__1; ++i__) {
		if (i__ > beos06_1.nta[jcs - 1]) {
		    io___18.ciunit = opaleos_1.iopale;
		    s_rsfe(&io___18);
		    do_fio(&c__1, blank, (ftnlen)1);
		    e_rsfe();
		    goto L4;
		}
		io___19.ciunit = opaleos_1.iopale;
		s_rsfe(&io___19);
		do_fio(&c__1, (char *)&aeos06_1.t6list[jcs + i__ * 169 - 170],
			 (ftnlen)sizeof(doublereal));
		do_fio(&c__1, (char *)&eeeeos06_1.amu_m__[jcs + i__ * 169 - 
			170], (ftnlen)sizeof(doublereal));
		do_fio(&c__1, (char *)&eeeeos06_1.alogne[jcs + j * 169 - 170],
			 (ftnlen)sizeof(doublereal));
		for (iv = 1; iv <= 9; ++iv) {
		    do_fio(&c__1, (char *)&aeos06_1.xz[aeos06_1.m + (
			    beos06_1.index[iv - 1] + (i__ + jcs * 197) * 10) *
			     5 - 9906], (ftnlen)sizeof(doublereal));
		}
		e_rsfe();
L4:
		;
	    }
	    io___21.ciunit = opaleos_1.iopale;
	    s_rsfe(&io___21);
	    do_fio(&c__1, blank, (ftnlen)1);
	    e_rsfe();
	    io___22.ciunit = opaleos_1.iopale;
	    s_rsfe(&io___22);
	    do_fio(&c__1, blank, (ftnlen)1);
	    e_rsfe();
	    io___23.ciunit = opaleos_1.iopale;
	    s_rsfe(&io___23);
	    do_fio(&c__1, blank, (ftnlen)1);
	    e_rsfe();
/* L2: */
	}
	io___24.ciunit = opaleos_1.iopale;
	s_rsfe(&io___24);
	do_fio(&c__1, blank, (ftnlen)1);
	e_rsfe();
/* L3: */
    }
    for (i__ = 1; i__ <= 197; ++i__) {
	if (aeos06_1.t6list[i__ * 169 - 169] == 0.) {
	    io___25.ciunit = luout_1.ishort;
	    s_wsfe(&io___25);
	    do_fio(&c__1, (char *)&i__, (ftnlen)sizeof(integer));
	    e_wsfe();
	    s_stop("", (ftnlen)0);
	}
	aeos06_1.t6a[i__ - 1] = aeos06_1.t6list[i__ * 169 - 169];
    }
    for (i__ = 2; i__ <= 197; ++i__) {
/* KC 2025-05-30 fixed "DO termination statement which is not END DO or CONTINUE" */
/*    12 dfs(i)=1D0/(t6a(i)-t6a(i-1)) */
	aeos06_1.dfs[i__ - 1] = 1. / (aeos06_1.t6a[i__ - 1] - aeos06_1.t6a[
		i__ - 2]);
/* L12: */
    }
    aeos06_1.rho[0] = eeeeos06_1.rhogr[0];
    for (i__ = 2; i__ <= 169; ++i__) {
/* KC 2025-05-30 fixed "DO termination statement which is not END DO or CONTINUE" */
/*       rho(i)=rhogr(1,i) */
/*    13 dfsr(i)=1D0/(rho(i)-rho(i-1)) */
	aeos06_1.rho[i__ - 1] = eeeeos06_1.rhogr[i__ * 5 - 5];
	aeos06_1.dfsr[i__ - 1] = 1. / (aeos06_1.rho[i__ - 1] - aeos06_1.rho[
		i__ - 2]);
/* L13: */
    }
    for (i__ = 2; i__ <= 5; ++i__) {
	aeos06_1.dfsx[i__ - 1] = 1. / (eeeos06_1.xx[i__ - 1] - eeeos06_1.xx[
		i__ - 2]);
    }
    cl__1.cerr = 0;
    cl__1.cunit = opaleos_1.iopale;
    cl__1.csta = 0;
    f_clos(&cl__1);
    return 0;
} /* readcoeos06_ */

