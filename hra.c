/* hra.f -- translated by f2c (version 20100827).
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

/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */
/*     HRA   EVALUATE FIT TO HARVARD REFERENCE ATMOSPHERE T-TAU */
/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */
/*     SPEED THIS UP BY PUTTING CONTSTANTS IN VARIABLES */
/*     TAKES TAU AND RETURNS LOG10(T) */
doublereal hra_(doublereal *tau)
{
    /* System generated locals */
    doublereal ret_val;

    /* Builtin functions */
    double d_lg10(doublereal *);

    /* Local variables */
    static doublereal x, tl, tl2, tl3, tl4, tl5, tl6, tl7, tl8, tl9;

    tl = d_lg10(tau);
    x = 3.81152046471;
    x += tl * .146133736471;
    tl2 = tl * tl;
    x += tl2 * .0267719174279;
    tl3 = tl2 * tl;
    x -= tl3 * .029280655317;
    tl4 = tl3 * tl;
    x -= tl4 * .0123814456666;
    tl5 = tl4 * tl;
    x += tl5 * .00285734990893;
    tl6 = tl5 * tl;
    x += tl6 * .0024575213331;
    tl7 = tl6 * tl;
    x += tl7 * 5.21560431455e-4;
    tl8 = tl7 * tl;
    x += tl8 * 4.71770176883e-5;
    tl9 = tl8 * tl;
    x += tl9 * 1.58685112637e-6;
    ret_val = x;
    return ret_val;
} /* hra_ */

