/* tridiag_gs.f -- translated by f2c (version 20061008).
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
/* Subroutine */ int tridiag_gs__(doublereal *a, doublereal *b, doublereal *
	c__, doublereal *ex_prime__, integer *npt, doublereal *ex)
{
    /* System generated locals */
    integer i__1;

    /* Builtin functions */
    /* Subroutine */ void s_stop(char *, ftnlen);

    /* Local variables */
    static integer j;
    static doublereal bet, gama[5000];

    /* Parameter adjustments */
    --ex;
    --ex_prime__;
    --c__;
    --b;
    --a;

    /* Function Body */
    bet = b[1];
    ex[1] = ex_prime__[1] / bet;
    i__1 = *npt;
    for (j = 2; j <= i__1; ++j) {
	gama[j - 1] = c__[j - 1] / bet;
	bet = b[j] - a[j] * gama[j - 1];
	if (bet == 0.) {
	    s_stop("#TRIDIA:SINGULAR MATRIX", (ftnlen)23);
	}
	ex[j] = (ex_prime__[j] - a[j] * ex[j - 1]) / bet;
/* L1: */
    }
    for (j = *npt - 1; j >= 1; --j) {
	ex[j] -= gama[j] * ex[j + 1];
/* L2: */
    }
/*  911  FORMAT(1P6E10.2) */
    return 0;
} /* tridiag_gs__ */

