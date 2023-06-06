/* condopacpint.f -- translated by f2c (version 20100827).
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

/* Table of constant values */

static doublereal c_b2 = 10.;
static doublereal c_b3 = 1.;
static doublereal c_b4 = 2.;
static doublereal c_b5 = 8.;
static doublereal c_b11 = -6.;

/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */

/*     condOpacPInt -  Calculate  Conductive Opacities based on Chirs */
/*                     Burke's conductive opacity code and callin */
/*                     on Potehkin code and table. */

/*                      LLP    5/31/04 */
/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */
/* Subroutine */ int condopacpint_(doublereal *dl, doublereal *tl, doublereal 
	*x, doublereal *z__, doublereal *oc, doublereal *ocl, doublereal *
	qodc, doublereal *qotc, doublereal *fxion, logical *lcondo)
{
    /* Initialized data */

    static doublereal ah1 = 1.008;
    static doublereal ahe4 = 4.004;
    static doublereal aox = 16.;

    /* System generated locals */
    doublereal d__1;

    /* Builtin functions */
    double pow_dd(doublereal *, doublereal *), d_lg10(doublereal *);

    /* Local variables */
    static doublereal wtoxbase, wthe4base, y;
    extern /* Subroutine */ int condopacp_(doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *);
    static doublereal rl, wth1, crap, wtox, crap2, wthe4, condl, condx, condy,
	     condz, qodcx, qodcy, qodcz, qotcx, qotcy, qotcz, condxl, condyl, 
	    condzl, wth1base;

    /* Parameter adjustments */
    --fxion;

    /* Function Body */
/* Get fractional abundances in nubers of atoms of H1, He4 and metals (Ox) */
    y = 1. - *x - *z__;
    wth1base = *x / ah1 / (*x / ah1 + y / ahe4 + *z__ / aox);
    wthe4base = y / ahe4 / (*x / ah1 + y / ahe4 + *z__ / aox);
    wtoxbase = *z__ / aox / (*x / ah1 + y / ahe4 + *z__ / aox);
/* In addition we now weight the H1, He and Ox by oncly */
/* considering those atoms H1 and He4 atomos which are */
/* charged. FXION(1) is the fraction of H1 atoms that are */
/* (singly) charged. FXION(2) is the fraction of He4 atoms */
/* that are singly charged and FXION(3) the fractoin that */
/* are doubly charged.  It is presumed that the metals (Ox) */
/* are fully ionized in first approximation. Because of */
/* their low abundance (tyically less than 2% divided by */
/* the atomic mass */
    wth1 = wth1base * fxion[1];
/* (FXION(1)/1D0 is the fraction */
    wthe4 = wthe4base * (fxion[2] + fxion[3] * 2.) / 2.;
    wtox = wtoxbase;
/* We initially presume no significant conductive opacity */
    *lcondo = FALSE_;
/*       OC = 1D50 */
/*       OCL = LOG10(OC) */
    *ocl = 9.9998;
    *oc = pow_dd(&c_b2, ocl);
    *qodc = *oc;
    *qotc = *oc;
    rl = *dl - (*tl - 6.) * 3.;
/*     DO CONDUCTIVE OPACITY CORRECTION in fully ionized approximation */
    if (*tl >= 3. && *tl <= 9. && *dl <= 9.75) {
	if (*dl >= -6.) {
	    condopacp_(&c_b3, tl, dl, &condxl, &qodcx, &qotcx);
	    condopacp_(&c_b4, tl, dl, &condyl, &qodcy, &qotcy);
	    condopacp_(&c_b5, tl, dl, &condzl, &qodcz, &qotcz);
	    d__1 = -condxl;
	    condx = pow_dd(&c_b2, &d__1);
	    d__1 = -condyl;
	    condy = pow_dd(&c_b2, &d__1);
	    d__1 = -condzl;
	    condz = pow_dd(&c_b2, &d__1);
	    d__1 = wth1 * condx + wthe4 * condy + wtox * condz;
	    condl = -d_lg10(&d__1);
/*           CONDL = LOG10( (X + 1D0) / 2D0 ) - */
/*     *             LOG10( X*CONDX + .5D0*Y*CONDY + .5D0*z*CONDZ) */
	    *qodc = condl * (wth1 * qodcx + wthe4 * qodcy + wtox * qodcz);
/*           QODC = 2D0 * CONDL / ( 1D0 + X ) * */
/*     *          (X*CONDX*QODCX +.5D0*Y*CONDY*QODCY +.5D0*Z*COBDZ*QODCZ) */
	    *qotc = condl * (wth1 * qodcx + wthe4 * qodcy + wtox * qodcz);
/*           QOTC = 2D0 * CONDL / ( 1D0 + X ) * */
/*     *          (X*CONDX*QOTCX +.5D0*Y*CONDY*QOTCY +.5D0*Z*CONDZ*QOTCZ) */
	    *ocl = *tl * 3. - 3.5194 - *dl - condl;
	    *qodc = -1. - *qodc;
	    *qotc = 3. - *qotc;
	    *lcondo = TRUE_;
	    *oc = pow_dd(&c_b2, ocl);
	}
	if (*dl < -6. && rl >= 0.) {
/* Extrapolate Conductive opacity */
	    condopacp_(&c_b3, tl, &c_b11, &condxl, qodc, qotc);
	    condopacp_(&c_b4, tl, &c_b11, &condyl, &crap, &crap2);
	    condopacp_(&c_b5, tl, &c_b11, &condzl, &crap, &crap2);
	    d__1 = -condxl;
	    condx = pow_dd(&c_b2, &d__1);
	    d__1 = -condyl;
	    condy = pow_dd(&c_b2, &d__1);
	    d__1 = -condzl;
	    condz = pow_dd(&c_b2, &d__1);
	    d__1 = wth1 * condx + wthe4 * condy + wtox * condz;
	    condl = d_lg10(&d__1);
/*           CONDL = LOG10( (X + 1D0) / 2D0 ) - */
/*     *            LOG10( X*CONDX + .5D0*Y*CONDY + .5D0*Z*CONDZ) */
	    *ocl = *tl * 3. - 3.5194 + 6. - condl;
	    *qodc = -1. - *qodc;
	    *qotc = 3. - *qotc;
	    *ocl += *qodc * (-6. - *dl);
	    *oc = pow_dd(&c_b2, ocl);
	    *lcondo = TRUE_;
	}
    }
    return 0;
} /* condopacpint_ */

