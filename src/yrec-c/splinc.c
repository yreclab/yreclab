/* splinc.f -- translated by f2c (version 20061008).
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
/* Subroutine */ int splinc_(doublereal *x, doublereal *y, doublereal *y2, 
	integer *n)
{
    /* System generated locals */
    integer i__1;

    /* Local variables */
    static integer i__, k;
    static doublereal p, u[5000], qn, un, sig;

/* NATURAL SPLINE */
    /* Parameter adjustments */
    --y2;
    --y;
    --x;

    /* Function Body */
    y2[1] = 0.;
    u[0] = 0.;
    i__1 = *n - 1;
    for (i__ = 2; i__ <= i__1; ++i__) {
	sig = (x[i__] - x[i__ - 1]) / (x[i__ + 1] - x[i__ - 1]);
	p = sig * y2[i__ - 1] + 2.;
	y2[i__] = (sig - 1.) / p;
	u[i__ - 1] = (((y[i__ + 1] - y[i__]) / (x[i__ + 1] - x[i__]) - (y[i__]
		 - y[i__ - 1]) / (x[i__] - x[i__ - 1])) * 6. / (x[i__ + 1] - 
		x[i__ - 1]) - sig * u[i__ - 2]) / p;
    }
    qn = 0.;
    un = 0.;
    y2[*n] = (un - qn * u[*n - 2]) / (qn * y2[*n - 1] + 1.);
    for (k = *n - 1; k >= 1; --k) {
	y2[k] = y2[k] * y2[k + 1] + u[k - 1];
    }
    return 0;
} /* splinc_ */

