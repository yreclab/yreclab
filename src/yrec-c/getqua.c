/* getqua.f -- translated by f2c (version 20061008).
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
    doublereal a[5000], b[5000], c__[5000], d__[5000], u[5000], gama[5000];
} tridi_;

#define tridi_1 tridi_

struct {
    doublereal quad[5000], gg[5000];
} quadru_;

#define quadru_1 quadru_

/* Subroutine */ int getqua_(doublereal *hd, doublereal *hg, doublereal *hru, 
	doublereal *omega, integer *m)
{
    /* System generated locals */
    integer i__1;
    doublereal d__1, d__2;

    /* Builtin functions */
    double exp(doublereal);
    /* Subroutine */ void s_stop(char *, ftnlen);

    /* Local variables */
    static integer i__, j;
    static doublereal dr, fx, dw2[5000], fac, bet, fmi, dri, fpl, drmi, drho, 
	    drpl, rplu, c4pig, drhow2;

/* SOLVE FOR THE QUADRUPOLE MOMENT OF A ROTATING STAR, USING THE */
/* SWEET(1950) FORMULATION AS GIVEN IN ZAHN(1992). */
/* WE ARE SOLVING THE EQUATION */
/* 1/R D**2/DR2 (R*QUAD) -6*QUAD/R**2 - 4*PI*G*RHO*D(RHO)/DP * QUAD = */
/*  -4/3*PI*G*R**2/(GM/R**2) * D/DR (RHO*OMEGA**2) */
/* THIS CAN BE EXPRESSED AS D**2/DR2(QUAD) + 2/R DQUAD/DR -6*QUAD/R**2 */
/* +4*PI*G*RHO*QUAD = 4*PI*G*RHO*R**2 *(OMEGA**2 - 2*OMEGA/G *DOMEGA/DR) */
/* USING HYDROSTATIC EQUILIBRIUM AND THE IDEAL GAS LAW */
/* D RHO/DR = DP/DR = -RHO*G. */
/* THIS DEFINES A TRIDIAGONAL MATRIX SYSTEM OF THE FORM */
/* A*QUAD(I-1)+B*QUAD(I)+C*QUAD(I+1) = D, WHICH CAN BE SOLVED IN */
/* THE STANDARD WAY FOR THE RUN OF QUAD(I) WITH APPROPRIATE BOUNDARY */
/* CONDITIONS.  THE CENTRAL B.C. IS THAT QUAD(0)=0; THE SURFACE B.C. */
/* IS THAT THERE IS NO CONTRIBUTION TO THE QUADRUPOLE FROM OUTSIDE THE */
/* FINAL SHELL, SUCH THAT QUAD(I) VARIES AS 1/R**4. */
    /* Parameter adjustments */
    --omega;
    --hru;
    --hg;
    --hd;

    /* Function Body */
    i__1 = *m;
    for (i__ = 1; i__ <= i__1; ++i__) {
/* Computing 2nd power */
	d__1 = omega[i__];
	dw2[i__ - 1] = exp(const1_1.cln * hd[i__]) * (d__1 * d__1);
    }
    c4pig = exp(const1_1.cln * (const1_1.c4pil + const2_1.cgl));
/* CENTER NUMERICAL DERIVATIVES, USING THE SMALLER OF THE LEFT AND */
/* RIGHT HANDED INTERVALS. */
/* Computing MIN */
    d__1 = hru[1], d__2 = hru[2] - hru[1];
    dr = min(d__1,d__2);
    fpl = dr / (hru[2] - hru[1]);
    fmi = dr / hru[1];
/* Computing 2nd power */
    d__1 = dr;
    fac = 1. / (d__1 * d__1);
    dri = 1. / dr / hru[1];
/* CENTRAL BOUNDARY CONDITION : QUADRUPOLE GOES TO ZERO. */
    tridi_1.a[0] = 0.;
    drho = (exp(const1_1.cln * hd[2]) - exp(const1_1.cln * hd[1])) / dr;
/* Computing 2nd power */
    d__1 = hru[1];
    tridi_1.b[0] = -fac * (fpl + fmi) + dri * (fmi - fpl) - 6. / (d__1 * d__1)
	     - c4pig * drho / hg[1];
    tridi_1.c__[0] = fpl * (fac + dri);
/* Computing 2nd power */
    d__1 = hru[1] * omega[1];
    tridi_1.d__[0] = -c4pig * drho * (d__1 * d__1) / 3. / hg[1];
/* GENERAL CASE : SECOND DERIVATIVE NUMERICALLY DIFFERENTIATED AS */

    i__1 = *m - 1;
    for (i__ = 2; i__ <= i__1; ++i__) {
	drpl = hru[i__ + 1] - hru[i__];
	drmi = hru[i__] - hru[i__ - 1];
	dr = min(drmi,drpl);
	fpl = dr / drpl;
	fmi = dr / drmi;
/* Computing 2nd power */
	d__1 = dr;
	fac = 1. / (d__1 * d__1);
	dri = 1. / dr / hru[i__];
	drho = (fpl * exp(const1_1.cln * hd[i__ + 1]) + (fmi - fpl) * exp(
		const1_1.cln * hd[i__]) - fmi * exp(const1_1.cln * hd[i__])) *
		 .5 / dr;
	tridi_1.a[i__ - 1] = fmi * (fac - dri);
/* Computing 2nd power */
	d__1 = hru[i__];
	tridi_1.b[i__ - 1] = -fac * (fpl + fmi) + dri * (fmi - fpl) - 6. / (
		d__1 * d__1) - c4pig * drho / hg[i__];
	tridi_1.c__[i__ - 1] = fpl * (fac + dri);
	drhow2 = (fpl * dw2[i__] + (fmi - fpl) * dw2[i__ - 1] - fmi * dw2[i__ 
		- 2]) * .5 / dr;
/* Computing 2nd power */
	d__1 = hru[i__];
	tridi_1.d__[i__ - 1] = -drhow2 * c4pig * (d__1 * d__1) / 3. / hg[i__];
    }
/* SURFACE B.C. D PHI/DR + 3 PHI/R = 0 */
/* THE SECOND AND THIRD TERMS IN THE EXPRESSION CANCEL IN THIS CASE. */
/* OUTSIDE THE STAR PHI(R) = PHI(RSTAR)*(RSTAR/R)**3. */
    dr = hru[*m] - hru[*m - 1];
    rplu = hru[*m] + dr;
/* Computing 3rd power */
    d__1 = hru[*m] / rplu;
    fx = d__1 * (d__1 * d__1);
/* Computing 2nd power */
    d__1 = dr;
    fac = 1. / (d__1 * d__1);
    tridi_1.a[*m - 1] = fac;
/* Computing 2nd power */
    d__1 = hru[*m];
    tridi_1.b[*m - 1] = (fx - 2.) * fac - 12. / (d__1 * d__1);
    tridi_1.c__[*m - 1] = 0.;
    tridi_1.d__[*m - 1] = 0.;
/*  SOLUTION OF SYSTEM FROM NUMERICAL RECIPES. */
    if (tridi_1.b[0] == 0.) {
	s_stop("", (ftnlen)0);
    }
    bet = tridi_1.b[0];
    tridi_1.u[0] = tridi_1.d__[0] / bet;
    i__1 = *m;
    for (j = 2; j <= i__1; ++j) {
	tridi_1.gama[j - 1] = tridi_1.c__[j - 2] / bet;
	bet = tridi_1.b[j - 1] - tridi_1.a[j - 1] * tridi_1.gama[j - 1];
	if (bet == 0.) {
	    s_stop("", (ftnlen)0);
	}
	tridi_1.u[j - 1] = (tridi_1.d__[j - 1] - tridi_1.a[j - 1] * tridi_1.u[
		j - 2]) / bet;
    }
/* BACKSUBSTITUTION. */
    for (j = *m - 1; j >= 1; --j) {
	tridi_1.u[j - 1] -= tridi_1.gama[j] * tridi_1.u[j];
    }
    i__1 = *m;
    for (i__ = 1; i__ <= i__1; ++i__) {
	quadru_1.quad[i__ - 1] = tridi_1.u[i__ - 1];
	quadru_1.gg[i__ - 1] = hg[i__];
    }
    return 0;
} /* getqua_ */

