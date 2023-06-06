/* oversh.f -- translated by f2c (version 20100827).
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
    integer ilast, idebug, itrack, ishort, imilne, imodpt, istor, iowr;
} luout_;

#define luout_1 luout_

struct {
    doublereal cln, clni, c4pi, c4pil, c4pi3l, cc13, cc23, cpi;
} const1_;

#define const1_1 const1_

struct {
    doublereal dpenv, alphac, alphae, alpham;
    integer iov1, iov2, iovim;
    logical lovstc, lovste, lovstm, lsemic, ladov;
} dpmix_;

#define dpmix_1 dpmix_

struct {
    doublereal wnew, walpcz, acfpft;
    integer itfp1, itfp2;
    logical lrot, linstb, lwnew;
} rot_;

#define rot_1 rot_

/* Table of constant values */

static integer c__1 = 1;



/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */
/*     OVERSH */
/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */
/* Subroutine */ int oversh_(doublereal *hcomp, doublereal *hd, doublereal *
	hp, doublereal *hr, doublereal *hs, doublereal *ht, integer *m, 
	integer *mxzone, integer *mxzon0, integer *nzone)
{
    /* Format strings */
    static char fmt_5[] = "(1x,\002FULLY CONVECTIVE MODEL - NO OVERSHOOT\002)"
	    ;
    static char fmt_200[] = "(1x,\002MIXED REGIONS WITHOUT OVERSHOOT\002,4"
	    "(\002[\002,i4,\002-\002,i4,\002 ]\002))";
    static char fmt_210[] = "(1x,\002MIXED REGIONS WITH OVERSHOOT   \002,4"
	    "(\002[\002,i4,\002-\002,i4,\002 ]\002))";

    /* System generated locals */
    integer i__1, i__2;

    /* Builtin functions */
    integer s_wsfe(cilist *), e_wsfe(void), do_fio(integer *, char *, ftnlen);
    double exp(doublereal);

    /* Local variables */
    static integer i__, j;
    static doublereal r__;
    static integer id;
    static doublereal rcz, ros;
    static integer jedge;
    extern /* Subroutine */ int hsubp_(doublereal *, doublereal *, doublereal 
	    *, doublereal *, doublereal *, doublereal *, integer *, 
	    doublereal *);
    static logical lflagd;
    static doublereal pscald;
    static logical lflagu;
    static doublereal pscalu;

    /* Fortran I/O blocks */
    static cilist io___2 = { 0, 0, 0, fmt_5, 0 };
    static cilist io___3 = { 0, 0, 0, fmt_200, 0 };
    static cilist io___14 = { 0, 0, 0, fmt_200, 0 };
    static cilist io___15 = { 0, 0, 0, fmt_210, 0 };


/*  THIS SR COMPUTES THE LOCAL PRESSURE SCALE HEIGHT AT BOTH EDGES OF A */
/*  GIVEN CONVECTIVE REGION AND LOCATES THE BOUNDARIES OF OVERSHOOT */
/*  REGIONS BASED ON THE USER-SPECIFIED EXTENT. */
    /* Parameter adjustments */
    mxzon0 -= 13;
    mxzone -= 13;
    --ht;
    --hs;
    --hr;
    --hp;
    --hd;
    hcomp -= 16;

    /* Function Body */
    dpmix_1.iov1 = -1;
    dpmix_1.iov2 = -1;
    i__1 = *nzone;
    for (i__ = 1; i__ <= i__1; ++i__) {
/* DETERMINE IF THIS REGION IS A CORE CONVECTION ZONE, SURFACE CZ, */
/* OR INTERMEDIATE CZ. THERE ARE SEPARATE FLAGS GOVERNING WHETHER */
/* OVERSHOOT WILL BE PERFORMED IN EACH CASE, AND SEPARATE USER */
/* PARAMETERS GOVERNING THE DEGREE OF OVERSHOOT. */
	if (mxzone[i__ + 12] == 1) {
/* CONVECTIVE CORE */
/* CHECK FOR A FULLY CONVECTIVE STAR; SKIP THIS SR IF THERE IS ONE. */
	    if (mxzone[i__ + 24] == *m) {
		io___2.ciunit = luout_1.ishort;
		s_wsfe(&io___2);
		e_wsfe();
		io___3.ciunit = luout_1.ishort;
		s_wsfe(&io___3);
		for (j = 1; j <= 2; ++j) {
		    do_fio(&c__1, (char *)&mxzon0[j * 12 + 1], (ftnlen)sizeof(
			    integer));
		}
		e_wsfe();
		return 0;
	    }
/* SKIP IF NO CORE OVERSHOOT IS DESIRED. */
	    if (! dpmix_1.lovstc) {
		goto L100;
	    }
	    lflagu = TRUE_;
	    lflagd = FALSE_;
	    jedge = mxzone[i__ + 24];
	    hsubp_(&hcomp[16], &hd[1], &hp[1], &hr[1], &hs[1], &ht[1], &jedge,
		     &pscalu);
/* PSCALU IS THE PRESSURE SCALE HEIGHT ABOVE THE CONVECTIVE REGION; */
/* ALPHAC IS THE DESIRED OVERSHOOT (IN SCALE HEIGHTS). */
	    pscalu *= dpmix_1.alphac;
	} else if (mxzone[i__ + 24] == *m) {
/* CONVECTIVE ENVELOPE */
/* SKIP IF NO ENVELOPE OVERSHOOT IS DESIRED. */
	    if (! dpmix_1.lovste) {
		goto L100;
	    }
	    lflagu = FALSE_;
	    lflagd = TRUE_;
	    jedge = mxzone[i__ + 12];
	    hsubp_(&hcomp[16], &hd[1], &hp[1], &hr[1], &hs[1], &ht[1], &jedge,
		     &pscald);
/* PSCALD IS THE PRESSURE SCALE HEIGHT BELOW THE CONVECTIVE REGION; */
/* ALPHAE IS THE DESIRED OVERSHOOT (IN SCALE HEIGHTS). */
	    pscald *= dpmix_1.alphae;
	} else {
/* INTERMEDIATE CONVECTION ZONE (NOT INCLUDING CENTRAL OR SURFACE POINT). */
/* SKIP IF NO INTERMEDIATE CONVECTION. */
	    if (! dpmix_1.lovstm) {
		goto L100;
	    }
	    lflagu = TRUE_;
	    lflagd = TRUE_;
/* PSCALU AND PSCALD HAVE THE SAME MEANING AS ABOVE; OVERSHOOT BOTH BELOW */
/* AND ABOVE IS PERFORMED BY AN AMOUNT ALPHAM. */
	    jedge = mxzone[i__ + 12];
	    hsubp_(&hcomp[16], &hd[1], &hp[1], &hr[1], &hs[1], &ht[1], &jedge,
		     &pscald);
	    pscald *= dpmix_1.alpham;
	    jedge = mxzone[i__ + 24];
	    hsubp_(&hcomp[16], &hd[1], &hp[1], &hr[1], &hs[1], &ht[1], &jedge,
		     &pscalu);
	    pscalu *= dpmix_1.alpham;
	}
/* COMPUTE EXTENSION OF CONVECTION ZONE BELOW SCHWARTZSCHILD BOUNDARY. */
	if (lflagd) {
	    id = mxzone[i__ + 12];
	    rcz = exp(const1_1.cln * hr[id]);
	    ros = rcz - pscald;
/* THE OVERSHOOT REGION IS EXTENDED THE RADIAL DISTANCE PSCALD DOWN; THE */
/* LAST POINT LESS THAN PSCALD FROM THE FORMAL EDGE OF THE CZ IS DEFINED */
/* AS THE NEW EDGE OF THE MIXED REGION. */
	    for (j = id - 1; j >= 1; --j) {
		r__ = exp(const1_1.cln * hr[j]);
		if (r__ < ros) {
		    goto L20;
		}
/* L10: */
	    }
/* IF THE CODE GETS HERE, THE OVERSHOOT REGION EXTENDS BELOW THE FIRST POINT. */
/* THE CODE WILL ASSIGN THE FIRST POINT AS THE LOWER EDGE(I.E. THE CZ WILL */
/* EXTEND TO THE CENTER). */
	    j = 0;
L20:
/* FOR ROTATING MODELS, ENSURE THAT THERE IS AT LEAST ONE RADIATIVE POINT */
/* IN THE OVERSHOOT REGION. */
	    mxzone[i__ + 12] = j + 1;
/* 11/91 MHP CHANGED TO REQUIRE AN OVERSHOOT ZONE ONLY IF LINSTB=T. */
	    if (rot_1.lrot && rot_1.linstb && mxzone[i__ + 12] == mxzon0[i__ 
		    + 12]) {
		--mxzone[i__ + 12];
	    }
/* DBG 8/94 STORE POSITION OF OVERSHOOT FOR ADIABATIC EXTENSION */
	    dpmix_1.iov2 = id;
	    dpmix_1.iov1 = mxzone[i__ + 12];
	}
/* COMPUTE EXTENSION OF CONVECTION ZONE ABOVE SCHWARTZSCHILD BOUNDARY. */
	if (lflagu) {
	    id = mxzone[i__ + 24];
	    rcz = exp(const1_1.cln * hr[id]);
	    ros = rcz + pscalu;
/* THE OVERSHOOT REGION IS EXTENDED THE RADIAL DISTANCE PSCALU UP; THE */
/* LAST POINT LESS THAN PSCALU FROM THE FORMAL EDGE OF THE CZ IS DEFINED */
/* AS THE NEW EDGE OF THE MIXED REGION. */
	    i__2 = *m;
	    for (j = id + 1; j <= i__2; ++j) {
		r__ = exp(const1_1.cln * hr[j]);
		if (r__ > ros) {
		    goto L40;
		}
/* L30: */
	    }
/* IF THE CODE GETS HERE, THE OVERSHOOT REGION EXTENDS ABOVE THE LAST POINT. */
/* THE CODE WILL ASSIGN THE LAST POINT AS THE UPPER EDGE(I.E. THE CZ WILL */
/* EXTEND TO THE SURFACE). */
	    j = *m + 1;
L40:
	    mxzone[i__ + 24] = j - 1;
/* 11/91 MHP CHANGED TO REQUIRE AN OVERSHOOT ZONE ONLY IF LINSTB=T. */
	    if (rot_1.lrot && rot_1.linstb && mxzone[i__ + 24] == mxzon0[i__ 
		    + 24]) {
		++mxzone[i__ + 24];
	    }
	}
L100:
	;
    }
/* OUTPUT : THE OLD AND NEW MIXED REGIONS ARE PRINTED OUT IN ISHORT. */
    io___14.ciunit = luout_1.ishort;
    s_wsfe(&io___14);
    i__1 = *nzone;
    for (i__ = 1; i__ <= i__1; ++i__) {
	for (j = 1; j <= 2; ++j) {
	    do_fio(&c__1, (char *)&mxzon0[i__ + j * 12], (ftnlen)sizeof(
		    integer));
	}
    }
    e_wsfe();
    io___15.ciunit = luout_1.ishort;
    s_wsfe(&io___15);
    i__1 = *nzone;
    for (i__ = 1; i__ <= i__1; ++i__) {
	for (j = 1; j <= 2; ++j) {
	    do_fio(&c__1, (char *)&mxzone[i__ + j * 12], (ftnlen)sizeof(
		    integer));
	}
    }
    e_wsfe();
    return 0;
} /* oversh_ */

