/* wtime.f -- translated by f2c (version 20100827).
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
    doublereal dtwind;
} ct2_;

#define ct2_1 ct2_

struct {
    doublereal wold[5000], hjx[5000], hio[5000], hgo[5000], r0x[5000], eta2x[
	    5000];
} oldrot_;

#define oldrot_1 oldrot_

struct {
    doublereal atime[14], tcut[5], tscut, tenv0, tenv1, tenv, tgcut;
} ctlim_;

#define ctlim_1 ctlim_

/* $$$$$$ */
/* Subroutine */ int wtime_(doublereal *delts, integer *m, doublereal *omega, 
	doublereal *deltsw, doublereal *dwmax)
{
    /* System generated locals */
    integer i__1;
    doublereal d__1;

    /* Local variables */
    static integer i__, ii;
    static doublereal fac, temp;
    static integer iwmax;
    static doublereal testw;

/*  FOR ROTATING MODELS, LIMIT TIMESTEP BASED ON MAX CHANGE IN OMEGA. */
/*  THE USER PARAMETER DTWIND GOVERNS THE MAXIMUM CHANGE ALLOWED BETWEEN */
/*  MODELS. */
/* INPUT VARIABLES : */
/* DECLARED VARIABLES */
/*   DELTS : PREVIOUS MODEL TIMESTEP */
/*   M : NUMBER OF MODEL POINTS */
/*   OMEGA : RUN OF ANGULAR VELOCITY IN THE CURRENT MODEL. */
/* VARIABLES IN COMMON BLOCKS : */
/*   DTWIND : MAX DELTA OMEGA/OMEGA (DEFAULT =0.08). */
/*   WOLD : RUN OF ANGULAR VELOCITY IN THE PREVIOUS MODEL. */

/* OUTPUT VARIABLES : */
/*   DELTSW : ROTATION-BASED TIMESTEP. */
/*   DWMAX : MAXIMUM FRACTIONAL CHANGE IN OMEGA. */

    /* Parameter adjustments */
    --omega;

    /* Function Body */
    ii = 1;
    *dwmax = (d__1 = omega[ii] - oldrot_1.wold[ii - 1], abs(d__1)) * 2. / (
	    omega[ii] + oldrot_1.wold[ii - 1]);
    iwmax = ii;
    i__1 = *m;
    for (i__ = ii + 1; i__ <= i__1; ++i__) {
	testw = (d__1 = omega[i__] - oldrot_1.wold[i__ - 1], abs(d__1)) * 2. /
		 (omega[i__] + oldrot_1.wold[i__ - 1]);
	if (testw > *dwmax) {
	    *dwmax = testw;
	    iwmax = i__;
	}
/* L50: */
    }
    fac = *dwmax / ct2_1.dtwind;
/*  IF NO CHANGE FROM PREVIOUS MODEL,SET DELTSW TO TIMESTEP */
/*  STORED IN THE PREVIOUS MODEL. */
/*      IF (FAC.EQ.0.D0) FAC=1.0D0 */
    if (fac == 0.) {
	*deltsw = 1e20;
	goto L999;
    }
/*  RESTRICT CHANGE IN TIMESTEP TO NO MORE THAN A FACTOR OF ATIME(14)% */
/* UP OR DOWN. */
    temp = ctlim_1.atime[13] + 1.;
    if (fac > temp) {
	fac = temp;
    }
    if (fac < 1. / temp) {
	fac = 1. / temp;
    }
    *deltsw = *delts / fac;
L999:
    return 0;
} /* wtime_ */

