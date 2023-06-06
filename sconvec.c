/* sconvec.f -- translated by f2c (version 20100827).
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
    logical lexcom;
} flag_;

#define flag_1 flag_

struct {
    integer ilast, idebug, itrack, ishort, imilne, imodpt, istor, iowr;
} luout_;

#define luout_1 luout_

struct {
    doublereal clsun, clsunl, clnsun, cmsun, cmsunl, crsun, crsunl, cmbol;
} const_;

#define const_1 const_

struct {
    doublereal cln, clni, c4pi, c4pil, c4pi3l, cc13, cc23, cpi;
} const1_;

#define const1_1 const1_

struct {
    doublereal olaol[64896]	/* was [12][104][52] */, oxa[12], ot[52], 
	    orho[104], tollaol;
    integer iolaol, numofxyz, numrho, numt;
    logical llaol, lpurez;
    integer iopurez;
    char flaol[256], fpurez[256];
} nwlaol_;

#define nwlaol_1 nwlaol_

struct {
    doublereal cdh, etadh0, etadh1, zdh[18], xxdh, yydh, zzdh, dhnue[18];
    logical ldh;
} debhu_;

#define debhu_1 debhu_

/* Table of constant values */

static integer c__1 = 1;

/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */
/* SCONVEC */
/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */
/* Subroutine */ int sconvec_(doublereal *delts, doublereal *hcomp, 
	doublereal *hd, doublereal *hl, doublereal *hp, doublereal *hr, 
	doublereal *hs, doublereal *ht, integer *m, integer *mxzone, integer *
	nzone)
{
    /* Format strings */
    static char fmt_601[] = "(1x,\002CZ OLD EDGE \002,i3,\002 EXTENDED TO"
	    "-\002,i3,\002 LIMIT=\002,l1,\002 RAD.GRADS-IN/OUT\002,2f8.4)";
    static char fmt_93[] = "(2x,\002MIXED ZONES MERGED DUE TO SEMICONVECTIO"
	    "N\002/2x,\002OLD\002,2(\002[\002,i3,\002-\002,i3,\002]\002),\002"
	    " NEW\002,\002[\002,i3,\002-\002,i3,\002]\002)";

    /* System generated locals */
    integer i__1, i__2, i__3;

    /* Builtin functions */
    double exp(doublereal);
    integer s_wsfe(cilist *), do_fio(integer *, char *, ftnlen), e_wsfe(void);

    /* Local variables */
    static doublereal b, d__;
    static integer i__, j, k;
    static doublereal o, p, t, x, z__;
    static integer k1, j2;
    static doublereal dl;
    static integer ii;
    static doublereal pl, rl, sl, tl;
    static integer iu;
    static doublereal ol, del;
    static integer jmc;
    static doublereal eta, fpl, amu, qcp, qdp, ftl;
    static integer jmr;
    static doublereal emu, qdt, qat, qap, qod, vel, rmu, qot;
    static integer jmc2;
    static doublereal dela;
    static integer jbeg;
    static doublereal fdel, beta;
    static integer jend;
    static doublereal qacp, delr, qacr, qact;
    static logical lmax;
    static doublereal qcpp, qdtp, qcpt, qdtt, rmax, rsum, beta1, delr0, delr1,
	     rval1, rval2, beta14;
    static integer ksaha;
    static doublereal rdiff;
    static logical latmo, lconv;
    static doublereal fxion[3];
    static integer jstep;
    static logical lflagd, lflagu, locond;
    extern /* Subroutine */ int tpgrad_(doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, logical *, logical *, doublereal *, doublereal *);
    static logical lderiv;
    extern /* Subroutine */ int eqstat_(doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, logical *,
	     logical *, integer *);
    static doublereal xintmu;
    extern /* Subroutine */ int getopac_(doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *);

    /* Fortran I/O blocks */
    static cilist io___69 = { 0, 0, 0, fmt_601, 0 };
    static cilist io___71 = { 0, 0, 0, fmt_93, 0 };


/* DBGLAOL */
/* DBGLAOL */
/* DBG 7/92 COMMON BLOCK ADDED TO COMPUTE DEBYE-HUCKEL CORRECTION. */
/* SEMI-CONVECTION IS TESTED FOR ALL CONVECTIVE REGIONS IN THIS SUBROUTINE. */
/* THE REFERENCE FOR THIS SECTION IS : */
/* CASTELLANI ET AL.(1971)ASTROPHYSICS AND SPACE SCIENCE, VOL. 10, PP.340-349. */

/* AT THE EDGE OF ALL CONVECTIVE REGIONS, THE RADIATIVE TEMPERATURE GRADIENT */
/* IS COMPUTED WITH BOTH THE LOCAL ABUNDANCES AND THOSE IN THE NEIGHBORING */
/* CONVECTION ZONE.  IF DEL(RAD)>DEL(AD) WHEN THE ABUNDANCES ARE PERTURBED, */
/* THEN THE REGION IS CONSIDERED UNSTABLE TO THE GROWTH OF A SEMI-CONVECTIVE */
/* REGION AND THE CODE COMPUTES ITS EXTENT. */

/* INPUT VARIABLES : */

/* DELTS : MODEL TIMESTEP (SECONDS) */
/* HD,HL,HP,HR,HS,HT : MODEL RUN OF DENSITY, LUMINOSITY, PRESSURE, RADIUS, */
/*   MASS, AND TEMPERATURE. */
/* HCOMP : MODEL RUN OF MASS FRACTIONS OF DIFFERENT CHEMICAL SPECIES; */
/*   HCOMP(1,...) IS HYDROGEN AND HCOMP(3,...) IS THE METALS. */
/* MXZONE, NZONE : THE LOCATIONS OF THE EDGES OF CONVECTIVE REGIONS, */
/*   STORED IN PAIRS, AND THE NUMBER OF DISTINCT CONVECTION ZONES. */
/*   E.G. MXZONE(3,1) IS THE ID OF THE BOTTOM SHELL IN THE 3RD CZ FROM */
/*   THE CENTER AND MXZONE(3,2) IS THE ID OF THE TOP SHELL IN THE SAME CZ. */

/* OUTPUT VARIABLES : */

/* MXZONE, NZONE CAN BE ALTERED BY THE SUBROUTINE. */

/* RUN THROUGH ALL THE CONVECTION ZONES. */
    /* Parameter adjustments */
    mxzone -= 13;
    --ht;
    --hs;
    --hr;
    --hp;
    --hl;
    --hd;
    hcomp -= 16;

    /* Function Body */
    i__1 = *nzone;
    for (i__ = 1; i__ <= i__1; ++i__) {
/* DETERMINE IF THIS REGION IS A CORE CONVECTION ZONE, SURFACE CZ, */
/* OR INTERMEDIATE CZ. */
/* LFLAGU IS T IF SEMICONVECTION ABOVE THE CZ NEEDS TO BE COMPUTED; */
/* LFLAGD IS T IF SEMICONVECTION BELOW THE CZ NEEDS TO BE COMPUTED. */
	if (mxzone[i__ + 12] == 1) {
/* CONVECTIVE CORE */
/* CHECK FOR A FULLY CONVECTIVE STAR; SKIP THIS SUBROUTINE IF THERE IS ONE. */
	    if (mxzone[i__ + 24] == *m) {
		return 0;
	    }
	    lflagu = TRUE_;
	    lflagd = FALSE_;
	} else if (mxzone[i__ + 24] == *m) {
/* CONVECTIVE ENVELOPE */
	    lflagu = FALSE_;
	    lflagd = TRUE_;
	} else {
/* INTERMEDIATE CONVECTION ZONE (NOT INCLUDING CENTRAL OR SURFACE POINT). */
	    lflagu = TRUE_;
	    lflagd = TRUE_;
	}
/* CHECK SEMICONVECTION BELOW (K=1) AND ABOVE (K=2) THE CZ. */
	for (k = 1; k <= 2; ++k) {
/* SKIP SEMI-CONVECTION BELOW A CENTRAL CZ AND ABOVE A SURFACE ONE. */
	    if (k == 1 && ! lflagd) {
		goto L200;
	    }
	    if (k == 2 && ! lflagu) {
		goto L200;
	    }
/* JMC AND JMR ARE THE LOCATIONS OF THE EDGE OF THE CONVECTIVE ZONE */
/* AND THE FIRST RADIATIVE POINT OUTSIDE IT RESPECTIVELY. */
	    jmc = mxzone[i__ + k * 12];
	    if (k == 1) {
		jmr = jmc - 1;
	    }
	    if (k == 2) {
		jmr = jmc + 1;
	    }
/* SET UP FLAGS FOR CALLS TO THE BASIC PHYSICS ROUTINES. */
	    lderiv = FALSE_;
	    locond = TRUE_;
	    latmo = TRUE_;
	    ksaha = 0;
/* USE THE STRUCTURE VARIABLES FOR THE FIRST POINT OUTSIDE THE CZ */
/* AND THE ABUNDANCES OF THE CZ TO DETERMINE THE MODIFIED MU AND */
/* RADIATIVE AND ADIABATIC TEMPERATURE GRADIENTS. */
	    b = hl[jmr];
	    sl = hs[jmr];
	    pl = hp[jmr];
	    tl = ht[jmr];
	    dl = hd[jmr];
/* MHP 10/02 added definition of RL */
	    rl = hr[jmr];
	    x = hcomp[jmc * 15 + 1];
	    z__ = hcomp[jmc * 15 + 3];
/* *** ADD ROTATION VECTORS *** */
	    fpl = 1.;
	    ftl = 1.;
	    iu = jmc;
	    if (debhu_1.ldh) {
		debhu_1.xxdh = hcomp[jmc * 15 + 1];
		debhu_1.yydh = hcomp[jmc * 15 + 2] + hcomp[jmc * 15 + 4];
		debhu_1.zzdh = hcomp[jmc * 15 + 3];
		debhu_1.zdh[0] = hcomp[jmc * 15 + 5] + hcomp[jmc * 15 + 6];
		debhu_1.zdh[1] = hcomp[jmc * 15 + 7] + hcomp[jmc * 15 + 8];
		debhu_1.zdh[2] = hcomp[jmc * 15 + 9] + hcomp[jmc * 15 + 10] + 
			hcomp[jmc * 15 + 11];
	    }
	    eqstat_(&tl, &t, &pl, &p, &dl, &d__, &x, &z__, &beta, &beta1, &
		    beta14, fxion, &rmu, &amu, &emu, &eta, &qdt, &qdp, &qcp, &
		    dela, &qdtt, &qdtp, &qat, &qap, &qcpt, &qcpp, &lderiv, &
		    latmo, &ksaha);
/* DBG 12/95 GET OPACITY */
	    getopac_(&dl, &tl, &x, &z__, &o, &ol, &qod, &qot, fxion);
	    tpgrad_(&tl, &t, &pl, &p, &d__, &rl, &sl, &b, &o, &qdt, &qdp, &
		    qot, &qod, &qcp, &del, &delr, &dela, &qdtt, &qdtp, &qat, &
		    qap, &qact, &qacp, &qacr, &qcpt, &qcpp, &vel, &lderiv, &
		    lconv, &fpl, &ftl);
/* SKIP IF ZONE IS STABLE WITH THE CORE COMPOSITION. */
	    if (delr < dela) {
		goto L200;
	    }
/* STORE MEAN MOLECULAR WEIGHT, ADJUSTED RADIATIVE TEMPERATURE GRADIENT, */
/* AND THE QUANTITY (DELR - DELA)/DELR. */
	    xintmu = amu + emu;
	    delr1 = delr;
	    rmax = 1. - dela / delr;
/* REPEAT CALL WITH THE LOCAL COMPOSITION. */
	    x = hcomp[jmr * 15 + 1];
	    z__ = hcomp[jmr * 15 + 3];
	    iu = jmr;
	    if (debhu_1.ldh) {
		debhu_1.xxdh = hcomp[jmr * 15 + 1];
		debhu_1.yydh = hcomp[jmr * 15 + 2] + hcomp[jmr * 15 + 4];
		debhu_1.zzdh = hcomp[jmr * 15 + 3];
		debhu_1.zdh[0] = hcomp[jmr * 15 + 5] + hcomp[jmr * 15 + 6];
		debhu_1.zdh[1] = hcomp[jmr * 15 + 7] + hcomp[jmr * 15 + 8];
		debhu_1.zdh[2] = hcomp[jmr * 15 + 9] + hcomp[jmr * 15 + 10] + 
			hcomp[jmr * 15 + 11];
	    }
	    eqstat_(&tl, &t, &pl, &p, &dl, &d__, &x, &z__, &beta, &beta1, &
		    beta14, fxion, &rmu, &amu, &emu, &eta, &qdt, &qdp, &qcp, &
		    dela, &qdtt, &qdtp, &qat, &qap, &qcpt, &qcpp, &lderiv, &
		    latmo, &ksaha);
/* DBG 12/95 GET OPACITY */
	    getopac_(&dl, &tl, &x, &z__, &o, &ol, &qod, &qot, fxion);
	    tpgrad_(&tl, &t, &pl, &p, &d__, &rl, &sl, &b, &o, &qdt, &qdp, &
		    qot, &qod, &qcp, &del, &delr, &dela, &qdtt, &qdtp, &qat, &
		    qap, &qact, &qacp, &qacr, &qcpt, &qcpp, &vel, &lderiv, &
		    lconv, &fpl, &ftl);
	    hd[jmr] = dl;
/* FDEL IS THE RATIO OF THE GRADIENTS WITH THE OLD COMP AND NEW ONE. */
	    fdel = delr1 / delr;
	    delr0 = delr;
/* RMAX IS THE MAXIMUM RADIAL DISTANCE THAT OVERSHOOT MAY PENETRATE, AND */
/* IS THE TIMESTEP(DELTS) MULTIPLIED BY THE VELOCITY OF PROPAGATION OF */
/* THE INSTABILITY (VP IN EQUATION 5PRIME, P. 347). */
	    rmax = rmax * (hl[jmc] * const_1.clsun / (const1_1.c4pi * 10. * 
		    exp(const1_1.cln * hp[jmc]))) * (*delts / exp(
		    const1_1.cln * (hr[jmc] + hr[jmc])));
/* INITIALIZE SUM. */
	    rsum = 0.;
/* LMAX IS SET TO TRUE IF THE OVERSHOOT REACHES ITS MAXIMUM EXTENT. */
	    lmax = FALSE_;
	    if (k == 1) {
		rval1 = exp(const1_1.cln * hr[jmr + 1]);
		jbeg = jmr - 1;
		jend = 1;
		jstep = -1;
	    } else if (k == 2) {
		rval1 = exp(const1_1.cln * hr[jmr - 1]);
		jbeg = jmr + 1;
		jend = *m;
		jstep = 1;
	    }
	    i__2 = jend;
	    i__3 = jstep;
	    for (ii = jbeg; i__3 < 0 ? ii >= i__2 : ii <= i__2; ii += i__3) {
/* TEST ON MAXIMUM OVERSHOOTING LIMIT IN RADIUS */
		if (k == 1) {
		    rval2 = exp(const1_1.cln * hr[ii + 1]);
		}
		if (k == 2) {
		    rval2 = exp(const1_1.cln * hr[ii - 1]);
		}
		rdiff = rval2 - rval1;
		rsum += (1. - xintmu / (amu + emu)) * rdiff;
		rval1 = rval2;
		if (rsum > rmax) {
		    goto L33;
		}
/* TEST ON RESCALED RAD. GRADIENT FOR CONVECTION */
		b = hl[ii];
		sl = hs[ii];
		pl = hp[ii];
		tl = ht[ii];
		dl = hd[ii];
		x = hcomp[ii * 15 + 1];
		z__ = hcomp[ii * 15 + 3];
		iu = ii;
		if (debhu_1.ldh) {
		    debhu_1.xxdh = hcomp[ii * 15 + 1];
		    debhu_1.yydh = hcomp[ii * 15 + 2] + hcomp[ii * 15 + 4];
		    debhu_1.zzdh = hcomp[ii * 15 + 3];
		    debhu_1.zdh[0] = hcomp[ii * 15 + 5] + hcomp[ii * 15 + 6];
		    debhu_1.zdh[1] = hcomp[ii * 15 + 7] + hcomp[ii * 15 + 8];
		    debhu_1.zdh[2] = hcomp[ii * 15 + 9] + hcomp[ii * 15 + 10] 
			    + hcomp[ii * 15 + 11];
		}
		eqstat_(&tl, &t, &pl, &p, &dl, &d__, &x, &z__, &beta, &beta1, 
			&beta14, fxion, &rmu, &amu, &emu, &eta, &qdt, &qdp, &
			qcp, &dela, &qdtt, &qdtp, &qat, &qap, &qcpt, &qcpp, &
			lderiv, &latmo, &ksaha);
/* DBG 12/95 GET OPACITY */
		getopac_(&dl, &tl, &x, &z__, &o, &ol, &qod, &qot, fxion);
		tpgrad_(&tl, &t, &pl, &p, &d__, &rl, &sl, &b, &o, &qdt, &qdp, 
			&qot, &qod, &qcp, &del, &delr, &dela, &qdtt, &qdtp, &
			qat, &qap, &qact, &qacp, &qacr, &qcpt, &qcpp, &vel, &
			lderiv, &lconv, &fpl, &ftl);
		hd[ii] = dl;
/* EXIT IF ZONE IS RADIATIVELY STABLE. */
		if (fdel * delr < dela) {
		    goto L34;
		}
/* L32: */
	    }
	    if (k == 1) {
		ii = 0;
	    }
	    if (k == 2) {
		ii = *m + 1;
	    }
L33:
	    lmax = TRUE_;
L34:
/* ASSIGN THE NEW EDGE LOCATION TO MXZONE. */
	    if (k == 1) {
		mxzone[i__ + k * 12] = ii + 1;
		jmc2 = ii + 1;
	    } else if (k == 2) {
		mxzone[i__ + k * 12] = ii - 1;
		jmc2 = ii - 1;
	    }
	    io___69.ciunit = luout_1.ishort;
	    s_wsfe(&io___69);
	    do_fio(&c__1, (char *)&jmc, (ftnlen)sizeof(integer));
	    do_fio(&c__1, (char *)&jmc2, (ftnlen)sizeof(integer));
	    do_fio(&c__1, (char *)&lmax, (ftnlen)sizeof(logical));
	    do_fio(&c__1, (char *)&delr1, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&delr0, (ftnlen)sizeof(doublereal));
	    e_wsfe();
L200:
	    ;
	}
/* L210: */
    }
/*  CHECK FOR MERGERS OF NEARBY CONVECTION ZONES CAUSED BY SEMI-CONVECTION. */
    if (*nzone <= 1) {
	return 0;
    }
    j = 1;
L85:
/*  CHECK IF 'TOP' OF ONE REGION IS ABOVE 'BOTTOM' OF THE NEXT ONE. */
    if (mxzone[j + 24] > mxzone[j + 13]) {
/*  IF THIS OCCURS, TWO CONVECTION ZONES HAVE MERGED. */
	io___71.ciunit = luout_1.ishort;
	s_wsfe(&io___71);
	i__1 = j + 1;
	for (k = j; k <= i__1; ++k) {
	    for (k1 = 1; k1 <= 2; ++k1) {
		do_fio(&c__1, (char *)&mxzone[k + k1 * 12], (ftnlen)sizeof(
			integer));
	    }
	}
	do_fio(&c__1, (char *)&mxzone[j + 12], (ftnlen)sizeof(integer));
	do_fio(&c__1, (char *)&mxzone[j + 25], (ftnlen)sizeof(integer));
	e_wsfe();
	mxzone[j + 13] = mxzone[j + 12];
	i__1 = *nzone - 1;
	for (k = j; k <= i__1; ++k) {
	    for (j2 = 1; j2 <= 2; ++j2) {
		mxzone[k + j2 * 12] = mxzone[k + 1 + j2 * 12];
/* L95: */
	    }
/* L90: */
	}
	--(*nzone);
	if (j <= *nzone - 1) {
	    goto L85;
	} else {
	    return 0;
	}
    }
    ++j;
    if (j <= *nzone - 1) {
	goto L85;
    }
    return 0;
} /* sconvec_ */

