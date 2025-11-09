/* mhdpx1.f -- translated by f2c (version 20061008).
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
    integer ilast, idebug, itrack, ishort, imilne, imodpt, istor, iowr;
} luout_;

#define luout_1 luout_

struct {
    logical ldebug, lcorr, lmilne, ltrack, lstpch;
} ccout2_;

#define ccout2_1 ccout2_

struct {
    doublereal tlim1, tlim2, tmini, tmaxi;
} tttt_;

#define tttt_1 tttt_

struct {
    doublereal varfin[25];
} mhdout_;

#define mhdout_1 mhdout_

/* Table of constant values */

static integer c__8 = 8;
static integer c__9 = 9;
static integer c__1 = 1;
static integer c__5 = 5;



/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */
/* MHDPX1 */
/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */
/* Subroutine */ int mhdpx1_(doublereal *pl, doublereal *tl, doublereal *x)
{
    /* System generated locals */
    doublereal d__1;

    /* Builtin functions */
    integer s_wsle(cilist *), do_lio(integer *, integer *, char *, ftnlen), 
	    e_wsle(void);
    /* Subroutine */ void s_stop(char *, ftnlen);

    /* Local variables */
    static doublereal h__;
    static integer i__, l;
    static doublereal x0, y0, y1, y2;
    static integer id, ii;
    static doublereal xc[8];
    static integer np, iv, ix[4];
    static doublereal xx[4];
    extern /* Subroutine */ int lir_(doublereal *, doublereal *, doublereal *,
	     doublereal *, integer *, integer *, integer *, integer *, 
	    integer *);
    static integer itbl;
    static doublereal vari1[100]	/* was [25][4] */;
    static integer inter, ixmin;
    extern /* Subroutine */ int quint_(doublereal *, doublereal *, doublereal 
	    *, doublereal *, doublereal *, doublereal *, doublereal *), 
	    mhdpx2_(doublereal *, doublereal *, integer *, doublereal *, 
	    doublereal *, integer *);
    static doublereal varout[200]	/* was [8][25] */;

    /* Fortran I/O blocks */
    static cilist io___7 = { 0, 0, 0, 0, 0 };
    static cilist io___8 = { 0, 0, 0, 0, 0 };
    static cilist io___9 = { 0, 0, 0, 0, 0 };
    static cilist io___10 = { 0, 0, 0, 0, 0 };



/*     MHDST MUST BE CALLED IN MAIN. */
/*     INTERPOLATION IN TABLES WITH DIFFERENT X AND FIXED Z */
/*     TL < TLIM1:         LOWER PART OF ZAMS TABLES */
/*     TLIM1 < TL < TLIM2: UPPER PART OF ZAMS TABLES */
/*     TL > TLIM2:         CENTRE TABLES */
/*     TMINI,TMAXI:        TEMPERATURE INTERVAL COVERED */
/*                         BY THE TABLES */

/*     QUANTITIES FOR INTERPOLATION IN X */
/*     OUTPUT */
/*     READ FROM APPROPRIATE TABLES */
/*     AND FILL ARRAYS VAROUT AND XC */
/*     CAN WE DO IT? */

/*     IRANGE = 1 */
    if (*tl < tttt_1.tmini || *tl > tttt_1.tmaxi) {
/*         IRANGE = 0 */
	goto L999;
    }
/*     LOWER ZAMS TABLES */
    if (*tl < tttt_1.tlim1) {
	for (i__ = 1; i__ <= 3; ++i__) {
	    itbl = -i__;
	    mhdpx2_(pl, tl, &itbl, varout, xc, &c__8);
/* L10: */
	}
    } else if (*tl < tttt_1.tlim2) {
/*     UPPER ZAMS TABLES */
	for (i__ = 1; i__ <= 3; ++i__) {
	    itbl = i__;
	    mhdpx2_(pl, tl, &itbl, varout, xc, &c__8);
/* L20: */
	}
    } else {
/*     CENTRE TABLES */
	for (i__ = 1; i__ <= 5; ++i__) {
/*        OFFSET (+3) TO ACCESS CENTER TABLES */
	    itbl = i__ + 3;
	    mhdpx2_(pl, tl, &itbl, varout, xc, &c__8);
/* L30: */
	}
    }
/*     INTERPOLATION IN X */
    if (*tl <= tttt_1.tlim2) {
/*        QUADRATIC NEWTON (EQUIDISTANT XC'S) */
	x0 = xc[0];
	h__ = xc[1] - xc[0];
	if ((d__1 = xc[2] - xc[1] - h__, abs(d__1)) > 1e-4) {
	    io___7.ciunit = luout_1.iowr;
	    s_wsle(&io___7);
	    do_lio(&c__9, &c__1, "ERROR (MHD): NON-EQUIDISTANT ZAMS TABLES.", 
		    (ftnlen)41);
	    e_wsle();
	    io___8.ciunit = luout_1.iowr;
	    s_wsle(&io___8);
	    do_lio(&c__9, &c__1, "XC(1-3)= ", (ftnlen)9);
	    do_lio(&c__5, &c__1, (char *)&xc[0], (ftnlen)sizeof(doublereal));
	    do_lio(&c__5, &c__1, (char *)&xc[1], (ftnlen)sizeof(doublereal));
	    do_lio(&c__5, &c__1, (char *)&xc[2], (ftnlen)sizeof(doublereal));
	    e_wsle();
	    io___9.ciunit = luout_1.ishort;
	    s_wsle(&io___9);
	    do_lio(&c__9, &c__1, "ERROR (MHD): NON-EQUIDISTANT ZAMS TABLES.", 
		    (ftnlen)41);
	    e_wsle();
	    io___10.ciunit = luout_1.ishort;
	    s_wsle(&io___10);
	    do_lio(&c__9, &c__1, "XC(1-3)= ", (ftnlen)9);
	    do_lio(&c__5, &c__1, (char *)&xc[0], (ftnlen)sizeof(doublereal));
	    do_lio(&c__5, &c__1, (char *)&xc[1], (ftnlen)sizeof(doublereal));
	    do_lio(&c__5, &c__1, (char *)&xc[2], (ftnlen)sizeof(doublereal));
	    e_wsle();
	    s_stop("", (ftnlen)0);
	}
/*         IF( ( XC(3).GT.XC(1) .AND. (X.GT.XC(3) .OR. X.LT.XC(1))) */
/*    1                               .OR. */
/*    2       ( XC(3).LT.XC(1) .AND. (X.GT.XC(1) .OR. X.LT.XC(3))) ) */
/*    3   THEN */
/*        END IF */
	for (iv = 1; iv <= 25; ++iv) {
	    y0 = varout[(iv << 3) - 8];
	    y1 = varout[(iv << 3) - 7];
	    y2 = varout[(iv << 3) - 6];
	    quint_(x, &x0, &h__, &y0, &y1, &y2, &mhdout_1.varfin[iv - 1]);
/* L100: */
	}
    } else {
/*     CUBIC LAGRANGIAN (ARBITRARILY SPACED XC'S) */
/*     USE 4 HIGHEST XC(I)'S, IF POSSIBLE. */
/*     DISTINGUISH CASE WHERE THE XC(I), I=4..8, */
/*     INCREASE OR DECREASE. */
	if (xc[3] < xc[7]) {
	    ixmin = 5;
	    if (*x < xc[4]) {
		ixmin = 4;
	    }
	} else {
	    ixmin = 4;
	    if (*x < xc[6]) {
		ixmin = 5;
	    }
	}
	for (i__ = 1; i__ <= 4; ++i__) {
/* KC 2025-05-30 fixed "DO termination statement which is not END DO or CONTINUE" */
/*  200     IX(I)=IXMIN+I-1 */
	    ix[i__ - 1] = ixmin + i__ - 1;
/* L200: */
	}
	for (i__ = 1; i__ <= 4; ++i__) {
/* KC 2025-05-30 fixed "Shared DO termination label" */
/*         XX(I) = XC(IX(I)) */
/*         DO 250 IV=1,IVARX */
/*         VARI1(IV,I) = VAROUT(IX(I),IV) */
	    xx[i__ - 1] = xc[ix[i__ - 1] - 1];
	    for (iv = 1; iv <= 25; ++iv) {
		vari1[iv + i__ * 25 - 26] = varout[ix[i__ - 1] + (iv << 3) - 
			9];
/* L251: */
	    }
/* L250: */
	}
	ii = 25;
	id = 25;
	np = 4;
	l = 1;
	inter = 1;
	lir_(x, xx, mhdout_1.varfin, vari1, &ii, &id, &np, &l, &inter);
    }
L999:
    return 0;
/* 1000  FORMAT(' RESULTS FROM MHDPX2, ITBL,X = ',I6,1PE15.7/) */
/* 1001  FORMAT(12(/1X,1P5E15.6)) */
/* 5001  FORMAT(1X,'******* WARNING: EXTRAPOLATION IN X (QUINT) ', */
/*      1          'PL,TL,X = ',3F12.6) */
/* 5011  FORMAT(1X,'******* WARNING: EXTRAPOLATION IN X (LIR) ', */
/*      1          'PL,TL,X = ',3F12.6) */
/* 9001  FORMAT(' ERROR IN MHDPX1. TL OUT OF RANGE. TL,TMINI,TMAXI=', */
/*      1 /1X,1P3E13.6) */
} /* mhdpx1_ */

