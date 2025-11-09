/* main.f -- translated by f2c (version 20061008).
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
    integer itrver;
} track_;

#define track_1 track_

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
    logical ldebug, lcorr, lmilne, ltrack, lstpch;
} ccout2_;

#define ccout2_1 ccout2_

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
    doublereal cgas, ca3, ca3l, csig, csigl, cgl, cmkh, cmkhn;
} const2_;

#define const2_1 const2_

struct {
    doublereal dtdif, djok;
    integer itdif1, itdif2;
} difus_;

#define difus_1 difus_

struct {
    doublereal dpenv, alphac, alphae, alpham, betac;
    integer iov1, iov2, iovim;
    logical lovstc, lovste, lovstm, lsemic, ladov, lovmax;
} dpmix_;

#define dpmix_1 dpmix_

struct {
    doublereal pscal0, pscal1;
} liov_;

#define liov_1 liov_

struct {
    doublereal rbase0, bli6old, bli7old, bbe9old;
    integer jenvos;
} prevcz_;

#define prevcz_1 prevcz_

struct {
    doublereal clsun, clsunl, clnsun, cmsun, cmsunl, crsun, crsunl, cmbol;
} const_;

#define const_1 const_

struct {
    doublereal cdelrl, cmixl, cmixl2, cmixl3, clndp, csecyr;
} const3_;

#define const3_1 const3_

struct {
    doublereal htoler[10]	/* was [5][2] */, fcorr0, fcorri, fcorr, 
	    hpttol[12];
    integer niter1, niter2, niter3;
} ctol_;

#define ctol_1 ctol_

struct {
    doublereal wmax, exmd, exw, extau, exr, exm, exl, expr, constfactor, 
	    structfactor, excen, c_2__;
    logical ljdot0;
} cwind_;

#define cwind_1 cwind_

struct {
    logical lexcom;
} flag_;

#define flag_1 flag_

struct {
    logical lkuthe;
} heflsh_;

#define heflsh_1 heflsh_

struct {
    doublereal wnew, walpcz, acfpft;
    integer itfp1, itfp2;
    logical lrot, linstb, lwnew;
} rot_;

#define rot_1 rot_

struct {
    doublereal endage[50], setdt[50];
    logical lendag[50], lsetdt[50];
    doublereal end_dcen__[50], end_xcen__[50], end_ycen__[50];
} sett_;

#define sett_1 sett_

struct {
    integer niter4;
    logical lnews, lsnu;
} neweng_;

#define neweng_1 neweng_

struct {
    doublereal htt0[5000], hpp0[5000], hll0[5000], hrr0[5000];
} entrop_;

#define entrop_1 entrop_

struct {
    doublereal hpo[5000], hto[5000], hro[5000], hlo[5000], hdo[5000], hcompp[
	    75000]	/* was [15][5000] */, hss[5000];
    logical lco[5000], lczo[5000];
    doublereal tefflo;
    integer mo;
} oldmod_;

#define oldmod_1 oldmod_

struct {
    logical lprt0;
} rotprt_;

#define rotprt_1 rotprt_

struct {
    doublereal sage, tdisk, pdisk;
    logical ldisk;
} disk_;

#define disk_1 disk_

struct {
    doublereal xmsol;
    logical lpulse;
    integer ipver;
} pulse_;

#define pulse_1 pulse_

struct {
    doublereal hras;
    integer kttau, kttau0;
    logical lttau;
} atmos_;

#define atmos_1 atmos_

struct {
    logical lrwsh, liso;
    integer iiso;
} chrone_;

#define chrone_1 chrone_

struct {
    doublereal xenv0a[50], zenv0a[50], cmixla[50];
    logical lsenv0a[50];
    doublereal senv0a[50];
} newxym_;

#define newxym_1 newxym_

struct {
    doublereal rsclzc[50], rsclzm1[50], rsclzm2[50];
    integer iolaol2, ioopal2, nk;
    logical lzramp;
} zramp_;

#define zramp_1 zramp_

struct {
    doublereal dage;
} theage_;

#define theage_1 theage_

struct {
    doublereal hcompf[75000]	/* was [15][5000] */, hrf[5000], hpf[5000], 
	    hdf[5000], hsf[5000], htf[5000];
} stch_;

#define stch_1 stch_

struct {
    doublereal poa, pob, poc, pomax;
    logical lpout;
} po_;

#define po_1 po_

struct {
    doublereal cln, clni, c4pi, c4pil, c4pi3l, cc13, cc23, cpi;
} const1_;

#define const1_1 const1_

struct {
    doublereal dldx, drdx, dlda, drda, blp, rlp, dx, da;
    logical lsol;
} calsun_;

#define calsun_1 calsun_

struct {
    doublereal toll, tolr, tolz;
    logical lcals, lcalsolzx;
    doublereal calsolzx, calsolage;
} cals2_;

#define cals2_1 cals2_

struct {
    doublereal fgry, fgrz;
    logical lthoul, ldifz;
} gravs3_;

#define gravs3_1 gravs3_

struct {
    doublereal xls, xlstol, steff, sr, bli, alri, ager, blr, blrp, agei;
    logical lstar, lteff, lpassr, lcalst;
} calstar_;

#define calstar_1 calstar_

struct {
    doublereal gam1[5000];
    logical lsound;
} sound_;

#define sound_1 sound_

struct {
    logical lmonte;
    integer imbeg, imend;
} monte_;

#define monte_1 monte_

struct {
    doublereal flux[10], fluxtot[10], clsnu, gasnu;
} fluxes_;

#define fluxes_1 fluxes_

struct {
    doublereal sstandard[17], qs0e[8], qqs0ee[8], fo16, fc12;
    logical lnewnuc;
} cross_;

#define cross_1 cross_

struct {
    doublereal s11[1000], s33[1000], s34[1000], s17[1000], zx[1000], fhe[1000]
	    , fzdif[1000], flum[1000], fage[1000];
} monte2_;

#define monte2_1 monte2_

struct {
    doublereal tcenter, pcenter, dcenter, envlm, envr;
} cent_;

#define cent_1 cent_

struct {
    doublereal tgr[70], xxg[10], r0gr[19], zzg[13], cappa2[167580]	/* 
	    was [126][70][19] */;
    integer numxm[13], nz[13];
} llot95a_;

#define llot95a_1 llot95a_

struct {
    doublereal cappa[13300]	/* was [10][70][19] */, ztab;
} llot95_;

#define llot95_1 llot95_

struct {
    doublereal cappae[1330]	/* was [70][19] */, xtab;
} llot95e_;

#define llot95e_1 llot95e_

struct {
    integer jz, jx[16]	/* was [4][4] */, jt, jd[4];
} op95indx_;

#define op95indx_1 op95indx_

struct {
    doublereal bz[4], bx[16]	/* was [4][4] */, bt[4], btt[4], bd[16]	/* 
	    was [4][4] */, bdd[16]	/* was [4][4] */;
} op95fact_;

#define op95fact_1 op95fact_

struct {
    doublereal hjm0[5000], hcompp0[75000]	/* was [15][5000] */;
} origstart_;

#define origstart_1 origstart_

struct {
    doublereal drate[5000], drate0[5000], fmassacc;
    integer jcz;
} deuter_;

#define deuter_1 deuter_

struct {
    logical lptime;
} ct3_;

#define ct3_1 ct3_

struct {
    doublereal be7massfraction;
} be7_;

#define be7_1 be7_

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
    doublereal enghe3, he3all, umhe33[5000], umheal[5000];
} grab_;

#define grab_1 grab_

struct {
    doublereal envrcz, rint;
} envcz_;

#define envcz_1 envcz_

struct {
    logical ltrist;
} govs_;

#define govs_1 govs_

struct {
    logical lnewtcz, lcalcenv;
    doublereal taucz, taucz0, pphot, pphot0, fracstep;
} ovrtrn_;

#define ovrtrn_1 ovrtrn_

struct {
    char falex06[256], fallard[256], fatm[256], ffermi[256], fkur[256], fkur2[
	    256], flaol[256], flaol2[256], fliv95[256], flldat[256], fmhd1[
	    256], fmhd2[256], fmhd3[256], fmhd4[256], fmhd5[256], fmhd6[256], 
	    fmhd7[256], fmhd8[256], fopal2[256], fpatm[256], fpenv[256], 
	    fpmod[256], fpurez[256], fscvh[256], fscvhe[256], fscvz[256], 
	    opecalex[1792];
} nmlctrl_;

#define nmlctrl_1 nmlctrl_

/* Table of constant values */

static integer c__1 = 1;
static integer c__3 = 3;
static integer c__5 = 5;
static integer c__9 = 9;
static integer c__2 = 2;
static doublereal c_b105 = 10.;



/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */
/* MAIN */
/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */
/* ******* */
/* initialize all variables, set up common blocks */
/* ******* */
/* the array size, i.e. max # of shells is specified in the */
/* parameter statement.  it defines JSON.  to change the array */
/* size do a global change on "JSON=2000" or whatever. */
/* Main program */ int MAIN__(void)
{
    /* Initialized data */

    static integer nao = 1;
    static doublereal sbp[17] = { .9558,.969,.9712,1.,1.,.992,1.,1.,1.,1.,1.,
	    1.,1.,1.,1.,.92088,.1625 };
    static doublereal sunl = 3.844e33;

    /* Format strings */
    static char fmt_1511[] = "(7x,1p7e10.3/e9.3)";
    static char fmt_101[] = "(\002STARTING D \002,e12.4,\002 BELOW STOP VALU"
	    "E \002,e12.4,\002 STOP DISABLED.\002)";
    static char fmt_102[] = "(\002STARTING X \002,e12.4,\002 BELOW STOP VALU"
	    "E \002,e12.4,\002 STOP DISABLED.\002)";
    static char fmt_103[] = "(\002STARTING Y \002,e12.4,\002 BELOW STOP VALU"
	    "E \002,e12.4,\002 STOP DISABLED.\002)";
    static char fmt_911[] = "(i5,1p11e10.3)";
    static char fmt_222[] = "(1p10e10.3)";
    static char fmt_145[] = "(f9.5,f7.3,f6.3,1p10e10.3)";
    static char fmt_104[] = "(\002CENTRAL D \002,e12.4,\002 BELOW STOP VAL"
	    "UE \002,e12.4)";
    static char fmt_105[] = "(\002CENTRAL X \002,e12.4,\002 BELOW STOP VAL"
	    "UE \002,e12.4)";
    static char fmt_106[] = "(\002CENTRAL Y \002,e12.4,\002 BELOW STOP VAL"
	    "UE \002,e12.4)";
    static char fmt_1525[] = "(5x,\002DID NOT CONVERGE WITHIN 10 ATTEMPTS "
	    "L,R\002,2f10.6)";
    static char fmt_1519[] = "(1x,i5,3f10.6,4e10.3)";
    static char fmt_1518[] = "(1x,i2,2f10.6,1p4e11.4)";
    static char fmt_1517[] = "(1x,f7.3,f7.2,f6.3,2f8.5)";
    static char fmt_1516[] = "(1x,2f8.3,1p10e10.3)";
    static char fmt_1520[] = "(i7,1p9e10.3)";
    static char fmt_1521[] = "(f7.4,2f8.5,1p2e10.3)";
    static char fmt_1522[] = "(f8.5,f9.6,2f8.5,f9.6)";
    static char fmt_1523[] = "(1p5e10.3)";

    /* System generated locals */
    integer i__1, i__2, i__3, i__4, i__5;
    doublereal d__1, d__2;
    alist al__1;

    /* Builtin functions */
    integer s_rsfe(cilist *), do_fio(integer *, char *, ftnlen), e_rsfe(void),
	     s_wsle(cilist *), do_lio(integer *, integer *, char *, ftnlen), 
	    e_wsle(void);
    double d_lg10(doublereal *);
    integer s_wsfe(cilist *), e_wsfe(void);
    double exp(doublereal);
    integer f_rew(alist *);
    double pow_dd(doublereal *, doublereal *);
    /* Subroutine */ void s_stop(char *, ftnlen);

    /* Local variables */
    extern /* Subroutine */ int liburn_(doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, integer *,
	     integer *, integer *), wrtout_(doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, logical *, integer *, integer *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, logical *, integer *, integer *, 
	    integer *, integer *, integer *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, logical *,
	     doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *);
    static doublereal teffi;
    extern /* Subroutine */ int chkscal_(doublereal *, doublereal *, 
	    doublereal *, integer *);
    static doublereal solzx;
    extern /* Subroutine */ int chkcal_(doublereal *, doublereal *, integer *,
	     doublereal *);
    static logical lptimesv;
    extern /* Subroutine */ int massloss_(doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, integer *, logical *, 
	    integer *, doublereal *, doublereal *, doublereal *, doublereal *,
	     logical *), wrtmonte_(doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, logical *,
	     integer *, doublereal *, doublereal *, doublereal *, doublereal *
	    , doublereal *, integer *, integer *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, integer *, integer *, integer *), putstore_(
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, logical *, doublereal *,
	     doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, integer *, integer *, 
	    integer *, integer *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *);
    static integer i__, j, k, m;
    static doublereal v[12], x, y, z__;
    static logical lend_kind__;
    static integer i0, i1;
    static doublereal r0[5000], t6;
    extern /* Subroutine */ int getnewenv_(doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, logical *, doublereal *, doublereal *, doublereal *,
	     doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, integer *, logical *);
    static doublereal hd[5000];
    static logical lc[5000];
    static doublereal hg[5000], hi[5000], bl, dl, hl[5000], fp[5000], hp[5000]
	    , hr[5000], hs[5000], ht[5000], ft[5000], ps[3], rs[3], ts[3];
    static integer nn;
    static doublereal tl;
    static integer iu;
    static doublereal fm, fr, dt, dp, dr;
    static integer ii;
    static doublereal gl, hf1[5000], hf2[5000], ds1, ds2, ds3, hr1[5000], hs1[
	    5000], hs2[5000], hr2[5000], hr3[5000], hr4[5000], hr5[5000], hr6[
	    5000], hr7[5000], hr8[5000], hr9[5000], xh2, hha[40000]	/* 
	    was [4][2][5000] */, hhb[20000]	/* was [4][5000] */, hhc[5000]
	    , ecn, hjm[5000], hpp[5000], htt[5000], qiw[5000], hr10[5000], 
	    hr11[5000], hr12[5000], hr13[5000];
    static logical lcz[5000];
    static doublereal be7m[5000], eta2[5000], qdp, qdt, vel, pdt, pdp, xc12, 
	    xc13, xhe3, xn14, xn15, xo16, xo17, xo18, epp1, epp2, epp3, e3al, 
	    pep, pet, sum1, pol1, pot1, poa1;
    extern /* Subroutine */ int mix_(doublereal *, doublereal *, doublereal *,
	     doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, integer *,
	     logical *, integer *, doublereal *, integer *, integer *, 
	    integer *, integer *, doublereal *);
    static doublereal rll;
    static logical lage;
    static doublereal dcen;
    static logical lsbc;
    static doublereal tcen, pcen, hmax[4], hsrf[6], tril[3], trit[3], ftri;
    static integer ikut, jenv;
    static logical lnew;
    static doublereal rhoe;
    static integer jenv0;
    static logical lmix;
    extern /* Subroutine */ int getw_(doublereal *, doublereal *, doublereal *
	    , doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, logical *, logical *, integer *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, integer *), fpft_(
	    doublereal *, doublereal *, doublereal *, integer *, doublereal *,
	     doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *);
    static integer jenv1;
    static doublereal ztox, yini, ddage, zini;
    extern /* Subroutine */ int engeb_(doublereal *, doublereal *, doublereal 
	    *, doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, integer *,
	     doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *);
    static doublereal omega[5000];
    static logical large;
    static doublereal cfenv[9], hcomp[75000]	/* was [15][5000] */, tlumx[8]
	    ;
    static integer nhmax[4];
    static doublereal estore[4], hkerot[5000], fluxi0[50000]	/* was [10][
	    5000] */;
    static integer mxzone[24]	/* was [12][2] */, mxzon0[24]	/* was [12][2]
	     */, mrzone[26]	/* was [13][2] */;
    static logical lpunch;
    extern /* Subroutine */ int parmin_(void), setups_(doublereal *, char *, 
	    char *, char *, char *, char *, char *, char *, char *, char *, 
	    char *, char *, char *, char *, char *, char *, char *, char *, 
	    char *, char *, char *, char *, char *, char *, char *, ftnlen, 
	    ftnlen, ftnlen, ftnlen, ftnlen, ftnlen, ftnlen, ftnlen, ftnlen, 
	    ftnlen, ftnlen, ftnlen, ftnlen, ftnlen, ftnlen, ftnlen, ftnlen, 
	    ftnlen, ftnlen, ftnlen, ftnlen, ftnlen, ftnlen, ftnlen);
    static doublereal fgrset, facage;
    static logical lsavpu;
    extern /* Subroutine */ int setcal_(doublereal *);
    static integer iconv;
    static doublereal xguess, aguess;
    static logical lreset;
    static doublereal sjtot, skerot;
    extern /* Subroutine */ int starin_(doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, integer *, integer *, integer *, logical *, logical 
	    *, logical *, integer *, integer *, integer *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *);
    static doublereal delts, deltsh, hstot;
    static integer istore;
    extern /* Subroutine */ int setscal_(void);
    static integer model;
    static doublereal smass, teffl;
    static logical lnutab;
    extern /* Subroutine */ int wrthead_(doublereal *);
    static doublereal polen;
    static integer iwrite;
    extern /* Subroutine */ int wrtlst_(integer *, doublereal *, doublereal *,
	     doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, logical *, doublereal *, doublereal *, doublereal *,
	     doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, integer *, integer *, integer *, integer *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *);
    static integer jcore;
    static doublereal hkeroto[5000];
    extern /* Subroutine */ int findsh_(doublereal *, doublereal *, logical *,
	     integer *, integer *, integer *, integer *, integer *, integer *,
	     logical *);
    static integer jxbeg, jxend, jxmid;
    static logical lshell;
    extern /* Subroutine */ int htimer_(doublereal *, doublereal *, integer *,
	     doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, integer *, integer *, doublereal *, 
	    doublereal *, doublereal *, integer *, doublereal *, doublereal *,
	     doublereal *, doublereal *, integer *, doublereal *);
    static doublereal dwmax, delts0;
    static integer modeln;
    extern /* Subroutine */ int pdist_(doublereal *, doublereal *, doublereal 
	    *, doublereal *, doublereal *, doublereal *, integer *, char *, 
	    char *, char *, ftnlen, ftnlen, ftnlen);
    static logical lnewfit;
    static doublereal senvold;
    static integer nspec, itlvl;
    extern /* Subroutine */ int hpoint_(integer *, doublereal *, doublereal *,
	     doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, logical *, doublereal *, doublereal *, doublereal *,
	     doublereal *, doublereal *, doublereal *, integer *, logical *, 
	    integer *, integer *, logical *, integer *, integer *, doublereal 
	    *, doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *), 
	    lirate88_(doublereal *, doublereal *, doublereal *, integer *, 
	    integer *);
    static integer itdone;
    static logical lfini;
    static integer kttausv, niter;
    extern /* Subroutine */ int crrect_(doublereal *, integer *, integer *, 
	    logical *, logical *, logical *, logical *, logical *, doublereal 
	    *, doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, integer *, doublereal *, doublereal *,
	     doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, logical *, integer *, doublereal *, 
	    logical *, logical *, logical *, logical *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, integer *, doublereal *, doublereal *,
	     doublereal *, integer *, logical *, integer *, doublereal *, 
	    doublereal *, doublereal *);
    static logical latmo, lderiv, locond;
    static integer itrot;
    static logical limix;
    extern /* Subroutine */ int mixcz_(doublereal *, doublereal *, logical *, 
	    integer *);
    static logical ljdot;
    extern /* Subroutine */ int convec_(doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, logical *,
	     integer *, integer *, integer *, integer *, integer *, integer *,
	     integer *, integer *, integer *);
    static integer nrzone, nzone, nzone0;

    /* Fortran I/O blocks */
    static cilist io___9 = { 0, 0, 0, fmt_1511, 0 };
    static cilist io___10 = { 0, 0, 0, 0, 0 };
    static cilist io___68 = { 0, 6, 0, fmt_101, 0 };
    static cilist io___69 = { 0, 0, 0, fmt_101, 0 };
    static cilist io___70 = { 0, 6, 0, fmt_102, 0 };
    static cilist io___71 = { 0, 0, 0, fmt_102, 0 };
    static cilist io___72 = { 0, 6, 0, fmt_103, 0 };
    static cilist io___73 = { 0, 0, 0, fmt_103, 0 };
    static cilist io___122 = { 0, 6, 0, fmt_911, 0 };
    static cilist io___123 = { 0, 76, 0, fmt_222, 0 };
    static cilist io___128 = { 0, 76, 0, fmt_145, 0 };
    static cilist io___142 = { 0, 6, 0, 0, 0 };
    static cilist io___143 = { 0, 6, 0, 0, 0 };
    static cilist io___185 = { 0, 6, 0, fmt_104, 0 };
    static cilist io___186 = { 0, 6, 0, fmt_105, 0 };
    static cilist io___187 = { 0, 6, 0, fmt_106, 0 };
    static cilist io___191 = { 0, 0, 0, fmt_1525, 0 };
    static cilist io___192 = { 0, 0, 0, fmt_1519, 0 };
    static cilist io___194 = { 0, 0, 0, fmt_1518, 0 };
    static cilist io___195 = { 0, 0, 0, fmt_1517, 0 };
    static cilist io___196 = { 0, 0, 0, fmt_1516, 0 };
    static cilist io___197 = { 0, 0, 0, fmt_1520, 0 };
    static cilist io___198 = { 0, 0, 0, fmt_1518, 0 };
    static cilist io___199 = { 0, 0, 0, fmt_1516, 0 };
    static cilist io___203 = { 0, 0, 0, fmt_1517, 0 };
    static cilist io___206 = { 0, 0, 0, fmt_1521, 0 };
    static cilist io___207 = { 0, 0, 0, fmt_1522, 0 };
    static cilist io___208 = { 0, 0, 0, fmt_1523, 0 };


/* DBGLAOL - to save space make tables single precision */
/* MHP 8/25 Removed unused variables and added pass-through variables */
/*      COMMON/LUFNM/ FLAST, FFIRST, FRUN, FSTAND, FFERMI, */
/*     1    FDEBUG, FTRACK, FSHORT, FMILNE, FMODPT, */
/*     2    FSTOR, FPMOD, FPENV, FPATM, FDYN, */
/*     3    FLLDAT, FSNU, FSCOMP, FKUR, */
/*     4    FMHD1, FMHD2, FMHD3, FMHD4, FMHD5, FMHD6, FMHD7, FMHD8 */
/* DBGLAOL */
/* MHP 8/25 Removed character file names from common block */
/* 11/91 COMMON BLOCKS ADDED FOR PRESSURE SCALE HEIGHT CALC. FOR LIBURN */
/* MHP 05/02 ADDED OPTION TO ITERATE BETWEEN ROTATION AND */
/* STRUCTURE CALCULATIONS - SET ITDIF1 GREATER THAN 1 */
/* MHP 8/17 ADDED EXCEN, C_2 TO COMMON BLOCK FOR MATT ET AL. 2012 CENT. TERM */
/*      COMMON/CWIND/WMAX,EXMD,EXW,EXTAU,EXR,EXM,CONSTFACTOR,STRUCTFACTOR,LJDOT0 */
/* MHP 10/24 ADDED STOP CRITERIA FOR CENTRAL H,D,AND HE4 */
/*      COMMON/SETT/ENDAGE(50),SETDT(50),LENDAG(50),LSETDT(50) */
/* 7/91 ENTROPY TERM COMMON BLOCK ADDED. */
/* 7/91 FLAG TO TOGGLE BETWEEN NEW/OLD RATES ADDED. */
/* MHP 9/94 */
/* MHP 9/94 ADDED DISK LOCKING OPTION - FLAG, TIME OVER WHICH LOCKING */
/* IS ENFORCED, AND PERIOD AT WHICH LOCKING IS SET ARE OPTIONS. */
/* MHP 8/25 Removed character file names from common block */
/* DBG 1/92 let XENV0, ZENV0, and CMIXL be arrays so can change during */
/* a set of runs. */
/* MHP 8/25 Removed character file names from common block */
/* DBG 4/26/94 Tired of not have access to current age of model so... */
/*     MHP 10/24 FLAG FOR END OF RUN */
/* JVS 02/12 */
/* DBG PULSE OUT 7/92 */
/* variables used to contral output of pulsation models.  model */
/* output after has traveled pomax in HR diagram */
/* LPOUT and POMAX added to control common block, rest in physics */
/* MHP 1/93 add common blocks for automatic calibration of solar models. */
/* MHP 6/13 ADD OPTION TO CALIBRATE SOLAR Z/X, SOLAR Z/X, SOLAR AGE */
/*      COMMON/CALS2/TOLL,TOLR,LCALS */
/* DBG 12/94 added calibrate stellar model */
/* MHP 7/96 common block added for sound speed */
/* MHP 8/96 monte carlo option for snus added. */
/* MHP 6/14 DERIVATIVES ADDED TO COMMON BLOCK.  NOT USED FOR DERIVATIVES */
/* IN THE MONTE CARLO. */
/*      COMMON/CROSS/SSTANDARD(17) */
/* MHP 8/96 */
/* added monte carlo parameters for metal diffusion, solar L, solar age. */
/* MHP 3/96 central T,P,RHO added */
/* as above for the model Z. */
/* as above for desired surface value of X. */
/* indices for interpolation in Z,X,T, and R */
/* interpolation factors for Z,X,T, and R, as well as derivative */
/* factors for T and RHO. */
/* MHP 05/02 ADDED FOR ITERATION BETWEEN ROTATION AND STRUCTURE CALCULATION */
/* MHP 05/02 DEUTERIUM BURNING RATE ADDED */
/* ***MHP 1/04 inserted for test */
/*      COMMON/OPTAB/OPTOL,ZSI,IDT,IDD(4) */
/* *** end test */
/* LLP 8/07 Make LPTIME available for calibration */
/* MHP 2/04 ADDED FOR NEUTRINO FLUX TABLE */
/* JVS 02/11 */
/* KC 2025-05-30 reordered common block elements */
/*       COMMON/ACDPTH/TAUCZN,DELADJ(JSON),TAUHE, TNORM, TCZ, WHE, ICLCD, */
/*      *LCLCD, AGEOUT(5), IACAT, IJLAST, LJLAST, LJWRT, LADON,LAOLY, IJVS, */
/* 10/11 He3+He3 luminosity info */
/* JVS 08/13 IF THE CZ IS BEYOND THE FITTING POINT, STORE ITS LOCATION */
/* JVS 04/14 Common block for additional timestep governors */
/* G Somers 3/17, ADDING NEW TAUCZ COMMON BLOCK */
/*     MHP 10/24 NEW VARIABLES FOR STOP CONDITIONS ON CENTRAL ABUNDANCE */
/*       REAL*8 XCEN(2,15),DTPREV */
/*       LOGICAL*4 L_LASTSTEP */
/* LC 11/25 Compatibility fixes for yreclab: */

/* latest values (Bahcall and Pinsonneault 1996)-actual values set in */
/* subroutine PARMIN */
/* MHP 3/96 added data for base solar age, L */
/*       DATA SUNAGE,SUNL/4.57D09,3.844D33/  ! KC 2025-05-31 */
/* ******* */
/* START */
/* ******* */
    luout_1.iowr = 9;
/* LPUNCH is TRUE once first model is calculated */
    lpunch = FALSE_;
/* read in user parameters */
    parmin_();
/* set up constants and read in tabular data */
/* MHP 8/25 directly pass file names instead of using common blocks */
    setups_(v, nmlctrl_1.falex06, nmlctrl_1.fallard, nmlctrl_1.fatm, 
	    nmlctrl_1.ffermi, nmlctrl_1.fkur, nmlctrl_1.fkur2, 
	    nmlctrl_1.flaol, nmlctrl_1.flaol2, nmlctrl_1.fliv95, 
	    nmlctrl_1.flldat, nmlctrl_1.fmhd1, nmlctrl_1.fmhd2, 
	    nmlctrl_1.fmhd3, nmlctrl_1.fmhd4, nmlctrl_1.fmhd5, 
	    nmlctrl_1.fmhd6, nmlctrl_1.fmhd7, nmlctrl_1.fmhd8, 
	    nmlctrl_1.fopal2, nmlctrl_1.fpurez, nmlctrl_1.fscvh, 
	    nmlctrl_1.fscvhe, nmlctrl_1.fscvz, nmlctrl_1.opecalex, (ftnlen)
	    256, (ftnlen)256, (ftnlen)256, (ftnlen)256, (ftnlen)256, (ftnlen)
	    256, (ftnlen)256, (ftnlen)256, (ftnlen)256, (ftnlen)256, (ftnlen)
	    256, (ftnlen)256, (ftnlen)256, (ftnlen)256, (ftnlen)256, (ftnlen)
	    256, (ftnlen)256, (ftnlen)256, (ftnlen)256, (ftnlen)256, (ftnlen)
	    256, (ftnlen)256, (ftnlen)256, (ftnlen)256);
/* MHP 3/96 changed I/O to read in only up to max run needed. */
    if (monte_1.lmonte) {
/* MHP 8/25 moved file open to parmin */
/*     OPEN(UNIT=IDYN,FILE=FDYN,FORM='FORMATTED',STATUS='OLD') */
	i0 = monte_1.imbeg;
	monte_1.imend = min(monte_1.imend,1000);
	i1 = monte_1.imend;
/* read in monte carlo data */
	i__1 = monte_1.imend;
	for (i__ = 1; i__ <= i__1; ++i__) {
	    io___9.ciunit = lunum_1.idyn;
	    s_rsfe(&io___9);
	    do_fio(&c__1, (char *)&monte2_1.s11[i__ - 1], (ftnlen)sizeof(
		    doublereal));
	    do_fio(&c__1, (char *)&monte2_1.s33[i__ - 1], (ftnlen)sizeof(
		    doublereal));
	    do_fio(&c__1, (char *)&monte2_1.s34[i__ - 1], (ftnlen)sizeof(
		    doublereal));
	    do_fio(&c__1, (char *)&monte2_1.s17[i__ - 1], (ftnlen)sizeof(
		    doublereal));
	    do_fio(&c__1, (char *)&monte2_1.zx[i__ - 1], (ftnlen)sizeof(
		    doublereal));
	    do_fio(&c__1, (char *)&monte2_1.fhe[i__ - 1], (ftnlen)sizeof(
		    doublereal));
	    do_fio(&c__1, (char *)&monte2_1.flum[i__ - 1], (ftnlen)sizeof(
		    doublereal));
	    do_fio(&c__1, (char *)&monte2_1.fage[i__ - 1], (ftnlen)sizeof(
		    doublereal));
	    e_rsfe();
	    io___10.ciunit = luout_1.iowr;
	    s_wsle(&io___10);
	    do_lio(&c__3, &c__1, (char *)&i__, (ftnlen)sizeof(integer));
	    do_lio(&c__5, &c__1, (char *)&monte2_1.s11[i__ - 1], (ftnlen)
		    sizeof(doublereal));
	    do_lio(&c__5, &c__1, (char *)&monte2_1.s33[i__ - 1], (ftnlen)
		    sizeof(doublereal));
	    do_lio(&c__5, &c__1, (char *)&monte2_1.s34[i__ - 1], (ftnlen)
		    sizeof(doublereal));
	    do_lio(&c__5, &c__1, (char *)&monte2_1.s17[i__ - 1], (ftnlen)
		    sizeof(doublereal));
	    do_lio(&c__5, &c__1, (char *)&monte2_1.zx[i__ - 1], (ftnlen)
		    sizeof(doublereal));
	    do_lio(&c__5, &c__1, (char *)&monte2_1.fhe[i__ - 1], (ftnlen)
		    sizeof(doublereal));
	    do_lio(&c__5, &c__1, (char *)&monte2_1.flum[i__ - 1], (ftnlen)
		    sizeof(doublereal));
	    do_lio(&c__5, &c__1, (char *)&monte2_1.fage[i__ - 1], (ftnlen)
		    sizeof(doublereal));
	    e_wsle();
	    monte2_1.fzdif[i__ - 1] = monte2_1.fhe[i__ - 1];
	}
    } else {
	i0 = 1;
	i1 = 1;
    }
    i__1 = i1;
    for (nn = i0; nn <= i__1; ++nn) {
/* for monte carlo run, input values of parameters being changed. */
	if (monte_1.lmonte) {
	    cross_1.sstandard[0] = monte2_1.s11[nn - 1] * sbp[0];
	    cross_1.sstandard[1] = monte2_1.s33[nn - 1] * sbp[1];
	    cross_1.sstandard[2] = monte2_1.s34[nn - 1] * sbp[2];
	    cross_1.sstandard[15] = monte2_1.s17[nn - 1] * sbp[15];
	    fgrset = monte2_1.fhe[nn - 1];
	    gravs3_1.fgrz = monte2_1.fzdif[nn - 1];
	    const_1.clsun = sunl * monte2_1.flum[nn - 1];
	    const_1.clsunl = d_lg10(&const_1.clsun);
	    const_1.clnsun = const1_1.cln / const_1.clsun;
	    facage = monte2_1.fage[nn - 1];
/* timestep and final age are altered in SR SETCAL; input #s should be */
/* scaled for a solar age of 4.57 Gyr */
	    sett_1.endage[1] = 1e8;
	    sett_1.endage[2] = 4.57e9;
	} else {
	    facage = 1.;
	}
/* DBG PULSE: save LPULSE flag, set LPULSE to F except on last model of */
/* last run, then set LPULSE to saved value of LPULSE. */
	lsavpu = pulse_1.lpulse;
/* 02/11 JVS uncommented LPULSE=.FALSE. */
/*      LPULSE = .FALSE. */
/* MHP 1/93 add option to automatically calibrate solar model. */
/* MHP 3/96 added counter for # of iterations per converged model and */
/* starting estimate of ALPHA and X */
	if (cals2_1.lcals) {
	    setcal_(&facage);
	    iconv = 1;
	    xguess = ckind_1.rescal[1];
	    aguess = newxym_1.cmixla[0];
	    lptimesv = ct3_1.lptime;
/* save LPTIME for reuse during calibration */
	    kttausv = atmos_1.kttau;
/* save KTTAU for reuse during calibration */
	} else {
	    iconv = 0;
	}
/* DBG 12/94 add option to automatically calculate a stellar model */
/* of specified Teff and L */
	if (calstar_1.lcalst) {
	    setscal_();
	}
/* ********** */
/*     RUN THROUGH THE KIND CARDS IN ORDER */
/* ********** */
	i__2 = ckind_1.numrun;
	for (zramp_1.nk = 1; zramp_1.nk <= i__2; ++zramp_1.nk) {
	    sound_1.lsound = FALSE_;
/*         LPULSE=.FALSE. */
	    label_1.xenv0 = newxym_1.xenv0a[zramp_1.nk - 1];
	    label_1.zenv0 = newxym_1.zenv0a[zramp_1.nk - 1];
	    const3_1.cmixl = newxym_1.cmixla[zramp_1.nk - 1];
	    cenv_1.lsenv0 = newxym_1.lsenv0a[zramp_1.nk - 1];
	    cenv_1.senv0 = newxym_1.senv0a[zramp_1.nk - 1];
	    lreset = FALSE_;
	    large = FALSE_;
/* MHP 10/02 ZERO OUT INITIAL ANGULAR MOMENTUM */
	    sjtot = 0.;
	    skerot = 0.;
/* read in the initial model here */
/* STARIN also calls RSCALE to perform rescaling if requested */
/*        CALL STARIN(BL,CFENV,DAGE,DDAGE,DELTS,DELTSH,DELTS0,ETA2,  ! KC 2025-05-31 */
	    starin_(&bl, cfenv, &theage_1.dage, &ddage, &delts, &deltsh, eta2,
		     fp, ft, &ftri, hcomp, hd, hi, hjm, hkerot, hl, hp, hr, 
		    hs, hs1, hs2, &hstot, ht, &ikut, &istore, &jenv, &large, 
		    lc, &lnew, &m, &model, &zramp_1.nk, omega, ps, &qdp, &qdt,
		     qiw, r0, rs, &sjtot, &skerot, &smass, &teffl, tlumx, 
		    tril, trit, ts, &vel, hg, v);
/*      *    HSTOT,HT,IKUT,ISTORE,JCORE,JENV,LARGE,LC,LNEW,M,MODEL,  ! KC 2025-05-31 */
/*     MHP 10/24 CHECK STOP CONDITIONS AND DISABLE THEM IF THE STARTING VALUES ARE BELOW THE TARGET THRESHOLD 
*/
	    if (sett_1.lendag[zramp_1.nk - 1]) {
		if (sett_1.end_dcen__[zramp_1.nk - 1] > 0. && hcomp[11] < 
			sett_1.end_dcen__[zramp_1.nk - 1]) {
		    sett_1.end_dcen__[zramp_1.nk - 1] = -sett_1.end_dcen__[
			    zramp_1.nk - 1];
		    s_wsfe(&io___68);
		    do_fio(&c__1, (char *)&hcomp[11], (ftnlen)sizeof(
			    doublereal));
		    do_fio(&c__1, (char *)&sett_1.end_dcen__[zramp_1.nk - 1], 
			    (ftnlen)sizeof(doublereal));
		    e_wsfe();
		    io___69.ciunit = luout_1.ishort;
		    s_wsfe(&io___69);
		    do_fio(&c__1, (char *)&hcomp[11], (ftnlen)sizeof(
			    doublereal));
		    do_fio(&c__1, (char *)&sett_1.end_dcen__[zramp_1.nk - 1], 
			    (ftnlen)sizeof(doublereal));
		    e_wsfe();
		}
		if (sett_1.end_xcen__[zramp_1.nk - 1] > 0. && hcomp[0] < 
			sett_1.end_xcen__[zramp_1.nk - 1]) {
		    sett_1.end_dcen__[zramp_1.nk - 1] = -sett_1.end_xcen__[
			    zramp_1.nk - 1];
		    s_wsfe(&io___70);
		    do_fio(&c__1, (char *)&hcomp[11], (ftnlen)sizeof(
			    doublereal));
		    do_fio(&c__1, (char *)&sett_1.end_dcen__[zramp_1.nk - 1], 
			    (ftnlen)sizeof(doublereal));
		    e_wsfe();
		    io___71.ciunit = luout_1.ishort;
		    s_wsfe(&io___71);
		    do_fio(&c__1, (char *)&hcomp[11], (ftnlen)sizeof(
			    doublereal));
		    do_fio(&c__1, (char *)&sett_1.end_dcen__[zramp_1.nk - 1], 
			    (ftnlen)sizeof(doublereal));
		    e_wsfe();
		}
		if (sett_1.end_ycen__[zramp_1.nk - 1] > 0. && hcomp[1] < 
			sett_1.end_ycen__[zramp_1.nk - 1]) {
		    sett_1.end_ycen__[zramp_1.nk - 1] = -sett_1.end_ycen__[
			    zramp_1.nk - 1];
		    s_wsfe(&io___72);
		    do_fio(&c__1, (char *)&hcomp[11], (ftnlen)sizeof(
			    doublereal));
		    do_fio(&c__1, (char *)&sett_1.end_dcen__[zramp_1.nk - 1], 
			    (ftnlen)sizeof(doublereal));
		    e_wsfe();
		    io___73.ciunit = luout_1.ishort;
		    s_wsfe(&io___73);
		    do_fio(&c__1, (char *)&hcomp[11], (ftnlen)sizeof(
			    doublereal));
		    do_fio(&c__1, (char *)&sett_1.end_dcen__[zramp_1.nk - 1], 
			    (ftnlen)sizeof(doublereal));
		    e_wsfe();
		}
	    }
/*     MHP 2/04 NEUTRINO TABLE */
/*      LNUTAB = .TRUE. */
	    lnutab = FALSE_;
	    if (lnutab) {
/* SET UP WEIGHTS AND MASSES. */
/* HS1 = LOCATION IN GM (UNLOGGED) OF SHELL CENTERS. */
/* HS2 = MASS IN GM OF EACH SHELL. */
		ds3 = exp(const1_1.cln * hs[0]);
		ds2 = -ds3;
		i__3 = m;
		for (i__ = 2; i__ <= i__3; ++i__) {
		    ds1 = ds2;
		    ds2 = ds3;
		    ds3 = exp(const1_1.cln * hs[i__ - 1]);
		    hs1[i__ - 2] = ds2;
		    hs2[i__ - 2] = (ds3 - ds1) * .5;
		}
		hs1[m - 1] = ds3;
		hs2[m - 1] = exp(const1_1.cln * hstot) - (ds2 + ds3) * .5;
		pdt = -1.;
		pdp = 1.;
		for (j = 1; j <= 10; ++j) {
		    fluxes_1.fluxtot[j - 1] = 0.;
		    i__3 = m;
		    for (k = 1; k <= i__3; ++k) {
			fluxi0[j + k * 10 - 11] = 0.;
		    }
		}
/* ASSIGN LOCAL VARIABLES FOR SR CALL FROM GLOBAL VECTORS. */
		i__3 = m;
		for (i__ = 1; i__ <= i__3; ++i__) {
		    dl = hd[i__ - 1];
		    tl = ht[i__ - 1];
/* SKIP CALCULATIONS FOR LOW TEMPERATURES. */
		    if (tl < 6.) {
			goto L666;
		    }
		    x = hcomp[i__ * 15 - 15];
		    y = hcomp[i__ * 15 - 14];
		    z__ = hcomp[i__ * 15 - 13];
		    xhe3 = hcomp[i__ * 15 - 12];
		    xc12 = hcomp[i__ * 15 - 11];
		    xc13 = hcomp[i__ * 15 - 10];
		    xn14 = hcomp[i__ * 15 - 9];
		    xn15 = hcomp[i__ * 15 - 8];
		    xo16 = hcomp[i__ * 15 - 7];
		    xo17 = hcomp[i__ * 15 - 6];
		    xo18 = hcomp[i__ * 15 - 5];
		    engeb_(&epp1, &epp2, &epp3, &ecn, &e3al, &pep, &pet, &
			    sum1, &dl, &tl, &x, &y, &xhe3, &xc12, &xc13, &
			    xn14, &xo16, &xo18, &xh2, &iu, hr1, hr2, hr3, hr4,
			     hr5, hr6, hr7, hr8, hr9, hr10, hr11, hr12, hr13, 
			    hf1, hf2);
/*      *TL,PDT,PDP,X,Y,Z,XHE3,XC12,XC13,XN14,XN15,XO16,XO17, */
/*      *XO18,XH2,XLI6,XLI7,XBE9,I,HR1,HR2,HR3,HR4,HR5,HR6,HR7,  ! KC 2025-05-31 */
/* BE7 MASS FRACTION. */
		    be7m[i__ - 1] = be7_1.be7massfraction;
/* CONVERT FROM ERG/GM/S TO ERG/S FOR EACH SHELL BY MULTIPLYING */
/* BY THE MASS OF EACH SHELL IN GM (HS2). */
		    for (j = 1; j <= 10; ++j) {
			fluxi0[j + i__ * 10 - 11] = fluxes_1.flux[j - 1] * 
				hs2[i__ - 1];
			fluxes_1.fluxtot[j - 1] += fluxi0[j + i__ * 10 - 11];
		    }
		    s_wsfe(&io___122);
		    do_fio(&c__1, (char *)&i__, (ftnlen)sizeof(integer));
		    do_fio(&c__1, (char *)&hs2[i__ - 1], (ftnlen)sizeof(
			    doublereal));
		    for (j = 1; j <= 10; ++j) {
			do_fio(&c__1, (char *)&fluxi0[j + i__ * 10 - 11], (
				ftnlen)sizeof(doublereal));
		    }
		    e_wsfe();
		}
L666:
/* WRITE OUT TOTAL NEUTRINO FLUXES. */
/* ***NOTE THAT THESE ARE IN UNITS OF 10**10. *** */
		s_wsfe(&io___123);
		for (i__ = 1; i__ <= 10; ++i__) {
		    do_fio(&c__1, (char *)&fluxes_1.fluxtot[i__ - 1], (ftnlen)
			    sizeof(doublereal));
		}
		e_wsfe();
/* NORMALIZE FLUXES. */
		for (j = 1; j <= 10; ++j) {
		    i__3 = m;
		    for (i__ = 1; i__ <= i__3; ++i__) {
			fluxi0[j + i__ * 10 - 11] /= fluxes_1.fluxtot[j - 1];
		    }
		}
		i__3 = m;
		for (i__ = 1; i__ <= i__3; ++i__) {
/* TEMPERATURE IN UNITS OF 10**6 K. */
		    t6 = exp(const1_1.cln * (ht[i__ - 1] - 6.));
		    if (t6 < 5.) {
			goto L141;
		    }
/* ELECTRON DENSITY. */
		    d__1 = (hcomp[i__ * 15 - 15] + 1.) / 2.;
		    rhoe = hd[i__ - 1] + d_lg10(&d__1);
/* MASS FRACTION. */
		    fm = hs2[i__ - 1] / 1.9891e33;
/* RADIUS FRACTION. */
		    fr = exp(const1_1.cln * hr[i__ - 1]) / const_1.crsun;
/* FLUXES ARE PRINTED IN THE SAME ORDER AS BAHCALL AND PINSONNEAULT. */
		    s_wsfe(&io___128);
		    do_fio(&c__1, (char *)&fr, (ftnlen)sizeof(doublereal));
		    do_fio(&c__1, (char *)&t6, (ftnlen)sizeof(doublereal));
		    do_fio(&c__1, (char *)&rhoe, (ftnlen)sizeof(doublereal));
		    do_fio(&c__1, (char *)&fm, (ftnlen)sizeof(doublereal));
		    do_fio(&c__1, (char *)&be7m[i__ - 1], (ftnlen)sizeof(
			    doublereal));
		    do_fio(&c__1, (char *)&fluxi0[i__ * 10 - 10], (ftnlen)
			    sizeof(doublereal));
		    do_fio(&c__1, (char *)&fluxi0[i__ * 10 - 6], (ftnlen)
			    sizeof(doublereal));
		    do_fio(&c__1, (char *)&fluxi0[i__ * 10 - 5], (ftnlen)
			    sizeof(doublereal));
		    do_fio(&c__1, (char *)&fluxi0[i__ * 10 - 4], (ftnlen)
			    sizeof(doublereal));
		    do_fio(&c__1, (char *)&fluxi0[i__ * 10 - 3], (ftnlen)
			    sizeof(doublereal));
		    do_fio(&c__1, (char *)&fluxi0[i__ * 10 - 7], (ftnlen)
			    sizeof(doublereal));
		    do_fio(&c__1, (char *)&fluxi0[i__ * 10 - 9], (ftnlen)
			    sizeof(doublereal));
		    do_fio(&c__1, (char *)&fluxi0[i__ * 10 - 8], (ftnlen)
			    sizeof(doublereal));
		    e_wsfe();
		}
L141:
/*         IF(M.GT.1)STOP999 */
		;
	    }
/* save mass in solar units */
	    pulse_1.xmsol = smass;
/* MHP 08/02 STORE STARTING CZ PROPERTIES */
	    deuter_1.jcz = jenv;
	    ovrtrn_1.taucz = 0.;
/* write out headers of the appropriate output files */
	    wrthead_(&smass);
/* DBG PULSE OUT 7/92 */
/* initialize variables for calculating when to dump pulse output */
	    pol1 = bl;
	    pot1 = teffl;
	    poa1 = theage_1.dage;
	    polen = 0.;
	    if (heflsh_1.lkuthe) {
/* timestep cutting requires a model stored in logical unit ILAST */
/* or it will crash - so copy initial model to unit ILAST */
		if (lpunch) {
		    iwrite = luout_1.ilast;
		    wrtlst_(&iwrite, hcomp, hd, hl, hp, hr, hs, ht, lc, trit, 
			    tril, ps, ts, rs, cfenv, &ftri, tlumx, &jcore, &
			    jenv, &model, &m, &smass, &teffl, &bl, &hstot, &
			    theage_1.dage, &ddage, omega);
		}
	    }
/* locate the hydrogen-burning shell and the boundaries of the central */
/* and surface convection zones (if applicable). */
	    findsh_(hcomp, hl, lc, &m, &jcore, &jenv, &jxbeg, &jxend, &jxmid, 
		    &lshell);
/* determine timestep for model */
/* JVS 04/14 Added Teffl to passed variables */
/*        CALL HTIMER(DELTS,DELTSH,M,HD,HL,HS1,HS2,HT,LC,HCOMP,JCORE, */
/*      *               JXMID,TLUMX,DAGE,DDAGE,QDT,QDP,NK,HP,HR,OMEGA,  ! KC 2025-05-31 */
	    htimer_(&delts, &deltsh, &m, hd, hl, hs1, hs2, ht, hcomp, &jcore, 
		    &jxmid, tlumx, &theage_1.dage, &ddage, &zramp_1.nk, hp, 
		    hr, omega, &dwmax, &jxbeg, &teffl);
	    delts0 = delts;
/* zero out entropy terms. */
	    i__3 = m;
	    for (i__ = 1; i__ <= i__3; ++i__) {
		entrop_1.htt0[i__ - 1] = 0.;
		entrop_1.hpp0[i__ - 1] = 0.;
		entrop_1.hll0[i__ - 1] = 0.;
		entrop_1.hrr0[i__ - 1] = 0.;
/* L99: */
	    }
/* zero out light element burning rates in the surface CZ. */
	    if (flag_1.lexcom) {
		prevcz_1.bli6old = 0.;
		prevcz_1.bli7old = 0.;
		prevcz_1.bbe9old = 0.;
	    }
/* for a given kind card, evolve NMODLS(NK) times */
/* if rescaling is being performed, NMODLS(NK) is the number of times */
/* the new model is being relaxed */
	    i__3 = ckind_1.nmodls[zramp_1.nk - 1];
	    for (modeln = 1; modeln <= i__3; ++modeln) {
/* rewind ISHORT if LRWSH is true (keeps ISHORT small) */
		if (chrone_1.lrwsh) {
		    al__1.aerr = 0;
		    al__1.aunit = luout_1.ishort;
		    f_rew(&al__1);
		}
/* DBG PULSE:  if last model of last run then set LPULSE to LSAVPU */
		if (modeln == ckind_1.nmodls[zramp_1.nk - 1] && zramp_1.nk == 
			ckind_1.numrun) {
		    pulse_1.lpulse = lsavpu;
		}
/* JVS 02/11: Also allow pulse output at particular ages along the way */

/*  If the step is bracketing an age of interest, turn on output. This will */
/* for the step before and step after the age in AGEOUT. Once the info has */
/* been printed out, AGEOUT is set to the next age. */

/* Turn on calcad: */
		if (acdpth_1.lacout) {
		    acdpth_1.ladon = TRUE_;
		} else {
		    acdpth_1.ladon = FALSE_;
		}
/* If output has been turned on for a previous step, keep it on for the next */
/* step, but then turn it off. */
		if (acdpth_1.lacout) {
		    if (acdpth_1.ljwrt) {
			s_wsle(&io___142);
			do_lio(&c__9, &c__1, "LJWRT on", (ftnlen)8);
			e_wsle();
			pulse_1.lpulse = lsavpu;
			++nao;
			acdpth_1.lclcd = TRUE_;
			acdpth_1.ljlast = FALSE_;
			acdpth_1.ljwrt = FALSE_;
		    } else if (! acdpth_1.ljwrt) {
			acdpth_1.lclcd = FALSE_;
		    }
/* If this is the step before one of the ages of interest, print everything out. */
/* Also, save model structure. */
		    if (nao < 6) {
			if (theage_1.dage + ddage / 1e9 - acdpth_1.ageout[nao 
				- 1] <= 0. && theage_1.dage + ddage * 2. / 
				1e9 - acdpth_1.ageout[nao - 1] >= 0. && ! 
				acdpth_1.ljwrt) {
			    s_wsle(&io___143);
			    do_lio(&c__9, &c__1, "AGEOUT reached", (ftnlen)14)
				    ;
			    e_wsle();
			    pulse_1.lpulse = lsavpu;
			    acdpth_1.lclcd = TRUE_;
			    acdpth_1.ljlast = TRUE_;
			    acdpth_1.ljwrt = TRUE_;
			}
		    }
		}
/* JVS end */

/* DBG PULSE:  if endage reached then set LPULSE to LSAVPU */
/* MHP 10/24 GENERALIZE CHECK */
		if (sett_1.lendag[zramp_1.nk - 1] && sett_1.endage[zramp_1.nk 
			- 1] > 0. && (d__1 = sett_1.endage[zramp_1.nk - 1] - 
			theage_1.dage * 1e9 - ddage, abs(d__1)) <= 1.) {
		    pulse_1.lpulse = lsavpu;
/* MHP 7/96 compute sound speed for solar model */
		    sound_1.lsound = TRUE_;
		}
/* FD echo LSOUND */
/*        print*,'MAIN LSOUND = ',LSOUND */
/* FD end */
		if (po_1.lpout) {
/* MHP 8/25 changed to add file names as declared variables */
		    pdist_(&pol1, &pot1, &poa1, &polen, &bl, &teffl, &modeln, 
			    nmlctrl_1.fpatm, nmlctrl_1.fpenv, nmlctrl_1.fpmod,
			     (ftnlen)256, (ftnlen)256, (ftnlen)256);
		}
/* STARIN called here for timestep cutting */
L15:
		if (large) {
/*              CALL STARIN(BL,CFENV,DAGE,DDAGE,DELTS,DELTSH,DELTS0,ETA2,  ! KC 2025-05-31 */
		    starin_(&bl, cfenv, &theage_1.dage, &ddage, &delts, &
			    deltsh, eta2, fp, ft, &ftri, hcomp, hd, hi, hjm, 
			    hkerot, hl, hp, hr, hs, hs1, hs2, &hstot, ht, &
			    ikut, &istore, &jenv, &large, lc, &lnew, &m, &
			    model, &zramp_1.nk, omega, ps, &qdp, &qdt, qiw, 
			    r0, rs, &sjtot, &skerot, &smass, &teffl, tlumx, 
			    tril, trit, ts, &vel, hg, v);
/*      *          HSTOT,HT,IKUT,ISTORE,JCORE,JENV,LARGE,LC,LNEW,M,MODEL,  ! KC 2025-05-31 */
		}
		lpunch = TRUE_;
/* skip this section if model not to be aged */
/* MHP 7/98 */
/* need to add logic to permit resacling + time evolution for */
/* pre-main sequence models */
		if (ckind_1.iresca[zramp_1.nk - 1] != 2 && model >= 0) {
		    lage = TRUE_;
		} else if (model >= 0 && ht[0] < 6.6) {
		    lage = TRUE_;
		} else {
		    lage = FALSE_;
		}
		lnewfit = FALSE_;
		if (lage) {
/* ADD MASS LOSS CALCULATION */
		    massloss_(&bl, &theage_1.dage, &delts, hcomp, hd, hjm, hp,
			     hr, hs, hs1, hs2, &hstot, ht, &jenv, &lnew, &m, 
			    omega, &smass, &teffl, &senvold, &lnewfit);
/* STORE COMPOSITION MATRIX AT THE BEGINNING OF THE TIMESTEP. */
		    nspec = 11;
		    if (flag_1.lexcom) {
			nspec = 15;
		    }
		    i__4 = m;
		    for (i__ = 1; i__ <= i__4; ++i__) {
			i__5 = nspec;
			for (j = 1; j <= i__5; ++j) {
			    oldmod_1.hcompp[j + i__ * 15 - 16] = hcomp[j + 
				    i__ * 15 - 16];
/* L32: */
			}
/* L33: */
		    }
		    itlvl = 1;
		    mix_(&delts, hcomp, hd, hl, hp, hr, hs, hs1, hs2, &hstot, 
			    ht, &itlvl, lc, &m, &ddage, &jcore, &jenv, mxzone,
			     mxzon0, &teffl);
/*      *                     HT,ITLVL,LC,M,QDT,QDP,DDAGE,JCORE,JENV,  ! KC 2025-05-31 */
		    ddage = delts / const3_1.csecyr;
		    theage_1.dage += ddage * 1e-9;
		}
/* ***MHP 1/04 OPACITY TEST */
/*      IDT = 15 */
/*      DO JJJ = 1,4 */
/*         IDD(JJJ) = 5 */
/*      END DO */
/*      XXX = 0.7D0 */
/*      ZZZ = 0.02D0 */
/*      Do JJJ = 1,2000 */
/*         READ(75,*)TL,DL,XX,ZZ,OO */
/*         IF(TT.GT.1.0D9)STOP911 */
/*         TL = LOG10(TT) */
/*         DL = LOG10(DD) */
/* DBG 12/95 GET OPACITY */
/*         CALL GETOPAC(DL, TL,XXX,ZZZ, O, OL, QOD, QOT) */
/*         DIFF = (O-OO)/O */
/*         RL = DL - 3*TL +18.0D0 */
/*         WRITE(76,1554)TL,RL,XXX,ZZZ,O,OO,DIFF */
/* 1554    format(4f11.6,3e20.10) */
/*      END DO */
/* *** END TEST */
/* rezone new model, except rezoning not performed for He flash calculations */
		if (! heflsh_1.lkuthe) {
		    hpoint_(&m, &hstot, hs, hs1, hs2, ht, hp, hr, lc, hl, hd, 
			    hcomp, ps, rs, estore, &istore, &lreset, &jxbeg, &
			    model, &lshell, &jcore, &jenv, omega, eta2, r0, 
			    hi, hjm, hkerot, &sjtot, &skerot, fp, ft, hg, qiw,
			     &teffl);
/*      *              HJM,HKEROT,SJTOT,SKEROT,BL,DELTS,FP,FT, */
/*      *              HG,QIW,SMASS,TEFFL)  ! KC 2025-05-31 */
/* STORE NEW CZ BASE */
		    deuter_1.jcz = jenv;
		} else {
/* save old model for PTIME */
		    i__4 = m;
		    for (i__ = 1; i__ <= i__4; ++i__) {
			oldmod_1.hpo[i__ - 1] = hp[i__ - 1];
			oldmod_1.hto[i__ - 1] = ht[i__ - 1];
			oldmod_1.hro[i__ - 1] = hr[i__ - 1];
			oldmod_1.hlo[i__ - 1] = hl[i__ - 1];
			oldmod_1.hdo[i__ - 1] = hd[i__ - 1];
		    }
/* JVS 04/14 Save Teff as well */
		    oldmod_1.tefflo = teffl;
/*  JVS 05/25 Added model number to list of saved values */
		    oldmod_1.mo = m;
		}
/* store starting distribution of rotational kinetic energy. */
		if (rot_1.lrot) {
		    i__4 = m;
		    for (i__ = 1; i__ <= i__4; ++i__) {
			hkeroto[i__ - 1] = hkerot[i__ - 1];
		    }
		}
/* changed for lithium burning with overshoot. */
/* store starting depth of C.Z. for light element burning. */
		if (flag_1.lexcom) {
		    prevcz_1.rbase0 = 0.;
		    jenv0 = jenv;
		    if (dpmix_1.lovste) {
			liov_1.pscal0 = dpmix_1.alphae * exp(const3_1.clndp * 
				(hp[jenv - 1] + hr[jenv - 1] * 2. - hd[jenv - 
				1] - const2_1.cgl - hs[jenv - 1]));
		    } else {
			liov_1.pscal0 = 0.;
		    }
/* find burning rates at the beginning of the time step. */
		    lirate88_(hcomp, hd, ht, &m, &c__1);
		}
/* begin correction routines */
/* set flags for CRRECT */
/* CRRECT checks surface boundary conditions in every iteration */
/* if LNEW0 = T, new envelope triangle calculated the 1st iteration */
/* (i.e. old triangle ignored) */
/* LFINI = T if model has converged */
/* LARGE = T if model has diverged */
		if (cenv_1.lnew0) {
		    lnew = TRUE_;
		}
		if (! lage) {
		    delts = -abs(delts);
		}
		ctol_1.fcorr = abs(ctol_1.fcorr0) - ctol_1.fcorri;
		itdone = 0;
		large = FALSE_;
		lfini = FALSE_;
		if (! neweng_1.lnews || delts <= 0.) {
		    i__4 = m;
		    for (i__ = 1; i__ <= i__4; ++i__) {
/* zero entropy terms */
			htt[i__ - 1] = 0.;
			hpp[i__ - 1] = 0.;
			entrop_1.htt0[i__ - 1] = 0.;
			entrop_1.hpp0[i__ - 1] = 0.;
			entrop_1.hll0[i__ - 1] = 0.;
			entrop_1.hrr0[i__ - 1] = 0.;
/* zero gravitational energy terms. */
			hhc[i__ - 1] = 0.;
/* L20: */
		    }
		} else {
/* use the rate of change in the previous model to estimate the new */
/* run of structure variables. */
		    i__4 = m;
		    for (i__ = 1; i__ <= i__4; ++i__) {
			dt = entrop_1.htt0[i__ - 1] * delts;
			dp = entrop_1.hpp0[i__ - 1] * delts;
			dl = hl[i__ - 1] * entrop_1.hll0[i__ - 1] * delts;
			dr = entrop_1.hrr0[i__ - 1] * delts;
			htt[i__ - 1] = dt;
			hpp[i__ - 1] = dp;
			ht[i__ - 1] += dt;
			hp[i__ - 1] += dp;
			hl[i__ - 1] += dl;
			hr[i__ - 1] += dr;
/* zero gravitational energy terms. */
			hhc[i__ - 1] = 0.;
/* L30: */
		    }
		}
/* FIRST LEVEL OF ITERATIONS */
/* USE ENVELOPE TRIANGLE OF THE PREVIOUS MODEL; */
/* FOR THE FIRST MODEL OF A RUN,THE TRIANGLE IS GENERATED HERE. */
		niter = ctol_1.niter1;
		lsbc = FALSE_;
/* CALL TO CRRECT - ADDED ITERATION LEVEL */
		itlvl = 1;
		crrect_(&delts, &m, &niter, &lfini, &large, &lnew, &lreset, &
			lsbc, trit, tril, cfenv, ps, ts, rs, &ftri, &istore, 
			estore, &hstot, &bl, &teffl, hd, hha, hhb, hhc, hl, 
			hmax, hp, hpp, hr, hs, hs1, hs2, hsrf, ht, htt, hcomp,
			 lc, nhmax, tlumx, &latmo, &lderiv, &lmix, &locond, &
			qdt, &qdp, fp, ft, eta2, omega, r0, &itdone, hg, hi, 
			hjm, &itlvl, lcz, mxzone, qiw, hkerot, hkeroto);
/*      *           LMIX,LOCOND,QDT,QDP,MODEL,FP,FT,ETA2,OMEGA,R0,ITDONE, */
/*      *           HG,HI,HJM, ITLVL,LCZ,MRZONE,MXZONE,NRZONE,NZONE,  ! KC 2025-05-31 */
/* SECOND LEVEL OF ITERATIONS */
/* CHECK ENVELOPE TRIANGLE BEFORE ITERATING FOR SOLUTION */
		if (large) {
		    goto L15;
		}
		lsbc = TRUE_;
		niter = ctol_1.niter2;
		itlvl = 2;
		crrect_(&delts, &m, &niter, &lfini, &large, &lnew, &lreset, &
			lsbc, trit, tril, cfenv, ps, ts, rs, &ftri, &istore, 
			estore, &hstot, &bl, &teffl, hd, hha, hhb, hhc, hl, 
			hmax, hp, hpp, hr, hs, hs1, hs2, hsrf, ht, htt, hcomp,
			 lc, nhmax, tlumx, &latmo, &lderiv, &lmix, &locond, &
			qdt, &qdp, fp, ft, eta2, omega, r0, &itdone, hg, hi, 
			hjm, &itlvl, lcz, mxzone, qiw, hkerot, hkeroto);
/*      *           LMIX,LOCOND,QDT,QDP,MODEL,FP,FT,ETA2,OMEGA,R0,ITDONE, */
/*      *           HG,HI,HJM, ITLVL,LCZ,MRZONE,MXZONE,NRZONE,NZONE,  ! KC 2025-05-31 */
		if (large) {
		    goto L15;
		}
/* 7/91 STORE CHANGES IN THE STRUCTURE. THESE CHANGES ARE USED TO GET AN */
/* IMPROVED FIRST GUESS AT THE STRUCTURE FOR THE NEXT MODEL IF LNEWS=T. */
		if (delts > 0.) {
		    i__4 = m;
		    for (ii = 1; ii <= i__4; ++ii) {
			entrop_1.htt0[ii - 1] = htt[ii - 1] / delts;
			entrop_1.hpp0[ii - 1] = hpp[ii - 1] / delts;
			entrop_1.hll0[ii - 1] = (hl[ii - 1] - oldmod_1.hlo[ii 
				- 1]) * 2. / (hl[ii - 1] + oldmod_1.hlo[ii - 
				1]) / delts;
			entrop_1.hrr0[ii - 1] = (hr[ii - 1] - oldmod_1.hro[ii 
				- 1]) / delts;
/* L27: */
		    }
		}
/* THIRD LEVEL OF ITERATIONS */
		lsbc = FALSE_;
		niter = ctol_1.niter3;
		itlvl = 3;
		crrect_(&delts, &m, &niter, &lfini, &large, &lnew, &lreset, &
			lsbc, trit, tril, cfenv, ps, ts, rs, &ftri, &istore, 
			estore, &hstot, &bl, &teffl, hd, hha, hhb, hhc, hl, 
			hmax, hp, hpp, hr, hs, hs1, hs2, hsrf, ht, htt, hcomp,
			 lc, nhmax, tlumx, &latmo, &lderiv, &lmix, &locond, &
			qdt, &qdp, fp, ft, eta2, omega, r0, &itdone, hg, hi, 
			hjm, &itlvl, lcz, mxzone, qiw, hkerot, hkeroto);
/*      *           LMIX,LOCOND,QDT,QDP,MODEL,FP,FT,ETA2,OMEGA,R0,ITDONE, */
/*      *           HG,HI,HJM, ITLVL,LCZ,MRZONE,MXZONE,NRZONE,NZONE,  ! KC 2025-05-31 */
		if (large) {
		    goto L15;
		}
		if (! rot_1.lrot) {
		    difus_1.itdif1 = 1;
		}
/* MHP 05/02 */
/* IF THE CODE IS ITERATING BETWEEN THE STRUCTURE AND ROTATION */
/* SOLUTIONS, ENSURE THAT THE START-OF-TIMESTEP QUANTITIES */
/* HCOMPP (COMPOSITION) AND HJMSAV (ANGULAR MOMENTUM) ARE ONLY */
/* OVERWRITTEN ON THE LAST RUN THROUGH. */
		if (difus_1.itdif1 > 1) {
		    i__4 = m;
		    for (i__ = 1; i__ <= i__4; ++i__) {
			origstart_1.hjm0[i__ - 1] = hjm[i__ - 1];
			for (j = 1; j <= 15; ++j) {
			    origstart_1.hcompp0[j + i__ * 15 - 16] = 
				    oldmod_1.hcompp[j + i__ * 15 - 16];
			}
		    }
		}
		i__4 = difus_1.itdif1;
		for (itrot = 1; itrot <= i__4; ++itrot) {
/* MHP 05/02 RESTORE ORIGINAL "START OF TIMESTEP" */
/* VALUES FOR THE COMPOSITION MATRIX */
		    if (itrot > 1) {
			i__5 = m;
			for (i__ = 1; i__ <= i__5; ++i__) {
			    for (j = 1; j <= 15; ++j) {
				oldmod_1.hcompp[j + i__ * 15 - 16] = 
					origstart_1.hcompp0[j + i__ * 15 - 16]
					;
			    }
			}
		    }
/* 7/91 THE FOURTH LEVEL OF ITERATION REPEATS THE ITERATION BETWEEN THE */
/* MIXING AND THE STRUCTURE VARIABLES.  IT SHOULD NOT BE USED FOR MODELS */
/* WHERE SEMI-CONVECTION IS IMPORTANT (ITERATING BETWEEN THE BURNING AND */
/* STRUCTURE GENERATES OSCILLATIONS). IT SHOULD BE USED FOR HIGH-PRECISION */
/* WORK (E.G. SOLAR MODELS). */
/* Surface boundary conditions checked again since we've changed the */
/* composition (and hence the structure) of the model in ITLVL=3 */
/* (to be implemented when I know the rest of it works!) */
		    niter = neweng_1.niter4;
		    lsbc = FALSE_;
		    itlvl = 4;
		    crrect_(&delts, &m, &niter, &lfini, &large, &lnew, &
			    lreset, &lsbc, trit, tril, cfenv, ps, ts, rs, &
			    ftri, &istore, estore, &hstot, &bl, &teffl, hd, 
			    hha, hhb, hhc, hl, hmax, hp, hpp, hr, hs, hs1, 
			    hs2, hsrf, ht, htt, hcomp, lc, nhmax, tlumx, &
			    latmo, &lderiv, &lmix, &locond, &qdt, &qdp, fp, 
			    ft, eta2, omega, r0, &itdone, hg, hi, hjm, &itlvl,
			     lcz, mxzone, qiw, hkerot, hkeroto);
/*      *           LMIX,LOCOND,QDT,QDP,MODEL,FP,FT,ETA2,OMEGA,R0,ITDONE, */
/*      *           HG,HI,HJM,ITLVL,LCZ,MRZONE,MXZONE,NRZONE,NZONE,  ! KC 2025-05-31 */
/*  25         CONTINUE */
		    if (! lfini) {
/* MODEL FAILED TO CONVERGE WITHIN(NITER1+NITER2+NITER3+NITER4)ITERATIONS */
			large = TRUE_;
			goto L15;
		    }
/* MODEL HAS CONVERGED */
/* ENSURE CONVECTION ZONES ARE FULLY MIXED. */
/* MHP 02/12 INFER CONVECTIVE OVERTURN TIMESCALE (USED IN MDOT) */
/* JVS 02/12 CALL MIXCZ(HCOMP,HS2,LC,M) */
/* KC 2025-05-30 addressed warning messages from Makefile.legacy */
/* C G Somers 6/14, SET IMIX = .TRUE. SO THE CORRECT GRADS ARE USED. */
/*       IMIX = .TRUE. */
/*       CALL MIXCZ(HCOMP,HS2,HS1,LC,HR,HP,HD,HG,M,IMIX) */
/* G Somers 6/14, SET LIMIX = .TRUE. SO THE CORRECT GRADS ARE USED. */
		    limix = TRUE_;
/*       CALL MIXCZ(HCOMP,HS2,HS1,LC,HR,HP,HD,HG,M,LIMIX)  ! KC 2025-05-31 */
		    mixcz_(hcomp, hs2, lc, &m);
/* G Somers END */
/* MHP 9/94 STORE TOTAL AGE IN SAGE */
		    disk_1.sage = theage_1.dage;
		    if (rot_1.lrot) {
/* RESTORE ORIGINAL START OF TIMESTEP VALUES */
/* TO THE ANGULAR MOMENTUM DISTRIBUTION */
			if (itrot > 1) {
			    i__5 = m;
			    for (i__ = 1; i__ <= i__5; ++i__) {
				hjm[i__ - 1] = origstart_1.hjm0[i__ - 1];
			    }
			}
/* MHP 9/94 ADDED FLAG TO TURN ON ROTATION OUTPUT WHEN END OF KIND */
/* CARD REACHED. */
/* MHP 10/24 GENERALIZE CHECK */
			if (sett_1.lendag[zramp_1.nk - 1] && sett_1.endage[
				zramp_1.nk - 1] > 0. && (d__1 = sett_1.endage[
				zramp_1.nk - 1] - theage_1.dage * 1e9 - ddage,
				 abs(d__1)) <= 1.) {
/*               IF(LENDAG(NK).AND.ENDAGE(NK)-DAGE*1.0D9.LE.1.0D0)THEN */
			    rotprt_1.lprt0 = TRUE_;
			} else {
			    rotprt_1.lprt0 = FALSE_;
			}
/* FIND THE NEW RUN OF OMEGA */
/* JENV0 ADDED TO SR CALL. */
			ljdot = cwind_1.ljdot0;
			getw_(&bl, &delts, &dwmax, fp, ft, hcomp, hd, hjm, hl,
				 hp, hr, hs, hs1, hs2, &hstot, ht, lc, &ljdot,
				 &m, &smass, &teffl, eta2, hg, hi, omega, qiw,
				 r0, &jenv0);
/*      *              HS,HS1,HS2,HSTOT,HT,LC,LJDOT,M,MODEL,SJTOT,SMASS,  ! KC 2025-05-31 */
/* CALCULATE FP AND FT GIVEN OMEGA FOR THE NEW POINT DISTRIBUTION */
			fpft_(hd, hr, hs, &m, omega, eta2, fp, ft, hg, r0);
		    }
		}
/* LOCATE THE HYDROGEN-BURNING SHELL AND THE BOUNDARIES OF THE CENTRAL */
/* AND SURFACE CONVECTION ZONES (IF APPLICABLE). */
		findsh_(hcomp, hl, lc, &m, &jcore, &jenv, &jxbeg, &jxend, &
			jxmid, &lshell);
/* PERFORM LIGHT ELEMENT BURNING */
		if (flag_1.lexcom && model >= 0 && delts > 0.) {
/* ONLY FOR MODELS WITHOUT ROTATION, OR WITHOUT ROTATIONAL MIXING. */
		    if (! rot_1.lrot || ! rot_1.linstb) {
/* FIND CONVECTION ZONE DEPTH AT THE END OF THE TIME STEP. */
			convec_(hcomp, hd, hp, hr, hs, ht, lc, &m, mrzone, 
				mxzone, mxzon0, &jcore, &jenv, &nrzone, &
				nzone, &nzone0);
/* CHANGED FOR LITHIUM BURNING WITH OVERSHOOT. */
			jenv1 = jenv;
			if (dpmix_1.lovste) {
			    liov_1.pscal1 = dpmix_1.alphae * exp(
				    const3_1.clndp * (hp[jenv - 1] + hr[jenv 
				    - 1] * 2. - hd[jenv - 1] - const2_1.cgl - 
				    hs[jenv - 1]));
			} else {
			    liov_1.pscal1 = 0.;
			}
/* FIND BURNING RATES AT THE END OF THE TIME STEP. */
			lirate88_(hcomp, hd, ht, &m, &c__2);
/*                CALL LIBURN(DELTS,HCOMP,HD,HR,HS1,HS2,HT,JENV1,JENV0,M)  ! KC 2025-05-31 */
			liburn_(&delts, hcomp, hr, hs1, hs2, ht, &jenv1, &
				jenv0, &m);
		    }
		}
/* MHP 07/02 RESTORE PRIOR FITTING POINT IF MASS ACCRETION IS BEING */
/* INCLUDED */
		if (lnewfit) {
		    getnewenv_(&senvold, hcomp, hd, hl, hp, hr, hs, hs1, hs2, 
			    &hstot, ht, lc, eta2, hi, hjm, qiw, r0, hkerot, &
			    bl, &sjtot, &skerot, &teffl, &m, &lnew);
/*     *                     HSTOT,HT,LC,ETA2,HG,HI,HJM,QIW,R0,  ! KC 2025-05-31 */
/* CALCULATE FP AND FT GIVEN OMEGA FOR THE NEW POINT DISTRIBUTION */
		    fpft_(hd, hr, hs, &m, omega, eta2, fp, ft, hg, r0);
		    lnewfit = FALSE_;
		}
/* DETERMINE TIMESTEP FOR NEXT MODEL */
/* HTIMER ALSO LOCATES THE H-BURNING SHELL */
/* JVS 04/14 added teffl to passed htimer variables */
		delts = abs(delts);
		delts0 = delts;
/*        CALL HTIMER(DELTS,DELTSH,M,HD,HL,HS1,HS2,HT,LC,HCOMP,JCORE, */
/*      *        JXMID,TLUMX,DAGE,DDAGE,QDT,QDP,NK,HP,HR,OMEGA,  ! KC 2025-05-31 */
		htimer_(&delts, &deltsh, &m, hd, hl, hs1, hs2, ht, hcomp, &
			jcore, &jxmid, tlumx, &theage_1.dage, &ddage, &
			zramp_1.nk, hp, hr, omega, &dwmax, &jxbeg, &teffl);
/*  IF EVOLVING TO A GIVEN AGE AND KIND CARD IS DONE, AVOID ZEROING OUT */
/*  TIMESTEP WRITTEN TO MODEL (AS THIS MAKES CONTINUING A SEQUENCE AWKWARD.) */
/*     INSTEAD WRITE THE PREVIOUS MODEL TIMESTEP TO MODEL. */
/* ONLY IF A FIXED END AGE IS USED, NOT FOR OTHER STOPS */
		if (sett_1.lendag[zramp_1.nk - 1] && sett_1.endage[zramp_1.nk 
			- 1] > 0.) {
		    if (sett_1.endage[zramp_1.nk - 1] - theage_1.dage * 1e9 <=
			     1.) {
/* Computing MAX */
			d__1 = delts0, d__2 = theage_1.dage * .001 * 
				const3_1.csecyr;
			delts = max(d__1,d__2);
			ddage = delts / const3_1.csecyr;
		    } else {
			delts0 = delts;
		    }
		} else {
		    delts0 = delts;
		}
		if (ckind_1.iresca[zramp_1.nk - 1] != 2) {
		    ++model;
		}
/* WRTOUT IS THE OUTPUT DRIVER ROUTINE */
		wrtout_(hcomp, hd, hl, hp, hr, hs, hs1, ht, lc, &m, &model, &
			theage_1.dage, &ddage, &smass, &teffl, &bl, &gl, &
			lshell, &jxbeg, &jxmid, &jxend, &jcore, &jenv, tlumx, 
			trit, tril, ps, ts, rs, cfenv, &ftri, &hstot, omega, &
			lpunch, fp, ft, eta2, r0, hjm, hi, &sjtot, &skerot, 
			hs2);
/*      *        LPUNCH,FP,FT,ETA2,R0,HJM,HI,SJTOT,SKEROT,HS2,NK)  ! KC 2025-05-31 */
/* MHP 10/24 GENERALIZED STOP CONDITIONS */
/*     IF EVOLVING TO A GIVEN AGE AND AGE IS REACHED, KIND CARD IS DONE */
/*       IF(LENDAG(NK).AND.ENDAGE(NK)-DAGE*1.0D9.LE.1.0D0)GOTO 110 */
		if (sett_1.lendag[zramp_1.nk - 1] && sett_1.endage[zramp_1.nk 
			- 1] > 0. && sett_1.endage[zramp_1.nk - 1] - 
			theage_1.dage * 1e9 <= 1.) {
		    goto L110;
		}
/* MHP 10/24 CHECK ALL STOP CONDITIONS, EXIT IF ANY SATISFIED */
		lend_kind__ = FALSE_;
		if (sett_1.lendag[zramp_1.nk - 1] && sett_1.end_dcen__[
			zramp_1.nk - 1] > 0. && hcomp[11] < sett_1.end_dcen__[
			zramp_1.nk - 1]) {
		    s_wsfe(&io___185);
		    do_fio(&c__1, (char *)&hcomp[11], (ftnlen)sizeof(
			    doublereal));
		    do_fio(&c__1, (char *)&sett_1.end_dcen__[zramp_1.nk - 1], 
			    (ftnlen)sizeof(doublereal));
		    e_wsfe();
		    lend_kind__ = TRUE_;
		}
		if (sett_1.lendag[zramp_1.nk - 1] && sett_1.end_xcen__[
			zramp_1.nk - 1] > 0. && hcomp[0] < sett_1.end_xcen__[
			zramp_1.nk - 1]) {
		    s_wsfe(&io___186);
		    do_fio(&c__1, (char *)&hcomp[0], (ftnlen)sizeof(
			    doublereal));
		    do_fio(&c__1, (char *)&sett_1.end_xcen__[zramp_1.nk - 1], 
			    (ftnlen)sizeof(doublereal));
		    e_wsfe();
		    lend_kind__ = TRUE_;
		}
		if (sett_1.lendag[zramp_1.nk - 1] && sett_1.end_ycen__[
			zramp_1.nk - 1] > 0. && hcomp[1] < sett_1.end_ycen__[
			zramp_1.nk - 1]) {
		    s_wsfe(&io___187);
		    do_fio(&c__1, (char *)&hcomp[1], (ftnlen)sizeof(
			    doublereal));
		    do_fio(&c__1, (char *)&sett_1.end_ycen__[zramp_1.nk - 1], 
			    (ftnlen)sizeof(doublereal));
		    e_wsfe();
		    lend_kind__ = TRUE_;
		}
/* IF EXITING, SET I/O FLAGS PROPERLY AND EXIT LOOP */
		if (lend_kind__) {
		    pulse_1.lpulse = lsavpu;
		    sound_1.lsound = TRUE_;
		    rotprt_1.lprt0 = TRUE_;
		    goto L110;
		}
/* TEST IF MODEL IS NEAR DESIRED Teff AND L. IF NOT RESCALE AND TRY AGAIN. */
		if (calstar_1.lcalst && ! calstar_1.lstar) {
		    if (zramp_1.nk % 2 == 0) {
			if (modeln == 1) {
			    teffi = pow_dd(&c_b105, &teffl);
			} else {
			    chkscal_(&bl, &teffl, &theage_1.dage, &zramp_1.nk)
				    ;
			    if (calstar_1.lpassr) {
				goto L200;
			    }
			}
		    }
		}
/* END OF RUN */
/* L100: */
	    }
/* G Somers 11/14, CHANGE CALL TO PUTSTORE INSTEAD OF WRTLST. */
/* STORE LAST MODEL IN ISTOR IF LSTORE, LSTPCH, AND LPUNCH ARE .TRUE. */
L110:
	    if (ccout_1.lstore && ccout2_1.lstpch && lpunch) {
		putstore_(hcomp, hd, hl, hp, hr, hs, ht, lc, trit, tril, ps, 
			ts, rs, cfenv, &ftri, tlumx, &jcore, &jenv, &model, &
			m, &smass, &teffl, &bl, &hstot, &theage_1.dage, &
			ddage, omega, hs1, eta2, r0, fp, ft, hjm, hi);
		lpunch = FALSE_;
	    }
/* 110  CONTINUE */
/* G Somers END */
/* MHP 1/93 CHECK AUTOMATIC CALIBRATATION OF SOLAR MODEL. */
/* MHP 5/96 changed solar calibration to perform solar models in 3 kind cards */
	    if (cals2_1.lcals) {
/* JVS Turn off calcad - speeds things up */
		acdpth_1.ladon = FALSE_;
		if (zramp_1.nk % 3 == 0) {
		    rll = (bl + const_1.clsunl - const1_1.c4pil - 
			    const2_1.csigl - teffl * 4.) * .5 - 
			    const_1.crsunl;
/* MHP 06/13 Add solar Z/X to observables */
		    solzx = hcomp[m * 15 - 13] / hcomp[m * 15 - 15];
		    chkcal_(&bl, &rll, &zramp_1.nk, &solzx);
/*               CALL CHKCAL(BL,RLL,NK) */
		    ct3_1.lptime = lptimesv;
/* Restore LPTIME to original value for next cycle */
		    atmos_1.kttau = kttausv;
/* Restore KTTAU to original value for next cycle */
		    if (calsun_1.lsol) {
			goto L250;
		    } else {
/* MHP 8/96 added counter for # of runs needed for calibration */
			++iconv;
/* MHP 6/97 STOP AFTER 10 ATTEMPTS AT CALIBRATION */
/*                  IF(ICONV.GE.11) GOTO 250 */
			if (iconv >= 15) {
			    goto L250;
			}
			if (pulse_1.lpulse) {
/* DBG 6/93 Need to delete pulse output because have not got ultimate */
/* model yet. */
/* MHP 8/25 Replaced delete file with rewind file. This is functionally the same and avoids the need to pass t
he character string for the file name from parmin. */
			    al__1.aerr = 0;
			    al__1.aunit = lunum_1.iopmod;
			    f_rew(&al__1);
			    al__1.aerr = 0;
			    al__1.aunit = lunum_1.iopenv;
			    f_rew(&al__1);
			    al__1.aerr = 0;
			    al__1.aunit = lunum_1.iopatm;
			    f_rew(&al__1);
/*                     CLOSE(IOPMOD, STATUS='DELETE') */
/*                     CLOSE(IOPENV, STATUS='DELETE') */
/*                     CLOSE(IOPATM, STATUS='DELETE') */
/*                     OPEN(IOPMOD, FILE=FPMOD,STATUS='UNKNOWN', */
/*     *                    FORM='FORMATTED') */
/*                     OPEN(IOPENV, FILE=FPENV,STATUS='UNKNOWN', */
/*     *                    FORM='FORMATTED') */
/*                     OPEN(IOPATM, FILE=FPATM,STATUS='UNKNOWN', */
/*     *                    FORM='FORMATTED') */
			}
		    }
		}
	    }
/* DBG 12/94 NO MORE RUNS NEEDED. HAVE CALIBRATED STELLAR MODEL */
	    if (calstar_1.lcalst && calstar_1.lstar && zramp_1.nk % 2 == 0) {
		goto L250;
	    }
/* END RUN LOOP */
L200:
	    ;
	}
/* EXIT RUN LOOP */
L250:
/* FOR MONTE CARLO, REWIND OUTPUT FILES AND WRITE OUT SNU FLUXES AND */
/* MODEL PARAMTERS TO AN OUTPUT FILE. */
/* RUN FAILED TO CONVERGE.  WRITE FINAL INFO WITH WARNING NOTE. */
	if (monte_1.lmonte && iconv >= 11 && ! calsun_1.lsol) {
	    al__1.aerr = 0;
	    al__1.aunit = luout_1.ilast;
	    f_rew(&al__1);
	    al__1.aerr = 0;
	    al__1.aunit = lunum_1.ifirst;
	    f_rew(&al__1);
	    al__1.aerr = 0;
	    al__1.aunit = luout_1.idebug;
	    f_rew(&al__1);
	    al__1.aerr = 0;
	    al__1.aunit = luout_1.itrack;
	    f_rew(&al__1);
	    al__1.aerr = 0;
	    al__1.aunit = luout_1.ishort;
	    f_rew(&al__1);
	    al__1.aerr = 0;
	    al__1.aunit = luout_1.imodpt;
	    f_rew(&al__1);
	    al__1.aerr = 0;
	    al__1.aunit = luout_1.istor;
	    f_rew(&al__1);
	    io___191.ciunit = lunum_1.isnu;
	    s_wsfe(&io___191);
	    do_fio(&c__1, (char *)&bl, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&rll, (ftnlen)sizeof(doublereal));
	    e_wsfe();
/* MONTE CARLO #, CONVERGED MIXING LENGTH AND INITIAL H, SURFACE X, */
/* SURFACE Z, Z/X, CENTRAL X, CENTRAL Z */
	    io___192.ciunit = lunum_1.isnu;
	    s_wsfe(&io___192);
	    do_fio(&c__1, (char *)&nn, (ftnlen)sizeof(integer));
	    do_fio(&c__1, (char *)&newxym_1.cmixla[zramp_1.nk - 1], (ftnlen)
		    sizeof(doublereal));
	    do_fio(&c__1, (char *)&ckind_1.rescal[(zramp_1.nk - 2 << 2) - 3], 
		    (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&hcomp[m * 15 - 15], (ftnlen)sizeof(
		    doublereal));
	    do_fio(&c__1, (char *)&hcomp[m * 15 - 13], (ftnlen)sizeof(
		    doublereal));
	    do_fio(&c__1, (char *)&ztox, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&hcomp[0], (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&hcomp[2], (ftnlen)sizeof(doublereal));
	    e_wsfe();
/* NUMERICAL DATA : #OF RUNS NEEDED FOR A CONVERGED MODEL, INITIAL X */
/* AND ALPHA, FINAL DL/DX,DR/DX,DL/D ALPHA, DR/D ALPHA */
	    io___194.ciunit = lunum_1.isnu;
	    s_wsfe(&io___194);
	    do_fio(&c__1, (char *)&iconv, (ftnlen)sizeof(integer));
	    do_fio(&c__1, (char *)&xguess, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&aguess, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&calsun_1.dldx, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&calsun_1.drdx, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&calsun_1.dlda, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&calsun_1.drda, (ftnlen)sizeof(doublereal));
	    e_wsfe();
/* SUMMARY OF STRUCTURE : TC, RHOC, PC */
	    io___195.ciunit = lunum_1.isnu;
	    s_wsfe(&io___195);
	    do_fio(&c__1, (char *)&cent_1.tcenter, (ftnlen)sizeof(doublereal))
		    ;
	    do_fio(&c__1, (char *)&cent_1.pcenter, (ftnlen)sizeof(doublereal))
		    ;
	    do_fio(&c__1, (char *)&cent_1.dcenter, (ftnlen)sizeof(doublereal))
		    ;
	    do_fio(&c__1, (char *)&hcomp[0], (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&hcomp[2], (ftnlen)sizeof(doublereal));
	    e_wsfe();
/* NEUTRINO FLUXES (SEE ENGEB FOR DETAILS) */
	    io___196.ciunit = lunum_1.isnu;
	    s_wsfe(&io___196);
	    do_fio(&c__1, (char *)&fluxes_1.clsnu, (ftnlen)sizeof(doublereal))
		    ;
	    do_fio(&c__1, (char *)&fluxes_1.gasnu, (ftnlen)sizeof(doublereal))
		    ;
	    for (i__ = 1; i__ <= 8; ++i__) {
		do_fio(&c__1, (char *)&fluxes_1.fluxtot[i__ - 1], (ftnlen)
			sizeof(doublereal));
	    }
	    e_wsfe();
/*          CALL WRTMONTE(HCOMP,HD,HL,HP,HR,HS,HT,LC,M,MODEL,DAGE, */
/*      *        DDAGE,SMASS,TEFFL,BL,GL,LSHELL,JXBEG,JXMID, */
/*      *        JXEND,JCORE,JENV,TLUMX,TRIT,TRIL,PS,TS,RS, */
/*      *        CFENV,FTRI,HSTOT,OMEGA,RLL,ICONV,NK,NN)  ! KC 2025-05-31 */
	    wrtmonte_(hcomp, hd, hl, hp, hr, hs, ht, lc, &m, &theage_1.dage, &
		    ddage, &smass, &teffl, &bl, &jcore, &jenv, tlumx, trit, 
		    tril, ps, ts, rs, cfenv, &ftri, &hstot, omega, &rll, &
		    iconv, &zramp_1.nk, &nn);
	} else if (cals2_1.lcals && neweng_1.lsnu && calsun_1.lsol) {
	    al__1.aerr = 0;
	    al__1.aunit = luout_1.ilast;
	    f_rew(&al__1);
	    al__1.aerr = 0;
	    al__1.aunit = lunum_1.ifirst;
	    f_rew(&al__1);
	    al__1.aerr = 0;
	    al__1.aunit = luout_1.idebug;
	    f_rew(&al__1);
	    al__1.aerr = 0;
	    al__1.aunit = luout_1.itrack;
	    f_rew(&al__1);
	    al__1.aerr = 0;
	    al__1.aunit = luout_1.ishort;
	    f_rew(&al__1);
	    al__1.aerr = 0;
	    al__1.aunit = luout_1.imodpt;
	    f_rew(&al__1);
	    al__1.aerr = 0;
	    al__1.aunit = luout_1.istor;
	    f_rew(&al__1);
	    ztox = hcomp[m * 15 - 13] / hcomp[m * 15 - 15];
/* HEADER FILE:  MONTE CARLO PARAMETERS */
	    if (monte_1.lmonte) {
		io___197.ciunit = lunum_1.isnu;
		s_wsfe(&io___197);
		do_fio(&c__1, (char *)&nn, (ftnlen)sizeof(integer));
		do_fio(&c__1, (char *)&monte2_1.s11[nn - 1], (ftnlen)sizeof(
			doublereal));
		do_fio(&c__1, (char *)&monte2_1.s33[nn - 1], (ftnlen)sizeof(
			doublereal));
		do_fio(&c__1, (char *)&monte2_1.s34[nn - 1], (ftnlen)sizeof(
			doublereal));
		do_fio(&c__1, (char *)&monte2_1.s17[nn - 1], (ftnlen)sizeof(
			doublereal));
		do_fio(&c__1, (char *)&monte2_1.zx[nn - 1], (ftnlen)sizeof(
			doublereal));
		do_fio(&c__1, (char *)&monte2_1.fhe[nn - 1], (ftnlen)sizeof(
			doublereal));
		do_fio(&c__1, (char *)&monte2_1.fzdif[nn - 1], (ftnlen)sizeof(
			doublereal));
		do_fio(&c__1, (char *)&monte2_1.flum[nn - 1], (ftnlen)sizeof(
			doublereal));
		do_fio(&c__1, (char *)&monte2_1.fage[nn - 1], (ftnlen)sizeof(
			doublereal));
		e_wsfe();
	    }
/* NUMERICAL DATA : #OF RUNS NEEDED FOR A CONVERGED MODEL, INITIAL X */
/* AND ALPHA, FINAL DL/DX,DR/DX,DL/D ALPHA, DR/D ALPHA */
	    io___198.ciunit = lunum_1.isnu;
	    s_wsfe(&io___198);
	    do_fio(&c__1, (char *)&iconv, (ftnlen)sizeof(integer));
	    do_fio(&c__1, (char *)&xguess, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&aguess, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&calsun_1.dldx, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&calsun_1.drdx, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&calsun_1.dlda, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&calsun_1.drda, (ftnlen)sizeof(doublereal));
	    e_wsfe();
/* NEUTRINO FLUXES (SEE ENGEB FOR DETAILS) */
	    io___199.ciunit = lunum_1.isnu;
	    s_wsfe(&io___199);
	    do_fio(&c__1, (char *)&fluxes_1.clsnu, (ftnlen)sizeof(doublereal))
		    ;
	    do_fio(&c__1, (char *)&fluxes_1.gasnu, (ftnlen)sizeof(doublereal))
		    ;
	    for (i__ = 1; i__ <= 10; ++i__) {
		do_fio(&c__1, (char *)&fluxes_1.fluxtot[i__ - 1], (ftnlen)
			sizeof(doublereal));
	    }
	    e_wsfe();
/* SUMMARY OF STRUCTURE : TC, RHOC, PC, XC, ZC (ADD MU C) */
	    d__1 = cent_1.tcenter - 6.;
	    tcen = pow_dd(&c_b105, &d__1);
	    d__1 = cent_1.pcenter - 17.;
	    pcen = pow_dd(&c_b105, &d__1);
	    dcen = pow_dd(&c_b105, &cent_1.dcenter);
	    io___203.ciunit = lunum_1.isnu;
	    s_wsfe(&io___203);
	    do_fio(&c__1, (char *)&tcen, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&dcen, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&pcen, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&hcomp[0], (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&hcomp[2], (ftnlen)sizeof(doublereal));
	    e_wsfe();
/* INITIAL ALPHA,Y,Z,ALPHA; FINAL R, L */
	    yini = 1. - ckind_1.rescal[(zramp_1.nk - 2 << 2) - 3] - 
		    ckind_1.rescal[(zramp_1.nk - 2 << 2) - 2];
	    zini = ckind_1.rescal[(zramp_1.nk - 2 << 2) - 2];
	    io___206.ciunit = lunum_1.isnu;
	    s_wsfe(&io___206);
	    do_fio(&c__1, (char *)&newxym_1.cmixla[zramp_1.nk - 1], (ftnlen)
		    sizeof(doublereal));
	    do_fio(&c__1, (char *)&yini, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&zini, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&bl, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&rll, (ftnlen)sizeof(doublereal));
	    e_wsfe();
/* CZ DEPTH (R,M), SURFACE Y, Z, Z/X (ADD T CZ BASE, RHO CZ BASE) */
	    io___207.ciunit = lunum_1.isnu;
	    s_wsfe(&io___207);
	    do_fio(&c__1, (char *)&cent_1.envr, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&cent_1.envlm, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&hcomp[m * 15 - 14], (ftnlen)sizeof(
		    doublereal));
	    do_fio(&c__1, (char *)&hcomp[m * 15 - 13], (ftnlen)sizeof(
		    doublereal));
	    do_fio(&c__1, (char *)&ztox, (ftnlen)sizeof(doublereal));
	    e_wsfe();
/* ENERGY GENERATION FRACTIONS PP I,II,III,CNO,EGRAV */
	    io___208.ciunit = lunum_1.isnu;
	    s_wsfe(&io___208);
	    for (j = 1; j <= 4; ++j) {
		do_fio(&c__1, (char *)&tlumx[j - 1], (ftnlen)sizeof(
			doublereal));
	    }
	    do_fio(&c__1, (char *)&tlumx[6], (ftnlen)sizeof(doublereal));
	    e_wsfe();
	    if (monte_1.lmonte) {
/*             CALL WRTMONTE(HCOMP,HD,HL,HP,HR,HS,HT,LC,M,MODEL,DAGE, */
/*      *           DDAGE,SMASS,TEFFL,BL,GL,LSHELL,JXBEG,JXMID, */
/*      *           JXEND,JCORE,JENV,TLUMX,TRIT,TRIL,PS,TS,RS, */
/*      *           CFENV,FTRI,HSTOT,OMEGA,RLL,ICONV,NK,NN)  ! KC 2025-05-31 */
		wrtmonte_(hcomp, hd, hl, hp, hr, hs, ht, lc, &m, &
			theage_1.dage, &ddage, &smass, &teffl, &bl, &jcore, &
			jenv, tlumx, trit, tril, ps, ts, rs, cfenv, &ftri, &
			hstot, omega, &rll, &iconv, &zramp_1.nk, &nn);
	    }
	}
/* L500: */
    }
    s_stop("", (ftnlen)0);
    return 0;
} /* MAIN__ */

