/* microdiff_etm.f -- translated by f2c (version 20061008).
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
    doublereal con_rad__, con_mass__, con_temp__, con_time__;
} confac_;

#define confac_1 confac_

struct {
    doublereal fgry, fgrz;
    logical lthoul, ldifz;
} gravs3_;

#define gravs3_1 gravs3_

struct {
    logical lnewdif, ldifli;
} gravs4_;

#define gravs4_1 gravs4_

/* $$$$$$ */
/* Subroutine */ int microdiff_etm__(doublereal *dt, doublereal *er, 
	doublereal *edelx, doublereal *edelz, doublereal *edelli, integer *
	ibegin, integer *iend, integer *npt, doublereal *hcomp, doublereal *
	hqpr, doublereal *hru, doublereal *hs1, doublereal *htu, integer *m, 
	doublereal *stot, integer *nlight, integer *cslight)
{
    /* System generated locals */
    integer edelli_dim1, edelli_offset, i__1, i__2, i__3, i__4;
    doublereal d__1;

    /* Local variables */
    static integer i__, j, k;
    static doublereal facinterp[4];
    static integer k0, ii, kk;
    static doublereal zz, zz2;
    static integer jmin;
    static doublereal xmax, zmin, zmax, dxmod, dzmod;
    extern /* Subroutine */ int intrp2_(doublereal *, doublereal *, 
	    doublereal *);
    static doublereal radmod, tabler[4], xminim;

/* MHP 3/94 ADDED METAL DIFFUSION */
/* KC 2025-05-30 fixed -Wconversion */
/*      *          HTU(JSON),TABLER(4),FACINTERP(4),CSLIGHT(NLIGHT) */
/*  TRANSFORM BACK TO ORIGINAL GRID OF MODEL POINTS FROM EQUALLY */
/*  SPACED GRID. */
    /* Parameter adjustments */
    --er;
    --edelx;
    --edelz;
    hcomp -= 16;
    --hqpr;
    --hru;
    --hs1;
    --htu;
    --cslight;
    edelli_dim1 = *nlight;
    edelli_offset = 1 + edelli_dim1;
    edelli -= edelli_offset;

    /* Function Body */
    xminim = 0.;
    for (i__ = *ibegin; i__ >= 1; --i__) {
/* Computing MAX */
	d__1 = hcomp[i__ * 15 + 1] + edelx[1];
	hcomp[i__ * 15 + 1] = max(d__1,xminim);
/* L10: */
    }
/* MHP 3/94 ADDED METAL DIFFUSION */
/* NOTE THAT BECAUSE METALS SINK, AND HYDROGEN RISES, THE FAILSAFES */
/* ARE OPPOSITE (GUARDING AGAINST NEGATIVE X AND Z>1 RESPECTIVELY). */
    if (gravs3_1.ldifz) {
	for (i__ = *ibegin; i__ >= 1; --i__) {
	    zmax = 1. - hcomp[i__ * 15 + 1] - hcomp[i__ * 15 + 4];
/* Computing MIN */
	    d__1 = hcomp[i__ * 15 + 3] + edelz[1];
	    zz = min(d__1,zmax);
	    zz2 = zz / hcomp[i__ * 15 + 3];
	    hcomp[i__ * 15 + 3] = zz;
	    for (j = 5; j <= 11; ++j) {
		hcomp[j + i__ * 15] = zz2 * hcomp[j + i__ * 15];
	    }
	    hcomp[i__ * 15 + 2] = 1. - hcomp[i__ * 15 + 1] - hcomp[i__ * 15 + 
		    3] - hcomp[i__ * 15 + 4];
	}
    } else {
	for (i__ = *ibegin; i__ >= 1; --i__) {
	    hcomp[i__ * 15 + 2] = 1. - hcomp[i__ * 15 + 1] - hcomp[i__ * 15 + 
		    3] - hcomp[i__ * 15 + 4];
	}
    }
/* G SOMERS 5/15; ADD LIGHT ELEMENT DIFFUSION */
    if (gravs4_1.ldifli) {
	i__1 = *nlight;
	for (kk = 1; kk <= i__1; ++kk) {
	    xminim = 0.;
	    for (i__ = *ibegin; i__ >= 1; --i__) {
		ii = cslight[kk];
/* Computing MAX */
		d__1 = hcomp[ii + i__ * 15] + edelli[kk + edelli_dim1];
		hcomp[ii + i__ * 15] = max(d__1,xminim);
/* L15: */
	    }
	}
    }

    jmin = 2;
    i__1 = *iend - 1;
    for (i__ = *ibegin + 1; i__ <= i__1; ++i__) {
	i__2 = *npt;
	for (j = jmin; j <= i__2; ++j) {
/*  FIND EQUALLY SPACED GRID POINTS CLOSEST TO THE MODEL POINT. */
	    if (er[j] >= hru[i__]) {
/*  ENSURE THAT FIRST INTERP. POINT NO LESS THAN FIRST EQUALLY SPACED POINT. */
/* Computing MAX */
		i__3 = j - 2;
		k0 = max(i__3,1);
/*  ENSURE THAT LAST INTERP. POINT NO GREATER THAN LAST EQUALLY SPACED POINT. */
/* Computing MIN */
		i__3 = k0, i__4 = *npt - 3;
		k0 = min(i__3,i__4);
/* JVS fix for NPT = 3? */
		if (k0 == 0) {
		    k0 = 1;
		}
		jmin = j;
		goto L40;
	    }
/* L30: */
	}
	k0 = *npt - 3;
	jmin = *npt;
L40:
	for (k = 1; k <= 4; ++k) {
	    tabler[k - 1] = er[k0 + k - 1];
/* L50: */
	}
	radmod = hru[i__];
/*  FIND 4 POINT LAGRANGIAN INTERPOLATION FACTORS. */
	intrp2_(tabler, facinterp, &radmod);
/*  PERFORM 4 POINT LAGRANGIAN INTERPOLATION FOR CHANGE IN X. */
	dxmod = facinterp[0] * edelx[k0] + facinterp[1] * edelx[k0 + 1] + 
		facinterp[2] * edelx[k0 + 2] + facinterp[3] * edelx[k0 + 3];
	xmax = 1. - hcomp[i__ * 15 + 3] - hcomp[i__ * 15 + 4];
/* Computing MIN */
	d__1 = hcomp[i__ * 15 + 1] + dxmod;
	hcomp[i__ * 15 + 1] = min(d__1,xmax);
/* MHP 3/94 ADDED METAL DIFFUSION */
	if (gravs3_1.ldifz) {
	    zmax = 1. - hcomp[i__ * 15 + 1] - hcomp[i__ * 15 + 4];
	    dzmod = facinterp[0] * edelz[k0] + facinterp[1] * edelz[k0 + 1] + 
		    facinterp[2] * edelz[k0 + 2] + facinterp[3] * edelz[k0 + 
		    3];
/* Computing MIN */
	    d__1 = hcomp[i__ * 15 + 3] + dzmod;
	    zz = min(d__1,zmax);
	    zz2 = zz / hcomp[i__ * 15 + 3];
	    hcomp[i__ * 15 + 3] = zz;
	    for (j = 5; j <= 11; ++j) {
		hcomp[j + i__ * 15] = zz2 * hcomp[j + i__ * 15];
	    }
	    hcomp[i__ * 15 + 2] = 1. - hcomp[i__ * 15 + 1] - hcomp[i__ * 15 + 
		    3] - hcomp[i__ * 15 + 4];
	} else {
	    hcomp[i__ * 15 + 2] = 1. - hcomp[i__ * 15 + 1] - hcomp[i__ * 15 + 
		    3] - hcomp[i__ * 15 + 4];
	}
/* GES 5/15 ADDED LIGHT ELEMENT DIFFUSION */
	if (gravs4_1.ldifli) {
	    i__2 = *nlight;
	    for (kk = 1; kk <= i__2; ++kk) {
		ii = cslight[kk];
		dxmod = facinterp[0] * edelli[kk + k0 * edelli_dim1] + 
			facinterp[1] * edelli[kk + (k0 + 1) * edelli_dim1] + 
			facinterp[2] * edelli[kk + (k0 + 2) * edelli_dim1] + 
			facinterp[3] * edelli[kk + (k0 + 3) * edelli_dim1];
		hcomp[ii + i__ * 15] += dxmod;
	    }
	}
/* L20: */
    }

    i__1 = *m;
    for (i__ = *iend; i__ <= i__1; ++i__) {
	xmax = 1. - hcomp[i__ * 15 + 3] - hcomp[i__ * 15 + 4];
/* Computing MIN */
	d__1 = hcomp[i__ * 15 + 1] + edelx[*npt];
	hcomp[i__ * 15 + 1] = min(d__1,xmax);
/* L60: */
    }
/* MHP 3/94 ADDED METAL DIFFUSION */
    if (gravs3_1.ldifz) {
	zmin = 0.;
	i__1 = *m;
	for (i__ = *iend; i__ <= i__1; ++i__) {
/* Computing MAX */
	    d__1 = hcomp[i__ * 15 + 3] + edelz[*npt];
	    zz = max(d__1,zmin);
	    zz2 = zz / hcomp[i__ * 15 + 3];
	    hcomp[i__ * 15 + 3] = zz;
	    for (j = 5; j <= 11; ++j) {
		hcomp[j + i__ * 15] = zz2 * hcomp[j + i__ * 15];
	    }
	    hcomp[i__ * 15 + 2] = 1. - hcomp[i__ * 15 + 1] - hcomp[i__ * 15 + 
		    3] - hcomp[i__ * 15 + 4];
	}
    } else {
	i__1 = *m;
	for (i__ = *iend; i__ <= i__1; ++i__) {
	    hcomp[i__ * 15 + 2] = 1. - hcomp[i__ * 15 + 1] - hcomp[i__ * 15 + 
		    3] - hcomp[i__ * 15 + 4];
	}
    }
/* GES 5/15 LIGHT ELEMENT DIFFUSION */
    if (gravs4_1.ldifli) {
	i__1 = *nlight;
	for (kk = 1; kk <= i__1; ++kk) {
	    i__2 = *m;
	    for (i__ = *iend; i__ <= i__2; ++i__) {
		ii = cslight[kk];
		hcomp[ii + i__ * 15] += edelli[kk + *npt * edelli_dim1];
/* L65: */
	    }
	}
    }

    i__1 = *m;
    for (i__ = 1; i__ <= i__1; ++i__) {
	hru[i__] /= confac_1.con_rad__;
	htu[i__] /= confac_1.con_temp__;
	hs1[i__] /= confac_1.con_mass__;
	hqpr[i__] *= confac_1.con_rad__;
/* L70: */
    }
    *dt *= confac_1.con_time__;
    *stot /= confac_1.con_mass__;
    return 0;
} /* microdiff_etm__ */

