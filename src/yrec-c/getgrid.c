/* getgrid.f -- translated by f2c (version 20061008).
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

/* $$$$$$ */
/* Subroutine */ int getgrid_(doublereal *hl, doublereal *hp, doublereal *hs, 
	integer *ibeg, integer *iend, integer *m)
{
    /* System generated locals */
    integer i__1;

    /* Builtin functions */
    double exp(doublereal);

    /* Local variables */
    static integer i__;
    static doublereal dl, dm;
    static integer ii;
    static doublereal dp;
    static integer ntab;
    static doublereal ytab[5000];
    extern /* Subroutine */ int osplin_(doublereal *, doublereal *, 
	    doublereal *, doublereal *, integer *, integer *);

/* OUTPUT VARIABLES */
/* INPUT VARIABLES */
/* LOCAL VARIABLES */
/* THIS ROUTINE FORMS THE SUM OF CHI, DEFINED AS */
/* CHI = LOG(M)/DM + L/(LTOT*DL) - LOG(P)/DP, WHERE DM, DP, AND DL ARE */
/* THE POINT SPACINGS FOR LOG MASS, LUMINOSITY, AND PRESSURE RESPECTIVELY. */
/* THIS ROUTINE TRANSFORMS THESE VARIABLES TO AN EQUALLY SPACED GRID FROM */
/* THE FIRST POINT TO THE LAST POINT.  IT RETURNS A SET OF EQUALLY SPACED */
/* CHI VALUES AND THEIR LOCATION IN MASS. */

/* USE THE MODEL CRITERIA FOR ASSIGNING THE SPACING BETWEEN GRID POINTS. */
    /* Parameter adjustments */
    --hs;
    --hp;
    --hl;

    /* Function Body */
    dm = ctol_1.hpttol[1];
    dl = ctol_1.hpttol[8] * hl[*m];
    dp = ctol_1.hpttol[10];
    ntab = *iend - *ibeg + 1;
    i__1 = ntab;
    for (ii = 1; ii <= i__1; ++ii) {
	i__ = *ibeg + ii - 1;
	egrid_1.chi[ii - 1] = hs[i__] / dm + hl[i__] / dl - hp[i__] / dp;
    }
/* DEFINE NTOT EQUAL TO NTAB */
    egrid_1.ntot = ntab;
/* TOTAL NUMBER OF ZONES IS MODULUS OF FINAL CHI PLUS ONE. */
/*      NTOT = INT(CHI(NTAB)-CHI(1))+1 */
/* FOR ROTATION PURPOSES, DEFINE THE MINIMUM NUMBER OF */
/* EQUALLY SPACED SHELLS AS 3. */
    egrid_1.ntot = max(egrid_1.ntot,3);
/* EQUALLY SPACED INCREMENT IN CHI */
/*      CHT = 0.5D0*(CHI(NTAB)+CHI(NTAB-1)) */
/*      CHB = 0.5D0*(CHI(2)+CHI(1)) */
/*      DCHI = (CHT-CHB)/FLOAT(NTOT-2) */
    egrid_1.dchi = (egrid_1.chi[ntab - 1] - egrid_1.chi[0]) / (doublereal) (
	    egrid_1.ntot - 1);
/* ASSIGN VECTOR OF EQUALLY SPACED CHI */
/*       ECHI(1) = CHB - 0.5D0*DCHI */
/*       DO I = 2,NTOT */
/*          ECHI(I) = ECHI(I-1)+DCHI */
/*       END DO */
    egrid_1.echi[0] = egrid_1.chi[0];
    i__1 = egrid_1.ntot;
    for (i__ = 2; i__ <= i__1; ++i__) {
	egrid_1.echi[i__ - 1] = egrid_1.echi[i__ - 2] + egrid_1.dchi;
    }
/* NOW ASSIGN MASSES TO THE NEW EQUALLY SPACED GRID POINTS. */
/* PERFORM INTERPOLATION IN LOG MASS - CONSISTENT WITH CHI DEFINED */
/* IN LOG M, LOG P, ETC. */
    i__1 = ntab;
    for (i__ = 1; i__ <= i__1; ++i__) {
	ytab[i__ - 1] = hs[*ibeg + i__ - 1];
    }
    osplin_(egrid_1.echi, egrid_1.es1, egrid_1.chi, ytab, &ntab, &
	    egrid_1.ntot);
/* TRANSFORM TO PHYSICAL MASS (GM) */
    i__1 = egrid_1.ntot;
    for (i__ = 1; i__ <= i__1; ++i__) {
	egrid_1.es1[i__ - 1] = exp(const1_1.cln * egrid_1.es1[i__ - 1]);
    }
    return 0;
} /* getgrid_ */

