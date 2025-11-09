/* get_imp_diffco.f -- translated by f2c (version 20061008).
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

/* $$$$$$ */
/* Subroutine */ int get_imp_diffco__(doublereal *alpha, doublereal *
	ecod2_h__, doublereal *ex_h__, doublereal *eqcod2x_h__, doublereal *a,
	 doublereal *b, doublereal *c__, integer *npt)
{
    /* System generated locals */
    integer i__1;

    /* Local variables */
    static integer i__;

/* CORRECT DIFFUSION COEFFICEINTS FOR CHANGE IN X IN THE PREVIOUS ITERATION. */
    /* Parameter adjustments */
    --c__;
    --b;
    --a;
    --eqcod2x_h__;
    --ex_h__;
    --ecod2_h__;
    --alpha;

    /* Function Body */
    i__1 = *npt - 1;
    for (i__ = 1; i__ <= i__1; ++i__) {
	ecod2_h__[i__] += eqcod2x_h__[i__] * ex_h__[i__];
/* L10: */
    }
/* NOW RECOMPUTE ELEMENTS OF THE TRIDIAGONAL MATRIX SYSTEM. */
    a[1] = 0.;
    b[1] = alpha[1] * ecod2_h__[1] + 1.;
    c__[1] = -alpha[1] * ecod2_h__[1];
/*   911 FORMAT(5X,I5,1P3E10.2) */
    i__1 = *npt - 1;
    for (i__ = 2; i__ <= i__1; ++i__) {
	a[i__] = -alpha[i__] * ecod2_h__[i__ - 1];
	b[i__] = alpha[i__] * (ecod2_h__[i__ - 1] + ecod2_h__[i__]) + 1.;
	c__[i__] = -alpha[i__] * ecod2_h__[i__];
/* L20: */
    }
    a[*npt] = -alpha[*npt] * ecod2_h__[*npt - 1];
    b[*npt] = alpha[*npt] * ecod2_h__[*npt - 1] + 1.;
    c__[*npt] = 0.;
    return 0;
} /* get_imp_diffco__ */

