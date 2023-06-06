/* op952d.f -- translated by f2c (version 20100827).
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
    doublereal cappae[1330]	/* was [70][19] */, xtab;
} llot95e_;

#define llot95e_1 llot95e_

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
/*     OP952D */
/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */
/* Subroutine */ int op952d_(doublereal *o, doublereal *ol, doublereal *qod, 
	doublereal *qot)
{
    /* Builtin functions */
    double pow_dd(doublereal *, doublereal *);

    /* Local variables */
    static doublereal c__[4];
    static integer i__, id;
    static doublereal qc[4];
    static integer it;
    static doublereal deltar;

/* MHP 7/98 GET OPAL95 OPACITY FROM TABLE AT SURFACE X,Z */
/* AS ABOVE FOR DESIRED SURFACE VALUE OF X. */
/* INDICES FOR INTERPOLATION IN Z,X,T, AND R */
/* INTERPOLATION FACTORS FOR Z,X,T, AND R, AS WELL AS DERIVATIVE */
/* FACTORS FOR T AND RHO. */
/* DATA FOR LINEAR EXTRAPOLATION WHEN OUTSIDE TABLE IN RHO */
/* FIND OPACITY AT EACH OF THE 4 NEARBY VALUES OF T. */
    for (i__ = 1; i__ <= 4; ++i__) {
	it = op95indx_1.jt + i__ - 1;
/* FOR EACH T, INTERPOLATE IN 4 VALUES OF R */
	id = op95indx_1.jd[i__ - 1];
/* LOG CAPPA AT DESIRED RHO FOR EACH OF THE 4 DESIRED T. */
	c__[i__ - 1] = op95fact_1.bd[i__ - 1] * llot95e_1.cappae[it + id * 70 
		- 71] + op95fact_1.bd[i__ + 3] * llot95e_1.cappae[it + (id + 
		1) * 70 - 71] + op95fact_1.bd[i__ + 7] * llot95e_1.cappae[it 
		+ (id + 2) * 70 - 71] + op95fact_1.bd[i__ + 11] * 
		llot95e_1.cappae[it + (id + 3) * 70 - 71];
/* D LOG CAPPA/D LOG R FOR EACH OF THE 4 DESIRED T. */
	qc[i__ - 1] = op95fact_1.bdd[i__ - 1] * llot95e_1.cappae[it + id * 70 
		- 71] + op95fact_1.bdd[i__ + 3] * llot95e_1.cappae[it + (id + 
		1) * 70 - 71] + op95fact_1.bdd[i__ + 7] * llot95e_1.cappae[it 
		+ (id + 2) * 70 - 71] + op95fact_1.bdd[i__ + 11] * 
		llot95e_1.cappae[it + (id + 3) * 70 - 71];
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
    *ol = op95fact_1.bt[0] * c__[0] + op95fact_1.bt[1] * c__[1] + 
	    op95fact_1.bt[2] * c__[2] + op95fact_1.bt[3] * c__[3];
/* D LOG CAPPA/D LOG T */
    *qot = op95fact_1.btt[0] * c__[0] + op95fact_1.btt[1] * c__[1] + 
	    op95fact_1.btt[2] * c__[2] + op95fact_1.btt[3] * c__[3];
/* D LOG CAPPA/D LOG R */
    *qod = op95fact_1.bt[0] * qc[0] + op95fact_1.bt[1] * qc[1] + 
	    op95fact_1.bt[2] * qc[2] + op95fact_1.bt[3] * qc[3];
/* CORRECT FROM DERIVATE AT FIXED R TO DERIVATIVE AT FIXED RHO. */
    *qot -= *qod * 3.;
    *o = pow_dd(&c_b2, ol);
    return 0;
} /* op952d_ */

