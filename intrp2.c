/* intrp2.f -- translated by f2c (version 20100827).
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
/* INTEP2 */
/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */
/* Subroutine */ int intrp2_(doublereal *a, doublereal *b, doublereal *x)
{
    static doublereal d1, d2, d3, d4, a21, a31, a41, a42, a43, a32, xa1, xa2, 
	    xa3, xa4;

/* INTERP WITHOUT DERIVATIVES */
/* INTERP IS THE INTERPOLATION ROUTINE FOR THE VANDENBERG */
/* OPACITY TABLES(CAPPA), AND IT USES A 4-POINT LAGRANGIAN */
/* INTERPOLATION SCHEME. */
    /* Parameter adjustments */
    --b;
    --a;

    /* Function Body */
    a43 = a[4] - a[3];
    a42 = a[4] - a[2];
    a41 = a[4] - a[1];
    a32 = a[3] - a[2];
    a31 = a[3] - a[1];
    a21 = a[2] - a[1];
    d1 = -a21 * a31 * a41;
    d2 = a21 * a32 * a42;
    d3 = -a31 * a32 * a43;
    d4 = a41 * a42 * a43;
    xa1 = *x - a[1];
    xa2 = *x - a[2];
    xa3 = *x - a[3];
    xa4 = *x - a[4];
    b[1] = xa2 * xa3 * xa4 / d1;
    b[2] = xa1 * xa3 * xa4 / d2;
    b[3] = xa1 * xa2 * xa4 / d3;
    b[4] = xa1 * xa2 * xa3 / d4;
    return 0;
} /* intrp2_ */

