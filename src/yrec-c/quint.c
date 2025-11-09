/* quint.f -- translated by f2c (version 20061008).
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
/* QUINT */
/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */
/* Subroutine */ int quint_(doublereal *x, doublereal *x0, doublereal *h__, 
	doublereal *y0, doublereal *y1, doublereal *y2, doublereal *y)
{
    static doublereal t, d1, d2;

/*     QUADRATIC INTERPOLATION FOR EQUIDISTANT POINTS */
/*     Y0=Y(X0),Y1=Y(X1),Y2=Y(X2); H=X1-X0=X2-X1; */
/*     COMPUTES Y=Y(X) */
    d1 = *y1 - *y0;
    d2 = *y2 - *y1 * 2. + *y0;
    t = (*x - *x0) / *h__;
    *y = *y0 + t * d1 + t * .5 * (t - 1.) * d2;
    return 0;
} /* quint_ */

