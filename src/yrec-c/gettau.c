/* gettau.f -- translated by f2c (version 20061008).
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

struct {
    doublereal spotf, spotx;
    logical lsdepth;
} spots_;

#define spots_1 spots_

/* Table of constant values */

static doublereal c_b4 = 4.;

/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */
/*                               GETTAU                              C */
/*                           G Somers, 3/17                         C */
/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */
/*       SUBROUTINE GETTAU(HCOMP,HR,HP,HD,HG,HS1,HT,FP,FT,TEFFL,HSTOT,BL,M,  ! KC 2025-05-31 */
/* Subroutine */ int gettau_(doublereal *hcomp, doublereal *hr, doublereal *
	hp, doublereal *hd, doublereal *hs1, doublereal *ht, doublereal *fp, 
	doublereal *ft, doublereal *teffl, doublereal *hstot, doublereal *bl, 
	integer *m, logical *lc, doublereal *rbcz)
{
    /* System generated locals */
    integer i__1;
    doublereal d__1;

    /* Builtin functions */
    double exp(doublereal), pow_dd(doublereal *, doublereal *), d_lg10(
	    doublereal *);

    /* Local variables */
    static doublereal b;
    static integer i__, j;
    static doublereal x, z__;
    extern /* Subroutine */ int tauintnew_(doublereal *, logical *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, integer *,
	     integer *, doublereal *, doublereal *, doublereal *, doublereal *
	    );
    static doublereal gl;
    static integer mm;
    static doublereal rl, hdf[5000], hgf[5000];
    static logical lcf[5000];
    static doublereal hpf[5000], hrf[5000], hsf[5000], htf[5000], fpl, hvf[
	    5000], ftl;
    static integer ixx;
    static doublereal dum1[4], dum2[3], dum3[3], dum4[3];
    static integer katm, imax, idum, kenv;
    static doublereal plim;
    static logical lprt;
    static doublereal delf1[5000], delf2[5000];
    static logical lsbc0;
    static integer ksaha;
    static doublereal ateffl, hcompf[75000]	/* was [15][5000] */;
    static logical lallcz;
    static doublereal chkprs;
    extern /* Subroutine */ int envint_(doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, integer *, logical *, 
	    logical *, doublereal *, doublereal *, doublereal *, doublereal *,
	     doublereal *, doublereal *, integer *, integer *, integer *, 
	    integer *, doublereal *, doublereal *, doublereal *, logical *), 
	    tauint_(doublereal *, logical *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, integer *, doublereal *, doublereal *,
	     doublereal *);
    static logical lpulpt;

/* KC 2025-05-30 reordered common block elements */
/* JvS 08/25 Updated with new elements */
/*       DIMENSION HCOMP(15,JSON),HR(JSON),HP(JSON),HD(JSON),HG(JSON),HS1(JSON),  ! KC 2025-05-31 */

/* This routine devises a new, systematic method for determining the */
/* convective overturn timescale. It will calculate the overturn timescale */
/* one pressure scale height above the BCZ for whichever of the following three */
/* conditions holds. */

/* 1) 1 PSCA above the BCZ is in the interior model. */
/* 2) 1 PSCA above the BCZ is in the envelope model. */
/* 3) The BCZ is in the interior, but 1 PSCA above is in the envelope. */

/* If none of these are satisfied, TAUCZ is set to 0.0. */

/* If 1): Call ENVINT to determine PPHOT, TAUINT(NEW) to determine TAUCZ */
/* If 2): Call ENVINT to determine PPHOT, which calls TAUCAL for TAUCZ. */
/* If 3): Stitch together interior and envelope. */
    /* Parameter adjustments */
    --lc;
    --ft;
    --fp;
    --ht;
    --hs1;
    --hd;
    --hp;
    --hr;
    hcomp -= 16;

    /* Function Body */
    ovrtrn_1.taucz = 0.f;
    ovrtrn_1.pphot = 0.f;
/* Check if 1 PSCA above BCZ is within envelope. If so, only the interior */
/* model should be considered for TAUCZ. Set LCALCENV = .FALSE.. If not, */
/* have ENVINT calculate the full structure, and stitch the envelope */
/* and interior together. */

/* Determine where the BCZ is. */
    for (i__ = *m - 1; i__ >= 1; --i__) {
	if (! lc[i__]) {
	    goto L81;
	}
/* L71: */
    }
    lallcz = TRUE_;
    i__ = 0;
L81:
    imax = i__ + 1;
/* Compare the pressure there to the surface pressure. */
    chkprs = hp[imax] - hp[*m];
/* IF CHKPRS > 1.0, AT LEAST 3 PSCAS, SO LOOK INTERIOR. */
/* IF CHKPRS < 1.0, 1 PSCA UP MIGHT BE IN ENV. STITCH TOGETHER. */
/* FINALLY, IF LNEWTCZ = .FALSE., MAKE SURE TO CALC AN ENV. */
    if (chkprs < 1.f || ! ovrtrn_1.lnewtcz) {
	ovrtrn_1.lcalcenv = TRUE_;
    } else {
	ovrtrn_1.lcalcenv = FALSE_;
    }

/* CALL ENVINT */

    fpl = fp[*m];
    ftl = ft[*m];
    idum = 0;
    b = exp(const1_1.cln * *bl);
    katm = 0;
    kenv = 0;
    ksaha = 0;
    ixx = 0;
    lprt = TRUE_;
    lsbc0 = FALSE_;
    lpulpt = FALSE_;
    x = hcomp[*m * 15 + 1];
    z__ = hcomp[*m * 15 + 3];
    rl = (*bl + const_1.clsunl - *teffl * 4. - const1_1.c4pil - 
	    const2_1.csigl) * .5;
    gl = const2_1.cgl + *hstot - rl - rl;
    plim = hp[*m];
/* G Somers 10/14, FOR SPOTTED RUNS, FIND THE */
/* PRESSURE AT THE AMBIENT TEMPERATURE ATEFFL */
    if (lc[*m] && spots_1.spotf != 0.f && spots_1.spotx != 1.f) {
	d__1 = spots_1.spotf * pow_dd(&spots_1.spotx, &c_b4) + 1.f - 
		spots_1.spotf;
	ateffl = *teffl - d_lg10(&d__1) * .25f;
    } else {
	ateffl = *teffl;
    }
    envint_(&b, &fpl, &ftl, &gl, hstot, &ixx, &lprt, &lsbc0, &plim, &rl, &
	    ateffl, &x, &z__, dum1, &idum, &katm, &kenv, &ksaha, dum2, dum3, 
	    dum4, &lpulpt);
/* PPHOT is now set, and structure variables are caluclated if */
/* LCALCENV = .TRUE.. */

/* IF LNEWTCZ IS FALSE, THEN TAUCZ WILL HAVE BEEN SET IN ENVINT, IF THE */
/* TOP OF THE INTERIOR MODEL IS RADIATIVE. CHECK IF TAUCZ = 0.0. IF NOT, */
/* THEN GO TO THE END. */

    if (ovrtrn_1.taucz != 0.f) {
	goto L100;
    }

/* COLLECT THE NECESSARY STRUCTURE VARIABLES INTO DUMMY VECTORS. */
    mm = *m;
    i__1 = mm;
    for (i__ = 1; i__ <= i__1; ++i__) {
	for (j = 1; j <= 15; ++j) {
	    hcompf[j + i__ * 15 - 16] = hcomp[j + i__ * 15];
	}
	hrf[i__ - 1] = hr[i__];
	hpf[i__ - 1] = hp[i__];
	hdf[i__ - 1] = hd[i__];
	hsf[i__ - 1] = hs1[i__];
	hgf[i__ - 1] = hs1[i__] * exp(const1_1.cln * (const2_1.cgl - hr[i__] *
		 2.));
	htf[i__ - 1] = ht[i__];
	hvf[i__ - 1] = scrtch_1.svel[i__ - 1];
	delf1[i__ - 1] = scrtch_1.sdel[i__ * 3 - 3];
	delf2[i__ - 1] = scrtch_1.sdel[i__ * 3 - 1];
	lcf[i__ - 1] = lc[i__];
    }

    if (ovrtrn_1.lcalcenv && ovrtrn_1.lnewtcz) {
/* IF CHKPRS < 1, THEN STITCH THE ENVELOPE ONTO THE INTERIOR. */
/* ENVELOPE WAS JUST INTEGRATED IN ENVINT ABOVE, SO USE THAT RUN. */
/* THIS CODE BORROWED FROM STITCH.F. */
	mm = *m + envstruct_1.numenv - 1;
	i__1 = mm;
	for (i__ = *m + 1; i__ <= i__1; ++i__) {
	    for (j = 1; j <= 15; ++j) {
		hcompf[j + i__ * 15 - 16] = hcomp[j + (*m + 1) * 15];
	    }
	    hrf[i__ - 1] = envstruct_1.envr[i__ - *m];
	    hpf[i__ - 1] = envstruct_1.envp[i__ - *m];
	    hdf[i__ - 1] = envstruct_1.envd[i__ - *m];
	    hsf[i__ - 1] = exp(const1_1.cln * (*hstot + envstruct_1.envs[i__ 
		    - *m]));
	    hgf[i__ - 1] = hsf[i__ - 1] * exp(const1_1.cln * (const2_1.cgl - 
		    hrf[i__ - 1] * 2.));
	    htf[i__ - 1] = envstruct_1.envt[i__ - *m];
	    hvf[i__ - 1] = envstruct_1.evels[i__ - *m];
	    delf1[i__ - 1] = envstruct_1.edels[(i__ - *m + 1) * 3 - 3];
	    delf2[i__ - 1] = envstruct_1.edels[(i__ - *m + 1) * 3 - 2];
	    lcf[i__ - 1] = envstruct_1.lcenv[i__ - *m];
	}
    }
/* CALL TAUINT */
    if (ovrtrn_1.lnewtcz) {
/*          CALL TAUINTNEW(HCOMPF,HS2,HSF,LCF,HRF,HPF,HDF,HGF,MM,M,HVF, */
/*      *                  DELF1,DELF2,HSTOT,RBCZ)  ! KC 2025-05-31 */
	tauintnew_(hsf, lcf, hrf, hpf, hdf, hgf, &mm, m, hvf, delf1, delf2, 
		rbcz);
    } else {
/*          CALL TAUINT(HCOMPF,HS2,HSF,LCF,HRF,HPF,HDF,HGF,MM,HVF, */
/*      *               DELF1,DELF2,HSTOT)  ! KC 2025-05-31 */
	tauint_(hsf, lcf, hrf, hpf, hdf, hgf, &mm, hvf, delf1, delf2);
    }
/* RETURN FULL FUNCTIONALITY TO ENVINT */
L100:
    ovrtrn_1.lcalcenv = TRUE_;
    return 0;
} /* gettau_ */

