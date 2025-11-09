/* microdiff.f -- translated by f2c (version 20061008).
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
    doublereal grtol;
    integer ilambda, niter_gs__;
    logical ldify;
} gravst_;

#define gravst_1 gravst_

struct {
    doublereal fgry, fgrz;
    logical lthoul, ldifz;
} gravs3_;

#define gravs3_1 gravs3_

struct {
    logical lnewdif, ldifli;
} gravs4_;

#define gravs4_1 gravs4_

struct {
    doublereal cln, clni, c4pi, c4pil, c4pi3l, cc13, cc23, cpi;
} const1_;

#define const1_1 const1_

struct {
    integer ilast, idebug, itrack, ishort, imilne, imodpt, istor, iowr;
} luout_;

#define luout_1 luout_

/* Table of constant values */

static integer c__3 = 3;

/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */
/* MICRODIFF */
/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */
/* Subroutine */ int microdiff_(doublereal *dt, doublereal *hcomp, doublereal 
	*hqpr, doublereal *hr, doublereal *hd, doublereal *hs1, doublereal *
	ht, logical *lc, integer *m, doublereal *stot)
{
    /* Initialized data */

    static integer cslight[3] = { 13,14,15 };
    static doublereal aslight[3] = { 6.015,7.016,9.012 };
    static doublereal zslight[3] = { 3.,3.,4. };

    /* System generated locals */
    integer i__1;

    /* Local variables */
    static integer i__, j;
    static doublereal em[5000];
    static integer ii;
    static doublereal dr, er[5000], ex[5000], ey[5000], ez[5000], eli[15000]	
	    /* was [3][5000] */, hru[5000], htu[5000];
    static integer npt;
    static doublereal em_h__[5000], eden[5000], er_h__[5000];
    static integer iend;
    static doublereal thea, ex_h__[5000], ey_h__[5000], oden[5000], ez_h__[
	    5000], etem[5000], otem[5000], thez, eli_h__[15000]	/* was [3][
	    5000] */, edelr[5000], espec[15000]	/* was [3][5000] */, edelx[
	    5000], edelz[5000], edxdr[5000], ehqpr[5000];
    extern /* Subroutine */ int microdiff_mte__(integer *, integer *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, integer *,
	     integer *, integer *, doublereal *, integer *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *), microdiff_etm__(doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, integer *, integer *, 
	    integer *, doublereal *, doublereal *, doublereal *, doublereal *,
	     doublereal *, integer *, doublereal *, integer *, integer *), 
	    microdiff_run__(doublereal *, doublereal *, doublereal *, integer 
	    *, doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, integer *);
    static doublereal eden_h__[5000];
    static integer ibegin;
    static doublereal edelli[15000]	/* was [3][5000] */, etem_h__[5000];
    static logical lallcz;
    static doublereal edelr_h__[5000], espec_h__[15000]	/* was [3][5000] */, 
	    edxdr_h__[5000], ehqpr_h__[5000];
    extern /* Subroutine */ int microdiff_setup__(doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, logical *,
	     integer *, doublereal *, doublereal *, doublereal *, doublereal *
	    , integer *, integer *, logical *, doublereal *, doublereal *);

/* SET NLIGHT TO THE NUMBER OF LIGHT ELEMENTS TO BE DIFFUSED. */
/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */
/* MHP 3/94 ADDED METAL DIFFUSION */
/* KC 2025-05-30 fixed -Wconversion */
/*      *          OTEM(JSON),CSLIGHT(NLIGHT),ASLIGHT(NLIGHT),ZSLIGHT(NLIGHT) */

/*     SET UP VECTORS FOR LIGHT ELEMENT DIFFUSION. THE LENGTH */
/*     OF EACH SHOULD EQUAL NLIGHT. */
    /* Parameter adjustments */
    --lc;
    --ht;
    --hs1;
    --hd;
    --hr;
    --hqpr;
    hcomp -= 16;

    /* Function Body */
/*  GARRETT SOMERS - 05/2015 */
/*  MICRODIFF IS AN UPDATED HELIUM, METAL, AND LIGHT ELEMENT DIFFUSION */
/*  ROUTINE. MUCH IS ADAPTED FROM GRSETT.F, WHICH IS RETAINED FOR BACKWARDS */
/*  COMPATABILITY. FOLLOWS THE FORMULISM OF BAHCALL AND LOEB 1989. */

/*  MICRODIFF PERFORMS THE FOLLOWING OPERATIONS: */
/*  1) TRANSFORMS PYHSICAL VARIABLES TO AN EQUALLY SPACED GRID IN RADIUS */
/*     (AND MANIPULATES THE MODEL VARIABLES INTO BAHCALL AND LOEB UNITS). */
/*  2) CALCULATES DIFFUSION COEFFICIENTS ALONG THE GRID FOR Y, Z, AND FOR */
/*     LIGHT ELEMENTS. THE DIFFUSION EQUATION HAS TWO TERMS : ONE THAT DEPENDS */
/*     ON DLNP/DR*DX/DR AND ONE THAT DEPENDS ON D^2X/DR^2. THE DIFFUSION */
/*     COEFFICIENTS ARE THEMSELVES FUNCTIONS OF BOTH THE THERMAL STRUCTURE, */
/*     ABUNDANCE, AND THE HYDROGEN GRADIENT. */
/*  3) SOLVES THIS DIFFUSION EQUATION IN TWO STEPS. THE FIRST TERM IS SOLVED */
/*     EXPLICITLY USING THE TWO-STEP LAX-WENDROFF SCHEME (NUMERICAL RECIPES, */
/*     PRESS ET AL. 1986,CAMBRIDGE UNIVERSITY PRESS,P.633). DIFFUSION */
/*     COEFFICIENTS ARE RECALCUALTED AT THE GRID MID-POINTS IN THE PROCESS. */
/*  4) THE SECOND TERM IS SOLVED IMPLICITLY, USING THE MODIFIED RUN OF */
/*     ABUNDANCE FOUND IN STEP 3) AS THE 'INITIAL' RUN OF ABUNDANCE. */
/*     THE IMPLICIT SCHEME ITERATES ON THE DIFFUSION COEFFICIENTS UNTIL */
/*     THE SOLUTION CONVERGES TO WITHIN THE USER-SPECIFIED TOLERANCE GRTOL. */
/*  5) UPDATES ABUNDANCE ARRAYS, TRANSFORMS BACK TO THE MODEL GRID, AND EXITS */

/*  DT - TIMESTEP (SEC) */
/*  HCOMP - RUN OF MASS FRACTIONS OF SPECIES.HCOMP(1,..)=X,HCOMP(2,...)=Y */
/*          HCOMP(3,...)=Z */
/*  HQPR - DLNP/DR */
/*  HR - LOG RADIUS (CM) */
/*  HS1 - MASS (GM), UNLOGGED */
/*  HT - LOG TEMPERATURE (K) */
/*  LC - FLAG T/F FOR CONVECTION */
/*  M - NUMBER OF MODEL POINTS */
/*  [COMMON] SDEL(2,...) - DEL (=DLNT/DLNP) */

/*  OUTPUT VARIABLES : */

/*  NEW RUN OF HCOMP(1-N,...). */

/*  CONVERT MODEL QUANTITIES TO BAHCALL AND LOEB UNITS; LOCATE */
/*  BOUNDARIES OF CONVECTIVE CORE AND ENVELOPE IF APPLICABLE; */
/*  COLLECT PHYSICAL VARIABLES FOR DIFFCO CALCULATION. */

    microdiff_setup__(dt, &hqpr[1], &hr[1], &hd[1], &hs1[1], &ht[1], &lc[1], 
	    m, stot, &hcomp[16], hru, htu, &ibegin, &iend, &lallcz, oden, 
	    otem);

/* SKIP SETTLING FOR FULLY CONVECTIVE MODELS. */
    if (lallcz) {
	return 0;
    }
/*  TRANSFORM TO AN EQUALLY SPACED GRID IN RADIUS. */
/*  NOTE : PREFIX E ALONE=VARIABLE AT EQUALLY SPACED GRID POINTS. */
/*         PREFIX E + SUFFIX _H= VARIABLE AT MIDPOINT BETWEEN EQUALLY */
/*         SPACED GRID POINTS.(BOTH ARE NEEDED FOR THE DIFFUSION TECHNIQUE). */

/*       CALL MICRODIFF_MTE(NLIGHT,CSLIGHT,HCOMP,HQPR,HRU,HS1,HTU,IBEGIN, */
/*      *               IEND,M,DR,NPT,LC,ODEN,OTEM,EM,ER,EDEN,ETEM,EHQPR,EDELR,  ! KC 2025-05-31 */
    microdiff_mte__(&c__3, cslight, &hcomp[16], &hqpr[1], hru, &hs1[1], &
	    ibegin, &iend, m, &dr, &npt, oden, otem, em, er, eden, etem, 
	    ehqpr, edelr, ex, ey, ez, eli, em_h__, er_h__, eden_h__, etem_h__,
	     ehqpr_h__, edelr_h__, ex_h__, ey_h__, ez_h__, eli_h__);

/*  PARTIALLY CONSTRUCT THE VECTORS ESPEC AND ESPEC_H, WHICH ARE THE */
/*  THREE SPECIES USED IN THE THOUL CALCULATION. 1=X, 2=Y, 3=METAL. */
    i__1 = npt - 1;
    for (i__ = 1; i__ <= i__1; ++i__) {
	espec[i__ * 3 - 3] = ex[i__ - 1];
	espec[i__ * 3 - 2] = ey[i__ - 1];
	espec_h__[i__ * 3 - 3] = ex_h__[i__ - 1];
	espec_h__[i__ * 3 - 2] = ey_h__[i__ - 1];
    }
    espec[npt * 3 - 3] = ex[npt - 1];
    espec[npt * 3 - 2] = ey[npt - 1];

/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */

/*  WITH THE EQUAL GRID CALCULATED, RUN THE DIFFUSION ROUTINE FOR EACH */
/*  DESIRED ELEMENT. PASS IN EQUAL GRID AND THREE PARAMETERS: */
/*     J = THOUL COLUMN OF DIFFUSED SPECIES (1 FOR X, 3 OTHERWISE) */
/*     THEA = ATOMIC WEIGHT OF DIFFUSED SPECIES */
/*     THEZ = ATOMIC CHARGE OF DIFFUSED SPECIES */
/*  IN THE CASE OF HYDROGEN DIFFUSION, PASS IN THEA/THEZ FOR IRON SINCE */
/*  THESE VALUES ARE USED FOR THE METAL ABUNDANCE IN THOUL. */

/*     DIFFUSE HYDROGEN. */
    if (gravst_1.ldify) {
	j = 1;
	thea = 55.86;
	thez = 26.;
/*        SET ESPEC(3,*) TO THE HEAVY METAL ABUNDANCE. */
	i__1 = npt - 1;
	for (i__ = 1; i__ <= i__1; ++i__) {
	    espec[i__ * 3 - 1] = ez[i__ - 1];
	    espec_h__[i__ * 3 - 1] = ez_h__[i__ - 1];
	}
	espec[npt * 3 - 1] = ez[npt - 1];
/*        PASS THE EVEN GRID INTO MICRODIFF_RUN TO PERFORM THE DIFFUSION. */
/*          CALL MICRODIFF_RUN(NLIGHT,CSLIGHT,DR,DT,STOT,NPT,EM,ER,EDEN,ETEM,  ! KC 2025-05-31 */
	microdiff_run__(&dr, dt, stot, &npt, em, er, eden, etem, ehqpr, edelr,
		 espec, edxdr, em_h__, er_h__, eden_h__, etem_h__, ehqpr_h__, 
		edelr_h__, espec_h__, edxdr_h__, &thea, &thez, &j);
/*        STORE THE RUN OF CHANGES TO HYDROGEN */
	i__1 = npt;
	for (i__ = 1; i__ <= i__1; ++i__) {
	    edelx[i__ - 1] = espec[i__ * 3 - 3];
	}
/*        RESTORE THE ORIGINAL ESPEC HYDROGEN VECTORS. */
	i__1 = npt - 1;
	for (i__ = 1; i__ <= i__1; ++i__) {
	    espec[i__ * 3 - 3] = ex[i__ - 1];
	    espec_h__[i__ * 3 - 3] = ex_h__[i__ - 1];
	}
	espec[npt * 3 - 3] = ex[npt - 1];
    }

/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */

/*     DIFFUSE HEAVY METALS. */
    if (gravs3_1.ldifz) {
	j = 3;
	thea = 55.86;
	thez = 26.;
/*        SET ESPEC(3,*) TO THE HEAVY METAL ABUNDANCE. */
	i__1 = npt - 1;
	for (i__ = 1; i__ <= i__1; ++i__) {
	    espec[i__ * 3 - 1] = ez[i__ - 1];
	    espec_h__[i__ * 3 - 1] = ez_h__[i__ - 1];
	}
	espec[npt * 3 - 1] = ez[npt - 1];
/*        PASS THE EVEN GRID INTO MICRODIFF_RUN TO PERFORM THE DIFFUSION. */
/*          CALL MICRODIFF_RUN(NLIGHT,CSLIGHT,DR,DT,STOT,NPT,EM,ER,EDEN,ETEM,  ! KC 2025-05-31 */
	microdiff_run__(&dr, dt, stot, &npt, em, er, eden, etem, ehqpr, edelr,
		 espec, edxdr, em_h__, er_h__, eden_h__, etem_h__, ehqpr_h__, 
		edelr_h__, espec_h__, edxdr_h__, &thea, &thez, &j);
/*        STORE THE RUN OF CHANGES TO HEAVY METALS */
	i__1 = npt;
	for (i__ = 1; i__ <= i__1; ++i__) {
	    edelz[i__ - 1] = espec[i__ * 3 - 1];
	}
/*        THE ORIGINAL HEAVY VECTOR DOESN'T NEED RESTORATION, SINCE IT WILL */
/*        BE OVERWRITTEN BELOW. */
    }

/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */

/*     DIFFUSE LIGHT ELEMENTS. */
    if (gravs4_1.ldifli) {
/*        ITERATE OVER THE DIFFUSION ROUTINES FOR EACH LIGHT ELEMENT. */
	j = 3;
	for (ii = 1; ii <= 3; ++ii) {
	    thea = aslight[ii - 1];
	    thez = zslight[ii - 1];
/*           SET ESPEC(3,*) TO THE LIGHT ELEMENT ABUNDANCE. */
	    i__1 = npt - 1;
	    for (i__ = 1; i__ <= i__1; ++i__) {
		espec[i__ * 3 - 1] = eli[ii + i__ * 3 - 4];
		espec_h__[i__ * 3 - 1] = eli_h__[ii + i__ * 3 - 4];
	    }
	    espec[i__ * 3 - 1] = eli[ii + npt * 3 - 4];
/*           PASS THE EVEN GRID INTO MICRODIFF_RUN TO PERFORM THE DIFFUSION. */
/*             CALL MICRODIFF_RUN(NLIGHT,CSLIGHT,DR,DT,STOT,NPT,EM,ER,EDEN,ETEM,  ! KC 2025-05-31 */
	    microdiff_run__(&dr, dt, stot, &npt, em, er, eden, etem, ehqpr, 
		    edelr, espec, edxdr, em_h__, er_h__, eden_h__, etem_h__, 
		    ehqpr_h__, edelr_h__, espec_h__, edxdr_h__, &thea, &thez, 
		    &j);
/*           STORE THE NEW RUN OF LIGHT METALS */
	    i__1 = npt;
	    for (i__ = 1; i__ <= i__1; ++i__) {
		edelli[ii + i__ * 3 - 4] = espec[i__ * 3 - 1];
	    }
	}
    }

/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */
/* TRANSFORM BACK TO ORIGINAL MODEL GRID; UPDATE HELIUM ARRAY USING */
/* X+Y+Z=1.  PRINT DIAGNOSTIC OUTPUT. */

    microdiff_etm__(dt, er, edelx, edelz, edelli, &ibegin, &iend, &npt, &
	    hcomp[16], &hqpr[1], hru, &hs1[1], htu, m, stot, &c__3, cslight);
    return 0;
} /* microdiff_ */

