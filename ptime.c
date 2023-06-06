/* ptime.f -- translated by f2c (version 20100827).
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
} oldmod_;

#define oldmod_1 oldmod_



/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */
/* PTIME */
/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */
/* Subroutine */ int ptime_(doublereal *delts, doublereal *hl, doublereal *hp,
	 doublereal *hr, doublereal *ht, integer *m, doublereal *pdelt)
{
    /* System generated locals */
    integer i__1;
    doublereal d__1;

    /* Local variables */
    static integer i__;
    static doublereal fac, hmax[4], temp;
    static integer nhmax[4];
    static doublereal testl, testp, testr, testt;

/*  THIS SR LIMITS THE TIMESTEP BASED ON THE REQUIREMENT THAT THE CHANGES FROM */
/*  ONE MODEL TO THE NEXT IN T,P,R,AND L BE LESS THAN THE USER PARAMETERS */
/*  ATIME(8)-ATIME(11) AT ANY MODEL POINT. */
/*  THIS CRITERION DOMINATES IN THE PRE-MAIN SEQUENCE, AND THIS SR MUST BE */
/*  USED (LPTIME=T) TO PERFORM PRE-MAIN SEQUENCE EVOLUTION. */

/* INPUT VARIABLES */
/* DECLARED VARIABLES : */
/*   DELTS : PREVIOUS MODEL TIMESTEP. */
/*   HL : RUN OF LUMINOSITY(AS A FUNCTION OF MASS) IN THE CURRENT MODEL. */
/*   HP : RUN OF PRESSURE IN THE CURRENT MODEL. */
/*   HR : RUN OF RADIUS IN THE CURRENT MODEL. */
/*   HT : RUN OF TEMPERATURE IN THE CURRENT MODEL. */
/*   M : NUMBER OF POINTS IN THE MODEL. */
/* VARIABLES IN COMMON BLOCKS : */
/*   ATIME(8) : MAX DELTA LOG T (= 0.02 DEFAULT) */
/*   ATIME(9) :  "    "    "  P (= 0.04   "    ) */
/*   ATIME(10):  "    "    "  R (= 0.02   "    ) */
/*   ATIME(11):  "  DELTA L/L   (= 0.02   "    ) */
/*   ATIME(12): maximum percentage change in the timestep from the previous one */
/*   HLO : RUN OF LUMINOSITY(AS A FUNCTION OF MASS) IN THE PREVIOUS MODEL. */
/*   HPO : RUN OF PRESSURE IN THE PREVIOUS MODEL. */
/*   HRO : RUN OF RADIUS IN THE PREVIOUS MODEL. */
/*   HTO : RUN OF TEMPERATURE IN THE PREVIOUS MODEL. */

/* OUTPUT VARIABLES : */
/*   PDELT : TIME STEP FOR REQUESTED CHANGE IN P,T,R,L. */

/* FIND MAXIMUM ABSOLUTE TIME DIFFERENCES FOR EACH QUANTITY */

/*  PRESSURE */
    /* Parameter adjustments */
    --ht;
    --hr;
    --hp;
    --hl;

    /* Function Body */
    hmax[0] = (d__1 = oldmod_1.hpo[0] - hp[1], abs(d__1));
/*  TEMPERATURE */
    hmax[1] = (d__1 = oldmod_1.hto[0] - ht[1], abs(d__1));
/*  RADIUS */
    hmax[2] = (d__1 = oldmod_1.hro[0] - hr[1], abs(d__1));
/*  LUMINSOITY */
    if (hl[1] + hl[2] > 0.) {
	hmax[3] = (d__1 = (oldmod_1.hlo[0] - hl[1]) * 2. / (hl[2] + hl[1]), 
		abs(d__1));
    } else {
	hmax[3] = 0.;
    }
    i__1 = *m;
    for (i__ = 2; i__ <= i__1; ++i__) {
	testp = (d__1 = oldmod_1.hpo[i__ - 1] - hp[i__], abs(d__1));
	if (hmax[0] <= testp) {
	    hmax[0] = testp;
	    nhmax[0] = i__;
	}
	testt = (d__1 = oldmod_1.hto[i__ - 1] - ht[i__], abs(d__1));
	if (hmax[1] <= testt) {
	    hmax[1] = testt;
	    nhmax[1] = i__;
	}
	testr = (d__1 = oldmod_1.hro[i__ - 1] - hr[i__], abs(d__1));
	if (hmax[2] <= testr) {
	    hmax[2] = testr;
	    nhmax[2] = i__;
	}
	if (hl[i__] + hl[i__ - 1] > 0.) {
	    testl = (d__1 = (oldmod_1.hlo[i__ - 1] - hl[i__]) * 2. / (hl[i__] 
		    + hl[i__ - 1]), abs(d__1));
	} else {
	    testl = 0.;
	}
	if (hmax[3] <= testl) {
	    hmax[3] = testl;
	    nhmax[3] = i__;
	}
/* L40: */
    }
/* NOW ACTUALLY LIMIT THE TIMESTEP BY A FACTOR THAT REDUCES THE */
/* TIME CHANGES IN ALL QUANTITIES TO THE PS VALUES OR LESS */
    fac = hmax[0] / ctlim_1.atime[8];
    if (hmax[1] / ctlim_1.atime[7] > fac) {
	fac = hmax[1] / ctlim_1.atime[7];
    }
    if (hmax[2] / ctlim_1.atime[9] > fac) {
	fac = hmax[2] / ctlim_1.atime[9];
    }
    if (hmax[3] / (ctlim_1.atime[10] * 2.3026) > fac) {
	fac = hmax[3] / (ctlim_1.atime[10] * 2.3026);
    }
/*  IF NO CHANGE FROM PREVIOUS MODEL,SET PDELT TO TIMESTEP */
/*  STORED IN THE PREVIOUS MODEL. */
    if (fac == 0.) {
	fac = 1.;
    }
/* RESTRICT CHANGE IN TIMESTEP TO NO MORE THAN A FACTOR OF ATIME(12)% */
/* UP OR DOWN. */
    temp = ctlim_1.atime[11] + 1.;
    if (fac > temp) {
	fac = temp;
    }
    if (fac < 1. / temp) {
	fac = 1. / temp;
    }
    *pdelt = *delts / fac;
    return 0;
} /* ptime_ */

