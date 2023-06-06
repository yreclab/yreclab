/* mixgrid.f -- translated by f2c (version 20100827).
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
    doublereal clsun, clsunl, clnsun, cmsun, cmsunl, crsun, crsunl, cmbol;
} const_;

#define const_1 const_

struct {
    doublereal cln, clni, c4pi, c4pil, c4pi3l, cc13, cc23, cpi;
} const1_;

#define const1_1 const1_

struct {
    doublereal cgas, ca3, ca3l, csig, csigl, cgl, cmkh, cmkhn;
} const2_;

#define const2_1 const2_

struct {
    doublereal htoler[10]	/* was [5][2] */, fcorr0, fcorri, fcorr, 
	    hpttol[12];
    integer niter1, niter2, niter3;
} ctol_;

#define ctol_1 ctol_

struct {
    doublereal chi[5000], echi[5000], es1[5000], dchi;
    integer ntot;
} egrid_;

#define egrid_1 egrid_

struct {
    doublereal amum[5000], cpm[5000], delm[5000], delam[5000], delrm[5000], 
	    esumm[5000], om[5000], qdtm[5000], thdifm[5000], velm[5000], 
	    viscm[5000], epsm[5000];
} mdphy_;

#define mdphy_1 mdphy_

struct {
    doublereal xval[5000], yval[5000], xtab[5000], ytab[5000];
} splin_;

#define splin_1 splin_

/* $$$$$$ */
/* Subroutine */ int mixgrid_(doublereal *cod2, doublereal *hd, doublereal *
	hl, doublereal *hp, doublereal *hr, doublereal *hs, doublereal *hs1, 
	doublereal *hs2, doublereal *hstot, integer *ibeg, integer *iend, 
	logical *lcz, integer *m, doublereal *ecod2, doublereal *em, logical *
	ldum2)
{
    /* System generated locals */
    integer i__1;

    /* Builtin functions */
    double exp(doublereal), d_lg10(doublereal *);

    /* Local variables */
    static integer i__, i0, i1;
    static doublereal dl, dm;
    static integer ii;
    static doublereal dp, fac;
    static integer ntab, ntabb;
    static doublereal embot, qchir, emtop;
    extern /* Subroutine */ int osplin_(doublereal *, doublereal *, 
	    doublereal *, doublereal *, integer *, integer *), getgrid_(
	    doublereal *, doublereal *, doublereal *, integer *, integer *, 
	    integer *);

/* INPUT VARIABLES */
/* OUTPUT VARIABLES */
/* FLAG THE SPECIAL CASE OF A SINGLE UNSTABLE INTERFACE AND EXIT */
    /* Parameter adjustments */
    --em;
    --ecod2;
    --lcz;
    --hs2;
    --hs1;
    --hs;
    --hr;
    --hp;
    --hl;
    --hd;
    --cod2;

    /* Function Body */
    if (*iend - *ibeg <= 1) {
	*ldum2 = TRUE_;
	goto L9999;
    } else {
	*ldum2 = FALSE_;
    }
/* DEFINE A GRID OF EQUALLY SPACED POINTS. */
    getgrid_(&hl[1], &hp[1], &hs[1], ibeg, iend, m);
/* GETGRID HAS DEFINED A SET OF CO-ORDINATES (CHI) AND EQUALLY SPACED */
/* MASS POINTS.  NOW FIND THE OTHER QUANTITIES OF INTEREST AT ZONE */
/* CENTERS: */
/* TOTAL ZONE MASSES */
/* INTERMEDIATE POINTS */
    i__1 = egrid_1.ntot - 1;
    for (i__ = 2; i__ <= i__1; ++i__) {
	em[i__] = (egrid_1.es1[i__] - egrid_1.es1[i__ - 2]) * .5;
    }
/* SPECIAL TREATMENT OF THE BOUNDARIES; CAN BE CONVECTIVE. */
/* IF CONVECTIVE SUM OVER ALL SHELLS.  CARE IS NEEDED TO DO BOOK-KEEPING */
/* PROPERLY AT THE EDGES - TOP IS HALFWAY TO EQUALLY SPACED POINT, NOT */
/* HALFWAY TO EDGE OF UNEQUALLY SPACED ORIGINAL SET OF POINTS. */

/* CENTER */
    emtop = (egrid_1.es1[1] + egrid_1.es1[0]) * .5;
    if (*ibeg > 1) {
	embot = (hs1[*ibeg] + hs1[*ibeg - 1]) * .5;
    } else {
	embot = 0.;
    }
    em[1] = emtop - embot;
    if (*ibeg > 1) {
	for (ii = *ibeg - 1; ii >= 1; --ii) {
	    if (! lcz[ii]) {
		i0 = i__ + 1;
		goto L10;
	    }
	    em[1] += hs2[ii];
	}
	i0 = 1;
L10:
	;
    } else {
	i0 = 1;
    }
/* SURFACE */
    embot = (egrid_1.es1[egrid_1.ntot - 1] + egrid_1.es1[egrid_1.ntot - 2]) * 
	    .5;
    if (*iend < *m) {
	emtop = (hs1[*iend] + hs1[*iend + 1]) * .5;
    } else {
	emtop = exp(const1_1.cln * *hstot);
    }
    em[egrid_1.ntot] = emtop - embot;
    if (*iend < *m) {
	i__1 = *m;
	for (ii = *iend + 1; ii <= i__1; ++ii) {
	    if (! lcz[ii]) {
		i1 = i__ - 1;
		goto L20;
	    }
	    em[egrid_1.ntot] += hs2[ii];
	}
	i1 = *m;
L20:
	;
    } else {
	i1 = *m;
    }
/* NOW SOLVE FOR QUANTITIES NEEDED AT THE ZONE EDGES.  THESE ARE */
/* RELATED TO THE DIFFUSION COEFFICIENTS.  UNLIKE THE EQUALLY SPACED */
/* GRID IN R, WE NEED TO INCLUDE A JACOBIAN TERM FOR THE TRANSFORMATION */
/* OF VARIABLES. */
    ntab = *iend - *ibeg + 1;
    splin_1.xtab[0] = egrid_1.chi[0];
    i__1 = ntab;
    for (i__ = 2; i__ <= i__1; ++i__) {
	splin_1.xtab[i__ - 1] = (egrid_1.chi[i__ - 1] + egrid_1.chi[i__ - 2]) 
		* .5;
    }
    ntabb = ntab + 1;
    splin_1.xtab[ntabb - 1] = egrid_1.chi[ntab - 1];
/* DIFFUSION COEFFICIENT FOR MIXING - ASSUME CONSTANT BELOW */
/* BOTTOM INTERFACE OR ABOVE TOP INTERFACE */
    splin_1.ytab[0] = cod2[*ibeg + 1];
    i__1 = ntab;
    for (i__ = 2; i__ <= i__1; ++i__) {
	ii = *ibeg + i__ - 1;
	splin_1.ytab[i__ - 1] = cod2[ii];
    }
    splin_1.ytab[ntabb - 1] = cod2[*iend];
    splin_1.xval[0] = egrid_1.chi[0];
    i__1 = egrid_1.ntot;
    for (i__ = 2; i__ <= i__1; ++i__) {
	splin_1.xval[i__ - 1] = egrid_1.echi[i__ - 1] - egrid_1.dchi * .5;
    }
    osplin_(splin_1.xval, &ecod2[1], splin_1.xtab, splin_1.ytab, &ntabb, &
	    egrid_1.ntot);
/* PRODUCT OF RHO R^2 BY D CHI/DR */
    dm = ctol_1.hpttol[1];
    dl = ctol_1.hpttol[8] * hl[*m] * const_1.clsun;
    dp = ctol_1.hpttol[10];
    i__1 = ntab;
    for (i__ = 1; i__ <= i__1; ++i__) {
	ii = *ibeg + i__ - 1;
	splin_1.xtab[i__ - 1] = egrid_1.chi[i__ - 1];
/* D CHI/DR = 1/DM*( D LOG M/DR) + 1/DL*(DL/DR) - 1/DP*(D LOG P/DR) */
/* OR, USING FAC = 4*PI*RHO*R**2 */
/* D CHI/DR = FAC/(LN 10 * DM * M) + FAC*EPSILON/DL + RHO*GM/(LN10*DP*R**2) */
/* STORED IN YVAL */
	fac = const1_1.c4pi * exp(const1_1.cln * (hd[ii] + hr[ii] * 2.));
	qchir = fac / (const1_1.cln * dm * hs1[ii]) + fac * mdphy_1.epsm[ii - 
		1] / dl + exp(const1_1.cln * (const2_1.cgl + hd[ii] + hs[ii] 
		- hp[ii] - hr[ii] * 2.)) / (const1_1.cln * dp);
	splin_1.ytab[i__ - 1] = hd[ii] + d_lg10(&qchir) + hr[ii] * 2.;
    }
    osplin_(splin_1.xval, splin_1.yval, splin_1.xtab, splin_1.ytab, &ntab, &
	    egrid_1.ntot);
/* NOW ADD MULTIPLICATIVE FACTORS TO DIFFUSION COEFFICIENTS */
    i__1 = egrid_1.ntot;
    for (i__ = 1; i__ <= i__1; ++i__) {
	ecod2[i__] *= exp(const1_1.cln * splin_1.yval[i__ - 1]);
    }
L9999:
    return 0;
} /* mixgrid_ */

