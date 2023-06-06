/* cowind.f -- translated by f2c (version 20100827).
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
    doublereal wmax, exmd, exw, exr, exm, factor;
    logical ljdot0;
} cwind_;

#define cwind_1 cwind_

struct {
    doublereal drate[5000], drate0[5000], fmassacc, taucz;
    integer jcz;
} deuter_;

#define deuter_1 deuter_

/* Table of constant values */

static integer c__1 = 1;

/* $$$$$$ */
/* Subroutine */ int cowind_(doublereal *bl, doublereal *dt, doublereal *hicz,
	 integer *it, doublereal *omegas, doublereal *smass, doublereal *
	teffl, doublereal *wold, doublereal *wind1, doublereal *wind2)
{
    /* Format strings */
    static char fmt_912[] = "(\002Omega sat, Tau\002,1p2e12.3)";
    static char fmt_911[] = "(\002ERROR IN WIND - TAUCZ NOT DEFINED \002,1p2"
	    "e12.3,\002STOPPED\002)";

    /* System generated locals */
    doublereal d__1, d__2;

    /* Builtin functions */
    integer s_wsfe(cilist *), do_fio(integer *, char *, ftnlen), e_wsfe(void);
    /* Subroutine */ int s_stop(char *, ftnlen);
    double exp(doublereal), pow_dd(doublereal *, doublereal *);

    /* Local variables */
    static doublereal c__, rl, wn, wp, temp, wsat, rtot, dmdot;

    /* Fortran I/O blocks */
    static cilist io___2 = { 0, 6, 0, fmt_912, 0 };
    static cilist io___3 = { 0, 6, 0, fmt_911, 0 };


/* MHP 3/09 ADDED OPTION TO SCALE THE SATURATION RATE BY THE OVERTURN TIMESCALE */
/*  COWIND RETURNS THE CHANGE IN THE ANGULAR VELOCITY OF THE SURFACE */
/*  CONVECTION ZONE OF A STAR WHICH IS EXPERIENCING ANGULAR MOMENTUM LOSS. */

/*  INPUT VARIABLES: */

/*       DECLARED */
/*  BL : TOTAL LUMINOSITY */
/*  DT : DIFFUSION TIMESTEP. */
/*  HICZ : TOTAL MOMENT OF INERTIA OF THE SURFACE C.Z. */
/*  IT : ITERATION NUMBER (IN THE DIFFUSION ROUTINES). */
/*  OMEGAS : SURFACE ANGULAR VELOCITY AT THE END OF THE PREVIOUS ITERATION. */
/*  SMASS : STELLAR MASS (SOLAR UNITS) */
/*  TEFFL : STELLAR EFFECTIVE TEMPERATURE. */
/*  WOLD : SURFACE ANGULAR VELOCITY AT THE BEGINNING OF THE TIMESTEP. */
/*       IN COMMON BLOCKS */

/*  EXMD,EXW,EXR,EXM,FACTOR : USER PARAMETERS WHICH VARY THE STRENGTH */
/*  OF ANGULAR MOMENTUM LOSS AND ITS DEPENDENCE ON SURFACE ROTATION RATE */
/*  AND OTHER STELLAR PARAMETERS. */

/*  OUTPUT VARIABLES */

/*  WIND1,WIND2:CHANGE IN ANGULAR VELOCITY OF THE SURFACE C.Z. FOR THE TIMESTEP */
/*  BASED ON THE ANGULAR VELOCITY AT THE BEGINNING AND END OF THE TIMESTEP */
/*  RESPECTIVELY. */

/*  WIND1 AND WIND2 ARE INCORPORATED INTO THE DIFFUSION EQUATIONS; */
/*  THEY ARE AVERAGED TO FIND THE TOTAL ANGULAR MOMENTUM LOSS FOR THE */
/*  TIMESTEP. */
/* FIND TOTAL RADIUS OF STAR. */
/* mhp 10/02 cgrav not used; omit */
/*      CGRAV = EXP(CLN*CGL) */
/* MHP 3/09 IF WMAX > 1 THEN ASSUME THAT THE PARAMETER WMAX IS DEFINED BY */
/* WMAX = WMAX(SUN)*TAUCZ(SUN) AND THE SATURATION THRESHOLD WSAT = WMAX/TAUCZ(STAR) */
    if (cwind_1.wmax > 1.) {
	if (deuter_1.taucz > 1.) {
	    wsat = cwind_1.wmax / deuter_1.taucz;
	    s_wsfe(&io___2);
	    do_fio(&c__1, (char *)&wsat, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&deuter_1.taucz, (ftnlen)sizeof(doublereal))
		    ;
	    e_wsfe();
	} else {
	    s_wsfe(&io___3);
	    do_fio(&c__1, (char *)&cwind_1.wmax, (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&deuter_1.taucz, (ftnlen)sizeof(doublereal))
		    ;
	    e_wsfe();
	    s_stop("", (ftnlen)0);
	}
    } else {
	wsat = cwind_1.wmax;
    }
    rl = (*bl + const_1.clsunl - const1_1.c4pil - const2_1.csigl - *teffl * 
	    4.) * .5;
    rtot = exp(const1_1.cln * rl);
/* DMDOT IS THE MASS LOSS RATE IN SOLAR MASSES PER YEAR. */
    dmdot = 2e-14;
/* DJ/DT = DT*FACTOR*(DMDOT/1.0D-14)**EXMD*OMEGA**EXW*(M/MSUN)**EXM */
/*         *(R/RSUN)**EXR */
/*  THE CONSTANT AND EXPONENTS ARE SET IN PARMIN BASED ON THE INPUT */
/*  INDEX ALFA;SEE PARMIN FOR DETAILS ON THE DEPENDENCE OF EACH ON ALFA. */
    d__1 = dmdot / 1e-14;
    d__2 = rtot / const_1.crsun;
    c__ = *dt / *hicz * cwind_1.factor * pow_dd(&d__1, &cwind_1.exmd) * 
	    pow_dd(&d__2, &cwind_1.exr) * pow_dd(smass, &cwind_1.exm);
    wp = min(*wold,wsat);
    wn = min(*omegas,wsat);
    d__1 = cwind_1.exw - 1.;
    *wind1 = c__ * pow_dd(&wp, &d__1) * *wold;
    d__1 = cwind_1.exw - 1.;
    temp = c__ * pow_dd(&wn, &d__1) * *omegas;
    if (*it == 1) {
	*wind2 = temp;
    } else {
	*wind2 = (*wind2 + temp) * .5;
    }
    return 0;
} /* cowind_ */

