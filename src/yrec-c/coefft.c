/* coefft.f -- translated by f2c (version 20061008).
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
    logical lstore, lstatm, lstenv, lstmod, lstphys, lstrot, lscrib, lstch, 
	    lphhd;
} ccout_;

#define ccout_1 ccout_

struct {
    integer npenv, nprtmod, nprtpt, npoint;
} ccout1_;

#define ccout1_1 ccout1_

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
    doublereal atime[14], tcut[5], tscut, tenv0, tenv1, tenv, tgcut;
} ctlim_;

#define ctlim_1 ctlim_

struct {
    logical lexcom;
} flag_;

#define flag_1 flag_

struct {
    doublereal optol, zsi;
    integer idt, idd[4];
} optab_;

#define optab_1 optab_

struct {
    doublereal sesum[5000], seg[35000]	/* was [7][5000] */, sbeta[5000], 
	    seta[5000];
    logical locons[5000];
    doublereal so[5000], sdel[15000]	/* was [3][5000] */, sfxion[15000]	
	    /* was [3][5000] */, svel[5000], scp[5000];
} scrtch_;

#define scrtch_1 scrtch_

struct {
    doublereal wnew, walpcz, acfpft;
    integer itfp1, itfp2;
    logical lrot, linstb, lwnew;
} rot_;

#define rot_1 rot_

struct {
    doublereal xmsol;
    logical lpulse;
    integer ipver;
} pulse_;

#define pulse_1 pulse_

struct {
    doublereal pqdp[5000], pqed[5000], pqet[5000], pqod[5000], pqot[5000], 
	    pqcp[5000], prmu[5000], pqdt[5000], pemu[5000];
    logical lpumod;
} pulse1_;

#define pulse1_1 pulse1_

struct {
    doublereal qqdp, qqed, qqet, qqod, qqot, qdel, qdela, qqcp, qrmu, qtl, 
	    qpl, qdl, qo, qol, qt, qp, qqdt, qemu, qd, qfs;
} pulse2_;

#define pulse2_1 pulse2_

struct {
    logical lmhd;
    integer iomhd1, iomhd2, iomhd3, iomhd4, iomhd5, iomhd6, iomhd7, iomhd8;
} mhd_;

#define mhd_1 mhd_

struct {
    doublereal flux[10], fluxtot[10], clsnu, gasnu;
} fluxes_;

#define fluxes_1 fluxes_

struct {
    integer niter4;
    logical lnews, lsnu;
} neweng_;

#define neweng_1 neweng_

struct {
    doublereal ealpca, enu;
} neweps_;

#define neweps_1 neweps_

struct {
    doublereal cdh, etadh0, etadh1, zdh[18], xxdh, yydh, zzdh, dhnue[18];
    logical ldh;
} debhu_;

#define debhu_1 debhu_

struct {
    doublereal dpenv, alphac, alphae, alpham, betac;
    integer iov1, iov2, iovim;
    logical lovstc, lovste, lovstm, lsemic, ladov, lovmax;
} dpmix_;

#define dpmix_1 dpmix_

struct {
    doublereal alfmlt, phmlt, cmxmlt, valfmlt[5000], vphmlt[5000], vcmxmlt[
	    5000];
} pualpha_;

#define pualpha_1 pualpha_

struct {
    doublereal gam1[5000];
    logical lsound;
} sound_;

#define sound_1 sound_

struct {
    doublereal derot[5000];
} roten_;

#define roten_1 roten_

struct {
    doublereal sqod[5000], sqot[5000], sqed[5000], sqet[5000], fracnuc[5000];
} rotder_;

#define rotder_1 rotder_

struct {
    doublereal dmdt0, fczdmdt, ftotdmdt, compacc[15], creim;
    logical lreimer, lmdot;
} masschg_;

#define masschg_1 masschg_

struct {
    doublereal sacc, scen, smass0, dlogp, dlogt;
} masschg2_;

#define masschg2_1 masschg2_

struct {
    doublereal enghe3, he3all, umhe33[5000], umheal[5000];
} grab_;

#define grab_1 grab_


/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */
/* COEFFT */
/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */
/* Subroutine */ int coefft_(doublereal *delts, integer *m, doublereal *hd, 
	doublereal *hha, doublereal *hhb, doublereal *hhc, doublereal *hl, 
	doublereal *hmax, doublereal *hp, doublereal *hpp, doublereal *hr, 
	doublereal *hs, doublereal *hs1, doublereal *hs2, doublereal *ht, 
	doublereal *htt, doublereal *hcomp, logical *lc, doublereal *tlumx, 
	logical *latmo, logical *lderiv, logical *lmix, logical *locond, 
	doublereal *qdt, doublereal *qdp, integer *ksaha, doublereal *fp, 
	doublereal *ft, doublereal *hkerot, doublereal *hkeroto, integer *
	jenv, doublereal *teffl)
{
    /* System generated locals */
    integer i__1;
    doublereal d__1;

    /* Builtin functions */
    double exp(doublereal);

    /* Local variables */
    static doublereal b, d__, e;
    static integer j;
    static doublereal o, p, t, x, y, z__, eg[6], dl;
    static integer im;
    static doublereal dt, pl, sl, tl, rl;
    static integer iu;
    static doublereal ol, qr, ql, cv, hf1[5000], hf2[5000];
    static integer im1;
    static doublereal hr1[5000], hr2[5000], hr3[5000], hr4[5000], hr5[5000], 
	    hr6[5000], hr7[5000], hr8[5000], hr9[5000], xh2, qp0, qt0, qr0, 
	    ql0, eca, del, eta, hr10[5000], hr11[5000], hr12[5000], hr13[5000]
	    , xc12, thl, xc13, xn14, xn15, xo16, xo17, xo18, fpl, ftl, rmu, 
	    amu, emu, qcp, qat, qap, qod, qot, vel, qrr, qrp, qrt, qpr, qpp, 
	    qtr, qtp, qtt, qlt, qlp, qed, qet, cht, xhe3, xbe9, qlp0, qpp0, 
	    qtl0, xli6, xli7, qpr0, sum1, qtr0, qtp0, qtt0, qrr0, qrp0, qrt0, 
	    qlt0, egg11, dela, egg22, egg33, egg44, beta, egg55, time, delr, 
	    qact, qdtt, qdtp, qcpt, qcpp, qacp, qacr, httt, hppp, entr, chrh, 
	    etot, entr1, entr2, entr3, beta14;
    extern /* Subroutine */ int engeb_(doublereal *, doublereal *, doublereal 
	    *, doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, integer *,
	     doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *);
    static doublereal betai, cccql, fxion[3], timei;
    extern /* Subroutine */ int meqos_(doublereal *, doublereal *, doublereal 
	    *, doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *);
    static logical lconv;
    static doublereal qtemp, egrav, esumi;
    extern /* Subroutine */ int reduce_(integer *, doublereal *, doublereal *,
	     doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *), tpgrad_(
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, logical *, logical *, 
	    doublereal *, doublereal *, doublereal *);
    static doublereal deltsi, egneut;
    extern /* Subroutine */ int eqstat_(doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, logical *,
	     logical *, integer *);
    static logical lntrpy;
    extern /* Subroutine */ int getopac_(doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *);

/*      *MODEL,FP,FT,HKEROT,HKEROTO,JENV,TEFFL)  ! KC 2025-05-31 */
/* 2/91 MHP FLAG TO TOGGLE BETWEEN OLD/NEW ENERGY GENERATION ROUTINES */
/* ADDED (COMMON BLOCK NEWENG). */
/* DBG PULSE */
/* DBG */
/* *** MHP 5/90 ADD COMMON BLOCK FOR SOLAR NEUTRINO I/O */
/* *** MHP 5/91 ADD COMMON BLOCK FOR ENERGY FROM ALPHA CAPTURE REACTIONS */
/*  AND LOSSES FROM NEUTRINO-COOLED CORES IN EVOVLED STARS. */
/* DBG 7/92 COMMON BLOCK ADDED TO COMPUTE DEBYE-HUCKEL CORRECTION. */
/* DBG 7/95 To store variables for pulse output */
/* MHP 7/96 COMMON BLOCK ADDED FOR SOUND SPEED */
/* MHP 06/02 COMMON BLOCK ADDED FOR DERIVATIVES OF */
/* CAPPA AND EPSILON */
/* JVS 10/11 Common block for He3+He3 luminosity */
/* JVS end */
/* 7/91 MHP */
/* ZERO OUT SOLAR NEUTRINO FLUXES. */
/* FLUXTOT = TOTAL FLUX OF EACH OF THE NEUTRINOS PRODUCED IN THE SUN */
    /* Parameter adjustments */
    --hkeroto;
    --hkerot;
    --ft;
    --fp;
    --tlumx;
    --lc;
    hcomp -= 16;
    --htt;
    --ht;
    --hs2;
    --hs1;
    --hs;
    --hr;
    --hpp;
    --hp;
    --hmax;
    --hl;
    --hhc;
    hhb -= 5;
    hha -= 13;
    --hd;

    /* Function Body */
    if (neweng_1.lsnu) {
	for (j = 1; j <= 10; ++j) {
	    fluxes_1.fluxtot[j - 1] = 0.;
/* L5: */
	}
    }
/* MHP 10/02 QFPR,QFTR NOT USED - OMIT */
/*      IF(.NOT.LROT) THEN */
/*       QFPR = 0.0D0 */
/*       QFTR = 0.0D0 */
/*      ENDIF */
    *locond = TRUE_;
    *lderiv = TRUE_;
    *latmo = FALSE_;
    *lmix = FALSE_;
    lntrpy = *delts > 0.;
    if (lntrpy) {
	deltsi = 1. / *delts;
	time = 3.1558e7;
	timei = 3.1688e-8;
    }
    for (j = 1; j <= 8; ++j) {
	tlumx[j] = 0.;
/* L10: */
    }
    optab_1.idt = 15;
    for (j = 1; j <= 4; ++j) {
	optab_1.idd[j - 1] = 5;
/* L15: */
    }
    i__1 = *m;
    for (im = 1; im <= i__1; ++im) {
/* SET UP LOCAL VARIABLES FOR CALLS TO BASIC PHYSICS ROUTINES */
	thl = 0.;
	sl = hs[im];
	tl = ht[im];
	pl = hp[im];
	rl = hr[im];
	b = hl[im];
	x = hcomp[im * 15 + 1];
	y = hcomp[im * 15 + 2];
	z__ = hcomp[im * 15 + 3];
	xhe3 = hcomp[im * 15 + 4];
	xc12 = hcomp[im * 15 + 5];
	xc13 = hcomp[im * 15 + 6];
	xn14 = hcomp[im * 15 + 7];
	xn15 = hcomp[im * 15 + 8];
	xo16 = hcomp[im * 15 + 9];
	xo17 = hcomp[im * 15 + 10];
	xo18 = hcomp[im * 15 + 11];
/* MHP 05/02 DEFINE THESE ALWAYS; THEY */
/* ARE PASSED TO THE SR ANYWAY. */
/*       IF(LEXCOM) THEN */
	xh2 = hcomp[im * 15 + 12];
	xli6 = hcomp[im * 15 + 13];
	xli7 = hcomp[im * 15 + 14];
	xbe9 = hcomp[im * 15 + 15];
/*       ENDIF */
	iu = im;
	dl = hd[im];
	fpl = fp[im];
	ftl = ft[im];
/* YC   IF LMHD USE MHD EQUATION OF STATE. */
	if (mhd_1.lmhd) {
	    meqos_(&tl, &t, &pl, &p, &dl, &d__, &x, &z__, &beta, &betai, &
		    beta14, fxion, &rmu, &amu, &emu, &eta, qdt, qdp, &qcp, &
		    dela, &qdtt, &qdtp, &qat, &qap, &qcpt, &qcpp);
/*      *           QCPP,LDERIV,LATMO,KSAHA)  ! KC 2025-05-31 */
	} else {
	    if (debhu_1.ldh) {
		debhu_1.xxdh = hcomp[im * 15 + 1];
		debhu_1.yydh = hcomp[im * 15 + 2] + hcomp[im * 15 + 4];
		debhu_1.zzdh = hcomp[im * 15 + 3];
		debhu_1.zdh[0] = hcomp[im * 15 + 5] + hcomp[im * 15 + 6];
		debhu_1.zdh[1] = hcomp[im * 15 + 7] + hcomp[im * 15 + 8];
		debhu_1.zdh[2] = hcomp[im * 15 + 9] + hcomp[im * 15 + 10] + 
			hcomp[im * 15 + 11];
	    }
	    eqstat_(&tl, &t, &pl, &p, &dl, &d__, &x, &z__, &beta, &betai, &
		    beta14, fxion, &rmu, &amu, &emu, &eta, qdt, qdp, &qcp, &
		    dela, &qdtt, &qdtp, &qat, &qap, &qcpt, &qcpp, lderiv, 
		    latmo, ksaha);
	}
/* DBG 12/95 GET OPACITY */
	getopac_(&dl, &tl, &x, &z__, &o, &ol, &qod, &qot, fxion);
	dpmix_1.iovim = im;
	tpgrad_(&tl, &t, &pl, &p, &d__, &rl, &sl, &b, &o, qdt, qdp, &qot, &
		qod, &qcp, &del, &delr, &dela, &qdtt, &qdtp, &qat, &qap, &
		qact, &qacp, &qacr, &qcpt, &qcpp, &vel, lderiv, &lconv, &fpl, 
		&ftl, teffl);
	hd[im] = dl;
/* COMPUTE DERIVATIVES */
/*       IF(LROT) THEN */
/*  CALCULATE D(LOG FP)/D(LOG R) AND D(LOG FT)/D(LOG R) */
/*            IF(IM.GT.1) THEN */
/*             IF(IM.LT.M) THEN */
/*              QFPR = (DLOG(FP(IM+1)) - DLOG(FP(IM-1)))/ */
/*     *                 (CLN*(HR(IM+1) - HR(IM-1))) */
/*              QFTR = (DLOG(FT(IM+1)) - DLOG(FT(IM-1)))/ */
/*     *                 (CLN*(HR(IM+1) - HR(IM-1))) */
/*             ELSE */
/*              QFPR = (DLOG(FP(M)) - DLOG(FP(M-1)))/ */
/*     *                 (CLN*(HR(M) - HR(M-1))) */
/*              QFTR = (DLOG(FT(M)) - DLOG(FT(M-1)))/ */
/*     *                 (CLN*(HR(M) - HR(M-1))) */
/*             ENDIF */
/*          ELSE */
/*             QFPR = (DLOG(FP(2)) - DLOG(FP(1)))/ */
/*     *              (CLN*(HR(2) - HR(1))) */
/*             QFTR = (DLOG(FT(2)) - DLOG(FT(1)))/ */
/*     *              (CLN*(HR(2) - HR(1))) */
/*          ENDIF */
/*       ENDIF */
	qtemp = const1_1.c4pil + rl + rl + rl;
	qr = exp(const1_1.cln * (sl - dl - qtemp));
	qrr = -qr - qr - qr;
	qrp = -qr * *qdp;
	qrt = -qr * *qdt;
	pulse2_1.qp = -exp(const1_1.cln * (const2_1.cgl + sl + sl - pl - 
		qtemp - rl)) * fp[im];
/*       QPR = -QP - QP - QP - QP*(1.0D0 - QFPR) */
	qpr = -pulse2_1.qp - pulse2_1.qp - pulse2_1.qp - pulse2_1.qp;
	qpp = -pulse2_1.qp;
	lc[im] = lconv;
	pulse2_1.qt = del * pulse2_1.qp;
	qtr = -pulse2_1.qt - pulse2_1.qt - pulse2_1.qt - pulse2_1.qt;
/*       QTR = -QT - QT - QT - QT*(1.0D0 - QFTR) */
	if (! lconv) {
/* TEMPERATURE GRADIENT IS RADIATIVE */
	    pulse2_1.qtl = const1_1.clni * pulse2_1.qt / b;
	    qtp = pulse2_1.qt * qod * *qdp;
	    qtt = pulse2_1.qt * (qot - 4. + qod * *qdt);
	} else {
/* TEMPERATURE GRADIENT IS CONVECTIVE */
	    pulse2_1.qtl = 0.;
	    qtp = pulse2_1.qt * (qacp - 1.);
	    qtt = pulse2_1.qt * qact;
	    qtr += pulse2_1.qt * qacr;
	}
	ql = 0.;
	qlt = 0.;
	qlp = 0.;
	if (tl > ctlim_1.tcut[0]) {
/* SET UP NUCLEAR ENERGY TERMS */
	    engeb_(&egg11, &egg22, &egg33, &egg44, &egg55, &qed, &qet, &sum1, 
		    &dl, &tl, &x, &y, &xhe3, &xc12, &xc13, &xn14, &xo16, &
		    xo18, &xh2, &iu, hr1, hr2, hr3, hr4, hr5, hr6, hr7, hr8, 
		    hr9, hr10, hr11, hr12, hr13, hf1, hf2);
/*      *           TL,QDT,QDP,X,Y,Z,XHE3,XC12,XC13,XN14,XN15,XO16,XO17, */
/*      *           XO18,XH2,XLI6,XLI7,XBE9,IU,HR1,HR2,HR3,HR4,HR5,HR6,HR7,  ! KC 2025-05-31 */
	    e = sum1;
	    eg[0] = egg11;
	    eg[1] = egg22;
	    eg[2] = egg33;
	    eg[3] = egg44;
	    eg[4] = egg55;
	    eg[5] = neweps_1.enu;
	    eca = neweps_1.ealpca;
/* 7/91 MHP */
/* CONVERT NEUTRINO FLUX RATES (UNITS 10**10 ERGS PER GM) */
/* TO UNITS OF 10**10 ERGS BY MULTIPLYING BY THE MASS. */
	    if (neweng_1.lsnu) {
		for (j = 1; j <= 10; ++j) {
		    fluxes_1.fluxtot[j - 1] += fluxes_1.flux[j - 1] * hs2[im];
/* L17: */
		}
	    }
	    for (j = 1; j <= 6; ++j) {
		tlumx[j] += hs2[im] / const_1.clsun * eg[j - 1];
		thl += hs2[im] / const_1.clsun * eg[j - 1];
/* L20: */
	    }
/* JVS 10/11 Calculate the He3+He3 and sum of He3+He3 and He3+He4 luminosity */
	    grab_1.umhe33[im - 1] = hs2[im] / const_1.clsun * grab_1.enghe3;
	    grab_1.umheal[im - 1] = hs2[im] / const_1.clsun * grab_1.he3all;
/* JVS end */
	    tlumx[8] += hs2[im] / const_1.clsun * eca;
	    thl += hs2[im] / const_1.clsun * eca;
	    ql = e;
	    qlt = qlt + qet + qed * *qdt;
	    qlp += qed * *qdp;
	}
	if (lntrpy) {
/* SET UP ENTROPY TERMS */
	    dt = deltsi;
	    if (masschg_1.lmdot && masschg_1.dmdt0 > 0.) {
		if (im >= *jenv) {
		    httt = htt[im] + masschg2_1.dlogt;
		    hppp = hpp[im] + masschg2_1.dlogp;
		} else {
		    httt = htt[im];
		    hppp = hpp[im];
		}
	    } else {
		httt = htt[im];
		hppp = hpp[im];
	    }
	    if (hcomp[im * 15 + 1] > .01 && *delts < time) {
		dt = timei;
	    }
	    entr1 = p * *qdt / d__;
	    entr2 = entr1 / dela;
	    entr = (entr2 * httt - entr1 * hppp) * const1_1.cln;
	    entr3 = entr2 * const1_1.cln * httt;
/*            ENTR = (ENTR2*HTT(IM) - ENTR1*HPP(IM))*CLN */
/*            ENTR3 = ENTR2*CLN*HTT(IM) */
	    egrav = dt * entr;
	    hhc[im] = egrav;
	    tlumx[7] += hs2[im] / const_1.clsun * egrav;
	    ql += egrav;
	    qlp += dt * (entr * (1. - *qdp + qdtp) - entr1 - entr3 * qap);
	    qlt += dt * (entr * (-(*qdt) + qdtt) + entr2 - entr3 * qat);
/* 7/92 INCLUDE CHANGE IN ROTATIONAL KINETIC ENERGY IN ENERGY EQUATION. */
	    if (rot_1.lrot) {
		roten_1.derot[im - 1] = dt * (hkerot[im] - hkeroto[im]) / hs2[
			im];
		ql -= roten_1.derot[im - 1];
	    }
/* ADD CHANGE IN ENTROPY FROM ACCRETED MATERIAL */
/*            IF(LMDOT.AND.DMDT0.GT.0.0D0)THEN */
/*               IF(IM.GE.JENV)THEN */
/*                  QACC = - T*SCEN*DMDT0/CSECYR/SMASS0 */
/*                  WRITE(*,*)QL,QACC */
/*                  QL = QL + QACC */
/*               ENDIF */
/*            ENDIF */
	}
	cccql = const_1.clnsun * hs1[im];
	ql = cccql * ql;
	qlp = cccql * qlp;
	qlt = cccql * qlt;
	if (im > 1) {
/* REDUCE MATRIX FOR PAIR OF POINTS (IM-1,IM) */
	    im1 = im;
	    reduce_(&im1, &hha[13], &hhb[5], &hl[1], &hmax[1], &hp[1], &hr[1],
		     &hs[1], &ht[1], &qp0, &pulse2_1.qp, &qpr0, &qpr, &qpp0, &
		    qpp, &qt0, &pulse2_1.qt, &qtr0, &qtr, &qtl0, &
		    pulse2_1.qtl, &qtp0, &qtp, &qtt0, &qtt, &qr0, &qr, &qrr0, 
		    &qrr, &qrp0, &qrp, &qrt0, &qrt, &ql0, &ql, &qlp0, &qlp, &
		    qlt0, &qlt);
	} else {
/* SETUP CENTRAL BOUNDARY CONDITIONS */
	    hha[15] = const1_1.cc13 * *qdp;
	    hha[19] = const1_1.cc13 * *qdt;
	    hhb[7] = -const1_1.cc13 * (const1_1.c4pi3l + dl - sl) - rl;
	    hha[16] = -qlp;
	    hha[20] = -qlt;
	    hhb[8] = const1_1.clni * ql - b;
	}
	qp0 = pulse2_1.qp;
	qpr0 = qpr;
	qpp0 = qpp;
	qt0 = pulse2_1.qt;
	qtr0 = qtr;
	qtl0 = pulse2_1.qtl;
	qtp0 = qtp;
	qtt0 = qtt;
	qr0 = qr;
	qrr0 = qrr;
	qrp0 = qrp;
	qrt0 = qrt;
	ql0 = ql;
	qlp0 = qlp;
	qlt0 = qlt;
/* MHP 02/12 REMOVED RESTRICTIONS ON WHERE INTERMEDIATE VARIABLES */
/* SUCH AS OPACITY ARE SAVED; PRIOR RESTRICTIONS WERE BASED ON OBSOLETE */
/* MEMORY RESTRICTIONS IN LEGACY CODE */
/*         IF(LMDOT.AND.DMDT0.GT.0.0D0)THEN */
	scrtch_1.svel[im - 1] = vel;
/*         ENDIF */
/*  STORE VARIABLES FOR OUTPUT IN SCRIB2 IF MODEL IS TO BE PRINTED OUT */
/* DBG PULSE STORE VARIABLES FOR PULSATION OUPUT */
/* DBG 3/91 CHANGED TO ALWAYS EXECUTE THIS STUFF */
/*         LONG = MOD(MODEL,NPRT2).EQ.0 .OR. LROT */
/* MHP 10/02 LSHORT NOT USED, OMIT */
/*         LSHORT = .NOT.LONG .AND. MOD(MODEL,NPRT1).EQ.0 */
/*  ZERO OUT NUCLEAR ENERGY TERMS IF T < NUCLEAR CUTOFF. */
	if (ht[im] < ctlim_1.tcut[0]) {
	    scrtch_1.sesum[im - 1] = 0.;
	    scrtch_1.seg[im * 7 - 1] = hhc[im];
	    for (j = 1; j <= 6; ++j) {
		scrtch_1.seg[j + im * 7 - 8] = 0.;
	    }
	} else {
/*         ELSE IF(LONG) THEN */
/*  LONG OUTPUT NEEDED */
	    scrtch_1.sesum[im - 1] = eg[0] + eg[1] + eg[2] + eg[3] + eg[4];
	    scrtch_1.seg[im * 7 - 2] = eg[5];
	    scrtch_1.seg[im * 7 - 1] = hhc[im];
	    if (scrtch_1.sesum[im - 1] > 1e-22) {
		esumi = 1. / scrtch_1.sesum[im - 1];
	    } else {
		esumi = 0.;
	    }
	    for (j = 1; j <= 5; ++j) {
		scrtch_1.seg[j + im * 7 - 8] = eg[j - 1] * esumi;
	    }
/*  SHORT OUTPUT ONLY */
/*         ELSE */
/*            SESUM(IM) = EG(1)+EG(2)+EG(3)+EG(4)+EG(5) */
/*            SEG(6,IM) = EG(6) */
/*            SEG(7,IM) = HHC(IM) */
	}
	scrtch_1.sbeta[im - 1] = beta;
	scrtch_1.seta[im - 1] = eta;
	scrtch_1.locons[im - 1] = *locond;
	scrtch_1.so[im - 1] = o;
	scrtch_1.sdel[im * 3 - 3] = delr;
	scrtch_1.sdel[im * 3 - 2] = del;
	scrtch_1.sdel[im * 3 - 1] = dela;
	for (j = 1; j <= 3; ++j) {
	    scrtch_1.sfxion[j + im * 3 - 4] = fxion[j - 1];
	}
	scrtch_1.svel[im - 1] = vel;
	scrtch_1.scp[im - 1] = qcp;
/* MHP 02/12 COMMENTED CODE OUT, AS REPLICATED BELOW */
/*         IF(LSOUND) THEN */
/* MHP 7/96 CALCULATION OF GAMMA1 FROM GUENTHER 1995 P.C. */
/*            CHRH = 1.0D0/QDP */
/*            CHT = -CHRH*QDT */
/*            CV = QCP - EXP(CLN*(HP(IM)-HD(IM)-HT(IM)))*CHT**2/CHRH */
/*            GAM1(IM) = CHRH*QCP/CV */
/*            PQDP(IM) = QDP */
/*         ENDIF */
/* JVS 01/11 always want gamma: */
	chrh = 1. / *qdp;
	cht = -chrh * *qdt;
/* Computing 2nd power */
	d__1 = cht;
	cv = qcp - exp(const1_1.cln * (hp[im] - hd[im] - ht[im])) * (d__1 * 
		d__1) / chrh;
	sound_1.gam1[im - 1] = chrh * qcp / cv;
	pulse1_1.pqdp[im - 1] = *qdp;
	pulse1_1.pqdt[im - 1] = *qdt;
/* JVS END */
	if (rot_1.lrot) {
	    rotder_1.sqod[im - 1] = qod;
	    rotder_1.sqot[im - 1] = qot;
/* MHP 10/02 variable index error */
	    if (scrtch_1.sesum[im - 1] > 0.) {
/*            IF(SESUM(I).GT.0.0D0)THEN */
/*               ETOT = SESUM(I) */
/*               EGNEUT = SEG(6,I)+SEG(7,I) */
		etot = scrtch_1.sesum[im - 1];
		egneut = scrtch_1.seg[im * 7 - 2] + scrtch_1.seg[im * 7 - 1];
		rotder_1.fracnuc[im - 1] = (etot - egneut) / etot;
	    } else {
		rotder_1.fracnuc[im - 1] = 0.;
	    }
	    rotder_1.sqed[im - 1] = qed;
	    rotder_1.sqet[im - 1] = qet;
	}
/* DBG PULSE */
	if (pulse_1.lpulse) {
	    pulse1_1.pqdp[im - 1] = *qdp;
	    pulse1_1.pqed[im - 1] = qed;
	    pulse1_1.pqet[im - 1] = qet;
	    pulse1_1.pqod[im - 1] = qod;
	    pulse1_1.pqot[im - 1] = qot;
	    pulse1_1.pqcp[im - 1] = qcp;
	    pulse1_1.prmu[im - 1] = rmu;
	    pulse1_1.pemu[im - 1] = emu;
	    pulse1_1.pqdt[im - 1] = *qdt;
	    pualpha_1.valfmlt[im - 1] = pualpha_1.alfmlt;
	    pualpha_1.vphmlt[im - 1] = pualpha_1.phmlt;
	    pualpha_1.vcmxmlt[im - 1] = pualpha_1.cmxmlt;
	}
/* L30: */
    }
    return 0;
} /* coefft_ */

