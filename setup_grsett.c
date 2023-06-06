/* setup_grsett.f -- translated by f2c (version 20100827).
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
    doublereal clsun, clsunl, clnsun, cmsun, cmsunl, crsun, crsunl, cmbol;
} const_;

#define const_1 const_

struct {
    doublereal cln, clni, c4pi, c4pil, c4pi3l, cc13, cc23, cpi;
} const1_;

#define const1_1 const1_

struct {
    doublereal cdelrl, cmixl, cmixl2, cmixl3, clndp, csecyr;
} const3_;

#define const3_1 const3_

struct {
    doublereal con_rad__, con_mass__, con_temp__, con_time__;
} confac_;

#define confac_1 confac_

struct {
    doublereal dt_gs__, xmin, ymin;
    logical lthoulfit;
} gravs2_;

#define gravs2_1 gravs2_

struct {
    doublereal sesum[5000], seg[35000]	/* was [7][5000] */, sbeta[5000], 
	    seta[5000];
    logical locons[5000];
    doublereal so[5000], sdel[15000]	/* was [3][5000] */, sfxion[15000]	
	    /* was [3][5000] */, svel[5000];
} scrtch_;

#define scrtch_1 scrtch_

struct {
    doublereal grtol;
    integer ilambda, niter_gs__;
    logical ldify;
} gravst_;

#define gravst_1 gravst_

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
    doublereal app[5000], atp[5000], apzp[5000], atzp[5000];
} gscof_;

#define gscof_1 gscof_

/* Table of constant values */

static integer c__1 = 1;
static doublereal c_b21 = 2.5;
static doublereal c_b22 = 1.2;

/* $$$$$$ */
/* Subroutine */ int setup_grsett__(doublereal *dt, doublereal *hqpr, 
	doublereal *hr, doublereal *hd, doublereal *hs1, doublereal *ht, 
	logical *lc, integer *m, doublereal *stot, doublereal *cod1, 
	doublereal *cod2, doublereal *hcomp, doublereal *hru, doublereal *htu,
	 integer *ibegin, integer *iend, logical *lallcz, doublereal *qcod1x, 
	doublereal *qcod2x)
{
    /* Initialized data */

    static doublereal atomwt[4] = { 1.008,4.004,55.86,5.486e-4 };
    static doublereal zspec[4] = { 1.,2.,26.,-1. };
    static integer nspec = 4;

    /* Format strings */
    static char fmt_15[] = "(1x,\002 FULLY CONVECTIVE MODEL - NO SETTLING"
	    "\002)";
    static char fmt_16[] = "(1x,\002X BELOW \002,f9.6,\002 IN WHOLE MODEL-NO"
	    " SETTLING\002)";
    static char fmt_17[] = "(1x,\002Y BELOW \002,f9.6,\002 IN WHOLE MODEL-NO"
	    " SETTLING\002)";

    /* System generated locals */
    integer i__1, i__2, i__3;
    doublereal d__1;

    /* Builtin functions */
    double log(doublereal);
    integer s_wsfe(cilist *), e_wsfe(void), do_fio(integer *, char *, ftnlen);
    double exp(doublereal), pow_dd(doublereal *, doublereal *), sqrt(
	    doublereal);

    /* Local variables */
    static doublereal c__[4];
    static integer i__;
    static doublereal t, ln_lambda__, x, z__, x2, x3, ac, ah, ao, ap;
    static integer ii;
    static doublereal ne;
    static integer jj;
    static doublereal at, ni, cz, xz, zz, fac, tac[16]	/* was [4][4] */, tcl[
	    16]	/* was [4][4] */, tap[4], tat[4], rho, xij, zxa, fac2, qacx, 
	    qapx, qatx, xfrac[4], lambda;
    extern /* Subroutine */ int thdiff_(integer *, doublereal *, doublereal *,
	     doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *);
    static doublereal lambdad;

    /* Fortran I/O blocks */
    static cilist io___5 = { 0, 0, 0, fmt_15, 0 };
    static cilist io___6 = { 0, 0, 0, fmt_16, 0 };
    static cilist io___7 = { 0, 0, 0, fmt_17, 0 };


/* MHP 3/94 ADDED METAL DIFFUSION */
/* MHP 8/94 ADDED I/O FOR DIFFUSION */
/*      COMMON/GSCOF2/TAPP(JSON),TATP(JSON),TCLP(JSON),TAPZP(JSON), */
/*     *              TATZP(JSON) */
/* MHP 8/94 ADDED ATOMIC WEIGHTS AND CHARGES FOR H,HE,FE,ELECTRONS - */
/*     NEEDED FOR FULL THOUL COEFFICIENTS */
/*     additional variables to be declared for variable ln lambda */
/*     intermediate variables: */
    /* Parameter adjustments */
    --qcod2x;
    --qcod1x;
    --htu;
    --hru;
    hcomp -= 16;
    --cod2;
    --cod1;
    --lc;
    --ht;
    --hs1;
    --hd;
    --hr;
    --hqpr;

    /* Function Body */
/*     OUTPUT VARIABLES : */

/*     HRU - VECTOR OF UNLOGGED RADII IN BAHCALL AND LOEB UNITS. */
/*     HTU - VECTOR OF UNLOGGED TEMPERATURES IN BAHCALL AND LOEB UNITS. */
/*     IBEGIN - FIRST ZONE FOR DIFFUSION PURPOSES (EITHER THE FIRST MODEL POINT */
/*          OR THE OUTERMOST POINT OF A CENTRAL CONVECTION ZONE). */
/*     IEND - LAST ZONE FOR DIFFUSION PURPOSES (EITHER THE LAST MODEL POINT OR */
/*        THE INNERMOST POINT OF A SURFACE CONVECTION ZONE). */
/*     THE VECTORS HQPR AND HS1, AND THE SCALARS DT AND STOT, ARE ALSO CONVERTED */
/*     TO BAHCALL AND LOEB UNITS. */
/*     CONSTANTS DEFINED : */
/*     CLN = CONVERSION FACTOR FROM LN TO LOG10 */
/*     CRSUN = SOLAR RADIUS (CM) */
/*     CSECYR = NUMBER OF SECONDS IN A YEAR. */
    const1_1.cln = log(10.);
    const_1.crsun = 6.9598e10;
    const3_1.csecyr = 3.1558e7;
/*     LALLCZ=T FOR FULLY CONVECTIVE MODEL(AND IF TRUE, DIFFUSION IS SKIPPED). */
    *lallcz = FALSE_;
/*     CHECK FOR CONVECTIVE CORE. */
    if (lc[1]) {
	i__1 = *m;
	for (i__ = 2; i__ <= i__1; ++i__) {
	    if (! lc[i__]) {
		goto L20;
	    }
/* L10: */
	}
/*        DIFFUSION NOT COMPUTED FOR FULLY CONVECTIVE MODELS. */
	*lallcz = TRUE_;
	io___5.ciunit = luout_1.ishort;
	s_wsfe(&io___5);
	e_wsfe();
	goto L9999;
L20:
/*        COMPUTE OVERSHOOT (TO BE ADDED). */
	*ibegin = i__ - 1;
    } else {
	*ibegin = 1;
    }
/* MHP 6/90 CHECK FOR HYDROGEN-EXHAUSTED CORE. */
    i__1 = *m;
    for (i__ = *ibegin; i__ <= i__1; ++i__) {
	if (hcomp[i__ * 15 + 1] > gravs2_1.xmin) {
	    goto L25;
	}
/* L23: */
    }
/*     HYDROGEN-FREE MODEL - EXIT. */
    io___6.ciunit = luout_1.ishort;
    s_wsfe(&io___6);
    do_fio(&c__1, (char *)&gravs2_1.xmin, (ftnlen)sizeof(doublereal));
    e_wsfe();
    *lallcz = TRUE_;
    goto L9999;
L25:
    *ibegin = i__;
/*     CHECK FOR CONVECTIVE ENVELOPE. */
    if (lc[*m]) {
	for (i__ = *m - 1; i__ >= 2; --i__) {
	    if (! lc[i__]) {
		goto L40;
	    }
/* L30: */
	}
L40:
/*        COMPUTE OVERSHOOT (TO BE ADDED). */
	*iend = i__ + 1;
    } else {
	*iend = *m;
    }
/*     CHECK FOR HELIUM-EXHAUSTED SURFACE. */
/*     OUTER POINT IS SET WHEREVER Y>YMIN. */
    for (i__ = *iend; i__ >= 1; --i__) {
	if (hcomp[i__ * 15 + 2] > gravs2_1.ymin) {
	    goto L47;
	}
/* L45: */
    }
/*     HYDROGEN-FREE MODEL - EXIT. */
    io___7.ciunit = luout_1.ishort;
    s_wsfe(&io___7);
    do_fio(&c__1, (char *)&gravs2_1.ymin, (ftnlen)sizeof(doublereal));
    e_wsfe();
    *lallcz = TRUE_;
    goto L9999;
L47:
    *iend = i__;
/*     CON_MASS=CONVERSION FACTOR FOR MASS. */
/*     CON_RADIUS=CONVERSION FACTOR FOR RADIUS. */
/*     CON_TEMP=CONVERSION FACOTR FOR TEMPERATURE. */
/*     CON_TIME=CONVERSION FACTOR FOR TIME. */
    confac_1.con_rad__ = 1. / const_1.crsun;
/* Computing 3rd power */
    d__1 = confac_1.con_rad__;
    confac_1.con_mass__ = d__1 * (d__1 * d__1) * .01;
    confac_1.con_temp__ = 1e-7;
/*     INCLUDES FACTOR OF 2.2 FROM LN LAMBDA */
    confac_1.con_time__ = const3_1.csecyr * 2.7e13;
/*     CONVERT LOG(RADIUS) AND LOG(TEMPERATURE) TO NATURAL UNITS. */
/*     ALSO CONVERT NATURAL UNITS TO BAHCALL AND LOEB UNITS. */
    i__1 = *m;
    for (i__ = 1; i__ <= i__1; ++i__) {
	hru[i__] = exp(const1_1.cln * hr[i__]) * confac_1.con_rad__;
	htu[i__] = exp(const1_1.cln * ht[i__]) * confac_1.con_temp__;
	hs1[i__] *= confac_1.con_mass__;
	hqpr[i__] /= confac_1.con_rad__;
/*        SDEL(2,I)=0.4D0   !COMMENT OUT IN REAL CODE */
/* L50: */
    }
    *dt /= confac_1.con_time__;
    *stot *= confac_1.con_mass__;
/*     SET UP DIFFUSION COEFFICIENTS. */
/*     MODIFIED BY BC MAY/90 -- VALID FOR ALL X WITH VARIABLE LN LAMBDA */
/*     GENERAL EQUATION IS */
/*     DX/DT = (D/DR(D1)+D/DR(D2 DX/DR))/(RHO*R**2), WHERE */
/*     D1 = R**2/LN LAMBDA  * X  * T**5/2 * (DLNP/DR) * (1-X) * */
/*          [5/4 + DEL*6*(X-0.32)/(5.4+6.3X-4.5X**2)] */
/*     D2 = R**2/LN LAMBDA * T**5/2 * (X+3)/(X+1)/(3+5X) */
    i__1 = *m;
    for (i__ = 1; i__ <= i__1; ++i__) {
	x = hcomp[i__ * 15 + 1];
/* MHP 10/02 INITIALIZED X - WAS NOT DONE PRIOR TO USAGE IN SHELL 1 */
	if (gravst_1.ilambda == 2) {
/*           Noerdlinger's formula (1977 A&A 57,407) for LN LAMBDA: */
/*           Ln Lambda = -19.7 - ln[4/(3*X + 1)]/2 - ln(rho)/2 + 1.5*ln(T) */
	    ln_lambda__ = -19.7 - log(1. / (x * .75 + .25)) * .5 - hd[i__] * 
		    .5 * const1_1.cln + ht[i__] * 1.5 * const1_1.cln;
	} else if (gravst_1.ilambda == 3) {
/*           Loeb's formula (1989 Phys. Rev. D 39, 1009) for LN LAMBDA */
/*           ln lambda = -19.105747 - ln(rho)/2 + 1.5*ln(T) */
	    ln_lambda__ = -19.105747 - hd[i__] * .5 * const1_1.cln + ht[i__] *
		     1.5 * const1_1.cln;
	} else {
	    ln_lambda__ = 2.2;
	}

/* Computing 2nd power */
	d__1 = hru[i__];
	fac = gravs3_1.fgry * (d__1 * d__1) * pow_dd(&htu[i__], &c_b21) / 
		ln_lambda__;
/*         X = HCOMP(1,I) */
	z__ = hcomp[i__ * 15 + 3] + hcomp[i__ * 15 + 4];
	zz = hcomp[i__ * 15 + 3];
	x2 = x * x;
	if (! gravs3_1.lthoul) {
	    xz = x * z__;
	    x3 = x2 * x;
	    fac2 = x * 6.3 + 5.4 - x2 * 4.5;
	    cod1[i__] = fac * hqpr[i__] * (x - x2 - xz) * (scrtch_1.sdel[i__ *
		     3 - 2] * 6. * (x + .32) / fac2 + 1.25);
	    cod2[i__] = fac * (x + 3.) / (x2 * 5. + x * 8. + 3.);
/* Computing 2nd power */
	    d__1 = fac2;
	    qcod1x[i__] = fac * hqpr[i__] * ((1. - x * 2. - z__) * (
		    scrtch_1.sdel[i__ * 3 - 2] * 6. * (x + .32) / fac2 + 1.25)
		     + (x - x2 - xz) * 6. * scrtch_1.sdel[i__ * 3 - 2] * (x * 
		    2.88 + 3.384 + x2 * 4.5) / (d__1 * d__1));
/* Computing 2nd power */
	    d__1 = x2 * 5. + x * 8. + 3.;
	    qcod2x[i__] = -fac * (x2 * 5. + x * 30. + 21.) / (d__1 * d__1);
	} else {
	    xfrac[0] = hcomp[i__ * 15 + 1];
	    xfrac[1] = hcomp[i__ * 15 + 2];
	    xfrac[2] = hcomp[i__ * 15 + 3];
	    if (! gravs2_1.lthoulfit) {
		if (gravst_1.ilambda == 4) {
		    rho = exp(const1_1.cln * hd[i__]);
		    t = exp(const1_1.cln * ht[i__]);
/*                 calculate concentrations from mass fractions: */
		    zxa = 0.;
		    i__2 = nspec - 1;
		    for (ii = 1; ii <= i__2; ++ii) {
			zxa += zspec[ii - 1] * xfrac[ii - 1] / atomwt[ii - 1];
		    }
		    i__2 = nspec - 1;
		    for (ii = 1; ii <= i__2; ++ii) {
			c__[ii - 1] = xfrac[ii - 1] / (atomwt[ii - 1] * zxa);
		    }
		    c__[nspec - 1] = 1.;
/*                 calculate density of electrons (NE) from mass density (RHO): */
		    ac = 0.;
		    i__2 = nspec;
		    for (ii = 1; ii <= i__2; ++ii) {
			ac += atomwt[ii - 1] * c__[ii - 1];
		    }
		    ne = rho / (ac * 1.6726e-24);
/*                 calculate interionic distance (AO): */
		    ni = 0.;
		    i__2 = nspec - 1;
		    for (ii = 1; ii <= i__2; ++ii) {
			ni += c__[ii - 1] * ne;
		    }
		    d__1 = .23873 / ni;
		    ao = pow_dd(&d__1, &const1_1.cc13);
/*                 calculate Debye length (LAMBDAD): */
		    cz = 0.;
		    i__2 = nspec;
		    for (ii = 1; ii <= i__2; ++ii) {
/* Computing 2nd power */
			d__1 = zspec[ii - 1];
			cz += c__[ii - 1] * (d__1 * d__1);
		    }
		    lambdad = sqrt(t / (ne * cz)) * 6.901;
/*                 calculate LAMBDA to use in Coulomb logarithm: */
		    lambda = max(lambdad,ao);
/*                 calculate Coulomb logarithms: */
		    i__2 = nspec;
		    for (ii = 1; ii <= i__2; ++ii) {
			i__3 = nspec;
			for (jj = 1; jj <= i__3; ++jj) {
			    xij = t * 2393.9 * lambda / (d__1 = zspec[ii - 1] 
				    * zspec[jj - 1], abs(d__1));
			    tcl[ii + (jj << 2) - 5] = log(pow_dd(&xij, &c_b22)
				     * .18769 + 1.) * .81245;
			}
		    }
		} else {
		    i__2 = nspec;
		    for (ii = 1; ii <= i__2; ++ii) {
			i__3 = nspec;
			for (jj = 1; jj <= i__3; ++jj) {
			    tcl[ii + (jj << 2) - 5] = ln_lambda__;
			}
		    }
		}
		thdiff_(&nspec, atomwt, zspec, xfrac, tcl, tap, tat, tac);
		ap = -tap[0];
		at = -scrtch_1.sdel[i__ * 3 - 2] * tat[0];
	    } else {
		ap = 1.58 - x * 2.42 + x2 * .844;
		at = scrtch_1.sdel[i__ * 3 - 2] * (1.9 - x * 2.69 + x2 * .805)
			;
	    }
	    ac = 1.15 - x * 1.42 + x2 * .647;
	    qapx = x * 1.688 - 2.42;
	    qatx = scrtch_1.sdel[i__ * 3 - 2] * (x * 1.61 - 2.69);
	    qacx = x * 1.294 - 1.42;
	    cod1[i__] = fac * hqpr[i__] * x * (ap + at);
	    cod2[i__] = fac * ac;
	    qcod1x[i__] = fac * hqpr[i__] * (ap + at + x * (qapx + qatx));
	    qcod2x[i__] = fac * qacx;
	}
/*        METAL DIFFUSION, USING THE THOUL ET AL. COEFFICIENTS FOR FULLY */
/*        IONIZED IRON. */
	if (gravs3_1.ldifz) {
/* Computing 2nd power */
	    d__1 = hru[i__];
	    fac = gravs3_1.fgrz * (d__1 * d__1) * pow_dd(&htu[i__], &c_b21) / 
		    ln_lambda__;
	    if (gravs3_1.lthoul) {
		if (gravs2_1.lthoulfit) {
		    ap = -.157 - x * .511 + x2 * .389;
		    at = scrtch_1.sdel[i__ * 3 - 2] * (-1.36 - x * 1.42 + x2 *
			     .549);
		} else {
		    ap = -tap[2];
		    at = -scrtch_1.sdel[i__ * 3 - 2] * tat[2];
		}
		ah = -.0375 - x * .193 + x2 * .107;
		gravsz_1.cod1z[i__ - 1] = fac * hqpr[i__] * zz * (ap + at);
/*              POSITIVE DIFFUSION COEFFICIENTS NEEDED! */
		gravsz_1.cod2z[i__ - 1] = (d__1 = fac * ah, abs(d__1));
		gravsz_1.qcod1z[i__ - 1] = fac * hqpr[i__] * (ap + at);
		gravsz_1.qcod2z[i__ - 1] = 0.;
	    }
	}

/* If using Noerdlinger's formula for LN LAMBDA, have a new term */
/* in D(D1)/DX */
	if (gravst_1.ilambda == 2) {
	    qcod1x[i__] += cod1[i__] * 1.5 / (ln_lambda__ * (x * 3. + 1.));
	}
/* L60: */
    }
L9999:
    return 0;
} /* setup_grsett__ */

