/* eqscve.f -- translated by f2c (version 20061008).
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

/* SUBROUTINE FOR INTERPOLATING IN THE SURFACE ABUNDANCE TABLE OF THE SCV */
/* EQUATION OF STATE. */
/*       SUBROUTINE EQSCVE(TL,T,PL,P,DL,D,X,Z,BETA,BETAI,BETA14,FXION,RMU, */
/*      *AMU,EMU,ETA,QDT,QDP,QCP,DELA,LCALC)  ! KC 2025-05-31 */
/* Subroutine */ int eqscve_(doublereal *tl, doublereal *t, doublereal *p, 
	doublereal *dl, doublereal *d__, doublereal *x, doublereal *z__, 
	doublereal *beta, doublereal *fxion, doublereal *qdt, doublereal *qdp,
	 doublereal *qcp, doublereal *dela, logical *lcalc)
{
    /* Initialized data */

    static doublereal tolsp = .08;
    static doublereal tolst = .032;

    /* System generated locals */
    integer i__1;
    doublereal d__1, d__2;

    /* Builtin functions */
    double d_lg10(doublereal *), exp(doublereal);

    /* Local variables */
    static doublereal xtf_he_e__, xtf_hepp__;
    static integer i__, j, k;
    static doublereal y, y0, y2[4];
    static integer ii, jj;
    static doublereal fp[4], ft[4], pp, qr[4], ur, fpd[4], ftd[4];
    static integer jjj;
    static doublereal fsp, fst, xhp, qpt, qut, qcp0, qdp0, qdt0, qpt0, prad, 
	    pgas, ytab[4], xhep, temp[20]	/* was [4][5] */;
    static integer ismp, ismt;
    static logical lsmp, lsmt;
    static doublereal chgt1, chgt2, betm1, xhepp, tempt[5], xtf_h1__, 
	    xtf_h2__, tempt1[5], tempt2[5], tempt3[5], xtf_he__;
    extern /* Subroutine */ int eqscvg_(doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *, doublereal *, logical *);
    static doublereal xtf_hp__;
    extern /* Subroutine */ int interp_(doublereal *, doublereal *, 
	    doublereal *, doublereal *);
    static doublereal tempt2p[5], tempt1t[5], xtf_h_e__, dpabove, dtabove, 
	    dpbelow, xtf_hep__, dtbelow;
    extern /* Subroutine */ int kspline_(doublereal *, doublereal *, 
	    doublereal *), ksplint_(doublereal *, doublereal *, doublereal *, 
	    doublereal *, doublereal *);

/* MHP  5/97 ADDED COMMON BLOCK FOR SCV EOS TABLES */
/* REPLACE 4-PT LAGRANGE INTERPOLATE WITH 4-PT NATURAL SPLINE */
/*      DIMENSION ATOMWT(4),QR(4),FT(4),FTD(4), */
/*     *     FP(4),FPD(4),TEMPT(5),TEMP(4,5),FXION(3) */
/*       DIMENSION ATOMWT(4),QR(4),YTAB(4),Y2(4),  ! KC 2025-05-31 */
/*       DATA ATOMWT/0.9921D0,0.24975D0,0.08322D0,0.4995D0/ */
/*       DATA CMH,CMHE,CBOLTZ/1.67357D-24,6.646442D-24,1.380658D-16/ */
    /* Parameter adjustments */
    --fxion;

    /* Function Body */
    if ((d__1 = *x - comp_1.xenv, abs(d__1)) > 1e-5 || (d__2 = *z__ - 
	    comp_1.zenv, abs(d__2)) > 1e-5) {
/*          CALL EQSCVG(TL,T,PL,P,DL,D,X,Z,BETA,BETAI,BETA14,FXION,RMU, */
/*      *               AMU,EMU,ETA,QDT,QDP,QCP,DELA,LCALC)  ! KC 2025-05-31 */
	eqscvg_(tl, t, p, dl, d__, x, z__, beta, &fxion[1], qdt, qdp, qcp, 
		dela, lcalc);
	return 0;
    }
/* FIND GAS PRESSURE (WHICH IS THE QUANTITY WHICH IS TABULATED). */
    betm1 = 1. - *beta;
    d__1 = *beta * *p;
    pp = d_lg10(&d__1);
/*  CHECK IF THE POINT IS WITHIN THE TABLE */
    if (*tl < scveos_1.tlogx[0] || *tl > scveos_1.tlogx[62] || pp < 4.) {
	*lcalc = FALSE_;
/* Error exit - no valid table entry */
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
	;
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
	;
    }
    scveos_1.idt = max(1,ii);
    scveos_1.idt = min(60,scveos_1.idt);
    lsmt = FALSE_;
    if (scveos_1.idt == ii) {
	dtabove = *tl - scveos_1.tlogx[scveos_1.idt];
	dtbelow = scveos_1.tlogx[scveos_1.idt + 1] - *tl;
	if (dtabove < tolst) {
	    if (scveos_1.idt > 1) {
		lsmt = TRUE_;
		ismt = -1;
		fst = (dtabove + tolst) / (tolst * 2.);
	    }
	} else if (dtbelow < tolst) {
	    if (scveos_1.idt < 60) {
		lsmt = TRUE_;
		ismt = 1;
		fst = dtbelow * .5 / tolst;
	    }
	}
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
	*lcalc = FALSE_;
/* Error exit - no valid table entry */
	return 0;
L40:
/* Computing MIN */
	i__1 = scveos_1.nptsx[scveos_1.idt - 1] - 3;
	scveos_1.idp = min(i__1,jj);
    }
    *lcalc = TRUE_;
    lsmp = FALSE_;
    if (scveos_1.idp == jj) {
	dpabove = pp - scveos_1.tablenv[scveos_1.idt + (scveos_1.idp + 77) * 
		63 - 4852];
	dpbelow = scveos_1.tablenv[scveos_1.idt + (scveos_1.idp + 78) * 63 - 
		4852] - pp;
	if (dpabove < tolsp) {
	    if (scveos_1.idp > 1) {
		lsmp = TRUE_;
		ismp = -1;
		fsp = (dpabove + tolsp) / (tolsp * 2.);
	    }
	} else if (dpbelow < tolsp) {
	    if (scveos_1.idp < scveos_1.nptsx[scveos_1.idt - 1] - 3) {
		lsmp = TRUE_;
		ismp = 1;
		fsp = dpbelow * .5 / tolsp;
	    }
	}
    }
/*      DO K = 1,4 */
/*         QR(K) = TLOGX(K+IDT-1) */
/*      END DO */
/*      CALL INTERP(QR,FT,FTD,TL) */
/*      DO K = 1,4 */
/*         QR(K) = TABLENV(IDT,IDP+K-1,1) */
/*      END DO */
/*      CALL INTERP(QR,FP,FPD,PP) */
    y = 1. - *x - *z__;
/* INCLUDE RADIATION PRESSURE IN THE EQUATION OF STATE. */
    prad = betm1 * *p;
    pgas = *beta * *p;
/* INTERPOLATE IN PRESSURE AT 4 DIFFERENT TEMPERATURE POINTS. */
    for (i__ = 1; i__ <= 4; ++i__) {
	ii = scveos_1.idt + i__ - 1;
	for (k = 1; k <= 4; ++k) {
	    qr[k - 1] = scveos_1.tablenv[scveos_1.idt + (scveos_1.idp + k + 
		    75) * 63 - 4852];
	}
	for (j = 1; j <= 5; ++j) {
	    for (k = 1; k <= 4; ++k) {
		ytab[k - 1] = scveos_1.tablenv[ii + (scveos_1.idp + k - 1 + (
			j + 1) * 76) * 63 - 4852];
	    }
	    kspline_(qr, ytab, y2);
	    ksplint_(qr, ytab, y2, &pp, &y0);
	    temp[i__ + (j << 2) - 5] = y0;
/*            TEMP(I,J)=FP(1)*TABLENV(II,IDP,J+1) + */
/*     *      FP(2)*TABLENV(II,IDP+1,J+1) + FP(3)*TABLENV(II,IDP+2,J+1) */
/*     *      + FP(4)*TABLENV(II,IDP+3,J+1) */
	}
    }
/* INTERPOLATE IN TEMPERATURE */
    for (k = 1; k <= 4; ++k) {
	qr[k - 1] = scveos_1.tlogx[k + scveos_1.idt - 2];
    }
    for (j = 1; j <= 5; ++j) {
	for (k = 1; k <= 4; ++k) {
	    ytab[k - 1] = temp[k + (j << 2) - 5];
	}
	kspline_(qr, ytab, y2);
	ksplint_(qr, ytab, y2, tl, &y0);
	tempt[j - 1] = y0;
    }
/* PERFORM INTERPOLATION AT ADJACENT TEMPERATURE TABLE POINTS */
    if (lsmt) {
/* INTERPOLATE IN PRESSURE AT 4 DIFFERENT TEMPERATURE POINTS. */
	for (i__ = 1; i__ <= 4; ++i__) {
	    ii = scveos_1.idt + i__ - 1 + ismt;
	    for (k = 1; k <= 4; ++k) {
		qr[k - 1] = scveos_1.tablenv[scveos_1.idt + (scveos_1.idp + k 
			+ 75) * 63 - 4852];
	    }
	    for (j = 1; j <= 5; ++j) {
		for (k = 1; k <= 4; ++k) {
		    ytab[k - 1] = scveos_1.tablenv[ii + (scveos_1.idp + k - 1 
			    + (j + 1) * 76) * 63 - 4852];
		}
		kspline_(qr, ytab, y2);
		ksplint_(qr, ytab, y2, &pp, &y0);
		temp[i__ + (j << 2) - 5] = y0;
/*            TEMP(I,J)=FP(1)*TABLENV(II,IDP,J+1) + */
/*     *      FP(2)*TABLENV(II,IDP+1,J+1) + FP(3)*TABLENV(II,IDP+2,J+1) */
/*     *      + FP(4)*TABLENV(II,IDP+3,J+1) */
	    }
	}
/* INTERPOLATE IN TEMPERATURE */
	for (k = 1; k <= 4; ++k) {
	    qr[k - 1] = scveos_1.tlogx[k + scveos_1.idt + ismt - 2];
	}
	for (j = 1; j <= 5; ++j) {
	    for (k = 1; k <= 4; ++k) {
		ytab[k - 1] = temp[k + (j << 2) - 5];
	    }
	    kspline_(qr, ytab, y2);
	    ksplint_(qr, ytab, y2, tl, &y0);
	    tempt1[j - 1] = y0;
	}
	if (ismt == -1) {
	    for (j = 1; j <= 5; ++j) {
		tempt1t[j - 1] = tempt1[j - 1] + fst * (tempt[j - 1] - tempt1[
			j - 1]);
	    }
	} else {
	    for (j = 1; j <= 5; ++j) {
		tempt1t[j - 1] = tempt[j - 1] + fst * (tempt1[j - 1] - tempt[
			j - 1]);
	    }
	}
    }
/* PERFORM INTERPOLATION AT ADJACENT PRESSURE TABLE POINTS */
    if (lsmp) {
/* INTERPOLATE IN PRESSURE AT 4 DIFFERENT TEMPERATURE POINTS. */
	for (i__ = 1; i__ <= 4; ++i__) {
	    ii = scveos_1.idt + i__ - 1;
	    for (k = 1; k <= 4; ++k) {
		qr[k - 1] = scveos_1.tablenv[scveos_1.idt + (scveos_1.idp + k 
			- 1 + ismp + 76) * 63 - 4852];
	    }
	    for (j = 1; j <= 5; ++j) {
		for (k = 1; k <= 4; ++k) {
		    ytab[k - 1] = scveos_1.tablenv[ii + (scveos_1.idp + k - 1 
			    + ismp + (j + 1) * 76) * 63 - 4852];
		}
		kspline_(qr, ytab, y2);
		ksplint_(qr, ytab, y2, &pp, &y0);
		temp[i__ + (j << 2) - 5] = y0;
/*            TEMP(I,J)=FP(1)*TABLENV(II,IDP,J+1) + */
/*     *      FP(2)*TABLENV(II,IDP+1,J+1) + FP(3)*TABLENV(II,IDP+2,J+1) */
/*     *      + FP(4)*TABLENV(II,IDP+3,J+1) */
	    }
	}
/* INTERPOLATE IN TEMPERATURE */
	for (k = 1; k <= 4; ++k) {
	    qr[k - 1] = scveos_1.tlogx[k + scveos_1.idt - 2];
	}
	for (j = 1; j <= 5; ++j) {
	    for (k = 1; k <= 4; ++k) {
		ytab[k - 1] = temp[k + (j << 2) - 5];
	    }
	    kspline_(qr, ytab, y2);
	    ksplint_(qr, ytab, y2, tl, &y0);
	    tempt2[j - 1] = y0;
	}
	if (ismp == -1) {
	    for (j = 1; j <= 5; ++j) {
		tempt2p[j - 1] = tempt2[j - 1] + fsp * (tempt[j - 1] - tempt2[
			j - 1]);
	    }
	} else {
	    for (j = 1; j <= 5; ++j) {
		tempt2p[j - 1] = tempt[j - 1] + fsp * (tempt2[j - 1] - tempt[
			j - 1]);
	    }
	}
    }
/* PERFORM INTERPOLATION AT ADJACENT T+P TABLE POINTS */
    if (lsmp && lsmt) {
/* INTERPOLATE IN PRESSURE AT 4 DIFFERENT TEMPERATURE POINTS. */
	for (i__ = 1; i__ <= 4; ++i__) {
	    ii = scveos_1.idt + i__ - 1 + ismt;
	    for (k = 1; k <= 4; ++k) {
		qr[k - 1] = scveos_1.tablenv[scveos_1.idt + (scveos_1.idp + k 
			- 1 + ismp + 76) * 63 - 4852];
	    }
	    for (j = 1; j <= 5; ++j) {
		for (k = 1; k <= 4; ++k) {
		    ytab[k - 1] = scveos_1.tablenv[ii + (scveos_1.idp + k - 1 
			    + ismp + (j + 1) * 76) * 63 - 4852];
		}
		kspline_(qr, ytab, y2);
		ksplint_(qr, ytab, y2, &pp, &y0);
		temp[i__ + (j << 2) - 5] = y0;
/*            TEMP(I,J)=FP(1)*TABLENV(II,IDP,J+1) + */
/*     *      FP(2)*TABLENV(II,IDP+1,J+1) + FP(3)*TABLENV(II,IDP+2,J+1) */
/*     *      + FP(4)*TABLENV(II,IDP+3,J+1) */
	    }
	}
/* INTERPOLATE IN TEMPERATURE */
	for (k = 1; k <= 4; ++k) {
	    qr[k - 1] = scveos_1.tlogx[k + scveos_1.idt - 1 + ismt - 1];
	}
	for (j = 1; j <= 5; ++j) {
	    for (k = 1; k <= 4; ++k) {
		ytab[k - 1] = temp[k + (j << 2) - 5];
	    }
	    kspline_(qr, ytab, y2);
	    ksplint_(qr, ytab, y2, tl, &y0);
	    tempt3[j - 1] = y0;
	}
    }
    if (lsmt) {
/* ADD CHANGES FOR BOTH T AND P INTERPOLATION */
	if (lsmp) {
/*            WRITE(*,911)(TEMPT(J),J=1,5) */
/*  911        FORMAT(1X,'ORIG ',1P5E16.7) */
/*            WRITE(*,912)(TEMPT1(J)-TEMPT(J),J=1,5) */
/*  912        FORMAT(1X,'INT T',1P5E16.7) */
/*            WRITE(*,913)(TEMPT2(J)-TEMPT(J),J=1,5) */
/*  913        FORMAT(1X,'INT P',1P5E16.7) */
/*            WRITE(*,914)(TEMPT3(J)-TEMPT(J),J=1,5) */
/*  914        FORMAT(1X,'INT PT',1P5E16.7) */
	    for (j = 1; j <= 5; ++j) {
		if (ismt == -1) {
/* INTERPOLATE IN T AT FIXED P */
		    chgt1 = tempt1[j - 1] + fst * (tempt[j - 1] - tempt1[j - 
			    1]);
/* INTERPOLATE IN T AT DIFFERENT P */
		    chgt2 = tempt3[j - 1] + fst * (tempt2[j - 1] - tempt3[j - 
			    1]);
		} else {
		    chgt1 = tempt[j - 1] + fst * (tempt1[j - 1] - tempt[j - 1]
			    );
		    chgt2 = tempt2[j - 1] + fst * (tempt3[j - 1] - tempt2[j - 
			    1]);
		}
		if (ismp == -1) {
		    tempt[j - 1] = chgt2 + fsp * (chgt1 - chgt2);
/* CHANGE IN P AT FIXED T */
/*                  CHGP1 = TEMPT2+FSP*(TEMPT(J)-TEMPT2(J)) */
/* CHANGE IN P AT DIFFERENT T */
/*                  CHGP2 = TEMPT3(J)+FSP*(TEMPT1(J)-TEMPT3(J)) */
		} else {
		    tempt[j - 1] = chgt1 + fsp * (chgt2 - chgt1);
/*                  CHGP1 = TEMPT(J)+FSP*(TEMPT2(J)-TEMPT(J)) */
/*                  CHGP2 = TEMPT1(J)+FSP*(TEMPT3(J)-TEMPT1(J)) */
		}
/*               WRITE(*,915)ISMP,ISMT,TEMPT(J),CHGT1,CHGT2,FSP,FST */
/*  915           FORMAT(2I2,1P5E16.7) */
	    }
	} else {
/* ADD T INTERPOLATION CHANGES ONLY */
/*            WRITE(*,911)(TEMPT(J),J=1,5) */
/*            WRITE(*,912)(TEMPT1(J)-TEMPT(J),J=1,5) */
	    for (j = 1; j <= 5; ++j) {
		tempt[j - 1] = tempt1t[j - 1];
	    }
	}
    } else if (lsmp) {
/* ADD P INTERPOLATION CHANGES ONLY */
/*            WRITE(*,911)(TEMPT(J),J=1,5) */
/*            WRITE(*,912)(TEMPT2(J)-TEMPT(J),J=1,5) */
	for (j = 1; j <= 5; ++j) {
	    tempt[j - 1] = tempt2p[j - 1];
	}
    }
/*      DO J = 1,5 */
/*         TEMPT(J)=FT(1)*TEMP(1,J) + FT(2)*TEMP(2,J) + FT(3)*TEMP(3,J) */
/*     *   + FT(4)*TEMP(4,J) */
/*      END DO */
/*  DENSITY */
    *dl = tempt[0];
    *d__ = exp(const1_1.cln * *dl);
/* D LN RHO/ D LN P = QDP */
/* FOR GAS PRESSURE QDP(TOT) = QDP(X)*X*RHO/RHO(X)+QDP(Y)*Y*RHO/RHO(Y) */
/* FOR RADIATION PRESSURE QDP = 0, SO QDP(TOT) = QDP(GAS)*P/PGAS */
    qdp0 = tempt[2];
    *qdp = qdp0 / *beta;
/* D LN RHO/ D LN T = QDT (NOTE : D LN P/ D LN T = QPT) */
/* FOR GAS PRESSURE, CORRECT AS PER QDP */
/* FOR RADIATION PRESSURE, USE QDT = -QDP*QPT.  CORRECT QPT FOR */
/* RADIATION PRESSURE AND USE THE CORRECTED QDP, QPT TO GET QDT. */
    qdt0 = tempt[1];
    qpt0 = -qdt0 / qdp0;
    qpt = qpt0 * *beta + betm1 * 4.;
    *qdt = -qpt * *qdp;
/*  CP = S*(D LN S/ D LN T)|P IS TABULATED. USE */
/*  CP = DU/DT + P*(D LN RHO/D LN T)**2/RHO/T/(D LN RHO/ D LN P) */
/*  TO FIND DU/DT.  THEN INCLUDE THE EFFECTS OF RADIATION PRESSURE */
/*  ON DU/DT AND THE OTEHR TERMS AND GET A CORRECTED CP. */
/* CP (GAS PRESSURE ONLY). */
    qcp0 = tempt[3];
/* NOW FIND DU/DT FROM THE ORIGINAL TABLE. */
    qut = tempt[4];
/*      QUT = QCP0 - PGAS*QDT0**2/QDP0/D/T */
/* CORRECT DU/DT FOR RADIATION */
    ur = prad * 3. / *d__;
    qut += ur * 4. / *t;
/* CORRECT CP FOR RADIATION PRESSURE */
    *qcp = qut - *p * *qdt * qpt / *d__ / *t;
/* ADIABATIC TEMPERATURE GRADIENT */
    *dela = -(*p) * *qdt / *d__ / *t / *qcp;
/* Get fractions of total particles (including electrons), as follows: */
/*   XTF_H2  the fraction that is neutral hydrogen molecules, and */
/*   XTF_He  the fraction thst is neutral helium). */
/*   These are in column 2 respectively of the SCV hydrogen and */
/*   Helium tables. */
/* INTERPOLATE IN PRESSURE AT 4 DIFFERENT TEMPERATURE POINTS. */
    for (k = 1; k <= 4; ++k) {
	qr[k - 1] = scveos_1.tlogx[k + scveos_1.idt - 2];
    }
    interp_(qr, ft, ftd, tl);
    for (k = 1; k <= 4; ++k) {
	qr[k - 1] = scveos_1.tablenv[scveos_1.idt + (scveos_1.idp + k + 75) * 
		63 - 4852];
    }
    interp_(qr, fp, fpd, &pp);
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
/* Normal exit. Valid table entry. LCALC is true. */
} /* eqscve_ */

