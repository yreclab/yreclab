/* readco.f -- translated by f2c (version 20100827).
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
    char fopale[256];
    logical lopale;
    integer iopale;
    char fopale01[256];
    logical lopale01;
    char fopale06[256];
    logical lopale06, lnumderiv;
} opaleos_;

#define opaleos_1 opaleos_

struct {
    doublereal q[4], h__[4], xxh;
} aa_;

#define aa_1 aa_

struct {
    doublereal xz[215600]	/* was [5][10][56][77] */, t6list[4312]	/* 
	    was [77][56] */, rho[77], t6a[56], esk[4312]	/* was [56][
	    77] */, esk2[4312]	/* was [56][77] */, dfsx[5], dfs[56], dfsr[77]
	    , xa[5];
    integer m, mf;
} a_;

#define a_1 a_

struct {
    doublereal zz[5];
    integer iri[10], index[10], nta[77];
} b_;

#define b_1 b_

struct {
    doublereal esact, eos[10];
} e_;

#define e_1 e_

struct {
    doublereal epl[21560]	/* was [5][56][77] */, xx[5];
} ee_;

#define ee_1 ee_

struct {
    doublereal moles[5], xin[5], tmass[5], rhogr[385]	/* was [5][77] */, 
	    frac[30]	/* was [5][6] */, alogr[4312]	/* was [77][56] */;
    integer icycuse[385]	/* was [5][77] */;
} eee_;

#define eee_1 eee_

struct rmpopeos_1_ {
    doublereal rmx[56];
    integer kra[56], kt;
};

#define rmpopeos_1 (*(struct rmpopeos_1_ *) &rmpopeos_)

/* Initialized data */

struct {
    doublereal fill_1[56];
    integer e_2[56];
    integer fill_3[1];
    } rmpopeos_ = { {0}, 77, 77, 77, 77, 77, 77, 77, 76, 76, 74, 74, 72, 72, 
	    70, 70, 68, 67, 66, 65, 64, 63, 61, 60, 59, 58, 57, 55, 54, 53, 
	    52, 51, 49, 49, 48, 47, 47, 46, 45, 45, 44, 44, 44, 44, 44, 44, 
	    44, 44, 44, 44, 44, 44, 44, 44, 44, 37, 37 };


/* Table of constant values */

static integer c__1 = 1;


/* ********************************************************************** */
/* Subroutine */ int readco_(void)
{
    /* System generated locals */
    integer i__1;
    olist o__1;
    cllist cl__1;

    /* Builtin functions */
    integer f_open(olist *), s_rsfe(cilist *), do_fio(integer *, char *, 
	    ftnlen), e_rsfe(void), s_wsfe(cilist *), e_wsfe(void);
    /* Subroutine */ int s_stop(char *, ftnlen);
    integer f_clos(cllist *);

    /* Local variables */
    static integer i__, j, k, l, iv, jcs;
    static doublereal dum;
    static char blank[1];
    static integer ntuse, numtot, itimeco;

    /* Fortran I/O blocks */
    static cilist io___7 = { 0, 0, 0, "(3X,F6.4,3X,F6.4,11X,F10.7,17X,F10.7)",
	     0 };
    static cilist io___8 = { 0, 0, 0, "(21X,E14.7,4X,E14.7,3X,E11.4,3X,E11.4"
	    ",3X,E11.4, 4X,E11.4)", 0 };
    static cilist io___9 = { 0, 0, 0, "(A)", 0 };
    static cilist io___11 = { 0, 0, 0, "(2I5,2F12.7,17X,E15.7)", 0 };
    static cilist io___14 = { 0, 0, 0, "(\" DATA FILE INCORRECT: NUMTOT,JC"
	    "S= \",2I5)", 0 };
    static cilist io___15 = { 0, 0, 0, "(A)", 0 };
    static cilist io___16 = { 0, 0, 0, "(A)", 0 };
    static cilist io___17 = { 0, 0, 0, "(\"PROBLEM WITH DATA FILES: X=\",F6."
	    "4,\" DENSITY=\",      E14.4)", 0 };
    static cilist io___18 = { 0, 0, 0, "(A)", 0 };
    static cilist io___19 = { 0, 0, 0, "(F8.4,1X,F6.2,3E13.5,E11.3,6F8.4)", 0 
	    };
    static cilist io___21 = { 0, 0, 0, "(A)", 0 };
    static cilist io___22 = { 0, 0, 0, "(A)", 0 };
    static cilist io___23 = { 0, 0, 0, "(A)", 0 };
    static cilist io___24 = { 0, 0, 0, "(A)", 0 };


/* ..... THE PURPOSE OF THIS SUBROUTINE IS TO READ THE DATA TABLES */
/* YCK >>>  2/95 OPAL EOS */
/* <<< YCK */
    *(unsigned char *)blank = ' ';
    if (itimeco != 12345678) {
	for (i__ = 1; i__ <= 5; ++i__) {
	    for (j = 1; j <= 10; ++j) {
		for (k = 1; k <= 56; ++k) {
		    for (l = 1; l <= 77; ++l) {
			a_1.xz[i__ + (j + (k + l * 56) * 10) * 5 - 2856] = 
				1e35;
		    }
		}
	    }
	}
	itimeco = 12345678;
    }
/* ..... READ  TABLES */
/* YCK >>> */
    o__1.oerr = 0;
    o__1.ounit = opaleos_1.iopale;
    o__1.ofnmlen = 256;
    o__1.ofnm = opaleos_1.fopale;
    o__1.orl = 0;
    o__1.osta = "OLD";
    o__1.oacc = 0;
    o__1.ofm = 0;
    o__1.oblnk = 0;
    f_open(&o__1);
/* <<< YCK */
    for (a_1.m = 1; a_1.m <= 5; ++a_1.m) {
	io___7.ciunit = opaleos_1.iopale;
	s_rsfe(&io___7);
	do_fio(&c__1, (char *)&eee_1.xin[a_1.m - 1], (ftnlen)sizeof(
		doublereal));
	do_fio(&c__1, (char *)&b_1.zz[a_1.m - 1], (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&eee_1.moles[a_1.m - 1], (ftnlen)sizeof(
		doublereal));
	do_fio(&c__1, (char *)&eee_1.tmass[a_1.m - 1], (ftnlen)sizeof(
		doublereal));
	e_rsfe();
	io___8.ciunit = opaleos_1.iopale;
	s_rsfe(&io___8);
	for (i__ = 1; i__ <= 6; ++i__) {
	    do_fio(&c__1, (char *)&eee_1.frac[a_1.m + i__ * 5 - 6], (ftnlen)
		    sizeof(doublereal));
	}
	e_rsfe();
	io___9.ciunit = opaleos_1.iopale;
	s_rsfe(&io___9);
	do_fio(&c__1, blank, (ftnlen)1);
	e_rsfe();
	for (jcs = 1; jcs <= 77; ++jcs) {
	    io___11.ciunit = opaleos_1.iopale;
	    s_rsfe(&io___11);
	    do_fio(&c__1, (char *)&numtot, (ftnlen)sizeof(integer));
	    do_fio(&c__1, (char *)&eee_1.icycuse[a_1.m + jcs * 5 - 6], (
		    ftnlen)sizeof(integer));
	    do_fio(&c__1, (char *)&dum, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&dum, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&eee_1.rhogr[a_1.m + jcs * 5 - 6], (ftnlen)
		    sizeof(doublereal));
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
	    if (eee_1.icycuse[a_1.m + jcs * 5 - 6] < b_1.nta[jcs - 1]) {
		io___17.ciunit = luout_1.ishort;
		s_wsfe(&io___17);
		do_fio(&c__1, (char *)&eee_1.xin[a_1.m - 1], (ftnlen)sizeof(
			doublereal));
		do_fio(&c__1, (char *)&eee_1.rhogr[a_1.m + jcs * 5 - 6], (
			ftnlen)sizeof(doublereal));
		e_wsfe();
		s_stop("", (ftnlen)0);
	    }
	    i__1 = eee_1.icycuse[a_1.m + jcs * 5 - 6];
	    for (i__ = 1; i__ <= i__1; ++i__) {
		if (i__ > b_1.nta[jcs - 1]) {
		    io___18.ciunit = opaleos_1.iopale;
		    s_rsfe(&io___18);
		    do_fio(&c__1, blank, (ftnlen)1);
		    e_rsfe();
		    goto L4;
		}
		io___19.ciunit = opaleos_1.iopale;
		s_rsfe(&io___19);
		do_fio(&c__1, (char *)&a_1.t6list[jcs + i__ * 77 - 78], (
			ftnlen)sizeof(doublereal));
		do_fio(&c__1, (char *)&eee_1.alogr[jcs + i__ * 77 - 78], (
			ftnlen)sizeof(doublereal));
		for (iv = 1; iv <= 10; ++iv) {
		    do_fio(&c__1, (char *)&a_1.xz[a_1.m + (b_1.index[iv - 1] 
			    + (i__ + jcs * 56) * 10) * 5 - 2856], (ftnlen)
			    sizeof(doublereal));
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
    for (i__ = 1; i__ <= 56; ++i__) {
	if (a_1.t6list[i__ * 77 - 77] == 0.) {
	    ntuse = i__;
	    goto L14;
	}
/* L11: */
	a_1.t6a[i__ - 1] = a_1.t6list[i__ * 77 - 77];
    }
L14:
    for (i__ = 2; i__ <= 56; ++i__) {
/* L12: */
	a_1.dfs[i__ - 1] = 1. / (a_1.t6a[i__ - 1] - a_1.t6a[i__ - 2]);
    }
    a_1.rho[0] = eee_1.rhogr[0];
    for (i__ = 2; i__ <= 77; ++i__) {
	a_1.rho[i__ - 1] = eee_1.rhogr[i__ * 5 - 5];
/* L13: */
	a_1.dfsr[i__ - 1] = 1. / (a_1.rho[i__ - 1] - a_1.rho[i__ - 2]);
    }
    for (i__ = 2; i__ <= 5; ++i__) {
	a_1.dfsx[i__ - 1] = 1. / (ee_1.xx[i__ - 1] - ee_1.xx[i__ - 2]);
    }

    cl__1.cerr = 0;
    cl__1.cunit = opaleos_1.iopale;
    cl__1.csta = 0;
    f_clos(&cl__1);
/*  MHP 8/98 ADDED RAMP BETWEEN OPAL AND OTHER EOS */
/*  NEED EDGE OF TABLE AT HIGH RHO, FIXED T. */
    rmpopeos_1.kt = 1;
    for (i__ = 1; i__ <= 56; ++i__) {
	rmpopeos_1.rmx[i__ - 1] = a_1.rho[rmpopeos_1.kra[i__ - 1] - 1];
    }
    return 0;
} /* readco_ */

