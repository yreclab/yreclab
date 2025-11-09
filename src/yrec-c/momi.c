/* momi.f -- translated by f2c (version 20061008).
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

/* $$$$$$ */
/*       SUBROUTINE MOMI(ETA2,HD,HR,HS,HS2,JSTART,JEND,OMEGA,R0,HI,QIW,M)  ! KC 2025-05-31 */
/* Subroutine */ int momi_(doublereal *eta2, doublereal *hr, doublereal *hs, 
	doublereal *hs2, integer *jstart, integer *jend, doublereal *omega, 
	doublereal *r0, doublereal *hi, doublereal *qiw)
{
    /* System generated locals */
    integer i__1;
    doublereal d__1;

    /* Builtin functions */
    double log(doublereal), exp(doublereal);

    /* Local variables */
    static doublereal a;
    static integer i__;
    static doublereal h0, r03, r0p, r0r, rad, him, con, qr0r, qiwm, rphi3, 
	    eta2x, rphip;
    extern /* Subroutine */ int intmom_(doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *);

/*       DIMENSION HD(JSON),HR(JSON),HS2(JSON),R0(JSON),ETA2(JSON),HI(JSON)  ! KC 2025-05-31 */
/*  FIND THE MOMENT OF INERTIA (HI) AND DI/D(OMEGA) (QIW). */
/*  MOMI ASSUMES THAT SHAPE HAS ALREADY BEEN CALLED. */
/*  MOMENT OF INERTIA IS CALCULATED BY THE METHOD USED IN WAI-YUEN LAW'S */
/*  THESIS(YALE,1980) P.61. */
    /* Parameter adjustments */
    --qiw;
    --hi;
    --r0;
    --omega;
    --hs2;
    --hs;
    --hr;
    --eta2;

    /* Function Body */
    if (*jstart == 1) {
	r0p = 0.;
	rphip = 0.;
    } else {
	r0p = log(r0[*jstart - 1]);
	rphip = const1_1.cln * hr[*jstart - 1];
    }
    con = const1_1.cc13 * 5. / exp(const1_1.cln * const2_1.cgl);
    if (rot_1.walpcz != 0.) {
	i__1 = *jend;
	for (i__ = *jstart; i__ <= i__1; ++i__) {
	    hi[i__] = const1_1.cc23 * hs2[i__] * exp(const1_1.cln * 2. * hr[
		    i__]);
	    qiw[i__] = 0.;
	}
	if (*jstart == 1) {
	    rad = (hr[1] + hr[2]) * .5;
	    hi[1] = hs2[1] * .4 * exp(const1_1.cln * 2. * rad);
	}
	return 0;
    }
    i__1 = *jend;
    for (i__ = *jstart; i__ <= i__1; ++i__) {
/*  QR0R = D LN R0/ D LN R */

	qr0r = 1.;
	h0 = const1_1.cc23 * hs2[i__] * exp(const1_1.cln * 2. * hr[i__]);
/* Computing 3rd power */
	d__1 = r0[i__];
	r03 = d__1 * (d__1 * d__1);
	rphi3 = exp(const1_1.cln * 3. * hr[i__]);
/* Computing 2nd power */
	d__1 = r0[i__];
	r0r = r03 / rphi3 * (d__1 * d__1);
/* Computing 2nd power */
	d__1 = omega[i__];
	a = con * (d__1 * d__1) * r03 / (exp(const1_1.cln * hs[i__]) * (eta2[
		i__] + 2.));
	eta2x = eta2[i__];
/*  EVALUATE INTEGRAL AT THE ZONE CENTER */
	intmom_(&a, &eta2x, &qr0r, &r0r, &him, &qiwm);
	hi[i__] = him * hs2[i__];
	qiw[i__] = qiwm * hs2[i__];
	r0p = log(r0[i__]);
	rphip = const1_1.cln * hr[i__];
/* L20: */
    }
    return 0;
} /* momi_ */

