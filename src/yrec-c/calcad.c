/* calcad.f -- translated by f2c (version 20061008).
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
    doublereal sesum[5000], seg[35000]	/* was [7][5000] */, sbeta[5000], 
	    seta[5000];
    logical locons[5000];
    doublereal so[5000], sdel[15000]	/* was [3][5000] */, sfxion[15000]	
	    /* was [3][5000] */, svel[5000], scp[5000];
} scrtch_;

#define scrtch_1 scrtch_

struct {
    doublereal xenv, zenv, zenvm, amuenv, fxenv[12], xnew, znew, stotal, senv;
} comp_;

#define comp_1 comp_

struct {
    doublereal gam1[5000];
    logical lsound;
} sound_;

#define sound_1 sound_

struct {
    doublereal esact, eos[10];
} eeos06_;

#define eeos06_1 eeos06_

struct {
    doublereal ztab;
} llot95_;

#define llot95_1 llot95_

struct {
    doublereal atmstp, envstp;
    logical lenvg;
} envgen_;

#define envgen_1 envgen_

struct {
    integer ilast, idebug, itrack, ishort, imilne, imodpt, istor, iowr;
} luout_;

#define luout_1 luout_

struct {
    doublereal endage[50], setdt[50];
    logical lendag[50], lsetdt[50];
    doublereal end_dcen__[50], end_xcen__[50], end_ycen__[50];
} sett_;

#define sett_1 sett_

struct {
    doublereal hras;
    integer kttau, kttau0;
    logical lttau;
} atmos_;

#define atmos_1 atmos_

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
    logical lopale;
    integer iopale;
    logical lopale01, lopale06, lnumderiv;
} opaleos_;

#define opaleos_1 opaleos_

struct {
    doublereal dmdt0, fczdmdt, ftotdmdt, compacc[15], creim;
    logical lreimer, lmdot;
} masschg_;

#define masschg_1 masschg_

struct {
    doublereal spotf, spotx;
    logical lsdepth;
} spots_;

#define spots_1 spots_

/* Table of constant values */

static doublereal c_b2 = 4.;
static integer c__7 = 7;
static integer c__1 = 1;
static doublereal c_b44 = 0.;


/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */
/* CALCAD: links together and integrates sound speed profiles, for acoustic */
/* depth to convection zone, acoustic depth of atmosphere */
/* INPUTS: */
/*      HR: array of radii for the interiors solution */
/*      RCZ: physical radius of the convection zone (logged), calculated in wrtout */
/*      M: last interior point */
/*      HD: interior's density */
/*      HP: interior pressure */
/*      HT: interior temperature */
/*      BL: logged luminosity */
/*      FP: Rotational distortion, needed for envelope integration */
/*      FT: Rotational distortion, needed for envelope integration */
/*      HSTOT: needed for ENVINT */
/*      LPRT: needed for ENVINT */
/*      TEFFL: logged effective temperature */
/*      HCOMP: vector of compositions for interior */
/*      NKK: obsolete? */
/*       DAGE: Age */
/*       DDAGE: obsolete? */




/* OUTPUTS: */
/*       Adjusts the values in the common block for acoustic depth: */
/*            TAUCZN = acoustic depth to CZ / sound travel time from surface-center */
/*            TCZ = acoustic depth to CZ (seconds) */
/*            TNORM = sound travel time from surface to center (seconds) */
/*            DELADJ = adiabatic gradient from OPAL 2006 EOS or SCV EOS */





/* COMMON BLOCKED THINGS: */

/*        LCLCD = Logical flag for output of CALCAD files at AGEOUT ages */
/*        AGEOUT(5) = Ages for which you want output. Hard coded in parmin */
/*        IACAT = */
/*        IJLAST = Again, for output */
/*        LJLAST = Again, for output */
/*        LJWRT = ouput on/off toggle */
/*        LADON = toggle on calcad imposed 4d interpolation in opacity */

/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */
/* Subroutine */ int calcad_(doublereal *hr, doublereal *rczl, integer *m, 
	doublereal *hd, doublereal *hp, doublereal *ht, doublereal *bl, 
	doublereal *fp, doublereal *ft, doublereal *hstot, doublereal *teffl, 
	doublereal *hcomp, doublereal *dage, integer *jenv)
{
    /* Format strings */
    static char fmt_67[] = "(1x,\002Acoustic depth to CZ:\002,f14.8,2x,\002A"
	    "coustic depth to center\002,f13.7,2x,\002Normalized taucz:\002,f"
	    "11.9,\002Acoustic depth of atmopshere:\002,f16.8,2x)";
    static char fmt_1506[] = "(1x,\002Number of points in envelope:\002,i5,2"
	    "x,\002Number of points in interior:\002,i5,2x,\002Index near Rcz:"
	    "\002,i5,2x)";
    static char fmt_1504[] = "(1x,11e16.8)";

    /* System generated locals */
    integer i__1;
    doublereal d__1;

    /* Builtin functions */
    double exp(doublereal), pow_dd(doublereal *, doublereal *), d_lg10(
	    doublereal *), sqrt(doublereal);
    integer s_wsfe(cilist *), do_fio(integer *, char *, ftnlen), e_wsfe(void);

    /* Local variables */
    static doublereal d__[7];
    static integer i__, k, p, u, v;
    static doublereal bj[1];
    static integer nn;
    static doublereal xj, zj, gm1[5000];
    static integer flg;
    static doublereal glj, ans[1], cht, cvj;
    static integer icz;
    static doublereal rlj, std;
    static integer klo, khi;
    static doublereal rcz[1], stp, stt, stx, stz, dum1[4], dum2[3], dum3[3], 
	    dum4[3];
    static integer irad;
    static doublereal etaj, chrh, fplj[1], ftlj[1], amuj, stdl, abeg0, ebeg0;
    static integer ixxj;
    static doublereal sttl, stpl, rmuj, emuj, qdtj, amin0, amax0, qdpj, emin0,
	     hood1[7], hood2[7], emax0, qcpj, qatj, qapj, delaj;
    extern /* Subroutine */ int esac06_(doublereal *, doublereal *, 
	    doublereal *, integer *, integer *);
    static doublereal betaj;
    static integer iendj;
    static doublereal bet14j;
    static integer katmj, idumj;
    static doublereal plimj, starc[5000], stard[5000];
    static integer kenvj;
    static doublereal starp[5000], starr[5000];
    static logical lprtj;
    static doublereal start[5000], starx[5000], starz[5000], qdttj, qdtpj;
    static logical lsbc0j;
    static doublereal qcptj, qcppj;
    extern /* Subroutine */ int boole_(doublereal *, doublereal *, integer *, 
	    integer *, doublereal *);
    static logical lcalcj;
    static doublereal betaij;
    static integer ksahaj;
    static doublereal ateffl;
    static logical lderij;
    static doublereal starcz[5000], atmosx;
    extern /* Subroutine */ int envint_(doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, integer *, logical *, 
	    logical *, doublereal *, doublereal *, doublereal *, doublereal *,
	     doublereal *, doublereal *, integer *, integer *, integer *, 
	    integer *, doublereal *, doublereal *, doublereal *, logical *);
    static integer iorder;
    static logical latmoj;
    static doublereal fxionj, starrz[5000];
    extern /* Subroutine */ int splinj_(doublereal *, doublereal *, 
	    doublereal *, integer *), splint_(doublereal *, doublereal *, 
	    integer *, doublereal *, doublereal *, doublereal *, integer *, 
	    integer *), eqstat2_(doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, logical *, logical *, 
	    integer *);
    static logical lpulptj;

    /* Fortran I/O blocks */
    static cilist io___89 = { 0, 0, 0, fmt_67, 0 };
    static cilist io___90 = { 0, 0, 0, fmt_1506, 0 };
    static cilist io___91 = { 0, 0, 0, fmt_1504, 0 };
    static cilist io___92 = { 0, 0, 0, fmt_1504, 0 };


/*      *                  LPRT, TEFFL, HCOMP, NKK, DAGE, DDAGE, JENV)  ! KC 2025-05-31 */
/*      REAL*8 ATMOSX, ATMOST(JSON),ATMOSD(JSON),ATMOSP(JSON),ADELAD(JSON),ATMOSC(JSON), */
/*     *       ATGAM1(JSON), ATMOSR(JSON),GM1(JSON) */
/* KC 2025-05-30 addressed warning messages from Makefile.legacy */
/*       INTEGER I, K, N, U, ICZ, NN, IENDJ, FLG, V, IATCNT, KTSAV */
/* IATCNT, KTSAV */
/* HL(JSON) */
/* KC 2025-05-30 reordered common block elements */
/*       COMMON/ACDPTH/TAUCZN,DELADJ(JSON),TAUHE, TNORM, TCZ, WHE, ICLCD, */
/* LTEST */
/*      *LCLCD, AGEOUT(5), IACAT, IJLAST, LJLAST, LJWRT, LADON, LAOLY, IJVS, */
/* MHP 10/24 ADDED STOP CRITERIA FOR CENTRAL H,D,AND HE4 */
/*      COMMON/SETT/ENDAGE(50),SETDT(50),LENDAG(50),LSETDT(50) */
/* KC 2025-05-30 reordered common block elements */
/*       COMMON/OPALEOS/FOPALE,LOPALE,IOPALE,fopale01,lopale01,fopale06, */
/*      *     lopale06,lNumDeriv */
/* MHP 8/25 Remove file names from common blocks */
/* Added for experimantal mass loss section */
/* G Somers 10/14, Add spot common block */
/* G Somers END */
/* Initialize values: */
    /* Parameter adjustments */
    hcomp -= 16;
    --ft;
    --fp;
    --ht;
    --hp;
    --hd;
    --rczl;
    --hr;

    /* Function Body */
    acdpth_1.tauczn = 0.;
    acdpth_1.tcz = 0.;
    acdpth_1.tnorm = 0.;
    acdpth_1.whe = 0.;
    acdpth_1.tauhe = 0.;
    atmosx = 0.;
    acdpth_1.tatmos = 0.;
/*      KTSAV = 3 */
/* Need to calculate the sound speed in the envelope: first, stitch */
/* envelope and interior together (so that T, P, R all agree at fitting */
/* point. Then calculate sound speed in the envelope and interior */
/* and integrate. */
/* First, do the envelope integration to make sure the values in ENVSTRUCT */
/* are up-to-date (this section of code grabbed from wrtmod). First, integrate the atm and store values with g
rey atm */
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
    idumj = 0;
    bj[0] = exp(const1_1.cln * *bl);
    fplj[0] = fp[*m];
    ftlj[0] = ft[*m];
    katmj = 0;
    kenvj = 0;
    ksahaj = 0;
    lpulptj = TRUE_;
    ixxj = 0;
    lprtj = TRUE_;
    lsbc0j = FALSE_;
    xj = hcomp[*m * 15 + 1];
    zj = hcomp[*m * 15 + 3];
    rlj = (*bl + const_1.clsunl - *teffl * 4. - const1_1.c4pil - 
	    const2_1.csigl) * .5;
    glj = const2_1.cgl + comp_1.stotal - rlj - rlj;
    plimj = hp[*m];
/*      IF (KTTAU .EQ. 0) LAOLY = .TRUE. */
/*      IF (KTTAU .EQ. 3) LAOLY = .FALSE.      ! for grey atm intergration: stores values in common block */
/*      G Somers 10/14, FOR SPOTTED RUNS, FIND THE PRESSURE AT */
/*      THE AMBIENT TEMPERATURE ATEFFL */
    if (*jenv == *m && spots_1.spotf != 0.f && spots_1.spotx != 1.f) {
	d__1 = spots_1.spotf * pow_dd(&spots_1.spotx, &c_b2) + 1.f - 
		spots_1.spotf;
	ateffl = *teffl - d_lg10(&d__1) * .25f;
    } else {
	ateffl = *teffl;
    }
    envint_(bj, fplj, ftlj, &glj, hstot, &ixxj, &lprtj, &lsbc0j, &plimj, &rlj,
	     &ateffl, &xj, &zj, dum1, &idumj, &katmj, &kenvj, &ksahaj, dum2, 
	    dum3, dum4, &lpulptj);
/*      G Somers END */
/* Stitch interior and envelope together, convert into ESAC06 units */
    i__1 = *m;
    for (i__ = 1; i__ <= i__1; ++i__) {
	starr[i__ - 1] = exp(const1_1.cln * hr[i__]);
/* get unlogged units */
	start[i__ - 1] = exp(const1_1.cln * ht[i__]) / 1e6;
/* ESAC06 takes T in units of 10^6K */
	stard[i__ - 1] = exp(const1_1.cln * hd[i__]);
	starp[i__ - 1] = exp(const1_1.cln * hp[i__]);
	starx[i__ - 1] = hcomp[i__ * 15 + 1];
	starz[i__ - 1] = hcomp[*m * 15 + 3];
/* L34: */
    }
    i__1 = envstruct_1.numenv - 1;
    for (i__ = 1; i__ <= i__1; ++i__) {
	starr[*m + i__ - 1] = exp(const1_1.cln * envstruct_1.envr[i__]);
	start[*m + i__ - 1] = exp(const1_1.cln * envstruct_1.envt[i__]) / 1e6;
	stard[*m + i__ - 1] = exp(const1_1.cln * envstruct_1.envd[i__]);
	starp[*m + i__ - 1] = exp(const1_1.cln * envstruct_1.envp[i__]);
	starx[*m + i__ - 1] = hcomp[*m * 15 + 1];
	starz[*m + i__ - 1] = hcomp[*m * 15 + 3];
/* L35: */
    }
/* Call EOS interpolator: Takes OPAL2006 EOS if possible. If OPAL06 is off, uses SCV */
/* For OPAL 2006 EOS: */
    if (opaleos_1.lopale06) {
	iorder = 9;
	irad = 1;
	i__1 = *m + envstruct_1.numenv - 1;
	for (i__ = 1; i__ <= i__1; ++i__) {
	    stx = starx[i__ - 1];
	    stt = start[i__ - 1];
	    std = stard[i__ - 1];
/*                   CALL ESAC06(STX,ZTAB,STT,STD,IORDER,IRAD,*999)  ! KC 2025-05-31 */
	    switch (esac06_(&stx, &stt, &std, &iorder, &irad)) {
		case 1:  goto L999;
	    }
L999:
	    starc[i__ - 1] = 1. / sqrt(eeos06_1.eos[7] * starp[i__ - 1] / 
		    stard[i__ - 1]);
	    acdpth_1.deladj[i__ - 1] = 1. / eeos06_1.eos[8];
	    gm1[i__ - 1] = eeos06_1.eos[7];
/* L36: */
	}
    }
/* For SCV EOS: (when OPAL06 is turned off, SCV on for backup, Yale if SCV is off) */
    if (! opaleos_1.lopale06) {
	i__1 = *m + envstruct_1.numenv - 1;
	for (i__ = 1; i__ <= i__1; ++i__) {
	    stx = starx[i__ - 1];
	    stt = start[i__ - 1] * 1e6;
	    std = stard[i__ - 1];
	    stdl = d_lg10(&stard[i__ - 1]);
	    stz = starz[i__ - 1];
	    sttl = d_lg10(&stt);
	    stp = starp[i__ - 1];
	    stpl = d_lg10(&stp);
	    lcalcj = TRUE_;
/*                  CALL EQSCVE(STTL,STT,STPL,STP,STDL,STD,STX,STZ,BETAJ,BETAIJ,BET14J,FXIONJ,RMUJ, */
/*     *                       AMUJ,EMUJ,ETAJ,QDTJ,QDPJ,QCPJ,DELAJ,LCALCJ) */
	    lderij = FALSE_;
	    latmoj = TRUE_;
	    eqstat2_(&sttl, &stt, &stpl, &stp, &stdl, &std, &stx, &stz, &
		    betaj, &betaij, &bet14j, &fxionj, &rmuj, &amuj, &emuj, &
		    etaj, &qdtj, &qdpj, &qcpj, &delaj, &qdttj, &qdtpj, &qatj, 
		    &qapj, &qcptj, &qcppj, &lderij, &latmoj, &ksahaj);
/*                  calculate gamma1 (taken from envint example, eqns in chap. 9 of Cox& Giuli): */
	    chrh = 1. / qdpj;
	    cht = -chrh * qdtj;
/* Computing 2nd power */
	    d__1 = cht;
	    cvj = qcpj - exp(const1_1.cln * (stpl - stdl - sttl)) * (d__1 * 
		    d__1) / chrh;
	    gm1[i__ - 1] = chrh * qcpj / cvj;
	    starc[i__ - 1] = 1. / sqrt(gm1[i__ - 1] * starp[i__ - 1] / stard[
		    i__ - 1]);
	    acdpth_1.deladj[i__ - 1] = delaj;
/* L41: */
	}
    }
/* Integrate for the full acoustic depth for normalization */
    k = envstruct_1.numenv - 1 + *m - 1;
    u = (envstruct_1.numenv - 1 + *m - 1) % 4;
    if (u != 0) {
	nn = k + 4 - u + 1;
    } else {
	nn = k + 1;
    }
    if (k <= 3) {
	k = 4;
	nn = 2;
    }
    boole_(starr, starc, &k, &nn, &acdpth_1.tnorm);
/* Find the location of the CZ, but only if one exists */
    if (*jenv < *m) {
	rcz[0] = exp(const1_1.cln * (rczl[1] + const_1.crsunl));
/*      get the location of the convection zone, and count nonzero entries: */
	iendj = 0;
	flg = 0;
	i__1 = k;
	for (i__ = 1; i__ <= i__1; ++i__) {
	    if (starr[i__ - 1] <= rcz[0] && starr[i__] >= rcz[0]) {
		icz = i__;
	    }
/*                  Interpolate to find Cs at the exact CZ radius */
	    if (i__ == icz && flg == 0 && icz > 3) {
		flg = 1;
		for (p = 1; p <= 7; ++p) {
		    hood1[p - 1] = starr[icz - 4 + p - 1];
		    hood2[p - 1] = starc[icz - 4 + p - 1];
/* L26: */
		}
		splinj_(hood1, hood2, d__, &c__7);
		splint_(hood1, hood2, &c__7, d__, rcz, ans, &klo, &khi);
		starr[icz - 1] = rcz[0];
		starc[icz - 1] = ans[0];
	    }
	    if (i__ == icz && flg == 0 && icz <= 3) {
		flg = 1;
		if (icz == 1) {
		    rcz[0] = starr[icz - 1];
		    ans[0] = starc[icz - 1];
		} else {
		    for (p = 1; p <= 7; ++p) {
			hood1[p - 1] = starr[icz - 2 + p - 1];
			hood2[p - 1] = starc[icz - 2 + p - 1];
/* L66: */
		    }
		    splinj_(hood1, hood2, d__, &c__7);
		    splint_(hood1, hood2, &c__7, d__, rcz, ans, &klo, &khi);
		    starr[icz - 1] = rcz[0];
		    starc[icz - 1] = ans[0];
		}
	    }
/* L22: */
	}
	i__1 = k - icz + 1;
	for (i__ = 1; i__ <= i__1; ++i__) {
	    starrz[i__ - 1] = starr[icz - 1 + i__ - 1];
	    starcz[i__ - 1] = starc[icz - 1 + i__ - 1];
/* L27: */
	}
/* Then call Boole from surface to cz: */
	u = (k - icz + 1) % 4;
	v = k - icz + 1;
	if (u != 0) {
	    nn = k - icz + 5 - u + 1;
	} else {
	    nn = k - icz + 2;
	}
	boole_(starrz, starcz, &v, &nn, &acdpth_1.tcz);
    } else {
	acdpth_1.tcz = 0.;
    }
/* Deal with the atmosphere seperately */
/*      Invert vectors and shift units */
/*      Adopt the atmosphere metallicity to be the same as the last envelope pt. */
/*      ATMOSX=STARX(M+NUMENV-1) */
/* Determine length of Atmosphere vector: */
/*      IATCNT=0 */
/*      DO 56, I=1,JSON-1 */
/*            IF(ACATMR(I) .NE. 0.0 .AND. ACATMR(I+1) .LE. 1.0D-7) THEN */
/*                   IATCNT=I */
/*                  GOTO 56 */
/*            END IF */
/* 56      CONTINUE */
/* Put the atmosphere in actual units, not differential */
/*      DO 39, I=1,IATCNT-1 */
/*            ACATMR(IATCNT-I)=ACATMR(IATCNT-I+1)+ACATMR(IATCNT-I) */
/* 39      CONTINUE */
/*      DO 40, I=1,IATCNT */
/*            ACATMR(I)=ACATMR(I)+STARR(M+NUMENV-1) */
/* 40      CONTINUE */
/*      DO 37,I=1,IATCNT */
/*            ATMOSD(I)=DEXP(CLN*ACATMD(IATCNT+1-I)) */
/*            ATMOST(I)=DEXP(CLN*ACATMT(IATCNT+1-I))/1.0D6 */
/*            ATMOSP(I)=DEXP(CLN*ACATMP(IATCNT+1-I)) */
/*            ATMOSR(I)=ACATMR(IATCNT+1-I) */
/* 37      CONTINUE */
/*      Pass atm vectors to ESAC06 */
/*      IORDER=9 */
/*      IRAD=1 */
/*      DO 38, I=1,IATCNT */
/*            CALL ESAC06(ATMOSX,ZTAB,ATMOST(I),ATMOSD(I),IORDER,IRAD,*998) */
/* 998            CONTINUE */
/*            ATMOSC(I)=1.0D0/SQRT(eos(8)*ATMOSP(I)/ATMOSD(I)) */
/*            ADELAD(I)=1.0D0/eos(9) */
/*            ATGAM1(I)= eos(8) */
/* 38      CONTINUE */
/*       Then call Boole to do the integration: */
/*      U=MOD((IATCNT),4) */
/*      V=IATCNT */
/*      IF (U.NE.0) THEN */
/*            NN=V+4-U+1 */
/*      ELSE */
/*            NN=V+1 */
/*      ENDIF */

/*      CALL BOOLE(ATMOSR,ATMOSC,V,NN,TATMOS) */
/* Output normalized acoustic depth */
    acdpth_1.tauczn = 0.;
    acdpth_1.tauczn = acdpth_1.tcz / acdpth_1.tnorm;
/* Output acoustic depth info to ISHORT */
    io___89.ciunit = luout_1.ishort;
    s_wsfe(&io___89);
    do_fio(&c__1, (char *)&acdpth_1.tcz, (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&acdpth_1.tnorm, (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&acdpth_1.tauczn, (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&acdpth_1.tatmos, (ftnlen)sizeof(doublereal));
    e_wsfe();
/* 555            CONTINUE */
/* -------------------------------------------------------------- */
/* Save all vectors of interest when the end of a kind card is reached. */
    if (acdpth_1.lclcd) {
	io___90.ciunit = acdpth_1.iclcd;
	s_wsfe(&io___90);
	do_fio(&c__1, (char *)&envstruct_1.numenv, (ftnlen)sizeof(integer));
	do_fio(&c__1, (char *)&(*m), (ftnlen)sizeof(integer));
	do_fio(&c__1, (char *)&icz, (ftnlen)sizeof(integer));
	e_wsfe();
	i__1 = *m + envstruct_1.numenv - 1;
	for (i__ = 1; i__ <= i__1; ++i__) {
	    if (i__ <= k - icz + 1) {
/* KC 2025-05-30 addressed warning messages from Makefile.legacy */
/*                         WRITE(UNIT=ICLCD,FMT=1504),DAGE, STARR(I), STARC(I), */
		io___91.ciunit = acdpth_1.iclcd;
		s_wsfe(&io___91);
		do_fio(&c__1, (char *)&(*dage), (ftnlen)sizeof(doublereal));
		do_fio(&c__1, (char *)&starr[i__ - 1], (ftnlen)sizeof(
			doublereal));
		do_fio(&c__1, (char *)&starc[i__ - 1], (ftnlen)sizeof(
			doublereal));
		do_fio(&c__1, (char *)&starrz[i__ - 1], (ftnlen)sizeof(
			doublereal));
		do_fio(&c__1, (char *)&starcz[i__ - 1], (ftnlen)sizeof(
			doublereal));
		do_fio(&c__1, (char *)&acdpth_1.deladj[i__ - 1], (ftnlen)
			sizeof(doublereal));
		do_fio(&c__1, (char *)&gm1[i__ - 1], (ftnlen)sizeof(
			doublereal));
		do_fio(&c__1, (char *)&starp[i__ - 1], (ftnlen)sizeof(
			doublereal));
		do_fio(&c__1, (char *)&start[i__ - 1], (ftnlen)sizeof(
			doublereal));
		do_fio(&c__1, (char *)&stard[i__ - 1], (ftnlen)sizeof(
			doublereal));
		do_fio(&c__1, (char *)&starx[i__ - 1], (ftnlen)sizeof(
			doublereal));
		e_wsfe();
	    } else {
/* KC 2025-05-30 addressed warning messages from Makefile.legacy */
/*                         WRITE(UNIT=ICLCD,FMT=1504) DAGE, STARR(I), STARC(I), */
		io___92.ciunit = acdpth_1.iclcd;
		s_wsfe(&io___92);
		do_fio(&c__1, (char *)&(*dage), (ftnlen)sizeof(doublereal));
		do_fio(&c__1, (char *)&starr[i__ - 1], (ftnlen)sizeof(
			doublereal));
		do_fio(&c__1, (char *)&starc[i__ - 1], (ftnlen)sizeof(
			doublereal));
		do_fio(&c__1, (char *)&c_b44, (ftnlen)sizeof(doublereal));
		do_fio(&c__1, (char *)&c_b44, (ftnlen)sizeof(doublereal));
		do_fio(&c__1, (char *)&acdpth_1.deladj[i__ - 1], (ftnlen)
			sizeof(doublereal));
		do_fio(&c__1, (char *)&gm1[i__ - 1], (ftnlen)sizeof(
			doublereal));
		do_fio(&c__1, (char *)&starp[i__ - 1], (ftnlen)sizeof(
			doublereal));
		do_fio(&c__1, (char *)&start[i__ - 1], (ftnlen)sizeof(
			doublereal));
		do_fio(&c__1, (char *)&stard[i__ - 1], (ftnlen)sizeof(
			doublereal));
		do_fio(&c__1, (char *)&starx[i__ - 1], (ftnlen)sizeof(
			doublereal));
		e_wsfe();
	    }
/* L1505: */
	}
/*                  DO 1520 I=1,IATCNT */
/*                        WRITE(UNIT=IACAT,FMT=1521),DAGE, ATMOSR(I), ATMOSC(I), */
/*    *                     DELADJ(I), ATGAM1(I), ATMOSP(I), ATMOST(I), ATMOSX */

/* 1520                  CONTINUE */
/* 1521                  FORMAT(1X,8E16.8) */
    }
/*      DO 444, I=1,JSON */
/*            ACATMR(I) =0.0d0 */
/*            ACATMP(I) =0.0d0 */
/*            ACATMT(I) =0.0d0 */
/*            ACATMD(I) =0.0d0 */
/* 444      CONTINUE */
/* 50      CONTINUE */
    return 0;
} /* calcad_ */

