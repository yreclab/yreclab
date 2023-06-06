/* wcz.f -- translated by f2c (version 20100827).
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
    doublereal cln, clni, c4pi, c4pil, c4pi3l, cc13, cc23, cpi;
} const1_;

#define const1_1 const1_

struct {
    doublereal wnew, walpcz, acfpft;
    integer itfp1, itfp2;
    logical lrot, linstb, lwnew;
} rot_;

#define rot_1 rot_

/* $$$$$$ */
/* Subroutine */ int wcz_(doublereal *hd, doublereal *hjm, doublereal *hr, 
	doublereal *hs, doublereal *hs2, integer *istart, integer *iend, 
	doublereal *eta2, doublereal *hi, doublereal *omega, doublereal *qiw, 
	doublereal *r0, integer *m)
{
    /* System generated locals */
    integer i__1;

    /* Builtin functions */
    double exp(doublereal);

    /* Local variables */
    static integer j;
    static doublereal w0;
    static integer jend;
    static doublereal cjnew;
    extern /* Subroutine */ int solid_(doublereal *, doublereal *, doublereal 
	    *, doublereal *, doublereal *, integer *, integer *, doublereal *,
	     doublereal *, doublereal *, doublereal *, doublereal *, integer *
	    );
    static doublereal cjtot, cmtot;
    static integer jstart;

    /* Parameter adjustments */
    --r0;
    --qiw;
    --omega;
    --hi;
    --eta2;
    --hs2;
    --hs;
    --hr;
    --hjm;
    --hd;

    /* Function Body */
    if (rot_1.walpcz >= 0.) {
/*  SOLID BODY ROTATION IN CONVECTIVE REGIONS. */
	solid_(&hd[1], &hjm[1], &hr[1], &hs[1], &hs2[1], istart, iend, &eta2[
		1], &hi[1], &omega[1], &qiw[1], &r0[1], m);
    } else if (rot_1.walpcz <= -2.) {
/*  CONSTANT SPECIFIC ANGULAR MOMENTUM PER UNIT MASS IN THE C.Z. */
/*  FIND TOTAL MASS AND ANGULAR MOMENTUM OF C.Z. */
	cjtot = hjm[*istart] * hs2[*istart];
	cmtot = hs2[*istart];
	i__1 = *iend;
	for (j = *istart + 1; j <= i__1; ++j) {
	    cjtot += hjm[j] * hs2[j];
	    cmtot += hs2[j];
/* L30: */
	}
/*  ASSIGN NEW RUN OF J/M IN THE C.Z. AND FIND THE NEW RUN OF OMEGA. */
	cjnew = cjtot / cmtot;
	i__1 = *iend;
	for (j = *istart; j <= i__1; ++j) {
	    hjm[j] = cjnew;
	    omega[j] = cjnew * hs2[j] / hi[j];
	    jstart = j;
	    jend = j;
	    solid_(&hd[1], &hjm[1], &hr[1], &hs[1], &hs2[1], &jstart, &jend, &
		    eta2[1], &hi[1], &omega[1], &qiw[1], &r0[1], m);
/* L40: */
	}
    } else {
/*  GENERAL LAW FOR OMEGA IN C.Z.: OMEGA = C*R**WALPCZ,WHERE C IS A CONSTANT */
/*  FOR THE ENTIRE C.Z. IF THIS HOLDS, THE RUN OF J/M CAN BE FOUND BY */
/*  SOLVING FOR THE CONSTANT BY REQUIRING THAT THE TOTAL J OF THE C.Z. BE */
/*  CONSERVED AND THEN USING J/M=C*R**WALPCZ*(MOMENT OF INERTIA PER UNIT */
/*  MASS). */
/*  FIND TOTAL MASS AND ANGULAR MOMENTUM OF C.Z. */
	cjtot = hjm[*istart] * hs2[*istart];
	cmtot = exp(const1_1.cln * rot_1.walpcz * hr[*istart]) * hi[*istart];
	i__1 = *iend;
	for (j = *istart + 1; j <= i__1; ++j) {
	    cjtot += hjm[j] * hs2[j];
	    cmtot += exp(const1_1.cln * rot_1.walpcz * hr[j]) * hi[j];
/* L50: */
	}
/*  ASSIGN NEW RUN OF J/M IN THE C.Z. AND FIND THE NEW RUN OF OMEGA. */
	w0 = cjtot / cmtot;
	i__1 = *iend;
	for (j = *istart; j <= i__1; ++j) {
	    omega[j] = w0 * exp(const1_1.cln * rot_1.walpcz * hr[j]);
	    hjm[j] = omega[j] * hi[j] / hs2[j];
	    jstart = j;
	    jend = j;
	    solid_(&hd[1], &hjm[1], &hr[1], &hs[1], &hs2[1], &jstart, &jend, &
		    eta2[1], &hi[1], &omega[1], &qiw[1], &r0[1], m);
/* L60: */
	}
    }
    return 0;
} /* wcz_ */

