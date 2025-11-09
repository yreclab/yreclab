/* gtpurz.f -- translated by f2c (version 20061008).
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
    doublereal olaol[64896]	/* was [12][104][52] */, oxa[12], ot[52], 
	    orho[104], tollaol;
    integer iolaol, numofxyz, numrho, numt;
    logical llaol, lpurez;
    integer iopurez;
} nwlaol_;

#define nwlaol_1 nwlaol_

struct {
    doublereal slaoll[64896]	/* was [12][104][52] */, srhol[64896]	/* 
	    was [12][104][52] */, sdorl[64896]	/* was [12][104][52] */;
    integer numrs[624]	/* was [12][52] */;
} slaol_;

#define slaol_1 slaol_

struct {
    doublereal zolaol[5408]	/* was [104][52] */, zot[52], zorho[104];
    integer numrhoz, numtz;
} zlaol_;

#define zlaol_1 zlaol_

struct {
    doublereal zslaoll[5408]	/* was [104][52] */, zsrhol[5408]	/* 
	    was [104][52] */, zsdorl[5408]	/* was [104][52] */;
    integer numrsz[52];
} zslaol_;

#define zslaol_1 zslaol_

/* Table of constant values */

static integer c__1 = 1;
static doublereal c_b7 = 1e30;
static doublereal c_b14 = 10.;



/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */
/*     GET LAOL OPACITY FOR PURE Z */
/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */
/* Subroutine */ int gtpurz_(doublereal *dl, doublereal *tl, doublereal *o, 
	doublereal *ol, doublereal *qod, doublereal *qot)
{
    /* Format strings */
    static char fmt_120[] = "(\002 OUTSIDE Z OPACITY TABLE, IN DENSITY.  "
	    "\002,\002LOG(RHO)=\002,1pe12.3,\002 LOG(T)=\002,1pe12.3)";
    static char fmt_121[] = "(\002 OUTSIDE Z OPACITY TABLE, IN TEMPERATURE"
	    ".  \002,\002LOG(RHO)=\002,1pe12.3,\002 LOG(T)=\002,1pe12.3)";

    /* System generated locals */
    integer i__1, i__2;

    /* Builtin functions */
    double log(doublereal);
    integer s_wsfe(cilist *), do_fio(integer *, char *, ftnlen), e_wsfe(void);
    /* Subroutine */ void s_stop(char *, ftnlen);
    double pow_dd(doublereal *, doublereal *);

    /* Local variables */
    static integer ir, it, jt;
    static doublereal tr[104], tt[52];
    static integer jt1, jt2, khi;
    static doublereal rdl;
    static integer klo;
    static doublereal rol, rtl, top[104], top1[52], dodr[52], tdor[104], tdot[
	    52], toll;
    static integer nums;
    extern /* Subroutine */ int xrng4_(integer *, integer *, integer *, 
	    integer *);
    static doublereal slope;
    static integer numts;
    extern /* Subroutine */ int locate_(doublereal *, integer *, doublereal *,
	     integer *), splint_(doublereal *, doublereal *, integer *, 
	    doublereal *, doublereal *, doublereal *, integer *, integer *), 
	    cspline_(doublereal *, doublereal *, integer *, doublereal *, 
	    doublereal *, doublereal *);

    /* Fortran I/O blocks */
    static cilist io___21 = { 0, 0, 0, fmt_120, 0 };
    static cilist io___23 = { 0, 0, 0, fmt_121, 0 };


/* MHP 8/25 Removed unused variables */
/*      CHARACTER*256 FLAOL, FPUREZ */
/* MHP 8/25 Removed character file names from common block */
/* DBG 12/95 ARRAYS FOR PURE Z TABLE */

/*     1. CUBIC SPLINE INTERPOLATE IN DENSITY */
/*     2. CUBIC SPLINE INTERPOLATE IN TEMPERATURE */
/*     IF WITHIN TOLLAOL OF EDGE THEN LINEAR EXTRAPOLATE */

/*     TOLLAOL PERMITS SOME EXTRAPLOATION BEYOND TABLE EDGE. */
    toll = log(nwlaol_1.tollaol);
    rtl = *tl;
    rdl = *dl;
    locate_(zlaol_1.zot, &zlaol_1.numtz, &rtl, &jt);
    numts = 0;
/*     GET RANGE OF FOUR TT SURROUNDING T */
    xrng4_(&jt, &zlaol_1.numtz, &jt1, &jt2);
    i__1 = jt2;
    for (it = jt1; it <= i__1; ++it) {
	nums = zslaol_1.numrsz[it - 1];
	if (nums >= 4) {
	    i__2 = nums;
	    for (ir = 1; ir <= i__2; ++ir) {
		top[ir - 1] = zslaol_1.zslaoll[ir + it * 104 - 105];
		tr[ir - 1] = zslaol_1.zsrhol[ir + it * 104 - 105];
		tdor[ir - 1] = zslaol_1.zsdorl[ir + it * 104 - 105];
	    }
	    if (rdl > tr[0] && rdl < tr[nums - 1]) {
		splint_(tr, top, &nums, tdor, &rdl, &rol, &klo, &khi);
		++numts;
		top1[numts - 1] = rol;
		tt[numts - 1] = zlaol_1.zot[it - 1];
		dodr[numts - 1] = (top[khi - 1] - top[klo - 1]) / (tr[khi - 1]
			 - tr[klo - 1]);
	    } else if (rdl > tr[0] - toll && rdl <= tr[0]) {
/*              PUT LINEAR EXTRAPOLATION ROUTINES HERE */
		slope = (top[1] - top[0]) / (tr[1] - tr[0]);
		rol = top[0] + slope * (rdl - tr[0]);
		++numts;
		top1[numts - 1] = rol;
		tt[numts - 1] = zlaol_1.zot[it - 1];
		dodr[numts - 1] = slope;
	    } else if (rdl >= tr[nums - 1] && rdl < tr[nums - 1] + toll) {
/*              PUT LINEAR EXTRAPOLATION ROUTINES HERE */
		slope = (top[nums - 2] - top[nums - 1]) / (tr[nums - 2] - tr[
			nums - 1]);
		rol = top[nums - 1] + slope * (rdl - tr[nums - 1]);
		++numts;
		top1[numts - 1] = rol;
		tt[numts - 1] = zlaol_1.zot[it - 1];
		dodr[numts - 1] = slope;
	    }
	} else {
	    io___21.ciunit = luout_1.ishort;
	    s_wsfe(&io___21);
	    do_fio(&c__1, (char *)&(*dl), (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&(*tl), (ftnlen)sizeof(doublereal));
	    e_wsfe();
	    s_stop("", (ftnlen)0);
	}
    }
    if (numts >= 4) {
	cspline_(tt, top1, &numts, &c_b7, &c_b7, tdot);
	splint_(tt, top1, &numts, tdot, &rtl, &rol, &klo, &khi);
	slope = (dodr[khi - 1] - dodr[klo - 1]) / (tt[khi - 1] - tt[klo - 1]);
	*qod = dodr[klo - 1] + slope * (rtl - tt[klo - 1]);
	*qot = (top1[khi - 1] - top1[klo - 1]) / (tt[khi - 1] - tt[klo - 1]);
    } else {
	io___23.ciunit = luout_1.ishort;
	s_wsfe(&io___23);
	do_fio(&c__1, (char *)&(*dl), (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&(*tl), (ftnlen)sizeof(doublereal));
	e_wsfe();
	s_stop("", (ftnlen)0);
    }
    if (rol > 35.) {
	*o = 1e35;
	*ol = 35.;
    } else {
	*o = pow_dd(&c_b14, &rol);
	*ol = rol;
    }
    return 0;
} /* gtpurz_ */

