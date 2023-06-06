/* eqrelv.f -- translated by f2c (version 20100827).
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
    doublereal dval[43], etat8[43], dtable[4300]	/* was [5][43][20] */;
    integer iden[261];
} ccr_;

#define ccr_1 ccr_

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
    doublereal cdh, etadh0, etadh1, zdh[18], xxdh, yydh, zzdh, dhnue[18];
    logical ldh;
} debhu_;

#define debhu_1 debhu_

/* Table of constant values */

static doublereal c_b5 = .5;
static integer c__1 = 1;



/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */
/* EQRELV */
/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */
/* Subroutine */ int eqrelv_(doublereal *tl, doublereal *t, doublereal *pl, 
	doublereal *p, doublereal *dl, doublereal *d__, doublereal *beta, 
	doublereal *amu, doublereal *emu, doublereal *eta, doublereal *qdt, 
	doublereal *qdp, doublereal *qcp, doublereal *dela, doublereal *qdtt, 
	doublereal *qdtp, doublereal *qat, doublereal *qap, doublereal *qcpt, 
	doublereal *qcpp, doublereal *x)
{
    /* Format strings */
    static char fmt_40[] = "(\002EQRELV: Did not Converge: T,P,Pcalc,Dcalc,C"
	    "ORR\002,4f10.6,f20.12)";

    /* System generated locals */
    integer i__1, i__2;
    doublereal d__1, d__2;

    /* Builtin functions */
    double d_lg10(doublereal *), sqrt(doublereal), exp(doublereal), d_sign(
	    doublereal *, doublereal *);
    integer s_wsfe(cilist *), do_fio(integer *, char *, ftnlen), e_wsfe(void);

    /* Local variables */
    static doublereal u, d8, t0, t1, ff[15]	/* was [5][3] */;
    static integer id;
    static doublereal pa;
    static integer ii;
    static doublereal pd, pe;
    static integer kk;
    static doublereal ua, ue;
    static integer nn;
    static doublereal ui, pr, pt, ur, xx, df1[15]	/* was [5][3] */, df2[
	    15]	/* was [5][3] */;
    static integer id1, id2, id3;
    static doublereal cl1, cl2, cl3, dl8, dx1, dx2;
    static integer jt1, jt2, jt3;
    static doublereal dx3, pr1, pl8, pr2, pr3, pr4, tl8, pr6, pr8, pr9, pr7, 
	    pr5, ffe[5], acp, bcp, dml, pdh, pel, peq, qpd, ueq, pdt, udh, 
	    ptl, pdu, qpt, dcl1, dcl2, dcl3;
    static integer id1p;
    static doublereal pr8l, pr9l, fact;
    static integer nden;
    static doublereal qped, pdhp, qcpi, emul, ramu, corr, qdpp, udhu, pinv, 
	    ttud, ttcu, qutd, qudt, cden1, cden2, beta1, cden3, qutp, dpel1, 
	    dpel2, emul8, cmfdh, factl, qqpdd, almix, qpeqd, slope, ttdcu, 
	    ramut, qqpdt, qpeqt, qqudt, queqt, cmfdh0, cmfdh1, qqptt, qqutt, 
	    factor, qqpedd;

    /* Fortran I/O blocks */
    static cilist io___70 = { 0, 0, 0, fmt_40, 0 };


/*          QDTT,QDTP = NAT-LOG DERIVATIVES OF QDT=D(LOG D )/D(LOG T ) */
/*          QAT,QAP = NAT-LOG DERIVATIVES OF THE ADIABATIC DERIVATIVE */
/* DBG 7/92 MODIFIED TO INCLUDE DEBYE-HUCKEL CORRECTION. */
/*     CORRECTION IS APPLIED TO PRESSURE AND ALL THERMODYNAMIC VARIABLES. */
/*     TREATMENT IS ALSO VALID FOR ELECTRON DEGENERACY.  A RAMP FUNCTION */
/*     BETWEEN THE NONDEGENERATE AND DEGERNATE ELECTRON GAS CASES OF THE */
/*     D.H. CORRECTION IS USED (THIS IS NOT CORRECT BUT, HOPEFULLY IS */
/*     CLOSE ENOUGH.  CONSTANT TERM CDH IS CALCULATED IN SETUPS. */
/* DBG 7/92 CDH IS CONSTANT TERM DEFINED IN SETUPS */
/*     RAMP FUNCTION BETWEEN NO ELECTRON DEGENERACY ETA .LT. ETADH0 */
/*     AND FULL ELECTRON DEGENERACY ETA .GT. ETADH1 VERSION OF D.H. */
/*     CORRECTION. */
/*     IF LDH = .TRUE. THEN APPLY D.H. CORRECTION. */
/*     ZDH IS ARRAY OF RELATIVE MASS FRACTIONS OF LAOL METAL MIXTURE */
/*     SUMMED TO 1.0. */
/* DBG 7/92 COMMON BLOCK ADDED TO COMPUTE DEBYE-HUCKEL CORRECTION. */
/*  THE ELECTRON PRESSURE (TABULATED IN FERMI TABLE) FOR A GIVEN (RHO,T) */
/*  IS FOUND HERE; THE DENSITY IS ADJUSTED SO THAT THE RESULTING TOTAL */
/*  PRESSURE (PE + PA + PR) EQUALS THE INITIAL P.  FOR DETAILS */
/*  CONSULT PRATHER'S THESIS. */
/*  SUFFIX E=ELECTRON;R=RADIATION;A=NUCLEON;I.E.PA=PRESSURE DUE TO NUCLEI */
    pinv = 1. / *p;
    beta1 = 1. - *beta;
    tl8 = *tl;
    pl8 = *pl;
    pr = beta1 * *p;
    ramu = const2_1.cgas * *amu;
    ramut = ramu * *t;
    emul = d_lg10(emu);
    emul8 = emul;
/*  PE IS TABULATED AS A FUNCTION OF X(=LOG D - LOG MUE - 3/2LOG T) AND */
/*  Y(= LOG T). FIND INDEX(JT1,JT2,JT3) FOR 3 PT INTERPOLATION IN Y. */
/* MHP 10/02 CORRECTED MIXED TYPE */
    jt1 = (integer) ((*tl - 5.) * 5.);
/* Computing MAX */
    i__1 = 1, i__2 = min(jt1,18);
    jt1 = max(i__1,i__2);
/* Force jt1 to be in the table */
    jt2 = jt1 + 1;
    jt3 = jt1 + 2;
    ttud = (tl8 - ((doublereal) jt1 * .2 + 5.)) * 5.;
    ttcu = ttud * .5 * (ttud - 1.);
    ttdcu = ttud - .5;
    dml = *dl + emul;
    nden = 1;
    id1p = -100;
/* DBG 7/92 CALCULATE D.H. TERMS: ALPHA-MIXTURE, MASS-FRAC0, MASS-FRAC1 */
    if (debhu_1.ldh) {
	almix = 0.;
	for (ii = 1; ii <= 18; ++ii) {
	    almix += debhu_1.dhnue[ii - 1] * debhu_1.zdh[ii - 1];
	}
	cmfdh0 = debhu_1.xxdh * 2. + debhu_1.yydh * 1.5 + (debhu_1.zzdh + 
		almix) * .5;
	cmfdh1 = debhu_1.xxdh + debhu_1.yydh + almix * .5;
    }
L10:
/* BEGIN ITERATION LOOP FOR CORRECT DENSITY */
/*  FIND INDEX (ID1,ID2,ID3) FOR 3-PT INTERPOLATION IN X */
    xx = dml - tl8 * 1.5;
    pr6 = (xx - ccr_1.dval[0]) * 20. + 1.;
/* MHP 10/02 CORRECTED MIXED TYPE */
    kk = (integer) pr6;
/*      KK = PR6 */
/* Computing MIN */
    i__1 = 261, i__2 = max(1,kk);
    kk = min(i__1,i__2);
    id1 = ccr_1.iden[kk - 1];
/*  IF INDEX UNCHANGED FROM PREVIOUS LOOP,SKIP THIS SECTION */
    if (id1 == id1p) {
	goto L30;
    }
    id1p = id1;
    id2 = id1 + 1;
    id3 = id1 + 2;
    pr9 = 1. / (ccr_1.dval[id3 - 1] - ccr_1.dval[id2 - 1]);
    pr8 = 1. / (ccr_1.dval[id2 - 1] - ccr_1.dval[id1 - 1]);
    pr7 = 1. / (ccr_1.dval[id1 - 1] - ccr_1.dval[id3 - 1]);
    cden1 = -pr7 * pr8;
    cden2 = -pr8 * pr9;
    cden3 = -pr9 * pr7;
/*  INTERPOLATION IN Y IS NEWTONIAN(EQUAL SPACING IN Y) */
    for (nn = 1; nn <= 3; ++nn) {
	id = id1 + nn - 1;
	df1[nn * 5 - 5] = ccr_1.dtable[(id + jt2 * 43) * 5 - 220] - 
		ccr_1.dtable[(id + jt1 * 43) * 5 - 220];
	df2[nn * 5 - 5] = ccr_1.dtable[(id + jt3 * 43) * 5 - 220] - 
		ccr_1.dtable[(id + jt2 * 43) * 5 - 220] - df1[nn * 5 - 5];
	ff[nn * 5 - 5] = ccr_1.dtable[(id + jt1 * 43) * 5 - 220] + ttud * df1[
		nn * 5 - 5] + ttcu * df2[nn * 5 - 5];
/* L20: */
    }
    dpel2 = (ff[0] * cden1 + ff[5] * cden2 + ff[10] * cden3) * 2.;
L30:
    dx1 = xx - ccr_1.dval[id1 - 1];
    dx2 = xx - ccr_1.dval[id2 - 1];
    dx3 = xx - ccr_1.dval[id3 - 1];
/*  INTERPOLATION IN X IS LAGRANGIAN(UNEQUAL TABLE SPACING IN X) */
    cl1 = dx2 * dx3 * cden1;
    cl2 = dx3 * dx1 * cden2;
    cl3 = dx1 * dx2 * cden3;
    dcl1 = (dx2 + dx3) * cden1;
    dcl2 = (dx3 + dx1) * cden2;
    dcl3 = (dx1 + dx2) * cden3;
    if (debhu_1.ldh) {
	*eta = cl1 * ccr_1.etat8[id1 - 1] + cl2 * ccr_1.etat8[id2 - 1] + cl3 *
		 ccr_1.etat8[id3 - 1];
	if (*eta < debhu_1.etadh0) {
	    cmfdh = cmfdh0 * sqrt(cmfdh0);
	} else if (*eta > debhu_1.etadh1) {
	    cmfdh = cmfdh0 * sqrt(cmfdh1);
	} else {
	    t0 = cmfdh0 * sqrt(cmfdh0);
	    t1 = cmfdh0 * sqrt(cmfdh1);
	    slope = (t1 - t0) / (debhu_1.etadh1 - debhu_1.etadh0);
	    cmfdh = t0 + (*eta - debhu_1.etadh0) * slope;
	}
    }
/*  NOW FIND PE AND ITS 1ST AND 2ND DERIVS.W/R/T DENSITY */
    pel = cl1 * ff[0] + cl2 * ff[5] + cl3 * ff[10];
    dpel1 = dcl1 * ff[0] + dcl2 * ff[5] + dcl3 * ff[10];
    dl8 = dml - emul8;
    d8 = exp(const1_1.cln * dl8);
    pa = ramut * d8;
    pe = exp(const1_1.cln * pel);
    if (debhu_1.ldh) {
	pdh = debhu_1.cdh * cmfdh * sqrt(d8 / *t) * d8;
    }
    pt = pa + pe + pr;
    if (debhu_1.ldh) {
	pt += pdh;
	pdhp = pdh / pt;
    }
    ptl = d_lg10(&pt);
    pr7 = (pa + pe * dpel1) / pt;
    if (debhu_1.ldh) {
	pr7 += pdhp * 1.5;
    }
    pr8 = (ptl - pl8) / pr7;
/* Computing 2nd power */
    d__1 = dpel1;
    pr9 = const1_1.cln * ((pa + pe * (d__1 * d__1 + dpel2 / const1_1.cln)) / (
	    pt * pr7) - pr7);
    if (debhu_1.ldh) {
	pr9 += pdhp * 2.25 / pr7;
    }
/* FACTOR IS THE DIFFERENCE BETWEEN THE P PREDICTED FROM THE GIVEN RHO */
/* AND THE TRUE P; IF TOO LARGE INCREMENT RHO AND TRY AGAIN. */
    factor = abs(pr8);
    if (factor < 1e-15) {
	factor = 1e-15;
    }
    pr8l = d_lg10(&factor);
    d__1 = abs(pr9);
    pr9l = d_lg10(&d__1);
    factl = d_lg10(&c_b5) + pr9l + pr8l * 2.;
    fact = exp(const1_1.cln * factl);
    fact = d_sign(&fact, &pr9);
    corr = -pr8 - fact;
/*  limit range of changes in density to a factor of 10**4   llp  1/31/07 */
    if (corr > 4.) {
	corr = 4.;
    }
    if (corr < -4.) {
	corr = -4.;
    }
    if (abs(corr) >= 1e-8) {
	dml += corr;
	++nden;
	if (nden <= 20) {
	    goto L10;
	}
	io___70.ciunit = luout_1.ishort;
	s_wsfe(&io___70);
	do_fio(&c__1, (char *)&(*tl), (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&(*pl), (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&ptl, (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&dml, (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&corr, (ftnlen)sizeof(doublereal));
	e_wsfe();
/*       PAUSE */
	return 0;
/*         STOP 'ERRELV failed' */
    }
    *dl = dl8;
    *d__ = d8;
    for (kk = 2; kk <= 5; ++kk) {
	for (nn = 1; nn <= 3; ++nn) {
	    id = id1 + nn - 1;
	    df1[kk + nn * 5 - 6] = ccr_1.dtable[kk + (id + jt2 * 43) * 5 - 
		    221] - ccr_1.dtable[kk + (id + jt1 * 43) * 5 - 221];
	    df2[kk + nn * 5 - 6] = ccr_1.dtable[kk + (id + jt3 * 43) * 5 - 
		    221] - ccr_1.dtable[kk + (id + jt2 * 43) * 5 - 221] - df1[
		    kk + nn * 5 - 6];
	    ff[kk + nn * 5 - 6] = ccr_1.dtable[kk + (id + jt1 * 43) * 5 - 221]
		     + ttud * df1[kk + nn * 5 - 6] + ttcu * df2[kk + nn * 5 - 
		    6];
/* L50: */
	}
	ffe[kk - 1] = cl1 * ff[kk - 1] + cl2 * ff[kk + 4] + cl3 * ff[kk + 9];
/* L60: */
    }
/* DERIVATIVES OF P */
    peq = exp(const1_1.cln * ffe[2]);
    qped = ffe[3];
    qqpedd = (dcl1 * ff[3] + dcl2 * ff[8] + dcl3 * ff[13]) * const1_1.clni;
    pr1 = df1[2] + ttdcu * df2[2];
    pr2 = df1[7] + ttdcu * df2[7];
    pr3 = df1[12] + ttdcu * df2[12];
    pr4 = dcl1 * ff[2] + dcl2 * ff[7] + dcl3 * ff[12];
    pr5 = (cl1 * pr1 + cl2 * pr2 + cl3 * pr3) * 5.;
    qpeqd = peq * pr4;
    qpeqt = peq * (pr5 - pr4 * 1.5);
    qpt = (pa + peq) * pinv + beta1 * 4.;
    if (debhu_1.ldh) {
	qpt -= pdhp * .5;
    }
    qpd = (pa + pe * qped) * pinv;
    if (debhu_1.ldh) {
	qpd += pdhp * 1.5;
    }
/* Computing 2nd power */
    d__1 = qpt;
    qqptt = (pa + qpeqt) * pinv + beta1 * 16. - d__1 * d__1;
    if (debhu_1.ldh) {
	qqptt += (qpt * .5 + .25) * pdhp;
    }
    qqpdt = (pa + qpeqd) * pinv - qpt * qpd;
    if (debhu_1.ldh) {
	qqpdt += (qpt * .5 - .75) * pdhp;
    }
/* Computing 2nd power */
    d__1 = qped;
/* Computing 2nd power */
    d__2 = qpd;
    qqpdd = (pa + pe * (d__1 * d__1 + qqpedd)) * pinv - d__2 * d__2;
    if (debhu_1.ldh) {
	qqpdd += (qpd * -1.5 + 2.25) * pdhp;
    }
/* DERIVATIVES OF DENSITY */
    *qdp = 1. / qpd;
    *qdt = -qpt * *qdp;
/* Computing 2nd power */
    d__1 = *qdp;
    pr1 = d__1 * d__1;
    qdpp = -qqpdd * *qdp * pr1;
    *qdtp = -qpt * qdpp - qqpdt * pr1;
    *qdtt = -qpt * *qdtp - *qdp * (qqptt + *qdt * qqpdt);
/* INTERNAL ENERGY TERM(U) AND ITS DERIVATIVES */
    ue = exp(const1_1.cln * (ffe[1] + emul));
    ueq = exp(const1_1.cln * (ffe[4] + emul));
    pr1 = df1[4] + ttdcu * df2[4];
    pr2 = df1[9] + ttdcu * df2[9];
    pr3 = df1[14] + ttdcu * df2[14];
    pr4 = dcl1 * ff[4] + dcl2 * ff[9] + dcl3 * ff[14];
    pr5 = (cl1 * pr1 + cl2 * pr2 + cl3 * pr3) * 5.;
    queqt = ueq * (pr5 - pr4 * 1.5);
    pd = *p / *d__;
    pdt = pd / *t;
    ua = ramut * 1.5;
    ur = beta1 * 3. * pd;
    if (debhu_1.ldh) {
	udh = pdh * 3. / d8;
    }
    u = ua + ue + ur;
    if (debhu_1.ldh) {
	u += udh;
	udhu = udh / u;
    }
    ui = 1. / u;
    pdu = pd * ui;
    qutd = (ua + ueq + ur * 4.) * ui;
    if (debhu_1.ldh) {
	qutd -= udhu * .5;
    }
    qudt = pdu * (1. - qpt);
    if (debhu_1.ldh) {
	qudt += udhu * .5;
    }
    qutp = qutd + *qdt * qudt;
/* Computing 2nd power */
    d__1 = qutd;
    qqutt = (ua + queqt + ur * 16.) * ui - d__1 * d__1;
    if (debhu_1.ldh) {
	qqutt += (qutd * .5 + .25) * udhu;
    }
    qqudt = qudt * (qpt - qutd) - pdu * qqptt;
    if (debhu_1.ldh) {
	qqudt += (qudt * .5 - .25) * udhu;
    }
/* SPECIFIC HEAT(QCP) AND ITS DERIVATIVES */
    pr1 = -pdt * *qdt;
    pr2 = u / *t;
    pr3 = -(*qdt + 1.) + *qdtt / *qdt;
    pr4 = 1. - *qdp + *qdtp / *qdt;
    acp = pr1 * qpt;
    bcp = pr2 * qutd;
    *qcp = acp + bcp;
    qcpi = 1. / *qcp;
    *qcpt = acp * pr3 + pr1 * (qqptt + *qdt * qqpdt) + bcp * (qutp - 1.) + 
	    pr2 * (qqutt + *qdt * qqudt);
    *qcpp = acp * pr4 + *qdp * (pr1 * qqpdt + bcp * qudt + pr2 * qqudt);
    *qcpt *= qcpi;
    *qcpp *= qcpi;
/* ADIABATIC GRADIENT(DELA) AND DERIVATIVES ( ALL DERIVS ARE LN(DELA)/LN( */
    *dela = pr1 * qcpi;
    *qat = pr3 - *qcpt;
    *qap = pr4 - *qcpp;
    *eta = cl1 * ccr_1.etat8[id1 - 1] + cl2 * ccr_1.etat8[id2 - 1] + cl3 * 
	    ccr_1.etat8[id3 - 1];
    return 0;
} /* eqrelv_ */

