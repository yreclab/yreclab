/* eqburn.f -- translated by f2c (version 20061008).
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
    doublereal atime[14], tcut[5], tscut, tenv0, tenv1, tenv, tgcut;
} ctlim_;

#define ctlim_1 ctlim_

struct {
    doublereal hpo[5000], hto[5000], hro[5000], hlo[5000], hdo[5000], hcompp[
	    75000]	/* was [15][5000] */, hss[5000];
    logical lco[5000], lczo[5000];
    doublereal tefflo;
    integer mo;
} oldmod_;

#define oldmod_1 oldmod_

/*       SUBROUTINE EQBURN(HF1,HR1,HR2,HR3,HR4,HR5,HR6,HR7,HR8,HR9, */
/*      *                  HR10,HR11,HR12,HS2,HT,IBEGIN,IEND,  ! KC 2025-05-31 */
/* Subroutine */ int eqburn_(doublereal *hr1, doublereal *hr2, doublereal *
	hr3, doublereal *hr4, doublereal *hr5, doublereal *hr6, doublereal *
	hr7, doublereal *hr10, doublereal *hr12, doublereal *hs2, doublereal *
	ht, integer *ibegin, integer *iend, doublereal *dcdt, doublereal *
	dodt, doublereal *dxdt, doublereal *dydt, doublereal *xc12, 
	doublereal *xo16, doublereal *x, doublereal *z__)
{
    /* System generated locals */
    integer i__1;
    doublereal d__1;

    /* Builtin functions */
    double sqrt(doublereal);

    /* Local variables */
    static integer i__, j;
    static doublereal y, r11, r34, r3a, r412, gr1, gr2, gr3, gr4, gr5, gr6, 
	    gr7, gr10, gr12, xc13, r1214, r1314, xn14, xhe3, xsum[11], xhe3e, 
	    wtsum, sumcno;

/*      *HR5(JSON),HR6(JSON),HR7(JSON),HR8(JSON),HR9(JSON),HR10(JSON), */
/*      *HR11(JSON),HR12(JSON),HF1(JSON),HS2(JSON)  ! KC 2025-05-31 */
/* SKIP BURNING CALCULATIONS IF STARTING SHELL BELOW T CUTOFF FOR REACTIONS. */
    /* Parameter adjustments */
    --ht;
    --hs2;
    --hr12;
    --hr10;
    --hr7;
    --hr6;
    --hr5;
    --hr4;
    --hr3;
    --hr2;
    --hr1;

    /* Function Body */
    *dxdt = 0.;
    *dydt = 0.;
    *dcdt = 0.;
    *dodt = 0.;
    if (ht[*ibegin] < ctlim_1.tcut[0]) {
	return 0;
    }
/* COMPUTE EXPLICIT HYDROGEN AND HELIUM BURNING RATES ASSUMING EQUILIBRIUM */
/* HE3 AND CN CYCLE ABUNDANCES. */
/* THIS IS USED FOR AN INITIAL GUESS AT THE BURNING RATES AT THE START */
/* OF THE TIME STEP, AND CAN BE SUPPLEMENTED BY A FULLY IMPLICIT */
/* NON-EQUILIBRIUM CALCULATION IN THE 3RD AND 4TH LEVELS OF ITERATION. */
    if (*ibegin != *iend) {
/* HOMOGENIZE CONVECTION ZONES. */
/* XSUM IS THE MASS-WEIGHTED AVERAGE ABUNDANCE FOR THE CZ. */
/* WTSUM IS THE TOTAL MASS OF THE CZ. */
/* INITIALIZE SUMS. */
	wtsum = 0.;
	for (j = 1; j <= 11; ++j) {
	    xsum[j - 1] = 0.;
/* L1: */
	}
	i__1 = *iend;
	for (i__ = *ibegin; i__ <= i__1; ++i__) {
	    wtsum += hs2[i__];
	    for (j = 1; j <= 11; ++j) {
		xsum[j - 1] += oldmod_1.hcompp[j + i__ * 15 - 16] * hs2[i__];
/* L3: */
	    }
/* L5: */
	}
	for (j = 1; j <= 11; ++j) {
	    xsum[j - 1] /= wtsum;
/* L7: */
	}
    } else {
	for (j = 1; j <= 11; ++j) {
	    xsum[j - 1] = oldmod_1.hcompp[j + *ibegin * 15 - 16];
/* L9: */
	}
    }
    if (*ibegin == *iend) {
/* PP */
	gr1 = hr1[*ibegin];
/* HE3,HE3 */
	gr2 = hr2[*ibegin];
/* HE3,HE4 */
	gr3 = hr3[*ibegin];
/* C12,P */
	gr4 = hr4[*ibegin];
/* C13,P */
	gr5 = hr5[*ibegin];
/* N14,P + N15,P */
	gr6 = hr6[*ibegin];
/* O16,P + O17,P. */
	gr7 = hr7[*ibegin];
/* C13,ALPHA */
/*        GR8 = HR8(IBEGIN) */
/* O16,ALPHA (NOT USED) */
/*        GR9 = HR9(IBEGIN) */
/* C12,ALPHA */
	gr10 = hr10[*ibegin];
/* N14,ALPHA */
/*        GR11 = HR11(IBEGIN) */
/* TRIPLE ALPHA */
	gr12 = hr12[*ibegin];
/* C12,C12 (NOT USED) */
/*        GR13 = HR13(IBEGIN) */
/* BRANCHING RATIO FOR N15,P : */
/* F3 = FRACTION GOING TO C12+ALPHA */
/* F4 = FRACTION GOING TO O16 */
/*        F3 = HF1(IBEGIN) */
/*        F4 = 1.0D0 - F3 */
    } else {
/* USE THE MASS-WEIGHTED AVERAGE RATES FOR THE CZ */
	gr1 = 0.;
	gr2 = 0.;
	gr3 = 0.;
	gr4 = 0.;
	gr5 = 0.;
	gr6 = 0.;
	gr7 = 0.;
/*        GR8 = 0.0D0 */
	gr10 = 0.;
/*        GR11 = 0.0D0 */
	gr12 = 0.;
/*        F3 = 0.0D0 */
	i__1 = *iend;
	for (i__ = *ibegin; i__ <= i__1; ++i__) {
	    gr1 += hs2[i__] * hr1[i__];
	    gr2 += hs2[i__] * hr2[i__];
	    gr3 += hs2[i__] * hr3[i__];
	    gr4 += hs2[i__] * hr4[i__];
	    gr5 += hs2[i__] * hr5[i__];
	    gr6 += hs2[i__] * hr6[i__];
	    gr7 += hs2[i__] * hr7[i__];
/*           GR8 = GR8 + HS2(I)*HR8(I) */
	    gr10 += hs2[i__] * hr10[i__];
/*           GR11 = GR11 + HS2(I)*HR11(I) */
	    gr12 += hs2[i__] * hr12[i__];
/*           F3 = F3 + HS2(I)*HF1(I) */
/* L15: */
	}
	gr1 /= wtsum;
	gr2 /= wtsum;
	gr3 /= wtsum;
	gr4 /= wtsum;
	gr5 /= wtsum;
	gr6 /= wtsum;
	gr7 /= wtsum;
/*        GR8 = GR8/WTSUM */
	gr10 /= wtsum;
/*        GR11 = GR11/WTSUM */
	gr12 /= wtsum;
/*        F3 = F3/WTSUM */
/*        F4 = 1.0D0 - F3 */
    }

/* INITIAL ABUNDANCES OF SPECIES. */

    *x = xsum[0];
    xhe3 = xsum[3];
    y = xsum[1];
    *z__ = xsum[2];
    *xc12 = xsum[4];
    xc13 = xsum[5];
    xn14 = xsum[6];
    *xo16 = xsum[8];
    if (*x > 1e-10 && ht[*ibegin] > ctlim_1.tcut[1]) {
/* FIND EQUILIBRIUM HELIUM-3 ABUNDANCE, USING THE QUADRATIC FORMULA. */
/* THE EQUATION IS -2*R(3,3)*XHE3**2 - R(3,4)*XHE3*XHE4 + R(1,1)X**2 = 0. */
/* Computing 2nd power */
	d__1 = *x;
	r11 = gr1 * (d__1 * d__1);
	r34 = gr3 * y;
/* Computing 2nd power */
	d__1 = r34;
	xhe3e = (sqrt(d__1 * d__1 + gr2 * 8. * r11) - r34) * .25 / gr2;
/* USE THE MINIMUM OF THE CURRENT AND EQUILIBRIUM HE3 ABUNDANCE - */
/* NEEDED TO AVOID SPURIOUSLY HIGH BURNING RATES IN OUTER LAYERS, */
/* WHERE THE TIMESCALE FOR HELIUM-3 TO REACH EQUILIBRIUM IS LONG. */
	xhe3 = min(xhe3,xhe3e);
/* PP BURNING. */
/* Computing 2nd power */
	d__1 = xhe3;
	*dxdt = r11 * -3. + gr2 * 2. * (d__1 * d__1) - r34 * xhe3;
    } else {
	*dxdt = 0.;
	goto L100;
    }
    if (ht[*ibegin] > ctlim_1.tcut[2]) {
/* FIND EQUILIBRIUM C12,C13,N14 ABUNDANCES TREATING CN PROCESSING AS */
/* A CLOSED LOOP. */
	sumcno = *xc12 / 12. + xc13 / 13. + xn14 / 14.;
/* FIND EXPLICIT RATES FOR P+C12,P+C13,P+N14(==R121,R131,R141) */
	r1214 = gr6 / gr4;
	r1314 = gr6 / gr5;
/* IN EQUILIBRIUM WE HAVE */
/* XC12 = XN14{R(1,14)/R(1,12)} */
/* XC13 = XN14{R(1,14)/R(1,13)} */
/* AND FROM CONSERVATION OF SPECIES XC12/12 +XC13/13 + XN14/14 IS UNCHANGED. */
/* EXPRESSING C12 AND C13 AS FUNCTIONS OF N14, SOLVE FOR THE NEW N14 */
/* EQUILIBRIUM ABUNDANCE. */
	xn14 = sumcno / (r1214 / 12. + r1314 / 13. + .071428571428571425);
	*xc12 = xn14 * r1214;
	xc13 = xn14 * r1314;
	*dxdt = *dxdt - gr4 * *x * *xc12 - gr5 * *x * xc13 - gr6 * 2. * *x * 
		xn14 - gr7 * 2. * *x * *xo16;
    }
L100:
/* HELIUM BURNING REACTIONS. */
    if (y > 1e-10 && ht[*ibegin] > ctlim_1.tcut[3]) {
/* Computing 3rd power */
	d__1 = y;
	r3a = gr12 * (d__1 * (d__1 * d__1));
	r412 = gr10 * y * *xc12;
	*dydt = (r412 + r3a * 3.) * -4.;
	*dcdt = (r3a - r412) * 12.;
	*dodt = r412 * 16.;
    } else {
	*dydt = 0.;
	*dcdt = 0.;
	*dodt = 0.;
    }
    return 0;
} /* eqburn_ */

