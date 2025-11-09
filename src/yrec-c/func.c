/* func.f -- translated by f2c (version 20061008).
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
    doublereal cgas, ca3, ca3l, csig, csigl, cgl, cmkh, cmkhn;
} const2_;

#define const2_1 const2_

/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */
/* FUNC */
/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */
/* Subroutine */ int func_(doublereal *x, doublereal *g, doublereal *s, 
	doublereal *r0, doublereal *hs, doublereal *aint, doublereal *q, 
	doublereal *w2, doublereal *a, integer *i__)
{
    /* System generated locals */
    doublereal d__1, d__2;

    /* Builtin functions */
    double cos(doublereal), sin(doublereal), exp(doublereal), sqrt(doublereal)
	    ;

    /* Local variables */
    static doublereal r__, p2, r2, cs, ss, qr0r, qr0t, qphir, const__, qphith;

    /* Parameter adjustments */
    --hs;
    --r0;

    /* Function Body */
    cs = cos(*x) * sin(*x);
/* Computing 2nd power */
    d__1 = sin(*x);
    ss = d__1 * d__1;
/* P2 = .5*(3COS(X)**2 - 1) = .5(3*(1-SIN(X)**2) - 1) = 1 - 1.5*SIN(X)**2 */
    p2 = 1. - ss * 1.5;
/* DERIVATIVES OF R0 WITH RESPECT TO R AND THETA */
    qr0r = 1. / (1. - *a * 4. * p2);
    qr0t = cs * 3. * *a * qr0r / (1. - *a * p2);
/* USE THE RELATION FOR R ON AN EQUIPOTENTIAL */
    r__ = r0[*i__] * (1. - *a * p2);
/* Computing 2nd power */
    d__1 = r__;
    r2 = d__1 * d__1;
    const__ = const1_1.c4pi * const1_1.cc13 / (r2 * r2);
/* CALCULATE THE DERIVATIVES OF PHI WITH RESPECT TO R AND THETA */
/* D(PHI)/DR = GM/R2 + 12PI*G*P2*AINT/5R**4 -4PI*G*P2*Q*(DR0/DR)/5R**3 */
/* -OMEGA**2*R*SIN(THETA)**2 - ASSUME DR0/DR = 1 */
    qphir = exp(const1_1.cln * (const2_1.cgl + hs[*i__])) / r2 - const__ * p2 
	    * (*aint * 3. - r__ * *q * qr0r) - *w2 * r__ * ss;
/* D(PHI)/D(THETA) = 4PI*G*3DCOS(THETA)DSIN(THETA)*AINT/5R**4 - */
/* 4PI*G*P2*Q*DR0/D(THETA)/5R**4 - OMEGA**2*R*DCOS(THETA)SIN(THETA) */
    qphith = const__ * (p2 * *q * qr0t - *aint * 3. * cs) - *w2 * r__ * cs;
/* Computing 2nd power */
    d__1 = qphir;
/* Computing 2nd power */
    d__2 = qphith;
    *g = sqrt(d__1 * d__1 + d__2 * d__2);
/* Computing 2nd power */
    d__1 = 1. - *a * p2;
/* Computing 2nd power */
    d__2 = cs * 3. * *a;
    *s = const1_1.c4pi * r__ * sin(*x) * r0[*i__] * sqrt(d__1 * d__1 + d__2 * 
	    d__2);
    return 0;
} /* func_ */

