/* ifermi12.f -- translated by f2c (version 20061008).
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

doublereal ifermi12_(doublereal *f)
{
    /* Initialized data */

    static doublereal an = .5;
    static integer m1 = 4;
    static integer k1 = 3;
    static integer m2 = 6;
    static integer k2 = 5;
    static doublereal a1[12] = { 19992.66880833,5702.479099336,661.0132843877,
	    38.18838129486,1. };
    static doublereal b1[12] = { 17718.04140488,-2014.785161019,
	    91.30355392717,-1.670718177489 };
    static doublereal a2[12] = { -.01277060388085,.07187946804945,
	    -.4262314235106,.4997559426872,-1.285579118012,-.3930805454272,1. 
	    };
    static doublereal b2[12] = { -.009745794806288,.05485432756838,
	    -.329946624326,.4077841975923,-1.145531476975,-.06067091689181 };

    /* System generated locals */
    doublereal ret_val, d__1;

    /* Builtin functions */
    double log(doublereal), pow_dd(doublereal *, doublereal *);

    /* Local variables */
    static integer i__;
    static doublereal ff, rn, den;

/* ..this routine applies a rational function expansion to get the inverse */
/* ..fermi-dirac integral of order 1/2 when it is equal to f. */
/* ..maximum error is 4.19d-9.   reference: antia apjs 84,101 1993 */
/* ..declare */
/*     1                 z,drn */
/* ..load the coefficients of the expansion */
    if (*f < 4.) {
	rn = *f + a1[m1 - 1];
	for (i__ = m1 - 1; i__ >= 1; --i__) {
	    rn = rn * *f + a1[i__ - 1];
	}
	den = b1[k1];
	for (i__ = k1; i__ >= 1; --i__) {
	    den = den * *f + b1[i__ - 1];
	}
	ret_val = log(*f * rn / den);
    } else {
	d__1 = 1. / (an + 1.);
	ff = 1. / pow_dd(f, &d__1);
	rn = ff + a2[m2 - 1];
	for (i__ = m2 - 1; i__ >= 1; --i__) {
	    rn = rn * ff + a2[i__ - 1];
	}
	den = b2[k2];
	for (i__ = k2; i__ >= 1; --i__) {
	    den = den * ff + b2[i__ - 1];
	}
	ret_val = rn / (den * ff);
    }
    return ret_val;
} /* ifermi12_ */

