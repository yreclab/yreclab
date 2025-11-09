/* sulaol.f -- translated by f2c (version 20061008).
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
    doublereal slaoll[64896]	/* was [12][104][52] */, srhol[64896]	/* 
	    was [12][104][52] */, sdorl[64896]	/* was [12][104][52] */;
    integer numrs[624]	/* was [12][52] */;
} slaol_;

#define slaol_1 slaol_

struct {
    doublereal slaoll2[64896]	/* was [12][104][52] */, srhol2[64896]	/* 
	    was [12][104][52] */, sdorl2[64896]	/* was [12][104][52] */;
    integer numrs2[624]	/* was [12][52] */;
} slaol2_;

#define slaol2_1 slaol2_

struct {
    doublereal rsclzc[50], rsclzm1[50], rsclzm2[50];
    integer iolaol2, ioopal2, nk;
    logical lzramp;
} zramp_;

#define zramp_1 zramp_

struct {
    doublereal zlaol1, zlaol2, zopal1, zopal2, zopal951, zalex1, zkur1, zkur2,
	     tmolmin, tmolmax;
    logical lalex06, llaol89, lopal92, lopal95, lkur90, lalex95, l2z;
} newopac_;

#define newopac_1 newopac_

/* Table of constant values */

static doublereal c_b2 = 1e30;



/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */
/*     SPLINE LAOL89 */
/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */
/* Subroutine */ int sulaol_(void)
{
    /* System generated locals */
    integer i__1, i__2, i__3;

    /* Builtin functions */
    double d_lg10(doublereal *);

    /* Local variables */
    static integer ir, it, ix;
    static doublereal tr[104], top[104], tdor[104];
    static integer nums;
    extern /* Subroutine */ int cspline_(doublereal *, doublereal *, integer *
	    , doublereal *, doublereal *, doublereal *);

/* DBG 4/94 Modified to do ZRAMP stuff. */
/* MHP 8/25 Removed unused variables */
/*      CHARACTER*256 FLAOL2 */
/*      CHARACTER*256 FLAOL, FPUREZ */
/* ZOPAL952, ZALEX2 */
/* MHP 8/25 Removed character file names from common block */
/* MHP 8/25 Removed character file names from common block */
/* OPACITY COMMON BLOCKS - modified 3/09 */
    i__1 = nwlaol_1.numt;
    for (it = 1; it <= i__1; ++it) {
	nwlaol_1.ot[it - 1] = d_lg10(&nwlaol_1.ot[it - 1]);
    }
    i__1 = nwlaol_1.numofxyz;
    for (ix = 1; ix <= i__1; ++ix) {
	i__2 = nwlaol_1.numt;
	for (it = 1; it <= i__2; ++it) {
	    nums = 0;
	    i__3 = nwlaol_1.numrho;
	    for (ir = 1; ir <= i__3; ++ir) {
		slaol_1.slaoll[ix + (ir + it * 104) * 12 - 1261] = 0.;
		slaol_1.srhol[ix + (ir + it * 104) * 12 - 1261] = 0.;
		slaol_1.sdorl[ix + (ir + it * 104) * 12 - 1261] = 0.;
		if (nwlaol_1.olaol[ix + (ir + it * 104) * 12 - 1261] != 0.) {
		    ++nums;
		    top[nums - 1] = d_lg10(&nwlaol_1.olaol[ix + (ir + it * 
			    104) * 12 - 1261]);
		    tr[nums - 1] = d_lg10(&nwlaol_1.orho[ir - 1]);
		}
	    }
	    if (nums >= 4) {
		slaol_1.numrs[ix + it * 12 - 13] = nums;
		cspline_(tr, top, &nums, &c_b2, &c_b2, tdor);
		i__3 = nums;
		for (ir = 1; ir <= i__3; ++ir) {
		    slaol_1.slaoll[ix + (ir + it * 104) * 12 - 1261] = top[ir 
			    - 1];
		    slaol_1.srhol[ix + (ir + it * 104) * 12 - 1261] = tr[ir - 
			    1];
		    slaol_1.sdorl[ix + (ir + it * 104) * 12 - 1261] = tdor[ir 
			    - 1];
		}
	    } else {
		slaol_1.numrs[ix + it * 12 - 13] = 0;
	    }
	}
    }
/* DBG 4/94 Do SPLINE on second opacity table if ZRAMP */
    if (newopac_1.l2z) {
	i__1 = nwlaol_1.numt;
	for (it = 1; it <= i__1; ++it) {
	    nwlaol2_1.ot2[it - 1] = d_lg10(&nwlaol2_1.ot2[it - 1]);
	}
	i__1 = nwlaol2_1.nxyz2;
	for (ix = 1; ix <= i__1; ++ix) {
	    i__2 = nwlaol2_1.nt2;
	    for (it = 1; it <= i__2; ++it) {
		nums = 0;
		i__3 = nwlaol2_1.nrho2;
		for (ir = 1; ir <= i__3; ++ir) {
		    slaol2_1.slaoll2[ix + (ir + it * 104) * 12 - 1261] = 0.;
		    slaol2_1.srhol2[ix + (ir + it * 104) * 12 - 1261] = 0.;
		    slaol2_1.sdorl2[ix + (ir + it * 104) * 12 - 1261] = 0.;
		    if (nwlaol2_1.olaol2[ix + (ir + it * 104) * 12 - 1261] != 
			    0.) {
			++nums;
			top[nums - 1] = d_lg10(&nwlaol2_1.olaol2[ix + (ir + 
				it * 104) * 12 - 1261]);
			tr[nums - 1] = d_lg10(&nwlaol2_1.orho2[ir - 1]);
		    }
		}
		if (nums >= 4) {
		    slaol2_1.numrs2[ix + it * 12 - 13] = nums;
		    cspline_(tr, top, &nums, &c_b2, &c_b2, tdor);
		    i__3 = nums;
		    for (ir = 1; ir <= i__3; ++ir) {
			slaol2_1.slaoll2[ix + (ir + it * 104) * 12 - 1261] = 
				top[ir - 1];
			slaol2_1.srhol2[ix + (ir + it * 104) * 12 - 1261] = 
				tr[ir - 1];
			slaol2_1.sdorl2[ix + (ir + it * 104) * 12 - 1261] = 
				tdor[ir - 1];
		    }
		} else {
		    slaol2_1.numrs2[ix + it * 12 - 13] = 0;
		}
	    }
	}
    }
    return 0;
} /* sulaol_ */

