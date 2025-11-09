/* eq2mod.f -- translated by f2c (version 20061008).
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
    doublereal xval[5000], yval[5000], xtab[5000], ytab[5000];
} splin_;

#define splin_1 splin_

struct {
    doublereal chi[5000], echi[5000], es1[5000], dchi;
    integer ntot;
} egrid_;

#define egrid_1 egrid_

/* $$$$$$ */
/* Subroutine */ int eq2mod_(doublereal *dj, doublereal *ej, doublereal *hs2, 
	integer *ibeg, integer *iend, logical *lcz, integer *m, doublereal *
	sumdj, doublereal *hjm)
{
    /* System generated locals */
    integer i__1;
    doublereal d__1;

    /* Local variables */
    static doublereal sumdjmod;
    static integer i__, i0, i1, ii;
    static doublereal val;
    static integer nmod;
    static doublereal test, ratio;
    extern /* Subroutine */ int osplin_(doublereal *, doublereal *, 
	    doublereal *, doublereal *, integer *, integer *);
    static doublereal sumjmod;

/*  THE DIFFUSION EQUATION FOR ANGULAR MOMENTUM TRANSPORT IS SOLVED USING AN */
/*  EQUALLY SPACED GRID FOR EACH UNSTABLE REGION.  ONCE THE EQUATION HAS */
/*  BEEN SOLVED, WE NEED THE NEW RUN OF ANGULAR MOMENTUM AT THE ORIGINAL */
/*  MODEL POINTS. */

/*  EQUAL2 TRANSFORM BACK TO THE ORIGINAL GRID AND CALCULATE THE CHANGE IN */
/*  SPECIFIC ANGULAR MOMENTUM IN EACH SHELL. */

/*  INPUT VARIABLES: */

/*     VARIABLES PERTAINING TO THE EQUALLY SPACED GRID POINTS USED TO SOLVE */
/*     THE DIFFUSION EQUATION : */

/*  DJ - CHANGE IN J AT EACH POINT DUE TO ROTATIONALLY INDUCED INSTABILITIES. */
/*  EJ - CONTAINS THE RUN OF ANGULAR MOMENTUM PRIOR TO ANGULAR MOMENTUM */
/*       REDISTRIBUTION. */
/*  NTOT - NUMBER OF EQUALLY SPACED GRID POINTS IN THE UNSTABLE REGION. */
/*  SUMDJ - TOTAL CHANGE IN ANGULAR MOMENTUM ACROSS GRID */
/*     VARIABLES PERTAINING TO THE ORIGINAL MODEL POINTS : */

/*  HS2 - THE UNLOGGED MASS CONTENT OF THE MODEL POINTS. */
/*  IBEG,IEND - THE FIRST AND LAST MODEL POINTS CONTAINED IN THE UNSTABLE */
/*  REGION. */
/*  LCZ - A LOGICAL ARRAY WHICH IS T IF THE MODEL POINT IS CONVECTIVE FOR */
/*  ANGULAR MOMENTUM PURPOSES AND F OTHERWISE. */
/*  M - THE TOTAL NUMBER OF MODEL POINTS. */

/* VARIABLES IN COMMON BLOCKS: */

/* /SPLIN/ CONTAINS DUMMY ARRAYS USED TO PERFORM AN OSCULATORY SPLINE */
/* INTERPOLATION. */
/* /EGRID/ CONTAINS THE VECTOR OF EQUALLY SPACED GRID POINTS. */
/* OUTPUT VARIABLE : */
/*  HJM - THE NEW RUN OF SPECIFIC ANGULAR MOMENTUM AT THE MODEL POINTS. */
/* ------------------------------------------------------------------------- */
/* CHECK FOR LOWER AND UPPER CONVECTION ZONES. */
    /* Parameter adjustments */
    --hjm;
    --lcz;
    --hs2;
    --ej;
    --dj;

    /* Function Body */
    if (! lcz[*ibeg] || *ibeg == 1) {
	i0 = *ibeg;
    } else {
	for (i__ = *ibeg - 1; i__ >= 1; --i__) {
	    if (! lcz[i__]) {
		i0 = i__ + 1;
		goto L10;
	    }
	}
	i0 = 1;
L10:
	;
    }
    if (! lcz[*iend] || *iend == *m) {
	i1 = *iend;
    } else {
	i__1 = *m;
	for (i__ = *iend + 1; i__ <= i__1; ++i__) {
	    if (! lcz[i__]) {
		i1 = i__ - 1;
		goto L20;
	    }
	}
	i1 = *m;
L20:
	;
    }
/* INTERPOLATE IN DJ/J AS A FUNCTION OF ECHI */
    nmod = *iend - *ibeg + 1;
    i__1 = nmod;
    for (i__ = 1; i__ <= i__1; ++i__) {
	splin_1.xval[i__ - 1] = egrid_1.chi[i__ - 1];
    }
    i__1 = egrid_1.ntot;
    for (i__ = 1; i__ <= i__1; ++i__) {
	splin_1.xtab[i__ - 1] = egrid_1.echi[i__ - 1];
	splin_1.ytab[i__ - 1] = dj[i__] / ej[i__];
    }
    osplin_(splin_1.xval, splin_1.yval, splin_1.xtab, splin_1.ytab, &
	    egrid_1.ntot, &nmod);
/* APPLY THE FRACTIONAL CHANGE IN J/M ACROSS THE MODEL. */
    sumjmod = 0.;
    sumdjmod = 0.;
    if (i0 < *ibeg) {
	i__1 = *ibeg - 1;
	for (i__ = i0; i__ <= i__1; ++i__) {
	    sumjmod += hjm[i__] * hs2[i__];
	    sumdjmod += splin_1.yval[0] * hjm[i__] * hs2[i__];
	    hjm[i__] *= splin_1.yval[0] + 1.;
	}
    }
    i__1 = *iend;
    for (i__ = *ibeg; i__ <= i__1; ++i__) {
	ii = i__ - *ibeg + 1;
	sumjmod += hjm[i__] * hs2[i__];
	sumdjmod += splin_1.yval[ii - 1] * hjm[i__] * hs2[i__];
	hjm[i__] *= splin_1.yval[ii - 1] + 1.;
    }
    if (i1 > *iend) {
	i__1 = i1;
	for (i__ = *iend + 1; i__ <= i__1; ++i__) {
	    sumjmod += hjm[i__] * hs2[i__];
	    sumdjmod += splin_1.yval[nmod - 1] * hjm[i__] * hs2[i__];
	    hjm[i__] *= splin_1.yval[nmod - 1] + 1.;
	}
    }
/* CHECK THAT ANGULAR MOMENTUM HAS BEEN CONSERVED.  THE TOTAL ANGULAR */
/* MOMENTUM CAN BE REDUCED FROM SURFACE ANGULAR MOMENTUM LOSS; CARE IS */
/* USED HERE BECAUSE DUMDJ SHOULD BE ZERO IN MODELS WITHOUT LOSS. */
    test = (d__1 = sumdjmod - *sumdj, abs(d__1));
    val = abs(*sumdj) * 1e-5;
/*      WRITE(*,*)SUMDJ,SUMDJMOD,SUMJMOD */
/*      WRITE(*,911)(DJ(I)/EJ(I),I=1,NTOT) */
/*  911  FORMAT(1P8E10.2) */
/* IF THE TEST SUM IS NOT THE SAME WITHIN THE RELATIVE TOLERANCE VAL, */
/* ADJUST THE TOTAL ANGULAR MOMENTUM OF THE ENTIRE REGION BY A CONSTANT */
/* FACTOR TO ENFORCE ANGULAR MOMENTUM CONSERVATION. */
    if (test > val) {
	ratio = (sumjmod + *sumdj) / (sumjmod + sumdjmod);
	i__1 = i1;
	for (i__ = i0; i__ <= i__1; ++i__) {
	    hjm[i__] *= ratio;
	}
    }
    return 0;
} /* eq2mod_ */

