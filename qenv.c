/* qenv.f -- translated by f2c (version 20100827).
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
    doublereal xmsol;
    logical lpulse;
    integer ipver;
} pulse_;

#define pulse_1 pulse_

struct {
    doublereal pqdp[5000], pqed[5000], pqet[5000], pqod[5000], pqot[5000], 
	    pqcp[5000], prmu[5000], pqdt[5000], pemu[5000];
    logical lpumod;
} pulse1_;

#define pulse1_1 pulse1_

struct {
    doublereal qqdp, qqed, qqet, qqod, qqot, qdel, qdela, qqcp, qrmu, qtl, 
	    qpl, qdl, qo, qol, qt, qp, qqdt, qemu, qd, qfs;
} pulse2_;

#define pulse2_1 pulse2_

struct {
    doublereal xenv, zenv, zenvm, amuenv, fxenv[12], xnew, znew, stotal, senv;
} comp_;

#define comp_1 comp_

struct {
    doublereal cln, clni, c4pi, c4pil, c4pi3l, cc13, cc23, cpi;
} const1_;

#define const1_1 const1_

struct {
    doublereal cgas, ca3, ca3l, csig, csigl, cgl, cmkh, cmkhn;
} const2_;

#define const2_1 const2_

struct {
    doublereal ep, et, er, es, ed, eo, ebeta, edel[3], efxion[3], evel;
} envprt_;

#define envprt_1 envprt_

struct {
    logical lexcom;
} flag_;

#define flag_1 flag_

struct {
    logical lmhd;
    integer iomhd1, iomhd2, iomhd3, iomhd4, iomhd5, iomhd6, iomhd7, iomhd8;
} mhd_;

#define mhd_1 mhd_

struct {
    doublereal dpenv, alphac, alphae, alpham;
    integer iov1, iov2, iovim;
    logical lovstc, lovste, lovstm, lsemic, ladov;
} dpmix_;

#define dpmix_1 dpmix_



/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */
/* QENV */
/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */
/* Subroutine */ int qenv_(doublereal *x0, doublereal *y, doublereal *dydx, 
	doublereal *b, doublereal *fpl, doublereal *ftl, doublereal *gl, 
	logical *latmo, logical *lderiv, logical *locond, logical *lsave, 
	doublereal *rl, doublereal *teffl, doublereal *x, doublereal *z__, 
	integer *kenv, integer *ksaha)
{
    /* Builtin functions */
    double exp(doublereal);

    /* Local variables */
    static doublereal d__, o, p, t, dl, ol, pl, sl, tl, del, eta, amu, qcp, 
	    qdp, emu, qat, qdt, qap, qod, vel, rmu, qot, dela, beta, delr, 
	    qact, qacp, qacr, beta1, qdtt, qdtp, qcpt, qcpp, beta14;
    static logical lconv;
    static doublereal fxion[3];
    extern /* Subroutine */ int meqos_(doublereal *, doublereal *, doublereal 
	    *, doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, logical *, logical *, 
	    integer *), tpgrad_(doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, logical *,
	     logical *, doublereal *, doublereal *), eqstat_(doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, logical *, logical *, integer *), getopac_(
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *);

    /* Parameter adjustments */
    --dydx;
    --y;

    /* Function Body */
    pl = *x0;
    sl = y[1] + comp_1.stotal;
    tl = y[2];
    *rl = y[3];
    if (mhd_1.lmhd) {
	meqos_(&tl, &t, &pl, &p, &dl, &d__, x, z__, &beta, &beta1, &beta14, 
		fxion, &rmu, &amu, &emu, &eta, &qdt, &qdp, &qcp, &dela, &qdtt,
		 &qdtp, &qat, &qap, &qcpt, &qcpp, lderiv, latmo, ksaha);
    } else {
	eqstat_(&tl, &t, &pl, &p, &dl, &d__, x, z__, &beta, &beta1, &beta14, 
		fxion, &rmu, &amu, &emu, &eta, &qdt, &qdp, &qcp, &dela, &qdtt,
		 &qdtp, &qat, &qap, &qcpt, &qcpp, lderiv, latmo, ksaha);
    }
    getopac_(&dl, &tl, x, z__, &o, &ol, &qod, &qot, fxion);
    dpmix_1.iovim = -1;
    tpgrad_(&tl, &t, &pl, &p, &d__, rl, &sl, b, &o, &qdt, &qdp, &qot, &qod, &
	    qcp, &del, &delr, &dela, &qdtt, &qdtp, &qat, &qap, &qact, &qacp, &
	    qacr, &qcpt, &qcpp, &vel, lderiv, &lconv, fpl, ftl);
    dydx[1] = -exp(const1_1.cln * (const1_1.c4pil + *rl * 4. + pl - 
	    const2_1.cgl - sl - sl)) / *fpl;
    dydx[2] = del;
    dydx[3] = -exp(const1_1.cln * (pl + *rl - const2_1.cgl - sl - dl)) * *fpl;
    ++(*kenv);
/* 07/02 ALWAYS STORE THE BASIC STRUCTURE VARIABLES. */
    envprt_1.ep = pl;
    envprt_1.et = tl;
    envprt_1.es = sl - comp_1.stotal;
    envprt_1.er = *rl;
    envprt_1.ed = dl;
    envprt_1.evel = vel;
    if (*lsave || pulse1_1.lpumod) {
/* 	 EP = PL */
/* 	 ET = TL */
/* 	 ES = SL - STOTAL */
/* 	 ER = RL */
/* 	 ED = DL */
	envprt_1.eo = o;
	envprt_1.ebeta = beta;
	envprt_1.edel[0] = delr;
	envprt_1.edel[1] = dela;
	envprt_1.edel[2] = del;
	envprt_1.efxion[0] = fxion[0];
	envprt_1.efxion[1] = fxion[1];
	envprt_1.efxion[2] = fxion[2];
/* 	 EVEL = VEL */
	pulse2_1.qtl = tl;
	pulse2_1.qt = exp(const1_1.cln * tl);
	pulse2_1.qpl = pl;
	pulse2_1.qp = exp(const1_1.cln * pl);
	pulse2_1.qdl = dl;
	pulse2_1.qd = exp(const1_1.cln * dl);
	pulse2_1.qo = o;
	pulse2_1.qol = ol;
	pulse2_1.qfs = exp(const1_1.cln * (sl - comp_1.stotal));
	pulse2_1.qqdp = qdp;
	pulse2_1.qqed = 0.;
	pulse2_1.qqod = qod;
	pulse2_1.qqot = qot;
	pulse2_1.qdel = del;
	pulse2_1.qqdt = qdt;
	pulse2_1.qdela = dela;
	pulse2_1.qqcp = qcp;
	pulse2_1.qrmu = rmu;
	pulse2_1.qemu = emu;
    }
    return 0;
} /* qenv_ */

