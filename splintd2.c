/* splintd2.f -- translated by f2c (version 20100827).
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

/* Common Block Declarations */

struct {
    integer ilast, idebug, itrack, ishort, imilne, imodpt, istor, iowr;
} luout_;

#define luout_1 luout_

/* Table of constant values */

static integer c__9 = 9;
static integer c__1 = 1;


/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */
/* SUBROUTINE SPLINTD */
/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */
/* REAL*8 VERSION */
/* TAKEN FROM NUMERICAL RECIPES, PRESS, ET AL, P89. */
/* GIVEN THE ARRAYS XA AND YA OF LENGTH N, WHICH TABULATE A FUNCTION */
/* (WITH THE XA[I]'S IN ORDER), AND GIVEN THE ARRAY Y2A, WHICH IS THE */
/* OUTPUT OF SPLINE ABOVE, AND GIVEN A VALUE OF X, THIS ROUTINE RETURNS */
/* A CUBIC-SPLINE INTERPOLATED VALUE Y. */
/* Subroutine */ int splintd2_(doublereal *xa, doublereal *ya, integer *n, 
	doublereal *y2a, doublereal *x, doublereal *y, integer *klo, integer *
	khi)
{
    /* System generated locals */
    doublereal d__1, d__2, d__3;

    /* Builtin functions */
    integer s_wsle(cilist *), do_lio(integer *, integer *, char *, ftnlen), 
	    e_wsle(void);
    /* Subroutine */ int s_stop(char *, ftnlen);

    /* Local variables */
    static doublereal a, b, h__;
    static integer k;

    /* Fortran I/O blocks */
    static cilist io___3 = { 0, 0, 0, 0, 0 };


    /* Parameter adjustments */
    --y2a;
    --ya;
    --xa;

    /* Function Body */
    *klo = 1;
    *khi = *n;
L1:
    if (*khi - *klo > 1) {
	k = (*khi + *klo) / 2;
	if (xa[k] > *x) {
	    *khi = k;
	} else {
	    *klo = k;
	}
	goto L1;
    }
    h__ = xa[*khi] - xa[*klo];
    if (h__ == 0.) {
	io___3.ciunit = luout_1.ishort;
	s_wsle(&io___3);
	do_lio(&c__9, &c__1, "ERROR IN SPLINT ROUTINE.", (ftnlen)24);
	e_wsle();
	s_stop("", (ftnlen)0);
    }
    a = (xa[*khi] - *x) / h__;
    b = (*x - xa[*klo]) / h__;
/* Computing 3rd power */
    d__1 = a;
/* Computing 3rd power */
    d__2 = b;
/* Computing 2nd power */
    d__3 = h__;
    *y = a * ya[*klo] + b * ya[*khi] + ((d__1 * (d__1 * d__1) - a) * y2a[*klo]
	     + (d__2 * (d__2 * d__2) - b) * y2a[*khi]) * (d__3 * d__3) / 6.;
    return 0;
} /* splintd2_ */

