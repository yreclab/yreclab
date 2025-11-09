/* rdzlaol.f -- translated by f2c (version 20061008).
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
    doublereal zolaol[5408]	/* was [104][52] */, zot[52], zorho[104];
    integer numrhoz, numtz;
} zlaol_;

#define zlaol_1 zlaol_

struct {
    integer ilast, idebug, itrack, ishort, imilne, imodpt, istor, iowr;
} luout_;

#define luout_1 luout_

struct {
    doublereal zlaol1, zlaol2, zopal1, zopal2, zopal951, zalex1, zkur1, zkur2,
	     tmolmin, tmolmax;
    logical lalex06, llaol89, lopal92, lopal95, lkur90, lalex95, l2z;
} newopac_;

#define newopac_1 newopac_

/* Table of constant values */

static integer c__1 = 1;
static integer c__9 = 9;



/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */
/*     READ PURE Z LAOL89 */
/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */
/* Subroutine */ int rdzlaol_(char *fpurez, ftnlen fpurez_len)
{
    /* Format strings */
    static char fmt_100[] = "(/,18x,i2,9x,i3,14x,i3)";
    static char fmt_120[] = "(47x,f8.5,//,1p6e12.5,/,1p4e12.5)";
    static char fmt_131[] = "(54x,f8.5,///////)";
    static char fmt_140[] = "(/,(1p6e12.5))";
    static char fmt_150[] = "(/,(1p6e12.5))";
    static char fmt_160[] = "(/,(1p6e12.5))";
    static char fmt_170[] = "(1x)";
    static char fmt_200[] = "(1x)";
    static char fmt_210[] = "(1p6e12.5)";

    /* System generated locals */
    integer i__1, i__2;
    olist o__1;
    cllist cl__1;

    /* Builtin functions */
    integer f_open(olist *), s_rsfe(cilist *), do_fio(integer *, char *, 
	    ftnlen), e_rsfe(void), s_wsle(cilist *), do_lio(integer *, 
	    integer *, char *, ftnlen), e_wsle(void);
    /* Subroutine */ void s_stop(char *, ftnlen);
    integer f_clos(cllist *);

    /* Local variables */
    static integer i__, n, ii, ir, it;
    static doublereal dummy[104];

    /* Fortran I/O blocks */
    static cilist io___1 = { 0, 0, 0, fmt_100, 0 };
    static cilist io___3 = { 0, 0, 0, 0, 0 };
    static cilist io___4 = { 0, 0, 0, fmt_120, 0 };
    static cilist io___7 = { 0, 0, 0, fmt_131, 0 };
    static cilist io___8 = { 0, 0, 0, fmt_140, 0 };
    static cilist io___9 = { 0, 0, 0, fmt_150, 0 };
    static cilist io___11 = { 0, 0, 0, fmt_160, 0 };
    static cilist io___12 = { 0, 0, 0, fmt_170, 0 };
    static cilist io___14 = { 0, 0, 0, fmt_200, 0 };
    static cilist io___15 = { 0, 0, 0, fmt_210, 0 };


/* MHP 10/02 vector v not used */
/*      SUBROUTINE RDZLAOL(V) */
/* ZOPAL952, ZALEX2 */
/* MHP 8/25 Removed character file names from common block */
/* DBG 12/95 ARRAYS FOR PURE Z TABLE */
/* OPACITY COMMON BLOCKS - modified 3/09 */
/*      DIMENSION V(12) */
    o__1.oerr = 0;
    o__1.ounit = nwlaol_1.iopurez;
    o__1.ofnmlen = 256;
    o__1.ofnm = fpurez;
    o__1.orl = 0;
    o__1.osta = "OLD";
    o__1.oacc = 0;
    o__1.ofm = "FORMATTED";
    o__1.oblnk = 0;
    f_open(&o__1);
/*     READ IN ARRAY SIZES */
    io___1.ciunit = nwlaol_1.iopurez;
    s_rsfe(&io___1);
    do_fio(&c__1, (char *)&n, (ftnlen)sizeof(integer));
    do_fio(&c__1, (char *)&zlaol_1.numrhoz, (ftnlen)sizeof(integer));
    do_fio(&c__1, (char *)&zlaol_1.numtz, (ftnlen)sizeof(integer));
    e_rsfe();
    if (n != 1 || zlaol_1.numrhoz > 104 || zlaol_1.numtz > 52) {
	io___3.ciunit = luout_1.ishort;
	s_wsle(&io___3);
	do_lio(&c__9, &c__1, " Z OPACITY INPUT ERROR.", (ftnlen)23);
	e_wsle();
	s_stop("", (ftnlen)0);
    }
    io___4.ciunit = nwlaol_1.iopurez;
    s_rsfe(&io___4);
    for (i__ = 1; i__ <= 11; ++i__) {
	do_fio(&c__1, (char *)&dummy[i__ - 1], (ftnlen)sizeof(doublereal));
    }
    e_rsfe();
    io___7.ciunit = nwlaol_1.iopurez;
    s_rsfe(&io___7);
    do_fio(&c__1, (char *)&dummy[0], (ftnlen)sizeof(doublereal));
    e_rsfe();
/*     READ IN H MASS FRACTIONS OF TABLE */
    io___8.ciunit = nwlaol_1.iopurez;
    s_rsfe(&io___8);
    do_fio(&c__1, (char *)&dummy[0], (ftnlen)sizeof(doublereal));
    e_rsfe();
/*     READ IN DENSITY GRID OF TABLE */
    io___9.ciunit = nwlaol_1.iopurez;
    s_rsfe(&io___9);
    i__1 = zlaol_1.numrhoz;
    for (ii = 1; ii <= i__1; ++ii) {
	do_fio(&c__1, (char *)&zlaol_1.zorho[ii - 1], (ftnlen)sizeof(
		doublereal));
    }
    e_rsfe();
/*     READ IN TEMPERATURE GRID OF TABLE */
    io___11.ciunit = nwlaol_1.iopurez;
    s_rsfe(&io___11);
    i__1 = zlaol_1.numtz;
    for (ii = 1; ii <= i__1; ++ii) {
	do_fio(&c__1, (char *)&zlaol_1.zot[ii - 1], (ftnlen)sizeof(doublereal)
		);
    }
    e_rsfe();
/*     READ IN PURE Z OPACITIES */
    io___12.ciunit = nwlaol_1.iopurez;
    s_rsfe(&io___12);
    e_rsfe();
    i__1 = zlaol_1.numrhoz;
    for (ir = 1; ir <= i__1; ++ir) {
	io___14.ciunit = nwlaol_1.iopurez;
	s_rsfe(&io___14);
	e_rsfe();
	io___15.ciunit = nwlaol_1.iopurez;
	s_rsfe(&io___15);
	i__2 = zlaol_1.numtz;
	for (it = 1; it <= i__2; ++it) {
	    do_fio(&c__1, (char *)&zlaol_1.zolaol[ir + it * 104 - 105], (
		    ftnlen)sizeof(doublereal));
	}
	e_rsfe();
    }
    cl__1.cerr = 0;
    cl__1.cunit = nwlaol_1.iopurez;
    cl__1.csta = 0;
    f_clos(&cl__1);
    return 0;
} /* rdzlaol_ */

