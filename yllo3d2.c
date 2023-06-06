/* yllo3d2.f -- translated by f2c (version 20100827).
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
    doublereal gridt2[50], gridx2[3], grhot32[17];
} gllot2_;

#define gllot2_1 gllot2_

struct {
    doublereal opacity2[2550]	/* was [150][17] */;
    integer numxm2, numtm2;
} llot2_;

#define llot2_1 llot2_

struct {
    doublereal xenv42, zenv42, cford42[3400]	/* was [50][68] */;
    integer kipm12;
} llot42_;

#define llot42_1 llot42_

struct {
    integer m12, m22, m32;
} kipmll2_;

#define kipmll2_1 kipmll2_

/* Table of constant values */

static integer c__3 = 3;
static doublereal c_b7 = 10.;



/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */
/*    YLLO3D2 */
/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */
/* Subroutine */ int yllo3d2_(doublereal *dl, doublereal *tl, doublereal *x, 
	doublereal *of, doublereal *olf, doublereal *qodf, doublereal *qotf)
{
    /* System generated locals */
    integer i__1;
    doublereal d__1;

    /* Builtin functions */
    /* Subroutine */ int s_stop(char *, ftnlen);
    double pow_dd(doublereal *, doublereal *);

    /* Local variables */
    static doublereal o0, o1, t6;
    static integer im1;
    static doublereal ol0, ol1, qod0, qod1, qot0, qot1, qodi;
    static logical lone;
    static doublereal qoti, rhot3, grdnt;
    extern /* Subroutine */ int findex_(doublereal *, integer *, doublereal *,
	     integer *), yllo2d2_(doublereal *, doublereal *, integer *, 
	    integer *, integer *, doublereal *, doublereal *, doublereal *, 
	    doublereal *);

/* DBG 5/94 opacity at different Z */
    lone = FALSE_;
/* INDEPENDENT PARAMETER IN LIVERMORE OPACITY TABLE; */
/* T6 = LN(T/10E6) */
    t6 = *tl - 6.;
/* RHOT3 = LN(RHO/(T/10E6)**3) */
    rhot3 = *dl - t6 * 3.;
    if ((d__1 = llot42_1.xenv42 - *x, abs(d__1)) <= 1e-5) {
	kipmll2_1.m12 = 4;
	lone = TRUE_;
	goto L131;
    }
    for (im1 = 1; im1 <= 3; ++im1) {
	if ((d__1 = gllot2_1.gridx2[im1 - 1] - *x, abs(d__1)) <= 1e-5) {
	    kipmll2_1.m12 = im1;
	    lone = TRUE_;
	    goto L131;
	}
/* L130: */
    }
    findex_(gllot2_1.gridx2, &c__3, x, &kipmll2_1.m12);
    if (kipmll2_1.m12 < 0) {
	kipmll2_1.m12 = -kipmll2_1.m12;
    }
    if (kipmll2_1.m12 <= 1 && rhot3 > -1.) {
	kipmll2_1.m12 = 2;
    }
    if (kipmll2_1.m12 >= 3) {
	kipmll2_1.m12 = 2;
    }
    if (kipmll2_1.m12 <= 0) {
	s_stop(" ERROR IN X2 GRID", (ftnlen)17);
    }
L131:
    findex_(gllot2_1.gridt2, &llot2_1.numtm2, &t6, &kipmll2_1.m22);
    if (kipmll2_1.m22 < 0 && gllot2_1.gridt2[llot2_1.numtm2 - 1] == t6) {
	kipmll2_1.m22 = -kipmll2_1.m22;
    }
    if (kipmll2_1.m22 < 0) {
	s_stop(" T OUT OF TABLE ", (ftnlen)16);
    }
    yllo2d2_(&t6, &rhot3, &kipmll2_1.m12, &kipmll2_1.m22, &kipmll2_1.m32, &o0,
	     &ol0, &qod0, &qot0);
    if (lone) {
/* >>> USE ONLY ONE X TABLE */
	*olf = ol0;
	*of = o0;
	qodi = qod0;
	qoti = qot0;
    } else {
/* >>> LINEAR EXTRAPOLATION IN X */
	i__1 = kipmll2_1.m12 + 1;
	yllo2d2_(&t6, &rhot3, &i__1, &kipmll2_1.m22, &kipmll2_1.m32, &o1, &
		ol1, &qod1, &qot1);
	grdnt = (*x - gllot2_1.gridx2[kipmll2_1.m12 - 1]) / (gllot2_1.gridx2[
		kipmll2_1.m12] - gllot2_1.gridx2[kipmll2_1.m12 - 1]);
	*olf = (ol1 - ol0) * grdnt + ol0;
	qodi = (qod1 - qod0) * grdnt + qod0;
	qoti = (qot1 - qot0) * grdnt + qot0;
	*of = pow_dd(&c_b7, olf);
    }
/* CONVERSION FROM THE DERIVATIVE WITH CONSTANT RHOT3 TO CONSTANT RHO */
    *qodf = qodi;
    *qotf = qoti - *qodf * 3.;
    return 0;
} /* yllo3d2_ */

