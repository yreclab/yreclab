/* envint.f -- translated by f2c (version 20061008).
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
    integer ifirst, irun, istand, ifermi, iopmod, iopenv, iopatm, idyn, 
	    illdat, isnu, iscomp, ikur;
} lunum_;

#define lunum_1 lunum_

struct {
    doublereal olaol[64896]	/* was [12][104][52] */, oxa[12], ot[52], 
	    orho[104], tollaol;
    integer iolaol, numofxyz, numrho, numt;
    logical llaol, lpurez;
    integer iopurez;
} nwlaol_;

#define nwlaol_1 nwlaol_

struct {
    doublereal tau, ap, at, ad, ao, afxion[3];
} atmprt_;

#define atmprt_1 atmprt_

struct {
    doublereal xenv, zenv, zenvm, amuenv, fxenv[12], xnew, znew, stotal, senv;
} comp_;

#define comp_1 comp_

struct {
    doublereal clsun, clsunl, clnsun, cmsun, cmsunl, crsun, crsunl, cmbol;
} const_;

#define const_1 const_

struct {
    doublereal cdelrl, cmixl, cmixl2, cmixl3, clndp, csecyr;
} const3_;

#define const3_1 const3_

struct {
    doublereal cln, clni, c4pi, c4pil, c4pi3l, cc13, cc23, cpi;
} const1_;

#define const1_1 const1_

struct {
    doublereal cgas, ca3, ca3l, csig, csigl, cgl, cmkh, cmkhn;
} const2_;

#define const2_1 const2_

struct {
    doublereal atime[14], tcut[5], tscut, tenv0, tenv1, tenv, tgcut;
} ctlim_;

#define ctlim_1 ctlim_

struct {
    doublereal ep, et, er, es, ed, eo, ebeta, edel[3], efxion[3], evel;
} envprt_;

#define envprt_1 envprt_

struct {
    logical lexcom;
} flag_;

#define flag_1 flag_

struct {
    doublereal atmerr, atmd0, atmbeg, atmmin, atmmax;
} intatm_;

#define intatm_1 intatm_

struct {
    doublereal enverr, envbeg, envmin, envmax;
} intenv_;

#define intenv_1 intenv_

struct {
    doublereal stolr0;
    integer imax, nuse;
} intpar_;

#define intpar_1 intpar_

struct {
    doublereal optol, zsi;
    integer idt, idd[4];
} optab_;

#define optab_1 optab_

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
    doublereal hras;
    integer kttau, kttau0;
    logical lttau;
} atmos_;

#define atmos_1 atmos_

struct {
    logical lmhd;
    integer iomhd1, iomhd2, iomhd3, iomhd4, iomhd5, iomhd6, iomhd7, iomhd8;
} mhd_;

#define mhd_1 mhd_

struct {
    doublereal atmpl[627]	/* was [57][11] */, atmtl[57], atmgl[11], 
	    atmz;
    integer ioatm;
} atmos2_;

#define atmos2_1 atmos2_

struct {
    doublereal atmplc[836]	/* was [76][11] */, atmtlc[76], atmglc[11];
} atmos2c_;

#define atmos2c_1 atmos2c_

struct {
    doublereal alatm_feh__, alatm_alpha__;
    logical laltptau100;
    integer ioatma;
} alatm03_;

#define alatm03_1 alatm03_

struct {
    doublereal dummy1, dummy2, dummy3, dummy4;
} alatm04_;

#define alatm04_1 alatm04_

struct {
    doublereal alfmlt, phmlt, cmxmlt, valfmlt[5000], vphmlt[5000], vcmxmlt[
	    5000];
} pualpha_;

#define pualpha_1 pualpha_

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

struct {
    doublereal atmop[5000], atmot[5000], atmod[5000], atmor[5000], adels[
	    15000]	/* was [3][5000] */, abetas[5000], agam1[5000], aqdt[
	    5000], afxions[15000]	/* was [3][5000] */, atmoo[5000], 
	    atmocp[5000];
    integer numatm;
} atmstruct_;

#define atmstruct_1 atmstruct_

struct {
    doublereal envrcz, rint;
} envcz_;

#define envcz_1 envcz_

struct {
    doublereal drate[5000], drate0[5000], fmassacc;
    integer jcz;
} deuter_;

#define deuter_1 deuter_

struct {
    doublereal tauczn, deladj[5000], tauhe, tnorm, tcz, whe, acatmr[5000], 
	    acatmd[5000], acatmp[5000], acatmt[5000], tatmos, ageout[5];
    logical lclcd;
    integer iclcd, iacat, ijlast;
    logical ljlast, ljwrt, ladon, laoly;
    integer ijvs, ijent, ijdel;
    logical lacout;
} acdpth_;

#define acdpth_1 acdpth_

struct {
    logical lstore, lstatm, lstenv, lstmod, lstphys, lstrot, lscrib, lstch, 
	    lphhd;
} ccout_;

#define ccout_1 ccout_

struct {
    logical lnewtcz, lcalcenv;
    doublereal taucz, taucz0, pphot, pphot0, fracstep;
} ovrtrn_;

#define ovrtrn_1 ovrtrn_

/* Table of constant values */

static integer c__9 = 9;
static integer c__1 = 1;
static doublereal c_b13 = .55;
static integer c__5 = 5;
static doublereal c_b357 = 10.;



/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */
/* ENVINT */
/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */
/* Subroutine */ int envint_(doublereal *b, doublereal *fpl, doublereal *ftl, 
	doublereal *gl, doublereal *hstot, integer *ie, logical *lprt, 
	logical *lsbc, doublereal *plim, doublereal *rl, doublereal *teffl, 
	doublereal *x, doublereal *z__, doublereal *estore, integer *istore, 
	integer *katm, integer *kenv, integer *ksaha, doublereal *ps, 
	doublereal *rs, doublereal *ts, logical *lpulpt)
{
    /* Initialized data */

    static doublereal xyz[22] = { 99.99,99.99,99.99,99.99,99.99,99.99,99.99,
	    99.99,99.99,99.99,99.99,99.99,99.99,99.99,99.99,99.99,99.99,99.99,
	    99.99,99.99,99.99,99.99 };

    /* Format strings */
    static char fmt_60[] = "(/,\002******** ATMOSPHERE BEGIN ********\002)";
    static char fmt_10[] = "(6x,\002TAU\002,9x,\002P\002,10x,\002T\002,10x"
	    ",\002D\002,11x,\002O\002,9x,\002HII  HEII HEIII   SAHA   KATM"
	    "\002)";
    static char fmt_20[] = "(1x,4f11.7,1pe14.7,0p3f6.3,2i7,4f12.8,1p2e12.5)";
    static char fmt_5001[] = "(5e16.9,/,5e16.9,/,5e16.9,/,4e16.9)";
    static char fmt_6001[] = "(5e23.16,/,5e23.16,/,5e23.16,/,4e23.16)";
    static char fmt_6003[] = "(6e23.16,/,6e23.16,/,6e23.16,/,4e23.16)";
    static char fmt_35[] = "(1x,\002ATMOSPHERE INTEGRATION COMPLETE\002,1x"
	    ",\002NUMBER OF STEPS ACCEPTED\002,i5,\002 REJECTED\002,i5/5x,"
	    "\002MAXIMUM RELATIVE ERROR IN P \002,1pe22.13)";
    static char fmt_50[] = "(5x,\002ATMOSPHERE INTEGRATION FAILED AFTER MAXS"
	    "TP\002,1x,\002INTEGRATIONS.I QUIT.\002)";
    static char fmt_61[] = "(/,\002******** ENVELOPE BEGIN ********\002)";
    static char fmt_230[] = "(4x,3f16.12,8x,f16.12)";
    static char fmt_240[] = "(1x,3a10,2a14,2a10,a7,a9,5a6,a9,2a12)";
    static char fmt_260[] = "(1x,1pe10.3,0p2f10.7,1p2e14.7,0p1f10.7,1pe10.2,"
	    "0pf7.3,1pe9.2,0p3f6.3,2f6.3,1pe9.2,0p2f12.8)";
    static char fmt_911[] = "(5x,\002ENVELOPE INTEGRATION FAILED AFTER MAXST"
	    "P TRIES.\002,1x,\002I QUIT\002)";
    static char fmt_215[] = "(1x,\002ENVELOPE INTEGRATION COMPLETE\002,1x"
	    ",\002NUMBER OF STEPS ACCEPTED\002,i5,\002 REJECTED\002,i5/5x,"
	    "\002SENV-LAST M=\002,1pe22.13,\002  LAST M=\002,e22.13/5x,\002MA"
	    "X RELATIVE ERRORS:M \002,1pe14.5,\002  T \002,e14.5,\002  R \002"
	    ",e14.5)";

    /* System generated locals */
    integer i__1;
    doublereal d__1, d__2;
    logical L__1;

    /* Builtin functions */
    integer s_wsfe(cilist *), e_wsfe(void), s_wsle(cilist *), do_lio(integer *
	    , integer *, char *, ftnlen), e_wsle(void);
    double d_lg10(doublereal *), exp(doublereal);
    integer do_fio(integer *, char *, ftnlen);
    /* Subroutine */ void s_stop(char *, ftnlen);
    double pow_dd(doublereal *, doublereal *);

    /* Local variables */
    static doublereal tauczenv, d__, h__;
    static integer i__, j, k;
    static doublereal o, p, t, y[3];
    static integer i1, i2;
    static doublereal x0, de, eg, dl;
    static integer jj;
    static doublereal pl, tl, ol, cv, op, dp;
    static integer nv;
    static doublereal on, dn, sl, dr, fx, dd1, dd2, wt0, del, eta;
    extern doublereal hra_(doublereal *);
    static doublereal cht, err[3], amu, emu, rmu, qdt, qdp, qcp, qat, qap, 
	    qod, qot, eps;
    static integer nok;
    static doublereal sgl, gam1, dum1;
    static integer nbad;
    static doublereal dela, hdid, beta, envg[5000];
    extern /* Subroutine */ int qatm_(doublereal *, doublereal *, doublereal *
	    , doublereal *, doublereal *, doublereal *, doublereal *, logical 
	    *, logical *, logical *, logical *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, integer *, integer *), qenv_(
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, logical *, logical *, 
	    logical *, logical *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, integer *, integer *);
    static doublereal edel1[5000], edel2[5000], dydx[3], envs1[5000], envs2[
	    5000], qdtt, qdtp, qcpt, qcpp, chrh, taup, delr, xlim, hmax, hmin,
	     taun, srad, sest, sdif;
    static logical ldum;
    static doublereal beta14, betai;
    static integer jenv;
    static doublereal yscal[3], fxion[3];
    static logical latmo;
    extern /* Subroutine */ int surfp_(doublereal *, doublereal *, logical *);
    static doublereal atmdx;
    extern /* Subroutine */ int meqos_(doublereal *, doublereal *, doublereal 
	    *, doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *);
    static doublereal qesum, deltr, pelpf;
    static integer nstep;
    static doublereal hnext, rsurf;
    static logical ltest;
    static doublereal chdeld, chdelj, ystart[3], errsum[3];
    static logical lderiv, locond;
    extern /* Subroutine */ int eqstat_(doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, logical *,
	     logical *, integer *);
    static doublereal stoler;
    extern /* Subroutine */ int bsstep_(doublereal *, doublereal *, integer *,
	     doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, S_fp, doublereal *, doublereal *, 
	    doublereal *, doublereal *, logical *, logical *, logical *, 
	    logical *, doublereal *, doublereal *, doublereal *, doublereal *,
	     integer *, integer *, doublereal *);
    static logical lsurcz;
    static doublereal xstart, envczl;
    extern /* Subroutine */ int taucal_(doublereal *, doublereal *, logical *,
	     doublereal *, doublereal *, doublereal *, doublereal *, integer *
	    , doublereal *, doublereal *, doublereal *);
    static logical lalfail;
    extern /* Subroutine */ int getopac_(doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *), alsurfp_(doublereal *, 
	    doublereal *, logical *, logical *), kcsurfp_(doublereal *, 
	    doublereal *, logical *);
    static logical llstore;

    /* Fortran I/O blocks */
    static cilist io___5 = { 0, 0, 0, fmt_60, 0 };
    static cilist io___7 = { 0, 6, 0, 0, 0 };
    static cilist io___8 = { 0, 0, 0, 0, 0 };
    static cilist io___43 = { 0, 0, 0, fmt_10, 0 };
    static cilist io___48 = { 0, 0, 0, fmt_20, 0 };
    static cilist io___58 = { 0, 0, 0, fmt_5001, 0 };
    static cilist io___59 = { 0, 0, 0, fmt_6001, 0 };
    static cilist io___63 = { 0, 0, 0, 0, 0 };
    static cilist io___64 = { 0, 0, 0, 0, 0 };
    static cilist io___76 = { 0, 0, 0, fmt_20, 0 };
    static cilist io___80 = { 0, 0, 0, fmt_5001, 0 };
    static cilist io___81 = { 0, 0, 0, fmt_6001, 0 };
    static cilist io___82 = { 0, 0, 0, fmt_35, 0 };
    static cilist io___83 = { 0, 0, 0, fmt_50, 0 };
    static cilist io___84 = { 0, 0, 0, fmt_50, 0 };
    static cilist io___85 = { 0, 0, 0, fmt_61, 0 };
    static cilist io___86 = { 0, 0, 0, fmt_5001, 0 };
    static cilist io___87 = { 0, 0, 0, fmt_6001, 0 };
    static cilist io___88 = { 0, 0, 0, fmt_230, 0 };
    static cilist io___93 = { 0, 0, 0, fmt_5001, 0 };
    static cilist io___94 = { 0, 0, 0, fmt_6001, 0 };
    static cilist io___95 = { 0, 0, 0, fmt_6003, 0 };
    static cilist io___96 = { 0, 0, 0, fmt_240, 0 };
    static cilist io___101 = { 0, 0, 0, fmt_260, 0 };
    static cilist io___110 = { 0, 0, 0, fmt_5001, 0 };
    static cilist io___111 = { 0, 0, 0, fmt_6001, 0 };
    static cilist io___112 = { 0, 0, 0, fmt_6003, 0 };
    static cilist io___113 = { 0, 0, 0, fmt_260, 0 };
    static cilist io___117 = { 0, 0, 0, fmt_230, 0 };
    static cilist io___118 = { 0, 0, 0, fmt_911, 0 };
    static cilist io___119 = { 0, 0, 0, fmt_911, 0 };
    static cilist io___124 = { 0, 0, 0, fmt_5001, 0 };
    static cilist io___125 = { 0, 0, 0, fmt_6003, 0 };
    static cilist io___126 = { 0, 0, 0, fmt_215, 0 };


/* PARAMETERS NT AND NG FOR TABULATED SURFACE PRESSURES OF KURUCZ. */
/* JNT 06/14 ADDED NTC/NGC FOR KTTAU=5 */
/* MHP 8/97 ADDED NTA AND NGA FOR ALLARD ATMOSPHERE TABLES */
/* DBG CHANGED MAXSTEP FROM 200 TO 2000 TO GIVE ATMOSPHERE INTEGRATER A CHANCE. */
/* MHP 8/25 Removed character file names from common block */
/* DBG PULSE: CONSTANTS NEEDED FOR DEL AND DELA CALCULATION */
/* DBG PULSE */
/* MHP 8/25 Removed file names from common block */
/*      COMMON/ATMOS2/ATMPL(NT,NG),ATMTL(NT), */
/*     *              ATMGL(NG),ATMZ,IOATM,FATM */
/* JNT 6/14 ADD FOR KURUCZ/CASTELLI 2004 ATMOSPHERES */
/* MHP 6/97 ADDED ALLARD MODEL ATMOSPHERES */
/*      COMMON/ATMOS3/ATMZA,ATMPLA(NTA,NGA), */
/*     *ATMTLA(NTA),ATMGLA(NGA),FALLARD,IOATMA */
/* MHP 8/25 Removed character file names from common block */
/* Shared: ALFILEIN, */
/* ALSURFP and PARMIN */
/* DBG 7/95 To store variables for pulse output */
/* MHP 07/02 STORE CONTENTS OF ENVELOPE INTEGRATION INTO A */
/* SET OF VECTORS, WHICH ARE FLIPPED AND CONVERTED INTO AN ASCENDING */
/* SERIES AFTER THE INTEGRATION IS DONE. */
/* KC 2025-05-30 reordered common block elements */
/* JvS 08/25 Updated with new elements */
/* JvS SAVE ATMOSPHERE STRUCTURE TO MAKE PROFILE OUTPUT EASIER */
/* JVS 08/13 IF THE CZ IS BEYOND THE FITTING POINT, STORE ITS LOCATION */
/* MHP 08/02 ADDED VECTOR FOR STORING THE OVERTURN TIMESCALE OF THE */
/* SURFACE CONVECTION ZONE */
/* JVS Acoustic depth common block */
/* KC 2025-05-30 reordered common block elements */
/*       COMMON/ACDPTH/TAUCZN,DELADJ(JSON),TAUHE, TNORM, TCZ, WHE, ICLCD, */
/*      *LCLCD, AGEOUT(5), IACAT, IJLAST, LJLAST, LJWRT, LADON,LAOLY, IJVS, */
/* G Somers 11/14, ADD I/O COMMON BLOCK */
/* G Somers END */
/* G Somers 3/17, ADDING NEW TAUCZ COMMON BLOCK */
/* MHP 1/01 CHANGED END OF FILE INDICATOR IN ATMOSPHERE/ENVELOPE FILES TO */
/* VECTOR FROM SCALAR */
    /* Parameter adjustments */
    --ts;
    --rs;
    --ps;
    --estore;

    /* Function Body */
/* DBG PULSE TURN ON DERIVATIVE CALCULATOR */
    if (*lpulpt && *lprt) {
	pulse1_1.lpumod = TRUE_;
	lderiv = TRUE_;
	latmo = FALSE_;
    } else {
	pulse1_1.lpumod = FALSE_;
	lderiv = FALSE_;
	latmo = TRUE_;
    }
    locond = FALSE_;
/* JVS 10/07/13 Always calculate derivatives */
    lderiv = TRUE_;
/* G Somers 11/14 WRITE ATMOSHPHERE HEADER TO .STORE FILE, AND ADDED */
/* I/O FLAGS TO THE ATMOSPHERE CALLS */
    if (*lprt && ccout_1.lstatm) {
	if (! ccout_1.lstch) {
	    io___5.ciunit = luout_1.istor;
	    s_wsfe(&io___5);
	    e_wsfe();
	}
    }
/* GET PRESSURE AT T=Teff BY INTERPOLATION IN TABLE ATMPL. */
    if (atmos_1.kttau == 3) {
/* KURUCZ ATMOSPHERES */
	if (ccout_1.lstch) {
	    ccout_1.lstatm = FALSE_;
	}
	L__1 = *lprt && ccout_1.lstatm;
	surfp_(teffl, gl, &L__1);
	goto L200;
/* JNT 06/14 */
/* GET PRESSURE AT T=Teff BY INTERPOLATION IN TABLE ATMPLC. */
    } else if (atmos_1.kttau == 5) {
/* KURUCZ ATMOSPHERES */
	if (ccout_1.lstch) {
	    ccout_1.lstatm = FALSE_;
	}
	L__1 = *lprt && ccout_1.lstatm;
	kcsurfp_(teffl, gl, &L__1);
	goto L200;
/* We have Kurucz atmosphere boundary conditions */
    } else if (atmos_1.kttau == 4) {
/* ALLARD & HAUSCHILDT ATMOSPHERES */
	if (ccout_1.lstch) {
	    ccout_1.lstatm = FALSE_;
	}
	L__1 = *lprt && ccout_1.lstatm;
	alsurfp_(teffl, gl, &L__1, &lalfail);
/* Changed to Allard atmosphere code */
	if (lalfail) {
	    atmos_1.kttau = 0;
	    atmos_1.lttau = TRUE_;
/* Set to gray atmosphere (KTTAU=0), as */
/* TeffL is above Allard max, or GL is out of range. */
	    s_wsle(&io___7);
	    do_lio(&c__9, &c__1, "ENVINT: Change to gray atmosphere (KTTAU=0)"
		    , (ftnlen)43);
	    e_wsle();
	    io___8.ciunit = luout_1.ishort;
	    s_wsle(&io___8);
	    do_lio(&c__9, &c__1, "ENVINT: Change to gray atmosphere (KTTAU=0)"
		    , (ftnlen)43);
	    e_wsle();
	    goto L2;
	}
	goto L200;
/* We have Allard atmosphere boundary conditions */
    }
L2:
/* Start gray atmosphere bounary conditions */
/* GUESS THE TEMPERATURE FOR AN OPTICAL DEPTH NEAR ZERO. */
    optab_1.idt = 15;
    for (jj = 1; jj <= 4; ++jj) {
	optab_1.idd[jj - 1] = 5;
/* L5: */
    }
    errsum[0] = 0.;
    if (atmos_1.kttau == 0) {
	tl = *teffl - .031235 + d_lg10(&const1_1.cc23) * .25;
    } else if (atmos_1.kttau == 1) {
	tl = *teffl - .031235 + d_lg10(&c_b13) * .25;
    } else if (atmos_1.kttau == 2) {
	tl = *teffl + hra_(&const1_1.cc23) - atmos_1.hras;
    }
/*                 For kttau = 0,1,or 2, very occasionally the integration */
/*                 fails because the starting point (X0) is past the end */
/*                 point (XLIM). When this happens, we divide the effective */
/*                 starting density (atmd0) by 10 and retry. */
    atmdx = intatm_1.atmd0;
L1998:
/* Return point if X0 > XLIM */
    t = exp(const1_1.cln * tl);
/* FIND THE PRESSURE CORRESPONDING TO THIS T AND THE DENSITY CHOSEN */
/* FOR THE START OF THE ATMOSPHERE INTEGRATION. */
/*      PL = DLOG10((CGAS*ATMD0 + CA3*T**3)*T) */
/* Computing 3rd power */
    d__2 = t;
    d__1 = (const2_1.cgas * atmdx + const2_1.ca3 * (d__2 * (d__2 * d__2))) * 
	    t;
    pl = d_lg10(&d__1);
/* NOW FIND THE OPTICAL DEPTH(X0) WHERE THE ATMOSPHERE INTEGRATION BEGINS. */
/* YC   IF LMHD USE MHD EQUATION OF STATE. */
    if (mhd_1.lmhd) {
	meqos_(&tl, &t, &pl, &p, &dl, &d__, x, z__, &beta, &betai, &beta14, 
		fxion, &rmu, &amu, &emu, &eta, &qdt, &qdp, &qcp, &dela, &qdtt,
		 &qdtp, &qat, &qap, &qcpt, &qcpp);
/*     *        QCPP,LDERIV,LATMO,KSAHA)  ! KC 2025-05-31 */
    } else {
	eqstat_(&tl, &t, &pl, &p, &dl, &d__, x, z__, &beta, &betai, &beta14, 
		fxion, &rmu, &amu, &emu, &eta, &qdt, &qdp, &qcp, &dela, &qdtt,
		 &qdtp, &qat, &qap, &qcpt, &qcpp, &lderiv, &latmo, ksaha);
    }
/* DBG 12/95 GET OPACITY */
    getopac_(&dl, &tl, x, z__, &o, &ol, &qod, &qot, fxion);
    x0 = pl - *gl + d_lg10(&o);
    y[0] = pl;
    dydx[0] = exp(const1_1.cln * (*gl + x0 - ol - pl));
/* G Somers 11/14 ADDED I/O FLAG AND CHANGED WRITE OUTS TO .STORE. */
    if (*lprt && ccout_1.lstatm) {
	if (! ccout_1.lstch) {
	    io___43.ciunit = luout_1.istor;
	    s_wsfe(&io___43);
	    e_wsfe();
	}
/* Computing 2nd power */
	d__2 = t;
/* Computing 2nd power */
	d__1 = d__2 * d__2;
	beta = 1. - const2_1.ca3 * (d__1 * d__1) / p;
	chrh = 1. / qdp;
	cht = -chrh * qdt;
/* Computing 2nd power */
	d__1 = cht;
	cv = qcpp - exp(const1_1.cln * (pl - dl - tl)) * (d__1 * d__1) / chrh;
	gam1 = chrh * qcpp / cv;
	if (! ccout_1.lstch) {
	    io___48.ciunit = luout_1.istor;
	    s_wsfe(&io___48);
	    do_fio(&c__1, (char *)&x0, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&pl, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&tl, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&dl, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&o, (ftnlen)sizeof(doublereal));
	    for (i__ = 1; i__ <= 3; ++i__) {
		do_fio(&c__1, (char *)&fxion[i__ - 1], (ftnlen)sizeof(
			doublereal));
	    }
	    do_fio(&c__1, (char *)&(*ksaha), (ftnlen)sizeof(integer));
	    do_fio(&c__1, (char *)&(*katm), (ftnlen)sizeof(integer));
	    do_fio(&c__1, (char *)&gam1, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&qdp, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&qdt, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&beta, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&qcpp, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&cv, (ftnlen)sizeof(doublereal));
	    e_wsfe();
	}
    }
/* DBG PULSE INITIAL POINT FOR PULSATION */
    if (*lpulpt && *lprt) {
	pulse2_1.qqed = 0.;
	qesum = 0.;
	pulse2_1.qqet = 0.;
	pulse2_1.qfs = 1.;
	taup = exp(const1_1.cln * x0);
	op = o;
	dp = exp(const1_1.cln * dl);
	deltr = 0.;
	pelpf = const2_1.cgas * t * d__ * emu;
/* FROM FIRST LINES OF TPGRAD */
	delr = o * *b * exp(const1_1.cln * (pl - *hstot - tl * 4. + 
		const_1.clsunl - const2_1.cgl + const3_1.cdelrl)) * *ftl / *
		fpl;
	if (delr - dela <= 1e-6) {
	    del = delr;
	} else {
	    del = dela;
	}
	if (pulse_1.ipver == 1) {
/* MHP 10/02 TYPO - QED SHOULD HAVE BEEN QQED */
/*     *         PL, QESUM,O,QDP,QED, */
	    io___58.ciunit = lunum_1.iopatm;
	    s_wsfe(&io___58);
	    do_fio(&c__1, (char *)&deltr, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&pulse2_1.qfs, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&(*b), (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&tl, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&dl, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&pl, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&qesum, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&o, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&qdp, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&pulse2_1.qqed, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&pulse2_1.qqet, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&qod, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&qot, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&del, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&dela, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&qcp, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&rmu, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&qdt, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&pelpf, (ftnlen)sizeof(doublereal));
	    e_wsfe();
/*     *         PL, TAUP ,O,QDP,QED, */
	} else if (pulse_1.ipver == 2 || pulse_1.ipver == 3) {
	    io___59.ciunit = lunum_1.iopatm;
	    s_wsfe(&io___59);
	    do_fio(&c__1, (char *)&deltr, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&pulse2_1.qfs, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&(*b), (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&tl, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&dl, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&pl, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&taup, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&o, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&qdp, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&pulse2_1.qqed, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&pulse2_1.qqet, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&qod, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&qot, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&del, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&dela, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&qcp, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&rmu, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&qdt, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&pelpf, (ftnlen)sizeof(doublereal));
	    e_wsfe();
	}
/* L6003: */
    }
/* INTEGRATE DP/DTAU FROM THIS STARTING TAU TO TAU = 2/3. */
/* SET NUMERICAL PARAMETERS UP. */
    nv = 1;
    eps = intatm_1.atmerr;
    if (atmos_1.kttau == 1) {
/* KRISHNA-SWAMY T TAU HAS DIFFERENT ZERO THAN EDDINGTON T TAU */
/* TAU = 0.312156330 AT TEFF. */
	xlim = -.505627854;
    } else {
/* TAU = 2/3 AT TEFF. */
	xlim = -.176091259;
    }
    if (x0 > xlim) {
/* Check that starting point is before endpoint */
	io___63.ciunit = luout_1.ishort;
	s_wsle(&io___63);
	do_lio(&c__9, &c__1, "ENVINT: X0>XLIM, X0,XLIM:", (ftnlen)25);
	do_lio(&c__5, &c__1, (char *)&x0, (ftnlen)sizeof(doublereal));
	do_lio(&c__5, &c__1, (char *)&xlim, (ftnlen)sizeof(doublereal));
	e_wsle();
	io___64.ciunit = luout_1.ishort;
	s_wsle(&io___64);
	do_lio(&c__9, &c__1, "ENVINT: get new X0 by dividing ATMD0 by 10", (
		ftnlen)42);
	e_wsle();
	atmdx /= 10.;
/* If not before, divide starting density by 10 */
	goto L1998;
/* and retry. */
    }
    hmax = intatm_1.atmmax;
    hmin = intatm_1.atmmin;
    h__ = intatm_1.atmbeg;
    stoler = intpar_1.stolr0;
    nok = 0;
    nbad = 0;
/* INTEGRATION LOOP. */
    for (nstep = 1; nstep <= 2000; ++nstep) {
/* YSCAL IS THE ARRAY THAT THE NUMERICAL ERRORS ARE SCALED AGAINST. */
	i__1 = nv;
	for (i__ = 1; i__ <= i__1; ++i__) {
	    yscal[i__ - 1] = (d__1 = y[i__ - 1], abs(d__1)) + (d__2 = h__ * 
		    dydx[i__ - 1], abs(d__2)) + 1e-30;
/* L30: */
	}
/* ENSURE THAT STEP DOESN'T EXCEED MAXIMUM STEP SIZE OR GO PAST */
/* THE LIMIT OF THE INTEGRATION. */
	if ((x0 - xlim) * (x0 + h__ - xlim) < 0.) {
	    h__ = xlim - x0;
	}
	if (h__ > hmax) {
	    h__ = hmax;
	}
/* INTEGRATE THE ATMOSPHERE FROM TAU TO TAU + H */
/* H IS THE ATTEMPTED STEP,HDID IS THE ONE PERFORMED, AND HNEXT IS THE */
/* PREDICTED NEXT STEP. */
	bsstep_(y, dydx, &nv, &x0, &h__, &eps, yscal, &hdid, &hnext, (S_fp)
		qatm_, b, fpl, ftl, gl, &latmo, &lderiv, &locond, lprt, rl, 
		teffl, x, z__, katm, ksaha, err);
/* FIND DP/DTAU AT THE START OF THE NEXT STEP. */
	errsum[0] += err[0];
	qatm_(&x0, y, dydx, b, fpl, ftl, gl, &latmo, &lderiv, &locond, lprt, 
		rl, teffl, x, z__, katm, ksaha);
/* G Somers 11/14 ADDED I/O FLAG AND CHANGED WRITE OUTS TO .STORE. */
	if (*lprt && ccout_1.lstatm) {
	    beta = 1. - const2_1.ca3 * exp(const1_1.cln * (atmprt_1.at * 4. - 
		    atmprt_1.ap));
	    chrh = 1. / pulse2_1.qqdp;
	    cht = -chrh * pulse2_1.qqdt;
/* Computing 2nd power */
	    d__1 = cht;
	    cv = pulse2_1.qqcp - exp(const1_1.cln * (atmprt_1.ap - 
		    atmprt_1.ad - atmprt_1.at)) * (d__1 * d__1) / chrh;
	    gam1 = chrh * pulse2_1.qqcp / cv;
	    if (! ccout_1.lstch) {
		io___76.ciunit = luout_1.istor;
		s_wsfe(&io___76);
		do_fio(&c__1, (char *)&atmprt_1.tau, (ftnlen)sizeof(
			doublereal));
		do_fio(&c__1, (char *)&atmprt_1.ap, (ftnlen)sizeof(doublereal)
			);
		do_fio(&c__1, (char *)&atmprt_1.at, (ftnlen)sizeof(doublereal)
			);
		do_fio(&c__1, (char *)&atmprt_1.ad, (ftnlen)sizeof(doublereal)
			);
		do_fio(&c__1, (char *)&atmprt_1.ao, (ftnlen)sizeof(doublereal)
			);
		for (i__ = 1; i__ <= 3; ++i__) {
		    do_fio(&c__1, (char *)&atmprt_1.afxion[i__ - 1], (ftnlen)
			    sizeof(doublereal));
		}
		do_fio(&c__1, (char *)&(*ksaha), (ftnlen)sizeof(integer));
		do_fio(&c__1, (char *)&(*katm), (ftnlen)sizeof(integer));
		do_fio(&c__1, (char *)&gam1, (ftnlen)sizeof(doublereal));
		do_fio(&c__1, (char *)&pulse2_1.qqdp, (ftnlen)sizeof(
			doublereal));
		do_fio(&c__1, (char *)&pulse2_1.qqdt, (ftnlen)sizeof(
			doublereal));
		do_fio(&c__1, (char *)&beta, (ftnlen)sizeof(doublereal));
		do_fio(&c__1, (char *)&pulse2_1.qqcp, (ftnlen)sizeof(
			doublereal));
		do_fio(&c__1, (char *)&cv, (ftnlen)sizeof(doublereal));
		e_wsfe();
	    }
/* JvS: SAVE STRUCTURE TO COMMON BLOCK */
	    atmstruct_1.atmop[nstep - 1] = atmprt_1.ap;
	    atmstruct_1.atmot[nstep - 1] = atmprt_1.at;
	    atmstruct_1.atmod[nstep - 1] = atmprt_1.ad;
	    atmstruct_1.abetas[nstep - 1] = beta;
	    atmstruct_1.agam1[nstep - 1] = gam1;
	    atmstruct_1.aqdt[nstep - 1] = pulse2_1.qqdt;
	    atmstruct_1.afxions[nstep * 3 - 3] = atmprt_1.afxion[0];
	    atmstruct_1.afxions[nstep * 3 - 2] = atmprt_1.afxion[1];
	    atmstruct_1.afxions[nstep * 3 - 1] = atmprt_1.afxion[2];
	    atmstruct_1.atmoo[nstep - 1] = atmprt_1.ao;
	    atmstruct_1.atmocp[nstep - 1] = pulse2_1.qqcp;
	}
	if (hdid == h__) {
	    ++nok;
	} else {
	    ++nbad;
	}
/* DBG PULSE ATMOSPHERE VALUES FOR PULSATION */
/* JVS 02/11 - Added LCLCD option to IF statement */
	if (*lpulpt && *lprt || acdpth_1.lclcd || ccout_1.lstch) {
	    pulse2_1.qqed = 0.;
	    qesum = 0.;
	    pulse2_1.qqet = 0.;
	    pulse2_1.qfs = 1.;
	    on = pulse2_1.qo;
	    dn = exp(const1_1.cln * pulse2_1.qdl);
	    taun = exp(const1_1.cln * atmprt_1.tau);
/* SEE J.P. COX PRINC. OF STELL. STRUC. P590 */
	    deltr = (taun - taup) / ((dn * on + dp * op) / 2);
	    pelpf = const2_1.cgas * pulse2_1.qt * pulse2_1.qd * pulse2_1.qemu;
	    op = on;
/* FROM FIRST LINES OF TPGRAD */
	    delr = pulse2_1.qo * *b * exp(const1_1.cln * (pulse2_1.qpl - *
		    hstot - pulse2_1.qtl * 4. + const_1.clsunl - const2_1.cgl 
		    + const3_1.cdelrl)) * *ftl / *fpl;
	    if (delr - pulse2_1.qdela <= 1e-6) {
		del = delr;
	    } else {
		del = pulse2_1.qdela;
	    }
	    if (*lpulpt && *lprt) {
		if (pulse_1.ipver == 1) {
		    io___80.ciunit = lunum_1.iopatm;
		    s_wsfe(&io___80);
		    do_fio(&c__1, (char *)&deltr, (ftnlen)sizeof(doublereal));
		    do_fio(&c__1, (char *)&pulse2_1.qfs, (ftnlen)sizeof(
			    doublereal));
		    do_fio(&c__1, (char *)&(*b), (ftnlen)sizeof(doublereal));
		    do_fio(&c__1, (char *)&pulse2_1.qtl, (ftnlen)sizeof(
			    doublereal));
		    do_fio(&c__1, (char *)&pulse2_1.qdl, (ftnlen)sizeof(
			    doublereal));
		    do_fio(&c__1, (char *)&pulse2_1.qpl, (ftnlen)sizeof(
			    doublereal));
		    do_fio(&c__1, (char *)&qesum, (ftnlen)sizeof(doublereal));
		    do_fio(&c__1, (char *)&pulse2_1.qo, (ftnlen)sizeof(
			    doublereal));
		    do_fio(&c__1, (char *)&pulse2_1.qqdp, (ftnlen)sizeof(
			    doublereal));
		    do_fio(&c__1, (char *)&pulse2_1.qqed, (ftnlen)sizeof(
			    doublereal));
		    do_fio(&c__1, (char *)&pulse2_1.qqet, (ftnlen)sizeof(
			    doublereal));
		    do_fio(&c__1, (char *)&pulse2_1.qqod, (ftnlen)sizeof(
			    doublereal));
		    do_fio(&c__1, (char *)&pulse2_1.qqot, (ftnlen)sizeof(
			    doublereal));
		    do_fio(&c__1, (char *)&del, (ftnlen)sizeof(doublereal));
		    do_fio(&c__1, (char *)&pulse2_1.qdela, (ftnlen)sizeof(
			    doublereal));
		    do_fio(&c__1, (char *)&pulse2_1.qqcp, (ftnlen)sizeof(
			    doublereal));
		    do_fio(&c__1, (char *)&pulse2_1.qrmu, (ftnlen)sizeof(
			    doublereal));
		    do_fio(&c__1, (char *)&pulse2_1.qqdt, (ftnlen)sizeof(
			    doublereal));
		    do_fio(&c__1, (char *)&pelpf, (ftnlen)sizeof(doublereal));
		    e_wsfe();
		} else if (pulse_1.ipver == 2 || pulse_1.ipver == 3) {
		    io___81.ciunit = lunum_1.iopatm;
		    s_wsfe(&io___81);
		    do_fio(&c__1, (char *)&deltr, (ftnlen)sizeof(doublereal));
		    do_fio(&c__1, (char *)&pulse2_1.qfs, (ftnlen)sizeof(
			    doublereal));
		    do_fio(&c__1, (char *)&(*b), (ftnlen)sizeof(doublereal));
		    do_fio(&c__1, (char *)&pulse2_1.qtl, (ftnlen)sizeof(
			    doublereal));
		    do_fio(&c__1, (char *)&pulse2_1.qdl, (ftnlen)sizeof(
			    doublereal));
		    do_fio(&c__1, (char *)&pulse2_1.qpl, (ftnlen)sizeof(
			    doublereal));
		    do_fio(&c__1, (char *)&taun, (ftnlen)sizeof(doublereal));
		    do_fio(&c__1, (char *)&pulse2_1.qo, (ftnlen)sizeof(
			    doublereal));
		    do_fio(&c__1, (char *)&pulse2_1.qqdp, (ftnlen)sizeof(
			    doublereal));
		    do_fio(&c__1, (char *)&pulse2_1.qqed, (ftnlen)sizeof(
			    doublereal));
		    do_fio(&c__1, (char *)&pulse2_1.qqet, (ftnlen)sizeof(
			    doublereal));
		    do_fio(&c__1, (char *)&pulse2_1.qqod, (ftnlen)sizeof(
			    doublereal));
		    do_fio(&c__1, (char *)&pulse2_1.qqot, (ftnlen)sizeof(
			    doublereal));
		    do_fio(&c__1, (char *)&del, (ftnlen)sizeof(doublereal));
		    do_fio(&c__1, (char *)&pulse2_1.qdela, (ftnlen)sizeof(
			    doublereal));
		    do_fio(&c__1, (char *)&pulse2_1.qqcp, (ftnlen)sizeof(
			    doublereal));
		    do_fio(&c__1, (char *)&pulse2_1.qrmu, (ftnlen)sizeof(
			    doublereal));
		    do_fio(&c__1, (char *)&pulse2_1.qqdt, (ftnlen)sizeof(
			    doublereal));
		    do_fio(&c__1, (char *)&pelpf, (ftnlen)sizeof(doublereal));
		    e_wsfe();
		}
	    }
/* JvS SAVE TO COMMON ATMSTRUCT COMMON BLOCK */
	    atmstruct_1.atmor[nstep - 1] = deltr;
	    atmstruct_1.adels[nstep * 3 - 3] = delr;
	    atmstruct_1.adels[nstep * 3 - 2] = del;
	    atmstruct_1.adels[nstep * 3 - 1] = pulse2_1.qdela;
	    atmstruct_1.numatm = nstep;
	    taup = taun;
	    dp = dn;
	}
/* DBG END */
/*  CHECK IF INTEGRATION COMPLETE */
	if ((d__1 = x0 - xlim, abs(d__1)) <= stoler) {
	    io___82.ciunit = luout_1.ishort;
	    s_wsfe(&io___82);
	    do_fio(&c__1, (char *)&nok, (ftnlen)sizeof(integer));
	    do_fio(&c__1, (char *)&nbad, (ftnlen)sizeof(integer));
	    do_fio(&c__1, (char *)&errsum[0], (ftnlen)sizeof(doublereal));
	    e_wsfe();
	    goto L200;
	}
	if (hnext < hmin) {
	    hnext = hmin;
	}
	h__ = hnext;
/* L40: */
    }
/* INTEGRATION HAS FAILED TO FINISH IN MAXSTP STEPS; */
/* PRINT NASTY MESSAGE AND QUIT. */
    io___83.ciunit = luout_1.iowr;
    s_wsfe(&io___83);
    e_wsfe();
    io___84.ciunit = luout_1.ishort;
    s_wsfe(&io___84);
    e_wsfe();
    s_stop("", (ftnlen)0);
/* ENVELOPE INTEGRATION */
/* HERE P IS THE INDEPENDENT VARIABLE AND M,R,AND T ARE */
/* DEPENDENT VARIABLES.  INTEGRATE FROM TAU = 2/3 TO THE LAST */
/* MASS POINT IN THE MODEL. */
L200:
/*  integration and come here */
/* G Somers 3/17, IF INTERESTED ONLY IN PPHOT, BREAK HERE. */
/* Kurucz and Allard (KTTAU=3 and 4) bypass atmosphere */
    ovrtrn_1.pphot = atmprt_1.ap;
    if (! ovrtrn_1.lcalcenv) {
	goto L555;
    }
/* G Somers 11/14 WRITE ENVELOPE HEADER */
    if (*lprt && ccout_1.lstenv) {
	if (! ccout_1.lstch) {
	    io___85.ciunit = luout_1.istor;
	    s_wsfe(&io___85);
	    e_wsfe();
	}
    }
/* DBG PULSE WRITE END OF DATA INDICATOR */
    if (*lpulpt && *lprt) {
/*         XYZ = 99.99D0 */
	if (pulse_1.ipver == 1) {
	    io___86.ciunit = lunum_1.iopatm;
	    s_wsfe(&io___86);
	    for (i__ = 1; i__ <= 19; ++i__) {
		do_fio(&c__1, (char *)&xyz[i__ - 1], (ftnlen)sizeof(
			doublereal));
	    }
	    e_wsfe();
	} else if (pulse_1.ipver == 2 || pulse_1.ipver == 3) {
	    io___87.ciunit = lunum_1.iopatm;
	    s_wsfe(&io___87);
	    for (i__ = 1; i__ <= 19; ++i__) {
		do_fio(&c__1, (char *)&xyz[i__ - 1], (ftnlen)sizeof(
			doublereal));
	    }
	    e_wsfe();
	}
/* 5002    FORMAT(E16.9) */
/* 6002    FORMAT(E23.16) */
    }
/* DBG */
/*  IF ENVELOPE MASS(SENV) SMALL ENOUGH,SKIP ENVELOPE INTEGRATION. */
/* DBG 2/92 CHANGED FROM 1.0D-10 to 1.0D-12 */
    if (comp_1.senv > -1e-12) {
	if (*lsbc) {
	    ps[*ie] = atmprt_1.ap;
	    rs[*ie] = *rl;
	    ts[*ie] = atmprt_1.at;
	    if (*lprt) {
		if (! ccout_1.lstch) {
		    io___88.ciunit = luout_1.istor;
		    s_wsfe(&io___88);
		    do_fio(&c__1, (char *)&ps[*ie], (ftnlen)sizeof(doublereal)
			    );
		    do_fio(&c__1, (char *)&ts[*ie], (ftnlen)sizeof(doublereal)
			    );
		    do_fio(&c__1, (char *)&rs[*ie], (ftnlen)sizeof(doublereal)
			    );
		    do_fio(&c__1, (char *)&comp_1.senv, (ftnlen)sizeof(
			    doublereal));
		    e_wsfe();
		}
	    }
	}
	goto L300;
    }
/*  INITIALIZE VARIABLES AND SET NUMERICAL PARAMETERS. */
    latmo = FALSE_;
    for (i__ = 1; i__ <= 3; ++i__) {
	errsum[i__ - 1] = 0.;
/* L235: */
    }
    nok = 0;
    nbad = 0;
    x0 = atmprt_1.ap;
    sl = 0.;
    y[0] = sl;
    y[1] = atmprt_1.at;
    y[2] = *rl;
    nv = 3;
    eps = intenv_1.enverr;
    hmax = intenv_1.envmax;
    hmin = intenv_1.envmin;
    h__ = intenv_1.envbeg;
    stoler = (d__1 = intpar_1.stolr0 * comp_1.senv, abs(d__1));
    rsurf = exp(const1_1.cln * *rl);
    if (*istore == *ie) {
	*istore = 0;
    }
    llstore = FALSE_;
    if (*lsbc) {
	ltest = FALSE_;
    } else {
	ltest = TRUE_;
    }
/*  FIND DY/DX AT THE START OF THE STEP. */
    qenv_(&x0, y, dydx, b, fpl, ftl, gl, &latmo, &lderiv, &locond, lprt, rl, 
	    teffl, x, z__, kenv, ksaha);
/* DBG PULSE WRITE FIRST POINT OF ENVELOPE */
    if (*lpulpt && *lprt) {
/*         REWIND IOPENV */
	pulse2_1.qqed = 0.;
	qesum = 0.;
	pulse2_1.qqet = 0.;
	pelpf = const2_1.cgas * pulse2_1.qt * pulse2_1.qd * pulse2_1.qemu;
	if (pulse_1.ipver == 1) {
	    io___93.ciunit = lunum_1.iopenv;
	    s_wsfe(&io___93);
	    do_fio(&c__1, (char *)&(*rl), (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&pulse2_1.qfs, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&(*b), (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&pulse2_1.qtl, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&pulse2_1.qdl, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&pulse2_1.qpl, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&qesum, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&pulse2_1.qo, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&pulse2_1.qqdp, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&pulse2_1.qqed, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&pulse2_1.qqet, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&pulse2_1.qqod, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&pulse2_1.qqot, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&pulse2_1.qdel, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&pulse2_1.qdela, (ftnlen)sizeof(doublereal))
		    ;
	    do_fio(&c__1, (char *)&pulse2_1.qqcp, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&pulse2_1.qrmu, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&pulse2_1.qqdt, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&pelpf, (ftnlen)sizeof(doublereal));
	    e_wsfe();
	} else if (pulse_1.ipver == 2) {
	    io___94.ciunit = lunum_1.iopenv;
	    s_wsfe(&io___94);
	    do_fio(&c__1, (char *)&(*rl), (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&pulse2_1.qfs, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&(*b), (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&pulse2_1.qtl, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&pulse2_1.qdl, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&pulse2_1.qpl, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&qesum, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&pulse2_1.qo, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&pulse2_1.qqdp, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&pulse2_1.qqed, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&pulse2_1.qqet, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&pulse2_1.qqod, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&pulse2_1.qqot, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&pulse2_1.qdel, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&pulse2_1.qdela, (ftnlen)sizeof(doublereal))
		    ;
	    do_fio(&c__1, (char *)&pulse2_1.qqcp, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&pulse2_1.qrmu, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&pulse2_1.qqdt, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&pelpf, (ftnlen)sizeof(doublereal));
	    e_wsfe();
	} else if (pulse_1.ipver == 3) {
/* DBG 7/95 Appended mixing length info at end of first three lines */
	    io___95.ciunit = lunum_1.iopenv;
	    s_wsfe(&io___95);
	    do_fio(&c__1, (char *)&(*rl), (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&pulse2_1.qfs, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&(*b), (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&pulse2_1.qtl, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&pulse2_1.qdl, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&pualpha_1.alfmlt, (ftnlen)sizeof(
		    doublereal));
	    do_fio(&c__1, (char *)&pulse2_1.qpl, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&qesum, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&pulse2_1.qo, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&pulse2_1.qqdp, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&pulse2_1.qqed, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&pualpha_1.phmlt, (ftnlen)sizeof(doublereal)
		    );
	    do_fio(&c__1, (char *)&pulse2_1.qqet, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&pulse2_1.qqod, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&pulse2_1.qqot, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&pulse2_1.qdel, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&pulse2_1.qdela, (ftnlen)sizeof(doublereal))
		    ;
	    do_fio(&c__1, (char *)&pualpha_1.cmxmlt, (ftnlen)sizeof(
		    doublereal));
	    do_fio(&c__1, (char *)&pulse2_1.qqcp, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&pulse2_1.qrmu, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&pulse2_1.qqdt, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&pelpf, (ftnlen)sizeof(doublereal));
	    e_wsfe();
	}
    }
/* DBG */
/* G Somers 11/14 ADDED I/O FLAG AND CHANGED WRITE OUTS TO .STORE. */
/* uncertain! */
    if (*lprt && ccout_1.lstenv) {
	if (! ccout_1.lstch) {
	    io___96.ciunit = luout_1.istor;
	    s_wsfe(&io___96);
	    do_fio(&c__1, "GRAV  ", (ftnlen)6);
	    do_fio(&c__1, "P   ", (ftnlen)4);
	    do_fio(&c__1, "T   ", (ftnlen)4);
	    do_fio(&c__1, "DEPTH    ", (ftnlen)9);
	    do_fio(&c__1, "M      ", (ftnlen)7);
	    do_fio(&c__1, "D    ", (ftnlen)5);
	    do_fio(&c__1, "O   ", (ftnlen)4);
	    do_fio(&c__1, "BETA", (ftnlen)4);
	    do_fio(&c__1, "DELR  ", (ftnlen)6);
	    do_fio(&c__1, "DELA", (ftnlen)4);
	    do_fio(&c__1, "DEL ", (ftnlen)4);
	    do_fio(&c__1, "HII ", (ftnlen)4);
	    do_fio(&c__1, "HEII", (ftnlen)4);
	    do_fio(&c__1, "HEIII", (ftnlen)5);
	    do_fio(&c__1, "V   ", (ftnlen)4);
	    do_fio(&c__1, "GAM1   ", (ftnlen)7);
	    do_fio(&c__1, "QQDP   ", (ftnlen)7);
	    e_wsfe();
	}
/*     X' ',4X,'GRAV',7X,'P',8X,'T',8X,'DEPTH',6X,'M', */
/*     *        9X,'D',6X,'O',7X,'BETA',3X,'DELR',5X,'DELA',3X, */
/*     *        'DEL',3X,'HII',3X,'HEII',1X,'HEIII',3X,'V') */
/* 260        FORMAT(1X,1PE10.3,0P2F10.7,1P2E14.7,0P1F10.7, */
/*     *           1PE10.2,0PF7.3,1PE9.2,0P3F6.3,2F6.3,1PE9.2, */
/*     *           0P2F12.8) */
	srad = exp(const1_1.cln * *rl);
	de = (rsurf - srad) / rsurf;
	sgl = const2_1.cgl + *hstot - *rl * 2.;
	eg = exp(const1_1.cln * sgl);
	chrh = 1. / pulse2_1.qqdp;
	cht = -chrh * pulse2_1.qqdt;
/* Computing 2nd power */
	d__1 = cht;
	cv = pulse2_1.qqcp - exp(const1_1.cln * (envprt_1.ep - envprt_1.ed - 
		envprt_1.et)) * (d__1 * d__1) / chrh;
	gam1 = chrh * pulse2_1.qqcp / cv;
	if (! ccout_1.lstch) {
	    io___101.ciunit = luout_1.istor;
	    s_wsfe(&io___101);
	    do_fio(&c__1, (char *)&eg, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&envprt_1.ep, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&envprt_1.et, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&de, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&envprt_1.es, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&envprt_1.ed, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&envprt_1.eo, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&envprt_1.ebeta, (ftnlen)sizeof(doublereal))
		    ;
	    for (k = 1; k <= 3; ++k) {
		do_fio(&c__1, (char *)&envprt_1.edel[k - 1], (ftnlen)sizeof(
			doublereal));
	    }
	    for (k = 1; k <= 3; ++k) {
		do_fio(&c__1, (char *)&envprt_1.efxion[k - 1], (ftnlen)sizeof(
			doublereal));
	    }
	    do_fio(&c__1, (char *)&envprt_1.evel, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&gam1, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&pulse2_1.qqdp, (ftnlen)sizeof(doublereal));
	    e_wsfe();
	}
    }
/* STORE STARTING VALUES OF THE INTEGRATION */
/* 07/02 INITIALIZE NUMBER OF STORED ENVELOPE POINTS TO 1 */
    lsurcz = FALSE_;
    tauczenv = 0.;
    envstruct_1.envd[0] = envprt_1.ed;
    envstruct_1.envp[0] = envprt_1.ep;
    envstruct_1.envr[0] = envprt_1.er;
    envstruct_1.envs[0] = envprt_1.es;
    envstruct_1.envt[0] = envprt_1.et;
    envstruct_1.envx[0] = *x;
    envstruct_1.envz[0] = *z__;
    envstruct_1.lcenv[0] = envprt_1.evel > 0.;
/* JVS 03/28 */
    envstruct_1.edels[0] = envprt_1.edel[0];
    envstruct_1.edels[1] = envprt_1.edel[1];
    envstruct_1.edels[2] = envprt_1.edel[2];
    envstruct_1.evels[0] = envprt_1.evel;
    envstruct_1.ebetas[0] = envprt_1.ebeta;
/* JVS end */
/* JVS 08/25 */
/* Always save these */
    chrh = 1. / pulse2_1.qqdp;
    cht = -chrh * pulse2_1.qqdt;
/* Computing 2nd power */
    d__1 = cht;
    cv = pulse2_1.qqcp - exp(const1_1.cln * (envprt_1.ep - envprt_1.ed - 
	    envprt_1.et)) * (d__1 * d__1) / chrh;
    envstruct_1.egam1[0] = chrh * pulse2_1.qqcp / cv;
    envstruct_1.eqcp[0] = pulse2_1.qqcp;
    envstruct_1.efxions[0] = envprt_1.efxion[0];
    envstruct_1.efxions[1] = envprt_1.efxion[1];
    envstruct_1.efxions[2] = envprt_1.efxion[2];
    envstruct_1.envo[0] = envprt_1.eo;
    envstruct_1.envl[0] = *b;
    envstruct_1.eqdt[0] = pulse2_1.qqdt;
/* JVS 10/10 */
    chdelj = envprt_1.edel[1];
    chdeld = pulse2_1.qdela;
    if (envstruct_1.lcenv[0]) {
	lsurcz = TRUE_;
    }
    envstruct_1.numenv = 1;
    for (nstep = 1; nstep <= 2000; ++nstep) {
	xstart = x0;
	i__1 = nv;
	for (i__ = 1; i__ <= i__1; ++i__) {
	    ystart[i__ - 1] = y[i__ - 1];
	    yscal[i__ - 1] = (d__1 = y[i__ - 1], abs(d__1)) + (d__2 = h__ * 
		    dydx[i__ - 1], abs(d__2)) + 1e-30;
/* L210: */
	}
	sest = y[0] + h__ * dydx[0];
	if (comp_1.senv - y[0] > 0. || comp_1.senv - sest > 0.) {
/*  IF THE INTEGRATION HAS OVERSHOT THE FITTING POINT, OR THE NEXT */
/*  STEP WILL DO SO,LIMIT STEP SIZE OR INTEGRATE BACKWARDS TO THE */
/*  CORRECT MASS. */
	    h__ = (comp_1.senv - y[0]) / dydx[0];
	}
/*  ENSURE THAT STEP DOESN'T EXCEED MAXIMUM STEP SIZE */
	if (h__ < 0.) {
	    if (h__ < -hmax) {
		h__ = -hmax;
	    }
	} else {
	    if (h__ > hmax) {
		h__ = hmax;
	    }
	}
/*  PLIM IS AN ESTIMATE OF THE ENDING PRESSURE FOR THE INTEGRATION, */
/*  BASED ON THE PRESSURE OF THE LAST MODEL POINT. */
/*  THE FIRST TIME THE INTEGRATOR TRIES TO PASS IT,LIMIT THE STEP */
/*  IN PRESSURE. */
	if (ltest) {
	    if (x0 + h__ > *plim) {
		h__ = *plim - x0;
		ltest = FALSE_;
	    }
	}
/*  INTEGRATE THE EQUATIONS FROM X0 TO X0 + H */
/*  H IS THE ATTEMPTED STEP,HDID IS THE ONE PERFORMED, AND HNEXT IS THE */
/*  PREDICTED NEXT STEP. */
	bsstep_(y, dydx, &nv, &x0, &h__, &eps, yscal, &hdid, &hnext, (S_fp)
		qenv_, b, fpl, ftl, gl, &latmo, &lderiv, &locond, lprt, rl, 
		teffl, x, z__, kenv, ksaha, err);
	for (k = 1; k <= 3; ++k) {
	    errsum[k - 1] += err[k - 1];
/* L255: */
	}
/*  FIND DY/DX AT THE START OF THE NEXT STEP. */
	qenv_(&x0, y, dydx, b, fpl, ftl, gl, &latmo, &lderiv, &locond, lprt, 
		rl, teffl, x, z__, kenv, ksaha);
/* DBG PULSE */
	if (*lpulpt && *lprt) {
	    pulse2_1.qqed = 0.;
	    qesum = 0.;
	    pulse2_1.qqet = 0.;
	    pelpf = const2_1.cgas * pulse2_1.qt * pulse2_1.qd * pulse2_1.qemu;
	    if (pulse_1.ipver == 1) {
		io___110.ciunit = lunum_1.iopenv;
		s_wsfe(&io___110);
		do_fio(&c__1, (char *)&(*rl), (ftnlen)sizeof(doublereal));
		do_fio(&c__1, (char *)&pulse2_1.qfs, (ftnlen)sizeof(
			doublereal));
		do_fio(&c__1, (char *)&(*b), (ftnlen)sizeof(doublereal));
		do_fio(&c__1, (char *)&pulse2_1.qtl, (ftnlen)sizeof(
			doublereal));
		do_fio(&c__1, (char *)&pulse2_1.qdl, (ftnlen)sizeof(
			doublereal));
		do_fio(&c__1, (char *)&pulse2_1.qpl, (ftnlen)sizeof(
			doublereal));
		do_fio(&c__1, (char *)&qesum, (ftnlen)sizeof(doublereal));
		do_fio(&c__1, (char *)&pulse2_1.qo, (ftnlen)sizeof(doublereal)
			);
		do_fio(&c__1, (char *)&pulse2_1.qqdp, (ftnlen)sizeof(
			doublereal));
		do_fio(&c__1, (char *)&pulse2_1.qqed, (ftnlen)sizeof(
			doublereal));
		do_fio(&c__1, (char *)&pulse2_1.qqet, (ftnlen)sizeof(
			doublereal));
		do_fio(&c__1, (char *)&pulse2_1.qqod, (ftnlen)sizeof(
			doublereal));
		do_fio(&c__1, (char *)&pulse2_1.qqot, (ftnlen)sizeof(
			doublereal));
		do_fio(&c__1, (char *)&pulse2_1.qdel, (ftnlen)sizeof(
			doublereal));
		do_fio(&c__1, (char *)&pulse2_1.qdela, (ftnlen)sizeof(
			doublereal));
		do_fio(&c__1, (char *)&pulse2_1.qqcp, (ftnlen)sizeof(
			doublereal));
		do_fio(&c__1, (char *)&pulse2_1.qrmu, (ftnlen)sizeof(
			doublereal));
		do_fio(&c__1, (char *)&pulse2_1.qqdt, (ftnlen)sizeof(
			doublereal));
		do_fio(&c__1, (char *)&pelpf, (ftnlen)sizeof(doublereal));
		e_wsfe();
	    } else if (pulse_1.ipver == 2) {
		io___111.ciunit = lunum_1.iopenv;
		s_wsfe(&io___111);
		do_fio(&c__1, (char *)&(*rl), (ftnlen)sizeof(doublereal));
		do_fio(&c__1, (char *)&pulse2_1.qfs, (ftnlen)sizeof(
			doublereal));
		do_fio(&c__1, (char *)&(*b), (ftnlen)sizeof(doublereal));
		do_fio(&c__1, (char *)&pulse2_1.qtl, (ftnlen)sizeof(
			doublereal));
		do_fio(&c__1, (char *)&pulse2_1.qdl, (ftnlen)sizeof(
			doublereal));
		do_fio(&c__1, (char *)&pulse2_1.qpl, (ftnlen)sizeof(
			doublereal));
		do_fio(&c__1, (char *)&qesum, (ftnlen)sizeof(doublereal));
		do_fio(&c__1, (char *)&pulse2_1.qo, (ftnlen)sizeof(doublereal)
			);
		do_fio(&c__1, (char *)&pulse2_1.qqdp, (ftnlen)sizeof(
			doublereal));
		do_fio(&c__1, (char *)&pulse2_1.qqed, (ftnlen)sizeof(
			doublereal));
		do_fio(&c__1, (char *)&pulse2_1.qqet, (ftnlen)sizeof(
			doublereal));
		do_fio(&c__1, (char *)&pulse2_1.qqod, (ftnlen)sizeof(
			doublereal));
		do_fio(&c__1, (char *)&pulse2_1.qqot, (ftnlen)sizeof(
			doublereal));
		do_fio(&c__1, (char *)&pulse2_1.qdel, (ftnlen)sizeof(
			doublereal));
		do_fio(&c__1, (char *)&pulse2_1.qdela, (ftnlen)sizeof(
			doublereal));
		do_fio(&c__1, (char *)&pulse2_1.qqcp, (ftnlen)sizeof(
			doublereal));
		do_fio(&c__1, (char *)&pulse2_1.qrmu, (ftnlen)sizeof(
			doublereal));
		do_fio(&c__1, (char *)&pulse2_1.qqdt, (ftnlen)sizeof(
			doublereal));
		do_fio(&c__1, (char *)&pelpf, (ftnlen)sizeof(doublereal));
		e_wsfe();
	    } else if (pulse_1.ipver == 3) {
/* DBG 7/95 Appended mixing length info at end of first three lines */
		io___112.ciunit = lunum_1.iopenv;
		s_wsfe(&io___112);
		do_fio(&c__1, (char *)&(*rl), (ftnlen)sizeof(doublereal));
		do_fio(&c__1, (char *)&pulse2_1.qfs, (ftnlen)sizeof(
			doublereal));
		do_fio(&c__1, (char *)&(*b), (ftnlen)sizeof(doublereal));
		do_fio(&c__1, (char *)&pulse2_1.qtl, (ftnlen)sizeof(
			doublereal));
		do_fio(&c__1, (char *)&pulse2_1.qdl, (ftnlen)sizeof(
			doublereal));
		do_fio(&c__1, (char *)&pualpha_1.alfmlt, (ftnlen)sizeof(
			doublereal));
		do_fio(&c__1, (char *)&pulse2_1.qpl, (ftnlen)sizeof(
			doublereal));
		do_fio(&c__1, (char *)&qesum, (ftnlen)sizeof(doublereal));
		do_fio(&c__1, (char *)&pulse2_1.qo, (ftnlen)sizeof(doublereal)
			);
		do_fio(&c__1, (char *)&pulse2_1.qqdp, (ftnlen)sizeof(
			doublereal));
		do_fio(&c__1, (char *)&pulse2_1.qqed, (ftnlen)sizeof(
			doublereal));
		do_fio(&c__1, (char *)&pualpha_1.phmlt, (ftnlen)sizeof(
			doublereal));
		do_fio(&c__1, (char *)&pulse2_1.qqet, (ftnlen)sizeof(
			doublereal));
		do_fio(&c__1, (char *)&pulse2_1.qqod, (ftnlen)sizeof(
			doublereal));
		do_fio(&c__1, (char *)&pulse2_1.qqot, (ftnlen)sizeof(
			doublereal));
		do_fio(&c__1, (char *)&pulse2_1.qdel, (ftnlen)sizeof(
			doublereal));
		do_fio(&c__1, (char *)&pulse2_1.qdela, (ftnlen)sizeof(
			doublereal));
		do_fio(&c__1, (char *)&pualpha_1.cmxmlt, (ftnlen)sizeof(
			doublereal));
		do_fio(&c__1, (char *)&pulse2_1.qqcp, (ftnlen)sizeof(
			doublereal));
		do_fio(&c__1, (char *)&pulse2_1.qrmu, (ftnlen)sizeof(
			doublereal));
		do_fio(&c__1, (char *)&pulse2_1.qqdt, (ftnlen)sizeof(
			doublereal));
		do_fio(&c__1, (char *)&pelpf, (ftnlen)sizeof(doublereal));
		e_wsfe();
	    }
	}
/* DBG END */
/* G Somers 11/14 ADDED I/O FLAG AND CHANGED WRITE OUTS TO .STORE. */
	if (*lprt && ccout_1.lstenv) {
	    srad = exp(const1_1.cln * *rl);
	    de = (rsurf - srad) / rsurf;
	    sgl = const2_1.cgl + *hstot - *rl * 2.;
	    eg = exp(const1_1.cln * sgl);
	    chrh = 1. / pulse2_1.qqdp;
	    cht = -chrh * pulse2_1.qqdt;
/* Computing 2nd power */
	    d__1 = cht;
	    cv = pulse2_1.qqcp - exp(const1_1.cln * (envprt_1.ep - 
		    envprt_1.ed - envprt_1.et)) * (d__1 * d__1) / chrh;
	    gam1 = chrh * pulse2_1.qqcp / cv;
	    if (! ccout_1.lstch) {
		io___113.ciunit = luout_1.istor;
		s_wsfe(&io___113);
		do_fio(&c__1, (char *)&eg, (ftnlen)sizeof(doublereal));
		do_fio(&c__1, (char *)&envprt_1.ep, (ftnlen)sizeof(doublereal)
			);
		do_fio(&c__1, (char *)&envprt_1.et, (ftnlen)sizeof(doublereal)
			);
		do_fio(&c__1, (char *)&de, (ftnlen)sizeof(doublereal));
		do_fio(&c__1, (char *)&envprt_1.es, (ftnlen)sizeof(doublereal)
			);
		do_fio(&c__1, (char *)&envprt_1.ed, (ftnlen)sizeof(doublereal)
			);
		do_fio(&c__1, (char *)&envprt_1.eo, (ftnlen)sizeof(doublereal)
			);
		do_fio(&c__1, (char *)&envprt_1.ebeta, (ftnlen)sizeof(
			doublereal));
		for (k = 1; k <= 3; ++k) {
		    do_fio(&c__1, (char *)&envprt_1.edel[k - 1], (ftnlen)
			    sizeof(doublereal));
		}
		for (k = 1; k <= 3; ++k) {
		    do_fio(&c__1, (char *)&envprt_1.efxion[k - 1], (ftnlen)
			    sizeof(doublereal));
		}
		do_fio(&c__1, (char *)&envprt_1.evel, (ftnlen)sizeof(
			doublereal));
		do_fio(&c__1, (char *)&gam1, (ftnlen)sizeof(doublereal));
		do_fio(&c__1, (char *)&pulse2_1.qqdp, (ftnlen)sizeof(
			doublereal));
		e_wsfe();
	    }
	}
	if (hdid == h__) {
	    ++nok;
	} else {
	    ++nbad;
	}
/*  CHECK IF INTEGRATION COMPLETE */
	sdif = comp_1.senv - y[0];
/* 07/02 STORE ENVELOPE TERMS IF THE INTEGRATION */
/* HAS NOT OVERSHOT THE FITTING POINT. */
	if (sdif <= stoler) {
	    ++envstruct_1.numenv;
	    envstruct_1.envd[envstruct_1.numenv - 1] = envprt_1.ed;
	    envstruct_1.envp[envstruct_1.numenv - 1] = envprt_1.ep;
	    envstruct_1.envr[envstruct_1.numenv - 1] = envprt_1.er;
	    envstruct_1.envs[envstruct_1.numenv - 1] = envprt_1.es;
	    envstruct_1.envt[envstruct_1.numenv - 1] = envprt_1.et;
	    envstruct_1.envx[envstruct_1.numenv - 1] = *x;
	    envstruct_1.envz[envstruct_1.numenv - 1] = *z__;
	    envstruct_1.lcenv[envstruct_1.numenv - 1] = envprt_1.evel > 0.;
/* JVS 08/13 ADD RUN FOR CZ CALCULATION */
	    envstruct_1.edels[envstruct_1.numenv * 3 - 3] = envprt_1.edel[0];
	    envstruct_1.edels[envstruct_1.numenv * 3 - 2] = envprt_1.edel[1];
	    envstruct_1.edels[envstruct_1.numenv * 3 - 1] = envprt_1.edel[2];
	    envstruct_1.evels[envstruct_1.numenv - 1] = envprt_1.evel;
	    envstruct_1.ebetas[envstruct_1.numenv - 1] = envprt_1.ebeta;
/* JVS 08/25 */
/* Always save these */
	    chrh = 1. / pulse2_1.qqdp;
	    cht = -chrh * pulse2_1.qqdt;
/* Computing 2nd power */
	    d__1 = cht;
	    cv = pulse2_1.qqcp - exp(const1_1.cln * (envprt_1.ep - 
		    envprt_1.ed - envprt_1.et)) * (d__1 * d__1) / chrh;
	    envstruct_1.egam1[envstruct_1.numenv - 1] = chrh * pulse2_1.qqcp /
		     cv;
	    envstruct_1.eqcp[envstruct_1.numenv - 1] = pulse2_1.qqcp;
	    envstruct_1.efxions[envstruct_1.numenv * 3 - 3] = envprt_1.efxion[
		    0];
	    envstruct_1.efxions[envstruct_1.numenv * 3 - 2] = envprt_1.efxion[
		    1];
	    envstruct_1.efxions[envstruct_1.numenv * 3 - 1] = envprt_1.efxion[
		    2];
	    envstruct_1.envo[envstruct_1.numenv - 1] = envprt_1.eo;
	    envstruct_1.envl[envstruct_1.numenv - 1] = *b;
	    envstruct_1.eqdt[envstruct_1.numenv - 1] = pulse2_1.qqdt;
	    if (! lsurcz) {
		if (envstruct_1.lcenv[envstruct_1.numenv - 1]) {
		    lsurcz = TRUE_;
		}
	    } else if (envprt_1.evel > 0.) {
		dr = pow_dd(&c_b357, &envstruct_1.envr[envstruct_1.numenv - 2]
			) - pow_dd(&c_b357, &envstruct_1.envr[
			envstruct_1.numenv - 1]);
		tauczenv += dr / envprt_1.evel;
	    }
	}
	if (abs(sdif) <= stoler) {
/*            WRITE(*,*)TAUCZENV/CSECYR */
	    if (*lsbc) {
		wt0 = sdif / (ystart[0] - y[0]);
		ps[*ie] = x0 + wt0 * (xstart - x0);
		rs[*ie] = y[2] + wt0 * (ystart[2] - y[2]);
		ts[*ie] = y[1] + wt0 * (ystart[1] - y[1]);
		if (*lprt) {
		    io___117.ciunit = luout_1.ishort;
		    s_wsfe(&io___117);
		    do_fio(&c__1, (char *)&ps[*ie], (ftnlen)sizeof(doublereal)
			    );
		    do_fio(&c__1, (char *)&ts[*ie], (ftnlen)sizeof(doublereal)
			    );
		    do_fio(&c__1, (char *)&rs[*ie], (ftnlen)sizeof(doublereal)
			    );
		    do_fio(&c__1, (char *)&comp_1.senv, (ftnlen)sizeof(
			    doublereal));
		    e_wsfe();
		}
	    }
	    goto L300;
	} else if (! llstore) {
	    if (y[1] >= ctlim_1.tenv && *lsbc) {
		llstore = TRUE_;
		*istore = *ie;
		estore[1] = x0;
		estore[2] = y[1];
		estore[3] = y[2];
		estore[4] = y[0];
	    }
	}
	if (hnext < hmin) {
	    hnext = hmin;
	}
	h__ = hnext;
/* L220: */
    }
/* INTEGRATION HAS FAILED TO FINISH IN MAXSTP STEPS; */
/* PRINT NASTY MESSAGE AND QUIT. */
    io___118.ciunit = luout_1.iowr;
    s_wsfe(&io___118);
    e_wsfe();
    io___119.ciunit = luout_1.ishort;
    s_wsfe(&io___119);
    e_wsfe();
    s_stop("", (ftnlen)0);
L300:
/* 07/02 NOW INVERT THE ENVELOPE VECTOR. */
    if (comp_1.senv < -1e-12) {
	i__1 = envstruct_1.numenv;
	for (i__ = 1; i__ <= i__1; ++i__) {
	    i1 = i__;
	    i2 = envstruct_1.numenv - i__ + 1;
	    if (i1 >= i2) {
		goto L310;
	    }
	    dum1 = envstruct_1.envd[i1 - 1];
	    envstruct_1.envd[i1 - 1] = envstruct_1.envd[i2 - 1];
	    envstruct_1.envd[i2 - 1] = dum1;
	    dum1 = envstruct_1.envp[i1 - 1];
	    envstruct_1.envp[i1 - 1] = envstruct_1.envp[i2 - 1];
	    envstruct_1.envp[i2 - 1] = dum1;
	    dum1 = envstruct_1.envr[i1 - 1];
	    envstruct_1.envr[i1 - 1] = envstruct_1.envr[i2 - 1];
	    envstruct_1.envr[i2 - 1] = dum1;
	    dum1 = envstruct_1.envs[i1 - 1];
	    envstruct_1.envs[i1 - 1] = envstruct_1.envs[i2 - 1];
	    envstruct_1.envs[i2 - 1] = dum1;
	    dum1 = envstruct_1.envt[i1 - 1];
	    envstruct_1.envt[i1 - 1] = envstruct_1.envt[i2 - 1];
	    envstruct_1.envt[i2 - 1] = dum1;
	    dum1 = envstruct_1.envx[i1 - 1];
	    envstruct_1.envx[i1 - 1] = envstruct_1.envx[i2 - 1];
	    envstruct_1.envx[i2 - 1] = dum1;
	    dum1 = envstruct_1.envz[i1 - 1];
	    envstruct_1.envz[i1 - 1] = envstruct_1.envz[i2 - 1];
	    envstruct_1.envz[i2 - 1] = dum1;
	    ldum = envstruct_1.lcenv[i1 - 1];
	    envstruct_1.lcenv[i1 - 1] = envstruct_1.lcenv[i2 - 1];
	    envstruct_1.lcenv[i2 - 1] = ldum;
/*  08/25 JVS */
	    dum1 = envstruct_1.envo[i1 - 1];
	    envstruct_1.envo[i1 - 1] = envstruct_1.envo[i2 - 1];
	    envstruct_1.envo[i2 - 1] = dum1;
	    dum1 = envstruct_1.envl[i1 - 1];
	    envstruct_1.envl[i1 - 1] = envstruct_1.envl[i2 - 1];
	    dum1 = envstruct_1.eqdt[i1 - 1];
	    envstruct_1.eqdt[i1 - 1] = envstruct_1.eqdt[i2 - 1];
	    envstruct_1.eqdt[i2 - 1] = dum1;
/* 08/13 JVS ADDED DEL VECTORS */
	    dum1 = envstruct_1.edels[i1 * 3 - 3];
	    envstruct_1.edels[i1 * 3 - 3] = envstruct_1.edels[i2 * 3 - 3];
	    envstruct_1.edels[i2 * 3 - 3] = dum1;
	    dum1 = envstruct_1.edels[i1 * 3 - 2];
	    envstruct_1.edels[i1 * 3 - 2] = envstruct_1.edels[i2 * 3 - 2];
	    envstruct_1.edels[i2 * 3 - 2] = dum1;
	    dum1 = envstruct_1.edels[i1 * 3 - 1];
	    envstruct_1.edels[i1 * 3 - 1] = envstruct_1.edels[i2 * 3 - 1];
	    envstruct_1.edels[i2 * 3 - 1] = dum1;
	    dum1 = envstruct_1.evels[i1 - 1];
	    envstruct_1.evels[i1 - 1] = envstruct_1.evels[i2 - 1];
	    envstruct_1.evels[i2 - 1] = dum1;
	    dum1 = envstruct_1.ebetas[i1 - 1];
	    envstruct_1.ebetas[i1 - 1] = envstruct_1.ebetas[i2 - 1];
	    envstruct_1.ebetas[i2 - 1] = dum1;
/*  08/25 JVS */
	    dum1 = envstruct_1.egam1[i1 - 1];
	    envstruct_1.egam1[i1 - 1] = envstruct_1.egam1[i2 - 1];
	    envstruct_1.egam1[i2 - 1] = dum1;
	    dum1 = envstruct_1.eqcp[i1 - 1];
	    envstruct_1.eqcp[i1 - 1] = envstruct_1.eqcp[i2 - 1];
	    envstruct_1.eqcp[i2 - 1] = dum1;
	    dum1 = envstruct_1.efxions[i1 * 3 - 3];
	    envstruct_1.efxions[i1 * 3 - 3] = envstruct_1.efxions[i2 * 3 - 3];
	    envstruct_1.efxions[i2 * 3 - 3] = dum1;
	    dum1 = envstruct_1.efxions[i1 * 3 - 2];
	    envstruct_1.efxions[i1 * 3 - 2] = envstruct_1.efxions[i2 * 3 - 2];
	    envstruct_1.efxions[i2 * 3 - 2] = dum1;
	    dum1 = envstruct_1.efxions[i1 * 3 - 1];
	    envstruct_1.efxions[i1 * 3 - 1] = envstruct_1.efxions[i2 * 3 - 1];
	    envstruct_1.efxions[i2 * 3 - 1] = dum1;
	}
L310:
/* JVS 07/12 Save the last envelope point pressure */
/*      PPHOT = ENVP(NUMENV) ! G Somers 3/17, MOVED PPHOT DEF HIGHER UP */
/* END JVS */
	;
    }
/* DBG PULSE WRITE END OF DATA INDICATOR */
    if (*lpulpt && *lprt) {
/*         XYZ = 99.99D0 */
	if (pulse_1.ipver == 1) {
	    io___124.ciunit = lunum_1.iopenv;
	    s_wsfe(&io___124);
	    for (i__ = 1; i__ <= 19; ++i__) {
		do_fio(&c__1, (char *)&xyz[i__ - 1], (ftnlen)sizeof(
			doublereal));
	    }
	    e_wsfe();
	} else if (pulse_1.ipver == 2 || pulse_1.ipver == 3) {
	    io___125.ciunit = lunum_1.iopenv;
	    s_wsfe(&io___125);
	    for (i__ = 1; i__ <= 22; ++i__) {
		do_fio(&c__1, (char *)&xyz[i__ - 1], (ftnlen)sizeof(
			doublereal));
	    }
	    e_wsfe();
	}
    }
    io___126.ciunit = luout_1.ishort;
    s_wsfe(&io___126);
    do_fio(&c__1, (char *)&nok, (ftnlen)sizeof(integer));
    do_fio(&c__1, (char *)&nbad, (ftnlen)sizeof(integer));
    do_fio(&c__1, (char *)&sdif, (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&y[0], (ftnlen)sizeof(doublereal));
    for (j = 1; j <= 3; ++j) {
	do_fio(&c__1, (char *)&errsum[j - 1], (ftnlen)sizeof(doublereal));
    }
    e_wsfe();
/* JVS 08/13 */
/* IF THE CZ IS IN THE ENVELOPE (.I.E. BEYOND THE FITTING POINT) TRACK ITS */
/* LOCATION IN MASS AND RADIUS FOR USE WITH AM LOSS ROUTINES */

/* G Somers 3/17, SKIP TAUCAL CALL IF USING NEW TAUCZ ROUTINES */
    if (ovrtrn_1.lnewtcz) {
	goto L555;
    }
/* G Somers END */
    jenv = 0.f;
    i__1 = envstruct_1.numenv;
    for (i__ = 1; i__ <= i__1; ++i__) {
	if ((real) jenv == 0.f && envstruct_1.lcenv[i__ - 1]) {
	    jenv = i__;
	}
    }
    if (jenv > 1) {
/* Calculate the the location of the base sof the surface CZ in radius */
	dd2 = envstruct_1.edels[(jenv - 1) * 3 - 3] - envstruct_1.edels[(jenv 
		- 1) * 3 - 2];
	dd1 = envstruct_1.edels[jenv * 3 - 3] - envstruct_1.edels[jenv * 3 - 
		2];
	fx = dd2 / (dd2 - dd1);
	envczl = envstruct_1.envr[jenv - 2] + fx * (envstruct_1.envr[jenv - 1]
		 - envstruct_1.envr[jenv - 2]) - const_1.crsunl;
	envcz_1.envrcz = exp(const1_1.cln * envczl);
	i__1 = envstruct_1.numenv;
	for (i__ = 1; i__ <= i__1; ++i__) {
	    envs1[i__ - 1] = exp(const1_1.cln * (envstruct_1.envs[i__ - 1] + *
		    hstot));
	    if (i__ == envstruct_1.numenv) {
		envs2[i__ - 1] = 0.f;
	    } else {
		envs2[i__ - 1] = exp(const1_1.cln * envstruct_1.envs[i__]) - 
			exp(const1_1.cln * envstruct_1.envs[i__ - 1]);
	    }
	    edel1[i__ - 1] = envstruct_1.edels[i__ * 3 - 3];
	    edel2[i__ - 1] = envstruct_1.edels[i__ * 3 - 2];
	}
/*             CALL TAUCAL(ENVX,ENVS2,ENVS1,LCENV,ENVR,ENVP,ENVD,ENVG,NUMENV,  ! KC 2025-05-31 */
	taucal_(envs2, envs1, envstruct_1.lcenv, envstruct_1.envr, 
		envstruct_1.envp, envstruct_1.envd, envg, &envstruct_1.numenv,
		 envstruct_1.evels, edel1, edel2);
    }
L555:
    return 0;
} /* envint_ */

