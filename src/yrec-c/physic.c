/* physic.f -- translated by f2c (version 20061008).
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
    doublereal yenv, y3env;
} comp2_;

#define comp2_1 comp2_

struct {
    doublereal cln, clni, c4pi, c4pil, c4pi3l, cc13, cc23, cpi;
} const1_;

#define const1_1 const1_

struct {
    doublereal cgas, ca3, ca3l, csig, csigl, cgl, cmkh, cmkhn;
} const2_;

#define const2_1 const2_

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
    doublereal cp[5000], hamu[5000], sqdt[5000], thdif[5000], visc[5000];
} temp_;

#define temp_1 temp_

struct {
    doublereal qwrmax[5000], qwrmx0[5000];
} dwmax_;

#define dwmax_1 dwmax_

struct {
    logical lmhd;
    integer iomhd1, iomhd2, iomhd3, iomhd4, iomhd5, iomhd6, iomhd7, iomhd8;
} mhd_;

#define mhd_1 mhd_

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

/* $$$$$$ */
/*       SUBROUTINE PHYSIC(FP,FT,HCOMP,HD,HG,HL,HP,HR,HS,HT,LC,LCZ,M,TEFFL)  ! KC 2025-05-31 */
/* Subroutine */ int physic_(doublereal *fp, doublereal *ft, doublereal *
	hcomp, doublereal *hd, doublereal *hg, doublereal *hl, doublereal *hp,
	 doublereal *hr, doublereal *hs, doublereal *ht, logical *lc, integer 
	*m, doublereal *teffl)
{
    /* Initialized data */

    static doublereal atomwt[4] = { 1.007825,4.002603,12.,3.01603 };

    /* System generated locals */
    integer i__1;
    doublereal d__1;

    /* Builtin functions */
    double exp(doublereal), sqrt(doublereal);

    /* Local variables */
    static doublereal b, d__;
    static integer i__, k;
    static doublereal o, p, t, x, z__, hf[4], dl;
    static integer im;
    static doublereal pl, sl, tl, rl, ol, del, eta, fpl, amu, qcp, qdp, ftl, 
	    emu, qdt, qat, qap, qod, vel, rmu, qot, dfx1, dfx2, dfx3, dfx4, 
	    amu2, emu2, dela, beta, dmid, gmid, hold[4], delr, qact, qacp, 
	    qacr, pmid, qcpp, temp, qcpt, qdtp, qdtt, beta14, betai;
    static integer ksaha;
    static doublereal hsmid;
    static logical latmo, lconv;
    static doublereal fxion[3];
    extern /* Subroutine */ int meqos_(doublereal *, doublereal *, doublereal 
	    *, doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *), intrp2_(doublereal *, 
	    doublereal *, doublereal *);
    static doublereal delamd, delmid;
    static logical locond;
    extern /* Subroutine */ int tpgrad_(doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, logical *, logical *, doublereal *, doublereal *, 
	    doublereal *);
    static logical lderiv;
    extern /* Subroutine */ int eqstat_(doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, logical *,
	     logical *, integer *), viscos_(doublereal *, doublereal *, 
	    doublereal *, integer *), getopac_(doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *);

/* DBG 7/92 COMMON BLOCK ADDED TO COMPUTE DEBYE-HUCKEL CORRECTION. */
/*      *     FXION(3),FP(JSON),FT(JSON),ATOMWT(4),LCZ(JSON),  ! KC 2025-05-31 */
    /* Parameter adjustments */
    --lc;
    --ht;
    --hs;
    --hr;
    --hp;
    --hl;
    --hg;
    --hd;
    hcomp -= 16;
    --ft;
    --fp;

    /* Function Body */
/*  FIND ACTUAL AND ADIABATIC TEMPERATURE GRADIENTS,OPACITY,AND */
/*  MEAN MOLECULAR WEIGHT FOR ALL RADIATIVE SHELLS. */
    lderiv = FALSE_;
    locond = FALSE_;
    latmo = FALSE_;
    optab_1.idt = 15;
    for (i__ = 1; i__ <= 4; ++i__) {
	optab_1.idd[i__ - 1] = 5;
/* L25: */
    }
    i__1 = *m;
    for (im = 1; im <= i__1; ++im) {
	sl = hs[im];
	tl = ht[im];
	pl = hp[im];
	rl = hr[im];
	b = hl[im];
	x = hcomp[im * 15 + 1];
	z__ = hcomp[im * 15 + 3];
	dl = hd[im];
	fpl = fp[im];
	ftl = ft[im];
	if (mhd_1.lmhd) {
	    meqos_(&tl, &t, &pl, &p, &dl, &d__, &x, &z__, &beta, &betai, &
		    beta14, fxion, &rmu, &amu, &emu, &eta, &qdt, &qdp, &qcp, &
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
		    beta14, fxion, &rmu, &amu, &emu, &eta, &qdt, &qdp, &qcp, &
		    dela, &qdtt, &qdtp, &qat, &qap, &qcpt, &qcpp, &lderiv, &
		    latmo, &ksaha);
	}
	getopac_(&dl, &tl, &x, &z__, &o, &ol, &qod, &qot, fxion);
	dpmix_1.iovim = im;
	tpgrad_(&tl, &t, &pl, &p, &d__, &rl, &sl, &b, &o, &qdt, &qdp, &qot, &
		qod, &qcp, &del, &delr, &dela, &qdtt, &qdtp, &qat, &qap, &
		qact, &qacp, &qacr, &qcpt, &qcpp, &vel, &lderiv, &lconv, &fpl,
		 &ftl, teffl);
	lc[im] = lconv;
	scrtch_1.sdel[im * 3 - 3] = delr;
	scrtch_1.sdel[im * 3 - 2] = del;
	scrtch_1.sdel[im * 3 - 1] = dela;
/*  FIND NEW RUN OF MEAN MOLECULAR WEIGHT ASSUMING FULLY IONIZED GAS. */
/*  AMUENV IS(1/MEAN MOLECULAR WEIGHT PER ION OF THE SURFACE MIXTURE.) */
	dfx1 = hcomp[im * 15 + 1] - comp_1.xenv;
	dfx2 = hcomp[im * 15 + 2] - comp2_1.yenv;
	dfx3 = hcomp[im * 15 + 3] - comp_1.zenv;
	dfx4 = hcomp[im * 15 + 4] - comp2_1.y3env;
	temp = comp_1.amuenv + dfx1 / atomwt[0] + dfx2 / atomwt[1] + dfx3 / 
		atomwt[2] + dfx4 / atomwt[3];
	amu2 = 1. / temp;
	temp = hcomp[im * 15 + 1] / atomwt[0] + (hcomp[im * 15 + 4] / atomwt[
		3] + hcomp[im * 15 + 2] / atomwt[1]) * 2. + hcomp[im * 15 + 3]
		 * .5;
	emu2 = 1. / temp;
	temp_1.hamu[im - 1] = amu2 * emu2 / (amu2 + emu2);
	scrtch_1.so[im - 1] = o;
	temp_1.cp[im - 1] = qcp;
	temp_1.sqdt[im - 1] = qdt;
/* JVS 10/13 Always want SVEL */
	scrtch_1.svel[im - 1] = vel;
/*         IF(LC(IM))THEN */
/*            SVEL(IM) = VEL */
/*         ELSE */
/*            SVEL(IM) = 0.0D0 */
/*         ENDIF */
/* L30: */
    }
/*  FIND THE THERMOMETRIC DIFFUSIVITY AND KINEMATIC VISCOSITY. */
/*       CALL VISCOS(HCOMP,HD,HT,LC,M)  ! KC 2025-05-31 */
    viscos_(&hcomp[16], &hd[1], &ht[1], m);
/*  FIND THE RUN OF MAXIMUM ALLOWABLE D OMEGA/D LNR AND THE RUN OF ACTUAL */
/*  D OMEGA/D LN R FOR ALL RADIATIVE ZONES. */
/*  IF THE GRADIENT OF OMEGA EXCEEDS THE CRITICAL VALUE FOR THE SHEAR */
/*  INSTABILITY, A SHORT TIMESCALE INSTABILITY OCCURS.  MIX ALL ADJACENT */
/*  UNSTABLE ZONES TO A MARGINALLY STABLE STATE. */
    i__1 = *m;
    for (im = 2; im <= i__1; ++im) {
/*  SKIP CONVECTIVE REGIONS */
	if (lc[im] && lc[im - 1]) {
	    dwmax_1.qwrmax[im - 1] = 0.;
	    goto L100;
	}
/*  NOW CHECK FOR SHEAR INSTABILITY -REF.ENDAL&SOFIA APJ 220:279(1978) */
/*  THERMODYNAMIC QUANTITIES ARE CALCULATED AT THE SHELL MIDPOINT BY */
/*  4-POINT LAGRANGIAN INTERPOLATION. */
	if (im <= 2) {
	    k = 1;
	} else if (im == *m) {
	    k = *m - 3;
	} else {
	    k = im - 2;
	}
	for (i__ = 1; i__ <= 4; ++i__) {
	    hold[i__ - 1] = hs[i__ + k - 1];
/* L90: */
	}
/*  USE 4-POINT LAGRANGIAN INTERPOLATION TO FIND PHYSICAL VARIABLES */
/*  AT THE INTERFACE BEING TESTED. */
	hsmid = (hs[im] + hs[im - 1]) * .5;
	intrp2_(hold, hf, &hsmid);
	pmid = hp[k] * hf[0] + hp[k + 1] * hf[1] + hp[k + 2] * hf[2] + hp[k + 
		3] * hf[3];
	dmid = hd[k] * hf[0] + hd[k + 1] * hf[1] + hd[k + 2] * hf[2] + hd[k + 
		3] * hf[3];
	delmid = scrtch_1.sdel[k * 3 - 2] * hf[0] + scrtch_1.sdel[(k + 1) * 3 
		- 2] * hf[1] + scrtch_1.sdel[(k + 2) * 3 - 2] * hf[2] + 
		scrtch_1.sdel[(k + 3) * 3 - 2] * hf[3];
	delamd = scrtch_1.sdel[k * 3 - 1] * hf[0] + scrtch_1.sdel[(k + 1) * 3 
		- 1] * hf[1] + scrtch_1.sdel[(k + 2) * 3 - 1] * hf[2] + 
		scrtch_1.sdel[(k + 3) * 3 - 1] * hf[3];
	gmid = hg[k] * hf[0] + hg[k + 1] * hf[1] + hg[k + 2] * hf[2] + hg[k + 
		3] * hf[3];
/* Computing 2nd power */
	d__1 = gmid;
	temp = exp(const1_1.cln * (dmid - pmid)) * (delamd - delmid) * (d__1 *
		 d__1);
	if (temp > 0.) {
	    dwmax_1.qwrmax[im - 1] = sqrt(temp) * 2.;
	} else {
	    dwmax_1.qwrmax[im - 1] = 0.;
	}
L100:
	;
    }
    return 0;
} /* physic_ */

