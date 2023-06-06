/* rates.f -- translated by f2c (version 20100827).
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
    doublereal atime[14], tcut[5], tscut, tenv0, tenv1, tenv, tgcut;
} ctlim_;

#define ctlim_1 ctlim_

struct {
    doublereal cln, clni, c4pi, c4pil, c4pi3l, cc13, cc23, cpi;
} const1_;

#define const1_1 const1_

struct {
    doublereal sstandard[17];
} cross_;

#define cross_1 cross_

struct {
    doublereal weakscreening;
} weak_;

#define weak_1 weak_

/* Table of constant values */

static doublereal c_b3 = 1.58;
static doublereal c_b6 = .6666667;
static doublereal c_b7 = .666667;
static doublereal c_b8 = .86;
static doublereal c_b9 = .58;
static doublereal c_b10 = .28;

/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */
/* RATES */
/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */
/* Subroutine */ int rates_(doublereal *dl, doublereal *tl, doublereal *x, 
	doublereal *y, doublereal *z__, doublereal *xhe3, doublereal *xc12, 
	doublereal *xc13, doublereal *xn14, doublereal *xn15, doublereal *
	xo16, doublereal *xo17, doublereal *xo18, doublereal *xh2, doublereal 
	*xli6, doublereal *xli7, doublereal *xbe9, integer *iu, doublereal *
	hr1, doublereal *hr2, doublereal *hr3, doublereal *hr4, doublereal *
	hr5, doublereal *hr6, doublereal *hr7, doublereal *hr8, doublereal *
	hr9, doublereal *hr10, doublereal *hr11, doublereal *hr12, doublereal 
	*hr13, doublereal *hf1, doublereal *hf2)
{
    /* Initialized data */

    static doublereal anuc[13] = { 1.008665,1.007276,2.013553,3.015501,
	    3.014933,4.001506,11.996709,13.000064,13.999233,15.990526,
	    17.994772,19.986954,23.978458 };
    static doublereal q7[7] = { 20.8964,76.6003,67.8036,69.13,70.3809,69.8517,
	    70.8012 };
    static doublereal q8[7] = { 0.,0.,0.,0.,0.,0.,0. };
    static integer nrxns = 13;
    static doublereal zprd[13] = { 1.,4.,4.,6.,6.,7.,8.,12.,16.,12.,14.,12.,
	    36. };
    static doublereal z53[13] = { 1.175,3.73,3.73,4.804,4.804,5.385,5.941,
	    9.014,11.24,9.014,10.15,9.104,23.28 };
    static doublereal z43[13] = { .52,1.31,1.31,1.488,1.488,1.61,1.721,2.577,
	    3.025,2.577,2.81,2.577,5.668 };
    static doublereal z23[13] = { -.413,-.655,-.655,-.643,-.643,-.659,-.673,
	    -.889,-.946,-.889,-.92,-.889,-1.36 };
    static doublereal z86[13] = { 1.63,5.917,5.917,8.302,8.302,9.52,10.716,
	    16.192,20.978,16.192,18.606,16.192,45.6635 };
    static doublereal c21 = 5.240358e-8;
    static doublereal znuc[13] = { 0.,1.,1.,1.,2.,2.,6.,6.,7.,8.,8.,10.,12. };
    static integer nelem = 13;
    static doublereal q1[8] = { .12317,.03392,.0325,.0304,.03035,.0273,.02494,
	    .040572 };
    static doublereal q2[8] = { 1.08749,-.273,-.2085,.763,-.4044,-1.6,-1.224,
	    0. };
    static doublereal q3[8] = { .93833,-.0648,-.0474,.1626,-.08598,-.3064,
	    -.2139,0. };
    static doublereal q4[8] = { 0.,0.,0.,4.79,7.456,0.,.69703,0. };
    static doublereal q5[8] = { 0.,0.,0.,2.595,4.032,0.,.3097,0. };
    static doublereal q6[7] = { -3.3804,-12.2757,-12.826,-13.6899,-13.7173,
	    -15.2281,-16.6925 };

    /* System generated locals */
    integer i__1;
    doublereal d__1, d__2, d__3, d__4, d__5, d__6;

    /* Builtin functions */
    double pow_dd(doublereal *, doublereal *), exp(doublereal), sqrt(
	    doublereal), d_lg10(doublereal *);

    /* Local variables */
    static doublereal zprdbe7p, utotbe7p;
    static integer i__;
    static doublereal be7proton, a1, a2, a3, a4, a5, f1, f3, f4, r1, r2, t9, 
	    dd, z33, z28, z58;
    static integer nz;
    static doublereal tm1, be7electron, amu, emu, rho, rwe, t9m1, zet, trm, 
	    t9m2, uwk, xxl, xtr, t9m12, t9m13, t9m23, t9m32, t9p13, t9p23, 
	    xxl6, degd, xxl8, rate[13], fprf, zbar, uint, utot[13], ustr, 
	    pfmc2, qrbe7, temp3, xfrac[13], efmkt, zcurl, z86be7p, camube7, 
	    c12alpha, o16gamma;

/* JULY 3, 1991 (MHP) */
/* THIS SUBROUTINE COMPUTES THE NUCLEAR BURNING RATES FOR USE IN KEMCOM. */
/* IT IS A STRIPPED-DOWN VERSION OF ENGEB; SEE ENGEB FOR DETAILED NOTES */
/* ON THE REACTIONS. */
/* ALL PHYSICAL QUANTITIES ARE CGS. THE REACTION RATES ARE IN */
/*  GM^{-1}S^{-1}. */
/*  MHP 10/97 */

/*   On 10/13/97, JNB converted the nuclear masses from neutral nuclear */
/*   masses to bare nuclear masses by subtracting Z(I)*(m_e)*c^2 from */
/*   the neutral nuclear masses. This caused changes in a number of */
/*   places: in ANUC(I), in Q1(I)-Q7(I), in the calculation of the Be7electron */
/*   Be7proton rates, and in the calculation of the N15p branching ratio. */

/*   JNB made some purely cosmetic changes on 1/20/96. Revised all of the */
/*   input Q's on 9/23-25/97 to agree with submitted version of Solar */
/*   Fusion Workshop paper. The SStandard are fixed to agree with */
/*   the Workshop paper. JNB recalculated all of the EG(I) to determine */
/*   the best values for the energy generation for all the reactions, */
/*   taking account of my improved calculations of neutrino energy loss. */
/*   The calculations are documented in Vol. 19, 132-141, 1997 of my notes. */
/*   The neutral atom mass differences are taken from Table of Isotopes, */
/*   8th Ed, 1996 and the neutrino energy losses from Bahcall, Gallium */
/*   solar neutrino experiments, Phys Rev C, in press, 1997. */

/* ALL NUMBERS IN THIS SUBROUTINE HAVE BEEN CHECKED AND REVISED, WHERE */
/*  NECESSARY, BY JOHN BAHCALL SO THAT THEY AGREE WITH THE MODERN NUMBERS */
/*  IN NEUTRINO ASTROPHYSICS (1989). */
/* ***************************************** */
/* CHANGING NUCLEAR REACTION CROSS SECTIONS. */
/* ***************************************** */
/* NUCLEAR CROSS SECTIONS CAN BE CHANGED SIMPLY BY INSERTING NEW NUMBERS */
/*  FOR THE DATA VALUES OF SSTANDARD(I), WHICH ARE THE RATIOS OF THE */
/*  DESIRED CROSS SECTION FACTORS TO THE VALUES GIVEN IN TABLES 3.2 AND */
/*  3.4 OF NEUTRINO ASTROPHYSICS (1989). IF THE VALUE GIVEN IN NEUTRINO */
/*  ASTROPHYSICS IS USED, THEN SSTANDARD(I) = 1.0 .  TO INCREASE THE CROSS */
/*  SECTION FOR REACTION K BY A FACTOR OF TWO COMPARED TO THE STANDARD */
/*  VALUE, SET SSTANDARD(K) = 2.0 .  TO DETERMINE WHICH VALUE OF I GOES */
/*  WITH WHICH REACTION, SEE THE SECTION JUST BELOW. */
/* THE ENERGY DERIVATIVES ENTER IN A FORM IN WHICH THEY ARE DIVIDED BY */
/*  THE ABSOLUTE VALUES OF THE CROSS SECTIONS AT ZERO ENERGY.  THUS IF */
/*  THE SHAPE OF THE CROSS SECTION EXTRAPOLATION IS UNCHANGED AND ONLY */
/*  THE INTERCEPT OF S(E) AT ZERO ENERGY IS CHANGED, THEN NO CORRECTION */
/*  NEED BE MADE FOR THE DERIVATIVES.  THEY ARE AUTOMATICALLY SCALED */
/*  CORRECTLY.  THE EXACT WAY THAT THE DERIVATIVES ENETER THE */
/*  CALCUALTIONS IS DESCRIBED IN THE SECTION LABELED ``DEFINING THE */
/*  Q(I)' THAT IS PRESENTED BELOW. */
/* ************************************ */
/* IDENTIFYING THE REACTIONS. */
/* ************************************ */
/*  THE VALUE OF J DENOTES WHICH OF THE REACTIONS THE COEFFICIENTS */
/*  REFER TO: */
/*  J = 1, PP; J = 2, HE3+HE3; J = 3, HE3+ HE4; J =4, P + C12;  J = 5, P+C13; */
/*  J = 6. P + N14; J = 7, P + O16 ; J = 8, HE4+C13; J = 10, HE4+C12; */
/*  J = 11, HE4 + N14; J = 12, TRIPLE ALPHA. */
/*  REACTION 14 IS PEP; REACTION 15 IS BE7 ELECTRON CAPTURE; REACTION 16 IS */
/*   BE7 PROTON CAPTURE; REACTION 17 IS THE HEP REACTION. */
/*  do not change sstandard(14) unless you want to change the ratio of */
/*  pep to pp. */
/*   REACTIONS 14-17 WERE NOT EXPLICITLY INCLUDED IN THE YALE */
/*    PREVIOUS VERSION OF THE CODE, BUT THEY ARE MOST OF THE STORY FOR */
/*    THE SOLAR NEUTRINO PROBLEM. */
/*   THE BRANCHING OF THE N15 + P REACTIONS IS TREATED IN A SERIES OF */
/*    SEPARATE STATEMENTS FOLLOWING THE CALCULATION OF THE BE7 + P */
/*    REACTION. SEE THE DEFINITIONS OF F3 AND F4.  IF THE CROSS-SECTION */
/*    FACTORS OF THE N15 + P REACTIONS ARE REVISED, THEN THE NUMERICAL */
/*    COEFFICIENTS MUST BE CHANGED IN THE DEFINITION OF C12ALPHA AND */
/*    O16GAMMA. */
/* FOR Q1(I), ...,Q(5(I), I = 8 CORRESPONDS TO THE BE7 +  P REACTION. */
/*  THIS ASSIGNMENT FOR I = 8 IS ONLY VALID FOR THE LISTED Q'S AND NOT */
/*  FOR OTHER ARRAYS IN THE PROGRAM. */
/* IU IS THE SHELL NUMBER. */
/* MHP 8/96 CROSS SECTIONS PUT IN COMMON BLOCK. */
/* *************************** */
/* ANUC ARE ATOMIC MASS UNITS. */
/* *************************** */
/*  On 10/13/97, JNB converted ANUC(I) from neutral atomic masses to */
/*  bare nuclear masses. */

/*  The scale is the mass of C12 divided by 12 or 931.49432 MeV, */
/*  which is 1.6605402 times 10^{-24} gm. The values are obtained */
/*  by dividing the mass excess (expressed in MeV) by 931.49432 MeV and */
/*  adding to this the atomic mass number, A.  The value for Be7, which */
/*  is used implicitly in this subroutine was, 7.016930, until 13/13/97. */
/*  We now use the bare nuclear mass of 7.014735 . */

    /* Parameter adjustments */
    --hf2;
    --hf1;
    --hr13;
    --hr12;
    --hr11;
    --hr10;
    --hr9;
    --hr8;
    --hr7;
    --hr6;
    --hr5;
    --hr4;
    --hr3;
    --hr2;
    --hr1;

    /* Function Body */
/* THE ISOTOPES ARE NEUTRON, H1, D, H3, HE3, HE4, C12, C13, N14, O16, O18, */
/*  NE20, MG24, RESPECTIVELY. ALL OF THESE NUMBERS WERE CHECKED. */
/* NELEM IS THE NUMBER OF ISOTOPES INCLUDED. */
/* ************************************************************************** */
/* THE QUANTITIES Q1(J), Q2(J), ...,Q5(J) ARE THE TERMS IN EQUATION 3.14 OF */
/*  NEUTRINO ASTROPHYSICS AND IN EQUATION 53 OF FOWLER, CAUGHLAN, AND */
/*  ZIMMERMAN (1967) EQ. 53, IN BOTH CASES MULTIPLIED BY T SUB 9 ^(-2/3). */
/*  THE REACTIONS CORRESPONDING TO EACH J ARE LISTED ABOVE, UNDER: */
/*   IDENTIFYING THE RECTIONS. */
/*  FOR THIS SET OF PARAMETERS, AND ONLY FOR THIS SET OF PARAMETERS, */
/*  J = 8 CORRESPONDS TO THE BE7 + P REACTION. */
/* ************************************************************************** */
/* GENERAL EXPRESSION FOR Q'S: */
/* T_9^(-2/3)[S_EFF/S(0)] = */
/*   [T_9^(-2/3) + Q1(I)T_9^(-1/3) + Q2(I) + Q3(I)T_9^(1/3) + */
/*    Q4(I)T_9^(2/3) + Q(5)T_9 ] */

/* BY COMPARISON WITH EQUATION 3.14 OF NEUTRINO ASTROPHYSICS, WE SEE THAT */

/*  Q1 = (5/(12*TAU))*T_9^(-1/3) . */
/*  Q2 = (S'/S)(E_0))*T_9^(-2/3) . */
/*  Q3 = (S'/S)(35/36)(K*10^9 K) */
/*  Q4 = (S''/2S)(E_0^2)(T_9^(-4/3) */
/*  Q5 = (89/72)(S''/S)(E_0)(KT)(T_9^(-5/3) */

/* EACH OF THE Q'S IS INDEPENDENT OF TEMPERATURE (T), AS CAN BE SEEN FROM */
/*  EQUATIONS 3.10 AND 3.11 . */

/* ALL OF THE VALUES OF THE Q1, ...., Q5 HAVE BEEN RECALCULATED, USING */
/*  WHERE NEEDED NUCLEAR CROSS SECTIONS GIVEN IN TABLES 3.2 AND 3.4 OF NEUTRINO */
/*  ASTROPHYSICS. */
/* ****************************************************************** */
/* Q6 IS THE COEFFICIENT OF THE TEMPERATURE TERM IN THE DEFINITION OF */
/*  TAU, EQUATION 3.10 OF NEUTRINO ASTROPHYSICS. */
/*  TAU = Q6*(T SUB 9 TO THE (-1/3) POWER ). */
/* ****************************************************************** */
/* SLIGHT CHANGES HAVE BEEN MADE IN THE PREVIOUS VALUES OF Q6 TO MAKE */
/*  THE DATA MORE ACCURATE. */
/* NOTE Q6 IS NEGATIVE. */
/* ******************************************************************** */
/* Q7 IS THE CONSTANT IN FRONT OF THE REACTION RATE. THE LOGARITHMS ARE */
/*  RELATED TO S FACTORS BY A LOGARITHM AND VARIOUS NUMERICAL FACTORS. */
/* ******************************************************************** */
/* THE GENERAL RELATION IS: */
/*  Q7 = 70.62860 + ((LN(Z0*Z1/A))/3) -LN(A0*A1) - LN(S SUB 0) */
/*       -LN(1 + DELTA_01) */
/*  HERE S SUB 0 IS THE CROSS SECTION FACTOR IN UNITS OF KEV-BARNS. */
/*  THE NUMERICAL VALUES USED HERE ARE TAKEN FROM TABLES 3.4 AND 3.2 */
/*   OF NUCLEAR ASTROPHYSICS. */
/*  THE QUANTITY DELTA_01 IS NON-ZERO (EQUAL TO UNITY) ONLY WHEN THE */
/*   TWO REACTING NUCLEI, 0 AND 1, ARE IDENTICAL. */
/* Q8 REFLECTS A TERM IN THE EXPONENTIAL THAT OCCURS IN THE RATES, THE */
/*  TERM BEING PROPORTIONAL TO E^( CONSTANT*T_9^2). SEE HARRIS, ET AL. */
/*  1983, ANNUAL REV. ASTRON. ASTROPHYS.21, 165 (1983) FOR THE MEANING */
/*  OF THIS OBSCURE TERM. */
/* THE VALUES OF Q1(I),...Q7(I) GIVEN BELOW WERE OBTAINED USING THE DATA */
/*  IN NEUTRINO ASTROPHYSICS WITH THE AID OF AUXILARY COMPUTER CODES */
/*  THAT GENERATED ACCURATE EVALUATIONS. THE NUMBERS GIVEN HERE ARE */
/*  IN MANY CASES COMPLETELY DIFFERENT FROM THE VALUES IN THE ORIGINAL */
/*  YALE CODE. */
/* NRXNS IS THE NUMBER OF REACTIONS BEING TRACKED. */
/* DBG 8/94 APPLIED MHP UPDATE TO NUCLEAR REACTIONS */
/* 10/13/97. Changed Q(I) so that are now calculated for the bare nuclear */
/* masses. The calculates were made cues.f . Last date on the calculations */
/* in my notes is 10/10/97.  Note Q6 is -tau(T_9 = 1); in cues.f, I calculate */
/* tau(T_6 = 1). The connection is:  Q6 = 0.1*tau(cues.f). */


/* BP00 values */
/*      DATA Q1/0.12317,.03392,.0325,.0304,.03035,.0273,.02494,.040572/, */
/*     1 Q2/1.08749,-.273,-.2085,.7630,-0.4044,-1.60,-1.224, -0.2095/, */
/*     2 Q3/.93833,-.0648,-.0474,.1626,-.08598,-.3064,-.2139,-0.0595/, */
/*     3 Q4/0.,0.,0.,4.79,7.456,0.0,.69703,.16762/, */
/*     4 Q5/0.,0.,0.,2.595,4.032,0.0,0.3097,.12114/, */
/*     5 Q6/-3.3804,-12.2757,-12.826,-13.6899,-13.7173,-15.2281, */
/*     5    -16.6925/, */
/*     6 Q7/20.8964,76.6003,67.8036,69.130,70.3809,69.8517,70.8012/, */
/*     7 Q8/0.,0.,0.,0.0,0.0,0.0,0.0/, */
/*     8NRXNS/13/ */
/* Revised values 7/21/03 */
/* For different values of SSTANDARD, check the comments in ENGEB */
/* ********************************************************************* */
/* THE VALUES OF SSTANDARD(I) ARE TO BE CHANGED FROM UNITY IF THE CROSS */
/*  SECTION FACTORS ARE NOT THE ONES GIVEN IN NEUTRINO ASTROPHYSICS, */
/*  TABLE 3.2 AND TABLE 3.4 . */
/* THE CURRENT VALUES ARE CHANGED TO BE THE PREFERRED VALUES LISTED IN */
/*  THE LAST COLUMN OF TABLE 1 OF BAHCALL AND PINSONNEAULT (1991), */
/*   6/14/91. */
/*  THE VALUE OF SSTANDARD(17) FOR HEP IS TAKEN FROM WOLFS ET AL. , PHYS. */
/*   REV. LETTERS, 63, 2721 (1989).  IT CORRESPONDS TO AN S SUB 0 = */
/*   15.3E-20 KEV-BARNS, A FACTOR OF 1.913 LARGER THAN FOR THE OLDER */
/*   MEASUREMENTS USED IN NEUTRINO ASTROPHYSICS. */
/* ********************************************************************* */
/* ZPRD IS USED IN SCREENING CALCULATIONS. IT IS THE PRODUCT OF THE */
/*  CHARGES OF THE INTERACTING IONS. ZPRD WAS CHECKED. Z86 IS USED */
/*  IN CALCULATING INTERMEDIATE SCREENING AND IS DEFINED BY GRABOSKE ET */
/*  AL, AP. J. 181, PAGE 465 (1973), IN TABLE 4.  Z86 WAS CHECKED AND */
/*  SOME NUMERICAL VALUES WERE MADE SLIGHTLY MORE ACCURATE.  Z53, Z43, */
/*  AND Z23 ARE ALSO DEFINED IN TABLE 4 (SEE ABOVE).  SINCE THEY ARE */
/*  ONLY USED IN STRONG SCREENING, THE VALUES OF Z53, Z43, AND Z23 */
/*  WERE NOT CHECKED. */
/* DEFINE NEXT THE FRACTIONAL ABUNDANCES BY MASS OF THE IMPORTANT */
/*  ISOTOPES. */
/* X, Y, Z, XHE3,..., XBE9 ARE THE MASS FRACTIONS OF THE ISOTOPES. */
/*  THE ABUNDANCES OF NEUTRONS, H2, H3, NE20,AND MG24, WHICH ARE, */
/*  RESPECTIVELY, XFRAC(I) FOR I = 1,3,4,12,13, ARE NO LONGER USED. */
    xfrac[0] = 0.f;
    xfrac[1] = *x;
    xfrac[2] = 0.f;
    xfrac[3] = 0.f;
    xfrac[4] = *xhe3;
    xfrac[5] = *y;
    xfrac[6] = *xc12;
    xfrac[7] = *xc13;
    xfrac[8] = *xn14;
    xfrac[9] = *xo16;
    xfrac[10] = *xo18;
    xfrac[11] = 0.f;
    xfrac[12] = 0.f;
/* ******************************************************************* */
/* BEGIN CALCULATION OF SCREENING CORRECTION. */
/* ******************************************************************* */
/*  THE BASIC REFERENCES ARE SALPETER, AUSTRALIAN JOURNAL OF PHYSICS, */
/*  VOL. 7, 373 (1954). THE FORMULA FOR WEAK SCREENING THAT IS BEING */
/*  PROGRAMMED IS EQUATION (25) OF THIS PAPER. THE OTHER IMPORTANT */
/*  REFERENCES ARE: DEWITT, GRABOSKE, AND COOPER, AP. J. 181, 439 (1973) */
/*  AND GRABOSKE ET AL., AP. J. 181, 457 (1973). THE VALUES OF EMU AND */
/*  ZET ARE ESSENTIAL FOR COMPUTING WEAK SCREENING; THE VALUE OF AMU IS */
/*  USED IN AN NON-ESSENTIAL WAY IN THIS COMPUTATION. XTR IS USED IN */
/*  COMPUTING INTERMEDIATE SCREENING. */
/* AMU IS ONE OVER THE MEAN MOLECULAR WEIGHT OF THE IONS, MU SUB I . */
/* EMU IS ONE OVER THE ELECTRON MEAN MOLECULAR WEIGHT, MU SUB E. */
/*  EMU IS USED HERE AS THE NAME FOR THE SECOND PART OF THE ZETA FUNCTION */
/*  IN THE SALPETER EXPRESSION FOR WEAK SCREENING. */
/* XTR IS USED LATER IN THE INTERMEDIATE SCREENING CALCULATION.  THE AVERAGE */
/*  OF THE QUANTITY Z**(3B -1) IS EQUAL TO XTR/AMU. */
/* ZET IS THE FIRST PART OF THE SALPETER SCREENING ZETA VARIABLE. */
/* MU = SUM OVER I OF [X(I)/A(I)]. */
/* MU SUB E = SUM OVER I [ Z(I)*X(I)/A(I)]. */
    amu = 0.f;
    emu = 0.f;
    xtr = 0.f;
    zet = 0.f;
    i__1 = nelem;
    for (i__ = 1; i__ <= i__1; ++i__) {
	trm = xfrac[i__ - 1] / anuc[i__ - 1];
	amu += trm;
	emu += trm * znuc[i__ - 1];
	xtr += trm * pow_dd(&znuc[i__ - 1], &c_b3);
/* Computing 2nd power */
	d__1 = znuc[i__ - 1];
	zet += trm * (d__1 * d__1);
/* L10: */
    }
/* DL AND DT ARE THE THE LOG10 OF THE DENSITY AND TEMPERATURE. */
/*  THE UNIT OF TEMPERATURE IS 10^9 K AND THE UNIT OF DENSITY IS */
/*  GM PER CM^3 . */
/* DD = LOG RHO TO THE BASE 10. */
/* CLN = LN10.  CLN IS CONVERSION BETWEEN LOG10 AND LN. */
/* CONVERT DENSITY TO UNLOGGED FORM. */
/* RWE = RHO/(MU SUB E), I. E., THE NUMBER OF ELECTRONS DIVIDED BY */
/*  AVOGADRO'S NUMBER. */
    rwe = exp(const1_1.cln * *dl) * emu;
/* THE EXPRESSION FOR RWE WAS INCORRECT IN THE ORIGINAL YALE SUBROUTINE. */
/*  THE ORIGINAL VERSION HAD ( EXP(CLN*DL) ) DIVIDED BY EMU INSTEAD OF */
/*  MULTIPLIED BY EMU.  RWE IS USED LATER IN COMPUTING THE SCREENING */
/*  CORRECTION. */
    dd = *dl;
/* SET RATES EQUAL TO ZERO FOR THE LOG_10(T) < TCUT(1) */
    if (*tl <= ctlim_1.tcut[0]) {
	i__1 = nrxns;
	for (i__ = 1; i__ <= i__1; ++i__) {
	    rate[i__ - 1] = 0.f;
/* L20: */
	}
	goto L200;
    }
/* T9P13 IS THE TEMPERATURE IN UNITS OF 10^9 DEGREES K TO THE PLUS 1/3 */
/*  POWER.  MINUS IS DENOTED BY M.  HERE T9 IS THE TEMPERATURE IN UNITS */
/*  OF 10^9 K, CONVERTED FROM THE LOG_10 (T) AND RHO IS THE DENSITY IN */
/*  CGS UNITS. */
    rho = exp(const1_1.cln * dd);
    t9 = exp(const1_1.cln * (*tl - 9.));
    t9p13 = pow_dd(&t9, &const1_1.cc13);
/* Computing 2nd power */
    d__1 = t9p13;
    t9p23 = d__1 * d__1;
    t9m13 = 1.f / t9p13;
/* Computing 2nd power */
    d__1 = t9m13;
    t9m23 = d__1 * d__1;
    t9m1 = 1.f / t9;
/* Computing 2nd power */
    d__1 = t9m1;
    t9m2 = d__1 * d__1;
    t9m12 = 1.f / sqrt(t9);
    t9m32 = t9m1 * t9m12;
/* *********************************** */
/* F PRIME/F */
/* *********************************** */
/* THE NEXT PIECE OF CODE COMPUTES FIRST THE FERMI ENERGY DIVIDED BY KT, WHERE */
/*  PFMC2 IS THE FERMI MOMENTUM DIVIDED BY MASS OF ELECTRON TIMES C, ALL */
/*  SQUARED AND EFMKT IS THE FERMI ENERGY DIVIDED BY KT.  THE QUANTITY */
/*  FPRF IS THE RATIO OF F PRIME TO F IN SALPETER'S SCREENING CORRECTION. */
/*  THE VALUE OF FPRF IS DETERMINED IN THE INTERMEDIATE CASE BY AN */
/*  INTERPOLATION FORMULA DEPENDING UPON THE DEGREE OF DEGENERACY, AS */
/*  MEASURED BY DEGD = LOG10(E_F/KT). THE NUMERICAL VALUES FOR THE FIT */
/*  WERE TAKEN FROM SALPETER'S ORIGINAL PAPER, FIGURE 1. THE ONLY CHANGES */
/*  IN THIS PART OF THE SUBROUTINE WERE THE CORRECTION OF THE ERROR IN */
/*  THE DEFINITION OF RWE (SEE ABOVE) AND REFINEMENTS OF THE COEFFICIENTS */
/*  IN THE EXPRESSIONS FOR PFMC2 AND EFMKT. */
    pfmc2 = pow_dd(&rwe, &c_b6) * 1.017677e-4f;
    efmkt = t9m1 * 5.92986f * (sqrt(pfmc2 + 1.f) - 1.f);
    if (efmkt <= .01f) {
	fprf = 1.f;
    } else {
	degd = d_lg10(&efmkt);
	if (degd >= 1.5f) {
	    fprf = 0.f;
	} else {
/* Computing 2nd power */
	    d__1 = degd;
/* Computing 3rd power */
	    d__2 = degd;
/* Computing 4th power */
	    d__3 = degd, d__3 *= d__3;
/* Computing 5th power */
	    d__4 = degd, d__5 = d__4, d__4 *= d__4;
/* Computing 6th power */
	    d__6 = degd, d__6 *= d__6;
	    fprf = .75793f - degd * .54621f - d__1 * d__1 * .30964f + d__2 * (
		    d__2 * d__2) * .12535f + d__3 * d__3 * .1203f - d__5 * (
		    d__4 * d__4) * .012857f - d__6 * (d__6 * d__6) * .014768f;
	}
    }
/* END OF CALCULATION OF FERMI ENERGY DIVIDED BY KT AND THE INTERPOLATION */
/*  FORMULA FOR (F PRIME/F), WHICH APPEARS IN SALPETER'S SCREENING */
/*  FORMULA. */
/* NOW WE GET TO THE COMPUTATION OF WEAK SCREENING (SEE ALSO PAGE 61 OF */
/*  NEUTRINO ASTROPHYSICS, WHICH GIVES ONLY A SIMPLIFIED FORMULA) AND */
/*  ALSO THE MORE COMPLICATED INTERMEDIATE AND STRONG SCREENING CASES */
/*  (SEE REFERENCES TO AP. J. 181 ABOVE FOR INTERMEDIATE */
/*  AND STRONG SCREENING), ESPECIALLY PAGE 465. */
/* XXL IS USED IN ALL THE SCREENING FORMULAE.  THIS QUANTITY IS THE */
/*  IS THE FUNCTION CALLED LAMBDA SUB ZERO BY GRABOSKE ET AL. THE */
/*  QUANTITY XXL**0.86 = XXL8 IS USED IN CALCULATING INTERMEDIATE */
/*  SCREENING. */
/* ZCURL IS THE QUANTITY DEFINED BY EQUATION (4) OF DEWITT ET AL; IT */
/*  IS THEIR Z WITH A CURLY SYMBOL ON ITS TOP. ZCURL IS USED IN WEAK */
/*  AND IN INTERMEDIATE SCREENING AND WAS FIRST DEFINED BY SALPETER. */
/*  ZCURL IS THE SAME AS SALPETER'S ZETA EXCEPT FOR THE FACTOR OF 1/AMU. */
/* (Z SUB 1 TIMES Z SUB 2)*XXL*ZCURL GIVES THE WEAK SCREENING FACTOR, */
/*  THE SAME AS SALPETER OR AS EQUATION (19) OF GRABOSKE ET AL. */
/* Z BAR IS THE SAME AS Z BAR OF DE WITT ET AL AND IS THE AVERAGE CHARGE */
/*  OF THE IONS.  IT IS EQUAL TO EMU/AMU.  THE QUANTITY (Z BAR)**0.28 = */
/*  Z28 OCCURS IN THE COMPUTATION OF INTERMEDIATE SCREENING. */
/* XXL6 IS USED FOR COMPUTING STRONG STRONG SCREENING. */
/* THE NOTATION USED HERE IS EXPLAINED IN LARGE PART BY */
/*  EQUATION (4) OF DEWITT ET AL., AP. J. 181, PAGE 439. */
/* THE FINAL EXPRESSION FOR WEAK SCREENING IS EXACTLY EQUAL TO SALPETER'S */
/*  FORMULA, WHICH INCLUDES A DEGENERACY CORRECTION. THE MORE GENERAL */
/*  EXPRESSIONS ARE GIVEN IN TABLE 4 AND EQUATION (19) OF GRABOSKE ET AL. */
    xxl = t9m32 * 5.9426e-6f * sqrt(rho * amu);
    xxl6 = pow_dd(&xxl, &c_b7);
    xxl8 = pow_dd(&xxl, &c_b8);
    zcurl = sqrt((zet + fprf * emu) / amu);
    zbar = emu / amu;
    z58 = pow_dd(&zcurl, &c_b9);
    z28 = pow_dd(&zbar, &c_b10);
    z33 = pow_dd(&zbar, &const1_1.cc13);
    tm1 = xxl * zcurl;
/* COMPUTE SCREENING FOR EACH OF THE REACTIONS. */
    i__1 = nrxns;
    for (i__ = 1; i__ <= i__1; ++i__) {
	uwk = tm1 * zprd[i__ - 1];
	if (uwk <= weak_1.weakscreening) {
/* WEAKSCREENING IS A NUMERICAL PARAMETER PASSED IN THE FLUX COMMON */
/*  BLOCK. TO OBTAIN THE GRABOSKE ET AL. AND SALPETER STANDARD RESULTS, */
/*  USE: WEAKSCREENING = 0.03.  FOR THE STANDARD SOLAR MODEL, THIS IS THE */
/*  VALUE THAT SHOULD BE ADOPTED. TO INVESTIGATE THE EFFECT OF ALWAYS USING */
/*  WEAK SCREENING, USE A LARGE VALUE FOR WEAKSCREENING, E. G., 30.  AS */
/*  LONG AS WEAKSCREENING IS ASSUMED TO BE BIGGER THAN ONE, THE PROGRAM */
/*  WILL ALWAYS CALCULATE FOR THE SUN WITH THE WEAK SCREENING */
/*  APPROXIMATION. */
/* UTOT IS THE FINAL SCREENING CORRECTION WHICH APPEARS IN THE */
/*  RATE EXPRESSION AS: EXP(UTOT) . */
	    utot[i__ - 1] = uwk;
	} else {
	    uint = xxl8 * .38f * xtr * z86[i__ - 1] / (amu * z58 * z28);
	    if (uwk <= 2.f) {
		utot[i__ - 1] = uint;
	    } else {
		ustr = z33 * .624f * xxl6 * (z53[i__ - 1] + z33 * .316f * z43[
			i__ - 1] + z23[i__ - 1] * .737f / (zbar * xxl6));
		if (ustr < uint || uwk >= 5.f) {
		    utot[i__ - 1] = ustr;
		} else {
		    utot[i__ - 1] = uint;
		}
	    }
	}
/* L30: */
    }
/* **************************************************************** */
/* END OF SCREENING CALCULATION. WEAK AND INTERMEDIATE SCREENING FORMS */
/*  ARE GIVEN CORRECTLY.  STRONG SCREENING WAS NOT CHECKED BECAUSE IT IS */
/*  NOT RELEVANT FOR THE SUN. */
/* **************************************************************** */
    nz = 1;
    if (*x == 0.f) {
	f1 = 0.f;
	f3 = 0.f;
	goto L50;
    }
    nz = 8;
/* ************************************************************** */
/*  CALCULATE REACTION RATES FOR THE THREE PRINCIPAL REACTIONS OF */
/*   THE PP CHAIN: PP, HE3+HE3, HE3 +HE4, AND THE FOUR PROTON */
/*   BURNING REACTIONS ON C12: C13, N14, AND O16. */
/* ************************************************************** */
/* R1 IS (T SUB 9)^(-3/2) TIMES (S SUB EFF)/(S SUB 0). THE CORRECT */
/*  EXPRESSION FOR (S SUB EFF)/(S SUB 0) IS GIVEN IN EQUATION 3.14 OF */
/*  NEUTRINO ASTROPHYSICS.  THE NUMERICAL FORM THAT IS USED IS EQUATION */
/*  52 OF FOWLER, CAUHLAN, AND ZIMMERMAN, VOL. 5, 1967. */
/* RATE(I) IS THE RATE OF THE DIFFERENT REACTIONS PER SECOND PER GRAM, */
/*  EXCEPT THAT THE MASS FRACTIONS ARE OMITTED. */
/* THE PREVIOUS YALE VERSION HAD THE RATE FOR THE O16 + P REACTION */
/*  MULTIPLIED BY T9**(-1/7). THIS FACTOR IS INCORRECT AND HAS BEEN */
/*  REMOVED; IT APPEARED BEFORE AS AN IF STATEMENT REFERRING ONLY TO */
/*  RATE(7). */
    for (i__ = 1; i__ <= 7; ++i__) {
	r1 = t9m23 + q1[i__ - 1] * t9m13 + q2[i__ - 1] + q3[i__ - 1] * t9p13 
		+ q4[i__ - 1] * t9p23 + q5[i__ - 1] * t9;
/* Computing 2nd power */
	d__1 = q8[i__ - 1] * t9;
	rate[i__ - 1] = rho * r1 * exp(q6[i__ - 1] * t9m13 + q7[i__ - 1] + 
		d__1 * d__1 + utot[i__ - 1]);
	rate[i__ - 1] *= cross_1.sstandard[i__ - 1];
	if (rate[i__ - 1] < 1e-30f) {
	    rate[i__ - 1] = 0.;
	}
/* L40: */
    }
/* *************************************************************** */
/* END OF CALCULATION OF REACTION RATES FOR FIRST 7 REACTIONS. */
/* *************************************************************** */
/* *********************************************** */
/* BE7 BURNING */
/* *********************************************** */
/* CALCULATE THE BURNING OF BE7 BY PROTONS (WHICH PRODUCES THE MOST */
/*  EXPERIMENTALLY ACCESSIBLE SOLAR NEUTRINOS) AND THE BURNING OF BE7 */
/*  BY ELECTRON CAPTURE (THE DOMINANT PROCESS). THE PREVIOUSLY USED */
/*  EXPRESSION CONTAINED A TERM THAT WAS PHYSICALLY INCORRECT */
/*  AND ALSO USED CROSS SECTION FACTORS THAT WERE OUT OF DATE. */
/* THE ELECTRON CAPTURE RATE IN SEC^(-1) IS GIVEN BY EQUATION (3.18) OF */
/*  NEUTRINO ASTROPHYSICS.  CAN OMIT THE FACTOR OF RHO (IN CGS UNITS) */
/*  WHICH ALSO APPEARS IN THE BE7PROTON RATE. THE BE7 PROTON CAPTURE */
/*  RATE IS GIVEN BY TABLE 3.2 AND EQUATION (3.12).  NOTE THAT 1 OVER MU */
/*  SUB E IS EQUAL TO EMU. */
/* HERE WE USE THE NOTATION BE7 + PROTON = BE7PROTON AND */
/*  BE7 + E = BE7ELECTRON. */
/* F1 IS THE FRACTION OF THE BE7 THAT IS BURNED BY ELECTRON CAPTURE. */
/* 1-F1 IS THE FRACTION OF THE BE7 THAT IS BURNED BY PROTON CAPTURE. */
/* F3 IS THE FRACTION OF THE N14 THAT IS BURNED BY P, ALPHA REACTION. */
/* 1-F3 IS THE FRACTION OF THE N15 THAT IS BURNED BY P, GAMMA REACTION. */
/* SEE TABLE 21 OF BAHCALL AND ULRICH (1988), REV. MOD. PHYS. 60. */
/* 10/13/97. I changed Temp3 (i.e., tau) by 5/10^5 as a result of */
/* using bare nuclear masses. Previously coefficient was -10.26202. */
/* I did not change Be7electron for the slightly different S0 for */
/* electron capture, since that is done in SStandard. Previous coefficient */
/* in Be7electron expression was (3.126571E+5). 10/14/97. */

    be7electron = t9m12 * 1.752e-10f * ((t9 * 1e3f - 16.f) * .004f + 1.f);
    be7electron = be7electron * emu * cross_1.sstandard[14];
    temp3 = t9m13 * -10.2625f;
    be7proton = *x * 312881.3f * cross_1.sstandard[15] * exp(temp3);
/* INCLUDE FOR BE7PROTON THE T9M23 FACTOR AND ALL CORRECTIONS PROPORTIONAL TO */
/*  Q1,...,Q5 FROM EQUATION 3.14 OF NEUTRINO ASTROPHYSICS. THESE */
/*  CORRECTIONS ARE DEFINED EARLIER IN THIS SUBROUTINE. */
    qrbe7 = t9m23 + q1[7] * t9m13 + q2[7] + q3[7] * t9p13 + q4[7] * t9p23 + 
	    q5[7] * t9;
    be7proton *= qrbe7;
/* CALCULATE THE SCREENING CORRECTION FOR BE7 + P REACTION.  USE WEAK AND */
/*  INTERMEDIATE SCREENING FORMULAE. */
    zprdbe7p = 4.f;
    z86be7p = 5.779f;
    uwk = tm1 * zprdbe7p;
    if (uwk <= weak_1.weakscreening) {
	utotbe7p = uwk;
    } else {
	uint = xxl8 * .38f * xtr * z86be7p / (amu * z58 * z28);
	utotbe7p = uint;
    }
    be7proton *= exp(utotbe7p);
/* END OF CALCULATION OF SCREENING CORRECTION FOR BE7 + P REACTION. */
/* MULTIPLY RATES BY FACTOR OF RHO/[(ATOMIC MASS UNIT)*A(BE7)] TO GET */
/*  IN UNITS OF GM^{-1}.  CALL FACTOR CAMUBE7. Corrected for Be7 bare */
/*  mass number. Previously used 8.582295E+22 in the expression below. */
/*  These corrections were made on 10/14/97. */

    camube7 = rho * 8.584981e22f;
    be7proton = camube7 * be7proton;
    be7electron = camube7 * be7electron;
/* END OF MULTIPLICATION INSERTED NOVEMBER 6, 1990. */
    f1 = be7electron / (be7electron + be7proton);
/* ********************************************************************* */
/* END OF CALCULATION OF CRUCIAL BE7 ELECTRON CAPTURE AND PROTON CAPTURE */
/*  RATES AND THEIR RATIO. */
/* ********************************************************************* */
/* *************************** */
/* N15 + P BRANCHING. */
/* *************************** */
/* THE FOLLOWING STATEMENTS COMPUTE THE BRANCHING OF N15(P,ALPHA)C12 */
/*  AND N15(P,GAMMA)O16. THESE STATEMENTS REPLACE OUTDATED STATEMENTS */
/*  IN THE YALE CODE. THE CNO CROSS-SECTION FACTORS ARE FROM TABLE 3.4 */
/*  OF NEUTRINO ASTROPHYSICS.  THE RATIO OF THE REACTIONS DEPENDS ONLY */
/*  UPON THE EFFECTIVE ZERO ENERGY S-FACTOR, WHICH IS S0(ZERO ENERGY) */
/*  TIMES THE COMBINATION OF TEMPERATURE AND S-FACTOR DERIVATIVES/S0 */
/*  THAT WAS USED PREVIOUSLY AS R1 IN THE RATE CALCULATIONS. THE */
/*  NUMERICAL COEFFICIENTS THAT APPEAR IN THE RATE WERE REPRESENTED */
/*  BY THE Q1(J),...Q5(J) FOR THE OTHER REACTIONS. */
/*  THE QVALUES FOR THE N15 REACTIONS HAVE BEEN COMPUTED SEPARATELY. */
/* DBG 8/94 APPLIED MHP UPDATE TO NUCLEAR REACTIONS */
/*  To agree with Solar Fusion Workshop paper, the value of S0 in keV-b */
/*  has been changed from 78000. to 675000. on 9/25/97. On 10/14/97, */
/*  JNB changed cues.f so as to compute the Q-coefficients for the N15 + p */
/*  reactions.  Also, checked that the coefficients are the same as the */
/*  ones given earlier in energy.f when we use the older CNO data. */

    o16gamma = t9m23 + t9m13 * .0273016f + .14374f + t9p13 * .02749f + t9p23 *
	     6.14685f + t9 * 2.9894f;
/* MULTIPLY BY THE VALUE OF S0 IN KEV-B. */
    o16gamma *= 64.f;

    c12alpha = t9m23 + t9m13 * .0273016f + 2.01186f + t9p13 * .384763f + 
	    t9p23 * 17.0579f + t9 * 8.2958f;
    c12alpha *= 67500.f;
    f3 = c12alpha / (c12alpha + o16gamma);
    f4 = 1. - f3;
/* END OF NEW ROUTINE FOR THE BRANCHING OF N15 + P . */
L50:
    i__1 = nrxns;
    for (i__ = nz; i__ <= i__1; ++i__) {
	rate[i__ - 1] = 0.f;
/* L60: */
    }
/* ***MHP 3/91 ALPHA CAPTURE REACTIONS UPDATED TO CAUGHLAN AND FOWLER(1988) */
/*   RATES.  THE RATES ARE EXPRESSED IN THE SAME TERMS USED BY CZ, WITH */
/*   THE CONVERSION FACTOR IN THE FRONT OBTAINED FROM VANDENBERG'S */
/*   NOTES ON THE REACTION RATES. */
/*  RATE(8)  HE4+C13 */
/*  RATE(10) HE4+C12=>O16 */
/*  RATE(11) HE4+N14=>O18 */
/*  RATE(12) TRIPLE ALPHA */
    if (*tl < ctlim_1.tcut[3]) {
	goto L100;
    }
/* C13(ALPHA,N) O16 */
    r1 = t9m23 + t9m13 * .0129 + 2.04 + t9p13 * .184;
/* Computing 2nd power */
    d__1 = t9 / 1.284;
    a1 = exp(t9m13 * -32.329 - d__1 * d__1) * 6.77e15;
    a2 = exp(t9m1 * -9.373f) * 3.82e5;
    a3 = exp(t9m1 * -11.873f) * 1.41e6;
    a4 = exp(t9m1 * -20.409f) * 2e9;
    a5 = exp(t9m1 * -29.283f) * 2.92e9;
    rate[7] = rho * 1.157126e22 * exp(utot[7]) * (a1 * r1 + t9m32 * (a2 + a3 
	    + a4 + a5));
/* C12(ALPHA,GAMMA)O16 */
    r1 = 1. / (t9m23 * .0489 + 1.);
    r2 = 1. / (t9m23 * .2654 + 1.);
    a1 = t9m2 * exp(t9m13 * -32.12f);
/* Computing 2nd power */
    d__1 = r1;
/* Computing 2nd power */
    d__2 = t9 / 3.496f;
    a2 = d__1 * d__1 * 1.04e8 * exp(-(d__2 * d__2));
/* Computing 2nd power */
    d__1 = r2;
    a3 = d__1 * d__1 * 1.76e8;
    a4 = t9m32 * 1250. * exp(t9m1 * -27.499f);
/* Computing 5th power */
    d__1 = t9, d__2 = d__1, d__1 *= d__1;
    a5 = d__2 * (d__1 * d__1) * .0143 * exp(t9m1 * -15.541f);
    rate[9] = rho * 1.25388e22 * exp(utot[9]) * (a1 * (a2 + a3) + a4 + a5);
/* N14(ALPHA,GAMMA)F18 + F18=>O18+EPLUS+NU */
    r1 = t9m23 + t9m13 * .012 + 1.45 + t9p13 * .177 + t9p23 * 1.97 + t9 * 
	    .406;
/* Computing 2nd power */
    d__1 = t9 / .881;
    a1 = exp(t9m13 * -36.031 - d__1 * d__1) * 7.78e9;
    a2 = t9m32 * 2.36e-10 * exp(t9m1 * -2.798);
    a3 = t9m32 * 2.03 * exp(t9m1 * -5.054);
    a4 = t9m23 * 11500. * exp(t9m1 * -12.31f);
    rate[10] = rho * 1.07452e22 * exp(utot[10]) * (a1 * r1 + a2 + a3 + a4);
/* TRIPLE ALPHA */
/* Computing 2nd power */
    d__1 = rho;
    rate[11] = d__1 * d__1 * 1.565315e21 * t9m1 * t9m2 * 2.79e-8f * exp(t9m1 *
	     -4.4027f + utot[11]);
L100:
    rate[8] = 0.;
    rate[12] = 0.;
/* END OF XEROING OUT OF REACTIONS 9 AND 13. */
    i__1 = nrxns;
    for (i__ = 1; i__ <= i__1; ++i__) {
	if (rate[i__ - 1] <= 1e-5f) {
	    rate[i__ - 1] = 0.f;
	}
/* L130: */
    }
/* ****************************************************** */
/* RATES PER 10^9 YEARS PER ATOMIC MASS UNIT: HRK(IU) */
/* ****************************************************** */
/* HR1, ..., HR13 ARE THE RATES OF THE INDIVIDUAL REACTIONS. */
/*  THE INTERPRETATION OF WHICH REACTION GOES WITH WHICH SYMBOL CAN BE */
/*  MADE EASILY BY LOOKING AT THE DEFINITIONS OF THE EG(I)'S. */
/*  THE ABUNDANCES ARE UPDATED IN SUBROUTINE KEMCOM USING THESE MATRICES. */
/* C21 IS THE PRODUCT OF (10^9 YEARS/1 SECOND)*(1 ATOMIC MASS UNIT/1 */
/*  GRAM). I HAVE USED HERE SIDEREAL YEAR IN CONVERTING TO SECONDS. */
L200:
    hr1[*iu] = rate[0] * c21;
    hr2[*iu] = rate[1] * c21;
    hr3[*iu] = rate[2] * c21;
    hr4[*iu] = rate[3] * c21;
    hr5[*iu] = rate[4] * c21;
    hr6[*iu] = rate[5] * c21;
    hr7[*iu] = rate[6] * c21;
    hr8[*iu] = rate[7] * c21;
    hr9[*iu] = rate[8] * c21;
    hr10[*iu] = rate[9] * c21;
    hr11[*iu] = rate[10] * c21;
    hr12[*iu] = rate[11] * c21;
    hr13[*iu] = rate[12] * c21;
    hf1[*iu] = f3;
    hf2[*iu] = f1;
/* **************************************** */
/* END OF COMPUTATION OF HRK(IU). */
/* **************************************** */
    return 0;
} /* rates_ */

