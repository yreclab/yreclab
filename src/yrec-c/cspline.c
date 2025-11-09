/* cspline.f -- translated by f2c (version 20061008).
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


/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */
/*  SUBROUTINE CSPLINE */
/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */
/* REAL*8 VERSION FOR OPACITIES */
/* TAKEN FROM NUMERICAL RECIPES, PRESS ET AL, P88 */
/* GIVEN ARRAYS X AND Y OF LENGTH N CONTAINING A TABULATED FUNCITION, */
/* I.E. Y[I] = F(X[I]) WITH X[1] < X[2] < ... X[N], AND GIVEN VALUES */
/* YP1 AND YPN FOR THE FIRST DERIVATIVE OF THE INTERPOLATING FUNCTION */
/* AT POINTS 1 AND N, RESPECTIVELY, THIS ROUTINE RETURNS AND ARRAY Y2 */
/* OF LENGTH N WHICH CONTAINS THE SECOND DERIVATIVES OF THE INTERPOLATING */
/* FUNCTION AT THE TABULATED POINTS X[I].  IF YP1 AND/OR YPN ARE EQUAL */
/* TO 1.0E30 OR LARGER, THE ROUTINE IS SIGNALLED TO SET THE CORRESPONDING */
/* BOUNDARY CONDITION FOR A NATURAL SPLINE, WITH ZERO SECOND DERIVATIVE */
/* ON THAT BOUNDARY. */
/* Subroutine */ int cspline_(doublereal *x, doublereal *y, integer *n, 
	doublereal *yp1, doublereal *ypn, doublereal *y2)
{
    /* System generated locals */
    integer i__1;

    /* Local variables */
    static integer i__, k;
    static doublereal p, u[5000], qn, un, sig;

    /* Parameter adjustments */
    --y2;
    --y;
    --x;

    /* Function Body */
    if (*yp1 > 9.9e29) {
	y2[1] = 0.;
	u[0] = 0.;
    } else {
	y2[1] = -.5;
	u[0] = 3. / (x[2] - x[1]) * ((y[2] - y[1]) / (x[2] - x[1]) - *yp1);
    }
    i__1 = *n - 1;
    for (i__ = 2; i__ <= i__1; ++i__) {
	sig = (x[i__] - x[i__ - 1]) / (x[i__ + 1] - x[i__ - 1]);
	p = sig * y2[i__ - 1] + 2.;
	y2[i__] = (sig - 1.) / p;
	u[i__ - 1] = (((y[i__ + 1] - y[i__]) / (x[i__ + 1] - x[i__]) - (y[i__]
		 - y[i__ - 1]) / (x[i__] - x[i__ - 1])) * 6. / (x[i__ + 1] - 
		x[i__ - 1]) - sig * u[i__ - 2]) / p;
    }
    if (*ypn > 9.9e29) {
	qn = 0.;
	un = 0.;
    } else {
	qn = .5;
	un = 3. / (x[*n] - x[*n - 1]) * (*ypn - (y[*n] - y[*n - 1]) / (x[*n] 
		- x[*n - 1]));
    }
    y2[*n] = (un - qn * u[*n - 2]) / (qn * y2[*n - 1] + 1.);
    for (k = *n - 1; k >= 1; --k) {
	y2[k] = y2[k] * y2[k + 1] + u[k - 1];
    }
    return 0;
} /* cspline_ */

