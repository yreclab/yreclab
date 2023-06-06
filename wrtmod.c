/* wrtmod.f -- translated by f2c (version 20100827).
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
    logical lscrib, lpshll, lchemo, lconzo, ljout, lprtin, lpenv;
} ccout_;

#define ccout_1 ccout_

struct {
    integer npenv, nprt1, nprt2, nprtpt, npoint;
} ccout1_;

#define ccout1_1 ccout1_

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
	    /* was [3][5000] */, svel[5000];
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

/* Table of constant values */

static integer c__1 = 1;



/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */
/* WRTMOD */
/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */
/* Subroutine */ int wrtmod_(integer *m, logical *lshell, integer *jxbeg, 
	integer *jxend, integer *jcore, integer *jenv, doublereal *hcomp, 
	doublereal *hs1, doublereal *hd, doublereal *hl, doublereal *hp, 
	doublereal *hr, doublereal *ht, logical *lc, integer *model, 
	doublereal *bl, doublereal *teffl, doublereal *omega, doublereal *fp, 
	doublereal *ft, doublereal *eta2, doublereal *r0, doublereal *hjm, 
	doublereal *hi, doublereal *hs, doublereal *dage)
{
    /* Format strings */
    static char fmt_123[] = "(1x,2f12.8,1p6e16.8)";
    static char fmt_124[] = "(1x,f11.7,1p4e16.8)";
    static char fmt_10[] = "(/,\002 ABUNDANCES H, He, C, N, and O\002,/,2x"
	    ",\002SHELL\002,4x,\002X\002,9x,\002Y\002,9x,\002Z\002,8x,\002HE"
	    "3\002,7x,\002C12\002,7x,\002C13\002,7x,\002N14\002,7x,\002N15"
	    "\002,7x,\002O16\002,7x,\002O17\002,7x,\002O18\002)";
    static char fmt_15[] = "(1x,\002CENTRAL CONVECTION ZONE COMPOSITION: SHE"
	    "LLS 1 TO\002,i4)";
    static char fmt_50[] = "(1x,\002SURFACE CONVECTION ZONE COMPOSITION:\002"
	    ",1x,\002SHELLS\002,i4,\002 TO\002,i4)";
    static char fmt_20[] = "(\002 \002,i4,3x,11(1pe9.3,1x))";
    static char fmt_91[] = "(2x,\002SHELL\002,4x,\002X2\002,7x,\002LI6\002,7"
	    "x,\002LI7\002,8x,\002BE9\002)";
    static char fmt_92[] = "(1x,i4,3x,4(1pe9.3,1x))";
    static char fmt_100[] = "(/,1x,\002NO SURFACE CONVECTION ZONE\002)";
    static char fmt_110[] = "(/,1x,\002CONVECTION ZONE\002,/,4x,\002GRAV\002"
	    ",5x,\002LOG P\002,1x,\002LOG T\002,2x,\0021-R/RTOT\002,3x,\002M/"
	    "MSTAR\002,2x,\002LOG D\002,5x,\002O\002,6x,\002BETA\002,4x,\002D"
	    "ELR\002,5x,\002DEL\002,3x,\002DELA\002,2x,\002HII\002,3x,\002HEII"
	    "\002,1x,\002HEIII\002,3x,\002V\002)";
    static char fmt_130[] = "(1x,1pd10.3,1x,0p2f6.3,1pd10.3,0p1f10.6,0p1f7.3"
	    ",1pd10.2,0pf7.3,1pd9.2,0p5f6.3,1pd9.2)";
    static char fmt_121[] = "(/)";
    static char fmt_98[] = "(\002 ZONE\002,\002      R0\002,12x,\002A\002,12"
	    "x,\002RP/RE\002,11x,\002FP\002,11x,\002FT\002,10x,\002OMEGA\002,"
	    "11x,\002J/M\002,11x,\002MOMENT\002)";
    static char fmt_99[] = "(1x,i4,1p3e15.6,0p2f12.8,1p4e15.6)";
    static char fmt_200[] = "(/,1x,\002PT(C)  M/MSTAR\002,4x,\002L/LSUN\002,"
	    "8x,\002LOG(R)   LOG(T)\002,3x,\002LOG(P)\002,5x,\002LOG(D)\002,6"
	    "x,\002X\002,8x,\002Z\002,6x,\002ENERGY-NUCLEAR-NEUTRINO-GRAV\002)"
	    ;
    static char fmt_5001[] = "(\002 MODEL#=\002,i5,\002  NUMBER OF SHELLS IN"
	    " MODEL=\002,i5,\002 VER=\002,i2,/,\002 MASS=\002,f8.5,\002  LOG("
	    "TEFF)=\002,f8.5,/,\002 LOG(L/LSUN)=\002,f16.10,\002  LOG(R/RSUN)="
	    "\002,f16.10,/,\002 AGE=\002,1pe12.5,\002 GYR\002,/,\002 MIXING L"
	    "ENGTH PARAMETER=\002,0pf16.10,/,\002 ZAMS (X,Z)=\002,2f18.10)";
    static char fmt_210[] = "(i5,l1,f10.7,1pe14.6,0pf10.6,f9.6,2f10.6,2f8.5,"
	    "2x,1p3e11.3)";
    static char fmt_5052[] = "(5e16.9,/,5e16.9,/,5e16.9,/,5e16.9)";
    static char fmt_6052[] = "(5e23.16,/,5e23.16,/,5e23.16,/,5e23.16)";
    static char fmt_6053[] = "(6e23.16,/,6e23.16,/,6e23.16,/,5e23.16)";
    static char fmt_230[] = "(/,3x,\002PT\002,4x,\002BETA     ETA (C)   OPAC"
	    "ITY     DELR\002,6x,\002DEL\002,5x,\002DELA\002,3x,\002ION-HII-H"
	    "EII-HEIII\002,6x,\002PPI\002,3x,\002PPII  PPIII\002,4x,\002CN"
	    "O\002,5x,\002HE\002)";
    static char fmt_240[] = "(i5,2x,0pf7.5,f9.4,l2,1x,1pe10.4,e11.4,0p2f8.5,"
	    "2x,3f6.3,2x,5f7.4)";

    /* System generated locals */
    integer i__1;
    doublereal d__1;

    /* Builtin functions */
    double exp(doublereal), sqrt(doublereal);
    integer s_wsfe(cilist *), do_fio(integer *, char *, ftnlen), e_wsfe(void);

    /* Local variables */
    static doublereal a, b;
    static integer i__, j, k;
    static doublereal x, z__, cg;
    static integer id[5000];
    static doublereal fm, dr, fr, rl, gl, sg, fs, sv, xx1, xx2, xx3, xx4, xx5;
    static integer idm;
    static doublereal fpl, fsi, ftl;
    static integer ixx;
    static doublereal xxx, dum1[4], dum2[3], dum3[3], dum4[3], qdr1, qdr2, 
	    qpr1, qpr2;
    static integer jbeg, jend;
    static doublereal rmid;
    static integer katm, idum;
    static logical long__;
    static doublereal plim, divp, divr, qqpr, qqdr;
    static logical lsbc0, lprt;
    static integer kenv;
    static doublereal abeg0, amin0, amax0, ebeg0, emin0, emax0, duma;
    static integer ksaha;
    static doublereal depth, pelpf, hstot, rsurf, tempr;
    extern /* Subroutine */ int pindex_(integer *, integer *, logical *, 
	    integer *, integer *, integer *);
    static logical lpulpt;
    extern /* Subroutine */ int envint_(doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, integer *, logical *, 
	    logical *, doublereal *, doublereal *, doublereal *, doublereal *,
	     doublereal *, doublereal *, integer *, integer *, integer *, 
	    integer *, doublereal *, doublereal *, doublereal *, logical *);
    static doublereal rsurfl, rpoleq, qsmass;

    /* Fortran I/O blocks */
    static cilist io___11 = { 0, 0, 0, fmt_123, 0 };
    static cilist io___22 = { 0, 0, 0, fmt_124, 0 };
    static cilist io___26 = { 0, 0, 0, fmt_10, 0 };
    static cilist io___27 = { 0, 0, 0, fmt_15, 0 };
    static cilist io___30 = { 0, 0, 0, fmt_50, 0 };
    static cilist io___31 = { 0, 0, 0, fmt_20, 0 };
    static cilist io___33 = { 0, 0, 0, fmt_20, 0 };
    static cilist io___34 = { 0, 0, 0, fmt_50, 0 };
    static cilist io___35 = { 0, 0, 0, fmt_91, 0 };
    static cilist io___36 = { 0, 0, 0, fmt_15, 0 };
    static cilist io___37 = { 0, 0, 0, fmt_92, 0 };
    static cilist io___38 = { 0, 0, 0, fmt_50, 0 };
    static cilist io___66 = { 0, 0, 0, fmt_100, 0 };
    static cilist io___67 = { 0, 0, 0, fmt_110, 0 };
    static cilist io___74 = { 0, 0, 0, fmt_130, 0 };
    static cilist io___76 = { 0, 0, 0, fmt_121, 0 };
    static cilist io___78 = { 0, 0, 0, fmt_98, 0 };
    static cilist io___82 = { 0, 0, 0, fmt_99, 0 };
    static cilist io___83 = { 0, 0, 0, fmt_200, 0 };
    static cilist io___86 = { 0, 0, 0, fmt_5001, 0 };
    static cilist io___87 = { 0, 0, 0, fmt_210, 0 };
    static cilist io___89 = { 0, 0, 0, fmt_5052, 0 };
    static cilist io___90 = { 0, 0, 0, fmt_6052, 0 };
    static cilist io___91 = { 0, 0, 0, fmt_6053, 0 };
    static cilist io___92 = { 0, 0, 0, fmt_230, 0 };
    static cilist io___93 = { 0, 0, 0, fmt_240, 0 };


/* DBG PULSE */
/* MHP 7/96 COMMON BLOCK INSERTED FOR SOUND SPEED */
/* DBG */
/* DBG 7/92 COMMON BLOCK ADDED TO COMPUTE DEBYE-HUCKEL CORRECTION. */
/* DBG 7/95 To store variables for pulse output */
/*      DATA IHEADR/4H***+/  Appears to be unused  LLP */
    /* Parameter adjustments */
    --hs;
    --hi;
    --hjm;
    --r0;
    --eta2;
    --ft;
    --fp;
    --omega;
    --lc;
    --ht;
    --hr;
    --hp;
    --hl;
    --hd;
    --hs1;
    hcomp -= 16;

    /* Function Body */
    if (sound_1.lsound) {
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
	    io___11.ciunit = luout_1.imodpt;
	    s_wsfe(&io___11);
	    do_fio(&c__1, (char *)&fr, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&fm, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&xx1, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&xx2, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&xx3, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&xx4, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&xx5, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&sv, (ftnlen)sizeof(doublereal));
	    e_wsfe();
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
		io___22.ciunit = luout_1.imodpt;
		s_wsfe(&io___22);
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
/*  DETERMINE WHICH POINTS TO PRINT OUT. */
    pindex_(jxbeg, jxend, lshell, m, id, &idm);
    ccout_1.lpenv = TRUE_;
    long__ = *model % ccout1_1.nprt2 == 0;
/* DBG 6/93 ONLY PRINT OUT IF LSCRIB=T */
    if (ccout_1.lchemo && ccout_1.lscrib) {
/*  PRINT OUT THE DETAILED CHEMICAL COMPOSITION */
/*  LIGHT ELEMENTS(H2,LI,BE) PRINTED OUT SEPARATELY */
	io___26.ciunit = luout_1.imodpt;
	s_wsfe(&io___26);
	e_wsfe();
/*  CHECK FOR CENTRAL CONVECTION ZONE */
/*  A CENTRAL OR SURFACE CONVECTION ZONE HAS 1 SET OF ABUNDANCES */
/*  PRINTED PER ZONE RATHER THAN EVERY NPRTPT POINTS */
	if (*jcore > 1) {
	    io___27.ciunit = luout_1.imodpt;
	    s_wsfe(&io___27);
	    do_fio(&c__1, (char *)&(*jcore), (ftnlen)sizeof(integer));
	    e_wsfe();
	    i__1 = idm;
	    for (j = 2; j <= i__1; ++j) {
		if (id[j - 1] > *jcore) {
		    goto L40;
		}
/* L30: */
	    }
	    j = idm;
L40:
	    jbeg = j - 1;
	} else {
	    jbeg = 1;
	}
	if (*jenv < *m) {
/*  SURFACE CONVECTION ZONE */
	    if (id[jbeg - 1] > *jenv) {
/*  SPECIAL CASE;ONLY 1ST,LAST PTS. PRINTED,BOTH CONVECTIVE. */
		io___30.ciunit = luout_1.imodpt;
		s_wsfe(&io___30);
		do_fio(&c__1, (char *)&(*jenv), (ftnlen)sizeof(integer));
		do_fio(&c__1, (char *)&(*m), (ftnlen)sizeof(integer));
		e_wsfe();
		io___31.ciunit = luout_1.imodpt;
		s_wsfe(&io___31);
		do_fio(&c__1, (char *)&(*m), (ftnlen)sizeof(integer));
		for (i__ = 1; i__ <= 11; ++i__) {
		    do_fio(&c__1, (char *)&hcomp[i__ + *m * 15], (ftnlen)
			    sizeof(doublereal));
		}
		e_wsfe();
		goto L90;
	    }
	    i__1 = jbeg;
	    for (j = idm - 1; j >= i__1; --j) {
		if (id[j - 1] < *jenv) {
		    goto L70;
		}
/* L60: */
	    }
	    j = jbeg;
L70:
	    jend = j + 1;
	} else {
	    jend = idm;
	}
/*  PRINT OUT POINTS FROM OUTSIDE THE CENTRAL CZ TO THE SURFACE. */
	i__1 = jend;
	for (j = jbeg; j <= i__1; ++j) {
	    io___33.ciunit = luout_1.imodpt;
	    s_wsfe(&io___33);
	    do_fio(&c__1, (char *)&id[j - 1], (ftnlen)sizeof(integer));
	    for (i__ = 1; i__ <= 11; ++i__) {
		do_fio(&c__1, (char *)&hcomp[i__ + id[j - 1] * 15], (ftnlen)
			sizeof(doublereal));
	    }
	    e_wsfe();
/* L80: */
	}
	if (*jenv < *m) {
	    io___34.ciunit = luout_1.imodpt;
	    s_wsfe(&io___34);
	    do_fio(&c__1, (char *)&(*jenv), (ftnlen)sizeof(integer));
	    do_fio(&c__1, (char *)&(*m), (ftnlen)sizeof(integer));
	    e_wsfe();
	}
L90:
/*  PRINT OUT RUN OF LIGHT ELEMENT COMPOSITION */
	if (flag_1.lexcom) {
	    io___35.ciunit = luout_1.imodpt;
	    s_wsfe(&io___35);
	    e_wsfe();
	    if (*jcore > 1) {
		io___36.ciunit = luout_1.imodpt;
		s_wsfe(&io___36);
		do_fio(&c__1, (char *)&(*jcore), (ftnlen)sizeof(integer));
		e_wsfe();
	    }
	    i__1 = jend;
	    for (j = jbeg; j <= i__1; ++j) {
		io___37.ciunit = luout_1.imodpt;
		s_wsfe(&io___37);
		do_fio(&c__1, (char *)&id[j - 1], (ftnlen)sizeof(integer));
		for (i__ = 12; i__ <= 15; ++i__) {
		    do_fio(&c__1, (char *)&hcomp[i__ + id[j - 1] * 15], (
			    ftnlen)sizeof(doublereal));
		}
		e_wsfe();
/* L94: */
	    }
	    if (*jenv < *m) {
		io___38.ciunit = luout_1.imodpt;
		s_wsfe(&io___38);
		do_fio(&c__1, (char *)&(*jenv), (ftnlen)sizeof(integer));
		do_fio(&c__1, (char *)&(*m), (ftnlen)sizeof(integer));
		e_wsfe();
	    }
	}
    }
/* DBG PULSE: PRINT OUT PULSATION ENV AND ATM IN ENVINT */
    if (envgen_1.lenvg || pulse_1.lpulse) {
/*  INTEGRATE AN ENVELOPE FROM THE SURFACE TO THE CONVERGED MODEL, */
/*  PRINTING OUT THE RESULTS. */
/*  SET UP FLAGS AND COUNTERS. */
	lsbc0 = FALSE_;
/* DBG 6/93 Bug fix LPRT was always true */
	lprt = ccout_1.lscrib;
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
	envint_(&b, &fpl, &ftl, &gl, &hstot, &ixx, &lprt, &lsbc0, &plim, &rl, 
		teffl, &x, &z__, dum1, &idum, &katm, &kenv, &ksaha, dum2, 
		dum3, dum4, &lpulpt);
	intatm_1.atmbeg = abeg0;
	intatm_1.atmmin = amin0;
	intatm_1.atmmax = amax0;
	intenv_1.envbeg = ebeg0;
	intenv_1.envmin = emin0;
	intenv_1.envmax = emax0;
    }
/*  PRINT OUT CONVECTION ZONE DETAILS IF APPLICABLE */
/* DBG 6/93 ONLY PRINT IF LSCRIB= T */
    if (ccout_1.lconzo && ccout_1.lscrib) {
	if (*jenv == *m) {
	    io___66.ciunit = luout_1.imodpt;
	    s_wsfe(&io___66);
	    e_wsfe();
	    goto L140;
	}
	io___67.ciunit = luout_1.imodpt;
	s_wsfe(&io___67);
	e_wsfe();
	rsurfl = (*bl - const1_1.c4pil - const2_1.csigl - *teffl * 4. + 
		const_1.clsunl) * .5;
	rsurf = exp(const1_1.cln * rsurfl);
	fsi = exp(const1_1.cln * comp_1.stotal);
	for (j = idm; j >= 1; --j) {
	    i__ = id[j - 1];
	    if (i__ < *jenv) {
		goto L140;
	    }
	    sg = exp(const1_1.cln * (const2_1.cgl - hr[i__] * 2.)) * hs1[i__];
	    depth = 1. - exp(const1_1.cln * hr[i__]) / rsurf;
	    fs = hs1[i__] / fsi;
	    io___74.ciunit = luout_1.imodpt;
	    s_wsfe(&io___74);
	    do_fio(&c__1, (char *)&sg, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&hp[i__], (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&ht[i__], (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&depth, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&fs, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&hd[i__], (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&scrtch_1.so[i__ - 1], (ftnlen)sizeof(
		    doublereal));
	    do_fio(&c__1, (char *)&scrtch_1.sbeta[i__ - 1], (ftnlen)sizeof(
		    doublereal));
	    for (k = 1; k <= 3; ++k) {
		do_fio(&c__1, (char *)&scrtch_1.sdel[k + i__ * 3 - 4], (
			ftnlen)sizeof(doublereal));
	    }
	    for (k = 1; k <= 3; ++k) {
		do_fio(&c__1, (char *)&scrtch_1.sfxion[k + i__ * 3 - 4], (
			ftnlen)sizeof(doublereal));
	    }
	    do_fio(&c__1, (char *)&scrtch_1.svel[i__ - 1], (ftnlen)sizeof(
		    doublereal));
	    e_wsfe();
/* L120: */
	}
	io___76.ciunit = luout_1.imodpt;
	s_wsfe(&io___76);
	e_wsfe();
L140:
	;
    }
/* DBG 6/93 ONLY PRINT IF LSCRIB= T */
    if (rot_1.lrot && ccout_1.ljout && ccout_1.lscrib) {
/*  PRINT OUT ROTATION INFORMATION */
	cg = exp(const1_1.cln * const2_1.cgl);
	io___78.ciunit = luout_1.imodpt;
	s_wsfe(&io___78);
	e_wsfe();
	i__1 = idm;
	for (j = 1; j <= i__1; ++j) {
	    i__ = id[j - 1];
	    fm = exp(const1_1.cln * hs[i__]);
/* Computing 2nd power */
	    d__1 = omega[i__];
	    duma = const1_1.cc13 * (d__1 * d__1) / (cg * fm) * 5. / (eta2[i__]
		     + 2.);
/* Computing 3rd power */
	    d__1 = r0[i__];
	    a = duma * (d__1 * (d__1 * d__1));
	    rpoleq = (1. - a) / (a * .5 + 1.);
	    io___82.ciunit = luout_1.imodpt;
	    s_wsfe(&io___82);
	    do_fio(&c__1, (char *)&i__, (ftnlen)sizeof(integer));
	    do_fio(&c__1, (char *)&r0[i__], (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&a, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&rpoleq, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&fp[i__], (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&ft[i__], (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&omega[i__], (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&hjm[i__], (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&hi[i__], (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&roten_1.derot[i__ - 1], (ftnlen)sizeof(
		    doublereal));
	    e_wsfe();
/* L190: */
	}
    }
/*  WRITE OUT MODEL VITAL STATISTICS - L,R,T,P,RHO,X,Z,EPSILON */
/*  AS FUNCTIONS OF MASS FRACTION. */
/*  ENERGY GENERATION TERMS ARE STORED IN COMMON BLOCK /SCRTCH/ */
/*  THE LAST TIME THE MODEL STRUCTURE IS ALTERED(IN SR COEFFT) */
    if (ccout_1.lscrib) {
	io___83.ciunit = luout_1.imodpt;
	s_wsfe(&io___83);
	e_wsfe();
    }
    fsi = exp(-const1_1.cln * comp_1.stotal);
/* DBG PULSE: WRITE HEADER INFORMATION FOR PULSE MODEL */
    if (pulse_1.lpulse) {
	rsurfl = (*bl - const1_1.c4pil - const2_1.csigl - *teffl * 4. + 
		const_1.clsunl) * .5;
	tempr = rsurfl - const_1.crsunl;
	qsmass = pulse_1.xmsol;
	io___86.ciunit = lunum_1.iopmod;
	s_wsfe(&io___86);
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
	if (ccout_1.lscrib) {
	    io___87.ciunit = luout_1.imodpt;
	    s_wsfe(&io___87);
	    do_fio(&c__1, (char *)&i__, (ftnlen)sizeof(integer));
	    do_fio(&c__1, (char *)&lc[i__], (ftnlen)sizeof(logical));
	    do_fio(&c__1, (char *)&fs, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&hl[i__], (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&hr[i__], (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&ht[i__], (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&hp[i__], (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&hd[i__], (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&hcomp[i__ * 15 + 1], (ftnlen)sizeof(
		    doublereal));
	    do_fio(&c__1, (char *)&hcomp[i__ * 15 + 3], (ftnlen)sizeof(
		    doublereal));
	    do_fio(&c__1, (char *)&scrtch_1.sesum[i__ - 1], (ftnlen)sizeof(
		    doublereal));
	    do_fio(&c__1, (char *)&scrtch_1.seg[i__ * 7 - 2], (ftnlen)sizeof(
		    doublereal));
	    do_fio(&c__1, (char *)&scrtch_1.seg[i__ * 7 - 1], (ftnlen)sizeof(
		    doublereal));
	    e_wsfe();
/* DBG WRITE PULSE MODEL */
	}
	if (pulse_1.lpulse && ccout_1.lscrib) {
/* MHP 10/02 uncommented pelpf statement, used later in i/o */
/* 	   PELPF = CGAS * DEXP(CLN*(HT(I) + HD(I)))* PEMU(I) */
/*          ADDED X AND Z TO OUTPUT */
	    if (j == 2 && i__ == 1) {
		goto L5003;
	    }
	    if (pulse_1.ipver == 1) {
		pelpf = const2_1.cgas * exp(const1_1.cln * (ht[i__] + hd[i__])
			) * pulse1_1.pemu[i__ - 1];
		io___89.ciunit = lunum_1.iopmod;
		s_wsfe(&io___89);
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
		io___90.ciunit = lunum_1.iopmod;
		s_wsfe(&io___90);
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
		io___91.ciunit = lunum_1.iopmod;
		s_wsfe(&io___91);
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
    if (long__ && ccout_1.lscrib) {
	io___92.ciunit = luout_1.imodpt;
	s_wsfe(&io___92);
	e_wsfe();
	i__1 = idm;
	for (j = 1; j <= i__1; ++j) {
	    i__ = id[j - 1];
	    io___93.ciunit = luout_1.imodpt;
	    s_wsfe(&io___93);
	    do_fio(&c__1, (char *)&i__, (ftnlen)sizeof(integer));
	    do_fio(&c__1, (char *)&scrtch_1.sbeta[i__ - 1], (ftnlen)sizeof(
		    doublereal));
	    do_fio(&c__1, (char *)&scrtch_1.seta[i__ - 1], (ftnlen)sizeof(
		    doublereal));
	    do_fio(&c__1, (char *)&scrtch_1.locons[i__ - 1], (ftnlen)sizeof(
		    logical));
	    do_fio(&c__1, (char *)&scrtch_1.so[i__ - 1], (ftnlen)sizeof(
		    doublereal));
	    for (k = 1; k <= 3; ++k) {
		do_fio(&c__1, (char *)&scrtch_1.sdel[k + i__ * 3 - 4], (
			ftnlen)sizeof(doublereal));
	    }
	    for (k = 1; k <= 3; ++k) {
		do_fio(&c__1, (char *)&scrtch_1.sfxion[k + i__ * 3 - 4], (
			ftnlen)sizeof(doublereal));
	    }
	    for (k = 1; k <= 5; ++k) {
		do_fio(&c__1, (char *)&scrtch_1.seg[k + i__ * 7 - 8], (ftnlen)
			sizeof(doublereal));
	    }
	    e_wsfe();
/* L250: */
	}
    }
    return 0;
} /* wrtmod_ */

