/* inter3.f -- translated by f2c (version 20061008).
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



/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */
/*   INTER3 */
/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */
/* INTER3 */
/* Subroutine */ int inter3_(doublereal *a, doublereal *b, doublereal *c__, 
	doublereal *x)
{
    static doublereal d1, d2, d3, a21, a31, a32, xa1, xa2, xa3;

/* INTER3 IS THE INTERPOLATION ROUTINE FOR DENSITY IN THE LIVERMORE */
/* OPACITY TABLES, AND IT USES A 3-POINT LAGRANGIAN INTERPOLATION SCHEME. */
    /* Parameter adjustments */
    --c__;
    --b;
    --a;

    /* Function Body */
    a32 = a[3] - a[2];
    a31 = a[3] - a[1];
    a21 = a[2] - a[1];
    d1 = a21 * a31;
    d2 = -a21 * a32;
    d3 = a31 * a32;
    xa1 = *x - a[1];
    xa2 = *x - a[2];
    xa3 = *x - a[3];
    b[1] = xa2 * xa3 / d1;
    b[2] = xa1 * xa3 / d2;
    b[3] = xa1 * xa2 / d3;
    c__[1] = (xa2 + xa3) / d1;
    c__[2] = (xa1 + xa3) / d2;
    c__[3] = (xa1 + xa2) / d3;
    return 0;
} /* inter3_ */

