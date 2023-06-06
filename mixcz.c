/* mixcz.f -- translated by f2c (version 20100827).
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
    logical lexcom;
} flag_;

#define flag_1 flag_

struct {
    doublereal xenv, zenv, zenvm, amuenv, fxenv[12], xnew, znew, stotal, senv;
} comp_;

#define comp_1 comp_

/* $$$$$$ */
/* Subroutine */ int mixcz_(doublereal *hcomp, doublereal *hs2, logical *lcz, 
	integer *m)
{
    /* System generated locals */
    integer i__1, i__2;
    doublereal d__1, d__2;

    /* Local variables */
    static integer i__, j, i1, i2, jj, mp1;
    static logical lcc;
    static integer iend;
    static doublereal xsum[15], wtsum;
    static integer mxzone[24];

/* COMPUTE STANDARD CONVECTION ZONES */
    /* Parameter adjustments */
    --lcz;
    --hs2;
    hcomp -= 16;

    /* Function Body */
    j = 1;
    lcc = FALSE_;
    mp1 = *m + 1;
    lcz[mp1] = FALSE_;
    i__1 = mp1;
    for (i__ = 1; i__ <= i__1; ++i__) {
	if (! lcz[i__]) {
	    goto L10;
	}
/* CONVECTION ZONE */
	if (lcc) {
	    goto L11;
	}
/* START OF CONVECTION ZONE */
	lcc = TRUE_;
	i1 = i__;
	goto L11;
L10:
	if (! lcc) {
	    goto L11;
	}
/*   END OF CONVECTION ZONE */
	lcc = FALSE_;
	mxzone[j - 1] = i1;
	mxzone[j] = i__ - 1;
	j += 2;
	if (j < 24) {
	    goto L11;
	}
	goto L12;
L11:
	;
    }
    mxzone[j - 1] = 0;
L12:
    iend = 11;
    if (flag_1.lexcom) {
	iend = 15;
    }
/* MIX ALL CONVECTIVE ZONES */
    for (j = 1; j <= 24; j += 2) {
	if (mxzone[j - 1] <= 0) {
	    goto L110;
	}
	i1 = mxzone[j - 1];
/* Computing MIN */
	i__1 = *m, i__2 = mxzone[j];
	i2 = min(i__1,i__2);
/* L903: */
	if (i1 != 1 && i1 >= i2) {
	    goto L100;
	}
/* INITIALIZE SUMS */
/* L904: */
	wtsum = 0.;
	i__1 = iend;
	for (i__ = 1; i__ <= i__1; ++i__) {
	    xsum[i__ - 1] = 0.;
/* L40: */
	}
	i__1 = i2;
	for (jj = i1; jj <= i__1; ++jj) {
	    wtsum += hs2[jj];
	    i__2 = iend;
	    for (i__ = 1; i__ <= i__2; ++i__) {
		xsum[i__ - 1] += hcomp[i__ + jj * 15] * hs2[jj];
/* L50: */
	    }
/* L60: */
	}
	i__1 = iend;
	for (i__ = 1; i__ <= i__1; ++i__) {
	    xsum[i__ - 1] /= wtsum;
/* L70: */
	}
	i__1 = i2;
	for (jj = i1; jj <= i__1; ++jj) {
	    i__2 = iend;
	    for (i__ = 1; i__ <= i__2; ++i__) {
		hcomp[i__ + jj * 15] = xsum[i__ - 1];
/* L80: */
	    }
/* L90: */
	}
L100:
	;
    }
L110:
/* RENORMALIZE COMPOSITION IF NECESSARY */
    i__1 = *m;
    for (i__ = 1; i__ <= i__1; ++i__) {
/* Computing MAX */
	d__1 = hcomp[i__ * 15 + 1];
	hcomp[i__ * 15 + 1] = max(d__1,0.);
/* Computing MIN */
	d__1 = hcomp[i__ * 15 + 3], d__2 = 1. - hcomp[i__ * 15 + 1];
	hcomp[i__ * 15 + 3] = min(d__1,d__2);
/* Computing MAX */
	d__1 = hcomp[i__ * 15 + 9], d__2 = (hcomp[i__ * 15 + 3] - 
		comp_1.zenvm) * 9.9e-4;
	hcomp[i__ * 15 + 9] = max(d__1,d__2);
/* L140: */
    }
    return 0;
} /* mixcz_ */

