/* alxztab.f -- translated by f2c (version 20061008).
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
    doublereal tgr[23], xxg[7], r0gr[17], zzg[15];
} galot_;

#define galot_1 galot_

struct {
    doublereal capalex[3128]	/* was [8][23][17] */, xe, ze;
    integer ix, it, id;
} alot_;

#define alot_1 alot_

struct {
    doublereal captalex[41055]	/* was [105][23][17] */;
} alotall_;

#define alotall_1 alotall_

/*  SUBROUTINE FOR GENERATING FIXED Z TABLE FROM THE FULL SET OF */
/*  ALEXANDER OPACITY TABLES. */
/* Subroutine */ int alxztab_(doublereal *z__)
{
    static integer i__, jj, kk;
    static doublereal fz[4], qr[4];
    static integer ii1, ii2, ii3, ii4, idz;
    extern /* Subroutine */ int intrp2_(doublereal *, doublereal *, 
	    doublereal *);

/*     ALEX LOW T OPACITY */
/*     LOCAL ARRAYS */
/* LOCATE FOUR NEAREST TABLES IN Z */
    for (i__ = 3; i__ <= 14; ++i__) {
	if (*z__ < galot_1.zzg[i__ - 1]) {
	    idz = i__ - 2;
	    goto L10;
	}
    }
    idz = 12;
L10:
    for (i__ = 1; i__ <= 4; ++i__) {
	qr[i__ - 1] = galot_1.zzg[idz + i__ - 2];
    }
/* GET INTERPOLATION FACTORS FOR Z. */
    intrp2_(qr, fz, z__);
/* INTERPOLATE IN Z AT FIXED X. */
    for (i__ = 1; i__ <= 7; ++i__) {
/*  INDICES FOR TABLES: SETS OF 7 X AT FIXED Z, STARTING FROM */
/*  Z= 0 AND GOING TO Z = 0.1. */
	ii1 = i__ + (idz - 1) * 7;
	ii2 = ii1 + 7;
	ii3 = ii2 + 7;
	ii4 = ii3 + 7;
	for (jj = 1; jj <= 23; ++jj) {
	    for (kk = 1; kk <= 17; ++kk) {
		alot_1.capalex[i__ + (jj + kk * 23 << 3) - 193] = fz[0] * 
			alotall_1.captalex[ii1 + (jj + kk * 23) * 105 - 2521] 
			+ fz[1] * alotall_1.captalex[ii2 + (jj + kk * 23) * 
			105 - 2521] + fz[2] * alotall_1.captalex[ii3 + (jj + 
			kk * 23) * 105 - 2521] + fz[3] * alotall_1.captalex[
			ii4 + (jj + kk * 23) * 105 - 2521];
	    }
	}
    }
    alot_1.ze = *z__;
    return 0;
} /* alxztab_ */

