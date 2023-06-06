/* yllo3d.f -- translated by f2c (version 20100827).
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
    doublereal gridt[50], gridx[3], grhot3[17];
} gllot_;

#define gllot_1 gllot_

struct {
    doublereal opacity[2550]	/* was [150][17] */;
    integer numxm, numtm;
} llot_;

#define llot_1 llot_

struct {
    doublereal xenv4, zenv4, cford4[3400]	/* was [50][68] */;
    integer kipm1;
} llot4_;

#define llot4_1 llot4_

struct kipmll_1_ {
    integer m1, m2, m3;
};

#define kipmll_1 (*(struct kipmll_1_ *) &kipmll_)

/* Initialized data */

struct {
    integer e_1[3];
    } kipmll_ = { 1, 1, 1 };


/* Table of constant values */

static integer c__3 = 3;
static doublereal c_b7 = 10.;

/*  THIS IS THE INTERPOLATION FACILITY FOR THE LIVERMORE OPACITY TABLES */
/* USING CUBIC SPLINE INTERPLOATION SCHEME. */
/* *** YLLO3D AND SETLLO ARE THE ROUTINES TO BE CALLED! */
/*      SUBROUTINE YLLO3D(DL,TL,X,OF,OLF,QODF,QOTF) */
/*      SUBROUTINE YLLO2D(T,D,M1,M2,M3,O,OL,QODF,QOTF) */
/*      SUBROUTINE YLLO3D2(DL,TL,X,OF,OLF,QODF,QOTF) */
/*      SUBROUTINE YLLO2D2(T,D,M1,M2,M3,O,OL,QODF,QOTF) */
/*      SUBROUTINE SETLLO(IOCTRL)                     READ LLOT */
/*      SUBROUTINE YLLOC                              SPLINE COEFF. */
/*      SUBROUTINE LL4TH(X) SURFACE TABLES */

/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */
/* YLLO3D */
/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */
/* Subroutine */ int yllo3d_(doublereal *dl, doublereal *tl, doublereal *x, 
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
    extern /* Subroutine */ int yllo2d_(doublereal *, doublereal *, integer *,
	     integer *, integer *, doublereal *, doublereal *, doublereal *, 
	    doublereal *), findex_(doublereal *, integer *, doublereal *, 
	    integer *);

    lone = FALSE_;
/* INDEPENDENT PARAMETER IN LIVERMORE OPACITY TABLE; */
/* T6 = LN(T/10E6) */
    t6 = *tl - 6.;
/* RHOT3 = LN(RHO/(T/10E6)**3) */
    rhot3 = *dl - t6 * 3.;
    if ((d__1 = llot4_1.xenv4 - *x, abs(d__1)) <= 1e-5) {
	kipmll_1.m1 = 4;
	lone = TRUE_;
	goto L131;
    }
    for (im1 = 1; im1 <= 3; ++im1) {
	if ((d__1 = gllot_1.gridx[im1 - 1] - *x, abs(d__1)) <= 1e-5) {
	    kipmll_1.m1 = im1;
	    lone = TRUE_;
	    goto L131;
	}
/* L130: */
    }
    findex_(gllot_1.gridx, &c__3, x, &kipmll_1.m1);
    if (kipmll_1.m1 < 0) {
	kipmll_1.m1 = -kipmll_1.m1;
    }
    if (kipmll_1.m1 <= 1 && rhot3 > -1.) {
	kipmll_1.m1 = 2;
    }
    if (kipmll_1.m1 >= 3) {
	kipmll_1.m1 = 2;
    }
    if (kipmll_1.m1 <= 0) {
	s_stop(" ERROR IN X GRID", (ftnlen)16);
    }
L131:
    findex_(gllot_1.gridt, &llot_1.numtm, &t6, &kipmll_1.m2);
    if (kipmll_1.m2 < 0 && gllot_1.gridt[llot_1.numtm - 1] == t6) {
	kipmll_1.m2 = -kipmll_1.m2;
    }
    if (kipmll_1.m2 < 0) {
	s_stop(" T OUT OF TABLE ", (ftnlen)16);
    }
    yllo2d_(&t6, &rhot3, &kipmll_1.m1, &kipmll_1.m2, &kipmll_1.m3, &o0, &ol0, 
	    &qod0, &qot0);
    if (lone) {
/* USE ONLY ONE X TABLE */
	*olf = ol0;
	*of = o0;
	qodi = qod0;
	qoti = qot0;
    } else {
/* LINEAR EXTRAPOLATION IN X */
	i__1 = kipmll_1.m1 + 1;
	yllo2d_(&t6, &rhot3, &i__1, &kipmll_1.m2, &kipmll_1.m3, &o1, &ol1, &
		qod1, &qot1);
	grdnt = (*x - gllot_1.gridx[kipmll_1.m1 - 1]) / (gllot_1.gridx[
		kipmll_1.m1] - gllot_1.gridx[kipmll_1.m1 - 1]);
	*olf = (ol1 - ol0) * grdnt + ol0;
	qodi = (qod1 - qod0) * grdnt + qod0;
	qoti = (qot1 - qot0) * grdnt + qot0;
	*of = pow_dd(&c_b7, olf);
    }
/* CONVERSION FROM THE DERIVATIVE WITH CONSTANT RHOT3 TO CONSTANT RHO */
    *qodf = qodi;
    *qotf = qoti - *qodf * 3.;
    return 0;
} /* yllo3d_ */

