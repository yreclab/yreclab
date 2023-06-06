/* readcoeos01.f -- translated by f2c (version 20100827).
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
} aaeos_;

#define aaeos_1 aaeos_

struct {
    doublereal xz[1613950]	/* was [5][10][191][169] */, t6list[32279]	
	    /* was [169][191] */, rho[169], t6a[191], esk[32279]	/* 
	    was [191][169] */, esk2[32279]	/* was [191][169] */, dfsx[5],
	     dfs[191], dfsr[169];
    integer m, mf;
    doublereal xa[5];
} aeos_;

#define aeos_1 aeos_

struct {
    integer iri[10], index[10], nta[169];
    doublereal zz[5];
} beos_;

#define beos_1 beos_

struct {
    doublereal esact, eos[10];
} eeos_;

#define eeos_1 eeos_

struct {
    doublereal epl[161395]	/* was [5][191][169] */, xx[5];
} eeeos_;

#define eeeos_1 eeeos_

struct {
    doublereal moles[5], xin[5], tmass[5];
    integer icycuse[845]	/* was [5][169] */;
    doublereal rhogr[845]	/* was [5][169] */, frac[30]	/* was [5][6] 
	    */, alogr[32279]	/* was [169][191] */;
} eeeeos_;

#define eeeeos_1 eeeeos_

struct {
    integer ilast, idebug, itrack, ishort, imilne, imodpt, istor, iowr;
} luout_;

#define luout_1 luout_

struct {
    char fopale[256];
    logical lopale;
    integer iopale;
    char fopale01[256];
    logical lopale01;
    char fopale06[256];
    logical lopale06, lnumderiv;
} opaleos_;

#define opaleos_1 opaleos_

struct rmpopeos01_1_ {
    doublereal rmx[191];
    integer kra[191], kt;
};

#define rmpopeos01_1 (*(struct rmpopeos01_1_ *) &rmpopeos01_)

/* Initialized data */

struct {
    doublereal fill_1[191];
    integer e_2[191];
    integer fill_3[1];
    } rmpopeos01_ = { {0}, 169, 169, 169, 169, 169, 169, 169, 169, 169, 169, 
	    169, 169, 169, 169, 169, 169, 168, 167, 166, 165, 164, 164, 163, 
	    162, 162, 161, 160, 159, 159, 143, 143, 143, 143, 137, 137, 137, 
	    137, 137, 134, 134, 134, 134, 134, 134, 125, 125, 123, 123, 123, 
	    123, 123, 122, 122, 121, 121, 121, 121, 121, 121, 119, 119, 119, 
	    119, 116, 116, 116, 116, 116, 116, 116, 116, 115, 115, 115, 115, 
	    115, 115, 115, 115, 115, 113, 113, 113, 113, 113, 111, 111, 111, 
	    111, 111, 111, 111, 110, 110, 110, 110, 110, 110, 109, 109, 109, 
	    109, 109, 109, 109, 109, 109, 109, 109, 109, 109, 109, 109, 109, 
	    109, 109, 109, 109, 109, 109, 109, 109, 109, 109, 109, 109, 109, 
	    109, 109, 109, 109, 109, 107, 104, 100, 100, 100, 100, 100, 100, 
	    100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 
	    100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 
	    100, 100, 100, 100, 100, 100, 100, 100, 99, 99, 99, 99, 99, 99, 
	    99, 99, 99, 99, 98, 97, 96, 95, 94, 93, 92 };


/* Table of constant values */

static integer c__1 = 1;

/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */

/*     READCOEOS01 */

/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */
/* Subroutine */ int readcoeos01_(void)
{
    /* System generated locals */
    integer i__1;
    olist o__1;
    cllist cl__1;

    /* Builtin functions */
    integer f_clos(cllist *), f_open(olist *), s_rsfe(cilist *), do_fio(
	    integer *, char *, ftnlen), e_rsfe(void), s_wsfe(cilist *), 
	    e_wsfe(void);
    /* Subroutine */ int s_stop(char *, ftnlen);

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
    static cilist io___14 = { 0, 0, 0, "(\" Data file incorrect: numtot,jc"
	    "s= \",2i5)", 0 };
    static cilist io___15 = { 0, 0, 0, "(a)", 0 };
    static cilist io___16 = { 0, 0, 0, "(a)", 0 };
    static cilist io___17 = { 0, 0, 0, "(\"problem with data files: X=\",f6."
	    "4,         \" density=\",e14.4)", 0 };
    static cilist io___18 = { 0, 0, 0, "(a)", 0 };
    static cilist io___19 = { 0, 0, 0, "(f9.5,1x,f6.2,3e13.5,6f8.4)", 0 };
    static cilist io___21 = { 0, 0, 0, "(a)", 0 };
    static cilist io___22 = { 0, 0, 0, "(a)", 0 };
    static cilist io___23 = { 0, 0, 0, "(a)", 0 };
    static cilist io___24 = { 0, 0, 0, "(a)", 0 };
    static cilist io___25 = { 0, 0, 0, "(\"READCOEOS01: Error:\",i4,        "
	    "   \"-th T6 value is zero\")", 0 };


/* ..... The purpose of this subroutine is to read the data tables */
/* mhp 7/2003 */
    *(unsigned char *)blank = ' ';
    if (itimeco != 12345678) {
	for (i__ = 1; i__ <= 5; ++i__) {
	    for (j = 1; j <= 10; ++j) {
		for (k = 1; k <= 191; ++k) {
		    for (l = 1; l <= 169; ++l) {
			aeos_1.xz[i__ + (j + (k + l * 191) * 10) * 5 - 9606] =
				 1e35;
		    }
		}
	    }
	}
	itimeco = 12345678;
    }
    cl__1.cerr = 0;
    cl__1.cunit = 2;
    cl__1.csta = 0;
    f_clos(&cl__1);
/* ..... read  tables */
    o__1.oerr = 0;
    o__1.ounit = opaleos_1.iopale;
    o__1.ofnmlen = 256;
    o__1.ofnm = opaleos_1.fopale01;
    o__1.orl = 0;
    o__1.osta = "OLD";
    o__1.oacc = 0;
    o__1.ofm = 0;
    o__1.oblnk = 0;
    f_open(&o__1);
    for (aeos_1.m = 1; aeos_1.m <= 5; ++aeos_1.m) {
	io___7.ciunit = opaleos_1.iopale;
	s_rsfe(&io___7);
	do_fio(&c__1, (char *)&eeeeos_1.xin[aeos_1.m - 1], (ftnlen)sizeof(
		doublereal));
	do_fio(&c__1, (char *)&beos_1.zz[aeos_1.m - 1], (ftnlen)sizeof(
		doublereal));
	do_fio(&c__1, (char *)&eeeeos_1.moles[aeos_1.m - 1], (ftnlen)sizeof(
		doublereal));
	do_fio(&c__1, (char *)&eeeeos_1.tmass[aeos_1.m - 1], (ftnlen)sizeof(
		doublereal));
	e_rsfe();
	io___8.ciunit = opaleos_1.iopale;
	s_rsfe(&io___8);
	for (i__ = 1; i__ <= 6; ++i__) {
	    do_fio(&c__1, (char *)&eeeeos_1.frac[aeos_1.m + i__ * 5 - 6], (
		    ftnlen)sizeof(doublereal));
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
	    do_fio(&c__1, (char *)&eeeeos_1.icycuse[aeos_1.m + jcs * 5 - 6], (
		    ftnlen)sizeof(integer));
	    do_fio(&c__1, (char *)&dum, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&dum, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&eeeeos_1.rhogr[aeos_1.m + jcs * 5 - 6], (
		    ftnlen)sizeof(doublereal));
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
	    if (eeeeos_1.icycuse[aeos_1.m + jcs * 5 - 6] < beos_1.nta[jcs - 1]
		    ) {
		io___17.ciunit = luout_1.ishort;
		s_wsfe(&io___17);
		do_fio(&c__1, (char *)&eeeeos_1.xin[aeos_1.m - 1], (ftnlen)
			sizeof(doublereal));
		do_fio(&c__1, (char *)&eeeeos_1.rhogr[aeos_1.m + jcs * 5 - 6],
			 (ftnlen)sizeof(doublereal));
		e_wsfe();
		s_stop("", (ftnlen)0);
	    }
	    i__1 = eeeeos_1.icycuse[aeos_1.m + jcs * 5 - 6];
	    for (i__ = 1; i__ <= i__1; ++i__) {
		if (i__ > beos_1.nta[jcs - 1]) {
		    io___18.ciunit = opaleos_1.iopale;
		    s_rsfe(&io___18);
		    do_fio(&c__1, blank, (ftnlen)1);
		    e_rsfe();
		    goto L4;
		}
		io___19.ciunit = opaleos_1.iopale;
		s_rsfe(&io___19);
		do_fio(&c__1, (char *)&aeos_1.t6list[jcs + i__ * 169 - 170], (
			ftnlen)sizeof(doublereal));
		do_fio(&c__1, (char *)&eeeeos_1.alogr[jcs + i__ * 169 - 170], 
			(ftnlen)sizeof(doublereal));
		for (iv = 1; iv <= 9; ++iv) {
		    do_fio(&c__1, (char *)&aeos_1.xz[aeos_1.m + (beos_1.index[
			    iv - 1] + (i__ + jcs * 191) * 10) * 5 - 9606], (
			    ftnlen)sizeof(doublereal));
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
    for (i__ = 1; i__ <= 191; ++i__) {
	if (aeos_1.t6list[i__ * 169 - 169] == 0.) {
	    io___25.ciunit = luout_1.ishort;
	    s_wsfe(&io___25);
	    do_fio(&c__1, (char *)&i__, (ftnlen)sizeof(integer));
	    e_wsfe();
	    s_stop("", (ftnlen)0);
	}
	aeos_1.t6a[i__ - 1] = aeos_1.t6list[i__ * 169 - 169];
    }
    for (i__ = 2; i__ <= 191; ++i__) {
/* L12: */
	aeos_1.dfs[i__ - 1] = 1. / (aeos_1.t6a[i__ - 1] - aeos_1.t6a[i__ - 2])
		;
    }
    aeos_1.rho[0] = eeeeos_1.rhogr[0];
    for (i__ = 2; i__ <= 169; ++i__) {
	aeos_1.rho[i__ - 1] = eeeeos_1.rhogr[i__ * 5 - 5];
/* L13: */
	aeos_1.dfsr[i__ - 1] = 1. / (aeos_1.rho[i__ - 1] - aeos_1.rho[i__ - 2]
		);
    }
    for (i__ = 2; i__ <= 5; ++i__) {
	aeos_1.dfsx[i__ - 1] = 1. / (eeeos_1.xx[i__ - 1] - eeeos_1.xx[i__ - 2]
		);
    }
    cl__1.cerr = 0;
    cl__1.cunit = opaleos_1.iopale;
    cl__1.csta = 0;
    f_clos(&cl__1);
/*  MHP 7/2003 ADDED RAMP BETWEEN OPAL AND OTHER EOS */
/*  NEED EDGE OF TABLE AT HIGH RHO, FIXED T. */
    rmpopeos01_1.kt = 1;
    for (i__ = 1; i__ <= 191; ++i__) {
	rmpopeos01_1.rmx[i__ - 1] = aeos_1.rho[rmpopeos01_1.kra[i__ - 1] - 1];
    }
    return 0;
} /* readcoeos01_ */

