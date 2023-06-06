/* meqos.f -- translated by f2c (version 20100827).
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
    doublereal xenv, zenv, zenvm, amuenv, fxenv[12], xnew, znew, stotal, senv;
} comp_;

#define comp_1 comp_

struct {
    doublereal atime[14], tcut[5], tscut, tenv0, tenv1, tenv, tgcut;
} ctlim_;

#define ctlim_1 ctlim_

struct {
    doublereal cln, clni, c4pi, c4pil, c4pi3l, cc13, cc23, cpi;
} const1_;

#define const1_1 const1_

struct {
    doublereal cgas, ca3, ca3l, csig, csigl, cgl, cmkh, cmkhn;
} const2_;

#define const2_1 const2_

struct {
    logical ldebug, lcorr, lmilne, ltrack, lstore, lstpch;
    integer npunch;
} ccout2_;

#define ccout2_1 ccout2_

struct {
    doublereal varmhd[25];
} mhdout_;

#define mhdout_1 mhdout_

/* Table of constant values */

static doublereal c_b2 = 10.;
static integer c__9 = 9;
static integer c__1 = 1;
static integer c__5 = 5;

/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */

/*     MIHALAS, HUMMER, DAPPEN EQUATION OF STATE */

/*     IMPLIMENTED BY YC MARCH 7, 1990 */

/* CCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC */
/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */
/* MEQOS */
/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */
/* Subroutine */ int meqos_(doublereal *t10, doublereal *t, doublereal *p10, 
	doublereal *p, doublereal *d10, doublereal *d__, doublereal *xc, 
	doublereal *z__, doublereal *beta, doublereal *betai, doublereal *
	beta14, doublereal *fxion, doublereal *rmu, doublereal *amu, 
	doublereal *emu, doublereal *eta, doublereal *qdt, doublereal *qdp, 
	doublereal *qcp, doublereal *dela, doublereal *qdtt, doublereal *qdpt,
	 doublereal *qat, doublereal *qap, doublereal *qcpt, doublereal *qcpp,
	 logical *lderiv, logical *latmo, integer *ksaha)
{

    /* System generated locals */
    doublereal d__1;

    /* Builtin functions */
    double pow_dd(doublereal *, doublereal *);
    integer s_wsle(cilist *), do_lio(integer *, integer *, char *, ftnlen), 
	    e_wsle(void);
    /* Subroutine */ int s_stop(char *, ftnlen);

    /* Local variables */
    static doublereal r10, cp;
    extern /* Subroutine */ int mu_(doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *);
    static integer ier, ion;
    static doublereal rmu2, chira, chita;
    extern /* Subroutine */ int mhdpx_(doublereal *, doublereal *, doublereal 
	    *, doublereal *);

    /* Fortran I/O blocks */
    static cilist io___10 = { 0, 0, 0, 0, 0 };
    static cilist io___11 = { 0, 0, 0, 0, 0 };
    static cilist io___12 = { 0, 0, 0, 0, 0 };
    static cilist io___13 = { 0, 0, 0, 0, 0 };
    static cilist io___14 = { 0, 0, 0, 0, 0 };
    static cilist io___15 = { 0, 0, 0, 0, 0 };
    static cilist io___16 = { 0, 0, 0, 0, 0 };


/*     LATMO,KSAHA NEEDED FOR EQSAHA */
    /* Parameter adjustments */
    --fxion;

    /* Function Body */
    ier = 0;
    *t = pow_dd(&c_b2, t10);
    *p = pow_dd(&c_b2, p10);
    mhdpx_(p10, t10, xc, &r10);
    *d10 = mhdout_1.varmhd[0];
    *d__ = pow_dd(&c_b2, d10);
    *qdp = 1. / mhdout_1.varmhd[3];
    chira = mhdout_1.varmhd[3];
    chita = mhdout_1.varmhd[4];
    *qdt = -chita / chira;
    cp = mhdout_1.varmhd[8];
    *qcp = pow_dd(&c_b2, &cp);
    *qcpp = *qdp * mhdout_1.varmhd[11];
    *qcpt = mhdout_1.varmhd[12] + mhdout_1.varmhd[11] * *qdt;
    *dela = mhdout_1.varmhd[7];
    *qap = *qdp * mhdout_1.varmhd[9] * .434294481 / *dela;
    *qat = (mhdout_1.varmhd[10] + mhdout_1.varmhd[9] * *qdt) * .434294481 / *
	    dela;
    *qdpt = *qdt * (*qap - 1. + *qdp + *qcpp);
    *qdtt = *qdt * (*qat + 1. + *qdt + *qcpt);
    d__1 = mhdout_1.varmhd[19] - mhdout_1.varmhd[1];
    *beta = pow_dd(&c_b2, &d__1);
    *betai = 1. / *beta;
    *beta14 = 1. - *beta;
    for (ion = 1; ion <= 3; ++ion) {
	fxion[ion] = mhdout_1.varmhd[ion + 12];
    }
    *eta = mhdout_1.varmhd[17];
    *rmu = pow_dd(&c_b2, &mhdout_1.varmhd[19]) / (*d__ * *t);
    mu_(t, p, d__, xc, z__, &rmu2, amu, emu, beta);
    if ((d__1 = (*rmu - rmu2) / *rmu, abs(d__1)) > 5e-7) {
	io___10.ciunit = luout_1.iowr;
	s_wsle(&io___10);
	do_lio(&c__9, &c__1, " ERROR(MHD) IN MEAN WEIGHTS ... ", (ftnlen)32);
	e_wsle();
	io___11.ciunit = luout_1.iowr;
	s_wsle(&io___11);
	do_lio(&c__5, &c__1, (char *)&(*rmu), (ftnlen)sizeof(doublereal));
	do_lio(&c__5, &c__1, (char *)&rmu2, (ftnlen)sizeof(doublereal));
	e_wsle();
	io___12.ciunit = luout_1.iowr;
	s_wsle(&io___12);
	do_lio(&c__9, &c__1, "ERROR (MHD): CHECK MU", (ftnlen)21);
	e_wsle();
	io___13.ciunit = luout_1.ishort;
	s_wsle(&io___13);
	do_lio(&c__9, &c__1, " ERROR(MHD): IN MEAN WEIGHTS ... ", (ftnlen)33);
	e_wsle();
	io___14.ciunit = luout_1.ishort;
	s_wsle(&io___14);
	do_lio(&c__5, &c__1, (char *)&(*rmu), (ftnlen)sizeof(doublereal));
	do_lio(&c__5, &c__1, (char *)&rmu2, (ftnlen)sizeof(doublereal));
	e_wsle();
	io___15.ciunit = luout_1.ishort;
	s_wsle(&io___15);
	do_lio(&c__9, &c__1, "ERROR (MHD): CHECK MU", (ftnlen)21);
	e_wsle();
	s_stop("", (ftnlen)0);
    }
    return 0;
/* L999: */
    io___16.ciunit = luout_1.ishort;
    s_wsle(&io___16);
    do_lio(&c__9, &c__1, "ERROR(MHD):... MHD TABLE FAIL", (ftnlen)29);
    e_wsle();
    s_stop("", (ftnlen)0);
    return 0;
} /* meqos_ */

