/* op953d.f -- translated by f2c (version 20100827).
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
    doublereal cappa[13300]	/* was [10][70][19] */, ztab;
} llot95_;

#define llot95_1 llot95_

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
/*     OP953D */
/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */
/* Subroutine */ int op953d_(doublereal *o, doublereal *ol, doublereal *qod, 
	doublereal *qot)
{
    /* Builtin functions */
    double pow_dd(doublereal *, doublereal *);

    /* Local variables */
    static doublereal c__[4];
    static integer i__, j;
    static doublereal cc[4];
    static integer id;
    static doublereal qc[4];
    static integer it, ix;
    static doublereal ccd[4], cct[4], deltar;

/* MHP 7/98 GET OPAL95 OPACITY FROM TABLE AT FIXED Z */
/* AS ABOVE FOR THE MODEL Z. */
/* INDICES FOR INTERPOLATION IN Z,X,T, AND R */
/* INTERPOLATION FACTORS FOR Z,X,T, AND R, AS WELL AS DERIVATIVE */
/* FACTORS FOR T AND RHO. */
/* DATA FOR LINEAR EXTRAPOLATION WHEN OUTSIDE TABLE IN RHO */
/* FIND OPACITY AT EACH OF THE 4 NEARBY VALUES OF X */
    for (j = 1; j <= 4; ++j) {
	ix = op95indx_1.jx[(j << 2) - 4];
/* FOR EACH X, GET CAPPA FOR 4 VALUES OF T */
	for (i__ = 1; i__ <= 4; ++i__) {
	    it = op95indx_1.jt + i__ - 1;
/* FOR EACH T, GET CAPPA FOR 4 VALUES OF R */
	    id = op95indx_1.jd[i__ - 1];
/* LOG CAPPA AT DESIRED RHO FOR EACH OF THE 4 DESIRED T. */
	    c__[i__ - 1] = op95fact_1.bd[i__ - 1] * llot95_1.cappa[ix + (it + 
		    id * 70) * 10 - 711] + op95fact_1.bd[i__ + 3] * 
		    llot95_1.cappa[ix + (it + (id + 1) * 70) * 10 - 711] + 
		    op95fact_1.bd[i__ + 7] * llot95_1.cappa[ix + (it + (id + 
		    2) * 70) * 10 - 711] + op95fact_1.bd[i__ + 11] * 
		    llot95_1.cappa[ix + (it + (id + 3) * 70) * 10 - 711];
/* D LOG CAPPA/D LOG R FOR EACH OF THE 4 DESIRED T. */
	    qc[i__ - 1] = op95fact_1.bdd[i__ - 1] * llot95_1.cappa[ix + (it + 
		    id * 70) * 10 - 711] + op95fact_1.bdd[i__ + 3] * 
		    llot95_1.cappa[ix + (it + (id + 1) * 70) * 10 - 711] + 
		    op95fact_1.bdd[i__ + 7] * llot95_1.cappa[ix + (it + (id + 
		    2) * 70) * 10 - 711] + op95fact_1.bdd[i__ + 11] * 
		    llot95_1.cappa[ix + (it + (id + 3) * 70) * 10 - 711];
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
	cc[j - 1] = op95fact_1.bt[0] * c__[0] + op95fact_1.bt[1] * c__[1] + 
		op95fact_1.bt[2] * c__[2] + op95fact_1.bt[3] * c__[3];
/* D LOG CAPPA/D LOG T */
	cct[j - 1] = op95fact_1.btt[0] * c__[0] + op95fact_1.btt[1] * c__[1] 
		+ op95fact_1.btt[2] * c__[2] + op95fact_1.btt[3] * c__[3];
/* D LOG CAPPA/D LOG R */
	ccd[j - 1] = op95fact_1.bt[0] * qc[0] + op95fact_1.bt[1] * qc[1] + 
		op95fact_1.bt[2] * qc[2] + op95fact_1.bt[3] * qc[3];
    }
/* INTERPOLATE FOR LOG CAPPA IN X. */
    *ol = op95fact_1.bx[0] * cc[0] + op95fact_1.bx[4] * cc[1] + op95fact_1.bx[
	    8] * cc[2] + op95fact_1.bx[12] * cc[3];
/* INTERPOLATE FOR QOT IN X. */
    *qot = op95fact_1.bx[0] * cct[0] + op95fact_1.bx[4] * cct[1] + 
	    op95fact_1.bx[8] * cct[2] + op95fact_1.bx[12] * cct[3];
/* INTERPOLATE FOR QOD IN X. */
    *qod = op95fact_1.bx[0] * ccd[0] + op95fact_1.bx[4] * ccd[1] + 
	    op95fact_1.bx[8] * ccd[2] + op95fact_1.bx[12] * ccd[3];
/* CORRECT FROM DERIVATE AT FIXED R TO DERIVATIVE AT FIXED RHO. */
    *qot -= *qod * 3.;
    *o = pow_dd(&c_b2, ol);
    return 0;
} /* op953d_ */

