/* yalo3d.f -- translated by f2c (version 20061008).
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
    doublereal zlaol1, zlaol2, zopal1, zopal2, zopal951, zalex1, zkur1, zkur2,
	     tmolmin, tmolmax;
    logical lalex06, llaol89, lopal92, lopal95, lkur90, lalex95, l2z;
} newopac_;

#define newopac_1 newopac_

struct {
    doublereal tgr[23], xxg[7], r0gr[17], zzg[15];
} galot_;

#define galot_1 galot_

struct {
    doublereal capalex[3128]	/* was [8][23][17] */, xe, ze;
    integer ix, it, id;
} alot_;

#define alot_1 alot_

/* MHP 4/98 SUBROUTINE FOR CALCULATING ALEXANDER LOW T OPACITIES */
/* Subroutine */ int yalo3d_(doublereal *dl, doublereal *tl, doublereal *x, 
	doublereal *z__, doublereal *o, doublereal *ol, doublereal *qod, 
	doublereal *qot)
{
    /* System generated locals */
    doublereal d__1;

    /* Builtin functions */
    double exp(doublereal);

    /* Local variables */
    static integer i__, j;
    static doublereal r__;
    static integer ii, jj;
    static doublereal op[4], qr[4], rr, ox[4], fxr[4], fxt[4], fxx[4], difz, 
	    fxrd[4], fxtd[4], qodx[4], qopr[4], qotx[4];
    extern /* Subroutine */ int alx8th_(doublereal *), intrp2_(doublereal *, 
	    doublereal *, doublereal *);
    static logical linear;
    extern /* Subroutine */ int interp_(doublereal *, doublereal *, 
	    doublereal *, doublereal *), alxztab_(doublereal *);

/* OPACITY COMMON BLOCKS - modified 3/09 */
    difz = (d__1 = *z__ - alot_1.ze, abs(d__1));
/*  ENSURE THAT OPACITY TABLE HAS THE SAME Z VALUE AS THE ENVELOPE. */
    if (difz > 1e-8) {
	alxztab_(z__);
	alx8th_(x);
    }
/*  COMPUTE R FOR GRID POINT */
    r__ = *dl - (*tl - 6.) * 3.;
/*  FIND NEAREST GRID POINTS IN T. */
/* Insure that index IT is within the required array bounds  llp  8/19/08 */
    if (alot_1.it < 1) {
	alot_1.it = 1;
    }
    if (alot_1.it + 2 > 23) {
	alot_1.it = 21;
    }
    if (*tl < galot_1.tgr[alot_1.it + 1]) {
	for (i__ = alot_1.it + 1; i__ >= 2; --i__) {
	    if (*tl > galot_1.tgr[i__ - 1]) {
		alot_1.it = i__ - 1;
		goto L10;
	    }
	}
	alot_1.it = 1;
L10:
	;
    } else {
	for (i__ = alot_1.it + 3; i__ <= 23; ++i__) {
	    if (*tl < galot_1.tgr[i__ - 1]) {
		alot_1.it = i__ - 2;
		alot_1.it = min(20,alot_1.it);
		goto L20;
	    }
	}
	alot_1.it = 20;
L20:
	;
    }
/* INTERPOLATION FACTORS IN LOG T */
    for (i__ = 1; i__ <= 4; ++i__) {
	qr[i__ - 1] = galot_1.tgr[alot_1.it + i__ - 2];
    }
    interp_(qr, fxt, fxtd, tl);
/*  FIND NEAREST GRID POINTS IN R = RHO/T6**3 */
    if (r__ < galot_1.r0gr[alot_1.id + 1]) {
	for (i__ = alot_1.id + 1; i__ >= 2; --i__) {
	    if (r__ > galot_1.r0gr[i__ - 1]) {
		alot_1.id = i__ - 1;
		goto L30;
	    }
	}
	alot_1.id = 1;
L30:
	;
    } else {
	for (i__ = alot_1.id + 3; i__ <= 17; ++i__) {
	    if (r__ < galot_1.r0gr[i__ - 1]) {
		alot_1.id = i__ - 2;
		alot_1.id = min(14,alot_1.id);
		goto L40;
	    }
	}
	alot_1.id = 14;
L40:
	;
    }
/*  INTERPOLATION FACTORS IN LOG R */
    if (r__ > galot_1.r0gr[16] && (d__1 = *x - alot_1.xe, abs(d__1)) < 1e-8) {
	linear = TRUE_;
	rr = r__;
	r__ = galot_1.r0gr[16];
    } else {
	linear = FALSE_;
    }
    for (i__ = 1; i__ <= 4; ++i__) {
	qr[i__ - 1] = galot_1.r0gr[alot_1.id + i__ - 2];
    }
    interp_(qr, fxr, fxrd, &r__);
/* NOW EITHER INTERPOLATE IN SURFACE X TABLE OR CALCULATE OPACITY AT */
/* 4 DIFFERENT VALUES OF X AND INTERPOLATE IN X. */
    if ((d__1 = *x - alot_1.xe, abs(d__1)) < 1e-8) {
/* SURFACE ABUNDANCE TABLE */
/* INTERPOLATE IN LOG R AT FIXED T */
	for (i__ = 1; i__ <= 4; ++i__) {
	    ii = alot_1.it + i__ - 1;
	    op[i__ - 1] = fxr[0] * alot_1.capalex[(ii + alot_1.id * 23 << 3) 
		    - 185] + fxr[1] * alot_1.capalex[(ii + (alot_1.id + 1) * 
		    23 << 3) - 185] + fxr[2] * alot_1.capalex[(ii + (
		    alot_1.id + 2) * 23 << 3) - 185] + fxr[3] * 
		    alot_1.capalex[(ii + (alot_1.id + 3) * 23 << 3) - 185];
	    qopr[i__ - 1] = fxrd[0] * alot_1.capalex[(ii + alot_1.id * 23 << 
		    3) - 185] + fxrd[1] * alot_1.capalex[(ii + (alot_1.id + 1)
		     * 23 << 3) - 185] + fxrd[2] * alot_1.capalex[(ii + (
		    alot_1.id + 2) * 23 << 3) - 185] + fxrd[3] * 
		    alot_1.capalex[(ii + (alot_1.id + 3) * 23 << 3) - 185];
	}
	if (linear) {
	    for (i__ = 1; i__ <= 4; ++i__) {
		ii = alot_1.it + i__ - 1;
		op[i__ - 1] += (rr - r__) * (alot_1.capalex[(ii + 391 << 3) - 
			185] - alot_1.capalex[(ii + 368 << 3) - 185]) / (
			galot_1.r0gr[16] - galot_1.r0gr[15]);
	    }
	    r__ = rr;
	}
/*  INTERPOLATE IN T */
	*ol = fxt[0] * op[0] + fxt[1] * op[1] + fxt[2] * op[2] + fxt[3] * op[
		3];
/* D LN CAPPA/D LN T AT FIXED R */
	*qot = fxtd[0] * op[0] + fxtd[1] * op[1] + fxtd[2] * op[2] + fxtd[3] *
		 op[3];
/* INTERPOLATE IN D LN CAPPA/ D LN R AT FIXED T */
	*qod = fxt[0] * qopr[0] + fxt[1] * qopr[1] + fxt[2] * qopr[2] + fxt[3]
		 * qopr[3];
/* CORRECT FROM DERIVATIVE AT FIXED R TO DERIVATIVE AT FIXED RHO */
	*qot -= *qod * 3.;
	*o = exp(const1_1.cln * *ol);
    } else {
/* FIND 4 NEAREST TABLES IN X. */
	if (*x < galot_1.xxg[3]) {
	    if (*x > galot_1.xxg[2]) {
		alot_1.ix = 2;
	    } else {
		alot_1.ix = 1;
	    }
	} else {
	    if (*x > galot_1.xxg[4]) {
		alot_1.ix = 4;
	    } else {
		alot_1.ix = 3;
	    }
	}
	for (i__ = 1; i__ <= 4; ++i__) {
	    qr[i__ - 1] = galot_1.xxg[alot_1.ix + i__ - 2];
	}
	intrp2_(qr, fxx, x);
/* INTERPOLATE IN LOG R AT FIXED T */
	for (j = 1; j <= 4; ++j) {
	    jj = alot_1.ix + j - 1;
	    for (i__ = 1; i__ <= 4; ++i__) {
		ii = alot_1.it + i__ - 1;
		op[i__ - 1] = fxr[0] * alot_1.capalex[jj + (ii + alot_1.id * 
			23 << 3) - 193] + fxr[1] * alot_1.capalex[jj + (ii + (
			alot_1.id + 1) * 23 << 3) - 193] + fxr[2] * 
			alot_1.capalex[jj + (ii + (alot_1.id + 2) * 23 << 3) 
			- 193] + fxr[3] * alot_1.capalex[jj + (ii + (
			alot_1.id + 3) * 23 << 3) - 193];
		qopr[i__ - 1] = fxrd[0] * alot_1.capalex[jj + (ii + alot_1.id 
			* 23 << 3) - 193] + fxrd[1] * alot_1.capalex[jj + (ii 
			+ (alot_1.id + 1) * 23 << 3) - 193] + fxrd[2] * 
			alot_1.capalex[jj + (ii + (alot_1.id + 2) * 23 << 3) 
			- 193] + fxrd[3] * alot_1.capalex[jj + (ii + (
			alot_1.id + 3) * 23 << 3) - 193];
	    }
/*  INTERPOLATE IN T */
	    ox[j - 1] = fxt[0] * op[0] + fxt[1] * op[1] + fxt[2] * op[2] + 
		    fxt[3] * op[3];
/* D LN CAPPA/D LN T AT FIXED R */
	    qotx[j - 1] = fxtd[0] * op[0] + fxtd[1] * op[1] + fxtd[2] * op[2] 
		    + fxtd[3] * op[3];
/* INTERPOLATE IN D LN CAPPA/ D LN R AT FIXED T */
	    qodx[j - 1] = fxt[0] * qopr[0] + fxt[1] * qopr[1] + fxt[2] * qopr[
		    2] + fxt[3] * qopr[3];
	}
/* INTERPOLATE IN X */
	*ol = fxx[0] * ox[0] + fxx[1] * ox[1] + fxx[2] * ox[2] + fxx[3] * ox[
		3];
	*qot = fxx[0] * qotx[0] + fxx[1] * qotx[1] + fxx[2] * qotx[2] + fxx[3]
		 * qotx[3];
	*qod = fxx[0] * qodx[0] + fxx[1] * qodx[1] + fxx[2] * qodx[2] + fxx[3]
		 * qodx[3];
/* CORRECT FROM DERIVATIVE AT FIXED R TO DERIVATIVE AT FIXED RHO */
	*qot -= *qod * 3.;
	*o = exp(const1_1.cln * *ol);
    }
    return 0;
} /* yalo3d_ */

