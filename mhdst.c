/* mhdst.f -- translated by f2c (version 20100827).
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
    logical ldebug, lcorr, lmilne, ltrack, lstore, lstpch;
    integer npunch;
} ccout2_;

#define ccout2_1 ccout2_

struct {
    doublereal tdvr1a[27840]	/* was [16][87][20] */, tlog1[16];
    integer nt1, nr1;
    doublereal drh1;
} tab1a_;

#define tab1a_1 tab1a_

struct {
    doublereal tdvr2a[33180]	/* was [79][21][20] */, tlog2[79];
    integer nt2, nr2;
    doublereal drh2;
} tab2a_;

#define tab2a_1 tab2a_

struct {
    doublereal tdvr1b[27840]	/* was [16][87][20] */;
} tab1b_;

#define tab1b_1 tab1b_

struct {
    doublereal tdvr2b[33180]	/* was [79][21][20] */;
} tab2b_;

#define tab2b_1 tab2b_

struct {
    doublereal tdvr1c[27840]	/* was [16][87][20] */;
} tab1c_;

#define tab1c_1 tab1c_

struct {
    doublereal tdvr2c[33180]	/* was [79][21][20] */;
} tab2c_;

#define tab2c_1 tab2c_

struct {
    doublereal atwta[6], abuna[6], abfrca[6], gasma;
} chea_;

#define chea_1 chea_

struct {
    doublereal atwtb[6], abunb[6], abfrcb[6], gasmb;
} cheb_;

#define cheb_1 cheb_

struct {
    doublereal atwtc[6], abunc[6], abfrcc[6], gasmc;
} chec_;

#define chec_1 chec_

struct {
    doublereal tdvrx1[5250]	/* was [10][21][25] */, tlogx[10];
    integer ntx, nrx;
    doublereal drhx;
} tabx1_;

#define tabx1_1 tabx1_

struct {
    doublereal tdvrx2[5250]	/* was [10][21][25] */;
} tabx2_;

#define tabx2_1 tabx2_

struct {
    doublereal tdvrx3[5250]	/* was [10][21][25] */;
} tabx3_;

#define tabx3_1 tabx3_

struct {
    doublereal tdvrx4[5250]	/* was [10][21][25] */;
} tabx4_;

#define tabx4_1 tabx4_

struct {
    doublereal tdvrx5[5250]	/* was [10][21][25] */;
} tabx5_;

#define tabx5_1 tabx5_

struct {
    doublereal atwt1[6], abun1[6], abfrc1[6], gasm1;
} che1_;

#define che1_1 che1_

struct {
    doublereal atwt2[6], abun2[6], abfrc2[6], gasm2;
} che2_;

#define che2_1 che2_

struct {
    doublereal atwt3[6], abun3[6], abfrc3[6], gasm3;
} che3_;

#define che3_1 che3_

struct {
    doublereal atwt4[6], abun4[6], abfrc4[6], gasm4;
} che4_;

#define che4_1 che4_

struct {
    doublereal atwt5[6], abun5[6], abfrc5[6], gasm5;
} che5_;

#define che5_1 che5_

struct {
    doublereal tlim1, tlim2, tmini, tmaxi;
} tttt_;

#define tttt_1 tttt_

/* Table of constant values */

static integer c__16 = 16;
static integer c__87 = 87;
static integer c__20 = 20;
static integer c__79 = 79;
static integer c__21 = 21;
static integer c__6 = 6;
static integer c__10 = 10;
static integer c__25 = 25;

/* ---------------------------  GROUP: SR_X  ------------------------------- */


/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */
/* MHDST */
/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */
/* Subroutine */ int mhdst_(integer *ir1, integer *ir2, integer *ir3, integer 
	*ir4, integer *ir5, integer *ir6, integer *ir7, integer *ir8)
{
    static integer idx;
    static doublereal abud[6], abuu[6], atwd[6], atwu[6];
    static integer nchem;
    static doublereal tlogd[79], drdum, tddum[27840]	/* was [16][87][20] */
	    , tldum[16];
    static integer ntdum, nrdum;
    static doublereal tlogu[79], tddif0[33180]	/* was [79][21][20] */;
    extern /* Subroutine */ int mhdst1_(integer *, integer *, integer *, 
	    integer *, integer *, integer *, integer *, integer *, integer *, 
	    integer *, integer *, integer *, integer *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, integer *, doublereal *, doublereal *, doublereal *,
	     doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *);
    static doublereal abfrcd[6], tddifd[33180]	/* was [79][21][20] */, 
	    abfrcu[6], tddifu[33180]	/* was [79][21][20] */;

/*     ZAMS TABLES (LABELLED BY A,B,C) */
/*     CENTRE TABLES (LABELLED BY 1,2,3,4,5) */
/*     TL<TLIM1:       LOWER PART OF ZAMS TABLES */
/*     TLIM1<TL<TLIM2: UPPER PART OF ZAMS TABLES */
/*     TL>TLIM2:       VARIABLE X TABLES */
/*     WORKING STORAGE FOR NUMERICAL X-DERIVATIVES. COMMON TO ALL */
/*     X-TABLES */

/*     DEFINE, WITH UNUSED STATEMENTS, STORAGE FOR VARIABLES */
/*     THAT WOULD OTHERWISE ONLY APPEAR AS FORMAL PARAMETERS */
/*     IN THIS SUBROUTINE. VICIOUS BUGS CAN BE THE RESULT IF */
/*     THIS STORAGE WERE NOT PROVIDED (REMEMBER: FORTRAN IS NOT */
/*     A RECURSIVE LANGUAGE.) */
    nchem = 0;
    drdum = 0.;
    ntdum = 0;
    nrdum = 0;
/*     READ ZAMS TABLES */
    if (*ir1 > 0) {
	idx = 0;
	mhdst1_(ir1, &idx, &c__16, &c__87, &c__20, &c__79, &c__21, &c__20, &
		c__6, &tab1a_1.nt1, &tab1a_1.nr1, &tab2a_1.nt2, &tab2a_1.nr2, 
		tab1a_1.tlog1, tab2a_1.tlog2, tab1a_1.tdvr1a, tab2a_1.tdvr2a, 
		&tab1a_1.drh1, &tab2a_1.drh2, &nchem, chea_1.atwta, 
		chea_1.abuna, chea_1.abfrca, &chea_1.gasma, tlogd, tlogu, 
		tddif0, tddifd, tddifu, atwd, atwu, abud, abuu, abfrcd, 
		abfrcu);
    }
    if (*ir2 > 0) {
	idx = 0;
	mhdst1_(ir2, &idx, &c__16, &c__87, &c__20, &c__79, &c__21, &c__20, &
		c__6, &tab1a_1.nt1, &tab1a_1.nr1, &tab2a_1.nt2, &tab2a_1.nr2, 
		tab1a_1.tlog1, tab2a_1.tlog2, tab1b_1.tdvr1b, tab2b_1.tdvr2b, 
		&tab1a_1.drh1, &tab2a_1.drh2, &nchem, cheb_1.atwtb, 
		cheb_1.abunb, cheb_1.abfrcb, &cheb_1.gasmb, tlogd, tlogu, 
		tddif0, tddifd, tddifu, atwd, atwu, abud, abuu, abfrcd, 
		abfrcu);
    }
    if (*ir3 > 0) {
	idx = 0;
	mhdst1_(ir3, &idx, &c__16, &c__87, &c__20, &c__79, &c__21, &c__20, &
		c__6, &tab1a_1.nt1, &tab1a_1.nr1, &tab2a_1.nt2, &tab2a_1.nr2, 
		tab1a_1.tlog1, tab2a_1.tlog2, tab1c_1.tdvr1c, tab2c_1.tdvr2c, 
		&tab1a_1.drh1, &tab2a_1.drh2, &nchem, chec_1.atwtc, 
		chec_1.abunc, chec_1.abfrcc, &chec_1.gasmc, tlogd, tlogu, 
		tddif0, tddifd, tddifu, atwd, atwu, abud, abuu, abfrcd, 
		abfrcu);
    }
/*     READ CENTRE TABLES */
    if (*ir4 > 0) {
	idx = 1;
	mhdst1_(ir4, &idx, &c__16, &c__87, &c__20, &c__10, &c__21, &c__25, &
		c__6, &ntdum, &nrdum, &tabx1_1.ntx, &tabx1_1.nrx, tldum, 
		tabx1_1.tlogx, tddum, tabx1_1.tdvrx1, &drdum, &tabx1_1.drhx, &
		nchem, che1_1.atwt1, che1_1.abun1, che1_1.abfrc1, &
		che1_1.gasm1, tlogd, tlogu, tddif0, tddifd, tddifu, atwd, 
		atwu, abud, abuu, abfrcd, abfrcu);
    }
    if (*ir5 > 0) {
	idx = 1;
	mhdst1_(ir5, &idx, &c__16, &c__87, &c__20, &c__10, &c__21, &c__25, &
		c__6, &ntdum, &nrdum, &tabx1_1.ntx, &tabx1_1.nrx, tldum, 
		tabx1_1.tlogx, tddum, tabx2_1.tdvrx2, &drdum, &tabx1_1.drhx, &
		nchem, che2_1.atwt2, che2_1.abun2, che2_1.abfrc2, &
		che2_1.gasm2, tlogd, tlogu, tddif0, tddifd, tddifu, atwd, 
		atwu, abud, abuu, abfrcd, abfrcu);
    }
    if (*ir6 > 0) {
	idx = 1;
	mhdst1_(ir6, &idx, &c__16, &c__87, &c__20, &c__10, &c__21, &c__25, &
		c__6, &ntdum, &nrdum, &tabx1_1.ntx, &tabx1_1.nrx, tldum, 
		tabx1_1.tlogx, tddum, tabx3_1.tdvrx3, &drdum, &tabx1_1.drhx, &
		nchem, che3_1.atwt3, che3_1.abun3, che3_1.abfrc3, &
		che3_1.gasm3, tlogd, tlogu, tddif0, tddifd, tddifu, atwd, 
		atwu, abud, abuu, abfrcd, abfrcu);
    }
    if (*ir7 > 0) {
	idx = 1;
	mhdst1_(ir7, &idx, &c__16, &c__87, &c__20, &c__10, &c__21, &c__25, &
		c__6, &ntdum, &nrdum, &tabx1_1.ntx, &tabx1_1.nrx, tldum, 
		tabx1_1.tlogx, tddum, tabx4_1.tdvrx4, &drdum, &tabx1_1.drhx, &
		nchem, che4_1.atwt4, che4_1.abun4, che4_1.abfrc4, &
		che4_1.gasm4, tlogd, tlogu, tddif0, tddifd, tddifu, atwd, 
		atwu, abud, abuu, abfrcd, abfrcu);
    }
    if (*ir8 > 0) {
	idx = 1;
	mhdst1_(ir8, &idx, &c__16, &c__87, &c__20, &c__10, &c__21, &c__25, &
		c__6, &ntdum, &nrdum, &tabx1_1.ntx, &tabx1_1.nrx, tldum, 
		tabx1_1.tlogx, tddum, tabx5_1.tdvrx5, &drdum, &tabx1_1.drhx, &
		nchem, che5_1.atwt5, che5_1.abun5, che5_1.abfrc5, &
		che5_1.gasm5, tlogd, tlogu, tddif0, tddifd, tddifu, atwd, 
		atwu, abud, abuu, abfrcd, abfrcu);
    }
/*     TEMPERATURE LIMITS */
    tttt_1.tmini = tab1a_1.tlog1[0];
    tttt_1.tlim1 = tab1a_1.tlog1[tab1a_1.nt1 - 1];
    if (*ir4 <= 0) {
	tttt_1.tlim2 = tab2a_1.tlog2[tab2a_1.nt2 - 1];
	tttt_1.tmaxi = tttt_1.tlim2;
    } else {
	tttt_1.tlim2 = tabx1_1.tlogx[0];
	tttt_1.tmaxi = tabx1_1.tlogx[tabx1_1.ntx - 1];
    }
    if (*ir4 <= 0) {
	goto L500;
    }
L500:
/* L8002: */
/* L8003: */
    return 0;
} /* mhdst_ */

