/* osplin.f -- translated by f2c (version 20100827).
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

/* ACM ALGORITHM 574 */

/* SHAPE-PRESERVING OSCULATORY QUADRATIC SPLINES */

/* BY D.F. MCALLISTER AND J.A. ROULIER */

/* ACM TRANSACTIONS ON MATHEMATICAL SOFTWARE, SEPTEMBER, 1981. */

/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */
/* OSPLIN */
/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */
/* Subroutine */ int osplin_(doublereal *xval, doublereal *yval, doublereal *
	xtab, doublereal *ytab, integer *n, integer *k)
{
    static doublereal m[5000], eps;
    static integer err;
    extern /* Subroutine */ int meval_(doublereal *, doublereal *, doublereal 
	    *, doublereal *, doublereal *, integer *, integer *, doublereal *,
	     integer *), slopes_(doublereal *, doublereal *, doublereal *, 
	    integer *);


/*   X CONTAINS THE ABSCISSAS OF THE POINTS OF INTERPOLAION. */

/*   Y CONTAINS THE ORDINATES OF THE POINTS OF INTERPOLATION. */

/*   N IS THE NUMBER OF DATA POINTS. */

/*   K IS THE NUMBER OF POINTS AT WHICH THE SPLINE IS TO BE EVALUATED. */


/* UPON EXIT FROM SUBROUTINE 'SLOPES'-- */

/*   M CONTAINS THE COMPUTED FIRST DERIVATIVES AT EACH DATA POINT. */

/* ---------------------------------------------------------------------- */

/* CALCULATE THE SLOPES AT EACH DATA POINT. */
    /* Parameter adjustments */
    --ytab;
    --xtab;
    --yval;
    --xval;

    /* Function Body */
    slopes_(&xtab[1], &ytab[1], m, n);

/* SET THE ERROR TOLERANCE EPS, WHICH IS USED IN SUBROUTINE 'CHOOSE'. */
    eps = 1e-4;
/* CALL MEVAL TO EVALUATE THE SPLINE AT THE RUN OF POINTS XVAL. */
    meval_(&xval[1], &yval[1], &xtab[1], &ytab[1], m, n, k, &eps, &err);
    return 0;
} /* osplin_ */

