/* lax_wendrof2.f -- translated by f2c (version 20061008).
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
    doublereal fgry, fgrz;
    logical lthoul, ldifz;
} gravs3_;

#define gravs3_1 gravs3_

struct {
    doublereal ecod1z[5000], ecod1z_h__[5000], ecod2z_h__[5000], eqcod1z_h__[
	    5000], eqcod2z_h__[5000], ez[5000], ez_h__[5000];
} gravez_;

#define gravez_1 gravez_

/* $$$$$$ */
/* Subroutine */ int lax_wendrof2__(doublereal *dt, doublereal *ecod1_h__, 
	doublereal *em_h__, doublereal *ex, integer *npt, doublereal *stot, 
	logical *ldoli)
{
    /* System generated locals */
    integer i__1;

    /* Local variables */
    static integer i__;
    static doublereal dt2, dex, dez, emass;

/* MHP 3/94 ADDED METAL DIFFUSION */
    /* Parameter adjustments */
    --ex;
    --em_h__;
    --ecod1_h__;

    /* Function Body */
    dt2 = *dt * const1_1.c4pi;
/* CENTRAL BOUNDARY CONDITION */
    emass = em_h__[1];
    dex = dt2 * ecod1_h__[1] / emass;
    ex[1] += dex;
/*    99 FORMAT(5X,1P2E15.7) */
/* GENERAL CASE */
    i__1 = *npt - 1;
    for (i__ = 2; i__ <= i__1; ++i__) {
	emass = em_h__[i__] - em_h__[i__ - 1];
	dex = dt2 * (ecod1_h__[i__] - ecod1_h__[i__ - 1]) / emass;
	ex[i__] += dex;
/* L10: */
    }
/* SURFACE BOUNDARY CONDITION. */
    emass = *stot - em_h__[*npt - 1];
    dex = -dt2 * ecod1_h__[*npt - 1] / emass;
    ex[*npt] += dex;
/* MHP 3/94 ADDED METAL DIFFUSION. */
    if (gravs3_1.ldifz && ! (*ldoli)) {
	emass = em_h__[1];
	dez = dt2 * gravez_1.ecod1z_h__[0] / emass;
	gravez_1.ez[0] += dez;
/* GENERAL CASE */
	i__1 = *npt - 1;
	for (i__ = 2; i__ <= i__1; ++i__) {
	    emass = em_h__[i__] - em_h__[i__ - 1];
	    dez = dt2 * (gravez_1.ecod1z_h__[i__ - 1] - gravez_1.ecod1z_h__[
		    i__ - 2]) / emass;
	    gravez_1.ez[i__ - 1] += dez;
	}
/* SURFACE BOUNDARY CONDITION. */
	emass = *stot - em_h__[*npt - 1];
	dez = -dt2 * gravez_1.ecod1z_h__[*npt - 2] / emass;
	gravez_1.ez[*npt - 1] += dez;
    }
    return 0;
} /* lax_wendrof2__ */

