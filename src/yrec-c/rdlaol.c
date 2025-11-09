/* rdlaol.f -- translated by f2c (version 20061008).
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
    doublereal olaol[64896]	/* was [12][104][52] */, oxa[12], ot[52], 
	    orho[104], tollaol;
    integer iolaol, numofxyz, numrho, numt;
    logical llaol, lpurez;
    integer iopurez;
} nwlaol_;

#define nwlaol_1 nwlaol_

struct {
    doublereal olaol2[64896]	/* was [12][104][52] */, oxa2[12], ot2[52], 
	    orho2[104];
    integer nxyz2, nrho2, nt2;
} nwlaol2_;

#define nwlaol2_1 nwlaol2_

struct {
    doublereal rsclzc[50], rsclzm1[50], rsclzm2[50];
    integer iolaol2, ioopal2, nk;
    logical lzramp;
} zramp_;

#define zramp_1 zramp_

struct {
    integer ilast, idebug, itrack, ishort, imilne, imodpt, istor, iowr;
} luout_;

#define luout_1 luout_

struct {
    doublereal cdh, etadh0, etadh1, zdh[18], xxdh, yydh, zzdh, dhnue[18];
    logical ldh;
} debhu_;

#define debhu_1 debhu_

struct {
    doublereal zlaol1, zlaol2, zopal1, zopal2, zopal951, zalex1, zkur1, zkur2,
	     tmolmin, tmolmax;
    logical lalex06, llaol89, lopal92, lopal95, lkur90, lalex95, l2z;
} newopac_;

#define newopac_1 newopac_

/* Table of constant values */

static integer c__1 = 1;
static integer c__9 = 9;
static integer c__18 = 18;



/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */
/*     READ LAOL89 */
/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */
/* Subroutine */ int rdlaol_(doublereal *v, char *flaol, char *flaol2, ftnlen 
	flaol_len, ftnlen flaol2_len)
{
    /* Format strings */
    static char fmt_100[] = "(/,18x,i2,9x,i3,14x,i3)";
    static char fmt_120[] = "(47x,f8.5,//,1p6e12.5,/,1p4e12.5)";
    static char fmt_130[] = "(54x,f8.5,/////,1p6e12.5,/,1p6e12.5,/1p6e12.5)";
    static char fmt_140[] = "(/,(1p6e12.5))";
    static char fmt_150[] = "(/,(1p6e12.5))";
    static char fmt_160[] = "(/,(1p6e12.5))";
    static char fmt_170[] = "(1x)";
    static char fmt_200[] = "(1x)";
    static char fmt_210[] = "(1p6e12.5)";

    /* System generated locals */
    integer i__1, i__2, i__3;
    olist o__1;
    cllist cl__1;

    /* Builtin functions */
    integer f_open(olist *), s_rsfe(cilist *), do_fio(integer *, char *, 
	    ftnlen), e_rsfe(void), s_wsle(cilist *), do_lio(integer *, 
	    integer *, char *, ftnlen), e_wsle(void);
    /* Subroutine */ void s_stop(char *, ftnlen);
    integer f_clos(cllist *);

    /* Local variables */
    static doublereal v2[12];
    static integer ii, ir, it, ix;
    static doublereal zdh2[18], zhit, zlot, zhit2, zlot2;

    /* Fortran I/O blocks */
    static cilist io___1 = { 0, 0, 0, fmt_100, 0 };
    static cilist io___2 = { 0, 0, 0, 0, 0 };
    static cilist io___3 = { 0, 0, 0, fmt_120, 0 };
    static cilist io___5 = { 0, 0, 0, fmt_130, 0 };
    static cilist io___7 = { 0, 0, 0, fmt_140, 0 };
    static cilist io___9 = { 0, 0, 0, fmt_150, 0 };
    static cilist io___10 = { 0, 0, 0, fmt_160, 0 };
    static cilist io___11 = { 0, 0, 0, fmt_170, 0 };
    static cilist io___14 = { 0, 0, 0, fmt_200, 0 };
    static cilist io___15 = { 0, 0, 0, fmt_210, 0 };
    static cilist io___17 = { 0, 0, 0, fmt_100, 0 };
    static cilist io___18 = { 0, 0, 0, 0, 0 };
    static cilist io___19 = { 0, 0, 0, fmt_120, 0 };
    static cilist io___22 = { 0, 0, 0, fmt_130, 0 };
    static cilist io___25 = { 0, 0, 0, fmt_140, 0 };
    static cilist io___26 = { 0, 0, 0, fmt_150, 0 };
    static cilist io___27 = { 0, 0, 0, fmt_160, 0 };
    static cilist io___28 = { 0, 0, 0, fmt_170, 0 };
    static cilist io___29 = { 0, 0, 0, fmt_200, 0 };
    static cilist io___30 = { 0, 0, 0, fmt_210, 0 };


/* DBG 4/94 MOdified to read in second table for ZRAMP core stuff */
/* MHP 8/25 Removed character file names from common block */
/* DBG 4/94 New common block for second opacity table */
/* MHP 8/25 Removed character file names from common block */
/* DBG 7/92 COMMON BLOCK ADDED TO COMPUTE DEBYE-HUCKEL CORRECTION. */
/* OPACITY COMMON BLOCKS - modified 3/09 */
    /* Parameter adjustments */
    --v;

    /* Function Body */
    o__1.oerr = 0;
    o__1.ounit = nwlaol_1.iolaol;
    o__1.ofnmlen = 256;
    o__1.ofnm = flaol;
    o__1.orl = 0;
    o__1.osta = "OLD";
    o__1.oacc = 0;
    o__1.ofm = "FORMATTED";
    o__1.oblnk = 0;
    f_open(&o__1);
/*     READ IN ARRAY SIZES */
    io___1.ciunit = nwlaol_1.iolaol;
    s_rsfe(&io___1);
    do_fio(&c__1, (char *)&nwlaol_1.numofxyz, (ftnlen)sizeof(integer));
    do_fio(&c__1, (char *)&nwlaol_1.numrho, (ftnlen)sizeof(integer));
    do_fio(&c__1, (char *)&nwlaol_1.numt, (ftnlen)sizeof(integer));
    e_rsfe();
    if (nwlaol_1.numofxyz > 11 || nwlaol_1.numrho > 104 || nwlaol_1.numt > 52)
	     {
	io___2.ciunit = luout_1.ishort;
	s_wsle(&io___2);
	do_lio(&c__9, &c__1, " OPACITY ARRAY TOO LARGE.", (ftnlen)25);
	e_wsle();
	s_stop("", (ftnlen)0);
    }
/*     READ IN RELATIVE ABUNDANCES BY WEIGTH OF THE METALS C,N,O,NE,NA, */
/*     MG,SI,AR,FE (THE COX&STEWART MIX).  MIXTURE IS FOR THE ZLOT PART */
/*     OF THE OPACITY TABLE WITH LAOL RELATIVE ABUNDANCES SCALED */
/*     TO SUM TO ZLOT. */
    io___3.ciunit = nwlaol_1.iolaol;
    s_rsfe(&io___3);
    do_fio(&c__1, (char *)&zlot, (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&v[6], (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&v[9], (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&v[8], (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&v[11], (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&v[1], (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&v[3], (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&v[2], (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&v[5], (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&v[10], (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&v[4], (ftnlen)sizeof(doublereal));
    e_rsfe();
/*     READ ZHIT THE METAL ABUNDANCE FOR THE HIT PART OF TABLE. */
/* DBG 7/92 NEED RELATIVE ABUNDANCES OF METALS FOR DEBYE-HUCKEL */
/*     CORRECTION. 18 ELEMENTS, C,N,O,Ne,Na,Mg,Al,Si,P, */
/*     S,Cl,Ar,Ca,Ti,Cr,Mn,Fe,Ni scaled to sum to ZHIT */
    io___5.ciunit = nwlaol_1.iolaol;
    s_rsfe(&io___5);
    do_fio(&c__1, (char *)&zhit, (ftnlen)sizeof(doublereal));
    do_fio(&c__18, (char *)&debhu_1.zdh[0], (ftnlen)sizeof(doublereal));
    e_rsfe();
/* 130 FORMAT(54X,F8.5,///////) */
/*     READ IN H MASS FRACTIONS OF TABLE */
    io___7.ciunit = nwlaol_1.iolaol;
    s_rsfe(&io___7);
    i__1 = nwlaol_1.numofxyz;
    for (ii = 1; ii <= i__1; ++ii) {
	do_fio(&c__1, (char *)&nwlaol_1.oxa[ii - 1], (ftnlen)sizeof(
		doublereal));
    }
    e_rsfe();
/*     READ IN DENSITY GRID OF TABLE */
    io___9.ciunit = nwlaol_1.iolaol;
    s_rsfe(&io___9);
    i__1 = nwlaol_1.numrho;
    for (ii = 1; ii <= i__1; ++ii) {
	do_fio(&c__1, (char *)&nwlaol_1.orho[ii - 1], (ftnlen)sizeof(
		doublereal));
    }
    e_rsfe();
/*     READ IN TEMPERATURE GRID OF TABLE */
    io___10.ciunit = nwlaol_1.iolaol;
    s_rsfe(&io___10);
    i__1 = nwlaol_1.numt;
    for (ii = 1; ii <= i__1; ++ii) {
	do_fio(&c__1, (char *)&nwlaol_1.ot[ii - 1], (ftnlen)sizeof(doublereal)
		);
    }
    e_rsfe();
/*     READ IN OPACITIES */
    io___11.ciunit = nwlaol_1.iolaol;
    s_rsfe(&io___11);
    e_rsfe();
    i__1 = nwlaol_1.numofxyz;
    for (ix = 1; ix <= i__1; ++ix) {
	i__2 = nwlaol_1.numrho;
	for (ir = 1; ir <= i__2; ++ir) {
	    io___14.ciunit = nwlaol_1.iolaol;
	    s_rsfe(&io___14);
	    e_rsfe();
	    io___15.ciunit = nwlaol_1.iolaol;
	    s_rsfe(&io___15);
	    i__3 = nwlaol_1.numt;
	    for (it = 1; it <= i__3; ++it) {
		do_fio(&c__1, (char *)&nwlaol_1.olaol[ix + (ir + it * 104) * 
			12 - 1261], (ftnlen)sizeof(doublereal));
	    }
	    e_rsfe();
	}
    }
    cl__1.cerr = 0;
    cl__1.cunit = nwlaol_1.iolaol;
    cl__1.csta = 0;
    f_clos(&cl__1);


/* DBG 4/94 New stuff follows */
    if (newopac_1.l2z) {
	o__1.oerr = 0;
	o__1.ounit = zramp_1.iolaol2;
	o__1.ofnmlen = 256;
	o__1.ofnm = flaol2;
	o__1.orl = 0;
	o__1.osta = "OLD";
	o__1.oacc = 0;
	o__1.ofm = "FORMATTED";
	o__1.oblnk = 0;
	f_open(&o__1);
/*        READ IN ARRAY SIZES */
	io___17.ciunit = zramp_1.iolaol2;
	s_rsfe(&io___17);
	do_fio(&c__1, (char *)&nwlaol2_1.nxyz2, (ftnlen)sizeof(integer));
	do_fio(&c__1, (char *)&nwlaol2_1.nrho2, (ftnlen)sizeof(integer));
	do_fio(&c__1, (char *)&nwlaol2_1.nt2, (ftnlen)sizeof(integer));
	e_rsfe();
	if (nwlaol2_1.nxyz2 > 11 || nwlaol2_1.nrho2 > 104 || nwlaol2_1.nt2 > 
		52) {
	    io___18.ciunit = luout_1.ishort;
	    s_wsle(&io___18);
	    do_lio(&c__9, &c__1, " SECOND OPACITY ARRAY TOO LARGE.", (ftnlen)
		    32);
	    e_wsle();
	    s_stop("", (ftnlen)0);
	}
/*        READ IN RELATIVE ABUNDANCES BY WEIGTH OF THE METALS C,N,O,NE,NA, */
/*        MG,SI,AR,FE (THE COX&STEWART MIX).  MIXTURE IS FOR THE ZLOT PART */
/*        OF THE OPACITY TABLE WITH LAOL RELATIVE ABUNDANCES SCALED */
/*        TO SUM TO ZLOT2. */
	io___19.ciunit = zramp_1.iolaol2;
	s_rsfe(&io___19);
	do_fio(&c__1, (char *)&zlot2, (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&v2[5], (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&v2[8], (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&v2[7], (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&v2[10], (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&v2[0], (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&v2[2], (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&v2[1], (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&v2[4], (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&v2[9], (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&v2[3], (ftnlen)sizeof(doublereal));
	e_rsfe();
/*        READ ZHIT2 THE METAL ABUNDANCE FOR THE HIT PART OF TABLE. */
/*        DBG 7/92 NEED RELATIVE ABUNDANCES OF METALS FOR DEBYE-HUCKEL */
/*        CORRECTION. 18 ELEMENTS, C,N,O,Ne,Na,Mg,Al,Si,P, */
/*        S,Cl,Ar,Ca,Ti,Cr,Mn,Fe,Ni scaled to sum to ZHIT */
	io___22.ciunit = zramp_1.iolaol2;
	s_rsfe(&io___22);
	do_fio(&c__1, (char *)&zhit2, (ftnlen)sizeof(doublereal));
	do_fio(&c__18, (char *)&zdh2[0], (ftnlen)sizeof(doublereal));
	e_rsfe();
/*        READ IN H MASS FRACTIONS OF TABLE */
	io___25.ciunit = zramp_1.iolaol2;
	s_rsfe(&io___25);
	i__1 = nwlaol2_1.nxyz2;
	for (ii = 1; ii <= i__1; ++ii) {
	    do_fio(&c__1, (char *)&nwlaol2_1.oxa2[ii - 1], (ftnlen)sizeof(
		    doublereal));
	}
	e_rsfe();
/*        READ IN DENSITY GRID OF TABLE */
	io___26.ciunit = zramp_1.iolaol2;
	s_rsfe(&io___26);
	i__1 = nwlaol2_1.nrho2;
	for (ii = 1; ii <= i__1; ++ii) {
	    do_fio(&c__1, (char *)&nwlaol2_1.orho2[ii - 1], (ftnlen)sizeof(
		    doublereal));
	}
	e_rsfe();
/*        READ IN TEMPERATURE GRID OF TABLE */
	io___27.ciunit = zramp_1.iolaol2;
	s_rsfe(&io___27);
	i__1 = nwlaol2_1.nt2;
	for (ii = 1; ii <= i__1; ++ii) {
	    do_fio(&c__1, (char *)&nwlaol2_1.ot2[ii - 1], (ftnlen)sizeof(
		    doublereal));
	}
	e_rsfe();
/*        READ IN OPACITIES */
	io___28.ciunit = zramp_1.iolaol2;
	s_rsfe(&io___28);
	e_rsfe();
	i__1 = nwlaol2_1.nxyz2;
	for (ix = 1; ix <= i__1; ++ix) {
	    i__2 = nwlaol2_1.nrho2;
	    for (ir = 1; ir <= i__2; ++ir) {
		io___29.ciunit = zramp_1.iolaol2;
		s_rsfe(&io___29);
		e_rsfe();
		io___30.ciunit = zramp_1.iolaol2;
		s_rsfe(&io___30);
		i__3 = nwlaol2_1.nt2;
		for (it = 1; it <= i__3; ++it) {
		    do_fio(&c__1, (char *)&nwlaol2_1.olaol2[ix + (ir + it * 
			    104) * 12 - 1261], (ftnlen)sizeof(doublereal));
		}
		e_rsfe();
	    }
	}
	cl__1.cerr = 0;
	cl__1.cunit = zramp_1.iolaol2;
	cl__1.csta = 0;
	f_clos(&cl__1);
    }
    return 0;
} /* rdlaol_ */

