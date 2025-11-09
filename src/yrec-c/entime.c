/* entime.f -- translated by f2c (version 20061008).
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
    doublereal cdelrl, cmixl, cmixl2, cmixl3, clndp, csecyr;
} const3_;

#define const3_1 const3_

struct {
    doublereal atime[14], tcut[5], tscut, tenv0, tenv1, tenv, tgcut;
} ctlim_;

#define ctlim_1 ctlim_

struct {
    doublereal hpo[5000], hto[5000], hro[5000], hlo[5000], hdo[5000], hcompp[
	    75000]	/* was [15][5000] */, hss[5000];
    logical lco[5000], lczo[5000];
    doublereal tefflo;
    integer mo;
} oldmod_;

#define oldmod_1 oldmod_

struct {
    doublereal tridt, tridl, senv0;
    logical lsenv0, lnew0;
} cenv_;

#define cenv_1 cenv_



/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */
/* ENTIME */
/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */
/* Subroutine */ int entime_(doublereal *delts, doublereal *hl, doublereal *
	teffl, integer *m, doublereal *edelt)
{
    /* System generated locals */
    doublereal d__1;

    /* Builtin functions */
    double d_lg10(doublereal *);

    /* Local variables */
    static doublereal fac, hmax[4], temp, testl, testt;

/* NHMAX(4) */
/*  THIS SR LIMITS THE TIMESTEP BASED ON THE REQUIREMENT THAT THE CHANGES FROM */
/*  ONE MODEL TO THE NEXT IN T,AND L BE LESS THAN THE SIZE OF THE ENVELOPE TRIANGLE */
/*  (TRIL AND TRIT). THIS PREVENTS EXTRAPOLATION OUTSIDE OF THE TRIANGLE */
/*  FOR SMALL ENVELOPE TRIANGLES. */

/* INPUT VARIABLES */
/* DECLARED VARIABLES : */
/*   DELTS : PREVIOUS MODEL TIMESTEP. */
/*   HL : RUN OF LUMINOSITY(AS A FUNCTION OF MASS) IN THE CURRENT MODEL. */
/*   TEFFL: EFFECTIVE TENPERATURE OF CURRENT MODEL */
/*   M : NUMBER OF POINTS IN THE MODEL. */
/* VARIABLES IN COMMON BLOCKS : */
/*   TRIL: DELT L OF ENVELOPE TRIANGLE */
/*   TRIT: DELT T OF ENVELOPE TRIANGLE */
/*   ATIME(13): maximum percentage change in the timestep from the previous one */
/*   HLO : RUN OF LUMINOSITY(AS A FUNCTION OF MASS) IN THE PREVIOUS MODEL. */
/*   TEFFLO : EFFECTIVE TEMPERATURE OF PREVIOUS MODEL */
/* OUTPUT VARIABLES : */
/*   EDELT : TIME STEP FOR REQUESTED CHANGE IN P,T,R,L. */

/* FIND MAXIMUM ABSOLUTE TIME DIFFERENCES FOR EACH QUANTITY */

/*  TEMPERATURE */
    /* Parameter adjustments */
    --hl;

    /* Function Body */
    hmax[0] = cenv_1.tridt;
/*  LUMINSOITY */
    hmax[1] = cenv_1.tridl;
    testt = (d__1 = oldmod_1.tefflo - *teffl, abs(d__1));
    testl = (d__1 = d_lg10(&oldmod_1.hlo[oldmod_1.mo - 1]) - d_lg10(&hl[*m]), 
	    abs(d__1));
/* NOW ACTUALLY LIMIT THE TIMESTEP BY A FACTOR THAT REDUCES THE */
/* TIME CHANGES IN ALL QUANTITIES TO THE TRIANGLE VALUES OR LESS */
    fac = testt / cenv_1.tridt;
    if (testl / cenv_1.tridl > fac) {
	fac = testl / cenv_1.tridl;
    }
/*  IF NO CHANGE FROM PREVIOUS MODEL,SET EDELT TO TIMESTEP */
/*  STORED IN THE PREVIOUS MODEL. */
    if (fac == 0.) {
	fac = 1.;
    }
/* USE ATIME(13) AS THE GLOBAL FACTOR FOR LIMITING TIMESTEP CHANGES */
    temp = ctlim_1.atime[12];
    if (fac > temp) {
	fac = temp;
    }
    if (fac < 1. / temp) {
	fac = 1. / temp;
    }
    *edelt = *delts / fac;
    return 0;
} /* entime_ */

