/* t6rinterp.f -- translated by f2c (version 20061008).
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
    integer ilast, idebug, itrack, ishort, imilne, imodpt, istor, iowr;
} luout_;

#define luout_1 luout_

struct {
    doublereal epl[21560]	/* was [5][56][77] */, xx[5];
} ee_;

#define ee_1 ee_

struct {
    doublereal q[4], h__[4], xxh;
} aa_;

#define aa_1 aa_

struct {
    doublereal xz[215600]	/* was [5][10][56][77] */, t6list[4312]	/* 
	    was [77][56] */, rho[77], t6a[56], esk[4312]	/* was [56][
	    77] */, esk2[4312]	/* was [56][77] */, dfsx[5], dfs[56], dfsr[77]
	    , xa[5];
    integer m, mf;
} a_;

#define a_1 a_

struct {
    integer l1, l2, l3, l4, k1, k2, k3, k4, ip, iq;
} bb_;

#define bb_1 bb_

struct {
    doublereal esact, eos[10];
} e_;

#define e_1 e_

/* *********************************************************************** */
/* Subroutine */ int t6rinterp_(doublereal *slr, doublereal *slt)
{
    /* System generated locals */
    integer i__1;

    /* Builtin functions */
    integer s_wsfe(cilist *), e_wsfe(void);
    /* Subroutine */ void s_stop(char *, ftnlen);

    /* Local variables */
    static integer is, iu, iw, kx;
    static doublereal dix, dix2;
    extern doublereal quad_(integer *, integer *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *);
    static doublereal esact2, esactq, esactq2;

    /* Fortran I/O blocks */
    static cilist io___10 = { 0, 0, 0, "(\"INTERPOLATION INDICES OUT OF RA"
	    "NGE\",              \";PLEASE REPORT CONDITIONS.\")", 0 };


/*     THE PURPOSE OF THIS SUBROUTINE IS TO INTERPOLATE IN T6 AND RHO */

    iu = 0;
    is = 0;
    i__1 = bb_1.k1 + bb_1.ip;
    for (kx = bb_1.k1; kx <= i__1; ++kx) {
	iw = 1;
	++iu;
	aa_1.h__[iu - 1] = quad_(&is, &iw, slr, &a_1.esk[kx + bb_1.l1 * 56 - 
		57], &a_1.esk[kx + bb_1.l2 * 56 - 57], &a_1.esk[kx + bb_1.l3 *
		 56 - 57], &a_1.rho[bb_1.l1 - 1], &a_1.rho[bb_1.l2 - 1], &
		a_1.rho[bb_1.l3 - 1]);
	if (bb_1.iq == 3) {
	    iw = 2;
	    aa_1.q[iu - 1] = quad_(&is, &iw, slr, &a_1.esk[kx + bb_1.l2 * 56 
		    - 57], &a_1.esk[kx + bb_1.l3 * 56 - 57], &a_1.esk[kx + 
		    bb_1.l4 * 56 - 57], &a_1.rho[bb_1.l2 - 1], &a_1.rho[
		    bb_1.l3 - 1], &a_1.rho[bb_1.l4 - 1]);
	}
	is = 1;
    }

    is = 0;
    iw = 1;
/* ..... EOS(I) IN LOWER-RIGHT 3X3(I=I1,I1+2 J=J1,J1+2) */
    e_1.esact = quad_(&is, &iw, slt, aa_1.h__, &aa_1.h__[1], &aa_1.h__[2], &
	    a_1.t6a[bb_1.k1 - 1], &a_1.t6a[bb_1.k2 - 1], &a_1.t6a[bb_1.k3 - 1]
	    );
    if (bb_1.iq == 3) {
/* .....    EOS(I) UPPER-RIGHT 3X3(I=I1+1,I1+3 J=J1,J1+2) */
	esactq = quad_(&is, &iw, slt, aa_1.q, &aa_1.q[1], &aa_1.q[2], &
		a_1.t6a[bb_1.k1 - 1], &a_1.t6a[bb_1.k2 - 1], &a_1.t6a[bb_1.k3 
		- 1]);
    }
    if (bb_1.ip == 3) {
/* .....    EOS(I) IN LOWER-LEFT 3X3. */
	esact2 = quad_(&is, &iw, slt, &aa_1.h__[1], &aa_1.h__[2], &aa_1.h__[3]
		, &a_1.t6a[bb_1.k2 - 1], &a_1.t6a[bb_1.k3 - 1], &a_1.t6a[
		bb_1.k4 - 1]);
/* .....    EOS(I) SMOOTHED IN LEFT 3X4 */
	dix = (a_1.t6a[bb_1.k3 - 1] - *slt) * a_1.dfs[bb_1.k3 - 1];
	e_1.esact = e_1.esact * dix + esact2 * (1. - dix);
    }
    if (bb_1.iq == 3) {
/* .....     EOS(I) IN UPPER-RIGHT 3X3. */
	esactq2 = quad_(&is, &iw, slt, &aa_1.q[1], &aa_1.q[2], &aa_1.q[3], &
		a_1.t6a[bb_1.k2 - 1], &a_1.t6a[bb_1.k3 - 1], &a_1.t6a[bb_1.k4 
		- 1]);
	esactq = esactq * dix + esactq2 * (1. - dix);
    }

    if (bb_1.iq == 3) {
	dix2 = (a_1.rho[bb_1.l3 - 1] - *slr) * a_1.dfsr[bb_1.l3 - 1];
	if (bb_1.ip == 3) {
/* .....        EOS(I) SMOOTHED IN BOTH LOG(T6) AND LOG(R) */
	    e_1.esact = e_1.esact * dix2 + esactq * (1. - dix2);
	}
    }
    if (e_1.esact > 1e15) {
	io___10.ciunit = luout_1.ishort;
	s_wsfe(&io___10);
	e_wsfe();
	s_stop("", (ftnlen)0);
    }
    return 0;
} /* t6rinterp_ */

