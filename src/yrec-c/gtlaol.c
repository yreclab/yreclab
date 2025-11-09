/* gtlaol.f -- translated by f2c (version 20061008).
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

/* Table of constant values */

static integer c__1 = 1;
static doublereal c_b7 = 1e30;
static doublereal c_b14 = 10.;



/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */
/*     GET LAOL OPACITY */
/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */
/* Subroutine */ int gtlaol_(doublereal *dl, doublereal *tl, doublereal *x, 
	doublereal *o, doublereal *ol, doublereal *qod, doublereal *qot)
{
    /* Format strings */
    static char fmt_120[] = "(\002 OUTSIDE OPACITY TABLE, IN DENSITY.  \002"
	    ",\002LOG(RHO)=\002,1pe12.3,\002 LOG(T)=\002,1pe12.3)";
    static char fmt_121[] = "(\002 OUTSIDE OPACITY TABLE, IN TEMPERATURE. "
	    " \002,\002LOG(RHO)=\002,1pe12.3,\002 LOG(T)=\002,1pe12.3)";
    static char fmt_122[] = "(\002 OUTSIDE OPACITY TABLE.  \002,\002LOG(RH"
	    "O)=\002,1pe12.3,\002 LOG(T)=\002,1pe12.3)";

    /* System generated locals */
    integer i__1, i__2, i__3;

    /* Builtin functions */
    double log(doublereal);
    integer s_wsfe(cilist *), do_fio(integer *, char *, ftnlen), e_wsfe(void);
    /* Subroutine */ void s_stop(char *, ftnlen);
    double pow_dd(doublereal *, doublereal *);

    /* Local variables */
    static integer ir, it, jt, ix, jx;
    static doublereal tr[104], tt[52], rx, xx[4];
    static integer jt1, jt2, khi;
    static doublereal rdl;
    static integer klo;
    static doublereal rol, rtl, top[104];
    static integer jxp1;
    static doublereal top1[52], top2[4], dodr[52], tdor[104], tdot[52], toll;
    static integer nums;
    extern /* Subroutine */ int xrng4_(integer *, integer *, integer *, 
	    integer *);
    static doublereal dodrx[4], dodtx[4], slope;
    static integer numts, numxs;
    extern /* Subroutine */ int locate_(doublereal *, integer *, doublereal *,
	     integer *), splint_(doublereal *, doublereal *, integer *, 
	    doublereal *, doublereal *, doublereal *, integer *, integer *), 
	    cspline_(doublereal *, doublereal *, integer *, doublereal *, 
	    doublereal *, doublereal *);

    /* Fortran I/O blocks */
    static cilist io___26 = { 0, 0, 0, fmt_120, 0 };
    static cilist io___32 = { 0, 0, 0, fmt_121, 0 };
    static cilist io___33 = { 0, 0, 0, fmt_122, 0 };


/* MHP 8/25 Removed character file names from common block */
/*      CHARACTER*256 FLAOL, FPUREZ */
/* MHP 8/25 Removed character file names from common block */

/*     1. CUBIC SPLINE INTERPOLATE IN DENSITY */
/*     2. CUBIC SPLINE INTERPOLATE IN TEMPERATURE */
/*     3. LINEAR INTERPOLATE IN COMPOSITION */
/*     IF WITHIN TOLLAOL OF EDGE THEN LINEAR EXTRAPOLATE */

/*     TOLLAOL PERMITS SOME EXTRAPLOATION BEYOND TABLE EDGE. */
    toll = log(nwlaol_1.tollaol);
/*     FACTOR = 3.0E-1 */
    rx = *x;
    rtl = *tl;
/*     RTL1 = TL+FACTOR */
/*     RTL2 = TL-FACTOR */
    rdl = *dl;
    locate_(nwlaol_1.ot, &nwlaol_1.numt, &rtl, &jt);
    locate_(nwlaol_1.oxa, &nwlaol_1.numofxyz, &rx, &jx);
    if (jx == nwlaol_1.numofxyz) {
	jx = nwlaol_1.numofxyz - 1;
    }
    if (jx == 0) {
	jx = 1;
    }
    numxs = 0;
    jxp1 = jx + 1;
    i__1 = jxp1;
    for (ix = jx; ix <= i__1; ++ix) {
	numts = 0;
/*        GET RANGE OF FOUR TT SURROUNDING T */
	xrng4_(&jt, &nwlaol_1.numt, &jt1, &jt2);
	i__2 = jt2;
	for (it = jt1; it <= i__2; ++it) {
	    nums = slaol_1.numrs[ix + it * 12 - 13];
	    if (nums >= 4) {
		i__3 = nums;
		for (ir = 1; ir <= i__3; ++ir) {
		    top[ir - 1] = slaol_1.slaoll[ix + (ir + it * 104) * 12 - 
			    1261];
		    tr[ir - 1] = slaol_1.srhol[ix + (ir + it * 104) * 12 - 
			    1261];
		    tdor[ir - 1] = slaol_1.sdorl[ix + (ir + it * 104) * 12 - 
			    1261];
		}
		if (rdl > tr[0] && rdl < tr[nums - 1]) {
		    splint_(tr, top, &nums, tdor, &rdl, &rol, &klo, &khi);
		    ++numts;
		    top1[numts - 1] = rol;
		    tt[numts - 1] = nwlaol_1.ot[it - 1];
		    dodr[numts - 1] = (top[khi - 1] - top[klo - 1]) / (tr[khi 
			    - 1] - tr[klo - 1]);
		} else if (rdl > tr[0] - toll && rdl <= tr[0]) {
/*                 PUT LINEAR EXTRAPOLATION ROUTINES HERE */
		    slope = (top[1] - top[0]) / (tr[1] - tr[0]);
		    rol = top[0] + slope * (rdl - tr[0]);
/*                 CALL SPLINT(TR,TOP,NUMS,TDOR,RDL, ROL1, KLO, KHI) */
		    ++numts;
		    top1[numts - 1] = rol;
		    tt[numts - 1] = nwlaol_1.ot[it - 1];
		    dodr[numts - 1] = slope;
		} else if (rdl >= tr[nums - 1] && rdl < tr[nums - 1] + toll) {
/*                 PUT LINEAR EXTRAPOLATION ROUTINES HERE */
		    slope = (top[nums - 2] - top[nums - 1]) / (tr[nums - 2] - 
			    tr[nums - 1]);
		    rol = top[nums - 1] + slope * (rdl - tr[nums - 1]);
/*                 CALL SPLINT(TR,TOP,NUMS,TDOR,RDL, ROL1, KLO, KHI) */
		    ++numts;
		    top1[numts - 1] = rol;
		    tt[numts - 1] = nwlaol_1.ot[it - 1];
		    dodr[numts - 1] = slope;
		}
	    } else {
		io___26.ciunit = luout_1.ishort;
		s_wsfe(&io___26);
		do_fio(&c__1, (char *)&(*dl), (ftnlen)sizeof(doublereal));
		do_fio(&c__1, (char *)&(*tl), (ftnlen)sizeof(doublereal));
		e_wsfe();
		s_stop("", (ftnlen)0);
	    }
	}
	if (numts >= 4) {
	    cspline_(tt, top1, &numts, &c_b7, &c_b7, tdot);
	    splint_(tt, top1, &numts, tdot, &rtl, &rol, &klo, &khi);
	    ++numxs;
	    top2[numxs - 1] = rol;
	    slope = (dodr[khi - 1] - dodr[klo - 1]) / (tt[khi - 1] - tt[klo - 
		    1]);
	    dodrx[numxs - 1] = dodr[klo - 1] + slope * (rtl - tt[klo - 1]);
	    dodtx[numxs - 1] = (top1[khi - 1] - top1[klo - 1]) / (tt[khi - 1] 
		    - tt[klo - 1]);
	    xx[numxs - 1] = nwlaol_1.oxa[ix - 1];
	} else {
	    io___32.ciunit = luout_1.ishort;
	    s_wsfe(&io___32);
	    do_fio(&c__1, (char *)&(*dl), (ftnlen)sizeof(doublereal));
	    do_fio(&c__1, (char *)&(*tl), (ftnlen)sizeof(doublereal));
	    e_wsfe();
	    s_stop("", (ftnlen)0);
	}
    }
    if (numxs >= 2) {
	slope = (top2[1] - top2[0]) / (xx[1] - xx[0]);
	rol = top2[0] + slope * (*x - xx[0]);
/*        SLOPE = (QOT2-QOT1)/(XX(2)-XX(1)) */
	slope = (dodtx[1] - dodtx[0]) / (xx[1] - xx[0]);
	*qot = dodtx[0] + slope * (*x - xx[0]);
	slope = (dodrx[1] - dodrx[0]) / (xx[1] - xx[0]);
	*qod = dodrx[0] + slope * (*x - xx[0]);
	if (rol > 35.) {
	    *o = 1e35;
	    *ol = 35.;
	} else {
	    *o = pow_dd(&c_b14, &rol);
	    *ol = rol;
	}
    } else {
	io___33.ciunit = luout_1.ishort;
	s_wsfe(&io___33);
	do_fio(&c__1, (char *)&(*dl), (ftnlen)sizeof(doublereal));
	do_fio(&c__1, (char *)&(*tl), (ftnlen)sizeof(doublereal));
	e_wsfe();
	s_stop("", (ftnlen)0);
    }
    return 0;
} /* gtlaol_ */

