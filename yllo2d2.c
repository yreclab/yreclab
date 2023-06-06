/* yllo2d2.f -- translated by f2c (version 20100827).
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
    doublereal gridt2[50], gridx2[3], grhot32[17];
} gllot2_;

#define gllot2_1 gllot2_

struct {
    doublereal opacity2[2550]	/* was [150][17] */;
    integer numxm2, numtm2;
} llot2_;

#define llot2_1 llot2_

struct {
    doublereal xenv42, zenv42, cford42[3400]	/* was [50][68] */;
    integer kipm12;
} llot42_;

#define llot42_1 llot42_

struct {
    doublereal cford2[10200]	/* was [150][68] */;
    integer nds2[150], ndd2[150];
} lintpl2_;

#define lintpl2_1 lintpl2_

/* Table of constant values */

static doublereal c_b5 = 10.;



/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */
/* YLLO2D2 */
/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */
/* Subroutine */ int yllo2d2_(doublereal *t, doublereal *d__, integer *m1, 
	integer *m2, integer *m3, doublereal *o, doublereal *ol, doublereal *
	qodf, doublereal *qotf)
{
    /* System generated locals */
    integer i__1;

    /* Builtin functions */
    /* Subroutine */ int s_stop(char *, ftnlen);
    double pow_dd(doublereal *, doublereal *);

    /* Local variables */
    static doublereal c1, c2, c3, c4, dx;
    static integer it, jt;
    static doublereal xt[50];
    static integer mm1;
    static doublereal ol0;
    static integer ndf;
    static doublereal ol00;
    static integer itf, its;
    static doublereal yto[50], aqod[50], qodi;
    static integer ndss, knot;
    static logical lmore;
    static doublereal qodti;
    static integer index1, index2;
    extern /* Subroutine */ int findex_(doublereal *, integer *, doublereal *,
	     integer *), intpol_(doublereal *, doublereal *, integer *, 
	    doublereal *, doublereal *, doublereal *);

/*     TWO DIMENSIONAL INTERPOLATION FOR OPACITY */
/*     AND THE DERIVTIVES. */
/* DBG 5/94 Modified to use second opacity table at different Z */
/* M1, M2, AND M3 ARE NEAREST GRID POINT OF ABUNDANCE, TEMPERATURE, */
/* AND DENSITY WE GOT AT 'GETD'. */
/* O IS OPACITY. */
/* OL IS DLOG(O) */
/* QODF IS THE PARTIAL DERIVATIVE OF O WRT D. */
/* QOTF IS THE PARTIAL DERIVATIVE OF O WRT T. */
/* ========================================================= */
    lmore = TRUE_;
/* CC FOR SIX GRID POINTS OF TEMPERATURE */
    its = *m2 - 2;
    if (its <= 0) {
	its = 1;
    }
    itf = *m2 + 3;
    if (itf > llot2_1.numtm2) {
	itf = llot2_1.numtm2;
    }
    if (*m1 < 4) {
	mm1 = *m1;
    } else {
	mm1 = llot42_1.kipm12;
    }
    jt = 0;
    i__1 = itf;
    for (it = its; it <= i__1; ++it) {
	index1 = it + (mm1 - 1) * llot2_1.numtm2;
	ndss = lintpl2_1.nds2[index1 - 1];
	if (ndss != 1) {
	    s_stop(" OPAL95 2D2 CHECK NDSS ", (ftnlen)23);
	}
	ndf = ndss + lintpl2_1.ndd2[index1 - 1] - 1;
	findex_(gllot2_1.grhot32, &ndf, d__, m3);
	if (*m3 < 0) {
/*  OUT SIDE THEN  LINEAR EXTRAPOLATION */
	    *m3 = -(*m3);
	    knot = *m3 - ndss + 1;
	    index2 = knot - 1 << 2;
	    dx = *d__ - gllot2_1.grhot32[*m3 - 1];
	    if (*m1 < 4) {
		c1 = lintpl2_1.cford2[index1 + (index2 + 1) * 150 - 151];
		c2 = lintpl2_1.cford2[index1 + (index2 + 2) * 150 - 151];
	    } else {
		c1 = llot42_1.cford42[it + (index2 + 1) * 50 - 51];
		c2 = llot42_1.cford42[it + (index2 + 2) * 50 - 51];
	    }
	    ol0 = c2 * dx + c1;
	    qodi = c2;
	} else {
/*  IN SIDE THEN  SPLINE INTERPOLATION */
	    knot = *m3 - ndss + 1;
	    index2 = knot - 1 << 2;
	    dx = *d__ - gllot2_1.grhot32[*m3 - 1];
	    if (*m1 < 4) {
		c1 = lintpl2_1.cford2[index1 + (index2 + 1) * 150 - 151];
		c2 = lintpl2_1.cford2[index1 + (index2 + 2) * 150 - 151];
		c3 = lintpl2_1.cford2[index1 + (index2 + 3) * 150 - 151];
		c4 = lintpl2_1.cford2[index1 + (index2 + 4) * 150 - 151];
	    } else {
		c1 = llot42_1.cford42[it + (index2 + 1) * 50 - 51];
		c2 = llot42_1.cford42[it + (index2 + 2) * 50 - 51];
		c3 = llot42_1.cford42[it + (index2 + 3) * 50 - 51];
		c4 = llot42_1.cford42[it + (index2 + 4) * 50 - 51];
	    }
/* INTERPOLATION FOR OPACITY(OL) IN THE ENTRY D AND THE EACH T-GRID */
/* ESTIMATES THE PARTIAL DERIVATIVE OF OL WRT D */
/* EVALUATES THE INTERPOLATION VALUE IN THE SUB-RANGE WE DETERMINED. */
	    ol0 = ((c4 * dx + c3) * dx + c2) * dx + c1;
	    qodi = (c4 * 3. * dx + c3 * 2.) * dx + c2;
	}

	++jt;
	xt[jt - 1] = gllot2_1.gridt2[it - 1];
	yto[jt - 1] = ol0;
	aqod[jt - 1] = qodi;
/* L300: */
    }
    if (xt[0] > *t || xt[jt - 1] < *t) {
	s_stop(" EXTRAPOLATION FAILS ", (ftnlen)21);
    }
/* C INTERPOLATION FOR THE OPACITY IN THE ENTRY T AND D. */
/* C GET THE PARTIAL DERIVATIVE OF OL WRT T. */
    intpol_(xt, yto, &jt, t, &ol00, qotf);
    *ol = ol00;
    *o = pow_dd(&c_b5, ol);
/* QOTF = D LN(O)/D LN(T) */
/* C FIND THE PARTIAL DERIVATIVE VALUE OF OL WRT D IN THE GIVEN T AND D */
    intpol_(xt, aqod, &jt, t, qodf, &qodti);
/* QODF = D LN(O)/D LN(D) */
    return 0;
} /* yllo2d2_ */

