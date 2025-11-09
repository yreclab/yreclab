/* meval.f -- translated by f2c (version 20061008).
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

/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */
/* MEVAL */
/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */
/* Subroutine */ int meval_(doublereal *xval, doublereal *yval, doublereal *
	xtab, doublereal *ytab, doublereal *mtab, integer *num, integer *nume,
	 doublereal *eps, integer *err)
{
    /* System generated locals */
    integer i__1;

    /* Local variables */
    static integer i__;
    static doublereal e1, e2, v1, v2, w1, w2, z1, z2, y1, y2;
    static integer end, fnd, ind, lcn, end1, lcn1, num1, nume1, ncase;
    extern /* Subroutine */ int cases_(doublereal *, doublereal *, doublereal 
	    *, doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, integer *);
    static integer start, start1;
    extern /* Subroutine */ int search_(doublereal *, integer *, doublereal *,
	     integer *, integer *), choose_(doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, integer *);
    extern doublereal spline_(doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, integer *);


/*                                 SHAPE PRESERVING QUADRATIC SPLINES */
/*                                   BY D.F.MCALLISTER & J.A.ROULIER */
/*                                     CODED BY S.L.DOOD & M.ROULIER */
/*                                       N.C. STATE UNIVERSITY */


/* MEVAL CONTROLS THE EVALUATION OF AN OSCULATORY QUADRATIC SPLINE. THE */
/* USER MAY PROVIDE HIS OWN SLOPES AT THE POINTS OF INTERPOLATION OR USE */
/* THE SUBROUTINE 'SLOPES' TO CALCULATE SLOPES WHICH ARE CONSISTENT WITH */
/* THE SHAPE OF THE DATA. */



/* ON INPUT-- */

/*   XVAL MUST BE A NONDECREASING VECTOR OF POINTS AT WHICH THE SPLINE */
/*   WILL BE EVALUATED. */

/*   XTAB CONTAINS THE ABSCISSAS OF THE DATA POINTS TO BE INTERPOLATED. */
/*   XTAB MUST BE INCREASING. */

/*   YTAB CONTAINS THE ORDINATES OF THE DATA POINTS TO BE INTERPOLATED. */

/*   MTAB CONTAINS THE SLOPE OF THE SPLINE AT EACH POINT OF INTERPOLA- */
/*   TION. */

/*   NUM IS THE NUMBER OF DATA POINTS (DIMENSION OF XTAB AND YTAB). */

/*   NUME IS THE NUMBER OF POINTS OF EVALUATION (DIMENSION OF XVAL AND */
/*   YVAL). */

/*   EPS IS A RELATIVE ERROR TOLERANCE USED IN SUBROUTINE 'CHOOSE' */
/*   TO DISTINGUISH THE SITUATION MTAB(I) OR MTAB(I+1) IS RELATIVELY */
/*   CLOSE TO THE SLOPE OR TWICE THE SLOPE OF THE LINEAR SEGMENT */
/*   BETWEEN XTAB(I) AND XTAB(I+1). IF THIS SITUATION OCCURS, */
/*   ROUNDOFF MAY CAUSE A CHANGE IN CONVEXITY OR MONOTONICITY OF THE */
/*   RESULTING SPLINE AND A CHANGE IN THE CASE NUMBER PROVIDED BY */
/*   CHOOSE. IF EPS IS NOT EQUAL TO ZERO, THEN EPS SHOULD BE GREATER */
/*   THAN OR EQUAL TO MACHINE EPSILON. */


/* ON OUTPUT-- */

/*   YVAL CONTAINS THE IMAGES OF THE POINTS IN XVAL. */

/*   ERR IS AN ERROR CODE-- */
/*   ERR=0 - MEVAL RAN NORMALLY. */
/*   ERR=1 - XVAL(I) IS LESS THAN XTAB(1) FOR AT LEAST ONE I OR */
/*           XVAL(I) IS GREATER THAN XTAB(NUM) FOR AT LEAST ONE I. */
/*           MEVAL WILL EXTRAPOLATE TO PROVIDE FUNCTION VALUES FOR */
/*           THESE ABSCISSAS. */
/*   ERR=2 - XVAL(I+1) .LT. XVAL(I) FOR SOME I. */

/* AND */

/*   MEVAL DOES NOT ALTER XVAL,XTAB,YTAB,MTAB,NUM,NUME. */


/*   MEVAL CALLS THE FOLLOWING SUBROUTINES OR FUNCTIONS: */
/*      SEARCH */
/*      CASES */
/*      CHOOSE */
/*      SPLINE */

/* --------------------------------------------------------------------- */

    /* Parameter adjustments */
    --mtab;
    --ytab;
    --xtab;
    --yval;
    --xval;

    /* Function Body */
    start = 1;
    end = *nume;
    *err = 0;
    if (*nume == 1) {
	goto L20;
    }

/* DETERMINE IF XVAL IS NONDECREASING. */
    nume1 = *nume - 1;
    i__1 = nume1;
    for (i__ = 1; i__ <= i__1; ++i__) {
	if (xval[i__ + 1] >= xval[i__]) {
	    goto L10;
	}
	*err = 2;
	goto L230;
L10:
	;
    }


/* IF XVAL(I) .LT. XTAB(1), THEN XVAL(I)=YTAB(1). */
/* IF XVAL(I) .GT. XTAB(NUM), THEN XVAL(I)=YTAB(NUM). */

/* DETERMINE IF ANY OF THE POINTS IN XVAL ARE LESS THAN THE ABSCISSA OF */
/* THE FIRST DATA POINT. */
L20:
    i__1 = *nume;
    for (i__ = 1; i__ <= i__1; ++i__) {
	if (xval[i__] >= xtab[1]) {
	    goto L40;
	}
	start = i__ + 1;
/* L30: */
    }


L40:
    nume1 = *nume + 1;

/* DETERMINE IF ANY OF THE POINTS IN XVAL ARE GREATER THAN THE ABSCISSA */
/* OF THE LAST DATA POINT. */
    i__1 = *nume;
    for (i__ = 1; i__ <= i__1; ++i__) {
	ind = nume1 - i__;
	if (xval[ind] <= xtab[*num]) {
	    goto L60;
	}
	end = ind - 1;
/* L50: */
    }


/* CALCULATE THE IMAGES OF POINTS OF EVALUATION WHOSE ABSCISSAS */
/* ARE LESS THAN THE ABSCISSA OF THE FIRST DATA POINT. */
L60:
    if (start == 1) {
	goto L80;
    }
/* SET THE ERROR PARAMETER TO INDICATE THAT EXTRAPOLATION HAS OCCURRED. */
    *err = 1;
    choose_(&xtab[1], &ytab[1], &mtab[1], &mtab[2], &xtab[2], &ytab[2], eps, &
	    ncase);
    cases_(&xtab[1], &ytab[1], &mtab[1], &mtab[2], &xtab[2], &ytab[2], &e1, &
	    e2, &v1, &v2, &w1, &w2, &z1, &z2, &y1, &y2, &ncase);
    start1 = start - 1;
    i__1 = start1;
    for (i__ = 1; i__ <= i__1; ++i__) {
	yval[i__] = spline_(&xval[i__], &z1, &z2, &xtab[1], &ytab[1], &xtab[2]
		, &ytab[2], &y1, &y2, &e2, &w2, &v2, &ncase);
/* L70: */
    }
    if (*nume == 1) {
	goto L230;
    }


/* SEARCH LOCATES THE INTERVAL IN WHICH THE FIRST IN-RANGE POINT OF */
/* EVALUATION LIES. */
L80:
    if (*nume == 1 && end != *nume) {
	goto L200;
    }
    search_(&xtab[1], num, &xval[start], &lcn, &fnd);

    lcn1 = lcn + 1;


/* IF THE FIRST IN-RANGE POINT OF EVALUATION IS EQUAL TO ONE OF THE DATA */
/* POINTS, ASSIGN THE APPROPRIATE VALUE FROM YTAB. CONTINUE UNTIL A */
/* POINT OF EVALUATION IS FOUND WHICH IS NOT EQUAL TO A DATA POINT. */
    if (fnd == 0) {
	goto L130;
    }
L90:
    yval[start] = ytab[lcn];
    start1 = start;
    ++start;
    if (start > *nume) {
	goto L230;
    }
    if (xval[start1] == xval[start]) {
	goto L90;
    }

/* KC 2025-05-30 fixed "Arithmetic IF statement" */
/*   100 IF (XVAL(START) - XTAB(LCN1)) 130,110,120 */
L100:
    if (xval[start] < xtab[lcn1]) {
	goto L130;
    } else if (xval[start] == xtab[lcn1]) {
	goto L110;
    } else {
	goto L120;
    }

L110:
    yval[start] = ytab[lcn1];
    start1 = start;
    ++start;
    if (start > *nume) {
	goto L230;
    }
    if (xval[start] != xval[start1]) {
	goto L120;
    }
    goto L110;

L120:
    lcn = lcn1;
    ++lcn1;
    goto L100;



/* CALCULATE THE IMAGES OF ALL THE POINTS WHICH LIE WITHIN RANGE OF THE */
/* DATA. */

L130:
    if (lcn == 1 && *err == 1) {
	goto L140;
    }
    choose_(&xtab[lcn], &ytab[lcn], &mtab[lcn], &mtab[lcn1], &xtab[lcn1], &
	    ytab[lcn1], eps, &ncase);
    cases_(&xtab[lcn], &ytab[lcn], &mtab[lcn], &mtab[lcn1], &xtab[lcn1], &
	    ytab[lcn1], &e1, &e2, &v1, &v2, &w1, &w2, &z1, &z2, &y1, &y2, &
	    ncase);

L140:
    i__1 = end;
    for (i__ = start; i__ <= i__1; ++i__) {

/* IF XVAL(I) -XTAB(LCN1) IS NEGATIVE, DO NOT RECALCULATE THE PARAMETERS */
/* FOR THIS SECTION OF THE SPLINE SINCE THEY ARE ALREADY KNOWN. */
/* KC 2025-05-30 fixed "Arithmetic IF statement" */
/*       IF (XVAL(I) - XTAB(LCN1)) 150,160,170 */
	if (xval[i__] < xtab[lcn1]) {
	    goto L150;
	} else if (xval[i__] == xtab[lcn1]) {
	    goto L160;
	} else {
	    goto L170;
	}

L150:
	yval[i__] = spline_(&xval[i__], &z1, &z2, &xtab[lcn], &ytab[lcn], &
		xtab[lcn1], &ytab[lcn1], &y1, &y2, &e2, &w2, &v2, &ncase);
	goto L190;

/* IF XVAL(I) IS A DATA POINT, ITS IMAGE IS KNOWN. */
L160:
	yval[i__] = ytab[lcn1];
	goto L190;

/* INCREMENT THE POINTERS WHICH GIVE THE LOCATION IN THE DATA VECTOR. */
L170:
	lcn = lcn1;
	lcn1 = lcn + 1;

/* DETERMINE THAT THE ROUTINE IS IN THE CORRECT PART OF THE SPLINE. */
/* KC 2025-05-30 fixed "Arithmetic IF statement" */
/*       IF (XVAL(I) - XTAB(LCN1)) 180,160,170 */
	if (xval[i__] < xtab[lcn1]) {
	    goto L180;
	} else if (xval[i__] == xtab[lcn1]) {
	    goto L160;
	} else {
	    goto L170;
	}

/* CALL CHOOSE TO DETERMINE THE APPROPRIATE CASE AND THEN CALL */
/* CASES TO COMPUTE THE PARAMETERS OF THE SPLINE. */
L180:
	choose_(&xtab[lcn], &ytab[lcn], &mtab[lcn], &mtab[lcn1], &xtab[lcn1], 
		&ytab[lcn1], eps, &ncase);
	cases_(&xtab[lcn], &ytab[lcn], &mtab[lcn], &mtab[lcn1], &xtab[lcn1], &
		ytab[lcn1], &e1, &e2, &v1, &v2, &w1, &w2, &z1, &z2, &y1, &y2, 
		&ncase);
	goto L150;
L190:
	;
    }


/* CALCULATE THE IMAGES OF THE POINTS OF EVALUATION WHOSE ABSCISSAS */
/* ARE GREATER THAN THE ABSCISSA OF THE LAST DATA POINT. */
    if (end == *nume) {
	goto L230;
    }
    if (lcn1 == *num && xval[end] != xtab[*num]) {
	goto L210;
    }
/* Previously, when we arrived at 200 or 210, NUM1 could be improperly set. */
/* The NUM1= lines below protect from that.  llp   8/19/08 */
/* SET THE ERROR PRARMETER TO INDICATE THAT EXTRAPOLATION HAS OCCURRED. */
L200:
    *err = 1;
/* Computing MAX */
    i__1 = *num - 1;
    num1 = max(i__1,1);
    choose_(&xtab[num1], &ytab[num1], &mtab[num1], &mtab[*num], &xtab[*num], &
	    ytab[*num], eps, &ncase);
    cases_(&xtab[num1], &ytab[num1], &mtab[num1], &mtab[*num], &xtab[*num], &
	    ytab[*num], &e1, &e2, &v1, &v2, &w1, &w2, &z1, &z2, &y1, &y2, &
	    ncase);
L210:
    end1 = end + 1;
/* Computing MAX */
    i__1 = *num - 1;
    num1 = max(i__1,1);
    i__1 = *nume;
    for (i__ = end1; i__ <= i__1; ++i__) {
	yval[i__] = spline_(&xval[i__], &z1, &z2, &xtab[num1], &ytab[num1], &
		xtab[*num], &ytab[*num], &y1, &y2, &e2, &w2, &v2, &ncase);
/* L220: */
    }


L230:
    return 0;
} /* meval_ */

