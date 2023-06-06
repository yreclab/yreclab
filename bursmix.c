/* bursmix.f -- translated by f2c (version 20100827).
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
    logical lexcom;
} flag_;

#define flag_1 flag_

struct {
    doublereal pscal0, pscal1;
} liov_;

#define liov_1 liov_

struct {
    doublereal rli6[5000], rli7[5000], rbe9[5000];
} newrat_;

#define newrat_1 newrat_

struct {
    doublereal rli60[5000], rli70[5000], rbe90[5000];
} oldrat_;

#define oldrat_1 oldrat_

struct {
    doublereal hpo[5000], hto[5000], hro[5000], hlo[5000], hdo[5000], hcompp[
	    75000]	/* was [15][5000] */, hss[5000];
    logical lco[5000], lczo[5000];
} oldmod_;

#define oldmod_1 oldmod_

/* Table of constant values */

static integer c__5 = 5;

/* $$$$$$ */
/* Subroutine */ int bursmix_(doublereal *cod2, doublereal *delts, doublereal 
	*hcomp, doublereal *hd, doublereal *hl, doublereal *hp, doublereal *
	hr, doublereal *hs, doublereal *hs1, doublereal *hs2, doublereal *
	hstot, doublereal *ht, doublereal *hv, integer *imax, integer *imin, 
	integer *jenv0, integer *jenv1, logical *lok, logical *lcz, integer *
	m, integer *mrzone, integer *mxzone, integer *nrzone, integer *nzone)
{
    /* Initialized data */

    static integer nseq[11] = { 1,2,4,6,8,10,12,14,16,18,20 };

    /* Format strings */
    static char fmt_5[] = "(\002 WARNING - EXTRAPOLATION IN BSBURN DID NOT C"
	    "ONVERGE\002)";

    /* System generated locals */
    integer i__1, i__2, i__3, i__4;

    /* Builtin functions */
    integer s_wsfe(cilist *), e_wsfe(void);

    /* Local variables */
    extern /* Subroutine */ int bsrotmix_(doublereal *, doublereal *, integer 
	    *, integer *, integer *, integer *, integer *, logical *);
    static integer i__, j;
    static doublereal em[5000], dt;
    static integer iii, jjj, ibeg, jbeg, iend, jend, ntot;
    static doublereal ecod2[5000], hkeep[15000]	/* was [3][5000] */, hcsav[
	    75000]	/* was [15][5000] */;
    static integer nspec;
    static logical lconv;
    static integer nburs, nstep;
    extern /* Subroutine */ int rotmix_(doublereal *, doublereal *, 
	    doublereal *, doublereal *, integer *, integer *, integer *, 
	    integer *, integer *, integer *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, logical *, doublereal *)
	    , liburn2_(doublereal *, doublereal *, doublereal *, doublereal *,
	     doublereal *, doublereal *, doublereal *, integer *, integer *, 
	    integer *), ndifcom_(doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, integer *, integer *, integer *, 
	    integer *, logical *, logical *, integer *, integer *, doublereal 
	    *, integer *, integer *);

    /* Fortran I/O blocks */
    static cilist io___20 = { 0, 6, 0, fmt_5, 0 };


/* INPUT VARIABLES */
/* LOCAL VARIABLES */
    /* Parameter adjustments */
    mxzone -= 13;
    mrzone -= 14;
    --lcz;
    --hv;
    --ht;
    --hs2;
    --hs1;
    --hs;
    --hr;
    --hp;
    --hl;
    --hd;
    hcomp -= 16;
    --cod2;

    /* Function Body */
/* THIS SUBROUTINE IS DESIGNED TO ALTERNATE BETWEEN NUCLEAR BURNING */
/* PLUS GRAVITATIONAL SETTLING AND MIXING IN A SERIES OF PROGRESSIVELY */
/* SMALLER TIMESTEPS, EXTRAPOLATING TO THE ANSWER FOR ZERO TIMESTEP. */
/* IT ASSUMES THAT THE DIFFUSION COEFFICIENTS, STRUCTURE, AND NUCLEAR REACTION */
/* RATES ARE HELD CONSTANT DURING THE TIME STEP.  THE PROCEDURE IS AS */
/* FOLLOWS: */
/* STORE THE RESULTS FOR THE WHOLE TIMESTEP IN ENTRY ONE. */
/* THEN CALL THE NUCLEAR BURNING ROUTINES TO BURN AND THE ROTATIONAL */
/* MIXING ROUTINE TO MIX FOR A SERIES OF SMALLER TIME STEPS, STORING THE */
/* ANSWER AS A FUNCTION OF TIME STEP. */
    if (flag_1.lexcom) {
	nspec = 15;
    } else {
	nspec = 11;
    }
    jbeg = 4;
    jend = nspec;
    nburs = 11;
/* STORE ALL ELEMENTS HERE - HCOMPP IS USED AS THE START OF */
/* TIMESTEP VARIABLE IN KEMCOM, SO IT NEEDS TO BE TEMPORARILY */
/* OVERWRITTEN IN THE SOLUTION PROCESS */
    i__1 = *m;
    for (i__ = 1; i__ <= i__1; ++i__) {
	i__2 = nspec;
	for (j = 1; j <= i__2; ++j) {
	    hcsav[j + i__ * 15 - 16] = oldmod_1.hcompp[j + i__ * 15 - 16];
	}
	for (j = 1; j <= 3; ++j) {
	    hkeep[j + i__ * 3 - 4] = hcomp[j + i__ * 15];
	}
    }
/* STORE RESULTS OF INITIAL CALCULATION AS FIRST ENTRY IN BS */
/* ROUTINE */
    iii = 1;
    bsrotmix_(delts, &hcomp[16], &iii, m, &jbeg, &nspec, nseq, &lconv);
    i__1 = nburs;
    for (iii = 2; iii <= i__1; ++iii) {
/* RESET COMPOSITION TO INITIAL VALUE. */
	i__2 = *m;
	for (i__ = 1; i__ <= i__2; ++i__) {
	    i__3 = nspec;
	    for (j = 1; j <= i__3; ++j) {
		hcomp[j + i__ * 15] = hcsav[j + i__ * 15 - 16];
		oldmod_1.hcompp[j + i__ * 15 - 16] = hcsav[j + i__ * 15 - 16];
	    }
	}
	nstep = nseq[iii - 1];
	dt = *delts / (doublereal) nstep;
	i__2 = nstep;
	for (jjj = 1; jjj <= i__2; ++jjj) {
/* PERFORM NUCLEAR BURNING */
	    rotmix_(&dt, &hcomp[16], &hs2[1], &ht[1], &c__5, m, &mrzone[14], &
		    mxzone[13], nrzone, nzone, hstot, &hd[1], &hs[1], &hr[1], 
		    &hp[1], &lcz[1], &hs1[1]);
/* PERFORM MIXING */
	    ndifcom_(&dt, &cod2[1], ecod2, em, &hd[1], &hl[1], &hp[1], &hr[1],
		     &hs[1], &hs1[1], &hs2[1], hstot, &hv[1], &ibeg, &iend, 
		    imax, imin, &lcz[1], lok, m, &ntot, &hcomp[16], &jbeg, &
		    jend);
	    if (flag_1.lexcom) {
		liburn2_(&dt, &hcomp[16], &hd[1], &hr[1], &hs1[1], &hs2[1], &
			ht[1], jenv1, jenv0, m);
	    }
	    i__3 = *m;
	    for (i__ = 1; i__ <= i__3; ++i__) {
		i__4 = nspec;
		for (j = 1; j <= i__4; ++j) {
		    oldmod_1.hcompp[j + i__ * 15 - 16] = hcomp[j + i__ * 15];
		}
	    }
	}
	bsrotmix_(delts, &hcomp[16], &iii, m, &jbeg, &nspec, nseq, &lconv);
	if (lconv) {
	    i__2 = *m;
	    for (i__ = 1; i__ <= i__2; ++i__) {
		i__3 = nspec;
		for (j = 1; j <= i__3; ++j) {
		    oldmod_1.hcompp[j + i__ * 15 - 16] = hcomp[j + i__ * 15];
		}
	    }
	    goto L10;
	}
    }
/* FAILED TO CONVERGE; PRINT WARNING */
/* IN THIS CASE THE UNEXTRAPOLATED FINAL COMPOSITION IS USED. */
    s_wsfe(&io___20);
    e_wsfe();
L10:
    i__1 = *m;
    for (i__ = 1; i__ <= i__1; ++i__) {
	hcomp[i__ * 15 + 1] = hkeep[i__ * 3 - 3];
	hcomp[i__ * 15 + 3] = hkeep[i__ * 3 - 1];
	hcomp[i__ * 15 + 2] = 1. - hcomp[i__ * 15 + 1] - hcomp[i__ * 15 + 3] 
		- hcomp[i__ * 15 + 4];
    }
    if (flag_1.lexcom) {
	i__1 = *m;
	for (i__ = 1; i__ <= i__1; ++i__) {
	    oldrat_1.rli60[i__ - 1] = newrat_1.rli6[i__ - 1];
	    oldrat_1.rli70[i__ - 1] = newrat_1.rli7[i__ - 1];
	    oldrat_1.rbe90[i__ - 1] = newrat_1.rbe9[i__ - 1];
	}
	*jenv0 = *jenv1;
	liov_1.pscal0 = liov_1.pscal1;
    }
    return 0;
} /* bursmix_ */

