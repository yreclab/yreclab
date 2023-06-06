/* ykoeff.f -- translated by f2c (version 20100827).
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
    doublereal gridt[60];
} gkrz_;

#define gkrz_1 gkrz_

struct {
    doublereal opacity[3000]	/* was [60][50] */, rho[3000]	/* was [60][
	    50] */;
    integer numtm;
} krz_;

#define krz_1 krz_

struct {
    doublereal cford[12000]	/* was [60][200] */;
    integer nds[60], ndd[60];
} intpl2_;

#define intpl2_1 intpl2_

struct {
    doublereal gridt2[60];
} gkrz2_;

#define gkrz2_1 gkrz2_

struct {
    doublereal opacity2[3000]	/* was [60][50] */, rho2[3000]	/* was [60][
	    50] */;
    integer numtm2;
} krz2_;

#define krz2_1 krz2_

struct {
    doublereal cford2[12000]	/* was [60][200] */;
    integer nds2[60], ndd2[60];
} intpl22_;

#define intpl22_1 intpl22_

struct {
    doublereal zlaol1, zlaol2, zopal1, zopal2, zopal951, zalex1, zkur1, zkur2,
	     tmolmin, tmolmax;
    logical lalex06, llaol89, lopal92, lopal95, lkur90, lalex95, l2z;
} newopac_;

#define newopac_1 newopac_



/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */
/* YKOEFF */
/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */
/* YCK 3/91 */
/* Subroutine */ int ykoeff_(void)
{
    /* System generated locals */
    integer i__1, i__2;

    /* Builtin functions */
    double d_lg10(doublereal *);
    /* Subroutine */ int s_stop(char *, ftnlen);

    /* Local variables */
    static doublereal c__[400]	/* was [4][100] */;
    static integer i__, j, id, jd;
    static doublereal xd[50];
    static integer it, idf, ids;
    static doublereal chkd, chko;
    static integer index1, index2;
    extern /* Subroutine */ int ysplin_(doublereal *, doublereal *, integer *)
	    ;

/* MHP 10/02 made array dimensions consistent */
/*      DIMENSION C(4,NUMD),XD(NUMD) */
/* OPACITY COMMON BLOCKS - modified 3/09 */
    i__1 = krz_1.numtm;
    for (it = 1; it <= i__1; ++it) {
	index1 = it;
	jd = 0;
	ids = 1;
	idf = 50;
	i__2 = idf;
	for (id = ids; id <= i__2; ++id) {
	    chkd = krz_1.rho[it + id * 60 - 61];
	    chko = krz_1.opacity[it + id * 60 - 61];
	    if (chko <= 0.) {
		goto L103;
	    }
	    if (jd <= 0) {
		intpl2_1.nds[index1 - 1] = id;
	    }
	    ++jd;
	    xd[jd - 1] = chkd;
	    c__[(jd << 2) - 4] = d_lg10(&chko);
L103:
	    ;
	}
	intpl2_1.ndd[index1 - 1] = jd;
	if (intpl2_1.nds[index1 - 1] != 1) {
	    s_stop(" ERROR KURUCZ OPACITY NDS", (ftnlen)25);
	}
	if (intpl2_1.ndd[index1 - 1] < 25) {
	    s_stop(" ERROR KURUCZ OPACITY NDD", (ftnlen)25);
	}
	if (jd <= 1) {
	    goto L102;
	}
	ysplin_(xd, c__, &jd);
	i__2 = jd;
	for (j = 1; j <= i__2; ++j) {
	    for (i__ = 1; i__ <= 4; ++i__) {
		index2 = i__ + (j - 1 << 2);
		intpl2_1.cford[index1 + index2 * 60 - 61] = c__[i__ + (j << 2)
			 - 5];
	    }
	}
L102:
	;
    }



/* DBG 12/95 second Z table */
    if (newopac_1.l2z) {
	i__1 = krz2_1.numtm2;
	for (it = 1; it <= i__1; ++it) {
	    index1 = it;
	    jd = 0;
	    ids = 1;
	    idf = 50;
	    i__2 = idf;
	    for (id = ids; id <= i__2; ++id) {
		chkd = krz2_1.rho2[it + id * 60 - 61];
		chko = krz2_1.opacity2[it + id * 60 - 61];
		if (chko <= 0.) {
		    goto L203;
		}
		if (jd <= 0) {
		    intpl22_1.nds2[index1 - 1] = id;
		}
		++jd;
		xd[jd - 1] = chkd;
		c__[(jd << 2) - 4] = d_lg10(&chko);
L203:
		;
	    }
	    intpl22_1.ndd2[index1 - 1] = jd;
	    if (intpl22_1.nds2[index1 - 1] != 1) {
		s_stop(" NDS2", (ftnlen)5);
	    }
	    if (intpl22_1.ndd2[index1 - 1] < 25) {
		s_stop(" NDD2", (ftnlen)5);
	    }
	    if (jd <= 1) {
		goto L202;
	    }
	    ysplin_(xd, c__, &jd);
	    i__2 = jd;
	    for (j = 1; j <= i__2; ++j) {
		for (i__ = 1; i__ <= 4; ++i__) {
		    index2 = i__ + (j - 1 << 2);
		    intpl22_1.cford2[index1 + index2 * 60 - 61] = c__[i__ + (
			    j << 2) - 5];
		}
	    }
L202:
	    ;
	}
    }
    return 0;
} /* ykoeff_ */

