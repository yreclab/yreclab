/* choose.f -- translated by f2c (version 20100827).
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
/* CHOOSE */
/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */
/* Subroutine */ int choose_(doublereal *p1, doublereal *p2, doublereal *m1, 
	doublereal *m2, doublereal *q1, doublereal *q2, doublereal *eps, 
	integer *ncase)
{
    /* System generated locals */
    doublereal d__1, d__2;

    /* Local variables */
    static doublereal spq, mref, prod, mref1, mref2, prod1, prod2;


/*                                 SHAPE PRESERVING QUADRATIC SPLINES */
/*                                   BY D.F.MCALLISTER & J.A. ROULIER */
/*                                     CODED BY S.L.DODD & M.ROULIER */


/* CHOOSE DETERMINES THE CASE NEEDED FOR THE COMPUTATION OF THE PARAME- */
/* TERS OF THE QUADRATIC SPLINE AND RETURNS THE VALUE IN THE VARIABLE */
/* NCASE. */

/* ON INPUT-- */

/*   (P1,P2) GIVES THE COORDINATES OF ONE OF THE POINTS OF INTERPOLATION. */

/*   M1 SPECIFIES THE DERIVATIVE CONDITION AT (P1,P2). */

/*   (Q1,Q2) GIVES THE COORDINATES OF ONE OF THE POINTS OF INTERPOLATION. */

/*   M2 SPECIFIES THE DERIVATIVE CONDITION AT (Q1,Q2). */

/*   EPS IS AN ERROR TOLERANCE USED TO DISTINGUISH CASES WHEN M1 OR M2 IS */
/*   RELATIVELY CLOSE TO THE SLOPE OR TWICE THE SLOPE OF THE LINE */
/*   SEGMENT JOINING (P1,P2) AND (Q1,Q2). IF EPS IS NOT EQUAL TO ZERO, */
/*   THEN EPS SHOULD BE GREATER THAN OR EQUAL TO MACHINE EPSILON. */


/* ON OUTPUT-- */

/*   NCASE CONTAINS THE VALUE WHICH CONTROLS HOW THE PARAMETERS OF THE */
/*   QUADRATIC SPLINE ARE EVALUATED. */

/* AND */

/*   CHOOSE DOES NOT ALTER P1,P2,Q1,Q2,M1,M2,EPS. */

/* ---------------------------------------------------------------------- */

/* CALCULATE THE SLOPE SPQ OF THE LINE JOINING (P1,P2),(Q1,Q2). */
    spq = (*q2 - *p2) / (*q1 - *p1);

/* CHECK WHETHER OR NOT SPQ IS 0. */
/* ******MODIFICATION BY MARC PINSONNEAULT TO AVOID DIVISION BY ZERO */
/* ******IN SR CASES */
    if (*m1 == 0. || *m2 == 0.) {
	goto L9;
    }
/* ****** */
    if (spq != 0.) {
	goto L20;
    }
    if (*m1 * *m2 >= 0.) {
	goto L10;
    }
    *ncase = 1;
    return 0;
L9:
L10:
    *ncase = 2;
    return 0;

L20:
    prod1 = spq * *m1;
    prod2 = spq * *m2;

/* FIND THE ABSOLUTE VALUES OF THE SLOPES SPQ,M1,AND M2. */
    mref = abs(spq);
    mref1 = abs(*m1);
    mref2 = abs(*m2);

/* IF THE RELATIVE DEVIATION OF M1 OR M2 FROM SPQ IS LESS THAN EPS, THEN */
/* CHOOSE CASE 2 OR CASE 3. */
    if ((d__1 = spq - *m1, abs(d__1)) <= *eps * mref || (d__2 = spq - *m2, 
	    abs(d__2)) <= *eps * mref) {
	goto L30;
    }

/* COMPARE THE SIGNS OF THE SLOPES SPQ,M1, AND M2. */
    if (prod1 < 0. || prod2 < 0.) {
	goto L80;
    }
    prod = (mref - mref1) * (mref - mref2);
    if (prod >= 0.) {
	goto L40;
    }

/* L1, THE LINE THROUGH (P1,P2) WITH SLOPE M1, AND L2, THE LINE THROUGH */
/* (Q1,Q2) WITH SLOPE M2, INTERSECT AT A POINT WHOSE ABSCISSA IS BETWEEN */
/* P1 AND Q1. THE ABSCISSA BECOMES A KNOT OF THE SPLINE. */
    *ncase = 1;
    return 0;

L30:
    if (prod1 < 0. || prod2 < 0.) {
	goto L80;
    }
L40:
    if (mref1 > mref * 2.) {
	goto L50;
    }
    if (mref2 > mref * 2.) {
	goto L60;
    }

/* BOTH L1 AND L2 CROSS THE LINE THROUGH (P1+Q1/2.,P2) AND (P1+Q1/2.,Q2), */
/* WHICH IS THE MIDLINE OF THE RECTANGLE FORMED BY (P1,P2),(Q1,P2), */
/* (Q1,Q2), AND (P1,Q2), OR BOTH M1 AND M2 HAVE SIGNS DIFFERENT THAN THE */
/* SIGN OF SPQ, OR ONE OF M1 AND M2 HAS OPPOSITE SIGN FROM SPQ AND L1 */
/* AND L2 INTERSECT TO THE LEFT OF P1 OR TO THE RIGHT OF Q1. THE POINT */
/* (P1+Q1)/2. IS A KNOT OF THE SPLINE. */
    *ncase = 2;
    return 0;

/* CHOOSE CASE 4 IF MREF2 IS GREATER THAN (2.-EPS)*MREF; OTHERWISE, */
/* CHOOSE CASE 3. */
L50:
    if (mref2 > (2. - *eps) * mref) {
	goto L70;
    }
    *ncase = 3;
    return 0;

/* IN CASES 3 AND 4, SIGN(M1)=SIGN(M2)=SIGN(SPQ). */

/* EITHER L1 OR L2 CROSSES THE MIDLINE, BUT NOT BOTH. */
/* CHOOSE CASE 4 IF MREF1 IS GREATER THAN (2.-EPS)*MREF; OTHERWISE, */
/* CHOOSE CASE 3. */
L60:
    if (mref1 > (2. - *eps) * mref) {
	goto L70;
    }
    *ncase = 3;
    return 0;

/* IF NEITHER L1 NOR L2 CROSSES THE MIDLINE, THE SPLINE REQUIRES TWO */
/* KNOTS BETWEEN P1 AND Q1. */
L70:
    *ncase = 4;
    return 0;

/* THE SIGN OF AT LEAST ONE OF THE SLOPES M1,M2 DOES NOT AGREE WITH THE */
/* SIGN OF THE SLOPE SPQ. */
L80:
    if (prod1 < 0. && prod2 < 0.) {
	goto L130;
    }

    if (prod1 < 0.) {
	goto L90;
    }
    goto L110;

L90:
    if (mref2 > (*eps + 1.) * mref) {
	goto L100;
    }
    *ncase = 2;
    return 0;

L100:
    *ncase = 1;
    return 0;

L110:
    if (mref1 > (*eps + 1.) * mref) {
	goto L120;
    }
    *ncase = 2;
    return 0;

L120:
    *ncase = 1;
    return 0;

L130:
    *ncase = 2;
    return 0;

} /* choose_ */

