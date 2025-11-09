/* ysplin.f -- translated by f2c (version 20061008).
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



/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */
/* YPSLIN */
/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */
/* FIND THE COEFFICIENTS FOR THE NATURAL CUBIC SPLINE. */
/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */
/* YCK 3/91 */
/* Subroutine */ int ysplin_(doublereal *xi, doublereal *c__, integer *n)
{
    /* System generated locals */
    integer i__1;

    /* Local variables */
    static doublereal d__[100], f[100], g, h__[100];
    static integer i__;
    static doublereal d3, const1, const2, const3, const4;

/* SET THE DIVIDED DIFFERENCE AT EACH SUBINTERVAL. */
    /* Parameter adjustments */
    c__ -= 5;
    --xi;

    /* Function Body */
    i__1 = *n;
    for (i__ = 2; i__ <= i__1; ++i__) {
	h__[i__ - 1] = xi[i__] - xi[i__ - 1];
	f[i__ - 1] = (c__[(i__ << 2) + 1] - c__[(i__ - 1 << 2) + 1]) / h__[
		i__ - 1];
/* L10: */
    }
/* SET THE TRIDIAGONALLY DOMINANT MATRIX AND THE MATRIX EQUATION */
/*  FOR THE NATURAL SPLINE. */
/* CCCC FIND THE COEFFICIENTS FOR THE SECOND ORDER TERMS CCCCC */
    i__ = 2;
    const1 = 3.;
    const2 = 1.5;
    const3 = 2.;
    const4 = 1.5;
    c__[(i__ << 2) + 2] = const1 * h__[i__ - 1] * f[i__] + const2 * h__[i__] *
	     f[i__ - 1];
    d__[i__ - 1] = const3 * h__[i__ - 1] + const4 * h__[i__];
    i__1 = *n - 2;
    for (i__ = 3; i__ <= i__1; ++i__) {
	const1 = 3.;
	const2 = 3.;
	const3 = 2.;
	const4 = 2.;
	c__[(i__ << 2) + 2] = const1 * h__[i__ - 1] * f[i__] + const2 * h__[
		i__] * f[i__ - 1];
	d__[i__ - 1] = const3 * h__[i__ - 1] + const4 * h__[i__];
/* L20: */
    }
    i__ = *n - 1;
    const1 = 1.5;
    const2 = 3.;
    const3 = 1.5;
    const4 = 2.;
    c__[(i__ << 2) + 2] = const1 * h__[i__ - 1] * f[i__] + const2 * h__[i__] *
	     f[i__ - 1];
    d__[i__ - 1] = const3 * h__[i__ - 1] + const4 * h__[i__];
/* SOLVE THE MATRIX EQUATION WITH GAUSS METHOD */
/* ELIMINATION OF THE SUB-DIAGONAL */
    i__1 = *n - 2;
    for (i__ = 2; i__ <= i__1; ++i__) {
	g = h__[i__ + 1] / d__[i__ - 1];
	d__[i__] -= g * h__[i__ - 1];
	c__[(i__ + 1 << 2) + 2] -= g * c__[(i__ << 2) + 2];
/* L30: */
    }
/* ELIMINATION OF THE SUPER-DIAGONAL */
    c__[(*n - 1 << 2) + 2] /= d__[*n - 2];
    for (i__ = *n - 2; i__ >= 2; --i__) {
	c__[(i__ << 2) + 2] = (c__[(i__ << 2) + 2] - h__[i__ - 1] * c__[(i__ 
		+ 1 << 2) + 2]) / d__[i__ - 1];
/* L40: */
    }
/* TREATMENT FOR THE FIRST AND LAST ROW. */
    c__[6] = f[1] * 1.5 - c__[10] / 2.;
    c__[(*n << 2) + 2] = f[*n - 1] * 1.5 - c__[(*n - 1 << 2) + 2] / 2.;
/* CC NOW, WE HAVE THE COEFFICIENTS FOR THE FIRST ORDER TERMS */

/* FIND THE COEFFICIENTS FOR THE SECOND, AND THE THIRD ORDER TERMS */
    i__1 = *n - 1;
    for (i__ = 1; i__ <= i__1; ++i__) {
	d3 = c__[(i__ << 2) + 2] + c__[(i__ + 1 << 2) + 2] - f[i__] * 2.;
	c__[(i__ << 2) + 3] = (f[i__] - c__[(i__ << 2) + 2] - d3) / h__[i__];
	c__[(i__ << 2) + 4] = d3 / (h__[i__] * h__[i__]);
/* L50: */
    }
/* CC   NOW, WE HAVE COMPLETE SET OF COEFFICIENTS FOR EACH SUB-INTERVAL. */
    return 0;
} /* ysplin_ */

