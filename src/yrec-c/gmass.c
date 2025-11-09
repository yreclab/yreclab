/* gmass.f -- translated by f2c (version 20061008).
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

/* ******************************************************************8 */
doublereal gmass_(doublereal *x, doublereal *z__, doublereal *amoles, 
	doublereal *eground, doublereal *fracz, doublereal *frac)
{
    /* Initialized data */

    static doublereal eion[7] = { -3388.637,-1970.918,-1431.717,-993.2303,
	    -76.2315,-15.29409 };
    static doublereal anum[6] = { 10.,8.,7.,6.,2.,1. };

    /* System generated locals */
    doublereal ret_val;

    /* Local variables */
    static integer i__;
    static doublereal xc, xh, xn, xo, xc2, xn2, xo2, xhe, xne, xne2, amas[7], 
	    xtot, anume;

    /* Parameter adjustments */
    --frac;

    /* Function Body */
    xc = .247137766;
    xn = .0620782;
    xo = .52837118;
    xne = .1624188;
    amas[6] = 1.0079;
    amas[5] = 4.0026;
    amas[4] = 12.011;
    amas[3] = 14.0067;
    amas[2] = 15.9994;
    amas[1] = 20.179;
    amas[0] = 5.4858e-4;
    *fracz = *z__ / (xc * amas[4] + xn * amas[3] + xo * amas[2] + xne * amas[
	    1]);
    xc2 = *fracz * xc;
    xn2 = *fracz * xn;
    xo2 = *fracz * xo;
    xne2 = *fracz * xne;
    xh = *x / amas[6];
    xhe = (1. - *x - *z__) / amas[5];
    xtot = xh + xhe + xc2 + xn2 + xo2 + xne2;
    frac[6] = xh / xtot;
    frac[5] = xhe / xtot;
    frac[4] = xc2 / xtot;
    frac[3] = xn2 / xtot;
    frac[2] = xo2 / xtot;
    frac[1] = xne2 / xtot;
    *eground = 0.;
    *amoles = 0.;
    for (i__ = 1; i__ <= 6; ++i__) {
	*eground += eion[i__ - 1] * frac[i__];
	*amoles += (anum[i__ - 1] + 1.) * frac[i__];
    }
    anume = *amoles - 1.;
    ret_val = anume * amas[0];
    for (i__ = 2; i__ <= 7; ++i__) {
	ret_val += amas[i__ - 1] * frac[i__ - 1];
    }
    return ret_val;
} /* gmass_ */

