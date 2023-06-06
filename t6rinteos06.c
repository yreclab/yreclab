/* t6rinteos06.f -- translated by f2c (version 20100827).
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
    doublereal epl[166465]	/* was [5][197][169] */, xx[5];
} eeeos06_;

#define eeeos06_1 eeeos06_

struct {
    doublereal q[4], h__[4], xxh;
} aaeos06_;

#define aaeos06_1 aaeos06_

struct {
    doublereal xz[1664650]	/* was [5][10][197][169] */, t6list[33293]	
	    /* was [169][197] */, rho[169], t6a[197], esk[33293]	/* 
	    was [197][169] */, esk2[33293]	/* was [197][169] */, dfsx[5],
	     dfs[197], dfsr[169];
    integer m, mf;
    doublereal xa[5];
} aeos06_;

#define aeos06_1 aeos06_

struct {
    integer l1, l2, l3, l4, k1, k2, k3, k4, ip, iq;
} bbeos06_;

#define bbeos06_1 bbeos06_

struct {
    doublereal esact, eos[10];
} eeos06_;

#define eeos06_1 eeos06_

struct {
    integer ilast, idebug, itrack, ishort, imilne, imodpt, istor, iowr;
} luout_;

#define luout_1 luout_

/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */

/*     T6RINTEOS01 */

/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */
/* Subroutine */ int t6rinteos06_(doublereal *slr, doublereal *slt)
{
    /* System generated locals */
    integer i__1;

    /* Builtin functions */
    integer s_wsfe(cilist *), e_wsfe(void);
    /* Subroutine */ int s_stop(char *, ftnlen);

    /* Local variables */
    extern doublereal quadeos06_(integer *, integer *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *);
    static integer is, iu, iw, kx;
    static doublereal dix, dix2, esact2, esactq, esactq2;

    /* Fortran I/O blocks */
    static cilist io___10 = { 0, 0, 0, "(\"T6RINTEOS06: Interpolation indice"
	    "s out\",              \" of range;please report conditions.\")", 
	    0 };


/*     The purpose of this OPAL 2006 EOS subroutine is to interpolate in */
/*     T6 and rho */

    iu = 0;
    is = 0;
    i__1 = bbeos06_1.k1 + bbeos06_1.ip;
    for (kx = bbeos06_1.k1; kx <= i__1; ++kx) {
	iw = 1;
	++iu;
	aaeos06_1.h__[iu - 1] = quadeos06_(&is, &iw, slr, &aeos06_1.esk[kx + 
		bbeos06_1.l1 * 197 - 198], &aeos06_1.esk[kx + bbeos06_1.l2 * 
		197 - 198], &aeos06_1.esk[kx + bbeos06_1.l3 * 197 - 198], &
		aeos06_1.rho[bbeos06_1.l1 - 1], &aeos06_1.rho[bbeos06_1.l2 - 
		1], &aeos06_1.rho[bbeos06_1.l3 - 1]);
	if (bbeos06_1.iq == 3) {
	    iw = 2;
	    aaeos06_1.q[iu - 1] = quadeos06_(&is, &iw, slr, &aeos06_1.esk[kx 
		    + bbeos06_1.l2 * 197 - 198], &aeos06_1.esk[kx + 
		    bbeos06_1.l3 * 197 - 198], &aeos06_1.esk[kx + 
		    bbeos06_1.l4 * 197 - 198], &aeos06_1.rho[bbeos06_1.l2 - 1]
		    , &aeos06_1.rho[bbeos06_1.l3 - 1], &aeos06_1.rho[
		    bbeos06_1.l4 - 1]);
	}
	is = 1;
    }

    is = 0;
    iw = 1;
/* ..... eos(i) in lower-right 3x3(i=i1,i1+2 j=j1,j1+2) */
    eeos06_1.esact = quadeos06_(&is, &iw, slt, aaeos06_1.h__, &aaeos06_1.h__[
	    1], &aaeos06_1.h__[2], &aeos06_1.t6a[bbeos06_1.k1 - 1], &
	    aeos06_1.t6a[bbeos06_1.k2 - 1], &aeos06_1.t6a[bbeos06_1.k3 - 1]);
    if (bbeos06_1.iq == 3) {
/* .....    eos(i) upper-right 3x3(i=i1+1,i1+3 j=j1,j1+2) */
	esactq = quadeos06_(&is, &iw, slt, aaeos06_1.q, &aaeos06_1.q[1], &
		aaeos06_1.q[2], &aeos06_1.t6a[bbeos06_1.k1 - 1], &
		aeos06_1.t6a[bbeos06_1.k2 - 1], &aeos06_1.t6a[bbeos06_1.k3 - 
		1]);
    }
    if (bbeos06_1.ip == 3) {
/* .....    eos(i) in lower-left 3x3. */
	esact2 = quadeos06_(&is, &iw, slt, &aaeos06_1.h__[1], &aaeos06_1.h__[
		2], &aaeos06_1.h__[3], &aeos06_1.t6a[bbeos06_1.k2 - 1], &
		aeos06_1.t6a[bbeos06_1.k3 - 1], &aeos06_1.t6a[bbeos06_1.k4 - 
		1]);
/* .....    eos(i) smoothed in left 3x4 */
	dix = (aeos06_1.t6a[bbeos06_1.k3 - 1] - *slt) * aeos06_1.dfs[
		bbeos06_1.k3 - 1];
	eeos06_1.esact = eeos06_1.esact * dix + esact2 * (1. - dix);
/*       endif   ! moved to loc a */
	if (bbeos06_1.iq == 3) {
/* .....     eos(i) in upper-right 3x3. */
	    esactq2 = quadeos06_(&is, &iw, slt, &aaeos06_1.q[1], &aaeos06_1.q[
		    2], &aaeos06_1.q[3], &aeos06_1.t6a[bbeos06_1.k2 - 1], &
		    aeos06_1.t6a[bbeos06_1.k3 - 1], &aeos06_1.t6a[
		    bbeos06_1.k4 - 1]);
	    esactq = esactq * dix + esactq2 * (1. - dix);
	}
    }

/* loc a */
    if (bbeos06_1.iq == 3) {
	dix2 = (aeos06_1.rho[bbeos06_1.l3 - 1] - *slr) * aeos06_1.dfsr[
		bbeos06_1.l3 - 1];
	if (bbeos06_1.ip == 3) {
/* .....        eos(i) smoothed in both log(T6) and log(R) */
	    eeos06_1.esact = eeos06_1.esact * dix2 + esactq * (1 - dix2);
	}
    }
    if (eeos06_1.esact > 1e15) {
	io___10.ciunit = luout_1.ishort;
	s_wsfe(&io___10);
	e_wsfe();
	s_stop("", (ftnlen)0);
    }
    return 0;
} /* t6rinteos06_ */

