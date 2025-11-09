/* intmom.f -- translated by f2c (version 20061008).
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
    doublereal cln, clni, c4pi, c4pil, c4pi3l, cc13, cc23, cpi;
} const1_;

#define const1_1 const1_

/* $$$$$$ */
/* Subroutine */ int intmom_(doublereal *a, doublereal *eta2x, doublereal *
	qr0r, doublereal *r0r, doublereal *him, doublereal *qiwm)
{
    /* Initialized data */

    static doublereal c__[5] = { .6,.72857142857143,.50884115884115,
	    .49728653699242,.42852079651326 };

    /* Builtin functions */
    double pow_di(doublereal *, integer *);

    /* Local variables */
    static integer j;
    static doublereal h1, sum, sum2;

/*  RETURN MOMENT OF INERTIA PER UNIT MASS AT THE SPECIFIED POINT(HI) */
/*  AND DI/D OMEGA PER UNIT MASS(QIW) */
    h1 = const1_1.cc23 * *qr0r * *r0r;
    sum = 0.;
    sum2 = 0.;
    for (j = 1; j <= 5; ++j) {
	sum += c__[j - 1] * (j * *eta2x + 5.) * pow_di(a, &j);
	sum2 += j * c__[j - 1] * (j * *eta2x + 5.) * pow_di(a, &j);
/* L10: */
    }
    *him = h1 * (sum * .15 + 1.);
    *qiwm = h1 * (sum2 * .15);
    return 0;
} /* intmom_ */

