/* condopacp.f -- translated by f2c (version 20100827).
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
    integer ikur2;
    char fkur2[256];
    integer icondopacp;
    char fcondopacp[256];
    logical lcondopacp;
} miscopac_;

#define miscopac_1 miscopac_

/* Table of constant values */

static integer c__5 = 5;
static integer c__1 = 1;
static integer c__15 = 15;
static integer c__19 = 19;
static integer c__64 = 64;

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*  This subroutine interpolates the electron thermal conductivity       * */
/*               from the data file "condall.d"                          * */
/*  ---------------------------------------------------  Version 23.05.99 */
/* Subroutine */ int condopacp_(doublereal *zion, doublereal *tlg, doublereal 
	*rlg, doublereal *ck, doublereal *drk, doublereal *dtk)
{
    /* Initialized data */

    static integer krun = -1;

    /* System generated locals */
    integer i__1, i__2;
    olist o__1;
    cllist cl__1;

    /* Builtin functions */
    integer f_open(olist *), s_rsfe(cilist *), e_rsfe(void), s_rsle(cilist *),
	     do_lio(integer *, integer *, char *, ftnlen), e_rsle(void);
    double d_lg10(doublereal *);
    integer f_clos(cllist *);
    /* Subroutine */ int s_stop(char *, ftnlen);

    /* Local variables */
    extern /* Subroutine */ int cinterp3_(doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, integer *, integer *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *);
    static doublereal z__, ar[64], at[19];
    static integer ip;
    static doublereal az[15];
    static integer ir, it, iz;
    static doublereal xr, xt, xz0, xz1;
    static integer irm, itm, irp;
    static doublereal zlg;
    static integer itp;
    static doublereal ckt0, ckt1, dt2k, akap[18240]	/* was [19][64][15] */
	    , cktm, cktp, drtk;
    extern /* Subroutine */ int hunt_(doublereal *, integer *, doublereal *, 
	    integer *);
    static doublereal drkt0, drkt1, drt2k, dr2kt0, dr2kt1, ckt0z0, ckt1z0, 
	    ckt0z1, ckt1z1, drktm, drktp, dr2ktm, dr2ktp, cktmz0, cktmz1, 
	    cktpz0, cktpz1, drkt0z0, drkt1z0, drkt0z1, drkt1z1, dr2kt0z0, 
	    dr2kt1z0, dr2kt0z1, dr2kt1z1, drktmz0, drktmz1, drktpz0, drktpz1, 
	    dr2ktmz0, dr2ktmz1, dr2ktpz0, dr2ktpz1;

    /* Fortran I/O blocks */
    static cilist io___3 = { 0, 0, 0, "(A)", 0 };
    static cilist io___5 = { 0, 0, 0, 0, 0 };
    static cilist io___11 = { 0, 0, 0, 0, 0 };


/* Input: Zion - ion charge, TLG - lg(T[K]), RLG - lg(rho[g/cc]) */
/* Output: CK - Log_{10} thermal conductivity (kappa) [CGS units] */
/*         DRK - d log kappa / d log rho */
/*         DTK - d log kappa / d log T */
/* **      (it is also possible to obtain all second derivatives)      *** */
/*     This Subroutine interpolates thermal conductivity from */
/*     a precalculated table condall.d available at */
/*     http://www.ioffe.rssi.ru/astro/conduct */
/*     For theoretical base of this calculation, see */
/*      A.Y.Potekhin, D.A.Baiko, P.Haensel, D.G.Yakovlev, 1999 */
/*                  Astron. Astrophys. 346, 345. */
/*     Extension from strongly- to weakly-degenerate regime */
/*     has been done using the thermal averaging - for example */
/*         A.Y.Potekhin, 1999, Astron. Astrophys. 351, 787. */
/*     Please quote these publication when using this program */
/*     SOURCE DATA FILE 'condall.d' MUST BE IN YOUR */
/*      CURRENT DIRECTORY */
/*     Please address any questions/comments to Alexander Potekhin: */
/*     e-mail: palex@astro.ioffe.rssi.ru */
/* The following three lines provide and interface to PARMIN in order to */
/* locate the Potekhin files. */
/* !! NB: These parameters must be consistent with the table "condall.d"!!! */
    if (krun != 12345) {
/* Reading */
	ip = miscopac_1.icondopacp;
	o__1.oerr = 0;
	o__1.ounit = ip;
	o__1.ofnmlen = 256;
	o__1.ofnm = miscopac_1.fcondopacp;
	o__1.orl = 0;
	o__1.osta = "OLD";
	o__1.oacc = 0;
	o__1.ofm = 0;
	o__1.oblnk = 0;
	f_open(&o__1);
/*         print*,'Reading thermal conductivity data...' */
	io___3.ciunit = ip;
	s_rsfe(&io___3);
	e_rsfe();
/* skip the first line */
	for (iz = 1; iz <= 15; ++iz) {
	    io___5.ciunit = ip;
	    s_rsle(&io___5);
	    do_lio(&c__5, &c__1, (char *)&z__, (ftnlen)sizeof(doublereal));
	    for (it = 1; it <= 19; ++it) {
		do_lio(&c__5, &c__1, (char *)&at[it - 1], (ftnlen)sizeof(
			doublereal));
	    }
	    e_rsle();
	    az[iz - 1] = d_lg10(&z__);
	    for (ir = 1; ir <= 64; ++ir) {
		io___11.ciunit = ip;
		s_rsle(&io___11);
		do_lio(&c__5, &c__1, (char *)&ar[ir - 1], (ftnlen)sizeof(
			doublereal));
		for (it = 1; it <= 19; ++it) {
		    do_lio(&c__5, &c__1, (char *)&akap[it + (ir + (iz << 6)) *
			     19 - 1236], (ftnlen)sizeof(doublereal));
		}
		e_rsle();
	    }
	}
	cl__1.cerr = 0;
	cl__1.cunit = ip;
	cl__1.csta = 0;
	f_clos(&cl__1);
	krun = 12345;
	iz = 8;
	it = 10;
	ir = 33;
/*         print*,'Potekhin Conductivity File read in.' */
    }
    zlg = d_lg10(zion);
    hunt_(az, &c__15, &zlg, &iz);
    if (iz == 0 || iz == 15) {
	s_stop("CONINTER: Z out of range", (ftnlen)24);
    }
    hunt_(at, &c__19, tlg, &it);
    if (it == 0 || it == 19) {
	s_stop("CONINTER: T out of range", (ftnlen)24);
    }
    hunt_(ar, &c__64, rlg, &ir);
    if (ir == 0 || ir == 64) {
	s_stop("CONINTER: rho out of range", (ftnlen)26);
    }
/* Computing MAX */
    i__1 = 1, i__2 = it - 1;
    itm = max(i__1,i__2);
/* Computing MIN */
    i__1 = 19, i__2 = it + 2;
    itp = min(i__1,i__2);
/* Computing MAX */
    i__1 = 1, i__2 = ir - 1;
    irm = max(i__1,i__2);
/* Computing MIN */
    i__1 = 64, i__2 = ir + 2;
    irp = min(i__1,i__2);
/* Cubic interpolation in RLG: */
/* Z0: */
    cinterp3_(&ar[irm - 1], &ar[ir - 1], &ar[ir], &ar[irp - 1], rlg, &ir, &
	    c__64, &akap[itm + (irm + (iz << 6)) * 19 - 1236], &akap[itm + (
	    ir + (iz << 6)) * 19 - 1236], &akap[itm + (ir + 1 + (iz << 6)) * 
	    19 - 1236], &akap[itm + (irp + (iz << 6)) * 19 - 1236], &cktmz0, &
	    drktmz0, &dr2ktmz0, &xr);
    cinterp3_(&ar[irm - 1], &ar[ir - 1], &ar[ir], &ar[irp - 1], rlg, &ir, &
	    c__64, &akap[it + (irm + (iz << 6)) * 19 - 1236], &akap[it + (ir 
	    + (iz << 6)) * 19 - 1236], &akap[it + (ir + 1 + (iz << 6)) * 19 - 
	    1236], &akap[it + (irp + (iz << 6)) * 19 - 1236], &ckt0z0, &
	    drkt0z0, &dr2kt0z0, &xr);
    cinterp3_(&ar[irm - 1], &ar[ir - 1], &ar[ir], &ar[irp - 1], rlg, &ir, &
	    c__64, &akap[it + 1 + (irm + (iz << 6)) * 19 - 1236], &akap[it + 
	    1 + (ir + (iz << 6)) * 19 - 1236], &akap[it + 1 + (ir + 1 + (iz <<
	     6)) * 19 - 1236], &akap[it + 1 + (irp + (iz << 6)) * 19 - 1236], 
	    &ckt1z0, &drkt1z0, &dr2kt1z0, &xr);
    cinterp3_(&ar[irm - 1], &ar[ir - 1], &ar[ir], &ar[irp - 1], rlg, &ir, &
	    c__64, &akap[itp + (irm + (iz << 6)) * 19 - 1236], &akap[itp + (
	    ir + (iz << 6)) * 19 - 1236], &akap[itp + (ir + 1 + (iz << 6)) * 
	    19 - 1236], &akap[itp + (irp + (iz << 6)) * 19 - 1236], &cktpz0, &
	    drktpz0, &dr2ktpz0, &xr);
/* Z1: */
    cinterp3_(&ar[irm - 1], &ar[ir - 1], &ar[ir], &ar[irp - 1], rlg, &ir, &
	    c__64, &akap[itm + (irm + (iz + 1 << 6)) * 19 - 1236], &akap[itm 
	    + (ir + (iz + 1 << 6)) * 19 - 1236], &akap[itm + (ir + 1 + (iz + 
	    1 << 6)) * 19 - 1236], &akap[itm + (irp + (iz + 1 << 6)) * 19 - 
	    1236], &cktmz1, &drktmz1, &dr2ktmz1, &xr);
    cinterp3_(&ar[irm - 1], &ar[ir - 1], &ar[ir], &ar[irp - 1], rlg, &ir, &
	    c__64, &akap[it + (irm + (iz + 1 << 6)) * 19 - 1236], &akap[it + (
	    ir + (iz + 1 << 6)) * 19 - 1236], &akap[it + (ir + 1 + (iz + 1 << 
	    6)) * 19 - 1236], &akap[it + (irp + (iz + 1 << 6)) * 19 - 1236], &
	    ckt0z1, &drkt0z1, &dr2kt0z1, &xr);
    cinterp3_(&ar[irm - 1], &ar[ir - 1], &ar[ir], &ar[irp - 1], rlg, &ir, &
	    c__64, &akap[it + 1 + (irm + (iz + 1 << 6)) * 19 - 1236], &akap[
	    it + 1 + (ir + (iz + 1 << 6)) * 19 - 1236], &akap[it + 1 + (ir + 
	    1 + (iz + 1 << 6)) * 19 - 1236], &akap[it + 1 + (irp + (iz + 1 << 
	    6)) * 19 - 1236], &ckt1z1, &drkt1z1, &dr2kt1z1, &xr);
    cinterp3_(&ar[irm - 1], &ar[ir - 1], &ar[ir], &ar[irp - 1], rlg, &ir, &
	    c__64, &akap[itp + (irm + (iz + 1 << 6)) * 19 - 1236], &akap[itp 
	    + (ir + (iz + 1 << 6)) * 19 - 1236], &akap[itp + (ir + 1 + (iz + 
	    1 << 6)) * 19 - 1236], &akap[itp + (irp + (iz + 1 << 6)) * 19 - 
	    1236], &cktpz1, &drktpz1, &dr2ktpz1, &xr);
/* Linear interpolation in ZLG: */
    xz1 = (zlg - az[iz - 1]) / (az[iz] - az[iz - 1]);
    xz0 = 1. - xz1;
    cktm = xz0 * cktmz0 + xz1 * cktmz1;
    drktm = xz0 * drktmz0 + xz1 * drktmz1;
    dr2ktm = xz0 * dr2ktmz0 + xz1 * dr2ktmz1;
    ckt0 = xz0 * ckt0z0 + xz1 * ckt0z1;
    drkt0 = xz0 * drkt0z0 + xz1 * drkt0z1;
    dr2kt0 = xz0 * dr2kt0z0 + xz1 * dr2kt0z1;
    ckt1 = xz0 * ckt1z0 + xz1 * ckt1z1;
    drkt1 = xz0 * drkt1z0 + xz1 * drkt1z1;
    dr2kt1 = xz0 * dr2kt1z0 + xz1 * dr2kt1z1;
    cktp = xz0 * cktpz0 + xz1 * cktpz1;
    drktp = xz0 * drktpz0 + xz1 * drktpz1;
    dr2ktp = xz0 * dr2ktpz0 + xz1 * dr2ktpz1;
/* Cubic interpolation in TLG: */
    cinterp3_(&at[itm - 1], &at[it - 1], &at[it], &at[itp - 1], tlg, &it, &
	    c__19, &cktm, &ckt0, &ckt1, &cktp, ck, dtk, &dt2k, &xt);
/* input: values of lg kappa */
/* lg kappa, d lg k / d lg T, d2 lg k / d2 lg T */
    cinterp3_(&at[itm - 1], &at[it - 1], &at[it], &at[itp - 1], tlg, &it, &
	    c__19, &drktm, &drkt0, &drkt1, &drktp, drk, &drtk, &drt2k, &xt);
/* input: values of d lg k / d lg rho */
/* d lg k / d lg rho, d2 lgk/(d lgT d lg rho) */
    return 0;
} /* condopacp_ */

/* Subroutine */ int cinterp3_(doublereal *zm, doublereal *z0, doublereal *z1,
	 doublereal *zp, doublereal *z__, integer *n0, integer *mxnv, 
	doublereal *vm, doublereal *v0, doublereal *v1, doublereal *vp, 
	doublereal *vf, doublereal *df, doublereal *d2, doublereal *xh)
{
    /* System generated locals */
    doublereal d__1, d__2;

    /* Builtin functions */
    /* Subroutine */ int s_stop(char *, ftnlen);

    /* Local variables */
    static doublereal h__, x, c2, c3, hm, v01, hp, v11;

/* Given 4 values of Z and 4 values of V, find VF corresponding to 5th Z */
/*                                                       Version 23.05.99 */
/*   Output: VF - interpolated value of function */
/*           DF - interpolated derivative */
/*           D2 - interpolated second derivative */
/*           XH - fraction of the path from N0 to N0+1 */
    if (*n0 <= 0 || *n0 >= *mxnv) {
	s_stop("CINTERP: N0 out of range", (ftnlen)24);
    }
    x = *z__ - *z0;
    h__ = *z1 - *z0;
/* basic interval */
    *xh = x / h__;
    if (*n0 > 1) {
	hm = *z0 - *zm;
/* left adjoint interval */
/* Computing 2nd power */
	d__1 = h__;
/* Computing 2nd power */
	d__2 = hm;
	v01 = ((*v1 - *v0) / (d__1 * d__1) + (*v0 - *vm) / (d__2 * d__2)) / (
		1. / h__ + 1. / hm);
/* left derivative */
    }
    if (*n0 < *mxnv - 1) {
	hp = *zp - *z1;
/* right adjoint interval */
/* Computing 2nd power */
	d__1 = h__;
/* Computing 2nd power */
	d__2 = hp;
	v11 = ((*v1 - *v0) / (d__1 * d__1) + (*vp - *v1) / (d__2 * d__2)) / (
		1. / h__ + 1. / hp);
/* right derivative */
    }
    if (*n0 > 1 && *n0 < *mxnv - 1) {
/* Cubic interpolation */
	c2 = (*v1 - *v0) * 3. - h__ * (v11 + v01 * 2.);
	c3 = h__ * (v01 + v11) - (*v1 - *v0) * 2.;
/* Computing 2nd power */
	d__1 = *xh;
/* Computing 3rd power */
	d__2 = *xh;
	*vf = *v0 + v01 * x + c2 * (d__1 * d__1) + c3 * (d__2 * (d__2 * d__2))
		;
/* Computing 2nd power */
	d__1 = *xh;
	*df = v01 + (c2 * 2. * *xh + c3 * 3. * (d__1 * d__1)) / h__;
/* Computing 2nd power */
	d__1 = h__;
	*d2 = (c2 * 2. + c3 * 6. * *xh) / (d__1 * d__1);
	goto L10;
    }
    if (*n0 == 1) {
/* Quadratic interpolation */
	c2 = *v0 - *v1 + v11 * h__;
/* Computing 2nd power */
	d__1 = 1. - *xh;
	*vf = *v1 - v11 * (h__ - x) + c2 * (d__1 * d__1);
	*df = v11 - c2 * 2. * (1. - *xh) / h__;
/* Computing 2nd power */
	d__1 = h__;
	*d2 = c2 * 2. / (d__1 * d__1);
    } else {
/* N0=MXNV-1 */
	c2 = *v1 - *v0 - v01 * h__;
/* Computing 2nd power */
	d__1 = *xh;
	*vf = *v0 + v01 * x + c2 * (d__1 * d__1);
	*df = v01 + c2 * 2. * *xh / h__;
/* Computing 2nd power */
	d__1 = h__;
	*d2 = c2 * 2. / (d__1 * d__1);
    }
L10:
    return 0;
} /* cinterp3_ */

/* Subroutine */ int hunt_(doublereal *xx, integer *n, doublereal *x, integer 
	*jlo)
{
    static integer jm, inc, jhi;
    static logical ascnd;

/*   W.H.Press, B.P.Flannery, S.A.Teukolsky, W.T.Vetterling */
/*   Numerical Receipes(Cambridge Univ., 1986) */
/*     Given an array XX of length N, and given a value X, */
/*     returns a value JLO such that X is between XX(JLO) and XX(JLO+1). */
/*     XX must be monotonic, either increasing or decreasing. */
/*     JLO=0 or JLO=N is returned to indicate that X is out of range. */
/*     JLO on input is taken as the initial guess for JLO on output. */
    /* Parameter adjustments */
    --xx;

    /* Function Body */
    ascnd = xx[*n] > xx[1];
/* true if ascending order, false otherwise */
    if (*jlo <= 0 || *jlo > *n) {
/* Input guess not useful. */
	*jlo = 0;
	jhi = *n + 1;
	goto L3;
/* go immediately to bisection */
    }
    inc = 1;
/* set the hunting increment */
    if (*x >= xx[*jlo] == ascnd) {
/* Hunt up: */
L1:
	jhi = *jlo + inc;
	if (jhi > *n) {
/* Done hunting, since off end of table */
	    jhi = *n + 1;
	} else if (*x >= xx[jhi] == ascnd) {
/* Not done hunting */
	    *jlo = jhi;
	    inc += inc;
	    goto L1;
	}
    } else {
/* Hunt down: */
	jhi = *jlo;
L2:
	*jlo = jhi - inc;
	if (*jlo < 1) {
/* Done hunting, since off end of table */
	    *jlo = 0;
	} else if (*x < xx[*jlo] == ascnd) {
/* Not done hunting */
	    jhi = *jlo;
	    inc += inc;
/* so double the increment */
	    goto L2;
/* and try again */
	}
/* Done hunting, value bracketed */
    }
/*   Hunt is done, so begin the final bisection phase: */
L3:
    if (jhi - *jlo == 1) {
	return 0;
    }
    jm = (jhi + *jlo) / 2;
    if (*x >= xx[jm] == ascnd) {
	*jlo = jm;
    } else {
	jhi = jm;
    }
    goto L3;
} /* hunt_ */

