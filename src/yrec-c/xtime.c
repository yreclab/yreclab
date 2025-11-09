/* xtime.f -- translated by f2c (version 20061008).
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
    doublereal atime[14], tcut[5], tscut, tenv0, tenv1, tenv, tgcut;
} ctlim_;

#define ctlim_1 ctlim_

struct {
    doublereal clsun, clsunl, clnsun, cmsun, cmsunl, crsun, crsunl, cmbol;
} const_;

#define const_1 const_

struct {
    doublereal cdelrl, cmixl, cmixl2, cmixl3, clndp, csecyr;
} const3_;

#define const3_1 const3_

struct {
    logical lptime;
} ct3_;

#define ct3_1 ct3_

struct {
    logical lexcom;
} flag_;

#define flag_1 flag_



/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */
/* XTIME */
/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */
/* Subroutine */ int xtime_(doublereal *hd, doublereal *hcomp, doublereal *hl,
	 doublereal *hs1, doublereal *hs2, doublereal *ht, doublereal *hydlum,
	 integer *jcore, integer *jxmid, integer *m, doublereal *deltsh, 
	doublereal *hr1, doublereal *hr2, doublereal *hr3, doublereal *hr4, 
	doublereal *hr5, doublereal *hr6, doublereal *hr7, doublereal *hr8, 
	doublereal *hr9, doublereal *hr10, doublereal *hr11, doublereal *hr12,
	 doublereal *hr13, doublereal *hf1, doublereal *hf2)
{
    /* System generated locals */
    doublereal d__1, d__2;

    /* Local variables */
    static doublereal x, y, z__, dl, dx, tl, xh2, xc12, xc13, xn14, xn15, 
	    xo16, xo17, xo18, xhe3, xbe9, xli6, xli7, dcdt;
    static integer iend;
    static doublereal dodt, dxdt, dydt;
    extern /* Subroutine */ int rates_(doublereal *, doublereal *, doublereal 
	    *, doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, integer *, doublereal *,
	     doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *);
    static integer ibegin;
    extern /* Subroutine */ int eqburn_(doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, integer *, integer *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *);
    static doublereal deltsh2;

/*      *   HR13,HF1,HF2,JXBEG)  ! KC 2025-05-31 */
/* MHP 10/02 ADDED MISSING DIMENSION STATEMENTS! */
/*  THIS SR FINDS THE TIMESTEP BASED ON HYDROGEN BURNING. */
/*  FOR STARS WITH CENTRAL X > ATIME(1) THE TIMESTEP */
/*       IS THE TIME NEEDED TO BURN THE MINIMUM OF ATIME(2) OF */
/*       X AT THE CENTER OR THE FRACTION ATIME(3) OF THE CENTRAL X. */
/*  STARS WITH CENTRAL X < ATIME(1) ARE CONSIDERED BY THE PROGRAM */
/*       TO HAVE A HYDROGEN SHELL BURNING SOURCE.  THE TIMESTEP IS THE */
/*       MINIMUM OF THE TIME REQUIRED TO BURN ATIME(7) OF X AT THE SHELL */
/*       MIDPOINT OR TO BURN THE MASS FRACTION ATIME(6) OF X IN THE */
/*       ENTIRE STAR. */
/* H-CORE BURNING TIME CRITERION */
/* **NOTE THAT FOR A CONVECTIVE CORE, THE TIMESTEP IS BASED ON THE TIME */
/*   NEEDED TO BURN THE GIVEN FRACTION OF HYDROGEN IN THE CORE AND NOT */
/*   JUST IN THE CENTRAL SHELL. */
    /* Parameter adjustments */
    --hf2;
    --hf1;
    --hr13;
    --hr12;
    --hr11;
    --hr10;
    --hr9;
    --hr8;
    --hr7;
    --hr6;
    --hr5;
    --hr4;
    --hr3;
    --hr2;
    --hr1;
    --ht;
    --hs2;
    --hs1;
    --hl;
    hcomp -= 16;
    --hd;

    /* Function Body */
    if (hcomp[16] >= ctlim_1.atime[0]) {
/* Computing MIN */
	d__1 = ctlim_1.atime[1], d__2 = ctlim_1.atime[2] * hcomp[*jcore * 15 
		+ 1];
	dx = min(d__1,d__2);
	*deltsh = 6e18 / const_1.clsun * (hs1[*jcore] / hl[*jcore]) * dx;
	return 0;
    }
/* H-SHELL BURNING CRITERION */
/* LIMIT TOTAL MASS OF HYDROGEN BURNED. */
/*      DX = ATIME(6)*HCOMP(1,M)*(CMSUN/CLSUN) */
    dx = ctlim_1.atime[5] * hcomp[*m * 15 + 1] * (const_1.cmsun / 
	    const_1.clsun);
    *deltsh = dx * 6e18 / *hydlum;
/* LIMIT X-DEPLETION AT SHELL MID-POINT. */
/* CALL NUCLEAR REACTION SR'S TO FIND DXDT AT THE SHELL MIDPOINT. */
    ibegin = *jxmid;
    iend = *jxmid;
    dl = hd[iend];
    tl = ht[iend];
    x = hcomp[iend * 15 + 1];
    y = hcomp[iend * 15 + 2];
    z__ = hcomp[iend * 15 + 3];
    xhe3 = hcomp[iend * 15 + 4];
    xc12 = hcomp[iend * 15 + 5];
    xc13 = hcomp[iend * 15 + 6];
    xn14 = hcomp[iend * 15 + 7];
    xn15 = hcomp[iend * 15 + 8];
    xo16 = hcomp[iend * 15 + 9];
    xo17 = hcomp[iend * 15 + 10];
    xo18 = hcomp[iend * 15 + 11];
    xh2 = hcomp[iend * 15 + 12];
    xli6 = hcomp[iend * 15 + 13];
    xli7 = hcomp[iend * 15 + 14];
    xbe9 = hcomp[iend * 15 + 15];
/* SETUP NUCLEAR ENERGY TERMS */
/*       CALL RATES(DL,TL,X,Y,Z,XHE3,XC12,XC13,XN14,XN15, */
/*      *     XO16,XO17,XO18,XH2,XLI6,XLI7,XBE9,IEND,HR1,HR2,HR3,HR4,  ! KC 2025-05-31 */
    rates_(&dl, &tl, &x, &y, &xhe3, &xc12, &xc13, &xn14, &xo16, &xo18, &iend, 
	    &hr1[1], &hr2[1], &hr3[1], &hr4[1], &hr5[1], &hr6[1], &hr7[1], &
	    hr8[1], &hr9[1], &hr10[1], &hr11[1], &hr12[1], &hr13[1], &hf1[1], 
	    &hf2[1]);
/*       CALL EQBURN(HF1,HR1,HR2,HR3,HR4,HR5,HR6,HR7,HR8,HR9,HR10,HR11,  ! KC 2025-05-31 */
    eqburn_(&hr1[1], &hr2[1], &hr3[1], &hr4[1], &hr5[1], &hr6[1], &hr7[1], &
	    hr10[1], &hr12[1], &hs2[1], &ht[1], &ibegin, &iend, &dcdt, &dodt, 
	    &dxdt, &dydt, &xc12, &xo16, &x, &z__);
    if (dxdt < 0. && ctlim_1.atime[6] > 0.) {
	deltsh2 = (d__1 = const3_1.csecyr * 1e9 * ctlim_1.atime[6] / dxdt, 
		abs(d__1));
	*deltsh = min(*deltsh,deltsh2);
    }
    return 0;
} /* xtime_ */

