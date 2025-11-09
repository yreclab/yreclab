/* readalex06.f -- translated by f2c (version 20061008).
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
    integer ialex06;
} alex06_;

#define alex06_1 alex06_

struct galot06_1_ {
    doublereal tgr06[85], xxg06[9], r0gr06[19], zzg06[16];
};

#define galot06_1 (*(struct galot06_1_ *) &galot06_)

struct alot06_1_ {
    doublereal capalex06[1615]	/* was [85][19] */, xe, ze;
    integer ix, it, id;
};

#define alot06_1 (*(struct alot06_1_ *) &alot06_)

struct {
    doublereal captalex06[230945]	/* was [143][85][19] */;
} alot06all_;

#define alot06all_1 alot06all_

struct {
    integer ilast, idebug, itrack, ishort, imilne, imodpt, istor, iowr;
} luout_;

#define luout_1 luout_

/* Initialized data */

struct {
    doublereal e_1[129];
    } galot06_ = { 2.7, 2.75, 2.8, 2.85, 2.9, 2.91, 2.92, 2.93, 2.94, 2.95, 
	    2.96, 2.97, 2.98, 2.99, 3., 3.01, 3.02, 3.03, 3.04, 3.05, 3.06, 
	    3.07, 3.08, 3.09, 3.1, 3.11, 3.12, 3.13, 3.14, 3.15, 3.16, 3.17, 
	    3.18, 3.19, 3.2, 3.21, 3.22, 3.23, 3.24, 3.25, 3.26, 3.27, 3.28, 
	    3.29, 3.3, 3.31, 3.32, 3.33, 3.34, 3.35, 3.36, 3.37, 3.38, 3.39, 
	    3.4, 3.41, 3.42, 3.43, 3.44, 3.45, 3.46, 3.47, 3.48, 3.49, 3.5, 
	    3.55, 3.6, 3.65, 3.7, 3.75, 3.8, 3.85, 3.9, 3.95, 4., 4.05, 4.1, 
	    4.15, 4.2, 4.25, 4.3, 4.35, 4.4, 4.45, 4.5, 0., .1, .2, .35, .5, 
	    .7, .8, .9, 1., -8., -7.5, -7., -6.5, -6., -5.5, -5., -4.5, -4., 
	    -3.5, -3., -2.5, -2., -1.5, -1., -.5, 0., .5, 1., 0., 1e-5, 3e-5, 
	    1e-4, 3e-4, .001, .002, .004, .01, .02, .03, .04, .05, .06, .08, 
	    .1 };

struct {
    doublereal fill_1[1615];
    doublereal e_2[2];
    integer e_3[3];
    } alot06_ = { {0}, 0., 0., 4, 43, 10 };


/* Table of constant values */

static integer c__1 = 1;

/* MHP 3/09  SUBROUTINE FOR READING IN ALEXANDER LOW T OPACITIES. */

/* ALEXANDER OPACITIES FERGUSON ET AL. 2005  APJ,623,585 */
/* FOR EACH  X = 0.0, 0.1, 0.2, 0.35, 0.5, 0.7, 0.8, 0.9, 1-Z */
/* INCREASING ORDER OF Z = 0.0, 0.00001, 0.00003, 0.0001, 0.0003, */
/*     (16)               0.001, 0.002, 0.004, 0.01, 0.02, 0.03, */
/*                        0.04, 0.05, 0.06, 0.08, 0.10 */
/* DESCENDING ORDER OF LOGT 4.5-3.5 IN 0.05 DEX INCREMENTS */
/*     (85)                 3.5-2.9 IN 0.01 DEX INCREMENTS */
/*                          2.9-2.7 IN 0.05 DEX INCREMENTS */
/* ASCENDING ORDER OF  LOGR -8.0 -7.5 -7.0 -6.5 -6.0 -5.5 -5.0 -4.5 -4.0 -3.5 */
/*     (19)                -3.0 -2.5 -2.0 -1.5 -1.0 -0.5  0.0  0.5  1.0 */
/* WHERE R = RHO/T_6**3 */
/* READ IN ALL Z VALUES AT FIXED X.  THEN GENERATE SURFACE X,Z TABLE. */
/* INTERPOLATION BETWEEN COMPOSITIONS IS 4-POINT LAGRANGIAN. */

/* MHP 8/25 Added file name to subroutine call */
/* Subroutine */ int readalex06_(char *falex06, ftnlen falex06_len)
{
    /* Format strings */
    static char fmt_10[] = "(30x,f9.6,7x,f9.6//)";
    static char fmt_15[] = "(1x,\002ERROR IN ALEXANDER OPACITY TABLES:\002/1"
	    "x,\002EXPECTED AND ACTUAL X,Z\002,4f7.2,\002 RUN STOPPED\002)";
    static char fmt_20[] = "(6x,19f7.3)";
    static char fmt_25[] = "(1x,\002ERROR IN ALEXANDER OPACITY TABLES:\002/1"
	    "x,\002EXPECTED AND ACTUAL R\002,i3,2f7.3,\002 RUN STOPPED\002)";
    static char fmt_30[] = "(f5.3,1x,19f7.3)";
    static char fmt_35[] = "(1x,\002ERROR IN ALEXANDER OPACITY TABLES:\002/1"
	    "x,\002EXPECTED AND ACTUAL T\002,i3,2f7.3,\002 RUN STOPPED\002)";

    /* System generated locals */
    olist o__1;
    cllist cl__1;

    /* Builtin functions */
    integer f_open(olist *), s_rsfe(cilist *), do_fio(integer *, char *, 
	    ftnlen), e_rsfe(void), s_wsfe(cilist *), e_wsfe(void);
    /* Subroutine */ void s_stop(char *, ftnlen);
    integer f_clos(cllist *);

    /* Local variables */
    static integer i__, j, k;
    static doublereal t;
    static integer ii, jj, kk;
    static doublereal xx, zz, xtest, r0grtab[19];

    /* Fortran I/O blocks */
    static cilist io___3 = { 0, 0, 0, fmt_10, 0 };
    static cilist io___6 = { 0, 6, 0, fmt_15, 0 };
    static cilist io___7 = { 0, 0, 0, fmt_20, 0 };
    static cilist io___11 = { 0, 6, 0, fmt_25, 0 };
    static cilist io___14 = { 0, 0, 0, fmt_30, 0 };
    static cilist io___16 = { 0, 6, 0, fmt_35, 0 };
    static cilist io___17 = { 0, 0, 0, fmt_10, 0 };
    static cilist io___19 = { 0, 6, 0, fmt_15, 0 };
    static cilist io___20 = { 0, 0, 0, fmt_20, 0 };
    static cilist io___21 = { 0, 6, 0, fmt_25, 0 };
    static cilist io___22 = { 0, 0, 0, fmt_30, 0 };
    static cilist io___23 = { 0, 6, 0, fmt_35, 0 };


/*     ALEX LOW T OPACITY COMMON BLOCKS */
/* MHP 8/25 Removed file names from common block */
/*     LOCAL ARRAYS */
/* INITIALIZE INDEX OF PREVIOUS CLOSEST POINTS AND ENVELOPE ABUNDANCES */
    o__1.oerr = 0;
    o__1.ounit = alex06_1.ialex06;
    o__1.ofnmlen = 256;
    o__1.ofnm = falex06;
    o__1.orl = 0;
    o__1.osta = 0;
    o__1.oacc = 0;
    o__1.ofm = 0;
    o__1.oblnk = 0;
    f_open(&o__1);
/* READ IN INITIAL X AND Z; ENSURE THAT THEY HAVE THE EXPECTED VALUES. */
    for (i__ = 1; i__ <= 8; ++i__) {
	for (ii = 1; ii <= 16; ++ii) {
/* INDEX FOR STORING TABLES : 15 SETS OF METAL ABUNDANCE WITH 7 SETS */
/* OF HYDROGEN FOR EACH.  THESE ARE STORED IN THE ORDER (X,Z) OF */
/* (0,0),(0,0.1),...(0.9,0),(0.9,0.1).  The final tables are defined */
/* at X = 1-Z except for the 0.1 Z case (already read in at X=0.9). */
/* HEADER INFORMATION: X AND Z; CHECK FOR CONSISTENCY */
	    io___3.ciunit = alex06_1.ialex06;
	    s_rsfe(&io___3);
	    do_fio(&c__1, (char *)&xx, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&zz, (ftnlen)sizeof(doublereal));
	    e_rsfe();
	    if (xx != galot06_1.xxg06[i__ - 1] || zz != galot06_1.zzg06[ii - 
		    1]) {
		s_wsfe(&io___6);
		do_fio(&c__1, (char *)&galot06_1.xxg06[i__ - 1], (ftnlen)
			sizeof(doublereal));
		do_fio(&c__1, (char *)&xx, (ftnlen)sizeof(doublereal));
		do_fio(&c__1, (char *)&galot06_1.zzg06[ii - 1], (ftnlen)
			sizeof(doublereal));
		do_fio(&c__1, (char *)&zz, (ftnlen)sizeof(doublereal));
		e_wsfe();
/*               STOP */
	    }
	    io___7.ciunit = alex06_1.ialex06;
	    s_rsfe(&io___7);
	    for (k = 1; k <= 19; ++k) {
		do_fio(&c__1, (char *)&r0grtab[k - 1], (ftnlen)sizeof(
			doublereal));
	    }
	    e_rsfe();
	    for (kk = 1; kk <= 16; ++kk) {
		if (r0grtab[kk - 1] != galot06_1.r0gr06[kk - 1]) {
		    s_wsfe(&io___11);
		    do_fio(&c__1, (char *)&kk, (ftnlen)sizeof(integer));
		    do_fio(&c__1, (char *)&galot06_1.r0gr06[kk - 1], (ftnlen)
			    sizeof(doublereal));
		    do_fio(&c__1, (char *)&r0grtab[kk - 1], (ftnlen)sizeof(
			    doublereal));
		    e_wsfe();
		    s_stop("", (ftnlen)0);
		}
	    }
	    jj = (i__ - 1 << 4) + ii;
/* OPACITY INFORMATION AT EACH SHELL: CHECK FOR CONSISTENCY WITH T. */
/* STORE IN A NUMXZ*NUMT*NUMR ARRAY. */
	    for (j = 85; j >= 1; --j) {
		io___14.ciunit = alex06_1.ialex06;
		s_rsfe(&io___14);
		do_fio(&c__1, (char *)&t, (ftnlen)sizeof(doublereal));
		for (k = 1; k <= 19; ++k) {
		    do_fio(&c__1, (char *)&alot06all_1.captalex06[jj + (j + k 
			    * 85) * 143 - 12299], (ftnlen)sizeof(doublereal));
		}
		e_rsfe();
		if (t != galot06_1.tgr06[j - 1]) {
		    s_wsfe(&io___16);
		    do_fio(&c__1, (char *)&j, (ftnlen)sizeof(integer));
		    do_fio(&c__1, (char *)&galot06_1.tgr06[j - 1], (ftnlen)
			    sizeof(doublereal));
		    do_fio(&c__1, (char *)&t, (ftnlen)sizeof(doublereal));
		    e_wsfe();
		    s_stop("", (ftnlen)0);
		}
	    }
	}
    }
/* FINAL SET OF X TABLES ARE DEFINED AT X = 1 - Z AND THERE IS NOT ONE FOR */
/* Z = 0.1 (ALREADY READ IN AT X=0.9). */
    for (ii = 1; ii <= 15; ++ii) {
/* INDEX FOR STORING TABLES : 15 SETS OF METAL ABUNDANCE WITH 7 SETS */
/* OF HYDROGEN FOR EACH.  THESE ARE STORED IN THE ORDER (X,Z) OF */
/* (0,0),(0,0.1),...(0.9,0),(0.9,0.1).  The final tables are defined */
/* at X = 1-Z except for the 0.1 Z case (already read in at X=0.9). */
/* HEADER INFORMATION: X AND Z; CHECK FOR CONSISTENCY */
	io___17.ciunit = alex06_1.ialex06;
	s_rsfe(&io___17);
	do_fio(&c__1, (char *)&xx, (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&zz, (ftnlen)sizeof(doublereal));
	e_rsfe();
	xtest = 1. - galot06_1.zzg06[ii - 1];
	if (xx != xtest || zz != galot06_1.zzg06[ii - 1]) {
	    s_wsfe(&io___19);
	    do_fio(&c__1, (char *)&xtest, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&xx, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&galot06_1.zzg06[ii - 1], (ftnlen)sizeof(
		    doublereal));
	    do_fio(&c__1, (char *)&zz, (ftnlen)sizeof(doublereal));
	    e_wsfe();
	    s_stop("", (ftnlen)0);
	}
	io___20.ciunit = alex06_1.ialex06;
	s_rsfe(&io___20);
	for (k = 1; k <= 19; ++k) {
	    do_fio(&c__1, (char *)&r0grtab[k - 1], (ftnlen)sizeof(doublereal))
		    ;
	}
	e_rsfe();
	for (kk = 1; kk <= 16; ++kk) {
	    if (r0grtab[kk - 1] != galot06_1.r0gr06[kk - 1]) {
		s_wsfe(&io___21);
		do_fio(&c__1, (char *)&kk, (ftnlen)sizeof(integer));
		do_fio(&c__1, (char *)&galot06_1.r0gr06[kk - 1], (ftnlen)
			sizeof(doublereal));
		do_fio(&c__1, (char *)&r0grtab[kk - 1], (ftnlen)sizeof(
			doublereal));
		e_wsfe();
		s_stop("", (ftnlen)0);
	    }
	}
	jj = ii + 128;
/* OPACITY INFORMATION AT EACH SHELL: CHECK FOR CONSISTENCY WITH T. */
/* STORE IN A NUMXZ*NUMT*NUMR ARRAY. */
	for (j = 85; j >= 1; --j) {
	    io___22.ciunit = alex06_1.ialex06;
	    s_rsfe(&io___22);
	    do_fio(&c__1, (char *)&t, (ftnlen)sizeof(doublereal));
	    for (k = 1; k <= 19; ++k) {
		do_fio(&c__1, (char *)&alot06all_1.captalex06[jj + (j + k * 
			85) * 143 - 12299], (ftnlen)sizeof(doublereal));
	    }
	    e_rsfe();
	    if (t != galot06_1.tgr06[j - 1]) {
		s_wsfe(&io___23);
		do_fio(&c__1, (char *)&j, (ftnlen)sizeof(integer));
		do_fio(&c__1, (char *)&galot06_1.tgr06[j - 1], (ftnlen)sizeof(
			doublereal));
		do_fio(&c__1, (char *)&t, (ftnlen)sizeof(doublereal));
		e_wsfe();
		s_stop("", (ftnlen)0);
	    }
	}
    }
    cl__1.cerr = 0;
    cl__1.cunit = alex06_1.ialex06;
    cl__1.csta = 0;
    f_clos(&cl__1);
/* INITIALIZE FIXED Z,X TABLE */
    for (i__ = 1; i__ <= 85; ++i__) {
	for (j = 1; j <= 19; ++j) {
	    alot06_1.capalex06[i__ + j * 85 - 86] = alot06all_1.captalex06[(
		    i__ + j * 85) * 143 - 12298];
	}
    }
    return 0;
} /* readalex06_ */

