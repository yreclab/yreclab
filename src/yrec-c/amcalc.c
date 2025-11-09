/* amcalc.f -- translated by f2c (version 20061008).
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
    doublereal clsun, clsunl, clnsun, cmsun, cmsunl, crsun, crsunl, cmbol;
} const_;

#define const_1 const_

struct {
    doublereal cln, clni, c4pi, c4pil, c4pi3l, cc13, cc23, cpi;
} const1_;

#define const1_1 const1_

struct {
    doublereal cgas, ca3, ca3l, csig, csigl, cgl, cmkh, cmkhn;
} const2_;

#define const2_1 const2_

struct {
    doublereal cdelrl, cmixl, cmixl2, cmixl3, clndp, csecyr;
} const3_;

#define const3_1 const3_

struct {
    doublereal wmax, exmd, exw, extau, exr, exm, exl, expr, constfactor, 
	    structfactor, excen, c_2__;
    logical ljdot0;
} cwind_;

#define cwind_1 cwind_

struct {
    doublereal pmma, pmmb, pmmc, pmmd, pmmm, pmmjd, pmmmd, pmmsolp, pmmsolw, 
	    pmmsoltau;
    logical lmwind, lrossby, lbscale;
    char awind[3];
} pmmwind_;

#define pmmwind_1 pmmwind_

struct {
    logical lnewtcz, lcalcenv;
    doublereal taucz, taucz0, pphot, pphot0, fracstep;
} ovrtrn_;

#define ovrtrn_1 ovrtrn_

/* Table of constant values */

static doublereal c_b2 = 10.;

/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */
/* AMCALC */
/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */
/* Subroutine */ int amcalc_(doublereal *smass, doublereal *bl, doublereal *
	teffl)
{
    /* System generated locals */
    doublereal d__1;

    /* Builtin functions */
    double exp(doublereal), pow_dd(doublereal *, doublereal *);

    /* Local variables */
    static doublereal rl, rrad, rtau, rlum, rtot, rmass, rphot;

/* MHP 8/17 ADDED EXCEN, C_2 TO COMMON BLOCK FOR MATT ET AL. 2012 CENT. TERM */
/*      COMMON/CWIND/WMAX,EXMD,EXW,EXTAU,EXR,EXM,CONSTFACTOR,STRUCTFACTOR,LJDOT0 */
/* KC 2025-05-30 reordered common block elements */
/*       COMMON/PMMWIND/AWIND,LMWIND,LROSSBY,LBSCALE,PMMA,PMMB,PMMC,PMMD,PMMM, */
/*      *         PMMJD,PMMMD,PMMSOLP,PMMSOLW,PMMSOLTAU */
/* G Somers, 6/16 */
/* THIS SHORT SUBROUTINE WILL USE THE DELIVERED STRUCTURAL VARIABLES TO DETERMINE */
/* THE STRENGTH OF THE TORQUE, ACCORDING TO THE MATT ET AL. (2012) FORMULATION. */

/* COLLECT THE RELEVANT STRUCTURE VARIABLES, AND */
/*     MASS */
    rmass = *smass;
/*     RADIUS */
    rl = (*bl + const_1.clsunl - const1_1.c4pil - const2_1.csigl - *teffl * 
	    4.) * .5;
    rtot = exp(const1_1.cln * rl);
    rrad = rtot / const_1.crsun;
/*     LUMINOSITY */
    rlum = pow_dd(&c_b2, bl);
/*     PHOTOSPHERIC PRESSURE */
    d__1 = ovrtrn_1.pphot0 + ovrtrn_1.fracstep * (ovrtrn_1.pphot - 
	    ovrtrn_1.pphot0);
    rphot = pow_dd(&c_b2, &d__1) / pow_dd(&c_b2, &pmmwind_1.pmmsolp);
/*     CONVECTIVE OVERTURN TIMESCALE */
    if (pmmwind_1.lrossby) {
	rtau = (ovrtrn_1.taucz0 + ovrtrn_1.fracstep * (ovrtrn_1.taucz - 
		ovrtrn_1.taucz0)) / pmmwind_1.pmmsoltau;
    } else {
	rtau = 1.f;
    }
/*     COMBINE THEM ALL */
    cwind_1.structfactor = pow_dd(&rmass, &cwind_1.exm) * pow_dd(&rrad, &
	    cwind_1.exr) * pow_dd(&rlum, &cwind_1.exl) * pow_dd(&rphot, &
	    cwind_1.expr) * pow_dd(&rtau, &cwind_1.extau);
    return 0;
} /* amcalc_ */

