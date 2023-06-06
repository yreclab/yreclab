/* eqstat2.f -- translated by f2c (version 20100827).
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
    char fopale[256];
    logical lopale;
    integer iopale;
    char fopale01[256];
    logical lopale01;
    char fopale06[256];
    logical lopale06, lnumderiv;
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

static integer c__9 = 9;
static integer c__1 = 1;
static integer c__5 = 5;
static doublereal c_b17 = 10.;



/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */
/* EQSTAT */
/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */
/* Subroutine */ int eqstat2_(doublereal *tl, doublereal *t, doublereal *pl, 
	doublereal *p, doublereal *dl, doublereal *d__, doublereal *x, 
	doublereal *z__, doublereal *beta, doublereal *betai, doublereal *
	beta14, doublereal *fxion, doublereal *rmu, doublereal *amu, 
	doublereal *emu, doublereal *eta, doublereal *qdt, doublereal *qdp, 
	doublereal *qcp, doublereal *dela, doublereal *qdtt, doublereal *qdtp,
	 doublereal *qat, doublereal *qap, doublereal *qcpt, doublereal *qcpp,
	 logical *lderiv, logical *latmo, integer *ksaha)
{
    /* Initialized data */

    static integer nzp1 = 12;
    static doublereal atomwt[4] = { .9921,.24975,.08322,.4995 };
    static doublereal scalet = .5;
    static doublereal scales = 2.;
    static doublereal atomw2[12] = { 23.,26.99,24.32,55.86,28.1,12.015,1.008,
	    16.,14.01,39.96,20.19,4.004 };

    /* System generated locals */
    integer i__1;
    doublereal d__1, d__2;

    /* Builtin functions */
    double exp(doublereal);
    integer s_wsle(cilist *), do_lio(integer *, integer *, char *, ftnlen), 
	    e_wsle(void);
    double pow_dd(doublereal *, doublereal *), d_lg10(doublereal *);

    /* Local variables */
    extern /* Subroutine */ int eqbound01_(doublereal *, doublereal *, 
	    doublereal *, doublereal *, logical *, logical *), eqbound06_(
	    doublereal *, doublereal *, doublereal *, doublereal *, logical *,
	     logical *);
    static integer i__;
    static doublereal d1, z0, fx[12], dl0, dl1, r1a, wt0, fac, raa, d10o, dpl,
	     rat, fmu, dtl, ppl, doo, dxx, dyy, ttl, wts, dpl2, dfx1, qap1, 
	    qcp1, dfx4, qdp1, qdp2, qcp2, qdt1, qdt2, dtl2, qat1, qdt0, qdp0, 
	    qcp0, qat0, qap0, wts2;
    static logical ltab;
    static doublereal dfx12, amui, amuo, qcpo, qdpo, emuo, dela1, dela2, 
	    dela0, rmuo, qdto, qcpp0, qcpp1, qcpt0, qcpt1, qdtp1, qdtp0, 
	    qdtt1, qdtt0;
    static logical lcalc;
    static doublereal delao;
    static logical lsaha;
    static doublereal betao;
    static logical lscvd, lramp;
    extern /* Subroutine */ int oeqos_(doublereal *, doublereal *, doublereal 
	    *, doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *);
    static logical lcalc1, lcalc2;
    static doublereal beta14o;
    extern /* Subroutine */ int eqsaha_(doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, logical *,
	     logical *, doublereal *, doublereal *, doublereal *, doublereal *
	    , doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, integer *);
    static doublereal betaio;
    extern /* Subroutine */ int eqscve_(doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, logical *), oeqos01_(doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *), oeqos06_(doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *), eqrelv_(doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *);
    static logical lonlys;
    extern /* Subroutine */ int eqbound_(doublereal *, doublereal *, 
	    doublereal *, doublereal *, logical *, logical *);

    /* Fortran I/O blocks */
    static cilist io___21 = { 0, 0, 0, 0, 0 };



/*  Input Arguments: TL, PL, X, Z, LDERIV, LATMO */

/*  Output Arguments: T, P, D, DL, BETA, BETAI, BETA14, FXION, RMU, AMU, */
/*          EMU, QDT, QDP, QCP, DELA, QDTT, QDTP, QAT, QAP, QCPT, QCPP, */

/*  Update (Input and Output) Arguments: KSAHA */

/* DBG 7/92 COMMON BLOCK ADDED TO COMPUTE DEBYE-HUCKEL CORRECTION. */
/* YCK 2/95 OPAL eos */
/* LLP 2001 OPAL eos */
/* LLP 2006 OPAL eos */
/* LLP Add Use Numerical Derivatives flag, LNumDeriv   7/07 */
/* MHP 3/94 ADDED METAL DIFFUSION */
/* MHP  5/97 ADDED COMMON BLOCK FOR SCV EOS TABLES */
    /* Parameter adjustments */
    --fxion;

    /* Function Body */
/* LSAHA = T IF T LOW ENOUGH TO REQUIRE CALL TO EQSAHA TO SOLVE */
/* SAHA IONIZATION EQUATION. IF LSAHA = F, FULLY IONIZED GAS ASSUMED. */
/* LONLYS = T IF SAHA EQUATION MUST BE SOLVED BUT RELATIVISTIC */
/* EQUATION OF STATE NOT NEEDED. */
/* L9: */
    lsaha = *tl < ctlim_1.tscut;
    lonlys = *tl <= ctlim_1.tscut - scalet;
/* MHP 3/94 METAL DIFFUSION ADDED.  ASSUME ALL METALS SCALE EQUALLY. */
    z0 = *z__;
    if (gravs3_1.ldifz) {
/* THE VECTOR FXENV IS DEFINED IN STARIN AS */
/* (MASS FRACTION OF SPECIES/ATOMIC WT/AMUENV) FOR THE COMPOSITION */
/* XENV,ZENV. */
/* AND AMU IS DEFINED AS THE SUM OF THE MASS FRACTIONS DIVIDED BY THEIR */
/* ATOMIC WEIGHTS.  FOR METAL DIFFUSION, ALL THE METALS ARE ASSUMED TO */
/* CHANGE EQUALLY. */
	rat = *z__ / comp_1.zenv;
	r1a = (rat - 1.) * comp_1.amuenv;
	*amu = comp_1.amuenv;
	for (i__ = 1; i__ <= 6; ++i__) {
	    *amu += r1a * comp_1.fxenv[i__ - 1];
	}
	dxx = (*x - comp_1.xenv) / atomw2[6];
	*amu += dxx;
	for (i__ = 8; i__ <= 11; ++i__) {
	    *amu += r1a * comp_1.fxenv[i__ - 1];
	}
	dyy = (comp_1.xenv + comp_1.zenv - *x - *z__) / atomw2[11];
	*amu += dyy;
	raa = rat * comp_1.amuenv / *amu;
	if (lsaha) {
	    for (i__ = 1; i__ <= 6; ++i__) {
		fx[i__ - 1] = raa * comp_1.fxenv[i__ - 1];
	    }
	    fx[6] = (comp_1.fxenv[6] * comp_1.amuenv + dxx) / *amu;
	    for (i__ = 8; i__ <= 11; ++i__) {
		fx[i__ - 1] = raa * comp_1.fxenv[i__ - 1];
	    }
	    fx[11] = (comp_1.fxenv[11] * comp_1.amuenv + dyy) / *amu;
	}
    } else {
/* SET UP FRACTIONAL ABUNDANCES */
	dfx1 = *x - comp_1.xenv;
	dfx12 = *z__ - comp_1.zenv;
	if (abs(dfx1) + abs(dfx12) < 1e-5) {
/* USE ENVELOPE ABUNDANCES */
	    *amu = comp_1.amuenv;
	    if (lsaha) {
		i__1 = nzp1;
		for (i__ = 1; i__ <= i__1; ++i__) {
		    fx[i__ - 1] = comp_1.fxenv[i__ - 1];
/* L10: */
		}
	    }
	} else {
	    dfx1 *= atomwt[0];
	    dfx12 *= atomwt[2];
	    dfx4 = (comp_1.xenv + comp_1.zenv - *x - *z__) * atomwt[1];
/* ASSUME EXCESS Z(METALS) IS IN THE FORM OF CARBON(12) */
	    *amu = comp_1.amuenv + dfx1 + dfx4 + dfx12;
	    amui = 1. / *amu;
	    if (lsaha) {
		fmu = comp_1.amuenv * amui;
		i__1 = nzp1;
		for (i__ = 1; i__ <= i__1; ++i__) {
		    fx[i__ - 1] = fmu * comp_1.fxenv[i__ - 1];
/* L20: */
		}
		fx[5] += dfx12 * amui;
		fx[6] += dfx1 * amui;
		fx[11] += dfx4 * amui;
	    }
	}
    }
/* COMPUTE RADIATION PRESSURE */
    *t = exp(const1_1.cln * *tl);
    *p = exp(const1_1.cln * *pl);
/* Computing 2nd power */
    d__2 = *t;
/* Computing 2nd power */
    d__1 = d__2 * d__2;
    *beta14 = const2_1.ca3 * (d__1 * d__1) / *p;
    *beta = 1 - *beta14;
    if (*beta < 0.) {
	io___21.ciunit = luout_1.ishort;
	s_wsle(&io___21);
	do_lio(&c__9, &c__1, "EQSTAT2: BETA is negative: TL,PL,BETA,1-BETA", (
		ftnlen)44);
	do_lio(&c__5, &c__1, (char *)&(*tl), (ftnlen)sizeof(doublereal));
	do_lio(&c__5, &c__1, (char *)&(*pl), (ftnlen)sizeof(doublereal));
	do_lio(&c__5, &c__1, (char *)&(*beta), (ftnlen)sizeof(doublereal));
	d__1 = 1. - *beta;
	do_lio(&c__5, &c__1, (char *)&d__1, (ftnlen)sizeof(doublereal));
	e_wsle();
    }
    *betai = 1. / *beta;
    *beta14 = *betai * 4. * min(1.,*beta14);
    *eta = 0.;
    if (! lsaha) {
/* COMPUTE VALUES FOR FULLY IONIZED GAS AND RETURN */
	*emu = *x * atomwt[0] + (1. - *x) * atomwt[3];
	*rmu = const2_1.cgas * (*amu + *emu);
	fxion[1] = 1.;
	fxion[2] = 0.;
	fxion[3] = 1.;
	eqrelv_(tl, t, pl, p, dl, d__, beta, amu, emu, eta, qdt, qdp, qcp, 
		dela, qdtt, qdtp, qat, qap, qcpt, qcpp, x);
	goto L200;
    }
/* CHECK IF SAUMON, CHABRIER, AND VAN HORN EQUATION OF STATE NEEDED. */
/* THIS EOS REPLACES THE CALL TO EQSAHA, EXCEPT FOR DERIVATIVE PURPOSES. */
    if (scveos_1.lscv) {
	eqsaha_(fx, tl, t, pl, p, dl, d__, beta, betai, beta14, &fxion[1], 
		rmu, amu, emu, lderiv, latmo, qdt, qdp, qcp, dela, qdtt, qdtp,
		 qat, qap, qcpt, qcpp, ksaha);
	eqscve_(tl, t, pl, p, dl, d__, x, z__, beta, betai, beta14, &fxion[1],
		 rmu, amu, emu, eta, qdt, qdp, qcp, dela, &lcalc);
	lscvd = FALSE_;
/* Do not do SCV derivatives */
	if (lscvd && lcalc) {
/*  LLP 9/6/03 To get reasonable accuracy in numerical derivatives in */
/* 	the 4-5 decimal place SCV tables, appropriate sizes for the */
/* 	stepouts in the numerical derivatives must be obtained.  The */
/* 	row to row and column to column spacings are .20 in PL and */
/* 	.08 in TL. Maximum row to row changes are of the order of */
/* 	0.2000 out of 10.0000 (in density).  Maximum column to column */
/*       changes changes are of the order of .0500 out of 3.5000 (in */
/* 	density.  It appears that stepouts of plus and minus half a */
/* 	row and column are needed to get appropriate accuracy for the */
/* 	derivatives. */
	    dpl = .01;
	    dtl = .04;
	    ttl = *tl + dtl;
	    *t = pow_dd(&c_b17, &ttl);
	    eqscve_(&ttl, t, pl, p, &dl1, &d1, x, z__, beta, betai, beta14, &
		    fxion[1], rmu, amu, emu, eta, &qdt1, &qdp1, &qcp1, &dela1,
		     &lcalc1);
	    ttl = *tl - dtl;
	    *t = pow_dd(&c_b17, &ttl);
	    eqscve_(&ttl, t, pl, p, &dl1, &d1, x, z__, beta, betai, beta14, &
		    fxion[1], rmu, amu, emu, eta, &qdt2, &qdp2, &qcp2, &dela2,
		     &lcalc2);
	    dtl2 = dtl * 2.;
	    qdtt1 = (qdt1 - qdt2) / dtl2 / const1_1.cln;
	    qcpt1 = (d_lg10(&qcp1) - d_lg10(&qcp2)) / dtl2;
	    qat1 = (d_lg10(&dela1) - d_lg10(&dela2)) / dtl2;
	    *t = pow_dd(&c_b17, tl);
	    ppl = *pl + dpl;
	    *p = pow_dd(&c_b17, &ppl);
	    eqscve_(tl, t, &ppl, p, &dl1, &d1, x, z__, beta, betai, beta14, &
		    fxion[1], rmu, amu, emu, eta, &qdt1, &qdp1, &qcp1, &dela1,
		     &lcalc1);
	    ppl = *pl - dpl;
	    *p = pow_dd(&c_b17, &ppl);
	    eqscve_(tl, t, &ppl, p, &dl1, &d1, x, z__, beta, betai, beta14, &
		    fxion[1], rmu, amu, emu, eta, &qdt2, &qdp2, &qcp2, &dela2,
		     &lcalc2);
	    *p = pow_dd(&c_b17, pl);
	    dpl2 = dpl * 2.;
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
    } else {
/* CALL TO PRATHER EOS - Either because SCV was not requested or it has failed. */
	eqsaha_(fx, tl, t, pl, p, dl, d__, beta, betai, beta14, &fxion[1], 
		rmu, amu, emu, lderiv, latmo, qdt, qdp, qcp, dela, qdtt, qdtp,
		 qat, qap, qcpt, qcpp, ksaha);
    }
/* STORE EQSAHA VALUES FOR INTERPOLATION WITH EQRELV VALUES */
    dl0 = *dl;
    qdt0 = *qdt;
    qdp0 = *qdp;
    qcp0 = *qcp;
    dela0 = *dela;
    if (*lderiv) {
	qdtt0 = *qdtt;
	qdtp0 = *qdtp;
	qcpt0 = *qcpt;
	qcpp0 = *qcpp;
	qat0 = *qat;
	qap0 = *qap;
    }
    if (lonlys) {
	goto L200;
    }
/* COMPUTE VALUES FOR FULLY IONIZED GAS */
/* Bypass relativistic EOS (eqrelv) if in low temperature region */
    *emu = *x * atomwt[0] + (1. - *x) * atomwt[3];
    *rmu = const2_1.cgas * (*amu + *emu);
    fxion[1] = 1.;
    fxion[2] = 0.;
    fxion[3] = 1.;
    eqrelv_(tl, t, pl, p, dl, d__, beta, amu, emu, eta, qdt, qdp, qcp, dela, 
	    qdtt, qdtp, qat, qap, qcpt, qcpp, x);
/* INTERPOLATE VALUES */
    wts = scales * (ctlim_1.tscut - *tl);
    wts2 = wts * wts;
    wt0 = wts2 * wts * (wts2 * 6. - wts * 15. + 10.);
/*      WT1 =-SCALES*30.0D0*WTS2*(1.0D0-WTS)**2 ! Derivative of WT0 */
    dl0 -= *dl;
    qdt0 -= *qdt;
    qdp0 -= *qdp;
    qcp0 -= *qcp;
    dela0 -= *dela;
    qcpt0 -= *qcpt;
    qcpp0 -= *qcpp;
    qat0 -= *qat;
    qap0 -= *qap;
    *dl += wt0 * dl0;
    *d__ = exp(const1_1.cln * *dl);
    *rmu = *beta * *p / (*d__ * *t);
    *emu = *rmu / const2_1.cgas - *amu;
    fxion[1] = wt0 * (fxion[1] - 1.) + 1.;
    fxion[2] = wt0 * fxion[2];
    fxion[3] = wt0 * (fxion[3] - 1.) + 1.;
    *qdt += wt0 * qdt0;
    *qdp += wt0 * qdp0;
    *qcp += wt0 * qcp0;
    *dela += wt0 * dela0;
    if (*lderiv) {
	*qdtt += wt0 * qdtt0;
	*qdtp += wt0 * qdtp0;
	*qcpt += wt0 * qcpt0;
	*qcpp += wt0 * qcpp0;
	*qat += wt0 * qat0;
	*qap += wt0 * qap0;
    }
L200:
/* 1995 OPAL eqos */
    if (opaleos_1.lopale) {
	if (*t >= 5e3 && *tl <= 8. && *dl <= 5.) {
	    switch (oeqos_(tl, t, pl, p, &d10o, &doo, x, z__, &betao, &betaio,
		     &beta14o, &rmuo, &amuo, &emuo, &qdto, &qdpo, &qcpo, &
		    delao)) {
		case 1:  goto L998;
	    }
	    eqbound_(t, &d10o, &dl0, &fac, &ltab, &lramp);
	    if (! ltab) {
		goto L998;
	    }
/* Point is not in OPAL 1995 EOS table, so exit. */
	    if (! lramp) {
/*  No ramping needed between OPAL 1995 EOS and Yale/SCV. Result is */
/*  fully in the OPAL 1995 table */
		*dl = d10o;
		*d__ = pow_dd(&c_b17, dl);
		*beta = betao;
		*betai = 1. / *beta;
		*beta14 = 1. - *beta;
		*rmu = rmuo;
		*amu = amuo;
		*emu = emuo;
		*qdt = qdto;
		*qdp = qdpo;
		*qcp = qcpo;
		*dela = delao;
	    } else {
/*  Ramping required. Result is on border between OPAL 1995 EOS and Yale/SCV. */
		*dl += fac * (d10o - *dl);
		*d__ = pow_dd(&c_b17, dl);
		*beta += fac * (betao - *beta);
		*betai = 1. / *beta;
		*beta14 = 1. - *beta;
		*rmu += fac * (rmuo - *rmu);
		*amu += fac * (amuo - *amu);
		*emu += fac * (emuo - *emu);
		*qdt += fac * (qdto - *qdt);
		*qdp += fac * (qdpo - *qdp);
		*qcp += fac * (qcpo - *qcp);
		*dela += fac * (delao - *dela);
	    }
	}
    }
/* 2001 OPAL eqos  LLP 6/17/03 */
    if (opaleos_1.lopale01) {
	if (*t >= 2e3 && *t <= 1e8 && *dl <= 7.) {
	    switch (oeqos01_(tl, t, pl, p, &d10o, &doo, x, z__, &betao, &
		    betaio, &beta14o, &rmuo, &amuo, &emuo, &qdto, &qdpo, &
		    qcpo, &delao)) {
		case 1:  goto L998;
	    }
	    eqbound01_(t, &d10o, &dl0, &fac, &ltab, &lramp);
/* eqbound01 determines whether or not the point is in the OPAL 2001 EOS table */
	    if (! ltab) {
		goto L998;
	    }
/* USE OPAL RESULTS IF NOT IN (RHO,T) REGIME WHERE RAMP */
/* NEEDED */
/* Point is not in OPAL 2001 tabel, so exit. */
	    if (! lramp) {
/*  No ramping needed between OPAL 2001 EOS and Yale/SCV. Result is */
/*  fully in the OPAL 2001 table */
		*dl = d10o;
		*d__ = pow_dd(&c_b17, dl);
		*beta = betao;
		*betai = 1. / *beta;
		*beta14 = 1. - *beta;
		*rmu = rmuo;
		*amu = amuo;
		*emu = emuo;
		*qdt = qdto;
		*qdp = qdpo;
		*qcp = qcpo;
		*dela = delao;
	    } else {
/*  Ramping required. Result is on border between OPAL 2001 EOS and Yale/SCV. */
		*dl += fac * (d10o - *dl);
		*d__ = pow_dd(&c_b17, dl);
		*beta += fac * (betao - *beta);
		*betai = 1. / *beta;
		*beta14 = 1. - *beta;
		*rmu += fac * (rmuo - *rmu);
		*amu += fac * (amuo - *amu);
		*emu += fac * (emuo - *emu);
		*qdt += fac * (qdto - *qdt);
		*qdp += fac * (qdpo - *qdp);
		*qcp += fac * (qcpo - *qcp);
		*dela += fac * (delao - *dela);
	    }
	}
    }
/* 2006 OPAL eqos  LLP 10/13/2996 */
    if (opaleos_1.lopale06) {
	if (*t >= 1870. && *t <= 2e8 && *dl <= 7.) {
	    switch (oeqos06_(tl, t, pl, p, &d10o, &doo, x, z__, &betao, &
		    betaio, &beta14o, &rmuo, &amuo, &emuo, &qdto, &qdpo, &
		    qcpo, &delao)) {
		case 1:  goto L998;
	    }
	    eqbound06_(t, &d10o, &dl0, &fac, &ltab, &lramp);
/* EQBOUND01 determines whether or not the point is in the OPAL 2006 EOS table */
/*    If LTAB is true, point is in Opal 2006 table */
/*    If LRAMP is true, point is in ramp area, and ramping is required. The ramp */
/*       factor FAC is the weight of the point for ramping purposes. */
/*    Also, to eliminate a point, one can set LRAMP to true and FAC to zero. */
	    if (! ltab) {
		goto L998;
	    }
/* USE OPAL 2006 RESULTS ONLY IF NOT IN (RHO,T) REGIME WHERE RAMPING is NEEDED */
/* Point is not in OPAL 2006 EOS table, so exit. */
	    if (! lramp) {
/*  No ramping needed between OPAL 2006 EOS and Yale/SCV. Result is */
/*  fully in the OPAL 2006 table */
		*dl = d10o;
		*d__ = pow_dd(&c_b17, dl);
		*beta = betao;
		*betai = 1. / *beta;
		*beta14 = 1. - *beta;
		*rmu = rmuo;
		*amu = amuo;
		*emu = emuo;
		*qdt = qdto;
		*qdp = qdpo;
		*qcp = qcpo;
		*dela = delao;
	    } else {
/*  Ramping required. Result is on border between OPAL 2006 EOS and Yale/SCV. */
		*dl += fac * (d10o - *dl);
		*d__ = pow_dd(&c_b17, dl);
		*beta += fac * (betao - *beta);
		*betai = 1. / *beta;
		*beta14 = 1. - *beta;
		*rmu += fac * (rmuo - *rmu);
		*amu += fac * (amuo - *amu);
		*emu += fac * (emuo - *emu);
		*qdt += fac * (qdto - *qdt);
		*qdp += fac * (qdpo - *qdp);
		*qcp += fac * (qcpo - *qcp);
		*dela += fac * (delao - *dela);
	    }
	}
    }
L998:
    *z__ = z0;
    return 0;
} /* eqstat2_ */

