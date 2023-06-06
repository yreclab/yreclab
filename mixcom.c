/* mixcom.f -- translated by f2c (version 20100827).
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
    doublereal chi[5000], echi[5000], es1[5000], dchi;
    integer ntot;
} egrid_;

#define egrid_1 egrid_

struct {
    doublereal xval[5000], yval[5000], xtab[5000], ytab[5000];
} splin_;

#define splin_1 splin_

struct {
    doublereal a[5000], b[5000], c__[5000], d__[5000], u[5000], gama[5000];
} tridi_;

#define tridi_1 tridi_

/* $$$$$$ */
/* Subroutine */ int mixcom_(doublereal *dt, doublereal *ecod2, doublereal *
	em, doublereal *hs2, integer *ibeg, integer *iend, logical *lcz, 
	logical *lok, integer *m, doublereal *hcomp, integer *jbeg, integer *
	jend)
{
    /* System generated locals */
    integer i__1, i__2;
    doublereal d__1;

    /* Local variables */
    static doublereal sumspec2;
    static integer i__, j, n, i0, i1, id[15], ii, ntab;
    static doublereal test, dcomp, ecomp[5000];
    static integer nspec;
    static doublereal dcomp2;
    extern /* Subroutine */ int ccoeft_(doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, integer *), ctridi_(
	    integer *), osplin_(doublereal *, doublereal *, doublereal *, 
	    doublereal *, integer *, integer *);
    static doublereal sumspec;

/*  DIFCOM CALCULATES THE DIFFUSION OF COMPOSITION DUE TO ANGULAR MOMENTUM */
/*  TRANSPORT.  THIS IS DONE BY TRANSFORMING TO AN EQUALLY SPACED GRID */
/*  WHICH WAS PREVIOUSLY DEFINED AND THEN TRANSFORMING BACK. */

/*  INPUT VARIABLES: */
/*  DT : DIFFUSION TIMESTEP(SEC). */
/*  ECOD2 : DIFFUSION COEFFICIENTS FOR COMPOSITION TRANSPORT AT THE EQUALLY */
/*          SPACED GRID POINTS. */
/*  EM : MASSES OF THE EQUALLY SPACED GRID POINTS(GM). */
/*     NOTE: FOR CONVECTIVE BOUNDARIES THE MASS OF THE LAST GRID POINT IS */
/*           THE MASS OF THE ENTIRE CONVECTION ZONE. */
/*  HCOMP : ARRAY OF MASS FRACTION OF ALL OF THE SPECIES AT THE ORIGINAL */
/*          MODEL POINTS. */
/*  HS2 : MASSES OF THE ORIGINAL MODEL POINTS(UNLOGGED). */
/*  IBEG,IEND :THE FIRST/LAST UNSTABLE POINTS IN THE REGION. */
/*     NOTE: FOR CONVECTIVE BOUNDARIES THESE ARE ONLY THE FIRST CONVECTIVE */
/*           POINTS ADJACENT TO AN UNSTABLE RADIATIVE REGION. */
/*  LCZ : FLAG WHICH TELLS WHICH OF THE ORIGINAL MODEL POINTS ARE */
/*        CONVECTIVE FOR ANGULAR MOMENTUM TRANSPORT PURPOSES(I.E. INCLUDES */
/*        OVERSHOOT REGIONS). LCZ=T IF CONVECTIVE. */
/*  M : NUMBER OF MODEL POINTS. */

/*  OUTPUT VARIABLES: */
/*  HCOMP IS UPDATED IN DIFCOM TO GIVE THE NEW RUN OF COMPOSITION AFTER */
/*  ANGULAR MOMENTUM TRANSPORT. */

/*  BEFORE THE LAST ITERATION(LOK=F),ONLY DIFFUSION OF H,HE4,HE3 CALCULATED */
/*  TO CALCULATE CHANGE IN MU GRADIENTS CAUSED BY DIFFUSION. */
/*  THIS ROUTINE WILL THEREFORE BE CALLED EITHER TO MIX THE OTHER SPECIES */
/*  OR JUST THE FIRST 4 DEPENDING ON LOK. */
/*  DETERMINE WHICH SPECIES VARY OVER THE UNSTABLE REGION. */
    /* Parameter adjustments */
    hcomp -= 16;
    --lcz;
    --hs2;
    --em;
    --ecod2;

    /* Function Body */
    nspec = 0;
    i__1 = *jend;
    for (j = *jbeg; j <= i__1; ++j) {
	test = hcomp[j + *ibeg * 15];
/*  ABUNDANCE 2(HE4) IS DEFINED AS 1-X-Z-HE3 SO IT IS NOT SOLVED FOR. */
	if (j != 2) {
	    i__2 = *iend;
	    for (i__ = *ibeg + 1; i__ <= i__2; ++i__) {
		if ((d__1 = hcomp[j + i__ * 15] - test, abs(d__1)) > 1e-14) {
		    ++nspec;
		    id[nspec - 1] = j;
		    goto L20;
		}
	    }
	}
L20:
	;
    }
    if (nspec == 0) {
	goto L200;
    }
/*  NOW SOLVE FOR DIFFUSION OF ALL SPECIES THAT VARY OVER THE */
/*  UNSTABLE REGION USING THE SAME DIFFUSION COEFFICIENTS. */
    ntab = *iend - *ibeg + 1;
/*  FIND RUN OF COMPOSITION AT THE EQUALLY SPACED GRID POINTS AT THE */
/*  START OF THE DIFFUSION TIMESTEP.  THIS IS DONE USING AN OSCULATORY */
/*  SPLINE. */
    i__1 = nspec;
    for (n = 1; n <= i__1; ++n) {
	i__2 = ntab;
	for (i__ = 1; i__ <= i__2; ++i__) {
	    ii = i__ + *ibeg - 1;
	    splin_1.xtab[i__ - 1] = egrid_1.chi[i__ - 1];
	    splin_1.ytab[i__ - 1] = hcomp[id[n - 1] + ii * 15];
	}
	osplin_(egrid_1.echi, ecomp, splin_1.xtab, splin_1.ytab, &ntab, &
		egrid_1.ntot);
/*  SET UP DIFFUSION EQUATION ARRAYS TO SOLVE FOR COMP AT END OF TSTEP */
	ccoeft_(&ecod2[1], &egrid_1.dchi, dt, ecomp, &em[1], &egrid_1.ntot);
/*  SOLVE MATRIX FOR THE RUN OF COMP AT TIME N+1 AT THE NEW GRID. */
	ctridi_(&egrid_1.ntot);
/*  TRANSFORM BACK TO THE ORIGINAL GRID AND UPDATE HCOMP IN THE */
/*  DIFFUSED REGION. U IS THE NEW RUN OF COMPOSITION IN THE REGION AT THE */
/*  EQUALLY SPACED GRID POINTS. */
/*  FOR THE BOUNDARY POINTS IN THE MODEL,EXTRAPOLATING U PAST THE */
/*  LAST EQUALLY SPACED GRID POINTS CAN LEAD TO SERIOUS ERRORS. */
/*  THEREFORE ADD THE *CHANGE* IN COMPOSITION AT THE EQUALLY SPACED GRID */
/*  POINTS TO HCOMP AND DO NOT REPLACE HCOMP WITH U. */
	dcomp = 0.;
	i__2 = egrid_1.ntot;
	for (i__ = 1; i__ <= i__2; ++i__) {
	    splin_1.xtab[i__ - 1] = egrid_1.echi[i__ - 1];
	    splin_1.ytab[i__ - 1] = tridi_1.u[i__ - 1] - ecomp[i__ - 1];
	    dcomp += splin_1.ytab[i__ - 1] * em[i__];
	}
	i__2 = ntab;
	for (i__ = 1; i__ <= i__2; ++i__) {
	    splin_1.xval[i__ - 1] = egrid_1.chi[i__ - 1];
	}
/*  USE YVAL AS DUMMY ARRAY FOR THE NEW RUN OF COMP AT THE ORIGINAL */
/*  POINT GRID. */
	osplin_(splin_1.xval, splin_1.yval, splin_1.xtab, splin_1.ytab, &
		egrid_1.ntot, &ntab);
/* CHECK FOR LOWER CONVECTION ZONE */
	if (lcz[*ibeg] && *ibeg > 1) {
	    for (i__ = *ibeg - 1; i__ >= 1; --i__) {
		if (! lcz[i__]) {
		    i0 = i__ + 1;
		    goto L90;
		}
	    }
	    i0 = 1;
L90:
	    ;
	} else {
	    i0 = *ibeg;
	}
/* CHECK FOR UPPER CONVECTION ZONE. */
	if (lcz[*iend] && *iend < *m) {
	    i__2 = *m;
	    for (i__ = *iend + 1; i__ <= i__2; ++i__) {
		if (! lcz[i__]) {
		    i1 = i__ - 1;
		    goto L97;
		}
	    }
	    i1 = *m;
L97:
	    ;
	}
	dcomp2 = 0.;
/* COMPUTE SUM OF SPECIES MASS */
	sumspec = 0.;
	i__2 = i1;
	for (i__ = i0; i__ <= i__2; ++i__) {
	    sumspec += hs2[i__] * hcomp[id[n - 1] + i__ * 15];
	}
/* UPDATE COMPOSITION ARRAY. */
	sumspec2 = 0.;
	i__2 = ntab;
	for (i__ = 1; i__ <= i__2; ++i__) {
	    j = *ibeg + i__ - 1;
	    hcomp[id[n - 1] + j * 15] += splin_1.yval[i__ - 1];
	    dcomp2 += splin_1.yval[i__ - 1] * hs2[j];
	    sumspec2 += hs2[j] * hcomp[id[n - 1] + j * 15];
	}
/* UPDATE INNER CZ COMPOSITION IF APPLICABLE. */
	if (i0 < *ibeg) {
	    i__2 = i0;
	    for (i__ = *ibeg - 1; i__ >= i__2; --i__) {
		hcomp[id[n - 1] + i__ * 15] = hcomp[id[n - 1] + *ibeg * 15];
		sumspec2 += hs2[i__] * hcomp[id[n - 1] + i__ * 15];
		dcomp2 += splin_1.yval[0] * hs2[i__];
	    }
	}
/* UPDATE OUTER CZ COMPOSITION IF APPLICABLE. */
	if (*iend < i1) {
	    i__2 = i1;
	    for (i__ = *iend + 1; i__ <= i__2; ++i__) {
		hcomp[id[n - 1] + i__ * 15] = hcomp[id[n - 1] + *iend * 15];
		sumspec2 += hs2[i__] * hcomp[id[n - 1] + i__ * 15];
		dcomp2 += splin_1.yval[ntab - 1] * hs2[i__];
	    }
	}
/* CHECK FOR CONSERVATION OF SPECIES */
/*         TEST = ABS(SUMSPEC-SUMSPEC2) */
/*         WRITE(*,911)ID(N),DCOMP,DCOMP2,SUMSPEC */
/* 911     FORMAT(I5,1P3E10.2) */
/*         IF(TEST.GT.1.0D-10*SUMSPEC)THEN */
/*            RATIO = SUMSPEC/SUMSPEC2 */
/*            DO I = I0,I1 */
/*               HCOMP(ID(N),I)=RATIO*HCOMP(ID(N),I) */
/*            END DO */
/*         ENDIF */
    }
/*  ADJUST HE4 FOR CHANGES IN X, Z, AND HE3. */
    if (! (*lok)) {
	i__1 = i1;
	for (i__ = i0; i__ <= i__1; ++i__) {
	    hcomp[i__ * 15 + 2] = 1. - hcomp[i__ * 15 + 1] - hcomp[i__ * 15 + 
		    3] - hcomp[i__ * 15 + 4];
	}
    }
L200:
    return 0;
} /* mixcom_ */

