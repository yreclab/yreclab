/* intpol.f -- translated by f2c (version 20061008).
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

/* Table of constant values */

static integer c__9 = 9;
static integer c__1 = 1;



/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */
/* INTPOL */
/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */
/*  ***** THE INTERPOLATION ROUTINE ***** */
/*  THIS ROUTINE CONTAINS TWO INTERPOLATION METHODS; HERMITE, */
/*  AND SPLINE.  EACH OF THESE HAS OWN MERIT AND DEMERIT. */
/*  IF THE INTERPOLANT IS SMOOTH, BOTH OF THESE WILL GIVE GOOD */
/*  RESULTS.  GENERALLY, SPLINE GIVES MORE SMOOTH INTERPOLATION. */
/*  WHEN THE INTERPOLANT CONTAINS ABRUPT VARIATION IN GRADIENT, */
/*  HOWEVER, SPLINE GET WORSE AT THAT PART, WHILE HERMIT STILL */
/*  GIVES REASONABLE RESULT.  UNFORTUNATELY, THERE IS NO CRITERION */
/*  FOR SELECTION BETWEEN THESE TWO METHODS.  THEREFORE, THIS */
/*  ROUTINE GIVES THE RIGHT FOR SELECTION TO USER. */
/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */
/* YCK 3/91 */
/* Subroutine */ int intpol_(doublereal *xi, doublereal *f, integer *n, 
	doublereal *xbar, doublereal *ybar, doublereal *ybarp)
{
    /* Initialized data */

    static doublereal c__[400]	/* was [4][100] */ = { 0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,
	    0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0.,0. };

    /* System generated locals */
    integer i__1;

    /* Builtin functions */
    integer s_wsle(cilist *), do_lio(integer *, integer *, char *, ftnlen), 
	    e_wsle(void);
    /* Subroutine */ void s_stop(char *, ftnlen);

    /* Local variables */
    static integer i__, k;
    static doublereal dx;
    static integer khi, klo;
    static doublereal valp, xbari, value;
    extern /* Subroutine */ int ysplin_(doublereal *, doublereal *, integer *)
	    ;

    /* Fortran I/O blocks */
    static cilist io___7 = { 0, 0, 0, 0, 0 };
    static cilist io___8 = { 0, 0, 0, 0, 0 };


/* ---------------------------------------------------------- */
/*  XI  ; ARRAY OF ABSCISSA POINTS */
/*  F   ; ARRAY OF ORDINATE POINTS */
/*  N   ; SIZE OF THE ARRAYS */
/*  XBAR; A X-VALUE AT WHICH WE WANT TO FIND Y-VALUE */
/*  KLO ; THE GRID POINT SMALLER THAN AND CLOSEST TO XBAR */
/*  YBAR; THE VALUE WE WANT */
/*  YBARP; THE DERIVATIVE VALUE AT XBAR */
/* --------------------------------------------------------- */
    /* Parameter adjustments */
    --f;
    --xi;

    /* Function Body */
/* THE COEFFICIENTS FOR THE ZERO-TH ORDER TERM */
    i__1 = *n;
    for (i__ = 1; i__ <= i__1; ++i__) {
	c__[(i__ << 2) - 4] = f[i__];
/* L1: */
    }
/* FIND THE COEFFICIENTS FOR SPLINE INTERPLOATION */
    ysplin_(&xi[1], c__, n);
    xbari = *xbar;
/* FIND THE GRID POINT,  KLO, SUCH THAT XI(KLO)<=XBARI, AND */
/* ABS(XI(KLO)-XBARI)<1. */
    if (xi[1] > *xbar) {
	klo = 1;
	khi = 2;
	goto L522;
    }
    if (xi[*n] < *xbar) {
	klo = *n - 1;
	khi = *n;
	goto L522;
    }
    klo = 1;
    khi = *n;
L2:
    if (khi - klo > 1) {
	k = (khi + klo) / 2;
	if (xi[k] > xbari) {
	    khi = k;
	} else {
	    klo = k;
	}
	goto L2;
    }
    if (khi - klo <= 0) {
	io___7.ciunit = luout_1.iowr;
	s_wsle(&io___7);
	do_lio(&c__9, &c__1, "ERROR COX OP: INTERPOLATION", (ftnlen)27);
	e_wsle();
	io___8.ciunit = luout_1.ishort;
	s_wsle(&io___8);
	do_lio(&c__9, &c__1, "ERROR COX OP: INTERPOLATION", (ftnlen)27);
	e_wsle();
	s_stop("", (ftnlen)0);
    }
L522:
/* NOW, (KLO,KHI) IS SUB-RANGE OF XI WHICH CONTAINS XBARI. */
    dx = xbari - xi[klo];
/* GO ON TO THE SPLINE INTERPOLATION ROUTINE. */
/* EVALUATES THE INTERPOLATION VALUE IN THE SUB-RANGE WE DETERMINED. */
    value = ((c__[(klo << 2) - 1] * dx + c__[(klo << 2) - 2]) * dx + c__[(klo 
	    << 2) - 3]) * dx + c__[(klo << 2) - 4];
    valp = (c__[(klo << 2) - 1] * 3. * dx + c__[(klo << 2) - 2] * 2.) * dx + 
	    c__[(klo << 2) - 3];
/* RETURN THE RESULTS FROM THE SPLINE ROUTINE */
    *ybar = value;
    *ybarp = valp;
    return 0;
} /* intpol_ */

