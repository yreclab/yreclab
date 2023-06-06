/* ovrot.f -- translated by f2c (version 20100827).
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
/* Subroutine */ int ovrot_(doublereal *hcomp, doublereal *hd, doublereal *hp,
	 doublereal *hr, doublereal *hs, doublereal *ht, logical *lc, integer 
	*m, logical *lcz, integer *mrzone, integer *mxzone, integer *nrzone, 
	integer *nzone)
{
    /* System generated locals */
    integer i__1, i__2;

    /* Local variables */
    static integer i__, j, jenv, jcore, nzone0, mxzon0[24]	/* was [12][2]
	     */;
    extern /* Subroutine */ int convec_(doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, logical *,
	     integer *, integer *, integer *, integer *, integer *, integer *,
	     integer *, integer *, integer *);

/* ISOLATE CONVECTIVE REGIONS INCLUDING OVERSHOOT. */
    /* Parameter adjustments */
    mxzone -= 13;
    mrzone -= 14;
    --lcz;
    --lc;
    --ht;
    --hs;
    --hr;
    --hp;
    --hd;
    hcomp -= 16;

    /* Function Body */
    convec_(&hcomp[16], &hd[1], &hp[1], &hr[1], &hs[1], &ht[1], &lc[1], m, &
	    mrzone[14], &mxzone[13], mxzon0, &jcore, &jenv, nrzone, nzone, &
	    nzone0);
    i__1 = *nrzone;
    for (j = 1; j <= i__1; ++j) {
	i__2 = mrzone[j + 26];
	for (i__ = mrzone[j + 13]; i__ <= i__2; ++i__) {
	    lcz[i__] = FALSE_;
/* L5: */
	}
/* L10: */
    }
    i__1 = *nzone;
    for (j = 1; j <= i__1; ++j) {
	i__2 = mxzone[j + 24];
	for (i__ = mxzone[j + 12]; i__ <= i__2; ++i__) {
	    lcz[i__] = TRUE_;
/* L15: */
	}
/* L20: */
    }
    return 0;
} /* ovrot_ */

