/* ratext.f -- translated by f2c (version 20061008).
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

/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */
/* RATEXT */
/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */
/* Subroutine */ int ratext_(integer *iest, doublereal *xest, doublereal *
	yest, doublereal *yz, doublereal *dy, integer *nv, integer *nuse)
{
    /* System generated locals */
    integer i__1, i__2;

    /* Local variables */
    static doublereal b, c__, d__[105]	/* was [15][7] */;
    static integer j, k;
    static doublereal v, x[11], b1;
    static integer m1;
    static doublereal fx[7], yy, ddy;

/*  SAME AS SR RZEXTR FROM NUMERICAL RECIPES, P.566. */

/*  SAVE CURRENT INDEPENDENT VARIABLE. */
    /* Parameter adjustments */
    --dy;
    --yz;
    --yest;

    /* Function Body */
    x[*iest - 1] = *xest;
    if (*iest == 1) {
	i__1 = *nv;
	for (j = 1; j <= i__1; ++j) {
	    yz[j] = yest[j];
	    d__[j - 1] = yest[j];
	    dy[j] = yest[j];
/* L11: */
	}
    } else {
/*  USE AT MOST NUSE PREVIOUS MEMBERS. */
	m1 = min(*iest,*nuse);
	i__1 = m1 - 1;
	for (k = 1; k <= i__1; ++k) {
	    fx[k] = x[*iest - k - 1] / *xest;
/* L12: */
	}
/*  EVALUATE NEXT DIAGONAL IN TABLEAU. */
	i__1 = *nv;
	for (j = 1; j <= i__1; ++j) {
	    yy = yest[j];
	    v = d__[j - 1];
	    c__ = yy;
	    d__[j - 1] = yy;
	    i__2 = m1;
	    for (k = 2; k <= i__2; ++k) {
		b1 = fx[k - 1] * v;
		b = b1 - c__;
/*  CARE NEEDED TO AVOID DIVISION BY ZERO. */
		if (b != 0.) {
		    b = (c__ - v) / b;
		    ddy = c__ * b;
		    c__ = b1 * b;
		} else {
		    ddy = v;
		}
		v = d__[j + k * 15 - 16];
		d__[j + k * 15 - 16] = ddy;
		yy += ddy;
/* L13: */
	    }
	    dy[j] = ddy;
	    yz[j] = yy;
/* L14: */
	}
    }
    return 0;
} /* ratext_ */

