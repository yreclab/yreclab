/* deutrate.f -- translated by f2c (version 20061008).
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
    doublereal cdelrl, cmixl, cmixl2, cmixl3, clndp, csecyr;
} const3_;

#define const3_1 const3_

struct {
    doublereal drate[5000], drate0[5000], fmassacc;
    integer jcz;
} deuter_;

#define deuter_1 deuter_

struct {
    logical lnewtcz, lcalcenv;
    doublereal taucz, taucz0, pphot, pphot0, fracstep;
} ovrtrn_;

#define ovrtrn_1 ovrtrn_

/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */
/* DEUTRATE - COMPUTE THE RATE OF NONEQUILIBRIUM DEUTERIUM BURNING */
/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */
/*       SUBROUTINE DEUTRATE(DL,TL,X,XH2,I,ITLVL)  ! KC 2025-05-31 */
/* Subroutine */ int deutrate_(doublereal *dl, doublereal *tl, doublereal *x, 
	integer *i__, integer *itlvl)
{
    /* Initialized data */

    static doublereal c21 = 5.240358e-8;

    /* System generated locals */
    doublereal d__1;

    /* Builtin functions */
    double exp(doublereal), pow_dd(doublereal *, doublereal *);

    /* Local variables */
    static doublereal tfacdeut, rdeutmax, z__, t9, rho, t9m1, t9m13, t9m23, 
	    t9p13, t9p23, rdeut, rdeut2;

/* G Somers 3/17, ADDING NEW TAUCZ COMMON BLOCK */
/* T9P13 IS THE TEMPERATURE IN UNITS OF 10^9 DEGREES K TO THE PLUS 1/3 */
/*  POWER.  MINUS IS DENOTED BY M.  HERE T9 IS THE TEMPERATURE IN UNITS */
/*  OF 10^9 K, CONVERTED FROM THE LOG_10 (T) AND RHO IS THE DENSITY IN */
/*  CGS UNITS. */
    rho = exp(const1_1.cln * *dl);
    t9 = exp(const1_1.cln * (*tl - 9.));
    t9p13 = pow_dd(&t9, &const1_1.cc13);
/* Computing 2nd power */
    d__1 = t9p13;
    t9p23 = d__1 * d__1;
    t9m13 = 1. / t9p13;
/* Computing 2nd power */
    d__1 = t9m13;
    t9m23 = d__1 * d__1;
    t9m1 = 1. / t9;
/* MHP 5/02 ADD DEUTERIUM BURNING TERM TO THE CODE */
/* IF DEUTERIUM IS ABOVE A MINIMUM THRESHOLD VALUE. */
/* RDEUT IS THE RATE (EXCLUDING FACTORS OF THE */
/* ABUNDANCES) AND QRTDEUT IS THE DERIVATIVE W/R/T T. */
/* NOTE THAT SCREENING IS EXCLUDED - REASONABLE GIVEN */
/* THE LOW TEMPERATURES INVOLVED. */
    z__ = t9m13 * -3.72;
    tfacdeut = t9p13 * .112 + 1. + t9p23 * 3.38 + t9 * 2.65;
/* FACTOR OF 3.0115D23 REFLECTS AVAGADROS NUMBER DIVIDED BY THE */
/* MASS OF THE DEUTERON IN AMU */
    rdeut = rho * 2240. * t9p23 * exp(z__) * tfacdeut * 3.0115e23;
/* NOW LIMIT DEUTERIUM BURNING IN A SURFACE CZ TO BE ON A TIME SCALE */
/* NO SHORTER THAN THE CONVECTIVE OVERTURN TIMESCALE. */
    if (*i__ >= deuter_1.jcz && ovrtrn_1.taucz > 1.) {
	rdeutmax = 3.0115e23 / ovrtrn_1.taucz;
	rdeut2 = rdeut * *x;
	if (*i__ == deuter_1.jcz) {
/* JVS 0712 Commented out write command */
/*            WRITE(*,911)RDEUT2,RDEUTMAX,TAUCZ */
/*  911        FORMAT(1P3E15.8) */
	}
	if (rdeut2 > rdeutmax) {
/* JVS 0712 Commented out write command */
/*            WRITE(*,*)RDEUT2,RDEUTMAX */
	    if (*x > 1e-6) {
		rdeut = rdeutmax / *x;
	    }
	}
    }
    deuter_1.drate[*i__ - 1] = *x * rdeut * c21;
    if (*itlvl == 1) {
	deuter_1.drate0[*i__ - 1] = deuter_1.drate[*i__ - 1];
    }
    return 0;
} /* deutrate_ */

