/* xrng4.f -- translated by f2c (version 20100827).
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

/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */
/*     GET FOUR POINTS IN X ARRAY WHICH SURROUND X */
/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */
/* Subroutine */ int xrng4_(integer *jx, integer *numx, integer *jx1, integer 
	*jx2)
{
    if (*jx <= 2) {
	*jx1 = 1;
	*jx2 = 4;
    } else if (*jx >= *numx - 2) {
	*jx1 = *numx - 3;
	*jx2 = *numx;
    } else {
	*jx1 = *jx - 1;
	*jx2 = *jx + 2;
    }
    return 0;
} /* xrng4_ */

