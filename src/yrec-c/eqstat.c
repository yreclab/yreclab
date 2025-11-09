/* eqstat.f -- translated by f2c (version 20061008).
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
    integer ilast, idebug, itrack, ishort, imilne, imodpt, istor, iowr;
} luout_;

#define luout_1 luout_

struct {
    doublereal xenv, zenv, zenvm, amuenv, fxenv[12], xnew, znew, stotal, senv;
} comp_;

#define comp_1 comp_

struct {
    doublereal atime[14], tcut[5], tscut, tenv0, tenv1, tenv, tgcut;
} ctlim_;

#define ctlim_1 ctlim_

struct {
    doublereal cln, clni, c4pi, c4pil, c4pi3l, cc13, cc23, cpi;
} const1_;

#define const1_1 const1_

struct {
    doublereal cgas, ca3, ca3l, csig, csigl, cgl, cmkh, cmkhn;
} const2_;

#define const2_1 const2_

struct {
    doublereal cdh, etadh0, etadh1, zdh[18], xxdy, yydh, zzdh, dhnue[18];
    logical ldh;
} debhu_;

#define debhu_1 debhu_

struct {
    logical lopale;
    integer iopale;
    logical lopale01, lopale06, lnumderiv;
} opaleos_;

#define opaleos_1 opaleos_

struct {
    doublereal fgry, fgrz;
    logical lthoul, ldifz;
} gravs3_;

#define gravs3_1 gravs3_

struct {
    doublereal tlogx[63], tablex[57456]	/* was [63][76][12] */, tabley[57456]	
	    /* was [63][76][12] */, smix[4788]	/* was [63][76] */, tablez[
	    62244]	/* was [63][76][13] */, tablenv[57456]	/* was [63][
	    76][12] */;
    integer nptsx[63];
    logical lscv;
    integer idt, idp;
} scveos_;

#define scveos_1 scveos_

/* Table of constant values */

static doublereal c_b2 = 10.;

/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */

/*   EQSTAT - New front end to equation of state routines */
/*            Provided to allow numerical differentiation of */
/*            current EOS routines by calling old EOS routine */
/*            (now called EQSTAT2) at aappropriated P and T */
/*            points in support of numerical differentiation. */
/*                                                                 LLP  10-22-06 */

/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */
/* Subroutine */ int eqstat_(doublereal *tl, doublereal *t, doublereal *pl, 
	doublereal *p, doublereal *dl, doublereal *d__, doublereal *x, 
	doublereal *z__, doublereal *beta, doublereal *betai, doublereal *
	beta14, doublereal *fxion, doublereal *rmu, doublereal *amu, 
	doublereal *emu, doublereal *eta, doublereal *qdt, doublereal *qdp, 
	doublereal *qcp, doublereal *dela, doublereal *qdtt, doublereal *qdtp,
	 doublereal *qat, doublereal *qap, doublereal *qcpt, doublereal *qcpp,
	 logical *lderiv, logical *latmo, integer *ksaha)
{
    /* Builtin functions */
    double pow_dd(doublereal *, doublereal *), d_lg10(doublereal *);

    /* Local variables */
    static doublereal d1, dl1, dpl, dtl, plo, ppl, tlo, ttl, dpl2, qap1, qcp1,
	     dtl2, qdp1, qdp2, qcp2, qdt1, qdt2, qat1, dela1, qatx, qapx, 
	    dela2, qcpp1, qcpt1, qdtp1, qdtt1, qcppx, qdtpx, qcptx, qdttx;
    static integer ksahax;
    static logical latmox, lderiv2;
    extern /* Subroutine */ int eqstat2_(doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, logical *,
	     logical *, integer *);
    static integer kssahax;


/*  Input Arguments: TL, PL, X, Z, LDERIV, LATMO */

/*  Output Arguments: T, P, D, DL, BETA, BETAI, BETA14, FXION, RMU, AMU, */
/*          EMU, QDT, QDP, QCP, DELA, QDTT, QDTP, QAT, QAP, QCPT, QCPP, */

/*  Update (Input and Output) Arguments: KSAHA */

/*       DIMENSION ATOMWT(4),FXION(3),ATOMW2(12)  ! FX(12)  ! KC 2025-05-31 */
/* DBG 7/92 COMMON BLOCK ADDED TO COMPUTE DEBYE-HUCKEL CORRECTION. */
/* YCK 2/95 OPAL eos */
/* LLP 2001 OPAL eos Mar 2003 */
/* LLP 2006 OPAL eos Oct 2006 */
/* LLP Add Use Numerical Derivatives flag, LNumDeriv   7/07 */
/* MHP 8/25 Remove unused variables */
/*      CHARACTER*256 FOPALE,fopale01,fopale06 */
/* KC 2025-05-30 reordered common block elements */
/*       COMMON/OPALEOS/FOPALE,LOPALE,IOPALE,fopale01,lopale01,fopale06, */
/*      x     lopale06,lNumDeriv */
/* MHP 8/25 Remove file names from common blocks */
/* MHP 3/94 ADDED METAL DIFFUSION */
/* MHP  5/97 ADDED COMMON BLOCK FOR SCV EOS TABLES */
/*       DATA NZP1/12/ */
/*       DATA ATOMWT/0.9921D0,0.24975D0,0.08322D0,0.4995D0/ */
/*       DATA SCALET,SCALES/0.500D0, 2.000D0/ */
/*       DATA ATOMW2/23.0D0,26.99D0,24.32D0,55.86D0,28.1D0,12.015D0, */
/*      *            1.008D0,16.0D0,14.01D0,39.96D0,20.19D0,4.004D0/ */
/*  LDERIV: if true, provide derivatives needed for relaxation, else don't */
/*  LNumDeriv - if true derivatives are calculated numerically. else get */
/*              them the old way using Yale EOS. */
/*              LNumDeriv is part of the PARMIN PHYSICS namelist. */
    /* Parameter adjustments */
    --fxion;

    /* Function Body */
    plo = *pl;
    tlo = *tl;
    latmox = *latmo;
    kssahax = *ksaha;
    if (*lderiv && opaleos_1.lnumderiv) {
/* Get Numerical Derivatives of Current EOS    LLP  8/5/07 */
/* If both derivatives and numerical derivatives are requested. */
/* A central difference approximation using values on both sides of */
/* TL and then PL is used. The error term in this approximation of */
/* the derivatives is of order h**2, where h is the interval. The */
/* error term when one sided derivatives are used is of order h. */
	dpl = .15;
/* the approximate table intervals */
	dtl = .03;
	dpl *= .01;
/* Empirically, scaling the intervals down */
	dtl *= .01;
/* by 100 seemed to work best. */
	dpl2 = dpl * 2.;
	dtl2 = dtl * 2.;
	dl1 = *dl;
/* Initialize DL1 and D1 to called values. */
	d1 = *d__;
/* This can avoid problems in initial table lookups */
	ttl = *tl + dtl;
/* Get derivatives wrt T. */
	*t = pow_dd(&c_b2, &ttl);
	lderiv2 = FALSE_;
	eqstat2_(&ttl, t, pl, p, &dl1, &d1, x, z__, beta, betai, beta14, &
		fxion[1], rmu, amu, emu, eta, &qdt1, &qdp1, &qcp1, &dela1, &
		qdttx, &qdtpx, &qatx, &qapx, &qcptx, &qcppx, &lderiv2, &
		latmox, &ksahax);
	ttl = *tl - dtl;
	*t = pow_dd(&c_b2, &ttl);
	lderiv2 = FALSE_;
	eqstat2_(&ttl, t, pl, p, &dl1, &d1, x, z__, beta, betai, beta14, &
		fxion[1], rmu, amu, emu, eta, &qdt2, &qdp2, &qcp2, &dela2, &
		qdttx, &qdtpx, &qatx, &qapx, &qcptx, &qcppx, &lderiv2, &
		latmox, &ksahax);
	qdtt1 = (qdt1 - qdt2) / dtl2 / const1_1.cln;
	qcpt1 = (d_lg10(&qcp1) - d_lg10(&qcp2)) / dtl2;
	qat1 = (d_lg10(&dela1) - d_lg10(&dela2)) / dtl2;
	*tl = tlo;
	*t = pow_dd(&c_b2, &tlo);
/* Restore original T */
	ppl = *pl + dpl;
	*p = pow_dd(&c_b2, &ppl);
	lderiv2 = FALSE_;
	eqstat2_(tl, t, &ppl, p, &dl1, &d1, x, z__, beta, betai, beta14, &
		fxion[1], rmu, amu, emu, eta, &qdt1, &qdp1, &qcp1, &dela1, &
		qdttx, &qdtpx, &qatx, &qapx, &qcptx, &qcppx, &lderiv2, &
		latmox, &ksahax);
	ppl = *pl - dpl;
	*p = pow_dd(&c_b2, &ppl);
	lderiv2 = FALSE_;
	eqstat2_(tl, t, &ppl, p, &dl1, &d1, x, z__, beta, betai, beta14, &
		fxion[1], rmu, amu, emu, eta, &qdt2, &qdp2, &qcp2, &dela2, &
		qdttx, &qdtpx, &qatx, &qapx, &qcptx, &qcppx, &lderiv2, &
		latmox, &ksahax);
	*pl = plo;
	*p = pow_dd(&c_b2, &plo);
/* Restore original P */
	qdtp1 = (qdt1 - qdt2) / dpl2 / const1_1.cln;
	qcpp1 = (d_lg10(&qcp1) - d_lg10(&qcp2)) / dpl2;
	qap1 = (d_lg10(&dela1) - d_lg10(&dela2)) / dpl2;
	*qdtt = qdtt1;
	*qdtp = qdtp1;
	*qat = qat1;
	*qap = qap1;
	*qcpp = qcpp1;
	*qcpt = qcpt1;
    }
    *tl = tlo;
/* Restore original TL and PL. */
    *pl = plo;
    if (*lderiv && ! opaleos_1.lnumderiv) {
	lderiv2 = TRUE_;
/* Call eqstat2 and request derivatives */
/* Need derivatives and have no numerical ones. */
	eqstat2_(tl, t, pl, p, dl, d__, x, z__, beta, betai, beta14, &fxion[1]
		, rmu, amu, emu, eta, qdt, qdp, qcp, dela, qdtt, qdtp, qat, 
		qap, qcpt, qcpp, &lderiv2, latmo, ksaha);
    } else {
	lderiv2 = FALSE_;
/* or do not need any derivatives. */
/* Call eqstat2 and request no derivatives */
/* We either already have numerical derivatives */
	eqstat2_(tl, t, pl, p, dl, d__, x, z__, beta, betai, beta14, &fxion[1]
		, rmu, amu, emu, eta, qdt, qdp, qcp, dela, &qdttx, &qdtpx, &
		qatx, &qapx, &qcptx, &qcppx, &lderiv2, latmo, ksaha);
/*            Note that the QDTT,QDTP,QAT,QAP,QCPT,QCPP OUTPUTS are to */
/*            dummy variables so they can not affect the previously */
/*            calculated second derivatives. */
    }
    return 0;
} /* eqstat_ */

