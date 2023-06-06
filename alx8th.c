/* alx8th.f -- translated by f2c (version 20100827).
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
    doublereal tgr[23], xxg[7], r0gr[17], zzg[15];
} galot_;

#define galot_1 galot_

struct {
    doublereal capalex[3128]	/* was [8][23][17] */, xe, ze;
    integer ix, it, id;
} alot_;

#define alot_1 alot_

/*  SUBROUTINE FOR GENERATING SURFACE X TABLES FOR ALEXANDER OPACITIES */
/* Subroutine */ int alx8th_(doublereal *x)
{
    static integer i__, j;
    static doublereal fx[4], qr[4];
    extern /* Subroutine */ int intrp2_(doublereal *, doublereal *, 
	    doublereal *);

/*     ALEX LOW T OPACITY */
    alot_1.xe = *x;
/* FIND 4 NEAREST TABLES IN X. */
    if (*x < galot_1.xxg[3]) {
	if (*x > galot_1.xxg[2]) {
	    alot_1.ix = 2;
	} else {
	    alot_1.ix = 1;
	}
    } else {
	if (*x > galot_1.xxg[4]) {
	    alot_1.ix = 4;
	} else {
	    alot_1.ix = 3;
	}
    }
    for (i__ = 1; i__ <= 4; ++i__) {
	qr[i__ - 1] = galot_1.xxg[alot_1.ix + i__ - 2];
    }
    intrp2_(qr, fx, x);
    for (i__ = 1; i__ <= 23; ++i__) {
	for (j = 1; j <= 17; ++j) {
	    alot_1.capalex[(i__ + j * 23 << 3) - 185] = fx[0] * 
		    alot_1.capalex[alot_1.ix + (i__ + j * 23 << 3) - 193] + 
		    fx[1] * alot_1.capalex[alot_1.ix + 1 + (i__ + j * 23 << 3)
		     - 193] + fx[2] * alot_1.capalex[alot_1.ix + 2 + (i__ + j 
		    * 23 << 3) - 193] + fx[3] * alot_1.capalex[alot_1.ix + 3 
		    + (i__ + j * 23 << 3) - 193];
	}
    }
    return 0;
} /* alx8th_ */

