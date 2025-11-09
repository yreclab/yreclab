/* massloss.f -- translated by f2c (version 20061008).
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
    doublereal tau, ap, at, ad, ao, afxion[3];
} atmprt_;

#define atmprt_1 atmprt_

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
    doublereal dmdt0, fczdmdt, ftotdmdt, compacc[15], creim;
    logical lreimer, lmdot;
} masschg_;

#define masschg_1 masschg_

struct {
    doublereal sacc, scen, smass0, dlogt, dlogp;
} masschg2_;

#define masschg2_1 masschg2_

struct {
    doublereal drate[5000], drate0[5000], fmassacc;
    integer jcz;
} deuter_;

#define deuter_1 deuter_

struct {
    doublereal sesum[5000], seg[35000]	/* was [7][5000] */, sbeta[5000], 
	    seta[5000];
    logical locons[5000];
    doublereal so[5000], sdel[15000]	/* was [3][5000] */, sfxion[15000]	
	    /* was [3][5000] */, svel[5000], scp[5000];
} scrtch_;

#define scrtch_1 scrtch_

struct {
    logical lnewtcz, lcalcenv;
    doublereal taucz, taucz0, pphot, pphot0, fracstep;
} ovrtrn_;

#define ovrtrn_1 ovrtrn_

/* Table of constant values */

static doublereal c_b3 = 10.;
static integer c__5 = 5;
static integer c__1 = 1;
static doublereal c_b21 = .25;

/* MHP 10/01 */
/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */
/* MASS LOSS DRIVER ROUTINE */
/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */
/* This is experimental code and valid for Allard atmospheres only. */
/*   llp  06/15/2009 */
/* Subroutine */ int massloss_(doublereal *bl, doublereal *dage, doublereal *
	delts, doublereal *hcomp, doublereal *hd, doublereal *hjm, doublereal 
	*hp, doublereal *hr, doublereal *hs, doublereal *hs1, doublereal *hs2,
	 doublereal *hstot, doublereal *ht, integer *jenv, logical *lnew, 
	integer *m, doublereal *omega, doublereal *smass, doublereal *teffl, 
	doublereal *senvold, logical *lnewfit)
{
    /* Initialized data */

    static doublereal facc = 1.;

    /* System generated locals */
    integer i__1;
    doublereal d__1, d__2;

    /* Builtin functions */
    double pow_dd(doublereal *, doublereal *);
    integer s_wsle(cilist *), do_lio(integer *, integer *, char *, ftnlen), 
	    e_wsle(void);
    double log(doublereal), sqrt(doublereal), d_lg10(doublereal *);

    /* Local variables */
    static doublereal d__;
    static integer j;
    static doublereal p, r__, t, x, z__, ethaccbar, dl, gl, pl, rl, tl, eta, 
	    eth, amu, qcp, qdp, emu, qdt, qat, qap, rmu, eacc, dela, beta, 
	    dmdt, qcpp;
    extern /* Subroutine */ int mdot_(doublereal *, doublereal *, doublereal *
	    , doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, integer *,
	     logical *, integer *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *);
    static doublereal qcpt, qdtp, eacc0, qdtt;
    static logical lprt;
    static doublereal rtot, stot, sacc2, dmdt2, beta14, betai;
    static integer ksaha;
    static doublereal ethav;
    static logical latmo;
    static doublereal fxion[3], gsurf, sumdm, delacc, ethacc, slocal, agetot;
    static logical lderiv;
    extern /* Subroutine */ int eqstat_(doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, logical *,
	     logical *, integer *);
    static doublereal sumeth;
    static logical lalfail, ldomdot;
    extern /* Subroutine */ int alsurfp_(doublereal *, doublereal *, logical *
	    , logical *);

    /* Fortran I/O blocks */
    static cilist io___9 = { 0, 6, 0, 0, 0 };


/* G Somers 3/17, ADDING NEW TAUCZ COMMON BLOCK */
/* MHP 5/02 EFFICIENCY FACTOR FOR THE THERMAL ENERGY CONTENT */
/* OF ACCRETED MATTER. */
    /* Parameter adjustments */
    --omega;
    --ht;
    --hs2;
    --hs1;
    --hs;
    --hr;
    --hp;
    --hjm;
    --hd;
    hcomp -= 16;

    /* Function Body */
/* INITIALIZE MASS LOSS AT DEFAULT RATE */
    dmdt = masschg_1.dmdt0;
    if (masschg_1.lmdot) {
	ldomdot = TRUE_;
    } else {
	ldomdot = FALSE_;
	*lnewfit = FALSE_;
	goto L9999;
    }
/*      IF(.NOT.LDOMDOT)RETURN */
/* TEFFL IS THE BASE 10 LOG OF THE EFFECTIVE TEMPERATURE */
/* COMPUTE GLOBAL QUANTITIES (RADIUS,MASS,AGE) IN CGS UNITS. */
/* RADIUS */
    rl = (*bl + const_1.clsunl - const1_1.c4pil - const2_1.csigl - *teffl * 
	    4.) * .5;
    rtot = pow_dd(&c_b3, &rl);
/* MASS */
    stot = *smass * const_1.cmsun;
/* AGE */
    agetot = *dage * 1e9 * const3_1.csecyr;
/* USE A REIMERS FORMULA TO COMPUTE MDOT IF DESIRED; OVERWRITES */
/* CONSTANT MDOT.  IN THIS EXPRESSION MDOT=K*L/G/R. */
    if (ldomdot && masschg_1.lreimer) {
/* Computing 2nd power */
	d__1 = rtot;
	gsurf = pow_dd(&c_b3, &const2_1.cgl) * stot / (d__1 * d__1);
	d__1 = *bl + const_1.clsunl;
	dmdt = masschg_1.creim * pow_dd(&c_b3, &d__1) / gsurf / rtot;
    }
/* 02/12 MHP TAUCZ NOW COMPUTED PRIOR TO CALL IN MIXCZ */
/* CONVECTIVE OVERTURN TIMESCALE */
    if (*jenv < *m) {
/*         TAUCZ = 0.0D0 */
/*         DO I = JENV+1,M */
/*            V = 0.5D0*(SVEL(I-1)+SVEL(I)) */
/*            DR = 10.0D0**(HR(I))-10.0D0**(HR(I-1)) */
/*            IF(V.GT.0.0D0)THEN */
/*               TAUCZ = TAUCZ + DR/V */
/*            ENDIF */
/*         END DO */
	s_wsle(&io___9);
	d__1 = ovrtrn_1.taucz / const3_1.csecyr;
	do_lio(&c__5, &c__1, (char *)&d__1, (ftnlen)sizeof(doublereal));
	d__2 = rtot / const_1.crsun;
	do_lio(&c__5, &c__1, (char *)&d__2, (ftnlen)sizeof(doublereal));
	e_wsle();
	deuter_1.jcz = *jenv;
    } else {
	ovrtrn_1.taucz = 0.;
	deuter_1.jcz = *m;
    }
/* MHP 8/10 */
/* THE RUNNING TOTAL OF THE MASS OF THE */
/* CONVECTIVE ENVELOPE, NEEDED ELSEWHERE AS WELL */
    sumdm = 0.;
    i__1 = *m;
    for (j = *jenv; j <= i__1; ++j) {
	sumdm += hs2[j];
    }
/* COMPUTE THE MEAN MOLECULAR WEIGHT FOR THE CZ */
    if (dmdt > 0.) {
	*lnewfit = TRUE_;
	t = pow_dd(&c_b3, &ht[*jenv]);
	p = pow_dd(&c_b3, &hp[*jenv]);
	d__ = pow_dd(&c_b3, &hd[*jenv]);
/* Computing 4th power */
	d__1 = t, d__1 *= d__1;
	beta = 1. - const2_1.ca3 * (d__1 * d__1) / p;
	rmu = p * beta / (d__ * t);
/* FROM THE VIRIAL THEOREM, A MAXIMUM OF */
/* 1/2 OF THE GRAVITATIONAL POTENTIAL ENERGY OF */
/* ACCRETED MATTER WILL BE CONVERTED INTO KINETIC */
/* ENERGY.  THE PARAMETER FACC IS USED TO INFER */
/* THE KINETIC ENERGY PER GRAM WHICH IS COMPARED */
/* WITH THE MEAN THERMAL ENERGY CONTENT OF THE */
/* CONVECTION ZONE. */
	eacc = facc * stot * pow_dd(&c_b3, &const2_1.cgl) / rtot;
	eacc0 = eacc;
/* DETERMINE THE MASS-WEIGHTED THERMAL ENERGY (PER GM) */
/* IN EACH SHELL OF THE CONVECTIVE ENV. */
	sumeth = 0.;
/*         SUMDM = 0.0D0 */
	ethaccbar = 0.;
	masschg2_1.scen = 0.;
	i__1 = *m;
	for (j = *jenv; j <= i__1; ++j) {
	    t = pow_dd(&c_b3, &ht[j]);
	    p = pow_dd(&c_b3, &hp[j]);
	    d__ = pow_dd(&c_b3, &hd[j]);
	    r__ = pow_dd(&c_b3, &hr[j]);
	    delacc = eacc * .5 * (rtot / r__ - 1.);
	    ethacc = eacc + delacc;
	    ethaccbar += hs2[j] * ethacc;
/* Computing 4th power */
	    d__1 = t, d__1 *= d__1;
	    beta = 1. - const2_1.ca3 * (d__1 * d__1) / p;
	    rmu = p * beta / (d__ * t);
	    slocal = rmu * (log(t) * 1.5 - log(d__));
	    masschg2_1.scen += slocal * hs2[j];
/* THE THERMAL ENERGY PER GM IN THE JTH SHELL IS */
	    eth = p * beta / d__;
/* THE RUNNING TOTAL OF THERMAL ENERGY THROUGHOUT THE */
/* CONVECTIVE ENVELOPE IS */
	    sumeth += eth * hs2[j];
/* THE RUNNING TOTAL OF THE MASS OF THE */
/* CONVECTIVE ENVELOPE IS */
/*            SUMDM = SUMDM + HS2(J) */
	}
/* THE AVERAGE THERMAL ENERGY OF THE UNPERTURBED CE (W/O ACCN) IS */
	ethav = sumeth / sumdm;
	eacc = ethaccbar / sumdm;
	masschg2_1.scen /= sumdm;
	lprt = FALSE_;
	gl = const2_1.cgl + *hstot - rl * 2.;
/* This is experimental code and valid for Allard atmospheres only. */
/*   llp  06/15/2009 */
	alsurfp_(teffl, &gl, &lprt, &lalfail);
	t = pow_dd(&c_b3, &atmprt_1.at);
	p = pow_dd(&c_b3, &atmprt_1.ap);
	tl = atmprt_1.at;
	pl = atmprt_1.ap;
	x = hcomp[*m * 15 + 1];
	z__ = hcomp[*m * 15 + 3];
	lderiv = FALSE_;
	ksaha = 1;
	latmo = TRUE_;
	eqstat_(&tl, &t, &pl, &p, &dl, &d__, &x, &z__, &beta, &betai, &beta14,
		 fxion, &rmu, &amu, &emu, &eta, &qdt, &qdp, &qcp, &dela, &
		qdtt, &qdtp, &qat, &qap, &qcpt, &qcpp, &lderiv, &latmo, &
		ksaha);
/* Computing 4th power */
	d__1 = t, d__1 *= d__1;
	beta = 1. - const2_1.ca3 * (d__1 * d__1) / p;
	rmu = p * beta / (d__ * t);
	masschg2_1.sacc = rmu * (log(t) * 1.5 - log(d__));
/*         WRITE(*,911)TL,PL,SACC,SCEN */
/*  911     FORMAT(' TSUR,PSUR ',2F8.5,' SACC ',1PE12.3,' SCORE ',E12.3) */
/* ALTERNATE EXPRESSION FOR SURFACE PRESSURE AND LUMINOSITY, FROM STAHLER 1988 */
	if (facc > 0.) {
	    dmdt2 = dmdt * const_1.cmsun / const3_1.csecyr;
/* Computing 3rd power */
	    d__1 = rtot;
	    p = dmdt2 / const1_1.c4pi * sqrt(facc * 2. * pow_dd(&c_b3, &gl) / 
		    (d__1 * (d__1 * d__1)));
/* Computing 2nd power */
	    d__2 = rtot;
	    d__1 = dmdt2 * eacc0 * .75 / const1_1.c4pi / (d__2 * d__2) / 
		    const2_1.csig;
	    t = pow_dd(&d__1, &c_b21);
	    pl = d_lg10(&p);
	    tl = d_lg10(&t);
	    eqstat_(&tl, &t, &pl, &p, &dl, &d__, &x, &z__, &beta, &betai, &
		    beta14, fxion, &rmu, &amu, &emu, &eta, &qdt, &qdp, &qcp, &
		    dela, &qdtt, &qdtp, &qat, &qap, &qcpt, &qcpp, &lderiv, &
		    latmo, &ksaha);
/* Computing 4th power */
	    d__1 = t, d__1 *= d__1;
	    beta = 1. - const2_1.ca3 * (d__1 * d__1) / p;
	    rmu = p * beta / (d__ * t);
	    sacc2 = rmu * (log(t) * 1.5 - log(d__));
/*            WRITE(*,911)TL,PL,SACC2,SCEN */
/*            SACC = MAX(SACC,SACC2) */
	    masschg2_1.scen = 0.;
/*            SCEN = SACC2 - SACC */
	} else {
	    masschg2_1.scen = 0.;
	}
    }
/* CALL MASS LOSS OR ACCRETION ROUTINE */
    if (ldomdot) {
	mdot_(delts, &hcomp[16], &hd[1], &hjm[1], &hp[1], &hr[1], &hs[1], &
		hs1[1], &hs2[1], hstot, &ht[1], jenv, lnew, m, &omega[1], &
		rmu, &rtot, smass, &dmdt, &eacc, &ethav, &sumdm, senvold);
    }
L9999:
    return 0;
} /* massloss_ */

