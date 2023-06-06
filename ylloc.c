/* ylloc.f -- translated by f2c (version 20100827).
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
    doublereal gridt[50], gridx[3], grhot3[17];
} gllot_;

#define gllot_1 gllot_

struct {
    doublereal opacity[2550]	/* was [150][17] */;
    integer numxm, numtm;
} llot_;

#define llot_1 llot_

struct {
    doublereal cford[10200]	/* was [150][68] */;
    integer nds[150], ndd[150];
} lintpl_;

#define lintpl_1 lintpl_

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



/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */
/* YLLOC */
/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */
/* Subroutine */ int ylloc_(void)
{
    /* System generated locals */
    integer i__1, i__2, i__3;

    /* Builtin functions */
    /* Subroutine */ int s_stop(char *, ftnlen);

    /* Local variables */
    static doublereal c__[400]	/* was [4][100] */;
    static integer i__, j, id, jd;
    static doublereal xd[17];
    static integer it, ix, idf, ids;
    static doublereal chkd, chko;
    static integer index1, index2;
    extern /* Subroutine */ int ysplin_(doublereal *, doublereal *, integer *)
	    ;

/* DBG 5/94 Modified to include ZRAMP and ZDIFF stuff (second opacity table) */
/* MHP 10/02 made array dimensions consistent */
/*      DIMENSION C(4,NUMD),XD(NUMD) */
/* DBG 5/94 different Z tables */
/* OPACITY COMMON BLOCKS - modified 3/09 */
    i__1 = llot_1.numxm;
    for (ix = 1; ix <= i__1; ++ix) {
	i__2 = llot_1.numtm;
	for (it = 1; it <= i__2; ++it) {
	    index1 = it + (ix - 1) * llot_1.numtm;
	    jd = 0;
	    ids = 1;
	    idf = 17;
	    i__3 = idf;
	    for (id = ids; id <= i__3; ++id) {
		chkd = gllot_1.grhot3[id - 1];
		chko = llot_1.opacity[it + (ix - 1) * 50 + id * 150 - 151];
/* >>>> CHECK THE EMPTY REGION */
		if (chko <= -9.999) {
		    goto L3;
		}
		if (jd <= 0) {
		    lintpl_1.nds[index1 - 1] = id;
		    if (id != 1) {
			s_stop(" CHECK NDS ", (ftnlen)11);
		    }
		}
		++jd;
		xd[jd - 1] = chkd;
/* >>>> CHECK THE OPACITY VALUE IN THE TABLE */
		c__[(jd << 2) - 4] = chko;
L3:
		;
	    }
	    lintpl_1.ndd[index1 - 1] = jd;
	    if (jd <= 1) {
		goto L2;
	    }
	    ysplin_(xd, c__, &jd);
	    i__3 = jd;
	    for (j = 1; j <= i__3; ++j) {
		for (i__ = 1; i__ <= 4; ++i__) {
		    index2 = i__ + (j - 1 << 2);
		    lintpl_1.cford[index1 + index2 * 150 - 151] = c__[i__ + (
			    j << 2) - 5];
/* L200: */
		}
/* L100: */
	    }
L2:
	    ;
	}
/* L1: */
    }

/* DBG 5/94 ZRAMP stuff */
    if (newopac_1.l2z) {
	i__1 = llot2_1.numxm2;
	for (ix = 1; ix <= i__1; ++ix) {
	    i__2 = llot2_1.numtm2;
	    for (it = 1; it <= i__2; ++it) {
		index1 = it + (ix - 1) * llot2_1.numtm2;
		jd = 0;
		ids = 1;
		idf = 17;
		i__3 = idf;
		for (id = ids; id <= i__3; ++id) {
		    chkd = gllot2_1.grhot32[id - 1];
		    chko = llot2_1.opacity2[it + (ix - 1) * 50 + id * 150 - 
			    151];
		    if (chko <= -9.999) {
			goto L503;
		    }
		    if (jd <= 0) {
			lintpl2_1.nds2[index1 - 1] = id;
			if (id != 1) {
			    s_stop(" CHECK NDS2 ", (ftnlen)12);
			}
		    }
		    ++jd;
		    xd[jd - 1] = chkd;
		    c__[(jd << 2) - 4] = chko;
L503:
		    ;
		}
		lintpl2_1.ndd2[index1 - 1] = jd;
		if (jd <= 1) {
		    goto L502;
		}
		ysplin_(xd, c__, &jd);
		i__3 = jd;
		for (j = 1; j <= i__3; ++j) {
		    for (i__ = 1; i__ <= 4; ++i__) {
			index2 = i__ + (j - 1 << 2);
			lintpl2_1.cford2[index1 + index2 * 150 - 151] = c__[
				i__ + (j << 2) - 5];
		    }
		}
L502:
		;
	    }
	}
    }
    return 0;
} /* ylloc_ */

