/* shape.f -- translated by f2c (version 20100827).
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

struct {
    doublereal wnew, walpcz, acfpft;
    integer itfp1, itfp2;
    logical lrot, linstb, lwnew;
} rot_;

#define rot_1 rot_

/* $$$$$$ */
/* Subroutine */ int shape_(doublereal *hd, doublereal *hr, doublereal *hs, 
	integer *jstart, integer *jend, doublereal *omega, doublereal *eta2, 
	doublereal *r0)
{
    /* System generated locals */
    integer i__1, i__2, i__3;
    doublereal d__1, d__2, d__3, d__4;

    /* Builtin functions */
    double exp(doublereal), pow_dd(doublereal *, doublereal *);

    /* Local variables */
    static doublereal a;
    static integer i__, j, k;
    static doublereal c1, c2, c3, c4, cg, gm, r03, dr, r0a, acc, rho, err, 
	    etaa, fact, rhoa, rphi, rhop, deta1, deta2, deta3, deta4, eta2t, 
	    rphi3, r0est, delr03, rhoba, rphia, rhobp, rphip;
    static integer jbegin;
    static doublereal rhobar;

/*  SHAPE FINDS THE DISTORTION OF A GIVEN SHELL FROM SPHERICAL SYMMETRY; */
/*  IT CALCULATES THE CHARACTERISTIC RADIUS R0 AND ASSOCIATED PARAMETER */
/*  ETA2.  IN POLAR CO-ORDINATES THE RADIUS OF A SHELL IS */
/*  R = R0*(1 - A*P2), WHERE A IS A FUNCTION OF ROTATION RATE AND P2 IS */
/*  THE SECOND LEGENDRE POLYNOMIAL.  FOR MORE INFORMATION SEE ENDAL AND */
/*  SOFIA. */
    /* Parameter adjustments */
    --r0;
    --eta2;
    --omega;
    --hs;
    --hr;
    --hd;

    /* Function Body */
    cg = exp(const1_1.cln * const2_1.cgl);
    c1 = .6;
    c2 = .057142857142857141;
    c3 = c1 * 3.;
    c4 = c2 * 4.;
    jbegin = *jstart;
    if (*jstart == 1) {
/*  CALCULATE FIRST POINT ETA2 USING CENTRAL B.C. */
/*  NOTE THAT THE SUFFIX 'P' DENOTES A QUANTITY FROM THE PREVIOUS SHELL. */
/*  E.G. RHOP IS THE DENSITY OF THE LAST SHELL AND RHO IS THE DENSITY OF */
/*  THE CURRENT ONE. */
	rhobar = exp(const1_1.cln * (hs[1] - const1_1.c4pi3l - hr[1] * 3.));
	rphi = exp(const1_1.cln * hr[1]);
	rho = exp(const1_1.cln * hd[1]);
	eta2[1] = (1. - rho / rhobar) * 6.;
/* ITERATE FOR R0 GIVEN RPHI AND ETA2 */
	gm = cg * exp(const1_1.cln * hs[1]);
/* Computing 3rd power */
	d__1 = rphi;
	rphi3 = d__1 * (d__1 * d__1);
	r03 = rphi3;
/* Computing 2nd power */
	d__1 = omega[1];
	fact = const1_1.cc13 * 5. * (d__1 * d__1) / (gm * (eta2[1] + 2.));
	i__1 = rot_1.itfp2;
	for (j = 1; j <= i__1; ++j) {
	    a = fact * r03;
/* Computing 2nd power */
	    d__1 = a;
/* Computing 3rd power */
	    d__2 = a;
/* Computing 2nd power */
	    d__3 = a;
/* Computing 3rd power */
	    d__4 = a;
	    delr03 = (rphi3 - r03 * (c1 * (d__1 * d__1) + 1. - c2 * (d__2 * (
		    d__2 * d__2)))) / (c3 * (d__3 * d__3) + 1. - c4 * (d__4 * 
		    (d__4 * d__4)));
	    r03 += delr03;
	    if ((d__1 = delr03 / r03, abs(d__1)) <= rot_1.acfpft) {
		goto L20;
	    }
/* L10: */
	}
L20:
	r0[1] = pow_dd(&r03, &const1_1.cc13);
	if (*jend == 1) {
	    goto L9999;
	}
	rhobp = rhobar;
	rphip = rphi;
	rhop = rho;
	jbegin = 2;
    } else {
	rhobp = exp(const1_1.cln * (hs[*jstart - 1] - const1_1.c4pi3l - hr[*
		jstart - 1] * 3.));
	rphip = exp(const1_1.cln * hr[*jstart - 1]);
	rhop = exp(const1_1.cln * hd[*jstart - 1]);
    }
/*  CALCULATE ETA2 AND R0 FOR REMAINING POINTS */
    i__1 = *jend;
    for (i__ = jbegin; i__ <= i__1; ++i__) {
	rhobar = exp(const1_1.cln * (hs[i__] - const1_1.c4pi3l - hr[i__] * 3.)
		);
	rho = exp(const1_1.cln * hd[i__]);
	rphi = exp(const1_1.cln * hr[i__]);
	gm = cg * exp(const1_1.cln * hs[i__]);
	dr = rphi - rphip;
/* FIND ETA2 USING 4-POINT RUNGE-KUTTE TECHNIQUE */
/* D(ETA2)/D(R0) IS COMPUTED USING RADAU'S EQUATION: */
/* R*(DETA2/DR)+6*RHO*(ETA2+1)/RHOBAR+ETA2*(ETA2-1) = 6 ,AND ETA2(0) = 0 */
/* FOR A FIRST GUESS,R0 = RPHI IS ASSUMED. */
/*    FIRST EVALUATE DETA/DR AT THE BEGINNING OF THE INTERVAL */
	deta1 = dr * (6. - rhop * 6. * (eta2[i__ - 1] + 1.) / rhobp - eta2[
		i__ - 1] * (eta2[i__ - 1] - 1.)) / rphip;
/* RHOA AND RHOBA ARE AVERAGES OF THE RHO,RHOBAR OF OLD AND NEW SHELLS */
	rhoa = (rho + rhop) * .5;
	rhoba = (rhobar + rhobp) * .5;
	etaa = eta2[i__ - 1] + deta1 * .5;
	rphia = rphip + dr * .5;
/*    USING THE ESTIMATED ETA2 AT THE MIDPOINT,FIND DETA/DR AT THE */
/*    MIDPOINT. */
	deta2 = dr * (6. - rhoa * 6. * (etaa + 1.) / rhoba - etaa * (etaa - 
		1.)) / rphia;
	etaa = eta2[i__ - 1] + deta2 * .5;
/*    USING THIS REFINED DERIVATIVE TO ESTIMATE ETA2 AT MIDPOINT, */
/*    FIND DETA/DR AT THE MIDPOINT AGAIN. */
	deta3 = dr * (6. - rhoa * 6. * (etaa + 1.) / rhoba - etaa * (etaa - 
		1.)) / rphia;
	etaa = eta2[i__ - 1] + deta3;
/*    USING DETA/DR AT THE MIDPOINT TO ESTIMATE ETA2 AT THE END OF */
/*    THE INTERVAL,GET DETA/DR AT THE END OF THE INTERVAL. */
	deta4 = dr * (6. - rho * 6. * (etaa + 1.) / rhobar - etaa * (etaa - 
		1.)) / rphi;
/*    PERFORM 4TH ORDER RUNGE-KUTTE INTEGRATION USING ABOVE 4 DERIVS. */
	eta2[i__] = eta2[i__ - 1] + const1_1.cc13 * (deta1 * .5 + deta2 + 
		deta3 + deta4 * .5);
/* Computing 3rd power */
	d__1 = rphi;
	rphi3 = d__1 * (d__1 * d__1);
	r03 = rphi3;
	r0est = rphi;
	acc = pow_dd(&rot_1.acfpft, &const1_1.cc13);
/* ITERATE BETWEEN SOLUTION FOR ETA2 AND SOLUTION FOR R0 ITFP1 TIMES. */
	i__2 = rot_1.itfp1;
	for (k = 1; k <= i__2; ++k) {
/* Computing 2nd power */
	    d__1 = omega[i__];
	    fact = const1_1.cc13 * 5. * (d__1 * d__1) / (gm * (eta2[i__] + 2.)
		    );
/* NOW ITERATE FOR R0 GIVEN RPHI AND ETA2, USING THE RELATION */
/* RPHI**3 = R0**3(1.0 + 3/5A**2 - 2/35A**3) */
/* WHERE A = OMEGA**2*R0**3*5/3GM(2+ETA2)) */
	    i__3 = rot_1.itfp2;
	    for (j = 1; j <= i__3; ++j) {
		a = fact * r03;
/* Computing 2nd power */
		d__1 = a;
/* Computing 3rd power */
		d__2 = a;
/* Computing 2nd power */
		d__3 = a;
/* Computing 3rd power */
		d__4 = a;
		delr03 = (rphi3 - r03 * (c1 * (d__1 * d__1) + 1. - c2 * (d__2 
			* (d__2 * d__2)))) / (c3 * (d__3 * d__3) + 1. - c4 * (
			d__4 * (d__4 * d__4)));
		r03 += delr03;
		if ((d__1 = delr03 / r03, abs(d__1)) < rot_1.acfpft) {
		    goto L50;
		}
/* L40: */
	    }
L50:
	    r0[i__] = pow_dd(&r03, &const1_1.cc13);
	    err = r0[i__] - r0est;
/*  ETA2 IS A FUNCTION OF R0, AND R0=RPHI WAS USED TO CALCULATE ETA2 */
/*  CORRECT ETA2 HERE IF DR/R0 > CUBE ROOT OF ACFPFT */
	    if (abs(err) / r0[i__] <= acc) {
		goto L70;
	    }
/* FIND ETA2 USING 4-POINT RUNGE-KUTTE TECHNIQUE AGAIN,BUT FINDING */
/* ETA2 AT R0(I) RATHER THAN ASSUMING R0 = RPHI. */
	    eta2t = eta2[i__];
	    dr = r0[i__] - r0[i__ - 1];
	    deta1 = dr * (6. - rhop * 6. * (eta2[i__ - 1] + 1.) / rhobp - 
		    eta2[i__ - 1] * (eta2[i__ - 1] - 1.)) / r0[i__ - 1];
	    etaa = eta2[i__ - 1] + deta1 * .5;
	    r0a = r0[i__ - 1] + dr * .5;
	    deta2 = dr * (6. - rhoa * 6. * (etaa + 1.) / rhoba - etaa * (etaa 
		    - 1.)) / r0a;
	    etaa = eta2[i__ - 1] + deta2 * .5;
	    deta3 = dr * (6. - rhoa * 6. * (etaa + 1.) / rhoba - etaa * (etaa 
		    - 1.)) / r0a;
	    etaa = eta2[i__ - 1] + deta3;
	    deta4 = dr * (6. - rho * 6. * (etaa + 1.) / rhobar - etaa * (etaa 
		    - 1.)) / r0[i__];
	    eta2[i__] = eta2[i__ - 1] + const1_1.cc13 * (deta1 * .5 + deta2 + 
		    deta3 + deta4 * .5);
	    err = eta2t - eta2[i__];
	    if (abs(err) <= acc) {
		goto L70;
	    }
	    r0est = r0[i__];
/* L60: */
	}
L70:
	rhop = rho;
	rhobp = rhobar;
	rphip = rphi;
/* L100: */
    }
L9999:
    return 0;
} /* shape_ */

