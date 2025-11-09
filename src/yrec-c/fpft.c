/* fpft.f -- translated by f2c (version 20061008).
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
    logical lstore, lstatm, lstenv, lstmod, lstphys, lstrot, lscrib, lstch, 
	    lphhd;
} ccout_;

#define ccout_1 ccout_

struct {
    doublereal cln, clni, c4pi, c4pil, c4pi3l, cc13, cc23, cpi;
} const1_;

#define const1_1 const1_

struct {
    doublereal cgas, ca3, ca3l, csig, csigl, cgl, cmkh, cmkhn;
} const2_;

#define const2_1 const2_

struct {
    integer ilast, idebug, itrack, ishort, imilne, imodpt, istor, iowr;
} luout_;

#define luout_1 luout_

struct {
    doublereal wnew, walpcz, acfpft;
    integer itfp1, itfp2;
    logical lrot, linstb, lwnew;
} rot_;

#define rot_1 rot_

struct {
    doublereal phisp[5000], phirot[5000], phidis[5000], rat[5000];
} quadd_;

#define quadd_1 quadd_

/* Table of constant values */

static integer c__1 = 1;
static doublereal c_b6 = 0.;

/* $$$$$$ */
/* Subroutine */ int fpft_(doublereal *hd, doublereal *hr, doublereal *hs, 
	integer *m, doublereal *omega, doublereal *eta2, doublereal *fp, 
	doublereal *ft, doublereal *hg, doublereal *r0)
{
    /* System generated locals */
    integer i__1, i__2, i__3;
    doublereal d__1;

    /* Builtin functions */
    double exp(doublereal), d_lg10(doublereal *);

    /* Local variables */
    static doublereal a, b, h__[20];
    static integer i__, j, k;
    static doublereal q, f0, g0;
    static integer j1, n1;
    static doublereal w2, cg, gm, r03;
    static integer km;
    static doublereal xa[20], ya[20], mp, sm, qp, r0p, w2p, eps, rho, fact, 
	    eta22, aint, dint;
    static integer jmax;
    static doublereal rphi, sphi, ginv, rhop, aint0[10], aint1, ginv0, rphi3, 
	    eta22p;
    extern /* Subroutine */ int shape_(doublereal *, doublereal *, doublereal 
	    *, integer *, integer *, doublereal *, doublereal *, doublereal *)
	    ;
    static doublereal aintp, aintt;
    extern /* Subroutine */ int qgauss_(doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, integer *)
	    , trapzd_(doublereal *, doublereal *, doublereal *, integer *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *), polint_(doublereal *, doublereal *, 
	    integer *, doublereal *, doublereal *, doublereal *);

/*  FIND THE RUN OF R0 AND ETA2 FOR THE MODEL */
    /* Parameter adjustments */
    --r0;
    --hg;
    --ft;
    --fp;
    --eta2;
    --omega;
    --hs;
    --hr;
    --hd;

    /* Function Body */
    shape_(&hd[1], &hr[1], &hs[1], &c__1, m, &omega[1], &eta2[1], &r0[1]);
    b = const1_1.c4pi * .125;
    cg = exp(const1_1.cln * const2_1.cgl);
    eps = 1e-6;
    jmax = 2;
    k = 2;
    km = k - 1;
/* THE VALUES OF THE PREVIOUS SHELL MPHI,ETA2+2,OMEGA**2,RHO, AND R0 ARE */
/* NEEDED FOR THE EVALUATION OF THE DISTORTED POTENTIAL. */
/* THE BELOW VALUES ARE THE CENTRAL VALUES OF THE ABOVE IN ORDER. */
    mp = 0.;
    eta22p = 2.;
/* Computing 2nd power */
    d__1 = omega[1];
    w2p = d__1 * d__1;
    rhop = exp(const1_1.cln * hd[1]);
    r0p = 0.;
    aintp = 0.;
    aintt = 0.;
    qp = 0.;
/* NOW CALCULATE FP AND FT USING THE ETA2 AND R0 VALUES */
    i__1 = *m;
    for (i__ = 1; i__ <= i__1; ++i__) {
	rho = exp(const1_1.cln * hd[i__]);
	gm = cg * exp(const1_1.cln * hs[i__]);
/* Computing 2nd power */
	d__1 = omega[i__];
	fact = const1_1.cc13 * 5. * (d__1 * d__1) / (gm * (eta2[i__] + 2.));
/* Computing 3rd power */
	d__1 = r0[i__];
	r03 = d__1 * (d__1 * d__1);
	a = fact * r03;
	sm = exp(const1_1.cln * hs[i__]);
	eta22 = eta2[i__] + 2.;
/* Computing 2nd power */
	d__1 = omega[i__];
	w2 = d__1 * d__1;
	h__[0] = 1.;
	i__2 = jmax;
	for (j = 1; j <= i__2; ++j) {
/*  EVALUATE THE INTEGRAL AINT FROM 0 TO R0 USING THE TRAPEZOIDAL RULE */
	    trapzd_(&r0p, &r0[i__], &aint0[j - 1], &j, &rho, &rhop, &sm, &mp, 
		    &w2, &w2p, &eta22, &eta22p, &q, &qp);
/*      *      W2,W2P,ETA22,ETA22P,Q,QP,I)  ! KC 2025-05-31 */
	    if (j >= k) {
		n1 = j - km;
		i__3 = k;
		for (j1 = 1; j1 <= i__3; ++j1) {
		    xa[j1 - 1] = h__[n1 - 1];
		    ya[j1 - 1] = aint0[n1 - 1];
		    ++n1;
/* L35: */
		}
		polint_(xa, ya, &k, &c_b6, &aint1, &dint);
		if (abs(dint) < eps * abs(aint1)) {
		    goto L50;
		}
	    }
	    aint0[j] = aint0[j - 1];
	    h__[j] = h__[j - 1] * .25;
/* L40: */
	}
L50:
	aint = aintp + aint1;
/*  FIND <G> AND <G-1> ACROSS THE SHELL BY GAUSSIAN QUADRATURE */
	qgauss_(&g0, &ginv0, &sphi, &b, &r0[1], &hs[1], &aint, &q, &w2, &a, &
		i__);
	hg[i__] = g0 / sphi;
	ginv = d_lg10(&ginv0);
	f0 = const1_1.c4pil + hr[i__] * 4. - ginv;
	fp[i__] = exp(const1_1.cln * (f0 - const2_1.cgl - hs[i__]));
	ft[i__] = exp(const1_1.cln * (f0 + const1_1.c4pil)) / g0;
/*  OUTPUT DATA */
	rphi = exp(const1_1.cln * hr[i__]);
/* Computing 3rd power */
	d__1 = rphi;
	rphi3 = d__1 * (d__1 * d__1);
	quadd_1.phisp[i__ - 1] = gm / rphi;
/* Computing 2nd power */
	d__1 = rphi;
	quadd_1.phirot[i__ - 1] = w2 * (d__1 * d__1);
	quadd_1.phidis[i__ - 1] = const1_1.c4pi * const1_1.cc13 * aint / 
		rphi3;
	aintp = aint;
	qp = q;
	mp = sm;
	eta22p = eta22;
	w2p = w2;
	rhop = rho;
	r0p = r0[i__];
/* L100: */
    }
    return 0;
} /* fpft_ */

