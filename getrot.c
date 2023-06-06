/* getrot.f -- translated by f2c (version 20100827).
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

/* $$$$$$ */
/* Subroutine */ int getrot_(doublereal *hd, doublereal *hjm, doublereal *hr, 
	doublereal *hs, doublereal *hs2, logical *lcz, integer *m, doublereal 
	*eta2, doublereal *hi, doublereal *omega, doublereal *qiw, doublereal 
	*r0)
{
    /* System generated locals */
    integer i__1;

    /* Local variables */
    static integer i__;
    extern /* Subroutine */ int wcz_(doublereal *, doublereal *, doublereal *,
	     doublereal *, doublereal *, integer *, integer *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, integer *)
	    ;
    static integer jend;
    extern /* Subroutine */ int solid_(doublereal *, doublereal *, doublereal 
	    *, doublereal *, doublereal *, integer *, integer *, doublereal *,
	     doublereal *, doublereal *, doublereal *, doublereal *, integer *
	    );
    static integer jstart;
    static logical lconvz;

/*  GETW TAKES THE ANGULAR MOMENTUM DISTRIBUTION AND FINDS THE */
/*  ROTATION CURVE THAT CORRESPONDS TO IT.  CONVECTIVE REGIONS HAVE */
/*  SOLID BODY ROTATION ENFORCED ON THEM. */
    /* Parameter adjustments */
    --r0;
    --qiw;
    --omega;
    --hi;
    --eta2;
    --lcz;
    --hs2;
    --hs;
    --hr;
    --hjm;
    --hd;

    /* Function Body */
    lconvz = FALSE_;
    i__1 = *m;
    for (i__ = 1; i__ <= i__1; ++i__) {
	if (! lconvz) {
	    if (! lcz[i__]) {
/*  RADIATIVE SHELL */
		jstart = i__;
		jend = i__;
		solid_(&hd[1], &hjm[1], &hr[1], &hs[1], &hs2[1], &jstart, &
			jend, &eta2[1], &hi[1], &omega[1], &qiw[1], &r0[1], m)
			;
	    } else {
/*  CONVECTION ZONE START - SET LCONVZ TO T */
		lconvz = TRUE_;
		jstart = i__;
	    }
	} else if (! lcz[i__]) {
/*  THE PREVIOUS SHELL WAS CONVECTIVE.  IF THIS ONE IS RADIATIVE, ENFORCE */
/*  THE APPROPRIATE ROTATION LAW IN THE ENTIRE CONVECTION ZONE PRECEDING IT. */
	    jend = i__ - 1;
	    wcz_(&hd[1], &hjm[1], &hr[1], &hs[1], &hs2[1], &jstart, &jend, &
		    eta2[1], &hi[1], &omega[1], &qiw[1], &r0[1], m);
/*  NOW FIND OMEGA IN THE CURRENT SHELL */
	    jstart = i__;
	    jend = i__;
	    solid_(&hd[1], &hjm[1], &hr[1], &hs[1], &hs2[1], &jstart, &jend, &
		    eta2[1], &hi[1], &omega[1], &qiw[1], &r0[1], m);
	    lconvz = FALSE_;
	} else if (i__ == *m) {
/*  SPECIAL CASE OF LAST SHELL CONVECTIVE - ENFORCE SOLID-BODY ROTATION */
/*  IN CZ AS ABOVE. */
	    jend = *m;
	    wcz_(&hd[1], &hjm[1], &hr[1], &hs[1], &hs2[1], &jstart, &jend, &
		    eta2[1], &hi[1], &omega[1], &qiw[1], &r0[1], m);
	}
/* L20: */
    }
    return 0;
} /* getrot_ */

