/* ndifcom.f -- translated by f2c (version 20100827).
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

/* $$$$$$ */
/* Subroutine */ int ndifcom_(doublereal *dt, doublereal *cod2, doublereal *
	ecod2, doublereal *em, doublereal *hd, doublereal *hl, doublereal *hp,
	 doublereal *hr, doublereal *hs, doublereal *hs1, doublereal *hs2, 
	doublereal *hstot, doublereal *hv, integer *ibeg, integer *iend, 
	integer *imax, integer *imin, logical *lcz, logical *lok, integer *m, 
	integer *ntot, doublereal *hcomp, integer *jbeg, integer *jend)
{
    /* System generated locals */
    integer i__1;

    /* Local variables */
    static integer j;
    static logical ldum, ldum2, ltest;
    extern /* Subroutine */ int mixcom_(doublereal *, doublereal *, 
	    doublereal *, doublereal *, integer *, integer *, logical *, 
	    logical *, integer *, doublereal *, integer *, integer *);
    static integer istart;
    extern /* Subroutine */ int mixgrid_(doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, integer *, integer *, 
	    logical *, integer *, doublereal *, doublereal *, logical *);

/*  DIFCOM CALCULATES THE DIFFUSION OF COMPOSITION DUE TO ANGULAR MOMENTUM */
/*  TRANSPORT.  THIS IS DONE BY TRANSFORMING TO AN EQUALLY SPACED GRID IN */
/*  RADIUS, SOLVING A DIFFUSION EQUATION, AND TRANSFORMING BACK. */

/*  INPUT VARIABLES: */
/*  DT : DIFFUSION TIMESTEP(SEC). */
/*  COD2 : DIFFUSION COEFFICIENTS FOR COMPOSITION TRANSPORT AT THE ORIGINAL */
/*         MODEL POINTS. */
/*  ECOD2 : DIFFUSION COEFFICIENTS FOR COMPOSITION TRANSPORT AT THE EQUALLY */
/*          SPACED GRID POINTS. */
/*  EM : MASSES OF THE EQUALLY SPACED GRID POINTS(GM). */
/*     NOTE: FOR CONVECTIVE BOUNDARIES THE MASS OF THE LAST GRID POINT IS */
/*           THE MASS OF THE ENTIRE CONVECTION ZONE. */
/*  HCOMP : ARRAY OF MASS FRACTION OF ALL OF THE SPECIES AT THE ORIGINAL */
/*          MODEL POINTS. */
/*  HS1 : LOCATION IN MASS(UNLOGGED) OF THE ORIGINAL MODEL POINTS. */
/*  HS2 : MASSES OF THE ORIGINAL MODEL POINTS(UNLOGGED). */
/*  HV : RUN OF DIFFUSION VELOCITIES. */
/*  IBEG,IEND :THE FIRST/LAST UNSTABLE POINTS IN THE REGION. */
/*     NOTE: FOR CONVECTIVE BOUNDARIES THESE ARE ONLY THE FIRST CONVECTIVE */
/*           POINTS ADJACENT TO AN UNSTABLE RADIATIVE REGION. */
/*  IMIN : THE INNERMOST RADIATIVE ZONE OUTSIDE OF ZONE 1. */
/*  LCZ : FLAG WHICH TELLS WHICH OF THE ORIGINAL MODEL POINTS ARE */
/*        CONVECTIVE FOR ANGULAR MOMENTUM TRANSPORT PURPOSES(I.E. INCLUDES */
/*        OVERSHOOT REGIONS). LCZ=T IF CONVECTIVE. */
/*  LOK : FLAG SET T WHEN FINAL ITERATION IS BEING PERFORMED. */
/*  M : NUMBER OF MODEL POINTS. */
/*  OUTPUT VARIABLES: */
/*  HCOMP IS UPDATED IN DIFCOM TO GIVE THE NEW RUN OF COMPOSITION AFTER */
/*  ANGULAR MOMENTUM TRANSPORT. */

/*  BEFORE THE LAST ITERATION(LOK=F),ONLY DIFFUSION OF H,HE4,HE3 CALCULATED */
/*  TO CALCULATE CHANGE IN MU GRADIENTS CAUSED BY DIFFUSION. */

/*  WHEN LOK IS T, ONLY DIFFUSION OF SPECIES HEAVIER THAN HE4 IS PERFORMED */
/*  (AS DIFFUSION OF LIGHTER SPECIES HAS ALREADY BEEN DONE). */
/*  THE EQUALLY SPACED GRID POINTS FROM THE LAST UNSTABLE REGION SOLVED */
/*  ARE USED INITIALLY, AND THEN THE PROGRAM CHECKS FOR ADDITIONAL UNSTABLE */
/*  REGIONS INTERIOR TO THAT. */
/* CALL MIXCOM FOR PREVIOUSLY IDENTIFIED UNSTABLE REGION IF THIS IS NOT */
/* THE CONVERGED CALL */
    /* Parameter adjustments */
    hcomp -= 16;
    --lcz;
    --hv;
    --hs2;
    --hs1;
    --hs;
    --hr;
    --hp;
    --hl;
    --hd;
    --em;
    --ecod2;
    --cod2;

    /* Function Body */
    if (! (*lok)) {
	mixcom_(dt, &ecod2[1], &em[1], &hs2[1], ibeg, iend, &lcz[1], lok, m, &
		hcomp[16], jbeg, jend);
    } else {
/* FIND UNSTABLE REGIONS IN ORDER, AND CALL MIXGRID TO SET UP THE */
/* EQUALLY SPACED GRID AND MIXCOM TO MIX THEM IN ORDER */
/*  EACH UNSTABLE REGION IS SOLVED SEPARATELY STARTING HERE. */
/*  LTEST IS SET T IF A NON-ZERO VELOCITY IS ENCOUNTERED. */
/*  IBEG IS THE ZONE BELOW THE FIRST NON-ZERO V;IEND IS THE ZONE ABOVE */
/*  THE LAST NON-ZERO V. */
	ldum = FALSE_;
	istart = *imin;
L60:
	ltest = FALSE_;
	i__1 = *imax;
	for (j = istart; j <= i__1; ++j) {
	    if (hv[j] > 0.) {
		ltest = TRUE_;
		if (! ldum) {
/*  START OF UNSTABLE REGION */
		    ldum = TRUE_;
		    *ibeg = j - 1;
		}
	    } else if (ldum) {
/*  END OF UNSTABLE REGION */
		*iend = j - 1;
		ldum = FALSE_;
		istart = j + 1;
		goto L80;
	    }
	}
/*  IF THE LAST INTERFACE IS UNSTABLE (NON-ZERO V) ENSURE THAT IEND IS SET */
/*  PROPERLY. */
	if (ldum) {
	    *iend = *imax;
	}
	istart = *imax + 1;
L80:
/*  IF NO NON-ZERO V'S ENCOUNTERED, EXIT. */
	if (! ltest) {
	    goto L90;
	}
/*  TRANSFORM TO EQUAL GRID SPACING IN R FOR THE REGION. */
	mixgrid_(&cod2[1], &hd[1], &hl[1], &hp[1], &hr[1], &hs[1], &hs1[1], &
		hs2[1], hstot, ibeg, iend, &lcz[1], m, &ecod2[1], &em[1], &
		ldum2);
/*  LDUM2=T IF TWO ZONES IN UNSTABLE REGION; */
/*  SKIP IF THIS OCCURS. */
	if (ldum2) {
	    if (istart <= *imax) {
		goto L60;
	    } else {
		goto L90;
	    }
	}
/*  PERFORM COMPOSITION DIFFUSION. */
/*  UNTIL THE FINAL ITERATION, ONLY COMPOSITION DIFFUSION OF SPECIES WHICH */
/*  AFFECT GRADIENTS IN MEAN MOLECULAR WEIGHT IS COMPUTED (H,HE3,HE4). */
/*  ON THE FINAL ITERATION, DIFFUSION OF ALL SPECIES IS PERFORMED. */
	mixcom_(dt, &ecod2[1], &em[1], &hs2[1], ibeg, iend, &lcz[1], lok, m, &
		hcomp[16], jbeg, jend);
/*  RETURN FOR NEXT REGION IF APPLICABLE */
	if (istart <= *imax) {
	    goto L60;
	}
L90:
	;
    }
    return 0;
} /* ndifcom_ */

