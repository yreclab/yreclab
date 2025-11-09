/* mhdst1.f -- translated by f2c (version 20061008).
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
    logical ldebug, lcorr, lmilne, ltrack, lstpch;
} ccout2_;

#define ccout2_1 ccout2_

/* Table of constant values */

static integer c__1 = 1;



/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */
/* MHDST1 */
/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */
/* Subroutine */ int mhdst1_(integer *ir, integer *idx, integer *nt1m, 
	integer *nr1m, integer *ivar1, integer *nt2m, integer *nr2m, integer *
	ivar2, integer *nchem0, integer *nt1, integer *nr1, integer *nt2, 
	integer *nr2, doublereal *tlog1, doublereal *tlog2, doublereal *
	tdvar1, doublereal *tdvar2, doublereal *drh1, doublereal *drh2, 
	integer *nchem, doublereal *atwt, doublereal *abun, doublereal *
	abfrcs, doublereal *gasmu, doublereal *tlogd, doublereal *tlogu, 
	doublereal *tddif0, doublereal *tddifd, doublereal *tddifu, 
	doublereal *atwd, doublereal *atwu, doublereal *abud, doublereal *
	abuu, doublereal *abfrcd, doublereal *abfrcu)
{
    /* System generated locals */
    integer tdvar1_dim1, tdvar1_dim2, tdvar1_offset, tdvar2_dim1, tdvar2_dim2,
	     tdvar2_offset, tddif0_dim1, tddif0_dim2, tddif0_offset, 
	    tddifd_dim1, tddifd_dim2, tddifd_offset, tddifu_dim1, tddifu_dim2,
	     tddifu_offset, i__1, i__2, i__3;
    doublereal d__1, d__2, d__3, d__4;

    /* Builtin functions */
    integer s_rsue(cilist *), do_uio(integer *, char *, ftnlen), e_rsue(void);
    /* Subroutine */ void s_stop(char *, ftnlen);

    /* Local variables */
    static integer m, n, ic, jt, iv;
    static doublereal ddx;
    extern /* Subroutine */ int rtab_(integer *, integer *, integer *, 
	    integer *, integer *, integer *, doublereal *, doublereal *), 
	    rabu_(integer *, integer *, integer *, doublereal *, doublereal *,
	     doublereal *, doublereal *);
    static integer iidx, idxr;
    static doublereal gasxd, cxlim;
    static integer ivarr;
    static doublereal gasxu;
    static integer ifiles, iresco, irescr;

    /* Fortran I/O blocks */
    static cilist io___3 = { 0, 0, 1, 0, 0 };
    static cilist io___11 = { 0, 0, 0, 0, 0 };


    /* Parameter adjustments */
    --tlog1;
    tdvar1_dim1 = *nt1m;
    tdvar1_dim2 = *nr1m;
    tdvar1_offset = 1 + tdvar1_dim1 * (1 + tdvar1_dim2);
    tdvar1 -= tdvar1_offset;
    --tlogu;
    --tlogd;
    --tlog2;
    tddifu_dim1 = *nt2m;
    tddifu_dim2 = *nr2m;
    tddifu_offset = 1 + tddifu_dim1 * (1 + tddifu_dim2);
    tddifu -= tddifu_offset;
    tddifd_dim1 = *nt2m;
    tddifd_dim2 = *nr2m;
    tddifd_offset = 1 + tddifd_dim1 * (1 + tddifd_dim2);
    tddifd -= tddifd_offset;
    tddif0_dim1 = *nt2m;
    tddif0_dim2 = *nr2m;
    tddif0_offset = 1 + tddif0_dim1 * (1 + tddif0_dim2);
    tddif0 -= tddif0_offset;
    tdvar2_dim1 = *nt2m;
    tdvar2_dim2 = *nr2m;
    tdvar2_offset = 1 + tdvar2_dim1 * (1 + tdvar2_dim2);
    tdvar2 -= tdvar2_offset;
    --abfrcu;
    --abfrcd;
    --abuu;
    --abud;
    --atwu;
    --atwd;
    --abfrcs;
    --abun;
    --atwt;

    /* Function Body */
    if (*idx == 0) {
	ifiles = 1;
    } else {
	ifiles = 3;
    }
    i__1 = ifiles;
    for (iidx = 1; iidx <= i__1; ++iidx) {
/*     READ(IR,98,END=1000) IVARR,IDXR,IRESCR,DDX */
	io___3.ciunit = *ir;
	i__2 = s_rsue(&io___3);
	if (i__2 != 0) {
	    goto L1000;
	}
	i__2 = do_uio(&c__1, (char *)&ivarr, (ftnlen)sizeof(integer));
	if (i__2 != 0) {
	    goto L1000;
	}
	i__2 = do_uio(&c__1, (char *)&idxr, (ftnlen)sizeof(integer));
	if (i__2 != 0) {
	    goto L1000;
	}
	i__2 = do_uio(&c__1, (char *)&irescr, (ftnlen)sizeof(integer));
	if (i__2 != 0) {
	    goto L1000;
	}
	i__2 = do_uio(&c__1, (char *)&ddx, (ftnlen)sizeof(doublereal));
	if (i__2 != 0) {
	    goto L1000;
	}
	i__2 = e_rsue();
	if (i__2 != 0) {
	    goto L1000;
	}
	if (*ivar1 < ivarr) {
	    s_stop("", (ftnlen)0);
	}
	if (*idx != idxr) {
	    s_stop("", (ftnlen)0);
	}
	if (iidx == 1) {
	    iresco = 0;
	} else if (iidx == 2) {
	    iresco = -1;
	} else if (iidx == 3) {
	    iresco = 1;
	}
	if (iresco != irescr) {
	    s_stop("", (ftnlen)0);
	}
	if (iidx == 1) {
	    rabu_(ir, nchem0, nchem, &atwt[1], &abun[1], &abfrcs[1], gasmu);
	}
	if (iidx == 2) {
	    rabu_(ir, nchem0, nchem, &atwd[1], &abud[1], &abfrcd[1], &gasxd);
	}
	if (iidx == 3) {
	    rabu_(ir, nchem0, nchem, &atwu[1], &abuu[1], &abfrcu[1], &gasxu);
	}
/*     READ(IR,1001) NT1,NT2,DRH1,DRH2 */
	io___11.ciunit = *ir;
	s_rsue(&io___11);
	do_uio(&c__1, (char *)&(*nt1), (ftnlen)sizeof(integer));
	do_uio(&c__1, (char *)&(*nt2), (ftnlen)sizeof(integer));
	do_uio(&c__1, (char *)&(*drh1), (ftnlen)sizeof(doublereal));
	do_uio(&c__1, (char *)&(*drh2), (ftnlen)sizeof(doublereal));
	e_rsue();
	if (*idx == 1 && *nt1 != 0) {
	    s_stop("", (ftnlen)0);
	}
	if (*nt1 > 0) {
	    rtab_(ir, nt1m, nr1m, ivar1, nt1, nr1, &tlog1[1], &tdvar1[
		    tdvar1_offset]);
	}
	if (*idx == 1) {
	    if (iidx == 1) {
		rtab_(ir, nt2m, nr2m, ivar1, nt2, nr2, &tlog2[1], &tddif0[
			tddif0_offset]);
	    }
	    if (iidx == 2) {
		rtab_(ir, nt2m, nr2m, ivar1, nt2, nr2, &tlogd[1], &tddifd[
			tddifd_offset]);
	    }
	    if (iidx == 3) {
		rtab_(ir, nt2m, nr2m, ivar1, nt2, nr2, &tlogu[1], &tddifu[
			tddifu_offset]);
	    }
	} else if (*idx == 0) {
	    rtab_(ir, nt2m, nr2m, ivar2, nt2, nr2, &tlog2[1], &tdvar2[
		    tdvar2_offset]);
	}
/* L400: */
    }
    if (*idx == 0) {
	goto L450;
    }
/*     IF IDX=1: CHECK TABLES FOR CORRECT COMPOSITION CONSTRUCTION */
/*     AND PERFORM NUMERICAL DERIVATIVES W.R.T. X */
    cxlim = abs(ddx) * .05;
    if ((d__1 = abfrcs[1] - abfrcd[1] - ddx, abs(d__1)) > cxlim || (d__2 = 
	    abfrcs[1] - abfrcu[1] + ddx, abs(d__2)) > cxlim || (d__3 = abfrcs[
	    2] - abfrcd[2] + ddx, abs(d__3)) > cxlim || (d__4 = abfrcs[2] - 
	    abfrcu[2] - ddx, abs(d__4)) > cxlim) {
	goto L500;
    }
    i__1 = *nchem;
    for (ic = 3; ic <= i__1; ++ic) {
	if ((d__1 = abfrcs[ic] - abfrcu[ic], abs(d__1)) > cxlim) {
	    goto L500;
	}
	if ((d__1 = abfrcs[ic] - abfrcd[ic], abs(d__1)) > cxlim) {
	    goto L500;
	}
/* L420: */
    }
    i__1 = *nt2;
    for (jt = 1; jt <= i__1; ++jt) {
	if (tlog2[jt] != tlogd[jt]) {
	    goto L600;
	}
	if (tlog2[jt] != tlogu[jt]) {
	    goto L600;
	}
/* L430: */
    }
/*     NUMERICAL DERIVATIVES W.R.T. X */
    i__1 = *nt2;
    for (n = 1; n <= i__1; ++n) {
/* KC 2025-05-30 fixed "Shared DO termination label" */
/*       DO 440 M =1,NR2 */
	i__2 = *nr2;
	for (m = 1; m <= i__2; ++m) {
	    i__3 = *ivar1;
	    for (iv = 1; iv <= i__3; ++iv) {
/* KC 2025-05-30 fixed "DO termination statement which is not END DO or CONTINUE" */
/* 435   TDVAR2(N,M,IV)=TDDIF0(N,M,IV) */
		tdvar2[n + (m + iv * tdvar2_dim2) * tdvar2_dim1] = tddif0[n + 
			(m + iv * tddif0_dim2) * tddif0_dim1];
/* L435: */
	    }

/*     EXTENDED SET OF VARIABLES (TDVAR2(N,M,IVAR1+1...IVAR2)) */
/*     FOR T-RHO REGIONS WITH INHOMOGENEOUS COMPOSITION. */
/*     IN THE COMMENTS,R AND T DENOTE LOG10(RHO) AND LOG10(T). */
/*     DLOG10(P)/DX,DLOG10(U)/DX,DDELAD/DX,DLOG10(CP)/DX */
	    tdvar2[n + (m + tdvar2_dim2 * 21) * tdvar2_dim1] = (tddifu[n + (m 
		    + (tddifu_dim2 << 1)) * tddifu_dim1] - tddifd[n + (m + (
		    tddifd_dim2 << 1)) * tddifd_dim1]) / (ddx * 2.);
	    tdvar2[n + (m + tdvar2_dim2 * 22) * tdvar2_dim1] = (tddifu[n + (m 
		    + tddifu_dim2 * 3) * tddifu_dim1] - tddifd[n + (m + 
		    tddifd_dim2 * 3) * tddifd_dim1]) / (ddx * 2.);
	    tdvar2[n + (m + tdvar2_dim2 * 23) * tdvar2_dim1] = (tddifu[n + (m 
		    + (tddifu_dim2 << 3)) * tddifu_dim1] - tddifd[n + (m + (
		    tddifd_dim2 << 3)) * tddifd_dim1]) / (ddx * 2.);
	    tdvar2[n + (m + tdvar2_dim2 * 24) * tdvar2_dim1] = (tddifu[n + (m 
		    + tddifu_dim2 * 9) * tddifu_dim1] - tddifd[n + (m + 
		    tddifd_dim2 * 9) * tddifd_dim1]) / (ddx * 2.);
/*     SPACE-HOLDER VARIABLE (LIKE VAR(20)) */
	    tdvar2[n + (m + tdvar2_dim2 * 25) * tdvar2_dim1] = 8888844444.;
/* L441: */
	}
/* L440: */
    }
/*     NORMAL EXIT */
L450:
    return 0;
/*     ERROR EXIT AND ERROR MESSAGES */
L500:
    s_stop("", (ftnlen)0);
L600:
    s_stop("", (ftnlen)0);
L1000:
    s_stop("", (ftnlen)0);
/*  98   FORMAT(1X,3I5,F13.5) */
/*  99   FORMAT(1X,I5,(/1X,3E15.7)) */
/* 1001  FORMAT(2I5,2F10.6) */
/* 8001  FORMAT(' CORRECT TABLE CONSTRUCTION FOR X-DERIVATIVES.', */
/*      1       ' CENTROID COMPOSITION IS:'//) */
/* 8002  FORMAT('      AT. WEIGHT     NUMBER ', */
/*      1 'ABUNDANCE  MASS FRACTION',(/1X,1P3G16.7)) */
/* 8003  FORMAT(/' MEAN MOLECULAR WEIGHT = ',F12.7//) */
/* 9006  FORMAT(' ERROR IN MHDST1. IVARR READ FROM TABLE IS', */
/*      1 ' BIGGER THAN THE VALUE USED IN THE COMMONS.', */
/*      2 ' IVAR,IVARR= ',/1X,2I8) */
/* 9007  FORMAT(' ERROR IN MHDST1. IDXR READ FROM TABLE IS INCORRECT', */
/*      1 ' IDX,IDXR= ',/1X,2I8) */
/* 9008  FORMAT(' ERROR IN MHDST1. IRESCR READ FROM TABLE IS INCORRECT', */
/*      1 ' IRESCO,IRESCR= ',/1X,2I8) */
/* 9010  FORMAT(' ERROR IN MHDST1. NT1 AND IDX ARE INCONSISTENT', */
/*      1 ' IDX,NT1,NT2 ',/1X,3I8) */
/* 9800  FORMAT(' ERROR IN TABLE CONSTRUCTION FOR X-DERIVATIVES', */
/*      1       ' CENTRAL, LOWER, UPPER TABLE: N(ELEMENT),ABFRCS(N)'//) */
/* 9810  FORMAT(1X,I5,F15.9) */
/* 9820  FORMAT(/) */
/* 9850  FORMAT(' ERROR IN TABLE CONSTRUCTION FOR X-DERIVATIVES:', */
/*      1       ' TEMPERATURES WRONG: J,TLOW(J),TCENT(J),TUPP(J)'//) */
/* 9860  FORMAT(1X,I5,3F15.9) */
/* 9900  FORMAT(' EOF REACHED IN INPUT FILE. ERROR STOP. IR,IDX = ',2I5) */
    return 0;
} /* mhdst1_ */

