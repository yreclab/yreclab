/* setscal.f -- translated by f2c (version 20100827).
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
    integer ilast, idebug, itrack, ishort, imilne, imodpt, istor, iowr;
} luout_;

#define luout_1 luout_

struct {
    doublereal endage[50], setdt[50];
    logical lendag[50], lsetdt[50];
} sett_;

#define sett_1 sett_

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
    doublereal xls, xlstol, steff, sr, bli, alri, ager, blr, blrp, agei;
    logical lstar, lteff, lpassr, lcalst;
} calstar_;

#define calstar_1 calstar_

/* Table of constant values */

static doublereal c_b2 = .25;
static integer c__9 = 9;
static integer c__1 = 1;
static integer c__5 = 5;


/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */
/* SETSCAL */
/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */
/* Subroutine */ int setscal_(void)
{
    /* System generated locals */
    doublereal d__1;

    /* Builtin functions */
    double sqrt(doublereal), pow_dd(doublereal *, doublereal *);
    integer s_wsle(cilist *), do_lio(integer *, integer *, char *, ftnlen), 
	    e_wsle(void);

    /* Local variables */
    static integer i__, j;

    /* Fortran I/O blocks */
    static cilist io___3 = { 0, 6, 0, 0, 0 };
    static cilist io___4 = { 0, 0, 0, 0, 0 };


/*     LSTAR     T - have got a star at Teff and L */
/*     LPASSR    T - on run have just passed Teff */
/*     XLS       Luminosity (L/Lsun) wanted by adjusting Y */
/*     XLSTOL    tolerance wanted for luminosity */
/*     LTEFF     T - specify Teff for star */
/*               F - specify R/Rsun for star */
/*     STEFF     Effective temperature of star (K) or... */
/*     SR        Radius of star (R/Rsun) */
/*     TEFF      Teff of current model */
/*     ALR       log(R/Rsun) of current model */
/*     ALRI      log(R/Rsun) of previous model */
/*     DAGE      age of current model (Gyr) */
/*     AGEI      age of previous model (Gyr) */
/*     AGER      age of model at R* */
/*     BL        luminosity of current model */
/*     BLI       luminosity of previous model */
/*     BLR       luminosity of model at R */
/*     BLRP      luminosity of model at R* of previous run */
/*     XP        X of previous run = RESCAL(2, NK-1) */
/* mhp 10/02 linct not used, commented out */
/*      LINCT = .TRUE. */
    calstar_1.lstar = FALSE_;
    calstar_1.lpassr = FALSE_;
    if (calstar_1.lteff) {
	calstar_1.sr = sqrt(calstar_1.xls * const_1.clsun / (const1_1.c4pi * 
		const2_1.csig)) / (calstar_1.steff * calstar_1.steff * 
		const_1.crsun);
    } else {
	d__1 = calstar_1.xls * const_1.clsun / (const1_1.c4pi * const2_1.csig 
		* calstar_1.sr * calstar_1.sr * const_1.crsun * const_1.crsun)
		;
	calstar_1.steff = pow_dd(&d__1, &c_b2);
    }
    calstar_1.alri = 0.;
/*     SET UP RUN TO EVOLVE TO L, Teff IN HR-DIAGRM. */
/*     THIS CONSISTS OF SETTING THE NUMBER OF RUNS TO THE MAXIMUM (50), */
/*     AND COPYING THE RELEVANT PARAMETERS FROM THE FIRST TWO RUNS TO */
/*     THE NEXT SERIES OF 24 CALIBRATING RUNS. */
    ckind_1.numrun = 50;
    for (i__ = 2; i__ <= 50; ++i__) {
	newxym_1.xenv0a[i__ - 1] = newxym_1.xenv0a[0];
	newxym_1.zenv0a[i__ - 1] = newxym_1.zenv0a[0];
	newxym_1.cmixla[i__ - 1] = newxym_1.cmixla[0];
	newxym_1.lsenv0a[i__ - 1] = newxym_1.lsenv0a[0];
	newxym_1.senv0a[i__ - 1] = newxym_1.senv0a[0];
    }
    for (i__ = 3; i__ <= 49; i__ += 2) {
	ckind_1.iresca[i__ - 1] = ckind_1.iresca[0];
	ckind_1.lfirst[i__ - 1] = TRUE_;
	ckind_1.nmodls[i__ - 1] = ckind_1.nmodls[0];
	zramp_1.rsclzc[i__ - 1] = zramp_1.rsclzc[0];
	zramp_1.rsclzm1[i__ - 1] = zramp_1.rsclzm1[0];
	zramp_1.rsclzm2[i__ - 1] = zramp_1.rsclzm2[0];
	for (j = 1; j <= 4; ++j) {
	    ckind_1.rescal[j + (i__ << 2) - 5] = ckind_1.rescal[j - 1];
	}
    }
    for (i__ = 4; i__ <= 50; i__ += 2) {
	ckind_1.iresca[i__ - 1] = 1;
	ckind_1.lfirst[i__ - 1] = FALSE_;
	ckind_1.nmodls[i__ - 1] = ckind_1.nmodls[1];
	sett_1.endage[i__ - 1] = sett_1.endage[1];
	sett_1.lendag[i__ - 1] = sett_1.lendag[1];
	sett_1.setdt[i__ - 1] = sett_1.setdt[1];
	sett_1.lsetdt[i__ - 1] = sett_1.lsetdt[1];
    }
    s_wsle(&io___3);
    do_lio(&c__9, &c__1, " Evolve to R*, L* = ", (ftnlen)20);
    do_lio(&c__5, &c__1, (char *)&calstar_1.sr, (ftnlen)sizeof(doublereal));
    do_lio(&c__5, &c__1, (char *)&calstar_1.xls, (ftnlen)sizeof(doublereal));
    e_wsle();
    io___4.ciunit = luout_1.itrack;
    s_wsle(&io___4);
    do_lio(&c__9, &c__1, "#Evolve to R*, L* = ", (ftnlen)20);
    do_lio(&c__5, &c__1, (char *)&calstar_1.sr, (ftnlen)sizeof(doublereal));
    do_lio(&c__5, &c__1, (char *)&calstar_1.xls, (ftnlen)sizeof(doublereal));
    e_wsle();
    return 0;
} /* setscal_ */

