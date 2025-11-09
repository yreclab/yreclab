/* mix.f -- translated by f2c (version 20061008).
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
    integer ilast, idebug, itrack, ishort, imilne, imodpt, istor, iowr;
} luout_;

#define luout_1 luout_

struct {
    doublereal hcompm[75000]	/* was [15][5000] */;
} burn_;

#define burn_1 burn_

struct {
    doublereal xenv, zenv, zenvm, amuenv, fxenv[12], xnew, znew, stotal, senv;
} comp_;

#define comp_1 comp_

struct {
    doublereal cln, clni, c4pi, c4pil, c4pi3l, cc13, cc23, cpi;
} const1_;

#define const1_1 const1_

struct {
    doublereal cgas, ca3, ca3l, csig, csigl, cgl, cmkh, cmkhn;
} const2_;

#define const2_1 const2_

struct {
    doublereal cdelrl, cmixl, cmixl2, cmixl3, clndp, csecyr;
} const3_;

#define const3_1 const3_

struct {
    doublereal atime[14], tcut[5], tscut, tenv0, tenv1, tenv, tgcut;
} ctlim_;

#define ctlim_1 ctlim_

struct {
    doublereal drate[5000], drate0[5000], fmassacc;
    integer jcz;
} deuter_;

#define deuter_1 deuter_

struct {
    doublereal dpenv, alphac, alphae, alpham, betac;
    integer iov1, iov2, iovim;
    logical lovstc, lovste, lovstm, lsemic, ladov, lovmax;
} dpmix_;

#define dpmix_1 dpmix_

struct {
    logical lexcom;
} flag_;

#define flag_1 flag_

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
    doublereal hpo[5000], hto[5000], hro[5000], hlo[5000], hdo[5000], hcompp[
	    75000]	/* was [15][5000] */, hss[5000];
    logical lco[5000], lczo[5000];
    doublereal tefflo;
    integer mo;
} oldmod_;

#define oldmod_1 oldmod_

struct {
    integer niter4;
    logical lnews, lsnu;
} neweng_;

#define neweng_1 neweng_

struct {
    doublereal dage;
} theage_;

#define theage_1 theage_

struct {
    doublereal dmdt0, fczdmdt, ftotdmdt, compacc[15], creim;
    logical lreimer, lmdot;
} masschg_;

#define masschg_1 masschg_

/* Table of constant values */

static integer c__1 = 1;

/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */
/* MIX */
/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */
/* THE ENERGY GENERATION ROUTINE (ENGEB) IS USED FOR CALCULATIONS OF */
/*    EPSILON AND ITS DERIVATIVES IN THE HENYEY PORTION OF THE CODE (COEFFT) */
/* PRIOR TO CALLING MIX THE FIRST TIME, STORE ORIGINAL VARIABLES IN VECTOR */
/*    HCOMPP.  REZONE HCOMPP ALONG WITH HCOMP IN HPOINT. */
/* THE MIX IS CALLED PRIOR TO REZONING AND ON THE THIRD LEVEL OF */
/*    ITERATION IN THE HENYEY PORTION. */

/* OUTLINE OF MIX : */

/* 1) CALL CONVEC TO DETERMINE LOCATION OF CZ EDGES AND EDGES OF MIXED */
/*    REGIONS WITH OVERSHOOT. */
/* 2) DETERMINE RUN OF RATES FOR GIVEN RUN OF COMP, RHO, T. */
/*    IF DESIRED, THE SR SPITS OUT SOLAR NEUTRINO FLUXES TO I/O UNIT ISNU. */
/* 3) USE KEMCOM TO IMPLICITLY SOLVE FOR ABUNDANCES IN RADIATIVE REGIONS. */
/* 4) SOLVE FOR BURNING IN EACH CONVECTION ZONE. */
/* 5) COMPUTE SEMI-CONVECTION IF DESIRED. */
/* 6) COMPUTE MICROSCOPIC DIFFUSION IF DESIRED. */

/* THE RATE SUBROUTINE CALLED BY MIX IS A STRIPPED-DOWN VERSION OF ENGEB */
/* (CALLED NRATE) WHICH HAS NO DERIVATIVES OR ENERGY YIELDS.  IT DOES */
/* CONTAIN NEUTRINO FLUXES FOR SOLAR NEUTRINO CALCULATIONS. */
/* Subroutine */ int mix_(doublereal *delts, doublereal *hcomp, doublereal *
	hd, doublereal *hl, doublereal *hp, doublereal *hr, doublereal *hs, 
	doublereal *hs1, doublereal *hs2, doublereal *hstot, doublereal *ht, 
	integer *itlvl, logical *lc, integer *m, doublereal *ddage, integer *
	jcore, integer *jenv, integer *mxzone, integer *mxzon0, doublereal *
	teffl)
{
    /* Format strings */
    static char fmt_110[] = "(\002 ZONES MIXED IN ORDER--\002,12(\002(\002,i"
	    "5,\002,\002,i5,\002) \002))";
    static char fmt_911[] = "(1x,\002NO SURFACE CZ - DIFFUSION NOT MEANING"
	    "FUL\002)";

    /* System generated locals */
    integer i__1, i__2, i__3;
    doublereal d__1, d__2;

    /* Builtin functions */
    double exp(doublereal);
    integer s_wsfe(cilist *), do_fio(integer *, char *, ftnlen), e_wsfe(void);
    double d_mod(doublereal *, doublereal *);

    /* Local variables */
    extern /* Subroutine */ int deutrate_(doublereal *, doublereal *, 
	    doublereal *, integer *, integer *);
    static integer i__, j, k;
    static doublereal x, y, z__;
    extern /* Subroutine */ int microdiff_(doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, logical *, integer *, doublereal *);
    static integer i1, i2;
    static doublereal dl;
    static integer ii;
    static doublereal fm;
    static integer jj;
    static doublereal dt, tl;
    static integer ns;
    static doublereal hf1[5000], hf2[5000], hr1[5000], hr2[5000], hr3[5000], 
	    hr4[5000], hr5[5000], hr6[5000], hr7[5000], hr8[5000], hr9[5000], 
	    xh2;
    static logical lcc[5000];
    static doublereal hr10[5000], hr11[5000], hr12[5000], hr13[5000], xc12, 
	    xc13, xn14, xn15, xo16, xo17, xo18, xhe3, xbe9, xli6, xli7, dcdt;
    static integer iend;
    static doublereal dodt, dxdt, dydt, hqpr[5000], stot, xsum[15];
    static integer nspec;
    static doublereal hsmax;
    extern /* Subroutine */ int rates_(doublereal *, doublereal *, doublereal 
	    *, doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, integer *, doublereal *,
	     doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *);
    static doublereal dtmax;
    extern /* Subroutine */ int dburn_(integer *, integer *, integer *, 
	    doublereal *, doublereal *, doublereal *);
    static integer nzone, nstep;
    static doublereal wtsum;
    static integer nzone0, ibegin;
    extern /* Subroutine */ int kemcom_(doublereal *, integer *, integer *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *), convec_(doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, logical *, integer *, integer *, integer *, integer 
	    *, integer *, integer *, integer *, integer *, integer *);
    static doublereal tscale;
    extern /* Subroutine */ int eqburn_(doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, integer *, integer *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *), grsett_(doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, logical *, integer *, doublereal *);
    static integer mrzone[26]	/* was [13][2] */, nrzone;
    static doublereal xh2test;
    extern /* Subroutine */ int sconvec_(doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, integer *, integer *, integer *, 
	    doublereal *);

    /* Fortran I/O blocks */
    static cilist io___57 = { 0, 0, 0, fmt_110, 0 };
    static cilist io___60 = { 0, 0, 0, fmt_911, 0 };


/*      *     HT,ITLVL,LC,M,QDT,QDP,DDAGE,JCORE,JENV,  ! KC 2025-05-31 */
/* ***MHP COMMON BLOCK ADDED FOR G.S. */
/* MHP 05/02 DEUTERIUM BURNING RATE ADDED */
/* *** MHP 5/90 ADD COMMON BLOCK FOR GRAVITATIONAL SETTLING. */
/* *** MHP 6/90 ADDITIONAL COMMON BLOCK FOR SETTLING. */
/* GES 6/15 INCLUDED COMMON BLOCK FOR NEW DIFFUSION ROUTINES. */
/* *** MHP 6/91 COMMON BLOCK FOR NEW MIXING AND SEMI-CONVECTION. */
/* THESE ARE PARMIN PARAMETERS IN MARK6. */
/* ADDED FOR MASS ACCRETION */
/*       DATA BURMIN/1.0D-30/ */
/* MHP 1/95 */
/* NSPEC IS THE NUMBER OF SPECIES BEING TRACKED. */
    /* Parameter adjustments */
    mxzon0 -= 13;
    mxzone -= 13;
    --lc;
    --ht;
    --hs2;
    --hs1;
    --hs;
    --hr;
    --hp;
    --hl;
    --hd;
    hcomp -= 16;

    /* Function Body */
    if (flag_1.lexcom) {
	nspec = 15;
    } else {
	nspec = 11;
    }
/*  DDAGE IS THE TIMESTEP IN YEARS. */
    *ddage = *delts / const3_1.csecyr;

/* DETERMINE THE LOCATION OF CONVECTION ZONES WITH AND WITHOUT OVERSHOOT. */

/* ******* INTRODUCE DPENV PARAMETER FOR DEEP MIXING ******************* */
/*  DPENV MIXES THE STAR FROM THE SURFACE TO MASS FRACTION DPENV */
/*  E.G. DPENV = 0.7 MEANS THE OUTER .3 OF THE STAR IS MIXED */
    if (dpmix_1.dpenv < 1. && *itlvl > 1) {
/* MIX FROM CENTER TO A FIXED MASS FRACTION */
	hsmax = dpmix_1.dpenv * exp(const1_1.cln * *hstot);
	i__1 = *m;
	for (i__ = 1; i__ <= i__1; ++i__) {
	    if (hs1[i__] > hsmax) {
		i__2 = *m;
		for (j = i__; j <= i__2; ++j) {
		    lcc[j - 1] = lc[j];
		}
		goto L5;
	    } else {
		lcc[i__ - 1] = TRUE_;
	    }
	}
/* MHP 1/95 CHANGE - DPENV MIXES TO A FIXED FRACTION OF THE MAXIMUM */
/* LUMINOSITY. */
/*         HLMAX = HL(1) */
/*         IMAX = 1 */
/*         DO I = 2,M */
/*            IF(HL(I).GT.HLMAX)THEN */
/*               HLMAX = HL(I) */
/*               IMAX = I */
/*            ENDIF */
/*         END DO */
/*         HLTEST = HLMAX*DPENV */
/*         DO I = 1,M */
/*            IF(HL(I).LE.HLTEST)THEN */
/*               LCC(I) = LC(I) */
/*            ELSE */
/*               DO J = I,M */
/*                  LCC(J) = .TRUE. */
/*               END DO */
/*               GOTO 5 */
/*            ENDIF */
/*         END DO */
L5:
	;
    } else {
	i__1 = *m;
	for (j = 1; j <= i__1; ++j) {
	    lcc[j - 1] = lc[j];
	}
    }
    convec_(&hcomp[16], &hd[1], &hp[1], &hr[1], &hs[1], &ht[1], lcc, m, 
	    mrzone, &mxzone[13], &mxzon0[13], jcore, jenv, &nrzone, &nzone, &
	    nzone0);
/* FIND BURNING RATES (HR1- HR13,HF1,HF2). */
    if (masschg_1.lmdot && masschg_1.dmdt0 > 0.) {
/* Computing MAX */
	d__1 = hcomp[*m * 15 + 12];
	xh2test = max(d__1,masschg_1.compacc[11]);
    } else {
	xh2test = hcomp[*m * 15 + 12];
    }
    i__1 = *m;
    for (i__ = 1; i__ <= i__1; ++i__) {
/* EXIT LOOP ONCE T DROPS BELOW NUCLEAR REACTION T CUTOFF */
	if (ht[i__] <= ctlim_1.tcut[0]) {
	    goto L20;
	}
/* SCALAR VARIABLES ARE USED IN THE CALLS TO THE ENERGY GENERATION ROUTINES. */
/* SET SCALARS EQUAL TO THE GLOBAL ARRAYS FOR THE VARIABLES OF INTEREST. */
/* DL-LOG(DENSITY),TL-LOG TEMPERATURE,X***-MASS FRACTION OF SPECIES ***, */
/* WITH HYDROGEN,HELIUM,AND METALS DENOTED AS USUAL BY X,Y,Z. */
	dl = hd[i__];
	tl = ht[i__];
	x = hcomp[i__ * 15 + 1];
	y = hcomp[i__ * 15 + 2];
	z__ = hcomp[i__ * 15 + 3];
	xhe3 = hcomp[i__ * 15 + 4];
	xc12 = hcomp[i__ * 15 + 5];
	xc13 = hcomp[i__ * 15 + 6];
	xn14 = hcomp[i__ * 15 + 7];
	xn15 = hcomp[i__ * 15 + 8];
	xo16 = hcomp[i__ * 15 + 9];
	xo17 = hcomp[i__ * 15 + 10];
	xo18 = hcomp[i__ * 15 + 11];
	xh2 = hcomp[i__ * 15 + 12];
	xli6 = hcomp[i__ * 15 + 13];
	xli7 = hcomp[i__ * 15 + 14];
	xbe9 = hcomp[i__ * 15 + 15];
/* SETUP NUCLEAR ENERGY TERMS */
/*          CALL RATES(DL,TL,X,Y,Z,XHE3,XC12,XC13,XN14,XN15, */
/*      *        XO16,XO17,XO18,XH2,XLI6,XLI7,XBE9,I,HR1,HR2,HR3,HR4,  ! KC 2025-05-31 */
	rates_(&dl, &tl, &x, &y, &xhe3, &xc12, &xc13, &xn14, &xo16, &xo18, &
		i__, hr1, hr2, hr3, hr4, hr5, hr6, hr7, hr8, hr9, hr10, hr11, 
		hr12, hr13, hf1, hf2);
/* MHP 5/02 COMPUTE RATE FOR DEUTERIUM BURNING */
	if (xh2test > 1e-11) {
/*             CALL DEUTRATE(DL,TL,X,XH2,I,ITLVL)  ! KC 2025-05-31 */
	    deutrate_(&dl, &tl, &x, &i__, itlvl);
	} else {
	    deuter_1.drate[i__ - 1] = 0.;
	}
/* L10: */
    }
    i__ = *m + 1;
L20:
    i__1 = *m;
    for (ii = i__; ii <= i__1; ++ii) {
	hr1[ii - 1] = 0.;
	hr2[ii - 1] = 0.;
	hr3[ii - 1] = 0.;
	hr4[ii - 1] = 0.;
	hr5[ii - 1] = 0.;
	hr6[ii - 1] = 0.;
	hr7[ii - 1] = 0.;
	hr8[ii - 1] = 0.;
	hr9[ii - 1] = 0.;
	hr10[ii - 1] = 0.;
	hr11[ii - 1] = 0.;
	hr12[ii - 1] = 0.;
	hr13[ii - 1] = 0.;
	hf1[ii - 1] = 0.;
	hf2[ii - 1] = 0.;
/* MHP 5/02 ZERO OUT DEUTERIUM BURNING RATE */
	deuter_1.drate[ii - 1] = 0.;
/* L21: */
    }
/*    22 FORMAT(5X,1P5E12.4/5X,E12.4) */
/*      WRITE(*,912)ITLVL,(DRATE(III),III=1,5), */
/*     *            (HT(JJJ),JJJ=1,5) */
/* 912  FORMAT(I2,1P5E14.6/2X,5E14.6) */

/*  NOW IMPLICITLY SOLVE FOR THE NEW ABUNDANCES AT THE END OF THE */
/*  TIMESTEP.  THIS IS DONE SHELL BY SHELL FOR RADIATIVE REGIONS, */
/*  AND FOR EACH CONVECTION ZONE AS A UNIT. */

/* RADIATIVE ZONES. */

    i__1 = nrzone;
    for (k = 1; k <= i__1; ++k) {
	i__2 = mrzone[k + 12];
	for (j = mrzone[k - 1]; j <= i__2; ++j) {
/* EXIT LOOP ONCE T DROPS BELOW NUCLEAR REACTION T CUTOFF */
	    if (ht[j] <= ctlim_1.tcut[0]) {
		goto L45;
	    }
	    ibegin = j;
	    iend = j;
	    kemcom_(&ht[1], &ibegin, &iend, hr1, hr2, hr3, hr4, hr5, hr6, hr7,
		     hr8, hr10, hr11, hr12, hf1, &hs2[1], &hcomp[16], ddage);
/*      *           HR7,HR8,HR9,HR10,HR11,HR12,HR13,HF1,HS2,HCOMP, */
/*      *           DDAGE,ITLVL)  ! KC 2025-05-31 */
/* L30: */
	}
/* L40: */
    }
L45:

/* CONVECTION ZONES. */
/* NOTE KEMCOM ALSO AUTOMATICALLY HOMOGENIZE CONVECTION ZONES. */

    i__1 = nzone;
    for (k = 1; k <= i__1; ++k) {
	ibegin = mxzone[k + 12];
	iend = mxzone[k + 24];
	kemcom_(&ht[1], &ibegin, &iend, hr1, hr2, hr3, hr4, hr5, hr6, hr7, 
		hr8, hr10, hr11, hr12, hf1, &hs2[1], &hcomp[16], ddage);
/*      *        HR7,HR8,HR9,HR10,HR11,HR12,HR13,HF1,HS2,HCOMP, */
/*      *        DDAGE,ITLVL)  ! KC 2025-05-31 */
/* L50: */
    }
/*    51 CONTINUE */
    i__1 = *m;
    for (i__ = 1; i__ <= i__1; ++i__) {
	burn_1.hcompm[i__ * 15 - 15] = hr1[i__ - 1];
	burn_1.hcompm[i__ * 15 - 14] = hr2[i__ - 1];
	burn_1.hcompm[i__ * 15 - 13] = hr3[i__ - 1];
	burn_1.hcompm[i__ * 15 - 12] = hr4[i__ - 1];
	burn_1.hcompm[i__ * 15 - 11] = hr5[i__ - 1];
	burn_1.hcompm[i__ * 15 - 10] = hr6[i__ - 1];
	burn_1.hcompm[i__ * 15 - 9] = hr7[i__ - 1];
	burn_1.hcompm[i__ * 15 - 8] = hr8[i__ - 1];
	burn_1.hcompm[i__ * 15 - 7] = hr9[i__ - 1];
	burn_1.hcompm[i__ * 15 - 6] = hr10[i__ - 1];
	burn_1.hcompm[i__ * 15 - 5] = hr11[i__ - 1];
	burn_1.hcompm[i__ * 15 - 4] = hr12[i__ - 1];
	burn_1.hcompm[i__ * 15 - 3] = hr13[i__ - 1];
	burn_1.hcompm[i__ * 15 - 2] = hf1[i__ - 1];
	burn_1.hcompm[i__ * 15 - 1] = hf2[i__ - 1];
    }

/* IF ITLVL=1 THEN THE RATES OF HYDROGEN AND HELIUM BURNING ARE */
/*   COMPUTED EXPLICITLY ASSUMING EQUILIBRIUM HE3 AND CN. */
/*   IF THIS IS THE CASE, CALL OLD ENERGY GENERATION ROUTINE AND */
/*   OVERWRITE THE HYDROGEN ABUNDANCES (H BURNING) AND Z,C12,O16 */
/*   ABUNDANCES (HE BURNING). */
    if (*itlvl == 1) {

/*  EXPLICITLY SOLVE FOR THE NEW HYDROGEN AND HELIUM BURNING RATES */
/*  AT THE BEGINNING OF THE TIMESTEP, ASSUMING EQUILIBRIUM HE3 AND CN */
/*  CYCLE ABUNDANCES.  THIS IS DONE SHELL BY SHELL FOR RADIATIVE REGIONS, */
/*  AND FOR EACH CONVECTION ZONE AS A UNIT. */

/* RADIATIVE ZONES. */

	dt = *ddage * 1e-9;
	i__1 = nrzone;
	for (k = 1; k <= i__1; ++k) {
	    i__2 = mrzone[k + 12];
	    for (j = mrzone[k - 1]; j <= i__2; ++j) {
/* EXIT LOOP ONCE T DROPS BELOW NUCLEAR REACTION T CUTOFF */
		if (ht[j] <= ctlim_1.tcut[0]) {
		    goto L60;
		}
		ibegin = j;
		iend = j;
/*                CALL EQBURN(HF1,HR1,HR2,HR3,HR4,HR5,HR6,HR7, */
/*      *              HR8,HR9,HR10,HR11,HR12,HS2,HT,IBEGIN,IEND,  ! KC 2025-05-31 */
		eqburn_(hr1, hr2, hr3, hr4, hr5, hr6, hr7, hr10, hr12, &hs2[1]
			, &ht[1], &ibegin, &iend, &dcdt, &dodt, &dxdt, &dydt, 
			&xc12, &xo16, &x, &z__);
/*  USE THE EXPLICIT HYDROGEN BURNING RATE. */
		if (dxdt != 0.) {
		    hcomp[j * 15 + 1] = x + dxdt * dt;
		}
/*  USE THE HELIUM BURNING RATE FROM EQBURN AND THE CARBON,ALPHA */
/*  BURNING RATE */
		if (dydt != 0.) {
		    hcomp[j * 15 + 3] = z__ - dydt * dt;
		    hcomp[j * 15 + 5] = xc12 + dcdt * dt;
		    hcomp[j * 15 + 9] = xo16 + dodt * dt;
		}
	    }
	}
L60:

/* CONVECTION ZONES. */
/* NOTE KEMCOM ALSO AUTOMATICALLY HOMOGENIZE CONVECTION ZONES. */

	i__1 = nzone;
	for (k = 1; k <= i__1; ++k) {
	    ibegin = mxzone[k + 12];
	    iend = mxzone[k + 24];
/*             CALL EQBURN(HF1,HR1,HR2,HR3,HR4,HR5,HR6,HR7,HR8, */
/*      *           HR9,HR10,HR11,HR12,HS2,HT,IBEGIN,IEND,  ! KC 2025-05-31 */
	    eqburn_(hr1, hr2, hr3, hr4, hr5, hr6, hr7, hr10, hr12, &hs2[1], &
		    ht[1], &ibegin, &iend, &dcdt, &dodt, &dxdt, &dydt, &xc12, 
		    &xo16, &x, &z__);
/*  USE THE EXPLICIT HYDROGEN BURNING RATE. */
	    if (dxdt != 0.) {
		x += dxdt * dt;
		i__2 = iend;
		for (i__ = ibegin; i__ <= i__2; ++i__) {
		    hcomp[i__ * 15 + 1] = x;
		}
	    }
/*  USE THE HELIUM BURNING RATE FROM EQBURN AND THE CARBON,ALPHA */
/*  BURNING RATE */
	    if (dydt != 0.) {
		z__ -= dydt * dt;
		xc12 += dcdt * dt;
		xo16 += dodt * dt;
		i__2 = iend;
		for (i__ = ibegin; i__ <= i__2; ++i__) {
		    hcomp[i__ * 15 + 3] = z__;
		    hcomp[i__ * 15 + 5] = xc12;
		    hcomp[i__ * 15 + 9] = xo16;
		}
	    }
	}
    }

/* DETERMINE EXTENT OF SEMI-CONVECTION IF APPLICABLE. */

    if (dpmix_1.lsemic) {
	if (*itlvl > 1) {
	    sconvec_(delts, &hcomp[16], &hd[1], &hl[1], &hp[1], &hr[1], &hs[1]
		    , &ht[1], m, &mxzone[13], &nzone, teffl);
	}
    }
    if (dpmix_1.lsemic || *itlvl == 1) {

/*    MIX CONVECTIVE REGIONS IN ORDER. */
/*    THIS NEEDS TO BE DONE IF SEMI-CONVECTION IS BEING CHECKED, OR */
/*    IF EXPLICIT H AND HE BURNING IS BEING DONE. */

/* NZONE IS THE NUMBER OF DISTINCT CONVECTION ZONES. */
/* MXZONE(J,1) AND MXZONE(J,2) ARE THE FIRST AND LAST SHELLS CONTAINED */
/* IN THE JTH CONVECTION ZONE. */
	i__1 = nzone;
	for (j = 1; j <= i__1; ++j) {
/* I1 AND I2 ARE THE FIRST AND LAST CONVECTIVE SHELLS IN THE GIVEN REGION. */
	    i1 = mxzone[j + 12];
	    i2 = mxzone[j + 24];
	    if (i1 != 1 && i1 >= i2) {
		goto L100;
	    }
/* INITIALIZE SUMS. */
	    wtsum = 0.;
	    i__2 = nspec;
	    for (i__ = 1; i__ <= i__2; ++i__) {
		xsum[i__ - 1] = 0.;
/* L55: */
	    }
/*  ADD UP THE TOTAL MASS OF EACH SPECIES IN THE CONVECTIVE REGION. */
/*  (HS2 IS THE MASS CONTAINED WITHIN A SHELL IN GRAMS). */
	    i__2 = i2;
	    for (jj = i1; jj <= i__2; ++jj) {
		wtsum += hs2[jj];
		i__3 = nspec;
		for (i__ = 1; i__ <= i__3; ++i__) {
		    xsum[i__ - 1] += hcomp[i__ + jj * 15] * hs2[jj];
/* L61: */
		}
/* L65: */
	    }
/*  DIVIDE BY THE TOTAL MASS TO FIND THE MEAN MASS FRACTION IN THE REGION. */
	    i__2 = nspec;
	    for (i__ = 1; i__ <= i__2; ++i__) {
		xsum[i__ - 1] /= wtsum;
/* L70: */
	    }
/*  APPLY THE MEAN MASS FRACTION OF ALL SPECIES THROUGHOUT THE CZ. */
	    i__2 = i2;
	    for (jj = i1; jj <= i__2; ++jj) {
		i__3 = nspec;
		for (i__ = 1; i__ <= i__3; ++i__) {
		    hcomp[i__ + jj * 15] = xsum[i__ - 1];
/* L80: */
		}
/* L90: */
	    }
L100:
	    ;
	}
    }
/*  WRITE OUT THE LOCATIONS OF MIXED REGIONS. */
    if (nzone >= 1) {
	io___57.ciunit = luout_1.ishort;
	s_wsfe(&io___57);
	i__1 = nzone;
	for (i__ = 1; i__ <= i__1; ++i__) {
	    for (j = 1; j <= 2; ++j) {
		do_fio(&c__1, (char *)&mxzone[i__ + j * 12], (ftnlen)sizeof(
			integer));
	    }
	}
	e_wsfe();
    }

/* MICROSCOPIC DIFFUSION OF HELIUM. */

/* ***MHP 12/89 MIX MODIFIED TO INCLUDE CALL TO GRAVITATIONAL SETTLING */
/*      ROUTINE USING THE BAHCALL AND LOEB METHOD. */
/* FIRST DEFINE VARIABLES NEEDED FOR SETTLING - */
/* HQPR=VECTOR OF D LN P/DR. */
/* STOT=TOTAL STELLAR MASS(UNLOGGED). */
    if (gravst_1.ldify) {
	if (hcomp[16] < gravs2_1.xmin) {
	    gravst_1.ldify = FALSE_;
	    goto L170;
	}
	stot = exp(const1_1.cln * *hstot);
	i__1 = *m;
	for (i__ = 1; i__ <= i__1; ++i__) {
	    hqpr[i__ - 1] = -exp(const1_1.cln * (hd[i__] + const2_1.cgl + hs[
		    i__] - hr[i__] * 2. - hp[i__]));
/* L130: */
	}
/* MHP 6/90 CHANGE ADDED : THE TIMESTEP FOR SETTLING IS RESTRICTED TO */
/*   A FRACTION OF THE TIMESCALE FOR SETTLING AT THE OUTER BOUNDARY. */
/*   THE OUTER BOUNDARY IS EITHER THE SURFACE CONVECTION ZONE OR THE */
/*   FIRST POINT WHERE THE HELIUM ABUNDANCE RISES ABOVE A USER-SPECIFIED */
/*   MINIMUM VALUE (YMIN). */

/*   LOCATE OUTER BOUNDARY. */
	if (! lc[*m]) {
	    io___60.ciunit = luout_1.ishort;
	    s_wsfe(&io___60);
	    e_wsfe();
/* DBG 2/92 CHANGED STOP TO JUST A WARNING MESSAGE, EXECUTION CONTINUES */
	    goto L170;
	}
	for (j = *jenv; j >= 1; --j) {
	    if (hcomp[j * 15 + 2] > gravs2_1.ymin) {
		goto L150;
	    }
/* L140: */
	}
/*   Y<YMIN FOR THE WHOLE STAR IF THE CODE GETS HERE. */
	goto L170;
L150:
/*  FM IS THE MASS FRACTION ABOVE THE OUTER POINT. */
	fm = (stot - hs1[j]) / stot;
/*  TSCALE IS THE TIMESCALE FOR SETTLING OF HELIUM AT THE OUTER */
/*  BOUNDARY (MICHAUD ET AL 1984, APJ V.282,P.206) */
	tscale = const3_1.csecyr * 4.348e21 * fm / exp(const1_1.cln * 1.5 * 
		ht[j]);
/*  RESTRICT TIMESTEP TO THE MINIMUM OF THE MODEL TIMESTEP AND */
/*  A USER SPECIFIED FRACTION (DT_GS) OF THE SETTLING TIMESCALE. */
	dtmax = gravs2_1.dt_gs__ * tscale;
	nstep = (integer) (*delts / dtmax);
	if (d_mod(&dtmax, delts) != 0.) {
	    ++nstep;
	}
	dt = *delts / (doublereal) nstep;
	i__1 = nstep;
	for (ns = 1; ns <= i__1; ++ns) {
/* PERFORM GRAVITATIONAL SETTLING. IF LNEWDIF = TRUE, USE THE NEW ROUTINES */
/* IN MICRODIFF. ELSE, USE THE OLD ROUTINES IN GRSETT. */
	    if (gravs4_1.lnewdif) {
		microdiff_(&dt, &hcomp[16], hqpr, &hr[1], &hd[1], &hs1[1], &
			ht[1], lcc, m, &stot);
	    } else {
		grsett_(&dt, &hcomp[16], hqpr, &hr[1], &hd[1], &hs1[1], &ht[1]
			, lcc, m, &stot);
	    }
/* L160: */
	}
L170:
	;
    }
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
/* MHP 1/95 ADDED CALL TO RESET JENV,JCORE FOR DEEP MIXING. */
    if (dpmix_1.dpenv < 1. && *itlvl > 1) {
	convec_(&hcomp[16], &hd[1], &hp[1], &hr[1], &hs[1], &ht[1], &lc[1], m,
		 mrzone, &mxzone[13], &mxzon0[13], jcore, jenv, &nrzone, &
		nzone, &nzone0);
    }
/* MHP 5/02 ADDED DEUTERIUM BURNING */
    if (flag_1.lexcom) {
/* RADIATIVE ZONES. */

	dt = *ddage * 1e-9;
	i__1 = nrzone;
	for (k = 1; k <= i__1; ++k) {
	    i__2 = mrzone[k + 12];
	    for (j = mrzone[k - 1]; j <= i__2; ++j) {
/* EXIT LOOP ONCE T DROPS BELOW NUCLEAR REACTION T CUTOFF */
		if (ht[j] <= ctlim_1.tcut[0]) {
		    goto L190;
		}
		ibegin = j;
		iend = j;
		dburn_(&ibegin, &iend, m, &hs2[1], &hcomp[16], &dt);
	    }
	}
L190:

/* CONVECTION ZONES. */
/* NOTE KEMCOM ALSO AUTOMATICALLY HOMOGENIZE CONVECTION ZONES. */

	i__1 = nzone;
	for (k = 1; k <= i__1; ++k) {
	    ibegin = mxzone[k + 12];
	    iend = mxzone[k + 24];
	    dburn_(&ibegin, &iend, m, &hs2[1], &hcomp[16], &dt);
	}
    }
    return 0;
} /* mix_ */

