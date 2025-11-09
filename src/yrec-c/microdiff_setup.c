/* microdiff_setup.f -- translated by f2c (version 20061008).
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
    doublereal clsun, clsunl, clnsun, cmsun, cmsunl, crsun, crsunl, cmbol;
} const_;

#define const_1 const_

struct {
    doublereal cln, clni, c4pi, c4pil, c4pi3l, cc13, cc23, cpi;
} const1_;

#define const1_1 const1_

struct {
    doublereal cdelrl, cmixl, cmixl2, cmixl3, clndp, csecyr;
} const3_;

#define const3_1 const3_

struct {
    doublereal con_rad__, con_mass__, con_temp__, con_time__;
} confac_;

#define confac_1 confac_

struct {
    doublereal dt_gs__, xmin, ymin;
    logical lthoulfit;
} gravs2_;

#define gravs2_1 gravs2_

struct {
    doublereal sesum[5000], seg[35000]	/* was [7][5000] */, sbeta[5000], 
	    seta[5000];
    logical locons[5000];
    doublereal so[5000], sdel[15000]	/* was [3][5000] */, sfxion[15000]	
	    /* was [3][5000] */, svel[5000], scp[5000];
} scrtch_;

#define scrtch_1 scrtch_

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
    doublereal app[5000], atp[5000], apzp[5000], atzp[5000];
} gscof_;

#define gscof_1 gscof_

struct {
    doublereal cstmixing, cstdiffmix;
} cmixing_;

#define cmixing_1 cmixing_

/* Table of constant values */

static integer c__1 = 1;

/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */
/* MICRODIFF_SETUP */
/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */
/* Subroutine */ int microdiff_setup__(doublereal *dt, doublereal *hqpr, 
	doublereal *hr, doublereal *hd, doublereal *hs1, doublereal *ht, 
	logical *lc, integer *m, doublereal *stot, doublereal *hcomp, 
	doublereal *hru, doublereal *htu, integer *ibegin, integer *iend, 
	logical *lallcz, doublereal *oden, doublereal *otem)
{
    /* Format strings */
    static char fmt_15[] = "(1x,\002 FULLY CONVECTIVE MODEL - NO SETTLING"
	    "\002)";
    static char fmt_16[] = "(1x,\002X BELOW \002,f9.6,\002 IN WHOLE MODEL-NO"
	    " SETTLING\002)";
    static char fmt_17[] = "(1x,\002Y BELOW \002,f9.6,\002 IN WHOLE MODEL-NO"
	    " SETTLING\002)";

    /* System generated locals */
    integer i__1;
    doublereal d__1;

    /* Builtin functions */
    integer s_wsfe(cilist *), e_wsfe(void), do_fio(integer *, char *, ftnlen);
    double exp(doublereal);

    /* Local variables */
    static integer i__;
    static doublereal crsun_bah__, csecyr_bah__;

    /* Fortran I/O blocks */
    static cilist io___4 = { 0, 0, 0, fmt_15, 0 };
    static cilist io___5 = { 0, 0, 0, fmt_16, 0 };
    static cilist io___6 = { 0, 0, 0, fmt_17, 0 };


/* MHP 8/94 ADDED I/O FOR DIFFUSION */
/*      COMMON/GSCOF2/TAPP(JSON),TATP(JSON),TCLP(JSON),TAPZP(JSON), */
/*     *              TATZP(JSON) */
/* FD 10/09 ADDED COMMON BLOCK FOR EXTRA MIXING. IT MIMIC SOME MIXING BY AFFECTING */
/*        THE SETTLING COEFFICIENT DIRECTLY (in setup_grsett.f) */


/*     OUTPUT VARIABLES : */

/*     HRU - VECTOR OF UNLOGGED RADII IN BAHCALL AND LOEB UNITS. */
/*     HTU - VECTOR OF UNLOGGED TEMPERATURES IN BAHCALL AND LOEB UNITS. */
/*     IBEGIN - FIRST ZONE FOR DIFFUSION PURPOSES (EITHER THE FIRST MODEL POINT */
/*          OR THE OUTERMOST POINT OF A CENTRAL CONVECTION ZONE). */
/*     IEND - LAST ZONE FOR DIFFUSION PURPOSES (EITHER THE LAST MODEL POINT OR */
/*        THE INNERMOST POINT OF A SURFACE CONVECTION ZONE). */
/*     THE VECTORS HQPR AND HS1, AND THE SCALARS DT AND STOT, ARE ALSO CONVERTED */
/*     TO BAHCALL AND LOEB UNITS. */
/*     CONSTANTS DEFINED : */
/*     CLN = CONVERSION FACTOR FROM LN TO LOG10 */
/*     CRSUN = SOLAR RADIUS (CM) */
/*     CSECYR = NUMBER OF SECONDS IN A YEAR. */
    /* Parameter adjustments */
    --otem;
    --oden;
    --htu;
    --hru;
    hcomp -= 16;
    --lc;
    --ht;
    --hs1;
    --hd;
    --hr;
    --hqpr;

    /* Function Body */
    crsun_bah__ = 6.9598e10;
    csecyr_bah__ = 3.1558e7;
/*     LALLCZ=T FOR FULLY CONVECTIVE MODEL(AND IF TRUE, DIFFUSION IS SKIPPED). */
    *lallcz = FALSE_;
/*     CHECK FOR CONVECTIVE CORE. */
    if (lc[1]) {
	i__1 = *m;
	for (i__ = 2; i__ <= i__1; ++i__) {
	    if (! lc[i__]) {
		goto L20;
	    }
/* L10: */
	}
/*        DIFFUSION NOT COMPUTED FOR FULLY CONVECTIVE MODELS. */
	*lallcz = TRUE_;
	io___4.ciunit = luout_1.ishort;
	s_wsfe(&io___4);
	e_wsfe();
	goto L9999;
L20:
/*        COMPUTE OVERSHOOT (TO BE ADDED). */
	*ibegin = i__ - 1;
    } else {
	*ibegin = 1;
    }
/* MHP 6/90 CHECK FOR HYDROGEN-EXHAUSTED CORE. */
    i__1 = *m;
    for (i__ = *ibegin; i__ <= i__1; ++i__) {
	if (hcomp[i__ * 15 + 1] > gravs2_1.xmin) {
	    goto L25;
	}
/* L23: */
    }
/*     HYDROGEN-FREE MODEL - EXIT. */
    io___5.ciunit = luout_1.ishort;
    s_wsfe(&io___5);
    do_fio(&c__1, (char *)&gravs2_1.xmin, (ftnlen)sizeof(doublereal));
    e_wsfe();
    *lallcz = TRUE_;
    goto L9999;
L25:
    *ibegin = i__;
/*     CHECK FOR CONVECTIVE ENVELOPE. */
    if (lc[*m]) {
	for (i__ = *m - 1; i__ >= 2; --i__) {
	    if (! lc[i__]) {
		goto L40;
	    }
/* L30: */
	}
L40:
/*        COMPUTE OVERSHOOT (TO BE ADDED). */
	*iend = i__ + 1;
    } else {
	*iend = *m;
    }
/*     CHECK FOR HELIUM-EXHAUSTED SURFACE. */
/*     OUTER POINT IS SET WHEREVER Y>YMIN. */
    for (i__ = *iend; i__ >= 1; --i__) {
	if (hcomp[i__ * 15 + 2] > gravs2_1.ymin) {
	    goto L47;
	}
/* L45: */
    }
/*     HYDROGEN-FREE MODEL - EXIT. */
    io___6.ciunit = luout_1.ishort;
    s_wsfe(&io___6);
    do_fio(&c__1, (char *)&gravs2_1.ymin, (ftnlen)sizeof(doublereal));
    e_wsfe();
    *lallcz = TRUE_;
    goto L9999;
L47:
    *iend = i__;
/*     CON_MASS=CONVERSION FACTOR FOR MASS. */
/*     CON_RADIUS=CONVERSION FACTOR FOR RADIUS. */
/*     CON_TEMP=CONVERSION FACOTR FOR TEMPERATURE. */
/*     CON_TIME=CONVERSION FACTOR FOR TIME. */
    confac_1.con_rad__ = 1. / crsun_bah__;
/* Computing 3rd power */
    d__1 = confac_1.con_rad__;
    confac_1.con_mass__ = d__1 * (d__1 * d__1) * .01;
    confac_1.con_temp__ = 1e-7;
/*     INCLUDES FACTOR OF 2.2 FROM LN LAMBDA */
    confac_1.con_time__ = csecyr_bah__ * 2.7e13;
/*     CONVERT LOG(RADIUS) AND LOG(TEMPERATURE) TO NATURAL UNITS. */
/*     ALSO CONVERT NATURAL UNITS TO BAHCALL AND LOEB UNITS. */
    i__1 = *m;
    for (i__ = 1; i__ <= i__1; ++i__) {
	hru[i__] = exp(const1_1.cln * hr[i__]) * confac_1.con_rad__;
	htu[i__] = exp(const1_1.cln * ht[i__]) * confac_1.con_temp__;
	hs1[i__] *= confac_1.con_mass__;
	hqpr[i__] /= confac_1.con_rad__;
/*        SDEL(2,I)=0.4D0   !COMMENT OUT IN REAL CODE */
/* L50: */
    }
    *dt /= confac_1.con_time__;
    *stot *= confac_1.con_mass__;

/* COLLECT THE NECESSARY QUANTITIES (NAMELY RHO AND T) FOR LATER */
/* TRANSFORMATION TO THE EQUALLY SPACED GRID. */
    i__1 = *m;
    for (i__ = 1; i__ <= i__1; ++i__) {
	oden[i__] = exp(const1_1.cln * hd[i__]);
	otem[i__] = exp(const1_1.cln * ht[i__]);
    }
L9999:
    return 0;
} /* microdiff_setup__ */

