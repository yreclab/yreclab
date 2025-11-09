/* mwind.f -- translated by f2c (version 20061008).
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
    doublereal cdelrl, cmixz, cmixl2, cmixl3, clndp, csecyr;
} const3_;

#define const3_1 const3_

struct {
    doublereal wmax, exmd, exw, extau, exr, exm, exl, expr, constfactor, 
	    structfactor, excen, c_2__;
    logical ljdot0;
} cwind_;

#define cwind_1 cwind_

struct {
    doublereal drate[5000], drate0[5000], fmassacc;
    integer jcz;
} deuter_;

#define deuter_1 deuter_

struct {
    doublereal wnew, walpcz, acfpft;
    integer itfp1, itfp2;
    logical lrot, linstb, lwnew;
} rot_;

#define rot_1 rot_

struct {
    logical lnewtcz, lcalcenv;
    doublereal taucz, taucz0, pphot, pphot0, fracstep;
} ovrtrn_;

#define ovrtrn_1 ovrtrn_

struct {
    doublereal pmma, pmmb, pmmc, pmmd, pmmm, pmmjd, pmmmd, pmmsolp, pmmsolw, 
	    pmmsoltau;
    logical lmwind, lrossby, lbscale;
    char awind[3];
} pmmwind_;

#define pmmwind_1 pmmwind_

/* $$$$$$ */
/* MHP 10/02 UNUSED LFIRST REMOVED FROM CALL */
/* Subroutine */ int mwind_(doublereal *bl, doublereal *delts, doublereal *
	hsbot, doublereal *hstop, integer *jstart, integer *jend, logical *
	ljdot, doublereal *omegas, doublereal *smass, doublereal *teffl, 
	doublereal *hicz, doublereal *hjm)
{
    /* System generated locals */
    integer i__1;
    doublereal d__1, d__2, d__3;

    /* Builtin functions */
    double exp(doublereal), pow_dd(doublereal *, doublereal *);

    /* Local variables */
    static integer k, n;
    static doublereal w, dm;
    static integer ii;
    static doublereal dt, dw, rl, ws, tcz, fcen;
    extern /* Subroutine */ int wind_(doublereal *, doublereal *, doublereal *
	    , doublereal *, integer *, integer *, logical *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *);
    static doublereal fsun, wsat, wnow, wnew0, fjdom, fcorr;
    static integer nstep;
    extern /* Subroutine */ int amcalc_(doublereal *, doublereal *, 
	    doublereal *);
    static doublereal dwtest;

/*      *                SJTOT,SMASS,TEFFL,HICZ,HJM,LFIRST)  ! KC 2025-05-31 */
/* MHP 8/17 ADDED EXCEN, C_2 TO COMMON BLOCK FOR MATT ET AL. 2012 CENT. TERM */
/*      COMMON/CWIND/WMAX,EXMD,EXW,EXTAU,EXR,EXM,CONSTFACTOR,STRUCTFACTOR,LJDOT0 */
/* MHP 3/09 ADDED OPTION TO SCALE THE SATURATION RATE BY THE OVERTURN TIMESCALE */
/* G Somers 3/17, ADDING NEW TAUCZ COMMON BLOCK */
/* KC 2025-05-30 reordered common block elements */
/*       COMMON/PMMWIND/AWIND,LMWIND,LROSSBY,LBSCALE,PMMA,PMMB,PMMC,PMMD,PMMM, */
/*      *         PMMJD,PMMMD,PMMSOLP,PMMSOLW,PMMSOLTAU */
/* IF DESIRED, REMOVE ANGULAR MOMENTUM FROM OUTER CONVECTION ZONE */
/* USING A WEBER-DAVIS MAGNETIC WIND MODEL */
    /* Parameter adjustments */
    --hjm;

    /* Function Body */
    if (! pmmwind_1.lmwind) {
	wind_(bl, delts, hsbot, hstop, jstart, jend, ljdot, omegas, smass, 
		teffl, hicz, &hjm[1]);
/*      *                SJTOT,SMASS,TEFFL,HICZ,HJM)  ! KC 2025-05-31 */
	goto L9999;
    }

/* ADD ROSSBY SCALING IF DESIRED. */
    if (pmmwind_1.lrossby) {
/* MHP 8/17 CORRECTED TAUCZ CALCULATION TO INTERPOLATE PROPERLY IN TIMESTEP */
	tcz = ovrtrn_1.taucz0 + ovrtrn_1.fracstep * (ovrtrn_1.taucz - 
		ovrtrn_1.taucz0);
	if (pmmwind_1.lbscale) {
/* G Somers 8/17 CREATE ROTATION DUMMY VARIABLES. */
	    wnow = *omegas * tcz / pmmwind_1.pmmsoltau;
	    wsat = cwind_1.wmax;
	} else {
	    wnow = *omegas;
	    wsat = cwind_1.wmax * pmmwind_1.pmmsoltau / tcz;
	}
/* If not scaling, just set dummies to the original values. */
    } else {
	wnow = *omegas;
	wsat = cwind_1.wmax;
    }

/* G Somers 3/17, CHANGING WINDLAW TO NEW MATT+2012 METHOD. */

/* FIND TOTAL RADIUS OF STAR. */
/* G Somers - CGRAV, RTOT not used, so blacking out. */
/*         CGRAV = DEXP(CLN*CGL) */
/*         RL=0.5D0*(BL+CLSUNL-C4PIL-CSIGL-4.D0*TEFFL) */
/*         RTOT = DEXP(CLN*RL) */
/* DMDOT IS THE MASS LOSS RATE IN SOLAR MASSES PER YEAR. */
/* G Somers - Don't need DMDOT anymore. */
/*         DMDOT = 2.0D-14 */
/* DJ/DT = DT*FACTOR*(DMDOT/1.0D-14)**EXMD*OMEGA**EXW*(M/MSUN)**EXM */
/*         *(R/RSUN)**EXR */

/* G Somers - New calculation. Call AMCALC to set "STRUCTFACTOR". */

    amcalc_(smass, bl, teffl);

/* TEST : THE LOSS RATE DEPENDS ON OMEGA, AND FOR TIMESTESP THAT ARE */
/* TOO LARGE, ROTATION RATES THAT ARE TOO HIGH, AND THIN SURFACE C.Z.S */
/* NEGATIVE SURFACE ANGULAR VELOCITIES CAN BE PRODUCED. */
/* TO AVOID THIS, CHECK THAT THE TIMESTEP IS SMALL ENOUGH TO ALLOW */
/* A POSITIVE SOLUTION FOR OMEGA IN THE FIRST GUESS AT THE LOSS RATE. */
/* IF NOT, USE A SERIES OF SMALL STEPS. */
/* MHP 12/91 CAP LOSS RATE AT WSAT. */

/* G Somers, Commenting out the old DWTEST, adding the PMM version. */
/*         DWTEST = (DELTS/HICZ)*FACTOR*(DMDOT/1.0D-14)**EXMD */
/*     *          *OMEGAS*(RTOT/CRSUN)**EXR*SMASS**EXM */
/*     *          *MIN(OMEGAS,WSAT)**(EXW-1.0D0) */
/* MHP 8/17 ADDED CENTRIFUGAL REDUCTION TERM FROM MATT+2012 ApJ 754, L26 */
/* NOTE THAT THIS IS IMPLEMENTED HERE RELATIVE TO THE SUN */
/*      C_2 = 0.0506 */
/* Computing 2nd power */
    d__1 = pmmwind_1.pmmsolw;
/* Computing 3rd power */
    d__2 = const_1.crsun;
    fsun = d__1 * d__1 * .5f * (d__2 * (d__2 * d__2)) / exp(const1_1.cln * 
	    const2_1.cgl) / const_1.cmsun;
/*     RADIUS */
    rl = (*bl + const_1.clsunl - const1_1.c4pil - const2_1.csigl - *teffl * 
	    4.) * .5;
/* Computing 2nd power */
    d__1 = *omegas;
    fcorr = d__1 * d__1 * .5f * exp(const1_1.cln * (rl * 3.f - const2_1.cgl)) 
	    / *smass / const_1.cmsun;
/* Computing 2nd power */
    d__2 = cwind_1.c_2__;
/* Computing 2nd power */
    d__3 = cwind_1.c_2__;
    d__1 = (d__2 * d__2 + fsun) / (d__3 * d__3 + fcorr);
    fcen = pow_dd(&d__1, &cwind_1.excen);
    d__1 = min(wnow,wsat);
    d__2 = cwind_1.exw - 1.;
    dwtest = *delts / *hicz * cwind_1.constfactor * cwind_1.structfactor * *
	    omegas * pow_dd(&d__1, &d__2) * fcen;
/*      DWTEST = (DELTS/HICZ)*CONSTFACTOR*STRUCTFACTOR*OMEGAS */
/*     *          *MIN(OMEGAS,WSAT)**(EXW-1.0D0) */
/* G Somers END */
    if (dwtest > *omegas) {
	nstep = (integer) (dwtest / *omegas) + 1;
	dt = *delts / (doublereal) nstep;
    } else {
	nstep = 1;
	dt = *delts;
    }
/*      WRITE(*,3)NSTEP */
/*    3 FORMAT(5X,I5) */
    ws = *omegas;
    i__1 = nstep;
    for (n = 1; n <= i__1; ++n) {
/*  THE CONSTANT AND EXPONENTS ARE SET IN PARMIN BASED ON THE INPUT */
/*  INDEX ALFA;SEE PARMIN FOR DETAILS ON THE DEPENDENCE OF EACH ON ALFA. */
/*  ITERATIVE SOLUTION : FOR FIRST GUESS, USE OMEGA=INITIAL OMEGA IN */
/*  COMPUTING LOSS RATE. TO COMPUTE SUBSEQUENT RATES, USE THE AVERAGE OF THE */
/*  STARTING OMEGA AND THE *PREVIOUS* ENDING OMEGA (I.E. AVERAGE EXPLICIT */
/*  AND IMPLICIT SOLUTIONS). */
	k = 0;
	w = ws;
	wnew0 = ws;
L5:
/* G Somers 08/17 IF ADDING ADDITIONAL B SCALING, ADD ADDITIONAL TAUCZ TERM. */
	if (pmmwind_1.lbscale) {
	    wnow = w * tcz / pmmwind_1.pmmsoltau;
	} else {
	    wnow = w;
	}
	++k;
/* G Somers, Commenting out the old WNEW, adding the PMM version. */
/*         WNEW = WS - (DT/HICZ)*FACTOR*(DMDOT/1.0D-14)**EXMD */
/*     *          *W*(RTOT/CRSUN)**EXR*SMASS**EXM */
/*     *          *MIN(W,WSAT)**(EXW-1.0D0) */
/* MHP 8/17 ADDED CENTRIFUGAL REDUCTION TERM FROM MATT+2012 ApJ 754, L26 */
/* NOTE THAT THIS IS IMPLEMENTED HERE RELATIVE TO THE SUN */
/* Computing 2nd power */
	d__1 = w;
	fcorr = d__1 * d__1 * .5f * exp(const1_1.cln * (rl * 3.f - 
		const2_1.cgl)) / *smass / const_1.cmsun;
/* Computing 2nd power */
	d__2 = cwind_1.c_2__;
/* Computing 2nd power */
	d__3 = cwind_1.c_2__;
	d__1 = (d__2 * d__2 + fsun) / (d__3 * d__3 + fcorr);
	fcen = pow_dd(&d__1, &cwind_1.excen);
	d__1 = min(wnow,wsat);
	d__2 = cwind_1.exw - 1.;
	rot_1.wnew = ws - dt / *hicz * cwind_1.constfactor * 
		cwind_1.structfactor * w * pow_dd(&d__1, &d__2) * fcen;
/*         WNEW = WS - (DT/HICZ)*CONSTFACTOR*STRUCTFACTOR*W */
/*     *          *MIN(W,WSAT)**(EXW-1.0D0) */
/* G Somers END */
	dw = (d__1 = (wnew0 - rot_1.wnew) / (wnew0 + rot_1.wnew), abs(d__1)) *
		 2.;
/*       WRITE(*,4)WS,W,WNEW,DW,HICZ */
/*    4 FORMAT(1X,1P5E14.6) */
	if (dw > 1e-6) {
	    w = (ws + rot_1.wnew) * .5;
	    wnew0 = rot_1.wnew;
	    if (k <= 20) {
		goto L5;
	    }
	}
	ws = rot_1.wnew;
/* L100: */
    }
/*     CON = DELTS*FACTOR*(DMDOT/1.0D-14)**EXMD*OMEGAS**(EXW-1.0D0) */
/*    *        *(RTOT/CRSUN)**EXR*SMASS**EXM */
/*     FJDOT = CON*OMEGAS/(1.0D0+(EXW*CON/HICZ)) */
/* DM IS THE TOTAL MASS IN THE CONVECTION ZONE. */
    dm = *hstop - *hsbot;
/* FIND CHANGE IN ANGULAR MOMENTUM PER UNIT MASS AND SUBTRACT THIS */
/* NUMBER FROM THE J/M OF EACH SHELL IN THE SURFACE CONVECTION ZONE. */
    fjdom = (*omegas - rot_1.wnew) * *hicz / dm;
/*      WRITE(*,11)FJDOM,HJM(JSTART),HJM(JEND) */
/*   11 FORMAT(5X,1P3E14.6) */
/*     FJDOM=FJDOT/DM */
/*     TAUJ=SJTOT/(FJDOT/DELTS)/CSECYR */
    i__1 = *jend;
    for (ii = *jstart; ii <= i__1; ++ii) {
	hjm[ii] -= fjdom;
/* L10: */
    }
L9999:
    return 0;
} /* mwind_ */

