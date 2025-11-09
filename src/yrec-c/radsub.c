/* radsub.f -- translated by f2c (version 20061008).
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
    doublereal esact, eos[10];
} e_;

#define e_1 e_

struct {
    doublereal zz[5];
    integer iri[10], index[10], nta[77];
} b_;

#define b_1 b_



/* *********************************************************************** */
/* Subroutine */ int radsub_(doublereal *t6, doublereal *density, doublereal *
	moles, doublereal *tmass)
{
    /* Initialized data */

    static doublereal unitf = .9648575;
    static doublereal unitfold = .9652;
    static doublereal sigmacc = .0018914785;
    static doublereal aprop = 83.1446304;

    /* System generated locals */
    doublereal d__1;

    /* Local variables */
    static doublereal dedrhoat, er, et, pr, sr, pt, st, rat, chir, cvtt, 
	    gam1t, chitt, gam2pt, gam3pt, revise, molenak;

/*       REAL*8 MOLES,K,MOLENAK,NA  ! KC 2025-05-31 */
/*       DATA NA/6.0221367D+23/, K/1.38065D-16/, UNITF/0.9648575D0/, */
/*      X UNITFOLD/0.9652D0/, C/2.9979245D+10/, SIGMA/5.67051D-5/, */
/*      X SIGMAC/1.8914785D-15/,SIGMACC/1.8914785D-3/,APROP/83.1446304D0/ */
/* PHYSICAL CONSTANTS */
/*       NA=6.0221367D+23 */
/*       K =1.380658D-16 !   ERG/DEGREE K */
/*       NA*K=6.0221367E+23*1.380658E-16 ERG/DEGREE K=8.314511E+7 ERG/DEGREE K */
/*           =8.314511E+7*11604.5 ERG/EV=0.9648575E+12 ERG/EV */
/*           DEFINE UNITF= NA*K/E+12=0.9648575 */
/*           UNITF=0.9648575  ! OBTAINED WITH LATEST PHYSICAL CONSTANTS */
/*           UNITFOLD=0.9652   ! OLD UNITS- STILL USED IN THE EOS CODE */
/*           IN THESE UNITS ENERGY/DENSITY IS IN UNITS OF MB-CC/GM */
/*           PRESSURE IS IN UNITS OF E+12 BARS=MB */
/*       SIGMA IS THE STEFAN-BOLTZMANN CONSTANT */
/*       SIGMA=5.67051E-5 !   ERG /(S*CM**2*K**4) */
/*       C=2.99792458E+10 !   CM/SEC */
/*     RAT=SIGMA/C    ! DYNE/(CM**2*K**4) */
/*     RAT=RAT*1.D+24  !CONVERT DEGREES K TO UNITS 10**6 K (T REPLACED WITH T6) */
    rat = sigmacc;
/* Computing 4th power */
    d__1 = *t6, d__1 *= d__1;
    pr = rat * 1.3333333333333333 * (d__1 * d__1);
/* MB */
    er = pr * 3. / *density;
/* MB-CC/GM */
    sr = er * 1.3333333333333333 / *t6;
/* MB-CC/(GM-UNIT T6) */
    pt = e_1.eos[b_1.iri[0] - 1] + pr;
    et = e_1.eos[b_1.iri[1] - 1] + er;
    st = e_1.eos[b_1.iri[2] - 1] + sr;
    chir = e_1.eos[b_1.iri[5] - 1] * e_1.eos[b_1.iri[0] - 1] / pt;
    chitt = (e_1.eos[b_1.iri[0] - 1] * e_1.eos[b_1.iri[6] - 1] + pr * 4.) / 
	    pt;
/*     GAM1T(JCS,I)=(P(JCS,I)*GAM1(JCS,I)+4.D0/3.D0*PR)/PT(JCS,I) */
/*     GAM2PT(JCS,I)=(GAM2P(JCS,I)*P(JCS,I)+4.D0*PR)/PT(JCS,I) */
/*     GAM3PT(JCS,I)=GAM1T(JCS,I)/GAM2PT(JCS,I) */
    molenak = *moles * aprop;
/* MB-CC/UNIT T6 */
    cvtt = e_1.eos[b_1.iri[4] - 1] * molenak / *tmass + er * 4. / *t6;
    gam3pt = pt * chitt / (cvtt * *density * *t6);
    gam1t = chir + chitt * gam3pt;
    gam2pt = gam1t / gam3pt;
/*     NORMALIZE CVT TO 3/2 WHEN GAS IS IDEAL,NON-DEGENERATE, */
/*     FULLY-IONIZED, AND HAS NO RADIATION CORRECTION */
/*     CVT=(EOS(5)*MOLENAK/TMASS+4.*ER/T6) */
/*    X  /MOLENAK */
    dedrhoat = e_1.eos[b_1.iri[3] - 1] - er / *density;
    revise = unitf / unitfold;
    pt *= revise;
/* MHP 10/02 EN is never used; should this be ET=ET*REVISE??? */
/*      EN=EN*REVISE */
    st *= revise;
/* DEDRHOA is never used; should this be DEDRHOAT=DEDRHOAT*REVISE???? */
/*      DEDRHOA=DEDRHOA*REVISE */
    e_1.eos[b_1.iri[0] - 1] = pt;
    e_1.eos[b_1.iri[1] - 1] = et;
    e_1.eos[b_1.iri[2] - 1] = st;
    e_1.eos[b_1.iri[3] - 1] = dedrhoat;
    e_1.eos[b_1.iri[4] - 1] = cvtt;
    e_1.eos[b_1.iri[5] - 1] = chir;
    e_1.eos[b_1.iri[6] - 1] = chitt;
    e_1.eos[b_1.iri[7] - 1] = gam1t;
    e_1.eos[b_1.iri[8] - 1] = gam2pt;
    e_1.eos[b_1.iri[9] - 1] = gam3pt;
    return 0;
} /* radsub_ */

