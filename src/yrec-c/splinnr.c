/* splinnr.f -- translated by f2c (version 20061008).
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

/* Subroutine */ int splinnr_(real *x, real *y, integer *n, real *yp1, real *
	ypn, real *y2)
{
    /* System generated locals */
    integer i__1;

    /* Local variables */
    static integer i__, k;
    static real p, u[500], qn, un, sig;

    /* Parameter adjustments */
    --y2;
    --y;
    --x;

    /* Function Body */
    if (*yp1 > 9.9e29f) {
	y2[1] = 0.f;
	u[0] = 0.f;
    } else {
	y2[1] = -.5f;
	u[0] = 3.f / (x[2] - x[1]) * ((y[2] - y[1]) / (x[2] - x[1]) - *yp1);
    }
    i__1 = *n - 1;
    for (i__ = 2; i__ <= i__1; ++i__) {
	sig = (x[i__] - x[i__ - 1]) / (x[i__ + 1] - x[i__ - 1]);
	p = sig * y2[i__ - 1] + 2.f;
	y2[i__] = (sig - 1.f) / p;
	u[i__ - 1] = (((y[i__ + 1] - y[i__]) / (x[i__ + 1] - x[i__]) - (y[i__]
		 - y[i__ - 1]) / (x[i__] - x[i__ - 1])) * 6.f / (x[i__ + 1] - 
		x[i__ - 1]) - sig * u[i__ - 2]) / p;
/* L11: */
    }
    if (*ypn > 9.9e29f) {
	qn = 0.f;
	un = 0.f;
    } else {
	qn = .5f;
	un = 3.f / (x[*n] - x[*n - 1]) * (*ypn - (y[*n] - y[*n - 1]) / (x[*n] 
		- x[*n - 1]));
    }
    y2[*n] = (un - qn * u[*n - 2]) / (qn * y2[*n - 1] + 1.f);
    for (k = *n - 1; k >= 1; --k) {
	y2[k] = y2[k] * y2[k + 1] + u[k - 1];
/* L12: */
    }
    return 0;
} /* splinnr_ */

