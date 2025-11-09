/* cases.f -- translated by f2c (version 20061008).
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
/* CASES */
/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */
/* Subroutine */ int cases_(doublereal *p1, doublereal *p2, doublereal *m1, 
	doublereal *m2, doublereal *q1, doublereal *q2, doublereal *e1, 
	doublereal *e2, doublereal *v1, doublereal *v2, doublereal *w1, 
	doublereal *w2, doublereal *z1, doublereal *z2, doublereal *y1, 
	doublereal *y2, integer *ncase)
{
    static doublereal c1, d1, h1, j1, k1, mbar1, mbar2, mbar3, ztwo;


/*                                 SHAPE PRESERVING QUADRATIC SPLINES */
/*                                   BY D.F.MCALLISTER & J.A.ROULIER */
/*                                     CODED BY S.L.DODD & M.ROULIER */
/*                                       N.C. STATE UNIVERSITY */


/* CASES COMPUTES THE KNOTS AND OTHER PARAMETERS OF THE SPLINE ON THE */
/* INTERVAL (P1,Q1). */


/* ON INPUT-- */

/*   (P1,P2) AND (Q1,Q2) ARE THE COORDINATES OF THE POINTS OF */
/*   INTERPOLATION. */

/*   M1 IS THE SLOPE AT (P1,P2). */

/*   M2 IS THE SLOPE AT (Q1,Q2) */

/*   NCASE CONTROLS THE NUMBER AND LOCATION OF THE KNOTS. */


/* ON OUTPUT-- */

/*   (V1,V2),(W1,W2),(Z1,Z2), AND (E1,E2) ARE THE COORDINATES OF THE */
/*   KNOTS AND OTHER PARAMETERS OF THE SPLINE ON (P1,Q1). (E1,E2) */
/*   AND (Y1,Y2) ARE USED ONLY IF NCASE=4. */

/* AND */

/*   CASES DOES NOT ALTER P1,P2,M1,M2,Q1,Q2. */

/* ---------------------------------------------------------------------- */

    if (*ncase == 3 || *ncase == 4) {
	goto L20;
    }
    if (*ncase == 2) {
	goto L10;
    }

/* CALCULATE THE PARAMETERS FOR CASE 1. */
    *z1 = (*p2 - *q2 + *m2 * *q1 - *m1 * *p1) / (*m2 - *m1);
    ztwo = *p2 + *m1 * (*z1 - *p1);
    *v1 = (*p1 + *z1) / 2.;
    *v2 = (*p2 + ztwo) / 2.;
    *w1 = (*z1 + *q1) / 2.;
    *w2 = (ztwo + *q2) / 2.;
    *z2 = *v2 + (*w2 - *v2) / (*w1 - *v1) * (*z1 - *v1);
    return 0;

/* CALCULATE THE PARAMETERS FOR CASE 2. */
L10:
    *z1 = (*p1 + *q1) / 2.;
    *v1 = (*p1 + *z1) / 2.;
    *v2 = *p2 + *m1 * (*v1 - *p1);
    *w1 = (*z1 + *q1) / 2.;
    *w2 = *q2 + *m2 * (*w1 - *q1);
    *z2 = (*v2 + *w2) / 2.;
    return 0;

/* CALCULATE THE PARAMETERS USED IN BOTH CASES 3 AND 4. */
L20:
    c1 = *p1 + (*q2 - *p2) / *m1;
    d1 = *q1 + (*p2 - *q2) / *m2;
    h1 = c1 * 2. - *p1;
    j1 = d1 * 2. - *q1;
    mbar1 = (*q2 - *p2) / (h1 - *p1);
    mbar2 = (*p2 - *q2) / (j1 - *q1);

    if (*ncase == 4) {
	goto L50;
    }

/* CALCULATE THE PARAMETERS FOR CASE 3. */
    k1 = (*p2 - *q2 + *q1 * mbar2 - *p1 * mbar1) / (mbar2 - mbar1);
    if (abs(*m1) > abs(*m2)) {
	goto L30;
    }
    *z1 = (k1 + *q1) / 2.;
    goto L40;
L30:
    *z1 = (k1 + *p1) / 2.;
L40:
    *v1 = (*p1 + *z1) / 2.;
    *v2 = *p2 + *m1 * (*v1 - *p1);
    *w1 = (*q1 + *z1) / 2.;
    *w2 = *q2 + *m2 * (*w1 - *q1);
    *z2 = *v2 + (*w2 - *v2) / (*w1 - *v1) * (*z1 - *v1);
    return 0;

/* CALCULATE THE PARAMETERS FOR CASE 4. */
L50:
    *y1 = (*p1 + c1) / 2.;
    *v1 = (*p1 + *y1) / 2.;
    *v2 = *m1 * (*v1 - *p1) + *p2;
    *z1 = (d1 + *q1) / 2.;
    *w1 = (*q1 + *z1) / 2.;
    *w2 = *m2 * (*w1 - *q1) + *q2;
    mbar3 = (*w2 - *v2) / (*w1 - *v1);
    *y2 = mbar3 * (*y1 - *v1) + *v2;
    *z2 = mbar3 * (*z1 - *v1) + *v2;
    *e1 = (*y1 + *z1) / 2.;
    *e2 = mbar3 * (*e1 - *v1) + *v2;
    return 0;

} /* cases_ */

