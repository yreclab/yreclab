/* microdiff_cod.f -- translated by f2c (version 20061008).
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
    doublereal cln, clni, c4pi, c4pil, c4pi3l, cc13, cc23, cpi;
} const1_;

#define const1_1 const1_

struct {
    doublereal sesum[5000], seg[35000]	/* was [7][5000] */, sbeta[5000], 
	    seta[5000];
    logical locons[5000];
    doublereal so[5000], sdel[15000]	/* was [3][5000] */, sfxion[15000]	
	    /* was [3][5000] */, svel[5000], scp[5000];
} scrtch_;

#define scrtch_1 scrtch_

struct {
    doublereal dage;
} theage_;

#define theage_1 theage_

/* Table of constant values */

static doublereal c_b3 = 1.2;
static doublereal c_b4 = 2.5;

/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */
/* MICRODIFF_COD */
/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */
/* Subroutine */ int microdiff_cod__(integer *npt, doublereal *espec, 
	doublereal *er, doublereal *eden, doublereal *etem, doublereal *ehqpr,
	 doublereal *edelr, doublereal *ecod1, doublereal *ecod2, doublereal *
	edxdr, doublereal *thea, doublereal *thez, integer *j)
{
    /* Initialized data */

    static integer nspec = 4;

    /* System generated locals */
    integer i__1, i__2, i__3;
    doublereal d__1;

    /* Builtin functions */
    double pow_dd(doublereal *, doublereal *), sqrt(doublereal), log(
	    doublereal);

    /* Local variables */
    static doublereal con_temp__;
    static integer i__;
    static doublereal t, ln_lambda__, t1, t2, ac, ad, ah, ao, ap;
    static integer ii;
    static doublereal ne;
    static integer jj;
    static doublereal at, ni, cz, fac, tac[16]	/* was [4][4] */, ads[5000], 
	    ahs[5000], tcl[16]	/* was [4][4] */, aps[5000], tap[4], ats[5000]
	    , tat[4], rho, xij, zxa, facs[5000], coni, dradi, xfrac[4], 
	    hru_i__, htu_i__, zspec[4], conim1, conip1, lambda;
    extern /* Subroutine */ int thdiff_(integer *, doublereal *, doublereal *,
	     doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *);
    static doublereal concen[4], dlncdr, hydcon[5000], atomwt[4], lambdad, 
	    con_rad__;

/*      *          HYDCON(JSON),EDXDR(JSON),FGRLI(4)  ! KC 2025-05-31 */
/* ED(JSON) */
    /* Parameter adjustments */
    --edxdr;
    --ecod2;
    --ecod1;
    --edelr;
    --ehqpr;
    --etem;
    --eden;
    --er;
    espec -= 4;

    /* Function Body */
/*       DATA FGRLI/1.0,1.0,1.0,1.0/ */
/* G Somers 5/15: THIS IS A SUBROUTINE WRITEN TO CALCULATE THE DIFFUSION */
/* COEFFICIENT ON THE EQUALLY-SPACED GRID USED FOR LIGHT ELEMENT DIFFUSION. */
/* THIS CODE TAKES IN THE NECESSARY PARAMETERS ON THE EQUAL GRID (NAMELY */
/* HCOMP(1,I), HCOMP(2,I), HCOMP(13-15,I), DENSITY, TEMPERATURE, HQPR, */
/* AND DELR(2,I) */

/* SET UP THE ATOMIC WEIGHT AND CHARGE MATRICIES */
    atomwt[0] = 1.008;
    atomwt[1] = 4.004;
    atomwt[2] = *thea;
    atomwt[3] = 5.486e-4;
    zspec[0] = 1.;
    zspec[1] = 2.;
    zspec[2] = *thez;
    zspec[3] = -1.;
/* SET LN_LAMBDA, CON_RAD, AND CON_TEMP. */
    ln_lambda__ = 2.2f;
    con_rad__ = 1.4368228972096899e-11;
    con_temp__ = 1e-7;
/* CALCULATE DIFFUSION COEFFICIENTS FOR EACH LAYER. */
    i__1 = *npt;
    for (i__ = 1; i__ <= i__1; ++i__) {
	xfrac[0] = espec[i__ * 3 + 1];
	xfrac[1] = espec[i__ * 3 + 2];
	xfrac[2] = espec[i__ * 3 + 3];
/* make sure XFRAC = 0.0 isn't used for diff coefficients */
	if (xfrac[0] < 1e-24) {
	    xfrac[0] = 1e-24;
	}
	if (xfrac[1] < 1e-24) {
	    xfrac[1] = 1e-24;
	}
	if (xfrac[2] < 1e-24) {
	    xfrac[2] = 1e-24;
	}
/*        calculate concentrations from mass fractions: */
	zxa = 0.;
	i__2 = nspec - 1;
	for (ii = 1; ii <= i__2; ++ii) {
	    zxa += zspec[ii - 1] * xfrac[ii - 1] / atomwt[ii - 1];
	}
	i__2 = nspec - 1;
	for (ii = 1; ii <= i__2; ++ii) {
	    concen[ii - 1] = xfrac[ii - 1] / (atomwt[ii - 1] * zxa);
	}
	concen[nspec - 1] = 1.;
/*        save the hydrogen concentration when X is diffused. */
	if (*j == 1) {
	    hydcon[i__ - 1] = concen[0];
	}
/*        now check whether the Thoul routine must be run. if not, */
/*        write COD1 = COD2 = 0. If its the first shell in the depleted */
/*        zone, permit the calculations so that AD is correct. */
	if (espec[*j + i__ * 3] == 0.f && i__ != *npt) {
	    if (espec[*j + (i__ + 1) * 3] == 0.f) {
		ads[i__ - 1] = 0.f;
		goto L5;
	    }
	}
/*        set relevant physical variables. */
	rho = eden[i__];
	t = etem[i__];
/*        calculate density of electrons (NE) from mass density (RHO): */
	ac = 0.;
	i__2 = nspec;
	for (ii = 1; ii <= i__2; ++ii) {
	    ac += atomwt[ii - 1] * concen[ii - 1];
	}
	ne = rho / (ac * 1.6726e-24);
/*        calculate interionic distance (AO): */
	ni = 0.;
	i__2 = nspec - 1;
	for (ii = 1; ii <= i__2; ++ii) {
	    ni += concen[ii - 1] * ne;
	}
	d__1 = .23873 / ni;
	ao = pow_dd(&d__1, &const1_1.cc13);
/*        calculate Debye length (LAMBDAD): */
	cz = 0.;
	i__2 = nspec;
	for (ii = 1; ii <= i__2; ++ii) {
/* Computing 2nd power */
	    d__1 = zspec[ii - 1];
	    cz += concen[ii - 1] * (d__1 * d__1);
	}
	lambdad = sqrt(t / (ne * cz)) * 6.901;
/*        calculate LAMBDA to use in Coulomb logarithm: */
	lambda = max(lambdad,ao);
/*        calculate Coulomb logarithms: */
	i__2 = nspec;
	for (ii = 1; ii <= i__2; ++ii) {
	    i__3 = nspec;
	    for (jj = 1; jj <= i__3; ++jj) {
		xij = t * 2393.9 * lambda / (d__1 = zspec[ii - 1] * zspec[jj 
			- 1], abs(d__1));
		tcl[ii + (jj << 2) - 5] = log(pow_dd(&xij, &c_b3) * .18769 + 
			1.) * .81245;
	    }
	}

/*        calculate the diffusion coefficients */

	thdiff_(&nspec, atomwt, zspec, xfrac, tcl, tap, tat, tac);

	hru_i__ = er[i__];
	htu_i__ = t * con_temp__;
/*         FAC=FGRLI(KK)*HRU_I**2*HTU_I**2.5D0/LN_LAMBDA */
/* Computing 2nd power */
	d__1 = hru_i__;
	fac = d__1 * d__1 * pow_dd(&htu_i__, &c_b4) / ln_lambda__;
/*        collect the first diffusion terms for hydroden. */
/*        collect the third diffusion terms for everything else. */
	ap = -tap[*j - 1];
	at = -tat[*j - 1] * edelr[i__];
	ah = -tac[*j - 1];
	ad = -tac[*j + (*j << 2) - 5];
/*        store the numbers so the hydrogen gradient can finish */
/*        being calculated; then use them later. */
	facs[i__ - 1] = fac;
	aps[i__ - 1] = ap;
	ats[i__ - 1] = at;
	ahs[i__ - 1] = ah;
	ads[i__ - 1] = ad;
L5:
	;
    }
    i__1 = *npt;
    for (i__ = 1; i__ <= i__1; ++i__) {
	fac = facs[i__ - 1];
	ap = aps[i__ - 1];
	at = ats[i__ - 1];
	ah = ahs[i__ - 1];
	ad = ads[i__ - 1];

/*        The general diffusion velocity is written as: */
/*        Ap(D)*dlnP/dR + At(D)*dlnT/dR + Ax(D)*dlnX/dR + Ad(D)*dlnD/dR */
/*        The first two terms are pressure and temperature gradients, and */
/*        the last two terms are the hydrogen gradient and the diffused element */
/*        gradient. For hydrogren diffusion, we can neglect the third term, as */
/*        it is the same as the final term. For metal diffusion, we need all */
/*        four. (see Thoul et al. 1994 for details) */

/*        calculate the hydrogen gradient if diffusing X, then set */
/*        the local gradient to 0 to remove 2nd self-diff term. */
/*        look it up otherwise. */

/*        only calculate the gradient on the hydrogen call. */
/*        set the gradient at first and last points to 0. */

	if (*j == 1) {
	    dlncdr = 1.f;
	    if (i__ == 1) {
		dlncdr = 0.f;
	    } else if (i__ == *npt) {
		dlncdr = 0.f;
	    } else {
		coni = log(hydcon[i__ - 1]);
		conip1 = log(hydcon[i__]);
		conim1 = log(hydcon[i__ - 2]);
		dradi = er[i__ + 1] - er[i__];
		t1 = (coni - conim1) / dradi;
		t2 = (conip1 - coni) / dradi;
		dlncdr = (t1 + t2) * .5f;
	    }
	    edxdr[i__] = dlncdr;
/*           zero out gradient for hydrogen abundance, as stated above. */
	    dlncdr = 0.f;
	} else {
/*           if not the hydrogen call, retrieve the gradient */
	    dlncdr = edxdr[i__];
	}
	ecod1[i__] = fac * (ehqpr[i__] * (ap + at) + dlncdr * ah) * espec[*j 
		+ i__ * 3];
	ecod2[i__] = fac * ad;
/* L10: */
    }
    return 0;
} /* microdiff_cod__ */

