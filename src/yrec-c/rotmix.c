/* rotmix.f -- translated by f2c (version 20061008).
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
    doublereal hcompm[75000]	/* was [15][5000] */;
} burn_;

#define burn_1 burn_

struct {
    doublereal cdelrl, cmixl, cmixl2, cmixl3, clndp, csecyr;
} const3_;

#define const3_1 const3_

struct {
    doublereal atime[14], tcut[5], tscut, tenv0, tenv1, tenv, tgcut;
} ctlim_;

#define ctlim_1 ctlim_

struct {
    logical lexcom;
} flag_;

#define flag_1 flag_

struct {
    doublereal cln, clni, c4pi, c4pil, c4pi3l, cc13, cc23, cpi;
} const1_;

#define const1_1 const1_

struct {
    doublereal cgas, ca3, ca3l, csig, csigl, cgl, cmkh, cmkhn;
} const2_;

#define const2_1 const2_

struct {
    doublereal grtol;
    integer ilambda, niter_gs__;
    logical ldify;
} gravst_;

#define gravst_1 gravst_

struct {
    doublereal dt_gs__, xmin, ymin;
    logical lthoulfit;
} gravs2_;

#define gravs2_1 gravs2_

struct {
    logical lnewdif, ldifli;
} gravs4_;

#define gravs4_1 gravs4_

struct {
    integer ilast, idebug, itrack, ishort, imilne, imodpt, istor, iowr;
} luout_;

#define luout_1 luout_

struct {
    doublereal amum[5000], cpm[5000], delm[5000], delam[5000], delrm[5000], 
	    esumm[5000], om[5000], qdtm[5000], thdifm[5000], velm[5000], 
	    viscm[5000], epsm[5000];
} mdphy_;

#define mdphy_1 mdphy_

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
static integer c__3 = 3;
static integer c__5 = 5;

/* 1) USE KEMCOM TO IMPLICITLY SOLVE FOR ABUNDANCES IN RADIATIVE REGIONS. */
/* 2) SOLVE FOR BURNING IN EACH CONVECTION ZONE. */
/*       SUBROUTINE ROTMIX(DELTS,HCOMP,HS2,HT,ITLVL,M,MRZONE,MXZONE,  ! KC 2025-05-31 */
/* Subroutine */ int rotmix_(doublereal *delts, doublereal *hcomp, doublereal 
	*hs2, doublereal *ht, integer *m, integer *mrzone, integer *mxzone, 
	integer *nrzone, integer *nzone, doublereal *hstot, doublereal *hd, 
	doublereal *hs, doublereal *hr, doublereal *hp, logical *lc, 
	doublereal *hs1)
{
    /* Format strings */
    static char fmt_911[] = "(1x,\002NO SURFACE CZ - DIFFUSION NOT MEANING"
	    "FUL\002/\002STOPPED IN SUBROUTINE MIX\002)";

    /* System generated locals */
    integer i__1, i__2;
    doublereal d__1, d__2;

    /* Builtin functions */
    integer s_wsfe(cilist *), e_wsfe(void);
    /* Subroutine */ void s_stop(char *, ftnlen);
    double exp(doublereal);
    integer s_wsle(cilist *), do_lio(integer *, integer *, char *, ftnlen), 
	    e_wsle(void);
    double d_mod(doublereal *, doublereal *);

    /* Local variables */
    static integer i__, j, k;
    extern /* Subroutine */ int microdiff_(doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, logical *, integer *, doublereal *);
    static integer ii;
    static doublereal fm, dt;
    static integer ns;
    static doublereal hf1[5000], hf2[5000], hr1[5000], hr2[5000], hr3[5000], 
	    hr4[5000], hr5[5000], hr6[5000], hr7[5000], hr8[5000], hr9[5000], 
	    hr10[5000], hr11[5000], hr12[5000], hr13[5000];
    static logical lcz[5000];
    static integer iend, jmax;
    static doublereal temp[5000], hqpr[5000], stot, ddage;
    static integer nspec;
    static doublereal dtmax;
    static integer nstep, ibegin;
    extern /* Subroutine */ int kemcom_(doublereal *, integer *, integer *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *);
    static doublereal tscale;
    extern /* Subroutine */ int grsett_(doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, logical *, integer *, doublereal *);

    /* Fortran I/O blocks */
    static cilist io___23 = { 0, 6, 0, fmt_911, 0 };
    static cilist io___24 = { 0, 0, 0, fmt_911, 0 };
    static cilist io___32 = { 0, 69, 0, 0, 0 };
    static cilist io___35 = { 0, 69, 0, 0, 0 };


/* GES 6/15 INCLUDED COMMON BLOCK FOR NEW DIFFUSION ROUTINES. */
/* NSPEC IS THE NUMBER OF SPECIES BEING TRACKED. */
    /* Parameter adjustments */
    --hs1;
    --lc;
    --hp;
    --hr;
    --hs;
    --hd;
    mxzone -= 13;
    mrzone -= 14;
    --ht;
    --hs2;
    hcomp -= 16;

    /* Function Body */
    if (flag_1.lexcom) {
	nspec = 15;
    } else {
	nspec = 11;
    }
/*  DDAGE IS THE TIMESTEP IN YEARS. */
    ddage = *delts / const3_1.csecyr;
    i__1 = *m;
    for (ii = 1; ii <= i__1; ++ii) {
	hr1[ii - 1] = burn_1.hcompm[ii * 15 - 15];
	hr2[ii - 1] = burn_1.hcompm[ii * 15 - 14];
	hr3[ii - 1] = burn_1.hcompm[ii * 15 - 13];
	hr4[ii - 1] = burn_1.hcompm[ii * 15 - 12];
	hr5[ii - 1] = burn_1.hcompm[ii * 15 - 11];
	hr6[ii - 1] = burn_1.hcompm[ii * 15 - 10];
	hr7[ii - 1] = burn_1.hcompm[ii * 15 - 9];
	hr8[ii - 1] = burn_1.hcompm[ii * 15 - 8];
	hr9[ii - 1] = burn_1.hcompm[ii * 15 - 7];
	hr10[ii - 1] = burn_1.hcompm[ii * 15 - 6];
	hr11[ii - 1] = burn_1.hcompm[ii * 15 - 5];
	hr12[ii - 1] = burn_1.hcompm[ii * 15 - 4];
	hr13[ii - 1] = burn_1.hcompm[ii * 15 - 3];
	hf1[ii - 1] = burn_1.hcompm[ii * 15 - 2];
	hf2[ii - 1] = burn_1.hcompm[ii * 15 - 1];
    }

/*  NOW IMPLICITLY SOLVE FOR THE NEW ABUNDANCES AT THE END OF THE */
/*  TIMESTEP.  THIS IS DONE SHELL BY SHELL FOR RADIATIVE REGIONS, */
/*  AND FOR EACH CONVECTION ZONE AS A UNIT. */

/* RADIATIVE ZONES. */

    i__1 = *nrzone;
    for (k = 1; k <= i__1; ++k) {
	i__2 = mrzone[k + 26];
	for (j = mrzone[k + 13]; j <= i__2; ++j) {
/* EXIT LOOP ONCE T DROPS BELOW NUCLEAR REACTION T CUTOFF */
	    if (ht[j] <= ctlim_1.tcut[0]) {
		goto L45;
	    }
	    ibegin = j;
	    iend = j;
	    kemcom_(&ht[1], &ibegin, &iend, hr1, hr2, hr3, hr4, hr5, hr6, hr7,
		     hr8, hr10, hr11, hr12, hf1, &hs2[1], &hcomp[16], &ddage);
/*      *                   HR8,HR9,HR10,HR11,HR12,HR13,HF1,HS2,HCOMP, */
/*      *                   DDAGE,ITLVL)  ! KC 2025-05-31 */
/* L30: */
	}
/* L40: */
    }
L45:

/* CONVECTION ZONES. */
/* NOTE KEMCOM ALSO AUTOMATICALLY HOMOGENIZE CONVECTION ZONES. */

    i__1 = *nzone;
    for (k = 1; k <= i__1; ++k) {
	ibegin = mxzone[k + 12];
	iend = mxzone[k + 24];
	kemcom_(&ht[1], &ibegin, &iend, hr1, hr2, hr3, hr4, hr5, hr6, hr7, 
		hr8, hr10, hr11, hr12, hf1, &hs2[1], &hcomp[16], &ddage);
/*      *                HR8,HR9,HR10,HR11,HR12,HR13,HF1,HS2,HCOMP, */
/*      *                DDAGE,ITLVL)  ! KC 2025-05-31 */
/* L50: */
    }

/* MICROSCOPIC DIFFUSION OF HELIUM. */

/* ***BC 5/92 ROTMIX MODIFIED TO INCLUDE CALL TO GRAVITATIONAL SETTLING */
/*      ROUTINE USING THE BAHCALL AND LOEB METHOD. */
/* FIRST DEFINE VARIABLES NEEDED FOR SETTLING - */
/* HQPR=VECTOR OF D LN P/DR. */
/* STOT=TOTAL STELLAR MASS(UNLOGGED). */
    if (gravst_1.ldify) {
	if (hcomp[16] < gravs2_1.xmin) {
	    gravst_1.ldify = FALSE_;
	    goto L170;
	}
/* MHP 6/90 CHANGE ADDED : THE TIMESTEP FOR SETTLING IS RESTRICTED TO */
/*   A FRACTION OF THE TIMESCALE FOR SETTLING AT THE OUTER BOUNDARY. */
/*   THE OUTER BOUNDARY IS EITHER THE SURFACE CONVECTION ZONE OR THE */
/*   FIRST POINT WHERE THE HELIUM ABUNDANCE RISES ABOVE A USER-SPECIFIED */
/*   MINIMUM VALUE (YMIN). */

/*   LOCATE OUTER BOUNDARY. */
	if (! lc[*m]) {
	    s_wsfe(&io___23);
	    e_wsfe();
	    io___24.ciunit = luout_1.ishort;
	    s_wsfe(&io___24);
	    e_wsfe();
	    s_stop("", (ftnlen)0);
	}
/* 7/92 MHP STATEMENT ADDED FOR EXIT IF OVERSHOOT CAUSES A FULLY CONVECTIVE */
/* CASE.  AVOIDS OCCASIONAL PRE-MS CRASH IN FIRST RADIATIVE MODEL. */
	if (mxzone[*nzone + 12] <= 2 && mxzone[*nzone + 24] == *m) {
	    goto L170;
	}
	jmax = mrzone[*nrzone + 26];
	for (j = jmax; j >= 1; --j) {
	    if (hcomp[j * 15 + 2] > gravs2_1.ymin) {
		goto L150;
	    }
/* L140: */
	}
/*   Y<YMIN FOR THE WHOLE STAR IF THE CODE GETS HERE. */
	goto L170;
L150:
	stot = exp(const1_1.cln * *hstot);
	i__1 = *m;
	for (i__ = 1; i__ <= i__1; ++i__) {
	    temp[i__ - 1] = scrtch_1.sdel[i__ * 3 - 2];
	    scrtch_1.sdel[i__ * 3 - 2] = mdphy_1.delm[i__ - 1];
	    hqpr[i__ - 1] = -exp(const1_1.cln * (hd[i__] + const2_1.cgl + hs[
		    i__] - hr[i__] * 2. - hp[i__]));
/* L130: */
	}
/* ***BC 6/92 only check for timestep cutting if JMAX is large */

	if (jmax >= 2) {
/*  FM IS THE MASS FRACTION ABOVE THE OUTER POINT. */
	    fm = (stot - hs1[jmax]) / stot;
/*  TSCALE IS THE TIMESCALE FOR SETTLING OF HELIUM AT THE OUTER */
/*  BOUNDARY (MICHAUD ET AL 1984, APJ V.282,P.206) */
	    tscale = const3_1.csecyr * 4.348e21 * fm / exp(const1_1.cln * 1.5 
		    * ht[jmax]);
/*  RESTRICT TIMESTEP TO THE MINIMUM OF THE MODEL TIMESTEP AND */
/*  A USER SPECIFIED FRACTION (DT_GS) OF THE SETTLING TIMESCALE. */
	    s_wsle(&io___32);
	    do_lio(&c__9, &c__1, "JMAX=", (ftnlen)5);
	    do_lio(&c__3, &c__1, (char *)&jmax, (ftnlen)sizeof(integer));
	    do_lio(&c__9, &c__1, " FM= ", (ftnlen)5);
	    do_lio(&c__5, &c__1, (char *)&fm, (ftnlen)sizeof(doublereal));
	    do_lio(&c__9, &c__1, " TSCALE=", (ftnlen)8);
	    do_lio(&c__5, &c__1, (char *)&tscale, (ftnlen)sizeof(doublereal));
	    e_wsle();
	    dtmax = gravs2_1.dt_gs__ * tscale;
	    nstep = (integer) (*delts / dtmax);
	    if (d_mod(&dtmax, delts) != 0. || nstep == 0) {
		++nstep;
	    }
	    s_wsle(&io___35);
	    do_lio(&c__9, &c__1, "DTMAX=", (ftnlen)6);
	    do_lio(&c__5, &c__1, (char *)&dtmax, (ftnlen)sizeof(doublereal));
	    do_lio(&c__9, &c__1, " DELTS=", (ftnlen)7);
	    do_lio(&c__5, &c__1, (char *)&(*delts), (ftnlen)sizeof(doublereal)
		    );
	    do_lio(&c__9, &c__1, " NSTEP=", (ftnlen)7);
	    do_lio(&c__3, &c__1, (char *)&nstep, (ftnlen)sizeof(integer));
	    e_wsle();
	    dt = *delts / (doublereal) nstep;
	} else {
	    nstep = 1;
	    dt = *delts;
	}
	i__1 = *nrzone;
	for (j = 1; j <= i__1; ++j) {
	    i__2 = mrzone[j + 26];
	    for (i__ = mrzone[j + 13]; i__ <= i__2; ++i__) {
		lcz[i__ - 1] = FALSE_;
	    }
	}
	i__1 = *nzone;
	for (j = 1; j <= i__1; ++j) {
	    i__2 = mxzone[j + 24];
	    for (i__ = mxzone[j + 12]; i__ <= i__2; ++i__) {
		lcz[i__ - 1] = TRUE_;
	    }
	}
	i__1 = nstep;
	for (ns = 1; ns <= i__1; ++ns) {
/* PERFORM GRAVITATIONAL SETTLING. IF LNEWDIF = TRUE, USE THE NEW ROUTINES */
/* IN MICRODIFF. ELSE, USE THE OLD ROUTINES IN GRSETT. */
	    if (gravs4_1.lnewdif) {
		microdiff_(&dt, &hcomp[16], hqpr, &hr[1], &hd[1], &hs1[1], &
			ht[1], lcz, m, &stot);
	    } else {
		grsett_(&dt, &hcomp[16], hqpr, &hr[1], &hd[1], &hs1[1], &ht[1]
			, lcz, m, &stot);
	    }
/* L160: */
	}
	i__1 = *m;
	for (i__ = 1; i__ <= i__1; ++i__) {
	    scrtch_1.sdel[i__ * 3 - 2] = temp[i__ - 1];
	}
L170:
	;
    }
/* END OF GRAVITATIONAL SETTLING */

/* RENORMALIZE COMPOSITION TO GUARD AGAINST ANOMALIES (I.E. SMALL NEGATIVE */
/* ABUNDANCES...). */
    i__1 = *m;
    for (i__ = 1; i__ <= i__1; ++i__) {
	i__2 = nspec;
	for (j = 1; j <= i__2; ++j) {
/* Computing MAX */
	    d__1 = hcomp[j + i__ * 15];
	    hcomp[j + i__ * 15] = max(d__1,0.);
/* Computing MIN */
	    d__1 = hcomp[j + i__ * 15];
	    hcomp[j + i__ * 15] = min(d__1,1.);
/* L175: */
	}
/* Computing MIN */
	d__1 = hcomp[i__ * 15 + 3], d__2 = 1. - hcomp[i__ * 15 + 1] - hcomp[
		i__ * 15 + 4];
	hcomp[i__ * 15 + 3] = min(d__1,d__2);
	hcomp[i__ * 15 + 2] = 1. - hcomp[i__ * 15 + 1] - hcomp[i__ * 15 + 3] 
		- hcomp[i__ * 15 + 4];
/* L180: */
    }
    return 0;
} /* rotmix_ */

