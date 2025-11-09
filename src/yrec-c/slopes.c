/* slopes.f -- translated by f2c (version 20061008).
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

/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */
/* SLOPES */
/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */
/* Subroutine */ int slopes_(doublereal *xtab, doublereal *ytab, doublereal *
	mtab, integer *num)
{
    /* System generated locals */
    doublereal d__1, d__2;

    /* Local variables */
    static integer i__, i1;
    static doublereal m1, m2;
    extern /* Subroutine */ int safedivide_(doublereal *, doublereal *, 
	    doublereal *);
    static integer im1;
    static doublereal m1s, m2s;
    static integer num1;
    static doublereal xbar, xmid, xhat, ydif1, ydif2, yxmid;


/*                                 SHAPE PRESERVING QUADRATIC SPLINES */
/*                                   BY D.F.MCALLISTER & J.A.ROULIER */
/*                                     CODED BY S.L.DODD & M.ROULIER */
/*                                       N.C.STATE UNIVERSITY */


/* SLOPES CALCULATES THE DERIVATIVE AT EACH OF THE DATA POINTS. THE */
/* SLOPES PROVIDED WILL INSURE THAT AN OSCULATORY QUADRATIC SPLINE WILL */
/* HAVE ONE ADDITIONAL KNOT BETWEEN TWO ADJACENT POINTS OF INTERPOLATION. */
/* CONVEXITY AND MONOTONICITY ARE PRESERVED WHEREVER THESE CONDITIONS */
/* ARE COMPATIBLE WITH THE DATA. */

/* ON INPUT-- */

/*   XTAB CONTAINS THE ABSCISSAS OF THE DATA POINTS. */

/*   YTAB CONTAINS THE ORDINATES OF THE DATA POINTS. */

/*   NUM IS THE NUMBER OF DATA POINTS (DIMENSION OF XTAB,YTAB). */


/* ON OUTPUT-- */

/*   MTAB CONTAINS THE VALUE OF THE FIRST DERIVATIVE AT EACH DATA POINT. */

/* AND */

/*   SLOPES DOES NOT ALTER XTAB,YTAB,NUM. */

/* ---------------------------------------------------------------------- */

    /* Parameter adjustments */
    --mtab;
    --ytab;
    --xtab;

    /* Function Body */
    num1 = *num - 1;
    im1 = 1;
    i__ = 2;
    i1 = 3;

/* CALCULATE THE SLOPES OF THE TWO LINES JOINING THE FIRST THREE DATA */
/* POINTS */
    ydif1 = ytab[2] - ytab[1];
    ydif2 = ytab[3] - ytab[2];
    m1 = ydif1 / (xtab[2] - xtab[1]);
    m1s = m1;
    m2 = ydif2 / (xtab[3] - xtab[2]);
    m2s = m2;

/* IF ONE OF THE PRECEDING SLOPES IS ZERO OR IF THEY HAVE OPPOSITE SIGN, */
/* ASSIGN THE VALUE ZERO TO THE DERIVATIVE AT THE MIDDLE POINT. */
L10:
    if (m1 == 0. || m2 == 0. || m1 * m2 <= 0.) {
	goto L20;
    }
    if (abs(m1) > abs(m2)) {
	goto L30;
    }
    goto L40;
L20:
    mtab[i__] = 0.;
    goto L50;

/* CALCULATE THE SLOPE BY EXTENDING THE LINE WITH SLOPE M1. */
L30:
    xbar = ydif2 / m1 + xtab[i__];
    xhat = (xbar + xtab[i1]) / 2.;
    mtab[i__] = ydif2 / (xhat - xtab[i__]);
    goto L50;

/* CALCULATE THE SLOPE BY EXTENDING THE LINE WITH SLOPE M2. */
L40:
    xbar = -ydif1 / m2 + xtab[i__];
    xhat = (xtab[im1] + xbar) / 2.;
    mtab[i__] = ydif1 / (xtab[i__] - xhat);

/* INCREMENT COUNTERS */
L50:
    im1 = i__;
    i__ = i1;
    ++i1;
    if (i__ > num1) {
	goto L60;
    }

/* CALCULATE THE SLOPES OF THE TWO LINES JOINING THREE CONSECUTIVE DATA */
/* POINTS. */
    ydif1 = ytab[i__] - ytab[im1];
    ydif2 = ytab[i1] - ytab[i__];
    m1 = ydif1 / (xtab[i__] - xtab[im1]);
/* KC 2025-05-31 PREVENT FLOATING POINT EXCEPTION */
/*       M2=YDIF2/(XTAB(I1) - XTAB(I)) */
    d__1 = xtab[i1] - xtab[i__];
    safedivide_(&ydif2, &d__1, &m2);
    goto L10;

/* CALCULATE THE SLOPE AT THE LAST POINT, XTAB(NUM). */
L60:
    if (m1 * m2 < 0.) {
	goto L80;
    }
    xmid = (xtab[num1] + xtab[*num]) / 2.;
    yxmid = mtab[num1] * (xmid - xtab[num1]) + ytab[num1];
/* KC 2025-05-31 PREVENT FLOATING POINT EXCEPTION */
/*       MTAB(NUM)=(YTAB(NUM)-YXMID)/(XTAB(NUM)-XMID) */
    d__1 = ytab[*num] - yxmid;
    d__2 = xtab[*num] - xmid;
    safedivide_(&d__1, &d__2, &mtab[*num]);
    if (mtab[*num] * m2 < 0.) {
	goto L70;
    }
    goto L90;
L70:
    mtab[*num] = 0.;
    goto L90;
L80:
    mtab[*num] = m2 * 2.;

/* CALCULATE THE SLOPE AT THE FIRST POINT, XTAB(1). */
L90:
    if (m1s * m2s < 0.) {
	goto L110;
    }
    xmid = (xtab[1] + xtab[2]) / 2.;
    yxmid = mtab[2] * (xmid - xtab[2]) + ytab[2];
    mtab[1] = (yxmid - ytab[1]) / (xmid - xtab[1]);
    if (mtab[1] * m1s < 0.) {
	goto L100;
    }
    return 0;
L100:
    mtab[1] = 0.;
    return 0;
L110:
    mtab[1] = m1s * 2.;
    return 0;

} /* slopes_ */

/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */
/* KC 2025-05-31 SAFEDIVIDE */
/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */
/* Subroutine */ int safedivide_(doublereal *numerator, doublereal *
	denominator, doublereal *result)
{
    *result = 0.;
    if (*numerator != 0. && *denominator != 0.) {
	*result = *numerator / *denominator;
    }
    return 0;
} /* safedivide_ */

