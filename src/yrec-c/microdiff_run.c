/* microdiff_run.f -- translated by f2c (version 20061008).
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
    doublereal dage;
} theage_;

#define theage_1 theage_

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

/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */
/* MICRODIFF_RUN */
/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */
/*       SUBROUTINE MICRODIFF_RUN(NLIGHT,CSLIGHT,DR,DT,STOT,NPT,EM,ER,EDEN,ETEM,  ! KC 2025-05-31 */
/* Subroutine */ int microdiff_run__(doublereal *dr, doublereal *dt, 
	doublereal *stot, integer *npt, doublereal *em, doublereal *er, 
	doublereal *eden, doublereal *etem, doublereal *ehqpr, doublereal *
	edelr, doublereal *espec, doublereal *edxdr, doublereal *em_h__, 
	doublereal *er_h__, doublereal *eden_h__, doublereal *etem_h__, 
	doublereal *ehqpr_h__, doublereal *edelr_h__, doublereal *espec_h__, 
	doublereal *edxdr_h__, doublereal *thea, doublereal *thez, integer *j)
{
    /* Format strings */
    static char fmt_90[] = "(1x,\002ITERATION \002,i3,\002 DXMAX \002,1pe10."
	    "2,\002 IMAX \002,i4)";
    static char fmt_110[] = "(1x,\002MICRODIFF FAILED TO CONVERGE TO WITHIN"
	    " \002,1pe9.3,\002 IN \002,i3,\002ITERATIONS\002/1x,\002LAST ITER"
	    "ATION CHANGE IN D \002,1pe9.3,\002 IN EQUALLY SPACED SHELL \002,"
	    "i5)";

    /* System generated locals */
    integer i__1, i__2;

    /* Builtin functions */
    integer s_wsfe(cilist *), do_fio(integer *, char *, ftnlen), e_wsfe(void);

    /* Local variables */
    static doublereal ed_prime__[5000], eqcod2x_h__[5000], a[5000], b[5000], 
	    c__[5000];
    static integer i__;
    static doublereal ed_orig_h__[5000], ed[5000], dx;
    extern /* Subroutine */ int tridiag_gs__(doublereal *, doublereal *, 
	    doublereal *, doublereal *, integer *, doublereal *);
    static doublereal fac;
    static integer npt2;
    static doublereal ed_h__[5000], ed_p__[5000];
    extern /* Subroutine */ int lax_wendrof1__(doublereal *, doublereal *, 
	    doublereal *, integer *, doublereal *, doublereal *, logical *), 
	    lax_wendrof2__(doublereal *, doublereal *, doublereal *, 
	    doublereal *, integer *, doublereal *, logical *);
    static integer imax, iter;
    static doublereal ecod1[5000], ecod2[5000], alpha[5000];
    static logical ldoli;
    static doublereal dxmax;
    extern /* Subroutine */ int microdiff_cod__(integer *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, integer *), get_imp_diffco__(
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, integer *);
    static doublereal ecod1_h__[5000], ecod2_h__[5000], ed_orig__[5000];

    /* Fortran I/O blocks */
    static cilist io___24 = { 0, 0, 0, fmt_90, 0 };
    static cilist io___25 = { 0, 0, 0, fmt_110, 0 };
    static cilist io___26 = { 0, 0, 0, fmt_110, 0 };


/* MHP 3/94 ADDED METAL DIFFUSION */
/*       DIMENSION HCOMP(15,JSON),HQPR(JSON),HR(JSON),HS1(JSON),HT(JSON), */
/*      *          HD(JSON),HRU(JSON),HTU(JSON),LC(JSON) */
/* ED_HALF(JSON) */

/* THIS PROGRAM EXECUTES THE DIFFUSING OF ELEMENTS. ALL OF THE RELEVANT */
/* PARAMETERS ARE DEFINED AT BOTH THE GRID POINTS AND MIDPOINTS. */

/* CREATE DUMMY VECTORS FOR THE DIFFUSING ELEMENT. THIS ALLOWS A SINGLE */
/* ELEMENT TO BE EASILY PASSED INTO SUB-ROUTINES. */

    /* Parameter adjustments */
    --edxdr_h__;
    espec_h__ -= 4;
    --edelr_h__;
    --ehqpr_h__;
    --etem_h__;
    --eden_h__;
    --er_h__;
    --em_h__;
    --edxdr;
    espec -= 4;
    --edelr;
    --ehqpr;
    --etem;
    --eden;
    --er;
    --em;

    /* Function Body */
    i__1 = *npt - 1;
    for (i__ = 1; i__ <= i__1; ++i__) {
	ed[i__ - 1] = espec[*j + i__ * 3];
	ed_h__[i__ - 1] = espec_h__[*j + i__ * 3];
    }
    ed[*npt - 1] = espec[*j + *npt * 3];

/* STORE ORIGINAL RUN OF LIGHT ELEMENT MASS FRACTIONS IN VECTOR ED_ORIG. */
/* THE CHANGE IN ELEMENTS (ED - ED_ORIG) IS INTERPOLATED BACK TO THE */
/* ORIGINAL GRID AT THE END OF THE ROUTINE; THE CHANGE IN ABUNDANCE */
/* (RATHER THAN THE NEW RUN OF ABUNDANCE) IS USED TO MINIMIZE ERRORS */
/* ARISING FROM THE INTERPOLATION. */
    i__1 = *npt - 1;
    for (i__ = 1; i__ <= i__1; ++i__) {
	ed_orig__[i__ - 1] = ed[i__ - 1];
	ed_orig_h__[i__ - 1] = ed_h__[i__ - 1];
    }
    ed_orig__[*npt - 1] = ed[*npt - 1];

/*  SET THE FLAG LDOLI = TRUE, SO THAT THE LAX-WENDROF ROUTINES KNOW TO NOT */
/*  USE THE OLD METAL DIFFUSION VECTORS. */
    ldoli = TRUE_;

/* NOW USE THE EQUALLY SPACED GRID TO CALUCLATE DIFFUSION COEFFICIENTS IN THE */
/* METHOD OF THE THOUL ROUTINE. MUCH OF THE FOLLOWING CODE WAS TAKEN FROM */
/* SETUP_LISETT.F. */

    microdiff_cod__(npt, &espec[4], &er[1], &eden[1], &etem[1], &ehqpr[1], &
	    edelr[1], ecod1, ecod2, &edxdr[1], thea, thez, j);

/* FIRST STEP OF TWO STEP LAX-WENDROFF METHOD. COMPUTE NEW ABUNDANCES AT ZONE */
/* MIDPOINTS USING THE LAX SCHEME : */
/* X(N+1/2,J+1/2)=1/2(X(N,J+1/2)-1/2(DT/DR)(COD1(N,J+1)-COD1(N,J)) */
/* WHERE N IS THE TIME VARIABLE, J IS THE SPATIAL ONE, AND COD1 IS THE */
/* DIFFUSION COEFFICIENT. */

    lax_wendrof1__(dt, ecod1, &em[1], npt, stot, ed_h__, &ldoli);

/* UPDATE ESPEC WITH THE NEW RUN OF ED_H, FOR THE PURPOSE OF */
/* CALUCLATING NEW DIFFUSION COEFFICIENTS. */

    i__1 = *npt - 1;
    for (i__ = 1; i__ <= i__1; ++i__) {
	espec_h__[*j + i__ * 3] = ed_orig_h__[i__ - 1] + ed_h__[i__ - 1];
    }

/* GET NEW DIFFUSION COEFFICIENTS AT THE ZONE MIDPOINTS, USING THE */
/* PROVISIONAL SOLUTION. NOTE THAT NPT-1 MUST BE PASSED IN, AS THE */
/* MIDPOINTS HAVE ONE LESS GRID ELEMENT. */

    npt2 = *npt - 1;
    microdiff_cod__(&npt2, &espec_h__[4], &er_h__[1], &eden_h__[1], &etem_h__[
	    1], &ehqpr_h__[1], &edelr_h__[1], ecod1_h__, ecod2_h__, &
	    edxdr_h__[1], thea, thez, j);

/* USING THE NEW COEFFICIENTS, SOLVE FOR THE NEW RUN OF ABUNDANCES. */
/* NOTE : THE SR ACTUALLY RETURNS THE *CHANGE* IN THE ABUNDANCE AS A FUNCTION */
/* OF RADIUS, WHICH IS APPLIED TO THE ORIGINAL RUN OF ELEMENTS, RATHER THAN */
/* COMPUTING A NEW RUN OF ABUNDANCE AND TRANSFORMING IT BACK.  THIS IS DONE */
/* TO MINIMIZE ERRORS FROM THE INTERPOLATION. */

    lax_wendrof2__(dt, ecod1_h__, &em_h__[1], ed, npt, stot, &ldoli);

/*  NOW IMPLICITLY SOLVE FOR THE SECOND TERM (INVOLVING THE SECOND */
/*  DERIVATIVE OF THE COMPOSITION GRADIENT). FIRST DEFINE VECTOR ED_P, */
/*  WHICH IS THE ABUNDANCE AT THE START OF THE TIMESTEP, AND ELI_PRIME, */
/*  THE ABUNDANCE ONE WOULD HAVE WITHOUT THE SECOND TERM IN THE DIFFUSION */
/*  EQUATION. */
    i__1 = *npt;
    for (i__ = 1; i__ <= i__1; ++i__) {
	ed_p__[i__ - 1] = ed_orig__[i__ - 1];
	ed_prime__[i__ - 1] = ed[i__ - 1];
    }
/*  ALPHA IS THE NUMERICAL FACTOR IN FRONT OF THE DIFFUSION COEFFICIENTS. */
    fac = const1_1.c4pi * *dt / *dr;
    alpha[0] = fac / em_h__[1];
    i__1 = *npt - 1;
    for (i__ = 2; i__ <= i__1; ++i__) {
	alpha[i__ - 1] = fac / (em_h__[i__] - em_h__[i__ - 1]);
    }
    alpha[*npt - 1] = fac / (*stot - em_h__[*npt - 1]);
/*  START ITERATION LOOP FOR THE NEW RUN OF ABUNDANCES. */
    i__1 = gravst_1.niter_gs__;
    for (iter = 1; iter <= i__1; ++iter) {
/*  FIND CHANGE IN D AT THE ZONE MIDPOINTS, GIVEN CHANGE IN D AT */
/*  THE ZONE CENTERS. */
	i__2 = *npt;
	for (i__ = 2; i__ <= i__2; ++i__) {
	    ed_h__[i__ - 1] = (ed[i__ - 1] + ed[i__ - 2] - ed_p__[i__ - 1] - 
		    ed_p__[i__ - 2]) * .5;
	}
/*  STORE CURRENT RUN OF ABUNDANCES IN VECTOR ED_P. THE ITERATION */
/*  LOOP IS COMPLETED ONCE ED - ED_P IS EVERYWHERE LESS THAN THE TOLERANCE */
/*  GRTOL. ALSO ZERO OUT EQCOD2X_H, WHICH IS ONLY USED IN GRSETT (OLD SETTLING */
/*  ROUTINE), BUT RETAINED FOR LEGACY. */
	i__2 = *npt - 1;
	for (i__ = 1; i__ <= i__2; ++i__) {
	    ed_p__[i__ - 1] = ed[i__ - 1];
	    eqcod2x_h__[i__ - 1] = 0.f;
	}
	ed_p__[*npt - 1] = ed[*npt - 1];
/*  GET NEW DIFFUSION COEFFICIENTS, TAKING INTO ACCOUNT THE CHANGE IN D */
/*  FROM THE PREVIOUS ITERATION. */

	get_imp_diffco__(alpha, ecod2_h__, ed_h__, eqcod2x_h__, a, b, c__, 
		npt);

/*  SOLVE THE TRIDIAGONAL MATRIX SYSTEM FOR THE NEW RUN OF LI. */

	tridiag_gs__(a, b, c__, ed_prime__, npt, ed);

/*  CHECK TO SEE IF THE CORRECTIONS TO THE HYDROGEN ABUNDANCE ARE SMALL */
/*  ENOUGH TO EXIT. */
	dxmax = 0.;
	imax = 0;
	i__2 = *npt;
	for (i__ = 1; i__ <= i__2; ++i__) {
	    dx = ed[i__ - 1] - ed_p__[i__ - 1];
	    if (dx > dxmax) {
		dxmax = dx;
		imax = i__;
	    }
	}
	io___24.ciunit = luout_1.ishort;
	s_wsfe(&io___24);
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
    io___25.ciunit = luout_1.iowr;
    s_wsfe(&io___25);
    do_fio(&c__1, (char *)&gravst_1.grtol, (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&gravst_1.niter_gs__, (ftnlen)sizeof(integer));
    do_fio(&c__1, (char *)&dxmax, (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&imax, (ftnlen)sizeof(integer));
    e_wsfe();
    io___26.ciunit = luout_1.ishort;
    s_wsfe(&io___26);
    do_fio(&c__1, (char *)&gravst_1.grtol, (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&gravst_1.niter_gs__, (ftnlen)sizeof(integer));
    do_fio(&c__1, (char *)&dxmax, (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&imax, (ftnlen)sizeof(integer));
    e_wsfe();
L120:

/*  STORE THE RUN OF CHANGES IN THE DIFFUSED ELEMENT. */
    i__1 = *npt;
    for (i__ = 1; i__ <= i__1; ++i__) {
	espec[*j + i__ * 3] = ed[i__ - 1] - ed_orig__[i__ - 1];
    }
    return 0;
} /* microdiff_run__ */

