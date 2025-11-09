/* quadeos01.f -- translated by f2c (version 20061008).
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

/*     QUADEOSS01 */

/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */
doublereal quadeos01_(integer *ic, integer *i__, doublereal *x, doublereal *
	y1, doublereal *y2, doublereal *y3, doublereal *x1, doublereal *x2, 
	doublereal *x3)
{
    /* System generated locals */
    doublereal ret_val;

    /* Local variables */
    static doublereal c1, c2, c3, xx[3], yy[3], xx12[30], xx13[30], xx23[30], 
	    xx1sq[30], xx1pxx2[30];

/* ..... this function performs a quadratic interpolation. */
    xx[0] = *x1;
    xx[1] = *x2;
    xx[2] = *x3;
    yy[0] = *y1;
    yy[1] = *y2;
    yy[2] = *y3;
    if (*ic == 0) {
	xx12[*i__ - 1] = 1. / (xx[0] - xx[1]);
	xx13[*i__ - 1] = 1. / (xx[0] - xx[2]);
	xx23[*i__ - 1] = 1. / (xx[1] - xx[2]);
	xx1sq[*i__ - 1] = xx[0] * xx[0];
	xx1pxx2[*i__ - 1] = xx[0] + xx[1];
    }
    c3 = (yy[0] - yy[1]) * xx12[*i__ - 1];
    c3 -= (yy[1] - yy[2]) * xx23[*i__ - 1];
    c3 *= xx13[*i__ - 1];
    c2 = (yy[0] - yy[1]) * xx12[*i__ - 1] - xx1pxx2[*i__ - 1] * c3;
    c1 = yy[0] - xx[0] * c2 - xx1sq[*i__ - 1] * c3;
    ret_val = c1 + *x * (c2 + *x * c3);
    return ret_val;
} /* quadeos01_ */

