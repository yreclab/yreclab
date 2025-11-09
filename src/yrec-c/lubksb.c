/* lubksb.f -- translated by f2c (version 20061008).
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

/* ******************************************************************** */
/* Subroutine */ int lubksb_(doublereal *a, integer *n, integer *np, integer *
	indx, doublereal *b)
{
    /* System generated locals */
    integer a_dim1, a_offset, i__1, i__2;

    /* Local variables */
    static integer i__, j, ii, ll;
    static doublereal sum;

/*     .. Scalar Arguments .. */
/*     .. */
/*     .. Array Arguments .. */
/*     .. */
/*     .. Local Scalars .. */
/*      REAL SUM */
/*     .. */
    /* Parameter adjustments */
    --b;
    --indx;
    a_dim1 = *np;
    a_offset = 1 + a_dim1;
    a -= a_offset;

    /* Function Body */
    ii = 0;
    i__1 = *n;
    for (i__ = 1; i__ <= i__1; ++i__) {
	ll = indx[i__];
	sum = b[ll];
	b[ll] = b[i__];
	if (ii != 0) {
	    i__2 = i__ - 1;
	    for (j = ii; j <= i__2; ++j) {
		sum -= a[i__ + j * a_dim1] * b[j];
/* L11: */
	    }
	} else if (sum != 0.) {
	    ii = i__;
	}
	b[i__] = sum;
/* L12: */
    }
    for (i__ = *n; i__ >= 1; --i__) {
	sum = b[i__];
	if (i__ < *n) {
	    i__1 = *n;
	    for (j = i__ + 1; j <= i__1; ++j) {
		sum -= a[i__ + j * a_dim1] * b[j];
/* L13: */
	    }
	}
	b[i__] = sum / a[i__ + i__ * a_dim1];
/* L14: */
    }
    return 0;
} /* lubksb_ */

