/* microdiff_mte.f -- translated by f2c (version 20061008).
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
    logical lnewdif, ldifli;
} gravs4_;

#define gravs4_1 gravs4_

struct {
    doublereal sesum[5000], seg[35000]	/* was [7][5000] */, sbeta[5000], 
	    seta[5000];
    logical locons[5000];
    doublereal so[5000], sdel[15000]	/* was [3][5000] */, sfxion[15000]	
	    /* was [3][5000] */, svel[5000], scp[5000];
} scrtch_;

#define scrtch_1 scrtch_

/* Table of constant values */

static integer c__9 = 9;
static integer c__1 = 1;

/* $$$$$$ */
/*       SUBROUTINE MICRODIFF_MTE(NLIGHT,CSLIGHT,HCOMP,HQPR,HRU,HS1,HTU,IBEGIN, */
/*      *               IEND,M,DR,NPT,LC,ODEN,OTEM,EM,ER,EDEN,ETEM,EHQPR,EDELR,  # KC 2025-05-31 */
/* Subroutine */ int microdiff_mte__(integer *nlight, integer *cslight, 
	doublereal *hcomp, doublereal *hqpr, doublereal *hru, doublereal *hs1,
	 integer *ibegin, integer *iend, integer *m, doublereal *dr, integer *
	npt, doublereal *oden, doublereal *otem, doublereal *em, doublereal *
	er, doublereal *eden, doublereal *etem, doublereal *ehqpr, doublereal 
	*edelr, doublereal *ex, doublereal *ey, doublereal *ez, doublereal *
	eli, doublereal *em_h__, doublereal *er_h__, doublereal *eden_h__, 
	doublereal *etem_h__, doublereal *ehqpr_h__, doublereal *edelr_h__, 
	doublereal *ex_h__, doublereal *ey_h__, doublereal *ez_h__, 
	doublereal *eli_h__)
{
    /* System generated locals */
    integer eli_dim1, eli_offset, eli_h_dim1, eli_h_offset, i__1, i__2, i__3, 
	    i__4;
    doublereal d__1, d__2;

    /* Builtin functions */
    double d_mod(doublereal *, doublereal *);
    integer s_wsle(cilist *), do_lio(integer *, integer *, char *, ftnlen), 
	    e_wsle(void);

    /* Local variables */
    static doublereal facderiv[4];
    static integer halfjson, i__, j, k;
    static doublereal facinterp[4];
    static integer k0, ii, kk, iu;
    static doublereal fx;
    static integer jmin;
    static doublereal drmin, drtot, tabler[4];
    extern /* Subroutine */ int interp_(doublereal *, doublereal *, 
	    doublereal *, doublereal *);
    static integer istart;
    static doublereal gridrad;

    /* Fortran I/O blocks */
    static cilist io___6 = { 0, 6, 0, 0, 0 };


/* MHP 3/94 ADDED METAL DIFFUSION. */
/*       DIMENSION HCOMP(15,JSON),HQPR(JSON),HRU(JSON),HS1(JSON),HTU(JSON),  ! KC 2025-05-31 */
/* KC 2025-05-30 fixed -Wconversion */
/*      *          EY_H(JSON),EZ_H(JSON),ELI_H(NLIGHT,JSON),CSLIGHT(NLIGHT), */
/*  FIND MINIMUM MODEL POINT SPACING IN RADIUS. */
    /* Parameter adjustments */
    eli_h_dim1 = *nlight;
    eli_h_offset = 1 + eli_h_dim1;
    eli_h__ -= eli_h_offset;
    eli_dim1 = *nlight;
    eli_offset = 1 + eli_dim1;
    eli -= eli_offset;
    --cslight;
    hcomp -= 16;
    --hqpr;
    --hru;
    --hs1;
    --oden;
    --otem;
    --em;
    --er;
    --eden;
    --etem;
    --ehqpr;
    --edelr;
    --ex;
    --ey;
    --ez;
    --em_h__;
    --er_h__;
    --eden_h__;
    --etem_h__;
    --ehqpr_h__;
    --edelr_h__;
    --ex_h__;
    --ey_h__;
    --ez_h__;

    /* Function Body */
    drtot = hru[*iend] - hru[*ibegin];
    drmin = drtot;
/*  ID THE MINIMUM SPACING IN THE 20 LAYERS BELOW THE SURFACE CZ. */
/* Computing MAX */
    i__1 = *iend - 20, i__2 = *ibegin + 1;
    istart = max(i__1,i__2);
    i__1 = *iend;
    for (i__ = istart; i__ <= i__1; ++i__) {
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
/* JVS add additional trap to deal with models with NPT=1 */
    if (*npt == 1) {
	++(*npt);
    }
/*  ENSURE THAT NUMBER OF POINTS DOES NOT EXCEED JSON. */
    halfjson = 5000;
    *npt = min(*npt,halfjson);
    *dr = drtot / (doublereal) (*npt - 1);
/*  SET UP VECTOR OF EQUALLY SPACED RADII AT ZONE MIDPOINTS. */
    er_h__[1] = hru[*ibegin] + *dr * .5;
/* JVS added logic trap (IF statement) */
    if (*npt == 2) {
	er_h__[2] = er_h__[1] + *dr;
    } else {
	i__1 = *npt - 1;
	for (i__ = 2; i__ <= i__1; ++i__) {
/* old piece */
	    if (i__ - 1 == 0) {
		s_wsle(&io___6);
		do_lio(&c__9, &c__1, "mte line 47", (ftnlen)11);
		e_wsle();
	    }
	    er_h__[i__] = er_h__[i__ - 1] + *dr;
/* old piece */
/* L10: */
	}
/* old piece */
    }
/*  NOW USE 4-POINT LAGRANGIAN INTERPOLATION TO FIND RUN OF VARIABLES */
/*  AT EQUALLY SPACED ZONE MIDPOINTS. */

/*  FIRST POINT : LINEAR INTERPOLATION BETWEEN STARTING POINT AND 2ND PT. */
    i__1 = *npt;
    for (iu = 2; iu <= i__1; ++iu) {
	if (hru[iu] >= er_h__[1]) {
	    goto L17;
	}
/* L15: */
    }
    iu = *npt;
L17:
    fx = (er_h__[1] - hru[iu - 1]) / (hru[iu] - hru[iu - 1]);
    em_h__[1] = hs1[iu - 1] + fx * (hs1[iu] - hs1[iu - 1]);
    eden_h__[1] = oden[iu - 1] + fx * (oden[iu] - oden[iu - 1]);
    etem_h__[1] = otem[iu - 1] + fx * (otem[iu] - otem[iu - 1]);
    ehqpr_h__[1] = hqpr[iu - 1] + fx * (hqpr[iu] - hqpr[iu - 1]);
    edelr_h__[1] = scrtch_1.sdel[(iu - 1) * 3 - 2] + fx * (scrtch_1.sdel[iu * 
	    3 - 2] - scrtch_1.sdel[(iu - 1) * 3 - 2]);
    ex_h__[1] = hcomp[(iu - 1) * 15 + 1] + fx * (hcomp[iu * 15 + 1] - hcomp[(
	    iu - 1) * 15 + 1]);
    ey_h__[1] = hcomp[(iu - 1) * 15 + 2] + fx * (hcomp[iu * 15 + 2] - hcomp[(
	    iu - 1) * 15 + 2]);
    ez_h__[1] = hcomp[(iu - 1) * 15 + 3] + fx * (hcomp[iu * 15 + 3] - hcomp[(
	    iu - 1) * 15 + 3]);
    if (gravs4_1.ldifli) {
	i__1 = *nlight;
	for (kk = 1; kk <= i__1; ++kk) {
	    ii = cslight[kk];
	    eli_h__[kk + eli_h_dim1] = hcomp[ii + (iu - 1) * 15] + fx * (
		    hcomp[ii + iu * 15] - hcomp[ii + (iu - 1) * 15]);
	}
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
	    if (hru[j] >= er_h__[i__]) {
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
	gridrad = er_h__[i__];
/*  FIND 4 POINT LAGRANGIAN INTERPOLATION FACTORS. */
/*  FACINTERP=INTERPOLATION FACTORS FOR POINT GRIDRAD GIVEN THE 4 TABLE */
/*  RADII IN TABLER; FACDERIV=SAME FOR DERIVATIVES AT POINT GRIDRAD. */
	interp_(tabler, facinterp, facderiv, &gridrad);
/*  PERFORM 4 POINT LAGRANGIAN INTERPOLATION FOR DESIRED QUANTITIES: */
/*  MASS WITHIN THE RADIUS ER */
	em_h__[i__] = facinterp[0] * hs1[k0] + facinterp[1] * hs1[k0 + 1] + 
		facinterp[2] * hs1[k0 + 2] + facinterp[3] * hs1[k0 + 3];
/*  RELAVENT PHYSICAL VARIABLES */
	eden_h__[i__] = facinterp[0] * oden[k0] + facinterp[1] * oden[k0 + 1] 
		+ facinterp[2] * oden[k0 + 2] + facinterp[3] * oden[k0 + 3];
	etem_h__[i__] = facinterp[0] * otem[k0] + facinterp[1] * otem[k0 + 1] 
		+ facinterp[2] * otem[k0 + 2] + facinterp[3] * otem[k0 + 3];
	ehqpr_h__[i__] = facinterp[0] * hqpr[k0] + facinterp[1] * hqpr[k0 + 1]
		 + facinterp[2] * hqpr[k0 + 2] + facinterp[3] * hqpr[k0 + 3];
	edelr_h__[i__] = facinterp[0] * scrtch_1.sdel[k0 * 3 - 2] + facinterp[
		1] * scrtch_1.sdel[(k0 + 1) * 3 - 2] + facinterp[2] * 
		scrtch_1.sdel[(k0 + 2) * 3 - 2] + facinterp[3] * 
		scrtch_1.sdel[(k0 + 3) * 3 - 2];
/*  MASS FRACTION OF HYDROGEN */
	ex_h__[i__] = facinterp[0] * hcomp[k0 * 15 + 1] + facinterp[1] * 
		hcomp[(k0 + 1) * 15 + 1] + facinterp[2] * hcomp[(k0 + 2) * 15 
		+ 1] + facinterp[3] * hcomp[(k0 + 3) * 15 + 1];
/*  MASS FRACTION OF HELIUM */
	ey_h__[i__] = facinterp[0] * hcomp[k0 * 15 + 2] + facinterp[1] * 
		hcomp[(k0 + 1) * 15 + 2] + facinterp[2] * hcomp[(k0 + 2) * 15 
		+ 2] + facinterp[3] * hcomp[(k0 + 3) * 15 + 2];
/*  MASS FRACTION OF METALS */
	ez_h__[i__] = facinterp[0] * hcomp[k0 * 15 + 3] + facinterp[1] * 
		hcomp[(k0 + 1) * 15 + 3] + facinterp[2] * hcomp[(k0 + 2) * 15 
		+ 3] + facinterp[3] * hcomp[(k0 + 3) * 15 + 3];
/*  MASS FRACTION OF LIGHT ELEMENTS */
	if (gravs4_1.ldifli) {
	    i__2 = *nlight;
	    for (kk = 1; kk <= i__2; ++kk) {
		ii = cslight[kk];
		eli_h__[kk + i__ * eli_h_dim1] = facinterp[0] * hcomp[ii + k0 
			* 15] + facinterp[1] * hcomp[ii + (k0 + 1) * 15] + 
			facinterp[2] * hcomp[ii + (k0 + 2) * 15] + facinterp[
			3] * hcomp[ii + (k0 + 3) * 15];
	    }
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
/* G Somers; added interpolation for Xfrac, Rho, T, and HQPR. */
    em[1] = hs1[*ibegin];
    eden[1] = oden[*ibegin];
    etem[1] = otem[*ibegin];
    ehqpr[1] = hqpr[*ibegin];
    edelr[1] = scrtch_1.sdel[*ibegin * 3 - 2];
    ex[1] = hcomp[*ibegin * 15 + 1];
    ey[1] = hcomp[*ibegin * 15 + 2];
    ez[1] = hcomp[*ibegin * 15 + 3];
    if (gravs4_1.ldifli) {
	i__1 = *nlight;
	for (kk = 1; kk <= i__1; ++kk) {
	    ii = cslight[kk];
	    eli[kk + eli_dim1] = hcomp[ii + *ibegin * 15];
	}
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
	eden[i__] = facinterp[0] * oden[k0] + facinterp[1] * oden[k0 + 1] + 
		facinterp[2] * oden[k0 + 2] + facinterp[3] * oden[k0 + 3];
	etem[i__] = facinterp[0] * otem[k0] + facinterp[1] * otem[k0 + 1] + 
		facinterp[2] * otem[k0 + 2] + facinterp[3] * otem[k0 + 3];
	ehqpr[i__] = facinterp[0] * hqpr[k0] + facinterp[1] * hqpr[k0 + 1] + 
		facinterp[2] * hqpr[k0 + 2] + facinterp[3] * hqpr[k0 + 3];
	edelr[i__] = facinterp[0] * scrtch_1.sdel[k0 * 3 - 2] + facinterp[1] *
		 scrtch_1.sdel[(k0 + 1) * 3 - 2] + facinterp[2] * 
		scrtch_1.sdel[(k0 + 2) * 3 - 2] + facinterp[3] * 
		scrtch_1.sdel[(k0 + 3) * 3 - 2];
	ex[i__] = facinterp[0] * hcomp[k0 * 15 + 1] + facinterp[1] * hcomp[(
		k0 + 1) * 15 + 1] + facinterp[2] * hcomp[(k0 + 2) * 15 + 1] + 
		facinterp[3] * hcomp[(k0 + 3) * 15 + 1];
	ey[i__] = facinterp[0] * hcomp[k0 * 15 + 2] + facinterp[1] * hcomp[(
		k0 + 1) * 15 + 2] + facinterp[2] * hcomp[(k0 + 2) * 15 + 2] + 
		facinterp[3] * hcomp[(k0 + 3) * 15 + 2];
	ez[i__] = facinterp[0] * hcomp[k0 * 15 + 3] + facinterp[1] * hcomp[(
		k0 + 1) * 15 + 3] + facinterp[2] * hcomp[(k0 + 2) * 15 + 3] + 
		facinterp[3] * hcomp[(k0 + 3) * 15 + 3];
	if (gravs4_1.ldifli) {
	    i__2 = *nlight;
	    for (kk = 1; kk <= i__2; ++kk) {
		ii = cslight[kk];
		eli[kk + i__ * eli_dim1] = facinterp[0] * hcomp[ii + k0 * 15] 
			+ facinterp[1] * hcomp[ii + (k0 + 1) * 15] + 
			facinterp[2] * hcomp[ii + (k0 + 2) * 15] + facinterp[
			3] * hcomp[ii + (k0 + 3) * 15];
	    }
	}
/* L70: */
    }
/*  LAST POINT : BY DEFINITION, AT ENDING POINT. */
    em[*npt] = hs1[*iend];
    eden[*npt] = oden[*iend];
    etem[*npt] = otem[*iend];
    ehqpr[*npt] = hqpr[*iend];
    edelr[*npt] = scrtch_1.sdel[*iend * 3 - 2];
    ex[*npt] = hcomp[*iend * 15 + 1];
    ey[*npt] = hcomp[*iend * 15 + 2];
    ez[*npt] = hcomp[*iend * 15 + 3];
    if (gravs4_1.ldifli) {
	i__1 = *nlight;
	for (kk = 1; kk <= i__1; ++kk) {
	    ii = cslight[kk];
	    eli[kk + *npt * eli_dim1] = hcomp[ii + *iend * 15];
	}
    }
    return 0;
} /* microdiff_mte__ */

