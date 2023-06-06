/* op954d.f -- translated by f2c (version 20100827).
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
    integer jz, jx[16]	/* was [4][4] */, jt, jd[4];
} op95indx_;

#define op95indx_1 op95indx_

struct {
    doublereal bz[4], bx[16]	/* was [4][4] */, bt[4], btt[4], bd[16]	/* 
	    was [4][4] */, bdd[16]	/* was [4][4] */;
} op95fact_;

#define op95fact_1 op95fact_

struct {
    doublereal rl, rll, rlh[4];
    logical lextl, lexth, lexh[4];
} op95ext_;

#define op95ext_1 op95ext_

/* Table of constant values */

static doublereal c_b2 = 10.;



/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */
/*     OP954D */
/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */
/* Subroutine */ int op954d_(doublereal *o, doublereal *ol, doublereal *qod, 
	doublereal *qot)
{
    /* Builtin functions */
    double pow_dd(doublereal *, doublereal *);

    /* Local variables */
    static doublereal c__[4];
    static integer i__, j, k;
    static doublereal cc[4];
    static integer id;
    static doublereal qc[4], cz[4];
    static integer it, iz;
    static doublereal ccd[4], cct[4], czd[4], czt[4];
    static integer ixz;
    static doublereal deltar;

/* MHP 7/98 GET OPAL95 OPACITY FROM FULL SET OF OPACITY TABLES. */
/* FULL SET OF TABLES: OPACITY AS A FUNCTION OF Z AND X, T, RHO/T6**3 */
/* TABLES ARE INCREMENTED IN SETS OF NZ*NX.  SO THE TABLES FOR THE */
/* THIRD METAL ABUNDANCE (3 X 10**-4)BEGIN AT TABLE 21 AND END AT TABLE 30. */
/* FOR THE HIGH VALUES OF Z, THE NUMBER OF X TABLES IS NOT THE SAME (I.E. */
/* X<0.9 FOR Z=0.1). */
/* FOR EACH COMPOSITION A FULL GRID IN (T,RHO/T6**3) IS RETAINED. */
/* INDICES FOR INTERPOLATION IN Z,X,T, AND R */
/* INTERPOLATION FACTORS FOR Z,X,T, AND R, AS WELL AS DERIVATIVE */
/* FACTORS FOR T AND RHO. */
/* DATA FOR LINEAR EXTRAPOLATION WHEN OUTSIDE TABLE IN RHO */
/* FIND OPACITY AT EACH OF THE 4 NEARBY VALUES OF Z */
    for (k = 1; k <= 4; ++k) {
	iz = llot95a_1.nz[op95indx_1.jz + k - 2];
/* FIND OPACITY AT EACH OF THE 4 NEARBY VALUES OF X */
	for (j = 1; j <= 4; ++j) {
	    ixz = op95indx_1.jx[k + (j << 2) - 5] + iz;
/* FOR EACH X, GET CAPPA FOR 4 VALUES OF T */
	    for (i__ = 1; i__ <= 4; ++i__) {
		it = op95indx_1.jt + i__ - 1;
/* FOR EACH T, GET CAPPA FOR 4 VALUES OF R */
		id = op95indx_1.jd[i__ - 1];
/* LOG CAPPA AT DESIRED RHO FOR EACH OF THE 4 DESIRED T. */
		c__[i__ - 1] = op95fact_1.bd[i__ - 1] * llot95a_1.cappa2[ixz 
			+ (it + id * 70) * 126 - 8947] + op95fact_1.bd[i__ + 
			3] * llot95a_1.cappa2[ixz + (it + (id + 1) * 70) * 
			126 - 8947] + op95fact_1.bd[i__ + 7] * 
			llot95a_1.cappa2[ixz + (it + (id + 2) * 70) * 126 - 
			8947] + op95fact_1.bd[i__ + 11] * llot95a_1.cappa2[
			ixz + (it + (id + 3) * 70) * 126 - 8947];
/* D LOG CAPPA/D LOG R FOR EACH OF THE 4 DESIRED T. */
		qc[i__ - 1] = op95fact_1.bdd[i__ - 1] * llot95a_1.cappa2[ixz 
			+ (it + id * 70) * 126 - 8947] + op95fact_1.bdd[i__ + 
			3] * llot95a_1.cappa2[ixz + (it + (id + 1) * 70) * 
			126 - 8947] + op95fact_1.bdd[i__ + 7] * 
			llot95a_1.cappa2[ixz + (it + (id + 2) * 70) * 126 - 
			8947] + op95fact_1.bdd[i__ + 11] * llot95a_1.cappa2[
			ixz + (it + (id + 3) * 70) * 126 - 8947];
	    }
/* CHECK ON WHETHER RHO IS OUTSIDE OF THE TABLE AND NEEDS EXTRAPOLATION */
	    if (op95ext_1.lextl) {
/* FACTOR IN R */
		deltar = op95ext_1.rl - op95ext_1.rll;
/* CORRECT CAPPA BY USING THE DERIVATIVE AT THE BOUNDARY. */
		for (i__ = 1; i__ <= 4; ++i__) {
		    c__[i__ - 1] += deltar * qc[i__ - 1];
		}
	    } else if (op95ext_1.lexth) {
		for (i__ = 1; i__ <= 4; ++i__) {
		    if (op95ext_1.lexh[i__ - 1]) {
			deltar = op95ext_1.rl - op95ext_1.rlh[i__ - 1];
			c__[i__ - 1] += deltar * qc[i__ - 1];
		    }
		}
	    }
/* INTERPOLATE FOR LOG CAPPA IN T. */
	    cc[j - 1] = op95fact_1.bt[0] * c__[0] + op95fact_1.bt[1] * c__[1] 
		    + op95fact_1.bt[2] * c__[2] + op95fact_1.bt[3] * c__[3];
/* D LOG CAPPA/D LOG T */
	    cct[j - 1] = op95fact_1.btt[0] * c__[0] + op95fact_1.btt[1] * c__[
		    1] + op95fact_1.btt[2] * c__[2] + op95fact_1.btt[3] * c__[
		    3];
/* D LOG CAPPA/D LOG R */
	    ccd[j - 1] = op95fact_1.bt[0] * qc[0] + op95fact_1.bt[1] * qc[1] 
		    + op95fact_1.bt[2] * qc[2] + op95fact_1.bt[3] * qc[3];
	}
/* INTERPOLATE FOR LOG CAPPA IN X. */
	cz[k - 1] = op95fact_1.bx[k - 1] * cc[0] + op95fact_1.bx[k + 3] * cc[
		1] + op95fact_1.bx[k + 7] * cc[2] + op95fact_1.bx[k + 11] * 
		cc[3];
/* INTERPOLATE FOR QOT IN X. */
	czt[k - 1] = op95fact_1.bx[k - 1] * cct[0] + op95fact_1.bx[k + 3] * 
		cct[1] + op95fact_1.bx[k + 7] * cct[2] + op95fact_1.bx[k + 11]
		 * cct[3];
/* INTERPOLATE FOR QOD IN X. */
	czd[k - 1] = op95fact_1.bx[k - 1] * ccd[0] + op95fact_1.bx[k + 3] * 
		ccd[1] + op95fact_1.bx[k + 7] * ccd[2] + op95fact_1.bx[k + 11]
		 * ccd[3];
    }
/* INTERPOLATE FOR LOG CAPPA IN Z. */
    *ol = op95fact_1.bz[0] * cz[0] + op95fact_1.bz[1] * cz[1] + op95fact_1.bz[
	    2] * cz[2] + op95fact_1.bz[3] * cz[3];
/* INTERPOLATE FOR QOT IN Z. */
    *qot = op95fact_1.bz[0] * czt[0] + op95fact_1.bz[1] * czt[1] + 
	    op95fact_1.bz[2] * czt[2] + op95fact_1.bz[3] * czt[3];
/* INTERPOLATE FOR QOD IN Z. */
    *qod = op95fact_1.bz[0] * czd[0] + op95fact_1.bz[1] * czd[1] + 
	    op95fact_1.bz[2] * czd[2] + op95fact_1.bz[3] * czd[3];
/* CORRECT FROM DERIVATE AT FIXED R TO DERIVATIVE AT FIXED RHO. */
    *qot -= *qod * 3.;
    *o = pow_dd(&c_b2, ol);
    return 0;
} /* op954d_ */

