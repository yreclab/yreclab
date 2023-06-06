/* pindex.f -- translated by f2c (version 20100827).
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
    logical lscrib, lpshll, lchemo, lconzo, ljout, lprtin, lpenv;
} ccout_;

#define ccout_1 ccout_

struct {
    integer npenv, nprt1, nprt2, nprtpt, npoint;
} ccout1_;

#define ccout1_1 ccout1_



/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */
/* PINDEX */
/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */
/* Subroutine */ int pindex_(integer *jxbeg, integer *jxend, logical *lshell, 
	integer *m, integer *id, integer *idm)
{
    /* System generated locals */
    integer i__1, i__2;

    /* Local variables */
    static integer j, ibeg, iend, ixbeg;

/*  ID IS THE ARRAY OF THE SHELLS TO BE PRINTED OUT; */
/*  I.E. IF SHELLS 1,3,5,..TO BE PRINTED ID(1)=1,ID(2)=3,.. */
    /* Parameter adjustments */
    --id;

    /* Function Body */
    id[1] = 1;
    *idm = 2;
    if (*lshell && ccout_1.lpshll) {
/*  PRINT OUT EVERY ZONE IN H-BURNING SHELL */
	if (ccout1_1.nprtpt < *jxbeg) {
	    ibeg = max(2,ccout1_1.nprtpt);
	    iend = *jxbeg / ccout1_1.nprtpt * ccout1_1.nprtpt;
	    i__1 = iend;
	    i__2 = ccout1_1.nprtpt;
	    for (j = ibeg; i__2 < 0 ? j >= i__1 : j <= i__1; j += i__2) {
		id[*idm] = j;
		++(*idm);
/* L10: */
	    }
	}
	if (iend == *jxbeg) {
	    ixbeg = *jxbeg + 1;
	} else {
	    ixbeg = *jxbeg;
	}
	i__2 = *jxend;
	for (j = ixbeg; j <= i__2; ++j) {
	    id[*idm] = j;
	    ++(*idm);
/* L20: */
	}
	if (ccout1_1.nprtpt < *m) {
	    ibeg = (*jxend / ccout1_1.nprtpt + 1) * ccout1_1.nprtpt;
	    iend = *m / ccout1_1.nprtpt * ccout1_1.nprtpt;
	    i__2 = iend;
	    i__1 = ccout1_1.nprtpt;
	    for (j = ibeg; i__1 < 0 ? j >= i__2 : j <= i__2; j += i__1) {
		id[*idm] = j;
		++(*idm);
/* L30: */
	    }
	}
    } else if (ccout1_1.nprtpt < *m) {
/*  GENERAL CASE; PRINT OUT EVERY NPRTPT POINTS. */
	ibeg = max(2,ccout1_1.nprtpt);
	iend = *m / ccout1_1.nprtpt * ccout1_1.nprtpt;
	if (iend == *m) {
	    iend -= ccout1_1.nprtpt;
	}
	i__1 = iend;
	i__2 = ccout1_1.nprtpt;
	for (j = ibeg; i__2 < 0 ? j >= i__1 : j <= i__1; j += i__2) {
	    id[*idm] = j;
	    ++(*idm);
/* L40: */
	}
    }
    id[*idm] = *m;
    return 0;
} /* pindex_ */

