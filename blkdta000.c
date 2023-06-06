/* blkdta000.f -- translated by f2c (version 20100827).
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
    doublereal q[4], h__[4], xxh;
} aa_;

#define aa_1 aa_

struct a_1_ {
    doublereal xz[215600]	/* was [5][10][56][77] */, t6list[4312]	/* 
	    was [77][56] */, rho[77], t6a[56], esk[4312]	/* was [56][
	    77] */, esk2[4312]	/* was [56][77] */, dfsx[5], dfs[56], dfsr[77]
	    , xa[5];
    integer m, mf;
};

#define a_1 (*(struct a_1_ *) &a_)

struct b_1_ {
    doublereal zz[5];
    integer iri[10], index[10], nta[77];
};

#define b_1 (*(struct b_1_ *) &b_)

/* Initialized data */

struct {
    doublereal fill_1[228807];
    doublereal e_2[5];
    doublereal fill_3[1];
    } a_ = { {0}, 0., .2, .4, .6, .8 };

struct {
    doublereal fill_1[10];
    integer e_2[87];
    } b_ = { {0}, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 56, 56, 56, 56, 56, 56, 56, 
	    56, 56, 56, 56, 56, 56, 56, 56, 56, 56, 56, 56, 56, 56, 56, 56, 
	    56, 56, 56, 56, 56, 56, 56, 56, 56, 56, 56, 56, 56, 56, 54, 54, 
	    54, 54, 54, 54, 54, 39, 37, 36, 34, 33, 31, 31, 30, 29, 28, 27, 
	    26, 26, 25, 24, 23, 22, 21, 21, 20, 19, 18, 17, 16, 15, 15, 13, 
	    13, 11, 11, 9, 9, 7 };


/* *********************************************************************** */

