/* boole.f -- translated by f2c (version 20061008).
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

/* ************************************************************* */
/* BOOLE: Performs 5-point Newton-Cotes integration of tabulated data */
/*      X: vector of independent variable values (x) */
/*      Y: vector dependent variable values ( f(x) ) */
/*      N: number of elements in X */
/*      NN: number of elements desired in interpolated grid (should be 1+4*A) */
/*       S: returned, integrated value of the function */
/*      XI: returned grid in X */
/*      YI: returned interpolated values of Y */

/*       Data need to be evenly gridded for the integration formula to work. */
/*      Data that are not already so are interpolated onto an even grid */
/*      using spline interpolation (numerical recipes SPLINE (renamed splinnr) */
/*      and SPLINT) */
/* ************************************************************* */
/*      PARAMETER(NN = 17) */
/*      PARAMETER(N = 16) */
/*      DATA Y/6.40,5.041,3.844,2.809,1.936,1.225,0.676,0.289,0.064,0.361, */
/*     *0.784,1.369,2.116,3.025,4.096,5.329/ */
/*      DATA X/-8.0,-7.1,-6.2,-5.3,-4.4,-3.5,-2.6,-1.7,0.8,1.9,2.8,3.7, */
/*    *4.6,5.5,6.4,7.3/ */
/* Subroutine */ int boole_(doublereal *x, doublereal *y, integer *n, integer 
	*nn, doublereal *s)
{
    /* System generated locals */
    integer i__1;

    /* Local variables */
    static doublereal h__[1];
    static integer i__, p;
    static doublereal xd[2048], yd[2048], xi[2048], yi[2048], d2x[2048];
    static integer khi, klo;
    extern /* Subroutine */ int splinj_(doublereal *, doublereal *, 
	    doublereal *, integer *), splint_(doublereal *, doublereal *, 
	    integer *, doublereal *, doublereal *, doublereal *, integer *, 
	    integer *);

/* Rescale radius and cs vectors to have values ~1 */
    /* Parameter adjustments */
    --s;
    --y;
    --x;

    /* Function Body */
    i__1 = *n;
    for (i__ = 1; i__ <= i__1; ++i__) {
	xd[i__ - 1] = x[i__] * 1e-11;
	yd[i__ - 1] = y[i__] * 1e7;
/* L22: */
    }
/* Deal with unevenly gridded datasets: */
/*      IF (.NOT.LEVEN) THEN            ! do for all */
    splinj_(xd, yd, d2x, n);
/* get derivs of interp. fn. */
    i__1 = *nn;
    for (i__ = 1; i__ <= i__1; ++i__) {
	xi[i__ - 1] = xd[0] + (i__ - 1) * (xd[*n - 1] - xd[0]) / (*nn - 1);
	splint_(xd, yd, n, d2x, &xi[i__ - 1], &yi[i__ - 1], &klo, &khi);
/* L20: */
    }
/* How many sets of four points do we have? */
    p = (*nn - 1) / 4;
    h__[0] = (xd[*n - 1] - xd[0]) / (*nn - 1);
/* For each set of 4 points before the last, apply formula and add up */
    s[1] = 0.;
    i__1 = p - 1;
    for (i__ = 0; i__ <= i__1; ++i__) {
	s[1] += h__[0] * 2.f * (yi[i__ * 4] * 7 + yi[(i__ << 2) + 1] * 32 + 
		yi[(i__ << 2) + 2] * 12 + yi[(i__ << 2) + 3] * 32 + yi[(i__ <<
		 2) + 4] * 7) / 45.f;
/* L21: */
    }
/* Rescale result back to actual units: */
    s[1] /= 9.9999999999999991e-5;
/*      PRINT*, 'Last point in vector:', NN */
/*      PRINT*, 'Last point integrated:',5+4*(P-1) */
/* -------------------------------------------------------------- */
/*                  OPEN(UNIT=100,FILE='diagnostic3.out',STATUS='OLD') */
/*                  DO 1505 I=1,N */
/*                              WRITE(100,1504), X(I), Y(I), XD(I), YD(I), */
/*     *                         XI(I), YI(I), S(1), H(1) */
/* 1505                  CONTINUE */
/* 1504                  FORMAT(1X,8E16.8) */
/*                  CLOSE(100) */
/* ---------------------------------------------------------------- */
    return 0;
} /* boole_ */

