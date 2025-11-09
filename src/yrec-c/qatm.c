/* qatm.f -- translated by f2c (version 20061008).
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
    doublereal olaol[64896]	/* was [12][104][52] */, oxa[12], ot[52], 
	    orho[104], tollaol;
    integer iolaol, numofxyz, numrho, numt;
    logical llaol, lpurez;
    integer iopurez;
} nwlaol_;

#define nwlaol_1 nwlaol_

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
    doublereal taul, ap, at, ad, ao, afxion[3];
} atmprt_;

#define atmprt_1 atmprt_

struct {
    doublereal cln, clni, c4pi, c4pil, c4pi3l, cc13, cc23, cpi;
} const1_;

#define const1_1 const1_

struct {
    doublereal hras;
    integer kttau, kttau0;
    logical lttau;
} atmos_;

#define atmos_1 atmos_

struct {
    logical lmhd;
    integer iomhd1, iomhd2, iomhd3, iomhd4, iomhd5, iomhd6, iomhd7, iomhd8;
} mhd_;

#define mhd_1 mhd_

/* Table of constant values */

static integer c__5 = 5;
static integer c__1 = 1;
static integer c__8 = 8;



/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */
/* QATM */
/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */
/* Subroutine */ int qatm_(doublereal *x0, doublereal *y, doublereal *dydx, 
	doublereal *b, doublereal *fpl, doublereal *ftl, doublereal *gl, 
	logical *latmo, logical *lderiv, logical *locond, logical *lsave, 
	doublereal *rl, doublereal *teffl, doublereal *x, doublereal *z__, 
	integer *katm, integer *ksaha)
{
    /* System generated locals */
    doublereal d__1;

    /* Builtin functions */
    double exp(doublereal), d_lg10(doublereal *);
    integer s_wsle(cilist *), do_lio(integer *, integer *, char *, ftnlen), 
	    e_wsle(void);

    /* Local variables */
    static doublereal d__, g, o, p, t, dl, ol, pl, tl, eta;
    extern doublereal hra_(doublereal *);
    static doublereal amu, qcp, qdp, emu, qdt, tau, qat, qap, qod, rmu, qot, 
	    dela, beta, qdtt, qdtp, qcpt, qcpp, beta1, beta14, fxion[3];
    extern /* Subroutine */ int meqos_(doublereal *, doublereal *, doublereal 
	    *, doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *), eqstat_(doublereal *, 
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

    /* Fortran I/O blocks */
    static cilist io___31 = { 0, 6, 0, 0, 0 };


/* QATM CALCULATES THE DERIVATIVE D(P)/D(TAU), USING THE EDDINGTON */
/* APPROXIMATION FOR A T-TAU RELATION. */
/* IT ALSO RETURNS TL,O, AND FXION FOR OUTPUT PURPOSES */
/*   Q(TAU) = 0.6666667 */
/* MHP 8/25 Removed unused variables */
/*      CHARACTER*256 FLAOL, FPUREZ */
/* MHP 8/25 Removed character file names from common block */
/* EDDINGTON APPROXIMATION */
/* KRISHNA-SWAMY APPROXIMATION (BASED ON FIT TO SOLAR ATMOSPHER) */
/* SEE KRISHNA-SWAMY, AP.J. 1966, 145, 176. */
    /* Parameter adjustments */
    --dydx;
    --y;

    /* Function Body */
    g = exp(const1_1.cln * *gl) * *fpl;
    atmprt_1.taul = *x0;
    tau = exp(const1_1.cln * atmprt_1.taul);
/* USE KTTAU TO IMPLIMENT FUTURE T TAU RELATIONS */
    if (atmos_1.kttau == 0) {
	d__1 = tau + const1_1.cc23;
	tl = *teffl - .031235 + .25 * d_lg10(&d__1);
    } else if (atmos_1.kttau == 1) {
	d__1 = tau + 1.39 - .815 * exp(-2.54 * tau) - .025 * exp(-30. * tau);
	tl = *teffl - .031235 + .25 * d_lg10(&d__1);
    } else if (atmos_1.kttau == 2) {
	tl = *teffl + hra_(&tau) - atmos_1.hras;
    }
    pl = y[1];
/* IF LMHD USE MHD EQUATION OF STATE. */
    if (mhd_1.lmhd) {
	meqos_(&tl, &t, &pl, &p, &dl, &d__, x, z__, &beta, &beta1, &beta14, 
		fxion, &rmu, &amu, &emu, &eta, &qdt, &qdp, &qcp, &dela, &qdtt,
		 &qdtp, &qat, &qap, &qcpt, &qcpp);
/*      *   EMU,ETA,QDT,QDP,QCP,DELA,QDTT,QDTP,QAT,QAP,QCPT,QCPP,LDERIV, */
/*      *   LATMO,KSAHA)  ! KC 2025-05-31 */
    } else {
	eqstat_(&tl, &t, &pl, &p, &dl, &d__, x, z__, &beta, &beta1, &beta14, 
		fxion, &rmu, &amu, &emu, &eta, &qdt, &qdp, &qcp, &dela, &qdtt,
		 &qdtp, &qat, &qap, &qcpt, &qcpp, lderiv, latmo, ksaha);
    }
    getopac_(&dl, &tl, x, z__, &o, &ol, &qod, &qot, fxion);
    dydx[1] = g * tau / (p * o);
    ++(*katm);
    atmprt_1.ap = pl;
    atmprt_1.at = tl;
    if (*lsave || pulse1_1.lpumod) {
	atmprt_1.ad = dl;
	atmprt_1.ao = o;
	atmprt_1.afxion[0] = fxion[0];
	atmprt_1.afxion[1] = fxion[1];
	atmprt_1.afxion[2] = fxion[2];
	pulse2_1.qtl = tl;
	pulse2_1.qt = exp(const1_1.cln * tl);
	pulse2_1.qpl = pl;
	pulse2_1.qp = exp(const1_1.cln * pl);
	pulse2_1.qdl = dl;
	pulse2_1.qd = exp(const1_1.cln * dl);
	pulse2_1.qo = o;
	pulse2_1.qol = ol;
	pulse2_1.qqdp = qdp;
	pulse2_1.qqed = 0.;
	pulse2_1.qqod = qod;
	pulse2_1.qqot = qot;
	pulse2_1.qdel = 0.;
	pulse2_1.qqdt = qdt;
	pulse2_1.qdela = dela;
	pulse2_1.qqcp = qcp;
	pulse2_1.qrmu = rmu;
	pulse2_1.qemu = emu;
    }
/* KC 2025-05-31 THESE MUST BE RETAINED FOR EXTERNAL PROCEDURE COMPATIBILITY. */
    if (FALSE_) {
	s_wsle(&io___31);
	do_lio(&c__5, &c__1, (char *)&(*b), (ftnlen)sizeof(doublereal));
	do_lio(&c__5, &c__1, (char *)&(*ftl), (ftnlen)sizeof(doublereal));
	do_lio(&c__8, &c__1, (char *)&(*locond), (ftnlen)sizeof(logical));
	do_lio(&c__5, &c__1, (char *)&(*rl), (ftnlen)sizeof(doublereal));
	e_wsle();
    }
    return 0;
} /* qatm_ */

