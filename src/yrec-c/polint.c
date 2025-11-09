/* polint.f -- translated by f2c (version 20061008).
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



/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */
/* POLINT */
/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */
/* Subroutine */ int polint_(doublereal *xa, doublereal *ya, integer *n, 
	doublereal *x, doublereal *y, doublereal *dy)
{
    /* System generated locals */
    integer i__1, i__2;
    doublereal d__1;

    /* Builtin functions */
    /* Subroutine */ void s_stop(char *, ftnlen);

    /* Local variables */
    static doublereal c__[20], d__[20];
    static integer i__, j;
    static doublereal w, ho, hp;
    static integer ns;
    static doublereal dif, den, dift;

/* MHP 10/02 dimensions changed for consistency with fpft */
    /* Parameter adjustments */
    --ya;
    --xa;

    /* Function Body */
    ns = 1;
    dif = (d__1 = *x - xa[1], abs(d__1));
    i__1 = *n;
    for (i__ = 1; i__ <= i__1; ++i__) {
	dift = (d__1 = *x - xa[i__], abs(d__1));
	if (dift < dif) {
	    ns = i__;
	    dif = dift;
	}
	c__[i__ - 1] = ya[i__];
	d__[i__ - 1] = ya[i__];
/* L10: */
    }
    *y = ya[ns];
    --ns;
    i__1 = *n - 1;
    for (j = 1; j <= i__1; ++j) {
	i__2 = *n - j;
	for (i__ = 1; i__ <= i__2; ++i__) {
	    ho = xa[i__] - *x;
	    hp = xa[i__ + j] - *x;
	    w = c__[i__] - d__[i__ - 1];
	    den = ho - hp;
	    if (abs(den) < 1e-20) {
		s_stop("", (ftnlen)0);
	    }
	    den = w / den;
	    d__[i__ - 1] = hp * den;
	    c__[i__ - 1] = ho * den;
/* L20: */
	}
	if (ns << 1 < *n - j) {
	    *dy = c__[ns];
	} else {
	    *dy = d__[ns - 1];
	    --ns;
	}
	*y += *dy;
/* L30: */
    }
    return 0;
} /* polint_ */

