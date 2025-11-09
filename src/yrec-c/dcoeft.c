/* dcoeft.f -- translated by f2c (version 20061008).
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
    doublereal a[5000], b[5000], c__[5000], d__[5000], u[5000], gama[5000];
} tridi_;

#define tridi_1 tridi_

struct {
    doublereal ecod3[5000], ecod4[5000];
} difad_;

#define difad_1 difad_

struct {
    doublereal vfc[5000];
    logical lvfc, ldifad;
} varfc_;

#define varfc_1 varfc_

/* $$$$$$ */
/* Subroutine */ int dcoeft_(doublereal *ecod, doublereal *dr, doublereal *dt,
	 doublereal *ei, doublereal *ej, doublereal *ew, integer *ntot, 
	doublereal *wind1, doublereal *wind2, logical *lfix)
{
    /* System generated locals */
    integer i__1;

    /* Local variables */
    static integer i__;
    static doublereal fact, fact0, facta;

/* MHP 7/93 */
/*  DCOEFT SETS UP THE COEFFICIENTS FOR THE DIFFUSION DIFFERENCE EQUATION. */

/*  INPUT VARIABLES: */
/*  ECOD : DIFFUSION COEFFICIENTS AT THE EQUALLY SPACED GRID POINTS. */
/*  DR : GRID SPACING. */
/*  DT : TIMESTEP. */
/*  EI : RUN OF MOMENTS OF INERTIA OF EQUALLY SPACED GRID POINTS. */
/*  EW : RUN OF ANGULAR VELOCITY OF EQUALLY SPACED GRID POINTS. */
/*  NTOT : NUMBER OF EQUALLY SPACED GRID POINTS. */
/*  WIND1 : THE ANGULAR MOMENTUM LOSS FROM A SURFACE C.Z. COMPUTED */
/*     EXPLICITILY. */
/*  WIND2 : AS WIND1, BUT COMPUTED IMPLICITLY. */
/*  *NOTE: IF NOT APPLICABLE, WIND1 AND WIND2 ARE ZEROED OUT. */

/*  OUTPUT VARIABLES : */
/*  THE ANGULAR VELOCITY OF SHELL I AT TIME N+1 (W(I,N+1)) IS A FUNCTION OF */
/*  W(I-1),W(I),AND W(I+1) AS DISCUSSED BELOW.  THIS CAN BE EXPRESSED */
/*  AS A TRIDIAGONAL MATRIX. */
/*  A(I) : CONTAINS ALL TERMS INVOLVING OMEGA(I-1). */
/*  B(I) : CONTAINS ALL TERMS INVOLVING OMEGA(I). */
/*  C(I) : CONTAINS ALL TERMS INVOLVING OMEGA(I+1) */
/*  D(I) : THE ANGULAR VELOCITY TERMS AT THE BEGINNING OF THE TIMESTEP. */
/*  *NOTE: ANGULAR MOMENTUM LOSS FROM A SURFACE C.Z. IS SUBTRACTED FROM */
/*     THE LAST ELEMENT OF ARRAY D IF APPLICABLE. */

/*  THE DIFFUSION EQUATION WE ARE SOLVING IS */
/*  dW/dT = 1/(4pi*RHO*R**2) 1/(I/M) d/dR(D*dW/dR) */
/*  WHERE D IS OUR DIFFUSION COEFFICIENT,W IS THE ANGULAR VELOCITY, */
/*  I IS THE MOMENT OF INERTIA,M IS MASS,T IS TIME,R IS RADIUS, */
/*  AND RHO IS DENSITY. */
/*  USING M = 4pi*RHO*R**2*DR THIS IS DIFFERENCED FOR SHELL I AS */
/*  W(I,N+1)-W(I,N)=(DT/DR)*(1/I)*(D(I+1/2)*(W(I+1,N+1)-W(I,N+1)) - */
/*  D(I-1/2)*(W(I,N+1)-W(I-1,N+1))) */
/*  WHERE INDEX N+1 REFERS TO VALUES AT THE END OF THE TIMESTEP,AND */
/*  INDEX N REFERS TO VALUES AT THE BEGINNING OF THE TIMESTEP. */
/*  THIS SYSTEM IS SUPPLEMENTED WITH APPROPRIATE BOUNDARY CONDITIONS. */

    /* Parameter adjustments */
    --ew;
    --ej;
    --ei;
    --ecod;

    /* Function Body */
    fact0 = *dt / *dr;
    i__1 = *ntot;
    for (i__ = 1; i__ <= i__1; ++i__) {
	tridi_1.d__[i__ - 1] = ew[i__];
/* L10: */
    }
    tridi_1.gama[*ntot - 1] = (*wind1 + *wind2) * -.5 * ei[*ntot];
    tridi_1.d__[*ntot - 1] *= tridi_1.gama[*ntot - 1] / ej[*ntot] + 1.;
    if (! varfc_1.ldifad) {
/*  FIRST SHELL BOUNDARY CONDITIONS: NO FLOW BELOW THE BOUNDARY */
/*  I.E. THE ANGULAR MOMENTUM TRANSPORT AT THE FIRST SHELL DOES NOT */
/*  DEPEND ON THE SHELLS BELOW IT. */
	fact = fact0 / ei[1];
	tridi_1.a[0] = 0.;
	tridi_1.b[0] = fact * ecod[2] + 1.;
	tridi_1.c__[0] = -fact * ecod[2];
	i__1 = *ntot - 1;
	for (i__ = 2; i__ <= i__1; ++i__) {
	    fact = fact0 / ei[i__];
	    tridi_1.a[i__ - 1] = -fact * ecod[i__];
	    tridi_1.b[i__ - 1] = fact * (ecod[i__] + ecod[i__ + 1]) + 1.;
	    tridi_1.c__[i__ - 1] = -fact * ecod[i__ + 1];
/* L20: */
	}
/*  LAST SHELL B.C. : SAME AS FIRST SHELL B.C. */
	fact = fact0 / ei[*ntot];
	if (! (*lfix)) {
	    tridi_1.a[*ntot - 1] = -fact * ecod[*ntot];
	    tridi_1.b[*ntot - 1] = fact * ecod[*ntot] + 1.;
	} else {
	    tridi_1.a[*ntot - 1] = 0.;
	    tridi_1.b[*ntot - 1] = 1.;
	}
	tridi_1.c__[*ntot - 1] = 0.;
    } else {
/* IF LDIFAD=T, WE ARE SOLVING A COMBINED DIFFUSION/ADVECTION EQUATION. */
/* THIS ADDS A TERM D/DR(RHO*R**4*V*W) TO THE ORIGINAL D/DR(RHO*R**4* */
/* V*R*DW/DR) EQUATION. */
/*  FIRST SHELL BOUNDARY CONDITIONS: NO FLOW BELOW THE BOUNDARY */
/*  I.E. THE ANGULAR MOMENTUM TRANSPORT AT THE FIRST SHELL DOES NOT */
/*  DEPEND ON THE SHELLS BELOW IT. */
	fact = fact0 / ei[1];
	facta = *dt * .5 / ei[1];
	tridi_1.a[0] = 0.;
	tridi_1.b[0] = fact * difad_1.ecod4[1] + 1. - facta * difad_1.ecod3[1]
		;
	tridi_1.c__[0] = -fact * difad_1.ecod4[1] - facta * difad_1.ecod3[1];
	i__1 = *ntot - 1;
	for (i__ = 2; i__ <= i__1; ++i__) {
	    fact = fact0 / ei[i__];
	    facta = *dt * .5 / ei[i__];
	    tridi_1.a[i__ - 1] = -fact * difad_1.ecod4[i__ - 1] + facta * 
		    difad_1.ecod3[i__ - 1];
	    tridi_1.b[i__ - 1] = fact * (difad_1.ecod4[i__ - 1] + 
		    difad_1.ecod4[i__]) + 1. + facta * (difad_1.ecod3[i__ - 1]
		     - difad_1.ecod3[i__]);
	    tridi_1.c__[i__ - 1] = -fact * difad_1.ecod4[i__] - facta * 
		    difad_1.ecod3[i__];
	}
/*  LAST SHELL B.C. : SAME AS FIRST SHELL B.C. */
	fact = fact0 / ei[*ntot];
	facta = *dt * .5 / ei[*ntot];
	if (! (*lfix)) {
	    tridi_1.a[*ntot - 1] = -fact * difad_1.ecod4[*ntot - 1] + facta * 
		    difad_1.ecod3[*ntot - 1];
	    tridi_1.b[*ntot - 1] = fact * difad_1.ecod4[*ntot - 1] + 1. + 
		    facta * difad_1.ecod3[*ntot - 1];
	} else {
	    tridi_1.a[*ntot - 1] = 0.;
	    tridi_1.b[*ntot - 1] = 1.;
	}
	tridi_1.c__[*ntot - 1] = 0.;
    }
    return 0;
} /* dcoeft_ */

