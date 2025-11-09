/* putstore.f -- translated by f2c (version 20061008).
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
    doublereal sesum[5000], seg[35000]	/* was [7][5000] */, sbeta[5000], 
	    seta[5000];
    logical locons[5000];
    doublereal so[5000], sdel[15000]	/* was [3][5000] */, sfxion[15000]	
	    /* was [3][5000] */, svel[5000], scp[5000];
} scrtch_;

#define scrtch_1 scrtch_

struct {
    doublereal gam1[5000];
    logical lsound;
} sound_;

#define sound_1 sound_

struct {
    doublereal ves[5000], ves0[5000], vss[5000], vss0[5000], hle[5000], vgsf[
	    5000], vgsf0[5000], vmu[5000];
} temp2_;

#define temp2_1 temp2_

struct {
    doublereal derot[5000];
} roten_;

#define roten_1 roten_

/* Table of constant values */

static integer c__1 = 1;
static real c_b191 = 0.f;


/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */
/* PUTSTORE - Write out a verbose stellar model to the .store file. This program */
/*            is mostly a clone of wrtlst.f and putmodel2.f, combined. */

/* G Somers  11/14 */
/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */


/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */
/* 06 */
/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */
/* Subroutine */ int putstore_(doublereal *hcomp, doublereal *hd, doublereal *
	hl, doublereal *hp, doublereal *hr, doublereal *hs, doublereal *ht, 
	logical *lc, doublereal *trit, doublereal *tril, doublereal *ps, 
	doublereal *ts, doublereal *rs, doublereal *cfenv, doublereal *ftri, 
	doublereal *tlumx, integer *jcore, integer *jenv, integer *model, 
	integer *m, doublereal *smass, doublereal *teffl, doublereal *bl, 
	doublereal *hstot, doublereal *dage, doublereal *ddage, doublereal *
	omega, doublereal *hs1, doublereal *eta2, doublereal *r0, doublereal *
	fp, doublereal *ft, doublereal *hjm, doublereal *hi)
{
    /* Format strings */
    static char fmt_7[] = "(\002*** YREC7 input file, flags, etc., have be"
	    "en \002,\002defaulted.  ***\002)";
    static char fmt_1013[] = "(\002# JCORE  JENV  CMIXL  EOS  ATM  ALOK HIK "
	    " LPUREZ  COMPMIX\002,\002  LEXCOM  LDIFY  LDIFZ  LSEMIC  LOVSTC "
	    " LOVSTE  LOVSTM\002,\002  LROT  LINSTB  LJDOT0  LDISK  TDISK  PD"
	    "ISK  WMAX  LSTORE\002,\002  LSTATM  LSTENV  LSTMOD  LSTPHYS  LST"
	    "ROT\002)";
    static char fmt_29[] = "(\002#\002,2i8,f16.10,1x,a6,1x,3(a4,1x),l1,1x,a4"
	    ",1x,11(l1,1x),3(1pe18.10),1x,6(l1,1x))";
    static char fmt_1014[] = "(\002MODEL SHELL MASS RADIUS LUMINOSITY PRESSU"
	    "RE TEMPERATURE DENSITY OMEGA \002,\002CONVECTIVE INTERIOR_PT ENV"
	    "_PT ATM_PT H1 He4 METALS He3 C12 C13 N14 N15 O16 \002,\002O17 O1"
	    "8 H2 Li6 Li7 Be9 OPACITY GRAV DELR DEL DELAD V_CONV GAM1 HII HEI"
	    "I HEIII \002,\002BETA ETA PPI PPII PPIII CNO TRIPLE_ALPHA E_NUC "
	    "E_NEU E_GRAV CP DLNRHODLNT A \002,\002RP/RE FP FT J/M MOMENT DEL"
	    "_KE V_ES V_GSF V_SS VTOT \002)";
    static char fmt_10[] = "(a5,2i8,5f16.11,1pe18.10,0p2f16.12)";
    static char fmt_11[] = "(a5,2i8,4f16.12,f16.10,1pe18.10,0p2f16.12)";
    static char fmt_12[] = "(a5,2i8,4f16.12,f16.9,1pe18.10,0p2f16.12)";
    static char fmt_13[] = "(a5,2i8,4f16.12,f16.8,1pe18.10,0p2f16.12)";
    static char fmt_30[] = "(2i8,f16.10,1x,a6,1x,3(a4,1x),l1,1x,a4,1x,11(l1,"
	    "1x),3(1pe18.10),1x,6(l1,1x))";
    static char fmt_40[] = "(\002TLUMX\002,5x,1p7e17.9)";
    static char fmt_50[] = "(\002ENV\002,i2,5f16.12,1p3e20.12)";
    static char fmt_55[] = "(/,\002 SHELL       MASS             RADIUS     "
	    "        LUMINOSITY            \002,\002PRESSURE         TEMPERAT"
	    "URE         DENSITY               OMEGA      \002,\002    C     "
	    "H1          He4        METALS         He3             C12   \002,"
	    "\002          C13             N14             N15             O1"
	    "6         \002,\002    O17             O18             H2       "
	    "       Li6             Li7\002,\002             Be9           OP"
	    "AC       GRAV        DELR        DEL      \002,\002   DELA      "
	    " V_CONV     GAM1      HII     HEII     HEIII    BETA      \002"
	    ",\002ETA       PPI         PPII       PPIII        CNO         3"
	    "HE         \002,\002E_NUC        E_NEU       E_GRAV          A  "
	    "         RP/RE           FP\002,\002            FT           J/M"
	    "          MOMENT        DEL_KE       V_ES \002,\002      V_GSF  "
	    "    V_SS       VTOT   \002,/)";
    static char fmt_62[] = "(i6,0p2f18.14,1pe24.16,0p3f18.14,1pe24.16,1x,l1,"
	    "3(0pf12.9),12(0pe16.8),2x,1pe10.4,1pe11.3,e12.4,e12.4,e12.4,1pe1"
	    "2.4,0pf9.5,f9.5,f9.5,f9.5,f9.5,f9.5,e12.4,e12.4,e12.4,e12.4,e12."
	    "4,e13.5,e13.5,e13.5,e14.6,e14.6,e14.6,e14.6,e14.6,e14.6,e14.6,e1"
	    "1.3,e11.3,e11.3,e11.3,e11.3)";
    static char fmt_65[] = "(/,/)";

    /* System generated locals */
    integer i__1;
    doublereal d__1, d__2;

    /* Builtin functions */
    /* Subroutine */ void s_copy(char *, char *, ftnlen, ftnlen);
    integer s_cmp(char *, char *, ftnlen, ftnlen), s_wsfe(cilist *), e_wsfe(
	    void), do_fio(integer *, char *, ftnlen);
    double exp(doublereal);

    /* Local variables */
    static doublereal a;
    static integer i__, j, k, i0;
    static doublereal cg;
    static integer id[5000], ii;
    static doublereal sg;
    static integer idm;
    static char hik[4], atm[4], eos[6], alok[4];
    static doublereal vtot;
    static integer jxbeg, jxend;
    static doublereal cccmax;
    extern /* Subroutine */ int stitch_(doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, integer *,
	     logical *, integer *), pindex_(integer *, integer *, logical *, 
	    integer *, integer *, integer *);
    static logical lshell;
    static doublereal rpoleq;
    static logical lmilne;
    extern /* Subroutine */ int wrtmil_(doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, integer *,
	     integer *), wrtmod_(integer *, integer *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, integer *, doublereal *, doublereal *,
	     doublereal *, doublereal *, doublereal *, doublereal *);

    /* Fortran I/O blocks */
    static cilist io___5 = { 0, 0, 0, fmt_7, 0 };
    static cilist io___6 = { 0, 0, 0, fmt_1013, 0 };
    static cilist io___7 = { 0, 0, 0, fmt_29, 0 };
    static cilist io___8 = { 0, 0, 0, fmt_1014, 0 };
    static cilist io___9 = { 0, 0, 0, fmt_10, 0 };
    static cilist io___10 = { 0, 0, 0, fmt_11, 0 };
    static cilist io___11 = { 0, 0, 0, fmt_12, 0 };
    static cilist io___12 = { 0, 0, 0, fmt_13, 0 };
    static cilist io___13 = { 0, 0, 0, fmt_30, 0 };
    static cilist io___16 = { 0, 0, 0, fmt_40, 0 };
    static cilist io___19 = { 0, 0, 0, fmt_50, 0 };
    static cilist io___25 = { 0, 0, 0, fmt_55, 0 };
    static cilist io___29 = { 0, 0, 0, fmt_62, 0 };
    static cilist io___34 = { 0, 0, 0, fmt_62, 0 };
    static cilist io___35 = { 0, 0, 0, fmt_62, 0 };
    static cilist io___36 = { 0, 0, 0, fmt_62, 0 };
    static cilist io___38 = { 0, 0, 0, fmt_65, 0 };


/*  PUTSTORE PUTS THE MOST RECENT VERBOSE OUTPUT FILE INTO THE .STORE FILE, */
/*  EITHER AT SPECIFIED AGES, EVERY NPRTMOD MODELS, OR AT THE END OF RUNS. */
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
/* MHP 8/17 ADDED EXCEN, C_2 TO COMMON BLOCK FOR MATT ET AL. 2012 CENT. TERM */
/*      COMMON/CWIND/WMAX,EXMD,EXW,EXTAU,EXR,EXM,CONSTFACTOR,STRUCTFACTOR,LJDOT0 */
/*      COMMON/DPMIX/DPENV,ALPHAC,ALPHAE,ALPHAM,IOV1,IOV2, */
/*     *      IOVIM, LOVSTC, LOVSTE, LOVSTM, LSEMIC, LADOV */
/* OPACITY COMMON BLOCKS - modified 3/09 */
/* MHP 8/25 Removed character file names from common block */
/* KC 2025-05-30 reordered common block elements */
/*       COMMON/OPALEOS/FOPALE,LOPALE,IOPALE,FOPALE01,LOPALE01, */
/*      x  FOPALE06,LOPALE06,LNumDeriv */
/* MHP 8/25 Remove file names from common blocks */
/* INCLUDE COMMON BLOCKS WITH REQUIRED PHYSICS AND OUTPUT FLAGS */
/* physics flags: */
/* Determine atmosphere flag, ATM */
    /* Parameter adjustments */
    --hi;
    --hjm;
    --ft;
    --fp;
    --r0;
    --eta2;
    --hs1;
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
/* Determine low temperature opacities flag, LOK */
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
    if (s_cmp(atm, " ? ", (ftnlen)4, (ftnlen)3) == 0) {
	io___5.ciunit = luout_1.ishort;
	s_wsfe(&io___5);
	e_wsfe();
    }
/* 09/25 JvS: Add secondary format option that prints stitched interior and envelope */
/* points. Output is either in the old format or new format, not both. */
    if (ccout_1.lstch) {
	if (ccout_1.lphhd) {
	    io___6.ciunit = luout_1.istor;
	    s_wsfe(&io___6);
	    e_wsfe();
/* write model physics header. Should only happen upon first model output. */
/* write physics flags: */
/* header key */
	    io___7.ciunit = luout_1.istor;
	    s_wsfe(&io___7);
	    do_fio(&c__1, (char *)&(*jcore), (ftnlen)sizeof(integer));
	    do_fio(&c__1, (char *)&(*jenv), (ftnlen)sizeof(integer));
	    do_fio(&c__1, (char *)&const3_1.cmixl, (ftnlen)sizeof(doublereal))
		    ;
	    do_fio(&c__1, eos, (ftnlen)6);
	    do_fio(&c__1, atm, (ftnlen)4);
	    do_fio(&c__1, alok, (ftnlen)4);
	    do_fio(&c__1, hik, (ftnlen)4);
	    do_fio(&c__1, (char *)&nwlaol_1.lpurez, (ftnlen)sizeof(logical));
	    do_fio(&c__1, i2o_1.compmix, (ftnlen)4);
	    do_fio(&c__1, (char *)&flag_1.lexcom, (ftnlen)sizeof(logical));
	    do_fio(&c__1, (char *)&gravst_1.ldify, (ftnlen)sizeof(logical));
	    do_fio(&c__1, (char *)&gravs3_1.ldifz, (ftnlen)sizeof(logical));
	    do_fio(&c__1, (char *)&dpmix_1.lsemic, (ftnlen)sizeof(logical));
	    do_fio(&c__1, (char *)&dpmix_1.lovstc, (ftnlen)sizeof(logical));
	    do_fio(&c__1, (char *)&dpmix_1.lovste, (ftnlen)sizeof(logical));
	    do_fio(&c__1, (char *)&dpmix_1.lovstm, (ftnlen)sizeof(logical));
	    do_fio(&c__1, (char *)&rot_1.lrot, (ftnlen)sizeof(logical));
	    do_fio(&c__1, (char *)&rot_1.linstb, (ftnlen)sizeof(logical));
	    do_fio(&c__1, (char *)&cwind_1.ljdot0, (ftnlen)sizeof(logical));
	    do_fio(&c__1, (char *)&disk_1.ldisk, (ftnlen)sizeof(logical));
	    do_fio(&c__1, (char *)&disk_1.tdisk, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&disk_1.pdisk, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&cwind_1.wmax, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&ccout_1.lstore, (ftnlen)sizeof(logical));
	    do_fio(&c__1, (char *)&ccout_1.lstatm, (ftnlen)sizeof(logical));
	    do_fio(&c__1, (char *)&ccout_1.lstenv, (ftnlen)sizeof(logical));
	    do_fio(&c__1, (char *)&ccout_1.lstmod, (ftnlen)sizeof(logical));
	    do_fio(&c__1, (char *)&ccout_1.lstphys, (ftnlen)sizeof(logical));
	    do_fio(&c__1, (char *)&ccout_1.lstrot, (ftnlen)sizeof(logical));
	    e_wsfe();
	    io___8.ciunit = luout_1.istor;
	    s_wsfe(&io___8);
	    e_wsfe();
/* profile header */
	    ccout_1.lphhd = FALSE_;
/* Turn off the physics header fo the rest of the run. */
	}
	stitch_(&hcomp[16], &hr[1], &hp[1], &hd[1], &hs[1], &ht[1], &hl[1], &
		hs1[1], &omega[1], &eta2[1], &hi[1], &r0[1], &hjm[1], &fp[1], 
		&ft[1], teffl, hstot, bl, m, &lc[1], model);
    } else {
/* write header records */
	if (*dage < 1e3) {
	    io___9.ciunit = luout_1.istor;
	    s_wsfe(&io___9);
	    do_fio(&c__1, "MOD2 ", (ftnlen)5);
	    do_fio(&c__1, (char *)&(*model), (ftnlen)sizeof(integer));
	    do_fio(&c__1, (char *)&(*m), (ftnlen)sizeof(integer));
	    do_fio(&c__1, (char *)&(*smass), (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&(*teffl), (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&(*bl), (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&(*hstot), (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&(*dage), (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&(*ddage), (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&hs[1], (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&hs[*m], (ftnlen)sizeof(doublereal));
	    e_wsfe();
	} else if (*dage < 1e4) {
	    io___10.ciunit = luout_1.istor;
	    s_wsfe(&io___10);
	    do_fio(&c__1, "MOD2 ", (ftnlen)5);
	    do_fio(&c__1, (char *)&(*model), (ftnlen)sizeof(integer));
	    do_fio(&c__1, (char *)&(*m), (ftnlen)sizeof(integer));
	    do_fio(&c__1, (char *)&(*smass), (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&(*teffl), (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&(*bl), (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&(*hstot), (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&(*dage), (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&(*ddage), (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&hs[1], (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&hs[*m], (ftnlen)sizeof(doublereal));
	    e_wsfe();
	} else if (*dage < 1e5) {
	    io___11.ciunit = luout_1.istor;
	    s_wsfe(&io___11);
	    do_fio(&c__1, "MOD2 ", (ftnlen)5);
	    do_fio(&c__1, (char *)&(*model), (ftnlen)sizeof(integer));
	    do_fio(&c__1, (char *)&(*m), (ftnlen)sizeof(integer));
	    do_fio(&c__1, (char *)&(*smass), (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&(*teffl), (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&(*bl), (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&(*hstot), (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&(*dage), (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&(*ddage), (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&hs[1], (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&hs[*m], (ftnlen)sizeof(doublereal));
	    e_wsfe();
	} else {
	    io___12.ciunit = luout_1.istor;
	    s_wsfe(&io___12);
	    do_fio(&c__1, "MOD2 ", (ftnlen)5);
	    do_fio(&c__1, (char *)&(*model), (ftnlen)sizeof(integer));
	    do_fio(&c__1, (char *)&(*m), (ftnlen)sizeof(integer));
	    do_fio(&c__1, (char *)&(*smass), (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&(*teffl), (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&(*bl), (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&(*hstot), (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&(*dage), (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&(*ddage), (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&hs[1], (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&hs[*m], (ftnlen)sizeof(doublereal));
	    e_wsfe();
	}
/* write physics flags: */
	io___13.ciunit = luout_1.istor;
	s_wsfe(&io___13);
	do_fio(&c__1, (char *)&(*jcore), (ftnlen)sizeof(integer));
	do_fio(&c__1, (char *)&(*jenv), (ftnlen)sizeof(integer));
	do_fio(&c__1, (char *)&const3_1.cmixl, (ftnlen)sizeof(doublereal));
	do_fio(&c__1, eos, (ftnlen)6);
	do_fio(&c__1, atm, (ftnlen)4);
	do_fio(&c__1, alok, (ftnlen)4);
	do_fio(&c__1, hik, (ftnlen)4);
	do_fio(&c__1, (char *)&nwlaol_1.lpurez, (ftnlen)sizeof(logical));
	do_fio(&c__1, i2o_1.compmix, (ftnlen)4);
	do_fio(&c__1, (char *)&flag_1.lexcom, (ftnlen)sizeof(logical));
	do_fio(&c__1, (char *)&gravst_1.ldify, (ftnlen)sizeof(logical));
	do_fio(&c__1, (char *)&gravs3_1.ldifz, (ftnlen)sizeof(logical));
	do_fio(&c__1, (char *)&dpmix_1.lsemic, (ftnlen)sizeof(logical));
	do_fio(&c__1, (char *)&dpmix_1.lovstc, (ftnlen)sizeof(logical));
	do_fio(&c__1, (char *)&dpmix_1.lovste, (ftnlen)sizeof(logical));
	do_fio(&c__1, (char *)&dpmix_1.lovstm, (ftnlen)sizeof(logical));
	do_fio(&c__1, (char *)&rot_1.lrot, (ftnlen)sizeof(logical));
	do_fio(&c__1, (char *)&rot_1.linstb, (ftnlen)sizeof(logical));
	do_fio(&c__1, (char *)&cwind_1.ljdot0, (ftnlen)sizeof(logical));
	do_fio(&c__1, (char *)&disk_1.ldisk, (ftnlen)sizeof(logical));
	do_fio(&c__1, (char *)&disk_1.tdisk, (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&disk_1.pdisk, (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&cwind_1.wmax, (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&ccout_1.lstore, (ftnlen)sizeof(logical));
	do_fio(&c__1, (char *)&ccout_1.lstatm, (ftnlen)sizeof(logical));
	do_fio(&c__1, (char *)&ccout_1.lstenv, (ftnlen)sizeof(logical));
	do_fio(&c__1, (char *)&ccout_1.lstmod, (ftnlen)sizeof(logical));
	do_fio(&c__1, (char *)&ccout_1.lstphys, (ftnlen)sizeof(logical));
	do_fio(&c__1, (char *)&ccout_1.lstrot, (ftnlen)sizeof(logical));
	e_wsfe();
/* write luminosities and output flags */
/* If TLUMX are in solar units, convert to ergs.  Decide by */
/* comparing to 10**20, if smaller, multiply by CLSUN */
/* Computing MAX */
	d__1 = max(tlumx[1],tlumx[2]), d__1 = max(d__1,tlumx[3]), d__1 = max(
		d__1,tlumx[4]), d__1 = max(d__1,tlumx[5]), d__2 = abs(tlumx[6]
		), d__1 = max(d__1,d__2);
	cccmax = max(d__1,tlumx[7]);
	if (cccmax <= 1e20) {
	    for (j = 1; j <= 7; ++j) {
		tlumx[j] *= const_1.clsun;
	    }
	}
	io___16.ciunit = luout_1.istor;
	s_wsfe(&io___16);
	for (j = 1; j <= 7; ++j) {
	    do_fio(&c__1, (char *)&tlumx[j], (ftnlen)sizeof(doublereal));
	}
	e_wsfe();
/* write ENVELOPE DATA */
	for (i__ = 1; i__ <= 3; ++i__) {
	    i0 = i__;
	    if (*ftri < 0.) {
		i0 = -i__;
	    }
	    io___19.ciunit = luout_1.istor;
	    s_wsfe(&io___19);
	    do_fio(&c__1, (char *)&i0, (ftnlen)sizeof(integer));
	    do_fio(&c__1, (char *)&trit[i__], (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&tril[i__], (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&ps[i__], (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&ts[i__], (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&rs[i__], (ftnlen)sizeof(doublereal));
	    for (j = 1; j <= 3; ++j) {
		do_fio(&c__1, (char *)&cfenv[i__ * 3 - 3 + j], (ftnlen)sizeof(
			doublereal));
	    }
	    e_wsfe();
	}
	pindex_(&jxbeg, &jxend, &lshell, m, id, &idm);
	if (ccout_1.lstmod) {
/* write column headings for all per shell information */
	    io___25.ciunit = luout_1.istor;
	    s_wsfe(&io___25);
	    e_wsfe();
/* write out the requested information. */
	    cg = exp(const1_1.cln * const2_1.cgl);
	    i__1 = idm;
	    for (ii = 1; ii <= i__1; ++ii) {
		i__ = id[ii - 1];
/* LC 10/25 rewrite for compatibility with F77 */
		if (ccout_1.lstphys) {
		    sg = exp(const1_1.cln * (const2_1.cgl - hr[i__] * 2.)) * 
			    hs1[i__];
		    if (ccout_1.lstrot && rot_1.lrot) {
			io___29.ciunit = luout_1.istor;
			s_wsfe(&io___29);
			do_fio(&c__1, (char *)&i__, (ftnlen)sizeof(integer));
			do_fio(&c__1, (char *)&hs[i__], (ftnlen)sizeof(
				doublereal));
			do_fio(&c__1, (char *)&hr[i__], (ftnlen)sizeof(
				doublereal));
			do_fio(&c__1, (char *)&hl[i__], (ftnlen)sizeof(
				doublereal));
			do_fio(&c__1, (char *)&hp[i__], (ftnlen)sizeof(
				doublereal));
			do_fio(&c__1, (char *)&ht[i__], (ftnlen)sizeof(
				doublereal));
			do_fio(&c__1, (char *)&hd[i__], (ftnlen)sizeof(
				doublereal));
			do_fio(&c__1, (char *)&omega[i__], (ftnlen)sizeof(
				doublereal));
			do_fio(&c__1, (char *)&lc[i__], (ftnlen)sizeof(
				logical));
			for (j = 1; j <= 15; ++j) {
			    do_fio(&c__1, (char *)&hcomp[j + i__ * 15], (
				    ftnlen)sizeof(doublereal));
			}
			do_fio(&c__1, (char *)&scrtch_1.so[i__ - 1], (ftnlen)
				sizeof(doublereal));
			do_fio(&c__1, (char *)&sg, (ftnlen)sizeof(doublereal))
				;
			do_fio(&c__1, (char *)&scrtch_1.sdel[i__ * 3 - 3], (
				ftnlen)sizeof(doublereal));
			do_fio(&c__1, (char *)&scrtch_1.sdel[i__ * 3 - 2], (
				ftnlen)sizeof(doublereal));
			do_fio(&c__1, (char *)&scrtch_1.sdel[i__ * 3 - 1], (
				ftnlen)sizeof(doublereal));
			do_fio(&c__1, (char *)&scrtch_1.svel[i__ - 1], (
				ftnlen)sizeof(doublereal));
			do_fio(&c__1, (char *)&sound_1.gam1[i__ - 1], (ftnlen)
				sizeof(doublereal));
			do_fio(&c__1, (char *)&c_b191, (ftnlen)sizeof(real));
			do_fio(&c__1, (char *)&c_b191, (ftnlen)sizeof(real));
			do_fio(&c__1, (char *)&c_b191, (ftnlen)sizeof(real));
			do_fio(&c__1, (char *)&scrtch_1.sbeta[i__ - 1], (
				ftnlen)sizeof(doublereal));
			do_fio(&c__1, (char *)&scrtch_1.seta[i__ - 1], (
				ftnlen)sizeof(doublereal));
			for (k = 1; k <= 5; ++k) {
			    do_fio(&c__1, (char *)&scrtch_1.seg[k + i__ * 7 - 
				    8], (ftnlen)sizeof(doublereal));
			}
			do_fio(&c__1, (char *)&scrtch_1.sesum[i__ - 1], (
				ftnlen)sizeof(doublereal));
			do_fio(&c__1, (char *)&scrtch_1.seg[i__ * 7 - 2], (
				ftnlen)sizeof(doublereal));
			do_fio(&c__1, (char *)&scrtch_1.seg[i__ * 7 - 1], (
				ftnlen)sizeof(doublereal));
			do_fio(&c__1, (char *)&a, (ftnlen)sizeof(doublereal));
			do_fio(&c__1, (char *)&rpoleq, (ftnlen)sizeof(
				doublereal));
			do_fio(&c__1, (char *)&fp[i__], (ftnlen)sizeof(
				doublereal));
			do_fio(&c__1, (char *)&ft[i__], (ftnlen)sizeof(
				doublereal));
			do_fio(&c__1, (char *)&hjm[i__], (ftnlen)sizeof(
				doublereal));
			do_fio(&c__1, (char *)&hi[i__], (ftnlen)sizeof(
				doublereal));
			do_fio(&c__1, (char *)&roten_1.derot[i__ - 1], (
				ftnlen)sizeof(doublereal));
			do_fio(&c__1, (char *)&temp2_1.ves[i__ - 1], (ftnlen)
				sizeof(doublereal));
			do_fio(&c__1, (char *)&temp2_1.vgsf[i__ - 1], (ftnlen)
				sizeof(doublereal));
			do_fio(&c__1, (char *)&temp2_1.vss[i__ - 1], (ftnlen)
				sizeof(doublereal));
			do_fio(&c__1, (char *)&vtot, (ftnlen)sizeof(
				doublereal));
			e_wsfe();
		    } else {
			io___34.ciunit = luout_1.istor;
			s_wsfe(&io___34);
			do_fio(&c__1, (char *)&i__, (ftnlen)sizeof(integer));
			do_fio(&c__1, (char *)&hs[i__], (ftnlen)sizeof(
				doublereal));
			do_fio(&c__1, (char *)&hr[i__], (ftnlen)sizeof(
				doublereal));
			do_fio(&c__1, (char *)&hl[i__], (ftnlen)sizeof(
				doublereal));
			do_fio(&c__1, (char *)&hp[i__], (ftnlen)sizeof(
				doublereal));
			do_fio(&c__1, (char *)&ht[i__], (ftnlen)sizeof(
				doublereal));
			do_fio(&c__1, (char *)&hd[i__], (ftnlen)sizeof(
				doublereal));
			do_fio(&c__1, (char *)&omega[i__], (ftnlen)sizeof(
				doublereal));
			do_fio(&c__1, (char *)&lc[i__], (ftnlen)sizeof(
				logical));
			for (j = 1; j <= 15; ++j) {
			    do_fio(&c__1, (char *)&hcomp[j + i__ * 15], (
				    ftnlen)sizeof(doublereal));
			}
			do_fio(&c__1, (char *)&scrtch_1.so[i__ - 1], (ftnlen)
				sizeof(doublereal));
			do_fio(&c__1, (char *)&sg, (ftnlen)sizeof(doublereal))
				;
			do_fio(&c__1, (char *)&scrtch_1.sdel[i__ * 3 - 3], (
				ftnlen)sizeof(doublereal));
			do_fio(&c__1, (char *)&scrtch_1.sdel[i__ * 3 - 2], (
				ftnlen)sizeof(doublereal));
			do_fio(&c__1, (char *)&scrtch_1.sdel[i__ * 3 - 1], (
				ftnlen)sizeof(doublereal));
			do_fio(&c__1, (char *)&scrtch_1.svel[i__ - 1], (
				ftnlen)sizeof(doublereal));
			do_fio(&c__1, (char *)&sound_1.gam1[i__ - 1], (ftnlen)
				sizeof(doublereal));
			do_fio(&c__1, (char *)&c_b191, (ftnlen)sizeof(real));
			do_fio(&c__1, (char *)&c_b191, (ftnlen)sizeof(real));
			do_fio(&c__1, (char *)&c_b191, (ftnlen)sizeof(real));
			do_fio(&c__1, (char *)&scrtch_1.sbeta[i__ - 1], (
				ftnlen)sizeof(doublereal));
			do_fio(&c__1, (char *)&scrtch_1.seta[i__ - 1], (
				ftnlen)sizeof(doublereal));
			for (k = 1; k <= 5; ++k) {
			    do_fio(&c__1, (char *)&scrtch_1.seg[k + i__ * 7 - 
				    8], (ftnlen)sizeof(doublereal));
			}
			do_fio(&c__1, (char *)&scrtch_1.sesum[i__ - 1], (
				ftnlen)sizeof(doublereal));
			do_fio(&c__1, (char *)&scrtch_1.seg[i__ * 7 - 2], (
				ftnlen)sizeof(doublereal));
			do_fio(&c__1, (char *)&scrtch_1.seg[i__ * 7 - 1], (
				ftnlen)sizeof(doublereal));
			do_fio(&c__1, (char *)&c_b191, (ftnlen)sizeof(real));
			do_fio(&c__1, (char *)&c_b191, (ftnlen)sizeof(real));
			do_fio(&c__1, (char *)&c_b191, (ftnlen)sizeof(real));
			do_fio(&c__1, (char *)&c_b191, (ftnlen)sizeof(real));
			do_fio(&c__1, (char *)&c_b191, (ftnlen)sizeof(real));
			do_fio(&c__1, (char *)&c_b191, (ftnlen)sizeof(real));
			do_fio(&c__1, (char *)&c_b191, (ftnlen)sizeof(real));
			do_fio(&c__1, (char *)&c_b191, (ftnlen)sizeof(real));
			do_fio(&c__1, (char *)&c_b191, (ftnlen)sizeof(real));
			do_fio(&c__1, (char *)&c_b191, (ftnlen)sizeof(real));
			do_fio(&c__1, (char *)&c_b191, (ftnlen)sizeof(real));
			e_wsfe();
		    }
		} else {
		    if (ccout_1.lstrot && rot_1.lrot) {
			io___35.ciunit = luout_1.istor;
			s_wsfe(&io___35);
			do_fio(&c__1, (char *)&i__, (ftnlen)sizeof(integer));
			do_fio(&c__1, (char *)&hs[i__], (ftnlen)sizeof(
				doublereal));
			do_fio(&c__1, (char *)&hr[i__], (ftnlen)sizeof(
				doublereal));
			do_fio(&c__1, (char *)&hl[i__], (ftnlen)sizeof(
				doublereal));
			do_fio(&c__1, (char *)&hp[i__], (ftnlen)sizeof(
				doublereal));
			do_fio(&c__1, (char *)&ht[i__], (ftnlen)sizeof(
				doublereal));
			do_fio(&c__1, (char *)&hd[i__], (ftnlen)sizeof(
				doublereal));
			do_fio(&c__1, (char *)&omega[i__], (ftnlen)sizeof(
				doublereal));
			do_fio(&c__1, (char *)&lc[i__], (ftnlen)sizeof(
				logical));
			for (j = 1; j <= 15; ++j) {
			    do_fio(&c__1, (char *)&hcomp[j + i__ * 15], (
				    ftnlen)sizeof(doublereal));
			}
			do_fio(&c__1, (char *)&c_b191, (ftnlen)sizeof(real));
			do_fio(&c__1, (char *)&c_b191, (ftnlen)sizeof(real));
			do_fio(&c__1, (char *)&c_b191, (ftnlen)sizeof(real));
			do_fio(&c__1, (char *)&c_b191, (ftnlen)sizeof(real));
			do_fio(&c__1, (char *)&c_b191, (ftnlen)sizeof(real));
			do_fio(&c__1, (char *)&c_b191, (ftnlen)sizeof(real));
			do_fio(&c__1, (char *)&c_b191, (ftnlen)sizeof(real));
			do_fio(&c__1, (char *)&c_b191, (ftnlen)sizeof(real));
			do_fio(&c__1, (char *)&c_b191, (ftnlen)sizeof(real));
			do_fio(&c__1, (char *)&c_b191, (ftnlen)sizeof(real));
			do_fio(&c__1, (char *)&c_b191, (ftnlen)sizeof(real));
			do_fio(&c__1, (char *)&c_b191, (ftnlen)sizeof(real));
			do_fio(&c__1, (char *)&c_b191, (ftnlen)sizeof(real));
			do_fio(&c__1, (char *)&c_b191, (ftnlen)sizeof(real));
			do_fio(&c__1, (char *)&c_b191, (ftnlen)sizeof(real));
			do_fio(&c__1, (char *)&c_b191, (ftnlen)sizeof(real));
			do_fio(&c__1, (char *)&c_b191, (ftnlen)sizeof(real));
			do_fio(&c__1, (char *)&c_b191, (ftnlen)sizeof(real));
			do_fio(&c__1, (char *)&c_b191, (ftnlen)sizeof(real));
			do_fio(&c__1, (char *)&c_b191, (ftnlen)sizeof(real));
			do_fio(&c__1, (char *)&a, (ftnlen)sizeof(doublereal));
			do_fio(&c__1, (char *)&rpoleq, (ftnlen)sizeof(
				doublereal));
			do_fio(&c__1, (char *)&fp[i__], (ftnlen)sizeof(
				doublereal));
			do_fio(&c__1, (char *)&ft[i__], (ftnlen)sizeof(
				doublereal));
			do_fio(&c__1, (char *)&hjm[i__], (ftnlen)sizeof(
				doublereal));
			do_fio(&c__1, (char *)&hi[i__], (ftnlen)sizeof(
				doublereal));
			do_fio(&c__1, (char *)&roten_1.derot[i__ - 1], (
				ftnlen)sizeof(doublereal));
			do_fio(&c__1, (char *)&temp2_1.ves[i__ - 1], (ftnlen)
				sizeof(doublereal));
			do_fio(&c__1, (char *)&temp2_1.vgsf[i__ - 1], (ftnlen)
				sizeof(doublereal));
			do_fio(&c__1, (char *)&temp2_1.vss[i__ - 1], (ftnlen)
				sizeof(doublereal));
			do_fio(&c__1, (char *)&vtot, (ftnlen)sizeof(
				doublereal));
			e_wsfe();
		    } else {
			io___36.ciunit = luout_1.istor;
			s_wsfe(&io___36);
			do_fio(&c__1, (char *)&i__, (ftnlen)sizeof(integer));
			do_fio(&c__1, (char *)&hs[i__], (ftnlen)sizeof(
				doublereal));
			do_fio(&c__1, (char *)&hr[i__], (ftnlen)sizeof(
				doublereal));
			do_fio(&c__1, (char *)&hl[i__], (ftnlen)sizeof(
				doublereal));
			do_fio(&c__1, (char *)&hp[i__], (ftnlen)sizeof(
				doublereal));
			do_fio(&c__1, (char *)&ht[i__], (ftnlen)sizeof(
				doublereal));
			do_fio(&c__1, (char *)&hd[i__], (ftnlen)sizeof(
				doublereal));
			do_fio(&c__1, (char *)&omega[i__], (ftnlen)sizeof(
				doublereal));
			do_fio(&c__1, (char *)&lc[i__], (ftnlen)sizeof(
				logical));
			for (j = 1; j <= 15; ++j) {
			    do_fio(&c__1, (char *)&hcomp[j + i__ * 15], (
				    ftnlen)sizeof(doublereal));
			}
			do_fio(&c__1, (char *)&c_b191, (ftnlen)sizeof(real));
			do_fio(&c__1, (char *)&c_b191, (ftnlen)sizeof(real));
			do_fio(&c__1, (char *)&c_b191, (ftnlen)sizeof(real));
			do_fio(&c__1, (char *)&c_b191, (ftnlen)sizeof(real));
			do_fio(&c__1, (char *)&c_b191, (ftnlen)sizeof(real));
			do_fio(&c__1, (char *)&c_b191, (ftnlen)sizeof(real));
			do_fio(&c__1, (char *)&c_b191, (ftnlen)sizeof(real));
			do_fio(&c__1, (char *)&c_b191, (ftnlen)sizeof(real));
			do_fio(&c__1, (char *)&c_b191, (ftnlen)sizeof(real));
			do_fio(&c__1, (char *)&c_b191, (ftnlen)sizeof(real));
			do_fio(&c__1, (char *)&c_b191, (ftnlen)sizeof(real));
			do_fio(&c__1, (char *)&c_b191, (ftnlen)sizeof(real));
			do_fio(&c__1, (char *)&c_b191, (ftnlen)sizeof(real));
			do_fio(&c__1, (char *)&c_b191, (ftnlen)sizeof(real));
			do_fio(&c__1, (char *)&c_b191, (ftnlen)sizeof(real));
			do_fio(&c__1, (char *)&c_b191, (ftnlen)sizeof(real));
			do_fio(&c__1, (char *)&c_b191, (ftnlen)sizeof(real));
			do_fio(&c__1, (char *)&c_b191, (ftnlen)sizeof(real));
			do_fio(&c__1, (char *)&c_b191, (ftnlen)sizeof(real));
			do_fio(&c__1, (char *)&c_b191, (ftnlen)sizeof(real));
			do_fio(&c__1, (char *)&c_b191, (ftnlen)sizeof(real));
			do_fio(&c__1, (char *)&c_b191, (ftnlen)sizeof(real));
			do_fio(&c__1, (char *)&c_b191, (ftnlen)sizeof(real));
			do_fio(&c__1, (char *)&c_b191, (ftnlen)sizeof(real));
			do_fio(&c__1, (char *)&c_b191, (ftnlen)sizeof(real));
			do_fio(&c__1, (char *)&c_b191, (ftnlen)sizeof(real));
			do_fio(&c__1, (char *)&c_b191, (ftnlen)sizeof(real));
			do_fio(&c__1, (char *)&c_b191, (ftnlen)sizeof(real));
			do_fio(&c__1, (char *)&c_b191, (ftnlen)sizeof(real));
			do_fio(&c__1, (char *)&c_b191, (ftnlen)sizeof(real));
			do_fio(&c__1, (char *)&c_b191, (ftnlen)sizeof(real));
			e_wsfe();
		    }
		}
/* C write out the basic info */
/*            WRITE(ISTOR,62,ADVANCE='no') I,HS(I),HR(I),HL(I),HP(I), */
/*     *         HT(I),HD(I),OMEGA(I),LC(I),(HCOMP(J,I),J=1,15) */
/* C write out additional physics if desired */
/*            IF(LSTPHYS)THEN */
/*             SG = DEXP(CLN*(CGL - 2.0D0*HR(I)))*HS1(I) */
/*               WRITE(ISTOR,63,ADVANCE='no') SO(I),SG,SDEL(1,I),SDEL(2,I), */
/*     *           SDEL(3,I),SVEL(I),GAM1(I),0.0,0.0,0.0,SBETA(I),SETA(I), */
/*     *           (SEG(K,I),K=1,5),SESUM(I),SEG(6,I),SEG(7,I) */
/* c               WRITE(ISTOR,63,ADVANCE='no') SO(I),SG,SDEL(1,I),SDEL(2,I), */
/* c     *           SDEL(3,I),SVEL(I),GAM1(I),SFXION(1,I),SFXION(2,I),SFXION(3,I), */
/* c     *           SBETA(I),SETA(I),(SEG(K,I),K=1,5),SESUM(I),SEG(6,I),SEG(7,I) */
/*            ELSE */
/*               WRITE(ISTOR,63,ADVANCE='no') 0.0,0.0,0.0,0.0,0.0,0.0,0.0, */
/*     *           0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0 */
/*            ENDIF */
/* C write out additional rotation info if desired */
/*            IF(LSTROT.AND.LROT)THEN */
/*             FM = DEXP(CLN*HS(I)) */
/*             DUMA = CC13*OMEGA(I)**2/(CG*FM)*5.D0/(2.D0+ETA2(I)) */
/*             A = DUMA * R0(I)**3 */
/*             RPOLEQ = (1.0D0 - A)/(1.0D0 + 0.5D0*A) */
/*               VTOT = VES(I)+VGSF(I)+VSS(I) */
/*               WRITE(ISTOR,64) A,RPOLEQ,FP(I),FT(I),HJM(I),HI(I),DEROT(I), */
/*     *            VES(I),VGSF(I),VSS(I),VTOT */
/*            ELSE */
/*               WRITE(ISTOR,64) 0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0 */
/*            ENDIF */
	    }
/* 62   FORMAT(I6,0P2F18.14,1PE24.16,0P3F18.14,1PE24.16,1x,L1, */
/*     &     3(0PF12.9),12(0PE16.8),2X) */
/* 63   FORMAT(1PE10.4,1PE11.3,E12.4,E12.4,E12.4,1PE12.4,0PF9.5,F9.5,F9.5,F9.5, */
/* C     &     F9.5,F9.5,F9.5,F9.5,F9.5,F9.5,F9.5,E13.5,E13.5,E13.5) */
/*     &     F9.5,F9.5,E12.4,E12.4,E12.4,E12.4,E12.4,E13.5,E13.5,E13.5) */
/* 64   FORMAT(E14.6,E14.6,E14.6,E14.6,E14.6,E14.6,E14.6,E11.3,E11.3,E11.3,E11.3, */
/*     &     E11.3) */
/* LC 10/25: Compatibility */
	}
/* now call wrtmod, with the goal of outputting the envelope and atmosphere, or */
/* if required by LPULSE. */
	if (ccout_1.lstatm || ccout_1.lstenv) {
	    if (lmilne) {
		wrtmil_(&hcomp[16], &hd[1], &hl[1], &hp[1], &hr[1], &hs1[1], 
			m, model);
	    }
/*        CALL WRTMOD(M,LSHELL,JXBEG,JXEND,JCORE,JENV,HCOMP,HS1,HD,HL, */
/*      *   HP,HR,HT,LC,MODEL,BL,TEFFL,OMEGA,FP,FT,ETA2,R0,HJM,HI,HS, */
/*      *   DAGE)  ! KC 2025-05-31 */
	    wrtmod_(m, jenv, &hcomp[16], &hs1[1], &hd[1], &hl[1], &hp[1], &hr[
		    1], &ht[1], model, bl, teffl, &fp[1], &ft[1], &hs[1], 
		    dage);
	}
	io___38.ciunit = luout_1.istor;
	s_wsfe(&io___38);
	e_wsfe();
    }
/* G Somers END */
/* CCCCCCCCCCCCCCCCCCCCCCCC */
/* closes logic block for new vs old store file format */
    return 0;
} /* putstore_ */

