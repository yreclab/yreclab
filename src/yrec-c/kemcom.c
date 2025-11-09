/* kemcom.f -- translated by f2c (version 20061008).
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
    doublereal cmin, abstol, reltol;
    integer kemmax;
} burtol_;

#define burtol_1 burtol_

struct {
    doublereal atime[14], tcut[5], tscut, tenv0, tenv1, tenv, tgcut;
} ctlim_;

#define ctlim_1 ctlim_

struct {
    integer ilast, idebug, itrack, ishort, imilne, imodpt, istor, iowr;
} luout_;

#define luout_1 luout_

struct {
    doublereal hpo[5000], hto[5000], hro[5000], hlo[5000], hdo[5000], hcompp[
	    75000]	/* was [15][5000] */, hss[5000];
    logical lco[5000], lczo[5000];
    doublereal tefflo;
    integer mo;
} oldmod_;

#define oldmod_1 oldmod_

/* Table of constant values */

static integer c__8 = 8;
static integer c__7 = 7;
static integer c__1 = 1;

/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */
/* KEMCOM */
/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */
/* Subroutine */ int kemcom_(doublereal *ht, integer *ibegin, integer *iend, 
	doublereal *hr1, doublereal *hr2, doublereal *hr3, doublereal *hr4, 
	doublereal *hr5, doublereal *hr6, doublereal *hr7, doublereal *hr8, 
	doublereal *hr10, doublereal *hr11, doublereal *hr12, doublereal *hf1,
	 doublereal *hs2, doublereal *hcomp, doublereal *ddage)
{
    /* Format strings */
    static char fmt_1000[] = "(1x,39(\002>\002),40(\002<\002)/1x,\002ERROR I"
	    "N SUBROUTINE KEMCOM\002/1x,\002UNABLE TO SOLVE FOR NEW ABUNDANCE"
	    "S IN SHELL\002,i4/1x,\002RUN STOPPED AFTER 50 ATTEMPTS\002)";

    /* System generated locals */
    integer i__1;
    doublereal d__1, d__2;
    static doublereal equiv_0[56];

    /* Builtin functions */
    integer s_wsfe(cilist *), do_fio(integer *, char *, ftnlen), e_wsfe(void);
    /* Subroutine */ void s_stop(char *, ftnlen);

    /* Local variables */
#define a (equiv_0)
#define b (equiv_0 + 49)
    static integer i__, j;
    static doublereal w[7], z__, f3, f4, xb;
    static integer iu, j1j, j2j;
    static doublereal gr1, gr9, gr2, gr3, gr4, gr5, gr6, gr7, gr8, x2r, x3r, 
	    y3r, x4r, x6r, gr10, gr13, gr11, gr12, xo18, xpr, ypr, bigb, bigd,
	     delt;
    static integer icon;
    static doublereal xsum[11], delt3, delt4, dcmin, delt12, delt13, delt14, 
	    delt16, wtsum;
    extern /* Subroutine */ int simeqc_(doublereal *, integer *, integer *);

    /* Fortran I/O blocks */
    static cilist io___44 = { 0, 0, 0, fmt_1000, 0 };


/*      *HR9,HR10,HR11,HR12,HR13,HF1,HS2,HCOMP,DDAGE,ITLVL)  ! KC 2025-05-31 */
/*      *HR5(JSON),HR6(JSON),HR7(JSON),HR8(JSON),HR9(JSON),HR10(JSON), */
/*      *HR11(JSON),HR12(JSON),HR13(JSON),HF1(JSON),HCOMP(15,JSON),  ! KC 2025-05-31 */
/* KEMCOM USES THE REACTION RATES COMPUTED IN ENGEB TO IMPLICITLY SOLVE */
/* FOR THE ABUNDANCES OF H,HE3,HE4,C12,C13,N14,O16, AND O18 SIMULTANEUOSLY. */
/* DON VANDENBERGS NOTES EXPLAIN WHAT THE SR IS DOING. */

/* INPUT VARIABLES : */

/* DDAGE - MODEL TIME STEP IN YEARS. */
/* HCOMP - ARRAY CONTAINING RUN OF MASS FRACTIONS OF DIFFERENT SPECIES. */
/*  HCOMP(1,..)=H; 2=HE4; 3=Z; 4=HE3; 5=C12; 6=C13; 7=N14; 9=O16; 11=O18. */
/*  ELEMENTS 8(N15) AND 10(O17) NOT CURRENTLY USED;12-15 ARE LIGHT ELEMENTS */
/*  WHOSE BURNING IS TREATED ELSEWHERE. */
/* HCOMPP - THE ARRAY OF ABUNDANCES AT THE START OF THE TIMESTEP. */
/* HS2 - RUN OF MASS CONTAINED IN EACH SHELL. */
/* HT - RUN OF MODEL TEMPERATURE. */
/* IBEGIN, IEND - STARTING AND ENDING SHELLS; DIFFERENT FOR A CONVECTION ZONE. */
/* HR1-HR13,HF1 - REACTION RATES (EXCLUDING TERMS THAT DEPEND ONLY ON */
/*  THE COMPOSITION) PER GIGAYEAR PER AMU.  NEEDS TO BE MULTIPLIED BY THE */
/*  MASS FRACTIONS OF THE REACTANTS AND THE ATOMIC WEIGHT (IN AMU) OF THE */
/*  PRODUCT TO GET THE RATE OF CHANGE OF THE MASS FRACTION. */

/* NUMERICAL PARAMETERS IN COMMON BLOCK /BURTOL/: */
/* ABUNDANCES BELOW CMIN ARE ZEROED OUT. */
/* ABSTOL AND RELTOL ARE THE ABSOLUTE AND RELATIVE TOLERANCES FOR CONVERGENCE. */
/* KEMMAX IS THE MAXIMUM NUMBER OF ITERATIONS BEFORE THE PROGRAM WILL HALT. */

/* OUTPUT VARIABLES : THE NEW RUN OF ABUNDANCE HCOMP. */

    /* Parameter adjustments */
    hcomp -= 16;
    --hs2;
    --hf1;
    --hr12;
    --hr11;
    --hr10;
    --hr8;
    --hr7;
    --hr6;
    --hr5;
    --hr4;
    --hr3;
    --hr2;
    --hr1;
    --ht;

    /* Function Body */
    if (*ibegin != *iend) {
/* HOMOGENIZE CONVECTION ZONES. */
/* XSUM IS THE MASS-WEIGHTED AVERAGE ABUNDANCE FOR THE CZ. */
/* WTSUM IS THE TOTAL MASS OF THE CZ. */
/* INITIALIZE SUMS. */
	wtsum = 0.;
	for (j = 1; j <= 11; ++j) {
	    xsum[j - 1] = 0.;
/* L1: */
	}
	i__1 = *iend;
	for (i__ = *ibegin; i__ <= i__1; ++i__) {
	    wtsum += hs2[i__];
	    for (j = 1; j <= 11; ++j) {
		xsum[j - 1] += oldmod_1.hcompp[j + i__ * 15 - 16] * hs2[i__];
/* L3: */
	    }
/* L5: */
	}
	for (j = 1; j <= 11; ++j) {
	    xsum[j - 1] /= wtsum;
/* L7: */
	}
    } else {
	for (j = 1; j <= 11; ++j) {
	    xsum[j - 1] = oldmod_1.hcompp[j + *ibegin * 15 - 16];
/* L9: */
	}
    }
/* SKIP BURNING CALCULATIONS IF STARTING SHELL BELOW T CUTOFF FOR REACTIONS. */
    if (ht[*ibegin] < ctlim_1.tcut[0]) {
	i__1 = *iend;
	for (i__ = *ibegin; i__ <= i__1; ++i__) {
	    for (j = 1; j <= 11; ++j) {
		hcomp[j + i__ * 15] = xsum[j - 1];
/* L11: */
	    }
/* L13: */
	}
	goto L200;
    }

/* SET UP NUMERICAL PARAMETERS. */

/* TIMESTEP IN GIGAYEARS. THE OTHER DELTS ARE THIS TIMESTEP MULTIPLIED */
/*  BY THE ATOMIC MASS OF THE DIFFERENT SPECIES (IN AMU). */
    delt = *ddage * 1e-9;
    delt3 = delt * 3.;
    delt4 = delt * 4.;
    delt12 = delt * 12.;
    delt13 = delt * 13.;
    delt14 = delt * 14.;
    delt16 = delt * 16.;
    dcmin = burtol_1.cmin;
/* COUNTER FOR THE NUMBER OF ITERATIONS. */
    icon = 0;

/* NUCLEAR REACTION RATES. */

/* THESE REACTIONS ARE NO LONGER INCLUDED AND ARE ZEROED OUT. */
    gr9 = 0.;
    gr13 = 0.;
    if (*ibegin == *iend) {
/* PP */
	gr1 = hr1[*ibegin];
/* HE3,HE3 */
	gr2 = hr2[*ibegin];
/* HE3,HE4 */
	gr3 = hr3[*ibegin];
/* C12,P */
	gr4 = hr4[*ibegin];
/* C13,P */
	gr5 = hr5[*ibegin];
/* N14,P + N15,P */
	gr6 = hr6[*ibegin];
/* O16,P + O17,P. */
	gr7 = hr7[*ibegin];
/* C13,ALPHA */
	gr8 = hr8[*ibegin];
/* O16,ALPHA (NOT USED) */
/*        GR9 = HR9(IBEGIN) */
/* C12,ALPHA */
	gr10 = hr10[*ibegin];
/* N14,ALPHA */
	gr11 = hr11[*ibegin];
/* TRIPLE ALPHA */
	gr12 = hr12[*ibegin];
/* C12,C12 (NOT USED) */
/*        GR13 = HR13(IBEGIN) */
/* BRANCHING RATIO FOR N15,P : */
/* F3 = FRACTION GOING TO C12+ALPHA */
/* F4 = FRACTION GOING TO O16 */
	f3 = hf1[*ibegin];
	f4 = 1. - f3;
    } else {
/* USE THE MASS-WEIGHTED AVERAGE RATES FOR THE CZ */
	gr1 = 0.;
	gr2 = 0.;
	gr3 = 0.;
	gr4 = 0.;
	gr5 = 0.;
	gr6 = 0.;
	gr7 = 0.;
	gr8 = 0.;
	gr10 = 0.;
	gr11 = 0.;
	gr12 = 0.;
	f3 = 0.;
	i__1 = *iend;
	for (i__ = *ibegin; i__ <= i__1; ++i__) {
	    gr1 += hs2[i__] * hr1[i__];
	    gr2 += hs2[i__] * hr2[i__];
	    gr3 += hs2[i__] * hr3[i__];
	    gr4 += hs2[i__] * hr4[i__];
	    gr5 += hs2[i__] * hr5[i__];
	    gr6 += hs2[i__] * hr6[i__];
	    gr7 += hs2[i__] * hr7[i__];
	    gr8 += hs2[i__] * hr8[i__];
	    gr10 += hs2[i__] * hr10[i__];
	    gr11 += hs2[i__] * hr11[i__];
	    gr12 += hs2[i__] * hr12[i__];
	    f3 += hs2[i__] * hf1[i__];
/* L15: */
	}
	gr1 /= wtsum;
	gr2 /= wtsum;
	gr3 /= wtsum;
	gr4 /= wtsum;
	gr5 /= wtsum;
	gr6 /= wtsum;
	gr7 /= wtsum;
	gr8 /= wtsum;
	gr10 /= wtsum;
	gr11 /= wtsum;
	gr12 /= wtsum;
	f3 /= wtsum;
	f4 = 1. - f3;
    }

/* INITIAL ABUNDANCES OF SPECIES. */

    xpr = xsum[0];
    y3r = xsum[3];
    ypr = xsum[1];
    x2r = xsum[4];
    x3r = xsum[5];
    x4r = xsum[6];
    x6r = xsum[8];
/* STARTING GUESS FOR FINAL ABUNDANCES OF SPECIES : */
/* FOR CALLS IN CRRECT (ITLVL>1) USE THE PREVIOUS RESULT. */
/* OTHERWISE USE THE FINAL ABUNDANCES FOUND FOR THE PREVIOUS SHELL */
/* UNLESS I = 1. */
    if (*ibegin != 1) {
	w[0] = hcomp[(*ibegin - 1) * 15 + 1];
	w[1] = hcomp[(*ibegin - 1) * 15 + 4];
	w[2] = hcomp[(*ibegin - 1) * 15 + 2];
	w[3] = hcomp[(*ibegin - 1) * 15 + 5];
	w[4] = hcomp[(*ibegin - 1) * 15 + 6];
	w[5] = hcomp[(*ibegin - 1) * 15 + 7];
	w[6] = hcomp[(*ibegin - 1) * 15 + 9];
    } else {
	w[0] = hcomp[*ibegin * 15 + 1];
	w[1] = hcomp[*ibegin * 15 + 4];
	w[2] = hcomp[*ibegin * 15 + 2];
	w[3] = hcomp[*ibegin * 15 + 5];
	w[4] = hcomp[*ibegin * 15 + 6];
	w[5] = hcomp[*ibegin * 15 + 7];
	w[6] = hcomp[*ibegin * 15 + 9];
    }

/* ITERATION FOR NEW ABUNDANCES. */

L10:
/* FUNCTIONS TO BE MINIMIZED. THESE ARE OF THE FORM */
/* A(#)=ABUNDANCE(END STEP)-ABUNDANCE (START STEP)-TIMESTEP*(D(SPECIES)/DT) */
/* BECAUSE THE BURNING RATES D(SPECIES)/DT USE THE ABUNDANCES AT THE */
/* END OF THE TIMESTEP W(1)-W(7), THIS IS AN IMPLICIT SCHEME. */
/* EQUATION FOR H (X) */
/* Computing 2nd power */
    d__1 = w[0];
/* Computing 2nd power */
    d__2 = w[1];
    a[49] = w[0] - xpr - delt * (gr1 * -3. * (d__1 * d__1) + gr2 * 2. * (d__2 
	    * d__2) - gr3 * w[1] * w[2] - gr4 * w[0] * w[3] - gr5 * w[0] * w[
	    4] - w[0] * 2. * (gr6 * w[5] + gr7 * w[6]));
/* HE3 */
/* Computing 2nd power */
    d__1 = w[0];
/* Computing 2nd power */
    d__2 = w[1];
    a[50] = w[1] - y3r - delt3 * (gr1 * (d__1 * d__1) - gr2 * 2. * (d__2 * 
	    d__2) - gr3 * w[1] * w[2]);
/* HE4 (Y) */
/* Computing 2nd power */
    d__1 = w[1];
/* Computing 3rd power */
    d__2 = w[2];
    a[51] = w[2] - ypr - delt4 * (gr2 * (d__1 * d__1) + gr3 * w[1] * w[2] + 
	    f3 * gr6 * w[5] * w[0] + gr7 * w[0] * w[6] - gr10 * w[2] * w[3] - 
	    gr8 * w[2] * w[4] - gr11 * w[2] * w[5] - gr12 * 3. * (d__2 * (
	    d__2 * d__2)));
/* C12 */
/* Computing 3rd power */
    d__1 = w[2];
    a[52] = w[3] - x2r - delt12 * (gr12 * (d__1 * (d__1 * d__1)) - gr4 * w[0] 
	    * w[3] - gr10 * w[2] * w[3] + f3 * gr6 * w[0] * w[5]);
/* C13 */
    a[53] = w[4] - x3r - delt13 * (gr4 * w[0] * w[3] - gr5 * w[0] * w[4] - 
	    gr8 * w[2] * w[4]);
/* N14 */
    a[54] = w[5] - x4r - delt14 * (gr5 * w[0] * w[4] + gr7 * w[0] * w[6] - 
	    gr6 * w[0] * w[5] - gr11 * w[2] * w[5]);
/* O16*W(4) */
    a[55] = w[6] - x6r - delt16 * (f4 * gr6 * w[0] * w[5] + gr10 * w[2] * w[3]
	     - gr7 * w[0] * w[6] + gr8 * w[2] * w[4]);
/* NOTE THAT THE O18 ABUNDANCE IS COMPUTED EXPLICITLY AT THE END OF THE */
/* SUBROUTINE. */
/* THE REMAINING VALUES OF A CORRESPOND TO THE DERIVATIVES OF THE ABOVE 7 */
/* FUNCTIONS WITH RESPECT TO THE 7 SPECIES. */
/* D(RATES)/DX */
    a[0] = delt * (gr1 * 6. * w[0] + gr4 * w[3] + gr5 * w[4] + (gr6 * w[5] + 
	    gr7 * w[6]) * 2.) + 1.;
    a[1] = delt3 * -2. * gr1 * w[0];
    a[2] = -delt4 * (f3 * gr6 * w[5] + gr7 * w[6]);
    a[3] = -delt12 * (f3 * gr6 * w[5] - gr4 * w[3]);
    a[4] = -delt13 * (gr4 * w[3] - gr5 * w[4]);
    a[5] = -delt14 * (gr5 * w[4] + gr7 * w[6] - gr6 * w[5]);
    a[6] = -delt16 * (f4 * gr6 * w[5] - gr7 * w[6]);
/* D(RATES)/DHE3 */
    a[7] = -delt * (gr2 * 4. * w[1] - gr3 * w[2]);
    a[8] = delt3 * (gr2 * 4. * w[1] + gr3 * w[2]) + 1.;
    a[9] = -delt4 * (gr2 * 2. * w[1] + gr3 * w[2]);
    a[10] = 0.;
    a[11] = 0.;
    a[12] = 0.;
    a[13] = 0.;
/* D(RATES)/DHE4 */
    a[14] = delt * gr3 * w[1];
    a[15] = delt3 * gr3 * w[1];
/* Computing 2nd power */
    d__1 = w[2];
    a[16] = 1. - delt4 * (gr3 * w[1] - gr10 * w[3] - gr8 * w[4] - gr11 * w[5] 
	    - gr12 * 9. * (d__1 * d__1));
/* Computing 2nd power */
    d__1 = w[2];
    a[17] = -delt12 * (gr12 * 3. * (d__1 * d__1) - gr10 * w[3]);
    a[18] = delt13 * gr8 * w[4];
    a[19] = delt14 * gr11 * w[5];
    a[20] = -delt16 * (gr10 * w[3] + gr8 * w[4]);
/* D(RATES)/DC12 */
    a[21] = delt * gr4 * w[0];
    a[22] = 0.;
    a[23] = delt4 * gr10 * w[2];
    a[24] = delt12 * (gr4 * w[0] + gr10 * w[2]) + 1.;
    a[25] = -delt13 * gr4 * w[0];
    a[26] = 0.;
    a[27] = -delt16 * gr10 * w[2];
/* D(RATES)/DC13 */
    a[28] = delt * gr5 * w[0];
    a[29] = 0.;
    a[30] = delt4 * gr8 * w[2];
    a[31] = 0.;
    a[32] = delt13 * (gr5 * w[0] + gr8 * w[2]) + 1.;
    a[33] = -delt14 * gr5 * w[0];
    a[34] = -delt16 * gr8 * w[2];
/* D(RATES)/DN14 */
    a[35] = delt * 2. * gr6 * w[0];
    a[36] = 0.;
    a[37] = -delt4 * (f3 * gr6 * w[0] - gr11 * w[2]);
    a[38] = -delt12 * f3 * gr6 * w[0];
    a[39] = 0.;
    a[40] = delt14 * (gr6 * w[0] + gr11 * w[2]) + 1.;
    a[41] = -f4 * delt16 * gr6 * w[0];
/* D(RATES)/DO16 */
    a[42] = delt * 2. * gr7 * w[0];
    a[43] = 0.;
    a[44] = -delt4 * gr7 * w[0];
    a[45] = 0.;
    a[46] = 0.;
    a[47] = -delt14 * gr7 * w[0];
    a[48] = delt16 * gr7 * w[0] + 1.;
/* REDUCE THE 7X8 SYSTEM TO FIND THE CORRECTIONS TO THE RELATIVE */
/* ABUNDANCES. */
    j1j = 0;
    j2j = 1;
    for (i__ = 1; i__ <= 49; ++i__) {
	if (i__ == j2j) {
	    j2j += 8;
	} else if ((d__1 = a[i__ - 1], abs(d__1)) < 1e-8) {
	    a[i__ - 1] = 0.;
	} else {
	    j1j = 1;
	}
/* L20: */
    }
    if (j1j != 0) {
	simeqc_(a, &c__8, &c__7);
    }
/* CHECK TO SEE IF THE SYSTEM HAS CONVERGED WITHIN THE DESIRED TOLERANCES. */
    bigb = 0.;
    bigd = 0.;
    for (i__ = 1; i__ <= 7; ++i__) {
	w[i__ - 1] -= b[i__ - 1];
	if ((d__1 = b[i__ - 1], abs(d__1)) >= bigd) {
	    bigd = (d__2 = b[i__ - 1], abs(d__2));
	}
	if (w[i__ - 1] < dcmin) {
	    w[i__ - 1] = 0.;
	} else {
	    xb = (d__1 = b[i__ - 1] / w[i__ - 1], abs(d__1));
	    if (xb >= bigb) {
		bigb = xb;
	    }
	}
/* L30: */
    }
    if (bigd >= burtol_1.abstol || bigb >= burtol_1.reltol) {
/* SYSTEM NOT CONVERGED - SEE IF MAXIMUM NUMBER OF ITERATIONS EXCEEDED. */
	++icon;
	if (icon >= burtol_1.kemmax) {
/* MHP 10/02 IU not defined */
/*            WRITE (ISHORT,1000) IU */
	    io___44.ciunit = luout_1.ishort;
	    s_wsfe(&io___44);
	    do_fio(&c__1, (char *)&(*ibegin), (ftnlen)sizeof(integer));
	    e_wsfe();
	    s_stop("", (ftnlen)0);
	} else {
	    goto L10;
	}
    }
/*  SYSTEM HAS CONVERGED. */
/*  UPDATE COMPOSITION MATRIX. */
/*  UPDATE O18. */
    xo18 = xsum[10] + delt * 18. * gr11 * w[2] * w[5];
/*  CHANGE METAL ABUNDANCE IF X<5.0D-7. */
    if (oldmod_1.hcompp[*iend * 15 - 15] < 5e-7) {
	z__ = 1. - w[0] - w[1] - w[2];
    } else {
	z__ = xsum[2];
    }
    i__1 = *iend;
    for (iu = *ibegin; iu <= i__1; ++iu) {
	hcomp[iu * 15 + 1] = w[0];
	hcomp[iu * 15 + 4] = w[1];
	hcomp[iu * 15 + 2] = w[2];
	hcomp[iu * 15 + 5] = w[3];
	hcomp[iu * 15 + 6] = w[4];
	hcomp[iu * 15 + 7] = w[5];
	hcomp[iu * 15 + 9] = w[6];
	hcomp[iu * 15 + 3] = z__;
	hcomp[iu * 15 + 11] = xo18;
/* L40: */
    }
L200:
    return 0;
} /* kemcom_ */

#undef b
#undef a


