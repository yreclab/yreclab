/* spline.f -- translated by f2c (version 20061008).
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

doublereal spline_(doublereal *xvals, doublereal *z1, doublereal *z2, 
	doublereal *xtabs, doublereal *ytabs, doublereal *xtabs1, doublereal *
	ytabs1, doublereal *y1, doublereal *y2, doublereal *e2, doublereal *
	w2, doublereal *v2, integer *ncase)
{
    /* System generated locals */
    doublereal ret_val, d__1, d__2, d__3;

    /* Local variables */
    static doublereal fs;


/*                                 SHAPE PRESERVING QUDRATIC SPLINES */
/*                                   BY D.F.MCALLISTER & J.A.ROULIER */
/*                                     CODED BY S.L.DODD & M.ROULIER */
/*                                       N.C. STATE UNIVERSITY */


/* SPLINE FINDS THE IMAGE OF A POINT IN XVAL. */

/* ON INPUT-- */

/*   XVALS CONTAINS THE VALUE AT WHICH THE SPLINE IS EVALUATED. */

/*   (XTABS,YTABS) ARE THE COORDINATES OF THE LEFT-HAND DATA POINT */
/*   USED IN THE EVALUATION OF XVALS. */

/*   (XTABS1,YTABS1) ARE THE COORDINATES OF THE RIGHT-HAND DATA POINT */
/*   USED IN THE EVALUATION OF XVALS. */

/*   Z1,Z2,Y1,Y2,E2,W2,V2 ARE THE PARAMETERS OF THE SPLINE. */

/*   NCASE CONTROLS THE EVALUATION OF THE SPLINE BY INDICATING WHETHER */
/*   ONE OR TWO KNOTS WERE PLACED IN THE INTERVAL (XTABS,XTABS1). */


/* ON OUTPUT-- */

/*   SPLINE IS THE IMAGE OF XVALS. */

/* AND */

/*   SPLINE DOES NOT ALTER ANY OF THE INPUT PARAMETERS. */

/* ---------------------------------------------------------------------- */

/*  *****MODIFICATION DUE TO MARC PINSONNEAULT 6/87***** */
/*  IF DIVISION BY ZERO WOULD BE CAUSED,LINEAR INTERPOLATION IS USED */
/*  INSTEAD OF THE SPLINE. */
/* IF NCASE .EQ. 4, MORE THAN ONE KNOT WAS PLACED IN THE INTERVAL. */
    if (*ncase == 4) {
	goto L40;
    }

/* CASES 1,2, OR 3. */

/* DETERMINE THE LOCATION OF XVALS RELATIVE TO THE KNOT. */
/* KC 2025-05-30 fixed "Arithmetic IF statement" */
/*       IF (Z1 - XVALS) 10,20,30 */
    if (*z1 < *xvals) {
	goto L10;
    } else if (*z1 == *xvals) {
	goto L20;
    } else {
	goto L30;
    }

L10:
    if (*xtabs1 != *z1) {
/* Computing 2nd power */
	d__1 = *xtabs1 - *xvals;
/* Computing 2nd power */
	d__2 = *xvals - *z1;
/* Computing 2nd power */
	d__3 = *xtabs1 - *z1;
	ret_val = (*z2 * (d__1 * d__1) + *w2 * 2. * (*xvals - *z1) * (*xtabs1 
		- *xvals) + *ytabs1 * (d__2 * d__2)) / (d__3 * d__3);
    } else {
	fs = (*xvals - *xtabs) / (*xtabs1 - *xtabs);
	ret_val = *ytabs + fs * (*ytabs1 - *ytabs);
    }
    return ret_val;

L20:
    ret_val = *z2;
    return ret_val;

L30:
    if (*z1 != *xtabs) {
/* Computing 2nd power */
	d__1 = *z1 - *xvals;
/* Computing 2nd power */
	d__2 = *xvals - *xtabs;
/* Computing 2nd power */
	d__3 = *z1 - *xtabs;
	ret_val = (*ytabs * (d__1 * d__1) + *v2 * 2. * (*xvals - *xtabs) * (*
		z1 - *xvals) + *z2 * (d__2 * d__2)) / (d__3 * d__3);
    } else {
	fs = (*xvals - *xtabs) / (*xtabs1 - *xtabs);
	ret_val = *ytabs + fs * (*ytabs1 - *ytabs);
    }
    return ret_val;

/* CASE 4. */

/* DETERMINE THE LOCATION OF XVALS RELATIVE TO THE FIRST KNOT. */
/* KC 2025-05-30 fixed "Arithmetic IF statement" */
/*   40  IF (Y1 - XVALS) 70,60,50 */
L40:
    if (*y1 < *xvals) {
	goto L70;
    } else if (*y1 == *xvals) {
	goto L60;
    } else {
	goto L50;
    }

L50:
    if (*y1 != *xtabs) {
/* Computing 2nd power */
	d__1 = *y1 - *xvals;
/* Computing 2nd power */
	d__2 = *xvals - *xtabs;
/* Computing 2nd power */
	d__3 = *y1 - *xtabs;
	ret_val = (*ytabs * (d__1 * d__1) + *v2 * 2. * (*xvals - *xtabs) * (*
		y1 - *xvals) + *y2 * (d__2 * d__2)) / (d__3 * d__3);
    } else {
	fs = (*xvals - *xtabs) / (*xtabs1 - *xtabs);
	ret_val = *ytabs + fs * (*ytabs1 - *ytabs);
    }
    return ret_val;

L60:
    ret_val = *y2;
    return ret_val;

/* DETERMINE THE LOCATION OF XVALS RELATIVE TO THE SECOND KNOT. */
/* KC 2025-05-30 fixed "Arithmetic IF statement" */
/*   70  IF (Z1 - XVALS) 100,90,80 */
L70:
    if (*z1 < *xvals) {
	goto L100;
    } else if (*z1 == *xvals) {
	goto L90;
    } else {
	goto L80;
    }

L80:
    if (*z1 != *y1) {
/* Computing 2nd power */
	d__1 = *z1 - *xvals;
/* Computing 2nd power */
	d__2 = *xvals - *y1;
/* Computing 2nd power */
	d__3 = *z1 - *y1;
	ret_val = (*y2 * (d__1 * d__1) + *e2 * 2. * (*xvals - *y1) * (*z1 - *
		xvals) + *z2 * (d__2 * d__2)) / (d__3 * d__3);
    } else {
	fs = (*xvals - *xtabs) / (*xtabs1 - *xtabs);
	ret_val = *ytabs + fs * (*ytabs1 - *ytabs);
    }
    return ret_val;

L90:
    ret_val = *z2;
    return ret_val;

L100:
    if (*xtabs1 != *z1) {
/* Computing 2nd power */
	d__1 = *xtabs1 - *xvals;
/* Computing 2nd power */
	d__2 = *xvals - *z1;
/* Computing 2nd power */
	d__3 = *xtabs1 - *z1;
	ret_val = (*z2 * (d__1 * d__1) + *w2 * 2. * (*xvals - *z1) * (*xtabs1 
		- *xvals) + *ytabs1 * (d__2 * d__2)) / (d__3 * d__3);
    } else {
	fs = (*xvals - *xtabs) / (*xtabs1 - *xtabs);
	ret_val = *ytabs + fs * (*ytabs1 - *ytabs);
    }
    return ret_val;
} /* spline_ */

