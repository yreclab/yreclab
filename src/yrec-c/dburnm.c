/* dburnm.f -- translated by f2c (version 20061008).
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
    doublereal dmdt0, fczdmdt, ftotdmdt, compacc[15], creim;
    logical lreimer, lmdot;
} masschg_;

#define masschg_1 masschg_

struct {
    doublereal hpo[5000], hto[5000], hro[5000], hlo[5000], hdo[5000], hcompp[
	    75000]	/* was [15][5000] */, hss[5000];
    logical lco[5000], lczo[5000];
    doublereal tefflo;
    integer mo;
} oldmod_;

#define oldmod_1 oldmod_

/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */
/* DBURN - COMPUTE THE ABUNDANCE CHANGES RESULTING FROM DEUTERIUM BURNING */
/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */
/* Subroutine */ int dburnm_(integer *ibegin, integer *iend, integer *m, 
	doublereal *hs2, doublereal *hcomp, doublereal *dt, doublereal *
	dratem, doublereal *dratem0, doublereal *fac2)
{
    /* System generated locals */
    integer i__1;

    /* Builtin functions */
    double exp(doublereal);

    /* Local variables */
    static integer i__;
    static doublereal x, r0, xn, xh2, dtt, dxh2, xhe3, xh2n, rate, summ, 
	    dxh2a, rate0, rate1, xh2na, dxh2o, xhe3n, xh2no, x2new, sumr0, 
	    sumr1, fstep;
    static integer istep;
    static doublereal tstep, fmassa, xh2nacc, delrate;

/*       DATA C21/5.240358E-8/ */
    /* Parameter adjustments */
    --dratem0;
    --dratem;
    hcomp -= 16;
    --hs2;

    /* Function Body */
    dtt = *dt * 1e-9 / const3_1.csecyr;
    if (*ibegin == *iend) {
	x = oldmod_1.hcompp[*ibegin * 15 - 15];
	xh2 = oldmod_1.hcompp[*ibegin * 15 - 4];
	xhe3 = oldmod_1.hcompp[*ibegin * 15 - 12];
	rate0 = dratem0[*ibegin];
	rate1 = dratem[*ibegin];
    } else {
	summ = 0.;
	sumr0 = 0.;
	sumr1 = 0.;
	x = 0.;
	xh2 = 0.;
	xhe3 = 0.;
	i__1 = *iend;
	for (i__ = *ibegin; i__ <= i__1; ++i__) {
	    summ += hs2[i__];
	    sumr0 += hs2[i__] * dratem0[i__];
	    sumr1 += hs2[i__] * dratem[i__];
	    x += oldmod_1.hcompp[i__ * 15 - 15] * hs2[i__];
	    xh2 += oldmod_1.hcompp[i__ * 15 - 4] * hs2[i__];
	    xhe3 += oldmod_1.hcompp[i__ * 15 - 12] * hs2[i__];
	}
	rate0 = sumr0 / summ;
	rate1 = sumr1 / summ;
	x /= summ;
	xh2 /= summ;
	xhe3 /= summ;
    }
    if (xh2 < 1e-14) {
	i__1 = *iend;
	for (i__ = *ibegin; i__ <= i__1; ++i__) {
	    hcomp[i__ * 15 + 12] = 0.;
	}
	goto L9999;
    }
/* BURN DEUTERIUM IN A SERIES OF SMALL STEPS, */
/* INCREMENTING THE BURNING RATE FROM THE STARTING */
/* TO ENDING VALUES. */
/* RESTRICT THE MAXIMUM BURNING TO 0.5 IN THE */
/* NATURAL LOG (<1% ERROR FROM A SIMPLE SUM */
/* OF DISCRETE STEPS OF THIS SIZE). */
/* MHP 10/02 INITIALIZE RATE */
    rate = max(rate0,rate1);
    istep = (integer) (rate * dtt / .1) + 1;
    fstep = (doublereal) istep;
    tstep = dtt / fstep;
    r0 = rate0;
    delrate = (rate1 - rate0) / fstep;
    xh2no = xh2;
    i__1 = istep;
    for (i__ = 1; i__ <= i__1; ++i__) {
	rate = r0 + delrate * .5;
	xh2no *= exp(rate * -2. * tstep);
	r0 += delrate;
    }
/* INCLUDE MASS ACCRETION FROM DEUTERIUM BURNING */
    if (masschg_1.lmdot && *iend == *m) {
/* ACCRETED MATTER IS EXPOSED TO BURNING FOR, ON */
/* AVERAGE. 1/2 OF THE TIMESTEP.  FMASSACC IS */
/* DEFINED AS DMDT*DT/ORIGINAL CZ MASS. */
/* BURN BOTH THE ACCRETED D AND THE ORIGINAL D */
/* SEPARATELY AND FIND THE NEW MASS-WEIGHTED */
/* AVERAGE D.  NOTE THAT ACCRETION OF ELEMENTS */
/* 1-11 HAS ALREADY BEEN TREATED. */
	r0 = rate0;
	xh2nacc = masschg_1.compacc[11];
	xh2na = 0.;
	i__1 = istep;
	for (i__ = 1; i__ <= i__1; ++i__) {
	    rate = r0 + delrate * .5;
/* FULLY BURN PRIOR ACCRETED MATTER */
	    xh2na *= exp(rate * -2. * tstep);
/* EXPOSE NEWLY ACCRETED MATTER TO 1/2 BURNING */
	    x2new = xh2nacc / fstep * exp(-rate * tstep);
	    xh2na += x2new;
	    r0 += delrate;
	}
/* NOW PERFORM A WEIGHTED SUM OF THE ORIGINAL */
/* AND NEWLY ACCRETED MATTER */
/* UNLIKE THE ROUTINE CALLED BY MIX, THE TIMESTEP */
/* HERE IS ONLY A PORTION OF THE TOTAL MODEL DT. */
/* DO ONLY THE SMALLER TIMESTEP PORTION OF THE */
/* TOTAL MASS ACCRETION. */
	fmassa = *fac2 * deuter_1.fmassacc;
	dxh2o = xh2no - xh2;
	dxh2a = xh2na - masschg_1.compacc[11];
	xh2n = (xh2no + xh2na * fmassa) / (fmassa + 1.);
	xn = x + (dxh2o + dxh2a * fmassa) * .5 / (fmassa + 1.);
	xhe3n = xhe3 - (dxh2o + dxh2a * fmassa) * 1.5 / (fmassa + 1.);
/*      IF(IEND.EQ.M)THEN */
/*      WRITE(*,911)IBEGIN,IEND,DRATEM0(IBEGIN),RATE0,RATE1,XH2,XH2N, */
/*     *            XHE3,XHE3N */
/*      ENDIF */
/* 911  FORMAT('DBURNM: MIDMOD Deuterium Burning #1', 2I5,1P7E12.3) */
    } else {
/* INCREMENT H,D,HE3 WITHOUT MASS ACCRETION */
	dxh2 = xh2no - xh2;
	xh2n = xh2no;
	xn = x + dxh2 * .5;
	xhe3n = xhe3 - dxh2 * 1.5;
/*      IF(IEND.EQ.M)THEN */
/*      WRITE(*,912)IBEGIN,IEND,DRATEM0(IBEGIN),RATE0,RATE1,XH2,XH2N, */
/*     *            XHE3,XHE3N */
/* 912  FORMAT('DBURNM: MIDMOD Deuterium Burning #2', 2I5,1P7E12.3) */
/*      ENDIF */
    }
    i__1 = *iend;
    for (i__ = *ibegin; i__ <= i__1; ++i__) {
	hcomp[i__ * 15 + 1] = xn;
	hcomp[i__ * 15 + 4] = xhe3n;
	hcomp[i__ * 15 + 12] = xh2n;
    }
L9999:
    return 0;
} /* dburnm_ */

