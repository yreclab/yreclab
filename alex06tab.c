/* alex06tab.f -- translated by f2c (version 20100827).
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
    doublereal tgr06[85], xxg06[9], r0gr06[19], zzg06[16];
} galot06_;

#define galot06_1 galot06_

struct {
    doublereal capalex06[1615]	/* was [85][19] */, xe, ze;
    integer ix, it, id;
} alot06_;

#define alot06_1 alot06_

struct {
    doublereal captalex06[230945]	/* was [143][85][19] */;
} alot06all_;

#define alot06all_1 alot06all_

/* Table of constant values */

static integer c__1 = 1;

/*  SUBROUTINE FOR GENERATING SURFACE X AND Z TABLES FOR ALEXANDER OPACITIES */
/* Subroutine */ int alex06tab_(void)
{
    /* Format strings */
    static char fmt_5[] = "(\002ILLEGAL COMPOSITION (X,Z) = \002,2f6.2,\002 "
	    "IN ALEX06.RUN STOPPED\002)";

    /* Builtin functions */
    integer s_wsfe(cilist *), do_fio(integer *, char *, ftnlen), e_wsfe(void);
    /* Subroutine */ int s_stop(char *, ftnlen);

    /* Local variables */
    static integer i__, j, k;
    static doublereal x;
    static integer kk;
    static doublereal fx[4], qr[4];
    static integer iz, kk2, kk3, kk4;
    static doublereal xmax, zmax;
    extern /* Subroutine */ int intrp2_(doublereal *, doublereal *, 
	    doublereal *);
    static doublereal captemp[6460]	/* was [4][85][19] */;

    /* Fortran I/O blocks */
    static cilist io___2 = { 0, 6, 0, fmt_5, 0 };
    static cilist io___4 = { 0, 6, 0, fmt_5, 0 };


/*  XE = DESIRED X; ZE = DESIRED Z */
    xmax = 1. - alot06_1.ze;
/* CHECK THAT THE REQUESTED COMPOSITION IS INSIDE TABLE BOUNDS */
    if (alot06_1.xe < 0. || alot06_1.xe > xmax) {
	s_wsfe(&io___2);
	do_fio(&c__1, (char *)&alot06_1.xe, (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&alot06_1.ze, (ftnlen)sizeof(doublereal));
	e_wsfe();
	s_stop("", (ftnlen)0);
    }
/* PERMIT EXTRAPOLATION IN Z BY UP TO 1 TABLE ELEMENT */
    zmax = galot06_1.zzg06[15] + (galot06_1.zzg06[15] - galot06_1.zzg06[14]);
    if (alot06_1.ze < 0. || alot06_1.ze > zmax) {
	s_wsfe(&io___4);
	do_fio(&c__1, (char *)&alot06_1.xe, (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&alot06_1.ze, (ftnlen)sizeof(doublereal));
	e_wsfe();
	s_stop("", (ftnlen)0);
    }
/* FIND 4 NEAREST TABLES IN Z. */
    for (i__ = 3; i__ <= 14; ++i__) {
	if (alot06_1.ze <= galot06_1.zzg06[i__ - 1]) {
	    iz = i__ - 2;
	    goto L7;
	}
    }
    iz = 13;
L7:
/* FIND 4 NEAREST TABLES IN X. */
    for (i__ = 3; i__ <= 7; ++i__) {
	if (alot06_1.xe <= galot06_1.xxg06[i__ - 1]) {
	    alot06_1.ix = i__ - 2;
	    goto L10;
	}
    }
/* NO TABLE FOR X > 0.9 IF Z =0.10 OR MORE */
    if (alot06_1.ze >= .1) {
	alot06_1.ix = 5;
    } else {
	alot06_1.ix = 6;
    }
L10:
/* INTERPOLATION FACTORS FOR Z */
    for (i__ = 1; i__ <= 4; ++i__) {
	qr[i__ - 1] = galot06_1.zzg06[iz + i__ - 2];
    }
/*      WRITE(*,*)ZE,(QR(I),I=1,4) */
    x = alot06_1.ze;
    intrp2_(qr, fx, &x);
/* THE DIFFERENCE IN THE NUMBER OF TABLES FOR THE Z=0.1 CASE REQUIRES SOME */
/* CARE IN X INTERPOLATION.  FIRST 3 X CASES CAN BE TREATED NORMALLY. */
    for (k = 1; k <= 3; ++k) {
	kk = (alot06_1.ix + k - 2 << 4) + iz;
	kk2 = kk + 1;
	kk3 = kk2 + 1;
	kk4 = kk3 + 1;
	for (i__ = 1; i__ <= 85; ++i__) {
	    for (j = 1; j <= 19; ++j) {
		captemp[k + (i__ + j * 85 << 2) - 345] = fx[0] * 
			alot06all_1.captalex06[kk + (i__ + j * 85) * 143 - 
			12299] + fx[1] * alot06all_1.captalex06[kk2 + (i__ + 
			j * 85) * 143 - 12299] + fx[2] * 
			alot06all_1.captalex06[kk3 + (i__ + j * 85) * 143 - 
			12299] + fx[3] * alot06all_1.captalex06[kk4 + (i__ + 
			j * 85) * 143 - 12299];
	    }
	}
    }
/* IF IN THE HIGH Z AND HIGH X DOMAIN THE TOP TABLE IS X = 1-Z (ENTRY NUMX) EXCEPT */
/* FOR THE Z=0.10 CASE (WHERE THE X=0.9 CASE DOUBLES AS THE X=1-Z CASE). */
    if (alot06_1.ix == 6 && iz == 13) {
/* USE DIFFERENT INDEXING FOR THE LAST TABLE */
	kk = (alot06_1.ix + 2 << 4) + iz;
	kk2 = kk + 1;
	kk3 = kk2 + 1;
	kk4 = alot06_1.ix + 2 << 4;
    } else {
	kk = (alot06_1.ix + 2 << 4) + iz;
	kk2 = kk + 1;
	kk3 = kk2 + 1;
	kk4 = kk3 + 1;
    }
    for (i__ = 1; i__ <= 85; ++i__) {
	for (j = 1; j <= 19; ++j) {
	    captemp[(i__ + j * 85 << 2) - 341] = fx[0] * 
		    alot06all_1.captalex06[kk + (i__ + j * 85) * 143 - 12299] 
		    + fx[1] * alot06all_1.captalex06[kk2 + (i__ + j * 85) * 
		    143 - 12299] + fx[2] * alot06all_1.captalex06[kk3 + (i__ 
		    + j * 85) * 143 - 12299] + fx[3] * alot06all_1.captalex06[
		    kk4 + (i__ + j * 85) * 143 - 12299];
	}
    }
/* NOW DO X INTERPOLATION */
/* INTERPOLATION FACTORS FOR X */
    for (i__ = 1; i__ <= 3; ++i__) {
	qr[i__ - 1] = galot06_1.xxg06[alot06_1.ix + i__ - 2];
    }
    if (iz == 13) {
	qr[3] = 1. - alot06_1.ze;
    } else {
	qr[3] = galot06_1.xxg06[alot06_1.ix + 2];
    }
    x = alot06_1.xe;
    intrp2_(qr, fx, &x);
/*      WRITE(*,*)XE,(QR(I),I=1,4) */
    for (i__ = 1; i__ <= 85; ++i__) {
	for (j = 1; j <= 19; ++j) {
	    alot06_1.capalex06[i__ + j * 85 - 86] = fx[0] * captemp[(i__ + j *
		     85 << 2) - 344] + fx[1] * captemp[(i__ + j * 85 << 2) - 
		    343] + fx[2] * captemp[(i__ + j * 85 << 2) - 342] + fx[3] 
		    * captemp[(i__ + j * 85 << 2) - 341];
	}
    }
/*      WRITE(*,*)TGR06(NUMT),R0GR06(NUMD),CAPALEX06(NUMT,NUMD) */
    return 0;
} /* alex06tab_ */

