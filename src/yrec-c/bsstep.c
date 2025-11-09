/* bsstep.f -- translated by f2c (version 20061008).
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
    doublereal stolr0;
    integer imax, nuse;
} intpar_;

#define intpar_1 intpar_

/* Table of constant values */

static doublereal c_b6 = 2.;
static integer c__9 = 9;
static integer c__1 = 1;



/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */
/* BSSTEP */
/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */
/* Subroutine */ int bsstep_(doublereal *y, doublereal *dydx, integer *nv, 
	doublereal *x0, doublereal *htry, doublereal *eps, doublereal *yscal, 
	doublereal *hdid, doublereal *hnext, U_fp deriv, doublereal *b, 
	doublereal *fpl, doublereal *ftl, doublereal *gl, logical *latmo, 
	logical *lderiv, logical *locond, logical *lsave, doublereal *rl, 
	doublereal *teffl, doublereal *x, doublereal *z__, integer *kount, 
	integer *ksaha, doublereal *err)
{
    /* Initialized data */

    static integer nseq[11] = { 2,4,6,8,12,16,24,32,48,64,96 };

    /* System generated locals */
    integer i__1, i__2;
    doublereal d__1, d__2, d__3;

    /* Builtin functions */
    double pow_di(doublereal *, integer *);
    integer s_wsle(cilist *), do_lio(integer *, integer *, char *, ftnlen), 
	    e_wsle(void);
    /* Subroutine */ void s_stop(char *, ftnlen);

    /* Local variables */
    static doublereal h__;
    static integer i__, j;
    extern /* Subroutine */ int mmid_(doublereal *, doublereal *, integer *, 
	    doublereal *, doublereal *, integer *, doublereal *, U_fp, 
	    doublereal *, doublereal *, doublereal *, doublereal *, logical *,
	     logical *, logical *, logical *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, integer *, integer *);
    static doublereal yerr[3], ysav[3], yseq[3], xsav, xest, dysav[3], errmax;
    extern /* Subroutine */ int ratext_(integer *, doublereal *, doublereal *,
	     doublereal *, doublereal *, integer *, integer *);

    /* Fortran I/O blocks */
    static cilist io___12 = { 0, 6, 0, 0, 0 };


    /* Parameter adjustments */
    --err;
    --yscal;
    --dydx;
    --y;

    /* Function Body */
    h__ = *htry;
    xsav = *x0;
    i__1 = *nv;
    for (i__ = 1; i__ <= i__1; ++i__) {
	ysav[i__ - 1] = y[i__];
	dysav[i__ - 1] = dydx[i__];
/* L10: */
    }
L20:
    i__1 = intpar_1.imax;
    for (i__ = 1; i__ <= i__1; ++i__) {
	mmid_(ysav, dysav, nv, &xsav, &h__, &nseq[i__ - 1], yseq, (U_fp)deriv,
		 b, fpl, ftl, gl, latmo, lderiv, locond, lsave, rl, teffl, x, 
		z__, kount, ksaha);
/* Computing 2nd power */
	d__1 = h__ / nseq[i__ - 1];
	xest = d__1 * d__1;
	ratext_(&i__, &xest, yseq, &y[1], yerr, nv, &intpar_1.nuse);
	errmax = 0.;
	i__2 = *nv;
	for (j = 1; j <= i__2; ++j) {
/* Computing MAX */
	    d__2 = errmax, d__3 = (d__1 = yerr[j - 1] / yscal[j], abs(d__1));
	    errmax = max(d__2,d__3);
	    err[j] = (d__1 = yerr[j - 1] / yscal[j], abs(d__1));
/* L30: */
	}
	errmax /= *eps;
	if (errmax < 1.) {
	    *x0 += h__;
	    *hdid = h__;
	    if (i__ == intpar_1.nuse) {
		*hnext = h__ * .95;
	    } else if (i__ == intpar_1.nuse - 1) {
		*hnext = h__ * 1.2;
	    } else {
		*hnext = h__ * (doublereal) nseq[intpar_1.nuse - 2] / (
			doublereal) nseq[i__ - 1];
	    }
	    return 0;
	}
/* L40: */
    }
    i__1 = (intpar_1.imax - intpar_1.nuse) / 2;
    h__ = h__ * .25 / pow_di(&c_b6, &i__1);
/*      H = 0.25D0*H/2**((IMAX-NUSE)/2) */
    if (*x + h__ == *x) {
	s_wsle(&io___12);
	do_lio(&c__9, &c__1, "ERROR IN BSSTEP", (ftnlen)15);
	e_wsle();
	s_stop("", (ftnlen)0);
    }
    goto L20;
} /* bsstep_ */

