/* engeb.f -- translated by f2c (version 20061008).
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
    doublereal drate[5000], drate0[5000], fmassacc;
    integer jcz;
} deuter_;

#define deuter_1 deuter_

struct {
    integer ilast, idebug, itrack, ishort, imilne, imodpt, istor, iowr;
} luout_;

#define luout_1 luout_

struct {
    doublereal atime[14], tcut[5], tscut, tenv0, tenv1, tenv, tgcut;
} ctlim_;

#define ctlim_1 ctlim_

struct {
    doublereal cln, clni, c4pi, c4pil, c4pi3l, cc13, cc23, cpi;
} const1_;

#define const1_1 const1_

struct {
    doublereal cdelrl, cmixl, cmixl2, cmixl3, clndp, csecyr;
} const3_;

#define const3_1 const3_

struct {
    integer niter4;
    logical lnews, lsnu;
} neweng_;

#define neweng_1 neweng_

struct {
    doublereal ealpca, enu;
} neweps_;

#define neweps_1 neweps_

struct {
    doublereal flux[10], fluxtot[10], clsnu, gasnu;
} fluxes_;

#define fluxes_1 fluxes_

struct {
    doublereal be7massfraction;
} be7_;

#define be7_1 be7_

struct {
    doublereal dsnudt, dsnudd;
    logical lnulos1;
} nuloss_;

#define nuloss_1 nuloss_

struct {
    doublereal sstandard[17], qs0e[8], qqs0ee[8], fo16, fc12;
    logical lnewnuc;
} cross_;

#define cross_1 cross_

struct {
    doublereal weakscreening;
} weak_;

#define weak_1 weak_

struct {
    logical lnewtcz, lcalcenv;
    doublereal taucz, taucz0, pphot, pphot0, fracstep;
} ovrtrn_;

#define ovrtrn_1 ovrtrn_

struct {
    doublereal enghe3, he3all, umhe33[5000], umheal[5000];
} grab_;

#define grab_1 grab_

/* Table of constant values */

static doublereal c_b3 = 1.58;
static doublereal c_b6 = .6666667;
static doublereal c_b7 = .666667;
static doublereal c_b8 = .86;
static doublereal c_b9 = .58;
static doublereal c_b10 = .28;
static doublereal c_b19 = 10.;

/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */
/*   ENGEB */
/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */
/* Subroutine */ int engeb_(doublereal *epp1, doublereal *epp2, doublereal *
	epp3, doublereal *ecn, doublereal *e3al, doublereal *pep, doublereal *
	pet, doublereal *sum1, doublereal *dl, doublereal *tl, doublereal *x, 
	doublereal *y, doublereal *xhe3, doublereal *xc12, doublereal *xc13, 
	doublereal *xn14, doublereal *xo16, doublereal *xo18, doublereal *xh2,
	 integer *iu, doublereal *hr1, doublereal *hr2, doublereal *hr3, 
	doublereal *hr4, doublereal *hr5, doublereal *hr6, doublereal *hr7, 
	doublereal *hr8, doublereal *hr9, doublereal *hr10, doublereal *hr11, 
	doublereal *hr12, doublereal *hr13, doublereal *hf1, doublereal *hf2)
{
    /* Initialized data */

    static doublereal v1[7] = { 6.002e19,2.084e20,1.872e21,.9383,-.4141,
	    .05829,5.5924 };
    static doublereal q4[8] = { 0.,0.,0.,4.79,7.456,0.,.69703,.16762 };
    static doublereal q5[8] = { 0.,0.,0.,2.595,4.032,0.,.3097,.12114 };
    static doublereal q6[7] = { -3.3804,-12.2757,-12.826,-13.6899,-13.7173,
	    -15.2281,-16.6925 };
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
    static doublereal v2[7] = { 4.886e10,7.58e10,6.023e10,.00629,.007483,
	    3.061e-4,1.5654 };
    static doublereal z86[13] = { 1.63,5.917,5.917,8.302,8.302,9.52,10.716,
	    16.192,20.978,16.192,18.606,16.192,45.6635 };
    static doublereal c21 = 5.240358e-8;
    static doublereal v3[7] = { 2.32e-7,8.449e-8,1.787e-8,.02581,.01734,
	    6.99e-4,.56457 };
    static doublereal anuc[13] = { 1.008665,1.007276,2.013553,3.015501,
	    3.014933,4.001506,11.996709,13.000064,13.999233,15.990526,
	    17.994772,19.986954,23.978458 };
    static doublereal znuc[13] = { 0.,1.,1.,1.,2.,2.,6.,6.,7.,8.,8.,10.,12. };
    static integer nelem = 13;
    static doublereal q1[8] = { .12317,.03392,.0325,.0304,.03035,.0273,.02494,
	    .040572 };
    static doublereal q2[8] = { 1.08749,-.273,-.2085,.763,-.4044,-1.6,-1.224,
	    -.2095 };
    static doublereal q3[8] = { .93833,-.0648,-.0474,.1626,-.08598,-.3064,
	    -.2139,-.0595 };

    /* System generated locals */
    integer i__1;
    doublereal d__1, d__2, d__3, d__4, d__5, d__6;

    /* Builtin functions */
    double pow_dd(doublereal *, doublereal *), exp(doublereal), sqrt(
	    doublereal), d_lg10(doublereal *);

    /* Local variables */
    static doublereal zprdbe7p, zprdhe3p, utotbe7p, utothe3p, tfacdeut, 
	    rdeutmax;
    extern /* Subroutine */ int neutrino_(doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *);
    static doublereal tfacdeut2, d__;
    static integer i__, k;
    static doublereal t, fourpiau2, be7proton, a1, a2, a3, a4, a5, f1, f2, f3,
	     f4, t9, r1, r2, dd, dg[13], eg[50], el, en, zc, z33, z28, ez, 
	    z58;
    static integer nz;
    static doublereal zo, zz, da1, el2, dr1, tm1, ez3, ex1, ex2, ex3, 
	    be7electron, eli, amu, emu, rho, rwe, t9m1, t9m2, zet, trm, snu, 
	    uwk, xxl, xtr, t9m12, t9m13, t9m23, t9m32, t9p13, t9p23, sum2, 
	    sum3, xxl6, degd, xxl8, qedn, rate[13], dscr[13], dsct[13], fprf, 
	    zbar, emue, temp, qetn, uint, utot[13], ustr, pfmc2, qrbe7, q6hep,
	     temp3, xfrac[13], efmkt, dratt[13], qednx, qdeut, rdeut, polx10, 
	    polx11, polx12, polx21, polx22, zcurl, polx31, polx32, qetnx, 
	    rdeut2, z86be7p, z86he3p, dgdeut, egdeut, dratro[13], camube7, 
	    c12alpha, o16gamma, convert, qrtdeut;

/*      *TL,PDT,PDP,X,Y,Z,XHE3,XC12,XC13,XN14,XN15,XO16,XO17, */
/*      *XO18,XH2,XLI6,XLI7,XBE9,IU,HR1,HR2,HR3,HR4,HR5,HR6,HR7,  ! KC 2025-05-31 */
/* 3/92 DBG Added new neutrino loss calculation routines */
/* NOVEMBER 6, 1990 (JNB) */
/* THE FOLLOWING SUBROUTINE CALCULATES THE NUCLEAR REACTION RATES WITH */
/*   SPECIAL ATTENTION TO DETAIL REQUIRED FOR CALCULATING SOLAR NEUTRINO */
/*   FLUXES. THE NEUTRINO FLUXES ARE EVALUATED ALSO IN THIS SUBROUTINE. */
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

/*  All numbers in this subroutine have been calculated by John Bahcall */
/*  so that they agree with the modern numbers in Neutrino */
/*  Astrophysics (1989) or much more recent results, as indicated in */
/*  comments lines. */

/*  PREVIOUS VERSIONS OF THE YALE CODE */
/*  USED THE NUCLEAR REACTION RATES PRIMARILY FROM FOWLER, CAUGHLAN, AND */
/*  ZIMMERMAN IN ANN. REV. ASTR. AND ASTROPHYS. (1975) OR, FOR THE BE7 AND */
/*  B8 RATES, THE VALUES FROM BAHCALL AND SEARS (1972), ALSO. ANN. REV. ASTR. */
/*  AND ASTROPHYS. SOME VALUES WERE FROM HARRIS ET AL (1983, ANN. REV. ASTR. */
/*  IN A FEW CASES, NUMERICAL ERRORS (NOT DUE TO REVISIONS IN THE NUCLEAR DATA) */
/*  HAVE BEEN CORRECTED.  IN A SMALL NUMBER OF OTHER PLACES, THE PREVIOUS */
/*  PROGRAM CONTAINED PHYSICALLY INCORRECT STATEMENTS, WHICH HAVE BEEN CORRECTED */
/*  IN THE PRESENT VERSION. IN THE COURSE OF THE CHECKING AND REVISIONS, I */
/*  HAVE ADDED MANY COMMENT STATEMENTS IN ORDER TO MAKE THE PROGRAM MORE */
/*  TRANSPARENT AND SIMPLER TO REVISE.  SOME STATEMENTS HAVE BEEN ADDED */
/*  TO SIMPLIFY THE PROCESS OF REVISING THE SUBROUTINE AS IMPROVED DATA */
/*  BECOME AVAILABLE.  FOR EXAMPLE, I HAVE INSERTED EXPLICITLY */
/*  THE STANDARD CROSS SECTION FACTORS IN A WAY THAT IS EASY TO REVISE; */
/*  SSTANDARD(I) = 1.0 WHEN THE ITH CROSS SECTION HAS THE STANDARD VALUE */
/*  MEASUREMENTS USED IN NEUTRINO ASTROPHYSICS. */
/*  MHP 10/97 */

/*  The PREVIOUS standard values of SStandard(I) used were those that */
/*   were given in Table 1 of Bahcall and Pinsonneault (1992).  This work */
/*   was  published in the Reviews of Modern Physics, 64,885, 1992. The */
/*   current version of SStandard(I) refers to Bahcall and */
/*   Pinsonneault(1995) , Rev. Mod. Phys. 67, 781 (1995), Table 1, if */
/*   changes have occured.  Otherwise, they are the same as in the */
/*   Bahcall-Pinsonnealt (1992) Rev. Mod. Phys. article. */

/*  Weakscreening is a parameter set in this subroutine. To obtain */
/*  the Graboske et al. and Salpeter standard results, use: */
/*  weakscreening = 0.03.  To investigate the effect of always using */
/*  weak screening, use a value for weakscreening greater than unity, */
/*  e. g., 30. The transition region between weak and strong screening */
/*  is defined by Graboske et al. as $\Lambda_{12} = 0.1$, see page */
/*  ApJ 181, 465 (1973) [5/15/97]. */

/*  The value of SStandard(17) for hep is taken from Carlson et al (1991) */
/*  Phys. Rev. C 44, 619. It corresponds to an S sub 0 = */
/*  1.3 E-20 keV-barns, a factor of 0.1625  smaller than indicated by the */
/*  older measurements and calculations used in Neutrino Astrophysics. */

/* THE NUCLEAR ENERGY RELEASE TO THE STAR FROM EACH REACTION */
/*  IS TAKEN FROM BAHCALL AND ULRICH, RMP 60, 297 (1988) AND TAKES ACCOUNT */
/*  ACCURATELY OF NEUTRINO ENERGY LOSS. */

/* I HAVE ADDED A NEW SECTION AT THE END OF THE SUBROUTINE THAT */
/*  CALCULATES THE SOLAR NEUTRINO FLUXES AT THE EARTH.  THESE FLUXES */
/*  ARE IN THE UNITS OF CM^-2 SEC^-2 PER GM. TO GET THE FLUX */
/*  FROM A SHELL, MULTIPLY BY THE MASS OF THE SHELL IN UNITS OF */
/*  GRAMS.  THE FLUXES ARE IN A COMMON BLOCK, FLUXES.  I ALSO CALCULATE */
/*  THE FICTIONAL NEUTRINO FLUXES ASSOCIATED WITH THE HE3 + HE3 AND WITH */
/*  THE HE3 + HE4 RECTIONS; THESE FICTIONAL FLUXES ARE USEFUL DIAGNOSTICS */
/*  OF THE SOLAR MODEL. */

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
/*  THE ENERGY DERIVATIVES ENTER IN A FORM IN WHICH THEY ARE DIVIDED BY */
/*  THE ABSOLUTE VALUES OF THE CROSS SECTIONS AT ZERO ENERGY.  THUS IF */
/*  THE SHAPE OF THE CROSS SECTION EXTRAPOLATION IS UNCHANGED AND ONLY */
/*  THE INTERCEPT OF S(E) AT ZERO ENERGY IS CHANGED, THEN NO CORRECTION */
/*  NEED BE MADE FOR THE DERIVATIVES.  THEY ARE AUTOMATICALLY SCALED */
/*  CORRECTLY.  THE EXACT WAY THAT THE DERIVATIVES ENTER THE */
/*  CALCULATIONS IS DESCRIBED IN THE SECTION LABELED ``DEFINING THE */
/*  Q(I)'' THAT IS PRESENTED BELOW. */
/* ************************************ */
/* IDENTIFYING THE REACTIONS. */
/* ************************************ */
/*  THE VALUE OF J DENOTES WHICH OF THE REACTIONS THE COEFFICIENTS */
/*  REFER TO: */
/*  J = 1, PP; J = 2, HE3+HE3; J = 3, HE3+ HE4; J =4, P + C12;  J = 5, P+C13; */
/*  J = 6. P + N14; J = 7, P + O16. */
/*  REACTIONS J = 8, 13 ARE NOT RELEVANT FOR THE SOLAR INTERIOR; THEY ARE */
/*   HOLDOVERS FROM THE EARLIER YALE CODE. */
/*  REACTION 14 IS PEP; REACTION 15 IS BE7 ELECTRON CAPTURE; REACTION 16 IS */
/*   BE7 PROTON CAPTURE; REACTION 17 IS THE HEP REACTION. */
/*  do not change sstandard(14) unless you want to change the ratio of */
/*  pep to pp. */
/*   REACTIONS 14-17 WERE NOT EXPLICITLY INCLUDED IN THE YALE */
/*    PREVIOUS VERSION OF THE CODE, BUT THEY ARE IMPORTANT FOR */
/*    SOLAR NEUTRINO CALCULATIONS. */
/*   THE BRANCHING OF THE N15 + P REACTIONS IS TREATED IN A SERIES OF */
/*    SEPARATE STATEMENTS FOLLOWING THE CALCULATION OF THE BE7 + P */
/*    REACTION. SEE THE DEFINITIONS OF F3 AND F4.  IF THE CROSS-SECTION */
/*    FACTORS OF THE N15 + P REACTIONS ARE REVISED, THEN THE NUMERICAL */
/*    COEFFICIENTS MUST BE CHANGED IN THE DEFINITION OF C12ALPHA AND */
/*    O16GAMMA. */
/* FOR Q1(I), ...,Q(5(I), I = 8 CORRESPONDS TO THE BE7 +  P REACTION. */
/*  THIS ASSIGNMENT FOR I = 8 IS ONLY VALID FOR THE LISTED Q'S AND NOT */
/*  FOR OTHER ARRAYS IN THE PROGRAM. */
/*  IU IS THE SHELL NUMBER. */
/* ADDED SECONDS PER YEAR */
/* 7/91 COMMON BLOCK ADDED TO SKIP FLUX CALCULATIONS IF LSNU=F */
/* 9/06 GN ---  New neutrino loss common block */
/* KC 2025-05-30 reordered common block elements */
/*       COMMON/NULOSS/LNULOS1,DSNUDT,DSNUDD */
/* MHP 8/96 CROSS SECTIONS PUT IN COMMON BLOCK. */
/*      COMMON/CROSS/SSTANDARD(17) */
/* MHP 6/14 DERIVATIVES ADDED */
/* G Somers 3/17, ADDING NEW TAUCZ COMMON BLOCK */
/* JVS 10/11 Common block for He3+He3 luminosity */
/* ***MHP 5/91 STATEMENTS ADDED FOR EVOLVED STAR NEUTRINO LOSSES. */
/* NEUTRINO COEFFICIENTS */
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

/* MHP 10/97 */
/* All of the values of the Q1, ...., Q5 have been recalculated, using */
/*  where needed nuclear cross sections given in Tables 3.2 and 3.4 of */
/*  Neutrino Astrophysics.  They have been updated on 9/16/97 to reflect */
/*  the derivatives and cross section factors in Adelberger et al. 1998, */
/*  the paper on the Solar Fusion Workshop. */

/* ****************************************************************** */
/* Q6 IS THE COEFFICIENT OF THE TEMPERATURE TERM IN THE DEFINITION OF */
/*  TAU, EQUATION 3.10 OF NEUTRINO ASTROPHYSICS. */
/*  TAU = Q6*(T SUB 9 TO THE (-1/3) POWER ). */
/* ****************************************************************** */
/* SLIGHT CHANGES HAVE BEEN MADE IN THE PREVIOUS VALUES OF Q6 TO MAKE */
/*  THE DATA MORE ACCURATE. */
/* NOTE THAT Q6 IS NEGATIVE. */
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
/*     1Q2/1.08749,-.273,-.2085,.7630,-0.4044,-1.60,-1.224, -0.2095/, */
/*     2Q3/.93833,-.0648,-.0474,.1626,-.08598,-.3064,-.2139,-0.0595/, */
/*     3Q4/0.,0.,0.,4.79,7.456,0.0,.69703,.16762/, */
/*     4Q5/0.,0.,0.,2.595,4.032,0.0,0.3097,.12114/, */
/*     5Q6/-3.3804,-12.2757,-12.826,-13.6899,-13.7173,-15.2281,-16.6925/, */
/*     6Q7/20.8964,76.6003,67.8036,69.130,70.3809,69.8517,70.8012/, */
/*     7Q8/0.,0.,0.,0.0,0.0,0.0,0./, */
/*     8NRXNS/13/ */
/* Revised values 7/21/03 */
/*      DATA Q1/0.12317,.03392,.0325,.0304,.03035,.0273,.02494,.040572/, */
/*     1Q2/1.08749,-.273,-.2085,.7630,-0.4044,-1.60,-1.224, 0.0/, */
/*     2Q3/.93833,-.0648,-.0474,.1626,-.08598,-.3064,-.2139,0.0/, */
/*     3Q4/0.,0.,0.,4.79,7.456,0.0,.69703,0.0/, */
/*     4Q5/0.,0.,0.,2.595,4.032,0.0,0.3097,0.0/, */
/*     5Q6/-3.3804,-12.2757,-12.826,-13.6899,-13.7173,-15.2281,-16.6925/, */
/*     6Q7/20.8964,76.6003,67.8036,69.130,70.3809,69.8517,70.8012/, */
/*     7Q8/0.,0.,0.,0.0,0.0,0.0,0./, */
/*     8NRXNS/13/ */
/* MHP 9/14 RESTORED BE7+P DERIVATIVES THAT WERE ZEROED OUT */
/* ***NOTE THAT SSTANDARD IS AN INPUT PARAMETER SET IN THE NAMELIST; */
/* PREVIOUS PUBLISHED SETS OF SSTANDARD ARE INDICATED BELOW. */
/* Changed slightly 3He-3He on 9/25/97 to take account of the S'. */

/* ****************FD Feb 09 ************************************ */
/* Original data from Neutrino Astrophysics 1989 Bahcall */
/* Table 3.2 and 3.4 */
/* Table 3.2 pp */
/*         Q(MeV)  S_0(KeV barns) */
/* H-p     1.44    4.07E-022 */
/* He3-He3 12.86   5.15E+003 */
/* He3-He4 1.59    0.54 */
/* 7Be-p   0.14    0.02 */
/* He-p    19.8    8.00E-020 */


/* Table 3.4 cno   Q(MeV)  S_0(MeV barns) */

/* C12-p   1.94    1.45E-003 */
/* C13-p   7.55    5.50E-003 */
/* N14-p   7.3     3.32E-003 */
/* N15-p O16       12.13   6.40E-002 */
/* N15-p C12       4.97    78 */
/* O16-p   0.6     9.40E-003 */

/* **************************************************************************** */
/* FD-MP Fev 2009 values changed to included the results presented at Gran Sasso */
/* by A. Formicola */
/* Cross sections are: */
/*  s11      pp      = 3.92 +- 0.08 D-25 MeVb      Physun talk Formicola */
/*  s13      Hep     = 8.6  +- 1.3  D-20 KeVb */
/*  s33      He3-He3 = 5.32 +- 0.08 MeVb */
/*  s34      He3_He4 = 0.568 +- 0.014 KeVb         mean LUNA 2007 - Brown 2007 - Singh 2004 */
/*  s17      Be7+p   = 22.1 +-0.6 +-0.6 eVb        A.Junghans PRC70(2004)045501 */
/*  s114     N14-p   = 1.57 +- 0.13 KeVb           Marta et al. Luna coll. PRC 78 (2008) 022802) */

/* This cross section factor gives the following SSTANDARD */

/*  SSTANDARD=0.9631,1.0330,1.0519,0.9241,1.3818,0.47290,1.0, */
/* 1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0108,0.84770,1.0750 */
/* ********************************************************************** */
/* BP03 values, changed 7/21/03 */
/*     SStandard/0.9681,1.0485,0.9815,0.9241,1.3818,1.0542,1.0, */
/*    $          1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0108,0.8807,1.075/ */
/*  Previously (6/16/97) used S at Gamow Peak. Agrees with Workshop paper. */

/*     SStandard/0.9828,1.0485,0.9815,0.9241,1.3818,1.0542,1.0, */
/*    $          1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0108,0.7819,0.2875/ */
/*  This is the revised version created from the Seattle Workshop paper */
/*  on Solar Fusion Reactions. Corrections inserted 9/16/1997. See pg. */
/*  132, Volume 19, of notes. */
/*     9  SStandard/0.9828,1.0291,0.9815,0.9241,1.3818,1.0542,1.0, */
/*     $ 1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.018,0.7819,0.2875/ */
/* VALUES BASED ON PARKER REVIEW ARTICLE. */
/*    9  SSTANDARD/1.0049,0.9709,0.9870,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0, */
/*    $  1.0,1.0,1.0,1.0,1.0,1.913/ */
/* BP 92 VALUES */
/*     9  SSTANDARD/0.9828,0.9709,0.9870,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0, */
/*     $  1.0,1.0,1.0,1.0,0.9218,0.1625/ */
/* BP 95 VALUES */
/*     9  SSTANDARD/0.9558,0.9690,0.9712,1.0,1.0,0.992,1.0,1.0,1.0,1.0, */
/*     $  1.0,1.0,1.0,1.0,1.0,0.92088,0.1625/ */
/* LATEST VALUES, INCLUDING NEW PP RATE */
/*    9  SSTANDARD/0.9558,0.9709,0.9870,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0, */
/*    $  1.0,1.0,1.0,1.0,0.9218,0.1625/ */
/* Dar & Shaviv Values */
/*    9  SSTANDARD/0.9828,0.9709,0.8333,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0, */
/*    $  1.0,1.0,1.0,1.0,0.6996,0.1625/ */
/* Schramm & Shi Values */
/*    9  SSTANDARD/0.9828,1.0874,0.9870,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0, */
/*    $  1.0,1.0,1.0,1.0,0.8313,0.1625/ */
/* ********************************************************************* */
/* THE VALUES OF SSTANDARD(I) ARE TO BE CHANGED FROM UNITY IF THE CROSS */
/*  SECTION FACTORS ARE NOT THE ONES GIVEN IN NEUTRINO ASTROPHYSICS, */
/*  TABLE 3.2 AND TABLE 3.4 . */
/* THE CURRENT VALUES ARE CHANGED TO BE THE PREFERRED VALUES LISTED IN */
/*  THE LAST COLUMN OF TABLE 1 OF BAHCALL AND PINSONNEAULT (1991), */
/*   6/14/91. */
/* ********************************************************************* */
/* ZPRD IS USED IN SCREENING CALCULATIONS. IT IS THE PRODUCT OF THE */
/*  CHARGES OF THE INTERACTING IONS. ZPRD WAS CHECKED. Z86 IS USED */
/*  IN CALCULATING INTERMEDIATE SCREENING AND IS DEFINED BY GRABOSKE ET */
/*  AL, AP. J. 181, PAGE 465 (1973), IN TABLE 4.  Z86 WAS CHECKED AND */
/*  SOME NUMERICAL VALUES WERE MADE SLIGHTLY MORE ACCURATE.  Z53, Z43, */
/*  AND Z23 ARE ALSO DEFINED IN TABLE 4 (SEE ABOVE).  SINCE THEY ARE */
/*  ONLY USED IN STRONG SCREENING, THE VALUES OF Z53, Z43, AND Z23 */
/*  WERE NOT CHECKED. */
/* ZERO OUT THE ENERGY YIELDS FROM NEUTRINOS(ENU) AND ALPHA CAPTURE */
/* REACTIONS (EALPCA). */
    neweps_1.enu = 0.;
    neweps_1.ealpca = 0.;
/* DEFINE NEXT THE FRACTIONAL ABUNDANCES BY MASS OF THE IMPORTANT */
/*  ISOTOPES. */
/* X, Y, Z, XHE3,..., XBE9 ARE THE MASS FRACTIONS OF THE ISOTOPES. */
/*  THE ABUNDANCES OF NEUTRONS, H2, H3, NE20,AND MG24, WHICH ARE, */
/*  RESPECTIVELY, XFRAC(I) FOR I = 1,3,4,12,13, ARE NO LONGER USED. */
    xfrac[0] = 0.f;
    xfrac[1] = *x;
/* MHP 5/02 ADDED DEUTERIUM */
/*      XFRAC(3) = 0.0 */
    xfrac[2] = *xh2;
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
/* PDT AND PDP ARE THE DERIVATIVES OF THE DENSITY WITH RESPECT TO */
/*  TEMPERATURE AND DENSITY. */
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
/* SET RATES EQUAL TO ZERO FOR THE LOG_10(T) < 6.0. */
/* REPLACED FIXED 1 MILLION K THRESHOLD WITH TCUT(1). */
/*      IF(TL.LE.6.0) THEN */
    if (*tl <= ctlim_1.tcut[0]) {
/* MHP 5/02 DEUTERIUM BURNING */
	dgdeut = 0.;
	qrtdeut = 0.;
	en = -20.f;
	*pep = 0.f;
	*pet = 0.f;
	i__1 = nrxns;
	for (i__ = 1; i__ <= i__1; ++i__) {
	    eg[i__ - 1] = 0.f;
	    rate[i__ - 1] = 0.f;
	    dg[i__ - 1] = 0.f;
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
/* MHP 5/02 ADD DEUTERIUM BURNING TERM TO THE CODE */
/* IF DEUTERIUM IS ABOVE A MINIMUM THRESHOLD VALUE. */
/* RDEUT IS THE RATE (EXCLUDING FACTORS OF THE */
/* ABUNDANCES) AND QRTDEUT IS THE DERIVATIVE W/R/T T. */
/* NOTE THAT SCREENING IS EXCLUDED - REASONABLE GIVEN */
/* THE LOW TEMPERATURES INVOLVED. */
    if (*xh2 <= 1e-11) {
	rdeut = 0.;
	qrtdeut = 0.;
    } else {
/* ENERGY YIELD FOR DEUTERIUM BURNING */
	qdeut = 5.494;
	zz = t9m13 * -3.72;
	tfacdeut = t9p13 * .112 + 1. + t9p23 * 3.38 + t9 * 2.65;
/* FACTOR OF 6.023D23/ REFLECTS AVAGADROS NUMBER DIVIDED BY THE */
/* MASS OF THE DEUTERON IN AMU */
	rdeut = rho * 2240. * t9p23 * exp(zz) * tfacdeut * 6.023e23 / anuc[2];
	tfacdeut2 = t9p13 * .112 + t9p23 * 6.76 + t9 * 7.95;
	qrtdeut = const1_1.cc13 * (tfacdeut2 / tfacdeut - 2. - zz);
/* NOW LIMIT DEUTERIUM BURNING IN A SURFACE CZ TO BE ON A TIME SCALE */
/* NO SHORTER THAN THE CONVECTIVE OVERTURN TIMESCALE. */
	if (*iu >= deuter_1.jcz && ovrtrn_1.taucz > 1.) {
	    rdeutmax = 6.023e23 / anuc[2] / ovrtrn_1.taucz;
	    rdeut2 = rdeut * *x;
	    if (rdeut2 > rdeutmax) {
/* JVS 0712 Commented out write command */
/*              WRITE(*,*)RDEUT2,RDEUTMAX */
		if (*x > 1e-6) {
		    rdeut = rdeutmax / *x;
		}
	    }
	}
    }
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
/* DSCR IS THE LOGARITHMIC DERIVATIVE WITH RESPECT TO DENSITY OF THE */
/*  SCREENING CORRECTION, D LOG (E^(U_TOT)) /D LOG RHO . */
/* DSCT IS THE LOGARITHMIC DERIVATIVE OF THE SCREENING WITH RESPECT TO T, */
/* D LOG (E^(U_TOT)) /D LOG T .  THE LIMITING FORMULAE GIVEN IN THE FIRST */
/* OPTION ARE OBVIOUS SINCE IN THE WEAK LIMIT SALPETER'S FORMULA SHOWS */
/* THAT U IS PROPORTIONAL TO THE SQUARE ROOT OF RHO TIMES T^(-3/2). */
	    utot[i__ - 1] = uwk;
	    dscr[i__ - 1] = uwk * .5f;
	    dsct[i__ - 1] = uwk * -1.5f;
	} else {
	    uint = xxl8 * .38f * xtr * z86[i__ - 1] / (amu * z58 * z28);
	    if (uwk <= 2.f) {
		utot[i__ - 1] = uint;
		dscr[i__ - 1] = uint * .43f;
		dsct[i__ - 1] = uint * -1.29f;
	    } else {
		ustr = z33 * .624f * xxl6 * (z53[i__ - 1] + z33 * .316f * z43[
			i__ - 1] + z23[i__ - 1] * .737f / (zbar * xxl6));
		if (ustr < uint || uwk >= 5.f) {
		    utot[i__ - 1] = ustr;
		    dscr[i__ - 1] = z33 * .208f * (z53[i__ - 1] + z33 * .316f 
			    * z43[i__ - 1]) * xxl6;
		    dsct[i__ - 1] = dscr[i__ - 1] * -3.f;
		} else {
		    utot[i__ - 1] = uint;
		    dscr[i__ - 1] = uint * .43f;
		    dsct[i__ - 1] = uint * -1.29f;
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
	f2 = 0.f;
	f3 = 0.f;
	f4 = 0.f;
	goto L50;
    }
    nz = 8;
/* ************************************************************** */
/*  CALCULATE REACTION RATES FOR THE THREE PRINCIPAL RECTIONS OF */
/*   THE PP CHAIN: PP, HE3+HE3, HE3 +HE4, AND THE FOUR PROTON */
/*   BURNING REACTIONS ON C12: C13, N14, AND O16. */
/* ************************************************************** */
/* R1 IS (T SUB 9)^(-3/2) TIMES (S SUB EFF)/(S SUB 0). THE CORRECT */
/*  EXPRESSION FOR (S SUB EFF)/(S SUB 0) IS GIVEN IN EQUATION 3.14 OF */
/*  NEUTRINO ASTROPHYSICS.  THE NUMERICAL FORM THAT IS USED IS EQUATION */
/*  52 OF FOWLER, CAUHLAN, AND ZIMMERMAN, VOL. 5, 1967. */
/* RATE(I) IS THE RATE OF THE DIFFERENT REACTIONS PER SECOND PER GRAM, */
/*  EXCEPT THAT THE MASS FRACTIONS ARE OMITTED AT THIS POINT AND PUT IN */
/*  LATER. */
/* DRATT IS LOGARITHMIC DERIVATIVE OF RATE WITH RESPECT TO TEMPERATURE, */
/*  D LOG RATE DIVIDED BY D LOG T, LOG TO BASE 10. */
/* DRATRO IS THE LOGARITHMIC DERIVATIVE OF THE RATE WITH RESPECT TO */
/*  DENSITY, D LOG RATE/D LOG RHO, LOG TO BASE 10. */
/* THE PREVIOUS YALE VERSION HAD THE RATE FOR THE O16 + P REACTION */
/*  MULTIPLIED BY T9**(-1/7). THIS FACTOR IS INCORRECT AND HAS BEEN */
/*  REMOVED; IT APPEARED BEFORE AS AN IF STATEMENT REFERRING ONLY TO */
/*  RATE(7). */
    for (i__ = 1; i__ <= 7; ++i__) {
/*         R1=T9M23+Q1(I)*T9M13+Q2(I)+Q3(I)*T9P13+Q4(I)*T9P23+Q5(I)*T9 */
/* MHP 8/14 RATES CORRECTED TO PERMIT USER MODIFICATION OF REACTION */
/* RATE DERIVATIVES */
	r1 = t9m23 + q1[i__ - 1] * t9m13 + cross_1.qs0e[i__ - 1] * (q2[i__ - 
		1] + q3[i__ - 1] * t9p13) + cross_1.qqs0ee[i__ - 1] * (q4[i__ 
		- 1] * t9p23 + q5[i__ - 1] * t9);
/* Computing 2nd power */
	d__1 = q8[i__ - 1] * t9;
	rate[i__ - 1] = rho * r1 * exp(q6[i__ - 1] * t9m13 + q7[i__ - 1] + 
		d__1 * d__1 + utot[i__ - 1]);
	rate[i__ - 1] *= cross_1.sstandard[i__ - 1];
	if (rate[i__ - 1] < 1e-30f) {
	    rate[i__ - 1] = 0.f;
	    dratt[i__ - 1] = 0.f;
	} else {
	    dratro[i__ - 1] = dscr[i__ - 1] + 1.f;
/* Computing 2nd power */
	    d__1 = q8[i__ - 1] * t9;
	    dratt[i__ - 1] = dsct[i__ - 1] - (q6[i__ - 1] * t9m13 + (t9m23 * 
		    2.f + q1[i__ - 1] * t9m13 - q3[i__ - 1] * t9p13 - q4[i__ 
		    - 1] * 2.f * t9p23 - q5[i__ - 1] * 3.f * t9) / r1) / 3.f 
		    + d__1 * d__1 * 2.f;
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
/*  BY ELECTRON CAPTURE (THE DOMINANT PROCESS). */
/*  THE ELECTRON CAPTURE RATE IN SEC^(-1) IS GIVEN BY EQUATION (3.18) OF */
/*  NEUTRINO ASTROPHYSICS.  CAN OMIT THE FACTOR OF RHO (IN CGS UNITS) */
/*  WHICH ALSO APPEARS IN THE BE7PROTON RATE. THE BE7 PROTON CAPTURE */
/*  RATE IS GIVEN BY TABLE 3.2 AND EQUATION (3.12).  NOTE THAT 1 OVER MU */
/*  SUB E IS EQUAL TO EMU. */
/* HERE WE USE THE NOTATION BE7 + PROTON = BE7PROTON AND */
/*  BE7 + E = BE7ELECTRON. */
/* F1 IS THE FRACTION OF THE BE7 THAT IS BURNED BY ELECTRON CAPTURE. */
/* F2 IS THE FRACTION OF THE BE7 THAT IS BURNED BY PROTON CAPTURE. */
/* F3 IS THE FRACTION OF THE N14 THAT IS BURNED BY P, ALPHA REACTION. */
/* F4 IS THE FRACTION OF THE N15 THAT IS BURNED BY P, GAMMA REACTION. */
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
/*         QRBE7 = T9M23 + Q1(8)*T9M13 + Q2(8)+ Q3(8)*T9P13 */
/*     $          + Q4(8)*T9P23 + Q5(8)*T9 */
/* MHP 9/14 ADDED THE ABILITY TO ALTER DERIVATIVES INDEPENDENTLY */
    qrbe7 = t9m23 + q1[7] * t9m13 + cross_1.qs0e[7] * (q2[7] + q3[7] * t9p13) 
	    + cross_1.qqs0ee[7] * (q4[7] * t9p23 + q5[7] * t9);
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
    f2 = be7proton / (be7electron + be7proton);
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
/*      O16GAMMA = O16GAMMA*64. */
/* MHP 9/14 ADDED THE OPTION TO MODIFY THE RELATIVE CROSS SECTIONS */
/* FOR N15+P -> C12+ALPHA AND O16+GAMMA */
    o16gamma = o16gamma * 64 * cross_1.fo16;

    c12alpha = t9m23 + t9m13 * .0273016f + 2.01186f + t9p13 * .384763f + 
	    t9p23 * 17.0579f + t9 * 8.2958f;
/*      C12ALPHA = C12ALPHA*67500 */
    c12alpha = c12alpha * 67500 * cross_1.fc12;
    f3 = c12alpha / (c12alpha + o16gamma);
    f4 = 1. - f3;
/* END OF NEW ROUTINE FOR THE BRANCHING OF N15 + P . */
L50:
    i__1 = nrxns;
    for (i__ = nz; i__ <= i__1; ++i__) {
	rate[i__ - 1] = 0.f;
	dratro[i__ - 1] = 0.f;
	dratt[i__ - 1] = 0.f;
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
    dratro[7] = dscr[7] + 1.;
    dr1 = const1_1.cc13 * (t9m23 * -2. - t9m13 * .0129 + t9p13 * .184);
/* Computing 2nd power */
    d__1 = t9 / 1.284;
    da1 = a1 * (const1_1.cc13 * 32.329 * t9m13 - d__1 * d__1 * 2.);
    dratt[7] = dsct[7] + rho / rate[7] * (dr1 * a1 + r1 * da1 + a2 * (t9m1 * 
	    9.373f - 1.5) + a3 * (t9m1 * 11.873f - 1.5) + a4 * (t9m1 * 
	    20.409f - 1.5) + a5 * (t9m1 * 29.283f - 1.5));
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
    dratro[9] = dscr[9] + 1.;
/* Computing 2nd power */
    d__1 = t9 / 3.496f;
    dratt[9] = dsct[9] + rho / rate[9] * (a1 * ((const1_1.cc13 * 32.12f * 
	    t9m13 - 2.) * (a2 + a3) + a2 * (r1 * const1_1.cc13 * .1956f - 
	    d__1 * d__1 * 2.) + a3 * (const1_1.cc13 * 1.0616 * r2)) + a4 * (
	    t9m1 * 27.499f - 1.5) + a5 * (t9m1 * 15.541f + 5.));
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
    dratro[10] = dscr[10] + 1.f;
    dr1 = const1_1.cc13 * (t9m23 * -2. - t9m13 * .012 + t9p13 * .177 + t9p23 *
	     3.94) + t9 * .406;
/* Computing 2nd power */
    d__1 = t9 / .881;
    da1 = a1 * (const1_1.cc13 * 36.031 * t9m13 - d__1 * d__1 * 2.);
    dratt[10] = dsct[10] + rho / rate[10] * (dr1 * a1 + r1 * da1 + a2 * (t9m1 
	    * 2.798 - 1.5) + a3 * (t9m1 * 5.054 - 1.5) + a4 * (t9m1 * 12.31 - 
	    const1_1.cc23));
/* TRIPLE ALPHA */
/* Computing 2nd power */
    d__1 = rho;
    rate[11] = d__1 * d__1 * 1.565315e21 * t9m1 * t9m2 * 2.79e-8f * exp(t9m1 *
	     -4.4027f + utot[11]);
    dratro[11] = dscr[11] + 2.;
    dratt[11] = dsct[11] - 3. + t9m1 * 4.4027;
/* ******************* */
/* EG(I) */
/* ******************* */
/* MULTIPLY THE RATES PER GRAM, RATE(I), BY THE ABUNDANCES OF THE */
/*  REACTING SPECIES BY MASS, TO GET THE TOTAL RATES PER GRAM, EG. */
L100:
    eg[0] = rate[0] * *x * *x;
/* MHP 5/02 ADD DEUTERIUM BURNING IF RELEVANT */
    if (*xh2 > 1e-11) {
	egdeut = rdeut * *x * *xh2;
    } else {
	egdeut = 0.;
    }
    eg[1] = rate[1] * *xhe3 * *xhe3;
    eg[2] = rate[2] * *xhe3 * *y;
    eg[3] = rate[3] * *x * *xc12;
    eg[4] = rate[4] * *x * *xc13;
    eg[5] = rate[5] * *x * *xn14;
    eg[6] = rate[6] * *x * *xo16;
    eg[7] = rate[7] * *y * *xc13;
/*     EG(9)=RATE(9)*Y*X016 */
    eg[9] = rate[9] * *y * *xc12;
    eg[10] = rate[10] * *y * *xn14;
/* Computing 3rd power */
    d__1 = *y;
    eg[11] = rate[11] * (d__1 * (d__1 * d__1));
/*     EG(13)=RATE(13)*XC12*XC12 */
/* ****************************************************************** */
/* **************************************** */
/* ENERGY GENERATION. */
/* **************************************** */
/* CALCULATE ENERGY GENERATION BY MULTIPLYING RATES PER GRAM PER SEC BY */
/*  THE ENERGY RELEASE.  THE ENERGIES ARE TAKEN FROM TABLE 21 OF BAHCALL AND */
/*  ULRICH (1988), REV. MOD. PHYS. 60, 297. THIS TABLE IS BASED UPON A CAREFUL */
/*  CALCULATION OF THE AVERAGE AMOUNT OF ENERGY LOSS BY NEUTRINOS FOR */
/*  EACH REACTION. THE NUMBERS FOR THE C12 + P REACTION SEQUENCE AND THE */
/*  C13 + P REACTION ARE BROKEN DOWN SEPARATELY FOR THIS */
/*  SUBROUTINE. */
/* THE FINAL NUMBERS ARE IN ERG PER GM PER SECOND. */
/* DEFINE THE CONSTANT TO CONVERT MEV'S TO ERGS. THE NUMBERS THAT APPEAR */
/*  ARE IN MEV SO THEY CAN BE EASILY IDENTIFIED. */
    convert = 1.602177e-6f;
/* THE MULTIPLYING CONSTANTS BELOW ARE IN MEV. */
/*  JNB changed the pp energy release by 0.002 MeV because of a better */
/*  estimate of the neutrino energy loss on 9/25/97. See pg. 139 of */
/*  Vol. 19 of my notes.  On pgs. 139-141, I document other small changes */
/*  to this energy generation. No large changes; all of order keV changes */
/*  except for the rare 8B reaction.  9/28/97. */

    dg[0] = eg[0] * 6.664f * convert;
/* MHP 5/02 ADD DEUTERIUM BURNING */
    if (*xh2 > 1e-11) {
	dgdeut = egdeut * qdeut * convert;
    } else {
	dgdeut = 0.;
    }
    dg[1] = eg[1] * 12.86f * convert;
    dg[2] = eg[2] * (f1 * 17.394f + 1.586f + f2 * 11.499f) * convert;
    dg[3] = eg[3] * 3.457372f * convert;
    dg[4] = eg[4] * 7.550628f * convert;
    dg[5] = eg[5] * (f3 * 4.966f + 9.054f + f4 * 12.128f) * convert;
    dg[6] = eg[6] * 3.553f * convert;
    dg[7] = eg[7] * 2.216f * convert;
    dg[9] = eg[9] * 7.162f * convert;
    dg[10] = eg[10] * 5.815f * convert;
    dg[11] = eg[11] * 7.275f * convert;
/* JVS 10/11 Need to grab He3 energy generation */
    grab_1.enghe3 = dg[1];
    grab_1.he3all = dg[1] + dg[2];
/* JVS end */
/* ******************************************************************* */
/* END OF CALCULATION OF ENERGY RELEASE. */
/* ******************************************************************* */
/* SET TO ZERO O16+ALPHA AND C12+C12 RATES. */
    dratro[8] = 0.f;
    dratt[8] = 0.f;
    dg[8] = 0.f;
    dratro[12] = 0.f;
    dratt[12] = 0.f;
    dg[12] = 0.f;
/* END OF XEROING OUT OF REACTIONS 9 AND 13. */
    *sum1 = 0.f;
    sum2 = 0.f;
    sum3 = 0.f;
    i__1 = nrxns;
    for (i__ = 1; i__ <= i__1; ++i__) {
/* ******************************************************************* */
/* SUM OF THE TOTAL ENERGY GENERATION IN ERGS PER GRM PER SECOND WITH */
/* DERIVATIVES WITH RESPECT TO DENSITY AND TO TEMPERATURE. */
/* ******************************************************************* */
/* SUM1 = SUM OF ALL ENERGY GENERATION RATES. NOTE THAT THE BURNING OF */
/*  BE7 IS INCLUDED IN DG(3) ABOVE. */
/* SUM2 = SUM OVER I OF DG(I)* [D LOG RATE(I) / D LOG RHO ]. */
/* SUM3 = SUM OVER I OF DG(I)* [D LOG RATE(I) / D LOG T ]. */
	*sum1 += dg[i__ - 1];
	sum2 += dg[i__ - 1] * dratro[i__ - 1];
	sum3 += dg[i__ - 1] * dratt[i__ - 1];
/* L110: */
    }
/* MHP 5/02 ADD DEUTERIUM BURNING */
/*      IF(IU.LE.10)THEN */
/*         WRITE(*,911)IU,SUM1,DGDEUT,SUM2,SUM3,QRTDEUT */
/*      ENDIF */
/* 911  FORMAT(I5,1P5E13.3) */
    *sum1 += dgdeut;
    sum2 += dgdeut;
    sum3 += dgdeut * qrtdeut;
    if (*sum1 <= 1e-12f) {
	en = -20.f;
	*pep = 0.f;
	*pet = 0.f;
	i__1 = nrxns;
	for (i__ = 1; i__ <= i__1; ++i__) {
	    eg[i__ - 1] = 0.f;
/* L120: */
	}
    } else {
/* ****************************************************** */
/* GLOBAL QUANTITIES THAT ARE RETURNED BY THE SUBROUTINE. */
/* ****************************************************** */
/* PEP AND PET ARE THE DERIVATIVES OF THE TOTAL ENERGY GENERATION RATE */
/*  WITH RESPECT TO DENSITY AND TEMPERATURE. */
/* MHP 5/90 CHANGE DERIVATIVES TO BE D LN EPS/D LN RHO AND D LN EPS/D LN T */
/* TO PUT THEM IN THE SAME FORM AS PRATHER DERIVATIVES. */
/*        EN=DLOG10(SUM1) */
/*        PEPD=SUM2/SUM1 */
/*        PEP=PDP*PEPD */
/*        PET=SUM3/SUM1+PDT*PEPD */
	*pep = sum2;
	*pet = sum3;
    }
/* PDP = D LOG RHO/ D LOG P; PDT = D LOG RHO/ D LOG T. */
/* ***************************************************** */
/* END OF COMPUTATION OF THE GLOBAL QUANTITIES. */
/* ***************************************************** */
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
/* **************************************** */
/* CALCULATING THE TOTAL ENERGY GENERATION. */
/* **************************************** */
/* THE SUMMATION OF THE ENERGIES IS GIVEN IN TABLE 21 OF NEUTRINO */
/*  ASTROPHYSICS. */
/* THE ORIGINAL YALE SUBROUTINE CONTAINED SERIOUS ERRORS.  THE */
/*  CALCULATION OF THE RATE OF ENERGY THROUGH EPP2 AND EPP3 (SEE */
/*  BELOW) CONTAINED TWO FACTORS OF BRANCHING RATIOS, RATHER THAN */
/*  THE SINGLE FACTOR THAT SHOULD BE PRESENT. THIS HAD THE EFFECT */
/*  OF REDUCING ARTIFICIALLY THE ENERGY CALCULATED FROM THESE */
/*  REACTIONS. */
/* EPP1 INCLUDES THE ENERGY GENERATED BY THE PP REACTION, BY THE H2 + P */
/*  REACTION, AND BY THE HE3 + HE3 REACTION.  SEE TABLE 21 OF NEUTRINO */
/*  ASTROPHYSICS. */
    *epp1 = dg[0] + dg[1] + dgdeut;
/*      EPP1 = DG(1)+DG(2) */
/* EPP3 INCLUDES THE ENERGY GENERATED BY THE HE3 + HE4 REACTION AND BY */
/*  THE BURNING OF BE7 THROUGH PROTON CAPTURE. */
/*      EPP3 = EG(3)*(1.586 + F2*11.499)*CONVERT */
    *epp3 = eg[2] * f2 * 13.085000000000001f * convert;
/* EPP2 INCLUDES THE ENERGY GENERATED BY THE HE3 + HE4 REACTION AND BY */
/*  THE BURNING OF BE7 THROUGH ELECTRON CAPTURE. */
/*      EPP2 = EG(3)*(1.586 + F1*17.394)*CONVERT */
    *epp2 = dg[2] - *epp3;
/* ECN IS THE ENERGY GENERATED THROUGH THE CNO CYCLE. */
    *ecn = dg[3] + dg[4] + dg[5] + dg[6];
/* E3AL IS THE ENERGY GENERATED THROUGH THE TRIPLE-ALPHA REACTION AND */
/*  IS NEGLIGIBLE FOR THE SUN. */
    *e3al = dg[11];
/* ENERGY FROM ALPHA CAPTURE REACTIONS. */
    neweps_1.ealpca = dg[7] + dg[9] + dg[10];
    if (neweng_1.lsnu) {
/* MHP 9/91 CHANGE TO TURN OFF NEUTRINO CALC FOR HYDROGEN-EXHAUSTED CORE. */
	if (*x <= 1e-6) {
	    for (i__ = 1; i__ <= 10; ++i__) {
		fluxes_1.flux[i__ - 1] = 0.;
	    }
	} else {
/* **************************************************************** */
/* CALCULATION OF NEUTRINO FLUXES */
/* **************************************************************** */
/* THIS PART OF THE SUBROUTINE CALCULATES THE NEUTRINOS FLUXES IN */
/*  NUMBER PER GRAM PER SQUARE CENTIMETER PER SECOND AT THE EARTH'S SURFACE */
/*  (ASSUMING NOTHING HAPPENS TO THE NEUTRINOS AFTER THEY ARE CREATED). */
/* SEE TABLES 3.1 AND 3.3 OF NEUTRINOS ASTROPHYSICS OR EQUATIONS 6.1-6.8 */
/*  FOR THE REACTIONS. THE ORDER OF THE REACTIONS IS THE SAME AS IN */
/*  EQUATIONS 6.1-6.8 . */
/* DEFINE 4*PI*(AU)**2 . */
	    fourpiau2 = 2.812295e27f;
/* FLUX OF PP NEUTRINOS. */
	    fluxes_1.flux[0] = eg[0] / fourpiau2;
/* FLUX OF PEP NEUTRINOS. USE EQUATION 3.17 OF NEUTRINO ASTROPHYSICS. */
/* Note that should not change SStandard(14) unless the ratio of pep to pp */
/*  is changed.  Pep rate is explicitly scaled here with respect to the pp */
/*  rate. */
	    fluxes_1.flux[1] = rwe * 3.4848e-6f * t9m12 * (t9 * 20.f + 1.f) * 
		    eg[0];
	    fluxes_1.flux[1] = fluxes_1.flux[1] * cross_1.sstandard[13] / 
		    fourpiau2;
/* FLUX OF HEP NEUTRINOS.  USE EQUATION 3.12 DIRECTLY. */
	    q6hep = -6.1399f;
/* Q6 IS THE NEGATIVE OF THE COEFFICIENT OF T9M13 IN TAU, EQUATION 3.10. */
	    fluxes_1.flux[2] = rho * 1.71724e11f * t9m23 * exp(q6hep * t9m13);
/* THE DERIVATIVES OF THE CROSS SECTION FACTOR ARE NOT KNOWN AND ARE */
/*  TAKEN TO BE ZERO.  THE ONLY TERM FROM EQUATION 3.14 THAT SURVIVES */
/*  IS 5/(12*TAU). */
	    fluxes_1.flux[2] = (t9p13 * .067862f + 1.f) * cross_1.sstandard[
		    16] * fluxes_1.flux[2];
/* CALCULATE WEAK OR INTERMEDIATE SCREENING FOR HEP NEUTRINOS. */
	    zprdhe3p = 2.f;
	    z86he3p = 3.08687f;
	    uwk = tm1 * zprdhe3p;
	    if (uwk <= weak_1.weakscreening) {
		utothe3p = uwk;
	    } else {
		uint = xxl8 * .38f * xtr * z86he3p / (amu * z58 * z28);
		utothe3p = uint;
	    }
/* END OF CALCULATION OF SCREENING CORRECTION FOR HE3 + P REACTION. */
	    fluxes_1.flux[2] *= exp(utothe3p);
	    fluxes_1.flux[2] = fluxes_1.flux[2] * *x * *xhe3 / fourpiau2;
/* COMPUTE BE7MASSFRACTION. THIS IS NOT REQUIRED FOR THE NEUTRINO */
/*  FLUXES SINCE BE7 IS ALWAYS IN EQUILIBRIUM WITH THE SLOWER PRODUCTION */
/*  RATE OF HE3 + HE4.  HOWEVER, IT IS OF INTEREST IN SOME APPLICATIONS */
/*  TO KNOW THE BE7 MASS FRACTION, SO I COMPUTE IT HERE AND IT CAN BE */
/*  EXTRACTED WITH A COMMON STATEMENT IF DESIRED. */
	    be7_1.be7massfraction = eg[2] / (be7proton + be7electron);
/* END OF NOVEMBER 6, 1990  ADDITION. */
/* FLUX OF BE7 NEUTRINOS. */
	    fluxes_1.flux[3] = eg[2] * f1 / fourpiau2;
/* FLUX OF B8 NEUTRINOS. */
	    fluxes_1.flux[4] = eg[2] * f2 / fourpiau2;
/* FLUX OF N13 NEUTRINOS. */
	    fluxes_1.flux[5] = eg[3] / fourpiau2;
/* FLUX OF O15 NEUTRINOS. */
	    fluxes_1.flux[6] = eg[5] / fourpiau2;
/* FLUX OF F17 NEUTRINOS. */
	    fluxes_1.flux[7] = eg[6] / fourpiau2;
/* FLUX OF FICTIONAL HE3 + HE3 NEUTRINOS. */
	    fluxes_1.flux[8] = eg[1] / fourpiau2;
/* FLUX OF FICTIONAL HE3 + HE4 NEUTRINOS. */
	    fluxes_1.flux[9] = eg[2] / fourpiau2;
/* SET UNITS OF NEUTRINO FLUXES TO BE 10**10 PER CM^2 PER SEC PER GM AT THE */
/*  EARTH. MULTIPLY BY 10**-10. */
/*  IF THE VALUE FOR THIS SHELL IS NEGLIGIBLY SMALL, SET EQUAL TO ZERO. */
	    for (k = 1; k <= 10; ++k) {
		fluxes_1.flux[k - 1] *= 1e-10f;
		temp = fluxes_1.flux[k - 1];
/* KC 2025-05-30 CHANGED 1.E-50 TO 0.0 TO AVOID UNDERFLOW */
		if (temp <= 0.f) {
		    fluxes_1.flux[k - 1] = 0.f;
		}
	    }
/* MHP 9/91 ENDIF INSERTED HERE. */
	}
    }
/* END OF NEUTRINO FLUX ROUTINE. */

/* ***MHP 5/91 */
/* C CALCULATE NEUTRINO LOSSES FOR NEUTRINO-COOLED CORES OF EVOLVED STARS. */
/* 3/92 DBG Added option to use new (more sophisticated) neutrino loss */
/* routines.  See subroutine NEUTR for complete description. */
    if (*tl <= ctlim_1.tcut[4]) {
	return 0;
    }
    zc = *xc12 + *xc13;
    zo = *xo16 + *xo18;
    t = pow_dd(&c_b19, tl);
    d__ = pow_dd(&c_b19, dl);
/* **** Itoh 1996 Neutrino loss routines - Grant Newsham 9/06 ***** */
    if (nuloss_1.lnulos1) {
	neutrino_(&t, &d__, x, y, &zc, &zo, &snu, &nuloss_1.dsnudt, &
		nuloss_1.dsnudd);
	neweps_1.enu = -snu;
	nuloss_1.dsnudt = -nuloss_1.dsnudt * t / neweps_1.enu;
	nuloss_1.dsnudd = -nuloss_1.dsnudd * d__ / neweps_1.enu;
	*sum1 += neweps_1.enu;
	*pep += nuloss_1.dsnudd;
	*pet = *pep + nuloss_1.dsnudt;
/* **************************************************************** */
    } else {
/*     THESE ARE OLD NEUTRINO LOSS ROUTINES */
	el = t9 / 5.9302f;
	eli = 1.f / el;
	ez = exp(const1_1.cc13 * const1_1.cln * (*dl - 9.f)) * eli * (*x * 
		.2063f + .7937f);
/* Computing 3rd power */
	d__1 = ez;
	ez3 = d__1 * (d__1 * d__1);
	emue = (*x + 1.f) * .5f;
	ex1 = 0.f;
	if (t9 >= .2f) {
/* C PAIR NEUTRINOS */
	    el2 = el * el;
	    polx10 = el2 * (el2 * (el2 * (el2 * 918.6f + 1534.f) + 133.5f) - 
		    13.04f) + 1.f;
	    polx11 = v1[0] + ez * (v1[1] + ez * v1[2]);
	    polx12 = ez3 + eli * (v1[3] + eli * (v1[4] + eli * v1[5]));
	    ex1 = exp(-ez * v1[6] - eli - eli - const1_1.cln * *dl) * polx10 *
		     polx11 / polx12;
	}
/* C PHOTO NEUTRINOS */
	polx21 = v2[0] + ez * (v2[1] + ez * v2[2]);
	polx22 = ez3 + eli * (v2[3] + eli * (v2[4] + eli * v2[5]));
/* Computing 5th power */
	d__1 = el, d__2 = d__1, d__1 *= d__1;
	ex2 = emue * (d__2 * (d__1 * d__1)) * exp(-ez * v2[6]) * polx21 / 
		polx22;
/* C PLASMA NEUTRINOS */
	polx31 = v3[0] + ez * (v3[1] + ez * v3[2]);
	polx32 = ez3 + eli * (v3[3] + eli * (v3[4] + eli * v3[5]));
/* Computing 3rd power */
	d__1 = emue;
	ex3 = d__1 * (d__1 * d__1) * exp(-ez * v3[6] + const1_1.cln * (*dl + *
		dl)) * polx31 / polx32;
	neweps_1.enu = -(ex1 + ex2 + ex3);
	*sum1 += neweps_1.enu;
	qetnx = 0.f;
	qednx = 0.f;
	if (t9 >= .2f) {
/* MHP 10/02 fixed column 72 problem */
	    qedn = ez * (v1[1] + ez * 2.f * v1[2]) / polx11 - ez * v1[6] - 
		    ez3 * 3. / polx12;
	    qetn = -qedn + eli * (v1[3] + eli * (v1[4] * 2.f + eli * 3.f * v1[
		    5])) / polx12;
	    qetnx = el2 * (el2 * (el2 * (el2 * 7348.8f + 9204.f) + 534.f) - 
		    26.08f) / polx10;
	    qetnx = (qetnx + qetn + eli + eli) * ex1;
	    qednx = (const1_1.cc13 * qedn - 1.f) * ex1;
	}
	qedn = ez * (v2[1] + ez * 2.f * v2[2]) / polx21 - ez * v2[6] - ez3 * 
		3.f / polx22;
	qetn = -qedn + eli * (v2[3] + eli * (v2[4] * 2.f + eli * 3.f * v2[5]))
		 / polx22;
	qetnx += (qetn + 5.f) * ex2;
	qednx += const1_1.cc13 * qedn * ex2;
	qedn = ez * (v3[1] + ez * 2.f * v3[2]) / polx31 - ez * v3[6] - ez3 * 
		3.f / polx32;
	qetn = -qedn + eli * (v3[3] + eli * (v3[4] * 2.f + eli * 3.f * v3[5]))
		 / polx32;
	qetnx += qetn * ex3;
	qednx += (const1_1.cc13 * qedn + 2.f) * ex3;
	*pet -= qetnx;
	*pep -= qednx;
    }
    return 0;
} /* engeb_ */

