/* setups.f -- translated by f2c (version 20100827).
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
    doublereal cdh, etadh0, etadh1, zdh[18], xxdh, yydh, zzdh, dhnue[18];
    logical ldh;
} debhu_;

#define debhu_1 debhu_

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
    doublereal dval[43], etat8[43], dtable[4300]	/* was [5][43][20] */;
    integer iden[261];
} ccr_;

#define ccr_1 ccr_

struct {
    logical lmhd;
    integer iomhd1, iomhd2, iomhd3, iomhd4, iomhd5, iomhd6, iomhd7, iomhd8;
} mhd_;

#define mhd_1 mhd_

struct {
    doublereal hras;
    integer kttau;
} atmos_;

#define atmos_1 atmos_

struct {
    doublereal atmpl[627]	/* was [57][11] */, atmtl[57], atmgl[11], 
	    atmz;
    integer ioatm;
    char fatm[256];
} atmos2_;

#define atmos2_1 atmos2_

struct {
    integer imin[57], jp, kp[4];
} fac_;

#define fac_1 fac_

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
    char fscvh[256], fscvhe[256], fscvz[256];
    integer iscvh, iscvhe, iscvz;
} scv2_;

#define scv2_1 scv2_

/* Table of constant values */

static doublereal c_b2 = 16.;
static integer c__1 = 1;


/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */
/* SETUPS */
/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */
/* Subroutine */ int setups_(doublereal *v)
{
    /* Format strings */
    static char fmt_150[] = "(8x,9f8.4)";
    static char fmt_160[] = "(2i5,5f12.7)";
    static char fmt_1000[] = "(1x,39(\002>\002),40(\002<\002)/1x,\002ERROR I"
	    "N SUBROUTINE SETUPS\002/1x,\002GLITCH IN FERMI TABLE ELEMENT\002"
	    ",i4/1x,\002RUN STOPPED\002)";
    static char fmt_200[] = "(11x,1pe16.8,/)";
    static char fmt_201[] = "(1p4e16.8,13(/1p4e16.8),/1pe16.8,/)";
    static char fmt_202[] = "(1p4e16.8,/1p4e16.8,/1p3e16.8,/)";
    static char fmt_203[] = "(1p4e16.8,/1p4e16.8,/1p3e16.8)";
    static char fmt_1[] = "(f5.2,i4)";
    static char fmt_2[] = "(f6.2,1p2e13.5,0p,8f9.4)";
    static char fmt_3[] = "(f6.2,12f9.4)";

    /* System generated locals */
    integer i__1;
    doublereal d__1;
    olist o__1;
    cllist cl__1;
    alist al__1;

    /* Builtin functions */
    double log(doublereal), d_lg10(doublereal *), sqrt(doublereal);
    integer f_open(olist *), s_rsfe(cilist *), do_fio(integer *, char *, 
	    ftnlen), e_rsfe(void), f_rew(alist *), s_wsfe(cilist *), e_wsfe(
	    void);
    /* Subroutine */ int s_stop(char *, ftnlen);
    integer f_clos(cllist *);

    /* Local variables */
    extern /* Subroutine */ int alfilein_(void);
    static integer i__, j, k, k1, k2;
    extern /* Subroutine */ int setupopac_(doublereal *, doublereal *);
    static doublereal cc;
    extern doublereal hra_(doublereal *);
    static doublereal dum1, dum3, elec;
    static integer idum2, idum4;
    static doublereal hmass, cmelec, cboltz, cplnck;
    extern /* Subroutine */ int mhdtbl_(void);
    static integer ncards;

    /* Fortran I/O blocks */
    static cilist io___7 = { 0, 0, 0, fmt_150, 0 };
    static cilist io___9 = { 0, 0, 0, fmt_150, 0 };
    static cilist io___10 = { 0, 0, 0, fmt_160, 0 };
    static cilist io___15 = { 0, 0, 0, fmt_1000, 0 };
    static cilist io___17 = { 0, 0, 0, fmt_200, 0 };
    static cilist io___18 = { 0, 0, 0, fmt_201, 0 };
    static cilist io___19 = { 0, 0, 0, fmt_202, 0 };
    static cilist io___20 = { 0, 0, 0, fmt_203, 0 };
    static cilist io___21 = { 0, 0, 0, fmt_1, 0 };
    static cilist io___22 = { 0, 0, 0, fmt_1, 0 };
    static cilist io___25 = { 0, 0, 0, fmt_1, 0 };
    static cilist io___28 = { 0, 0, 0, fmt_2, 0 };
    static cilist io___29 = { 0, 0, 0, fmt_2, 0 };
    static cilist io___30 = { 0, 0, 0, fmt_3, 0 };


/* MHP 8/97 ADDED NTA AND NGA FOR ALLARD ATMOSPHERE */
/* DBGLAOL */
/* DBGLAOL */
/* DBG 7/92 COMMON BLOCK ADDED TO COMPUTE DEBYE-HUCKEL CORRECTION. */
/* MHP 8/92 COMMON BLOCK ADDED FOR LOWER EDGE OF TABLE IN LOG G. */
/* MHP  5/97 ADDED COMMON BLOCK FOR SCV EOS TABLES */
/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */
/* SETUP CONSTANTS */
/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */
    /* Parameter adjustments */
    --v;

    /* Function Body */
    const3_1.clndp = log(10.);
    const1_1.cln = const3_1.clndp;
    const1_1.clni = 1. / const1_1.cln;
/* Luminosity of Sun */
    const_1.clsunl = d_lg10(&const_1.clsun);
    const_1.clnsun = const1_1.cln / const_1.clsun;
/* Mass of Sun */
    const_1.cmsun = 1.9891e33;
    const_1.cmsunl = d_lg10(&const_1.cmsun);
/* Radius of Sun */
    const_1.crsunl = d_lg10(&const_1.crsun);
/* Bolometric magnitude of the sun */
    const_1.cmbol = 4.79;
/* No. of seconds per year and other mathematical constants */
    const3_1.csecyr = 3.1558e7;
    const1_1.cc13 = .33333333333333331;
    const1_1.cc23 = const1_1.cc13 + const1_1.cc13;
    const1_1.cpi = 3.1415926535898;
    const1_1.c4pi = const1_1.cpi * 4.;
    const1_1.c4pil = d_lg10(&const1_1.c4pi);
    d__1 = const1_1.cc13 * const1_1.c4pi;
    const1_1.c4pi3l = d_lg10(&d__1);
/* Speed of Light */
    cc = 29979245800.;
/* Stefan-Boltzmann constant */
    const2_1.csig = 5.67051e-5;
    const2_1.csigl = d_lg10(&const2_1.csig);
/* radiation constant/3 */
    const2_1.ca3 = const2_1.csig * 4. / (cc * 3.);
    const2_1.ca3l = d_lg10(&const2_1.ca3);
/* molar gas constant */
    const2_1.cgas = 83145100.;
/* log of Gravitational constant G=6.67259D-8 */
    const2_1.cgl = -7.17571;
/* mass of the electron */
    cmelec = 9.1093897e-28;
/* Boltzmann constant */
    cboltz = 1.380658e-16;
/* Planck's constant */
    cplnck = 6.6260755e-27;
    d__1 = const1_1.cpi * 2. * cmelec;
    const2_1.cmkh = d_lg10(&d__1) * 1.5 + d_lg10(&cboltz) * 2.5 - d_lg10(&
	    cplnck) * 3.;
    const3_1.cdelrl = -const1_1.c4pi3l - const2_1.csigl - d_lg10(&c_b2);
    const3_1.cmixl2 = const1_1.cc13;
    const3_1.cmixl3 = sqrt(2.) * 16. * const2_1.csig;
/* DBG CALCULATE DEBYE-HUCKEL CONSTAND CDH */
/* mass hydrogen atom (gm) */
    hmass = 1.6605189550148313e-24;
/* charge electron (ESU) */
    elec = 4.802e-10;
    debhu_1.cdh = -sqrt(const1_1.cpi / (cboltz * hmass * hmass * hmass)) * 
	    elec * elec * elec / 3.;
/* Electric charge of C,N,O,Ne,Na,Mg,Al,Si,P,S,Cl,Ar,Ca,Ti,Cr,Mn,Fe,Ni */
    debhu_1.dhnue[0] = 6.;
    debhu_1.dhnue[1] = 7.;
    debhu_1.dhnue[2] = 8.;
    debhu_1.dhnue[3] = 10.;
    debhu_1.dhnue[4] = 11.;
    debhu_1.dhnue[5] = 12.;
    debhu_1.dhnue[6] = 13.;
    debhu_1.dhnue[7] = 14.;
    debhu_1.dhnue[8] = 15.;
    debhu_1.dhnue[9] = 16.;
    debhu_1.dhnue[10] = 17.;
    debhu_1.dhnue[11] = 18.;
    debhu_1.dhnue[12] = 20.;
    debhu_1.dhnue[13] = 22.;
    debhu_1.dhnue[14] = 24.;
    debhu_1.dhnue[15] = 25.;
    debhu_1.dhnue[16] = 26.;
    debhu_1.dhnue[17] = 28.;
/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */
/*     EVALUATE TAU = 2/3 TEMPERATURE FOR HRA */
/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */
    atmos_1.hras = hra_(&const1_1.cc23);
/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */
/*     SET UP OPACITY TABLES */
/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */
    setupopac_(&comp_1.xenv, &v[1]);
/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */
/*     READ IN MHD EOS TABLES */
/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */
    if (mhd_1.lmhd) {
	mhdtbl_();
    }


/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */
/* INPUT F-TABLES FOR DEGENERATE EQUATION OF STATE */
/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */
/*  OPEN DATA FILES */
    o__1.oerr = 0;
    o__1.ounit = lunum_1.ifermi;
    o__1.ofnmlen = 256;
    o__1.ofnm = lufnm_1.ffermi;
    o__1.orl = 0;
    o__1.osta = "OLD";
    o__1.oacc = 0;
    o__1.ofm = "FORMATTED";
    o__1.oblnk = 0;
    f_open(&o__1);
    io___7.ciunit = lunum_1.ifermi;
    s_rsfe(&io___7);
    for (i__ = 1; i__ <= 43; ++i__) {
	do_fio(&c__1, (char *)&ccr_1.dval[i__ - 1], (ftnlen)sizeof(doublereal)
		);
    }
    e_rsfe();
    io___9.ciunit = lunum_1.ifermi;
    s_rsfe(&io___9);
    for (i__ = 1; i__ <= 43; ++i__) {
	do_fio(&c__1, (char *)&ccr_1.etat8[i__ - 1], (ftnlen)sizeof(
		doublereal));
    }
    e_rsfe();
    io___10.ciunit = lunum_1.ifermi;
    s_rsfe(&io___10);
    for (ncards = 1; ncards <= 860; ++ncards) {
	do_fio(&c__1, (char *)&i__, (ftnlen)sizeof(integer));
	do_fio(&c__1, (char *)&j, (ftnlen)sizeof(integer));
	for (k = 1; k <= 5; ++k) {
	    do_fio(&c__1, (char *)&ccr_1.dtable[k + (i__ + j * 43) * 5 - 221],
		     (ftnlen)sizeof(doublereal));
	}
    }
    e_rsfe();
    al__1.aerr = 0;
    al__1.aunit = lunum_1.ifermi;
    f_rew(&al__1);
    k1 = 1;
    for (i__ = 1; i__ <= 41; ++i__) {
/* MHP 10/02 SHOULD BE INT(DVAL,ETC.) */
	if (ccr_1.dval[i__] <= ccr_1.dval[i__ - 1]) {
/* 	 IF (INT(DVAL(I+1)).LE.INT(DVAL(I))) THEN */
	    io___15.ciunit = luout_1.ishort;
	    s_wsfe(&io___15);
	    do_fio(&c__1, (char *)&i__, (ftnlen)sizeof(integer));
	    e_wsfe();
	    s_stop("", (ftnlen)0);
	}
	k = (integer) ((ccr_1.dval[i__] - ccr_1.dval[i__ - 1]) * 20. + .1);
	k2 = k1 + k - 1;
	if (i__ == 41) {
	    k2 = 261;
	}
	i__1 = k2;
	for (j = k1; j <= i__1; ++j) {
	    ccr_1.iden[j - 1] = i__;
/* L170: */
	}
	k1 = k2 + 1;
/* L180: */
    }
/*  CLOSE EQUATION OF STATE FILE. */
    cl__1.cerr = 0;
    cl__1.cunit = lunum_1.ifermi;
    cl__1.csta = 0;
    f_clos(&cl__1);
/* JMH 8/18/91 */
/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */
/* INPUT PRESSURE TABLE FOR SURFACE BOUNDARY CONDITIONS */
/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */
    if (atmos_1.kttau == 3 || atmos_1.kttau == 4) {
/* OPEN SURFACE PRESSURE TABLE */
	o__1.oerr = 0;
	o__1.ounit = atmos2_1.ioatm;
	o__1.ofnmlen = 256;
	o__1.ofnm = atmos2_1.fatm;
	o__1.orl = 0;
	o__1.osta = "OLD";
	o__1.oacc = 0;
	o__1.ofm = 0;
	o__1.oblnk = 0;
	f_open(&o__1);
/* GET ABUNDANCE: */
	io___17.ciunit = atmos2_1.ioatm;
	s_rsfe(&io___17);
	do_fio(&c__1, (char *)&atmos2_1.atmz, (ftnlen)sizeof(doublereal));
	e_rsfe();
/* GET VALUES OF LOG Teff: */
	io___18.ciunit = atmos2_1.ioatm;
	s_rsfe(&io___18);
	for (i__ = 1; i__ <= 57; ++i__) {
	    do_fio(&c__1, (char *)&atmos2_1.atmtl[i__ - 1], (ftnlen)sizeof(
		    doublereal));
	}
	e_rsfe();
/* GET VALUES OF LOG G: */
	io___19.ciunit = atmos2_1.ioatm;
	s_rsfe(&io___19);
	for (i__ = 1; i__ <= 11; ++i__) {
	    do_fio(&c__1, (char *)&atmos2_1.atmgl[i__ - 1], (ftnlen)sizeof(
		    doublereal));
	}
	e_rsfe();
/* GET GRID OF LOG PRESSURE VALUES: */
	for (j = 1; j <= 57; ++j) {
	    io___20.ciunit = atmos2_1.ioatm;
	    s_rsfe(&io___20);
	    for (i__ = 1; i__ <= 11; ++i__) {
		do_fio(&c__1, (char *)&atmos2_1.atmpl[j + i__ * 57 - 58], (
			ftnlen)sizeof(doublereal));
	    }
	    e_rsfe();
/* L205: */
	}
	al__1.aerr = 0;
	al__1.aunit = atmos2_1.ioatm;
	f_rew(&al__1);
	cl__1.cerr = 0;
	cl__1.cunit = atmos2_1.ioatm;
	cl__1.csta = 0;
	f_clos(&cl__1);
	for (j = 1; j <= 57; ++j) {
	    for (k = 10; k >= 1; --k) {
		if (atmos2_1.atmpl[j + k * 57 - 58] <= 0.) {
		    fac_1.imin[j - 1] = k + 1;
		    goto L5;
		}
	    }
	    fac_1.imin[j - 1] = 1;
L5:
	    ;
	}
/* MHP 6/97 ADDED OPTION FOR ALLARD MODEL ATMOSPHERES; USED INSTEAD OF */
/* KURUCZ FOR TEFF < 10,000 K. */
	if (atmos_1.kttau == 4) {
/*            ATMZA = 0.02D0 */
	    alfilein_();
/* Get Allard Atmospheres files and */
	}
/* initialize tables. 9/23/08 LLP */
    }
/* MHP 5/97 ADDED OPTION FOR NEW SCV EQUATION OF STATE TABLES. */
    if (scveos_1.lscv) {
	o__1.oerr = 0;
	o__1.ounit = scv2_1.iscvh;
	o__1.ofnmlen = 256;
	o__1.ofnm = scv2_1.fscvh;
	o__1.orl = 0;
	o__1.osta = "OLD";
	o__1.oacc = 0;
	o__1.ofm = 0;
	o__1.oblnk = 0;
	f_open(&o__1);
	o__1.oerr = 0;
	o__1.ounit = scv2_1.iscvhe;
	o__1.ofnmlen = 256;
	o__1.ofnm = scv2_1.fscvhe;
	o__1.orl = 0;
	o__1.osta = "OLD";
	o__1.oacc = 0;
	o__1.ofm = 0;
	o__1.oblnk = 0;
	f_open(&o__1);
	o__1.oerr = 0;
	o__1.ounit = scv2_1.iscvz;
	o__1.ofnmlen = 256;
	o__1.ofnm = scv2_1.fscvz;
	o__1.orl = 0;
	o__1.osta = "OLD";
	o__1.oacc = 0;
	o__1.ofm = 0;
	o__1.oblnk = 0;
	f_open(&o__1);
/*  READ IN EQUATION OF STATE TABLES FOR HYDROGEN AND HELIUM */
	for (i__ = 1; i__ <= 63; ++i__) {
	    io___21.ciunit = scv2_1.iscvh;
	    s_rsfe(&io___21);
	    do_fio(&c__1, (char *)&scveos_1.tlogx[i__ - 1], (ftnlen)sizeof(
		    doublereal));
	    do_fio(&c__1, (char *)&scveos_1.nptsx[i__ - 1], (ftnlen)sizeof(
		    integer));
	    e_rsfe();
	    io___22.ciunit = scv2_1.iscvhe;
	    s_rsfe(&io___22);
	    do_fio(&c__1, (char *)&dum1, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&idum2, (ftnlen)sizeof(integer));
	    e_rsfe();
	    io___25.ciunit = scv2_1.iscvz;
	    s_rsfe(&io___25);
	    do_fio(&c__1, (char *)&dum3, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&idum4, (ftnlen)sizeof(integer));
	    e_rsfe();
/* TABLE GRID POINTS IN T, P(T) ARE THE SAME - NPTSY AND TLOGX */
/* READ IN TO RETAIN PARALLEL COMMON BLOCK STRUCTURE. */
	    i__1 = scveos_1.nptsx[i__ - 1];
	    for (j = 1; j <= i__1; ++j) {
		io___28.ciunit = scv2_1.iscvh;
		s_rsfe(&io___28);
		for (k = 1; k <= 11; ++k) {
		    do_fio(&c__1, (char *)&scveos_1.tablex[i__ + (j + k * 76) 
			    * 63 - 4852], (ftnlen)sizeof(doublereal));
		}
		e_rsfe();
		io___29.ciunit = scv2_1.iscvhe;
		s_rsfe(&io___29);
		for (k = 1; k <= 11; ++k) {
		    do_fio(&c__1, (char *)&scveos_1.tabley[i__ + (j + k * 76) 
			    * 63 - 4852], (ftnlen)sizeof(doublereal));
		}
		e_rsfe();
	    }
/*  READ IN METAL EQUATION OF STATE TABLE; COMPUTED USING THE PRATHER */
/* EQUATION OF STATE IN THE OLD YALE CODE. */
	    for (j = scveos_1.nptsx[i__ - 1]; j >= 1; --j) {
		io___30.ciunit = scv2_1.iscvz;
		s_rsfe(&io___30);
		for (k = 1; k <= 13; ++k) {
		    do_fio(&c__1, (char *)&scveos_1.tablez[i__ + (j + k * 76) 
			    * 63 - 4852], (ftnlen)sizeof(doublereal));
		}
		e_rsfe();
	    }
	}
    }
    return 0;
} /* setups_ */

