/* setscv.f -- translated by f2c (version 20061008).
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
    doublereal cgas, ca3, ca3l, csig, csigl, cgl, cmkh, cmkhn;
} const2_;

#define const2_1 const2_

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

struct {
    doublereal xenv, zenv, zenvm, amuenv, fxenv[12], xnew, znew, stotal, senv;
} comp_;

#define comp_1 comp_

/* Table of constant values */

static doublereal c_b2 = 10.;

/*     This is to evaluate the EOS with the new tables and call eqstat to */
/*     compute the new equation of state and compare to the old one... */
/* Subroutine */ int setscv_(void)
{
    /* Initialized data */

    static doublereal cmh = 1.67357e-24;
    static doublereal cmhe = 6.646442e-24;
    static doublereal cboltz = 1.380658e-16;

    /* System generated locals */
    integer i__1, i__2;
    doublereal d__1, d__2;

    /* Builtin functions */
    double exp(doublereal), log(doublereal), pow_dd(doublereal *, doublereal *
	    ), d_lg10(doublereal *);

    /* Local variables */
    static doublereal d__;
    static integer i__, j, k;
    static doublereal p, t, x, y, z__, s0, be, ga, de, dl;
    static integer ii, jj;
    static doublereal fp[3], ft[3], xd, yd, pl, tl, qr[3], sx, sy, ym1, dei, 
	    fpd[3], ftd[3], dln, qap, qat, tln, qut, qcp0, qdp0, qdt0, qpt0, 
	    qst0, prad, qpdd, pgas, denx, deny, denz, dmix, qcpp, hnum, qdtp, 
	    qcpt, tote, qdtt, tnum, henum, hnume;
    extern /* Subroutine */ int inter3_(doublereal *, doublereal *, 
	    doublereal *, doublereal *);
    static doublereal henume, qsmixt;

/* MHP  5/97 ADDED COMMON BLOCK FOR SCV EOS TABLES */
/*       DIMENSION ATOMWT(4),QR(3),FT(3),FTD(3),FP(3),FPD(3)  ! KC 2025-05-31 */
/*       DATA ATOMWT/0.9921D0,0.24975D0,0.08322D0,0.4995D0/ */
/*  READ IN EQUATION OF STATE TABLES FOR HYDROGEN AND HELIUM */
    for (i__ = 1; i__ <= 63; ++i__) {
	i__1 = scveos_1.nptsx[i__ - 1];
	for (j = 1; j <= i__1; ++j) {
/*  COMPUTE DU/DT - NEEDED FOR SPECIFIC HEAT DERIVATIVES */
/*  CP = T (DS/DT)|P = S(D LN S/D LN T)|P (EQ 1) */
/* AND CP = DU/DT + P*(D LN RHO/D LN T)**2/(RHO*T*D LN RHO/D LN P) (EQ 2) */
/* DU/DT CAN BE INFERRED FROM EQ 1 AND THE SECOND TERM IN EQ 2, ALL OF */
/* WHICH ARE CONTAINED IN THE TABLES. */
/* Computing 2nd power */
	    d__1 = scveos_1.tablex[i__ + (j + 532) * 63 - 4852];
	    scveos_1.tablex[i__ + (j + 912) * 63 - 4852] = exp(const1_1.cln * 
		    scveos_1.tablex[i__ + (j + 380) * 63 - 4852]) * 
		    scveos_1.tablex[i__ + (j + 684) * 63 - 4852] - exp(
		    const1_1.cln * (scveos_1.tablex[i__ + (j + 76) * 63 - 
		    4852] - scveos_1.tablex[i__ + (j + 304) * 63 - 4852] - 
		    scveos_1.tlogx[i__ - 1])) * (d__1 * d__1) / 
		    scveos_1.tablex[i__ + (j + 608) * 63 - 4852];
/* Computing 2nd power */
	    d__1 = scveos_1.tabley[i__ + (j + 532) * 63 - 4852];
	    scveos_1.tabley[i__ + (j + 912) * 63 - 4852] = exp(const1_1.cln * 
		    scveos_1.tabley[i__ + (j + 380) * 63 - 4852]) * 
		    scveos_1.tabley[i__ + (j + 684) * 63 - 4852] - exp(
		    const1_1.cln * (scveos_1.tabley[i__ + (j + 76) * 63 - 
		    4852] - scveos_1.tabley[i__ + (j + 304) * 63 - 4852] - 
		    scveos_1.tlogx[i__ - 1])) * (d__1 * d__1) / 
		    scveos_1.tabley[i__ + (j + 608) * 63 - 4852];
/* COMPUTE THE ENTROPY OF MIXING. */
/* NUMBER DENSITY OF HYDROGEN AND HELIUM */
	    y = 1. - comp_1.xenv;
	    ym1 = 1. - y;
	    denx = exp(const1_1.cln * scveos_1.tablex[i__ + (j + 304) * 63 - 
		    4852]);
	    deny = exp(const1_1.cln * scveos_1.tabley[i__ + (j + 304) * 63 - 
		    4852]);
	    dmix = 1. / (ym1 / denx + y / deny);
	    hnum = ym1 * 2. * dmix / cmh / (scveos_1.tablex[i__ + (j + 152) * 
		    63 - 4852] * 3. + 1. + scveos_1.tablex[i__ + (j + 228) * 
		    63 - 4852]);
	    henum = y * 3. * dmix / cmhe / (scveos_1.tabley[i__ + (j + 152) * 
		    63 - 4852] * 2. + 1. + scveos_1.tabley[i__ + (j + 228) * 
		    63 - 4852]);
/* HYDROGEN AND HELIUM ELECTRON NUMBER DENSITIES */
	    hnume = hnum * .5 * (1. - scveos_1.tablex[i__ + (j + 152) * 63 - 
		    4852] - scveos_1.tablex[i__ + (j + 228) * 63 - 4852]);
	    henume = const1_1.cc13 * henum * (2. - scveos_1.tabley[i__ + (j + 
		    152) * 63 - 4852] * 2. - scveos_1.tabley[i__ + (j + 228) *
		     63 - 4852]);
	    tote = hnume + henume;
	    hnume = max(hnume,1.);
	    henume = max(henume,1.);
	    tote = max(tote,1.);
	    if (hnum == 0. || henum == 0.) {
		scveos_1.smix[i__ + j * 63 - 64] = 0.;
	    } else {
		be = cmh / cmhe * (y / ym1);
		ga = (scveos_1.tablex[i__ + (j + 228) * 63 - 4852] + 1. + 
			scveos_1.tablex[i__ + (j + 152) * 63 - 4852] * 3.) * 
			1.5 / (scveos_1.tabley[i__ + (j + 152) * 63 - 4852] * 
			2. + 1. + scveos_1.tabley[i__ + (j + 228) * 63 - 4852]
			);
		xd = 1. - scveos_1.tablex[i__ + (j + 152) * 63 - 4852] - 
			scveos_1.tablex[i__ + (j + 228) * 63 - 4852];
		yd = 2. - scveos_1.tabley[i__ + (j + 152) * 63 - 4852] * 2. - 
			scveos_1.tabley[i__ + (j + 228) * 63 - 4852];
		if (xd > 0.) {
		    de = yd * 1.5 * be * ga / xd;
		} else {
		    de = 0.;
		}
		if (yd > 0.) {
		    dei = xd / (yd * 1.5 * be * ga);
		} else {
		    dei = 0.;
		}
		tnum = hnum + henum;
		scveos_1.smix[i__ + j * 63 - 64] = ym1 / cmh * 2. / (
			scveos_1.tablex[i__ + (j + 228) * 63 - 4852] + 1. + 
			scveos_1.tablex[i__ + (j + 152) * 63 - 4852] * 3.) * (
			log(be * ga + 1.) - hnume / tnum * log(de + 1.) + be *
			 ga * log(1. / be / ga + 1.) - henume / tnum * log(
			dei + 1.));
		scveos_1.smix[i__ + j * 63 - 64] = cboltz * scveos_1.smix[i__ 
			+ j * 63 - 64];
	    }
	}
    }
/*  NOW COMPUTE EQUATION OF STATE VARIABLES FOR THE SURFACE MIXTURE. */
    for (i__ = 1; i__ <= 63; ++i__) {
	tl = scveos_1.tlogx[i__ - 1];
	t = pow_dd(&c_b2, &tl);
/* TEMPERATURE INTERPOLATION FACTORS */
	if (i__ == 1) {
	    scveos_1.idt = 1;
	} else if (i__ == 63) {
	    scveos_1.idt = i__ - 2;
	} else {
	    scveos_1.idt = i__ - 1;
	}
	for (k = 1; k <= 3; ++k) {
	    qr[k - 1] = const1_1.cln * scveos_1.tlogx[k + scveos_1.idt - 2];
	}
	tln = const1_1.cln * tl;
	inter3_(qr, ft, ftd, &tln);
	i__1 = scveos_1.nptsx[i__ - 1];
	for (j = 1; j <= i__1; ++j) {
	    pl = scveos_1.tablex[i__ + (j + 76) * 63 - 4852];
	    dl = scveos_1.tablex[i__ + (j + 304) * 63 - 4852];
	    x = comp_1.xenv;
	    z__ = comp_1.zenv;
	    y = 1. - x - z__;
	    p = pow_dd(&c_b2, &pl);
/* INCLUDE RADIATION PRESSURE IN THE EQUATION OF STATE. */
/* Computing 2nd power */
	    d__2 = t;
/* Computing 2nd power */
	    d__1 = d__2 * d__2;
	    prad = const2_1.ca3 * (d__1 * d__1);
	    pgas = p;
	    p += prad;
	    pl = d_lg10(&p);
/*  DENSITY : ADD INVERSELY : 1/RHO = X/RHO(X) + Y/RHO(Y) + Z/RHO(Z) */
	    denx = exp(const1_1.cln * scveos_1.tablex[i__ + (j + 304) * 63 - 
		    4852]);
	    deny = exp(const1_1.cln * scveos_1.tabley[i__ + (j + 304) * 63 - 
		    4852]);
	    denz = exp(const1_1.cln * scveos_1.tablez[i__ + (j + 304) * 63 - 
		    4852]);
	    d__ = 1. / (x / denx + y / deny + z__ / denz);
	    dl = d_lg10(&d__);
/* D LN RHO/ D LN P = QDP */
/* FOR GAS PRESSURE QDP(TOT) = QDP(X)*X*RHO/RHO(X)+QDP(Y)*Y*RHO/RHO(Y) */
/* FOR RADIATION PRESSURE QDP = 0, SO QDP(TOT) = QDP(GAS)*P/PGAS */
	    qdp0 = scveos_1.tablex[i__ + (j + 608) * 63 - 4852] * x * (d__ / 
		    denx) + scveos_1.tabley[i__ + (j + 608) * 63 - 4852] * y *
		     (d__ / deny) + scveos_1.tablez[i__ + (j + 988) * 63 - 
		    4852] * z__ * (d__ / denz);
/* D LN RHO/ D LN T = QDT (NOTE : D LN P/ D LN T = QPT) */
/* FOR GAS PRESSURE, CORRECT AS PER QDP */
/* FOR RADIATION PRESSURE, USE QDT = QDP*QPT.  CORRECT QPT FOR */
/* RADIATION PRESSURE AND USE THE CORRECTED QDP, QPT TO GET QDT. */
	    qdt0 = x * (d__ / denx) * scveos_1.tablex[i__ + (j + 532) * 63 - 
		    4852] + y * (d__ / deny) * scveos_1.tabley[i__ + (j + 532)
		     * 63 - 4852] + z__ * (d__ / denz) * scveos_1.tablez[i__ 
		    + (j + 760) * 63 - 4852];
	    qpt0 = -qdt0 / qdp0;
	    sx = exp(const1_1.cln * scveos_1.tablex[i__ + (j + 380) * 63 - 
		    4852]);
	    sy = exp(const1_1.cln * scveos_1.tabley[i__ + (j + 380) * 63 - 
		    4852]);
/* ENTROPY.  OBEYS ADDITIVE VOLUME RULE, BUT ALSO NEED TO INCLUDE THE */
/* ENTROPY OF MIXING. */
	    s0 = x * sx + y * sy + scveos_1.smix[i__ + j * 63 - 64];
	    qsmixt = ftd[0] * scveos_1.smix[scveos_1.idt + j * 63 - 64] + ftd[
		    1] * scveos_1.smix[scveos_1.idt + 1 + j * 63 - 64] + ftd[
		    2] * scveos_1.smix[scveos_1.idt + 2 + j * 63 - 64];
/* D LN S/ D LN T */
	    qst0 = (x * sx * scveos_1.tablex[i__ + (j + 684) * 63 - 4852] + y 
		    * sy * scveos_1.tabley[i__ + (j + 684) * 63 - 4852] + 
		    qsmixt) / s0;
/*  CP = S*(D LN S/ D LN T)|P IS TABULATED. USE */
/*  CP = DU/DT + P*(D LN RHO/D LN T)**2/RHO/T/(D LN RHO/ D LN P) */
/*  TO INCLUDE THE EFFECTS OF RADIATION PRESSURE. */
/* CP (GAS PRESSURE ONLY). */
/* Computing 2nd power */
	    d__1 = scveos_1.tablez[i__ + (j + 760) * 63 - 4852];
	    qcp0 = s0 * qst0 + z__ * (exp(const1_1.cln * scveos_1.tablez[i__ 
		    + (j + 532) * 63 - 4852]) + pgas * (d__1 * d__1) / 
		    scveos_1.tablez[i__ + (j + 988) * 63 - 4852] / denz / t);
/* NOW FIND DU/DT FROM THE ORIGINAL TABLE. */
/* Computing 2nd power */
	    d__1 = qdt0;
	    qut = qcp0 - pgas * (d__1 * d__1) / qdp0 / d__ / t;
/* NOW STORE THE RELEVANT VARIABLES IN A TABLE FOR THE ENVELOPE */
/* MIXTURE. */
	    scveos_1.tablenv[i__ + (j + 76) * 63 - 4852] = scveos_1.tablex[
		    i__ + (j + 76) * 63 - 4852];
	    scveos_1.tablenv[i__ + (j + 152) * 63 - 4852] = dl;
	    scveos_1.tablenv[i__ + (j + 228) * 63 - 4852] = qdt0;
	    scveos_1.tablenv[i__ + (j + 304) * 63 - 4852] = qdp0;
	    scveos_1.tablenv[i__ + (j + 380) * 63 - 4852] = qcp0;
	    scveos_1.tablenv[i__ + (j + 456) * 63 - 4852] = qut;
	}
    }
/* NOW FIND THE FOLLOWING DERIVATIVES NUMERICALLY : */
/* D QDT/ D LN T */
/* D QDT/ D LN P */
/* D LN CP / D LN P */
/* D LN CP / D LN T */
/* D LN DEL(AD) / D LN P */
/* D LN DEL(AD) / D LN T */
    for (i__ = 1; i__ <= 63; ++i__) {
/* TEMPERATURE INTERPOLATION FACTORS */
	if (i__ == 1) {
	    scveos_1.idt = 1;
	} else if (i__ == 63) {
	    scveos_1.idt = i__ - 2;
	} else {
	    scveos_1.idt = i__ - 1;
	}
	for (k = 1; k <= 3; ++k) {
	    qr[k - 1] = const1_1.cln * scveos_1.tlogx[k + scveos_1.idt - 2];
	}
	tl = const1_1.cln * scveos_1.tlogx[i__ - 1];
	inter3_(qr, ft, ftd, &tl);
	t = exp(tl);
	i__1 = scveos_1.nptsx[i__ - 1];
	for (j = 1; j <= i__1; ++j) {
/* PRESSURE INTERPOLATION FACTORS */
	    if (j == 1) {
		scveos_1.idp = 1;
	    } else if (j == scveos_1.nptsx[i__ - 1]) {
		scveos_1.idp = j - 2;
	    } else {
		scveos_1.idp = j - 1;
	    }
	    for (k = 1; k <= 3; ++k) {
		qr[k - 1] = const1_1.cln * scveos_1.tablenv[i__ + (
			scveos_1.idp + k + 75) * 63 - 4852];
	    }
	    pl = const1_1.cln * scveos_1.tablenv[i__ + (j + 76) * 63 - 4852];
	    inter3_(qr, fp, fpd, &pl);
/* DERIVATIVES OF D LN RHO/ D LN T */
	    qdtp = scveos_1.tablenv[i__ + (scveos_1.idp + 228) * 63 - 4852] * 
		    fpd[0] + scveos_1.tablenv[i__ + (scveos_1.idp + 229) * 63 
		    - 4852] * fpd[1] + scveos_1.tablenv[i__ + (scveos_1.idp + 
		    230) * 63 - 4852] * fpd[2];
	    qdtt = scveos_1.tablenv[scveos_1.idt + (j + 228) * 63 - 4852] * 
		    ftd[0] + scveos_1.tablenv[scveos_1.idt + 1 + (j + 228) * 
		    63 - 4852] * ftd[1] + scveos_1.tablenv[scveos_1.idt + 2 + 
		    (j + 228) * 63 - 4852] * ftd[2];
/* DERIVATIVES OF LN CP */
	    for (k = 1; k <= 3; ++k) {
		qr[k - 1] = log(scveos_1.tablenv[i__ + (scveos_1.idp + k + 
			379) * 63 - 4852]);
	    }
	    qcpp = qr[0] * fpd[0] + qr[1] * fpd[1] + qr[2] * fpd[2];
	    for (k = 1; k <= 3; ++k) {
		ii = scveos_1.idt + k - 1;
/* Computing MIN */
		i__2 = scveos_1.nptsx[ii - 1];
		jj = min(i__2,j);
		qr[k - 1] = log(scveos_1.tablenv[ii + (jj + 380) * 63 - 4852])
			;
	    }
	    qcpt = qr[0] * ftd[0] + qr[1] * ftd[1] + qr[2] * ftd[2];
/* DERIVATIVES OF DU/DT */
	    for (k = 1; k <= 3; ++k) {
		ii = scveos_1.idt + k - 1;
/* Computing MIN */
		i__2 = scveos_1.nptsx[ii - 1];
		jj = min(i__2,j);
		qr[k - 1] = scveos_1.tablenv[ii + (jj + 456) * 63 - 4852];
		qr[k - 1] = scveos_1.tablenv[scveos_1.idt + k - 1 + (j + 456) 
			* 63 - 4852];
	    }
	    qat = qr[0] * ftd[0] + qr[1] * ftd[1] + qr[2] * ftd[2];
	    for (k = 1; k <= 3; ++k) {
		qr[k - 1] = scveos_1.tablenv[i__ + (scveos_1.idp + k + 455) * 
			63 - 4852];
	    }
	    qap = qr[0] * fpd[0] + qr[1] * fpd[1] + qr[2] * fpd[2];
/* D/D LN RHO (D LN P/D LN RHO) */
	    for (k = 1; k <= 3; ++k) {
		qr[k - 1] = const1_1.cln * scveos_1.tablenv[i__ + (
			scveos_1.idp + k + 151) * 63 - 4852];
	    }
	    dln = const1_1.cln * scveos_1.tablenv[i__ + (j + 152) * 63 - 4852]
		    ;
	    inter3_(qr, fp, fpd, &dln);
	    qpdd = fpd[0] / scveos_1.tablenv[i__ + (scveos_1.idp + 304) * 63 
		    - 4852] + fpd[1] / scveos_1.tablenv[i__ + (scveos_1.idp + 
		    305) * 63 - 4852] + fpd[2] / scveos_1.tablenv[i__ + (
		    scveos_1.idp + 306) * 63 - 4852];
	    scveos_1.tablenv[i__ + (j + 532) * 63 - 4852] = qdtp;
	    scveos_1.tablenv[i__ + (j + 608) * 63 - 4852] = qdtt;
	    scveos_1.tablenv[i__ + (j + 684) * 63 - 4852] = qpdd;
	    scveos_1.tablenv[i__ + (j + 760) * 63 - 4852] = qcpt;
	    scveos_1.tablenv[i__ + (j + 836) * 63 - 4852] = qap;
	    scveos_1.tablenv[i__ + (j + 912) * 63 - 4852] = qat;
	}
    }
    return 0;
} /* setscv_ */

