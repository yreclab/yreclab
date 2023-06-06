/* ccoeft.f -- translated by f2c (version 20100827).
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
    logical lscrib, lpshll, lchemo, lconzo, ljout, lprtin, lpenv;
} ccout_;

#define ccout_1 ccout_

struct {
    integer ilast, idebug, itrack, ishort, imilne, imodpt, istor, iowr;
} luout_;

#define luout_1 luout_

struct {
    doublereal a[5000], b[5000], c__[5000], d__[5000], u[5000], gama[5000];
} tridi_;

#define tridi_1 tridi_

/* $$$$$$ */
/* Subroutine */ int ccoeft_(doublereal *cod, doublereal *dr, doublereal *dt, 
	doublereal *ecomp, doublereal *em, integer *ntot)
{
    /* System generated locals */
    integer i__1;

    /* Local variables */
    static integer i__;
    static doublereal fact, fact0;

/*  SET UP COEFFICIENTS OF DIFFUSION DIFFERENCE EQUATIONS FOR COMPOSITION */
/*  TRANSPORT DUE TO ROTATIONALLY INDUCED MIXING. */

/*  INPUT VARIABLES: */
/*  COD : RUN OF DIFFUSION COEFFICIENTS (COMPUTED IN SR COEFFT). */
/*  DR : GRID SPACING IN RADIUS(CM). */
/*  DT : DIFFUSION TIMESTEP (SEC). */
/*  ECOMP : STARTING ARRAY OF COMPOSITION MASS FRACTION AT THE EQUALLY */
/*          SPACED GRID. */
/*  EM : RUN OF MASSES OF THE EQUALLY SPACED GRID POINTS (GM). */
/*  NTOT : NUMBER OF POINTS IN THE EQUALLY SPACED GRID USED TO SOLVE */
/*         THE DIFFUSION EQUATION. */
/*  OUTPUT VARIABLES : */
/*  THE ABUNDANCE OF SHELL I AT TIME N+1 (COMP(I,N+1)) IS A FUNCTION OF */
/*  COMP(I-1),COMP(I),AND COMP(I+1) AS DISCUSSED BELOW.  THIS CAN BE EXPRESSED */
/*  AS A TRIDIAGONAL MATRIX.  TERMS WHICH DEPEND ON COMP(I-1) ARE STORED IN */
/*  ARRAY A; THOSE WHICH DEPEND ON COMP(I) ARE STORED IN ARRAY B; THOSE */
/*  WHICH DEPEND ON COMP(I+1) ARE STORED IN ARRAY C; AND THE STARTING RUN */
/*  OF COMPOSITION IS STORED IN ARRAY D. */

/*  THE DIFFUSION EQUATION WE ARE SOLVING IS */
/*  dX/dT = 1/(4pi*RHO*R**2)d/dR(D*dX/dR) */
/*  WHERE D IS OUR DIFFUSION COEFFICIENT,X IS THE MASS FRACTION OF THE */
/*  SPECIES IN QUESTION,T IS TIME,R IS RADIUS, AND RHO IS DENSITY. */
/*  USING M = 4pi*RHO*R**2*DR THIS IS DIFFERENCED FOR SHELL I AS */
/*  X(I,N+1)-X(I,N)=(DT/DR)*(1/M)*(D(I+1/2)*(X(I+1,N+1)-X(I,N+1)) - */
/*  D(I-1/2)*(X(I,N+1)-X(I-1,N+1))) */
/*  WHERE M IS THE MASS OF SHELL , INDEX N+1 REFERS TO VALUES AT THE */
/*  END OF THE TIMESTEP, INDEX N REFERS TO VALUES AT THE BEGINNING OF */
/*  THE TIMESTEP. */
/*  THIS SYSTEM IS SUPPLEMENTED WITH APPROPRIATE BOUNDARY CONDITIONS. */

/*  STORE THE RUN OF COMPOSITION AT THE BEGINNING OF THE TIMESTEP IN ARRAY D */
    /* Parameter adjustments */
    --em;
    --ecomp;
    --cod;

    /* Function Body */
    i__1 = *ntot;
    for (i__ = 1; i__ <= i__1; ++i__) {
	tridi_1.d__[i__ - 1] = ecomp[i__];
/* L10: */
    }
/*  FIRST SHELL BOUNDARY CONDITIONS: NO FLOW BELOW THE BOUNDARY */
/*  I.E. THE ANGULAR MOMENTUM TRANSPORT AT THE FIRST SHELL DOES NOT */
/*  DEPEND ON THE SHELLS BELOW IT.(SAME USED FOR LAST SHELL B.C.) */
    fact0 = *dt / *dr;
    fact = fact0 / em[1];
    tridi_1.a[0] = 0.;
    tridi_1.b[0] = fact * cod[2] + 1.;
    tridi_1.c__[0] = -fact * cod[2];
    i__1 = *ntot - 1;
    for (i__ = 2; i__ <= i__1; ++i__) {
	fact = fact0 / em[i__];
	tridi_1.a[i__ - 1] = -fact * cod[i__];
	tridi_1.b[i__ - 1] = fact * (cod[i__] + cod[i__ + 1]) + 1.;
	tridi_1.c__[i__ - 1] = -fact * cod[i__ + 1];
/* L20: */
    }
/*  LAST SHELL BOUNDARY CONDITIONS. */
    fact = fact0 / em[*ntot];
    tridi_1.a[*ntot - 1] = -fact * cod[*ntot];
    tridi_1.b[*ntot - 1] = fact * cod[*ntot] + 1.;
    tridi_1.c__[*ntot - 1] = 0.;
    return 0;
} /* ccoeft_ */

