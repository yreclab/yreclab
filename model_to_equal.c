/* model_to_equal.f -- translated by f2c (version 20100827).
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
    doublereal fgry, fgrz;
    logical lthoul, ldifz;
} gravs3_;

#define gravs3_1 gravs3_

struct {
    doublereal cod1z[5000], cod2z[5000], qcod1z[5000], qcod2z[5000];
} gravsz_;

#define gravsz_1 gravsz_

struct {
    doublereal ecod1z[5000], ecod1z_h__[5000], ecod2z_h__[5000], eqcod1z_h__[
	    5000], eqcod2z_h__[5000], ez[5000], ez_h__[5000];
} gravez_;

#define gravez_1 gravez_

/* $$$$$$ */
/* Subroutine */ int model_to_equal__(doublereal *cod1, doublereal *cod2, 
	doublereal *hcomp, doublereal *hqpr, doublereal *hru, doublereal *hs1,
	 doublereal *htu, integer *ibegin, integer *iend, integer *m, 
	doublereal *qcod1x, doublereal *qcod2x, doublereal *dr, doublereal *
	ecod1, doublereal *ecod1_h__, doublereal *ecod2_h__, doublereal *em, 
	doublereal *em_h__, doublereal *eqcod1x_h__, doublereal *eqcod2x_h__, 
	doublereal *er, doublereal *ex, doublereal *ex_h__, integer *npt)
{
    /* System generated locals */
    integer i__1, i__2, i__3, i__4;
    doublereal d__1, d__2;

    /* Builtin functions */
    double d_mod(doublereal *, doublereal *);

    /* Local variables */
    static doublereal facderiv[4];
    static integer i__, j, k;
    static doublereal facinterp[4];
    static integer k0, iu;
    static doublereal fx, dr1, dr2, fac1, fac2, delr;
    static integer jmin;
    static doublereal drmin, drtot, tabler[4];
    extern /* Subroutine */ int interp_(doublereal *, doublereal *, 
	    doublereal *, doublereal *);
    static doublereal gridrad;

/* MHP 3/94 ADDED METAL DIFFUSION. */
/*  FIND MINIMUM MODEL POINT SPACING IN RADIUS. */
    /* Parameter adjustments */
    --ex_h__;
    --ex;
    --er;
    --eqcod2x_h__;
    --eqcod1x_h__;
    --em_h__;
    --em;
    --ecod2_h__;
    --ecod1_h__;
    --ecod1;
    --qcod2x;
    --qcod1x;
    --htu;
    --hs1;
    --hru;
    --hqpr;
    hcomp -= 16;
    --cod2;
    --cod1;

    /* Function Body */
    drtot = hru[*iend] - hru[*ibegin];
    drmin = drtot;
    i__1 = *iend;
    for (i__ = *ibegin + 1; i__ <= i__1; ++i__) {
/* Computing MIN */
	d__1 = drmin, d__2 = hru[i__] - hru[i__ - 1];
	drmin = min(d__1,d__2);
/* L7: */
    }
/*  ASSIGN THE MINIMUM NUMBER OF EQUALLY SPACED GRID POINTS SUCH THAT */
/*  DR <= DRMIN. */
    *npt = (integer) (drtot / drmin);
    if (d_mod(&drtot, &drmin) != 0.) {
	++(*npt);
    }
/*  ENSURE THAT NUMBER OF POINTS DOES NOT EXCEED JSON. */
    *npt = min(*npt,5000);
    *dr = drtot / (doublereal) (*npt - 1);
/*  SET UP VECTOR OF EQUALLY SPACED RADII AT ZONE MIDPOINTS. */
    er[1] = hru[*ibegin] + *dr * .5;
    i__1 = *npt - 1;
    for (i__ = 2; i__ <= i__1; ++i__) {
	er[i__] = er[i__ - 1] + *dr;
/* L10: */
    }
/*  NOW USE 4-POINT LAGRANGIAN INTERPOLATION TO FIND RUN OF VARIABLES */
/*  AT EQUALLY SPACED ZONE MIDPOINTS. */

/*  FIRST POINT : LINEAR INTERPOLATION BETWEEN STARTING POINT AND 2ND PT. */
    i__1 = *npt;
    for (iu = 2; iu <= i__1; ++iu) {
	if (hru[iu] >= er[1]) {
	    goto L17;
	}
/* L15: */
    }
    iu = *npt;
L17:
    fx = (er[1] - hru[iu - 1]) / (hru[iu] - hru[iu - 1]);
    em_h__[1] = hs1[iu - 1] + fx * (hs1[iu] - hs1[iu - 1]);
    ecod1_h__[1] = cod1[iu - 1] + fx * (cod1[iu] - cod1[iu - 1]);
    ecod2_h__[1] = cod2[iu - 1] + fx * (cod2[iu] - cod2[iu - 1]);
    eqcod1x_h__[1] = qcod1x[iu - 1] + fx * (qcod1x[iu] - qcod1x[iu - 1]);
    eqcod2x_h__[1] = qcod2x[iu - 1] + fx * (qcod2x[iu] - qcod2x[iu - 1]);
    ex_h__[1] = hcomp[(iu - 1) * 15 + 1] + fx * (hcomp[iu * 15 + 1] - hcomp[(
	    iu - 1) * 15 + 1]);
    if (gravs3_1.ldifz) {
	gravez_1.ecod1z_h__[0] = gravsz_1.cod1z[iu - 2] + fx * (
		gravsz_1.cod1z[iu - 1] - gravsz_1.cod1z[iu - 2]);
	gravez_1.ecod2z_h__[0] = gravsz_1.cod2z[iu - 2] + fx * (
		gravsz_1.cod2z[iu - 1] - gravsz_1.cod2z[iu - 2]);
	gravez_1.eqcod1z_h__[0] = gravsz_1.qcod1z[iu - 2] + fx * (
		gravsz_1.qcod1z[iu - 1] - gravsz_1.qcod1z[iu - 2]);
	gravez_1.eqcod2z_h__[0] = gravsz_1.qcod2z[iu - 2] + fx * (
		gravsz_1.qcod2z[iu - 1] - gravsz_1.qcod2z[iu - 2]);
	gravez_1.ez_h__[0] = hcomp[(iu - 1) * 15 + 8] + fx * (hcomp[iu * 15 + 
		8] - hcomp[(iu - 1) * 15 + 8]);
    }
/*  CENTER DERIVATIVE. */
    dr1 = er[1] - hru[iu - 1];
    dr2 = hru[iu] - er[1];
    if (dr2 > dr1) {
	fac1 = 1.;
	fac2 = dr1 / dr2;
	delr = dr1 * 2.;
    } else if (dr1 > dr2) {
	fac1 = dr2 / dr1;
	fac2 = 1.;
	delr = dr2 * 2.;
    } else {
	fac1 = 1.;
	fac2 = 1.;
	delr = dr1 + dr2;
    }
/*  FOR OTHER POINTS: FIRST FIND 4 NEAREST (IN RADIUS) MODEL POINTS */
/*  AND THEN FIND LAGRANGIAN INTERPOLATION FACTORS. APPLY THEM TO FIND */
/*  MODEL QUANTITIES AT THE EQUALLY SPACED GRID POINTS. */
/*  JMIN IS THE UPPERMOST MODEL POINT ABOVE THE PREVIOUS EQUALLY SPACED */
/*  GRID POINT (IN RADIUS). */
    jmin = *ibegin + 1;
    i__1 = *npt - 1;
    for (i__ = 2; i__ <= i__1; ++i__) {
	i__2 = *iend;
	for (j = jmin; j <= i__2; ++j) {
/*  FIND 4 MODEL POINTS CLOSEST TO THE EQUALLY SPACED GRID POINT. */
	    if (hru[j] >= er[i__]) {
/*  ENSURE THAT FIRST INTERPOLATION POINT NO LESS THAN FIRST MODEL POINT. */
/* Computing MAX */
		i__3 = j - 2;
		k0 = max(i__3,1);
/*  ENSURE THAT LAST INTERPOLATION POINT NO GREATER THAN LAST MODEL POINT. */
/* Computing MIN */
		i__3 = k0, i__4 = *m - 3;
		k0 = min(i__3,i__4);
		jmin = j;
		goto L30;
	    }
/* L20: */
	}
	k0 = *m - 3;
	jmin = *m;
L30:
	for (k = 1; k <= 4; ++k) {
	    tabler[k - 1] = hru[k0 + k - 1];
/* L40: */
	}
	gridrad = er[i__];
/*  FIND 4 POINT LAGRANGIAN INTERPOLATION FACTORS. */
/*  FACINTERP=INTERPOLATION FACTORS FOR POINT GRIDRAD GIVEN THE 4 TABLE */
/*  RADII IN TABLER; FACDERIV=SAME FOR DERIVATIVES AT POINT GRIDRAD. */
	interp_(tabler, facinterp, facderiv, &gridrad);
/*  PERFORM 4 POINT LAGRANGIAN INTERPOLATION FOR DESIRED QUANTITIES: */
/*  MASS WITHIN THE RADIUS ER */
	em_h__[i__] = facinterp[0] * hs1[k0] + facinterp[1] * hs1[k0 + 1] + 
		facinterp[2] * hs1[k0 + 2] + facinterp[3] * hs1[k0 + 3];
/*  D1 */
	ecod1_h__[i__] = facinterp[0] * cod1[k0] + facinterp[1] * cod1[k0 + 1]
		 + facinterp[2] * cod1[k0 + 2] + facinterp[3] * cod1[k0 + 3];
/*  D2 */
	ecod2_h__[i__] = facinterp[0] * cod2[k0] + facinterp[1] * cod2[k0 + 1]
		 + facinterp[2] * cod2[k0 + 2] + facinterp[3] * cod2[k0 + 3];
/*  DERIVATIVE OF D1 WRT X */
	eqcod1x_h__[i__] = facinterp[0] * qcod1x[k0] + facinterp[1] * qcod1x[
		k0 + 1] + facinterp[2] * qcod1x[k0 + 2] + facinterp[3] * 
		qcod1x[k0 + 3];
/*  DERIVATIVE OF D2 WRT X */
	eqcod2x_h__[i__] = facinterp[0] * qcod2x[k0] + facinterp[1] * qcod2x[
		k0 + 1] + facinterp[2] * qcod2x[k0 + 2] + facinterp[3] * 
		qcod2x[k0 + 3];
/*  MASS FRACTION OF HYDROGEN */
	ex_h__[i__] = facinterp[0] * hcomp[k0 * 15 + 1] + facinterp[1] * 
		hcomp[(k0 + 1) * 15 + 1] + facinterp[2] * hcomp[(k0 + 2) * 15 
		+ 1] + facinterp[3] * hcomp[(k0 + 3) * 15 + 1];
	if (gravs3_1.ldifz) {
/*  METAL DIFFUSION-TREATED AS FULLY IONIZED IRON. */
/*  D1 */
	    gravez_1.ecod1z_h__[i__ - 1] = facinterp[0] * gravsz_1.cod1z[k0 - 
		    1] + facinterp[1] * gravsz_1.cod1z[k0] + facinterp[2] * 
		    gravsz_1.cod1z[k0 + 1] + facinterp[3] * gravsz_1.cod1z[k0 
		    + 2];
/*  D2 */
	    gravez_1.ecod2z_h__[i__ - 1] = facinterp[0] * gravsz_1.cod2z[k0 - 
		    1] + facinterp[1] * gravsz_1.cod2z[k0] + facinterp[2] * 
		    gravsz_1.cod2z[k0 + 1] + facinterp[3] * gravsz_1.cod2z[k0 
		    + 2];
/*  DERIVATIVE OF D1 WRT Z */
	    gravez_1.eqcod1z_h__[i__ - 1] = facinterp[0] * gravsz_1.qcod1z[k0 
		    - 1] + facinterp[1] * gravsz_1.qcod1z[k0] + facinterp[2] *
		     gravsz_1.qcod1z[k0 + 1] + facinterp[3] * gravsz_1.qcod1z[
		    k0 + 2];
/*  DERIVATIVE OF D2 WRT Z */
	    gravez_1.eqcod2z_h__[i__ - 1] = facinterp[0] * gravsz_1.qcod2z[k0 
		    - 1] + facinterp[1] * gravsz_1.qcod2z[k0] + facinterp[2] *
		     gravsz_1.qcod2z[k0 + 1] + facinterp[3] * gravsz_1.qcod2z[
		    k0 + 2];
/*  MASS FRACTION OF METALS */
	    gravez_1.ez_h__[i__ - 1] = facinterp[0] * hcomp[k0 * 15 + 8] + 
		    facinterp[1] * hcomp[(k0 + 1) * 15 + 8] + facinterp[2] * 
		    hcomp[(k0 + 2) * 15 + 8] + facinterp[3] * hcomp[(k0 + 3) *
		     15 + 8];
	}
/* L50: */
    }
/*  SET UP VECTOR OF EQUALLY SPACED RADII AT ZONE CENTERS. */
    er[1] = hru[*ibegin];
    i__1 = *npt;
    for (i__ = 2; i__ <= i__1; ++i__) {
	er[i__] = er[i__ - 1] + *dr;
/* L60: */
    }
/*  NOW USE 4-POINT LAGRANGIAN INTERPOLATION TO FIND RUN OF VARIABLES */
/*  AT EQUALLY SPACED ZONE CENTERS. */

/*  FIRST POINT : BY DEFINITION, AT STARTING POINT. */
    em[1] = hs1[*ibegin];
    ex[1] = hcomp[*ibegin * 15 + 1];
    ecod1[1] = cod1[*ibegin];
    if (gravs3_1.ldifz) {
	gravez_1.ez[0] = hcomp[*ibegin * 15 + 8];
	gravez_1.ecod1z[0] = gravsz_1.cod1z[*ibegin - 1];
    }
/*  FOR OTHER POINTS: FIRST FIND 4 NEAREST (IN RADIUS) MODEL POINTS */
/*  AND THEN FIND LAGRANGIAN INTERPOLATION FACTORS. APPLY THEM TO FIND */
/*  MODEL QUANTITIES AT THE EQUALLY SPACED GRID POINTS. */
/*  JMIN IS THE UPPERMOST MODEL POINT ABOVE THE PREVIOUS EQUALLY SPACED */
/*  GRID POINT (IN RADIUS). */
    jmin = *ibegin + 1;
    i__1 = *npt - 1;
    for (i__ = 2; i__ <= i__1; ++i__) {
	i__2 = *iend;
	for (j = jmin; j <= i__2; ++j) {
/*  FIND 4 MODEL POINTS CLOSEST TO THE EQUALLY SPACED GRID POINT. */
	    if (hru[j] >= er[i__]) {
/*  ENSURE THAT FIRST INTERPOLATION POINT NO LESS THAN FIRST MODEL POINT. */
/* Computing MAX */
		i__3 = j - 2;
		k0 = max(i__3,1);
/*  ENSURE THAT LAST INTERPOLATION POINT NO GREATER THAN LAST MODEL POINT. */
/* Computing MIN */
		i__3 = k0, i__4 = *m - 3;
		k0 = min(i__3,i__4);
		jmin = j;
		goto L90;
	    }
/* L80: */
	}
	k0 = *m - 3;
	jmin = *m;
L90:
	for (k = 1; k <= 4; ++k) {
	    tabler[k - 1] = hru[k0 + k - 1];
/* L100: */
	}
	gridrad = er[i__];
/*  FIND 4 POINT LAGRANGIAN INTERPOLATION FACTORS. */
/*  FACINTERP=INTERPOLATION FACTORS FOR POINT GRIDRAD GIVEN THE 4 TABLE */
/*  RADII IN TABLER; FACDERIV=SAME FOR DERIVATIVES AT POINT GRIDRAD. */
	interp_(tabler, facinterp, facderiv, &gridrad);
/*  PERFORM 4 POINT LAGRANGIAN INTERPOLATION FOR DESIRED QUANTITIES: */
/*  MASS WITHIN THE RADIUS ER */
	em[i__] = facinterp[0] * hs1[k0] + facinterp[1] * hs1[k0 + 1] + 
		facinterp[2] * hs1[k0 + 2] + facinterp[3] * hs1[k0 + 3];
/*  D1 */
	ecod1[i__] = facinterp[0] * cod1[k0] + facinterp[1] * cod1[k0 + 1] + 
		facinterp[2] * cod1[k0 + 2] + facinterp[3] * cod1[k0 + 3];
/*  MASS FRACTION OF HYDROGEN */
	ex[i__] = facinterp[0] * hcomp[k0 * 15 + 1] + facinterp[1] * hcomp[(
		k0 + 1) * 15 + 1] + facinterp[2] * hcomp[(k0 + 2) * 15 + 1] + 
		facinterp[3] * hcomp[(k0 + 3) * 15 + 1];
/* METAL DIFFUSION */
	if (gravs3_1.ldifz) {
/*  D1 */
	    gravez_1.ecod1z[i__ - 1] = facinterp[0] * gravsz_1.cod1z[k0 - 1] 
		    + facinterp[1] * gravsz_1.cod1z[k0] + facinterp[2] * 
		    gravsz_1.cod1z[k0 + 1] + facinterp[3] * gravsz_1.cod1z[k0 
		    + 2];
/*  MASS FRACTION OF METALS */
	    gravez_1.ez[i__ - 1] = facinterp[0] * hcomp[k0 * 15 + 8] + 
		    facinterp[1] * hcomp[(k0 + 1) * 15 + 8] + facinterp[2] * 
		    hcomp[(k0 + 2) * 15 + 8] + facinterp[3] * hcomp[(k0 + 3) *
		     15 + 8];
	}
/* L70: */
    }
/*  LAST POINT : BY DEFINITION, AT ENDING POINT. */
    em[*npt] = hs1[*iend];
    ex[*npt] = hcomp[*iend * 15 + 1];
    ecod1[*npt] = cod1[*iend];
    if (gravs3_1.ldifz) {
	gravez_1.ez[*npt - 1] = hcomp[*iend * 15 + 8];
	gravez_1.ecod1z[*npt - 1] = gravsz_1.cod1z[*iend - 1];
    }
    return 0;
} /* model_to_equal__ */

