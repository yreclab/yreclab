/* ctridi.f -- translated by f2c (version 20100827).
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
    doublereal a[5000], b[5000], c__[5000], d__[5000], u[5000], gama[5000];
} tridi_;

#define tridi_1 tridi_

/* $$$$$$ */
/* Subroutine */ int ctridi_(integer *n)
{
    /* System generated locals */
    integer i__1;

    /* Builtin functions */
    /* Subroutine */ int s_stop(char *, ftnlen);

    /* Local variables */
    static integer j;
    static doublereal bet;

/*  SOLVES A TRIDIAGONAL MATRIX SYSTEM FOR THE FRACTIONAL ABUNDANCE */
/*  OF A SPECIES. NEW ABUNDANCE IS STORED IN ARRAY U. */
/*  THIS ROUTINE IS FROM NUMERICAL RECIPES, P.40. */
    bet = tridi_1.b[0];
    tridi_1.u[0] = tridi_1.d__[0] / bet;
    i__1 = *n;
    for (j = 2; j <= i__1; ++j) {
	tridi_1.gama[j - 1] = tridi_1.c__[j - 2] / bet;
	bet = tridi_1.b[j - 1] - tridi_1.a[j - 1] * tridi_1.gama[j - 1];
	if (bet == 0.) {
	    s_stop("#TRIDIA:SINGULAR MATRIX", (ftnlen)23);
	}
	tridi_1.u[j - 1] = (tridi_1.d__[j - 1] - tridi_1.a[j - 1] * tridi_1.u[
		j - 2]) / bet;
/* L1: */
    }
    for (j = *n - 1; j >= 1; --j) {
	tridi_1.u[j - 1] -= tridi_1.gama[j] * tridi_1.u[j];
/* L2: */
    }
    return 0;
} /* ctridi_ */

