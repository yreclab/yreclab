/* locate.f -- translated by f2c (version 20100827).
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


/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */
/*     LOCATE */
/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */
/* GIVEN AN ARRAY XX OF LENGTH N, AND GIVEN A VALUE X, RETURNS */
/* A VALUE J SUCH THAT X IS BETWEEN XX(J) AND XX(J+1).  X=0 OR N */
/* THEN OUT OF RANGE. */

/* Subroutine */ int locate_(doublereal *xx, integer *n, doublereal *x, 
	integer *j)
{
    static integer jl, jm, ju;

    /* Parameter adjustments */
    --xx;

    /* Function Body */
    jl = 0;
    ju = *n + 1;
L10:
    if (ju - jl > 1) {
	jm = (ju + jl) / 2;
	if (xx[*n] > xx[1] == *x > xx[jm]) {
	    jl = jm;
	} else {
	    ju = jm;
	}
	goto L10;
    }
    *j = jl;
    if (*j == 0 && *x > xx[1] * .99) {
	*j = 1;
    }
    if (*j == *n && *x < xx[*n] * 1.01) {
	*j = *n - 1;
    }
    return 0;
} /* locate_ */

