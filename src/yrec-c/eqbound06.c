/* eqbound06.f -- translated by f2c (version 20061008).
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
    doublereal xz[1664650]	/* was [5][10][197][169] */, t6list[33293]	
	    /* was [169][197] */, rho[169], t6a[197], esk[33293]	/* 
	    was [197][169] */, esk2[33293]	/* was [197][169] */, dfsx[5],
	     dfs[197], dfsr[169];
    integer m, mf;
    doublereal xa[5];
} aeos06_;

#define aeos06_1 aeos06_

struct {
    doublereal zz[5];
    integer iri[10], index[10], nta[169], nra[197];
} beos06_;

#define beos06_1 beos06_

struct {
    integer l1, l2, l3, l4, k1, k2, k3, k4, ip, iq;
} bbeos06_;

#define bbeos06_1 bbeos06_

/* Table of constant values */

static doublereal c_b2 = 10.;

/* LLP  10/16/06 SUBROUTINE TO CHECK IF POINT IS WITHIN */
/* OPAL 2006 EOS TABLE. */
/*       SUBROUTINE EQBOUND06(T,DL,DL0,FAC,LTAB,LRAMP)  ! KC 2025-05-31 */
/* Subroutine */ int eqbound06_(doublereal *t, doublereal *dl, doublereal *
	fac, logical *ltab, logical *lramp)
{
    /* Builtin functions */
    double pow_dd(doublereal *, doublereal *);

    /* Local variables */
    static doublereal d__;
    static integer k, l;
    static doublereal t6, drampf, trampf;

/* KC 2025-05-30 reordered common block elements */
/*       common/beos06/ iri(10),index(10),nta(nr),zz(mx),nra(nt) */
    t6 = *t * 1e-6;
    d__ = pow_dd(&c_b2, dl);
/* EXIT IF OUTSIDE TABLE IN RHO */
    if (d__ < aeos06_1.rho[0] || d__ >= aeos06_1.rho[168]) {
	goto L9999;
/* Out of Table in density. Go to out of table exit. */
    }
/* Exit if outside table in T6 */
    if (t6 > aeos06_1.t6a[0] || t6 <= aeos06_1.t6a[196]) {
	goto L9999;
/* Out of Table in temperature. Go to out of table exit. */
    }
/* Initialize */
    drampf = 1.;
/* Initialize density ramp factor to 1 */
    trampf = 1.;
/* Initialize temperature ramp factor to 1 */
    *ltab = TRUE_;
/* Presume that T6,D point is in OPAL table */
    *lramp = FALSE_;
/* i.e. we are not in the border of the table. */
/* Check for easy borders */
/* presume ramping is not needed, */
    if (t6 > aeos06_1.t6a[1]) {
	trampf = (t6 - aeos06_1.t6a[0]) / (aeos06_1.t6a[1] - aeos06_1.t6a[0]);
/* Ramp in temperature */
	*lramp = TRUE_;
    }
    if (d__ < aeos06_1.rho[1]) {
	drampf = (d__ - aeos06_1.rho[0]) / (aeos06_1.rho[1] - aeos06_1.rho[0])
		;
/* Ramp in density */
	*lramp = TRUE_;
    }
/* Find a k such that T6a(k-1) >= T6 > T6a(k) */
/* and an l such that rho(l-1) <  D  <= rho(l) */
/* The ESAC06 variables (k=)k3 and (l-)l2 are close to what we need. */
/* A linear search will work fine. */
    k = bbeos06_1.k3;
L10:
    if (t6 <= aeos06_1.t6a[k - 1]) {
	++k;
	goto L10;
    }
L20:
    if (t6 > aeos06_1.t6a[k - 2]) {
	--k;
	goto L20;
    }
/* We now have: T6a(k-1) >= T6 > T6a(k) */
    l = bbeos06_1.l2;
L30:
    if (d__ > aeos06_1.rho[l - 1]) {
	++l;
	goto L30;
    }
L40:
    if (d__ <= aeos06_1.rho[l - 2]) {
	--l;
	goto L40;
    }
/* We now have: rho(l-1) <  D  <= rho(l) */
/* For a given temperature in array T6a with index k, e.e., T6a(k), element */
/* nra(k) of array nra contains the index to the max allowed density in */
/* array rho. So, for a given T6a(k), the associated D must be less than */
/* rho(nra(k)). A valid index in array rho must be less than or equal to */
/* nra(k) */
    if (l > beos06_1.nra[k - 1]) {
	goto L9999;
/* Out of table exit in density. */
    }
    if (l == beos06_1.nra[k - 1]) {
	*lramp = TRUE_;
	drampf = (aeos06_1.rho[l - 1] - d__) / (aeos06_1.rho[l - 1] - 
		aeos06_1.rho[l - 2]);
    }
/* For a given density in array rho with index l, i.e., rho(l), element */
/* nta(l) of array nta contains the index to the min allowed temperature */
/* in array T6a. So for a given rho(l), the associated T6 must be */
/* greater than T6a(nta(l)). (Note that T6a is a decreasing array.) A */
/* valid index in T6a must be less than or equal to nta(l). */
    if (k > beos06_1.nta[l - 1]) {
	goto L9999;
/* Out of table exit in temperature */
    }
    if (k == beos06_1.nta[l - 1]) {
	*lramp = TRUE_;
	trampf = (t6 - aeos06_1.t6a[k - 1]) / (aeos06_1.t6a[k - 2] - 
		aeos06_1.t6a[k - 1]);
    }
    *fac = drampf * trampf;
    return 0;
/* OUT OF TABLE EXIT */
L9999:
    *ltab = FALSE_;
/* Not in table */
    *lramp = TRUE_;
/* Turn on ramping */
    *fac = 0.;
/*                            This way, out of table results are ramped to zero. */
/* Set ramping factor to zero */
    return 0;
} /* eqbound06_ */

