/* ludcmp.f -- translated by f2c (version 20100827).
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

/* ******************************************************** */
/* Subroutine */ int ludcmp_(doublereal *a, integer *n, integer *np, integer *
	indx, doublereal *d__)
{
    /* System generated locals */
    integer a_dim1, a_offset, i__1, i__2, i__3;
    doublereal d__1, d__2;

    /* Builtin functions */
    /* Subroutine */ int s_stop(char *, ftnlen);

    /* Local variables */
    static integer i__, j, k;
    static doublereal vv[100], dum, sum;
    static integer imax;
    static doublereal aamax;

/*     .. Parameters .. */
/*      REAL TINY */
/*     .. */
/*     .. Scalar Arguments .. */
/*      REAL D */
/*     .. */
/*     .. Array Arguments .. */
/*     .. */
/*     .. Local Scalars .. */
/*      REAL AAMAX,DUM,SUM */
/*     .. */
/*     .. Local Arrays .. */
/*     .. */
/*     .. Intrinsic Functions .. */
/*     .. */
    /* Parameter adjustments */
    --indx;
    a_dim1 = *np;
    a_offset = 1 + a_dim1;
    a -= a_offset;

    /* Function Body */
    *d__ = 1.;
    i__1 = *n;
    for (i__ = 1; i__ <= i__1; ++i__) {
	aamax = 0.;
	i__2 = *n;
	for (j = 1; j <= i__2; ++j) {
	    if ((d__1 = a[i__ + j * a_dim1], abs(d__1)) > aamax) {
		aamax = (d__2 = a[i__ + j * a_dim1], abs(d__2));
	    }
/* L11: */
	}
	if (aamax == 0.) {
	    s_stop("Singular matrix.", (ftnlen)16);
	}
	vv[i__ - 1] = 1. / aamax;
/* L12: */
    }
    i__1 = *n;
    for (j = 1; j <= i__1; ++j) {
	if (j > 1) {
	    i__2 = j - 1;
	    for (i__ = 1; i__ <= i__2; ++i__) {
		sum = a[i__ + j * a_dim1];
		if (i__ > 1) {
		    i__3 = i__ - 1;
		    for (k = 1; k <= i__3; ++k) {
			sum -= a[i__ + k * a_dim1] * a[k + j * a_dim1];
/* L13: */
		    }
		    a[i__ + j * a_dim1] = sum;
		}
/* L14: */
	    }
	}
	aamax = 0.;
	i__2 = *n;
	for (i__ = j; i__ <= i__2; ++i__) {
	    sum = a[i__ + j * a_dim1];
	    if (j > 1) {
		i__3 = j - 1;
		for (k = 1; k <= i__3; ++k) {
		    sum -= a[i__ + k * a_dim1] * a[k + j * a_dim1];
/* L15: */
		}
		a[i__ + j * a_dim1] = sum;
	    }
	    dum = vv[i__ - 1] * abs(sum);
	    if (dum >= aamax) {
		imax = i__;
		aamax = dum;
	    }
/* L16: */
	}
	if (j != imax) {
	    i__2 = *n;
	    for (k = 1; k <= i__2; ++k) {
		dum = a[imax + k * a_dim1];
		a[imax + k * a_dim1] = a[j + k * a_dim1];
		a[j + k * a_dim1] = dum;
/* L17: */
	    }
	    *d__ = -(*d__);
	    vv[imax - 1] = vv[j - 1];
	}
	indx[j] = imax;
	if (j != *n) {
	    if (a[j + j * a_dim1] == 0.) {
		a[j + j * a_dim1] = 1e-20;
	    }
	    dum = 1. / a[j + j * a_dim1];
	    i__2 = *n;
	    for (i__ = j + 1; i__ <= i__2; ++i__) {
		a[i__ + j * a_dim1] *= dum;
/* L18: */
	    }
	}
/* L19: */
    }
    if (a[*n + *n * a_dim1] == 0.) {
	a[*n + *n * a_dim1] = 1e-20;
    }
    return 0;
} /* ludcmp_ */

