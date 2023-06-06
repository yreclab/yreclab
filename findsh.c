/* findsh.f -- translated by f2c (version 20100827).
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
    doublereal atime[14], tcut[5], tscut, tenv0, tenv1, tenv, tgcut;
} ctlim_;

#define ctlim_1 ctlim_



/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */
/* FINDSH */
/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */
/* Subroutine */ int findsh_(doublereal *hcomp, doublereal *hl, logical *lc, 
	integer *m, integer *jcore, integer *jenv, integer *jxbeg, integer *
	jxend, integer *jxmid, logical *lshell)
{
    /* Initialized data */

    static doublereal dlmin = 1e-5;
    static doublereal dxmin = 1e-5;

    /* System generated locals */
    integer i__1;

    /* Local variables */
    static integer i__;
    static doublereal xmid, xlend;

    /* Parameter adjustments */
    --lc;
    --hl;
    hcomp -= 16;

    /* Function Body */
/*   SR FINDSH LOCATES THE OUTER EDGE OF A CENTRAL CONVECTION ZONE AND THE INNER */
/*   EDGE OF A SURFACE C.Z.  IT ALSO LOCATES THE BEGINNING,CENTER,AND END OF */
/*   A HYDROGEN-BURNING SHELL IF APPLICABLE. */
/* ** TO BE ADDED ** */
/*   LOCATING THE EXACT EDGES OF CENTRAL AND SURFACE C.Z.'S AND ADDING */
/*   POINTS AT THE EDGES. */

/* INPUT VARIABLES: */
/* DECLARED: */
/*   HCOMP : RUN OF MASS FRACTION OF THE VARIOUS CHEMICAL SPECIES. */
/*   HL : RUN OF LUMINOSITY AS A FUNCTION OF MASS (SOLAR UNITS). */
/*   LC : FLAG SET T IF A SHELL IS CONVECTIVE. */
/*   M : NUMBER OF POINTS IN THE MODEL. */
/* IN COMMON BLOCKS : */
/*   ATIME(1) : USER PARAMETER; IF X < ATIME(1) THEN THE PROGRAM CONSIDERS */
/*        THE STAR TO HAVE A HYDROGEN-BURNING SHELL RATHER THAN A HYDROGEN- */
/*        BURNING CORE. */
/* LOCAL VARIABLES : */
/*   DLMIN : THE OUTER EDGE OF THE H-BURNING SHELL IS DEFINED AS THE POINT */
/*        WHERE THE CHANGE IN LUMINOSITY FROM ONE SHELL TO THE NEXT */
/*        IS LESS THAN ENDSHL. */
/*   DXMIN : THE OUTER EDGE OF THE H-BURNING SHELL IS REACHED WHEN X DIFFERS */
/*        FROM THE SURFACE VALUE BY LESS THAN DXMIN REGARDLESS OF THE */
/*        LUMINOSITY TEST. */

/* OUTPUT VARIABLES : */
/*   JCORE : OUTERMOST POINT IN THE CONVECTIVE CORE (1=NO CONVECTIVE CORE) */
/*   JENV : INNERMOST POINT IN THE SURFACE C.Z. (M=NO SURFACE C.Z.) */
/*   LSHELL : FLAG SET T IF THE PROGRAM CONSIDERS THE MODEL TO HAVE A */
/*        HYDROGEN-BURNING SHELL. */
/*   IF LSHELL=T THEN THE FOLLOWING ARE COMPUTED : */
/*   JXBEG : FIRST SHELL WITH X > ATIME(1). */
/*   JXMID : FIRST SHELL WHERE X EXCEEDS 1/2 THE SURFACE VALUE. */
/*   JXEND : LAST SHELL WHERE L(I)-L(I-1) > ENDSHL OR X IS WITHIN 1.0E-5 */
/*        OF THE SURFACE VALUE. */
/* CC H-SHELL VALUES */
    *jxbeg = 1;
    *jxmid = 1;
    *jxend = 1;
    *lshell = FALSE_;
/*  IF CENTRAL X BELOW THRESHOLD THEN CALCULATE H SHELL VALUES */
    if (hcomp[16] <= ctlim_1.atime[0]) {
	*lshell = TRUE_;
	xmid = hcomp[*m * 15 + 1] * .5;
	xlend = dlmin * hl[*m];
/*  FIND BEGINNING(JXBEG), MIDDLE(JXMID) AND END(JXEND) OF H SHELL */
	i__1 = *m;
	for (i__ = 1; i__ <= i__1; ++i__) {
/* 	    IF(HCOMP(1,I).LE.1.0D-10) THEN  ! Changed after discussion with Marc */
	    if (hcomp[i__ * 15 + 1] <= ctlim_1.atime[0]) {
/* to force consistency with above LLP 9/24/08 */
		++(*jxbeg);
		++(*jxmid);
	    } else if (hcomp[i__ * 15 + 1] <= xmid) {
		++(*jxmid);
	    } else if (hl[i__] - hl[i__ - 1] < xlend) {
/*               write(*,*)'luminosity criteria' */
		goto L20;
	    } else if (hcomp[*m * 15 + 1] - hcomp[i__ * 15 + 1] < dxmin) {
/*               write(*,*)'composition criteria' */
		goto L20;
	    }
/* L10: */
	}
	i__ = *m;
L20:
	*jxend = i__;
    }
/* CC FIND BOUNDARY OF CENTRAL CONVECTION ZONE. */
    i__1 = *m;
    for (i__ = 1; i__ <= i__1; ++i__) {
	if (! lc[i__]) {
	    goto L40;
	}
/* L30: */
    }
L40:
    if (i__ > 1) {
	*jcore = i__ - 1;
    } else {
	*jcore = 1;
    }
/* CC FIND BOUNDARY OF SURFACE C.Z. */
    for (i__ = *m; i__ >= 1; --i__) {
	if (! lc[i__]) {
	    goto L60;
	}
/* L50: */
    }
L60:
    if (i__ < *m) {
	*jenv = i__ + 1;
    } else {
	*jenv = *m;
    }
/*  FOR A FULLY CONVECTIVE STAR (JENV=1),TURN THE CONVECTIVE CORE OFF(JCORE=1). */
/*  THIS IS DONE BECAUSE JCORE IS USED IN COMPUTING THE NUCLEAR TIMESTEP, */
/*  AND PUTTING IT AT THE SURFACE DOES STRANGE THINGS. */
    if (*jenv == 1) {
	*jcore = 1;
    }
    return 0;
} /* findsh_ */

