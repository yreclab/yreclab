/* chkscal.f -- translated by f2c (version 20061008).
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
    doublereal rescal[200]	/* was [4][50] */;
    integer nmodls[50], iresca[50];
    logical lfirst[50];
    integer numrun;
} ckind_;

#define ckind_1 ckind_

struct {
    doublereal endage[50], setdt[50];
    logical lendag[50], lsetdt[50];
    doublereal end_dcen__[50], end_xcen__[50], end_ycen__[50];
} sett_;

#define sett_1 sett_

struct {
    doublereal xenv0a[50], zenv0a[50], cmixla[50];
    logical lsenv0a[50];
    doublereal senv0a[50];
} newxym_;

#define newxym_1 newxym_

struct {
    doublereal xls, xlstol, steff, sr, bli, alri, ager, blr, blrp, agei;
    logical lstar, lteff, lpassr, lcalst;
} calstar_;

#define calstar_1 calstar_

struct {
    integer ilast, idebug, itrack, ishort, imilne, imodpt, istor, iowr;
} luout_;

#define luout_1 luout_

/* Table of constant values */

static doublereal c_b2 = 10.;
static integer c__9 = 9;
static integer c__1 = 1;
static integer c__5 = 5;
static integer c__3 = 3;



/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */
/* CHKSCAL */
/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */
/* Subroutine */ int chkscal_(doublereal *bl, doublereal *teffl, doublereal *
	dage, integer *nk)
{
    /* System generated locals */
    doublereal d__1;

    /* Builtin functions */
    double pow_dd(doublereal *, doublereal *), sqrt(doublereal);
    integer s_wsle(cilist *), do_lio(integer *, integer *, char *, ftnlen), 
	    e_wsle(void);
    double d_lg10(doublereal *);

    /* Local variables */
    static doublereal x, xp, alr, dadr, teff, dldr, dxdl;

    /* Fortran I/O blocks */
    static cilist io___3 = { 0, 6, 0, 0, 0 };
    static cilist io___4 = { 0, 0, 0, 0, 0 };
    static cilist io___7 = { 0, 6, 0, 0, 0 };
    static cilist io___8 = { 0, 0, 0, 0, 0 };
    static cilist io___9 = { 0, 6, 0, 0, 0 };
    static cilist io___10 = { 0, 0, 0, 0, 0 };
    static cilist io___13 = { 0, 6, 0, 0, 0 };
    static cilist io___14 = { 0, 0, 0, 0, 0 };
    static cilist io___16 = { 0, 6, 0, 0, 0 };
    static cilist io___17 = { 0, 0, 0, 0, 0 };


/*     ONLY CALLED FOR EVEN NK, ASSUMES RESCALING ON ODD NK AND EVOLVING */
/*     ON EVEN NK */
/* MHP 10/24 ADDED STOP CRITERIA FOR CENTRAL H,D,AND HE4 */
/*      COMMON/SETT/ENDAGE(50),SETDT(50),LENDAG(50),LSETDT(50) */
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
/*     BL        luminosity of current model log(L/Lsun) */
/*     BLI       luminosity of previous model */
/*     BLR       luminosity of model at R */
/*     BLRP      luminosity of model at R* of previous run */
/*     XP        X of previous run = RESCAL(2, NK-1) */

/*     Check if star has passed R*. */
/*     If not store L and age and return. */
    calstar_1.lpassr = FALSE_;
    teff = pow_dd(&c_b2, teffl);
    alr = sqrt(pow_dd(&c_b2, bl) * const_1.clsun / (const1_1.c4pi * 
	    const2_1.csig)) / (teff * teff * const_1.crsun);
    if (alr > calstar_1.alri) {
	if (! (alr > calstar_1.sr && calstar_1.alri <= calstar_1.sr)) {
	    calstar_1.bli = *bl;
	    calstar_1.agei = *dage;
	    calstar_1.alri = alr;
	    return 0;
	}
    } else {
	if (! (alr < calstar_1.sr && calstar_1.alri >= calstar_1.sr)) {
	    calstar_1.bli = *bl;
	    calstar_1.agei = *dage;
	    calstar_1.alri = alr;
	    return 0;
	}
    }

/*     Check if track has passed through Teff the right number of */
/*     times. If not store L and age and return. */
/* ZZZ */
    s_wsle(&io___3);
    do_lio(&c__9, &c__1, " Just passed R*", (ftnlen)15);
    e_wsle();
    io___4.ciunit = luout_1.itrack;
    s_wsle(&io___4);
    do_lio(&c__9, &c__1, "#Just passed R*", (ftnlen)15);
    e_wsle();
    calstar_1.lpassr = TRUE_;

/*     Have previous L,Age and current L,Age (one before R* and */
/*     one after R*).  Interpolate to get L,Age at R* */
    dldr = (*bl - calstar_1.bli) / (alr - calstar_1.alri);
    calstar_1.blr = *bl + dldr * (calstar_1.sr - alr);
    dadr = (*dage - calstar_1.agei) / (alr - calstar_1.alri);
    calstar_1.ager = *dage + dadr * (calstar_1.sr - alr);
    s_wsle(&io___7);
    do_lio(&c__9, &c__1, " X, LogL/Lsun at R* =", (ftnlen)21);
    do_lio(&c__5, &c__1, (char *)&ckind_1.rescal[(*nk - 1 << 2) - 3], (ftnlen)
	    sizeof(doublereal));
    do_lio(&c__5, &c__1, (char *)&calstar_1.blr, (ftnlen)sizeof(doublereal));
    e_wsle();
    io___8.ciunit = luout_1.itrack;
    s_wsle(&io___8);
    do_lio(&c__9, &c__1, "#X, LogL/Lsun at R* =", (ftnlen)21);
    do_lio(&c__5, &c__1, (char *)&ckind_1.rescal[(*nk - 1 << 2) - 3], (ftnlen)
	    sizeof(doublereal));
    do_lio(&c__5, &c__1, (char *)&calstar_1.blr, (ftnlen)sizeof(doublereal));
    e_wsle();
    if ((d__1 = pow_dd(&c_b2, &calstar_1.blr) - calstar_1.xls, abs(d__1)) <= 
	    calstar_1.xlstol) {
/*        Get here then have track that passes through specified */
/*        L and R. Use age at R for final */
/*        run to stop at that age. Do one more run */
/*        stopping at interpolated age. */
	calstar_1.lstar = TRUE_;
	sett_1.lendag[*nk] = TRUE_;
	sett_1.endage[*nk] = calstar_1.ager * 1e9;
	sett_1.lendag[*nk + 1] = TRUE_;
	sett_1.endage[*nk + 1] = calstar_1.ager * 1e9;
	ckind_1.rescal[(*nk + 1 << 2) - 3] = ckind_1.rescal[(*nk - 1 << 2) - 
		3];
	newxym_1.xenv0a[*nk] = ckind_1.rescal[(*nk + 1 << 2) - 3];
	newxym_1.xenv0a[*nk + 1] = newxym_1.xenv0a[*nk];

	s_wsle(&io___9);
	do_lio(&c__9, &c__1, " Have hit R* & L*, prepare final run to age:", (
		ftnlen)44);
	do_lio(&c__5, &c__1, (char *)&calstar_1.ager, (ftnlen)sizeof(
		doublereal));
	e_wsle();
	io___10.ciunit = luout_1.itrack;
	s_wsle(&io___10);
	do_lio(&c__9, &c__1, "#Have hit R* & L*, prepare final run to age:", (
		ftnlen)44);
	do_lio(&c__5, &c__1, (char *)&calstar_1.ager, (ftnlen)sizeof(
		doublereal));
	e_wsle();
	return 0;
    } else {
	if (*nk == 2) {
/*           First time through. Save L and X at R*. */
/*           Add 0.01 to Y. Start next run. */
	    calstar_1.blrp = calstar_1.blr;
	    xp = ckind_1.rescal[(*nk - 1 << 2) - 3];
	    x = xp - .01;
	    ckind_1.rescal[(*nk + 1 << 2) - 3] = x;
	    newxym_1.xenv0a[*nk] = x;
	    newxym_1.xenv0a[*nk + 1] = x;

	    s_wsle(&io___13);
	    do_lio(&c__9, &c__1, " NK=2, Y=Y+0.01, Setup next run, X=", (
		    ftnlen)35);
	    do_lio(&c__5, &c__1, (char *)&x, (ftnlen)sizeof(doublereal));
	    e_wsle();
	    io___14.ciunit = luout_1.itrack;
	    s_wsle(&io___14);
	    do_lio(&c__9, &c__1, "#NK=2, Y=Y+0.01, Setup next run, X=", (
		    ftnlen)35);
	    do_lio(&c__5, &c__1, (char *)&x, (ftnlen)sizeof(doublereal));
	    e_wsle();
	    return 0;
	} else {
/*           If NK=4,6,8,... (second and more times through) then */
/*           Use current and previous values of L at R and X to calculate */
/*           dX/dlogL. Save L.  Start next run. */
	    x = ckind_1.rescal[(*nk - 1 << 2) - 3];
	    xp = ckind_1.rescal[(*nk - 3 << 2) - 3];
	    dxdl = (x - xp) / (calstar_1.blr - calstar_1.blrp);
	    x = dxdl * (d_lg10(&calstar_1.xls) - calstar_1.blr) + x;

	    s_wsle(&io___16);
	    do_lio(&c__9, &c__1, " Setup next run, NK, X =", (ftnlen)24);
	    do_lio(&c__3, &c__1, (char *)&(*nk), (ftnlen)sizeof(integer));
	    do_lio(&c__5, &c__1, (char *)&x, (ftnlen)sizeof(doublereal));
	    e_wsle();
	    io___17.ciunit = luout_1.itrack;
	    s_wsle(&io___17);
	    do_lio(&c__9, &c__1, " Setup next run, NK, X =", (ftnlen)24);
	    do_lio(&c__3, &c__1, (char *)&(*nk), (ftnlen)sizeof(integer));
	    do_lio(&c__5, &c__1, (char *)&x, (ftnlen)sizeof(doublereal));
	    e_wsle();
	    calstar_1.blrp = calstar_1.blr;
	    ckind_1.rescal[(*nk + 1 << 2) - 3] = x;
	    newxym_1.xenv0a[*nk] = x;
	    newxym_1.xenv0a[*nk + 1] = x;
	}
    }
    return 0;
} /* chkscal_ */

