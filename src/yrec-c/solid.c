/* solid.f -- translated by f2c (version 20061008).
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
    doublereal toleri;
} errmom_;

#define errmom_1 errmom_

struct {
    integer ilast, idebug, itrack, ishort, imilne, imodpt, istor, iowr;
} luout_;

#define luout_1 luout_

struct {
    doublereal sage, tdisk, pdisk;
    logical ldisk;
} disk_;

#define disk_1 disk_

/* $$$$$$ */
/* SOLID */
/* Subroutine */ int solid_(doublereal *hd, doublereal *hjm, doublereal *hr, 
	doublereal *hs, doublereal *hs2, integer *jstart, integer *jend, 
	doublereal *eta2, doublereal *hi, doublereal *omega, doublereal *qiw, 
	doublereal *r0, integer *m)
{
    /* System generated locals */
    integer i__1;
    doublereal d__1;

    /* Local variables */
    static integer j;
    static doublereal czi, czj, delj;
    static logical lock;
    static doublereal delw;
    extern /* Subroutine */ int momi_(doublereal *, doublereal *, doublereal *
	    , doublereal *, integer *, integer *, doublereal *, doublereal *, 
	    doublereal *, doublereal *);
    static doublereal wsum;
    extern /* Subroutine */ int shape_(doublereal *, doublereal *, doublereal 
	    *, integer *, integer *, doublereal *, doublereal *, doublereal *)
	    ;
    static doublereal czqiw, czjnew;
    static integer icount;
    static doublereal wguess;

/* MHP 9/94 ADDED DISK LOCKING OPTION - FLAG, TIME OVER WHICH LOCKING */
/* IS ENFORCED, AND PERIOD AT WHICH LOCKING IS SET ARE OPTIONS. */
/*  GIVEN THE ANGULAR MOMENTUM PER UNIT MASS, SOLID RETURNS THE ROTATION */
/*  RATE OMEGA.  IT ALSO CALLS MOMI, WHICH CALCULATES THE MOMENT OF INERT */
/*  AND R0 AND ETA2; R0 AND ETA2 ARE NEEDED BY FPFT. */
    /* Parameter adjustments */
    --r0;
    --qiw;
    --omega;
    --hi;
    --eta2;
    --hs2;
    --hs;
    --hr;
    --hjm;
    --hd;

    /* Function Body */
    czj = 0.;
    wsum = 0.;
    icount = 0;
/*  FIND THE TOTAL ANGULAR MOMENTUM OF SHELLS JSTART TO JEND. */
/*  ALSO MAKE A FIRST GUESS AT OMEGA BY AVERAGING THE PREVIOUS VALUES. */
    i__1 = *jend;
    for (j = *jstart; j <= i__1; ++j) {
	czj += hs2[j] * hjm[j];
	wsum += omega[j];
/* L10: */
    }
/* MHP 9/94 OPTION ADDED TO ENFORCE DISK LOCKING UP TO A GIVEN AGE IN */
/* THE SURFACE C.Z. ONLY. */
    lock = FALSE_;
    if (*jend == *m && *jstart != *jend && disk_1.ldisk && disk_1.sage <= 
	    disk_1.tdisk) {
	lock = TRUE_;
    }
    if (! lock) {
	wguess = wsum / (doublereal) (*jend - *jstart + 1);
    } else {
	wguess = disk_1.pdisk;
    }
L20:
    i__1 = *jend;
    for (j = *jstart; j <= i__1; ++j) {
	omega[j] = wguess;
/* L30: */
    }
/*  DETERMINE THE MOMENTS OF INERTIA OF SHELLS JSTART TO JEND WITH OMEGA */
/*  EQUAL TO WGUESS. */
    shape_(&hd[1], &hr[1], &hs[1], jstart, jend, &omega[1], &eta2[1], &r0[1]);
/*       CALL MOMI(ETA2,HD,HR,HS,HS2,JSTART,JEND,OMEGA,R0,HI,QIW,M)  ! KC 2025-05-31 */
    momi_(&eta2[1], &hr[1], &hs[1], &hs2[1], jstart, jend, &omega[1], &r0[1], 
	    &hi[1], &qiw[1]);
    czi = 0.;
    czqiw = 0.;
/*  FIND TOTAL MOMENT OF INERTIA(CZI) AND TOTAL DI/DOMEGA (CZQIW) */
    i__1 = *jend;
    for (j = *jstart; j <= i__1; ++j) {
	czi += hi[j];
	czqiw += qiw[j];
/* L40: */
    }
    czjnew = wguess * czi;
/*  CHECK IF THE TOTAL ANGULAR MOMENTUM FOUND WITH OMEGA = WGUESS IS CLOS */
/*  ENOUGH.  IF NOT, CALCULATE DELTA OMEGA AND TRY AGAIN WITH A NEW WGUES */
    delj = czj - czjnew;
    if (lock) {
	goto L45;
    }
    if ((d__1 = delj / czj, abs(d__1)) > errmom_1.toleri) {
	if (icount < 20) {
	    ++icount;
	    delw = delj / (czi + wguess * czqiw);
	    wguess += delw;
	    goto L20;
	}
    }
L45:
    i__1 = *jend;
    for (j = *jstart; j <= i__1; ++j) {
	hjm[j] = hi[j] * omega[j] / hs2[j];
/* L50: */
    }
    return 0;
} /* solid_ */

