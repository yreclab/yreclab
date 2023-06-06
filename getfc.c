/* getfc.f -- translated by f2c (version 20100827).
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
    doublereal alm[5000], delami[5000], delmi[5000], dm[5000], epsilm[5000], 
	    hgm[5000], hs3[5000], pm[5000], qdtm[5000], rm[5000], tm[5000];
} intvar_;

#define intvar_1 intvar_

struct {
    doublereal fw, fc, fo, fes, fgsf, fmu, fss, rcrit;
} vmult_;

#define vmult_1 vmult_

struct {
    doublereal vfc[5000];
    logical lvfc, ldifad;
} varfc_;

#define varfc_1 varfc_


/* $$$$$$GETFC */

/* Subroutine */ int getfc_(doublereal *hd, doublereal *hru, doublereal *hv, 
	integer *imin, integer *imax, doublereal *omega)
{
    /* System generated locals */
    integer i__1;
    doublereal d__1, d__2;

    /* Builtin functions */
    double exp(doublereal);

    /* Local variables */
    static integer i__;
    static doublereal v[5000], fx, vm, wm, vp, dudr, rhor, dr2vm, dr2vp, 
	    alpha[5000], ftest, drhor2;

/* INPUT VARIABLES : */
/* HD - LOG10 OF DENSITY(GM/CM**3) AT ZONE CENTERS. */
/* RM - UNLOGGED RUN OF RADII AT ZONE EDGES. */
/* HRU - UNLOGGED RUN OF RADII AT ZONE CENTERS. */
/* HV - UNLOGGED RUN OF DIFFUSION VELOCITIES AT ZONE EDGES. */
/* IMIN,IMAX - STARTING AND ENDING SHELLS. */
/* OMEGA - RUN OF ANGULAR VELOCITIES AT ZONE CENTERS. */
/* OUTPUT VARIABLE : */
/* VFC - RATIO OF DIFFUSION COEFFICIENT FOR MIXING TO THAT FOR */
/*       ANGULAR MOMENTUM TRANSPORT. */
/* THIS SUBROUTINE SOLVES FOR THE VARIABLE FC USING THE */
/* PRESCRIPTION OF ZAHN (1992). */
/* FC = MIN (1, C/30*U/(2V-ALPHA*U), WHERE ALPHA=1/2 D(LN J/M)/D LN R */
/* AND V = 1/(6*RHO*R) *D/DR(RHO* R**2 * U) (U = DIFFUSION VELOCITY). */

/* IF FC = 0, SKIP CALCULATION (NO MIXING). */
    /* Parameter adjustments */
    --omega;
    --hv;
    --hru;
    --hd;

    /* Function Body */
    if (vmult_1.fc <= 0.) {
	i__1 = *imax;
	for (i__ = *imin; i__ <= i__1; ++i__) {
	    varfc_1.vfc[i__ - 1] = 0.;
	}
	goto L9999;
    }
/* DETERMINE ALPHA. */
    i__1 = *imax;
    for (i__ = *imin; i__ <= i__1; ++i__) {
	wm = (omega[i__] + omega[i__ - 1]) * .5;
/* Computing 2nd power */
	d__1 = hru[i__];
/* Computing 2nd power */
	d__2 = hru[i__ - 1];
	alpha[i__ - 1] = (omega[i__] * (d__1 * d__1) - omega[i__ - 1] * (d__2 
		* d__2)) / (hru[i__] - hru[i__ - 1]) / (wm * intvar_1.rm[i__ 
		- 1]);
    }
/* DETERMINE 2V. */
    fx = (hru[*imin] - intvar_1.rm[*imin - 1]) / (intvar_1.rm[*imin] - 
	    intvar_1.rm[*imin - 1]);
    vm = hv[*imin] + fx * (hv[*imin + 1] - hv[*imin]);
/* Computing 2nd power */
    d__1 = hru[*imin];
    dr2vm = exp(const1_1.cln * hd[*imin]) * (d__1 * d__1) * vm;
    i__1 = *imax - 1;
    for (i__ = *imin + 1; i__ <= i__1; ++i__) {
	fx = (hru[i__] - intvar_1.rm[i__ - 1]) / (intvar_1.rm[i__] - 
		intvar_1.rm[i__ - 1]);
	vp = hv[i__] + fx * (hv[i__ + 1] - hv[i__]);
/* Computing 2nd power */
	d__1 = hru[i__];
	dr2vp = exp(const1_1.cln * hd[i__]) * (d__1 * d__1) * vp;
	rhor = intvar_1.dm[i__ - 1] * intvar_1.rm[i__ - 1];
	v[i__ - 1] = const1_1.cc13 * (dr2vp - dr2vm) / rhor / (hru[i__] - hru[
		i__ - 1]);
	dr2vm = dr2vp;
    }
/* FOR FIRST AND LAST SHELLS, CALCULATE U*D/DR(RHO*R**2) AND ASSUME */
/* DU/DR = VALUE DERIVED FROM THE LAST NEIGHBOR SHELL WITH NONZERO V. */
    rhor = intvar_1.dm[*imin - 1] * intvar_1.rm[*imin - 1];
/* Computing 2nd power */
    d__1 = hru[*imin];
/* Computing 2nd power */
    d__2 = hru[*imin - 1];
    drhor2 = (exp(const1_1.cln * hd[*imin]) * (d__1 * d__1) - exp(
	    const1_1.cln * hd[*imin - 1]) * (d__2 * d__2)) / (hru[*imin] - 
	    hru[*imin - 1]);
    dudr = (hv[*imin + 1] - hv[*imin]) / (intvar_1.rm[*imin] - intvar_1.rm[*
	    imin - 1]);
    v[*imin - 1] = const1_1.cc13 * (hv[*imin] * drhor2 / rhor + intvar_1.rm[*
	    imin - 1] * dudr);
    rhor = intvar_1.dm[*imax - 1] * intvar_1.rm[*imax - 1];
/* Computing 2nd power */
    d__1 = hru[*imax];
/* Computing 2nd power */
    d__2 = hru[*imax - 1];
    drhor2 = (exp(const1_1.cln * hd[*imax]) * (d__1 * d__1) - exp(
	    const1_1.cln * hd[*imax - 1]) * (d__2 * d__2)) / (hru[*imax] - 
	    hru[*imax - 1]);
    dudr = (hv[*imax] - hv[*imax - 1]) / (intvar_1.rm[*imax - 1] - 
	    intvar_1.rm[*imax - 2]);
    v[*imax - 1] = const1_1.cc13 * (hv[*imax] * drhor2 / rhor + intvar_1.rm[*
	    imax - 1] * dudr);
/* NOW COMPUTE RUN OF FC; THIS ASSUMES THAT FC = SAME FOR ALL */
/* MECHANISMS AND IS LIMITED TO A MAXIMUM OF 1. */
    i__1 = *imax;
    for (i__ = *imin; i__ <= i__1; ++i__) {
	if (hv[i__] <= 0.) {
	    varfc_1.vfc[i__ - 1] = 0.;
	} else {
/* Computing MAX */
	    d__2 = (d__1 = v[i__ - 1] - alpha[i__ - 1] * hv[i__], abs(d__1)) /
		     hv[i__];
	    ftest = max(d__2,vmult_1.fc);
	    varfc_1.vfc[i__ - 1] = vmult_1.fc / ftest;
	}
    }
L9999:
    return 0;
} /* getfc_ */

