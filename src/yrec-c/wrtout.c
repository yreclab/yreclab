/* wrtout.f -- translated by f2c (version 20061008).
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
    doublereal tcenter, pcenter, dcenter, envlm, envr;
} cent_;

#define cent_1 cent_

struct {
    integer itrver;
} track_;

#define track_1 track_

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
    logical lexcom;
} flag_;

#define flag_1 flag_

struct {
    logical lkuthe;
} heflsh_;

#define heflsh_1 heflsh_

struct {
    doublereal xenv0, zenv0;
} label_;

#define label_1 label_

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
    logical lmhd;
    integer iomhd1, iomhd2, iomhd3, iomhd4, iomhd5, iomhd6, iomhd7, iomhd8;
} mhd_;

#define mhd_1 mhd_

struct {
    doublereal grtol;
    integer ilambda, niter_gs__;
    logical ldify;
} gravst_;

#define gravst_1 gravst_

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
    logical lrwsh, liso;
    integer iiso;
} chrone_;

#define chrone_1 chrone_

struct {
    doublereal cdh, etadh0, etadh1, zdh[18], xxdh, yydh, zzdh, dhnue[18];
    logical ldh;
} debhu_;

#define debhu_1 debhu_

struct {
    logical lprt0;
} rotprt_;

#define rotprt_1 rotprt_

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
    doublereal envrcz, rint;
} envcz_;

#define envcz_1 envcz_

struct {
    doublereal gam1[5000];
    logical lsound;
} sound_;

#define sound_1 sound_

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
    doublereal derot[5000];
} roten_;

#define roten_1 roten_

struct {
    doublereal enghe3, he3all, umhe33[5000], umheal[5000];
} grab_;

#define grab_1 grab_

struct {
    logical lnewtcz, lcalcenv;
    doublereal taucz, taucz0, pphot, pphot0, fracstep;
} ovrtrn_;

#define ovrtrn_1 ovrtrn_

/* Table of constant values */

static integer c__1 = 1;
static doublereal c_b23 = 10.;


/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */
/* WRTOUT */
/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */
/* Subroutine */ int wrtout_(doublereal *hcomp, doublereal *hd, doublereal *
	hl, doublereal *hp, doublereal *hr, doublereal *hs, doublereal *hs1, 
	doublereal *ht, logical *lc, integer *m, integer *model, doublereal *
	dage, doublereal *ddage, doublereal *smass, doublereal *teffl, 
	doublereal *bl, doublereal *gl, logical *lshell, integer *jxbeg, 
	integer *jxmid, integer *jxend, integer *jcore, integer *jenv, 
	doublereal *tlumx, doublereal *trit, doublereal *tril, doublereal *ps,
	 doublereal *ts, doublereal *rs, doublereal *cfenv, doublereal *ftri, 
	doublereal *hstot, doublereal *omega, logical *lpunch, doublereal *fp,
	 doublereal *ft, doublereal *eta2, doublereal *r0, doublereal *hjm, 
	doublereal *hi, doublereal *sjtot, doublereal *skerot, doublereal *
	hs2)
{
    /* Initialized data */

    static doublereal gasnuf[8] = { 11.8,215.,71400.,71.7,2.4e4,60.4,113.7,
	    113.9 };
    static doublereal clsnuf[8] = { 0.,16.,42600.,2.4,11400.,1.7,6.8,6.9 };
    static integer icheck = 0;

    /* Format strings */
    static char fmt_21[] = "(/,1x,127(\002*\002))";
    static char fmt_20[] = "(1x,127(\002*\002))";
    static char fmt_30[] = "(1x,\002MODEL NO.\002,i5,2x,\002MASS\002,f13.7,2"
	    "x,\002(X,Z)=(\002,f11.9,\002,\002,f11.9,\002)\002,2x,\002AGE(GYR"
	    "S)\002,f14.8,\002 STEP(YRS)=\002,f12.0)";
    static char fmt_40[] = "(1x,\002MODEL NO.\002,i5,2x,\002MASS\002,f13.7,2"
	    "x,\002(X,Z)=(\002,f11.9,\002,\002,f11.9,\002)\002,2x,\002AGE(GYR"
	    "S)\002,f14.8,\002 STEP(YRS)=\002,1pe12.4)";
    static char fmt_50[] = "(1x,\002SHELLS=\002,i5,2x,\002(X0,Z0)=(\002,f9"
	    ".7,\002,\002,f9.7,\002)\002,2x,\002CONV. ZONE MASSES(MSUN): COR"
	    "E\002,f10.7,\002 ENV.\002,f10.7,\002 RAD. FRAC.\002,f10.7)";
    static char fmt_60[] = "(1x,\002LOG(TEFF)=\002,f11.8,\002  M(BOL)=\002,f"
	    "11.7,\002  LOG(L/LSUN)=\002,f12.8,\002  LOG(R/RSUN)=\002,f12.8"
	    ",\002  LOG(G) =\002,f12.8)";
    static char fmt_70[] = "(1x,\002CENTER: LOG P=\002,f10.7,\002 LOG T=\002"
	    ",f10.8,\002 LOG D=\002,f10.6,\002 BETA=\002,f9.7,\002 ETA=\002,0"
	    "pf10.5,\002  X=\002,0pf9.7,\002 Z=\002,f9.7,\002 O16=\002,f9.7)";
    static char fmt_80[] = "(1x,\002ENERGY: PPI\002,1pe13.6,\002  PPII\002,e"
	    "13.6,\002  PPIII\002,e13.6,\002  CNO\002,e13.6,/,9x,\002TRIPLE A"
	    "LPHA\002,e13.6,\002  HE-C\002,e13.6,\002  NEUTRINOS\002,e13.6"
	    ",\002  GRAV\002,e13.6)";
    static char fmt_120[] = "(1x,\002H-SHELL MID-PT=\002,f10.7,\002 MASS TOT"
	    "AL=\002,f10.7,2x,\002HE-CORE MASS=\002,f10.7,1x,\002MAX-T=\002,f"
	    "10.7,\002 (MASS=\002,f9.7,\002)\002)";
    static char fmt_150[] = "(1x,\002CONVECTION = \002,l1,5x,\002LOG(R) MAX-"
	    "T =\002,f8.5)";
    static char fmt_160[] = "(1x,\002NEUTRINOS 1E10ERG/CM^2 PP,PEP,HEP,BE7"
	    ",\002,\002B8,N13,O15,F17:\002,1p8e9.2)";
    static char fmt_2160[] = "(1x,\002NEUTRINO ENERGIES (1.E-36ERG): 7Li="
	    "\002,1pe9.2,\002 37Cl=\002,1pe9.2,\002 71Ga=\002,1pe9.2,\002 81B"
	    "r=\002,1pe9.2,\002 98Mo=\002,1pe9.2,\002 115In=\002,1pe9.2)";
    static char fmt_170[] = "(1x,\002FIT-POINT    M/MSUN=\002,f16.12,5x,\002"
	    "(P,T,R) =\002,3f12.7)";
    static char fmt_1499[] = "(1x,2i8,1p7e16.8,1p5e12.4,16e16.8,12e10.3,41e1"
	    "6.8)";
    static char fmt_1500[] = "(1x,2i8,1p7e16.8,0pf8.4,1p4e12.4)";
    static char fmt_1509[] = "(1x,1p9e16.8)";
    static char fmt_1510[] = "(1x,1p8e16.8)";
    static char fmt_1515[] = "(1x,2f8.3,1p10e10.3)";
    static char fmt_1520[] = "(1x,1p8e16.8,/,1x,1p8e16.8)";
    static char fmt_1530[] = "(1x,1p6e16.8)";
    static char fmt_1540[] = "(1x,1p6e13.5,0p,2f11.5,1e13.5)";
    static char fmt_1501[] = "(1x,2i8,1p5e13.5,1p2e11.3,0pf8.4,1pe13.5)";
    static char fmt_1005[] = "(1x,i5,1p7e17.8)";
    static char fmt_1800[] = "(1x,2i8,1p7e16.8,0pf8.4,1p4e12.4,16e16.8,12e10"
	    ".3,39e16.8,i8)";

    /* System generated locals */
    integer i__1;
    doublereal d__1, d__2;

    /* Builtin functions */
    integer s_wsfe(cilist *), e_wsfe(void), do_fio(integer *, char *, ftnlen);
    double exp(doublereal), d_lg10(doublereal *), pow_dd(doublereal *, 
	    doublereal *);

    /* Local variables */
    static doublereal gmhecore, d__;
    extern /* Subroutine */ int putstore_(doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, logical *, doublereal *, doublereal *, doublereal *,
	     doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, integer *, integer *, integer *, integer *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *);
    static integer i__, j, k;
    static doublereal p, t, x, z__, dl, fx, rl, pl, tl, dd1, dd2, fx2, ss1, 
	    ss2, ss3, ss4, eta, hsb, qap, amu, qdp, thl, emu, qdt, qcp, qat, 
	    cmr, rmu, rrr1, rrr2, rrr3, sss1, sss2, sss3, dela, beta, bolm, 
	    envd, hicz, temp, qdtt, qdtp, qcpt, qcpp, envo, envt, envp, rotp, 
	    rotv, fl7li, beta14, fl71ga, betai;
    static integer ksaha;
    static doublereal fl37cl, fxion[3], corem, corer;
    static logical latmo;
    extern /* Subroutine */ int meqos_(doublereal *, doublereal *, doublereal 
	    *, doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *);
    static doublereal envrl, envtl, envdl, envpl, tlmax;
    static integer itmax;
    static doublereal rlmax;
    static logical lcmax;
    static doublereal fl81br, fl98mo, fl115in, hitot, yrage;
    extern /* Subroutine */ int calcad_(doublereal *, doublereal *, integer *,
	     doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, integer *);
    static logical ltscal;
    static doublereal corerl;
    static logical lderiv;
    extern /* Subroutine */ int eqstat_(doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, logical *,
	     logical *, integer *);
    static doublereal fitmas;
    extern /* Subroutine */ int gettau_(doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, integer *, logical *, doublereal *);
    static doublereal ergpsl, xkteff, cmpsqs;
    static integer iwrite;
    extern /* Subroutine */ int wrtlst_(integer *, doublereal *, doublereal *,
	     doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, logical *, doublereal *, doublereal *, doublereal *,
	     doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, integer *, integer *, integer *, integer *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *), wrtmil_(doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, integer *, integer *), wrtmod_(integer *, integer *,
	     doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, integer *, doublereal *,
	     doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *), stitch_(doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, integer *, logical *, 
	    integer *);
    static doublereal ycenter;

    /* Fortran I/O blocks */
    static cilist io___8 = { 0, 0, 0, fmt_21, 0 };
    static cilist io___9 = { 0, 0, 0, fmt_30, 0 };
    static cilist io___10 = { 0, 0, 0, fmt_40, 0 };
    static cilist io___58 = { 0, 0, 0, fmt_50, 0 };
    static cilist io___59 = { 0, 0, 0, fmt_60, 0 };
    static cilist io___60 = { 0, 0, 0, fmt_70, 0 };
    static cilist io___61 = { 0, 0, 0, fmt_80, 0 };
    static cilist io___69 = { 0, 0, 0, fmt_120, 0 };
    static cilist io___72 = { 0, 0, 0, fmt_120, 0 };
    static cilist io___73 = { 0, 0, 0, fmt_150, 0 };
    static cilist io___74 = { 0, 0, 0, fmt_160, 0 };
    static cilist io___81 = { 0, 0, 0, fmt_2160, 0 };
    static cilist io___83 = { 0, 0, 0, fmt_170, 0 };
    static cilist io___84 = { 0, 0, 0, fmt_20, 0 };
    static cilist io___96 = { 0, 0, 0, fmt_1499, 0 };
    static cilist io___97 = { 0, 0, 0, fmt_1500, 0 };
    static cilist io___98 = { 0, 0, 0, fmt_1509, 0 };
    static cilist io___99 = { 0, 0, 0, fmt_1510, 0 };
    static cilist io___100 = { 0, 0, 0, fmt_1515, 0 };
    static cilist io___101 = { 0, 0, 0, fmt_1510, 0 };
    static cilist io___102 = { 0, 0, 0, fmt_1520, 0 };
    static cilist io___103 = { 0, 0, 0, fmt_1530, 0 };
    static cilist io___104 = { 0, 0, 0, fmt_1540, 0 };
    static cilist io___105 = { 0, 0, 0, fmt_1501, 0 };
    static cilist io___113 = { 0, 0, 0, fmt_1005, 0 };
    static cilist io___115 = { 0, 0, 0, fmt_1800, 0 };


/*      * FP,FT,ETA2,R0,HJM,HI,SJTOT,SKEROT,HS2,NKK)  ! KC 2025-05-31 */
/* MHP 8/25 Fscomp file depreciated,unused variables removed */
/*      CHARACTER*256 FLAST, FFIRST, FRUN, FSTAND, FFERMI, */
/*     1    FDEBUG, FTRACK, FSHORT, FMILNE, FMODPT, */
/*     2    FSTOR, FPMOD, FPENV, FPATM, FDYN, FISO, */
/*     3    FLLDAT, FSNU, FSCOMP, FKUR, */
/*     4    FMHD1, FMHD2, FMHD3, FMHD4, FMHD5, FMHD6, FMHD7, FMHD8 */
/* JVS 0712 for call to envint: */
/*       REAL*8 DUM1(4),DUM2(3),DUM3(3),DUM4(3) */
/* JVS 10/13 for recalculation of taucz */
/*       REAL*8 DEL1(JSON), DEL2(JSON) */
/* end JVS */
/*      COMMON/LUFNM/ FLAST, FFIRST, FRUN, FSTAND, FFERMI, */
/*     1    FDEBUG, FTRACK, FSHORT, FMILNE, FMODPT, */
/*     2    FSTOR, FPMOD, FPENV, FPATM, FDYN, */
/*     3    FLLDAT, FSNU, FSCOMP, FKUR, */
/*     4    FMHD1, FMHD2, FMHD3, FMHD4, FMHD5, FMHD6, FMHD7, FMHD8 */
/* DBG PULSE */
/* *** MHP 5/90 ADD COMMON BLOCK FOR GRAVITATIONAL SETTLING. */
/* *** MHP 7/91 ADD COMMON BLOCKS FOR SOLAR NEUTRINO I/O. */
/* MHP 8/25 Removed character file names from common block */
/* DBG 11/11/91 */
/* DBG 7/92 COMMON BLOCK ADDED TO COMPUTE DEBYE-HUCKEL CORRECTION. */
/* MHP 4/09 ADDED OPTION TO SCALE THE SATURATION RATE BY THE OVERTURN TIMESCALE */
/* JVS 01/11 ACOUSTIC DEPTH */
/* KC 2025-05-30 reordered common block elements */
/* COMMON/ACDPTH/TAUCZN,DELADJ(JSON),TAUHE, TNORM, TCZ, WHE, ICLCD, */
/*      *LCLCD, AGEOUT(5), IACAT, IJLAST, LJLAST, LJWRT, LADON,LAOLY, IJVS, */
/* JVS 08/13 IF THE CZ IS BEYOND THE FITTING POINT, STORE ITS LOCATION */
/* G Somers 10/14, Add spot common block */
/* G Somers END */
/* JVS END */
/* JVS 10/11 Common block for He3+He3 luminosity */
/* JVS end */
/* G Somers 3/17, ADDING NEW TAUCZ COMMON BLOCK */
/* MHP 8/96 CROSS SECTIONS OF DIFFERENT NEUTRINOS TO THE CHLORINE */
/* AND GALLIUM EXPERIMENTS; TAKEN FROM NEUTRINO ASTROPHYSICS,P.207. */
/* note changes in cl37 cross sections (see bahcall and pinsonneault, */
/* REV.MOD.PHYS., P.895) */
/* ID(JSON) */
    /* Parameter adjustments */
    --hs2;
    --hi;
    --hjm;
    --r0;
    --eta2;
    --ft;
    --fp;
    --omega;
    --cfenv;
    --rs;
    --ts;
    --ps;
    --tril;
    --trit;
    --tlumx;
    --lc;
    --ht;
    --hs1;
    --hs;
    --hr;
    --hp;
    --hl;
    --hd;
    hcomp -= 16;

    /* Function Body */
    ltscal = FALSE_;
/*  RENORMALIZE LUMINOSITY TERMS TLUMX - SKIPPED FOR HE FLASH */
    if (! heflsh_1.lkuthe) {
	thl = tlumx[1] + tlumx[2] + tlumx[3] + tlumx[4] + tlumx[5] + tlumx[6] 
		+ tlumx[7] + tlumx[8];
	temp = hl[*m] / thl;
	for (i__ = 1; i__ <= 8; ++i__) {
	    tlumx[i__] *= temp;
/* L10: */
	}
    }
/*  WRITE HEADER FILE DESCRIBING THE GLOBAL PROPERTIES OF THE STAR */
/*  AND THE CENTRAL CONDITIONS TO THE SHORT OUTPUT FILE */
/*  THIS INFORMATION IS ALSO WRITTEN TO THE MODEL OUTPUT FILE IF */
/*  A DETAILED BREAKDOWN OF THE STELLAR STRUCTURE IS TO BE PRINTED */
/*  FOR THIS MODEL. */

    io___8.ciunit = luout_1.ishort;
    s_wsfe(&io___8);
    e_wsfe();
/* L20: */
    if (! heflsh_1.lkuthe) {
	io___9.ciunit = luout_1.ishort;
	s_wsfe(&io___9);
	do_fio(&c__1, (char *)&(*model), (ftnlen)sizeof(integer));
	do_fio(&c__1, (char *)&(*smass), (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&comp_1.xnew, (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&comp_1.znew, (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&(*dage), (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&(*ddage), (ftnlen)sizeof(doublereal));
	e_wsfe();
    } else {
	io___10.ciunit = luout_1.ishort;
	s_wsfe(&io___10);
	do_fio(&c__1, (char *)&(*model), (ftnlen)sizeof(integer));
	do_fio(&c__1, (char *)&(*smass), (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&comp_1.xnew, (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&comp_1.znew, (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&(*dage), (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&(*ddage), (ftnlen)sizeof(doublereal));
	e_wsfe();
    }
/*  CALCULATE MASS OF CENTRAL AND SURFACE CONVECTION ZONES */
/*  THESE MASSES ARE IN SOLAR UNITS */
    if (*jcore > 1) {
	corem = hs1[*jcore] / const_1.cmsun;
    } else {
	corem = 0.;
    }
/* JVS 10/11 Be more care about the true boundary of the convective core */
    if (*jcore > 1) {
	fx2 = (scrtch_1.sdel[(*jcore + 1) * 3 - 1] - scrtch_1.sdel[*jcore * 3 
		- 3]) / (scrtch_1.sdel[(*jcore + 1) * 3 - 1] - scrtch_1.sdel[*
		jcore * 3 - 3]);
	corerl = hr[*jcore] + fx * (hr[*jcore + 1] - hr[*jcore]) - 
		const_1.crsunl;
	corer = exp(const1_1.cln * corerl);
    } else {
	corer = 0.;
    }
/* JVS end */
    bolm = const_1.cmbol - *bl * 2.5;
    rl = (*bl + const_1.clsunl - const1_1.c4pil - const2_1.csigl - *teffl * 
	    4.) * .5;
    *gl = const2_1.cgl + comp_1.stotal - rl - rl;
/* MHP 02/12 MOVED ABOVE SECTION WHERE THESE ARE USED */
/*  DETERMINE CENTRAL T,P, AND DENSITY USING THE FIRST SHELL VALUES. */
/*  CENTRAL ETA AND BETA ARE ALSO CALCULATED. */
/*  EXTRAPOLATE FROM INNER SHELL P AND T TO CENTRAL P AND T */
    temp = exp(const1_1.cln * (const1_1.cc13 * (const1_1.c4pi3l + hd[1] - hs[
	    1]) + hd[1] + const2_1.cgl + hs[1])) * .5;
    p = exp(const1_1.cln * hp[1]);
    d__1 = p + temp;
    pl = d_lg10(&d__1);
/*  SDEL(2,1) IS THE ACTUAL T GRADIENT AT POINT 1( = DEL) */
    d__1 = temp * scrtch_1.sdel[1] / p + 1.;
    tl = ht[1] + d_lg10(&d__1);
    dl = hd[1];
    x = hcomp[16];
    z__ = hcomp[18];
    latmo = TRUE_;
    lderiv = FALSE_;
/*  CALL EQSTAT TO GET TRUE CENTRAL DENSITY, BETA, AND ETA. */
/* YC  If LMHD then use MHD equation of state. */
    if (mhd_1.lmhd) {
	meqos_(&tl, &t, &pl, &p, &dl, &d__, &x, &z__, &beta, &betai, &beta14, 
		fxion, &rmu, &amu, &emu, &eta, &qdt, &qdp, &qcp, &dela, &qdtt,
		 &qdtp, &qat, &qap, &qcpt, &qcpp);
/*      *   AMU,EMU,ETA,QDT,QDP,QCP,DELA,QDTT,QDTP,QAT,QAP,QCPT,QCPP, */
/*      *   LDERIV,LATMO,KSAHA)  ! KC 2025-05-31 */
    } else {
	if (debhu_1.ldh) {
	    debhu_1.xxdh = hcomp[16];
	    debhu_1.yydh = hcomp[17] + hcomp[19];
	    debhu_1.zzdh = hcomp[18];
	    debhu_1.zdh[0] = hcomp[20] + hcomp[21];
	    debhu_1.zdh[1] = hcomp[22] + hcomp[23];
	    debhu_1.zdh[2] = hcomp[24] + hcomp[25] + hcomp[26];
	}
	eqstat_(&tl, &t, &pl, &p, &dl, &d__, &x, &z__, &beta, &betai, &beta14,
		 fxion, &rmu, &amu, &emu, &eta, &qdt, &qdp, &qcp, &dela, &
		qdtt, &qdtp, &qat, &qap, &qcpt, &qcpp, &lderiv, &latmo, &
		ksaha);
    }
/* MHP 02/12 MOVED ABOVE TO WHERE FIRST USED */
/* STORE CENTRAL RHO,P,T FOR LATER USE */
    cent_1.pcenter = pl;
    cent_1.tcenter = tl;
    cent_1.dcenter = dl;
/* MHP 02/12 FIXED MINOR GLITCH ON BASE OF THE CONVECTION ZONE */
/* PROPERTIES FOR FULLY CONVECTIVE STARS; TCENTER PCENTER RHOCENTER */
/* WERE BEING DEFINED AFTER THIS CODE SECTION */
    if (*jenv < *m) {
	if (*jenv > 1) {
/*  FIND MASS FRACTION OF THE ZONE EDGE AT BASE OF SURFACE C.Z. */
/* JVS 10/11/13 SDEL(1,JENV) IN DENOMINATOR WAS A TYPO. CHANGED TO SDEL(3,JENV) */
/*            FX = (SDEL(3,JENV)-SDEL(1,JENV-1))/ */
/*     *           (SDEL(3,JENV)-SDEL(1,JENV-1)) */
	    dd2 = scrtch_1.sdel[(*jenv - 1) * 3 - 3] - scrtch_1.sdel[(*jenv - 
		    1) * 3 - 1];
	    dd1 = scrtch_1.sdel[*jenv * 3 - 3] - scrtch_1.sdel[*jenv * 3 - 1];
	    fx = dd2 / (dd2 - dd1);
/*            HSB = 0.5D0*(HS1(JENV)+HS1(JENV-1)) */
	    hsb = hs1[*jenv - 1] + fx * (hs1[*jenv] - hs1[*jenv - 1]);
	    cent_1.envlm = (exp(const1_1.cln * *hstot) - hsb) / const_1.cmsun;
/*           ENVLM = SMASS-HS1(JENV-1)/CMSUN */
/*          HSR = 0.5D0*(10.0D0**HR(JENV)+10.0D0**HR(JENV-1)) */
/*          ENVX = HSR/(10.0D0**RL) */
/* MHP 2/98 FIND RADIUS OF CZ BASE */
	    envrl = hr[*jenv - 1] + fx * (hr[*jenv] - hr[*jenv - 1]) - 
		    const_1.crsunl;
	    cent_1.envr = exp(const1_1.cln * envrl);
	    envo = scrtch_1.so[*jenv - 2] + fx * (scrtch_1.so[*jenv - 1] - 
		    scrtch_1.so[*jenv - 2]);
	    envtl = ht[*jenv - 1] + fx * (ht[*jenv] - ht[*jenv - 1]);
	    envdl = hd[*jenv - 1] + fx * (hd[*jenv] - hd[*jenv - 1]);
	    envpl = hp[*jenv - 1] + fx * (hp[*jenv] - hp[*jenv - 1]);
	    envt = exp(const1_1.cln * envtl);
	    envd = exp(const1_1.cln * envdl);
	    envp = exp(const1_1.cln * envpl);
	} else {
	    cent_1.envlm = *smass;
	    cent_1.envr = 0.;
	    envt = pow_dd(&c_b23, &cent_1.tcenter);
	    envd = pow_dd(&c_b23, &cent_1.dcenter);
	    envp = pow_dd(&c_b23, &cent_1.pcenter);
	    envo = scrtch_1.so[0];
	}
    } else {
	cent_1.envlm = 0.;
	cent_1.envr = 0.;
	envt = 0.;
	envd = 0.;
	envp = 0.;
	envo = 0.;
    }
    io___58.ciunit = luout_1.ishort;
    s_wsfe(&io___58);
    do_fio(&c__1, (char *)&(*m), (ftnlen)sizeof(integer));
    do_fio(&c__1, (char *)&label_1.xenv0, (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&label_1.zenv0, (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&corem, (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&cent_1.envlm, (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&cent_1.envr, (ftnlen)sizeof(doublereal));
    e_wsfe();
    rl -= const_1.crsunl;
    io___59.ciunit = luout_1.ishort;
    s_wsfe(&io___59);
    do_fio(&c__1, (char *)&(*teffl), (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&bolm, (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&(*bl), (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&rl, (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&(*gl), (ftnlen)sizeof(doublereal));
    e_wsfe();
/* MHP 02/12 MOVED ABOVE SECTION WHERE THESE ARE USED */
/*  DETERMINE CENTRAL T,P, AND DENSITY USING THE FIRST SHELL VALUES. */
/*  CENTRAL ETA AND BETA ARE ALSO CALCULATED. */
/*  EXTRAPOLATE FROM INNER SHELL P AND T TO CENTRAL P AND T */
/*      TEMP =0.5D0*DEXP(CLN*(CC13*(C4PI3L+HD(1)-HS(1))+HD(1)+CGL+HS(1))) */
/*      P = DEXP(CLN*HP(1)) */
/*      PL = DLOG10(P + TEMP) */
/*  SDEL(2,1) IS THE ACTUAL T GRADIENT AT POINT 1( = DEL) */
/*      TL = HT(1) + DLOG10(1.0D0+ TEMP*SDEL(2,1)/P) */
/*      DL = HD(1) */
/*      X = HCOMP(1,1) */
/*      Z = HCOMP(3,1) */
/*      LATMO = .TRUE. */
/*      LDERIV = .FALSE. */
/*  CALL EQSTAT TO GET TRUE CENTRAL DENSITY, BETA, AND ETA. */
/* YC  If LMHD then use MHD equation of state. */
/*      IF (LMHD) THEN */
/*         CALL MEQOS(TL,T,PL,P,DL,D,X,Z,BETA,BETAI,BETA14,FXION,RMU, */
/*     *   AMU,EMU,ETA,QDT,QDP,QCP,DELA,QDTT,QDTP,QAT,QAP,QCPT,QCPP, */
/*     *   LDERIV,LATMO,KSAHA) */
/*      ELSE */
/*      IF (LDH) THEN */
/*         XXDH = HCOMP(1,1) */
/*         YYDH = HCOMP(2,1)+HCOMP(4,1) */
/*         ZZDH = HCOMP(3,1) */
/*         ZDH(1) = HCOMP(5,1)+HCOMP(6,1) */
/*         ZDH(2) = HCOMP(7,1)+HCOMP(8,1) */
/*         ZDH(3) = HCOMP(9,1)+HCOMP(10,1)+HCOMP(11,1) */
/*      END IF */
/*      CALL EQSTAT(TL,T,PL,P,DL,D,X,Z,BETA,BETAI,BETA14,FXION,RMU, */
/*     *AMU,EMU,ETA,QDT,QDP,QCP,DELA,QDTT,QDTP,QAT,QAP,QCPT,QCPP,LDERIV, */
/*     *LATMO,KSAHA) */
/*      END IF */
    io___60.ciunit = luout_1.ishort;
    s_wsfe(&io___60);
    do_fio(&c__1, (char *)&pl, (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&tl, (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&dl, (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&beta, (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&eta, (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&x, (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&z__, (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&hcomp[24], (ftnlen)sizeof(doublereal));
    e_wsfe();
    io___61.ciunit = luout_1.ishort;
    s_wsfe(&io___61);
    for (j = 1; j <= 5; ++j) {
	do_fio(&c__1, (char *)&tlumx[j], (ftnlen)sizeof(doublereal));
    }
    do_fio(&c__1, (char *)&tlumx[8], (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&tlumx[6], (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&tlumx[7], (ftnlen)sizeof(doublereal));
    e_wsfe();
    ss3 = 0.;
    ss4 = 0.;
    if (*lshell) {
/* H-SHELL VALUES PRINTED OUT - MASSES IN SOLAR UNITS */
/* SS1 - MASS INTERIOR TO CENTER OF H SHELL; SS2 = MASS OF H SHELL; */
/* SS3 = HE CORE MASS; SS4 = MASS INTERIOR TO SHELL WITH MAXIMUM T */
	ss1 = hs1[*jxmid] / const_1.cmsun;
	ss2 = (hs1[*jxend] - hs1[*jxbeg - 1]) / const_1.cmsun;
	ss3 = hs1[*jxbeg - 1] / const_1.cmsun;
	tlmax = tl;
/* LOCATE MAXIMUM T - NOTE DIFFERENT METHOD USED FOR HE FLASH */
	if (! heflsh_1.lkuthe) {
	    i__1 = *m;
	    for (i__ = 2; i__ <= i__1; ++i__) {
		if (ht[i__] < ht[i__ - 1]) {
		    goto L110;
		}
/* L100: */
	    }
	    i__ = *m + 1;
L110:
	    itmax = i__ - 1;
	    if (itmax > 1) {
		ss4 = hs1[itmax] / const_1.cmsun;
		tlmax = ht[itmax];
	    } else {
		ss4 = 0.;
		tlmax = ht[1];
	    }
	    io___69.ciunit = luout_1.ishort;
	    s_wsfe(&io___69);
	    do_fio(&c__1, (char *)&ss1, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&ss2, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&ss3, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&tlmax, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&ss4, (ftnlen)sizeof(doublereal));
	    e_wsfe();
	} else {
/*  HE FLASH */
	    i__1 = *m;
	    for (i__ = 2; i__ <= i__1; ++i__) {
		if (ht[i__] < ht[i__ - 1] && ht[i__ - 1] > 7.98) {
		    goto L140;
		}
/* L130: */
	    }
	    i__ = *m + 1;
L140:
	    itmax = i__ - 1;
	    if (itmax > 1) {
		ss4 = hs1[itmax] / const_1.cmsun;
		tlmax = ht[itmax];
/*  ADDITIONAL OUTPUT FOR HE FLASH */
		rlmax = hr[itmax];
		lcmax = lc[itmax];
		io___72.ciunit = luout_1.ishort;
		s_wsfe(&io___72);
		do_fio(&c__1, (char *)&ss1, (ftnlen)sizeof(doublereal));
		do_fio(&c__1, (char *)&ss2, (ftnlen)sizeof(doublereal));
		do_fio(&c__1, (char *)&ss3, (ftnlen)sizeof(doublereal));
		do_fio(&c__1, (char *)&tlmax, (ftnlen)sizeof(doublereal));
		do_fio(&c__1, (char *)&ss4, (ftnlen)sizeof(doublereal));
		e_wsfe();
		io___73.ciunit = luout_1.ishort;
		s_wsfe(&io___73);
		do_fio(&c__1, (char *)&lcmax, (ftnlen)sizeof(logical));
		do_fio(&c__1, (char *)&rlmax, (ftnlen)sizeof(doublereal));
		e_wsfe();
	    }
	}
/*  END H-SHELL SECTION */
    }
/*     PRINT OUT NEUTRINO RATES FROM ENGEB CALCULATION */
    io___74.ciunit = luout_1.ishort;
    s_wsfe(&io___74);
    for (i__ = 1; i__ <= 8; ++i__) {
	do_fio(&c__1, (char *)&fluxes_1.fluxtot[i__ - 1], (ftnlen)sizeof(
		doublereal));
    }
    e_wsfe();
/* DBG 7/93 from Bahcall's book p 207 table 8.2 */
    fl7li = fluxes_1.fluxtot[0] * 0. + fluxes_1.fluxtot[1] * 665. + 
	    fluxes_1.fluxtot[2] * 8.4e4 + fluxes_1.fluxtot[3] * 9.6 + 
	    fluxes_1.fluxtot[4] * 3.9e4 + fluxes_1.fluxtot[5] * 42.4 + 
	    fluxes_1.fluxtot[6] * 246. + fluxes_1.fluxtot[7] * 249.;
    fl37cl = fluxes_1.fluxtot[0] * 0. + fluxes_1.fluxtot[1] * 16. + 
	    fluxes_1.fluxtot[2] * 42600. + fluxes_1.fluxtot[3] * 2.4 + 
	    fluxes_1.fluxtot[4] * 10900. + fluxes_1.fluxtot[5] * 1.7 + 
	    fluxes_1.fluxtot[6] * 6.8 + fluxes_1.fluxtot[7] * 6.9;
    fl71ga = fluxes_1.fluxtot[0] * 11.8 + fluxes_1.fluxtot[1] * 215. + 
	    fluxes_1.fluxtot[2] * 7.3e4 + fluxes_1.fluxtot[3] * 73.2 + 
	    fluxes_1.fluxtot[4] * 24300. + fluxes_1.fluxtot[5] * 61.8 + 
	    fluxes_1.fluxtot[6] * 116. + fluxes_1.fluxtot[7] * 117.;
    fl81br = fluxes_1.fluxtot[0] * 0. + fluxes_1.fluxtot[1] * 75. + 
	    fluxes_1.fluxtot[2] * 9e4 + fluxes_1.fluxtot[3] * 18.3 + 
	    fluxes_1.fluxtot[4] * 2.7e4 + fluxes_1.fluxtot[5] * 14.5 + 
	    fluxes_1.fluxtot[6] * 36.7 + fluxes_1.fluxtot[7] * 37.;
    fl98mo = fluxes_1.fluxtot[0] * 0. + fluxes_1.fluxtot[1] * 0. + 
	    fluxes_1.fluxtot[2] * 1e5 + fluxes_1.fluxtot[3] * 0. + 
	    fluxes_1.fluxtot[4] * 3e4 + fluxes_1.fluxtot[5] * 0. + 
	    fluxes_1.fluxtot[6] * 0. + fluxes_1.fluxtot[7] * 0.;
    fl115in = fluxes_1.fluxtot[0] * 78. + fluxes_1.fluxtot[1] * 576. + 
	    fluxes_1.fluxtot[2] * 6.1e4 + fluxes_1.fluxtot[3] * 248. + 
	    fluxes_1.fluxtot[4] * 2.5e4 + fluxes_1.fluxtot[5] * 224. + 
	    fluxes_1.fluxtot[6] * 355. + fluxes_1.fluxtot[7] * 356.;
    io___81.ciunit = luout_1.ishort;
    s_wsfe(&io___81);
    do_fio(&c__1, (char *)&fl7li, (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&fl37cl, (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&fl71ga, (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&fl81br, (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&fl98mo, (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&fl115in, (ftnlen)sizeof(doublereal));
    e_wsfe();
    fitmas = hs1[*m] / const_1.cmsun;
    io___83.ciunit = luout_1.ishort;
    s_wsfe(&io___83);
    do_fio(&c__1, (char *)&fitmas, (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&hp[*m], (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&ht[*m], (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&hr[*m], (ftnlen)sizeof(doublereal));
    e_wsfe();
    io___84.ciunit = luout_1.ishort;
    s_wsfe(&io___84);
    e_wsfe();
    if (ccout2_1.ltrack) {
/* MHP 02/12 MOVED ABOVE TO WHERE FIRST USED */
/* MHP 8/96 */
/* STORE CENTRAL RHO,P,T FOR LATER USE */
/*         PCENTER = PL */
/*         TCENTER = TL */
/*         DCENTER = DL */
/*  Total moment of inertia */
	hitot = 0.;
	if (! rot_1.lrot) {
	    i__1 = *m;
	    for (i__ = 1; i__ <= i__1; ++i__) {
		hitot += const1_1.cc23 * hs2[i__] * exp(const1_1.cln * 2. * 
			hr[i__]);
	    }
	} else {
	    i__1 = *m;
	    for (i__ = 1; i__ <= i__1; ++i__) {
		hitot += hi[i__];
	    }
	}
/* MHP 12/09 NEW OPTION TO OUTPUT TRACK INFORMATION IN ONE LINE PER MODEL FORMAT. */
	if (track_1.itrver == 0) {
/* MHP 8/96 ADD LINE TO COMPUTE SNU's for Cl37 and Ga71. */
	    fluxes_1.clsnu = 0.;
	    fluxes_1.gasnu = 0.;
	    if (neweng_1.lsnu) {
		for (i__ = 1; i__ <= 8; ++i__) {
		    fluxes_1.clsnu += clsnuf[i__ - 1] * fluxes_1.fluxtot[i__ 
			    - 1];
		    fluxes_1.gasnu += gasnuf[i__ - 1] * fluxes_1.fluxtot[i__ 
			    - 1];
		}
	    } else {
		for (i__ = 1; i__ <= 10; ++i__) {
		    fluxes_1.fluxtot[i__ - 1] = 0.;
		}
	    }
/* MHP 02/12 */
/* ADDED SURFACE CZ MOMENT OF INERTIA CALCULATION TO NON-ROTATING */
/* MODELS, AND CORRECTLY ZERO OUT TERMS NOT COMPUTED IN SPHERICAL MODELS */
/* ROTATION I/O */
	    hicz = 0.;
	    if (rot_1.lrot) {
/* Computing MIN */
		d__1 = 9999., d__2 = const1_1.c4pi * .5 / omega[*m] / 86400.;
		rotp = min(d__1,d__2);
		rotv = omega[*m] * exp(const1_1.cln * (rl + const_1.crsunl)) *
			 1e-5;
		if (*jenv < *m) {
		    i__1 = *m;
		    for (k = *jenv; k <= i__1; ++k) {
			hicz += hi[k];
		    }
		}
	    } else {
		rotp = 0.;
		rotv = 0.;
		if (*jenv < *m) {
		    i__1 = *m;
		    for (k = *jenv; k <= i__1; ++k) {
			hicz += const1_1.cc23 * hs2[k] * exp(const1_1.cln * 
				2. * hr[k]);
		    }
		}
	    }
/* END CHANGED SECTION */
/*        Get location of bottom, middle, top of B burning shell. */
	    if (*lshell) {
		sss1 = hs1[*jxbeg] / const_1.cmsun;
		sss2 = hs1[*jxmid] / const_1.cmsun;
		sss3 = hs1[*jxend] / const_1.cmsun;
		rrr1 = exp(const1_1.cln * (hr[*jxbeg] - rl - const_1.crsunl));
		rrr2 = exp(const1_1.cln * (hr[*jxmid] - rl - const_1.crsunl));
		rrr3 = exp(const1_1.cln * (hr[*jxend] - rl - const_1.crsunl));
	    } else {
		sss1 = 0.;
		sss2 = sss1;
		sss3 = sss1;
		rrr1 = sss1;
		rrr2 = sss1;
		rrr3 = sss1;
	    }
/* JVS 0712 Drop sinkline to get pressure at photosphere (updates PPHOT) */
/*             ABEG0 = ATMBEG */
/*            AMIN0 = ATMMIN */
/*            AMAX0 = ATMMAX */
/*            EBEG0 = ENVBEG */
/*            EMIN0 = ENVMIN */
/*            EMAX0 = ENVMAX */
/*            ATMBEG = ATMSTP */
/*            ATMMIN = ATMSTP */
/*            ATMMAX = ATMSTP */
/*            ENVBEG = ENVSTP */
/*            ENVMIN = ENVSTP */
/*            ENVMAX = ENVSTP */
/*            IDUM = 0 */
/*            B = DEXP(CLN*BL) */
/*            FPL = FP(M) */
/*             FTL = FT(M) */
/*            KATM = 0 */
/*             KENV = 0 */
/*             KSAHA = 0 */
/* CCC            LPULPT=.FALSE. */
/*            IXX=0 */
/*            LPRT=.FALSE. */
/*            LSBC0 = .FALSE. */
/*            X = HCOMP(1,M) */
/*             Z = HCOMP(3,M) */
/*            RLL = 0.5D0*(BL + CLSUNL - 4.0D0*TEFFL - C4PIL - CSIGL) */
/*            GL = CGL + HSTOT - RLL - RLL */
/*            PLIM = HP(M) */
/* C G Somers 10/14, FOR SPOTTED RUNS, FIND THE */
/* C PRESSURE AT THE AMBIENT TEMPERATURE ATEFFL */
/*            IF(JENV.EQ.M.AND.SPOTF.NE.0.0.AND.SPOTX.NE.1.0)THEN */
/*                   ATEFFL = TEFFL - 0.25*LOG10(SPOTF*SPOTX**4.0+1.0-SPOTF) */
/*            ELSE */
/*               ATEFFL = TEFFL */
/*            ENDIF */
/*            CALL ENVINT(B,FPL,FTL,GL,HSTOT,IXX,LPRT,LSBC0, */
/*     *            PLIM,RLL,ATEFFL,X,Z,DUM1,IDUM,KATM,KENV,KSAHA, */
/*     *            DUM2,DUM3,DUM4,LPULPT) */
/* C G Somers END */

/* C JVS 08/13 TRACKS CZ EVEN WHEN OUTSIDE THE ENVELOPE FITTING POINT */
/*      IF(JENV.GE.M .AND. .NOT. LC(M)) THEN */
/*            ENVR = ENVRCZ */
/*      ELSE IF(JENV.GE.M .AND. LC(M)) THEN */
/*            DO I=1,M */
/*                  DEL1(I) = SDEL(1,I) */
/*                  DEL2(I) = SDEL(3,I) */
/*            ENDDO */
/*                  LJVS = .TRUE. */
/*                  CALL TAUINT(HCOMP,HS2,HS1,LC,HR,HP,HD,HG,M,SVEL,DEL1,DEL2) */
/*                  LJVS = .FALSE. */
/*                  DD2 = DEL1(JENV-1)-DEL2(JENV-1) */
/*                  DD1 = DEL1(JENV)-DEL2(JENV) */
/*                  FX = DD2/(DD2-DD1) */
/*                  ENVCZL = HR(JENV-1)+FX*(HR(JENV)-HR(JENV-1)) */
/*                  ENVR = EXP(CLN*ENVCZL)/CRSUN */
/*      ELSE */
/*            DO I=1,M */
/*                  DEL1(I) = SDEL(1,I) */
/*                  DEL2(I) = SDEL(3,I) */
/*            ENDDO */
/*                  LJVS = .TRUE. */
/*                  CALL TAUINT(HCOMP,HS2,HS1,LC,HR,HP,HD,HG,M,SVEL,DEL1,DEL2) */
/*                  LJVS = .FALSE. */
/*      ENDIF */

/* G Somers 3/17, ADDED CALL TO NEW TAUCZ AND PPHOT CALCULATION ROUTINE. */
/*       CALL GETTAU(HCOMP,HR,HP,HD,HG,HS1,HT,FP,FT,TEFFL,  ! KC 2025-05-31 */
	    gettau_(&hcomp[16], &hr[1], &hp[1], &hd[1], &hs1[1], &ht[1], &fp[
		    1], &ft[1], teffl, hstot, bl, m, &lc[1], &cent_1.envr);
	    ovrtrn_1.taucz0 = ovrtrn_1.taucz;
	    ovrtrn_1.pphot0 = ovrtrn_1.pphot;
/* JVS 02/12 Added PPHOT and SMASS to the output */
	    io___96.ciunit = luout_1.itrack;
	    s_wsfe(&io___96);
	    do_fio(&c__1, (char *)&(*model), (ftnlen)sizeof(integer));
	    do_fio(&c__1, (char *)&(*m), (ftnlen)sizeof(integer));
	    do_fio(&c__1, (char *)&(*dage), (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&(*bl), (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&rl, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&(*gl), (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&(*teffl), (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&corem, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&cent_1.envlm, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&cent_1.envr, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&envt, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&envd, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&envp, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&envo, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&tl, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&dl, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&pl, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&beta, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&eta, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&hcomp[16], (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&hcomp[17], (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&hcomp[18], (ftnlen)sizeof(doublereal));
	    for (j = 1; j <= 5; ++j) {
		do_fio(&c__1, (char *)&tlumx[j], (ftnlen)sizeof(doublereal));
	    }
	    do_fio(&c__1, (char *)&tlumx[8], (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&tlumx[7], (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&tlumx[6], (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&fluxes_1.clsnu, (ftnlen)sizeof(doublereal))
		    ;
	    do_fio(&c__1, (char *)&fluxes_1.gasnu, (ftnlen)sizeof(doublereal))
		    ;
	    for (i__ = 1; i__ <= 10; ++i__) {
		do_fio(&c__1, (char *)&fluxes_1.fluxtot[i__ - 1], (ftnlen)
			sizeof(doublereal));
	    }
	    for (i__ = 4; i__ <= 11; ++i__) {
		do_fio(&c__1, (char *)&hcomp[i__ + 15], (ftnlen)sizeof(
			doublereal));
	    }
	    for (i__ = 4; i__ <= 15; ++i__) {
		do_fio(&c__1, (char *)&hcomp[i__ + *m * 15], (ftnlen)sizeof(
			doublereal));
	    }
	    for (i__ = 1; i__ <= 3; ++i__) {
		do_fio(&c__1, (char *)&hcomp[i__ + *m * 15], (ftnlen)sizeof(
			doublereal));
	    }
	    d__1 = hcomp[*m * 15 + 3] / hcomp[*m * 15 + 1];
	    do_fio(&c__1, (char *)&d__1, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&(*sjtot), (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&(*skerot), (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&hitot, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&hicz, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&omega[*m], (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&omega[1], (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&rotp, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&rotv, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&ovrtrn_1.taucz, (ftnlen)sizeof(doublereal))
		    ;
	    do_fio(&c__1, (char *)&sss1, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&sss2, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&sss3, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&rrr1, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&rrr2, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&rrr3, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&ovrtrn_1.pphot, (ftnlen)sizeof(doublereal))
		    ;
	    do_fio(&c__1, (char *)&(*smass), (ftnlen)sizeof(doublereal));
	    e_wsfe();
/* MHP 9/25 added more columns to cz depth to avoid overflow */
/*     1499       FORMAT(1X,2I8,1P7E16.8,0PF8.4,1P4E12.4,16E16.8,12E10.3,41E16.8) */
	} else if (track_1.itrver == 1 || track_1.itrver == 2) {
	    io___97.ciunit = luout_1.itrack;
	    s_wsfe(&io___97);
	    do_fio(&c__1, (char *)&(*model), (ftnlen)sizeof(integer));
	    do_fio(&c__1, (char *)&(*m), (ftnlen)sizeof(integer));
	    do_fio(&c__1, (char *)&(*dage), (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&(*bl), (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&rl, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&(*gl), (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&(*teffl), (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&corem, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&cent_1.envlm, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&cent_1.envr, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&envt, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&envd, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&envp, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&envo, (ftnlen)sizeof(doublereal));
	    e_wsfe();
	    io___98.ciunit = luout_1.itrack;
	    s_wsfe(&io___98);
	    do_fio(&c__1, (char *)&tl, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&dl, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&pl, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&beta, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&eta, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&hcomp[16], (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&hcomp[17], (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&hcomp[18], (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&hitot, (ftnlen)sizeof(doublereal));
	    e_wsfe();
/* L1510: */
	    io___99.ciunit = luout_1.itrack;
	    s_wsfe(&io___99);
	    for (j = 1; j <= 5; ++j) {
		do_fio(&c__1, (char *)&tlumx[j], (ftnlen)sizeof(doublereal));
	    }
	    do_fio(&c__1, (char *)&tlumx[8], (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&tlumx[7], (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&tlumx[6], (ftnlen)sizeof(doublereal));
	    e_wsfe();
/* MHP 8/96 ADD LINE TO COMPUTE SNU's for Cl37 and Ga71. */
	    fluxes_1.clsnu = 0.;
	    fluxes_1.gasnu = 0.;
	    for (i__ = 1; i__ <= 8; ++i__) {
		fluxes_1.clsnu += clsnuf[i__ - 1] * fluxes_1.fluxtot[i__ - 1];
		fluxes_1.gasnu += gasnuf[i__ - 1] * fluxes_1.fluxtot[i__ - 1];
	    }
	    io___100.ciunit = luout_1.itrack;
	    s_wsfe(&io___100);
	    do_fio(&c__1, (char *)&fluxes_1.clsnu, (ftnlen)sizeof(doublereal))
		    ;
	    do_fio(&c__1, (char *)&fluxes_1.gasnu, (ftnlen)sizeof(doublereal))
		    ;
	    for (i__ = 1; i__ <= 10; ++i__) {
		do_fio(&c__1, (char *)&fluxes_1.fluxtot[i__ - 1], (ftnlen)
			sizeof(doublereal));
	    }
	    e_wsfe();
	    io___101.ciunit = luout_1.itrack;
	    s_wsfe(&io___101);
	    for (i__ = 4; i__ <= 11; ++i__) {
		do_fio(&c__1, (char *)&hcomp[i__ + 15], (ftnlen)sizeof(
			doublereal));
	    }
	    e_wsfe();
/* ADD SURFACE X,Y,Z,Z/X. */
	    io___102.ciunit = luout_1.itrack;
	    s_wsfe(&io___102);
	    for (i__ = 4; i__ <= 15; ++i__) {
		do_fio(&c__1, (char *)&hcomp[i__ + *m * 15], (ftnlen)sizeof(
			doublereal));
	    }
	    for (i__ = 1; i__ <= 3; ++i__) {
		do_fio(&c__1, (char *)&hcomp[i__ + *m * 15], (ftnlen)sizeof(
			doublereal));
	    }
	    d__1 = hcomp[*m * 15 + 3] / hcomp[*m * 15 + 1];
	    do_fio(&c__1, (char *)&d__1, (ftnlen)sizeof(doublereal));
	    e_wsfe();
/* ROTATION I/O */
	    if (rot_1.lrot) {
/* MHP 8/25 removed limit on rotation period output */
/*     ROTP = MIN(9999.0D0,0.5D0*C4PI/OMEGA(M)/8.64D4) */
		rotp = const1_1.c4pi * .5 / omega[*m] / 86400.;
		rotv = omega[*m] * exp(const1_1.cln * (rl + const_1.crsunl)) *
			 1e-5;
		hicz = 0.;
		if (lc[*m]) {
		    i__1 = *m;
		    for (k = *jenv; k <= i__1; ++k) {
			hicz += hi[k];
		    }
		} else {
		    hicz = 0.;
		}
	    }
/*        Get location of bottom, middle, top of B burning shell. */
	    if (*lshell) {
		sss1 = hs1[*jxbeg] / const_1.cmsun;
		sss2 = hs1[*jxmid] / const_1.cmsun;
		sss3 = hs1[*jxend] / const_1.cmsun;
		rrr1 = exp(const1_1.cln * (hr[*jxbeg] - rl - const_1.crsunl));
		rrr2 = exp(const1_1.cln * (hr[*jxmid] - rl - const_1.crsunl));
		rrr3 = exp(const1_1.cln * (hr[*jxend] - rl - const_1.crsunl));
	    } else {
		sss1 = 0.;
		sss2 = sss1;
		sss3 = sss1;
		rrr1 = sss1;
		rrr2 = sss1;
		rrr3 = sss1;
	    }
	    io___103.ciunit = luout_1.itrack;
	    s_wsfe(&io___103);
	    do_fio(&c__1, (char *)&sss1, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&sss2, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&sss3, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&rrr1, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&rrr2, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&rrr3, (ftnlen)sizeof(doublereal));
	    e_wsfe();
	}
/*        ROTATION STUFF */
/* 4/09 ADDED TAUCZ TO ROTATION INFORMATION */
	if (track_1.itrver == 2) {
	    io___104.ciunit = luout_1.itrack;
	    s_wsfe(&io___104);
	    do_fio(&c__1, (char *)&(*sjtot), (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&(*skerot), (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&hitot, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&hicz, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&omega[*m], (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&omega[1], (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&rotp, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&rotv, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&ovrtrn_1.taucz, (ftnlen)sizeof(doublereal))
		    ;
	    e_wsfe();
	}
	if (track_1.itrver == 3) {
/*        RATIO OF GRAV TO TOTAL ENERGY */
/*       GROTOT = 100.0*TLUMX(7)/HL(M) */
	    io___105.ciunit = luout_1.itrack;
	    s_wsfe(&io___105);
	    do_fio(&c__1, (char *)&(*model), (ftnlen)sizeof(integer));
	    do_fio(&c__1, (char *)&(*m), (ftnlen)sizeof(integer));
	    do_fio(&c__1, (char *)&(*dage), (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&(*bl), (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&rl, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&(*gl), (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&(*teffl), (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&corem, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&cent_1.envlm, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&cent_1.envr, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&comp_1.xnew, (ftnlen)sizeof(doublereal));
	    e_wsfe();
	}
    }
/* April 1992, DBG ISOCHRONE OUTPUT */
    if (chrone_1.liso) {
/* Write out model no., age (yr), L (erg/s), R (cm), Teff (K), */
/* g (cm/s**2), Ycenter, Mass He core (gm) */
	yrage = *dage * 1e9;
	ergpsl = pow_dd(&c_b23, bl);
	ergpsl *= const_1.clsun;
	cmr = pow_dd(&c_b23, &rl);
	cmr *= const_1.crsun;
	xkteff = pow_dd(&c_b23, teffl);
	cmpsqs = pow_dd(&c_b23, gl);
	ycenter = hcomp[17];
	if (*lshell) {
	    gmhecore = hs1[*jxbeg - 1];
	} else {
	    gmhecore = 0.;
	}
	io___113.ciunit = chrone_1.iiso;
	s_wsfe(&io___113);
	do_fio(&c__1, (char *)&(*model), (ftnlen)sizeof(integer));
	do_fio(&c__1, (char *)&yrage, (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&ergpsl, (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&cmr, (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&xkteff, (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&cmpsqs, (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&ycenter, (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&gmhecore, (ftnlen)sizeof(doublereal));
	e_wsfe();
    }
/* MHP 8/25 Fscomp depreciated, call commented out */
/*     WRITE OUT SURFACE COMPOSITIONS TO FILE ISCOMP IF extended comp MODEL. */
/*      IF(LEXCOM) THEN */
/*       OPEN(UNIT=ISCOMP,FILE=FSCOMP, FORM='FORMATTED', */
/*     *        STATUS='UNKNOWN',ACCESS='APPEND') */
/*       WRITE(ISCOMP,235)MODEL,DAGE,HCOMP(4,M),HCOMP(5,M),HCOMP(6,M), */
/*     *                HCOMP(7,M),HCOMP(14,M),HCOMP(15,M) */
/*  235    FORMAT(I4,F13.9,1P6E10.3) */
/*       CLOSE(ISCOMP) */
/*      ENDIF */

/* G Somers 11/14, WRITE THE LAST MODEL TO .LAST, AND IF LSTORE=T AND WE'RE ON */
/* A STORING TIMESTEP, WRITE THE EXTENDED INFORMATION TO LSTORE. IF NOT, GRAB */
/* THE PULSATION INFO IF LPULSE=TRUE. */

/*  STORE LAST CONVERGED MODEL IN LOGICAL UNIT ILAST */
/*  IF LSTORE = T, STORE EVERY NPUNCH MODELS IN LOGICAL UNIT ISTOR */
/*  IF LSTPCH = T, STORE THE LAST MODEL CALCULATED IN A RUN */
    iwrite = luout_1.ilast;
    wrtlst_(&iwrite, &hcomp[16], &hd[1], &hl[1], &hp[1], &hr[1], &hs[1], &ht[
	    1], &lc[1], &trit[1], &tril[1], &ps[1], &ts[1], &rs[1], &cfenv[1],
	     ftri, &tlumx[1], jcore, jenv, model, m, smass, teffl, bl, hstot, 
	    dage, ddage, &omega[1]);

/*  PRINT OUT MODEL DETAILS IF REQUESTED FOR THIS MODEL. THIS IS ALL DONE */
/*  IN THE SR PUTSTORE. */

    if (ccout_1.lstore && *model % ccout1_1.nprtmod == 0) {
	putstore_(&hcomp[16], &hd[1], &hl[1], &hp[1], &hr[1], &hs[1], &ht[1], 
		&lc[1], &trit[1], &tril[1], &ps[1], &ts[1], &rs[1], &cfenv[1],
		 ftri, &tlumx[1], jcore, jenv, model, m, smass, teffl, bl, 
		hstot, dage, ddage, &omega[1], &hs1[1], &eta2[1], &r0[1], &fp[
		1], &ft[1], &hjm[1], &hi[1]);
	*lpunch = FALSE_;
    }
/* the call to putstore above creates the necessary pulsation output for LPULSE. */
/* however, in the event that the above block is not executed and pulsation */
/* output is desired, call wrtmod. */
    if (! (ccout_1.lstore && *model % ccout1_1.nprtmod == 0) && 
	    pulse_1.lpulse) {
	if (ccout2_1.lmilne) {
	    wrtmil_(&hcomp[16], &hd[1], &hl[1], &hp[1], &hr[1], &hs1[1], m, 
		    model);
	}
/*        CALL WRTMOD(M,LSHELL,JXBEG,JXEND,JCORE,JENV,HCOMP,HS1,HD,HL, */
/*      *   HP,HR,HT,LC,MODEL,BL,TEFFL,OMEGA,FP,FT,ETA2,R0,HJM,HI,HS, */
/*      *   DAGE)  ! KC 2025-05-31 */
	wrtmod_(m, jenv, &hcomp[16], &hs1[1], &hd[1], &hl[1], &hp[1], &hr[1], 
		&ht[1], model, bl, teffl, &fp[1], &ft[1], &hs[1], dage);
    }
/* G Somers END */
/* JVS 01/11 Added new track file output format, +manipulations for stitching */
/* together the interior and envelope pieces. Columns 68,69,70 are normalized */
/* acoustic depth, depth to CZ and acoustic crossing time, respectively. */
    if (acdpth_1.lacout) {
	if (*jenv > 1 && acdpth_1.ladon) {
	    calcad_(&hr[1], &envrl, m, &hd[1], &hp[1], &ht[1], bl, &fp[1], &
		    ft[1], hstot, teffl, &hcomp[16], dage, jenv);
/*      *            LPRT, TEFFL, HCOMP, NKK, DAGE, DDAGE, JENV)  ! KC 2025-05-31 */
	} else if (*jenv == 1) {
	    acdpth_1.tauczn = 0.;
	}
	if (lc[*m]) {
	    icheck = 1;
	} else if (! lc[*m]) {
	    icheck = 0;
	}
	if (acdpth_1.ljlast) {
	    iwrite = acdpth_1.ijlast;
	    wrtlst_(&iwrite, &hcomp[16], &hd[1], &hl[1], &hp[1], &hr[1], &hs[
		    1], &ht[1], &lc[1], &trit[1], &tril[1], &ps[1], &ts[1], &
		    rs[1], &cfenv[1], ftri, &tlumx[1], jcore, jenv, model, m, 
		    smass, teffl, bl, hstot, dage, ddage, &omega[1]);
	}
	io___115.ciunit = luout_1.itrack;
	s_wsfe(&io___115);
	do_fio(&c__1, (char *)&(*model), (ftnlen)sizeof(integer));
	do_fio(&c__1, (char *)&(*m), (ftnlen)sizeof(integer));
	do_fio(&c__1, (char *)&(*dage), (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&(*bl), (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&rl, (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&(*gl), (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&(*teffl), (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&corem, (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&cent_1.envlm, (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&cent_1.envr, (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&envt, (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&envd, (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&envp, (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&envo, (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&tl, (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&dl, (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&pl, (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&beta, (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&eta, (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&hcomp[16], (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&hcomp[17], (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&hcomp[18], (ftnlen)sizeof(doublereal));
	for (j = 1; j <= 5; ++j) {
	    do_fio(&c__1, (char *)&tlumx[j], (ftnlen)sizeof(doublereal));
	}
	do_fio(&c__1, (char *)&tlumx[8], (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&tlumx[7], (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&tlumx[6], (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&fluxes_1.clsnu, (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&fluxes_1.gasnu, (ftnlen)sizeof(doublereal));
	for (i__ = 1; i__ <= 10; ++i__) {
	    do_fio(&c__1, (char *)&fluxes_1.fluxtot[i__ - 1], (ftnlen)sizeof(
		    doublereal));
	}
	for (i__ = 4; i__ <= 11; ++i__) {
	    do_fio(&c__1, (char *)&hcomp[i__ + 15], (ftnlen)sizeof(doublereal)
		    );
	}
	for (i__ = 4; i__ <= 15; ++i__) {
	    do_fio(&c__1, (char *)&hcomp[i__ + *m * 15], (ftnlen)sizeof(
		    doublereal));
	}
	for (i__ = 1; i__ <= 3; ++i__) {
	    do_fio(&c__1, (char *)&hcomp[i__ + *m * 15], (ftnlen)sizeof(
		    doublereal));
	}
	d__1 = hcomp[*m * 15 + 3] / hcomp[*m * 15 + 1];
	do_fio(&c__1, (char *)&d__1, (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&(*sjtot), (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&acdpth_1.tauczn, (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&acdpth_1.tcz, (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&acdpth_1.tnorm, (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&acdpth_1.tauhe, (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&acdpth_1.whe, (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&acdpth_1.tatmos, (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&rotv, (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&ovrtrn_1.taucz, (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&sss1, (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&sss2, (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&sss3, (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&rrr1, (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&rrr2, (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&rrr3, (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&icheck, (ftnlen)sizeof(integer));
	e_wsfe();
/* JVS END */
    }
/* JVS 08/25 Added the option to output a stitched version of the interior and envelope */
/* solutions. */
    if (ccout_1.lstch && *model % ccout1_1.nprtmod == 0) {
	stitch_(&hcomp[16], &hr[1], &hp[1], &hd[1], &hs[1], &ht[1], &hl[1], &
		hs1[1], &omega[1], &eta2[1], &hi[1], &r0[1], &hjm[1], &fp[1], 
		&ft[1], teffl, hstot, bl, m, &lc[1], model);
    }
    return 0;
} /* wrtout_ */

