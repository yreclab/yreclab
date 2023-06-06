/* grsett.f -- translated by f2c (version 20100827).
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
    doublereal ecod1z[5000], ecod1z_h__[5000], ecod2z_h__[5000], eqcod1z_h__[
	    5000], eqcod2z_h__[5000], ez[5000], ez_h__[5000];
} gravez_;

#define gravez_1 gravez_

struct {
    doublereal cln, clni, c4pi, c4pil, c4pi3l, cc13, cc23, cpi;
} const1_;

#define const1_1 const1_

struct {
    integer ilast, idebug, itrack, ishort, imilne, imodpt, istor, iowr;
} luout_;

#define luout_1 luout_

/* Table of constant values */

static integer c__1 = 1;

/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */
/* GRESETT */
/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */
/* Subroutine */ int grsett_(doublereal *dt, doublereal *hcomp, doublereal *
	hqpr, doublereal *hr, doublereal *hd, doublereal *hs1, doublereal *ht,
	 logical *lc, integer *m, doublereal *stot)
{
    /* Format strings */
    static char fmt_90[] = "(1x,\002ITERATION \002,i3,\002 DXMAX \002,1pe10."
	    "2,\002 IMAX \002,i4)";
    static char fmt_110[] = "(1x,\002GRSETT FAILED TO CONVERGE TO WITHIN "
	    "\002,1pe9.3,\002 IN \002,i3,\002ITERATIONS\002/1x,\002LAST ITERA"
	    "TION CHANGE IN X \002,1pe9.3,\002 IN EQUALLY SPACED SHELL \002,i"
	    "5)";

    /* System generated locals */
    integer i__1, i__2;

    /* Builtin functions */
    integer s_wsfe(cilist *), do_fio(integer *, char *, ftnlen), e_wsfe(void);

    /* Local variables */
    static doublereal ex_prime__[5000], eqcod1x_h__[5000], eqcod2x_h__[5000], 
	    a[5000], b[5000], c__[5000];
    static integer i__;
    static doublereal em[5000], dr, er[5000], ex[5000], dx;
    extern /* Subroutine */ int tridiag_gs__(doublereal *, doublereal *, 
	    doublereal *, doublereal *, integer *, doublereal *);
    static doublereal zz1, zz2, fac, hru[5000], htu[5000];
    static integer npt;
    static doublereal cod1[5000], cod2[5000], em_h__[5000];
    static integer iend;
    static doublereal ex_h__[5000];
    extern /* Subroutine */ int lax_wendrof1__(doublereal *, doublereal *, 
	    doublereal *, integer *, doublereal *, doublereal *), 
	    lax_wendrof2__(doublereal *, doublereal *, doublereal *, 
	    doublereal *, integer *, doublereal *);
    static doublereal ex_p__[5000], ez_p__[5000];
    static integer imax, iter;
    static doublereal ecod1[5000], alpha[5000];
    extern /* Subroutine */ int setup_grsett__(doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, logical *,
	     integer *, doublereal *, doublereal *, doublereal *, doublereal *
	    , doublereal *, doublereal *, integer *, integer *, logical *, 
	    doublereal *, doublereal *);
    static doublereal dxmax, qcod1x[5000], qcod2x[5000];
    static integer ibegin;
    static logical lallcz;
    extern /* Subroutine */ int get_imp_diffco__(doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, integer *);
    static doublereal ecod1_h__[5000], ecod2_h__[5000];
    extern /* Subroutine */ int model_to_equal__(doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, integer *, integer *, integer *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, integer *)
	    , equal_to_model__(doublereal *, doublereal *, doublereal *, 
	    integer *, integer *, integer *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, integer *, doublereal *)
	    ;
    static doublereal ex_orig__[5000], ez_orig__[5000];

    /* Fortran I/O blocks */
    static cilist io___37 = { 0, 0, 0, fmt_90, 0 };
    static cilist io___38 = { 0, 0, 0, fmt_110, 0 };
    static cilist io___39 = { 0, 0, 0, fmt_110, 0 };


/* MHP 3/94 ADDED METAL DIFFUSION */
/*  GRSETT SOLVES FOR THE GRAVITATIONAL SETTLING OF HELIUM USING THE */
/*  FORMULISM OF BAHCALL AND LOEB 1989.  SETTLING OF METALS WILL BE ADDED */
/*  LATER. */
/*  GRSETT PERFORMS THE FOLLOWING SERIES OF OPERATIONS : */
/*  1)  TRANSFORMS TO AN EQUALLY SPACED GRID IN RADIUS (AND MANIPULATES */
/*  THE MODEL VARIABLES INTO BAHCALL AND LOEB UNITS). */

/*  THE DIFFUSION EQUATION HAS TWO TERMS : ONE THAT DEPENDS ON DLNP/DR*DX/DR */
/*  AND ONE THAT DEPENDS ON D^2X/DR^2. THE DIFFUSION COEFFICIENTS ARE */
/*  THEMSELVES FUNCTIONS OF BOTH THE THERMAL STRUCTURE AND X. */
/*  GRSETT SOLVES THIS DIFFUSION EQUATION IN TWO STEPS : */
/*  2) THE FIRST TERM IS SOLVED EXPLICITLY USING THE TWO-STEP */
/*  LAX-WENDROFF SCHEME (NUMERICAL RECIPES, PRESS ET AL. 1986, */
/*  CAMBRIDGE UNIVERSITY PRESS,P.633) */
/*  3) THE SECOND TERM IS SOLVED IMPLICITLY, USING THE MODIFIED RUN OF */
/*  ABUNDANCE FOUND IN STEP 2) AS THE 'INITIAL' RUN OF ABUNDANCE. */
/*  THE IMPLICIT SCHEME ITERATES ON THE DIFFUSION COEFFICIENTS UNTIL */
/*  THE SOLUTION CONVERGES TO WITHIN THE USER-SPECIFIED TOLERANCE GRTOL. */

/*  4) GRSETT THEN UPDATES THE ABUNDANCE ARRAY AND EXITS. */

/*  INPUT VARIABLES : */

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

/*  NEW RUN OF HCOMP(1,...) AND HCOMP(2,...). */

/*  CONVERT MODEL QUANTITIES TO BAHCALL AND LOEB UNITS; LOCATE */
/*  BOUNDARIES OF CONVECTIVE CORE AND ENVELOPE IF APPLICABLE. */
/*  COMPUTE THE DIFFUSION COEFFICIENTS (COD1 AND COD2) AND THEIR */
/*  DERIVATIVES WITH RESPECT TO X (QCOD1X AND QCOD2X). */

    /* Parameter adjustments */
    --lc;
    --ht;
    --hs1;
    --hd;
    --hr;
    --hqpr;
    hcomp -= 16;

    /* Function Body */
    setup_grsett__(dt, &hqpr[1], &hr[1], &hd[1], &hs1[1], &ht[1], &lc[1], m, 
	    stot, cod1, cod2, &hcomp[16], hru, htu, &ibegin, &iend, &lallcz, 
	    qcod1x, qcod2x);

/* SKIP SETTLING FOR FULLY CONVECTIVE MODELS. */
    if (lallcz) {
	return 0;
    }
/*  TRANSFORM TO AN EQUALLY SPACED GRID IN RADIUS. */
/*  NOTE : PREFIX E ALONE=VARIABLE AT EQUALLY SPACED GRID POINTS. */
/*         PREFIX E + SUFFIX _H= VARIABLE AT MIDPOINT BETWEEN EQUALLY */
/*         SPACED GRID POINTS.(BOTH ARE NEEDED FOR THE DIFFUSION TECHNIQUE). */

    model_to_equal__(cod1, cod2, &hcomp[16], &hqpr[1], hru, &hs1[1], htu, &
	    ibegin, &iend, m, qcod1x, qcod2x, &dr, ecod1, ecod1_h__, 
	    ecod2_h__, em, em_h__, eqcod1x_h__, eqcod2x_h__, er, ex, ex_h__, &
	    npt);

/* STORE ORIGINAL RUN OF HYDROGEN MASS FRACTION IN VECTOR EX_ORIG. */
/* THE CHANGE IN HYDROGEN (EX - EX_ORIG) IS INTERPOLATED BACK TO THE */
/* ORIGINAL GRID AT THE END OF THE ROUTINE; THE CHANGE IN ABUNDANCE */
/* (RATHER THAN THE NEW RUN OF ABUNDANCE) IS USED TO MINIMIZE ERRORS */
/* ARISING FROM THE INTERPOLATION. */
    i__1 = npt;
    for (i__ = 1; i__ <= i__1; ++i__) {
	ex_orig__[i__ - 1] = ex[i__ - 1];
/* L5: */
    }
/* MHP 3/94 METAL DIFFUSION */
    if (gravs3_1.ldifz) {
	i__1 = npt;
	for (i__ = 1; i__ <= i__1; ++i__) {
	    ez_orig__[i__ - 1] = gravez_1.ez[i__ - 1];
	}
    }
/*  FIRST STEP OF TWO STEP LAX-WENDROFF METHOD.   COMPUTE NEW X'S AT ZONE */
/*  MIDPOINTS USING THE LAX SCHEME : */
/* X(N+1/2,J+1/2)=1/2(X(N,J+1/2)-1/2(DT/DR)(COD1(N,J+1)-COD1(N,J)) */
/* WHERE N IS THE TIME VARIABLE, J IS THE SPATIAL ONE, AND COD1 IS THE */
/* DIFFUSION COEFFICIENT. */

/* SOLVE FOR NEW ABUNDANCES AT THE ZONE MIDPOINTS USING THE ABOVE D.C. */

    lax_wendrof1__(dt, ecod1, em, &npt, stot, ex_h__);

/* NOW COMPUTE NEW DIFFUSION COEFFICIENTS AT THE ZONE MIDPOINTS USING THE */
/* PROVISIONAL SOLUTION FOR X AT THE ZONE MIDPOINTS. */

/* GET NEW DIFFUSION COEFFICIENTS. */
/* ALSO DEFINE VECTOR EX_P, WHICH IS THE HYDROGEN ABUNDANCE AT THE */
/* END OF THE PREVIOUS ITERATION. */

    i__1 = npt - 1;
    for (i__ = 1; i__ <= i__1; ++i__) {
	ecod1_h__[i__ - 1] += ex_h__[i__ - 1] * eqcod1x_h__[i__ - 1];
	ex_p__[i__ - 1] = ex_orig__[i__ - 1];
/* L10: */
    }
    ex_p__[npt - 1] = ex_orig__[npt - 1];
/* MHP 3/94 METAL DIFFUSION */
    if (gravs3_1.ldifz) {
	i__1 = npt - 1;
	for (i__ = 1; i__ <= i__1; ++i__) {
	    gravez_1.ecod1z_h__[i__ - 1] += gravez_1.ez_h__[i__ - 1] * 
		    gravez_1.eqcod1z_h__[i__ - 1];
	    ez_p__[i__ - 1] = ez_orig__[i__ - 1];
	}
	ez_p__[npt - 1] = ez_orig__[npt - 1];
    }

/* USING THE NEW COEFFICIENTS, SOLVE FOR THE NEW RUN OF HYDROGEN ABUNDANCES. */
/* NOTE : THE SR ACTUALLY RETURNS THE *CHANGE* IN THE ABUNDANCE AS A FUNCTION */
/* OF RADIUS, WHICH IS APPLIED TO THE ORIGINAL RUN OF X, RATHER THAN */
/* COMPUTING A NEW RUN OF ABUNDANCE AND TRANSFORMING IT BACK.  THIS IS DONE */
/* TO MINIMIZE ERRORS FROM THE INTERPOLATION. */

    lax_wendrof2__(dt, ecod1_h__, em_h__, ex, &npt, stot);

/*  NOW IMPLICITLY SOLVE FOR THE SECOND TERM (INVOLVING THE SECOND */
/*  DERIVATIVE OF THE COMPOSITION GRADIENT). */
/*  EX_PRIME IS THE HYDROGEN ABUNDANCE ONE WOULD HAVE IN THE ABSENCE OF */
/*  THE SECOND TERM IN THE DIFFUSION EQUATION. */
    i__1 = npt;
    for (i__ = 1; i__ <= i__1; ++i__) {
	ex_prime__[i__ - 1] = ex[i__ - 1];
/* L15: */
    }
/*  ALPHA IS THE NUMERICAL FACTOR IN FRONT OF THE DIFFUSION COEFFICIENTS. */
    fac = const1_1.c4pi * *dt / dr;
    alpha[0] = fac / em_h__[0];
    i__1 = npt - 1;
    for (i__ = 2; i__ <= i__1; ++i__) {
	alpha[i__ - 1] = fac / (em_h__[i__ - 1] - em_h__[i__ - 2]);
/* L20: */
    }
    alpha[npt - 1] = fac / (*stot - em_h__[npt - 2]);
/*  START ITERATION LOOP FOR THE NEW RUN OF HYDROGEN. */
    i__1 = gravst_1.niter_gs__;
    for (iter = 1; iter <= i__1; ++iter) {
/*  FIND CHANGE IN X AT THE ZONE MIDPOINTS, GIVEN CHANGE IN X AT */
/*  THE ZONE CENTERS. */
	i__2 = npt;
	for (i__ = 2; i__ <= i__2; ++i__) {
	    ex_h__[i__ - 1] = (ex[i__ - 1] + ex[i__ - 2] - ex_p__[i__ - 1] - 
		    ex_p__[i__ - 2]) * .5;
/* L30: */
	}
/*  STORE CURRENT RUN OF HYDROGEN ABUNDANCES IN VECTOR EX_P. THE ITERATION */
/*  LOOP IS COMPLETED ONCE EX - EX_P IS EVERYWHERE LESS THAN THE TOLERANCE */
/*  GRTOL. */
	i__2 = npt;
	for (i__ = 1; i__ <= i__2; ++i__) {
	    ex_p__[i__ - 1] = ex[i__ - 1];
/* L40: */
	}
/*  GET NEW DIFFUSION COEFFICIENTS, TAKING INTO ACCOUNT THE CHANGE IN X */
/*  FROM THE PREVIOUS ITERATION. */

	get_imp_diffco__(alpha, ecod2_h__, ex_h__, eqcod2x_h__, a, b, c__, &
		npt);

/*  SOLVE THE TRIDIAGONAL MATRIX SYSTEM FOR THE NEW RUN OF X. */

	tridiag_gs__(a, b, c__, ex_prime__, &npt, ex);

/*  CHECK TO SEE IF THE CORRECTIONS TO THE HYDROGEN ABUNDANCE ARE SMALL */
/*  ENOUGH TO EXIT. */
	dxmax = 0.;
	imax = 0;
	i__2 = npt;
	for (i__ = 1; i__ <= i__2; ++i__) {
	    dx = ex[i__ - 1] - ex_p__[i__ - 1];
	    if (dx > dxmax) {
		dxmax = dx;
		imax = i__;
	    }
/* L50: */
	}
/*         WRITE(IOWR,90)ITER,DXMAX,IMAX */
	io___37.ciunit = luout_1.ishort;
	s_wsfe(&io___37);
	do_fio(&c__1, (char *)&iter, (ftnlen)sizeof(integer));
	do_fio(&c__1, (char *)&dxmax, (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&imax, (ftnlen)sizeof(integer));
	e_wsfe();
/*  EXIT ITERATION LOOP IF SYSTEM HAS CONVERGED. */
	if (dxmax < gravst_1.grtol) {
	    goto L120;
	}
/* L100: */
    }
    io___38.ciunit = luout_1.iowr;
    s_wsfe(&io___38);
    do_fio(&c__1, (char *)&gravst_1.grtol, (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&gravst_1.niter_gs__, (ftnlen)sizeof(integer));
    do_fio(&c__1, (char *)&dxmax, (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&imax, (ftnlen)sizeof(integer));
    e_wsfe();
    io___39.ciunit = luout_1.ishort;
    s_wsfe(&io___39);
    do_fio(&c__1, (char *)&gravst_1.grtol, (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&gravst_1.niter_gs__, (ftnlen)sizeof(integer));
    do_fio(&c__1, (char *)&dxmax, (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&imax, (ftnlen)sizeof(integer));
    e_wsfe();
L120:
/*  FIND RUN OF CHANGES IN X. */
    i__1 = npt;
    for (i__ = 1; i__ <= i__1; ++i__) {
	ex[i__ - 1] -= ex_orig__[i__ - 1];
/* L130: */
    }
/* MHP 3/94 ADDED METAL DIFFUSION */
    if (gravs3_1.ldifz) {
	zz1 = gravez_1.ez[0] - ez_orig__[0];
	zz2 = gravez_1.ez[npt - 1] - ez_orig__[npt - 1];
	i__1 = npt;
	for (i__ = 1; i__ <= i__1; ++i__) {
	    gravez_1.ez[i__ - 1] -= ez_orig__[i__ - 1];
	}
    }
/* TRANSFORM BACK TO ORIGINAL MODEL GRID; UPDATE HELIUM ARRAY USING */
/* X+Y+Z=1.  PRINT DIAGNOSTIC OUTPUT. */
    equal_to_model__(dt, er, ex, &ibegin, &iend, &npt, &hcomp[16], &hqpr[1], 
	    hru, &hs1[1], htu, m, stot);
    return 0;
} /* grsett_ */

