/* zero.f -- translated by f2c (version 20061008).
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
/* ZERO */
/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */
/* Subroutine */ int zero_(doublereal *a, integer *nn)
{
    /* System generated locals */
    integer i__1;

    /* Local variables */
    static integer n;

/*     SETS A(N)=0., N=1,NN */
    /* Parameter adjustments */
    --a;

    /* Function Body */
    i__1 = *nn;
    for (n = 1; n <= i__1; ++n) {
/* KC 2025-05-30 fixed "DO termination statement which is not END DO or CONTINUE" */
/*     1 A(N)=0.D0 */
	a[n] = 0.;
/* L1: */
    }
    return 0;
} /* zero_ */

