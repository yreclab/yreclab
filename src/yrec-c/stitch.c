/* stitch.f -- translated by f2c (version 20061008).
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
    logical lstore, lstatm, lstenv, lstmod, lstphys, lstrot, lscrib, lstch, 
	    lphhd;
} ccout_;

#define ccout_1 ccout_

struct {
    integer ilast, idebug, itrack, ishort, imilne, imodpt, istor, iowr;
} luout_;

#define luout_1 luout_

struct {
    doublereal atmstp, envstp;
    logical lenvg;
} envgen_;

#define envgen_1 envgen_

struct {
    doublereal atmerr, atmd0, atmbeg, atmmin, atmmax;
} intatm_;

#define intatm_1 intatm_

struct {
    doublereal enverr, envbeg, envmin, envmax;
} intenv_;

#define intenv_1 intenv_

struct {
    doublereal cln, clni, c4pi, c4pil, c4pi3l, cc13, cc23, cpi;
} const1_;

#define const1_1 const1_

struct {
    doublereal clsun, clsunl, clnsun, cmsun, cmsunl, crsun, crsunl, cmbol;
} const_;

#define const_1 const_

struct {
    doublereal cgas, ca3, ca3l, csig, csigl, cgl, cmkh, cmkhn;
} const2_;

#define const2_1 const2_

struct {
    doublereal wnew, walpcz, acfpft;
    integer itfp1, itfp2;
    logical lrot, linstb, lwnew;
} rot_;

#define rot_1 rot_

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
    doublereal sesum[5000], seg[35000]	/* was [7][5000] */, sbeta[5000], 
	    seta[5000];
    logical locons[5000];
    doublereal so[5000], sdel[15000]	/* was [3][5000] */, sfxion[15000]	
	    /* was [3][5000] */, svel[5000], scp[5000];
} scrtch_;

#define scrtch_1 scrtch_

struct {
    doublereal pqdp[5000], pqed[5000], pqet[5000], pqod[5000], pqot[5000], 
	    pqcp[5000], prmu[5000], pqdt[5000], pemu[5000];
    logical lpumod;
} pulse1_;

#define pulse1_1 pulse1_

struct {
    doublereal spotf, spotx;
    logical lsdepth;
} spots_;

#define spots_1 spots_

struct {
    logical lnewtcz, lcalcenv;
    doublereal taucz, taucz0, pphot, pphot0, fracstep;
} ovrtrn_;

#define ovrtrn_1 ovrtrn_

struct {
    doublereal derot[5000];
} roten_;

#define roten_1 roten_

struct {
    doublereal gam1[5000];
    logical lsound;
} sound_;

#define sound_1 sound_

struct {
    doublereal ves[5000], ves0[5000], vss[5000], vss0[5000], hle[5000], vgsf[
	    5000], vgsf0[5000], vmu[5000];
} temp2_;

#define temp2_1 temp2_

/* Table of constant values */

static integer c__1 = 1;
static logical c_true = TRUE_;
static logical c_false = FALSE_;
static real c_b89 = 0.f;
static doublereal c_b111 = 4.;

/* Subroutine */ int stitch_(doublereal *hcomp, doublereal *hr, doublereal *
	hp, doublereal *hd, doublereal *hs, doublereal *ht, doublereal *hl, 
	doublereal *hs1, doublereal *omega, doublereal *eta2, doublereal *hi, 
	doublereal *r0, doublereal *hjm, doublereal *fp, doublereal *ft, 
	doublereal *teffl, doublereal *hstot, doublereal *bl, integer *m, 
	logical *lc, integer *model)
{
    /* Format strings */
    static char fmt_62[] = "(i6,1x,i6,0p2f18.14,1pe24.16,0p3f18.14,1pe24.16,"
	    "1x,l1,1x,l1,1x,l1,1x,l1,3(0pf12.9),12(0pe16.8),2x,1pe10.4,1pe11."
	    "3,e12.4,e12.4,e12.4,1pe12.4,0pf9.5,f9.5,f9.5,f9.5,f9.5,f9.5,e12."
	    "4,e12.4,e12.4,e12.4,e12.4,e13.5,e13.5,e13.5,e13.5,e13.5,e13.5,e1"
	    "3.5,e13.5,e14.6,e14.6,e14.6,e14.6,e14.6,e14.6,e14.6,e11.3,e11.3,"
	    "e11.3,e11.3)";

    /* System generated locals */
    integer i__1;
    doublereal d__1;

    /* Builtin functions */
    double exp(doublereal);
    integer s_wsfe(cilist *), do_fio(integer *, char *, ftnlen), e_wsfe(void);
    double pow_dd(doublereal *, doublereal *), d_lg10(doublereal *);

    /* Local variables */
    static doublereal a, b;
    static integer i__, j, k;
    static doublereal x, z__, cg, fm, gl, sg, rl, rad, fpl, ftl;
    static integer ixx;
    static doublereal dum1[4], dum2[3], dum3[3], dum4[3], duma;
    static integer idum, katm;
    static doublereal plim, abeg0, vtot, ebeg0;
    static integer kenv;
    static logical lprt, lsbc0;
    static doublereal amin0, amax0, emin0, emax0, envs1[5000];
    static integer ksaha;
    static doublereal ateffl, rpoleq;
    extern /* Subroutine */ int envint_(doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, integer *, logical *, 
	    logical *, doublereal *, doublereal *, doublereal *, doublereal *,
	     doublereal *, doublereal *, integer *, integer *, integer *, 
	    integer *, doublereal *, doublereal *, doublereal *, logical *);
    static logical lpulpt;

    /* Fortran I/O blocks */
    static cilist io___9 = { 0, 0, 0, fmt_62, 0 };
    static cilist io___12 = { 0, 0, 0, fmt_62, 0 };
    static cilist io___41 = { 0, 0, 0, fmt_62, 0 };
    static cilist io___43 = { 0, 0, 0, fmt_62, 0 };


/* G Somers 10/14, Add spot common block */
/* G Somers END */
/* G Somers 3/17, ADDING NEW TAUCZ COMMON BLOCK */


/* STITCH: and alternate file format for .store that provides profiles for each */
/* desired model. Stitches the envelope and atmosphere solutions onto the interior */
/* when LSTENV and LSTATM are true. Will not provide atmosphere information when */
/* atmosphere tables are used. */

/* The output columns in the new .store format are: */
/* 1 MODEL, 2 SHELL, 3 log(mass[g]), 4 log(r[cm]), 5 L/Lsun, 6 log(P[cgs]), 7 log(T[K])', */
/* 8 log(DENSITY[cgs]),9 OMEGA(rad/s),10 CONVECTIVE?, 11 INTERIOR_POINT?, 12 ENVLELOPE_PT? */
/* 13 ATMOSPHERE_POINT?, 14 H1(mass frac), 15 He4(mass frac),16 METALS(mass frac), */
/* 17 He3(mass frac), 18 C12(mass frac), 19 C13(mass frac), 20 N14(mass frac), */
/* 21 N15(mass frac), 22 O16(mass frac), 23 O17(mass frac), 24 O18(mass frac), */
/* 25 H2(mass frac), 26 Li6(mass frac),27 Li7(mass frac),28 Be9(mass frac),29 OPACITY[cgs] */
/* 30 GRAVITY(cgs), 31 DELR(Rad. temp. grad), 32 DEL(actual temp grad), */
/* 33 DELA(adiabatic temp grad), 34 CONVECTIVE _VELOCITY[cm/s],35 GAM1(adiabatic exponent), */
/* 36 HII, 37 HEII, 38 HEIII, 39 BETA, 40 ETA, 41 PPI, 42 PPII, 43 PPIII, 44, CNO, 45 3HE */
/* 46 E_NUC,47 E_NEU,48 E_GRAV,49 Cp,50 dlnrho/dlnT,51 A, 52 RP/RE, 53 FP, 54 FT, 55 J/M, */
/* 56 MOMENT, 57 DEL_KE, 58 V_ES, 59 V_GSF, 60 V_SS, 61 VTOT   ' */

/* ****************************  WRITE OUT INTERIOR INFORMATION   ********************** */
    /* Parameter adjustments */
    --lc;
    --ft;
    --fp;
    --hjm;
    --r0;
    --hi;
    --eta2;
    --omega;
    --hs1;
    --hl;
    --ht;
    --hs;
    --hd;
    --hp;
    --hr;
    hcomp -= 16;

    /* Function Body */
    cg = exp(const1_1.cln * const2_1.cgl);
    i__1 = *m;
    for (i__ = 1; i__ <= i__1; ++i__) {
	sg = exp(const1_1.cln * (const2_1.cgl - hr[i__] * 2.)) * hs1[i__];
/* LC 10/25 Edits for compatibility with F77: */
	if (rot_1.lrot) {
	    fm = exp(const1_1.cln * hs[i__]);
/* Computing 2nd power */
	    d__1 = omega[i__];
	    duma = const1_1.cc13 * (d__1 * d__1) / (cg * fm) * 5. / (eta2[i__]
		     + 2.);
/* Computing 3rd power */
	    d__1 = r0[i__];
	    a = duma * (d__1 * (d__1 * d__1));
	    rpoleq = (1. - a) / (a * .5 + 1.);
	    vtot = temp2_1.ves[i__ - 1] + temp2_1.vgsf[i__ - 1] + temp2_1.vss[
		    i__ - 1];
	    io___9.ciunit = luout_1.istor;
	    s_wsfe(&io___9);
	    do_fio(&c__1, (char *)&(*model), (ftnlen)sizeof(integer));
	    do_fio(&c__1, (char *)&i__, (ftnlen)sizeof(integer));
	    do_fio(&c__1, (char *)&hs[i__], (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&hr[i__], (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&hl[i__], (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&hp[i__], (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&ht[i__], (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&hd[i__], (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&omega[i__], (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&lc[i__], (ftnlen)sizeof(logical));
	    do_fio(&c__1, (char *)&c_true, (ftnlen)sizeof(logical));
	    do_fio(&c__1, (char *)&c_false, (ftnlen)sizeof(logical));
	    do_fio(&c__1, (char *)&c_false, (ftnlen)sizeof(logical));
	    for (j = 1; j <= 15; ++j) {
		do_fio(&c__1, (char *)&hcomp[j + i__ * 15], (ftnlen)sizeof(
			doublereal));
	    }
	    do_fio(&c__1, (char *)&scrtch_1.so[i__ - 1], (ftnlen)sizeof(
		    doublereal));
	    do_fio(&c__1, (char *)&sg, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&scrtch_1.sdel[i__ * 3 - 3], (ftnlen)sizeof(
		    doublereal));
	    do_fio(&c__1, (char *)&scrtch_1.sdel[i__ * 3 - 2], (ftnlen)sizeof(
		    doublereal));
	    do_fio(&c__1, (char *)&scrtch_1.sdel[i__ * 3 - 1], (ftnlen)sizeof(
		    doublereal));
	    do_fio(&c__1, (char *)&scrtch_1.svel[i__ - 1], (ftnlen)sizeof(
		    doublereal));
	    do_fio(&c__1, (char *)&sound_1.gam1[i__ - 1], (ftnlen)sizeof(
		    doublereal));
	    do_fio(&c__1, (char *)&scrtch_1.sfxion[i__ * 3 - 3], (ftnlen)
		    sizeof(doublereal));
	    do_fio(&c__1, (char *)&scrtch_1.sfxion[i__ * 3 - 2], (ftnlen)
		    sizeof(doublereal));
	    do_fio(&c__1, (char *)&scrtch_1.sfxion[i__ * 3 - 1], (ftnlen)
		    sizeof(doublereal));
	    do_fio(&c__1, (char *)&envstruct_1.ebetas[i__ - 1], (ftnlen)
		    sizeof(doublereal));
	    do_fio(&c__1, (char *)&scrtch_1.seta[i__ - 1], (ftnlen)sizeof(
		    doublereal));
	    for (k = 1; k <= 5; ++k) {
		do_fio(&c__1, (char *)&scrtch_1.seg[k + i__ * 7 - 8], (ftnlen)
			sizeof(doublereal));
	    }
	    do_fio(&c__1, (char *)&scrtch_1.sesum[i__ - 1], (ftnlen)sizeof(
		    doublereal));
	    do_fio(&c__1, (char *)&scrtch_1.seg[i__ * 7 - 2], (ftnlen)sizeof(
		    doublereal));
	    do_fio(&c__1, (char *)&scrtch_1.seg[i__ * 7 - 1], (ftnlen)sizeof(
		    doublereal));
	    do_fio(&c__1, (char *)&scrtch_1.scp[i__ - 1], (ftnlen)sizeof(
		    doublereal));
	    do_fio(&c__1, (char *)&pulse1_1.pqdt[i__ - 1], (ftnlen)sizeof(
		    doublereal));
	    do_fio(&c__1, (char *)&a, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&rpoleq, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&fp[i__], (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&ft[i__], (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&hjm[i__], (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&hi[i__], (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&roten_1.derot[i__ - 1], (ftnlen)sizeof(
		    doublereal));
	    do_fio(&c__1, (char *)&temp2_1.ves[i__ - 1], (ftnlen)sizeof(
		    doublereal));
	    do_fio(&c__1, (char *)&temp2_1.vgsf[i__ - 1], (ftnlen)sizeof(
		    doublereal));
	    do_fio(&c__1, (char *)&temp2_1.vss[i__ - 1], (ftnlen)sizeof(
		    doublereal));
	    do_fio(&c__1, (char *)&vtot, (ftnlen)sizeof(doublereal));
	    e_wsfe();
	} else {
	    io___12.ciunit = luout_1.istor;
	    s_wsfe(&io___12);
	    do_fio(&c__1, (char *)&(*model), (ftnlen)sizeof(integer));
	    do_fio(&c__1, (char *)&i__, (ftnlen)sizeof(integer));
	    do_fio(&c__1, (char *)&hs[i__], (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&hr[i__], (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&hl[i__], (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&hp[i__], (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&ht[i__], (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&hd[i__], (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&omega[i__], (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&lc[i__], (ftnlen)sizeof(logical));
	    do_fio(&c__1, (char *)&c_true, (ftnlen)sizeof(logical));
	    do_fio(&c__1, (char *)&c_false, (ftnlen)sizeof(logical));
	    do_fio(&c__1, (char *)&c_false, (ftnlen)sizeof(logical));
	    for (j = 1; j <= 15; ++j) {
		do_fio(&c__1, (char *)&hcomp[j + i__ * 15], (ftnlen)sizeof(
			doublereal));
	    }
	    do_fio(&c__1, (char *)&scrtch_1.so[i__ - 1], (ftnlen)sizeof(
		    doublereal));
	    do_fio(&c__1, (char *)&sg, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&scrtch_1.sdel[i__ * 3 - 3], (ftnlen)sizeof(
		    doublereal));
	    do_fio(&c__1, (char *)&scrtch_1.sdel[i__ * 3 - 2], (ftnlen)sizeof(
		    doublereal));
	    do_fio(&c__1, (char *)&scrtch_1.sdel[i__ * 3 - 1], (ftnlen)sizeof(
		    doublereal));
	    do_fio(&c__1, (char *)&scrtch_1.svel[i__ - 1], (ftnlen)sizeof(
		    doublereal));
	    do_fio(&c__1, (char *)&sound_1.gam1[i__ - 1], (ftnlen)sizeof(
		    doublereal));
	    do_fio(&c__1, (char *)&scrtch_1.sfxion[i__ * 3 - 3], (ftnlen)
		    sizeof(doublereal));
	    do_fio(&c__1, (char *)&scrtch_1.sfxion[i__ * 3 - 2], (ftnlen)
		    sizeof(doublereal));
	    do_fio(&c__1, (char *)&scrtch_1.sfxion[i__ * 3 - 1], (ftnlen)
		    sizeof(doublereal));
	    do_fio(&c__1, (char *)&envstruct_1.ebetas[i__ - 1], (ftnlen)
		    sizeof(doublereal));
	    do_fio(&c__1, (char *)&scrtch_1.seta[i__ - 1], (ftnlen)sizeof(
		    doublereal));
	    for (k = 1; k <= 5; ++k) {
		do_fio(&c__1, (char *)&scrtch_1.seg[k + i__ * 7 - 8], (ftnlen)
			sizeof(doublereal));
	    }
	    do_fio(&c__1, (char *)&scrtch_1.sesum[i__ - 1], (ftnlen)sizeof(
		    doublereal));
	    do_fio(&c__1, (char *)&scrtch_1.seg[i__ * 7 - 2], (ftnlen)sizeof(
		    doublereal));
	    do_fio(&c__1, (char *)&scrtch_1.seg[i__ * 7 - 1], (ftnlen)sizeof(
		    doublereal));
	    do_fio(&c__1, (char *)&scrtch_1.scp[i__ - 1], (ftnlen)sizeof(
		    doublereal));
	    do_fio(&c__1, (char *)&pulse1_1.pqdt[i__ - 1], (ftnlen)sizeof(
		    doublereal));
	    do_fio(&c__1, (char *)&c_b89, (ftnlen)sizeof(real));
	    do_fio(&c__1, (char *)&c_b89, (ftnlen)sizeof(real));
	    do_fio(&c__1, (char *)&c_b89, (ftnlen)sizeof(real));
	    do_fio(&c__1, (char *)&c_b89, (ftnlen)sizeof(real));
	    do_fio(&c__1, (char *)&c_b89, (ftnlen)sizeof(real));
	    do_fio(&c__1, (char *)&c_b89, (ftnlen)sizeof(real));
	    do_fio(&c__1, (char *)&c_b89, (ftnlen)sizeof(real));
	    do_fio(&c__1, (char *)&c_b89, (ftnlen)sizeof(real));
	    do_fio(&c__1, (char *)&c_b89, (ftnlen)sizeof(real));
	    do_fio(&c__1, (char *)&c_b89, (ftnlen)sizeof(real));
	    do_fio(&c__1, (char *)&c_b89, (ftnlen)sizeof(real));
	    e_wsfe();
	}
/* C write out the basic info */
/*            WRITE(ISTOR,62,ADVANCE='no') MODEL,I,HS(I),HR(I),HL(I),HP(I), */
/*     *         HT(I),HD(I),OMEGA(I),LC(I),.TRUE.,.FALSE.,.FALSE.,(HCOMP(J,I),J=1,15) */
/* C write out additional physics if desired */
/*            WRITE(ISTOR,63,ADVANCE='no') SO(I),SG,SDEL(1,I),SDEL(2,I), */
/*     *           SDEL(3,I),SVEL(I),GAM1(I),SFXION(1,I),SFXION(2,I),SFXION(3,I), */
/*     *           EBETAS(I),SETA(I),(SEG(K,I),K=1,5),SESUM(I),SEG(6,I),SEG(7,I), */
/*     *           SCP(I),PQDT(I) */
/* C write out additional rotation info if rotation is on */
/*            IF(LROT)THEN */
/*              FM = DEXP(CLN*HS(I)) */
/*              DUMA = CC13*OMEGA(I)**2/(CG*FM)*5.D0/(2.D0+ETA2(I)) */
/*              A = DUMA * R0(I)**3 */
/*              RPOLEQ = (1.0D0 - A)/(1.0D0 + 0.5D0*A) */
/*              VTOT = VES(I)+VGSF(I)+VSS(I) */
/*              WRITE(ISTOR,64) A,RPOLEQ,FP(I),FT(I),HJM(I),HI(I),DEROT(I), */
/*     *            VES(I),VGSF(I),VSS(I),VTOT */
/*            ELSE */
/*               WRITE(ISTOR,64) 0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0 */
/*            ENDIF */
    }
/* **************************   WRITE OUT ENVELOPE INFORMATION   ********************** */
    if (ccout_1.lstenv) {
/* Begin by "dropping a sinkline" with the envelope integrator */
/* only provide an envelope if asked to do so */
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
	idum = 0;
	b = exp(const1_1.cln * *bl);
	fpl = fp[*m];
	ftl = ft[*m];
	katm = 0;
	kenv = 0;
	ksaha = 0;
	ixx = 0;
	lprt = TRUE_;
	lsbc0 = FALSE_;
	x = hcomp[*m * 15 + 1];
	z__ = hcomp[*m * 15 + 3];
	rl = (*bl + const_1.clsunl - *teffl * 4. - const1_1.c4pil - 
		const2_1.csigl) * .5;
	gl = const2_1.cgl + *hstot - rl - rl;
	plim = hp[*m];
/* G Somers 10/14, FOR SPOTTED RUNS, FIND THE */
/* PRESSURE AT THE AMBIENT TEMPERATURE ATEFFL */
	if (lc[*m] && spots_1.spotf != 0.f && spots_1.spotx != 1.f) {
	    d__1 = spots_1.spotf * pow_dd(&spots_1.spotx, &c_b111) + 1.f - 
		    spots_1.spotf;
	    ateffl = *teffl - d_lg10(&d__1) * .25f;
	} else {
	    ateffl = *teffl;
	}
	envint_(&b, &fpl, &ftl, &gl, hstot, &ixx, &lprt, &lsbc0, &plim, &rl, &
		ateffl, &x, &z__, dum1, &idum, &katm, &kenv, &ksaha, dum2, 
		dum3, dum4, &lpulpt);
/* DEFINE SOME ARRAYS WE NEED */
	i__1 = envstruct_1.numenv;
	for (i__ = 1; i__ <= i__1; ++i__) {
	    envs1[i__ - 1] = exp(const1_1.cln * (envstruct_1.envs[i__ - 1] + *
		    hstot));
	}
	i__1 = *m + envstruct_1.numenv;
	for (i__ = *m + 1; i__ <= i__1; ++i__) {
	    sg = exp(const1_1.cln * (const2_1.cgl - envstruct_1.envr[i__ - *m 
		    - 1] * 2.)) * envs1[i__ - *m - 1];
/* LC 10/25 Edits for compatibility with F77: */
	    io___41.ciunit = luout_1.istor;
	    s_wsfe(&io___41);
	    do_fio(&c__1, (char *)&(*model), (ftnlen)sizeof(integer));
	    do_fio(&c__1, (char *)&i__, (ftnlen)sizeof(integer));
	    d__1 = envstruct_1.envs[i__ - *m - 1] + *hstot;
	    do_fio(&c__1, (char *)&d__1, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&envstruct_1.envr[i__ - *m - 1], (ftnlen)
		    sizeof(doublereal));
	    do_fio(&c__1, (char *)&envstruct_1.envl[i__ - *m - 1], (ftnlen)
		    sizeof(doublereal));
	    do_fio(&c__1, (char *)&envstruct_1.envp[i__ - *m - 1], (ftnlen)
		    sizeof(doublereal));
	    do_fio(&c__1, (char *)&envstruct_1.envt[i__ - *m - 1], (ftnlen)
		    sizeof(doublereal));
	    do_fio(&c__1, (char *)&envstruct_1.envd[i__ - *m - 1], (ftnlen)
		    sizeof(doublereal));
	    do_fio(&c__1, (char *)&omega[*m], (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&envstruct_1.lcenv[i__ - *m - 1], (ftnlen)
		    sizeof(logical));
	    do_fio(&c__1, (char *)&c_false, (ftnlen)sizeof(logical));
	    do_fio(&c__1, (char *)&c_true, (ftnlen)sizeof(logical));
	    do_fio(&c__1, (char *)&c_false, (ftnlen)sizeof(logical));
	    for (j = 1; j <= 15; ++j) {
		do_fio(&c__1, (char *)&hcomp[j + *m * 15], (ftnlen)sizeof(
			doublereal));
	    }
	    do_fio(&c__1, (char *)&envstruct_1.envo[i__ - *m - 1], (ftnlen)
		    sizeof(doublereal));
	    do_fio(&c__1, (char *)&sg, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&envstruct_1.edels[(i__ - *m) * 3 - 3], (
		    ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&envstruct_1.edels[(i__ - *m) * 3 - 2], (
		    ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&envstruct_1.edels[(i__ - *m) * 3 - 1], (
		    ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&envstruct_1.evels[i__ - *m - 1], (ftnlen)
		    sizeof(doublereal));
	    do_fio(&c__1, (char *)&envstruct_1.egam1[i__ - *m - 1], (ftnlen)
		    sizeof(doublereal));
	    do_fio(&c__1, (char *)&envstruct_1.efxions[(i__ - *m) * 3 - 3], (
		    ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&envstruct_1.efxions[(i__ - *m) * 3 - 2], (
		    ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&envstruct_1.efxions[(i__ - *m) * 3 - 1], (
		    ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&envstruct_1.ebetas[i__ - *m - 1], (ftnlen)
		    sizeof(doublereal));
	    do_fio(&c__1, (char *)&c_b89, (ftnlen)sizeof(real));
	    do_fio(&c__1, (char *)&c_b89, (ftnlen)sizeof(real));
	    do_fio(&c__1, (char *)&c_b89, (ftnlen)sizeof(real));
	    do_fio(&c__1, (char *)&c_b89, (ftnlen)sizeof(real));
	    do_fio(&c__1, (char *)&c_b89, (ftnlen)sizeof(real));
	    do_fio(&c__1, (char *)&c_b89, (ftnlen)sizeof(real));
	    do_fio(&c__1, (char *)&c_b89, (ftnlen)sizeof(real));
	    do_fio(&c__1, (char *)&c_b89, (ftnlen)sizeof(real));
	    do_fio(&c__1, (char *)&c_b89, (ftnlen)sizeof(real));
	    do_fio(&c__1, (char *)&envstruct_1.eqcp[i__ - *m - 1], (ftnlen)
		    sizeof(doublereal));
	    do_fio(&c__1, (char *)&envstruct_1.eqdt[i__ - *m - 1], (ftnlen)
		    sizeof(doublereal));
	    do_fio(&c__1, (char *)&c_b89, (ftnlen)sizeof(real));
	    do_fio(&c__1, (char *)&c_b89, (ftnlen)sizeof(real));
	    do_fio(&c__1, (char *)&c_b89, (ftnlen)sizeof(real));
	    do_fio(&c__1, (char *)&c_b89, (ftnlen)sizeof(real));
	    do_fio(&c__1, (char *)&c_b89, (ftnlen)sizeof(real));
	    do_fio(&c__1, (char *)&c_b89, (ftnlen)sizeof(real));
	    do_fio(&c__1, (char *)&c_b89, (ftnlen)sizeof(real));
	    do_fio(&c__1, (char *)&c_b89, (ftnlen)sizeof(real));
	    do_fio(&c__1, (char *)&c_b89, (ftnlen)sizeof(real));
	    do_fio(&c__1, (char *)&c_b89, (ftnlen)sizeof(real));
	    do_fio(&c__1, (char *)&c_b89, (ftnlen)sizeof(real));
	    e_wsfe();
/* C write out the basic info. Omega and abundances take value of last interior point. */
/*            WRITE(ISTOR,62,ADVANCE='no') MODEL,I,ENVS(I-M)+HSTOT,ENVR(I-M),ENVL(I-M), */
/*     *      ENVP(I-M),ENVT(I-M),ENVD(I-M),OMEGA(M),LCENV(I-M),.FALSE.,.TRUE.,.FALSE., */
/*     *      (HCOMP(J,M),J=1,15) */
/* C write out additional physics */
/*               WRITE(ISTOR,63,ADVANCE='no') ENVO(I-M),SG,EDELS(1,I-M),EDELS(2,I-M), */
/*     *           EDELS(3,I-M),EVELS(I-M),EGAM1(I-M),EFXIONS(1,I-M),EFXIONS(2,I-M), */
/*     *           EFXIONS(3,I-M),EBETAS(I-M),0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0, */
/*     *           EQCP(I-M),EQDT(I-M) */
/* C             zero out rotation columns for envelope */
/*               WRITE(ISTOR,64) 0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0 */
	}
    }
/* *************************** WRITE OUT ATMOSPHERE INFORMATION  ************************ */
/* Finish with the atmosphere, if the atmosphere was computed */
    if (ccout_1.lstatm) {
	for (i__ = atmstruct_1.numatm; i__ >= 1; --i__) {
/* write out the basic info. Omega and abundances take value of last interior point. */
	    d__1 = exp(const1_1.cln * envstruct_1.envr[envstruct_1.numenv - 1]
		    ) + atmstruct_1.atmor[i__ - 1];
	    rad = d_lg10(&d__1);
/* LC 10/25 Edits for compatibility with F77: */
	    io___43.ciunit = luout_1.istor;
	    s_wsfe(&io___43);
	    do_fio(&c__1, (char *)&(*model), (ftnlen)sizeof(integer));
	    i__1 = atmstruct_1.numatm - i__ + *m + envstruct_1.numenv;
	    do_fio(&c__1, (char *)&i__1, (ftnlen)sizeof(integer));
	    do_fio(&c__1, (char *)&(*hstot), (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&rad, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&b, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&atmstruct_1.atmop[i__ - 1], (ftnlen)sizeof(
		    doublereal));
	    do_fio(&c__1, (char *)&atmstruct_1.atmot[i__ - 1], (ftnlen)sizeof(
		    doublereal));
	    do_fio(&c__1, (char *)&atmstruct_1.atmod[i__ - 1], (ftnlen)sizeof(
		    doublereal));
	    do_fio(&c__1, (char *)&omega[*m], (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&c_false, (ftnlen)sizeof(logical));
	    do_fio(&c__1, (char *)&c_false, (ftnlen)sizeof(logical));
	    do_fio(&c__1, (char *)&c_false, (ftnlen)sizeof(logical));
	    do_fio(&c__1, (char *)&c_true, (ftnlen)sizeof(logical));
	    for (j = 1; j <= 15; ++j) {
		do_fio(&c__1, (char *)&hcomp[j + *m * 15], (ftnlen)sizeof(
			doublereal));
	    }
	    do_fio(&c__1, (char *)&atmstruct_1.atmoo[i__ - 1], (ftnlen)sizeof(
		    doublereal));
	    do_fio(&c__1, (char *)&sg, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&atmstruct_1.adels[i__ * 3 - 3], (ftnlen)
		    sizeof(doublereal));
	    do_fio(&c__1, (char *)&atmstruct_1.adels[i__ * 3 - 2], (ftnlen)
		    sizeof(doublereal));
	    do_fio(&c__1, (char *)&atmstruct_1.adels[i__ * 3 - 1], (ftnlen)
		    sizeof(doublereal));
	    do_fio(&c__1, (char *)&c_b89, (ftnlen)sizeof(real));
	    do_fio(&c__1, (char *)&atmstruct_1.agam1[i__ - 1], (ftnlen)sizeof(
		    doublereal));
	    do_fio(&c__1, (char *)&atmstruct_1.afxions[i__ * 3 - 3], (ftnlen)
		    sizeof(doublereal));
	    do_fio(&c__1, (char *)&atmstruct_1.afxions[i__ * 3 - 2], (ftnlen)
		    sizeof(doublereal));
	    do_fio(&c__1, (char *)&atmstruct_1.afxions[i__ * 3 - 1], (ftnlen)
		    sizeof(doublereal));
	    do_fio(&c__1, (char *)&atmstruct_1.abetas[i__ - 1], (ftnlen)
		    sizeof(doublereal));
	    do_fio(&c__1, (char *)&c_b89, (ftnlen)sizeof(real));
	    do_fio(&c__1, (char *)&c_b89, (ftnlen)sizeof(real));
	    do_fio(&c__1, (char *)&c_b89, (ftnlen)sizeof(real));
	    do_fio(&c__1, (char *)&c_b89, (ftnlen)sizeof(real));
	    do_fio(&c__1, (char *)&c_b89, (ftnlen)sizeof(real));
	    do_fio(&c__1, (char *)&c_b89, (ftnlen)sizeof(real));
	    do_fio(&c__1, (char *)&c_b89, (ftnlen)sizeof(real));
	    do_fio(&c__1, (char *)&c_b89, (ftnlen)sizeof(real));
	    do_fio(&c__1, (char *)&c_b89, (ftnlen)sizeof(real));
	    do_fio(&c__1, (char *)&atmstruct_1.atmocp[i__ - 1], (ftnlen)
		    sizeof(doublereal));
	    do_fio(&c__1, (char *)&atmstruct_1.aqdt[i__ - 1], (ftnlen)sizeof(
		    doublereal));
	    do_fio(&c__1, (char *)&c_b89, (ftnlen)sizeof(real));
	    do_fio(&c__1, (char *)&c_b89, (ftnlen)sizeof(real));
	    do_fio(&c__1, (char *)&c_b89, (ftnlen)sizeof(real));
	    do_fio(&c__1, (char *)&c_b89, (ftnlen)sizeof(real));
	    do_fio(&c__1, (char *)&c_b89, (ftnlen)sizeof(real));
	    do_fio(&c__1, (char *)&c_b89, (ftnlen)sizeof(real));
	    do_fio(&c__1, (char *)&c_b89, (ftnlen)sizeof(real));
	    do_fio(&c__1, (char *)&c_b89, (ftnlen)sizeof(real));
	    do_fio(&c__1, (char *)&c_b89, (ftnlen)sizeof(real));
	    do_fio(&c__1, (char *)&c_b89, (ftnlen)sizeof(real));
	    do_fio(&c__1, (char *)&c_b89, (ftnlen)sizeof(real));
	    e_wsfe();
/*            WRITE(ISTOR,62,ADVANCE='no') MODEL,NUMATM-I+M+NUMENV,HSTOT,RAD,B, */
/*     *      ATMOP(I),ATMOT(I),ATMOD(I),OMEGA(M), */
/*     *      .FALSE.,.FALSE.,.FALSE.,.TRUE.,(HCOMP(J,M),J=1,15) */
/* C write out additional physics */
/*            WRITE(ISTOR,63,ADVANCE='no') ATMOO(I),SG,ADELS(1,I), */
/*     *           ADELS(2,I),ADELS(3,I),0.0,AGAM1(I), */
/*     *           AFXIONS(1,I),AFXIONS(2,I), */
/*     *           AFXIONS(3,I),ABETAS(I),0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0, */
/*     *           ATMOCP(I),AQDT(I) */
/* C  zero placeholders for rotation output */
/*            WRITE(ISTOR,64) 0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0 */
	}
    }
/* **************************    Output format codes   ****************************** */
/* 62   FORMAT(I6,1X,I6,0P2F18.14,1PE24.16,0P3F18.14,1PE24.16,1X,L1,1X,L1,1X,L1,1X,L1, */
/*     &     3(0PF12.9),12(0PE16.8),2X) */
/* 63   FORMAT(1PE10.4,1PE11.3,E12.4,E12.4,E12.4,1PE12.4,0PF9.5,F9.5,F9.5,F9.5, */
/* CC     &     F9.5,F9.5,F9.5,F9.5,F9.5,F9.5,F9.5,E13.5,E13.5,E13.5) */
/* C     &     F9.5,F9.5,E12.4,E12.4,E12.4,E12.4,E12.4,E13.5,E13.5,E13.5,E13.5) */
/*     &  F9.5,F9.5,E12.4,E12.4,E12.4,E12.4,E12.4,E13.5,E13.5,E13.5,E13.5,E13.5,E13.5,E13.5, */
/*     &  E13.5) */
/* 64   FORMAT(E14.6,E14.6,E14.6,E14.6,E14.6,E14.6,E14.6,E11.3,E11.3,E11.3,E11.3) */
    return 0;
} /* stitch_ */

