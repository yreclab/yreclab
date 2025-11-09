#include "f2c.h"
#include <string.h>
#include <stdio.h>

/* Explicit definitions for COMMON blocks missing from Fortran sources */

struct {
    doublereal captalex06[230945]	/* was [143][85][19] */;
} alot06all_ = {0};

struct {
    integer ilast, idebug, itrack, ishort, imilne, imodpt, istor, iowr;
} luout_ = {0};

struct {
    doublereal teffls[250], gls[25], fehs[25], alphas[25], pls[6250]	/* 
	    was [250][25] */, p100ls[6250]	/* was [250][25] */, t100ls[
	    6250]	/* was [250][25] */;
    logical loldnextgen;
    integer nteff, ngl, nfeh, nalpha;
} alatm01_ = {0};

struct {
    doublereal glmin[250], glmax[250];
    integer iglmin[250], iglmax[250];
    doublereal tefflmin, tefflmax, glxmin, glxmax;
} alatm02_ = {0};

struct {
    doublereal alatm_feh__, alatm_alpha__;
    logical laltptau100;
    integer ioatma;
} alatm03_ = {0};

struct {
    doublereal dummy1, dummy2, dummy3, dummy4;
} alatm04_ = {0};

struct {
    doublereal tau, ap, at, ad, ao, afxion[3];
} atmprt_ = {0};

struct {
    doublereal al_tefflmin__, al_tefflmax__;
} alatm05_ = {0};

struct {
    integer ialxo;
} alexo_ = {0};

struct {
    doublereal captalex[41055]	/* was [105][23][17] */;
} alotall_ = {0};

struct {
    doublereal cln, clni, c4pi, c4pil, c4pi3l, cc13, cc23, cpi;
} const1_ = {0};

struct {
    doublereal cgas, ca3, ca3l, csig, csigl, cgl, cmkh, cmkhn;
} const2_ = {0};

struct {
    doublereal xenv, zenv, zenvm, amuenv, fxenv[12], xnew, znew, stotal, senv;
} comp_ = {0};

struct {
    doublereal envp[5000], envt[5000], envs[5000], envd[5000], envr[5000], 
	    envx[5000], envz[5000];
    logical lcenv[5000];
    doublereal edels[15000]	/* was [3][5000] */, evels[5000], ebetas[5000]
	    , egam1[5000], eqcp[5000], efxions[15000]	/* was [3][5000] */, 
	    envo[5000], envl[5000], eqdt[5000];
    integer numenv;
} envstruct_ = {0};

struct {
    doublereal esact, eos[10];
} eeos06_ = {0};

struct {
    doublereal a[5000], b[5000], c__[5000], d__[5000], u[5000], gama[5000];
} tridi_ = {0};

struct {
    doublereal hpo[5000], hto[5000], hro[5000], hlo[5000], hdo[5000], hcompp[
	    75000]	/* was [15][5000] */, hss[5000];
    logical lco[5000], lczo[5000];
    doublereal tefflo;
    integer mo;
} oldmod_ = {0};

struct {
    doublereal yenv, y3env;
} comp2_ = {0};

struct {
    doublereal amum[5000], cpm[5000], delm[5000], delam[5000], delrm[5000], 
	    esumm[5000], om[5000], qdtm[5000], thdifm[5000], velm[5000], 
	    viscm[5000], epsm[5000];
} mdphy_ = {0};

struct {
    doublereal toleri;
} errmom_ = {0};

struct {
    doublereal wold[5000], hjx[5000], hio[5000], hgo[5000], r0x[5000], eta2x[
	    5000];
} oldrot_ = {0};

struct {
    doublereal dldx, drdx, dlda, drda, blp, rlp, dx, da;
    logical lsol;
} calsun_ = {0};

struct {
    doublereal ves[5000], ves0[5000], vss[5000], vss0[5000], hle[5000], vgsf[
	    5000], vgsf0[5000], vmu[5000];
} temp2_ = {0};

struct {
    doublereal flux[10], fluxtot[10], clsnu, gasnu;
} fluxes_ = {0};

struct {
    doublereal qqdp, qqed, qqet, qqod, qqot, qdel, qdela, qqcp, qrmu, qtl, 
	    qpl, qdl, qo, qol, qt, qp, qqdt, qemu, qd, qfs;
} pulse2_ = {0};

struct {
    doublereal ealpca, enu;
} neweps_ = {0};

struct {
    doublereal enghe3, he3all, umhe33[5000], umheal[5000];
} grab_ = {0};

struct {
    doublereal sacc, scen, smass0, dlogp, dlogt;
} masschg2_ = {0};

struct {
    doublereal derot[5000];
} roten_ = {0};

struct {
    doublereal sesum[5000], seg[35000]	/* was [7][5000] */, sbeta[5000], 
	    seta[5000];
    logical locons[5000];
    doublereal so[5000], sdel[15000]	/* was [3][5000] */, sfxion[15000]	
	    /* was [3][5000] */, svel[5000], scp[5000];
} scrtch_ = {0};

struct {
    doublereal gam1[5000];
    logical lsound;
} sound_ = {0};

struct {
    doublereal pqdp[5000], pqed[5000], pqet[5000], pqod[5000], pqot[5000], 
	    pqcp[5000], prmu[5000], pqdt[5000], pemu[5000];
    logical lpumod;
} pulse1_ = {0};

struct {
    doublereal sqod[5000], sqot[5000], sqed[5000], sqet[5000], fracnuc[5000];
} rotder_ = {0};

struct {
    doublereal alfmlt, phmlt, cmxmlt, valfmlt[5000], vphmlt[5000], vcmxmlt[
	    5000];
} pualpha_ = {0};

struct {
    doublereal qchire[5000], qchirc[5000];
} egridchi_ = {0};

struct {
    doublereal facd2[5000], facd3[5000], vesd2[5000], vesd3[5000], ecod5[5000]
	    , ecod6[5000], fgeom[5000], fv0[5000], fv1a[5000], fv1b[5000], 
	    fv2a[5000], fv2b[5000], ev0[5000], ev1a[5000], ev1b[5000], ev2a[
	    5000], ev2b[5000], dss[5000], dgsf[5000], ess[5000], egsf[5000];
} difad3_ = {0};

struct {
    doublereal ecod3[5000], ecod4[5000];
} difad_ = {0};

struct {
    doublereal eqqcod[5000], eqqqcod[5000], qqcod[5000], qqqcod[5000];
} egridder_ = {0};

struct {
    doublereal fgeomix[5000], vesn[5000], req[5000];
} difad4_ = {0};

struct {
    doublereal drate[5000], drate0[5000], fmassacc;
    integer jcz;
} deuter_ = {0};

struct {
    doublereal be7massfraction;
} be7_ = {0};

struct {
    integer ifirst, irun, istand, ifermi, iopmod, iopenv, iopatm, idyn, 
	    illdat, isnu, iscomp, ikur;
} lunum_ = {0};

struct {
    doublereal atmop[5000], atmot[5000], atmod[5000], atmor[5000], adels[
	    15000]	/* was [3][5000] */, abetas[5000], agam1[5000], aqdt[
	    5000], afxions[15000]	/* was [3][5000] */, atmoo[5000], 
	    atmocp[5000];
    integer numatm;
} atmstruct_ = {0};

struct {
    doublereal ep, et, er, es, ed, eo, ebeta, edel[3], efxion[3], evel;
} envprt_ = {0};

struct {
    doublereal envrcz, rint;
} envcz_ = {0};

struct {
    doublereal xval[5000], yval[5000], xtab[5000], ytab[5000];
} splin_ = {0};

struct {
    doublereal chi[5000], echi[5000], es1[5000], dchi;
    integer ntot;
} egrid_ = {0};

struct {
    integer l1, l2, l3, l4, k1, k2, k3, k4, ip, iq;
} bbeos06_ = {0};

struct {
    doublereal dval[43], etat8[43], dtable[4300]	/* was [5][43][20] */;
    integer iden[261];
} ccr_ = {0};

struct {
    doublereal ecod1z[5000], ecod1z_h__[5000], ecod2z_h__[5000], eqcod1z_h__[
	    5000], eqcod2z_h__[5000], ez[5000], ez_h__[5000];
} gravez_ = {0};

struct {
    doublereal con_rad__, con_mass__, con_temp__, con_time__;
} confac_ = {0};

struct {
    integer itime;
} lreadco_ = {0};

struct {
    doublereal epl[161395]	/* was [5][191][169] */, xx[5];
} eeeos_ = {0};

struct {
    integer l1, l2, l3, l4, k1, k2, k3, k4, ip, iq;
} bbeos_ = {0};

struct {
    doublereal esact, eos[10];
} eeos_ = {0};

struct {
    doublereal epl[166465]	/* was [5][197][169] */, xx[5];
} eeeos06_ = {0};

struct {
    doublereal epl[21560]	/* was [5][56][77] */, xx[5];
} ee_ = {0};

struct {
    integer l1, l2, l3, l4, k1, k2, k3, k4, ip, iq;
} bb_ = {0};

struct {
    doublereal esact, eos[10];
} e_ = {0};

struct {
    doublereal phisp[5000], phirot[5000], phidis[5000], rat[5000];
} quadd_ = {0};

struct {
    doublereal alm[5000], delami[5000], delmi[5000], dm[5000], epsilm[5000], 
	    hgm[5000], hs3[5000], pm[5000], qdtmi[5000], rm[5000], tm[5000];
} intvar_ = {0};

struct {
    doublereal rl, rll, rlh[4];
    logical lextl, lexth, lexh[4];
} op95ext_ = {0};

struct {
    doublereal bz[4], bx[16]	/* was [4][4] */, bt[4], btt[4], bd[16]	/* 
	    was [4][4] */, bdd[16]	/* was [4][4] */;
} op95fact_ = {0};

struct {
    doublereal cappa[13300]	/* was [10][70][19] */, ztab;
} llot95_ = {0};

struct {
    doublereal cappae[1330]	/* was [70][19] */, xtab;
} llot95e_ = {0};

struct {
    doublereal quad[5000], gg[5000];
} quadru_ = {0};

struct {
    doublereal tho[5000], thn[5000], thm[5000], ddelm[5000], festime[5000], 
	    thp[5000], qwrst[5000], wmst[5000], qwrmst[5000];
} oldrot2_ = {0};

struct {
    doublereal cp[5000], hamu[5000], sqdt[5000], thdif[5000], visc[5000];
} temp_ = {0};

struct {
    doublereal delo[5000], delao[5000], amuo[5000], oo[5000], cpo[5000], qdto[
	    5000], velo[5000], visco[5000], thdifo[5000], esumo[5000], delro[
	    5000], epso[5000];
} oldphy_ = {0};

struct {
    doublereal pscal0, pscal1;
} liov_ = {0};

struct {
    doublereal rli60[5000], rli70[5000], rbe90[5000];
} oldrat_ = {0};

struct {
    doublereal rli6[5000], rli7[5000], rbe9[5000];
} newrat_ = {0};

struct {
    logical lprt0;
} rotprt_ = {0};

struct {
    doublereal olaol2[64896]	/* was [12][104][52] */, oxa2[12], ot2[52], 
	    orho2[104];
    integer nxyz2, nrho2, nt2;
} nwlaol2_ = {0};

struct {
    doublereal slaoll2[64896]	/* was [12][104][52] */, srhol2[64896]	/* 
	    was [12][104][52] */, sdorl2[64896]	/* was [12][104][52] */;
    integer numrs2[624]	/* was [12][52] */;
} slaol2_ = {0};

struct {
    doublereal slaoll[64896]	/* was [12][104][52] */, srhol[64896]	/* 
	    was [12][104][52] */, sdorl[64896]	/* was [12][104][52] */;
    integer numrs[624]	/* was [12][52] */;
} slaol_ = {0};

struct {
    doublereal zolaol[5408]	/* was [104][52] */, zot[52], zorho[104];
    integer numrhoz, numtz;
} zlaol_ = {0};

struct {
    doublereal zslaoll[5408]	/* was [104][52] */, zsrhol[5408]	/* 
	    was [104][52] */, zsdorl[5408]	/* was [104][52] */;
    integer numrsz[52];
} zslaol_ = {0};

struct {
    doublereal htt0[5000], hpp0[5000], hll0[5000], hrr0[5000];
} entrop_ = {0};


struct {
    doublereal hcompm[75000]	/* was [15][5000] */;
} burn_ = {0};


struct {
    doublereal qwrmax[5000], qwrmx0[5000];
} dwmax_ = {0};

struct {
    doublereal atmplc[836]	/* was [76][11] */, atmtlc[76], atmglc[11];
} atmos2c_ = {0};

struct {
    integer imin[57], iminmax[57], jp, kp[4], imin2[76], iminmax2[76];
} fac_ = {0};

struct {
    doublereal gridt[60];
} gkrz2_ = {0};

struct {
    doublereal opacity[3000]	/* was [60][50] */, rho[3000]	/* was [60][
	    50] */;
    integer numtm;
} krz2_ = {0};

struct {
    doublereal cford[12000]	/* was [60][200] */;
    integer nds[60], ndd[60];
} intpl22_ = {0};

struct {
    doublereal gridt[60];
} gkrz_ = {0};

struct {
    doublereal opacity[3000]	/* was [60][50] */, rho[3000]	/* was [60][
	    50] */;
    integer numtm;
} krz_ = {0};

struct {
    doublereal cford[12000]	/* was [60][200] */;
    integer nds[60], ndd[60];
} intpl2_ = {0};

struct {
    doublereal rbase0, bli6old, bli7old, bbe9old;
    integer jenvos;
} prevcz_ = {0};

struct {
    doublereal xenv4, zenv4, cford4[3400]	/* was [50][68] */;
    integer kipm1;
} llot4_ = {0};

struct {
    doublereal gridt[50], gridx[3], grhot3[17];
} gllot_ = {0};

struct {
    doublereal xenv42, zenv42, cford42[3400]	/* was [50][68] */;
    integer kipm12;
} llot42_ = {0};

struct {
    doublereal cford[10200]	/* was [150][68] */;
    integer nds[150], ndd[150];
} lintpl_ = {0};

struct {
    doublereal opacity[2550]	/* was [150][17] */;
    integer numxm, numtm;
} llot_ = {0};

struct {
    doublereal gridt2[50], gridx2[3], grhot32[17];
} gllot2_ = {0};

struct {
    doublereal opacity2[2550]	/* was [150][17] */;
    integer numxm2, numtm2;
} llot2_ = {0};

struct {
    doublereal cford2[10200]	/* was [150][68] */;
    integer nds2[150], ndd2[150];
} lintpl2_ = {0};

struct {
    integer iliv95;
} lopal95_ = {0};

struct {
    doublereal s11[1000], s33[1000], s34[1000], s17[1000], zx[1000], fhe[1000]
	    , fzdif[1000], flum[1000], fage[1000];
} monte2_ = {0};

struct {
    doublereal dage;
} theage_ = {0};

struct {
    doublereal hjm0[5000], hcompp0[75000]	/* was [15][5000] */;
} origstart_ = {0};

struct {
    doublereal tcenter, pcenter, dcenter, envlm, envr;
} cent_ = {0};

struct {
    doublereal varmhd[25];
} mhdout_ = {0};

struct {
    doublereal tlim1, tlim2, tmini, tmaxi;
} tttt_ = {0};

struct {
    doublereal tdvr1a[27840]	/* was [16][87][20] */, tlog1[16];
    integer nt1, nr1;
    doublereal drh1;
} tab1a_ = {0};

struct {
    doublereal atwta[6], abuna[6], abfrca[6], gasma;
} chea_ = {0};

struct {
    doublereal tdvr2a[33180]	/* was [79][21][20] */, tlog2[79];
    integer nt2, nr2;
    doublereal drh2;
} tab2a_ = {0};

struct {
    doublereal tdvr1b[27840]	/* was [16][87][20] */;
} tab1b_ = {0};

struct {
    doublereal atwtb[6], abunb[6], abfrcb[6], gasmb;
} cheb_ = {0};

struct {
    doublereal tdvr2b[33180]	/* was [79][21][20] */;
} tab2b_ = {0};

struct {
    doublereal tdvr1c[27840]	/* was [16][87][20] */;
} tab1c_ = {0};

struct {
    doublereal atwtc[6], abunc[6], abfrcc[6], gasmc;
} chec_ = {0};

struct {
    doublereal tdvrx1[5250]	/* was [10][21][25] */, tlogx[10];
    integer ntx, nrx;
    doublereal drhx;
} tabx1_ = {0};

struct {
    doublereal tdvrx2[5250]	/* was [10][21][25] */;
} tabx2_ = {0};

struct {
    doublereal tdvr2c[33180]	/* was [79][21][20] */;
} tab2c_ = {0};

struct {
    doublereal atwt1[6], abun1[6], abfrc1[6], gasm1;
} che1_ = {0};

struct {
    doublereal atwt2[6], abun2[6], abfrc2[6], gasm2;
} che2_ = {0};

struct {
    doublereal tdvrx3[5250]	/* was [10][21][25] */;
} tabx3_ = {0};

struct {
    doublereal atwt3[6], abun3[6], abfrc3[6], gasm3;
} che3_ = {0};

struct {
    doublereal tdvrx4[5250]	/* was [10][21][25] */;
} tabx4_ = {0};

struct {
    doublereal atwt4[6], abun4[6], abfrc4[6], gasm4;
} che4_ = {0};

struct {
    doublereal tdvrx5[5250]	/* was [10][21][25] */;
} tabx5_ = {0};

struct {
    doublereal atwt5[6], abun5[6], abfrc5[6], gasm5;
} che5_ = {0};

struct {
    doublereal ddelp[5000], ddeln[5000], hrp[5000];
    logical lcp[5000];
} prevmid_ = {0};

struct {
    doublereal hcomps[75000]	/* was [15][5000] */;
} oldab_ = {0};

struct {
    doublereal cod1z[5000], cod2z[5000], qcod1z[5000], qcod2z[5000];
} gravsz_ = {0};

struct {
    char compmix[4];
} i2o_ = {0};

struct {
    integer ialex06;
} alex06_ = {0};

struct {
    doublereal moles[5], xin[5], tmass[5], rhogr[385]	/* was [5][77] */, 
	    frac[30]	/* was [5][6] */, alogr[4312]	/* was [77][56] */;
    integer icycuse[385]	/* was [5][77] */;
} eee_ = {0};

struct {
    doublereal moles[5], xin[5], tmass[5], rhogr[845]	/* was [5][169] */, 
	    frac[30]	/* was [5][6] */, alogr[32279]	/* was [169][191] */;
    integer icycuse[845]	/* was [5][169] */;
} eeeeos_ = {0};

struct {
    doublereal moles[5], xin[5], tmass[5], amu_m__[33293]	/* was [169][
	    197] */, alogne[33293]	/* was [169][197] */, rhogr[845]	
	    /* was [5][169] */, frac[30]	/* was [5][6] */, alogr[33293]
	    	/* was [169][197] */;
    integer icycuse[845]	/* was [5][169] */;
} eeeeos06_ = {0};

struct {
    doublereal vesa[5000], vesa0[5000], vesd[5000], vesd0[5000];
} difad2_ = {0};

struct {
    doublereal atmpl[627]	/* was [57][11] */, atmtl[57], atmgl[11], 
	    atmz;
    integer ioatm;
} atmos2_ = {0};

struct {
    integer iscvh, iscvhe, iscvz;
} scv2_ = {0};

struct {
    doublereal faci[20000]	/* was [4][5000] */;
} intfac_ = {0};

struct {
    doublereal fact6[5000], fes1[5000], fes2[5000], fgsfj[5000], fgsfk[5000], 
	    fes3[5000];
} taukh_ = {0};

struct {
    doublereal fact1[5000], fact2[5000], fact3[5000], fact4[5000], fact5[5000]
	    , fact7[5000], fact8[5000];
} vfact_ = {0};

struct {
    doublereal q[4], h__[4], xxh;
} aaeos_ = {0};

struct {
    doublereal q[4], h__[4], xxh;
} aaeos06_ = {0};

struct {
    doublereal q[4], h__[4], xxh;
} aa_ = {0};

struct {
    doublereal vmup[5000];
} prevmu_ = {0};

struct {
    doublereal amumi[5000], thdifmi[5000], viscmi[5000], wm[5000];
} intvr2_ = {0};

struct {
    char fmonte1[256], fmonte2[256];
    integer imonte1, imonte2;
} iomonte_ = {0};

struct {
    integer m12, m22, m32;
} kipmll2_ = {0};




struct {
    char flast[256], ffirst[256], frun[256], fstand[256], ffermi[256], fdebug[
	    256], ftrack[256], fshort[256], fmilne[256], fmodpt[256], fstor[
	    256], fpmod[256], fpenv[256], fpatm[256], fdyn[256], flldat[256], 
	    fsnu[256], fscomp[256], fkur[256], fmhd1[256], fmhd2[256], fmhd3[
	    256], fmhd4[256], fmhd5[256], fmhd6[256], fmhd7[256], fmhd8[256];
} lufnm_ = {0};

struct {
    char descrip[512];
} desc_ = {0};

/* Stub for Fortran GETARG intrinsic.
 * If there are issues with getarg_,
 * this can be uncommented. */
/* int getarg_(integer *n, char *s, ftnlen len)
{
    const char *dummy = "";
    size_t l = strlen(dummy);
    if (l > (size_t)len) l = len;
    memcpy(s, dummy, l);
    if (l < (size_t)len) memset(s + l, ' ', len - l);
    return 0;
} */

struct {
    char falex06[256], fallard[256], fatm[256], ffermi[256], fkur[256], fkur2[
	    256], flaol[256], flaol2[256], fliv95[256], flldat[256], fmhd1[
	    256], fmhd2[256], fmhd3[256], fmhd4[256], fmhd5[256], fmhd6[256], 
	    fmhd7[256], fmhd8[256], fopal2[256], fpatm[256], fpenv[256], 
	    fpmod[256], fpurez[256], fscvh[256], fscvhe[256], fscvz[256], 
	    opecalex[1792];
} nmlctrl_ = {0};


struct {
    doublereal dmsun, dmwsun, dmwmax;
    logical lsolwind;
} masschg3_ = {0};

int xargc = 1;
char *xargv[] = { "yrec", NULL };
