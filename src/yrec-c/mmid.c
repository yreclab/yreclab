/* mmid.f -- translated by f2c (version 20061008).
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



/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */
/* MMID */
/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */
/* Subroutine */ int mmid_(doublereal *y, doublereal *dydx, integer *nvar, 
	doublereal *xs, doublereal *htot, integer *nstep, doublereal *yout, 
	S_fp deriv, doublereal *b, doublereal *fpl, doublereal *ftl, 
	doublereal *gl, logical *latmo, logical *lderiv, logical *locond, 
	logical *lsave, doublereal *rl, doublereal *teffl, doublereal *x, 
	doublereal *z__, integer *kount, integer *ksaha)
{
    /* System generated locals */
    integer i__1, i__2;

    /* Local variables */
    static doublereal h__;
    static integer i__, n;
    static doublereal h2, x0, ym[3], yn[3], swap;

/*  INTEGRATES THE DEPENDENT VARIABLES Y FROM XS TO XS + HTOT IN */
/*  NSTEP INCREMENTS.  INPUT ARE THE Y'S AND DY/DX'S AT XS; VALUES OF */
/*  Y AT XS + HTOT ARE STORED IN YOUT.  DERIVATIVES ARE CALCULATED IN */
/*  SUBROUTINE DERIV. THIS SR FROM NUMERICAL RECIPES, P.562. */
/*  H IS THE SIZE OF EACH SMALL STEP. */
    /* Parameter adjustments */
    --yout;
    --dydx;
    --y;

    /* Function Body */
    h__ = *htot / (doublereal) (*nstep);
/*  FIRST STEP */
    i__1 = *nvar;
    for (i__ = 1; i__ <= i__1; ++i__) {
	ym[i__ - 1] = y[i__];
	yn[i__ - 1] = y[i__] + dydx[i__] * h__;
/* L10: */
    }
    x0 = *xs + h__;
/*  YOUT TEMPORARILY USED FOR STORAGE OF DERIVATIVES. */
    (*deriv)(&x0, yn, &yout[1], b, fpl, ftl, gl, latmo, lderiv, locond, lsave,
	     rl, teffl, x, z__, kount, ksaha);
    h2 = h__ * 2.;
/*  GENERAL STEP. */
    i__1 = *nstep;
    for (n = 2; n <= i__1; ++n) {
	i__2 = *nvar;
	for (i__ = 1; i__ <= i__2; ++i__) {
	    swap = ym[i__ - 1] + h2 * yout[i__];
	    ym[i__ - 1] = yn[i__ - 1];
	    yn[i__ - 1] = swap;
/* L20: */
	}
	x0 += h__;
	(*deriv)(&x0, yn, &yout[1], b, fpl, ftl, gl, latmo, lderiv, locond, 
		lsave, rl, teffl, x, z__, kount, ksaha);
/* L30: */
    }
/*  LAST STEP. */
    i__1 = *nvar;
    for (i__ = 1; i__ <= i__1; ++i__) {
	yout[i__] = (ym[i__ - 1] + yn[i__ - 1] + h__ * yout[i__]) * .5;
/* L40: */
    }
    return 0;
} /* mmid_ */

