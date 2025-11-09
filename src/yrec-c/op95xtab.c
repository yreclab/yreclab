/* op95xtab.f -- translated by f2c (version 20061008).
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
    doublereal tgr[70], xxg[10], r0gr[19], zzg[13], cappa2[167580]	/* 
	    was [126][70][19] */;
    integer numxm[13], nz[13];
} llot95a_;

#define llot95a_1 llot95a_

struct {
    doublereal cappa[13300]	/* was [10][70][19] */, ztab;
} llot95_;

#define llot95_1 llot95_

struct {
    doublereal cappae[1330]	/* was [70][19] */, xtab;
} llot95e_;

#define llot95e_1 llot95e_



/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */
/*     OP95XTAB */
/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */
/* Subroutine */ int op95xtab_(doublereal *x)
{
    static doublereal a[4], b[4];
    static integer i__, j, k, i1, i2, i3, i4, idx;
    extern /* Subroutine */ int intrp2_(doublereal *, doublereal *, 
	    doublereal *);

/* MHP 7/98 COMPUTE OPACITY TABLE AT FIXED X FROM THE OP95 TABLE AT */
/* THE MODEL Z */
/* FULL SET OF TABLES: OPACITY AS A FUNCTION OF Z AND X, T, RHO/T6**3 */
/* TABLES ARE INCREMENTED IN SETS OF NZ*NX.  SO THE TABLES FOR THE */
/* THIRD METAL ABUNDANCE (3 X 10**-4)BEGIN AT TABLE 21 AND END AT TABLE 30. */
/* FOR THE HIGH VALUES OF Z, THE NUMBER OF X TABLES IS NOT THE SAME (I.E. */
/* X<0.9 FOR Z=0.1). */
/* FOR EACH COMPOSITION A FULL GRID IN (T,RHO/T6**3) IS RETAINED. */
/* GRID ENTRIES FOR TEMPERATURE, ABUNDANCE (X), AND RHO/T6**3 */
/* OPACITY AS A FUNCTION OF X, T, AND RHO/T6**3 */
/* AS ABOVE FOR DESIRED SURFACE VALUE OF X. */
    llot95e_1.xtab = *x;
/*  FIND 4 NEAREST TABLES IN X TO DESIRED VALUE. */
    if (*x <= .8) {
/* DON'T NEED TO WORRY ABOUT MISSING X TABLES AT HIGH Z. */
	for (i__ = 3; i__ <= 9; ++i__) {
	    if (llot95a_1.xxg[i__ - 1] >= *x) {
		idx = i__ - 2;
		goto L10;
	    }
	}
	idx = 7;
L10:
	for (i__ = 1; i__ <= 4; ++i__) {
	    a[i__ - 1] = llot95a_1.xxg[idx + i__ - 2];
	}
    } else if (llot95_1.ztab <= .04) {
/* HIGH X TABLES PRESENT AT LOW Z. */
	for (i__ = 3; i__ <= 9; ++i__) {
	    if (llot95a_1.xxg[i__ - 1] >= *x) {
		idx = i__ - 2;
		goto L20;
	    }
	}
	idx = 7;
L20:
	for (i__ = 1; i__ <= 4; ++i__) {
	    a[i__ - 1] = llot95a_1.xxg[idx + i__ - 2];
	}
    } else if (llot95_1.ztab >= .1) {
/* USE TABLES 6-9 */
	idx = 6;
	for (i__ = 1; i__ <= 4; ++i__) {
	    a[i__ - 1] = llot95a_1.xxg[idx + i__ - 2];
	}
    } else {
/* IF Z IS BETWEEN 0.04 AND 0.1, TABLES 1-8 AND 10 EXIST. */
/* SINCE WE HAVE ALREADY DETERMINED THAT X > 0.8, USE 6-8 AND 10. */
	idx = 11;
	a[0] = llot95a_1.xxg[5];
	a[1] = llot95a_1.xxg[6];
	a[2] = llot95a_1.xxg[7];
	a[3] = llot95a_1.xxg[9];
    }

/*  FIND INTERPOLATION FACTORS IN Z. */
    intrp2_(a, b, x);
/* INDICES FOR 4 DESIRED COMPOSITIONS. */
    if (idx < 10) {
	i1 = idx;
	i2 = idx + 1;
	i3 = idx + 2;
	i4 = idx + 3;
    } else {
	i1 = 6;
	i2 = 7;
	i3 = 8;
	i4 = 10;
    }
    for (j = 1; j <= 70; ++j) {
	for (k = 1; k <= 19; ++k) {
	    llot95e_1.cappae[j + k * 70 - 71] = b[0] * llot95_1.cappa[i1 + (j 
		    + k * 70) * 10 - 711] + b[1] * llot95_1.cappa[i2 + (j + k 
		    * 70) * 10 - 711] + b[2] * llot95_1.cappa[i3 + (j + k * 
		    70) * 10 - 711] + b[3] * llot95_1.cappa[i4 + (j + k * 70) 
		    * 10 - 711];
	}
    }
    return 0;
} /* op95xtab_ */

