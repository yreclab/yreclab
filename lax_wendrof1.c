/* lax_wendrof1.f -- translated by f2c (version 20100827).
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

/* Subroutine */ int lax_wendrof1__(doublereal *dt, doublereal *ecod1, 
	doublereal *em, integer *npt, doublereal *stot, doublereal *ex_h__)
{
    /* System generated locals */
    integer i__1;

    /* Local variables */
    static integer i__;
    static doublereal dt2, dex_h__, dez_h__, emass;

/* MHP 3/94 ADDED METAL DIFFUSION */
/* VARIABLES : ECOD1 IS RUN OF DIFFUSION COEFFICIENTS, EM IS RUN OF MASSES, */
/* AND EX_H IS RUN OF CHANGES IN THE HYDROGEN ABUNDANCE. */
    /* Parameter adjustments */
    --ex_h__;
    --em;
    --ecod1;

    /* Function Body */
    dt2 = *dt * .5 * const1_1.c4pi;
/* CENTRAL BOUNDARY CONDITION */
    emass = em[2];
    dex_h__ = dt2 * ecod1[2] / emass;
    ex_h__[1] = dex_h__;
/* GENERAL CASE */
    i__1 = *npt - 2;
    for (i__ = 2; i__ <= i__1; ++i__) {
	emass = em[i__ + 1] - em[i__];
	dex_h__ = dt2 * (ecod1[i__ + 1] - ecod1[i__]) / emass;
	ex_h__[i__] = dex_h__;
/* L10: */
    }
/* SURFACE BOUNDARY CONDITION. */
    emass = *stot - em[*npt - 1];
    dex_h__ = -dt2 * ecod1[*npt - 1] / emass;
    ex_h__[*npt - 1] = dex_h__;
/* METAL DIFFUSION */
    if (gravs3_1.ldifz) {
/* CENTRAL BOUNDARY CONDITION */
	emass = em[2];
	dez_h__ = dt2 * gravez_1.ecod1z[1] / emass;
	gravez_1.ez_h__[0] = dez_h__;
/* GENERAL CASE */
	i__1 = *npt - 2;
	for (i__ = 2; i__ <= i__1; ++i__) {
	    emass = em[i__ + 1] - em[i__];
	    dez_h__ = dt2 * (gravez_1.ecod1z[i__] - gravez_1.ecod1z[i__ - 1]) 
		    / emass;
	    gravez_1.ez_h__[i__ - 1] = dez_h__;
	}
/* SURFACE BOUNDARY CONDITION. */
	emass = *stot - em[*npt - 1];
	dez_h__ = -dt2 * gravez_1.ecod1z[*npt - 2] / emass;
	gravez_1.ez_h__[*npt - 2] = dez_h__;
    }
    return 0;
} /* lax_wendrof1__ */

