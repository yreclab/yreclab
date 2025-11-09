/* remap.f -- translated by f2c (version 20061008).
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
    doublereal htoler[10]	/* was [5][2] */, fcorr0, fcorri, fcorr, 
	    hpttol[12];
    integer niter1, niter2, niter3;
} ctol_;

#define ctol_1 ctol_

struct {
    doublereal atime[14], tcut[5], tscut, tenv0, tenv1, tenv, tgcut;
} ctlim_;

#define ctlim_1 ctlim_

struct {
    doublereal dtdif, djok;
    integer itdif1, itdif2;
} difus_;

#define difus_1 difus_

struct {
    doublereal dtwind;
} ct2_;

#define ct2_1 ct2_

struct {
    logical lptime;
} ct3_;

#define ct3_1 ct3_

struct {
    doublereal sstandard[17], qs0e[8], qqs0ee[8], fo16, fc12;
    logical lnewnuc;
} cross_;

#define cross_1 cross_

struct {
    doublereal s0_1_1__, s0_3_3__, s0_3_4__, s0_1_12__, s0_1_13__, s0_1_14__, 
	    s0_1_16__, s0_pep__, s0_1_be7e__, s0_1_be7p__, s0_hep__, 
	    s0_1_15_c12alp__, s0_1_15_o16__, s0p_1_1__, s0p_3_3__, s0p_3_4__, 
	    s0p_1_12__, s0p_1_13__, s0p_1_14__, s0p_1_16__, s0pp_1_12__, 
	    s0pp_1_13__, s0pp_1_16__, s0p_1_be7p__, s0pp_1_be7p__;
} newcross_;

#define newcross_1 newcross_

struct {
    doublereal flag_dx__, flag_dw__, flag_dz__, time_core_min__, time_dl__, 
	    time_dp__, time_dr__, time_dt__, time_dw_global__, time_dw_mix__, 
	    time_dx_core_frac__, time_dx_core_tot__, time_dx_shell__, 
	    time_dx_total__, time_dy_core_frac__, time_dy_core_tot__, 
	    time_dy_shell__, time_dy_total__, tol_czbase_fine_width__, 
	    tol_dl_max__, tol_dm_max__, tol_dm_min__, tol_dp_core_max__, 
	    tol_dp_czbase_max__, tol_dp_env_max__, tol_dx_max__, tol_dz_max__,
	     time_max_dt_frac__;
    logical lstruct_time__, lnewvars;
} newparam_;

#define newparam_1 newparam_

/* MHP 6/2014 */
/* Subroutine to remap new, more intuitively named, namelist parameters */
/* onto existing code parameters */
/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */
/* REMAP */
/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */
/* Subroutine */ int remap_(void)
{
    /* Initialized data */

    static doublereal s0_1_1_ref__ = 4.07e-22;
    static doublereal s0_1_be7p_ref__ = .0243;
    static doublereal s0_hep_ref__ = 8e-20;
    static doublereal s0_1_15_c12alp_ref__ = 67500.;
    static doublereal s0_1_15_o16_ref__ = 64.;
    static doublereal s0_1_1_a98__ = 4e-22;
    static doublereal s0_1_be7p_a98__ = .019;
    static doublereal qs0e_1_1_a98__ = 4.48e-24;
    static doublereal qs0e_3_3_a98__ = -4.1;
    static doublereal qs0e_3_4_a98__ = -3e-4;
    static doublereal qs0e_1_12_a98__ = .0026;
    static doublereal s0_3_3_ref__ = 5150.;
    static doublereal qs0e_1_13_a98__ = -.0078;
    static doublereal qs0e_1_14_a98__ = -.0128;
    static doublereal qs0e_1_16_a98__ = -.024;
    static doublereal qs0e_1_be7p_a98__ = -1.33e-5;
    static doublereal qqs0ee_1_12_a98__ = 8.3e-5;
    static doublereal qqs0ee_1_13_a98__ = 7.3e-4;
    static doublereal qqs0ee_1_16_a98__ = 5.7e-5;
    static doublereal qqs0ee_1_be7p_a98__ = 7.22e-8;
    static doublereal s0_3_4_ref__ = .54;
    static doublereal s0_1_12_ref__ = 1.45;
    static doublereal s0_1_13_ref__ = 5.5;
    static doublereal s0_1_14_ref__ = 3.32;
    static doublereal s0_1_16_ref__ = 9.4;
    static doublereal s0_pep_ref__ = 3.4848e-6;
    static doublereal s0_1_be7e_ref__ = 1.752e-10;

    static integer i__;

/* PARAMETERS NT AND NG FOR TABULATED SURFACE PRESSURES. */
/* PARAMETERS NTA AND NGA FOR TABULATED ALLARD MODEL SURFACE PRESSURES. */
/* MHP 8/96 CROSS SECTIONS PUT IN COMMON BLOCK */
/* MHP 6/14 DERIVATIVES ADDED */
/* 10/14 MHP NEW PARAMETERS - REPLACING DTDIF,DTWIND, HPTTOL & ATIME VECTORS */
/* KC 2025-05-30 reordered common block elements */
/*       COMMON/NEWPARAM/FLAG_DX,FLAG_DW,FLAG_DZ,LSTRUCT_TIME, */
/*      * TOL_DX_MAX,TOL_DZ_MAX,TIME_MAX_DT_FAC,LNEWVARS */
/* NOTE: PEP IS THE PROPORTIONALITY CONSTANT RELATIVE TO PP */
/* NOTE: BE7+E- IS THE PROPORTIONALITY CONSTANT IN THE LINEAR TERM */
/* THE CODE USES T9, NOT T6, SO ANY EXPRESSION IN TERMS OF T/10^6 K */
/* NEEDS TO BE DIVIDED BY 1000^0.5 (FOR BOTH PEP AND BE7+E-) */
/* REFERENCE ADELBERGER ET AL. 1998 CROSS SECTIONS - USED IN HARD-CODED */
/* FIRST AND SECOND DERIVATIVE TERMS (EXPRESSED AS S'/S AND S''/S) */
/* UNITS ARE KeV b */
/*       DATA S0_1_1_A98,S0_3_3_A98,S0_3_4_A98,S0_1_12_A98,S0_1_13_A98/ */
/*      *     4.00D-22,5.4D3,5.3D-1,1.34D0,7.6D0/  ! KC 2025-05-31 */
/*       DATA S0_1_14_A98,S0_1_16_A98,S0_PEP_A98,S0_1_BE7E_A98/ */
/*      *     3.5D0,9.4D0,3.5734D-6,1.77088D-10/ */
/*       DATA S0_1_BE7P_A98,S0_HEP_A98,S0_1_15_C12ALP_A98,S0_1_15_O16_A98/ */
/*      *     0.019D0,2.3D-20,6.75D4,6.4D1/ */
/* REFERENCE FIRST DERRIVATIVES OF CROSS-SECTIONS (ADELBERGER ET AL. 1998) */
/* UNITS ARE b */
/* REFERENCE SECOND DERIVATIVES OF CROSS SECTIONS (ADELBERGER ET AL. 1998) */
/* The code explicitly treats non-equilibrium C12,C13,N14,O16. */
/* N15 burning is assumed to immediately follow N14+p, with the */
/* branching ratio between C12+Alpha and O16+Gamma calculated using */
/* the relative S0 for the two.  To change the branching ratio, change */
/* S0_1_15_C12ALP and S0_1_15_O16.  O17 proton capture is assumed to */
/* immediately follow O16 proton capture, producing N14. */
/* He-burning reactions triple-alpha,C12+He4,C13+He4,N14+He4 are tracked */
/* in the code, using the Caughlin&Fowler(1988) cross-sections.  As resonances */
/* are important for these reactions, a simple scaling by S0 is not sufficient, */
/* and updates should instead use different functional forms (e.g. NACRE II). */
/* IF THE LNEWNUC FLAG IS SET TRUE THE SSTANDARD VECTOR IS NORMALIZED TO UNITY */
/* AND THE INDIVIDUAL CROSS-SECTION VALUES AND THEIR DERIVATIVES ARE USED INSTEAD. */
    for (i__ = 1; i__ <= 8; ++i__) {
	cross_1.qs0e[i__ - 1] = 1.;
	cross_1.qqs0ee[i__ - 1] = 1.;
    }
    cross_1.fc12 = 1.;
    cross_1.fo16 = 1.;
/*      WRITE(*,911)(QS0E(I),I=1,8),(QQS0EE(I),I=1,8), */
/*     * (SSTANDARD(I),I=1,17),LNEWNUC */
/* 911  FORMAT(8E12.3/8E12.3/8E12.3/9E12.3/L5) */
    if (cross_1.lnewnuc) {
	for (i__ = 1; i__ <= 17; ++i__) {
	    cross_1.sstandard[i__ - 1] = 1.;
	}
/* The energy generation subroutine engeb has a vector, SSTANDARD, */
/* which is the ratio of the desired S0 to that of Bahcall & Ulrich (1988). */
/* If this option is true, the namelist SSTANDARD vector is replaced */
/* by explicit cross-sections for individual reactions, and the implied */
/* Sstandard vector is derived here.  The first and second derivatives */
/* of the reactions are permitted to be separately modified, unlike in the */
/* original version of engeb.  In this case the inputs are the ratios */
/* S'/S0 and S''/S0, relative to the Solar Fusion I (Adelberger et al. 1998) ratios. */
	cross_1.sstandard[0] = newcross_1.s0_1_1__ / s0_1_1_ref__;
	cross_1.sstandard[1] = newcross_1.s0_3_3__ / s0_3_3_ref__;
	cross_1.sstandard[2] = newcross_1.s0_3_4__ / s0_3_4_ref__;
	cross_1.sstandard[3] = newcross_1.s0_1_12__ / s0_1_12_ref__;
	cross_1.sstandard[4] = newcross_1.s0_1_13__ / s0_1_13_ref__;
	cross_1.sstandard[5] = newcross_1.s0_1_14__ / s0_1_14_ref__;
	cross_1.sstandard[6] = newcross_1.s0_1_16__ / s0_1_16_ref__;
/*      SSTANDARD(8) = S0_4_13/S0_4_13_REF resonant; not fit by simple S0 */
/*      SSTANDARD(9) = S0_4_16/S0_4_16_REF not used */
/*      SSTANDARD(10) = S0_4_12/S0_4_12_REF resonant; not fit by simple S0 */
/*      SSTANDARD(11) = S0_4_14/S0_4_14_REF resonant; not fit by simple S0 */
/*      SSTANDARD(12) = S0_3A/S0_3A_REF resonant; not fit by simple S0 */
/*      SSTANDARD(13) = S0_12_12/S0_12_12_REF not used */
	cross_1.sstandard[13] = newcross_1.s0_pep__ / s0_pep_ref__;
	cross_1.sstandard[14] = newcross_1.s0_1_be7e__ / s0_1_be7e_ref__;
	cross_1.sstandard[15] = newcross_1.s0_1_be7p__ / s0_1_be7p_ref__;
	cross_1.sstandard[16] = newcross_1.s0_hep__ / s0_hep_ref__;
/* ABILITY TO CHANGE THE HARD-CODED BRANCHING RATIOS FOR THE OUTCOME OF N15+P */
	cross_1.fc12 = newcross_1.s0_1_15_c12alp__ / s0_1_15_c12alp_ref__;
	cross_1.fo16 = newcross_1.s0_1_15_o16__ / s0_1_15_o16_ref__;
/* NUCLEAR REACTION DERIVATIVES ARE USED IN THE VECTORS Q2-Q5 IN ENGEB AND NRATES. */
/* THE Q2 AND Q3 FACTORS ARE DEFINED PROPORTIONAL TO S'/S (REFERENCE: SOLAR FUSION I IN 1998) */
/* THE Q4 AND Q5 FACTORS ARE DEFINTED PROPORTIONAL TO S''/S (SAME REFERENCE) */
/* FIRST DERIVATIVE TERMS - TO BE USED TO MULTIPLY Q2 AND Q3 TERMS IN ENGEB */
/* MHP 4/25 FIXED TYPOS AND TRAPPED OUT POTENTIAL DIVIDE BY ZERO ERRORS */
	if (newcross_1.s0_1_1__ > 0.) {
	    cross_1.qs0e[0] = newcross_1.s0p_1_1__ / newcross_1.s0_1_1__ / (
		    qs0e_1_1_a98__ / s0_1_1_a98__);
	} else {
	    cross_1.qs0e[0] = 0.;
	}
	if (newcross_1.s0_3_3__ > 0.) {
	    cross_1.qs0e[1] = newcross_1.s0p_3_3__ / newcross_1.s0_3_3__ / (
		    qs0e_3_3_a98__ / s0_1_1_a98__);
	} else {
	    cross_1.qs0e[1] = 0.;
	}
	if (newcross_1.s0_3_4__ > 0.) {
	    cross_1.qs0e[2] = newcross_1.s0p_3_4__ / newcross_1.s0_3_4__ / (
		    qs0e_3_4_a98__ / s0_1_1_a98__);
	} else {
	    cross_1.qs0e[2] = 0.;
	}
	if (newcross_1.s0_1_12__ > 0.) {
	    cross_1.qs0e[3] = newcross_1.s0p_1_12__ / newcross_1.s0_1_12__ / (
		    qs0e_1_12_a98__ / s0_1_1_a98__);
	} else {
	    cross_1.qs0e[3] = 0.;
	}
	if (newcross_1.s0_1_13__ > 0.) {
	    cross_1.qs0e[4] = newcross_1.s0p_1_13__ / newcross_1.s0_1_13__ / (
		    qs0e_1_13_a98__ / s0_1_1_a98__);
	} else {
	    cross_1.qs0e[4] = 0.;
	}
	if (newcross_1.s0_1_14__ > 0.) {
	    cross_1.qs0e[5] = newcross_1.s0p_1_14__ / newcross_1.s0_1_14__ / (
		    qs0e_1_14_a98__ / s0_1_1_a98__);
	} else {
	    cross_1.qs0e[5] = 0.;
	}
	if (newcross_1.s0_1_16__ > 0.) {
	    cross_1.qs0e[6] = newcross_1.s0p_1_16__ / newcross_1.s0_1_16__ / (
		    qs0e_1_16_a98__ / s0_1_1_a98__);
	} else {
	    cross_1.qs0e[6] = 0.;
	}
/*         QS0E(8)=(S0P_1_BE7P/S0_1_BE7P)/(QS0E_1_BE7P_A98/S0_1_BE7P__A98) */
	if (newcross_1.s0_1_be7p__ > 0.) {
	    cross_1.qs0e[7] = newcross_1.s0p_1_be7p__ / 
		    newcross_1.s0_1_be7p__ / (qs0e_1_be7p_a98__ / 
		    s0_1_be7p_a98__);
	} else {
	    cross_1.qs0e[7] = 0.;
	}
/* SECOND DERIVATIVE TERMS - TO BE USED TO MULTIPLY Q4 AND Q5 TERMS IN ENGEB */
/*         QQS0EE(1) = (S0PP_1_1/S0_1_1)/(QQS0EE_1_1_A98/S0_1_1_A98) ZEROED OUT IN 2003 VERSION */
/*         QQS0EE(2) = (S0PP_3_3/S0_3_3)/(QQS0EE_3_3_A98/S0_3_3_A98) ZEROED OUT IN 2003 VERSION */
/*         QQS0EE(3) = (S0PP_3_4/S0_3_4)/(QQS0EE_3_4_A98/S0_3_4_A98) ZEROED OUT IN 2003 VERSION */
	if (newcross_1.s0_1_12__ > 0.) {
	    cross_1.qqs0ee[3] = newcross_1.s0pp_1_12__ / newcross_1.s0_1_12__ 
		    / (qqs0ee_1_12_a98__ / s0_1_1_a98__);
	} else {
	    cross_1.qqs0ee[3] = 0.;
	}
	if (newcross_1.s0_1_13__ > 0.) {
	    cross_1.qqs0ee[4] = newcross_1.s0pp_1_13__ / newcross_1.s0_1_13__ 
		    / (qqs0ee_1_13_a98__ / s0_1_1_a98__);
	} else {
	    cross_1.qqs0ee[4] = 0.;
	}
/*         QQS0EE(6) = (S0PP_1_14/S0_1_14)/(QQS0EE_1_14_A98/S0_1_14_A98) ZEROED OUT IN 2003 VERSION */
	if (newcross_1.s0_1_16__ > 0.) {
	    cross_1.qqs0ee[6] = newcross_1.s0pp_1_16__ / newcross_1.s0_1_16__ 
		    / (qqs0ee_1_16_a98__ / s0_1_1_a98__);
	} else {
	    cross_1.qqs0ee[6] = 0.;
	}
	if (newcross_1.s0_1_be7p__ > 0.) {
	    cross_1.qqs0ee[7] = newcross_1.s0pp_1_be7p__ / 
		    newcross_1.s0_1_be7p__ / (qqs0ee_1_be7p_a98__ / 
		    s0_1_be7p_a98__);
	} else {
	    cross_1.qqs0ee[7] = 0.;
	}
    }
/* OPTION TO OVERWRITE SPATIAL AND TEMPORAL TOLERANCES WITH MORE INTUITIVE VARIABLE NAMES. */
/* NOTE: THIS OVERWRITES THE HPTTOL AND ATIME VECTORS. */
    if (newparam_1.lnewvars) {
/* MINIMUM LOG MASS SPACING BETWEEN SHELLS */
	ctol_1.hpttol[0] = newparam_1.tol_dm_min__;
/* MAXIMUM LOG MASS SPACING BETWEEN SHELLS */
	ctol_1.hpttol[1] = newparam_1.tol_dm_max__;
/* MAXIMUM L/LSURF SPACING BETWEEN SHELLS */
	ctol_1.hpttol[8] = newparam_1.tol_dl_max__;
/* MAXIMUM LOG P SPACING BETWEEN SHELLS, RADIATIVE INTERIOR */
	ctol_1.hpttol[10] = newparam_1.tol_dp_core_max__;
/* MAXIMUM LOG P SPACING BETWEEN SHELLS, CONVECTIVE ENVELOPE */
	ctol_1.hpttol[7] = newparam_1.tol_dp_env_max__;
/* MAXIMUM LOG P SPACING BETWEEN SHELLS, NEAR CZ BASE */
	ctol_1.hpttol[9] = newparam_1.tol_dp_czbase_max__;
/* WIDTH (IN LOG P) OF FINELY ZONED REGION NEAR THE CZ BASE */
	ctol_1.hpttol[6] = newparam_1.tol_czbase_fine_width__;
/* MAXIMUM X SPACING BETWEEN SHELLS (USUALLY DISABLED) */
	ctol_1.hpttol[4] = newparam_1.tol_dx_max__;
/* MAXIMUM Z SPACING BETWEEN SHELLS (USUALLY DISABLED) */
	ctol_1.hpttol[5] = newparam_1.tol_dz_max__;
/* X DIFFERENCE BETWEEN SHELLS REQUIRED TO FLAG (AVOID NUMERICAL DIFFUSION) */
	ctol_1.hpttol[2] = newparam_1.flag_dx__;
/* Z DIFFERENCE BETWEEN SHELLS REQUIRED TO FLAG (AVOID NUMERICAL DIFFUSION) */
	ctol_1.hpttol[3] = newparam_1.flag_dz__;
/* MAXIMUM LOG OMEGA SPACING BETWEEN SHELLS (ROTATING MODELS ONLY) */
	ctol_1.hpttol[11] = newparam_1.flag_dw__;
/* MINIMUM CENTRAL ABUNDANCE TO USE CORE BURNING DT CRITERION */
	ctlim_1.atime[0] = newparam_1.time_core_min__;
/* MAX PERMITTED ABSOLUTE DELTA X BURNED IN CORE IN TIMESTEP */
	ctlim_1.atime[1] = newparam_1.time_dx_core_tot__;
/* MAX PERMITTED FRACTION OF X BURNED IN CORE IN TIMESTEP */
	ctlim_1.atime[2] = newparam_1.time_dx_core_frac__;
/* MAX PERMITTED SOLAR MASSES OF X BURNED IN TIMESTEP */
	ctlim_1.atime[5] = newparam_1.time_dx_total__;
/* MAX PERMITTED FRACTION OF X BURNED IN SHELL IN TIMESTEP */
	ctlim_1.atime[6] = newparam_1.time_dx_shell__;
/* MAX PERMITTED ABSOLUTE DELTA Y BURNED IN CORE IN TIMESTEP */
	ctlim_1.atime[3] = newparam_1.time_dy_core_tot__;
/* MAX PERMITTED FRACTION OF Y BURNED IN CORE IN TIMESTEP */
	ctlim_1.atime[4] = newparam_1.time_dy_core_frac__;
/* MAX PERMITTED FRACTION OF Y BURNED IN SHELL IN TIMESTEP */
	ctlim_1.atime[11] = newparam_1.time_dy_shell__;
/* MAX PERMITTED SOLAR MASSES OF Y BURNED IN SHELL IN TIMESTEP */
	ctlim_1.atime[13] = newparam_1.time_dy_total__;
/* MAX PERMITTED CHANGES IN T, P, R, L AT ANY GIVEN SHELL IN TIMESTEP */
	ctlim_1.atime[7] = newparam_1.time_dt__;
	ctlim_1.atime[8] = newparam_1.time_dp__;
	ctlim_1.atime[9] = newparam_1.time_dr__;
	ctlim_1.atime[10] = newparam_1.time_dl__;
/* MASTER FLAG THAT USES/DOES NOT USE ATIME(8)-(11) */
/* NOTE: THIS IS USED ONLY IN THE PRE-MS AND DISABLED FOR MS STARS AUTOMATICALLY. */
	ct3_1.lptime = newparam_1.lstruct_time__;
/* MAX PERMITTED CHANGE IN OMEGA PER GLOBAL TIMESTEP */
	ct2_1.dtwind = newparam_1.time_dw_global__;
/* THE CODE CAN MIX IN A SERIES OF SMALLER TIMESTEPS; THIS IS */
/* THE MAX PERMITTED CHANGE IN OMEGA IN A SMALL, ROTATIONAL MIXING STEP */
	difus_1.dtdif = newparam_1.time_dw_mix__;
/* THE TIMESTEP IS NOT PERMITTED TO CHANGE FROM ONE MODEL TO THE NEXT BY */
/* MORE THAN THIS SCALE FACTOR */
/*          ATIME(13) = TIME_MAX_DT_FAC */
	ctlim_1.atime[12] = newparam_1.time_max_dt_frac__;
    }
    return 0;
} /* remap_ */

