/* lirate88.f -- translated by f2c (version 20061008).
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
    doublereal cln, clni, c4pi, c4pil, c4pi3l, cc13, cc23, cpi;
} const1_;

#define const1_1 const1_

struct {
    doublereal rli6[5000], rli7[5000], rbe9[5000];
} newrat_;

#define newrat_1 newrat_

struct {
    doublereal hpo[5000], hto[5000], hro[5000], hlo[5000], hdo[5000], hcompp[
	    75000]	/* was [15][5000] */, hss[5000];
    logical lco[5000], lczo[5000];
    doublereal tefflo;
    integer mo;
} oldmod_;

#define oldmod_1 oldmod_

struct {
    doublereal rli60[5000], rli70[5000], rbe90[5000];
} oldrat_;

#define oldrat_1 oldrat_

struct {
    doublereal sli6, sli7, sbe91, sbe92, sbe93;
} burnscs_;

#define burnscs_1 burnscs_

/* Table of constant values */

static doublereal c_b4 = 1.5;
static doublereal c_b5 = .75;



/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */
/* LIRATE88 */
/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */
/* Subroutine */ int lirate88_(doublereal *hcomp, doublereal *hd, doublereal *
	ht, integer *m, integer *j)
{
    /* Initialized data */

    static doublereal tlim = 6.;

    /* System generated locals */
    integer i__1;
    doublereal d__1;

    /* Builtin functions */
    double exp(doublereal), pow_dd(doublereal *, doublereal *);

    /* Local variables */
    static integer i__, k;
    static doublereal t9, c56, fx, ex, t9a, t913, t923, t932, t943, t953, 
	    t934, fli6, fli7, fbe91, fbe92, fbe93, rhox, fsbe9;

/* G Somers 6/14, IMPORT LIGHT ELEMENT SCALE FACTOR BLOCK */
/* G Somers END */
    /* Parameter adjustments */
    --ht;
    --hd;
    hcomp -= 16;

    /* Function Body */
/* THIS ROUTINE COMPUTES THE BURNING RATES FOR LI6,LI7,BE9 AT THE */
/* BEGINNING AND END OF A TIMESTEP AND STORES THEM IN COMMON BLOCKS */
/* NEWRAT AND OLDRAT. */

/* BURNING RATES FROM CAUGHLIN AND FOWLER (1988). */

    i__1 = *m;
    for (i__ = 1; i__ <= i__1; ++i__) {
	if (ht[i__] < tlim && oldmod_1.hto[i__ - 1] < tlim) {
	    goto L110;
	}
	if (*j == 1) {
	    rhox = exp(const1_1.cln * hd[i__]) * hcomp[i__ * 15 + 1];
	    t9 = exp(const1_1.cln * (ht[i__] - 9.));
	} else {
	    rhox = exp(const1_1.cln * oldmod_1.hdo[i__ - 1]) * 
		    oldmod_1.hcompp[i__ * 15 - 15];
	    t9 = exp(const1_1.cln * (oldmod_1.hto[i__ - 1] - 9.));
	}
	t913 = pow_dd(&t9, &const1_1.cc13);
	t923 = t913 * t913;
	t943 = t923 * t923;
/* MHP 10/91 ADDED DEFINITION */
	t953 = t943 * t913;
	t932 = pow_dd(&t9, &c_b4);
	t934 = pow_dd(&t9, &c_b5);

/* LI6(P,HE3)ALPHA */

/*           FLI6=3.73D10/T923*EXP(-8.413/T913-(T9/5.50)**2)* */
/*    1      (1.+%TYPO%0.50*T913-0.061*T923-0.021*T9+0.006*T943+0.006*T953) */
/*    2      +1.33D10/T932*EXP(-17.763/T9)+1.29D9/T9*EXP(-21.820/T9) */
/* ***TYPO IN OLD RATE*** */
/* Computing 2nd power */
	d__1 = t9 / 5.5;
	fli6 = 3.73e10 / t923 * exp(-8.413 / t913 - d__1 * d__1) * (t913 * 
		.05 + 1. - t923 * .061 - t9 * .021 + t943 * .006 + t953 * 
		.005) + 1.33e10 / t932 * exp(-17.763 / t9) + 1.29e9 / t9 * 
		exp(-21.82 / t9);

/* LI7(P,ALFA)HE4 */

/*           FLI7=8.04D08/T923*EXP(-8.471/T913-(T9/30.068)**2)* */
/*    1      (1.+0.049*T913+0.230*T923+0.079*T9-0.027*T943-0.023*T953) */
/*    2      +1.54D06/T932*EXP(-4.479/T9)+1.07D10/T932*EXP(-30.443/T9) */
	t9a = t9 / (t9 * .759 + 1.);
	c56 = const1_1.cc23 * 1.25;
	fli7 = 1.096e9 / t923 * exp(-8.472 / t913) - pow_dd(&t9a, &c56) * 
		4.83e8 / t932 * exp(-8.472 / pow_dd(&t9a, &const1_1.cc13)) + 
		1.06e10 / t932 * exp(-30.442 / t9);

/* BE9(P,GAMMA)B10 */

/* Computing 2nd power */
	d__1 = t9 / .846;
	fbe91 = 1.33e7 / t923 * exp(-10.359 / t913 - d__1 * d__1) * (t913 * 
		.04 + 1. + t923 * 1.52 + t9 * .428 + t943 * 2.15 + t953 * 
		1.54) + 96400. / t932 * exp(-3.445 / t9) + 2.72e6 / t932 * 
		exp(-10.62 / t9);
/*    3      2.76D+6/T932*EXP(-10.62D0/T9) %OLD LAST LINE% */

/* BE9(P,D)2HE4 - UNCHANGED. */

/* Computing 2nd power */
	d__1 = t9 / .52;
	fx = 2.11e11 / t923 * exp(-10.359 / t913 - d__1 * d__1) * (t913 * .04 
		+ 1. + t923 * 1.09 + t9 * .307 + t943 * 3.21 + t953 * 2.3);
	ex = exp(-3.046 / t9) / t9;
	fbe92 = fx + ex * 5.79e8 + 8.5e8 / t934 * exp(-5.8 / t9);

/* BE9(P,ALPHA)LI6 */

	fbe93 = fx + ex * 4.51e8 + 6.7e8 / t934 * exp(-5.16 / t9);
/* G Somers 6/14, SCALE BY THE NEW CROSS SECTIONS */
	fli6 = burnscs_1.sli6 * fli6;
	fli7 = burnscs_1.sli7 * fli7;
	fbe91 = burnscs_1.sbe91 * fbe91;
	fbe92 = burnscs_1.sbe92 * fbe92;
	fbe93 = burnscs_1.sbe93 * fbe93;
/* G Somers END */
/* SUM RATES */
	fsbe9 = fbe91 + fbe92 + fbe93;
	if (*j == 1) {
	    newrat_1.rli6[i__ - 1] = fli6 * rhox;
	    newrat_1.rli7[i__ - 1] = fli7 * rhox;
	    newrat_1.rbe9[i__ - 1] = fsbe9 * rhox;
	} else {
	    oldrat_1.rli60[i__ - 1] = fli6 * rhox;
	    oldrat_1.rli70[i__ - 1] = fli7 * rhox;
	    oldrat_1.rbe90[i__ - 1] = fsbe9 * rhox;
	}
/* L100: */
    }
L110:
    i__1 = *m;
    for (k = i__; k <= i__1; ++k) {
	newrat_1.rli6[k - 1] = 0.;
	newrat_1.rli7[k - 1] = 0.;
	newrat_1.rbe9[k - 1] = 0.;
	oldrat_1.rli60[k - 1] = 0.;
	oldrat_1.rli70[k - 1] = 0.;
	oldrat_1.rbe90[k - 1] = 0.;
/* L120: */
    }
    return 0;
} /* lirate88_ */

