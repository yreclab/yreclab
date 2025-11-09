/* search.f -- translated by f2c (version 20061008).
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
/* SEARCH */
/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */
/* Subroutine */ int search_(doublereal *xtab, integer *num, doublereal *s, 
	integer *lcn, integer *fnd)
{
    static integer last, first, middle;


/*                                 SHAPE PRESERVING QUADRATIC SPLINES */
/*                                   BY D.F.MCALLISTER & J.A.ROULIER */
/*                                     CODED BY S.L.DODD & M.ROULIER */
/*                                       N.C. STATE UNIVERSITY */


/* SEARCH CONDUCTS A BINARY SEARCH FOR S. SEARCH IS CALLED ONLY IF S IS */
/* BETWEEN XTAB(1) AND XTAB(NUM). */

/* ON INPUT-- */

/*   XTAB CONTAINS THE ABSCISSAS OF THE DATA POINTS OF INTERPOLATION. */

/*   NUM IS THE DIMENSION OF XTAB */

/*   S IS THE VALUE WHOSE RELATIVE POSITION IN XTAB IS LOCATED BY SEARCH. */


/* ON OUTPUT-- */

/*   FND IS SET EQUAL TO 1 IF S IS FOUND IN XTAB AND IS SET EQUAL TO 0 */
/*   OTHERWISE. */

/*   LCN IS THE INDEX OF THE LARGEST VALUE IN XTAB FOR WHICH XTAB(I) */
/*   .LT. S. */

/* AND */

/*   SEARCH DOES NOT ALTER XTAB,NUM,S. */

/* ---------------------------------------------------------------------- */

    /* Parameter adjustments */
    --xtab;

    /* Function Body */
    first = 1;
    last = *num;
    *fnd = 0;

    if (xtab[1] != *s) {
	goto L10;
    }
    *lcn = 1;
    *fnd = 1;
    return 0;

L10:
    if (xtab[*num] != *s) {
	goto L20;
    }
    *lcn = *num;
    *fnd = 1;
    return 0;

/* IF (LAST-FIRST) .EQ. 1, S IS NOT IN XTAB.  SET POSITION EQUAL TO */
/* FIRST. */
L20:
    if (last - first == 1) {
	goto L30;
    }

    middle = (first + last) / 2;

/* CHECK IF S .EQ. XTAB(MIDDLE). IF NOT, CONTINUE THE SEARCH IN THE */
/* APPROPRIATE HALF OF THE VECTOR XTAB. */
/* KC 2025-05-30 fixed "Arithmetic IF statement" */
/*       IF (XTAB(MIDDLE) - S) 40,50,60 */
    if (xtab[middle] < *s) {
	goto L40;
    } else if (xtab[middle] == *s) {
	goto L50;
    } else {
	goto L60;
    }

L30:
    *lcn = first;
    return 0;
L40:
    first = middle;
    goto L20;
L50:
    *lcn = middle;
    *fnd = 1;
    return 0;
L60:
    last = middle;
    goto L20;
} /* search_ */

