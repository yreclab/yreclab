/* ytime.f -- translated by f2c (version 20061008).
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
    doublereal ealpca, enu;
} neweps_;

#define neweps_1 neweps_

struct {
    logical lexcom;
} flag_;

#define flag_1 flag_

/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */
/* YTIME */
/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */
/* Subroutine */ int ytime_(doublereal *eg, doublereal *hcomp, doublereal *hd,
	 doublereal *hl, doublereal *hs1, doublereal *ht, integer *jcore, 
	integer *m, doublereal *deltsy, doublereal *hr1, doublereal *hr2, 
	doublereal *hr3, doublereal *hr4, doublereal *hr5, doublereal *hr6, 
	doublereal *hr7, doublereal *hr8, doublereal *hr9, doublereal *hr10, 
	doublereal *hr11, doublereal *hr12, doublereal *hr13, doublereal *hf1,
	 doublereal *hf2, integer *jxbeg)
{
    /* System generated locals */
    integer i__1;
    doublereal d__1, d__2;

    /* Local variables */
    static doublereal e, x, y, z__, dl;
    static integer it, iu;
    static doublereal tl, xh2, eca, qed, xc12, xc13, qet, xn14, xn15, xo16, 
	    xo17, xo18, xhe3, xbe9, xli6, xli7, sum1, egg11, egg22, egg33, 
	    egg44, egg55;
    extern /* Subroutine */ int engeb_(doublereal *, doublereal *, doublereal 
	    *, doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, integer *,
	     doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *);
    static doublereal htmax;
    static integer itmax;
    static doublereal ycore;

/*      *   HF1,HF2,QDP,QDT,JXBEG)  ! KC 2025-05-31 */
/* MHP 10/02 added missing common block */
/*  STARS WITH A HELIUM LUMINOSITY HAVE A TIMESTEP LIMIT */
/*       BASED ON THE TIME REQUIRED TO BURN ATIME(4) OF Y AT THE */
/*       MAXIMUM IN TEMPERATURE OR THE FRACTION ATIME(5) OF Y AT THIS POINT. */
/* TEST FOR HELIUM FLASH BURNING; HIGH CENTRAL DENSITY IS TAKEN AS */
/* A SIGN THAT THE MODEL IS A GIANT UNDERGOING A HE FLASH RATHER THAN */
/* A HORIZONTAL BRANCH STAR. */
/*       DATA Q3A,QCA/5.85D17,1.7276D18/ */
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
    --hs1;
    --hl;
    --hd;
    hcomp -= 16;
    --eg;

    /* Function Body */
    if (hd[1] >= 5.) {
/*     SEARCH FOR TEMPERATURE MAXIMUM */
	htmax = 0.;
	itmax = 1;
	i__1 = *m;
	for (it = 1; it <= i__1; ++it) {
	    if (ht[it] > htmax) {
		itmax = it;
		htmax = ht[it];
	    }
/* L210: */
	}
/*     CALCULATE HELIUM BURNING RATE AT TMAX */
	dl = hd[itmax];
	tl = ht[itmax];
	x = hcomp[itmax * 15 + 1];
	y = hcomp[itmax * 15 + 2];
	z__ = hcomp[itmax * 15 + 3];
	xhe3 = hcomp[itmax * 15 + 4];
	xc12 = hcomp[itmax * 15 + 5];
	xc13 = hcomp[itmax * 15 + 6];
	xn14 = hcomp[itmax * 15 + 7];
	xn15 = hcomp[itmax * 15 + 8];
	xo16 = hcomp[itmax * 15 + 9];
	xo17 = hcomp[itmax * 15 + 10];
	xo18 = hcomp[itmax * 15 + 11];
	if (flag_1.lexcom) {
	    xh2 = hcomp[itmax * 15 + 12];
	    xli6 = hcomp[itmax * 15 + 13];
	    xli7 = hcomp[itmax * 15 + 14];
	    xbe9 = hcomp[itmax * 15 + 15];
	}
	iu = itmax;
	engeb_(&egg11, &egg22, &egg33, &egg44, &egg55, &qed, &qet, &sum1, &dl,
		 &tl, &x, &y, &xhe3, &xc12, &xc13, &xn14, &xo16, &xo18, &xh2, 
		&iu, &hr1[1], &hr2[1], &hr3[1], &hr4[1], &hr5[1], &hr6[1], &
		hr7[1], &hr8[1], &hr9[1], &hr10[1], &hr11[1], &hr12[1], &hr13[
		1], &hf1[1], &hf2[1]);
/*      *        TL,QDT,QDP,X,Y,Z,XHE3,XC12,XC13,XN14,XN15,XO16,XO17, */
/*      *        XO18,XH2,XLI6,XLI7,XBE9,IU,HR1,HR2,HR3,HR4,HR5,HR6,HR7,  ! KC 2025-05-31 */
	e = sum1;
	eg[1] = egg11;
	eg[2] = egg22;
	eg[3] = egg33;
	eg[4] = egg44;
	eg[5] = egg55;
	eg[6] = neweps_1.enu;
	eca = neweps_1.ealpca;
	if (eg[5] < 1e-22) {
	    eg[5] = 1e-22;
	}
	*deltsy = 1e15 / eg[5];
    } else {
/* SET LIMITS ON HE BURNING FOR NON-HELIUM FLASH STARS */
	ycore = 1. - hcomp[*jcore * 15 + 3];
	if (ycore >= ctlim_1.atime[0]) {
/* Computing MIN */
	    d__1 = ctlim_1.atime[3], d__2 = ctlim_1.atime[4] * ycore;
	    *deltsy = min(d__1,d__2);

	    *deltsy = 5.85e17 / const_1.clsun * *deltsy * (hs1[*jcore] / hl[*
		    jcore]);
	} else {
	    *deltsy = 5.85e17 / const_1.clsun * *deltsy * (hs1[*jxbeg - 1] / 
		    hl[*jxbeg - 1]);

	}

    }
    return 0;
} /* ytime_ */

