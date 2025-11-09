/* eqsaha.f -- translated by f2c (version 20061008).
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
    doublereal cgas, ca3, ca3l, csig, csigl, cgl, cmkh, cmkhn;
} const2_;

#define const2_1 const2_

/* Table of constant values */

static doublereal c_b17 = 1.;
static integer c__1 = 1;



/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */
/* EQSAHA */
/* $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ */
/* Subroutine */ int eqsaha_(doublereal *fx, doublereal *tl, doublereal *t, 
	doublereal *pl, doublereal *p, doublereal *dl, doublereal *d__, 
	doublereal *beta, doublereal *betai, doublereal *beta14, doublereal *
	fxion, doublereal *rmu, doublereal *amu, doublereal *emu, logical *
	lderiv, logical *latmo, doublereal *qdt, doublereal *qdp, doublereal *
	qcp, doublereal *dela, doublereal *qdtt, doublereal *qdtp, doublereal 
	*qat, doublereal *qap, doublereal *qcpt, doublereal *qcpp, integer *
	ksaha)
{
    /* Initialized data */

    static doublereal sahat[11] = { 59630.,69450.,88710.,91330.,94570.,
	    130630.,157800.,1.58e5,168630.,183080.,250200. };
    static doublereal sahex2 = 0.;
    static doublereal stolee = 1e-9;
    static doublereal sahet0 = 285270.;
    static doublereal sahet1 = 631370.;
    static doublereal sahau[13] = { -.01,-.47,.6,.49,.08,.11,0.,-.04,.64,.99,
	    1.03,.6,0. };
    static integer nz = 11;
    static integer maxs = 20;
    static doublereal stol = 40.;
    static doublereal e = .1;
    static doublereal sahex1 = 0.;

    /* Format strings */
    static char fmt_99[] = "(\002 -----SAHA FAILURE (TL,PL)=\002,2f10.6,\002"
	    "  (E,DE)=\002,2f20.12)";

    /* System generated locals */
    integer i__1, i__2;
    doublereal d__1, d__2;

    /* Builtin functions */
    double exp(doublereal), d_lg10(doublereal *), d_sign(doublereal *, 
	    doublereal *);
    integer s_wsfe(cilist *), do_fio(integer *, char *, ftnlen), e_wsfe(void);

    /* Local variables */
    static integer i__;
    static doublereal r1, r2, r3, c11, c12, c22, c23, c33, c32, c13, c21, c31,
	     ti, ep1, r1l, r1p, r2p, r3p, r1t;
    static integer nz0, nz1;
    static doublereal r3t, r2t, c12l, c13l, ep12, cr12, cr13, cr23, div, pdt, 
	    fxs[11], fxt[11], qut, ep1e, eep1, fact, cr12l, cr13l;
    static logical lfin;
    static doublereal fxhe, emax, qcpi, ramu, rmub, temp, sqep, pdtq, sqet, 
	    usum, fact1, fact2, temp8, sk0qt, sk1qt, sx0qp, sx1qp, sx2qp, 
	    sx0qt, sx1qt, sx2qt, beta16;
    static integer isaha;
    static doublereal sahak[11], delte, sahax[11];
    static logical lnohe;
    static doublereal btemp, etemp, stemp, sqetp, sqett, upsum, qqutp, sahek0,
	     sahek1, utsum, qqutt;
    static logical lnohe2;
    static doublereal sahex0, delx1l, deltx1, deltx2, stemp1, stemp2, stemp3, 
	    stemp4, stemp5, stemp6, stemp7, sx1qtp, sx2qtp, sx1qtt, sx2qtt, 
	    deltel, sahatt[11], betaut;

    /* Fortran I/O blocks */
    static cilist io___63 = { 0, 0, 0, fmt_99, 0 };


    /* Parameter adjustments */
    --fxion;
    --fx;

    /* Function Body */
/*  1    FXHE = FX(12) */
    fxhe = fx[12];
    emax = fxhe + 1.;
    ti = 1. / *t;
/* BEGIN SAHA ROUTINE */
/* COMPUTE SAHA K'S */
    stemp = *tl * 2.5 - *pl + const2_1.cmkh;
    nz1 = 1;
    i__1 = nz;
    for (i__ = 1; i__ <= i__1; ++i__) {
	sahatt[i__ - 1] = sahat[i__ - 1] * ti;
	sahak[i__ - 1] = const1_1.cln * (sahau[i__ - 1] + stemp) - sahatt[i__ 
		- 1];
	if (sahak[i__ - 1] < -stol) {
	    goto L12;
	}
	if (sahak[i__ - 1] > stol) {
	    goto L10;
	}
	sahak[i__ - 1] = *betai * exp(sahak[i__ - 1]);
	goto L11;
L10:
	sahak[i__ - 1] = 1e16;
	nz1 = i__ + 1;
L11:
	;
    }
    i__ = nz + 1;
L12:
    nz0 = i__ - 1;
    nz1 = min(nz,nz1);
    lnohe = TRUE_;
    lnohe2 = TRUE_;
    if (fxhe < 1e-10) {
	goto L13;
    }
    sahek0 = const1_1.cln * (sahau[11] + stemp) - sahet0 / *t;
    if (sahek0 < -stol) {
	goto L13;
    }
    lnohe = FALSE_;
    sahek0 = *betai * exp(sahek0);
    sahek1 = const1_1.cln * (sahau[12] + stemp) - sahet1 / *t;
    if (sahek1 < -stol) {
	goto L14;
    }
    lnohe2 = FALSE_;
    sahek1 = *betai * exp(sahek1);
    goto L15;
L13:
    sahex1 = 0.;
L14:
    sahex2 = 0.;
L15:
/* BEGIN ITERATIONS FOR SOLUTION OF E */
    i__1 = maxs;
    for (isaha = 1; isaha <= i__1; ++isaha) {
	++(*ksaha);
	ep1 = 1. / (e + 1.);
	ep1e = ep1 / e;
	ep12 = ep1 * ep1;
	eep1 = e * ep1;
	c33 = -e * (e + 1.);
	r3 = e;
	if (nz0 <= 0) {
	    goto L22;
	}
	i__2 = nz0;
	for (i__ = 1; i__ <= i__2; ++i__) {
	    div = 1. / (sahak[i__ - 1] + eep1);
	    temp8 = sahak[i__ - 1] * div;
	    sahax[i__ - 1] = temp8;
	    temp8 *= fx[i__];
	    r3 -= temp8;
	    temp8 = temp8 * eep1 * div;
	    c33 -= temp8;
	    fxs[i__ - 1] = temp8;
/* L21: */
	}
L22:
	c33 *= ep1e;
	r3 -= fxhe * (sahex1 + sahex2 + sahex2);
	lfin = abs(r3) < stolee;
	if (lnohe) {
	    goto L25;
	}
	c22 = sahek0 + eep1;
	c23 = sahex1 * ep12;
	c32 = fxhe;
	r2 = sahek0 * (1. - sahex1 - sahex2) - sahex1 * eep1;
	if (lnohe2) {
	    goto L23;
	}
	c11 = eep1;
	c12 = -sahek1;
	c13 = sahex2 * ep12;
	c21 = sahek0;
	c31 = fxhe * 2.;
	r1 = sahex1 * sahek1 - sahex2 * eep1;
/* REDUCTION OF SAHA MATRIX TO DIAGONAL FORM */
	cr12 = -c21 / c11;
	cr13 = -c31 / c11;
	c22 += cr12 * c12;
	c32 += cr13 * c12;
	c23 += cr12 * c13;
	c33 += cr13 * c13;
	if (r1 == 0.) {
	    goto L210;
	}
	d__1 = abs(r1);
	r1l = d_lg10(&d__1);
	if (cr12 == 0.) {
	    goto L200;
	}
	d__1 = abs(cr12);
	cr12l = d_lg10(&d__1);
	fact = cr12l + r1l;
	if (fact < -38.) {
	    goto L200;
	}
	r2 += cr12 * r1;
L200:
	if (cr13 == 0.) {
	    goto L210;
	}
	d__1 = abs(cr13);
	cr13l = d_lg10(&d__1);
	fact = cr13l + r1l;
	if (fact < -38.) {
	    goto L210;
	}
	r3 += cr13 * r1;
L210:
/* ENTRY FOR NO FULLY IONIZED HELIUM (SAHEX2 = 0.0) */
L23:
	cr23 = -c32 / c22;
	c33 += cr23 * c23;
	r3 += cr23 * r2;
/* ENTRY FOR NEUTRAL HELIUM */
L25:
	delte = r3 / c33;
	if (lnohe) {
	    goto L26;
	}
	deltx1 = (r2 - c23 * delte) / c22;
	sahex1 += deltx1;
/* Computing MAX */
	d__1 = 0., d__2 = min(1.,sahex1);
	sahex1 = max(d__1,d__2);
	if (lnohe2) {
	    goto L26;
	}
/* CC   STATEMENT RECALCULATED FOR DEC-20 SYSTEM */
	if (c12 == 0. || deltx1 == 0.) {
	    goto L100;
	}
	d__1 = abs(c12);
	c12l = d_lg10(&d__1);
	d__1 = abs(deltx1);
	delx1l = d_lg10(&d__1);
	fact1 = c12l + delx1l;
	if (fact1 >= -38.) {
	    goto L100;
	}
	fact1 = -38.;
	fact1 = exp(const1_1.cln * fact1) * d_sign(&c_b17, &c12) * d_sign(&
		c_b17, &deltx1);
	goto L105;
L100:
	fact1 = c12 * deltx1;
L105:
	if (c13 == 0. || delte == 0.) {
	    goto L110;
	}
	d__1 = abs(c13);
	c13l = d_lg10(&d__1);
	d__1 = abs(delte);
	deltel = d_lg10(&d__1);
	fact2 = c13l + deltel;
	if (fact2 >= -38.) {
	    goto L110;
	}
	fact2 = -38.;
	fact2 = exp(const1_1.cln * fact2) * d_sign(&c_b17, &c13) * d_sign(&
		c_b17, &delte);
	goto L115;
L110:
	fact2 = c13 * delte;
L115:
	deltx2 = (r1 - fact1 - fact2) / c11;
	sahex2 += deltx2;
/* Computing MAX */
	d__1 = 0., d__2 = min(1.,sahex2);
	sahex2 = max(d__1,d__2);
L26:
	e += delte;
/* Computing MAX */
	d__1 = 1e-11, d__2 = min(emax,e);
	e = max(d__1,d__2);
	lfin = lfin && abs(delte) < stolee;
	if (lfin) {
	    goto L29;
	}
/* L28: */
    }
    io___63.ciunit = luout_1.ishort;
    s_wsfe(&io___63);
    do_fio(&c__1, (char *)&(*tl), (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&(*pl), (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&e, (ftnlen)sizeof(doublereal));
    do_fio(&c__1, (char *)&delte, (ftnlen)sizeof(doublereal));
    e_wsfe();
/* SYSTEM HAS BEEN SOLVED FOR E */
L29:
    *emu = e * *amu;
    *rmu = const2_1.cgas * (*emu + *amu);
    *d__ = *beta * *p / (*rmu * *t);
    *dl = d_lg10(d__);
    fxion[1] = 0.;
    if (nz0 >= 7) {
	fxion[1] = sahax[6];
    }
    fxion[2] = sahex1;
    fxion[3] = sahex2;
    if (*latmo) {
	goto L60;
    }
/* COMPUTE FIRST DERIVATIVES */
    rmub = *rmu * *betai;
    r3t = 0.;
    r3p = 0.;
    if (nz0 <= 0) {
	goto L31;
    }
    i__1 = nz0;
    for (i__ = nz1; i__ <= i__1; ++i__) {
	r3p -= fxs[i__ - 1];
/* KC 2025-05-30 fixed "DO termination statement which is not END DO or CONTINUE" */
/*  30   R3T = R3T -FXS(I)*(2.5D0 + BETA14 + SAHATT(I)) */
	r3t -= fxs[i__ - 1] * (*beta14 + 2.5 + sahatt[i__ - 1]);
/* L30: */
    }
    r3p = -(*betai) * r3p;
L31:
    if (lnohe) {
	goto L33;
    }
    sahex0 = 1. - sahex1 - sahex2;
    sk0qt = *beta14 + 2.5 + sahet0 * ti;
    temp = sahek0 * sahex0;
    r2t = temp * sk0qt;
    r2p = -temp * *betai;
    if (lnohe2) {
	goto L32;
    }
    sk1qt = *beta14 + 2.5 + sahet1 * ti;
    temp = sahek1 * sahex1;
    r1t = temp * sk1qt;
    r1p = -temp * *betai;
    r2t += cr12 * r1t;
    r2p += cr12 * r1p;
    r3t += cr13 * r1t;
    r3p += cr13 * r1p;
L32:
    r3t += cr23 * r2t;
    r3p += cr23 * r2p;
L33:
    sqet = r3t / c33;
    sqep = r3p / c33;
    *qdt = -1. - *beta14 - ep1 * sqet;
    *qdp = *betai - ep1 * sqep;
/* COMPUTE INTERNAL ENERGY TEMPERATURE DERIVATIVE(QUT) */
    usum = 0.;
    if (lnohe) {
	goto L35;
    }
    sx1qt = (r2t - c23 * sqet) / c22;
    sx1qp = (r2p - c23 * sqep) / c22;
    sx2qt = 0.;
    sx2qp = 0.;
    if (lnohe2) {
	goto L34;
    }
    sx2qt = (r1t - c12 * sx1qt - c13 * sqet) / c11;
    sx2qp = (r1p - c12 * sx1qp - c13 * sqep) / c11;
L34:
    sx0qt = -(sx1qt + sx2qt);
    sx0qp = -(sx1qp + sx2qp);
    usum = fxhe * (sx1qt * sahet0 + sx2qt * (sahet0 + sahet1));
L35:
    if (nz0 <= 0) {
	goto L37;
    }
    stemp = *beta14 + 2.5 - ep1e * sqet;
    i__1 = nz0;
    for (i__ = nz1; i__ <= i__1; ++i__) {
	fxt[i__ - 1] = fxs[i__ - 1] * (stemp + sahatt[i__ - 1]);
/* KC 2025-05-30 fixed "DO termination statement which is not END DO or CONTINUE" */
/*  36   USUM = USUM + FXT(I)*SAHAT(I) */
	usum += fxt[i__ - 1] * sahat[i__ - 1];
/* L36: */
    }
L37:
    betaut = (*beta14 + 2.) * .75;
    ramu = const2_1.cgas * *amu;
    qut = ramu * ((e + 1.) * (betaut + *betai * 3. * *beta14) + betaut * sqet 
	    + usum * ti);
/* COMPUTE SPECIFIC HEAT(QCP) AND ADIABATIC GRADIENT(DELA) */
    pdt = *p / (*d__ * *t);
    pdtq = pdt * *qdt;
    *qcp = qut - pdtq;
    qcpi = 1. / *qcp;
    *dela = -pdtq * qcpi;
    if (! (*lderiv)) {
	goto L60;
    }
/* COMPUTE DERIVATIVES OF QDT,QCP,DELA */
    beta16 = *betai * 4. * *beta14;
    r3t = 0.;
    r3p = 0.;
    utsum = 0.;
    upsum = 0.;
    if (nz0 <= 0) {
	goto L42;
    }
/* Computing 2nd power */
    d__1 = e * (e + 1.);
    etemp = (e + 1. + e) / (d__1 * d__1);
    stemp1 = *beta14 + 2.5 - sqet * ep1e;
    stemp2 = -(*betai) - sqep * ep1e;
    stemp3 = etemp * sqep * sqet - *betai * *beta14;
/* Computing 2nd power */
    d__1 = sqet;
    stemp4 = etemp * (d__1 * d__1) + beta16;
    i__1 = nz0;
    for (i__ = nz1; i__ <= i__1; ++i__) {
	stemp5 = (stemp1 + sahatt[i__ - 1]) * (1. - sahax[i__ - 1] * 2.);
	stemp6 = fxs[i__ - 1] * (stemp4 - sahatt[i__ - 1]) + fxt[i__ - 1] * 
		stemp5;
	r3t -= stemp6;
	utsum += sahat[i__ - 1] * (stemp6 - fxt[i__ - 1]);
	stemp7 = fxs[i__ - 1] * (stemp3 + stemp2 * stemp5);
	r3p -= stemp7;
/* KC 2025-05-30 fixed "DO termination statement which is not END DO or CONTINUE" */
/*  41   UPSUM = UPSUM + SAHAT(I)*STEMP7 */
	upsum += sahat[i__ - 1] * stemp7;
/* L41: */
    }
L42:
    if (lnohe) {
	goto L44;
    }
    stemp = sahex1 * 2. * ep1 * sqet;
/* Computing 2nd power */
    d__1 = sk0qt;
    r2t = sahek0 * (sahex0 * (beta16 - sahet0 * ti + d__1 * d__1) + sx0qt * 
	    2. * sk0qt) + ep12 * (stemp * sqet - sx1qt * 2. * sqet);
    r2p = sahek0 * (sahex0 * *betai * (-(*beta14) - sk0qt) + sx0qp * sk0qt - *
	    betai * sx0qt) + ep12 * (stemp * sqep - sx1qp * sqet - sx1qt * 
	    sqep);
    if (lnohe2) {
	goto L43;
    }
    stemp = sahex2 * 2. * ep1 * sqet;
/* Computing 2nd power */
    d__1 = sk1qt;
    r1t = sahek1 * (sahex1 * (beta16 - sahet1 * ti + d__1 * d__1) + sx1qt * 
	    2. * sk1qt) + ep12 * (stemp * sqet - sx2qt * 2. * sqet);
    r1p = sahek1 * (sahex1 * *betai * (-(*beta14) - sk1qt) + sx1qp * sk1qt - *
	    betai * sx1qt) + ep12 * (stemp * sqep - sx2qp * sqet - sx2qt * 
	    sqep);
    r2t += cr12 * r1t;
    r2p += cr12 * r1p;
    r3p += cr13 * r1p;
    r3t += cr13 * r1t;
L43:
    r3p += cr23 * r2p;
    r3t += cr23 * r2t;
L44:
    sqett = r3t / c33;
    sqetp = r3p / c33;
/* Computing 2nd power */
    d__1 = ep1 * sqet;
    *qdtt = -beta16 + d__1 * d__1 - ep1 * sqett;
    *qdtp = *betai * *beta14 + ep12 * sqet * sqep - ep1 * sqetp;
    if (nz0 <= 0) {
	goto L46;
    }
    stemp = ep1e * sqett;
    stemp1 = ep1e * sqetp;
    i__1 = nz0;
    for (i__ = nz1; i__ <= i__1; ++i__) {
	utsum -= fxs[i__ - 1] * sahat[i__ - 1] * stemp;
/* KC 2025-05-30 fixed "DO termination statement which is not END DO or CONTINUE" */
/*  45   UPSUM = UPSUM - FXS(I)*SAHAT(I)*STEMP1 */
	upsum -= fxs[i__ - 1] * sahat[i__ - 1] * stemp1;
/* L45: */
    }
L46:
    if (lnohe) {
	goto L48;
    }
    sx1qtt = (r2t - c23 * sqett) / c22;
    sx1qtp = (r2p - c23 * sqetp) / c22;
    if (lnohe2) {
	goto L47;
    }
    sx2qtt = (r1t - c12 * sx1qtt - c13 * sqett) / c11;
    sx2qtp = (r1p - c12 * sx1qtp - c13 * sqetp) / c11;
    utsum += fxhe * (sahet0 + sahet1) * (sx2qtt - sx2qt);
    upsum += fxhe * (sahet0 + sahet1) * sx2qtp;
L47:
    utsum += fxhe * sahet0 * (sx1qtt - sx1qt);
    upsum += fxhe * sahet0 * sx1qtp;
L48:
    btemp = (e + 1.) * *beta14 * *betai * (*betai * 24. - 9.);
    qqutt = ramu * (btemp + (*beta14 * (*betai * 8. + 1.) + 2.) * .75 * sqet 
	    + betaut * sqett + utsum * ti);
    qqutp = ramu * (btemp * -.25 + ((*beta14 * (*betai * 4. + 1.) + 2.) * 
	    sqep - *beta14 * *betai * sqet) * .75 + betaut * sqetp + upsum * 
	    ti);
    *qcpt = qcpi * (qqutt + pdtq * (*qdt + 1.) - pdt * *qdtt);
    *qcpp = qcpi * (qqutp - pdtq * (1. - *qdp) - pdt * *qdtp);
    *qat = -1. - *qdt - *qcpt + *qdtt / *qdt;
    *qap = 1. - *qdp - *qcpp + *qdtp / *qdt;
L60:
    return 0;
} /* eqsaha_ */

