/* mcowind.f -- translated by f2c (version 20061008).
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
/* Subroutine */ int mcowind_(doublereal *bl, doublereal *dt, doublereal *
	hicz, integer *it, doublereal *omegas, doublereal *smass, doublereal *
	teffl, doublereal *wold, doublereal *wind1, doublereal *wind2)
{
    /* System generated locals */
    doublereal d__1, d__2, d__3;

    /* Builtin functions */
    double exp(doublereal), pow_dd(doublereal *, doublereal *);

    /* Local variables */
    static doublereal c__, gl, rl, wn, wp, tcz, temp, fsun, wsat, wnow, fcen1,
	     fcen2, fcorr1, fcorr2;
    extern /* Subroutine */ int amcalc_(doublereal *, doublereal *, 
	    doublereal *), cowind_(doublereal *, doublereal *, doublereal *, 
	    integer *, doublereal *, doublereal *, doublereal *, doublereal *,
	     doublereal *, doublereal *);
    static doublereal wfirst;

/* MHP 8/17 ADDED EXCEN, C_2 TO COMMON BLOCK FOR MATT ET AL. 2012 CENT. TERM */
/*      COMMON/CWIND/WMAX,EXMD,EXW,EXTAU,EXR,EXM,CONSTFACTOR,STRUCTFACTOR,LJDOT0 */
/* MHP 3/09 ADDED OPTION TO SCALE THE SATURATION RATE BY THE OVERTURN TIMESCALE */
/* G Somers 3/17, ADDING NEW TAUCZ COMMON BLOCK */
/* KC 2025-05-30 reordered common block elements */
/*       COMMON/PMMWIND/AWIND,LMWIND,LROSSBY,LBSCALE,PMMA,PMMB,PMMC,PMMD,PMMM, */
/*      *         PMMJD,PMMMD,PMMSOLP,PMMSOLW,PMMSOLTAU */
/*  COWIND RETURNS THE CHANGE IN THE ANGULAR VELOCITY OF THE SURFACE */
/*  CONVECTION ZONE OF A STAR WHICH IS EXPERIENCING ANGULAR MOMENTUM LOSS. */

/*  INPUT VARIABLES: */

/*       DECLARED */
/*  BL : TOTAL LUMINOSITY */
/*  DT : DIFFUSION TIMESTEP. */
/*  HICZ : TOTAL MOMENT OF INERTIA OF THE SURFACE C.Z. */
/*  IT : ITERATION NUMBER (IN THE DIFFUSION ROUTINES). */
/*  OMEGAS : SURFACE ANGULAR VELOCITY AT THE END OF THE PREVIOUS ITERATION. */
/*  SMASS : STELLAR MASS (SOLAR UNITS) */
/*  TEFFL : STELLAR EFFECTIVE TEMPERATURE. */
/*  WOLD : SURFACE ANGULAR VELOCITY AT THE BEGINNING OF THE TIMESTEP. */
/*       IN COMMON BLOCKS */

/*  EXMD,EXW,EXTAU,EXR,EXM,FACTOR : USER PARAMETERS WHICH VARY THE STRENGTH */
/*  OF ANGULAR MOMENTUM LOSS AND ITS DEPENDENCE ON SURFACE ROTATION RATE */
/*  AND OTHER STELLAR PARAMETERS. */

/*  OUTPUT VARIABLES */

/*  WIND1,WIND2:CHANGE IN ANGULAR VELOCITY OF THE SURFACE C.Z. FOR THE TIMESTEP */
/*  BASED ON THE ANGULAR VELOCITY AT THE BEGINNING AND END OF THE TIMESTEP */
/*  RESPECTIVELY. */

/*  WIND1 AND WIND2 ARE INCORPORATED INTO THE DIFFUSION EQUATIONS; */
/*  THEY ARE AVERAGED TO FIND THE TOTAL ANGULAR MOMENTUM LOSS FOR THE */
/*  TIMESTEP. */

/* RUN OLD WINDLAW IF LMWIND = FALSE */
    if (! pmmwind_1.lmwind) {
	cowind_(bl, dt, hicz, it, omegas, smass, teffl, wold, wind1, wind2);
	goto L9999;
    }

/* G Somers 8/17 CREATE ROTATION DUMMY VARIABLES. */
    wfirst = *wold;
    wnow = *omegas;

/* ADD ROSSBY SCALING TO WMAX = CRITICAL W FOR THE SUN. */
    if (pmmwind_1.lrossby) {
/* MHP 8/17 CORRECTED TAUCZ CALCULATION TO INTERPOLATE PROPERLY IN TIMESTEP */
	tcz = ovrtrn_1.taucz0 + ovrtrn_1.fracstep * (ovrtrn_1.taucz - 
		ovrtrn_1.taucz0);
	wsat = cwind_1.wmax * pmmwind_1.pmmsoltau / tcz;
/* G Somers 08/17 IF ADDING ADDITIONAL B SCALING, ADD ADDITIONAL TAUCZ TERM. */
	if (pmmwind_1.lbscale) {
	    wfirst = wfirst * tcz / pmmwind_1.pmmsoltau;
	    wnow = wnow * tcz / pmmwind_1.pmmsoltau;
	    wsat = wsat * tcz / pmmwind_1.pmmsoltau;
	}
    } else {
	wsat = cwind_1.wmax;
    }

/* G Somers 3/17, COMMENTING OUT OLD WIND LAW COEFFICIENT */
/* CALCULATION. ADDING NEW PMM-STYLE VERSION */

/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */

/*      RL=0.5D0*(BL+CLSUNL-C4PIL-CSIGL-4.D0*TEFFL) */
/*      RTOT = EXP(CLN*RL) */
/* DMDOT IS THE MASS LOSS RATE IN SOLAR MASSES PER YEAR. */
/*      DMDOT = 2.0D-14 */
/* DJ/DT = DT*FACTOR*(DMDOT/1.0D-14)**EXMD*OMEGA**EXW*(M/MSUN)**EXM */
/*         *(R/RSUN)**EXR */
/*  THE CONSTANT AND EXPONENTS ARE SET IN PARMIN BASED ON THE INPUT */
/*  INDEX ALFA;SEE PARMIN FOR DETAILS ON THE DEPENDENCE OF EACH ON ALFA. */
/*      C = DT/HICZ*FACTOR*(DMDOT/1.0D-14)**EXMD */
/*     *    *(RTOT/CRSUN)**EXR*SMASS**EXM */

/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */

/* NEW CALCULATION. CALL AMCALC TO SET "STRUCTFACTOR" */

    amcalc_(smass, bl, teffl);

/* CALCULATE THE NEW WIND COEFFICIENT. */

    c__ = *dt / *hicz * cwind_1.constfactor * cwind_1.structfactor;
/* MHP 8/17 ADDED CENTRIFUGAL REDUCTION TERM FROM MATT+2012 ApJ 754, L26 */
/* NOTE THAT THIS IS IMPLEMENTED HERE RELATIVE TO THE SUN */
/*      C_2 = 0.0506 */
/* Computing 2nd power */
    d__1 = pmmwind_1.pmmsolw;
/* Computing 3rd power */
    d__2 = const_1.crsun;
    fsun = d__1 * d__1 * .5f * (d__2 * (d__2 * d__2)) / exp(const1_1.cln * gl)
	     / const_1.cmsun;
/*     RADIUS */
    rl = (*bl + const_1.clsunl - const1_1.c4pil - const2_1.csigl - *teffl * 
	    4.) * .5;
/* Computing 2nd power */
    d__1 = *wold;
    fcorr1 = d__1 * d__1 * .5f * exp(const1_1.cln * (rl * 3.f - const2_1.cgl))
	     / *smass / const_1.cmsun;
/* Computing 2nd power */
    d__1 = *omegas;
    fcorr2 = d__1 * d__1 * .5f * exp(const1_1.cln * (rl * 3.f - const2_1.cgl))
	     / *smass / const_1.cmsun;
/* Computing 2nd power */
    d__2 = cwind_1.c_2__;
/* Computing 2nd power */
    d__3 = cwind_1.c_2__;
    d__1 = (d__2 * d__2 + fsun) / (d__3 * d__3 + fcorr1);
    fcen1 = pow_dd(&d__1, &cwind_1.excen);
/* Computing 2nd power */
    d__2 = cwind_1.c_2__;
/* Computing 2nd power */
    d__3 = cwind_1.c_2__;
    d__1 = (d__2 * d__2 + fsun) / (d__3 * d__3 + fcorr2);
    fcen2 = pow_dd(&d__1, &cwind_1.excen);

/* G Somers, END */
    wp = min(wfirst,wsat);
    wn = min(wnow,wsat);
    d__1 = cwind_1.exw - 1.;
    *wind1 = c__ * pow_dd(&wp, &d__1) * *wold * fcen1;
    d__1 = cwind_1.exw - 1.;
    temp = c__ * pow_dd(&wn, &d__1) * *omegas * fcen2;
/*      WIND1 = C*WP**(EXW-1.0D0)*WOLD */
/*      TEMP = C*WN**(EXW-1.0D0)*OMEGAS */
    if (*it == 1) {
	*wind2 = temp;
    } else {
	*wind2 = (*wind2 + temp) * .5;
    }
L9999:
    return 0;
} /* mcowind_ */

