/* wrtlst.f -- translated by f2c (version 20061008).
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
    doublereal cdelrl, cmixl, cmixl2, cmixl3, clndp, csecyr;
} const3_;

#define const3_1 const3_

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
    char compmix[4];
} i2o_;

#define i2o_1 i2o_

struct {
    doublereal hras;
    integer kttau, kttau0;
    logical lttau;
} atmos_;

#define atmos_1 atmos_

struct {
    doublereal wmax, exmd, exw, extau, exr, exm, exl, expr, constfactor, 
	    structfactor, excen, c_2__;
    logical ljdot0;
} cwind_;

#define cwind_1 cwind_

struct {
    doublereal cdh, etadh0, etadh1, zdh[18], xxdh, yydh, zzdh, dhnue[18];
    logical ldh;
} debhu_;

#define debhu_1 debhu_

struct {
    doublereal sage, tdisk, pdisk;
    logical ldisk;
} disk_;

#define disk_1 disk_

struct {
    doublereal dpenv, alphac, alphae, alpham, betac;
    integer iov1, iov2, iovim;
    logical lovstc, lovste, lovstm, lsemic, ladov, lovmax;
} dpmix_;

#define dpmix_1 dpmix_

struct {
    doublereal grtol;
    integer ilambda, niter_gs__;
    logical ldify;
} gravst_;

#define gravst_1 gravst_

struct {
    doublereal fgry, fgrz;
    logical lthoul, ldifz;
} gravs3_;

#define gravs3_1 gravs3_

struct {
    doublereal zlaol1, zlaol2, zopal1, zopal2, zopal951, zalex1, zkur1, zkur2,
	     tmolmin, tmolmax;
    logical lalex06, llaol89, lopal92, lopal95, lkur90, lalex95, l2z;
} newopac_;

#define newopac_1 newopac_

struct {
    doublereal olaol[64896]	/* was [12][104][52] */, oxa[12], ot[52], 
	    orho[104], tollaol;
    integer iolaol, numofxyz, numrho, numt;
    logical llaol, lpurez;
    integer iopurez;
} nwlaol_;

#define nwlaol_1 nwlaol_

struct {
    logical lopale;
    integer iopale;
    logical lopale01, lopale06, lnumderiv;
} opaleos_;

#define opaleos_1 opaleos_

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

/* Table of constant values */

static integer c__1 = 1;



/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */
/* 06 */
/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */
/* MHP 10/02 NKK removed from declared variable list */
/* Subroutine */ int wrtlst_(integer *iwrite, doublereal *hcomp, doublereal *
	hd, doublereal *hl, doublereal *hp, doublereal *hr, doublereal *hs, 
	doublereal *ht, logical *lc, doublereal *trit, doublereal *tril, 
	doublereal *ps, doublereal *ts, doublereal *rs, doublereal *cfenv, 
	doublereal *ftri, doublereal *tlumx, integer *jcore, integer *jenv, 
	integer *model, integer *m, doublereal *smass, doublereal *teffl, 
	doublereal *bl, doublereal *hstot, doublereal *dage, doublereal *
	ddage, doublereal *omega)
{
    /* Format strings */
    static char fmt_360[] = "(i6,\002  #SHELLS=\002,i4,\002  LogTeff=\002,f8"
	    ".5,\002  Log(L/Lsun)=\002,f8.5,\002  Age=\002,f12.5)";
    static char fmt_330[] = "(\002 DUMPED MODEL\002,i5,\002  FILE\002,i3)";
    static char fmt_340[] = "(\002 DUMPED MODEL\002,i5,\002 AGE\002,f13.9"
	    ",\002  FILE\002,i3)";

    /* System generated locals */
    alist al__1;

    /* Builtin functions */
    /* Subroutine */ void s_copy(char *, char *, ftnlen, ftnlen);
    integer s_wsfe(cilist *), do_fio(integer *, char *, ftnlen), e_wsfe(void),
	     f_rew(alist *);

    /* Local variables */
    extern /* Subroutine */ int putmodel2_(doublereal *, doublereal *, 
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
	    ftnlen);
    static char hik[4], atm[4], eos[6], alok[4];

    /* Fortran I/O blocks */
    static cilist io___5 = { 0, 0, 0, fmt_360, 0 };
    static cilist io___6 = { 0, 0, 0, fmt_330, 0 };
    static cilist io___7 = { 0, 0, 0, fmt_340, 0 };


/*  WRTLST WRITES THE CONVERGED MODEL TO LAST MODEL A(STORES LAST */
/*  CONVERGED MODEL) AND STORE MODELS D(EVERY NPUNCH MODELS) */
/*     WRITE MODEL OUT IN ASCII FORMAT */
/*     CHARACTER*4 ATM, LOK, HIK, COMPMIX */
/* MHP 4/25 changed LOK name to make it unique, used elsewhere */
/* MHP 8/25 Removed unused variables */
/*      CHARACTER*256 FLAOL, FPUREZ */
/*      CHARACTER*256 FOPALE,FOPALE01,FOPALE06  ! FcondOpacP */
/* llp  3/19/03 Add COMMON block /I2O/ for info directly transferred from */
/*      input to output model - starting with a code for th initial model */
/*      compostion (COMPMIX) */
/* llp 3/19/03 Add required COMMON blocks such that header flags */
/*     ATM, EOS, HIK and LOK can be determined. */
/*      COMMON/CWIND/WMAX,EXMD,EXW,EXTAU,EXR,EXM,CONSTFACTOR,STRUCTFACTOR,LJDOT0 */
/* MHP 8/17 ADDED EXCEN, C_2 TO COMMON BLOCK FOR MATT ET AL. 2012 CENT. TERM */
/* OPACITY COMMON BLOCKS - modified 3/09 */
/* MHP 8/25 Removed file names from common blocks */
/* KC 2025-05-30 reordered common block elements */
/*       COMMON/OPALEOS/FOPALE,LOPALE,IOPALE,FOPALE01,LOPALE01, */
/*      x  FOPALE06,LOPALE06,LNumDeriv */
/* MHP 8/25 Remove file names from common blocks */
/* physics flags: */
/* Determine atmosphere flag, ATM */
    /* Parameter adjustments */
    --omega;
    --tlumx;
    --cfenv;
    --rs;
    --ts;
    --ps;
    --tril;
    --trit;
    --lc;
    --ht;
    --hs;
    --hr;
    --hp;
    --hl;
    --hd;
    hcomp -= 16;

    /* Function Body */
    if (atmos_1.kttau == 0) {
	s_copy(atm, "EDD ", (ftnlen)4, (ftnlen)4);
    } else if (atmos_1.kttau == 1) {
	s_copy(atm, "KS  ", (ftnlen)4, (ftnlen)4);
    } else if (atmos_1.kttau == 2) {
	s_copy(atm, "HRA ", (ftnlen)4, (ftnlen)4);
    } else if (atmos_1.kttau == 3) {
	s_copy(atm, "KUR ", (ftnlen)4, (ftnlen)4);
    } else if (atmos_1.kttau == 4) {
	s_copy(atm, "ALL ", (ftnlen)4, (ftnlen)4);
/* JNT 06/14 */
    } else if (atmos_1.kttau == 5) {
	s_copy(atm, "K/C ", (ftnlen)4, (ftnlen)4);
    }
/* Determine equation of state flag, EOS */
    s_copy(eos, "SAHA  ", (ftnlen)6, (ftnlen)6);
    if (debhu_1.ldh) {
	s_copy(eos, "SAH+DH", (ftnlen)6, (ftnlen)6);
    }
    if (scveos_1.lscv) {
	s_copy(eos, "SCV   ", (ftnlen)6, (ftnlen)6);
	if (opaleos_1.lopale) {
	    s_copy(eos, "SCV+OP", (ftnlen)6, (ftnlen)6);
	}
	if (opaleos_1.lopale01) {
	    s_copy(eos, "SCV+O1", (ftnlen)6, (ftnlen)6);
	}
	if (debhu_1.ldh) {
	    if (opaleos_1.lopale06) {
		s_copy(eos, "SCV+O6", (ftnlen)6, (ftnlen)6);
	    }
	    s_copy(eos, "SCV+DH", (ftnlen)6, (ftnlen)6);
	    if (opaleos_1.lopale) {
		s_copy(eos, "SCVDHO", (ftnlen)6, (ftnlen)6);
	    }
	    if (opaleos_1.lopale01) {
		s_copy(eos, "SCDHO1", (ftnlen)6, (ftnlen)6);
	    }
	    if (opaleos_1.lopale06) {
		s_copy(eos, "SCDHO6", (ftnlen)6, (ftnlen)6);
	    }
	}
    } else {
	if (opaleos_1.lopale) {
	    s_copy(eos, "OPAL  ", (ftnlen)6, (ftnlen)6);
	    if (debhu_1.ldh) {
		s_copy(eos, "OPA+DH", (ftnlen)6, (ftnlen)6);
	    }
	}
	if (opaleos_1.lopale01) {
	    s_copy(eos, "OPAL01", (ftnlen)6, (ftnlen)6);
	    if (debhu_1.ldh) {
		s_copy(eos, "OP1+DH", (ftnlen)6, (ftnlen)6);
	    }
	}
	if (opaleos_1.lopale06) {
	    s_copy(eos, "OPAL06", (ftnlen)6, (ftnlen)6);
	    if (debhu_1.ldh) {
		s_copy(eos, "OP6+DH", (ftnlen)6, (ftnlen)6);
	    }
	}
    }
/* Determine low temperature opacities flag, ALOK */
    s_copy(alok, "NONE", (ftnlen)4, (ftnlen)4);
    if (newopac_1.lalex95) {
	s_copy(alok, "ALEX", (ftnlen)4, (ftnlen)4);
    }
    if (newopac_1.lkur90) {
	s_copy(alok, "KURZ", (ftnlen)4, (ftnlen)4);
    }
/* Determine high temperature opacities flag, HIK */
    s_copy(hik, "NONE", (ftnlen)4, (ftnlen)4);
    if (newopac_1.lopal95) {
	s_copy(hik, "OP95", (ftnlen)4, (ftnlen)4);
    }
    if (newopac_1.lopal92) {
	s_copy(hik, "OP92", (ftnlen)4, (ftnlen)4);
    }
    if (newopac_1.llaol89) {
	s_copy(hik, "LL89", (ftnlen)4, (ftnlen)4);
    }
    putmodel2_(bl, &cfenv[1], &const3_1.cmixl, dage, ddage, ftri, &hcomp[16], 
	    &hd[1], &hl[1], &hp[1], &hr[1], &hs[1], hstot, &ht[1], iwrite, &
	    luout_1.ishort, jcore, jenv, &lc[1], &flag_1.lexcom, &rot_1.lrot, 
	    m, model, &omega[1], &ps[1], &rs[1], smass, teffl, &tlumx[1], &
	    tril[1], &trit[1], &ts[1], atm, eos, hik, &gravst_1.ldify, &
	    gravs3_1.ldifz, &disk_1.ldisk, &rot_1.linstb, &cwind_1.ljdot0, 
	    alok, &dpmix_1.lovstc, &dpmix_1.lovste, &dpmix_1.lovstm, &
	    nwlaol_1.lpurez, &dpmix_1.lsemic, i2o_1.compmix, &disk_1.pdisk, &
	    disk_1.tdisk, &cwind_1.wmax, (ftnlen)4, (ftnlen)6, (ftnlen)4, (
	    ftnlen)4, (ftnlen)4);
/* First three lines above are YREC7 inputs */
/* Last two lines are MODEL2 add-ons */
    io___5.ciunit = luout_1.iowr;
    s_wsfe(&io___5);
    do_fio(&c__1, (char *)&(*model), (ftnlen)sizeof(integer));
    do_fio(&c__1, (char *)&(*m), (ftnlen)sizeof(integer));
    do_fio(&c__1, (char *)&(*teffl), (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&(*bl), (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&(*dage), (ftnlen)sizeof(doublereal));
    e_wsfe();
    if (*iwrite == 11) {
	io___6.ciunit = luout_1.ishort;
	s_wsfe(&io___6);
	do_fio(&c__1, (char *)&(*model), (ftnlen)sizeof(integer));
	do_fio(&c__1, (char *)&(*iwrite), (ftnlen)sizeof(integer));
	e_wsfe();
    } else {
	io___7.ciunit = luout_1.ishort;
	s_wsfe(&io___7);
	do_fio(&c__1, (char *)&(*model), (ftnlen)sizeof(integer));
	do_fio(&c__1, (char *)&(*dage), (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&(*iwrite), (ftnlen)sizeof(integer));
	e_wsfe();
    }
    if (*iwrite == luout_1.ilast) {
	al__1.aerr = 0;
	al__1.aunit = luout_1.ilast;
	f_rew(&al__1);
    }
    return 0;
} /* wrtlst_ */

