/* getalex06.f -- translated by f2c (version 20061008).
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
    doublereal tgr06[85], xxg06[9], r0gr06[19], zzg06[16];
} galot06_;

#define galot06_1 galot06_

struct {
    doublereal capalex06[1615]	/* was [85][19] */, xe, ze;
    integer ix, it, id;
} alot06_;

#define alot06_1 alot06_

/* MHP 3/09 SUBROUTINE FOR CALCULATING ALEXANDER LOW T OPACITIES */
/* Subroutine */ int getalex06_(doublereal *dl, doublereal *tl, doublereal *x,
	 doublereal *z__, doublereal *o, doublereal *ol, doublereal *qod, 
	doublereal *qot)
{
    /* System generated locals */
    doublereal d__1;

    /* Builtin functions */
    double exp(doublereal);

    /* Local variables */
    extern /* Subroutine */ int alex06tab_(void);
    static integer i__;
    static doublereal r__;
    static integer ii;
    static doublereal op[4], qr[4], rr, fxr[4], fxt[4], difx, difz, fxrd[4], 
	    fxtd[4], qopr[4];
    static logical linear;
    extern /* Subroutine */ int interp_(doublereal *, doublereal *, 
	    doublereal *, doublereal *);

    difz = (d__1 = *z__ - alot06_1.ze, abs(d__1));
    difx = (d__1 = *x - alot06_1.xe, abs(d__1));
/*  ENSURE THAT OPACITY TABLE HAS THE SAME X,Z VALUE AS THE POINT */
    if (difz > 1e-8 || difx > 1e-8) {
	alot06_1.ze = *z__;
	alot06_1.xe = *x;
	alex06tab_();
    }
/*  COMPUTE R FOR GRID POINT */
    r__ = *dl - (*tl - 6.) * 3.;
/* Insure that index IT is within the required array bounds */
    if (alot06_1.it < 1) {
	alot06_1.it = 1;
    }
    if (alot06_1.it + 2 > 85) {
	alot06_1.it = 83;
    }
/*  FIND NEAREST GRID POINTS IN T. */
    if (*tl < galot06_1.tgr06[alot06_1.it + 1]) {
	for (i__ = alot06_1.it + 1; i__ >= 2; --i__) {
	    if (*tl > galot06_1.tgr06[i__ - 1]) {
		alot06_1.it = i__ - 1;
		goto L10;
	    }
	}
	alot06_1.it = 1;
L10:
	;
    } else {
	for (i__ = alot06_1.it + 3; i__ <= 85; ++i__) {
	    if (*tl < galot06_1.tgr06[i__ - 1]) {
		alot06_1.it = i__ - 2;
		alot06_1.it = min(82,alot06_1.it);
		goto L20;
	    }
	}
	alot06_1.it = 82;
L20:
	;
    }
/* INTERPOLATION FACTORS IN LOG T */
    for (i__ = 1; i__ <= 4; ++i__) {
	qr[i__ - 1] = galot06_1.tgr06[alot06_1.it + i__ - 2];
    }
    interp_(qr, fxt, fxtd, tl);
/* Insure that index ID is within the required array bounds */
    if (alot06_1.id < 1) {
	alot06_1.id = 1;
    }
    if (alot06_1.id + 2 > 19) {
	alot06_1.id = 17;
    }
/*  FIND NEAREST GRID POINTS IN R = RHO/T6**3 */
    if (r__ < galot06_1.r0gr06[alot06_1.id + 1]) {
	for (i__ = alot06_1.id + 1; i__ >= 2; --i__) {
	    if (r__ > galot06_1.r0gr06[i__ - 1]) {
		alot06_1.id = i__ - 1;
		goto L30;
	    }
	}
	alot06_1.id = 1;
L30:
	;
    } else {
	for (i__ = alot06_1.id + 3; i__ <= 19; ++i__) {
	    if (r__ < galot06_1.r0gr06[i__ - 1]) {
		alot06_1.id = i__ - 2;
		alot06_1.id = min(16,alot06_1.id);
		goto L40;
	    }
	}
	alot06_1.id = 16;
L40:
	;
    }
/*  INTERPOLATION FACTORS IN LOG R */
    if (r__ > galot06_1.r0gr06[18]) {
	linear = TRUE_;
	rr = r__;
	r__ = galot06_1.r0gr06[18];
    } else {
	linear = FALSE_;
    }
    for (i__ = 1; i__ <= 4; ++i__) {
	qr[i__ - 1] = galot06_1.r0gr06[alot06_1.id + i__ - 2];
    }
    interp_(qr, fxr, fxrd, &r__);
/* INTERPOLATE IN LOG R AT FIXED T */
    for (i__ = 1; i__ <= 4; ++i__) {
	ii = alot06_1.it + i__ - 1;
	op[i__ - 1] = fxr[0] * alot06_1.capalex06[ii + alot06_1.id * 85 - 86] 
		+ fxr[1] * alot06_1.capalex06[ii + (alot06_1.id + 1) * 85 - 
		86] + fxr[2] * alot06_1.capalex06[ii + (alot06_1.id + 2) * 85 
		- 86] + fxr[3] * alot06_1.capalex06[ii + (alot06_1.id + 3) * 
		85 - 86];
	qopr[i__ - 1] = fxrd[0] * alot06_1.capalex06[ii + alot06_1.id * 85 - 
		86] + fxrd[1] * alot06_1.capalex06[ii + (alot06_1.id + 1) * 
		85 - 86] + fxrd[2] * alot06_1.capalex06[ii + (alot06_1.id + 2)
		 * 85 - 86] + fxrd[3] * alot06_1.capalex06[ii + (alot06_1.id 
		+ 3) * 85 - 86];
    }
    if (linear) {
	for (i__ = 1; i__ <= 4; ++i__) {
	    ii = alot06_1.it + i__ - 1;
	    op[i__ - 1] += (rr - r__) * (alot06_1.capalex06[ii + 1529] - 
		    alot06_1.capalex06[ii + 1444]) / (galot06_1.r0gr06[18] - 
		    galot06_1.r0gr06[17]);
	}
	r__ = rr;
    }
/*  INTERPOLATE IN T */
    *ol = fxt[0] * op[0] + fxt[1] * op[1] + fxt[2] * op[2] + fxt[3] * op[3];
/* D LN CAPPA/D LN T AT FIXED R */
    *qot = fxtd[0] * op[0] + fxtd[1] * op[1] + fxtd[2] * op[2] + fxtd[3] * op[
	    3];
/* INTERPOLATE IN D LN CAPPA/ D LN R AT FIXED T */
    *qod = fxt[0] * qopr[0] + fxt[1] * qopr[1] + fxt[2] * qopr[2] + fxt[3] * 
	    qopr[3];
/* CORRECT FROM DERIVATIVE AT FIXED R TO DERIVATIVE AT FIXED RHO */
    *qot -= *qod * 3.;
    *o = exp(const1_1.cln * *ol);
    return 0;
} /* getalex06_ */

