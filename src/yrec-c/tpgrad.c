/* tpgrad.f -- translated by f2c (version 20061008).
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
    doublereal dpenv, alphac, alphae, alpham, betac;
    integer iov1, iov2, iovim;
    logical lovstc, lovste, lovstm, lsemic, ladov, lovmax;
} dpmix_;

#define dpmix_1 dpmix_

struct {
    doublereal alfmlt, phmlt, cmxmlt, valfmlt[5000], vphmlt[5000], vcmxmlt[
	    5000];
} pualpha_;

#define pualpha_1 pualpha_

struct {
    doublereal spotf, spotx;
    logical lsdepth;
} spots_;

#define spots_1 spots_

/* Table of constant values */

static doublereal c_b3 = 4.;
static doublereal c_b4 = 10.;
static integer c__1 = 1;
static doublereal c_b25 = -.333333333;



/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */
/* TPGRAD */
/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */
/* Subroutine */ int tpgrad_(doublereal *tl, doublereal *t, doublereal *pl, 
	doublereal *p, doublereal *d__, doublereal *rl, doublereal *sl, 
	doublereal *b, doublereal *o, doublereal *qdt, doublereal *qdp, 
	doublereal *qot, doublereal *qod, doublereal *qcp, doublereal *del, 
	doublereal *delr, doublereal *dela, doublereal *qdtt, doublereal *
	qdtp, doublereal *qat, doublereal *qap, doublereal *qact, doublereal *
	qacp, doublereal *qacr, doublereal *qcpt, doublereal *qcpp, 
	doublereal *vel, logical *lderiv, logical *lconv, doublereal *fpl, 
	doublereal *ftl, doublereal *teffl)
{
    /* Initialized data */

    static doublereal vtol = 1e-10;

    /* Format strings */
    static char fmt_201[] = "(\002***WARNING***\002/\002TPGRAD TRIED TO TAKE"
	    " SQUARE ROOT\002,\002 OF NEGATIVE NUMBER - ASSUMED ADIABATIC CON"
	    "VECTION\002/\002 DELDEL \002,1pe12.3,\002 QDT \002,e12.3,\002 DI"
	    "SC. \002,e12.3)";
    static char fmt_911[] = "(1p10e12.3)";
    static char fmt_20[] = "(\002 -----CUBIC NON-CONVERGENCE(PL,TL,CAPPA,CP,"
	    "QDT)=\002,2f10.6/1p3e12.6)";

    /* System generated locals */
    doublereal d__1;

    /* Builtin functions */
    double exp(doublereal), pow_dd(doublereal *, doublereal *), d_lg10(
	    doublereal *), sqrt(doublereal);
    integer s_wsfe(cilist *), do_fio(integer *, char *, ftnlen), e_wsfe(void);
    /* Subroutine */ void s_stop(char *, ftnlen);

    /* Local variables */
    static doublereal g, v, a1, a3, vd, vp, a3p, phi, rrr, qvp, qvr, qvt, 
	    phi2, qa1p, qa1r, qa3p, qa1t, qa3r, qa3t, ddel, deli;
    static integer iter;
    static doublereal test, temp1, temp2, temp3, delpm, deepx, deldel, ateffl,
	     qdelap, qddelp, qdelat, qddelt, phiphi, presht, tempot, tempop;

    /* Fortran I/O blocks */
    static cilist io___12 = { 0, 6, 0, fmt_201, 0 };
    static cilist io___13 = { 0, 6, 0, fmt_911, 0 };
    static cilist io___20 = { 0, 0, 0, fmt_20, 0 };


/*  DL,OL,X,Z,LOCOND USED BY OPACTY */
/* COMPUTES RADIATIVE GRADIENT AND COMPARES WITH ADIABATIC GRADIENT */
/* COMPUTES CONVECTIVE GRADIENT VIA MIXING LENGTH THEORY IF APPLICABLE */
/* ASSUMES EQSTAT AND OPACTY HAVE BEEN CALLED */
/* RETURNS LCONV = .TRUE. IF CONVECTIVE */
/*         DELR = RADIATIVE GRADIENT */
/*         DEL = ACTUAL GRADIENT */
/*          QACT,QACP = NAT-LOG DERIVATIVES OF THE CONVECTIVE GRADIENT */
/* DBG 7/95 To store variables for pulse output */
/* G Somers 09/14, Add spot common block */
/* G Somers END */
    pualpha_1.alfmlt = 0.;
    pualpha_1.phmlt = 0.;
    pualpha_1.cmxmlt = 0.;
    *delr = *o * *b * exp(const1_1.cln * (*pl - *sl - *tl * 4. + 
	    const_1.clsunl - const2_1.cgl + const3_1.cdelrl)) * *ftl / *fpl;
    deldel = *delr - *dela;
    if (deldel <= 1e-6) {
/* ZONE IS RADIATIVE */
	*lconv = FALSE_;
	*del = *delr;
	*vel = 0.;
	if (dpmix_1.ladov && dpmix_1.iovim >= dpmix_1.iov1 && dpmix_1.iovim <=
		 dpmix_1.iov2 && dpmix_1.iovim != -1) {
	    *del = *dela;
	}
	goto L200;
    }
/* ZONE IS CONVECTIVE */
    *lconv = TRUE_;
    *del = *dela;
/* SKIP MIXING LENGTH THEORY FOR CORES */
    if (*tl > ctlim_1.tgcut) {
	*vel = 1e-11;
	if (*lderiv) {
/* DERIVATIVES OF CONVECTIVE GRADIENT */
	    *qact = *qat;
	    *qacp = *qap;
	    *qacr = 0.;
	}
	goto L200;
    }
/* G Somers 9/14, Add the ability to include spots, which alter */
/* the radiative flux in the convective reigons. This is done by */
/* setting the flux to Lspotted = L/[f*x^4 + (1-f)], where f is the */
/* spot filling factor and x is the temperature contrast between */
/* the spotted surface and the normal surface (0 <= x <= 1). We also */
/* alter the surface boundary condition used in envint.f, by looking */
/* up the pressure at the un-spotted T (ATEFFL) instead of Teff. */

/* We have also included the ability to have the temperature contrast */
/* SPOTX vary with depth, as is the case in stars. In this case, SPOTX */
/* is locally determined by X(T) = 1 - (1-Xsurf)(ATeff/T), where ATeff */
/* is the surface temperature of the unspotted regions. This is the */
/* analytic expression resulting from a user specified Xsurf, the */
/* assumption of magnetic equipartition at the surface (Pmag = Psurf/2), */
/* and the assumption of constant Pmag with depth. */

/* This flux alters DELR, so recalculate DELDEL with the correction. Only */
/* do this if the spot filling factor is non-zero, and the envelope is */
/* convective. */
    if (spots_1.spotf != 0.f) {
	if (spots_1.lsdepth) {
	    d__1 = spots_1.spotf * pow_dd(&spots_1.spotx, &c_b3) + 1.f - 
		    spots_1.spotf;
	    ateffl = *teffl - d_lg10(&d__1) * .25f;
	    deepx = 1.f - (1.f - spots_1.spotx) * pow_dd(&c_b4, &ateffl) / 
		    pow_dd(&c_b4, tl);
	} else {
	    deepx = spots_1.spotx;
	}
	deldel = *delr / (spots_1.spotf * pow_dd(&deepx, &c_b3) + 1.f - 
		spots_1.spotf) - *dela;
    }
/* G Somers END */
    g = exp(const1_1.cln * (const2_1.cgl + *sl - *rl - *rl));
    presht = *p / (*d__ * g);
    phi = const3_1.cmixl * *d__ * *o * presht;
    phi2 = phi * phi;
    phiphi = 1. / (const3_1.cmixl2 * phi2 + 1.);
/* SOLVE CUBIC A3*V**3 + V**2 + A1*V - 1.0 = 0.0 */
/* ENSURE THAT THE SQUARE ROOT BEING TAKEN IS THAT OF A */
/* POSITIVE NUMBER */
    test = deldel * g * (-(*qdt)) / presht;
    if (test > 0.) {
/* Computing 3rd power */
	d__1 = *t;
	a1 = const3_1.cmixl3 * phiphi * (d__1 * (d__1 * d__1)) * *o / (*qcp * 
		sqrt(test));
    } else {
/* ODD CONVERGENCE PROBLEM; WRITE DIAGNOSTIC AND CONTINUE. */
	s_wsfe(&io___12);
	do_fio(&c__1, (char *)&deldel, (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&(*qdt), (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&test, (ftnlen)sizeof(doublereal));
	e_wsfe();
	s_wsfe(&io___13);
	do_fio(&c__1, (char *)&(*o), (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&(*b), (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&(*pl), (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&(*sl), (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&(*tl), (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&(*ftl), (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&(*fpl), (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&(*delr), (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&(*dela), (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&(*rl), (ftnlen)sizeof(doublereal));
	e_wsfe();
	s_stop("912", (ftnlen)3);
/*         GOTO 15 */
    }
/*      A1 = CMIXL3*PHIPHI*T**3*O/(QCP*DSQRT(DELDEL*G*(-QDT)/PRESHT)) */
    v = 1. / a1;
    a3 = phi2 * .75 * phiphi / a1;
    a3p = a3 * 3.;
    if (a3 > 1e3) {
	v = pow_dd(&a3, &c_b25);
    }
    for (iter = 1; iter <= 25; ++iter) {
	v = min(v,1.);
	vp = a1 + v * (v * a3p + 2.);
	vd = (v * (a1 + v * (v * a3 + 1.)) - 1.) / vp;
	vd *= vd * (v * a3p + 1.) / vp + 1.;
	v -= vd;
	if (abs(vd) < vtol) {
	    goto L30;
	}
/* L10: */
    }
/*  15   CONTINUE */
    io___20.ciunit = luout_1.ishort;
    s_wsfe(&io___20);
    do_fio(&c__1, (char *)&(*pl), (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&(*tl), (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&(*o), (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&(*qcp), (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&(*qdt), (ftnlen)sizeof(doublereal));
    e_wsfe();
/* ASSUME ADIABATIC CONVECTION */
    *vel = 1e-11;
    if (*lderiv) {
/* DERIVATIVES OF CONVECTIVE GRADIENT */
	*qact = *qat;
	*qacp = *qap;
	*qacr = 0.;
    }
    goto L200;
L30:
    ddel = deldel * v * (v + a1);
    *del = *dela + ddel;
/* CALCULATE CONVECTIVE VELOCITY */
    test = g * (-(*qdt)) * presht * deldel;
    if (test > 0.) {
/* Computing 2nd power */
	d__1 = const3_1.cmixl;
	*vel = v * sqrt(g * (-(*qdt)) * (d__1 * d__1) * presht * deldel / 8.);
    } else {
	*vel = -10.;
    }
    delpm = *del - v * v * deldel;
    rrr = pow_dd(&c_b4, rl);
    if (*lderiv) {
/* DERIVATIVES OF CONVECTIVE GRADIENT */
	qdelat = *qat * *dela;
	qdelap = *qap * *dela;
	tempot = *qod * *qdt + *qot;
	tempop = *qod * *qdp;
	qddelt = ((tempot - 4.) * *delr - qdelat) / deldel;
	qddelp = ((tempop + 1.) * *delr - qdelap) / deldel;
	temp1 = const3_1.cmixl2 * 2. * phi2 * phiphi;
	qa1t = tempot * (1. - temp1) - *qcpt - (*qdt + qddelt + *qdtt / *qdt) 
		* .5 + 3.;
	qa1p = tempop * (1. - temp1) - temp1 - *qcpp - (*qdp + qddelp + *qdtp 
		/ *qdt) * .5 + .5;
	qa1r = temp1 * -2. + 2.;
	qa3t = phiphi * 2. * tempot - qa1t;
	qa3p = phiphi * 2. * (tempop + 1.) - qa1p;
	qa3r = phiphi * 4. - qa1r;
	temp1 = a1 * v;
	temp2 = a3 * v * v * v;
	temp3 = 1. / vp;
	qvt = -(temp1 * qa1t + temp2 * qa3t) * temp3;
	qvp = -(temp1 * qa1p + temp2 * qa3p) * temp3;
	qvr = -(temp1 * qa1r + temp2 * qa3r) * temp3;
	temp1 = deldel * (a1 + v + v);
	temp2 = deldel * a1 * v;
	deli = 1. / *del;
	*qact = (qdelat + qddelt * ddel + temp1 * qvt + temp2 * qa1t) * deli;
	*qacp = (qdelap + qddelp * ddel + temp1 * qvp + temp2 * qa1p) * deli;
	*qacr = (temp1 * qvr + temp2 * qa1r) * deli;
    }
L200:
    return 0;
} /* tpgrad_ */

