/* zfermim12.f -- translated by f2c (version 20100827).
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

doublereal zfermim12_(doublereal *x)
{
    /* Initialized data */

    static integer m1 = 7;
    static integer k1 = 7;
    static integer m2 = 11;
    static integer k2 = 11;
    static doublereal a1[12] = { 17144637.4704454,38814830.2324068,
	    31674338.5304962,11458760.9192151,1836963.70756153,
	    114980.998186874,1982.76889924768,1. };
    static doublereal b1[12] = { 9672825.87452899,28738643.6731785,
	    32607013.0734158,17765702.7846367,4816480.22267831,
	    613709.569333207,31359.5854332114,435.061725080755 };
    static doublereal a2[12] = { -4.46620341924942e-15,-1.58654991146236e-12,
	    -4.44467627042232e-10,-6.84738791621745e-8,-6.64932238528105e-6,
	    -3.69976170193942e-4,-.0112295393687006,-.160926102124442,
	    -.852408612877447,-.745519953763928,2.98435207466372,1. };
    static doublereal b2[12] = { -2.23310170962369e-15,-7.94193282071464e-13,
	    -2.22564376956228e-10,-3.43299431079845e-8,-3.33919612678907e-6,
	    -1.86432212187088e-4,-.00569764436880529,-.0834904593067194,
	    -.47877084400944,-.499759250374148,1.86795964993052,
	    .416485970495288 };

    /* System generated locals */
    doublereal ret_val;

    /* Builtin functions */
    double exp(doublereal), sqrt(doublereal);

    /* Local variables */
    static integer i__;
    static doublereal rn, xx, den;

/* ..this routine applies a rational function expansion to get the fermi-dirac */
/* ..integral of order -1/2 evaluated at x. maximum error is 1.23d-12. */
/* ..reference: antia apjs 84,101 1993 */
/* ..declare */
/* ..load the coefficients of the expansion */
    if (*x < 2.) {
	xx = exp(*x);
	rn = xx + a1[m1 - 1];
	for (i__ = m1 - 1; i__ >= 1; --i__) {
	    rn = rn * xx + a1[i__ - 1];
	}
	den = b1[k1];
	for (i__ = k1; i__ >= 1; --i__) {
	    den = den * xx + b1[i__ - 1];
	}
	ret_val = xx * rn / den;
/* .. */
    } else {
	xx = 1. / (*x * *x);
	rn = xx + a2[m2 - 1];
	for (i__ = m2 - 1; i__ >= 1; --i__) {
	    rn = rn * xx + a2[i__ - 1];
	}
	den = b2[k2];
	for (i__ = k2; i__ >= 1; --i__) {
	    den = den * xx + b2[i__ - 1];
	}
	ret_val = sqrt(*x) * rn / den;
    }
    return ret_val;
} /* zfermim12_ */

