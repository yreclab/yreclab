/* wrtmonte.f -- translated by f2c (version 20061008).
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
    doublereal rescal[200]	/* was [4][50] */;
    integer nmodls[50], iresca[50];
    logical lfirst[50];
    integer numrun;
} ckind_;

#define ckind_1 ckind_

struct {
    doublereal xenv0a[50], zenv0a[50], cmixla[50];
    logical lsenv0a[50];
    doublereal senv0a[50];
} newxym_;

#define newxym_1 newxym_

struct {
    doublereal dldx, drdx, dlda, drda, blp, rlp, dx, da;
    logical lsol;
} calsun_;

#define calsun_1 calsun_

struct {
    doublereal flux[10], fluxtot[10], clsnu, gasnu;
} fluxes_;

#define fluxes_1 fluxes_

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
    char fmonte1[256], fmonte2[256];
    integer imonte1, imonte2;
} iomonte_;

#define iomonte_1 iomonte_

/* Table of constant values */

static integer c__1 = 1;
static doublereal c_b27 = 10.;

/*      SUBROUTINE FOR WRITING MONTE CARLO OUTPUT */
/*       SUBROUTINE WRTMONTE(HCOMP,HD,HL,HP,HR,HS,HT,LC,M,MODEL,DAGE, */
/*      *DDAGE,SMASS,TEFFL,BL,GL,LSHELL,JXBEG,JXMID,JXEND,JCORE,JENV,  ! KC 2025-05-31 */
/* Subroutine */ int wrtmonte_(doublereal *hcomp, doublereal *hd, doublereal *
	hl, doublereal *hp, doublereal *hr, doublereal *hs, doublereal *ht, 
	logical *lc, integer *m, doublereal *dage, doublereal *ddage, 
	doublereal *smass, doublereal *teffl, doublereal *bl, integer *jcore, 
	integer *jenv, doublereal *tlumx, doublereal *trit, doublereal *tril, 
	doublereal *ps, doublereal *ts, doublereal *rs, doublereal *cfenv, 
	doublereal *ftri, doublereal *hstot, doublereal *omega, doublereal *
	rll, integer *iconv, integer *nk, integer *nn)
{
    /* Format strings */
    static char fmt_10[] = "(i7,1p9e10.3)";
    static char fmt_20[] = "(1x,i2,1p4e11.4)";
    static char fmt_30[] = "(1x,2f8.3,1p8e10.3)";
    static char fmt_40[] = "(1x,f7.3,f7.2,f6.3,2f8.5)";
    static char fmt_50[] = "(i5,f7.4,2f8.5,1p2e10.3)";
    static char fmt_60[] = "(f8.5,f9.6,2f8.5,f9.6)";
    static char fmt_70[] = "(1p5e10.3)";

    /* System generated locals */
    doublereal d__1;

    /* Builtin functions */
    integer s_wsfe(cilist *), do_fio(integer *, char *, ftnlen), e_wsfe(void);
    double pow_dd(doublereal *, doublereal *);

    /* Local variables */
    static integer i__, j;
    static doublereal dcen, pcen, tcen, yini, zini, ztox;
    static integer iwrite;
    extern /* Subroutine */ int wrtlst_(integer *, doublereal *, doublereal *,
	     doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, logical *, doublereal *, doublereal *, doublereal *,
	     doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, integer *, integer *, integer *, integer *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *);

    /* Fortran I/O blocks */
    static cilist io___3 = { 0, 0, 0, fmt_10, 0 };
    static cilist io___4 = { 0, 0, 0, fmt_20, 0 };
    static cilist io___5 = { 0, 0, 0, fmt_30, 0 };
    static cilist io___10 = { 0, 0, 0, fmt_40, 0 };
    static cilist io___13 = { 0, 0, 0, fmt_50, 0 };
    static cilist io___14 = { 0, 0, 0, fmt_60, 0 };
    static cilist io___15 = { 0, 0, 0, fmt_70, 0 };


/* MHP 3/96 CENTRAL T,P,RHO ADDED */
/*  STORE LAST CONVERGED MODEL IN LOGICAL UNIT IMONTE2 */
    /* Parameter adjustments */
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
    --hs;
    --hr;
    --hp;
    --hl;
    --hd;
    hcomp -= 16;

    /* Function Body */
    iwrite = iomonte_1.imonte2;
    wrtlst_(&iwrite, &hcomp[16], &hd[1], &hl[1], &hp[1], &hr[1], &hs[1], &ht[
	    1], &lc[1], &trit[1], &tril[1], &ps[1], &ts[1], &rs[1], &cfenv[1],
	     ftri, &tlumx[1], jcore, jenv, nn, m, smass, teffl, bl, hstot, 
	    dage, ddage, &omega[1]);
/* GLOBAL INFORMATION SENT TO FIRST MONTE CARLO OUTPUT FILE */
/* SURFACE Z/X */
    ztox = hcomp[*m * 15 + 3] / hcomp[*m * 15 + 1];
/* HEADER FILE:  MONTE CARLO PARAMETERS */
    io___3.ciunit = iomonte_1.imonte1;
    s_wsfe(&io___3);
    do_fio(&c__1, (char *)&(*nn), (ftnlen)sizeof(integer));
    do_fio(&c__1, (char *)&monte2_1.s11[*nn - 1], (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&monte2_1.s33[*nn - 1], (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&monte2_1.s34[*nn - 1], (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&monte2_1.s17[*nn - 1], (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&monte2_1.zx[*nn - 1], (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&monte2_1.fhe[*nn - 1], (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&monte2_1.fzdif[*nn - 1], (ftnlen)sizeof(doublereal)
	    );
    do_fio(&c__1, (char *)&monte2_1.flum[*nn - 1], (ftnlen)sizeof(doublereal))
	    ;
    do_fio(&c__1, (char *)&monte2_1.fage[*nn - 1], (ftnlen)sizeof(doublereal))
	    ;
    e_wsfe();
/* NUMERICAL DATA : #OF RUNS NEEDED FOR A CONVERGED MODEL, INITIAL X */
/* AND ALPHA, FINAL DL/DX,DR/DX,DL/D ALPHA, DR/D ALPHA */
    io___4.ciunit = iomonte_1.imonte1;
    s_wsfe(&io___4);
    do_fio(&c__1, (char *)&(*iconv), (ftnlen)sizeof(integer));
    do_fio(&c__1, (char *)&calsun_1.dldx, (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&calsun_1.drdx, (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&calsun_1.dlda, (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&calsun_1.drda, (ftnlen)sizeof(doublereal));
    e_wsfe();
/*      WRITE(IMONTE1,20)ICONV,XGUESS,AGUESS,DLDX,DRDX,DLDA,DRDA */
/* 20   FORMAT(1X,I2,2F10.6,1P4E11.4) */
/* NEUTRINO FLUXES (SEE ENGEB FOR DETAILS) */
    io___5.ciunit = iomonte_1.imonte1;
    s_wsfe(&io___5);
    do_fio(&c__1, (char *)&fluxes_1.clsnu, (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&fluxes_1.gasnu, (ftnlen)sizeof(doublereal));
    for (i__ = 1; i__ <= 8; ++i__) {
	do_fio(&c__1, (char *)&fluxes_1.fluxtot[i__ - 1], (ftnlen)sizeof(
		doublereal));
    }
    e_wsfe();
/* SUMMARY OF STRUCTURE : TC, RHOC, PC, XC, ZC (ADD MU C) */
    d__1 = cent_1.tcenter - 6.;
    tcen = pow_dd(&c_b27, &d__1);
    d__1 = cent_1.pcenter - 17.;
    pcen = pow_dd(&c_b27, &d__1);
    dcen = pow_dd(&c_b27, &cent_1.dcenter);
    io___10.ciunit = iomonte_1.imonte1;
    s_wsfe(&io___10);
    do_fio(&c__1, (char *)&tcen, (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&dcen, (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&pcen, (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&hcomp[16], (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&hcomp[18], (ftnlen)sizeof(doublereal));
    e_wsfe();
/*  #SHELLS, INITIAL ALPHA, Y, Z; FINAL R, L */
    yini = 1. - ckind_1.rescal[(*nk - 2 << 2) - 3] - ckind_1.rescal[(*nk - 2 
	    << 2) - 2];
    zini = ckind_1.rescal[(*nk - 2 << 2) - 2];
    io___13.ciunit = iomonte_1.imonte1;
    s_wsfe(&io___13);
    do_fio(&c__1, (char *)&(*m), (ftnlen)sizeof(integer));
    do_fio(&c__1, (char *)&newxym_1.cmixla[*nk - 1], (ftnlen)sizeof(
	    doublereal));
    do_fio(&c__1, (char *)&yini, (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&zini, (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&(*bl), (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&(*rll), (ftnlen)sizeof(doublereal));
    e_wsfe();
/*  CZ DEPTH (R,M), SURFACE Y, Z, Z/X (ADD T CZ BASE, RHO CZ BASE) */
    io___14.ciunit = iomonte_1.imonte1;
    s_wsfe(&io___14);
    do_fio(&c__1, (char *)&cent_1.envr, (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&cent_1.envlm, (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&hcomp[*m * 15 + 2], (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&hcomp[*m * 15 + 3], (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&ztox, (ftnlen)sizeof(doublereal));
    e_wsfe();
/*  ENERGY GENERATION FRACTIONS PP I,II,III,CNO,EGRAV */
    io___15.ciunit = iomonte_1.imonte1;
    s_wsfe(&io___15);
    for (j = 1; j <= 4; ++j) {
	do_fio(&c__1, (char *)&tlumx[j], (ftnlen)sizeof(doublereal));
    }
    do_fio(&c__1, (char *)&tlumx[7], (ftnlen)sizeof(doublereal));
    e_wsfe();
    return 0;
} /* wrtmonte_ */

