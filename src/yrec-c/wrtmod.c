/* wrtmod.f -- translated by f2c (version 20061008).
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
    doublereal xenv0, zenv0;
} label_;

#define label_1 label_

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
    logical ldebug, lcorr, lmilne, ltrack, lstpch;
} ccout2_;

#define ccout2_1 ccout2_

struct {
    doublereal xenv, zenv, zenvm, amuenv, fxenv[12], xnew, znew, stotal, senv;
} comp_;

#define comp_1 comp_

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
    doublereal atmstp, envstp;
    logical lenvg;
} envgen_;

#define envgen_1 envgen_

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
    doublereal wnew, walpcz, acfpft;
    integer itfp1, itfp2;
    logical lrot, linstb, lwnew;
} rot_;

#define rot_1 rot_

struct {
    doublereal sesum[5000], seg[35000]	/* was [7][5000] */, sbeta[5000], 
	    seta[5000];
    logical locons[5000];
    doublereal so[5000], sdel[15000]	/* was [3][5000] */, sfxion[15000]	
	    /* was [3][5000] */, svel[5000], scp[5000];
} scrtch_;

#define scrtch_1 scrtch_

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
    doublereal gam1[5000];
    logical lsound;
} sound_;

#define sound_1 sound_

struct {
    doublereal cdh, etadh0, etadh1, zdh[18], xxdh, yydh, zzdh, dhnue[18];
    logical ldh;
} debhu_;

#define debhu_1 debhu_

struct {
    doublereal alfmlt, phmlt, cmxmlt, valfmlt[5000], vphmlt[5000], vcmxmlt[
	    5000];
} pualpha_;

#define pualpha_1 pualpha_

struct {
    doublereal derot[5000];
} roten_;

#define roten_1 roten_

struct {
    doublereal spotf, spotx;
    logical lsdepth;
} spots_;

#define spots_1 spots_

struct {
    doublereal ves[5000], ves0[5000], vss[5000], vss0[5000], hle[5000], vgsf[
	    5000], vgsf0[5000], vmu[5000];
} temp2_;

#define temp2_1 temp2_

struct {
    doublereal phisp[5000], phirot[5000], phidis[5000], rat[5000];
} quadd_;

#define quadd_1 quadd_

/* Table of constant values */

static integer c__9 = 9;
static integer c__1 = 1;
static integer c__8 = 8;
static doublereal c_b41 = 4.;



/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */
/* WRTMOD */
/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */
/*       SUBROUTINE WRTMOD(M,LSHELL,JXBEG,JXEND,JCORE,JENV,HCOMP,HS1,HD, */
/*      *HL,HP,HR,HT,LC,MODEL,BL,TEFFL,OMEGA,FP,FT,ETA2,R0,HJM,HI,HS, */
/*      * DAGE)  ! KC 2025-05-31 */
/* Subroutine */ int wrtmod_(integer *m, integer *jenv, doublereal *hcomp, 
	doublereal *hs1, doublereal *hd, doublereal *hl, doublereal *hp, 
	doublereal *hr, doublereal *ht, integer *model, doublereal *bl, 
	doublereal *teffl, doublereal *fp, doublereal *ft, doublereal *hs, 
	doublereal *dage)
{
    /* Format strings */
    static char fmt_9124[] = "(1x,\002Shell#\002,5x,\002R/Rsun\002,7x,\002M/"
	    "Msun\002,7x,\002Cs\002,15x,\002Rho\002)";
    static char fmt_9123[] = "(1x,i6,1x,2f12.8,1p,3e16.8)";
    static char fmt_123[] = "(1x,2f12.8,1p6e16.8)";
    static char fmt_124[] = "(1x,f11.7,1p4e16.8)";
    static char fmt_5001[] = "(\002 MODEL#=\002,i5,\002  NUMBER OF SHELLS IN"
	    " MODEL=\002,i5,\002 VER=\002,i2,/,\002 MASS=\002,f8.5,\002  LOG("
	    "TEFF)=\002,f8.5,/,\002 LOG(L/LSUN)=\002,f16.10,\002  LOG(R/RSUN)="
	    "\002,f16.10,/,\002 AGE=\002,1pe12.5,\002 GYR\002,/,\002 MIXING L"
	    "ENGTH PARAMETER=\002,0pf16.10,/,\002 ZAMS (X,Z)=\002,2f18.10)";
    static char fmt_5052[] = "(5e16.9,/,5e16.9,/,5e16.9,/,5e16.9)";
    static char fmt_6052[] = "(5e23.16,/,5e23.16,/,5e23.16,/,5e23.16)";
    static char fmt_6053[] = "(6e23.16,/,6e23.16,/,6e23.16,/,5e23.16)";

    /* System generated locals */
    integer i__1;
    doublereal d__1;
    olist o__1;

    /* Builtin functions */
    integer s_wsle(cilist *), do_lio(integer *, integer *, char *, ftnlen), 
	    e_wsle(void), f_open(olist *), s_wsfe(cilist *), e_wsfe(void);
    double exp(doublereal), sqrt(doublereal);
    integer do_fio(integer *, char *, ftnlen);
    double pow_dd(doublereal *, doublereal *), d_lg10(doublereal *);

    /* Local variables */
    static doublereal b;
    static integer i__, j;
    static doublereal x, z__;
    static integer id[5000];
    static doublereal fm, dr, fr, rl, gl, fs, sv, xx1, xx2, xx3, xx4, xx5;
    static integer idm;
    static doublereal fpl, fsi, ftl;
    static integer ixx;
    static doublereal xxx, dum1[4], dum2[3], dum3[3], dum4[3], qdr1, qdr2, 
	    qpr1, qpr2, rmid;
    static integer katm, idum;
    static doublereal plim, divp, divr, qqpr, qqdr;
    static logical lsbc0, lprt;
    static integer kenv;
    static doublereal abeg0, amin0, amax0, ebeg0, emin0, emax0;
    static integer ksaha;
    static doublereal pelpf, tempr, hstot, ateffl;
    static logical lpulpt;
    extern /* Subroutine */ int envint_(doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, integer *, logical *, 
	    logical *, doublereal *, doublereal *, doublereal *, doublereal *,
	     doublereal *, doublereal *, integer *, integer *, integer *, 
	    integer *, doublereal *, doublereal *, doublereal *, logical *);
    static doublereal rsurfl, qsmass;

    /* Fortran I/O blocks */
    static cilist io___1 = { 0, 6, 0, 0, 0 };
    static cilist io___2 = { 0, 6, 0, 0, 0 };
    static cilist io___3 = { 0, 500, 0, fmt_9124, 0 };
    static cilist io___14 = { 0, 0, 0, fmt_123, 0 };
    static cilist io___15 = { 0, 500, 0, fmt_9123, 0 };
    static cilist io___26 = { 0, 0, 0, fmt_124, 0 };
    static cilist io___59 = { 0, 0, 0, fmt_5001, 0 };
    static cilist io___65 = { 0, 0, 0, fmt_5052, 0 };
    static cilist io___66 = { 0, 0, 0, fmt_6052, 0 };
    static cilist io___67 = { 0, 0, 0, fmt_6053, 0 };


/* DBG PULSE */
/* MHP 7/96 COMMON BLOCK INSERTED FOR SOUND SPEED */
/* DBG */
/* DBG 7/92 COMMON BLOCK ADDED TO COMPUTE DEBYE-HUCKEL CORRECTION. */
/* DBG 7/95 To store variables for pulse output */
/*      *HS1(JSON),HD(JSON),HL(JSON),HP(JSON),HR(JSON),HT(JSON),LC(JSON) */
/*       DIMENSION OMEGA(JSON),FP(JSON),FT(JSON),ETA2(JSON),ID(JSON) */
/*       DIMENSION R0(JSON),HJM(JSON),HI(JSON),HS(JSON)  ! KC 2025-05-31 */
/* KC 2025-05-30 addressed warning messages from Makefile.legacy */
/*      DATA IHEADR/4H***+/ */
/* G Somers 10/14, Add spot common block, and store common block. */
/* G Somers END */
    /* Parameter adjustments */
    --hs;
    --ft;
    --fp;
    --ht;
    --hr;
    --hp;
    --hl;
    --hd;
    --hs1;
    hcomp -= 16;

    /* Function Body */
    s_wsle(&io___1);
    do_lio(&c__9, &c__1, "wrtmod LSOUND 1: ", (ftnlen)17);
    do_lio(&c__8, &c__1, (char *)&sound_1.lsound, (ftnlen)sizeof(logical));
    e_wsle();
    if (sound_1.lsound) {
	s_wsle(&io___2);
	do_lio(&c__9, &c__1, "wrtmod LSOUND 2: ", (ftnlen)17);
	do_lio(&c__8, &c__1, (char *)&sound_1.lsound, (ftnlen)sizeof(logical))
		;
	e_wsle();
/* FD 10/09 Add an extra output to plot the sound speed profile easyly */
	o__1.oerr = 0;
	o__1.ounit = 500;
	o__1.ofnmlen = 10;
	o__1.ofnm = "Csound.dat";
	o__1.orl = 0;
	o__1.osta = "unknown";
	o__1.oacc = 0;
	o__1.ofm = 0;
	o__1.oblnk = 0;
	f_open(&o__1);
	s_wsfe(&io___3);
	e_wsfe();
/* L9123: */
/* FD end */
	i__1 = *m;
	for (i__ = 1; i__ <= i__1; ++i__) {
	    fr = exp(const1_1.cln * hr[i__]) / const_1.crsun;
	    fm = exp(const1_1.cln * hs[i__]) / const_1.cmsun;
/* Computing 3rd power */
	    d__1 = fr;
	    xx1 = fm / (d__1 * (d__1 * d__1));
	    xxx = -exp(const1_1.cln * (const2_1.cgl + hs[i__] + hd[i__] - hp[
		    i__] - hr[i__]));
	    xx2 = -xxx / sound_1.gam1[i__ - 1];
	    xx3 = sound_1.gam1[i__ - 1];
	    xx4 = -xx2 - xxx * (pulse1_1.pqdp[i__ - 1] + scrtch_1.sdel[i__ * 
		    3 - 2] * pulse1_1.pqdt[i__ - 1]);
	    xx5 = exp(const1_1.cln * (const1_1.c4pil + hd[i__] + hr[i__] * 3. 
		    - hs[i__]));
	    sv = sqrt(sound_1.gam1[i__ - 1] * exp(const1_1.cln * (hp[i__] - 
		    hd[i__]))) * 1e-5;
	    io___14.ciunit = luout_1.imodpt;
	    s_wsfe(&io___14);
	    do_fio(&c__1, (char *)&fr, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&fm, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&xx1, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&xx2, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&xx3, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&xx4, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&xx5, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&sv, (ftnlen)sizeof(doublereal));
	    e_wsfe();
/* FD 10/09 Add an extra output to plot the sound speed profile easyly */
	    s_wsfe(&io___15);
	    do_fio(&c__1, (char *)&i__, (ftnlen)sizeof(integer));
	    do_fio(&c__1, (char *)&fr, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&fm, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&sv, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&hd[i__], (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&ht[i__], (ftnlen)sizeof(doublereal));
	    e_wsfe();
/* FD end */
/*  DERIVATIVES OF DP/DR, DRHO/DR */
	    if (i__ < *m) {
		rmid = (exp(const1_1.cln * hr[i__]) + exp(const1_1.cln * hr[
			i__ + 1])) * .5;
		dr = exp(const1_1.cln * hr[i__ + 1]) - exp(const1_1.cln * hr[
			i__]);
		divp = (sound_1.gam1[i__ - 1] * exp(const1_1.cln * hp[i__]) + 
			sound_1.gam1[i__] * exp(const1_1.cln * hp[i__ + 1])) *
			 .5 * dr;
		divr = (exp(const1_1.cln * hd[i__]) + exp(const1_1.cln * hd[
			i__ + 1])) * .5 * dr;
		qpr1 = exp(const1_1.cln * (const2_1.cgl + hs[i__] + hd[i__] - 
			hr[i__] * 2.));
		qdr1 = exp(const1_1.cln * (hd[i__] - hp[i__])) * 
			pulse1_1.pqdp[i__ - 1] * qpr1;
		qpr2 = exp(const1_1.cln * (const2_1.cgl + hs[i__ + 1] + hd[
			i__ + 1] - hr[i__ + 1] * 2.));
		qdr2 = exp(const1_1.cln * (hd[i__ + 1] - hp[i__ + 1])) * 
			pulse1_1.pqdp[i__] * qpr1;
		qqpr = (qpr1 - qpr2) / divp;
		qqdr = (qdr1 - qdr2) / divr;
		io___26.ciunit = luout_1.imodpt;
		s_wsfe(&io___26);
		d__1 = rmid / const_1.crsun;
		do_fio(&c__1, (char *)&d__1, (ftnlen)sizeof(doublereal));
		do_fio(&c__1, (char *)&qpr1, (ftnlen)sizeof(doublereal));
		do_fio(&c__1, (char *)&qdr1, (ftnlen)sizeof(doublereal));
		do_fio(&c__1, (char *)&qqpr, (ftnlen)sizeof(doublereal));
		do_fio(&c__1, (char *)&qqdr, (ftnlen)sizeof(doublereal));
		e_wsfe();
	    }
	}
    }

/* G Somers 11/14 LCHEMO BLOCK REMOVED, AS THIS INFO IS ALREADY IN .STORE. */

/* DBG PULSE: PRINT OUT PULSATION ENV AND ATM IN ENVINT */
/* G Somers 11/14 CHANGE TO NEW I/O FLAGS. */
    if (ccout_1.lstatm || ccout_1.lstenv || pulse_1.lpulse) {
/*  INTEGRATE AN ENVELOPE FROM THE SURFACE TO THE CONVERGED MODEL, */
/*  PRINTING OUT THE RESULTS. */
/*  SET UP FLAGS AND COUNTERS. */
	lsbc0 = FALSE_;
	if (ccout_1.lstore) {
	    lprt = TRUE_;
	}
	katm = 0;
	kenv = 0;
	ksaha = 0;
/*  SAVE THE INTEGRATION STEP PARAMETERS AND ENFORCE THE SPACING */
/*  REQUESTED FOR PRINTOUT PURPOSES. */
	abeg0 = intatm_1.atmbeg;
	amin0 = intatm_1.atmmin;
	amax0 = intatm_1.atmmax;
	ebeg0 = intenv_1.envbeg;
	emin0 = intenv_1.envmin;
	emax0 = intenv_1.envmax;
	intatm_1.atmbeg = envgen_1.atmstp;
	intatm_1.atmmin = envgen_1.atmstp;
	intatm_1.atmmax = envgen_1.atmstp;
	intenv_1.envbeg = envgen_1.envstp;
	intenv_1.envmin = envgen_1.envstp;
	intenv_1.envmax = envgen_1.envstp;
	b = exp(const1_1.cln * *bl);
	rl = (*bl + const_1.clsunl - *teffl * 4. - const1_1.c4pil - 
		const2_1.csigl) * .5;
	gl = const2_1.cgl + comp_1.stotal - rl - rl;
	x = hcomp[*m * 15 + 1];
	z__ = hcomp[*m * 15 + 3];
	fpl = fp[*m];
	ftl = ft[*m];
	ixx = 0;
	hstot = comp_1.stotal;
	plim = hp[*m];
/* DBG PULSE: ADDED ARGUEMENT TO ENVINT TO TURN ON/OFF PULSE OUTPUT */
	lpulpt = pulse_1.lpulse;
	if (debhu_1.ldh) {
	    debhu_1.xxdh = hcomp[*m * 15 + 1];
	    debhu_1.yydh = hcomp[*m * 15 + 2] + hcomp[*m * 15 + 4];
	    debhu_1.zzdh = hcomp[*m * 15 + 3];
	    debhu_1.zdh[0] = hcomp[*m * 15 + 5] + hcomp[*m * 15 + 6];
	    debhu_1.zdh[1] = hcomp[*m * 15 + 7] + hcomp[*m * 15 + 8];
	    debhu_1.zdh[2] = hcomp[*m * 15 + 9] + hcomp[*m * 15 + 10] + hcomp[
		    *m * 15 + 11];
	}
/* MHP 10/02  define ISTORE - used in ENVINT */
	idum = 0;
/* G Somers 10/14, FOR SPOTTED RUNS, FIND THE */
/* PRESSURE AT THE AMBIENT TEMPERATURE ATEFFL */
	if (*jenv == *m && spots_1.spotf != 0.f && spots_1.spotx != 1.f) {
	    d__1 = spots_1.spotf * pow_dd(&spots_1.spotx, &c_b41) + 1.f - 
		    spots_1.spotf;
	    ateffl = *teffl - d_lg10(&d__1) * .25f;
	} else {
	    ateffl = *teffl;
	}
	envint_(&b, &fpl, &ftl, &gl, &hstot, &ixx, &lprt, &lsbc0, &plim, &rl, 
		&ateffl, &x, &z__, dum1, &idum, &katm, &kenv, &ksaha, dum2, 
		dum3, dum4, &lpulpt);
/* G Somers END */
	intatm_1.atmbeg = abeg0;
	intatm_1.atmmin = amin0;
	intatm_1.atmmax = amax0;
	intenv_1.envbeg = ebeg0;
	intenv_1.envmin = emin0;
	intenv_1.envmax = emax0;
    }

/* G Somers 11/14 LCONZO (convection zone info) block deleted. */

/* G Somers 11/14 LJOUT (rotation info) block deleted. */

    fsi = exp(-const1_1.cln * comp_1.stotal);
/* DBG PULSE: WRITE HEADER INFORMATION FOR PULSE MODEL */
    if (pulse_1.lpulse) {
	rsurfl = (*bl - const1_1.c4pil - const2_1.csigl - *teffl * 4. + 
		const_1.clsunl) * .5;
	tempr = rsurfl - const_1.crsunl;
	qsmass = pulse_1.xmsol;
	io___59.ciunit = lunum_1.iopmod;
	s_wsfe(&io___59);
	do_fio(&c__1, (char *)&(*model), (ftnlen)sizeof(integer));
	do_fio(&c__1, (char *)&idm, (ftnlen)sizeof(integer));
	do_fio(&c__1, (char *)&pulse_1.ipver, (ftnlen)sizeof(integer));
	do_fio(&c__1, (char *)&qsmass, (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&(*teffl), (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&(*bl), (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&tempr, (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&(*dage), (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&const3_1.cmixl, (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&label_1.xenv0, (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&label_1.zenv0, (ftnlen)sizeof(doublereal));
	e_wsfe();
    }
    i__1 = idm;
    for (j = 1; j <= i__1; ++j) {
	i__ = id[j - 1];
	fs = fsi * hs1[i__];

/* G Somers 11/14 FINAL LSCRIB BLOCK DELETED */

/* DBG WRITE PULSE MODEL */
/*       PRINT*, 'LPULSE=',LPULSE */
	if (pulse_1.lpulse && ccout_1.lstore) {
/* MHP 10/02 uncommented pelpf statement, used later in i/o */
/*         PELPF = CGAS * DEXP(CLN*(HT(I) + HD(I)))* PEMU(I) */
/*          ADDED X AND Z TO OUTPUT */
	    if (j == 2 && i__ == 1) {
		goto L5003;
	    }
	    if (pulse_1.ipver == 1) {
		pelpf = const2_1.cgas * exp(const1_1.cln * (ht[i__] + hd[i__])
			) * pulse1_1.pemu[i__ - 1];
		io___65.ciunit = lunum_1.iopmod;
		s_wsfe(&io___65);
		do_fio(&c__1, (char *)&hr[i__], (ftnlen)sizeof(doublereal));
		do_fio(&c__1, (char *)&fs, (ftnlen)sizeof(doublereal));
		do_fio(&c__1, (char *)&hl[i__], (ftnlen)sizeof(doublereal));
		do_fio(&c__1, (char *)&ht[i__], (ftnlen)sizeof(doublereal));
		do_fio(&c__1, (char *)&hd[i__], (ftnlen)sizeof(doublereal));
		do_fio(&c__1, (char *)&hp[i__], (ftnlen)sizeof(doublereal));
		do_fio(&c__1, (char *)&scrtch_1.sesum[i__ - 1], (ftnlen)
			sizeof(doublereal));
		do_fio(&c__1, (char *)&scrtch_1.so[i__ - 1], (ftnlen)sizeof(
			doublereal));
		do_fio(&c__1, (char *)&pulse1_1.pqdp[i__ - 1], (ftnlen)sizeof(
			doublereal));
		do_fio(&c__1, (char *)&pulse1_1.pqed[i__ - 1], (ftnlen)sizeof(
			doublereal));
		do_fio(&c__1, (char *)&pulse1_1.pqet[i__ - 1], (ftnlen)sizeof(
			doublereal));
		do_fio(&c__1, (char *)&pulse1_1.pqod[i__ - 1], (ftnlen)sizeof(
			doublereal));
		do_fio(&c__1, (char *)&pulse1_1.pqot[i__ - 1], (ftnlen)sizeof(
			doublereal));
		do_fio(&c__1, (char *)&scrtch_1.sdel[i__ * 3 - 2], (ftnlen)
			sizeof(doublereal));
		do_fio(&c__1, (char *)&scrtch_1.sdel[i__ * 3 - 1], (ftnlen)
			sizeof(doublereal));
		do_fio(&c__1, (char *)&pulse1_1.pqcp[i__ - 1], (ftnlen)sizeof(
			doublereal));
		do_fio(&c__1, (char *)&pulse1_1.prmu[i__ - 1], (ftnlen)sizeof(
			doublereal));
		do_fio(&c__1, (char *)&pulse1_1.pqdt[i__ - 1], (ftnlen)sizeof(
			doublereal));
		do_fio(&c__1, (char *)&pelpf, (ftnlen)sizeof(doublereal));
		e_wsfe();
	    } else if (pulse_1.ipver == 2) {
		io___66.ciunit = lunum_1.iopmod;
		s_wsfe(&io___66);
		do_fio(&c__1, (char *)&hr[i__], (ftnlen)sizeof(doublereal));
		do_fio(&c__1, (char *)&fs, (ftnlen)sizeof(doublereal));
		do_fio(&c__1, (char *)&hl[i__], (ftnlen)sizeof(doublereal));
		do_fio(&c__1, (char *)&ht[i__], (ftnlen)sizeof(doublereal));
		do_fio(&c__1, (char *)&hd[i__], (ftnlen)sizeof(doublereal));
		do_fio(&c__1, (char *)&hp[i__], (ftnlen)sizeof(doublereal));
		do_fio(&c__1, (char *)&scrtch_1.sesum[i__ - 1], (ftnlen)
			sizeof(doublereal));
		do_fio(&c__1, (char *)&scrtch_1.so[i__ - 1], (ftnlen)sizeof(
			doublereal));
		do_fio(&c__1, (char *)&pulse1_1.pqdp[i__ - 1], (ftnlen)sizeof(
			doublereal));
		do_fio(&c__1, (char *)&pulse1_1.pqed[i__ - 1], (ftnlen)sizeof(
			doublereal));
		do_fio(&c__1, (char *)&pulse1_1.pqet[i__ - 1], (ftnlen)sizeof(
			doublereal));
		do_fio(&c__1, (char *)&pulse1_1.pqod[i__ - 1], (ftnlen)sizeof(
			doublereal));
		do_fio(&c__1, (char *)&pulse1_1.pqot[i__ - 1], (ftnlen)sizeof(
			doublereal));
		do_fio(&c__1, (char *)&scrtch_1.sdel[i__ * 3 - 2], (ftnlen)
			sizeof(doublereal));
		do_fio(&c__1, (char *)&scrtch_1.sdel[i__ * 3 - 1], (ftnlen)
			sizeof(doublereal));
		do_fio(&c__1, (char *)&pulse1_1.pqcp[i__ - 1], (ftnlen)sizeof(
			doublereal));
		do_fio(&c__1, (char *)&pulse1_1.prmu[i__ - 1], (ftnlen)sizeof(
			doublereal));
		do_fio(&c__1, (char *)&pulse1_1.pqdt[i__ - 1], (ftnlen)sizeof(
			doublereal));
		do_fio(&c__1, (char *)&hcomp[i__ * 15 + 1], (ftnlen)sizeof(
			doublereal));
		do_fio(&c__1, (char *)&hcomp[i__ * 15 + 3], (ftnlen)sizeof(
			doublereal));
		e_wsfe();
	    } else if (pulse_1.ipver == 3) {
/* DBG 7/95 Modifed to include mixing length variables */
		io___67.ciunit = lunum_1.iopmod;
		s_wsfe(&io___67);
		do_fio(&c__1, (char *)&hr[i__], (ftnlen)sizeof(doublereal));
		do_fio(&c__1, (char *)&fs, (ftnlen)sizeof(doublereal));
		do_fio(&c__1, (char *)&hl[i__], (ftnlen)sizeof(doublereal));
		do_fio(&c__1, (char *)&ht[i__], (ftnlen)sizeof(doublereal));
		do_fio(&c__1, (char *)&hd[i__], (ftnlen)sizeof(doublereal));
		do_fio(&c__1, (char *)&pualpha_1.valfmlt[i__ - 1], (ftnlen)
			sizeof(doublereal));
		do_fio(&c__1, (char *)&hp[i__], (ftnlen)sizeof(doublereal));
		do_fio(&c__1, (char *)&scrtch_1.sesum[i__ - 1], (ftnlen)
			sizeof(doublereal));
		do_fio(&c__1, (char *)&scrtch_1.so[i__ - 1], (ftnlen)sizeof(
			doublereal));
		do_fio(&c__1, (char *)&pulse1_1.pqdp[i__ - 1], (ftnlen)sizeof(
			doublereal));
		do_fio(&c__1, (char *)&pulse1_1.pqed[i__ - 1], (ftnlen)sizeof(
			doublereal));
		do_fio(&c__1, (char *)&pualpha_1.vphmlt[i__ - 1], (ftnlen)
			sizeof(doublereal));
		do_fio(&c__1, (char *)&pulse1_1.pqet[i__ - 1], (ftnlen)sizeof(
			doublereal));
		do_fio(&c__1, (char *)&pulse1_1.pqod[i__ - 1], (ftnlen)sizeof(
			doublereal));
		do_fio(&c__1, (char *)&pulse1_1.pqot[i__ - 1], (ftnlen)sizeof(
			doublereal));
		do_fio(&c__1, (char *)&scrtch_1.sdel[i__ * 3 - 2], (ftnlen)
			sizeof(doublereal));
		do_fio(&c__1, (char *)&scrtch_1.sdel[i__ * 3 - 1], (ftnlen)
			sizeof(doublereal));
		do_fio(&c__1, (char *)&pualpha_1.vcmxmlt[i__ - 1], (ftnlen)
			sizeof(doublereal));
		do_fio(&c__1, (char *)&pulse1_1.pqcp[i__ - 1], (ftnlen)sizeof(
			doublereal));
		do_fio(&c__1, (char *)&pulse1_1.prmu[i__ - 1], (ftnlen)sizeof(
			doublereal));
		do_fio(&c__1, (char *)&pulse1_1.pqdt[i__ - 1], (ftnlen)sizeof(
			doublereal));
		do_fio(&c__1, (char *)&hcomp[i__ * 15 + 1], (ftnlen)sizeof(
			doublereal));
		do_fio(&c__1, (char *)&hcomp[i__ * 15 + 3], (ftnlen)sizeof(
			doublereal));
		e_wsfe();
	    }
L5003:
	    ;
	}
/* DBG END */
/* L220: */
    }

/* G Somers 11/14 REMOVED LONG BLOCK */

    return 0;
} /* wrtmod_ */

