/* qgauss.f -- translated by f2c (version 20100827).
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

struct {
    doublereal cgas, ca3, ca3l, csig, csigl, cgl, cmkh, cmkhn;
} const2_;

#define const2_1 const2_

/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */
/* QGAUSS */
/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */
/* Subroutine */ int qgauss_(doublereal *g0g, doublereal *ginvg, doublereal *
	sphig, doublereal *b, doublereal *r0, doublereal *hs, doublereal *
	aint, doublereal *q, doublereal *w2, doublereal *a, integer *i__)
{
    /* Initialized data */

    static doublereal x[5] = { .14887433898163,.43339539412925,
	    .67940956829902,.86506336668899,.97390652851717 };
    static doublereal w[5] = { .29552422471475,.26926671931,.21908636251598,
	    .14945134915058,.06667134430869 };

    /* System generated locals */
    doublereal d__1;

    /* Local variables */
    static doublereal g;
    static integer j;
    static doublereal s, g2, s2, dx, xm, xr;
    extern /* Subroutine */ int func_(doublereal *, doublereal *, doublereal *
	    , doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, integer *);

    /* Parameter adjustments */
    --hs;
    --r0;

    /* Function Body */
    xm = .5 * *b;
    xr = xm;
    *g0g = 0.;
    *ginvg = 0.;
    *sphig = 0.;
    for (j = 1; j <= 5; ++j) {
	dx = xr * x[j - 1];
	d__1 = xm + dx;
	func_(&d__1, &g, &s, &r0[1], &hs[1], aint, q, w2, a, i__);
	d__1 = xm - dx;
	func_(&d__1, &g2, &s2, &r0[1], &hs[1], aint, q, w2, a, i__);
	*g0g += w[j - 1] * (g * s + g2 * s2);
	*ginvg += w[j - 1] * (s / g + s2 / g2);
	*sphig += w[j - 1] * (s + s2);
/* L10: */
    }
    *g0g *= xr;
    *ginvg *= xr;
    *sphig *= xr;
    return 0;
} /* qgauss_ */

