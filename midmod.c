/* midmod.f -- translated by f2c (version 20100827).
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
    doublereal clsun, clsunl, clnsun, cmsun, cmsunl, crsun, crsunl, cmbol;
} const_;

#define const_1 const_

struct {
    doublereal cln, clni, c4pi, c4pil, c4pi3l, cc13, cc23, cpi;
} const1_;

#define const1_1 const1_

struct {
    doublereal wmax, exmd, exw, exr, exm, factor;
    logical ljdot0;
} cwind_;

#define cwind_1 cwind_

struct {
    logical lexcom;
} flag_;

#define flag_1 flag_

struct {
    doublereal amum[5000], cpm[5000], delm[5000], delam[5000], delrm[5000], 
	    esumm[5000], om[5000], qdtm[5000], thdifm[5000], velm[5000], 
	    viscm[5000], epsm[5000];
} mdphy_;

#define mdphy_1 mdphy_

struct {
    doublereal hpo[5000], hto[5000], hro[5000], hlo[5000], hdo[5000], hcompp[
	    75000]	/* was [15][5000] */, hss[5000];
    logical lco[5000], lczo[5000];
} oldmod_;

#define oldmod_1 oldmod_

struct {
    doublereal wold[5000], hjx[5000], hio[5000], hgo[5000], r0x[5000], eta2x[
	    5000];
} oldrot_;

#define oldrot_1 oldrot_

struct {
    doublereal delo[5000], delao[5000], amuo[5000], oo[5000], cpo[5000], qdto[
	    5000], velo[5000], visco[5000], thdifo[5000], esumo[5000], delro[
	    5000], epso[5000];
} oldphy_;

#define oldphy_1 oldphy_

struct {
    doublereal sesum[5000], seg[35000]	/* was [7][5000] */, sbeta[5000], 
	    seta[5000];
    logical locons[5000];
    doublereal so[5000], sdel[15000]	/* was [3][5000] */, sfxion[15000]	
	    /* was [3][5000] */, svel[5000];
} scrtch_;

#define scrtch_1 scrtch_

struct {
    doublereal cp[5000], hamu[5000], sqdt[5000], thdif[5000], visc[5000];
} temp_;

#define temp_1 temp_

struct {
    doublereal qwrmax[5000], qwrmx0[5000];
} dwmax_;

#define dwmax_1 dwmax_

struct {
    doublereal hcomps[75000]	/* was [15][5000] */;
} oldab_;

#define oldab_1 oldab_

struct {
    doublereal atime[14], tcut[5], tscut, tenv0, tenv1, tenv, tgcut;
} ctlim_;

#define ctlim_1 ctlim_

struct {
    doublereal drate[5000], drate0[5000], fmassacc, taucz;
    integer jcz;
} deuter_;

#define deuter_1 deuter_

struct {
    doublereal ddelp[5000], ddeln[5000], hrp[5000];
    logical lcp[5000];
} prevmid_;

#define prevmid_1 prevmid_

struct {
    logical lsolid;
} sbrot_;

#define sbrot_1 sbrot_

/* Table of constant values */

static integer c__3 = 3;
static integer c__1 = 1;
static integer c__5 = 5;
static doublereal c_b18 = 10.;
static doublereal c_b50 = .5;

/* $$$$$$ */
/* Subroutine */ int midmod_(doublereal *delts, doublereal *dt, doublereal *
	fx, doublereal *hcomp, doublereal *hd, doublereal *hg, doublereal *
	hjm, doublereal *hl, doublereal *hp, doublereal *hr, doublereal *hs, 
	doublereal *hs1, doublereal *hs2, doublereal *hstot, doublereal *ht, 
	logical *lc, logical *lcz, logical *lfirst, integer *m, doublereal *
	eta2m, doublereal *hdm, doublereal *hgm, doublereal *hicz, doublereal 
	*him, doublereal *hlm, doublereal *hpm, doublereal *hrm, doublereal *
	hsbot, doublereal *hstop, doublereal *htm, integer *imin, integer *
	imax, logical *lallcz, logical *lcm, logical *lczm, logical *lczsur, 
	doublereal *omegam, doublereal *r0m, doublereal *qiwm, integer *
	mrzone, integer *mxzone, integer *nrzone, integer *nzone)
{
    /* System generated locals */
    integer i__1, i__2, i__3;
    doublereal d__1, d__2;

    /* Builtin functions */
    integer s_wsle(cilist *), do_lio(integer *, integer *, char *, ftnlen), 
	    e_wsle(void);
    double pow_dd(doublereal *, doublereal *), exp(doublereal), d_lg10(
	    doublereal *);

    /* Local variables */
    static integer i__, j, k;
    static doublereal f2;
    static integer i0, i1, ii;
    static doublereal rr, dd1, dd2, ps1, ps2;
    static logical lcc, ldo;
    static integer ind;
    static doublereal fac2, czi, czj, hrr, hjm2;
    static integer icz0, icz1;
    static logical lchg[5000];
    static doublereal delj;
    static integer iend, jend;
    static doublereal psca, cvel, temp, hrsh, envr, psca1, psca2;
    extern /* Subroutine */ int solid_(doublereal *, doublereal *, doublereal 
	    *, doublereal *, doublereal *, integer *, integer *, doublereal *,
	     doublereal *, doublereal *, doublereal *, doublereal *, integer *
	    );
    static doublereal ratio, envrl;
    extern /* Subroutine */ int ovrot_(doublereal *, doublereal *, doublereal 
	    *, doublereal *, doublereal *, doublereal *, logical *, integer *,
	     logical *, integer *, integer *, integer *, integer *);
    static doublereal rtest1, rtest2;
    static integer ibegin;
    static doublereal dratem[5000];
    extern /* Subroutine */ int dburnm_(integer *, integer *, integer *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *);
    static logical lnewcz;
    extern /* Subroutine */ int getrot_(doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, logical *, integer *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *);
    static integer jstart;
    static doublereal rtestl;
    extern /* Subroutine */ int rotmix_(doublereal *, doublereal *, 
	    doublereal *, doublereal *, integer *, integer *, integer *, 
	    integer *, integer *, integer *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, logical *, doublereal *)
	    ;
    static doublereal dratem0[5000];

    /* Fortran I/O blocks */
    static cilist io___12 = { 0, 6, 0, 0, 0 };
    static cilist io___26 = { 0, 6, 0, 0, 0 };
    static cilist io___27 = { 0, 6, 0, 0, 0 };


/* MHP 05/02 ADDED FOR DEUTERIUM BURNING */
/* MHP 06/02 */
/* MHP 3/09 ADDED FLAG TO ENFORCE SOLID BODY ROTATION AT ALL TIMES. */
/* MHP 06/02 */
/* ADDED VECTOR FOR DEUTERIUM BURNING */
/* IN GENERAL A DIFFUSION TIMESTEP IS LESS THAN A MODEL TIMESTEP. */
/* SR MIDMOD TAKES THE STRUCTURE AT THE BEGINNING AND END OF THE TIMESTEP */
/* AND ASSIGNS AN INTERMEDIATE STRUCTURE USING LINEAR INTERPOLATION IN TIME. */
/* NUCLEAR BURNING IS ACCOUNTED FOR HERE, AND THE CHANGES IN ANGULAR */
/* VELOCITY DUE TO CHANGES IN RADIUS AND CONSERVATION OF ANGULAR MOMENTUM */
/* ARE ALSO COMPUTED. */
/* MIDMOD ALSO LOCATES THE OUTER EDGE OF A CENTRAL CONVECTION ZONE AND THE INNER */
/* EDGE OF A SURFACE C.Z., AND DETERMINES THE MASS AND MOMENT OF INERTIA OF */
/* THE SURFACE C.Z. */
    /* Parameter adjustments */
    mxzone -= 13;
    mrzone -= 14;
    --qiwm;
    --r0m;
    --omegam;
    --lczm;
    --lcm;
    --htm;
    --hrm;
    --hpm;
    --hlm;
    --him;
    --hgm;
    --hdm;
    --eta2m;
    --lcz;
    --lc;
    --ht;
    --hs2;
    --hs1;
    --hs;
    --hr;
    --hp;
    --hl;
    --hjm;
    --hg;
    --hd;
    hcomp -= 16;

    /* Function Body */
    iend = 11;
    if (flag_1.lexcom) {
	iend = 15;
    }
/*  INITIALIZE COMPOSITION ARRAY THE FIRST TIME THROUGH. */
/*  HCOMPM IS THE ARRAY OF CHANGES IN COMPOSITION DUE TO NUCLEAR BURNING */
/*  DURING THE COURSE OF THE MODEL TIMESTEP. */
/* MHP 06/02 SAVE CHANGES IN R, CZ DEPTH, DELAD-DELRAD FROM THE */
/* PRIOR STEP. */
    if (*lfirst) {
	i__1 = *m;
	for (j = 1; j <= i__1; ++j) {
	    prevmid_1.lcp[j - 1] = oldmod_1.lco[j - 1];
	    prevmid_1.hrp[j - 1] = oldmod_1.hro[j - 1];
	    prevmid_1.ddelp[j - 1] = oldphy_1.delao[j - 1] - oldphy_1.delro[j 
		    - 1];
	    mdphy_1.amum[j - 1] = oldphy_1.amuo[j - 1];
	    i__2 = iend;
	    for (i__ = 1; i__ <= i__2; ++i__) {
		hcomp[i__ + j * 15] = oldmod_1.hcompp[i__ + j * 15 - 16];
/* L10: */
	    }
/* L20: */
	}
    } else {
	i__1 = *m;
	for (j = 1; j <= i__1; ++j) {
	    prevmid_1.hrp[j - 1] = hrm[j];
	    prevmid_1.ddelp[j - 1] = prevmid_1.ddeln[j - 1];
	    prevmid_1.lcp[j - 1] = lcm[j];
	}
    }
    lnewcz = FALSE_;
/*  INTERPOLATE IN THE MODEL VARIABLES AND AUXILLARY PHYSICS. */
    fac2 = *dt / *delts;
    i__1 = *m;
    for (j = 1; j <= i__1; ++j) {
	hdm[j] = oldmod_1.hdo[j - 1] + *fx * (hd[j] - oldmod_1.hdo[j - 1]);
	hlm[j] = oldmod_1.hlo[j - 1] + *fx * (hl[j] - oldmod_1.hlo[j - 1]);
	hpm[j] = oldmod_1.hpo[j - 1] + *fx * (hp[j] - oldmod_1.hpo[j - 1]);
	hrm[j] = oldmod_1.hro[j - 1] + *fx * (hr[j] - oldmod_1.hro[j - 1]);
	htm[j] = oldmod_1.hto[j - 1] + *fx * (ht[j] - oldmod_1.hto[j - 1]);
/*        DO 30 I = 1,IEND */
/*           HCOMP(I,J)=HCOMP(I,J)+FAC2*HCOMPM(I,J) */
/*           HCOMPP(I,J) = HCOMP(I,J) */
/*  30    CONTINUE */
	hgm[j] = oldrot_1.hgo[j - 1] + *fx * (hg[j] - oldrot_1.hgo[j - 1]);
	mdphy_1.delam[j - 1] = oldphy_1.delao[j - 1] + *fx * (scrtch_1.sdel[j 
		* 3 - 1] - oldphy_1.delao[j - 1]);
	mdphy_1.delm[j - 1] = oldphy_1.delo[j - 1] + *fx * (scrtch_1.sdel[j * 
		3 - 2] - oldphy_1.delo[j - 1]);
	mdphy_1.delrm[j - 1] = oldphy_1.delro[j - 1] + *fx * (scrtch_1.sdel[j 
		* 3 - 3] - oldphy_1.delro[j - 1]);
	mdphy_1.esumm[j - 1] = oldphy_1.esumo[j - 1] + *fx * (scrtch_1.sesum[
		j - 1] - oldphy_1.esumo[j - 1]);
	mdphy_1.viscm[j - 1] = oldphy_1.visco[j - 1] + *fx * (temp_1.visc[j - 
		1] - oldphy_1.visco[j - 1]);
	mdphy_1.thdifm[j - 1] = oldphy_1.thdifo[j - 1] + *fx * (temp_1.thdif[
		j - 1] - oldphy_1.thdifo[j - 1]);
	mdphy_1.cpm[j - 1] = oldphy_1.cpo[j - 1] + *fx * (temp_1.cp[j - 1] - 
		oldphy_1.cpo[j - 1]);
	mdphy_1.qdtm[j - 1] = oldphy_1.qdto[j - 1] + *fx * (temp_1.sqdt[j - 1]
		 - oldphy_1.qdto[j - 1]);
	mdphy_1.om[j - 1] = oldphy_1.oo[j - 1] + *fx * (scrtch_1.so[j - 1] - 
		oldphy_1.oo[j - 1]);
	mdphy_1.amum[j - 1] += fac2 * (temp_1.hamu[j - 1] - oldphy_1.amuo[j - 
		1]);
/* MHP 6/00 ADDED TOTAL ENERGY GENERATION */
	temp = scrtch_1.sesum[j - 1] + scrtch_1.seg[j * 7 - 2] + scrtch_1.seg[
		j * 7 - 1];
	mdphy_1.epsm[j - 1] = oldphy_1.epso[j - 1] + *fx * (temp - 
		oldphy_1.epso[j - 1]);
/* L40: */
    }
/*  CHECK FOR ADVANCING OR RECEDING CONVECTIVE REGIONS.USE INTERPOLATED */
/*  RADIATIVE AND ADIABATIC TEMPERATURE GRADIENTS TO DETERMINE WHETHER */
/*  OR NOT A ZONE IS CONVECTIVE IF IT CHANGES STATE OVER THE COURSE OF A */
/*  TIMESTEP. */
    i__1 = *m;
    for (i__ = 1; i__ <= i__1; ++i__) {
	prevmid_1.ddeln[i__ - 1] = mdphy_1.delam[i__ - 1] - mdphy_1.delrm[i__ 
		- 1];
	if (lc[i__] == prevmid_1.lcp[i__ - 1]) {
	    lcm[i__] = lc[i__];
	    mdphy_1.velm[i__ - 1] = oldphy_1.velo[i__ - 1] + *fx * (
		    scrtch_1.svel[i__ - 1] - oldphy_1.velo[i__ - 1]);
	    lchg[i__ - 1] = FALSE_;
	} else {
	    lchg[i__ - 1] = TRUE_;
	    lnewcz = TRUE_;
	    if (mdphy_1.delam[i__ - 1] < mdphy_1.delrm[i__ - 1]) {
		lcm[i__] = TRUE_;
/* Computing MAX */
		d__1 = oldphy_1.velo[i__ - 1], d__2 = scrtch_1.svel[i__ - 1];
		mdphy_1.velm[i__ - 1] = max(d__1,d__2);
	    } else {
		lcm[i__] = FALSE_;
		mdphy_1.velm[i__ - 1] = 0.;
	    }
	}
/* L50: */
    }
    lnewcz = FALSE_;
/* MHP 06/02 IF THE CZ DEPTHS HAVE CHANGED, RESOLVE */
/* OUT WHEN A GIVEN ZONE "DROPPED OUT" OF THE CONVECTION */
/* ZONE OR ENTERED IT.  MODIFY THE SPECIFIC ANGULAR MOMENTUM */
/* ACCORDINGLY. */
    if (lnewcz) {
	lcc = FALSE_;
	ldo = FALSE_;
	i__1 = *m - 1;
	for (i__ = 1; i__ <= i__1; ++i__) {
	    if (lchg[i__ - 1]) {
		if (! lcc) {
/* START OF CHANGED REGION */
		    lcc = TRUE_;
		    i0 = i__;
		}
	    }
	    if (! lchg[i__ - 1]) {
		if (lcc) {
/* END OF CHANGED REGION */
		    i1 = i__ - 1;
		    lcc = FALSE_;
		    ldo = TRUE_;
		    s_wsle(&io___12);
		    do_lio(&c__3, &c__1, (char *)&i0, (ftnlen)sizeof(integer))
			    ;
		    do_lio(&c__3, &c__1, (char *)&i1, (ftnlen)sizeof(integer))
			    ;
		    do_lio(&c__5, &c__1, (char *)&prevmid_1.ddeln[i0 - 1], (
			    ftnlen)sizeof(doublereal));
		    do_lio(&c__5, &c__1, (char *)&prevmid_1.ddeln[i0 - 2], (
			    ftnlen)sizeof(doublereal));
		    do_lio(&c__5, &c__1, (char *)&prevmid_1.ddeln[i1], (
			    ftnlen)sizeof(doublereal));
		    e_wsle();
/* ONLY CHANGE IF THERE IS A RECEDING CONVECTION ZONE; */
/* WE CAN ASSUME LOCAL CONSERVATION OF J PRIOR TO HAVING */
/* A SHELL INCORPORATED INTO A CZ. */
		    if (prevmid_1.ddeln[i0 - 1] > 0.) {
			if (prevmid_1.ddeln[i0 - 2] < 0.) {
/* SUBTRACTED FROM A CORE CZ */
			    ind = -1;
			} else if (prevmid_1.ddeln[i1] < 0.) {
/* SUBTRACTED FROM AN ENVELOPE CZ */
			    ind = 1;
			} else {
			    ldo = FALSE_;
			}
		    } else {
			ldo = FALSE_;
		    }
		}
	    }
	    if (ldo) {
		ldo = FALSE_;
/* CORE CZ */
		if (ind < 0) {
/* LOCATE EDGES OF CURRENT LOWER CZ */
		    icz1 = i0 - 1;
		    for (ii = i0 - 1; ii >= 1; --ii) {
			if (! lcm[ii]) {
			    icz0 = ii + 1;
			    goto L11;
			}
		    }
		    icz0 = 1;
L11:
		    i__2 = i0;
		    for (j = i1; j >= i__2; --j) {
			if (prevmid_1.ddeln[j - 1] < 0.) {
			    goto L13;
			}
			czi = 0.;
			czj = 0.;
/* FRACTION OF THE TIMESTEP SHELL WAS RADIATIVE */
			*fx = prevmid_1.ddeln[j - 1] / (prevmid_1.ddeln[j - 1]
				 - prevmid_1.ddelp[j - 1]);
/* FRACTION OF THE TIMESTEP THAT THE SHELL WAS CONVECTIVE */
			f2 = 1. - *fx;
			i__3 = j - 1;
			for (ii = icz0; ii <= i__3; ++ii) {
			    hrr = prevmid_1.hrp[ii - 1] + f2 * (hr[ii] - 
				    oldmod_1.hro[ii - 1]);
			    d__1 = hrr * 2.;
			    czi += const1_1.cc23 * hs2[ii] * pow_dd(&c_b18, &
				    d__1);
			    czj += hjm[ii] * hs2[ii];
			}
/* GET THE CZ MOMENT OF INERTIA AND TOTAL J AT THE TIME THE */
/* SHELL WAS RELEASED; THIS GIVES A CORRECTED VALUE FOR */
/* J/M.  REDISTRIBUTE THE DIFFERENCE IN J BACK INTO THE CZ. */
			hrsh = (prevmid_1.hrp[j - 1] + f2 * (hr[j] - 
				prevmid_1.hrp[j - 1])) * 2.;
			hjm2 = const1_1.cc23 * (czj / czi) * pow_dd(&c_b18, &
				hrsh);
			delj = (hjm[j] - hjm2) * hs2[j];
			ratio = (czj - delj) / czj;
			hjm[j] = hjm2;
			rr = hjm2 / hjm[j];
			s_wsle(&io___26);
			do_lio(&c__3, &c__1, (char *)&j, (ftnlen)sizeof(
				integer));
			do_lio(&c__5, &c__1, (char *)&(*fx), (ftnlen)sizeof(
				doublereal));
			do_lio(&c__5, &c__1, (char *)&rr, (ftnlen)sizeof(
				doublereal));
			do_lio(&c__5, &c__1, (char *)&delj, (ftnlen)sizeof(
				doublereal));
			do_lio(&c__5, &c__1, (char *)&ratio, (ftnlen)sizeof(
				doublereal));
			e_wsle();
			i__3 = j - 1;
			for (ii = icz0; ii <= i__3; ++ii) {
			    hjm[ii] *= ratio;
			}
		    }
		} else {
/* ENVELOPE CZ */
/* LOCATE EDGES OF CURRENT LOWER CZ */
		    icz0 = i1 + 1;
		    i__2 = *m;
		    for (ii = i1 + 2; ii <= i__2; ++ii) {
			if (! lcm[ii]) {
			    icz1 = ii - 1;
			    goto L12;
			}
		    }
		    icz1 = *m;
L12:
		    i__2 = i1;
		    for (j = i0; j <= i__2; ++j) {
			if (prevmid_1.ddeln[j - 1] < 0.) {
			    goto L13;
			}
			czi = 0.;
			czj = 0.;
/* FRACTION OF THE TIMESTEP SHELL WAS RADIATIVE */
			*fx = prevmid_1.ddeln[j - 1] / (prevmid_1.ddeln[j - 1]
				 - prevmid_1.ddelp[j - 1]);
/* FRACTION OF THE TIMESTEP THAT THE SHELL WAS CONVECTIVE */
			f2 = 1. - *fx;
			i__3 = icz1;
			for (ii = j + 1; ii <= i__3; ++ii) {
			    hrr = prevmid_1.hrp[ii - 1] + f2 * (hr[ii] - 
				    oldmod_1.hro[ii - 1]);
			    d__1 = hrr * 2.;
			    czi += const1_1.cc23 * hs2[ii] * pow_dd(&c_b18, &
				    d__1);
			    czj += hjm[ii] * hs2[ii];
			}
/* GET THE CZ MOMENT OF INERTIA AND TOTAL J AT THE TIME THE */
/* SHELL WAS RELEASED; THIS GIVES A CORRECTED VALUE FOR */
/* J/M.  REDISTRIBUTE THE DIFFERENCE IN J BACK INTO THE CZ. */
			hrsh = (prevmid_1.hrp[j - 1] + f2 * (hr[j] - 
				prevmid_1.hrp[j - 1])) * 2.;
			hjm2 = const1_1.cc23 * (czj / czi) * pow_dd(&c_b18, &
				hrsh);
			delj = (hjm[j] - hjm2) * hs2[j];
			ratio = (czj - delj) / czj;
			hjm[j] = hjm2;
			rr = hjm2 / hjm[j];
			s_wsle(&io___27);
			do_lio(&c__3, &c__1, (char *)&j, (ftnlen)sizeof(
				integer));
			do_lio(&c__5, &c__1, (char *)&(*fx), (ftnlen)sizeof(
				doublereal));
			do_lio(&c__5, &c__1, (char *)&rr, (ftnlen)sizeof(
				doublereal));
			do_lio(&c__5, &c__1, (char *)&delj, (ftnlen)sizeof(
				doublereal));
			do_lio(&c__5, &c__1, (char *)&ratio, (ftnlen)sizeof(
				doublereal));
			e_wsle();
			i__3 = *m;
			for (ii = j + 1; ii <= i__3; ++ii) {
			    hjm[ii] *= ratio;
			}
		    }
		}
L13:
		;
	    }
	}
    }
/*  CONVECTIVE OVERSHOOT APPLIED TO NORMAL CONVECTION ZONES. */
    ovrot_(&hcomp[16], &hdm[1], &hpm[1], &hrm[1], &hs[1], &htm[1], &lcm[1], m,
	     &lczm[1], &mrzone[14], &mxzone[13], nrzone, nzone);
/*  REBURN THE ORIGINAL MIXTURE FOR THE SMALL DIFFUSION TIME STEP. */
/* MHP 6/00 - FOR THERMODYNAMIC CONSISTENCY USE CURRENT T, NOT END OF */
/* TIMESTEP T (REPLACED HT IN CALL WITH HTM) */
    rotmix_(dt, &hcomp[16], &hs2[1], &htm[1], &c__5, m, &mrzone[14], &mxzone[
	    13], nrzone, nzone, hstot, &hdm[1], &hs[1], &hrm[1], &hpm[1], &
	    lczm[1], &hs1[1]);
    i__1 = *m;
    for (i__ = 1; i__ <= i__1; ++i__) {
	for (j = 1; j <= 11; ++j) {
	    oldab_1.hcomps[j + i__ * 15 - 16] = hcomp[j + i__ * 15];
	}
    }
/* MHP 05/02 ADDED DEUTERIUM BURNING */
    if (oldmod_1.hcompp[*m * 15 - 4] > 1e-14) {
/* INCREMENT THE TIMESTEP */
	if (*lfirst) {
	    i__1 = *m;
	    for (i__ = 1; i__ <= i__1; ++i__) {
		dratem[i__ - 1] = deuter_1.drate0[i__ - 1] + fac2 * (
			deuter_1.drate[i__ - 1] - deuter_1.drate0[i__ - 1]);
		dratem0[i__ - 1] = deuter_1.drate0[i__ - 1];
	    }
	} else {
	    i__1 = *m;
	    for (i__ = 1; i__ <= i__1; ++i__) {
		dratem0[i__ - 1] = dratem[i__ - 1];
		dratem[i__ - 1] += fac2 * (deuter_1.drate[i__ - 1] - 
			deuter_1.drate0[i__ - 1]);
	    }
	}
/* RADIATIVE ZONES. */

	i__1 = *nrzone;
	for (k = 1; k <= i__1; ++k) {
	    i__2 = mrzone[k + 26];
	    for (j = mrzone[k + 13]; j <= i__2; ++j) {
/* EXIT LOOP ONCE T DROPS BELOW NUCLEAR REACTION T CUTOFF */
		if (htm[j] <= ctlim_1.tcut[0]) {
		    goto L190;
		}
		ibegin = j;
		iend = j;
		dburnm_(&ibegin, &iend, m, &hs2[1], &hcomp[16], dt, dratem, 
			dratem0, &fac2);
	    }
	}
L190:

/* CONVECTION ZONES. */
/* NOTE KEMCOM ALSO AUTOMATICALLY HOMOGENIZE CONVECTION ZONES. */

	i__1 = *nzone;
	for (k = 1; k <= i__1; ++k) {
	    ibegin = mxzone[k + 12];
	    iend = mxzone[k + 24];
	    dburnm_(&ibegin, &iend, m, &hs2[1], &hcomp[16], dt, dratem, 
		    dratem0, &fac2);
	}
    }
/*  DETERMINE EXTENT OF CENTRAL CONVECTION ZONE. */
/*  IMIN IS THE FIRST ZONE ABOVE A CENTRAL CONVECTION ZONE, AND THUS THE */
/*  FIRST ZONE CONSIDERED FOR STABILITY AGAINST ROTATIONAL INSTABILITIES. */
    if (lczm[1]) {
	i__1 = *m;
	for (i__ = 2; i__ <= i__1; ++i__) {
	    if (! lczm[i__]) {
		goto L65;
	    }
/* L60: */
	}
	i__ = *m + 1;
L65:
/* Computing MAX */
	i__1 = 2, i__2 = i__ - 1;
	*imin = max(i__1,i__2);
    } else {
	*imin = 2;
    }
/*  DETERMINE EXTENT OF SURFACE CONVECTION ZONE. */
    *lallcz = FALSE_;
    if (lczm[*m]) {
/*  SURFACE C.Z. EXISTS.  FIND LOWEST SHELL (IMAX), WHICH IS ALSO THE */
/*  UPPERMOST ZONE CONSIDERED FOR STABILITY AGAINST ROTATIONALLY INDUCED MIXING. */
	for (i__ = *m - 1; i__ >= 1; --i__) {
	    if (! lczm[i__]) {
		goto L80;
	    }
/* L70: */
	}
	*lallcz = TRUE_;
	i__ = 0;
L80:
	*imax = i__ + 1;
/*  HSTOP IS THE MASS AT THE TOP OF THE C.Z. */
/*  HSBOT IS THE MASS AT THE BOTTOM OF THE C.Z. */
	*hstop = exp(const1_1.cln * *hstot);
	if (*imax > 1) {
	    *hsbot = (hs1[*imax] + hs1[*imax - 1]) * .5;
	} else {
	    *hsbot = 0.;
	}
/*  LCZSUR=T IF A SURFACE C.Z.DEEP ENOUGH FOR ANGULAR MOMENTUM LOSS EXISTS */
	if ((*hstop - *hsbot) / const_1.cmsun > 0.) {
	    *lczsur = TRUE_;
	} else {
	    *lczsur = FALSE_;
	}
    } else {
/*  NO SURFACE C.Z. */
	*imax = *m;
	*lczsur = FALSE_;
    }
/* MHP 3/09 ADD ABILITY TO COMPUTE THE CONVECTIVE OVERTURN TIMESCALE 'LOCALLY'. */
/* THIS IS DEFINED AS HP/V, WHERE HP IS THE PRESSURE SCALE HEIGHT AT THE BASE */
/* AND V IS THE CONVECTIVE VELOCITY ONE PRESSURE SCALE HEIGHT ABOVE THE BASE. */
/* FOR FULLY CONVECTIVE STARS THE CENTRAL PRESSURE SCALE HEIGHT DIVERGES, SO */
/* INSTEAD DEFINE V AT THE POINT WHERE HP = P/RHO*G = P*R^2/RHO*G*M = R. */
    if (*lczsur) {
	if (! (*lallcz)) {
/* PINPOINT RCZ */
	    dd2 = mdphy_1.delrm[*imax - 2] - mdphy_1.delam[*imax - 2];
	    dd1 = mdphy_1.delrm[*imax - 1] - mdphy_1.delam[*imax - 1];
	    *fx = dd2 / (dd2 - dd1);
/*            WRITE(*,911)IMAX,FX,DD2,DD1 */
/* 911        FORMAT(I5,1P3E12.3) */
/* INFER HP */
	    envrl = hrm[*imax - 1] + *fx * (hrm[*imax] - hrm[*imax - 1]);
	    envr = exp(const1_1.cln * envrl);
	    ps2 = exp(const1_1.cln * (hpm[*imax] - hdm[*imax])) / hgm[*imax];
	    ps1 = exp(const1_1.cln * (hpm[*imax - 1] - hdm[*imax - 1])) / hgm[
		    *imax - 1];
	    psca = ps1 + *fx * (ps2 - ps1);
	    d__1 = envr + psca;
	    rtestl = d_lg10(&d__1);
/* FIND V */
	    i__1 = *m;
	    for (k = *imax + 1; k <= i__1; ++k) {
		if (hrm[k] > rtestl) {
		    *fx = (rtestl - hrm[k - 1]) / (hrm[k] - hrm[k - 1]);
		    cvel = mdphy_1.velm[k - 2] + *fx * (mdphy_1.velm[k - 1] - 
			    mdphy_1.velm[k - 2]);
		    goto L85;
		}
	    }
	    cvel = mdphy_1.velm[*m - 1];
L85:
/* DEFINE TAUCZ */
	    deuter_1.taucz = psca / cvel;
/*            WRITE(*,911)K,PSCA,CVEL,TAUCZ */
	} else {
/* INFER HP */
	    psca2 = exp(const1_1.cln * (hpm[1] - hdm[1])) / hgm[1];
	    rtest2 = exp(const1_1.cln * hr[1]);
	    if (psca2 <= rtest2) {
/* HP < R AT THE FIRST POINT.  ASSUME V CONSTANT INSIDE AND HP = K/R FOR */
/* SLOWLY VARYING DENSITY AND PRESSURE NEAR THE CENTER. */
		cvel = mdphy_1.velm[0];
		d__1 = psca2 * rtest2;
		psca = pow_dd(&d__1, &c_b50);
		deuter_1.taucz = psca / cvel;
/*               WRITE(*,912)PSCA2,RTEST2,PSCA,CVEL,TAUCZ */
/* 912           FORMAT(1P5E12.3) */
	    } else {
		i__1 = *m;
		for (k = 2; k <= i__1; ++k) {
		    psca1 = psca2;
		    rtest1 = rtest2;
		    psca2 = exp(const1_1.cln * (hpm[k] - hdm[k])) / hgm[k];
		    rtest2 = exp(const1_1.cln * hr[k]);
/* FIND LOCATION WHERE HP = R */
		    if (psca2 <= rtest2) {
			*fx = (rtest1 - psca1) / (psca2 - rtest2 - (psca1 - 
				rtest1));
/* FIND V */
			cvel = mdphy_1.velm[k - 2] + *fx * (mdphy_1.velm[k - 
				1] - mdphy_1.velm[k - 2]);
			psca = psca1 + *fx * (psca2 - psca1);
/* DEFINE TAUCZ */
			deuter_1.taucz = psca / cvel;
			goto L95;
		    }
		}
		k = *m;
		cvel = mdphy_1.velm[*m - 1];
		psca = psca2;
		deuter_1.taucz = psca / cvel;
L95:
/*               WRITE(*,911)K,PSCA,CVEL,TAUCZ */
		;
	    }
	}
    }
    if (! sbrot_1.lsolid) {
/*  NOW FIND THE RUN OF ROTATION VARIABLES THAT ARE CONSISTENT WITH THE */
/*  INTERMEDIATE STRUCTURE AND THE RUN OF SPECIFIC ANGULAR MOMENTUM J/M. */
/*  J/M = I/M * OMEGA. */
/*  FIRST GUESS AT MOMENT OF INERTIA OF DISTORTED SPERICAL SHELLS: */
/*  I/M = 2/3 R**2. */
	i__1 = *m;
	for (i__ = 1; i__ <= i__1; ++i__) {
	    him[i__] = const1_1.cc23 * exp(const1_1.cln * 2. * hrm[i__]);
	    omegam[i__] = hjm[i__] / him[i__];
	    him[i__] = hs2[i__] * him[i__];
	}
/*  SOLVE FOR THE ANGULAR VELOCITIES OF THE SHELLS GIVEN THE SPECIFIC */
/*  ANGULAR MOMENTUM (HJM) AND A FIRST GUESS AT THE ANGULAR VELOCITY(OMEGAM) */
/*  AND MOMENT OF INERTIA (HIM). */
	getrot_(&hdm[1], &hjm[1], &hrm[1], &hs[1], &hs2[1], &lczm[1], m, &
		eta2m[1], &him[1], &omegam[1], &qiwm[1], &r0m[1]);
/*  FIND TOTAL MOMENT OF INERTIA OF THE SURFACE C.Z. IF APPLICABLE. */
	if (*lczsur) {
	    *hicz = him[*m];
	    for (i__ = *m - 1; i__ >= 1; --i__) {
		if (! lczm[i__]) {
		    goto L110;
		}
		*hicz += him[i__];
	    }
L110:
	    ;
	}
    } else {
	jstart = 1;
	jend = *m;
	solid_(&hdm[1], &hjm[1], &hrm[1], &hs[1], &hs2[1], &jstart, &jend, &
		eta2m[1], &him[1], &omegam[1], &qiwm[1], &r0m[1], m);
	if (*lczsur) {
	    *hicz = him[1];
	    i__1 = *m;
	    for (i__ = 2; i__ <= i__1; ++i__) {
		*hicz += him[i__];
	    }
	}
    }
    return 0;
} /* midmod_ */

