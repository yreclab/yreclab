/* zsulaol.f -- translated by f2c (version 20100827).
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
    doublereal zolaol[5408]	/* was [104][52] */, zot[52], zorho[104];
    integer numrhoz, numtz;
} zlaol_;

#define zlaol_1 zlaol_

struct {
    doublereal zslaoll[5408]	/* was [104][52] */, zsrhol[5408]	/* 
	    was [104][52] */, zsdorl[5408]	/* was [104][52] */;
    integer numrsz[52];
} zslaol_;

#define zslaol_1 zslaol_

/* Table of constant values */

static doublereal c_b2 = 1e30;



/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */
/*     SPLINE PURE Z LAOL89 */
/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */
/* Subroutine */ int zsulaol_(void)
{
    /* System generated locals */
    integer i__1, i__2;

    /* Builtin functions */
    double d_lg10(doublereal *);

    /* Local variables */
    static integer ir, it;
    static doublereal tr[104], top[104], tdor[104];
    static integer nums;
    extern /* Subroutine */ int cspline_(doublereal *, doublereal *, integer *
	    , doublereal *, doublereal *, doublereal *);

/* DBG 4/94 Modified to do ZRAMP stuff. */
/* DBG 12/95 ARRAYS FOR PURE Z TABLE */
    i__1 = zlaol_1.numtz;
    for (it = 1; it <= i__1; ++it) {
	zlaol_1.zot[it - 1] = d_lg10(&zlaol_1.zot[it - 1]);
    }
    i__1 = zlaol_1.numtz;
    for (it = 1; it <= i__1; ++it) {
	nums = 0;
	i__2 = zlaol_1.numrhoz;
	for (ir = 1; ir <= i__2; ++ir) {
	    zslaol_1.zslaoll[ir + it * 104 - 105] = 0.;
	    zslaol_1.zsrhol[ir + it * 104 - 105] = 0.;
	    zslaol_1.zsdorl[ir + it * 104 - 105] = 0.;
	    if (zlaol_1.zolaol[ir + it * 104 - 105] != 0.) {
		++nums;
		top[nums - 1] = d_lg10(&zlaol_1.zolaol[ir + it * 104 - 105]);
		tr[nums - 1] = d_lg10(&zlaol_1.zorho[ir - 1]);
	    }
	}
	if (nums >= 4) {
	    zslaol_1.numrsz[it - 1] = nums;
	    cspline_(tr, top, &nums, &c_b2, &c_b2, tdor);
	    i__2 = nums;
	    for (ir = 1; ir <= i__2; ++ir) {
		zslaol_1.zslaoll[ir + it * 104 - 105] = top[ir - 1];
		zslaol_1.zsrhol[ir + it * 104 - 105] = tr[ir - 1];
		zslaol_1.zsdorl[ir + it * 104 - 105] = tdor[ir - 1];
	    }
	} else {
	    zslaol_1.numrsz[it - 1] = 0;
	}
    }
    return 0;
} /* zsulaol_ */

