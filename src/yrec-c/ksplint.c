/* ksplint.f -- translated by f2c (version 20061008).
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

/* Table of constant values */

static integer c__9 = 9;
static integer c__1 = 1;

/* $$$$$$ */
/* Subroutine */ int ksplint_(doublereal *xa, doublereal *ya, doublereal *y2a,
	 doublereal *x, doublereal *y)
{
    /* System generated locals */
    doublereal d__1, d__2, d__3;

    /* Builtin functions */
    integer s_wsle(cilist *), do_lio(integer *, integer *, char *, ftnlen), 
	    e_wsle(void);
    /* Subroutine */ void s_stop(char *, ftnlen);

    /* Local variables */
    static doublereal a, b, h__;
    static integer k, khi, klo;

    /* Fortran I/O blocks */
    static cilist io___5 = { 0, 6, 0, 0, 0 };


    /* Parameter adjustments */
    --y2a;
    --ya;
    --xa;

    /* Function Body */
    klo = 1;
    khi = 4;
L1:
    if (khi - klo > 1) {
	k = (khi + klo) / 2;
	if (xa[k] > *x) {
	    khi = k;
	} else {
	    klo = k;
	}
	goto L1;
    }
/*      WRITE(*,*)KHI,KLO,XA(KHI),XA(KLO),X */
    h__ = xa[khi] - xa[klo];
    if (h__ == 0.) {
	s_wsle(&io___5);
	do_lio(&c__9, &c__1, "Ksplint failure", (ftnlen)15);
	e_wsle();
	s_stop("", (ftnlen)0);
    }
/*      IF(H.EQ.0D0) STOP 911 */
    a = (xa[khi] - *x) / h__;
    b = (*x - xa[klo]) / h__;
/* Computing 3rd power */
    d__1 = a;
/* Computing 3rd power */
    d__2 = b;
/* Computing 2nd power */
    d__3 = h__;
    *y = a * ya[klo] + b * ya[khi] + ((d__1 * (d__1 * d__1) - a) * y2a[klo] + 
	    (d__2 * (d__2 * d__2) - b) * y2a[khi]) * (d__3 * d__3) / 6.;
    return 0;
} /* ksplint_ */

