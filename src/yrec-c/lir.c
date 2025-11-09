/* lir.f -- translated by f2c (version 20061008).
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


/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */
/* LIR */
/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */
/* Subroutine */ int lir_0_(int n__, doublereal *z__, doublereal *zi, 
	doublereal *y, doublereal *yi, integer *ii, integer *id, integer *nt, 
	integer *l, integer *inter)
{
    /* Initialized data */

    static integer n = -1;

    /* System generated locals */
    integer i__1, i__2;

    /* Local variables */
    static doublereal a[4];
    static integer i__, j, k, m;
    static doublereal y1, y2, y3, y4, z1, z2, z3, z4;
    static integer il, ir;
    static doublereal z12, z34, yy;
    static integer ir1, ird, iir;
    static doublereal diff;

/*     INTERPOLATION/EXTRAPOLATION ROUTINE */
/*     FOR A SUCH THAT Z=ZI(A),  SETS Y(I)=YI(I,A), I=1,II */
/*     ZI(N),YI(I,N) MUST BE SUPPLIED FOR N=1,NT AND I=1,II */
/*     ID IS FIRST DIMENSION OF YI */
/*     INTER IS SET TO 1 FOR INTERPOLATION AND 0 FOR EXTRAPOLATION */
/*     IF L.LE.1, SCAN TO FIND THE ZI(N) WHICH IMMEDIATELY BOUND Z */
/*                STARTS AT N=1 */
/*     IF L.GT.1, SCAN STARTS FROM VALUE OF N FROM PREVIOUS CALL OF LIR */
/*     LIR USE CUBIC INTERPOLATION/EXTRAPOLATION UNLESS NT.LT.4 */
/*     LIR1 USE LINEAR INTERPOLATION/EXTRAPOLATION */
/*     NOTE */
/*     MOST OF THE COMPUTATION IS PERFORMED IN SINGLE PRECISION */
    /* Parameter adjustments */
    --zi;
    --y;
    --yi;

    /* Function Body */
    switch(n__) {
	case 1: goto L_lir1;
	}


    il = 0;
    goto L1;

L_lir1:
    il = 1;
L1:
    ir = 1;
/*     CHECK NT AND RESET IL IF NECESSARY */
    if (*nt < 2) {
	goto L101;
    }
    if (*nt < 4) {
	il = 1;
    }
/*     ADDRESSING CONSTANTS */
    *inter = 1;
    ir1 = ir - 1;
    ird = ir * *id;
    iir = (*ii - 1) * ir + 1;
    j = (*nt - 1) * ir + 1;
    diff = zi[j] - zi[1];
/*     SET INDEX FOR START OF SEARCH */
    n = (n - 2) * ir + 1;
    if (*l <= 1 || n < 1) {
	n = 1;
    }
/*     DETERMINE POSITION OF Z WITHIN ZI */
L2:
    if (n > j) {
	goto L8;
    }
/* KC 2025-05-30 fixed "Arithmetic IF statement" */
/*       IF(DIFF) 4,102,3 */
/*     3 IF(ZI(N)-Z) 5,6,9 */
/*     4 IF(ZI(N)-Z) 9,6,5 */
    if (diff < 0.f) {
	goto L4;
    } else if (diff == 0.f) {
	goto L102;
    } else {
	goto L3;
    }
L3:
    if (zi[n] < *z__) {
	goto L5;
    } else if (zi[n] == *z__) {
	goto L6;
    } else {
	goto L9;
    }
L4:
    if (zi[n] < *z__) {
	goto L9;
    } else if (zi[n] == *z__) {
	goto L6;
    } else {
	goto L5;
    }
L5:
    n += ir;
    goto L2;
/*     SET Y WHEN Z LIES ON A MESH POINT */
L6:
    j = (n - 1) * *id;
    i__1 = iir;
    for (i__ = 1; i__ <= i__1; ++i__) {
/* KC 2025-05-30 fixed "DO termination statement which is not END DO or CONTINUE" */
/*       Y(I)=YI(I+J) */
/*     7 IF(Y(I).EQ.0.D0) Y(I+IR1)=0.D0 */
	y[i__] = yi[i__ + j];
	if (y[i__] == 0.) {
	    y[i__ + ir1] = 0.;
	}
/* L7: */
    }
    goto L30;
/*     CONTROL WHEN Z DOES NOT LIE ON A MESH POINT */
L8:
    *inter = 0;
L9:
    if (n <= 1) {
	*inter = 0;
    }
    if (il == 1) {
	goto L20;
    }
/*     CUBIC INTERPOLATION/EXTRAPOLATION */
/*     PIVOTAL POINT (M) AND POINT (K) CLOSEST TO Z */
/*    10 M=N */
    m = n;
    k = 3;
    if (n > ir + 1) {
	goto L11;
    }
    m = ir + 1 + ir;
    k = n;
L11:
    if (n < j) {
	goto L12;
    }
    m = j - ir;
    k = 4;
/*     WEIGHTING FACTORS */
L12:
    y1 = zi[m - (ir << 1)];
    y2 = zi[m - ir];
    y3 = zi[m];
    y4 = zi[m + ir];
    z1 = *z__ - y1;
    z2 = *z__ - y2;
    z3 = *z__ - y3;
    z4 = *z__ - y4;
/*    13 Z12=Z1*Z2 */
    z12 = z1 * z2;
    z34 = z3 * z4;
/*    14 A(1)=Z2*Z34/((Y1-Y2)*(Y1-Y3)*(Y1-Y4)) */
    a[0] = z2 * z34 / ((y1 - y2) * (y1 - y3) * (y1 - y4));
    a[1] = z1 * z34 / ((y2 - y1) * (y2 - y3) * (y2 - y4));
    a[2] = z12 * z4 / ((y3 - y1) * (y3 - y2) * (y3 - y4));
    a[3] = z12 * z3 / ((y4 - y1) * (y4 - y2) * (y4 - y3));
/*     CORRECT A(K) */
/*    15 DIFF=A(1)+A(2)+A(3)+A(4) */
    diff = a[0] + a[1] + a[2] + a[3];
    a[k - 1] = a[k - 1] + 1. - diff;
/*     COMPUTE Y */
/*    16 M=(M-1)/IR-3 */
    m = (m - 1) / ir - 3;
    m *= ird;
    i__1 = iir;
    for (i__ = 1; i__ <= i__1; ++i__) {
/* KC 2025-05-30 fixed "DO termination statement which is not END DO or CONTINUE" */
/*       K=I+M */
/*       YY=0.D0 */
/*       DO 17 J=1,4 */
/*       K=K+IRD */
/*       DIFF=YI(K) */
/*    17 YY=YY+A(J)*DIFF */
/*       Y(I)=YY */
/*    18 IF(Y(I).EQ.0.D0) Y(I+IR1)=0.D0 */
	k = i__ + m;
	yy = 0.;
	for (j = 1; j <= 4; ++j) {
	    k += ird;
	    diff = yi[k];
	    yy += a[j - 1] * diff;
/* L17: */
	}
	y[i__] = yy;
	if (y[i__] == 0.) {
	    y[i__ + ir1] = 0.;
	}
/* L18: */
    }
    goto L30;
/*     LINEAR INTERPOLATION/EXTRAPOLATION */
L20:
    if (n == 1) {
	n = ir + 1;
    }
    if (n > j) {
	n = j;
    }
    z1 = zi[n];
    y1 = (z1 - *z__) / (z1 - zi[n - ir]);
    y2 = 1. - y1;
    j = (n - 1) * *id;
    m = j - ird;
    i__1 = iir;
    i__2 = ir;
    for (i__ = 1; i__2 < 0 ? i__ >= i__1 : i__ <= i__1; i__ += i__2) {
/* KC 2025-05-30 fixed "DO termination statement which is not END DO or CONTINUE" */
/*       Y(I)=Y1*YI(I+M)+Y2*YI(I+J) */
/*    21 IF(Y(I).EQ.0.D0) Y(I+IR1)=0.D0 */
	y[i__] = y1 * yi[i__ + m] + y2 * yi[i__ + j];
	if (y[i__] == 0.) {
	    y[i__ + ir1] = 0.;
	}
/* L21: */
    }
/*     RESET N */
L30:
    n = (n + ir - 1) / ir;
    return 0;
/*     DIAGNOSTICS */
L101:
    return 0;
L102:
    return 0;
/*  1001 FORMAT(/1X,10('*'),5X,'THERE ARE FEWER THAN TWO DATA POINTS IN', */
/*      *      ' LIR     NT =',I4,5X,10('*')/) */
/*  1002 FORMAT(/1X,10('*'),5X,'EXTREME VALUES OF INDEPENDENT VARIABLE', */
/*      *      ' EQUAL IN LIR',5X,10('*')/16X,'ZI(1) =',1PE13.5,',   ', */
/*      *       'ZI(',I4,') =',1PE13.5/) */
} /* lir_ */

/* Subroutine */ int lir_(doublereal *z__, doublereal *zi, doublereal *y, 
	doublereal *yi, integer *ii, integer *id, integer *nt, integer *l, 
	integer *inter)
{
    return lir_0_(0, z__, zi, y, yi, ii, id, nt, l, inter);
    }

/* Subroutine */ int lir1_(doublereal *z__, doublereal *zi, doublereal *y, 
	doublereal *yi, integer *ii, integer *id, integer *nt, integer *l, 
	integer *inter)
{
    return lir_0_(1, z__, zi, y, yi, ii, id, nt, l, inter);
    }

