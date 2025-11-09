/* eqscvg.f -- translated by f2c (version 20061008).
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
    doublereal cgas, ca3, ca3l, csig, csigl, cgl, cmkh, cmkhn;
} const2_;

#define const2_1 const2_

struct {
    doublereal tlogx[63], tablex[57456]	/* was [63][76][12] */, tabley[57456]	
	    /* was [63][76][12] */, smix[4788]	/* was [63][76] */, tablez[
	    62244]	/* was [63][76][13] */, tablenv[57456]	/* was [63][
	    76][12] */;
    integer nptsx[63];
    logical lscv;
    integer idt, idp;
} scveos_;

#define scveos_1 scveos_

struct {
    doublereal xenv, zenv, zenvm, amuenv, fxenv[12], xnew, znew, stotal, senv;
} comp_;

#define comp_1 comp_

/* SUBROUTINE FOR INTERPOLATING IN THE GENERAL ABUNDANCE TABLES OF THE SCV */
/* EQUATION OF STATE. */
/*       SUBROUTINE EQSCVG(TL,T,PL,P,DL,D,X,Z,BETA,BETAI,BETA14,FXION,RMU, */
/*      *AMU,EMU,ETA,QDT,QDP,QCP,DELA,LCALC)  ! KC 2025-05-31 */
/* Subroutine */ int eqscvg_(doublereal *tl, doublereal *t, doublereal *p, 
	doublereal *dl, doublereal *d__, doublereal *x, doublereal *z__, 
	doublereal *beta, doublereal *fxion, doublereal *qdt, doublereal *qdp,
	 doublereal *qcp, doublereal *dela, logical *lcalc)
{
    /* System generated locals */
    integer i__1;
    doublereal d__1;

    /* Builtin functions */
    double d_lg10(doublereal *), exp(doublereal);

    /* Local variables */
    static doublereal xtf_he_e__, xtf_hepp__;
    static integer i__, j, k;
    static doublereal y, s0;
    static integer ii, jj;
    static doublereal fp[4], ft[4], pp, sm, qr[4], ur, sx, sy, fpd[4], ftd[4];
    static integer jjj;
    static doublereal ddx, ddy, ddz, xhp, qpt, sxl, syl, qut, qcp0, qdp0, 
	    qdt0, qpt0, qst0, prad, pgas, denx, deny, denz, xhep, temp[12]	
	    /* was [4][3] */, qdpx, qdpy, qdpz, qdtx, qdty, qdtz, qsmt, qstx, 
	    qsty, qutz, betm1, denxl, denyl, denzl, xhepp, qutzl, xtf_h1__, 
	    xtf_h2__, xtf_he__, xtf_hp__;
    extern /* Subroutine */ int interp_(doublereal *, doublereal *, 
	    doublereal *, doublereal *);
    static doublereal xtf_h_e__, xtf_hep__;

/* MHP  5/97 ADDED COMMON BLOCK FOR SCV EOS TABLES */
/*       DIMENSION ATOMWT(4),QR(4),FT(4),FTD(4),  ! KC 2025-05-31 */
/*       DATA ATOMWT/0.9921D0,0.24975D0,0.08322D0,0.4995D0/ */
/*       DATA CMH,CMHE,CBOLTZ/1.67357D-24,6.646442D-24,1.380658D-16/ */
/* FIND GAS PRESSURE (WHICH IS THE QUANTITY WHICH IS TABULATED). */
    /* Parameter adjustments */
    --fxion;

    /* Function Body */
    betm1 = 1. - *beta;
    d__1 = *beta * *p;
    pp = d_lg10(&d__1);
/*  CHECK IF THE POINT IS WITHIN THE TABLE */
    if (*tl < scveos_1.tlogx[0] || *tl > scveos_1.tlogx[62] || pp < 4.) {
	*lcalc = FALSE_;
	return 0;
    }
/*  FIND NEAREST POINTS IN TEMPERATURE. */
    if (*tl < scveos_1.tlogx[scveos_1.idt]) {
/* SEARCH DOWN TO FIND NEAREST 4 TABLE ELEMENTS */
	for (i__ = scveos_1.idt; i__ >= 1; --i__) {
	    if (*tl > scveos_1.tlogx[i__ - 1]) {
		ii = i__ - 1;
		goto L10;
	    }
	}
	ii = 1;
L10:
	scveos_1.idt = max(1,ii);
	scveos_1.idt = min(60,scveos_1.idt);
    } else {
/* SEARCH UP FOR NEAREST 4 TABLE ELEMENTS */
	for (i__ = scveos_1.idt + 2; i__ <= 63; ++i__) {
	    if (*tl < scveos_1.tlogx[i__ - 1]) {
		ii = i__ - 2;
		goto L20;
	    }
	}
	ii = 60;
L20:
	scveos_1.idt = max(1,ii);
	scveos_1.idt = min(60,scveos_1.idt);
    }
/*  FIND NEAREST POINTS IN PRESSURE. */
/* Computing MIN */
    i__1 = scveos_1.nptsx[scveos_1.idt - 1] - 3;
    jjj = min(i__1,scveos_1.idp);
    if (pp < scveos_1.tablenv[scveos_1.idt + (jjj + 77) * 63 - 4852]) {
/* SEARCH DOWN TO FIND NEAREST 4 TABLE ELEMENTS */
	for (j = jjj; j >= 1; --j) {
	    if (pp > scveos_1.tablenv[scveos_1.idt + (j + 76) * 63 - 4852]) {
		jj = j - 1;
		goto L30;
	    }
	}
	jj = 1;
L30:
	scveos_1.idp = max(1,jj);
/* Computing MIN */
	i__1 = scveos_1.nptsx[scveos_1.idt - 1] - 3;
	scveos_1.idp = min(i__1,scveos_1.idp);
    } else {
/* SEARCH UP FOR NEAREST 4 TABLE ELEMENTS.  NOTE SEARCH IS DONE AT LOWEST */
/* TEMPERATURE POINT (WITH THE MINIMUM RANGE IN P). */
	i__1 = scveos_1.nptsx[scveos_1.idt - 1];
	for (j = jjj + 2; j <= i__1; ++j) {
	    if (pp < scveos_1.tablenv[scveos_1.idt + (j + 76) * 63 - 4852]) {
		jj = j - 2;
		goto L40;
	    }
	}
/* POINT IS OUTSIDE TABLE; RETURN. */
/*         WRITE(*,5)TL,PL */
	*lcalc = FALSE_;
	return 0;
L40:
/* Computing MIN */
	i__1 = scveos_1.nptsx[scveos_1.idt - 1] - 3;
	scveos_1.idp = min(i__1,jj);
    }
    *lcalc = TRUE_;
    for (k = 1; k <= 4; ++k) {
	qr[k - 1] = scveos_1.tlogx[k + scveos_1.idt - 2];
    }
    interp_(qr, ft, ftd, tl);
    for (k = 1; k <= 4; ++k) {
	qr[k - 1] = scveos_1.tablenv[scveos_1.idt + (scveos_1.idp + k + 75) * 
		63 - 4852];
    }
    interp_(qr, fp, fpd, &pp);
    y = 1. - *x - *z__;
/* INCLUDE RADIATION PRESSURE IN THE EQUATION OF STATE. */
    prad = betm1 * *p;
    pgas = *beta * *p;
/* DENSITY FOR X=1, Y=1, Z=1 */
/* INTERPOLATE IN PRESSURE AT 4 DIFFERENT TEMPERATURE POINTS. */
    for (i__ = 1; i__ <= 4; ++i__) {
	ii = scveos_1.idt + i__ - 1;
	temp[i__ - 1] = fp[0] * scveos_1.tablex[ii + (scveos_1.idp + 304) * 
		63 - 4852] + fp[1] * scveos_1.tablex[ii + (scveos_1.idp + 305)
		 * 63 - 4852] + fp[2] * scveos_1.tablex[ii + (scveos_1.idp + 
		306) * 63 - 4852] + fp[3] * scveos_1.tablex[ii + (
		scveos_1.idp + 307) * 63 - 4852];
	temp[i__ + 3] = fp[0] * scveos_1.tabley[ii + (scveos_1.idp + 304) * 
		63 - 4852] + fp[1] * scveos_1.tabley[ii + (scveos_1.idp + 305)
		 * 63 - 4852] + fp[2] * scveos_1.tabley[ii + (scveos_1.idp + 
		306) * 63 - 4852] + fp[3] * scveos_1.tabley[ii + (
		scveos_1.idp + 307) * 63 - 4852];
	temp[i__ + 7] = fp[0] * scveos_1.tablez[ii + (scveos_1.idp + 304) * 
		63 - 4852] + fp[1] * scveos_1.tablez[ii + (scveos_1.idp + 305)
		 * 63 - 4852] + fp[2] * scveos_1.tablez[ii + (scveos_1.idp + 
		306) * 63 - 4852] + fp[3] * scveos_1.tablez[ii + (
		scveos_1.idp + 307) * 63 - 4852];
    }
/* INTERPOLATE IN TEMPERATURE */
    denxl = ft[0] * temp[0] + ft[1] * temp[1] + ft[2] * temp[2] + ft[3] * 
	    temp[3];
    denx = exp(const1_1.cln * denxl);
    denyl = ft[0] * temp[4] + ft[1] * temp[5] + ft[2] * temp[6] + ft[3] * 
	    temp[7];
    deny = exp(const1_1.cln * denyl);
    denzl = ft[0] * temp[8] + ft[1] * temp[9] + ft[2] * temp[10] + ft[3] * 
	    temp[11];
    denz = exp(const1_1.cln * denzl);
/*  DENSITY */
    *d__ = 1. / (*x / denx + y / deny + *z__ / denz);
    *dl = d_lg10(d__);
    ddx = *x * *d__ / denx;
    ddy = y * *d__ / deny;
    ddz = *z__ * *d__ / denz;
/* D LN RHO/ D LN P = QDP */
/* FOR GAS PRESSURE QDP(TOT) = QDP(X)*X*RHO/RHO(X)+QDP(Y)*Y*RHO/RHO(Y) */
/* FOR RADIATION PRESSURE QDP = 0, SO QDP(TOT) = QDP(GAS)*P/PGAS */
/* INTERPOLATE IN PRESSURE AT 4 DIFFERENT TEMPERATURE POINTS. */
    for (i__ = 1; i__ <= 4; ++i__) {
	ii = scveos_1.idt + i__ - 1;
	temp[i__ - 1] = fp[0] * scveos_1.tablex[ii + (scveos_1.idp + 608) * 
		63 - 4852] + fp[1] * scveos_1.tablex[ii + (scveos_1.idp + 609)
		 * 63 - 4852] + fp[2] * scveos_1.tablex[ii + (scveos_1.idp + 
		610) * 63 - 4852] + fp[3] * scveos_1.tablex[ii + (
		scveos_1.idp + 611) * 63 - 4852];
	temp[i__ + 3] = fp[0] * scveos_1.tabley[ii + (scveos_1.idp + 608) * 
		63 - 4852] + fp[1] * scveos_1.tabley[ii + (scveos_1.idp + 609)
		 * 63 - 4852] + fp[2] * scveos_1.tabley[ii + (scveos_1.idp + 
		610) * 63 - 4852] + fp[3] * scveos_1.tabley[ii + (
		scveos_1.idp + 611) * 63 - 4852];
	temp[i__ + 7] = fp[0] * scveos_1.tablez[ii + (scveos_1.idp + 988) * 
		63 - 4852] + fp[1] * scveos_1.tablez[ii + (scveos_1.idp + 989)
		 * 63 - 4852] + fp[2] * scveos_1.tablez[ii + (scveos_1.idp + 
		990) * 63 - 4852] + fp[3] * scveos_1.tablez[ii + (
		scveos_1.idp + 991) * 63 - 4852];
    }
/* INTERPOLATE IN TEMPERATURE */
    qdpx = ft[0] * temp[0] + ft[1] * temp[1] + ft[2] * temp[2] + ft[3] * temp[
	    3];
    qdpy = ft[0] * temp[4] + ft[1] * temp[5] + ft[2] * temp[6] + ft[3] * temp[
	    7];
    qdpz = ft[0] * temp[8] + ft[1] * temp[9] + ft[2] * temp[10] + ft[3] * 
	    temp[11];
    qdp0 = qdpx * ddx + qdpy * ddy + qdpz * ddz;
    *qdp = qdp0 / *beta;
/* D LN RHO/ D LN T = QDT (NOTE : D LN P/ D LN T = QPT) */
/* FOR GAS PRESSURE, CORRECT AS PER QDP */
/* FOR RADIATION PRESSURE, USE QDT = -QDP*QPT.  CORRECT QPT FOR */
/* RADIATION PRESSURE AND USE THE CORRECTED QDP, QPT TO GET QDT. */
/* INTERPOLATE IN PRESSURE AT 4 DIFFERENT TEMPERATURE POINTS.zdiffOPEOSfinalewkop95zscv1.full */
    for (i__ = 1; i__ <= 4; ++i__) {
	ii = scveos_1.idt + i__ - 1;
	temp[i__ - 1] = fp[0] * scveos_1.tablex[ii + (scveos_1.idp + 532) * 
		63 - 4852] + fp[1] * scveos_1.tablex[ii + (scveos_1.idp + 533)
		 * 63 - 4852] + fp[2] * scveos_1.tablex[ii + (scveos_1.idp + 
		534) * 63 - 4852] + fp[3] * scveos_1.tablex[ii + (
		scveos_1.idp + 535) * 63 - 4852];
	temp[i__ + 3] = fp[0] * scveos_1.tabley[ii + (scveos_1.idp + 532) * 
		63 - 4852] + fp[1] * scveos_1.tabley[ii + (scveos_1.idp + 533)
		 * 63 - 4852] + fp[2] * scveos_1.tabley[ii + (scveos_1.idp + 
		534) * 63 - 4852] + fp[3] * scveos_1.tabley[ii + (
		scveos_1.idp + 535) * 63 - 4852];
	temp[i__ + 7] = fp[0] * scveos_1.tablez[ii + (scveos_1.idp + 760) * 
		63 - 4852] + fp[1] * scveos_1.tablez[ii + (scveos_1.idp + 761)
		 * 63 - 4852] + fp[2] * scveos_1.tablez[ii + (scveos_1.idp + 
		762) * 63 - 4852] + fp[3] * scveos_1.tablez[ii + (
		scveos_1.idp + 763) * 63 - 4852];
    }
/* INTERPOLATE IN TEMPERATURE */
    qdtx = ft[0] * temp[0] + ft[1] * temp[1] + ft[2] * temp[2] + ft[3] * temp[
	    3];
    qdty = ft[0] * temp[4] + ft[1] * temp[5] + ft[2] * temp[6] + ft[3] * temp[
	    7];
    qdtz = ft[0] * temp[8] + ft[1] * temp[9] + ft[2] * temp[10] + ft[3] * 
	    temp[11];
    qdt0 = qdtx * ddx + qdty * ddy + qdtz * ddz;
    qpt0 = -qdt0 / qdp0;
    qpt = qpt0 * *beta + betm1 * 4.;
    *qdt = -qpt * *qdp;
/*  CP = S*(D LN S/ D LN T)|P IS TABULATED. USE */
/*  CP = DU/DT + P*(D LN RHO/D LN T)**2/RHO/T/(D LN RHO/ D LN P) */
/*  TO FIND DU/DT.  THEN INCLUDE THE EFFECTS OF RADIATION PRESSURE */
/*  ON DU/DT AND THE OTHER TERMS AND GET A CORRECTED CP. */
/* CP (GAS PRESSURE ONLY). */
/* NOTE THAT UNLIKE THE ENVELOPE TABLE, WE NEED TO INTERPOLATE IN */
/* ENTROPY S, D LN S/D LNT, AND ENTROPY OF MIXING, THEN CALCULATE */
/* DU/DT */
/*  ENTROPY AND ENTROPY OF MIXING */
/* INTERPOLATE IN PRESSURE AT 4 DIFFERENT TEMPERATURE POINTS. */
    for (i__ = 1; i__ <= 4; ++i__) {
	ii = scveos_1.idt + i__ - 1;
	temp[i__ - 1] = fp[0] * scveos_1.tablex[ii + (scveos_1.idp + 380) * 
		63 - 4852] + fp[1] * scveos_1.tablex[ii + (scveos_1.idp + 381)
		 * 63 - 4852] + fp[2] * scveos_1.tablex[ii + (scveos_1.idp + 
		382) * 63 - 4852] + fp[3] * scveos_1.tablex[ii + (
		scveos_1.idp + 383) * 63 - 4852];
	temp[i__ + 3] = fp[0] * scveos_1.tabley[ii + (scveos_1.idp + 380) * 
		63 - 4852] + fp[1] * scveos_1.tabley[ii + (scveos_1.idp + 381)
		 * 63 - 4852] + fp[2] * scveos_1.tabley[ii + (scveos_1.idp + 
		382) * 63 - 4852] + fp[3] * scveos_1.tabley[ii + (
		scveos_1.idp + 383) * 63 - 4852];
	temp[i__ + 7] = fp[0] * scveos_1.smix[ii + scveos_1.idp * 63 - 64] + 
		fp[1] * scveos_1.smix[ii + (scveos_1.idp + 1) * 63 - 64] + fp[
		2] * scveos_1.smix[ii + (scveos_1.idp + 2) * 63 - 64] + fp[3] 
		* scveos_1.smix[ii + (scveos_1.idp + 3) * 63 - 64];
    }
/* INTERPOLATE IN TEMPERATURE */
    sxl = ft[0] * temp[0] + ft[1] * temp[1] + ft[2] * temp[2] + ft[3] * temp[
	    3];
    sx = exp(const1_1.cln * sxl);
    syl = ft[0] * temp[4] + ft[1] * temp[5] + ft[2] * temp[6] + ft[3] * temp[
	    7];
    sy = exp(const1_1.cln * syl);
    sm = ft[0] * temp[8] + ft[1] * temp[9] + ft[2] * temp[10] + ft[3] * temp[
	    11];
    qsmt = ftd[0] * d_lg10(&temp[8]) + ftd[1] * d_lg10(&temp[9]) + ftd[2] * 
	    d_lg10(&temp[10]) + ftd[3] * d_lg10(&temp[11]);
    s0 = *x * sx + y * sy + sm;
/* D LN S/ D LN T (X AND Y) AND DU/DT (Z) */
/* INTERPOLATE IN PRESSURE AT 4 DIFFERENT TEMPERATURE POINTS. */
    for (i__ = 1; i__ <= 4; ++i__) {
	ii = scveos_1.idt + i__ - 1;
	temp[i__ - 1] = fp[0] * scveos_1.tablex[ii + (scveos_1.idp + 684) * 
		63 - 4852] + fp[1] * scveos_1.tablex[ii + (scveos_1.idp + 685)
		 * 63 - 4852] + fp[2] * scveos_1.tablex[ii + (scveos_1.idp + 
		686) * 63 - 4852] + fp[3] * scveos_1.tablex[ii + (
		scveos_1.idp + 687) * 63 - 4852];
	temp[i__ + 3] = fp[0] * scveos_1.tabley[ii + (scveos_1.idp + 684) * 
		63 - 4852] + fp[1] * scveos_1.tabley[ii + (scveos_1.idp + 685)
		 * 63 - 4852] + fp[2] * scveos_1.tabley[ii + (scveos_1.idp + 
		686) * 63 - 4852] + fp[3] * scveos_1.tabley[ii + (
		scveos_1.idp + 687) * 63 - 4852];
	temp[i__ + 7] = fp[0] * scveos_1.tablez[ii + (scveos_1.idp + 532) * 
		63 - 4852] + fp[1] * scveos_1.tablez[ii + (scveos_1.idp + 533)
		 * 63 - 4852] + fp[2] * scveos_1.tablez[ii + (scveos_1.idp + 
		534) * 63 - 4852] + fp[3] * scveos_1.tablez[ii + (
		scveos_1.idp + 535) * 63 - 4852];
    }
/* INTERPOLATE IN TEMPERATURE */
    qstx = ft[0] * temp[0] + ft[1] * temp[1] + ft[2] * temp[2] + ft[3] * temp[
	    3];
    qsty = ft[0] * temp[4] + ft[1] * temp[5] + ft[2] * temp[6] + ft[3] * temp[
	    7];
    qutzl = ft[0] * temp[8] + ft[1] * temp[9] + ft[2] * temp[10] + ft[3] * 
	    temp[11];
    qutz = exp(const1_1.cln * qutzl);
    qst0 = *x * sx * qstx + y * sy * qsty + sm * qsmt;
/* Computing 2nd power */
    d__1 = qdtz;
    qcp0 = qst0 + *z__ * (qutz + pgas * (d__1 * d__1) / qdpz / denz / *t);
/* NOW FIND DU/DT FROM THE ORIGINAL TABLE. */
/* Computing 2nd power */
    d__1 = qdt0;
    qut = qcp0 - pgas * (d__1 * d__1) / qdp0 / *d__ / *t;
/* CORRECT DU/DT FOR RADIATION */
    ur = prad * 3. / *d__;
    qut += ur * 4. / *t;
/* CORRECT CP FOR RADIATION PRESSURE */
/* Computing 2nd power */
    d__1 = *qdt;
    *qcp = qut + *p * (d__1 * d__1) / *qdp / *d__ / *t;
/* ADIABATIC TEMPERATURE GRADIENT */
    *dela = -(*p) * *qdt / *d__ / *t / *qcp;
/* Get fractions of total particles (including electrons), as follows: */
/*   XTF_H2  the fraction that is neutral hydrogen molecules, and */
/*   XTF_He  the fraction thst is neutral helium). */
/*   These are in column 2 respectively of the SCV hydrogen and */
/*   Helium tables. */
/* INTERPOLATE IN PRESSURE AT 4 DIFFERENT TEMPERATURE POINTS. */
    for (i__ = 1; i__ <= 4; ++i__) {
	ii = scveos_1.idt + i__ - 1;
	temp[i__ - 1] = fp[0] * scveos_1.tablex[ii + (scveos_1.idp + 152) * 
		63 - 4852] + fp[1] * scveos_1.tablex[ii + (scveos_1.idp + 153)
		 * 63 - 4852] + fp[2] * scveos_1.tablex[ii + (scveos_1.idp + 
		154) * 63 - 4852] + fp[3] * scveos_1.tablex[ii + (
		scveos_1.idp + 155) * 63 - 4852];
	temp[i__ + 3] = fp[0] * scveos_1.tabley[ii + (scveos_1.idp + 152) * 
		63 - 4852] + fp[1] * scveos_1.tabley[ii + (scveos_1.idp + 153)
		 * 63 - 4852] + fp[2] * scveos_1.tabley[ii + (scveos_1.idp + 
		154) * 63 - 4852] + fp[3] * scveos_1.tabley[ii + (
		scveos_1.idp + 155) * 63 - 4852];
    }
/* INTERPOLATE IN TEMPERATURE */
    xtf_h2__ = ft[0] * temp[0] + ft[1] * temp[1] + ft[2] * temp[2] + ft[3] * 
	    temp[3];
    xtf_he__ = ft[0] * temp[4] + ft[1] * temp[5] + ft[2] * temp[6] + ft[3] * 
	    temp[7];
/* Get more fractions of total particles (including electrons), as follows: */
/*   XTF_H1  the fraction that is neutral hydrogen atoms, and */
/*   XTF_HeP  the fraction thst is singly ionized helium). */
/*   These are in column 3 respectively of the SCV hydrogen and */
/*   Helium tables. */
/* INTERPOLATE IN PRESSURE AT 4 DIFFERENT TEMPERATURE POINTS. */
    for (i__ = 1; i__ <= 4; ++i__) {
	ii = scveos_1.idt + i__ - 1;
	temp[i__ - 1] = fp[0] * scveos_1.tablex[ii + (scveos_1.idp + 228) * 
		63 - 4852] + fp[1] * scveos_1.tablex[ii + (scveos_1.idp + 229)
		 * 63 - 4852] + fp[2] * scveos_1.tablex[ii + (scveos_1.idp + 
		230) * 63 - 4852] + fp[3] * scveos_1.tablex[ii + (
		scveos_1.idp + 231) * 63 - 4852];
	temp[i__ + 3] = fp[0] * scveos_1.tabley[ii + (scveos_1.idp + 228) * 
		63 - 4852] + fp[1] * scveos_1.tabley[ii + (scveos_1.idp + 229)
		 * 63 - 4852] + fp[2] * scveos_1.tabley[ii + (scveos_1.idp + 
		230) * 63 - 4852] + fp[3] * scveos_1.tabley[ii + (
		scveos_1.idp + 231) * 63 - 4852];
    }
/* INTERPOLATE IN TEMPERATURE */
    xtf_h1__ = ft[0] * temp[0] + ft[1] * temp[1] + ft[2] * temp[2] + ft[3] * 
	    temp[3];
    xtf_hep__ = ft[0] * temp[4] + ft[1] * temp[5] + ft[2] * temp[6] + ft[3] * 
	    temp[7];
/* At tis time we can calculate the ramaining particles fractions using conservation */
/* of particles and coservation of charge.  The variable names are: */
/*  XTF_H_e  the hycrogen related fraction that is electrons */
/*  XTF_HP   the hydrogen ralated fraction that is H+ ions */
/*  XTF_He_e the helium related fraction that is electrons */
/*  XTF_HePP the helium related fraction that is doubly ionized helium (He++) */
/* Particle and charge conservation yields: */
    xtf_h_e__ = (1. - xtf_h2__ - xtf_h1__) * .5;
    xtf_hp__ = xtf_h_e__;
    xtf_he_e__ = (2. - xtf_he__ * 2. - xtf_hep__) * .33333333333333331;
    xtf_hepp__ = 1. - xtf_he__ - xtf_hep__ - xtf_he_e__;
/* We are seeking the fraction XHP of hydrogen nuclei that are singly ionized, */
/* the fraction XHeP of helium huclei that are singly ionized and XHePP, the */
/* helium fraction that is doubly ionized. */
    xhp = xtf_hp__ / (xtf_h2__ + xtf_h1__ + xtf_hp__);
    xhep = xtf_hep__ / (xtf_he__ + xtf_hep__ + xtf_hepp__);
    xhepp = xtf_hepp__ / (xtf_he__ + xtf_hep__ + xtf_hepp__);
/* In the same order, these are the desired elements of array XION(3) */
    fxion[1] = xhp;
    fxion[2] = xhep;
    fxion[3] = xhepp;
    return 0;
/* Primay exit. Success. LCALC is true. */
} /* eqscvg_ */

