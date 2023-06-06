/* ll4th.f -- translated by f2c (version 20100827).
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
    doublereal xenv4, zenv4, cford4[3400]	/* was [50][68] */;
    integer kipm1;
} llot4_;

#define llot4_1 llot4_

struct {
    doublereal xenv42, zenv42, cford42[3400]	/* was [50][68] */;
    integer kipm12;
} llot42_;

#define llot42_1 llot42_

struct {
    doublereal gridt[50], gridx[3], grhot3[17];
} gllot_;

#define gllot_1 gllot_

struct {
    doublereal gridt2[50], gridx2[3], grhot32[17];
} gllot2_;

#define gllot2_1 gllot2_

struct {
    doublereal opacity[2550]	/* was [150][17] */;
    integer numxm, numtm;
} llot_;

#define llot_1 llot_

struct {
    doublereal opacity2[2550]	/* was [150][17] */;
    integer numxm2, numtm2;
} llot2_;

#define llot2_1 llot2_

struct {
    doublereal cford[10200]	/* was [150][68] */;
    integer nds[150], ndd[150];
} lintpl_;

#define lintpl_1 lintpl_

struct {
    doublereal cford2[10200]	/* was [150][68] */;
    integer nds2[150], ndd2[150];
} lintpl2_;

#define lintpl2_1 lintpl2_

struct {
    doublereal zlaol1, zlaol2, zopal1, zopal2, zopal951, zalex1, zkur1, zkur2,
	     tmolmin, tmolmax;
    logical lalex06, llaol89, lopal92, lopal95, lkur90, lalex95, l2z;
} newopac_;

#define newopac_1 newopac_

/* Table of constant values */

static integer c__3 = 3;
static doublereal c_b5 = 10.;



/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */
/* LL4TH */
/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */
/*     THIS IS THE 4TH TABLE OF THE LAWRENCE LIVERMORE OPACITY TABLES. */
/*     IT CONTAINS THE OPACITIES FOR THE SURFACE ABUNDANCES OF X AND Z, AND */
/*     IS USED TO AVOID MANY INTERPOLATIONS TO THE SAME X. */
/* Subroutine */ int ll4th_(doublereal *x)
{
    /* System generated locals */
    integer i__1, i__2, i__3;

    /* Builtin functions */
    /* Subroutine */ int s_stop(char *, ftnlen);
    double pow_dd(doublereal *, doublereal *);

    /* Local variables */
    static doublereal c__[400]	/* was [4][100] */;
    static integer i__, j, m1, m2, m3;
    static doublereal o0, o1, t6, of;
    static integer im2, im3;
    static doublereal ol0, ol1;
    static integer ndf;
    static doublereal olf, qod0, qod1, qot0, qot1;
    static integer ndss;
    static doublereal rhot3, grdnt;
    static integer index1, index2;
    extern /* Subroutine */ int yllo2d_(doublereal *, doublereal *, integer *,
	     integer *, integer *, doublereal *, doublereal *, doublereal *, 
	    doublereal *), findex_(doublereal *, integer *, doublereal *, 
	    integer *), yllo2d2_(doublereal *, doublereal *, integer *, 
	    integer *, integer *, doublereal *, doublereal *, doublereal *, 
	    doublereal *), ysplin_(doublereal *, doublereal *, integer *);

/* MHP 10/02 made array dimensions consistent */
/*      DIMENSION C(4,NUMD) */
/*     OUTPUT OF LL4TH */
/*     GRIDS */
/*     LL OPACITY TABLES */
/*     THE SPLINE COEFFICIENTS AND THE SHAPE OF THE LL TABLE. */
/* OPACITY COMMON BLOCKS - modified 3/09 */
/*     KEEP THE COMPOSITION OF THE 4TH TABLE. */
    llot4_1.xenv4 = *x;
    llot4_1.zenv4 = newopac_1.zopal1;
    findex_(gllot_1.gridx, &c__3, x, &m1);
    if (m1 < 0) {
	m1 = -m1;
    }
    if (m1 >= 3) {
	m1 = 2;
    }
    if (m1 <= 0) {
	s_stop(" ERROR IN X GRID", (ftnlen)16);
    }
    llot4_1.kipm1 = m1;
    i__1 = llot_1.numtm;
    for (im2 = 1; im2 <= i__1; ++im2) {
	m1 = llot4_1.kipm1;
	t6 = gllot_1.gridt[im2 - 1];
	m2 = im2;
	index1 = im2 + (m1 - 1) * llot_1.numtm;
	ndss = lintpl_1.nds[index1 - 1];
	if (ndss != 1) {
	    s_stop(" LL4TH NDSS ", (ftnlen)12);
	}
	ndf = ndss + lintpl_1.ndd[index1 - 1] - 1;
	i__2 = ndf;
	for (im3 = ndss; im3 <= i__2; ++im3) {
	    rhot3 = gllot_1.grhot3[im3 - 1];
	    yllo2d_(&t6, &rhot3, &m1, &m2, &m3, &o0, &ol0, &qod0, &qot0);
	    i__3 = m1 + 1;
	    yllo2d_(&t6, &rhot3, &i__3, &m2, &m3, &o1, &ol1, &qod1, &qot1);
	    grdnt = (*x - gllot_1.gridx[m1 - 1]) / (gllot_1.gridx[m1] - 
		    gllot_1.gridx[m1 - 1]);
	    olf = (ol1 - ol0) * grdnt + ol0;
	    of = pow_dd(&c_b5, &olf);
/*     CONVERSION FROM THE DERIVATIVE WITH CONSTANT RHOT3 TO CONSTANT RHO */
	    c__[(im3 << 2) - 4] = olf;
	}
	ysplin_(gllot_1.grhot3, c__, &ndf);
	i__2 = ndf;
	for (j = 1; j <= i__2; ++j) {
	    for (i__ = 1; i__ <= 4; ++i__) {
		index2 = i__ + (j - 1 << 2);
		llot4_1.cford4[im2 + index2 * 50 - 51] = c__[i__ + (j << 2) - 
			5];
	    }
	}
    }
    if (newopac_1.l2z) {
	llot42_1.xenv42 = *x;
	llot42_1.zenv42 = newopac_1.zopal2;
	findex_(gllot2_1.gridx2, &c__3, x, &m1);
	if (m1 < 0) {
	    m1 = -m1;
	}
	if (m1 >= 3) {
	    m1 = 2;
	}
	if (m1 <= 0) {
	    s_stop(" ERROR IN X GRID", (ftnlen)16);
	}
	llot42_1.kipm12 = m1;
	i__1 = llot2_1.numtm2;
	for (im2 = 1; im2 <= i__1; ++im2) {
	    m1 = llot42_1.kipm12;
	    t6 = gllot2_1.gridt2[im2 - 1];
	    m2 = im2;
	    index1 = im2 + (m1 - 1) * llot2_1.numtm2;
	    ndss = lintpl2_1.nds2[index1 - 1];
	    if (ndss != 1) {
		s_stop(" LL4TH Z1 CHECK NDSS ", (ftnlen)21);
	    }
	    ndf = ndss + lintpl2_1.ndd2[index1 - 1] - 1;
	    i__2 = ndf;
	    for (im3 = ndss; im3 <= i__2; ++im3) {
		rhot3 = gllot2_1.grhot32[im3 - 1];
		yllo2d2_(&t6, &rhot3, &m1, &m2, &m3, &o0, &ol0, &qod0, &qot0);
		i__3 = m1 + 1;
		yllo2d2_(&t6, &rhot3, &i__3, &m2, &m3, &o1, &ol1, &qod1, &
			qot1);
		grdnt = (*x - gllot2_1.gridx2[m1 - 1]) / (gllot2_1.gridx2[m1] 
			- gllot2_1.gridx2[m1 - 1]);
		olf = (ol1 - ol0) * grdnt + ol0;
		of = pow_dd(&c_b5, &olf);
/* CONVERSION FROM THE DERIVATIVE WITH CONSTANT RHOT3 TO CONSTANT RHO */
		c__[(im3 << 2) - 4] = olf;
	    }
	    ysplin_(gllot2_1.grhot32, c__, &ndf);
	    i__2 = ndf;
	    for (j = 1; j <= i__2; ++j) {
		for (i__ = 1; i__ <= 4; ++i__) {
		    index2 = i__ + (j - 1 << 2);
		    llot42_1.cford42[im2 + index2 * 50 - 51] = c__[i__ + (j <<
			     2) - 5];
		}
	    }
	}
    }
    return 0;
} /* ll4th_ */

