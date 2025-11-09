/* wind.f -- translated by f2c (version 20061008).
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

/* Table of constant values */

static integer c__1 = 1;

/* $$$$$$ */
/* MHP 10/02 UNUSED LFIRST REMOVED FROM CALL */
/* Subroutine */ int wind_(doublereal *bl, doublereal *delts, doublereal *
	hsbot, doublereal *hstop, integer *jstart, integer *jend, logical *
	ljdot, doublereal *omegas, doublereal *smass, doublereal *teffl, 
	doublereal *hicz, doublereal *hjm)
{
    /* Format strings */
    static char fmt_911[] = "(\002ERROR IN WIND - TAUCZ NOT DEFINED \002,1p2"
	    "e12.3,\002STOPPED\002)";

    /* System generated locals */
    integer i__1;
    doublereal d__1, d__2, d__3, d__4;

    /* Builtin functions */
    integer s_wsfe(cilist *), do_fio(integer *, char *, ftnlen), e_wsfe(void);
    /* Subroutine */ void s_stop(char *, ftnlen);
    double exp(doublereal), pow_dd(doublereal *, doublereal *);

    /* Local variables */
    static integer k, n;
    static doublereal w, dm;
    static integer ii;
    static doublereal dt, dw, rl, ws, wsat, rtot, wnew0, cgrav, fjdom, dmdot;
    static integer nstep;
    static doublereal dwtest;

    /* Fortran I/O blocks */
    static cilist io___2 = { 0, 6, 0, fmt_911, 0 };


/*      *                SJTOT,SMASS,TEFFL,HICZ,HJM,LFIRST)  ! KC 2025-05-31 */
/* MHP 8/17 ADDED EXCEN, C_2 TO COMMON BLOCK FOR MATT ET AL. 2012 CENT. TERM */
/*      COMMON/CWIND/WMAX,EXMD,EXW,EXTAU,EXR,EXM,CONSTFACTOR,STRUCTFACTOR,LJDOT0 */
/* MHP 3/09 ADDED OPTION TO SCALE THE SATURATION RATE BY THE OVERTURN TIMESCALE */
/* IF DESIRED, REMOVE ANGULAR MOMENTUM FROM OUTER CONVECTION ZONE */
/* USING A WEBER-DAVIS MAGNETIC WIND MODEL */
/* MHP 3/09 IF WMAX > 1 THEN ASSUME THAT THE PARAMETER WMAX IS DEFINED BY */
/* WMAX = WMAX(SUN)*TAUCZ(SUN) AND THE SATURATION THRESHOLD WSAT = WMAX/TAUCZ(STAR) */
/* ONLY APPLY THIS IF ANGULAR MOMENTUM TRANSPORT ENABLED */
    /* Parameter adjustments */
    --hjm;

    /* Function Body */
    if (! rot_1.linstb) {
	wsat = cwind_1.wmax;
    } else if (cwind_1.wmax > 1.) {
	if (ovrtrn_1.taucz > 1.) {
	    wsat = cwind_1.wmax / ovrtrn_1.taucz;
/*            WRITE(*,912)WSAT,TAUCZ */
/* 912        FORMAT('Omega sat, Tau',1p2e12.3) */
	} else {
	    s_wsfe(&io___2);
	    do_fio(&c__1, (char *)&cwind_1.wmax, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&ovrtrn_1.taucz, (ftnlen)sizeof(doublereal))
		    ;
	    e_wsfe();
	    s_stop("", (ftnlen)0);
	}
    } else {
	wsat = cwind_1.wmax;
    }
    if (*ljdot) {
/* FIND TOTAL RADIUS OF STAR. */
	cgrav = exp(const1_1.cln * const2_1.cgl);
	rl = (*bl + const_1.clsunl - const1_1.c4pil - const2_1.csigl - *teffl 
		* 4.) * .5;
	rtot = exp(const1_1.cln * rl);
/* DMDOT IS THE MASS LOSS RATE IN SOLAR MASSES PER YEAR. */
	dmdot = 2e-14;
/* DJ/DT = DT*CONSTFACTOR*(DMDOT/1.0D-14)**EXMD*OMEGA**EXW*(M/MSUN)**EXM */
/*         *(R/RSUN)**EXR */
/* TEST : THE LOSS RATE DEPENDS ON OMEGA, AND FOR TIMESTESP THAT ARE */
/* TOO LARGE, ROTATION RATES THAT ARE TOO HIGH, AND THIN SURFACE C.Z.S */
/* NEGATIVE SURFACE ANGULAR VELOCITIES CAN BE PRODUCED. */
/* TO AVOID THIS, CHECK THAT THE TIMESTEP IS SMALL ENOUGH TO ALLOW */
/* A POSITIVE SOLUTION FOR OMEGA IN THE FIRST GUESS AT THE LOSS RATE. */
/* IF NOT, USE A SERIES OF SMALL STEPS. */
/* MHP 12/91 CAP LOSS RATE AT WSAT. */
	d__1 = dmdot / 1e-14;
	d__2 = rtot / const_1.crsun;
	d__3 = min(*omegas,wsat);
	d__4 = cwind_1.exw - 1.;
	dwtest = *delts / *hicz * cwind_1.constfactor * pow_dd(&d__1, &
		cwind_1.exmd) * *omegas * pow_dd(&d__2, &cwind_1.exr) * 
		pow_dd(smass, &cwind_1.exm) * pow_dd(&d__3, &d__4);
	if (dwtest > *omegas) {
	    nstep = (integer) (dwtest / *omegas) + 1;
	    dt = *delts / (doublereal) nstep;
	} else {
	    nstep = 1;
	    dt = *delts;
	}
/*         WRITE(*,3)NSTEP */
/*    3    FORMAT(5X,I5) */
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
	    ++k;
	    d__1 = dmdot / 1e-14;
	    d__2 = rtot / const_1.crsun;
	    d__3 = min(w,wsat);
	    d__4 = cwind_1.exw - 1.;
	    rot_1.wnew = ws - dt / *hicz * cwind_1.constfactor * pow_dd(&d__1,
		     &cwind_1.exmd) * w * pow_dd(&d__2, &cwind_1.exr) * 
		    pow_dd(smass, &cwind_1.exm) * pow_dd(&d__3, &d__4);
	    dw = (d__1 = (wnew0 - rot_1.wnew) / (wnew0 + rot_1.wnew), abs(
		    d__1)) * 2.;
/*         WRITE(*,4)WS,W,WNEW,DW,HICZ */
/*    4    FORMAT(1X,1P5E14.6) */
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
/*        CON = DELTS*CONSTFACTOR*(DMDOT/1.0D-14)**EXMD*OMEGAS**(EXW-1.0D0) */
/*    *           *(RTOT/CRSUN)**EXR*SMASS**EXM */
/*        FJDOT = CON*OMEGAS/(1.0D0+(EXW*CON/HICZ)) */
/* DM IS THE TOTAL MASS IN THE CONVECTION ZONE. */
	dm = *hstop - *hsbot;
/* FIND CHANGE IN ANGULAR MOMENTUM PER UNIT MASS AND SUBTRACT THIS */
/* NUMBER FROM THE J/M OF EACH SHELL IN THE SURFACE CONVECTION ZONE. */
	fjdom = (*omegas - rot_1.wnew) * *hicz / dm;
/*         WRITE(*,11)FJDOM,HJM(JSTART),HJM(JEND) */
/*   11    FORMAT(5X,1P3E14.6) */
/*        FJDOM=FJDOT/DM */
/*        TAUJ=SJTOT/(FJDOT/DELTS)/CSECYR */
	i__1 = *jend;
	for (ii = *jstart; ii <= i__1; ++ii) {
	    hjm[ii] -= fjdom;
/* L10: */
	}
    }
    return 0;
} /* wind_ */

