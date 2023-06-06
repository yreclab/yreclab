/* main.f -- translated by f2c (version 20100827).
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
    char flast[256], ffirst[256], frun[256], fstand[256], ffermi[256], fdebug[
	    256], ftrack[256], fshort[256], fmilne[256], fmodpt[256], fstor[
	    256], fpmod[256], fpenv[256], fpatm[256], fdyn[256], flldat[256], 
	    fsnu[256], fscomp[256], fkur[256], fmhd1[256], fmhd2[256], fmhd3[
	    256], fmhd4[256], fmhd5[256], fmhd6[256], fmhd7[256], fmhd8[256];
} lufnm_;

#define lufnm_1 lufnm_

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
    integer itrver;
} track_;

#define track_1 track_

struct {
    doublereal xenv0, zenv0;
} label_;

#define label_1 label_

struct {
    logical lscrib, lpshll, lchemo, lconzo, ljout, lprtin, lpenv;
} ccout_;

#define ccout_1 ccout_

struct {
    logical ldebug, lcorr, lmilne, ltrack, lstore, lstpch;
    integer npunch;
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
    doublereal dpenv, alphac, alphae, alpham;
    integer iov1, iov2, iovim;
    logical lovstc, lovste, lovstm, lsemic, ladov;
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
    doublereal wmax, exmd, exw, exr, exm, factor;
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
    integer kttau;
} atmos_;

#define atmos_1 atmos_

struct {
    logical lrwsh, liso;
    integer iiso;
    char fiso[256];
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
    char flaol2[256], fopal2[256];
} zramp_;

#define zramp_1 zramp_

struct {
    doublereal dage;
} theage_;

#define theage_1 theage_

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
    doublereal toll, tolr;
    logical lcals;
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
    doublereal sstandard[17];
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
    doublereal drate[5000], drate0[5000], fmassacc, taucz;
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

/* Table of constant values */

static integer c__1 = 1;
static integer c__3 = 3;
static integer c__5 = 5;
static integer c__2 = 2;
static doublereal c_b72 = 10.;

integer mode = 0;
integer modeliter = 0;



/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */
/* MAIN */
/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */
/* ******* */
/* initialize all variables, set up common blocks */
/* ******* */
/* the array size, i.e. max # of shells is specified in the */
/* parameter statement.  it defines JSON.  to change the array */
/* size do a global change on "JSON=2000" or whatever. */
/* Main program */ int MAIN__()
{
    /* Initialized data */

    static doublereal sbp[17] = { .9558,.969,.9712,1.,1.,.992,1.,1.,1.,1.,1.,
	    1.,1.,1.,1.,.92088,.1625 };
    static doublereal sunl = 3.844e33;

    /* Format strings */
    static char fmt_1511[] = "(7x,1p7e10.3/e9.3)";
    static char fmt_911[] = "(i5,1p11e10.3)";
    static char fmt_222[] = "(1p10e10.3)";
    static char fmt_145[] = "(f9.5,f7.3,f6.3,1p10e10.3)";
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
    olist o__1;
    cllist cl__1;
    alist al__1;

    /* Builtin functions */
    integer f_open(olist *), s_rsfe(cilist *), do_fio(integer *, char *, 
	    ftnlen), e_rsfe(void), s_wsle(cilist *), do_lio(integer *, 
	    integer *, char *, ftnlen), e_wsle(void);
    double d_lg10(doublereal *), exp(doublereal);
    integer s_wsfe(cilist *), e_wsfe(void), f_rew(alist *);
    double pow_dd(doublereal *, doublereal *);
    integer f_clos(cllist *);
    /* Subroutine */ int s_stop(char *, ftnlen);

    /* Local variables */
    static logical lptimesv;
    extern /* Subroutine */ int massloss_(doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, integer *, logical *, 
	    integer *, doublereal *, doublereal *, doublereal *, doublereal *,
	     logical *), wrtmonte_(doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, logical *,
	     integer *, integer *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, logical *, integer *, 
	    integer *, integer *, integer *, integer *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, integer *, integer *, integer *);
    static integer i__, j, k, m;
    static doublereal v[12], x, y, z__;
    static integer i0, i1;
    static doublereal r0[5000], t6;
    extern /* Subroutine */ int getnewenv_(doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, logical *, doublereal *, doublereal *, doublereal *,
	     doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, integer *,
	     logical *);
    static doublereal hd[5000];
    static logical lc[5000];
    static doublereal hg[5000], hi[5000], bl, dl, hl[5000], fp[5000], hp[5000]
	    , hr[5000], hs[5000], ht[5000], ft[5000], ps[3], rs[3], ts[3];
    static integer nn;
    static doublereal tl, fm, fr, dt, dp, dr;
    static integer ii;
    static doublereal gl, hf1[5000], hf2[5000], ds1, ds2, ds3, hr1[5000], hs1[
	    5000], hs2[5000], hr2[5000], hr3[5000], hr4[5000], hr5[5000], hr6[
	    5000], hr7[5000], hr8[5000], hr9[5000], xh2, hha[40000]	/* 
	    was [4][2][5000] */, hhb[20000]	/* was [4][5000] */, hhc[5000]
	    , ecn, hjm[5000], hpp[5000], htt[5000], qiw[5000], hr10[5000], 
	    hr11[5000], hr12[5000], hr13[5000];
    static logical lcz[5000];
    static doublereal qdp, qdt, vel, pdt, pdp, xc12, xc13, xn14, be7m[5000], 
	    eta2[5000], xn15, xo16, xo17, xo18, e3al, pep, epp1, epp2, xhe3, 
	    epp3, pet, xbe9, pol1, xli6, xli7, pot1, sum1, poa1;
    extern /* Subroutine */ int mix_(doublereal *, doublereal *, doublereal *,
	     doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, integer *,
	     logical *, integer *, doublereal *, doublereal *, doublereal *, 
	    integer *, integer *, integer *, integer *);
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
	    doublereal *, logical *, logical *, integer *, integer *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, integer *), fpft_(doublereal *, doublereal *, 
	    doublereal *, integer *, doublereal *, doublereal *, doublereal *,
	     doublereal *, doublereal *, doublereal *);
    static integer jenv1;
    static doublereal ztox, yini, zini, ddage;
    extern /* Subroutine */ int engeb_(doublereal *, doublereal *, doublereal 
	    *, doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, integer *,
	     doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *);
    static doublereal omega[5000];
    static logical large;
    static doublereal cfenv[9], hcomp[75000]	/* was [15][5000] */;
    static integer nhmax[4];
    static doublereal tlumx[8], fluxi0[50000]	/* was [10][5000] */, facage;
    static integer iconv;
    static doublereal sjtot, delts, delts0, hstot;
    static integer jcore, model;
    static doublereal smass, teffl;
    static integer mxzon0[24]	/* was [12][2] */;
    static doublereal polen;
    static integer jxbeg, jxend;
    static doublereal estore[4], hkerot[5000];
    static integer mxzone[24]	/* was [12][2] */, mrzone[26]	/* was [13][2]
	     */;
    static logical lpunch;
    extern /* Subroutine */ int parmin_(void), setups_(doublereal *);
    static doublereal fgrset;
    static logical lsavpu;
    extern /* Subroutine */ int setcal_(doublereal *);
    static doublereal xguess, aguess;
    static logical lreset;
    static doublereal skerot;
    extern /* Subroutine */ int starin_(doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, integer *, integer *, integer *, 
	    integer *, logical *, logical *, logical *, integer *, integer *, 
	    integer *, doublereal *, doublereal *, doublereal *, doublereal *,
	     doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *);
    static doublereal deltsh;
    static integer istore;
    static logical lnutab;
    static integer iwrite;
    extern /* Subroutine */ int wrtlst_(integer *, doublereal *, doublereal *,
	     doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, logical *, doublereal *, doublereal *, doublereal *,
	     doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, integer *, integer *, integer *, integer *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *), findsh_(doublereal *, 
	    doublereal *, logical *, integer *, integer *, integer *, integer 
	    *, integer *, integer *, logical *);
    static integer jxmid;
    static logical lshell;
    extern /* Subroutine */ int htimer_(doublereal *, doublereal *, integer *,
	     doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, logical *, doublereal *, integer *, integer *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, integer *, doublereal *, doublereal *, doublereal *,
	     doublereal *, integer *);
    static doublereal dwmax;
    static integer modeln;
    extern /* Subroutine */ int pdist_(doublereal *, doublereal *, doublereal 
	    *, doublereal *, doublereal *, doublereal *, integer *);
    static integer nspec, itlvl;
    extern /* Subroutine */ int hpoint_(integer *, doublereal *, doublereal *,
	     doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, logical *, doublereal *, doublereal *, doublereal *,
	     doublereal *, doublereal *, doublereal *, integer *, logical *, 
	    integer *, integer *, logical *, integer *, integer *, doublereal 
	    *, doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *);
    static integer itdone;
    static logical lfini;
    static integer niter;
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
	    doublereal *, integer *, doublereal *, doublereal *, doublereal *,
	     doublereal *, doublereal *, integer *, doublereal *, doublereal *
	    , doublereal *, integer *, logical *, integer *, integer *, 
	    integer *, integer *, doublereal *, doublereal *, doublereal *);
    static logical latmo, lderiv;
    extern /* Subroutine */ int setscal_(void), wrthead_(doublereal *), 
	    lirate88_(doublereal *, doublereal *, doublereal *, integer *, 
	    integer *);
    static logical locond;
    static integer nrzone, nzone, itrot;
    static logical lnewfit;
    extern /* Subroutine */ int mixcz_(doublereal *, doublereal *, logical *, 
	    integer *);
    static doublereal senvold, hkeroto[5000];
    static logical ljdot;
    extern /* Subroutine */ int convec_(doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, logical *,
	     integer *, integer *, integer *, integer *, integer *, integer *,
	     integer *, integer *, integer *);
    static integer nzone0;
    extern /* Subroutine */ int liburn_(doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, integer *, integer *, integer *), wrtout_(
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, logical *,
	     integer *, integer *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, logical *, integer *, 
	    integer *, integer *, integer *, integer *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, logical *, doublereal *, doublereal *, doublereal *,
	     doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, integer *);
    static doublereal teffi;
    extern /* Subroutine */ int chkscal_(doublereal *, doublereal *, 
	    doublereal *, integer *), chkcal_(doublereal *, doublereal *, 
	    integer *);
    static integer kttausv;

    /* Fortran I/O blocks */
    static cilist io___9 = { 0, 0, 0, fmt_1511, 0 };
    static cilist io___10 = { 0, 0, 0, 0, 0 };
    static cilist io___120 = { 0, 6, 0, fmt_911, 0 };
    static cilist io___121 = { 0, 76, 0, fmt_222, 0 };
    static cilist io___126 = { 0, 76, 0, fmt_145, 0 };
    static cilist io___179 = { 0, 0, 0, fmt_1525, 0 };
    static cilist io___180 = { 0, 0, 0, fmt_1519, 0 };
    static cilist io___182 = { 0, 0, 0, fmt_1518, 0 };
    static cilist io___183 = { 0, 0, 0, fmt_1517, 0 };
    static cilist io___184 = { 0, 0, 0, fmt_1516, 0 };
    static cilist io___185 = { 0, 0, 0, fmt_1520, 0 };
    static cilist io___186 = { 0, 0, 0, fmt_1518, 0 };
    static cilist io___187 = { 0, 0, 0, fmt_1516, 0 };
    static cilist io___191 = { 0, 0, 0, fmt_1517, 0 };
    static cilist io___194 = { 0, 0, 0, fmt_1521, 0 };
    static cilist io___195 = { 0, 0, 0, fmt_1522, 0 };
    static cilist io___196 = { 0, 0, 0, fmt_1523, 0 };


/* DBGLAOL - to save space make tables single precision */
/* DBGLAOL */
/* 11/91 COMMON BLOCKS ADDED FOR PRESSURE SCALE HEIGHT CALC. FOR LIBURN */
/* MHP 05/02 ADDED OPTION TO ITERATE BETWEEN ROTATION AND */
/* STRUCTURE CALCULATIONS - SET ITDIF1 GREATER THAN 1 */
/* 7/91 ENTROPY TERM COMMON BLOCK ADDED. */
/* 7/91 FLAG TO TOGGLE BETWEEN NEW/OLD RATES ADDED. */
/* MHP 9/94 */
/* MHP 9/94 ADDED DISK LOCKING OPTION - FLAG, TIME OVER WHICH LOCKING */
/* IS ENFORCED, AND PERIOD AT WHICH LOCKING IS SET ARE OPTIONS. */
/* DBG 1/92 let XENV0, ZENV0, and CMIXL be arrays so can change during */
/* a set of runs. */
/* DBG 4/26/94 Tired of not have access to current age of model so... */
/* DBG PULSE OUT 7/92 */
/* variables used to contral output of pulsation models.  model */
/* output after has traveled pomax in HR diagram */
/* LPOUT and POMAX added to control common block, rest in physics */
/* MHP 1/93 add common blocks for automatic calibration of solar models. */
/* DBG 12/94 added calibrate stellar model */
/* MHP 7/96 common block added for sound speed */
/* MHP 8/96 monte carlo option for snus added. */
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
/* latest values (Bahcall and Pinsonneault 1996)-actual values set in */
/* subroutine PARMIN */
/* MHP 3/96 added data for base solar age, L */
/* ******* */
/* START */
/* ******* */
    if (mode == 0){
    luout_1.iowr = 9;
/* LPUNCH is TRUE once first model is calculated */
    lpunch = FALSE_;
/* read in user parameters */
    parmin_();
/* set up constants and read in tabular data */
    setups_(v);
/* MHP 3/96 changed I/O to read in only up to max run needed. */
    if (monte_1.lmonte) {
	o__1.oerr = 0;
	o__1.ounit = lunum_1.idyn;
	o__1.ofnmlen = 256;
	o__1.ofnm = lufnm_1.fdyn;
	o__1.orl = 0;
	o__1.osta = "OLD";
	o__1.oacc = 0;
	o__1.ofm = "FORMATTED";
	o__1.oblnk = 0;
	f_open(&o__1);
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
	}}
	mode = 1;
	}
/* ********** */
/*     RUN THROUGH THE KIND CARDS IN ORDER */
/* ********** */
    if (mode > 0){
	i__2 = ckind_1.numrun;
	zramp_1.nk = mode;
	if (zramp_1.nk <= i__2 && modeliter == 0) {
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
	    starin_(&bl, cfenv, &theage_1.dage, &ddage, &delts, &deltsh, &
		    delts0, eta2, fp, ft, &ftri, hcomp, hd, hi, hjm, hkerot, 
		    hl, hp, hr, hs, hs1, hs2, &hstot, ht, &ikut, &istore, &
		    jcore, &jenv, &large, lc, &lnew, &m, &model, &zramp_1.nk, 
		    omega, ps, &qdp, &qdt, qiw, r0, rs, &sjtot, &skerot, &
		    smass, &teffl, tlumx, tril, trit, ts, &vel, hg, v);
/* MHP 2/04 NEUTRINO TABLE */
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
			    sum1, &dl, &tl, &pdt, &pdp, &x, &y, &z__, &xhe3, &
			    xc12, &xc13, &xn14, &xn15, &xo16, &xo17, &xo18, &
			    xh2, &xli6, &xli7, &xbe9, &i__, hr1, hr2, hr3, 
			    hr4, hr5, hr6, hr7, hr8, hr9, hr10, hr11, hr12, 
			    hr13, hf1, hf2);
/* BE7 MASS FRACTION. */
		    be7m[i__ - 1] = be7_1.be7massfraction;
/* CONVERT FROM ERG/GM/S TO ERG/S FOR EACH SHELL BY MULTIPLYING */
/* BY THE MASS OF EACH SHELL IN GM (HS2). */
		    for (j = 1; j <= 10; ++j) {
			fluxi0[j + i__ * 10 - 11] = fluxes_1.flux[j - 1] * 
				hs2[i__ - 1];
			fluxes_1.fluxtot[j - 1] += fluxi0[j + i__ * 10 - 11];
		    }
		    s_wsfe(&io___120);
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
		s_wsfe(&io___121);
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
		    s_wsfe(&io___126);
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
	    deuter_1.taucz = 0.;
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
	    htimer_(&delts, &deltsh, &m, hd, hl, hs1, hs2, ht, lc, hcomp, &
		    jcore, &jxmid, tlumx, &theage_1.dage, &ddage, &qdt, &qdp, 
		    &zramp_1.nk, hp, hr, omega, &dwmax, &jxbeg);
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
	    if(modeliter <= ckind_1.nmodls[zramp_1.nk - 1]){
	    ++modeliter;}
	    else {
			modeliter = 1;
			++mode;
			zramp_1.nk = mode;
			}}
/* for a given kind card, evolve NMODLS(NK) times */
/* if rescaling is being performed, NMODLS(NK) is the number of times */
/* the new model is being relaxed */
        if(zramp_1.nk <= i__2 && modeliter > 0){
	    i__3 = ckind_1.nmodls[zramp_1.nk - 1];
	    if(modeliter <= i__3){
	    modeln = modeliter;
//	    for (modeln = 1; modeln <= i__3; ++modeln) {
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
/* DBG PULSE:  if endage reached then set LPULSE to LSAVPU */
		if (sett_1.lendag[zramp_1.nk - 1] && (d__1 = sett_1.endage[
			zramp_1.nk - 1] - theage_1.dage * 1e9 - ddage, abs(
			d__1)) <= 1.) {
		    pulse_1.lpulse = lsavpu;
/* MHP 7/96 compute sound speed for solar model */
		    sound_1.lsound = TRUE_;
		}
		if (po_1.lpout) {
		    pdist_(&pol1, &pot1, &poa1, &polen, &bl, &teffl, &modeln);
		}
/* STARIN called here for timestep cutting */
L15:
		if (large) {
		    starin_(&bl, cfenv, &theage_1.dage, &ddage, &delts, &
			    deltsh, &delts0, eta2, fp, ft, &ftri, hcomp, hd, 
			    hi, hjm, hkerot, hl, hp, hr, hs, hs1, hs2, &hstot,
			     ht, &ikut, &istore, &jcore, &jenv, &large, lc, &
			    lnew, &m, &model, &zramp_1.nk, omega, ps, &qdp, &
			    qdt, qiw, r0, rs, &sjtot, &skerot, &smass, &teffl,
			     tlumx, tril, trit, ts, &vel, hg, v);
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
			    ht, &itlvl, lc, &m, &qdt, &qdp, &ddage, &jcore, &
			    jenv, mxzone, mxzon0);
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
			    hi, hjm, hkerot, &sjtot, &skerot, &bl, &delts, fp,
			     ft, hg, qiw, &smass, &teffl);
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
			qdt, &qdp, &model, fp, ft, eta2, omega, r0, &itdone, 
			hg, hi, hjm, &itlvl, lcz, mrzone, mxzone, &nrzone, &
			nzone, qiw, hkerot, hkeroto);
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
			qdt, &qdp, &model, fp, ft, eta2, omega, r0, &itdone, 
			hg, hi, hjm, &itlvl, lcz, mrzone, mxzone, &nrzone, &
			nzone, qiw, hkerot, hkeroto);
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
			qdt, &qdp, &model, fp, ft, eta2, omega, r0, &itdone, 
			hg, hi, hjm, &itlvl, lcz, mrzone, mxzone, &nrzone, &
			nzone, qiw, hkerot, hkeroto);
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
			    latmo, &lderiv, &lmix, &locond, &qdt, &qdp, &
			    model, fp, ft, eta2, omega, r0, &itdone, hg, hi, 
			    hjm, &itlvl, lcz, mrzone, mxzone, &nrzone, &nzone,
			     qiw, hkerot, hkeroto);
/* L25: */
		    if (! lfini) {
/* MODEL FAILED TO CONVERGE WITHIN(NITER1+NITER2+NITER3+NITER4)ITERATIONS */
			large = TRUE_;
			goto L15;
		    }
/* MODEL HAS CONVERGED */
/* ENSURE CONVECTION ZONES ARE FULLY MIXED. */
		    mixcz_(hcomp, hs2, lc, &m);
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
			if (sett_1.lendag[zramp_1.nk - 1] && sett_1.endage[
				zramp_1.nk - 1] - theage_1.dage * 1e9 <= 1.) {
			    rotprt_1.lprt0 = TRUE_;
			} else {
			    rotprt_1.lprt0 = FALSE_;
			}
/* FIND THE NEW RUN OF OMEGA */
/* JENV0 ADDED TO SR CALL. */
			ljdot = cwind_1.ljdot0;
			getw_(&bl, &delts, &dwmax, fp, ft, hcomp, hd, hjm, hl,
				 hp, hr, hs, hs1, hs2, &hstot, ht, lc, &ljdot,
				 &m, &model, &sjtot, &smass, &teffl, eta2, hg,
				 hi, omega, qiw, r0, &jenv0);
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
			liburn_(&delts, hcomp, hd, hr, hs1, hs2, ht, &jenv1, &
				jenv0, &m);
		    }
		}
/* MHP 07/02 RESTORE PRIOR FITTING POINT IF MASS ACCRETION IS BEING */
/* INCLUDED */
		if (lnewfit) {
		    getnewenv_(&senvold, hcomp, hd, hl, hp, hr, hs, hs1, hs2, 
			    &hstot, ht, lc, eta2, hg, hi, hjm, qiw, r0, 
			    hkerot, &bl, &sjtot, &skerot, &teffl, &m, &lnew);
/* CALCULATE FP AND FT GIVEN OMEGA FOR THE NEW POINT DISTRIBUTION */
		    fpft_(hd, hr, hs, &m, omega, eta2, fp, ft, hg, r0);
		    lnewfit = FALSE_;
		}
/* DETERMINE TIMESTEP FOR NEXT MODEL */
/* HTIMER ALSO LOCATES THE H-BURNING SHELL */
		delts = abs(delts);
		delts0 = delts;
		htimer_(&delts, &deltsh, &m, hd, hl, hs1, hs2, ht, lc, hcomp, 
			&jcore, &jxmid, tlumx, &theage_1.dage, &ddage, &qdt, &
			qdp, &zramp_1.nk, hp, hr, omega, &dwmax, &jxbeg);
/*  IF EVOLVING TO A GIVEN AGE AND KIND CARD IS DONE, AVOID ZEROING OUT */
/*  TIMESTEP WRITTEN TO MODEL (AS THIS MAKES CONTINUING A SEQUENCE AWKWARD.) */
/*  INSTEAD WRITE THE PREVIOUS MODEL TIMESTEP TO MODEL. */
		if (sett_1.lendag[zramp_1.nk - 1]) {
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
			hs2, &zramp_1.nk);
/* IF EVOLVING TO A GIVEN AGE AND AGE IS REACHED, KIND CARD IS DONE */
		if (sett_1.lendag[zramp_1.nk - 1] && sett_1.endage[zramp_1.nk 
			- 1] - theage_1.dage * 1e9 <= 1.) {
		    goto L110;
		}
/* TEST IF MODEL IS NEAR DESIRED Teff AND L. IF NOT RESCALE AND TRY AGAIN. */
		if (calstar_1.lcalst && ! calstar_1.lstar) {
		    if (zramp_1.nk % 2 == 0) {
			if (modeln == 1) {
			    teffi = pow_dd(&c_b72, &teffl);
			} else {
			    chkscal_(&bl, &teffl, &theage_1.dage, &zramp_1.nk)
				    ;
			    if (calstar_1.lpassr) {
				goto L200;
			    }
			}
		}
		}
		
	    if(modeliter <= ckind_1.nmodls[zramp_1.nk - 1]){
	    ++modeliter;}
	    else {
			modeliter = 0;
			++mode;
			zramp_1.nk = mode;
			}
			
		return -1;
/* END OF RUN */
/* L100: */
	    }
/* STORE LAST MODEL IN ISTOR IF LSTPCH AND LPUNCH ARE .TRUE. */
L110:
	    if (ccout2_1.lstpch) {
		if (lpunch) {
		    iwrite = luout_1.istor;
		    wrtlst_(&iwrite, hcomp, hd, hl, hp, hr, hs, ht, lc, trit, 
			    tril, ps, ts, rs, cfenv, &ftri, tlumx, &jcore, &
			    jenv, &model, &m, &smass, &teffl, &bl, &hstot, &
			    theage_1.dage, &ddage, omega);
		    lpunch = FALSE_;
		}
	    }
/* MHP 1/93 CHECK AUTOMATIC CALIBRATATION OF SOLAR MODEL. */
/* MHP 5/96 changed solar calibration to perform solar models in 3 kind cards */
	    if (cals2_1.lcals) {
		if (zramp_1.nk % 3 == 0) {
		    rll = (bl + const_1.clsunl - const1_1.c4pil - 
			    const2_1.csigl - teffl * 4.) * .5 - 
			    const_1.crsunl;
		    chkcal_(&bl, &rll, &zramp_1.nk);
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
			    cl__1.cerr = 0;
			    cl__1.cunit = lunum_1.iopmod;
			    cl__1.csta = "DELETE";
			    f_clos(&cl__1);
			    cl__1.cerr = 0;
			    cl__1.cunit = lunum_1.iopenv;
			    cl__1.csta = "DELETE";
			    f_clos(&cl__1);
			    cl__1.cerr = 0;
			    cl__1.cunit = lunum_1.iopatm;
			    cl__1.csta = "DELETE";
			    f_clos(&cl__1);
			    o__1.oerr = 0;
			    o__1.ounit = lunum_1.iopmod;
			    o__1.ofnmlen = 256;
			    o__1.ofnm = lufnm_1.fpmod;
			    o__1.orl = 0;
			    o__1.osta = "UNKNOWN";
			    o__1.oacc = 0;
			    o__1.ofm = "FORMATTED";
			    o__1.oblnk = 0;
			    f_open(&o__1);
			    o__1.oerr = 0;
			    o__1.ounit = lunum_1.iopenv;
			    o__1.ofnmlen = 256;
			    o__1.ofnm = lufnm_1.fpenv;
			    o__1.orl = 0;
			    o__1.osta = "UNKNOWN";
			    o__1.oacc = 0;
			    o__1.ofm = "FORMATTED";
			    o__1.oblnk = 0;
			    f_open(&o__1);
			    o__1.oerr = 0;
			    o__1.ounit = lunum_1.iopatm;
			    o__1.ofnmlen = 256;
			    o__1.ofnm = lufnm_1.fpatm;
			    o__1.orl = 0;
			    o__1.osta = "UNKNOWN";
			    o__1.oacc = 0;
			    o__1.ofm = "FORMATTED";
			    o__1.oblnk = 0;
			    f_open(&o__1);
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
	    io___179.ciunit = lunum_1.isnu;
	    s_wsfe(&io___179);
	    do_fio(&c__1, (char *)&bl, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&rll, (ftnlen)sizeof(doublereal));
	    e_wsfe();
/* MONTE CARLO #, CONVERGED MIXING LENGTH AND INITIAL H, SURFACE X, */
/* SURFACE Z, Z/X, CENTRAL X, CENTRAL Z */
	    io___180.ciunit = lunum_1.isnu;
	    s_wsfe(&io___180);
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
	    io___182.ciunit = lunum_1.isnu;
	    s_wsfe(&io___182);
	    do_fio(&c__1, (char *)&iconv, (ftnlen)sizeof(integer));
	    do_fio(&c__1, (char *)&xguess, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&aguess, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&calsun_1.dldx, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&calsun_1.drdx, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&calsun_1.dlda, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&calsun_1.drda, (ftnlen)sizeof(doublereal));
	    e_wsfe();
/* SUMMARY OF STRUCTURE : TC, RHOC, PC */
	    io___183.ciunit = lunum_1.isnu;
	    s_wsfe(&io___183);
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
	    io___184.ciunit = lunum_1.isnu;
	    s_wsfe(&io___184);
	    do_fio(&c__1, (char *)&fluxes_1.clsnu, (ftnlen)sizeof(doublereal))
		    ;
	    do_fio(&c__1, (char *)&fluxes_1.gasnu, (ftnlen)sizeof(doublereal))
		    ;
	    for (i__ = 1; i__ <= 8; ++i__) {
		do_fio(&c__1, (char *)&fluxes_1.fluxtot[i__ - 1], (ftnlen)
			sizeof(doublereal));
	    }
	    e_wsfe();
	    wrtmonte_(hcomp, hd, hl, hp, hr, hs, ht, lc, &m, &model, &
		    theage_1.dage, &ddage, &smass, &teffl, &bl, &gl, &lshell, 
		    &jxbeg, &jxmid, &jxend, &jcore, &jenv, tlumx, trit, tril, 
		    ps, ts, rs, cfenv, &ftri, &hstot, omega, &rll, &iconv, &
		    zramp_1.nk, &nn);
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
		io___185.ciunit = lunum_1.isnu;
		s_wsfe(&io___185);
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
	    io___186.ciunit = lunum_1.isnu;
	    s_wsfe(&io___186);
	    do_fio(&c__1, (char *)&iconv, (ftnlen)sizeof(integer));
	    do_fio(&c__1, (char *)&xguess, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&aguess, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&calsun_1.dldx, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&calsun_1.drdx, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&calsun_1.dlda, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&calsun_1.drda, (ftnlen)sizeof(doublereal));
	    e_wsfe();
/* NEUTRINO FLUXES (SEE ENGEB FOR DETAILS) */
	    io___187.ciunit = lunum_1.isnu;
	    s_wsfe(&io___187);
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
	    tcen = pow_dd(&c_b72, &d__1);
	    d__1 = cent_1.pcenter - 17.;
	    pcen = pow_dd(&c_b72, &d__1);
	    dcen = pow_dd(&c_b72, &cent_1.dcenter);
	    io___191.ciunit = lunum_1.isnu;
	    s_wsfe(&io___191);
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
	    io___194.ciunit = lunum_1.isnu;
	    s_wsfe(&io___194);
	    do_fio(&c__1, (char *)&newxym_1.cmixla[zramp_1.nk - 1], (ftnlen)
		    sizeof(doublereal));
	    do_fio(&c__1, (char *)&yini, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&zini, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&bl, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&rll, (ftnlen)sizeof(doublereal));
	    e_wsfe();
/* CZ DEPTH (R,M), SURFACE Y, Z, Z/X (ADD T CZ BASE, RHO CZ BASE) */
	    io___195.ciunit = lunum_1.isnu;
	    s_wsfe(&io___195);
	    do_fio(&c__1, (char *)&cent_1.envr, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&cent_1.envlm, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&hcomp[m * 15 - 14], (ftnlen)sizeof(
		    doublereal));
	    do_fio(&c__1, (char *)&hcomp[m * 15 - 13], (ftnlen)sizeof(
		    doublereal));
	    do_fio(&c__1, (char *)&ztox, (ftnlen)sizeof(doublereal));
	    e_wsfe();
/* ENERGY GENERATION FRACTIONS PP I,II,III,CNO,EGRAV */
	    io___196.ciunit = lunum_1.isnu;
	    s_wsfe(&io___196);
	    for (j = 1; j <= 4; ++j) {
		do_fio(&c__1, (char *)&tlumx[j - 1], (ftnlen)sizeof(
			doublereal));
	    }
	    do_fio(&c__1, (char *)&tlumx[6], (ftnlen)sizeof(doublereal));
	    e_wsfe();
	    if (monte_1.lmonte) {
		wrtmonte_(hcomp, hd, hl, hp, hr, hs, ht, lc, &m, &model, &
			theage_1.dage, &ddage, &smass, &teffl, &bl, &gl, &
			lshell, &jxbeg, &jxmid, &jxend, &jcore, &jenv, tlumx, 
			trit, tril, ps, ts, rs, cfenv, &ftri, &hstot, omega, &
			rll, &iconv, &zramp_1.nk, &nn);
	    }
	}
/* L500: */
    }
    if (modeliter <= ckind_1.nmodls[zramp_1.nk - 1]) {++modeliter;}
    else if (mode < i__2) {
		++mode;
		zramp_1.nk = mode;
		modeliter = 0;
		return -1;
		}
    return 0;
} /* MAIN__ */

