/* t6rinteos01.f -- translated by f2c (version 20061008).
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
    doublereal epl[161395]	/* was [5][191][169] */, xx[5];
} eeeos_;

#define eeeos_1 eeeos_

struct {
    doublereal q[4], h__[4], xxh;
} aaeos_;

#define aaeos_1 aaeos_

struct {
    doublereal xz[1613950]	/* was [5][10][191][169] */, t6list[32279]	
	    /* was [169][191] */, rho[169], t6a[191], esk[32279]	/* 
	    was [191][169] */, esk2[32279]	/* was [191][169] */, dfsx[5],
	     dfs[191], dfsr[169];
    integer m, mf;
    doublereal xa[5];
} aeos_;

#define aeos_1 aeos_

struct {
    integer l1, l2, l3, l4, k1, k2, k3, k4, ip, iq;
} bbeos_;

#define bbeos_1 bbeos_

struct {
    doublereal esact, eos[10];
} eeos_;

#define eeos_1 eeos_

struct {
    integer ilast, idebug, itrack, ishort, imilne, imodpt, istor, iowr;
} luout_;

#define luout_1 luout_

/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */

/*     T6RINTEOS01 */

/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */
/* Subroutine */ int t6rinteos01_(doublereal *slr, doublereal *slt)
{
    /* System generated locals */
    integer i__1;

    /* Builtin functions */
    integer s_wsfe(cilist *), e_wsfe(void);
    /* Subroutine */ void s_stop(char *, ftnlen);

    /* Local variables */
    extern doublereal quadeos01_(integer *, integer *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *);
    static integer is, iu, iw, kx;
    static doublereal dix, dix2, esact2, esactq, esactq2;

    /* Fortran I/O blocks */
    static cilist io___10 = { 0, 0, 0, "(\"Interpolation indices out of ra"
	    "nge\",              \";please report conditions.\")", 0 };


/*     The purpose of this subroutine is to interpolate in T6 and rho */

    iu = 0;
    is = 0;
    i__1 = bbeos_1.k1 + bbeos_1.ip;
    for (kx = bbeos_1.k1; kx <= i__1; ++kx) {
	iw = 1;
	++iu;
	aaeos_1.h__[iu - 1] = quadeos01_(&is, &iw, slr, &aeos_1.esk[kx + 
		bbeos_1.l1 * 191 - 192], &aeos_1.esk[kx + bbeos_1.l2 * 191 - 
		192], &aeos_1.esk[kx + bbeos_1.l3 * 191 - 192], &aeos_1.rho[
		bbeos_1.l1 - 1], &aeos_1.rho[bbeos_1.l2 - 1], &aeos_1.rho[
		bbeos_1.l3 - 1]);
	if (bbeos_1.iq == 3) {
	    iw = 2;
	    aaeos_1.q[iu - 1] = quadeos01_(&is, &iw, slr, &aeos_1.esk[kx + 
		    bbeos_1.l2 * 191 - 192], &aeos_1.esk[kx + bbeos_1.l3 * 
		    191 - 192], &aeos_1.esk[kx + bbeos_1.l4 * 191 - 192], &
		    aeos_1.rho[bbeos_1.l2 - 1], &aeos_1.rho[bbeos_1.l3 - 1], &
		    aeos_1.rho[bbeos_1.l4 - 1]);
	}
	is = 1;
    }

    is = 0;
    iw = 1;
/* ..... eos(i) in lower-right 3x3(i=i1,i1+2 j=j1,j1+2) */
    eeos_1.esact = quadeos01_(&is, &iw, slt, aaeos_1.h__, &aaeos_1.h__[1], &
	    aaeos_1.h__[2], &aeos_1.t6a[bbeos_1.k1 - 1], &aeos_1.t6a[
	    bbeos_1.k2 - 1], &aeos_1.t6a[bbeos_1.k3 - 1]);
    if (bbeos_1.iq == 3) {
/* .....    eos(i) upper-right 3x3(i=i1+1,i1+3 j=j1,j1+2) */
	esactq = quadeos01_(&is, &iw, slt, aaeos_1.q, &aaeos_1.q[1], &
		aaeos_1.q[2], &aeos_1.t6a[bbeos_1.k1 - 1], &aeos_1.t6a[
		bbeos_1.k2 - 1], &aeos_1.t6a[bbeos_1.k3 - 1]);
    }
    if (bbeos_1.ip == 3) {
/* .....    eos(i) in lower-left 3x3. */
	esact2 = quadeos01_(&is, &iw, slt, &aaeos_1.h__[1], &aaeos_1.h__[2], &
		aaeos_1.h__[3], &aeos_1.t6a[bbeos_1.k2 - 1], &aeos_1.t6a[
		bbeos_1.k3 - 1], &aeos_1.t6a[bbeos_1.k4 - 1]);
/* .....    eos(i) smoothed in left 3x4 */
	dix = (aeos_1.t6a[bbeos_1.k3 - 1] - *slt) * aeos_1.dfs[bbeos_1.k3 - 1]
		;
	eeos_1.esact = eeos_1.esact * dix + esact2 * (1. - dix);
/*       endif   ! moved to loc a */
	if (bbeos_1.iq == 3) {
/* .....     eos(i) in upper-right 3x3. */
	    esactq2 = quadeos01_(&is, &iw, slt, &aaeos_1.q[1], &aaeos_1.q[2], 
		    &aaeos_1.q[3], &aeos_1.t6a[bbeos_1.k2 - 1], &aeos_1.t6a[
		    bbeos_1.k3 - 1], &aeos_1.t6a[bbeos_1.k4 - 1]);
	    esactq = esactq * dix + esactq2 * (1. - dix);
	}
    }

/* loc a */
    if (bbeos_1.iq == 3) {
	dix2 = (aeos_1.rho[bbeos_1.l3 - 1] - *slr) * aeos_1.dfsr[bbeos_1.l3 - 
		1];
	if (bbeos_1.ip == 3) {
/* .....        eos(i) smoothed in both log(T6) and log(R) */
	    eeos_1.esact = eeos_1.esact * dix2 + esactq * (1 - dix2);
	}
    }
    if (eeos_1.esact > 1e15) {
	io___10.ciunit = luout_1.ishort;
	s_wsfe(&io___10);
	e_wsfe();
	s_stop("", (ftnlen)0);
    }
    return 0;
} /* t6rinteos01_ */

