/* wczimp.f -- translated by f2c (version 20061008).
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
    logical lsolid;
    integer impjmod;
} sbrot_;

#define sbrot_1 sbrot_

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

/* Table of constant values */

static integer c__1 = 1;

/* $$$$$$ */
/* Subroutine */ int wczimp_(doublereal *hd, doublereal *hjm, doublereal *hr, 
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

/* JNT 2025/09/03 copy of 2025/05/14 TO MAKE THE CODE ENFORCE */
/* SPECIFIC ROTATION PROFILES */
/* JNT 2025/09/03 COPY OF 2015/05/07 ADD IEND.LT.M TO ENFORCE SB */
/* ROTATION IN CONVECTIVE ZONES THAT ARE NOT THE SURFACE CONVECTIVE */
/* ZONE EVEN IF WALPCZ IS TURNED ON (I.E. WALPCZ NOW ONLY AFFECTS */
/* SURFACE CONVECTION ZONES) */
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
    if (rot_1.walpcz >= 0. || sbrot_1.lsolid || sbrot_1.impjmod == 1 || *iend 
	    < *m) {
/*  SOLID BODY ROTATION IN CONVECTIVE REGIONS. */
	solid_(&hd[1], &hjm[1], &hr[1], &hs[1], &hs2[1], istart, iend, &eta2[
		1], &hi[1], &omega[1], &qiw[1], &r0[1], m);
/* JNT 2025/09/03 COPY OF 2015/05/14 ADD OPTION TO MAKE EVERYTHING */
/* BELOW THE SURFACE CONVECTION ZONE ROTATE AS A SOLID BODY, */
/* DETACHED FROM WHAT IS HAPPENING IN THE CONVECTION ZONE */
    } else if (sbrot_1.impjmod == 2) {
	cjtot = hjm[*istart] * hs2[*istart];
	cmtot = exp(const1_1.cln * rot_1.walpcz * hr[*istart]) * hi[*istart];
	i__1 = *iend;
	for (j = *istart + 1; j <= i__1; ++j) {
	    cjtot += hjm[j] * hs2[j];
	    cmtot += exp(const1_1.cln * rot_1.walpcz * hr[j]) * hi[j];
/* L30: */
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
/* L31: */
	}
	if (*istart > 1) {
	    i__1 = *istart - 1;
	    solid_(&hd[1], &hjm[1], &hr[1], &hs[1], &hs2[1], &c__1, &i__1, &
		    eta2[1], &hi[1], &omega[1], &qiw[1], &r0[1], m);
	}
/* JNT 2025/09/04 REPLICATING 2015/05/14 ADD OPTION TO MAKE */
/* EVERYTHING BELOW THE SURFACE CONVECTION ZONE ROTATE AS A */
/* SOLID BODY AT THE RATE OF THE BASE OF THE CONVECTION ZONE. */
    } else if (sbrot_1.impjmod == 3) {
	cjtot = hjm[1] * hs2[1];
	cmtot = exp(const1_1.cln * rot_1.walpcz * hr[*istart]) * hi[1];
	if (*istart > 1) {
	    i__1 = *istart;
	    for (j = 2; j <= i__1; ++j) {
		cjtot += hjm[j] * hs2[j];
		cmtot += exp(const1_1.cln * rot_1.walpcz * hr[*istart]) * hi[
			j];
/* L32: */
	    }
	}
	i__1 = *iend;
	for (j = *istart + 1; j <= i__1; ++j) {
	    cjtot += hjm[j] * hs2[j];
	    cmtot += exp(const1_1.cln * rot_1.walpcz * hr[j]) * hi[j];
/* L33: */
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
/* L34: */
	}
	if (*istart > 1) {
	    i__1 = *istart - 1;
	    for (j = 1; j <= i__1; ++j) {
		omega[j] = omega[*istart];
		hjm[j] = omega[j] * hi[j] / hs2[j];
/* L35: */
	    }
	    i__1 = *istart - 1;
	    solid_(&hd[1], &hjm[1], &hr[1], &hs[1], &hs2[1], &c__1, &i__1, &
		    eta2[1], &hi[1], &omega[1], &qiw[1], &r0[1], m);
	}
    } else if (rot_1.walpcz <= -2. && sbrot_1.impjmod == 0) {
/*  CONSTANT SPECIFIC ANGULAR MOMENTUM PER UNIT MASS IN THE C.Z. */
/*  FIND TOTAL MASS AND ANGULAR MOMENTUM OF C.Z. */
	cjtot = hjm[*istart] * hs2[*istart];
	cmtot = hs2[*istart];
	i__1 = *iend;
	for (j = *istart + 1; j <= i__1; ++j) {
	    cjtot += hjm[j] * hs2[j];
	    cmtot += hs2[j];
/* L36: */
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
} /* wczimp_ */

