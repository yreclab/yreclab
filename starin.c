/* starin.f -- translated by f2c (version 20100827).
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
    integer ifirst, irun, istand, ifermi, iopmod, iopenv, iopatm, idyn, 
	    illdat, isnu, iscomp, ikur;
} lunum_;

#define lunum_1 lunum_

struct {
    char flast[256], ffirst[256], frun[256], fstand[256], ffermi[256], fdebug[
	    256], ftrack[256], fshort[256], fmilne[256], fmodpt[256], fstor[
	    256], fpmod[256], fpenv[256], fpatm[256], fdyn[256], flldat[256], 
	    fsnu[256], fscomp[256], fkur[256], fmhd1[256], fmhd2[256], fmhd3[
	    256], fmhd4[256], fmhd5[256], fmhd6[256], fmhd7[256], fmhd8[256];
} lufnm_;

#define lufnm_1 lufnm_

struct {
    integer ilast, idebug, itrack, ishort, imilne, imodpt, istor, iowr;
} luout_;

#define luout_1 luout_

struct {
    doublereal olaol[64896]	/* was [12][104][52] */, oxa[12], ot[52], 
	    orho[104], tollaol;
    integer iolaol, numofxyz, numrho, numt;
    logical llaol, lpurez;
    integer iopurez;
    char flaol[256], fpurez[256];
} nwlaol_;

#define nwlaol_1 nwlaol_

struct {
    doublereal tridt, tridl, senv0;
    logical lsenv0, lnew0;
} cenv_;

#define cenv_1 cenv_

struct {
    doublereal rescal[200]	/* was [4][50] */;
    integer nmodls[50], iresca[50];
    logical lfirst[50];
    integer numrun;
} ckind_;

#define ckind_1 ckind_

struct {
    doublereal xenv, zenv, zenvm, amuenv, fxenv[12], xnew, znew, stotal, senv;
} comp_;

#define comp_1 comp_

struct {
    doublereal yenv, y3env;
} comp2_;

#define comp2_1 comp2_

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
    doublereal ep, et, er, es, ed, eo, ebeta, edel[3], efxion[3], evel;
} envprt_;

#define envprt_1 envprt_

struct {
    logical lexcom;
} flag_;

#define flag_1 flag_

struct {
    logical lkuthe;
} heflsh_;

#define heflsh_1 heflsh_

struct {
    doublereal hpo[5000], hto[5000], hro[5000], hlo[5000], hdo[5000], hcompp[
	    75000]	/* was [15][5000] */, hss[5000];
    logical lco[5000], lczo[5000];
} oldmod_;

#define oldmod_1 oldmod_

struct {
    doublereal wold[5000], hjx[5000], hio[5000], hgo[5000], r0x[5000], eta2x[
	    5000];
} oldrot_;

#define oldrot_1 oldrot_

struct {
    doublereal optol, zsi;
    integer idt, idd[4];
} optab_;

#define optab_1 optab_

struct {
    doublereal wnew, walpcz, acfpft;
    integer itfp1, itfp2;
    logical lrot, linstb, lwnew;
} rot_;

#define rot_1 rot_

struct {
    logical lmhd;
    integer iomhd1, iomhd2, iomhd3, iomhd4, iomhd5, iomhd6, iomhd7, iomhd8;
} mhd_;

#define mhd_1 mhd_

struct {
    logical lcore;
    integer mcore;
    doublereal fcore;
} core_;

#define core_1 core_

struct {
    doublereal cdh, etadh0, etadh1, zdh[18], xxdh, yydh, zzdh, dhnue[18];
    logical ldh;
} debhu_;

#define debhu_1 debhu_

struct {
    doublereal dpenv, alphac, alphae, alpham;
    integer iov1, iov2, iovim;
    logical lovstc, lovste, lovstm, lsemic, ladov;
} dpmix_;

#define dpmix_1 dpmix_

struct {
    doublereal zlaol1, zlaol2, zopal1, zopal2, zopal951, zalex1, zkur1, zkur2,
	     tmolmin, tmolmax;
    logical lalex06, llaol89, lopal92, lopal95, lkur90, lalex95, l2z;
} newopac_;

#define newopac_1 newopac_

struct {
    char opecalex[1792];
    integer ialxo;
} alexo_;

#define alexo_1 alexo_

struct {
    doublereal xalex, zalex;
} alexmix_;

#define alexmix_1 alexmix_

struct {
    doublereal vnew[12];
} vnewcb_;

#define vnewcb_1 vnewcb_

struct {
    doublereal tlogx[63], tablex[57456]	/* was [63][76][12] */, tabley[57456]	
	    /* was [63][76][12] */, smix[4788]	/* was [63][76] */, tablez[
	    62244]	/* was [63][76][13] */, tablenv[57456]	/* was [63][
	    76][12] */;
    integer nptsx[63];
    logical lscv;
    integer idtt, idp;
} scveos_;

#define scveos_1 scveos_

struct {
    doublereal htoler[10]	/* was [5][2] */, fcorr0, fcorri, fcorr, 
	    hpttol[12];
    integer niter1, niter2, niter3;
} ctol_;

#define ctol_1 ctol_

struct {
    doublereal enverr, envbeg, envmin, envmax;
} intenv_;

#define intenv_1 intenv_

struct {
    doublereal envp[5000], envt[5000], envs[5000], envd[5000], envr[5000], 
	    envx[5000], envz[5000];
    logical lcenv[5000];
    integer numenv;
} envstruct_;

#define envstruct_1 envstruct_

struct {
    char compmix[4];
} i2o_;

#define i2o_1 i2o_

/* Table of constant values */

static integer c__1 = 1;
static integer c__5000 = 5000;
static doublereal c_b63 = 10.;



/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */
/* STARIN */
/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */
/* Subroutine */ int starin_(doublereal *bl, doublereal *cfenv, doublereal *
	dage, doublereal *ddage, doublereal *delts, doublereal *deltsh, 
	doublereal *delts0, doublereal *eta2, doublereal *fp, doublereal *ft, 
	doublereal *ftri, doublereal *hcomp, doublereal *hd, doublereal *hi, 
	doublereal *hjm, doublereal *hkerot, doublereal *hl, doublereal *hp, 
	doublereal *hr, doublereal *hs, doublereal *hs1, doublereal *hs2, 
	doublereal *hstot, doublereal *ht, integer *ikut, integer *istore, 
	integer *jcore, integer *jenv, logical *large, logical *lc, logical *
	lnew, integer *m, integer *model, integer *nk, doublereal *omega, 
	doublereal *ps, doublereal *qdp, doublereal *qdt, doublereal *qiw, 
	doublereal *r0, doublereal *rs, doublereal *sjtot, doublereal *skerot,
	 doublereal *smass, doublereal *teffl, doublereal *tlumx, doublereal *
	tril, doublereal *trit, doublereal *ts, doublereal *vel, doublereal *
	hg, doublereal *v)
{
    /* Initialized data */

    static doublereal atomwt[12] = { 23.,26.99,24.32,55.86,28.1,12.015,1.008,
	    16.,14.01,39.96,20.19,4.004 };

    /* Format strings */
    static char fmt_1000[] = "(1x,39(\002>\002),40(\002<\002)/,\002STARIN:  "
	    "      ***** RUN STOPPED *****\002)";
    static char fmt_1010[] = "(\002STARIN: ***** MODEL FAILED TO CONVERGE **"
	    "***\002)";
    static char fmt_10[] = "(a4)";
    static char fmt_12[] = "(\002STARIN:  Input model has YREC7 format\002)";
    static char fmt_16[] = "(\002STARIN:  Input model has MODEL2 format\002)";
    static char fmt_20[] = "(\002STARIN: ***** RUN TERMINATED, INVALID INPU"
	    "T\002,\002 MODEL FILE.  *****\002)";
    static char fmt_1040[] = "(1x,\002ERROR IN SUBROUTINE STARIN\002/1x,\002"
	    "USER PARAMETERS\002,\002 OF WRONG TYPE FOR INITIAL MODEL\002/1x"
	    ",\002MIXING LENGTH - USER\002,\002 DESIRES\002,f7.3,\002 MODEL M"
	    "IX LENGTH\002,f7.3/1x,\002EXTENDED COMP-USER DESIRES \002,l1,"
	    "\002 MODEL USED \002,l1)";
    static char fmt_476[] = "(2a)";
    static char fmt_477[] = "(a,i8,a,i8)";
    static char fmt_478[] = "(a)";
    static char fmt_576[] = "(5x,\002ERROR IN SUBROUTINE STARIN\002/5x,\002D"
	    "ESIRED\002,\002 ENVELOPE MASS\002,1pe22.13,\002 TOO LARGE\002/5x,"
	    "\002ENVELOPE\002,\002 MASS NOT CHANGED\002)";
    static char fmt_910[] = "(1x,\002NEW INTERIOR POINTS FROM CHANGE IN ENVE"
	    "LOPE MASS\002/\002 J,LOG RHO, LOG L, LOG P, LOG R, LOG M, LOG T,"
	    " CONV T/F\002)";
    static char fmt_911[] = "(i5,1p6e16.8,l2)";
    static char fmt_597[] = "(5x,\002***** NEW ENVELOPE MASS CALCULATED **"
	    "***\002/8x,\002OLD SENV \002,1pe22.13,\002  NEW SENV\002,e22.13)";
    static char fmt_560[] = "(1x,\002TOTAL J OF STAR - PREVIOUS \002,1pe21.1"
	    "3,\002 NEW \002,1pe21.13/1x,\002TOTAL ROTATIONAL K.E. OF STAR - "
	    "PREVIOUS \002,1pe21.13,\002 NEW \002,1pe21.13)";

    /* System generated locals */
    integer i__1, i__2;
    doublereal d__1;
    alist al__1;

    /* Builtin functions */
    integer s_wsfe(cilist *), e_wsfe(void);
    /* Subroutine */ int s_stop(char *, ftnlen);
    integer f_rew(alist *), s_rsfe(cilist *), do_fio(integer *, char *, 
	    ftnlen), e_rsfe(void), s_cmp(char *, char *, ftnlen, ftnlen);
    double d_lg10(doublereal *), exp(doublereal), pow_dd(doublereal *, 
	    doublereal *);

    /* Local variables */
    extern /* Subroutine */ int getyrec7_(doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, integer *,
	     integer *, integer *, integer *, logical *, logical *, logical *,
	     integer *, integer *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, char *, char *, char *, logical *, 
	    logical *, logical *, logical *, logical *, char *, logical *, 
	    logical *, logical *, logical *, logical *, char *, doublereal *, 
	    doublereal *, doublereal *, ftnlen, ftnlen, ftnlen, ftnlen, 
	    ftnlen), surfopac_(doublereal *), getmodel2_(doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, integer *, integer *, integer *, integer *, logical 
	    *, logical *, logical *, integer *, integer *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, char *, 
	    char *, char *, logical *, logical *, logical *, logical *, 
	    logical *, char *, logical *, logical *, logical *, logical *, 
	    logical *, char *, doublereal *, doublereal *, doublereal *, 
	    ftnlen, ftnlen, ftnlen, ftnlen, ftnlen);
    static doublereal b, d__;
    static integer i__, j, k;
    static doublereal o, p, t, x, z__, x0, x1, x2, dd, dl, gl;
    static integer mn;
    static doublereal ds, pp, pl, tl, fs, rl, sl;
    static integer kk;
    static doublereal ol;
    static integer mm;
    static doublereal dp, dt, dr;
    static integer jm;
    static doublereal fx, hj, fv, ds1, ds2, ds3;
    static integer mp1;
    static doublereal del, hlc, eta;
    static char hik[4], atm[4], lok[4], eos[6];
    static doublereal fpl, ftl, rmu, amu, emu, qcp, qat, qap, qod, qot;
    static integer ixx;
    static doublereal dum1[4], dum2[3], dum3[3], dum4[3], dela, beta;
    static integer jend;
    static doublereal delr, qact, qacp, qacr, rhoc;
    static integer katm, idum, jenv0;
    static doublereal temp, qdtt, qdtp, wmax0, qcpt, qcpp, senv1;
    static logical lrot0;
    static doublereal emax0, emin0, ebeg0;
    static logical lsbc0, lprt;
    static integer kenv;
    static doublereal plim;
    extern /* Subroutine */ int fpft_(doublereal *, doublereal *, doublereal *
	    , integer *, doublereal *, doublereal *, doublereal *, doublereal 
	    *, doublereal *, doublereal *), momi_(doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, integer *, integer *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, integer *)
	    ;
    static doublereal sumj, vsum, beta14;
    static integer iread;
    static doublereal betai;
    static integer ksaha;
    static char atemp[4];
    static doublereal fxion[3];
    static integer jcore0;
    static doublereal cmixl0;
    static logical ldify0, ldifz0, ldisk0;
    static doublereal pdisk0, tdisk0;
    static logical lmixl, lexcp0, latmo;
    static doublereal hsend;
    extern /* Subroutine */ int meqos_(doublereal *, doublereal *, doublereal 
	    *, doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, logical *, logical *, 
	    integer *);
    static logical lconv;
    static doublereal sumke;
    extern /* Subroutine */ int rscale_(doublereal *, doublereal *, 
	    doublereal *, doublereal *, integer *, integer *, doublereal *, 
	    logical *);
    static logical lexcom0, linstb0, ljdot00, lsemic0, lderiv, locond;
    extern /* Subroutine */ int eqstat_(doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, logical *,
	     logical *, integer *), tpgrad_(doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, logical *, logical *, doublereal *, doublereal *);
    static logical lpulpt;
    extern /* Subroutine */ int envint_(doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, integer *, logical *, 
	    logical *, doublereal *, doublereal *, doublereal *, doublereal *,
	     doublereal *, doublereal *, integer *, integer *, integer *, 
	    integer *, doublereal *, doublereal *, doublereal *, logical *), 
	    setscv_(void);
    static logical lovstc0, lovste0, lpurez0, lovstm0;
    extern /* Subroutine */ int getopac_(doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *);

    /* Fortran I/O blocks */
    static cilist io___2 = { 0, 0, 0, fmt_1000, 0 };
    static cilist io___3 = { 0, 0, 0, fmt_1010, 0 };
    static cilist io___5 = { 0, 0, 0, fmt_10, 0 };
    static cilist io___7 = { 0, 0, 0, fmt_12, 0 };
    static cilist io___30 = { 0, 0, 0, fmt_16, 0 };
    static cilist io___31 = { 0, 0, 0, fmt_20, 0 };
    static cilist io___33 = { 0, 0, 0, fmt_1040, 0 };
    static cilist io___35 = { 0, 0, 0, fmt_1040, 0 };
    static cilist io___38 = { 0, 0, 0, fmt_476, 0 };
    static cilist io___39 = { 0, 0, 0, fmt_477, 0 };
    static cilist io___40 = { 0, 0, 0, fmt_478, 0 };
    static cilist io___82 = { 0, 0, 0, fmt_576, 0 };
    static cilist io___124 = { 0, 6, 0, fmt_910, 0 };
    static cilist io___125 = { 0, 6, 0, fmt_911, 0 };
    static cilist io___126 = { 0, 0, 0, fmt_597, 0 };
    static cilist io___133 = { 0, 0, 0, fmt_560, 0 };


/* DBGLAOL */
/* DBGLAOL */
/* DBG 7/92 COMMON BLOCK ADDED TO COMPUTE DEBYE-HUCKEL CORRECTION. */
/* OPACITY COMMON BLOCKS - modified 3/09 */
/* DBG 1/96 VNEW REPLACES V */
/* MHP  5/97 ADDED COMMON BLOCK FOR SCV EOS TABLES */
/* MHP 10/98 ADDED HPTTOL FOR CHANGING CORE FITTING POINT */
/* MHP 07/02 ADDED FOR ENVELOPE INTEGRATION WHEN CHANGING THE */
/* OUTER FITTING POINT */
/* MHP 07/02 STORE CONTENTS OF ENVELOPE INTEGRATION INTO A */
/* SET OF VECTORS, WHICH ARE FLIPPED AND CONVERTED INTO AN ASCENDING */
/* SERIES AFTER THE INTEGRATION IS DONE. */
/* LLP  3/19/03 Add COMMON block /I2O/ for info directly transferred from */
/*      input to output model - starting with a code for th initial model */
/*      compostion (COMPMIX) */
    /* Parameter adjustments */
    --v;
    --hg;
    --ts;
    --trit;
    --tril;
    --tlumx;
    --rs;
    --r0;
    --qiw;
    --ps;
    --omega;
    --lc;
    --ht;
    --hs2;
    --hs1;
    --hs;
    --hr;
    --hp;
    --hl;
    --hkerot;
    --hjm;
    --hi;
    --hd;
    hcomp -= 16;
    --ft;
    --fp;
    --eta2;
    --cfenv;

    /* Function Body */
/* If flag LARGE is set, model has failed to converge.  Terminate the run. */
    if (*large) {
	io___2.ciunit = luout_1.ishort;
	s_wsfe(&io___2);
	e_wsfe();
	io___3.ciunit = luout_1.ishort;
	s_wsfe(&io___3);
	e_wsfe();
	s_stop("", (ftnlen)0);
    }
/* THIS SUBROUTINE READS IN THE INITIAL STELLAR MODEL */
/* INITIAL MODEL IS STORED IN LOGICAL UNIT IFIRST */
/* Set flags for reading an input model */
    *ikut = 0;
    iread = lunum_1.ifirst;
/* INITIALIZE VARIABLES */
    *vel = 0.;
    *qdt = -1.;
    *qdp = 1.;
/* Flag LFIRST(NK) tells where to get the starting stellar model for the current */
/* step (step NK).  If LFIRST(NK) is true, read in the starting stellarmodel from */
/* the file specified by LU IFIRST.  If LFIRST(NK) is false, as starting model use */
/* the stellar model currently stored in memory. */
    if (! ckind_1.lfirst[*nk - 1]) {
/* Use the model currently in memory as the starting model. */
/* DBG 2/92 CHANGED SO WILL RESCALE ENVELOPE MASS ON EACH NEW RUN */
	if (ckind_1.iresca[*nk - 1] != 1) {
	    rscale_(&hl[1], &hcomp[16], &hs[1], hstot, m, nk, smass, &lc[1]);
	}
/* Now skip over the reading and processing of an input model file */
	goto L3000;
    }
/*     Read in the starting model from LU IFIRST and process it. */
/*  Get file format of input model */
    al__1.aerr = 0;
    al__1.aunit = iread;
    f_rew(&al__1);
    io___5.ciunit = iread;
    s_rsfe(&io___5);
    do_fio(&c__1, atemp, (ftnlen)4);
    e_rsfe();
/* ATEMP now contains a keyword describing the format of the input stellar */
/* model.  We decide what kind of model format it has and process accordingly. */
    if (s_cmp(atemp, "NMOD", (ftnlen)4, (ftnlen)4) == 0) {
	io___7.ciunit = luout_1.ishort;
	s_wsfe(&io___7);
	e_wsfe();
	getyrec7_(bl, &cfenv[1], &cmixl0, dage, ddage, ftri, &hcomp[16], &hd[
		1], &hl[1], &hp[1], &hr[1], &hs[1], hstot, &ht[1], &iread, &
		luout_1.ishort, &jcore0, &jenv0, &lc[1], &lexcom0, &lrot0, m, 
		model, &omega[1], &ps[1], &rs[1], smass, teffl, &tlumx[1], &
		tril[1], &trit[1], &ts[1], atm, eos, hik, &ldify0, &ldifz0, &
		ldisk0, &linstb0, &ljdot00, lok, &lovstc0, &lovste0, &lovstm0,
		 &lpurez0, &lsemic0, i2o_1.compmix, &pdisk0, &tdisk0, &wmax0, 
		(ftnlen)4, (ftnlen)6, (ftnlen)4, (ftnlen)4, (ftnlen)4);
/* First three lines above are YREC7 inputs */
/* Last three lines are MODEL2 add-ons */
    } else if (s_cmp(atemp, "MOD2 ", (ftnlen)4, (ftnlen)5) == 0) {
	io___30.ciunit = luout_1.ishort;
	s_wsfe(&io___30);
	e_wsfe();
	getmodel2_(bl, &cfenv[1], &cmixl0, dage, ddage, ftri, &hcomp[16], &hd[
		1], &hl[1], &hp[1], &hr[1], &hs[1], hstot, &ht[1], &iread, &
		luout_1.ishort, &jcore0, &jenv0, &lc[1], &lexcom0, &lrot0, m, 
		model, &omega[1], &ps[1], &rs[1], smass, teffl, &tlumx[1], &
		tril[1], &trit[1], &ts[1], atm, eos, hik, &ldify0, &ldifz0, &
		ldisk0, &linstb0, &ljdot00, lok, &lovstc0, &lovste0, &lovstm0,
		 &lpurez0, &lsemic0, i2o_1.compmix, &pdisk0, &tdisk0, &wmax0, 
		(ftnlen)4, (ftnlen)6, (ftnlen)4, (ftnlen)4, (ftnlen)4);
/* First three lines above are YREC7 inputs */
/* Last three lines are MODEL2 add-ons */
    } else {
	io___31.ciunit = luout_1.ishort;
	s_wsfe(&io___31);
	e_wsfe();
	s_stop("", (ftnlen)0);
    }
/* Model has now been read in. Some post-processing is required. */
    *delts = const3_1.csecyr * *ddage;
    *deltsh = abs(*delts);
    comp_1.stotal = *hstot;
/* CHECK TO ENSURE THAT MIX LENGTH, SURFACE B.C. AND CONVECTION ZONE */
/* THEORY OF THE MODEL ARE THE SAME AS USER PARAMETERS */
/* CHECKED ONLY FOR EVOLVED MODELS(MODEL NUMBER > 0) */
/* 1/92 Changed to not stop just give warning. */
    if (*model > 0) {
	lmixl = TRUE_;
/* Jan 12, 1989 : in STARIN changed test to see if model has correct mixing */
/* length from 1.0e-6 to 2.0e-3 because models only store */
/* mixing length to four sig digits. */
	if (cmixl0 > 0.) {
	    lmixl = (d__1 = const3_1.cmixl - cmixl0, abs(d__1)) < .002;
	}
/* MHP 9/03 FIXED TYPO */
	if ((! lmixl || lexcom0) != flag_1.lexcom) {
	    io___33.ciunit = luout_1.ishort;
	    s_wsfe(&io___33);
	    do_fio(&c__1, (char *)&const3_1.cmixl, (ftnlen)sizeof(doublereal))
		    ;
	    do_fio(&c__1, (char *)&cmixl0, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&flag_1.lexcom, (ftnlen)sizeof(logical));
	    do_fio(&c__1, (char *)&lexcp0, (ftnlen)sizeof(logical));
	    e_wsfe();
	    io___35.ciunit = luout_1.iowr;
	    s_wsfe(&io___35);
	    do_fio(&c__1, (char *)&const3_1.cmixl, (ftnlen)sizeof(doublereal))
		    ;
	    do_fio(&c__1, (char *)&cmixl0, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&flag_1.lexcom, (ftnlen)sizeof(logical));
	    do_fio(&c__1, (char *)&lexcp0, (ftnlen)sizeof(logical));
	    e_wsfe();
/* =>RUN STOPPED DUE TO INCONSISTENCY BETWEEN MODEL AND RUN PARMS */
/*            STOP */
	}
    }
/* ENVELOPE DATA (Now bypassed) */
/* LNEW0 HAS BEEN READ IN, IF TRUE THEN RECOMPUTE ENVELOPE EVERY MODEL */
/* STORED ENVELOPE RECORDS ONLY USED FOR HE FLASH CALCS */
/*      IF(LNEW0) THEN */
/* 	 LNEW = .TRUE. */
/*      ELSE */
/* 	 LNEW = .NOT.LKUTHE */
/*      ENDIF */
/*      DO 80 I = 1,3 */
/* 	 IF((.NOT.LNEW).AND.IABS(IO).NE.I) LNEW = .TRUE. */
/* 80   CONTINUE */
    *istore = 0;
    *ftri = 1.;
/* Require recompute of envelope. No assurance of reliable */
/* input triangle */
    *lnew = TRUE_;
/* GET XNEW AND ZNEW FROM HENYEY POINTS */
    comp_1.xnew = hcomp[*m * 15 + 1];
    comp_1.znew = hcomp[*m * 15 + 3];
/* FOURTH PART:  - LOG J/M STORED */
    if (rot_1.lrot) {
	if (rot_1.lwnew) {
/* GENERATE A SOLID BODY ROTATION CURVE WITH OMEGA = WNEW; */
/* THIS IS DONE TO CONVERT A NON-ROTATING MODEL TO A ROTATING ONE. */
	    i__1 = *m;
	    for (i__ = 1; i__ <= i__1; ++i__) {
		omega[i__] = rot_1.wnew;
/* L540: */
	    }
	}
    } else {
	for (i__ = 1; i__ <= 5000; ++i__) {
	    fp[i__] = 1.;
	    ft[i__] = 1.;
/* L570: */
	}
    }
/* KEEP IREAD OPEN */
    al__1.aerr = 0;
    al__1.aunit = iread;
    f_rew(&al__1);
/* End of the reading and processing of an input model file. */
L3000:
/*     The following code enables us to extend the model from the current */
/*     inner most shell to a point ncloser to center, if flag LCORE is set. */
/* 9/98 MHP REPLACE AS FOLLOWS: */
/* ADD INTEGER NUMBER OF POINTS USING THE DESIRED SPACING IN MASS,HPTTOL. */
/* USE STELLAR STRUCTURE EQUATIONS CONSISTENT WITH THE ASSUMPTIONS */
/* IN THE MODEL, NAMELY CONSTANT ENERGY GENERATION RATE AND DENSITY */
/* INTERIOR TO THE LOCATION OF THE CENTRAL FITTING POINT. */
    if (core_1.lcore && *nk == 1) {
/* AVOID SHUFFLING POINTS BY ASSIGNING NEW CENTRAL POINTS IN INTEGER */
/* MULTIPLES OF THE CENTRAL POINT SPACING. */
/*     MCORE is number of shells to extrapolate to new core. */
/*     FCORE is factor to reduce inner mass shell. */
	core_1.mcore = (integer) (d_lg10(&core_1.fcore) / ctol_1.hpttol[1]) + 
		1;
	core_1.fcore = (doublereal) core_1.mcore * ctol_1.hpttol[1];
	mn = *m + core_1.mcore;
	if (mn > 5000) {
	    io___38.ciunit = luout_1.ishort;
	    s_wsfe(&io___38);
	    do_fio(&c__1, "STARIN: Unable to extend core inward ", (ftnlen)37)
		    ;
	    do_fio(&c__1, "- JSON too small", (ftnlen)16);
	    e_wsfe();
	    io___39.ciunit = luout_1.ishort;
	    s_wsfe(&io___39);
	    do_fio(&c__1, "STARIN: Required size =", (ftnlen)23);
	    do_fio(&c__1, (char *)&mn, (ftnlen)sizeof(integer));
	    do_fio(&c__1, ", JSON = ", (ftnlen)9);
	    do_fio(&c__1, (char *)&c__5000, (ftnlen)sizeof(integer));
	    e_wsfe();
	    io___40.ciunit = luout_1.ishort;
	    s_wsfe(&io___40);
	    do_fio(&c__1, "STARIN:  ***** RUN TERMINATED *****", (ftnlen)35);
	    e_wsfe();
	}
	ds = ctol_1.hpttol[1];
/* shift data for remaining points by the required number */
	for (i__ = *m; i__ >= 1; --i__) {
	    hs[i__ + core_1.mcore] = hs[i__];
	    hr[i__ + core_1.mcore] = hr[i__];
	    hl[i__ + core_1.mcore] = hl[i__];
	    hp[i__ + core_1.mcore] = hp[i__];
	    ht[i__ + core_1.mcore] = ht[i__];
	    lc[i__ + core_1.mcore] = lc[i__];
	    for (j = 1; j <= 15; ++j) {
		hcomp[j + (i__ + core_1.mcore) * 15] = hcomp[j + i__ * 15];
	    }
	    omega[i__ + core_1.mcore] = omega[i__];
	}
	mp1 = core_1.mcore + 1;
/* MARCH INWARD IN MASS FROM THE INNERMOST MODEL POINT. */
/* ASSUME EPSILON=CONSTANT AND DEL=CONSTANT */
	rhoc = hd[1];
	del = (ht[2] - ht[1]) / (hp[2] - hp[1]);
	hlc = hl[1];
	for (i__ = core_1.mcore; i__ >= 1; --i__) {
	    hs[i__] = hs[i__ + 1] - ds;
/* USE M  = 4PI/3*RHOC*R**3 TO GET R AS A FUNCTION OF M */
	    hr[i__] = const1_1.cc13 * (hs[i__] - const1_1.c4pi3l - rhoc);
/* USE EPSILON=CONSTANT TO GET L */
	    hl[i__] = exp(const1_1.cln * (hs[i__] - hs[mp1])) * hlc;
/* USE HYDROSTATIC EQUILIBRIUM TO GET P */
	    pp = hp[i__ + 1];
	    temp = exp(const1_1.cln * (const2_1.cgl + hs[i__] * 2. - 
		    const1_1.c4pil - pp - hr[i__] * 4.));
	    pp += temp * .5 * ds;
	    temp = exp(const1_1.cln * (const2_1.cgl + hs[i__] * 2. - 
		    const1_1.c4pil - pp - hr[i__] * 4.));
	    hp[i__] = hp[i__ + 1] + temp * ds;
/* ASSUME R/C FLAG IS THE SAME AS FOR THE FIRST POINT */
	    lc[i__] = lc[mp1];
/* ASSUME DEL= CONSTANT IN THE CORE */
	    ht[i__] = ht[i__ + 1] + temp * del * ds;
/* ASSUME OMEGA = CONSTANT */
	    omega[i__] = omega[mp1];
/* ASSUME COMPOSITION IS UNIFORM */
	    for (j = 1; j <= 15; ++j) {
		hcomp[j + i__ * 15] = hcomp[j + mp1 * 15];
	    }
/* CALL EQUATION OF STATE TO GET CONSISTENT DENSITY */
	    lderiv = FALSE_;
	    locond = FALSE_;
	    latmo = FALSE_;
	    ksaha = 0;
	    x = hcomp[i__ * 15 + 1];
	    z__ = hcomp[i__ * 15 + 3];
	    pl = hp[i__];
	    p = exp(const1_1.cln * pl);
	    tl = ht[i__];
	    t = exp(const1_1.cln * tl);
	    dl = hd[i__ + 1];
	    d__ = exp(const1_1.cln * dl);
	    fpl = 1.;
	    ftl = 1.;
	    eqstat_(&tl, &t, &pl, &p, &dl, &d__, &x, &z__, &beta, &betai, &
		    beta14, fxion, &rmu, &amu, &emu, &eta, qdt, qdp, &qcp, &
		    dela, &qdtt, &qdtp, &qat, &qap, &qcpt, &qcpp, &lderiv, &
		    latmo, &ksaha);
	    hd[i__] = dl;
	}
	*m = mn;
    }
/* End of code to extend core inward */
/* PERFORM RESCALING OF FIRST MODEL IF REQUIRED */
    if (ckind_1.iresca[*nk - 1] != 1) {
	rscale_(&hl[1], &hcomp[16], &hs[1], hstot, m, nk, smass, &lc[1]);
    }
/* What is the metallicity of your model? (surface X and Z) */
/* put in SETUPOPAC here, and take out of setups. */
/* DBG 2/92 CHANGED SO THAT WORKS ON FIRST MODEL OF EACH NEW RUN */
/* CHANGE FITTING POINT OF THE ENVELOPE INTEGRATION IF REQUESTED; */
/* PROCEDURE IS: */
/* IF THE REQUESTED ENVELOPE MASS(SENV0) IS GREATER THAN THE */
/* CURRENT ONE, DELETE POINTS UNTIL THE MASS IS EQUAL. */
/* LINEAR INTERPOLATION BETWEEN THE LAST POINT ABOVE THE FITTING */
/* MASS AND THE FIRST POINT BELOW IT IS USED;COMPOSITION IS */
/* ASSUMED EQUAL TO THE LAST OLD POINT BELOW THE NEW FITTING POINT. */
/* IF THE REQUESTED ENVELOPE MASS IS SMALLER THAN THE CURRENT ONE, */
/* AN ENVELOPE WITH TEFF AND L EQUAL TO THE STORED MODEL VALUE */
/* IS INTEGRATED FROM THE SURFACE TO THE DESIRED FITTING POINT. */
/* 1 NEW POINT IS ADDED, AND THE COMPOSITION OF THE NEW POINT */
/* IS ASSUMED EQUAL TO THAT OF THE LAST OLD POINT. */
    if (cenv_1.lsenv0) {
	if (cenv_1.senv0 > 0.) {
	    cenv_1.senv0 = -cenv_1.senv0;
	}
/* DBG 2/92 CHANGED MINIMUM FROM 1.0D-10 TO 1.0D-12 */
/* RESTRICT MIMIMUM ENVELOPE MASS;1.0D-12 CORRESPONDS TO TAU=2/3 */
/* FOR THIS PURPOSE(BASE OF ATMOSPHERE). */
	if (cenv_1.senv0 > -1e-12) {
	    cenv_1.senv0 = -1e-12;
	}
	comp_1.senv = hs[*m] - *hstot;
	senv1 = comp_1.senv;
	if (comp_1.senv == cenv_1.senv0) {
	    goto L599;
	}
	jend = 11;
	if (flag_1.lexcom) {
	    jend = 15;
	}
	if (cenv_1.senv0 < comp_1.senv) {
/* NEW ENVELOPE DEEPER THAN THE OLD ONE */
	    hsend = *hstot + cenv_1.senv0;
	    for (i__ = *m - 1; i__ >= 1; --i__) {
		if (hs[i__] < hsend) {
		    goto L580;
		}
/* L575: */
	    }
/* ENVELOPE MASS DESIRED WITHIN FIRST POINT;PRINT NASTY MESSAGE */
/* AND ABORT. */
	    io___82.ciunit = luout_1.ishort;
	    s_wsfe(&io___82);
	    do_fio(&c__1, (char *)&cenv_1.senv0, (ftnlen)sizeof(doublereal));
	    e_wsfe();
	    goto L599;
L580:
	    *m = i__ + 1;
	    comp_1.senv = cenv_1.senv0;
	    fs = (hsend - hs[i__]) / (hs[i__ + 1] - hs[i__]);
	    hs[*m] = hsend;
	    hd[*m] = hd[i__] + fs * (hd[i__ + 1] - hd[i__]);
	    hl[*m] = hl[i__] + fs * (hl[i__ + 1] - hl[i__]);
	    hp[*m] = hp[i__] + fs * (hp[i__ + 1] - hp[i__]);
	    hr[*m] = hr[i__] + fs * (hr[i__ + 1] - hr[i__]);
	    ht[*m] = ht[i__] + fs * (ht[i__ + 1] - ht[i__]);
	    i__1 = jend;
	    for (j = 1; j <= i__1; ++j) {
		hcomp[j + *m * 15] = hcomp[j + i__ * 15];
/* L585: */
	    }
	    comp_1.xnew = hcomp[*m * 15 + 1];
	    comp_1.znew = hcomp[*m * 15 + 3];
	    if (rot_1.lrot) {
		omega[*m] = omega[i__] + fs * (omega[i__ + 1] - omega[i__]);
	    }
	    if (lc[i__] && lc[i__ + 1]) {
		lc[*m] = TRUE_;
	    } else if (! lc[i__] && ! lc[i__ + 1]) {
		lc[*m] = FALSE_;
	    } else {
/* CALL BASIC PHYSICS ROUTINES TO DETERMINE IF THE NEW LAST SHELL IS */
/* CONVECTIVE OR RADIATIVE. */
		lderiv = FALSE_;
		locond = FALSE_;
		latmo = TRUE_;
		ksaha = 0;
		x = hcomp[*m * 15 + 1];
		z__ = hcomp[*m * 15 + 3];
		pl = hp[*m];
		tl = ht[*m];
		dl = hd[*m];
		b = hl[*m];
		rl = hr[*m];
		sl = hs[*m];
		fpl = 1.;
		ftl = 1.;
		optab_1.idt = 15;
		for (kk = 1; kk <= 4; ++kk) {
		    optab_1.idd[kk - 1] = 5;
/* L588: */
		}
		if (mhd_1.lmhd) {
		    meqos_(&tl, &t, &pl, &p, &dl, &d__, &x, &z__, &beta, &
			    betai, &beta14, fxion, &rmu, &amu, &emu, &eta, 
			    qdt, qdp, &qcp, &dela, &qdtt, &qdtp, &qat, &qap, &
			    qcpt, &qcpp, &lderiv, &latmo, &ksaha);
		} else {
		    if (debhu_1.ldh) {
			debhu_1.xxdh = hcomp[*m * 15 + 1];
			debhu_1.yydh = hcomp[*m * 15 + 2] + hcomp[*m * 15 + 4]
				;
			debhu_1.zzdh = hcomp[*m * 15 + 3];
			debhu_1.zdh[0] = hcomp[*m * 15 + 5] + hcomp[*m * 15 + 
				6];
			debhu_1.zdh[1] = hcomp[*m * 15 + 7] + hcomp[*m * 15 + 
				8];
			debhu_1.zdh[2] = hcomp[*m * 15 + 9] + hcomp[*m * 15 + 
				10] + hcomp[*m * 15 + 11];
		    }
		    eqstat_(&tl, &t, &pl, &p, &dl, &d__, &x, &z__, &beta, &
			    betai, &beta14, fxion, &rmu, &amu, &emu, &eta, 
			    qdt, qdp, &qcp, &dela, &qdtt, &qdtp, &qat, &qap, &
			    qcpt, &qcpp, &lderiv, &latmo, &ksaha);
		}
		getopac_(&dl, &tl, &x, &z__, &o, &ol, &qod, &qot, fxion);
		dpmix_1.iovim = -1;
		tpgrad_(&tl, &t, &pl, &p, &d__, &rl, &sl, &b, &o, qdt, qdp, &
			qot, &qod, &qcp, &del, &delr, &dela, &qdtt, &qdtp, &
			qat, &qap, &qact, &qacp, &qacr, &qcpt, &qcpp, vel, &
			lderiv, &lconv, &fpl, &ftl);
		hd[*m] = dl;
		lc[*m] = lconv;
	    }
	} else {
/* DESIRED ENVELOPE MASS LESS THAN CURRENT VALUE. */
	    mm = *m;
	    emax0 = intenv_1.envmax;
	    emin0 = intenv_1.envmin;
	    ebeg0 = intenv_1.envbeg;
	    intenv_1.envmax = ctol_1.hpttol[7];
	    intenv_1.envmin = ctol_1.hpttol[7];
	    intenv_1.envbeg = ctol_1.hpttol[7];
/* 	    SENV = SENV0 */
	    lsbc0 = FALSE_;
	    lprt = TRUE_;
	    katm = 0;
	    kenv = 0;
	    ksaha = 0;
	    b = exp(const1_1.cln * *bl);
	    rl = (*bl + const_1.clsunl - *teffl * 4. - const1_1.c4pil - 
		    const2_1.csigl) * .5;
	    gl = const2_1.cgl + comp_1.stotal - rl - rl;
	    x = hcomp[*m * 15 + 1];
	    z__ = hcomp[*m * 15 + 3];
	    fpl = 1.;
	    ftl = 1.;
	    ixx = 0;
	    plim = hp[*m];
/* DBG PULSE: DO NOT DO PULSE OUTPUT */
	    lpulpt = FALSE_;
	    if (debhu_1.ldh) {
		debhu_1.xxdh = hcomp[*m * 15 + 1];
		debhu_1.yydh = hcomp[*m * 15 + 2] + hcomp[*m * 15 + 4];
		debhu_1.zzdh = hcomp[*m * 15 + 3];
		debhu_1.zdh[0] = hcomp[*m * 15 + 5] + hcomp[*m * 15 + 6];
		debhu_1.zdh[1] = hcomp[*m * 15 + 7] + hcomp[*m * 15 + 8];
		debhu_1.zdh[2] = hcomp[*m * 15 + 9] + hcomp[*m * 15 + 10] + 
			hcomp[*m * 15 + 11];
	    }
/* MHP 10/02  define ISTORE - used in ENVINT */
	    idum = 0;
	    envint_(&b, &fpl, &ftl, &gl, hstot, &ixx, &lprt, &lsbc0, &plim, &
		    rl, teffl, &x, &z__, dum1, &idum, &katm, &kenv, &ksaha, 
		    dum2, dum3, dum4, &lpulpt);
	    intenv_1.envmax = emax0;
	    intenv_1.envmin = emin0;
	    intenv_1.envbeg = ebeg0;
	    comp_1.senv = cenv_1.senv0;
	    if (*m + envstruct_1.numenv >= 5000) {
		s_stop("9999", (ftnlen)4);
	    }
/* ENFORCE CONSISTENCY WITH THE INTERIOR SOLUTION; */
/* ADJUST THE (P, RHO, T, R) POINTS TO BE CONSISTENT */
/* WITH THE LAST MODEL POINT. */
	    dp = hp[*m] - envstruct_1.envp[0];
	    dd = hd[*m] - envstruct_1.envd[0];
	    dt = ht[*m] - envstruct_1.envt[0];
	    dr = hr[*m] - envstruct_1.envr[0];
	    i__1 = envstruct_1.numenv - 1;
	    for (j = 1; j <= i__1; ++j) {
		envstruct_1.envd[j - 1] = envstruct_1.envd[j] + dd;
		envstruct_1.envp[j - 1] = envstruct_1.envp[j] + dp;
		envstruct_1.envr[j - 1] = envstruct_1.envr[j] + dr;
		envstruct_1.envs[j - 1] = envstruct_1.envs[j];
		envstruct_1.envt[j - 1] = envstruct_1.envt[j] + dt;
		envstruct_1.envx[j - 1] = envstruct_1.envx[j];
		envstruct_1.envz[j - 1] = envstruct_1.envz[j];
	    }
	    --envstruct_1.numenv;
	    i__1 = *m + envstruct_1.numenv;
	    for (j = *m + 1; j <= i__1; ++j) {
		jm = j - *m;
/* LUMINOSITY ASSUMED CONSTANT */
		hl[j] = hl[*m];
/* INCLUDE NEW POINTS UP TO THE DIFFERENT DESIRED FITTING POINT */
		if (envstruct_1.envs[jm - 1] <= comp_1.senv) {
		    hd[j] = envstruct_1.envd[jm - 1];
		    hp[j] = envstruct_1.envp[jm - 1];
		    hr[j] = envstruct_1.envr[jm - 1];
		    hs[j] = envstruct_1.envs[jm - 1] + comp_1.stotal;
		    ht[j] = envstruct_1.envt[jm - 1];
		    hcomp[j * 15 + 1] = envstruct_1.envx[jm - 1];
		    hcomp[j * 15 + 3] = envstruct_1.envz[jm - 1];
		    i__2 = jend;
		    for (k = 4; k <= i__2; ++k) {
			hcomp[k + j * 15] = hcomp[k + *m * 15];
		    }
		    hcomp[j * 15 + 2] = 1. - hcomp[j * 15 + 1] - hcomp[j * 15 
			    + 3] - hcomp[j * 15 + 4];
		    lc[j] = envstruct_1.lcenv[jm - 1];
		} else {
/* POINTS BEYOND THIS ARE ABOVE THE NEW DESIRED FITTING POINT; */
/* INTERPOLATE LINEARLY, SET NEW NUMBER OF TOTAL POINTS, AND EXIT */
		    if (jm == 1) {
/* INTERPOLATE BETWEEN THE LAST INTERIOR POINT AND THE FIRST ENVELOPE POINT */
			x0 = hs[*m];
			x1 = comp_1.stotal + comp_1.senv;
			x2 = envstruct_1.envs[jm - 1] + comp_1.stotal;
			if (x2 - x0 < 1e-14) {
			    s_stop("9998", (ftnlen)4);
			}
			fx = (x1 - x0) / (x2 - x0);
			hd[j] = hd[*m] + fx * (envstruct_1.envd[jm - 1] - hd[*
				m]);
			hp[j] = hp[*m] + fx * (envstruct_1.envp[jm - 1] - hp[*
				m]);
			hr[j] = hr[*m] + fx * (envstruct_1.envr[jm - 1] - hr[*
				m]);
			hs[j] = x1;
			ht[j] = ht[*m] + fx * (envstruct_1.envt[jm - 1] - ht[*
				m]);
			hcomp[j * 15 + 1] = hcomp[*m * 15 + 1] + fx * (hcomp[*
				m * 15 + 1] - envstruct_1.envx[jm - 1]);
			hcomp[j * 15 + 3] = hcomp[*m * 15 + 3] + fx * (hcomp[*
				m * 15 + 3] - envstruct_1.envz[jm - 1]);
			i__2 = jend;
			for (k = 4; k <= i__2; ++k) {
			    hcomp[k + j * 15] = hcomp[k + *m * 15];
			}
			hcomp[j * 15 + 2] = 1. - hcomp[j * 15 + 1] - hcomp[j *
				 15 + 3] - hcomp[j * 15 + 4];
			if (envstruct_1.lcenv[jm - 1] || lc[*m]) {
			    lc[j] = TRUE_;
			} else {
			    lc[j] = FALSE_;
			}
		    } else {
/* INTERPOLATE BETWEEN THE LAST 2 ENVELOPE POINTS */
			x0 = envstruct_1.envs[jm - 2] + comp_1.stotal;
			x1 = comp_1.stotal + comp_1.senv;
			x2 = envstruct_1.envs[jm - 1] + comp_1.stotal;
			if (x2 - x0 < 1e-14) {
			    s_stop("9998", (ftnlen)4);
			}
			fx = (x1 - x0) / (x2 - x0);
			hd[j] = envstruct_1.envd[jm - 2] + fx * (
				envstruct_1.envd[jm - 1] - envstruct_1.envd[
				jm - 2]);
			hp[j] = envstruct_1.envp[jm - 2] + fx * (
				envstruct_1.envp[jm - 1] - envstruct_1.envp[
				jm - 2]);
			hr[j] = envstruct_1.envr[jm - 2] + fx * (
				envstruct_1.envr[jm - 1] - envstruct_1.envr[
				jm - 2]);
			hs[j] = x1;
			ht[j] = envstruct_1.envt[jm - 2] + fx * (
				envstruct_1.envt[jm - 1] - envstruct_1.envt[
				jm - 2]);
			hcomp[j * 15 + 1] = envstruct_1.envx[jm - 2] + fx * (
				envstruct_1.envx[jm - 1] - envstruct_1.envx[
				jm - 2]);
			hcomp[j * 15 + 3] = envstruct_1.envz[jm - 2] + fx * (
				envstruct_1.envz[jm - 1] - envstruct_1.envz[
				jm - 2]);
			i__2 = jend;
			for (k = 4; k <= i__2; ++k) {
			    hcomp[k + j * 15] = hcomp[k + *m * 15];
			}
			hcomp[j * 15 + 2] = 1. - hcomp[j * 15 + 1] - hcomp[j *
				 15 + 3] - hcomp[j * 15 + 4];
			if (envstruct_1.lcenv[jm - 1] || envstruct_1.lcenv[jm 
				- 2]) {
			    lc[j] = TRUE_;
			} else {
			    lc[j] = FALSE_;
			}
		    }
		    *m = j;
		    goto L587;
		}
	    }
/* ASSIGN THE BOUNDARY AT THE PHOTOSPHERE FOR ENVELOPE MASS BELOW 1.0D-12. */
	    *m += envstruct_1.numenv;
L587:
	    if (rot_1.lrot) {
		i__1 = *m;
		for (j = mm + 1; j <= i__1; ++j) {
		    omega[j] = omega[mm];
		    d__1 = hr[j] * 2.;
		    hjm[j] = const1_1.cc23 * omega[mm] * pow_dd(&c_b63, &d__1)
			    ;
		}
	    }
	    s_wsfe(&io___124);
	    e_wsfe();
	    s_wsfe(&io___125);
	    i__1 = *m;
	    for (j = mm; j <= i__1; ++j) {
		do_fio(&c__1, (char *)&j, (ftnlen)sizeof(integer));
		do_fio(&c__1, (char *)&hd[j], (ftnlen)sizeof(doublereal));
		do_fio(&c__1, (char *)&hl[j], (ftnlen)sizeof(doublereal));
		do_fio(&c__1, (char *)&hp[j], (ftnlen)sizeof(doublereal));
		do_fio(&c__1, (char *)&hr[j], (ftnlen)sizeof(doublereal));
		d__1 = hs[j] - comp_1.stotal;
		do_fio(&c__1, (char *)&d__1, (ftnlen)sizeof(doublereal));
		do_fio(&c__1, (char *)&ht[j], (ftnlen)sizeof(doublereal));
		do_fio(&c__1, (char *)&lc[j], (ftnlen)sizeof(logical));
	    }
	    e_wsfe();
/* 	    M = M + 1 */
/* 	    HS(M) = HSTOT + SENV */
/* 	    HD(M) = ED */
/* 	    HL(M) = HL(M-1) */
/* 	    HP(M) = EP */
/* 	    HR(M) = ER */
/* 	    HT(M) = ET */
/* 	    LC(M) = EVEL.GT.0.0D0 */
/* 	    DO 590 J = 1,JEND */
/* 	       HCOMP(J,M) = HCOMP(J,M-1) */
/* 590        CONTINUE */
/* 	    XNEW = HCOMP(1,M) */
/* 	    ZNEW = HCOMP(3,M) */
/* 	    IF(LROT) OMEGA(M) = OMEGA(I) + FS*(OMEGA(I+1)-OMEGA(I)) */
	}
	*lnew = TRUE_;
	io___126.ciunit = luout_1.ishort;
	s_wsfe(&io___126);
	do_fio(&c__1, (char *)&senv1, (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&comp_1.senv, (ftnlen)sizeof(doublereal));
	e_wsfe();
L599:
	;
    }
/* SET UP WEIGHTS AND MASSES */
/* HS1 IS THE UNLOGGED HS; HS2 IS THE MASS OF THE SHELL(ALSO NOT LOG). */
    ds3 = exp(const1_1.cln * hs[1]);
    ds2 = -ds3;
    i__1 = *m;
    for (i__ = 2; i__ <= i__1; ++i__) {
	ds1 = ds2;
	ds2 = ds3;
	ds3 = exp(const1_1.cln * hs[i__]);
	hs1[i__ - 1] = ds2;
	hs2[i__ - 1] = (ds3 - ds1) * .5;
/* L120: */
    }
    hs1[*m] = ds3;
    hs2[*m] = exp(const1_1.cln * *hstot) - (ds2 + ds3) * .5;
    if (rot_1.lrot) {
/* CALCULATE FP,FT,R0 AND ETA2 GIVEN OMEGA */
	fpft_(&hd[1], &hr[1], &hs[1], m, &omega[1], &eta2[1], &fp[1], &ft[1], 
		&hg[1], &r0[1]);
/* FIND MOMENT OF INERTIA(HI) */
	momi_(&eta2[1], &hd[1], &hr[1], &hs[1], &hs2[1], &c__1, m, &omega[1], 
		&r0[1], &hi[1], &qiw[1], m);
/* GIVEN OMEGA AND I, FIND ANGULAR MOMENTUM AND ROTATIONAL K.E. */
	sumj = 0.;
	sumke = 0.;
	i__1 = *m;
	for (i__ = 1; i__ <= i__1; ++i__) {
	    hj = omega[i__] * hi[i__];
	    hjm[i__] = hj / hs2[i__];
	    hkerot[i__] = omega[i__] * .5 * hj;
	    sumj += hj;
	    sumke += hkerot[i__];
/* L550: */
	}
	io___133.ciunit = luout_1.ishort;
	s_wsfe(&io___133);
	do_fio(&c__1, (char *)&(*sjtot), (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&sumj, (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&(*skerot), (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&sumke, (ftnlen)sizeof(doublereal));
	e_wsfe();
	*sjtot = sumj;
	*skerot = sumke;
    }
    if (*nk > 1) {
	goto L630;
    }
/* SET UP MASS FRACTIONS AND NUMBER FRACTIONS OF ELEMENTS IN */
/* ENVELOPE. */
/* DBG 1/96 V (ENVELOPE MASS FRACTIONS WAS NORMALLY READ IN VIA */
/* RDLAOL. NOW THAT THESE OPACITIES ARE OBSOLETE VNEW IS INTRODUCED */
/* HOLD THE RELATIVE MASS FRACTIONS OF THE ELEMENTS (SEE PARMIN). */
/* TO MAINTAIN BACKWARD COMPATIBILITY IF LLAOL=T THEN USE V READ IN */
/* VIA RDLAOL OTHERWISE USE VNEW. */
    if (! nwlaol_1.llaol) {
	for (i__ = 1; i__ <= 12; ++i__) {
	    v[i__] = vnewcb_1.vnew[i__ - 1];
	}
    }
/* COMPUTE SURFACE MIX VALUES. */
/* ZENVM = Z OTHER THAN CNO CYCLE ELEMENTS; */
/* AMUENV = MEAN ATOMIC WEIGHT OF SURFACE Z; */
/* FXENV = NUMBER DENSITY OF SPECIES . */
    comp_1.xenv = comp_1.xnew;
    comp_1.zenv = comp_1.znew;
    comp2_1.yenv = 1. - comp_1.xenv - comp_1.zenv - hcomp[*m * 15 + 4];
    comp2_1.y3env = hcomp[*m * 15 + 4];
/* EVERYTHING BUT V(7)=H, AND V(12)=HE */
    vsum = v[1] + v[2] + v[3] + v[4] + v[5] + v[6] + v[8] + v[9] + v[10] + v[
	    11];
    comp_1.zenvm = comp_1.zenv * (vsum - v[6] - v[8] - v[9]) / vsum;
    fv = comp_1.zenv / vsum;
    v[7] = comp_1.xenv / fv;
    v[12] = (1. - comp_1.xenv - comp_1.zenv) / fv;
    vsum = 0.;
    for (i__ = 1; i__ <= 12; ++i__) {
	v[i__] = fv * v[i__] / atomwt[i__ - 1];
	vsum += v[i__];
/* L610: */
    }
    comp_1.amuenv = vsum;
    fv = 1. / comp_1.amuenv;
/* DBG 1/96 FXENV ARE NUMBER FRACTIONS OF ELEMENTS REQURIED */
/* BY EOS ROUTINES (SEE EQSTAT AND EQSAHA) */
    for (i__ = 1; i__ <= 12; ++i__) {
	comp_1.fxenv[i__ - 1] = v[i__] * fv;
/* L620: */
    }
/*     FIND SURFACE COMPOSITION OPACITY TABLE */
/*     FIRST FIND INTERPOLATING FACTOR FOR COMPOSITION */
L630:
/* DBG 11/95 GENERATE NEW SURFACE OPACITY TABLES */
    surfopac_(&comp_1.xenv);
    if (scveos_1.lscv) {
	setscv_();
    }
/* CLONE P,T,R,L ARRAY TO DUMMY ARRAY HPOLD. */
/* HPOLD IS USED TO LIMIT THE TIMESTEP BASED ON CHANGES FROM */
/* MODEL TO MODEL IN P,T,R,L. */
    i__1 = *m;
    for (i__ = 1; i__ <= i__1; ++i__) {
	oldmod_1.hpo[i__ - 1] = hp[i__];
	oldmod_1.hto[i__ - 1] = ht[i__];
	oldmod_1.hro[i__ - 1] = hr[i__];
	oldmod_1.hlo[i__ - 1] = hl[i__];
/* L710: */
    }
    if (rot_1.lrot) {
	i__1 = *m;
	for (i__ = 1; i__ <= i__1; ++i__) {
	    oldrot_1.wold[i__ - 1] = omega[i__];
/* L720: */
	}
    }
    return 0;
} /* starin_ */

