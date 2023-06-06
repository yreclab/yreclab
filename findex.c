/* findex.f -- translated by f2c (version 20100827).
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



/*  INTERPOLATION PKG FOR COX'S AND FOR KURUCZ'S OPACITIES */
/*     SUBROUTINE FINDEX(AX,NX,X,M)               FIND INDEX */
/*     SUBROUTINE INTPOL(XI,F,N,XBAR,YBAR,YBARP)  PIECEWISE INTERPOL R */
/*     SUBROUTINE YSPLIN(XI,C,N)                  SPLINE R */



/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */
/* FINDEX */
/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */
/* YCK 3/91 */
/* Subroutine */ int findex_(doublereal *ax, integer *nx, doublereal *x, 
	integer *m)
{
    /* System generated locals */
    integer i__1;

    /* Local variables */
    static integer kip, iyc;

/* FIND THE 'M' */
    /* Parameter adjustments */
    --ax;

    /* Function Body */
    if (*m < 1 || *m > *nx) {
	*m = 1;
    }
    kip = *m;
    if (*x < ax[kip]) {
	for (iyc = kip - 1; iyc >= 1; --iyc) {
	    if (ax[iyc] <= *x) {
		kip = iyc;
		goto L213;
	    }
/* L211: */
	}
	kip = -1;
    } else {
	i__1 = *nx - 1;
	for (iyc = kip; iyc <= i__1; ++iyc) {
	    if (ax[iyc + 1] > *x) {
		kip = iyc;
		goto L213;
	    }
/* L212: */
	}
	kip = -(*nx);
    }
L213:
    *m = kip;
    return 0;
} /* findex_ */

