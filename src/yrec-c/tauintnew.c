/* tauintnew.f -- translated by f2c (version 20061008).
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
    doublereal xenv, zenv, zenvm, amuenv, fxenv[12], xnew, znew, stotal, senv;
} comp_;

#define comp_1 comp_

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
    doublereal wnew, walpcz, acfpft;
    integer itfp1, itfp2;
    logical lrot, linstb, lwnew;
} rot_;

#define rot_1 rot_

struct {
    doublereal cgas, ca3, ca3l, csig, csigl, cgl, cmkh, cmkhn;
} const2_;

#define const2_1 const2_

struct {
    doublereal clsun, clsunl, clnsun, cmsun, cmsunl, crsun, crsunl, cmbol;
} const_;

#define const_1 const_

struct {
    doublereal cln, clni, c4pi, c4pil, c4pi3l, cc13, cc23, cpi;
} const1_;

#define const1_1 const1_

struct {
    integer imax1, imax2;
    logical ljvs;
} jtest_;

#define jtest_1 jtest_

struct {
    doublereal envp[5000], envt[5000], envs[5000], envd[5000], envr[5000], 
	    envx[5000], envz[5000];
    logical lcenv[5000];
    doublereal edels[15000]	/* was [3][5000] */, evels[5000], ebetas[5000]
	    , egam1[5000], eqcp[5000], efxions[15000]	/* was [3][5000] */, 
	    envo[5000], envl[5000], eqdt[5000];
    integer numenv;
} envstruct_;

#define envstruct_1 envstruct_

/* Table of constant values */

static doublereal c_b9 = 0.;

/* $$$$$$ */
/*       RECURSIVE SUBROUTINE TAUINTNEW(HCOMP,HS2,HS1,LCZ,HR,HP,HD,HG,M,MINT,SVEL, */
/*      *                     DEL1,DEL2,HSTOT,RBCZ)  ! KC 2025-05-31 */
/* Subroutine */ int tauintnew_(doublereal *hs1, logical *lcz, doublereal *hr,
	 doublereal *hp, doublereal *hd, doublereal *hg, integer *m, integer *
	mint, doublereal *svel, doublereal *del1, doublereal *del2, 
	doublereal *rbcz)
{
    /* System generated locals */
    integer i__1;
    doublereal d__1;

    /* Builtin functions */
    double exp(doublereal), d_lg10(doublereal *);

    /* Local variables */
    static logical lradzone;
    static integer i__, j, k, kk;
    static doublereal fx, dd1, dd2;
    static integer ibeg;
    static doublereal psca, cvel, delr, xdel[4], xrad[4], yrad[4];
    static integer imax, jmax;
    static doublereal yvel[4], ypsc[4], yspl[4];
    static integer itop;
    static doublereal rtcz, psca1, psca2;
    static integer jcore, ijmax;
    static doublereal hsbot, hstop, rtest, rtest1, rtest2;
    static logical lallcz;
    static doublereal envrcl;
    static logical lczsur;
    extern /* Subroutine */ int kspline_(doublereal *, doublereal *, 
	    doublereal *);
    static doublereal valtest;
    extern /* Subroutine */ int ksplint_(doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *);

/* Needs access to this common block: grants knowledge of envellope */
/* KC 2025-05-30 reordered common block elements */
/* JvS 08/25 Updated with new elements */
/*       DIMENSION HCOMP(15,JSON),HS2(JSON),LCZ(JSON),  ! KC 2025-05-31 */
/* G Somers; Adding vectors for cubic spline int. */
/* XSUM(15) */

/* G Somers 3/17, IMPLEMENTING NEW TAUCZ METHOD. */
/* THE METHOD WORKS AS FOLLOWS. SEARCH FROM THE CENTER OF THE STAR UP UNTIL YOU */
/* FIND THE BASE OF THE SURFACE CONVECTION ZONE. THEN SEARCH FROM THE SURFACE */
/* DOWN UNTIL YOU FIND THE SAME. IF BOTH DIRECTIONS GIVE SAME ANSWER, THEN */
/* SURFACE CONVECTION ZONE IS UNIQUE, AND THE OLD TOP-DOWN SINKLINE METHOD CAN */
/* BE EMPLOYED. IF THEY ARE DIFFERENT, THEN MULTIPLE SURFACE CONVECTION CELLS */
/* EXIST. IN THIS CASE, DETERMINE THE CROSSING TIME OF THE LOWEST CONVECTION */
/* CELL IN THE ENVELOPE. */

/* IMAX: BASE OF THE MAIN INTERNAL CONVECTION ZONE. */
/* JMAX: BASE OF THE UPPER-MOST CONVECTION ZONE. */
/* RBCZ: RADIUS AT WHICH THE BCZ EXISTS */
/* TAUCZ: OVERTURN TIMESCALE */

/* DETERMINE EXTENT OF SURFACE CONVECTION ZONE. */
    /* Parameter adjustments */
    --del2;
    --del1;
    --svel;
    --hg;
    --hd;
    --hp;
    --hr;
    --lcz;
    --hs1;

    /* Function Body */
    lallcz = FALSE_;
/* FIND THE TOP OF THE MAIN INTERNAL CONVECTION ZONE. */
    ibeg = 1;
L50:
    lradzone = TRUE_;
    if (lcz[ibeg]) {
	lradzone = FALSE_;
    }
    i__1 = *m;
    for (i__ = ibeg; i__ <= i__1; ++i__) {
	if (! lradzone && ! lcz[i__]) {
	    jcore = i__ - 1;
	    lradzone = TRUE_;
	}
	if (lradzone && lcz[i__]) {
	    goto L70;
	}
/* L60: */
    }
/* IF THE CODE GETS HERE, EITHER THE STAR IS FULLY CONVECTIVE, OR */
/* HAS A COMPLETELY RADIATIVE ENVLOPE, MAYBE WITH A CONVECTIVE CORE. */
    if (lradzone) {
/* RADIATIVE ENVELOPE */
	lallcz = FALSE_;
	lczsur = FALSE_;
	imax = *m;
	jmax = *m;
	jcore = *m;
	goto L100;
    } else {
/* FULLY CONVECTIVE */
	lallcz = TRUE_;
	lczsur = TRUE_;
	i__ = 1;
	j = 0;
	jcore = 1;
	goto L90;
    }
L70:
/* FIND THE BASE OF THE UPPER-MOST CONVECTION ZONE */
    for (j = *m - 1; j >= 1; --j) {
	if (! lcz[j]) {
	    goto L90;
	}
/* L80: */
    }
L90:
    imax = i__;
    jmax = j + 1;
    ijmax = jmax - imax;
/* LOCATING THE CORRECT CZ INCURES VARIOUS PATHOLOGIES. TRAP THEM OUT. */

/* ENSURE THIS CZ IS SUFFICIENTLY FAR FROM THE CONVECTIVE CORE. IN SOME CASES */
/* THERE ARE A FEW SHELLS RIGHT ABOVE THE CORE THAT ARE CONVECTIVE. SKIP THESE. */
/* KC 2025-05-30 ADDED IF CHECK TO AVOID RUNTIME ERROR. */
    if (imax > 0 && jcore > 0) {
	if (*m != *mint && hp[jcore] - hp[imax] < 1.) {
	    ibeg = imax + 1;
	    goto L50;
	}
    }
/* ENSURE THIS CZ IS AT LEAST 3 SHELLS THICK. IF NOT, WE ARE LIKELY SNAGGED */
/* ON A SINGLE SHELL CONV ZONE DEEP IN THE INTERIOR. RECOMMENSE SEARCH FROM */
/* ABOVE THIS SHELL. */
    if (! (lcz[imax] && lcz[imax + 1] && lcz[imax + 2])) {
	if (! lcz[imax + 1]) {
	    ibeg = imax + 1;
	} else {
	    ibeg = imax + 2;
	}
	goto L50;
    }
/* IN THE CASE WHERE ONLY THE INTERIOR MODEL IS CONSIDERED, USE JMAX. */
    if (ijmax != 0 && *m == *mint) {
	imax = jmax;
	ijmax = 0;
    }
/*  HSTOP IS THE MASS AT THE TOP OF THE C.Z. */
/*  HSBOT IS THE MASS AT THE BOTTOM OF THE C.Z. */
    hstop = hs1[*m];
    if (jmax > 1) {
	hsbot = (hs1[jmax] + hs1[jmax - 1]) * .5;
    } else {
	hsbot = 0.;
    }
/*  LCZSUR=T IF A SURFACE C.Z.DEEP ENOUGH FOR ANGULAR MOMENTUM LOSS EXISTS */
    if ((hstop - hsbot) / const_1.cmsun > 0.) {
	lczsur = TRUE_;
    } else {
	lczsur = FALSE_;
    }
L100:
/* CALCULATE TAUCZ TOP DOWN FOR FULLY AND PARTIALLY CONVECTIVE. FOR A FULLY */
/* RADIATIVE ENVELOPE, SET TAUCZ = 0.0. */
    if (lczsur) {
/* INFER RBCZ, THE RADIUS AT THE BASE OF THE SURFACE CZ. */
	if (lallcz) {
/*           SET TO CENTER OF STAR, I.E. A VERY SMALL NUMBER */
/*           IN CGS UNITS, RELATIVE TO THE RADII OF STARS. */
	    *rbcz = 1.f;
	} else {
/*           PINPOINT RCZ LINEARLY */
	    dd2 = del1[imax - 1] - del2[imax - 1];
	    dd1 = del1[imax] - del2[imax];
	    fx = dd2 / (dd2 - dd1);
	    *rbcz = hr[imax - 1] + fx * (hr[imax] - hr[imax - 1]);
	}
	*rbcz = exp(const1_1.cln * *rbcz);
/*        IF THERE ARE MULTIPLE CONVECTION CELLS IN THE PREDOMINATELY */
/*        RADIATIVE ENVELOPE, USE AVERAGING METHOD. */
	if (ijmax != 0) {
	    goto L110;
	}
/* CALCULATE HP */
	psca2 = exp(const1_1.cln * (hp[imax] - hd[imax])) / hg[imax];
	rtest2 = exp(const1_1.cln * hr[imax]) - *rbcz;
	valtest = rtest2 - psca2;
	if (valtest > 0.f) {
/* INNER MOST POINT PSCA IS BELOW BCZ */
	    k = imax;
	    cvel = svel[imax];
	    psca = psca2;
	    ovrtrn_1.taucz = psca / cvel;
	} else {
	    i__1 = *m - 1;
	    for (k = imax + 1; k <= i__1; ++k) {
		psca1 = psca2;
		rtest1 = rtest2;
		psca2 = exp(const1_1.cln * (hp[k] - hd[k])) / hg[k];
		rtest2 = exp(const1_1.cln * hr[k]) - *rbcz;
		valtest = rtest2 - psca2;
/*              FIND LOCATION WHERE HP = R */
		if (valtest > 0.f) {
/*                 IF K = IMAX+1, MOVE AWAY FROM EDGE CASE. */
		    kk = k;
		    if (k == imax + 1) {
			kk = k + 1;
		    }
/*                 FIND V WITH CUBIC SPLINE */
		    xdel[0] = exp(const1_1.cln * hr[kk - 2]) - *rbcz - exp(
			    const1_1.cln * (hp[kk - 2] - hd[kk - 2])) / hg[kk 
			    - 2];
		    xdel[1] = exp(const1_1.cln * hr[kk - 1]) - *rbcz - exp(
			    const1_1.cln * (hp[kk - 1] - hd[kk - 1])) / hg[kk 
			    - 1];
		    xdel[2] = exp(const1_1.cln * hr[kk]) - *rbcz - exp(
			    const1_1.cln * (hp[kk] - hd[kk])) / hg[kk];
		    xdel[3] = exp(const1_1.cln * hr[kk + 1]) - *rbcz - exp(
			    const1_1.cln * (hp[kk + 1] - hd[kk + 1])) / hg[kk 
			    + 1];
		    yvel[0] = svel[kk - 2];
		    yvel[1] = svel[kk - 1];
		    yvel[2] = svel[kk];
		    yvel[3] = svel[kk + 1];
		    kspline_(xdel, yvel, yspl);
		    ksplint_(xdel, yvel, yspl, &c_b9, &cvel);
		    ypsc[0] = exp(const1_1.cln * (hp[kk - 2] - hd[kk - 2])) / 
			    hg[kk - 2];
		    ypsc[1] = exp(const1_1.cln * (hp[kk - 1] - hd[kk - 1])) / 
			    hg[kk - 1];
		    ypsc[2] = exp(const1_1.cln * (hp[kk] - hd[kk])) / hg[kk];
		    ypsc[3] = exp(const1_1.cln * (hp[kk + 1] - hd[kk + 1])) / 
			    hg[kk + 1];
		    kspline_(xdel, ypsc, yspl);
		    ksplint_(xdel, ypsc, yspl, &c_b9, &psca);
		    yrad[0] = hr[kk - 2];
		    yrad[1] = hr[kk - 1];
		    yrad[2] = hr[kk];
		    yrad[3] = hr[kk + 1];
		    kspline_(xdel, yrad, yspl);
		    ksplint_(xdel, yrad, yspl, &c_b9, &envrcl);
/* DEFINE TAUCZ */
		    ovrtrn_1.taucz = psca / cvel;
		    goto L140;
		}
	    }
/* KC 2025-05-31 MOVED ENDIF HERE TO AVOID BLOCK MISMATCH. */
	}
L110:
/* IF CODE GETS HERE, THEN 1 PSCA ABOVE THE BCZ IS OUTSIDE OF THE STAR, */
/* OR MULTIPLE CONVECTION CELLS RESIDE WITHIN THE RADIATIVE ENVELOPE. */
/* IN THIS CASE, EVALUATE CVEL AT CENTER OF BOTTOM CZ. FIRST, FIND UPPER EDGE. */
	i__1 = *m - 1;
	for (k = imax; k <= i__1; ++k) {
	    if (! lcz[k]) {
		goto L120;
	    }
	}
L120:
	itop = k - 1;
/* PINPOINT TOP OF CZ LINEARLY */
	dd2 = del1[itop] - del2[itop];
	dd1 = del1[itop + 1] - del2[itop + 1];
	fx = dd2 / (dd2 - dd1);
	rtcz = hr[itop] + fx * (hr[itop + 1] - hr[itop]);
	rtcz = exp(const1_1.cln * rtcz);
/* CALCULATE WIDTH OF THE CONVECTION CELL */
	delr = rtcz - *rbcz;
/* FIND INDICES SURROUNDING LINEAR CENTER OF CZ */
	d__1 = *rbcz + delr * .5f;
	rtest = d_lg10(&d__1);
	i__1 = itop + 1;
	for (k = imax; k <= i__1; ++k) {
	    if (hr[k] > rtest) {
		goto L130;
	    }
	}
L130:
	rtest = exp(const1_1.cln * rtest);
/*           IF K = IMAX+1, MOVE AWAY FROM EDGE CASE. */
	kk = k;
	if (k == imax + 1) {
	    kk = k + 1;
	}
/* CALCULATE CVEL AT THAT CENTRAL LOCATION */
	xrad[0] = exp(const1_1.cln * hr[kk - 2]);
	xrad[1] = exp(const1_1.cln * hr[kk - 1]);
	xrad[2] = exp(const1_1.cln * hr[kk]);
	xrad[3] = exp(const1_1.cln * hr[kk + 1]);
	yvel[0] = svel[kk - 2];
	yvel[1] = svel[kk - 1];
	yvel[2] = svel[kk];
	yvel[3] = svel[kk + 1];
	kspline_(xrad, yvel, yspl);
	ksplint_(xrad, yvel, yspl, &rtest, &cvel);
/* DEFINE TAUCZ */
	ovrtrn_1.taucz = delr / cvel;
L140:
/* KC 2025-05-31 MOVED ENDIF ABOVE TO AVOID BLOCK MISMATCH. */
/*          ENDIF */
/*        CONVERT CORE RADIUS INTO SOLAR UNITS */
	*rbcz /= const_1.crsun;
    } else {
	ovrtrn_1.taucz = 0.;
	*rbcz = 0.f;
    }
/*     ENSURE THAT TAUCZ WAS NOT ACCIDENTALLY CALCULATED */
/*     DEEP IN THE STELLAR INTERIOR. IF YES, REDO CALCULATION. */
    if (ovrtrn_1.taucz > 1e20f) {
	ibeg = imax + 1;
	goto L50;
    }
    return 0;
} /* tauintnew_ */

