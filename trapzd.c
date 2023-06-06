/* trapzd.f -- translated by f2c (version 20100827).
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
/* TRAPZD */
/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */
/* Subroutine */ int trapzd_(doublereal *b1, doublereal *b2, doublereal *s, 
	integer *n, doublereal *rho, doublereal *rhop, doublereal *sm, 
	doublereal *smp, doublereal *w2, doublereal *w2p, doublereal *eta22, 
	doublereal *eta22p, doublereal *q, doublereal *qp, integer *i__)
{
    /* System generated locals */
    integer i__1;
    doublereal d__1, d__2;

    /* Local variables */
    static integer j;
    static doublereal y, q0, r0, dm, r03, dr;
    static integer it;
    static doublereal dw2, w2t, del, r03t, tnm, smt, sum, drho, rhot, deta2, 
	    eta22t;

    r0 = *b2;
/* Computing 3rd power */
    d__1 = r0;
    r03 = d__1 * (d__1 * d__1);
    if (*n == 1) {
/*  AINT = INT(0=>R0) (RHO/M)*R0'**7*OMEGA**2*(5+ETA2)/(2+ETA2) DR0' */
/*  Q IS THE INTEGRAND (RO'**7,ETC.) EVALUATED AT R0(I) */
/*  AINT AND ITS DERIVATIVES W/R/TO R AND THETA ARE NEEDED TO FIND <G> */
	*q = *rho * *w2 * r03 * (*eta22 + 3.) / (*sm * *eta22) * r03 * r0;
/*        Q(I) = DEXP(CLN*(HD(I)-HS(I)))*OMEGA(I)**2*R0(I)**6 */
/*    *   *(5.0D0+ETA2(I))/(2.0D0+ETA2(I)) */
	*s = (*b2 - *b1) * .5 * (*qp + *q);
	it = 1;
    } else {
	tnm = (doublereal) it;
	dr = *b2 - *b1;
	del = dr / tnm;
	y = *b1 + del * .5;
	sum = 0.;
	drho = (*rho - *rhop) / dr;
/* Computing 2nd power */
	d__1 = *b2;
/* Computing 2nd power */
	d__2 = *b1;
	dm = (*sm - *smp) / (d__1 * d__1 - d__2 * d__2);
	deta2 = (*eta22 - *eta22p) / dr;
	dw2 = (*w2 - *w2p) / dr;
	i__1 = it;
	for (j = 1; j <= i__1; ++j) {
/* Computing 3rd power */
	    d__1 = y;
	    r03t = d__1 * (d__1 * d__1);
/* INTERPOLATE RHO,M,OMEGA,ETA2+2 BETWEEN SHELL I AND SHELL I-1 */
	    rhot = *rhop + drho * del;
/* Computing 2nd power */
	    d__1 = y;
/* Computing 2nd power */
	    d__2 = *b1;
	    smt = *smp + dm * (d__1 * d__1 - d__2 * d__2);
	    w2t = *w2p + dw2 * del;
	    eta22t = *eta22p + deta2 * del;
/* CALCULATE Q BETWEEN SHELLS */
	    q0 = rhot * w2t * r03t * (eta22t + 3.) / (smt * eta22t) * r03t * 
		    y;
/* Q0 = RHO*W2*R07T*(3.0D0+ETA22)/(SM*ETA22) */
	    sum += q0;
	    y += del;
/* L10: */
	}
	*s = (*s + del * sum) * .5;
	it <<= 1;
    }
    return 0;
} /* trapzd_ */

