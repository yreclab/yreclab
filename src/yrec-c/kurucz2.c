/* kurucz2.f -- translated by f2c (version 20061008).
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
    doublereal gridt[60];
} gkrz2_;

#define gkrz2_1 gkrz2_

struct {
    doublereal opacity[3000]	/* was [60][50] */, rho[3000]	/* was [60][
	    50] */;
    integer numtm;
} krz2_;

#define krz2_1 krz2_

struct {
    integer ilast, idebug, itrack, ishort, imilne, imodpt, istor, iowr;
} luout_;

#define luout_1 luout_

struct kipm2_1_ {
    integer m1, m2, m3;
};

#define kipm2_1 (*(struct kipm2_1_ *) &kipm2_)

struct {
    doublereal cford[12000]	/* was [60][200] */;
    integer nds[60], ndd[60];
} intpl22_;

#define intpl22_1 intpl22_

/* Initialized data */

struct {
    integer e_1[3];
    } kipm2_ = { 1, 1, 1 };


/* Table of constant values */

static integer c__9 = 9;
static integer c__1 = 1;
static integer c__5 = 5;
static doublereal c_b15 = 10.;



/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */
/*     KURUCZ2 */
/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */
/*     THIS IS INTERPOLATION FACILITIES FOR KURUCZ'S OPACITY TABLES */
/*     USING CUBIC SPLINE INTERPLOATION SCHEME. */
/*     SECOND Z TABLE */
/* Subroutine */ int kurucz2_(doublereal *dl, doublereal *tl, doublereal *of, 
	doublereal *olf, doublereal *qodf, doublereal *qotf)
{
    /* System generated locals */
    integer i__1, i__2;

    /* Builtin functions */
    integer s_wsle(cilist *), do_lio(integer *, integer *, char *, ftnlen), 
	    e_wsle(void);
    /* Subroutine */ void s_stop(char *, ftnlen);
    double pow_dd(doublereal *, doublereal *);

    /* Local variables */
    static doublereal d__, t, c1, c2, c3, c4, dx;
    static integer it, jt;
    static doublereal xt[60], ol0;
    static integer ndf;
    static doublereal ol00;
    static integer itf, kip, iyc, its;
    static doublereal yto[60], aqod[60], qodi;
    static integer ndss, knot;
    static logical lmore;
    static doublereal qodti;
    static integer index1, index2;
    extern /* Subroutine */ int findex_(doublereal *, integer *, doublereal *,
	     integer *), intpol_(doublereal *, doublereal *, integer *, 
	    doublereal *, doublereal *, doublereal *);

    /* Fortran I/O blocks */
    static cilist io___25 = { 0, 0, 0, 0, 0 };


/*     TWO DIMENSIONAL INTERPOLATION FOR OPACITY */
/*     M1, M2, AND M3 ARE NEAREST GRID POINT OF ABUNDANCE, TEMPERATURE, */
/*     AND DENSITY WE GOT AT 'GETD'. */
/*     O IS OPACITY. */
/*     OL IS DLOG(O) */
/*     QODF IS THE PARTIAL DERIVATIVE OF O WRT D. */
/*     QOTF IS THE PARTIAL DERIVATIVE OF O WRT T. */
/*     THE VARIABLES WHICH HAVE 'TEM'-HEAD OR 'TEM'-TAIL ARE TEMPORARILLY */
/*     REQUIRED FOR DERIVATIVE VALUE ESTIMATION.  THESE ARE NOT THE VALUES */
/*     WE WANT. */
/*     THE VARIABLES WHICH HAVE 'I'-TAIL ARE OBTAINED FROM INTERPOLATION */
/*     ROUTINE.  WE WILL NOT USE THESE EVALUATIONS. */
/*     THE VARIABLES WHICH HAVE 'F'-TAIL ARE WHAT WILL BE RETURNED. */
/*     THIS VALUES IS ESTIMATED BY NUMERICAL DIFFERENTIATION. */
    findex_(gkrz2_1.gridt, &krz2_1.numtm, tl, &kipm2_1.m2);
    t = *tl;
    d__ = *dl;
    lmore = TRUE_;
/* FOR SIX GRID POINTS OF TEMPERATURE */
    its = kipm2_1.m2 - 2;
    if (its <= 0) {
	its = 1;
    }
    itf = kipm2_1.m2 + 3;
    if (itf > krz2_1.numtm) {
	itf = krz2_1.numtm;
    }
L333:
    jt = 0;
    i__1 = itf;
    for (it = its; it <= i__1; ++it) {
	index1 = it;
	ndss = intpl22_1.nds[index1 - 1];
	ndf = ndss + intpl22_1.ndd[index1 - 1] - 1;
/* FIND THE 'M3' */
	if (kipm2_1.m3 < ndss || kipm2_1.m3 > ndf) {
	    kipm2_1.m3 = ndf;
	}
	kip = kipm2_1.m3;
	if (d__ < krz2_1.rho[it + kip * 60 - 61]) {
	    i__2 = ndss;
	    for (iyc = kip - 1; iyc >= i__2; --iyc) {
		if (krz2_1.rho[it + iyc * 60 - 61] <= d__) {
		    kip = iyc;
		    goto L213;
		}
/* L211: */
	    }
	    goto L300;
	} else {
	    i__2 = ndf - 1;
	    for (iyc = kip; iyc <= i__2; ++iyc) {
		if (krz2_1.rho[it + (iyc + 1) * 60 - 61] > d__) {
		    kip = iyc;
		    goto L213;
		}
/* L212: */
	    }
	    if (krz2_1.rho[it + ndf * 60 - 61] >= d__) {
		kip = ndf;
		goto L213;
	    }
	    goto L300;
	}
L213:
	kipm2_1.m3 = kip;
	knot = kipm2_1.m3 - ndss + 1;
	index2 = knot - 1 << 2;
/* NOW, (KNOT,KNOT+1) IS SUB-RANGE OF RHO WHICH CONTAINS D. */
	dx = d__ - krz2_1.rho[it + kipm2_1.m3 * 60 - 61];
	c1 = intpl22_1.cford[index1 + (index2 + 1) * 60 - 61];
	c2 = intpl22_1.cford[index1 + (index2 + 2) * 60 - 61];
	c3 = intpl22_1.cford[index1 + (index2 + 3) * 60 - 61];
	c4 = intpl22_1.cford[index1 + (index2 + 4) * 60 - 61];
/* INTERPOLATION FOR OPACITY(OL) IN THE ENTRY D AND THE EACH T-GRID */
/* ESTIMATES THE PARTIAL DERIVATIVE OF OL WRT D */
/* EVALUATES THE INTERPOLATION VALUE IN THE SUB-RANGE WE DETERMINED. */
	ol0 = ((c4 * dx + c3) * dx + c2) * dx + c1;
	qodi = (c4 * 3. * dx + c3 * 2.) * dx + c2;
	++jt;
	xt[jt - 1] = gkrz2_1.gridt[it - 1];
	yto[jt - 1] = ol0;
	aqod[jt - 1] = qodi;
L300:
	;
    }
    if (jt <= 3) {
	if (lmore) {
	    its = 1;
	    itf = krz2_1.numtm;
	    lmore = FALSE_;
	    goto L333;
	}
	io___25.ciunit = luout_1.ishort;
	s_wsle(&io___25);
	do_lio(&c__9, &c__1, "ERROR KURUCZ OP: NO TABLE VALUE ", (ftnlen)32);
	do_lio(&c__5, &c__1, (char *)&d__, (ftnlen)sizeof(doublereal));
	do_lio(&c__5, &c__1, (char *)&t, (ftnlen)sizeof(doublereal));
	e_wsle();
	s_stop("", (ftnlen)0);
    }
    if (xt[0] > t || xt[jt - 1] < t) {
	return 1;
    }
/* INTERPOLATION FOR THE OPACITY IN THE ENTRY T AND D. */
/* GET THE PARTIAL DERIVATIVE OF OL WRT T. */
    intpol_(xt, yto, &jt, &t, &ol00, qotf);
    *olf = ol00;
    *of = pow_dd(&c_b15, olf);
/* QOTF = D LN(O)/D LN(T) */
/* FIND THE PARTIAL DERIVATIVE VALUE OF OL WRT D IN THE GIVEN T AND D */
    intpol_(xt, aqod, &jt, &t, qodf, &qodti);
/* QODF = D LN(O)/D LN(D) */
    return 0;
} /* kurucz2_ */

